#include "xmlreader.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "bufio.h"
#include "helpers.h"
#include "errors.h"
#include "utf8.h"
#include "array.h"
#include "base64.h"

enum xmlreader_state_enum {
  XMLREADER_STATE_TEXT,
  XMLREADER_STATE_LT,
  XMLREADER_STATE_LBRACKET,
  XMLREADER_STATE_EXLMN,
  XMLREADER_STATE_ELEMENT_NAME,
  XMLREADER_STATE_ATTRIBUTE_NAME,
  XMLREADER_STATE_AFTER_ATTRIBUTE_NAME,
  XMLREADER_STATE_BEFORE_ATTRIBUTE_VALUE,
  XMLREADER_STATE_ATTRIBUTE_VALUE_QUOT,
  XMLREADER_STATE_ATTRIBUTE_VALUE_APOS,
  XMLREADER_STATE_AFTER_ATTRIBUTE_VALUE,
  XMLREADER_STATE_BEFORE_ATTRIBUTE,
  XMLREADER_STATE_EMPTY_ELEMENT_CLOSE,
  XMLREADER_STATE_ELEMENT_END,
  XMLREADER_STATE_ELEMENT_END_CLOSE,
  XMLREADER_STATE_PI,
  XMLREADER_STATE_PI_AFTER_NAME,
  XMLREADER_STATE_PI_CLOSE,
  XMLREADER_STATE_PI_DATA,
  XMLREADER_STATE_PI_SKIP_DATA,
};

struct xmlreader_attribute_t {
  char* name;
  char* namespace;
  char* value;
};

struct xmlreader_element_t {
  char* name;
  char* namespace;
  array_t* attributes;
};

struct xmlreader_token_t {
  int type;
  union {
    struct xmlreader_element_t* el;
    char* cdata;
  } u;
};

struct xmlreader_tag_t {
  char* name;
  struct xmlreader_element_t* el;
};

void xmlreader_init (xmlreader_t* reader) {
  memset (reader, 0, sizeof (xmlreader_t));
  bufio_reader_init (&reader->bufio);
  reader->iterator = -1;
  reader->stack = array_new (sizeof (struct xmlreader_token_t), 5);
  reader->state = XMLREADER_STATE_TEXT;
  reader->tags = array_new (sizeof (struct xmlreader_tag_t), 5);
}

static void xmlreader_element_free (struct xmlreader_element_t* el) {
  free (el->name);
  if (el->attributes != NULL) {
    int i = 0;
    int len = array_length (el->attributes);
    for (i = 0; i < len; i++) {
      struct xmlreader_attribute_t* attribute = array_get (el->attributes, i);
      free (attribute->name);
      if (attribute->value != NULL)
        free (attribute->value);
    }
    array_free (el->attributes);
  }
  free (el);
}

void xmlreader_stack_clean (xmlreader_t* reader, int start) {
  int len = array_length (reader->stack);
  if (len == 0 || len == start) return;
  int i = len;
  for (i = start; i < len; i++) {
    struct xmlreader_token_t* child = array_get (reader->stack, i);
    switch (child->type) {
    case XML_START_ELEMENT: {
      struct xmlreader_element_t* el = child->u.el;
      xmlreader_element_free (el);
      break;
    }
    case XML_TEXT:
      if (child->u.cdata != NULL)
        free (child->u.cdata);
    }
  }
  reader->stack->length = start;
}

void xmlreader_reset (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_reset: reader is null");
  reader->iterator = -1;
  bufio_reader_reset (&reader->bufio);
  reader->state = XMLREADER_STATE_TEXT;
  xmlreader_stack_clean (reader, 0);
  if (reader->tags != NULL) {
    int len = array_length (reader->tags);
    int i = 0;
    for (i = 0; i < len; i++) {
      struct xmlreader_tag_t* tag = array_get (reader->tags, i);
      free (tag->name);
    }
    reader->tags->length = 0;
  }
}

static inline bool is_space (uint32_t u) {
  return (u == ' ' || u == '\t' || u == '\r' || u == '\n');
}

static inline bool is_name_start_char (uint32_t u) {
  return ((u >= 0x0061 && u <= 0x007A) || u == ':' || u == '_' ||
          (u >= 0x0041 && u <= 0x005A) || (u >= 0xC0 && u <= 0xD6) ||
          (u >= 0xD8 && u <= 0xF6) || (u >= 0xF8 && u <= 0x2FF) ||
          (u >= 0x370 && u <= 0x37D) || (u >= 0x37F && u <= 0x1FFF) ||
          (u >= 0x200C && u <= 0x200D) || (u >= 0x2070 && u <= 0x218F) ||
          (u >= 0x2C00 && u <= 0x2FEF) || (u >= 0x3001 && u <= 0xD7FF) ||
          (u >= 0xF900 && u <= 0xFDCF) || (u >= 0xFDF0 && u <= 0xFFFD) ||
          (u >= 0x10000 && u <= 0xEFFFF));
}

static inline bool is_name_char (uint32_t u) {
  return (is_name_start_char (u) || u == '-' || u == '.' ||
          (u >= 0x0030 && u <= 0x0039) || (u >= 0x0300 && u <= 0x036F) ||
          (u >= 0x203F && u <= 0x2040));
}

static uint32_t xmlreader_internal_name (xmlreader_t* reader) {
  uint32_t c = 0;
  
  if (reader->tmpbuf == NULL) {
    reader->tmpbuf = malloc (255);
    if (reader->tmpbuf == NULL)
      fatal ("xmlreader_internal_name: malloc failed");
    *reader->tmpbuf = 0;
  }
  int len = strlen (reader->tmpbuf);
  char* ptr = reader->tmpbuf+len;
  int err = 0;
  int width = 0;

  if (len == 0) {
    c = bufio_reader_get_rune (&reader->bufio);
    if (reader->bufio.err != 0) {
      reader->err = reader->bufio.err;
      return 0;
    }
    if (!is_name_start_char (c)) {
      reader->err = ERR_XML_SYNTAX;
      return 0;
    }
    
    err = utf8_append (ptr, c);
    if (err != 0) {
      reader->err = err;
      return 0;
    }
    width = utf8_width_of_uint32 (c);
    len += width;
    ptr += width;
  }

  while (1) {
    c = bufio_reader_get_rune (&reader->bufio);
    if (reader->bufio.err != 0) {
      reader->err = reader->bufio.err;
      return 0;
    }
    if (!is_name_char (c))
      break;
    width = utf8_width_of_uint32 (c);
    if (len % 255 + width >= 254) {
      reader->tmpbuf = realloc (reader->tmpbuf, (len / 255 + 1) * 255);
      if (reader->tmpbuf == NULL)
        fatal ("xmlreader_internal_name: realloc failed");
      ptr = reader->tmpbuf + len;
    }
    err = utf8_append (ptr, c);
    if (err != 0) {
      reader->err = err;
      return 0;
    }
    len += width;
    ptr += width;
  }
  *ptr = 0;

  return c;
}

static void xmlreader_internal_text (xmlreader_t* reader) {
  bool skip = false;
  if (array_length (reader->tags) < 2)
    skip = true;
  
  char* text = NULL;
  int len = 0;
  
  uint8_t c = 0;

  while (1) {
    c = bufio_reader_get_byte (&reader->bufio);
    if (reader->bufio.err != 0) {
      reader->err = reader->bufio.err;
      return;
    }
    
    if (c == '<') {
      reader->state = XMLREADER_STATE_LT;
      return;
    }
      
    if (!skip) {
      if (text == NULL) {
        struct xmlreader_token_t* child = array_get_last (reader->stack);
        if (child->type == XML_TEXT) 
          text = child->u.cdata;
        else {
          text = malloc (4096);
          if (text == NULL)
            fatal ("xmlreader_internal_text: malloc failed");
          *text = 0;
          struct xmlreader_token_t child;
          child.type = XML_TEXT;
          child.u.cdata = text;
          array_append (reader->stack, &child);
        }
        len = strlen (text);
      }
      if (len % 4096 == 4095) {
        text = realloc (text, len + 4096);
        if (text == NULL)
          fatal ("xmlreader_internal_text: realloc failed");
        struct xmlreader_token_t* child = array_get_last (reader->stack);
        if (child->type != XML_TEXT)
          fatal ("xmlreader_internal_text: wrong child");
        child->u.cdata = text;
      }
      *(text + len++) = c;
      *(text + len) = 0;
    }
  }
}

static void xmlreader_internal_attribute_value (xmlreader_t* reader, const char delim) {
  if (reader->tmpbuf == NULL) {
    reader->tmpbuf = malloc (255);
    if (reader->tmpbuf == NULL)
      fatal ("xmlreader_internal_attribute_value: malloc failed");
    *reader->tmpbuf = 0;
  }
  int len = strlen (reader->tmpbuf);
  char* ptr = reader->tmpbuf + len;
  uint32_t c = 0;
  
  while (1) {
    c = bufio_reader_get_byte (&reader->bufio);
    if (reader->bufio.err != 0) {
      *ptr = 0;
      reader->err = reader->bufio.err;
      return;
    }
    if (c == delim) {
      *ptr = 0;
      break;
    }
    if (len % 255 == 254) {
      reader->tmpbuf = realloc (reader->tmpbuf, len + 255);
      if (reader->tmpbuf == NULL)
        fatal ("xmlreader_internal_attribute_value: realloc failed");
      ptr = reader->tmpbuf + len;
    }
    *ptr++ = c;
    len++;
  }
}

static char* xmlreader_internal_resolve_namespace (xmlreader_t* reader, char* prefix, int prefix_len) {
  int len = array_length (reader->tags);
  int i = 0, j = 0;
  for (i = len-1; i >= 0; i--) {
    struct xmlreader_tag_t* tag = array_get (reader->tags, i);
    if (tag->el->attributes != NULL) {
      int llen = array_length (tag->el->attributes);
      for (j = 0; j < llen; j++) {
        struct xmlreader_attribute_t* attribute = array_get (tag->el->attributes, j);
        if (prefix == NULL) {
          if (strcmp ("xmlns", attribute->name) == 0)
            return attribute->value;
        } else {
          if (strlen (attribute->name) == prefix_len + 6 &&
              strncmp (attribute->name, "xmlns:", 6) == 0 &&
              strncmp (attribute->name + 6, prefix, prefix_len) == 0)
            return attribute->value;
        }
      }
    }
  }
  return NULL;
}

static void xmlreader_internal_process_namespaces (xmlreader_t* reader, struct xmlreader_element_t* el) {
  char* ns = NULL;
  char* colon = strchr (el->name, ':');
  int prefix_len = 0;
  if (colon != NULL) {
    prefix_len = colon - el->name;
    ns = xmlreader_internal_resolve_namespace (reader, el->name, prefix_len);
    if (ns != NULL) {
      el->namespace = ns;
      memmove (el->name, el->name + prefix_len+1, strlen (el->name) - prefix_len);
    }
  } else {
    ns = xmlreader_internal_resolve_namespace (reader, NULL, 0);
    if (ns != NULL)
      el->namespace = ns;
  }
  
  if (el->attributes != NULL) {
    int len = array_length (el->attributes);
    int i = 0;
    for (i = 0; i < len; i++) {
      struct xmlreader_attribute_t* attribute = array_get (el->attributes, i);
      colon = strchr (attribute->name, ':');
      if (colon != NULL) {
        prefix_len = colon - attribute->name;
        ns = xmlreader_internal_resolve_namespace (reader, attribute->name, prefix_len);
        if (ns != NULL) {
          attribute->namespace = ns;
          memmove (attribute->name, attribute->name + prefix_len + 1,
                   strlen (attribute->name) - prefix_len);
        }
      }
    }
  }
}

void xmlreader_read (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_read: reader is null");
  
  uint8_t c = 0;
  
  while (1) {
    c = bufio_reader_get_byte (&reader->bufio);
    if (reader->bufio.err != 0) {
      reader->err = reader->bufio.err;
      return;
    }
    
    switch (reader->state) {
    case XMLREADER_STATE_TEXT:
      bufio_reader_unget_byte (&reader->bufio);
      xmlreader_internal_text (reader);
      if (reader->err != 0) return;
      break;

    case XMLREADER_STATE_LT:
      switch (c) {
      case '/':
        reader->state = XMLREADER_STATE_ELEMENT_END;
        if (array_length (reader->stack) == 0) {
          reader->err = ERR_XML_SYNTAX;
          return;
        }
        break;

      case '?':
        reader->state = XMLREADER_STATE_PI;
        break;

      case '!':
        reader->state = XMLREADER_STATE_EXLMN;
        break;

      case '[':
        reader->state = XMLREADER_STATE_LBRACKET;
        break;

      default:
        reader->state = XMLREADER_STATE_ELEMENT_NAME;
        bufio_reader_unget_byte (&reader->bufio);
        break;
        
      }
      break;
    
    case XMLREADER_STATE_ELEMENT_NAME: {
      bufio_reader_unget_byte (&reader->bufio);
      uint32_t nextc = xmlreader_internal_name (reader);
      if (reader->err != 0) return;
      
      struct xmlreader_element_t* el = malloc (sizeof (struct xmlreader_element_t));
      if (el == NULL)
        fatal ("xmlreader_read: malloc failed");
      memset (el, 0, sizeof (struct xmlreader_element_t));

      struct xmlreader_tag_t tag = { strdup (reader->tmpbuf), el };
      array_append (reader->tags, &tag);

      el->name = reader->tmpbuf;
      reader->tmpbuf = NULL;

      struct xmlreader_token_t child;
      child.type = XML_START_ELEMENT;
      child.u.el = el;
      array_append (reader->stack, &child);
      
      if (is_space (nextc))
        reader->state = XMLREADER_STATE_BEFORE_ATTRIBUTE;
      else if (nextc == '/')
        reader->state = XMLREADER_STATE_EMPTY_ELEMENT_CLOSE;
      else if (nextc == '>') {
        reader->state = XMLREADER_STATE_TEXT;
        xmlreader_internal_process_namespaces (reader, el);
        if (array_length (reader->tags) == 1)
          return;
      } else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;
    }
      
    case XMLREADER_STATE_ELEMENT_END: {
      bufio_reader_unget_byte (&reader->bufio);
      uint32_t nextc = xmlreader_internal_name (reader);
      if (reader->err != 0) return;

      struct xmlreader_tag_t* tag = array_get_last (reader->tags);
      if (strcmp (tag->name, reader->tmpbuf) != 0) {
        printf ("wrong end element %s %s\n", tag->name, reader->tmpbuf);
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      free (reader->tmpbuf);
      reader->tmpbuf = NULL;
      
      free (tag->name);
      array_delete_last (reader->tags);
      struct xmlreader_token_t child;
      child.type = XML_END_ELEMENT;
      child.u.el = NULL;
      array_append (reader->stack, &child);

      if (is_space (nextc))
        reader->state = XMLREADER_STATE_ELEMENT_END_CLOSE;
      else if (nextc == '>') {
        reader->state = XMLREADER_STATE_TEXT;

        int len = array_length (reader->tags);
        if (len < 2)
          return;
      } else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;
    }

    case XMLREADER_STATE_ELEMENT_END_CLOSE:
      if (is_space (c))
        ; // same state
      else if (c == '>') {
        reader->state = XMLREADER_STATE_TEXT;

        int len = array_length (reader->tags);
        if (len < 2)
          return;
      } else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;
      
    case XMLREADER_STATE_EMPTY_ELEMENT_CLOSE: {
      if (c != '>') {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      reader->state = XMLREADER_STATE_TEXT;

      struct xmlreader_token_t* child = array_get_last (reader->stack);
      if (child->type != XML_START_ELEMENT)
        fatal ("xmlreader_read: wrong stack");
      struct xmlreader_element_t* el = child->u.el;
      xmlreader_internal_process_namespaces (reader, el);

      struct xmlreader_token_t cchild;
      cchild.type = XML_END_ELEMENT;
      cchild.u.el = NULL;
      array_append (reader->stack, &cchild);

      struct xmlreader_tag_t* tag = array_get_last (reader->tags);
      free (tag->name);
      array_delete_last (reader->tags);

      int len = array_length (reader->tags);
      if (len < 2)
        return;
      break;
    }
      
    case XMLREADER_STATE_BEFORE_ATTRIBUTE:
      if (is_space (c))
        ; // same stat
      else if (c == '/')
        reader->state = XMLREADER_STATE_EMPTY_ELEMENT_CLOSE;
      else if (c == '>') {
        reader->state = XMLREADER_STATE_TEXT;
        struct xmlreader_token_t* child = array_get_last (reader->stack);
        if (child->type != XML_START_ELEMENT)
          fatal ("xmlreader_read: wrong stack");
        struct xmlreader_element_t* el = child->u.el;
        xmlreader_internal_process_namespaces (reader, el);
        struct xmlreader_token_t cchild;
        cchild.type = XML_END_ELEMENT;
        cchild.u.el = NULL;
        array_append (reader->stack, &cchild);
        int len = array_length (reader->tags);
        if (len == 1)
          return;
      } else {
        bufio_reader_unget_byte (&reader->bufio);
        reader->state = XMLREADER_STATE_ATTRIBUTE_NAME;
      }
      break;
      
    case XMLREADER_STATE_ATTRIBUTE_NAME: {
      bufio_reader_unget_byte (&reader->bufio);
      uint32_t nextc = xmlreader_internal_name (reader);
      if (reader->err != 0) return;

      if (is_space (nextc))
        reader->state = XMLREADER_STATE_AFTER_ATTRIBUTE_NAME;
      else if (nextc == '=')
        reader->state = XMLREADER_STATE_BEFORE_ATTRIBUTE_VALUE;
      else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }

      struct xmlreader_token_t* child = array_get_last (reader->stack);
      if (child->type != XML_START_ELEMENT)
        fatal ("xmlreader_read: wrong stack");
      struct xmlreader_element_t* el = child->u.el;
      struct xmlreader_attribute_t attribute = { reader->tmpbuf, NULL, NULL};
      if (el->attributes == NULL)
        el->attributes = array_new (sizeof (struct xmlreader_attribute_t), 6);
      array_append (el->attributes, &attribute);
      reader->tmpbuf = NULL;
      break;
    }
      
    case XMLREADER_STATE_AFTER_ATTRIBUTE_NAME:
      if (is_space (c))
        ; // same state
      else if (c == '=')
        reader->state = XMLREADER_STATE_BEFORE_ATTRIBUTE_VALUE;
      else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;
      
    case XMLREADER_STATE_BEFORE_ATTRIBUTE_VALUE:
      if (is_space (c))
        ; // same state
      else if (c == '\'')
        reader->state = XMLREADER_STATE_ATTRIBUTE_VALUE_APOS;
      else if (c == '"')
        reader->state = XMLREADER_STATE_ATTRIBUTE_VALUE_QUOT;
      else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;

    case XMLREADER_STATE_ATTRIBUTE_VALUE_APOS:
      bufio_reader_unget_byte (&reader->bufio);
      xmlreader_internal_attribute_value (reader, '\'');
      if (reader->err != 0) return;
      struct xmlreader_token_t* child = array_get_last (reader->stack);
      if (child->type != XML_START_ELEMENT)
        fatal ("xmlreader_read: wrong stack");
      struct xmlreader_element_t* el = child->u.el;
      struct xmlreader_attribute_t* attribute = array_get_last (el->attributes);
      attribute->value = reader->tmpbuf;
      reader->tmpbuf = NULL;
      reader->state = XMLREADER_STATE_AFTER_ATTRIBUTE_VALUE;
      break;

    case XMLREADER_STATE_ATTRIBUTE_VALUE_QUOT: {
      bufio_reader_unget_byte (&reader->bufio);
      xmlreader_internal_attribute_value (reader, '"');
      if (reader->err != 0) return;
      struct xmlreader_attribute_t* attribute = array_get_last (el->attributes);
      attribute->value = reader->tmpbuf;
      reader->tmpbuf = NULL;
      reader->state = XMLREADER_STATE_AFTER_ATTRIBUTE_VALUE;
      break;
    }
      
    case XMLREADER_STATE_AFTER_ATTRIBUTE_VALUE: {
      if (is_space (c))
        reader->state = XMLREADER_STATE_BEFORE_ATTRIBUTE;
      else if (c == '/')
        reader->state = XMLREADER_STATE_EMPTY_ELEMENT_CLOSE;
      else if (c == '>') {
        reader->state = XMLREADER_STATE_TEXT;
        xmlreader_internal_process_namespaces (reader, el);
        if (array_length (reader->tags) == 1)
          return;
      } else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;
    }

    case XMLREADER_STATE_PI: {
      bufio_reader_unget_byte (&reader->bufio);
      uint32_t nextc = xmlreader_internal_name (reader);
      if (reader->err != 0) return;

      if (is_space (nextc))
        reader->state = XMLREADER_STATE_PI_AFTER_NAME;
      else if (nextc == '?')
        reader->state = XMLREADER_STATE_PI_CLOSE;
      else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;
    }

    case XMLREADER_STATE_PI_AFTER_NAME:
      if (is_space (c))
        ; // same state
      else {
        if (strcmp ("xml", reader->tmpbuf) == 0) {
          reader->state = XMLREADER_STATE_PI_DATA;
          *reader->tmpbuf = c;
          *(reader->tmpbuf + 1) = 0;
        } else {
          free (reader->tmpbuf);
          reader->tmpbuf = NULL;
          reader->state = XMLREADER_STATE_PI_SKIP_DATA;
        }
      }        
      break;

    case XMLREADER_STATE_PI_DATA:
      if (c == '?') {
        int len = strlen (reader->tmpbuf);
        char* ptr = reader->tmpbuf;
        if (len < 12 || strncmp ("version", ptr, 7) != 0) {
          reader->err = ERR_XML_SYNTAX;
          return;
        }
        len -= 7;
        ptr += 7;
        while (len > 0 && is_space (*ptr)) { len--; ptr++; }
        if (len-- > 0 && *ptr++ != '=') {
          reader->err = ERR_XML_SYNTAX;
          return;
        }
        while (len > 0 && is_space (*ptr)) { len--; ptr++; }
        char delim = *ptr++; len--;
        if (len < 4 || (delim != '\'' && delim != '"')) {
          reader->err = ERR_XML_SYNTAX;
          return;
        }
        if (strncmp ("1.0", ptr, 3) != 0 || *(ptr+3) != delim) {
          reader->err = ERR_XML_SYNTAX;
          return;
        }
        len -= 4;
        ptr += 4;
        while (len > 0 && is_space (*ptr)) { len--; ptr++; }
        if (len > 0) {
          if (len < 8 || strncmp ("encoding", ptr, 8) != 0) {
            reader->err = ERR_XML_SYNTAX;
            return;
          }
          len -= 8;
          ptr += 8;
          while (len >0 && is_space (*ptr)) { len--; ptr++; }
          if (len == 0) {
            reader->err = ERR_XML_SYNTAX;
            return;
          }
          delim = *ptr++;
          len--;
          if (len < 1 || delim != '\'' || delim != '"') {
            reader->err = ERR_XML_SYNTAX;
            return;
          }
          if (len < 6 || strncasecmp ("utf-8", ptr, 3) != 0 || *(ptr+3) != delim) {
            reader->err = ERR_XML_SYNTAX;
            return;
          }        
        }
        free (reader->tmpbuf);
        reader->tmpbuf = NULL;
        reader->state = XMLREADER_STATE_PI_CLOSE;
      } else {
        int len = strlen (reader->tmpbuf);
        if (len % 255 == 254) {
          reader->tmpbuf = realloc (reader->tmpbuf, len + 255);
          if (reader->tmpbuf == NULL)
            fatal ("xmlreader_read: realloc failed");
        }
        *(reader->tmpbuf + len) = c;
        *(reader->tmpbuf + len+1) = 0;
      }
      break;

    case XMLREADER_STATE_PI_SKIP_DATA:
      if (c == '?')
        reader->state = XMLREADER_STATE_PI_CLOSE;
      else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;

    case XMLREADER_STATE_PI_CLOSE:
      if (c == '>')
        reader->state = XMLREADER_STATE_TEXT;
      else {
        reader->err = ERR_XML_SYNTAX;
        return;
      }
      break;
      
    default:
      fatal ("xmlreader_read: unknown state");
    }
  }
}

const char* xmlreader_get_name (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_get_name: reader is null");
  
  struct xmlreader_token_t* child = array_get (reader->stack, reader->iterator);
  if (child->type != XML_START_ELEMENT)
    fatal ("xmlreader_get_name: wrong state 1");

  struct xmlreader_element_t* el = child->u.el;
  return el->name;
}

const char* xmlreader_get_namespace (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_get_name: reader is null");

  struct xmlreader_token_t* child = array_get (reader->stack, reader->iterator);
  if (child->type != XML_START_ELEMENT)
    fatal ("xmlreader_get_name: wrong state 2");
  struct xmlreader_element_t* el = child->u.el;

  if (el->namespace == NULL) {
    return NULL;
  }
  return el->namespace;
}
 
const char* xmlreader_attribute (xmlreader_t* reader, const char* namespace, const char* name) {
  if (reader == NULL)
    fatal ("xmlreader_attribute: reader is null");

  struct xmlreader_token_t* child = array_get (reader->stack, reader->iterator);
  if (child->type != XML_START_ELEMENT)
    fatal ("xmlreader_attribute: wrong nodetype");

  struct xmlreader_element_t* el = child->u.el;
  
  if (el->attributes == NULL)
    return NULL;

  char* value = NULL;
  int len = array_length (el->attributes);
  int i = 0;
  for (i = 0; i < len; i++) {
    struct xmlreader_attribute_t* attribute = array_get (el->attributes, i);
    if (namespace == NULL && attribute->namespace == NULL &&
        strcmp (name, attribute->name) == 0) {
      value = attribute->value;
      attribute->value = NULL;
    } else if (namespace != NULL && attribute->namespace != NULL &&
               strcmp (namespace, attribute->namespace) == 0) {
      value = attribute->value;
      attribute->value = NULL;
    }
  }
  return value;
}

int xmlreader_skip_element (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_skip_element: reader is null");
  
  struct xmlreader_token_t* child = NULL;

  while (1) {
    reader->iterator++;
    child = array_get (reader->stack, reader->iterator);
    
    switch (child->type) {
    case XML_START_ELEMENT:
      xmlreader_skip_element (reader);
      break;
    case XML_END_ELEMENT:
      return 0;
    case XML_TEXT:
      break;
    case XML_ERROR:
      return -1;
    }
  }
}

const char* xmlreader_text (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_text: reader is null");

  char* text = NULL;
  struct xmlreader_token_t* child;

  while (1) {
    reader->iterator++;
    child = array_get (reader->stack, reader->iterator);
    
    switch (child->type) {
    case XML_START_ELEMENT:
      xmlreader_skip_element (reader);
      break;
    case XML_END_ELEMENT:
      return text;
    case XML_TEXT:
      text = child->u.cdata;
      child->u.cdata = NULL;
      break;
    case XML_ERROR:
      return NULL;
    }
  }
  return text;
}

int xmlreader_base64 (xmlreader_t* reader, unsigned char** result, int* result_len) {
  if (reader == NULL)
    fatal ("xmlreader_base64: reader is null");

  char* data = (char*) xmlreader_text (reader);
  if (reader->err != 0) return -1;

  if (data == NULL) {
    *result = NULL;
    *result = 0;
    return 0;
  }

  char* src = data;
  int len = strlen (src);

  *result = malloc (len / 4 * 3);
  if (*result == NULL)
    fatal ("xmlreader_base64: malloc failed");

  unsigned char* dst = *result;
  int dst_len = 0;
  
  while (len > 0) {
    int dlen = 4;
    unsigned char dbuf[4];
    int j = 0;
    for (j = 0; j < 4; j++) {
      if (len == 0) {
        reader->err = ERR_BASE64_DECODE;
        break;
      }

      unsigned char in = src[0];
      src++;
      len--;
      if (in == '=') {
        if (j == 0 || j == 1) {
          // incorrect padding
          reader->err = ERR_BASE64_DECODE;
          break;
        }
        if (j == 2) {
          // "==" is expected, the first "=" is already consumed.
          if (len == 0) {
            reader->err = ERR_BASE64_DECODE;
            break;
          }
          if (src[0] != '=') {
            // incorrect padding
            reader->err = ERR_BASE64_DECODE;
            break;
          }
          src++;
          len--;
        }
        if (len > 0) {
          // trailing garbage
          reader->err = ERR_BASE64_DECODE;
        }
        dlen = j;
        break;
      }
      dbuf[j] = (unsigned char) decoding_table[(int) in];
      if (dbuf[j] == 0xFF) {
        reader->err = ERR_BASE64_DECODE;
        break;
      }
    }
    if (reader->err != 0)
      break;
    
    switch (dlen) {
    case 4:
      dst[2] = (unsigned char) (dbuf[2] << 6 | dbuf[3]);
    case 3:
      dst[1] = (unsigned char) dbuf[1] << 4 | dbuf[2] >> 2;
    case 2:
      dst[0] = (unsigned char) dbuf[0]<< 2 | dbuf[1] >> 4;
    }
    dst += 3;
    dst_len += dlen - 1;
  }
  *result_len = dst_len;
  free (data);
  if (reader->err != 0) {
    return -1;
  }
  return 0;
}

xmlreader_nodetype_enum xmlreader_next (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_next: reader is null");

  reader->iterator++;
  if (reader->iterator == array_length (reader->stack))
    fatal ("xmlreader_next: iterator %d  exceeded stack's length %d", reader->iterator,
           array_length (reader->stack));
  
  struct xmlreader_token_t* child = array_get (reader->stack, reader->iterator);
  return child->type;
}
