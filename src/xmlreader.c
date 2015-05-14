#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include "xmlreader.h"
#include "helpers.h"
#include "bufio.h"
#include "array.h"
#include "utf8.h"
#include "errors.h"
#include "base64.h"

struct attribute_t {
  const char* name;
  const char* value;
};

xmlreader_t* xmlreader_new (int fd) {
  xmlreader_t* reader = malloc (sizeof (xmlreader_t));
  if (reader == NULL)
    fatal ("xmlreader_new: malloc failed");

  reader->buf = bufio_reader_new (fd);
  reader->err = 0;
  reader->saved = (uint32_t) -1;
  reader->nodetype = XML_TEXT;
  reader->attributes = array_new (sizeof (struct attribute_t), 5);
  reader->tags = NULL;
  return reader;
}

void xmlreader_free (xmlreader_t* reader) {
  if (reader == NULL)
    return;

  bufio_reader_free (reader->buf);
  free (reader);
}

void xmlreader_reset (xmlreader_t* reader) {
  reader->err = 0;
  bufio_reader_reset (reader->buf);
  reader->saved = (uint32_t) -1;
  reader->nodetype = XML_TEXT;

  reader->attributes->length = 0;
  
  struct xmlreader_tag_t* t = reader->tags;
  while (t != NULL) {
    struct xmlreader_tag_t* next = t->prev;
    free (t);
    t = next;
  }
  reader->tags = NULL;
}

const char* xmlreader_get_name (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_get_name: reader is null");

  if (reader->tags == NULL)
    fatal ("xmlreader_get_name: reader->tags is null");
  
  const char* name = reader->tags->name;
  char* colon = strchr (name, ':');
  if (colon != NULL)
    return colon+1;

  return name;
}

static const char* xmlreader_internal_get_namespace (xmlreader_t* reader, const char* name) {
  struct xmlreader_tag_t* tag = reader->tags;
  int prefix_len = 0;
  const char* prefix = name;
  char* colon = strchr (name, ':');
  if (colon != NULL)
    prefix_len = colon - prefix - 1;
  else {
    prefix = "xmlns";
    prefix_len = 5;
  }

  int i = 0;
  while (tag != NULL) {
    if (tag->namespaces != NULL) {
      int len = array_length (tag->namespaces);
      for (i = 0; i < len; i++) {
        struct attribute_t* a = array_get (tag->namespaces, i);
        if (strncmp (a->name, prefix, prefix_len) == 0) {
          return a->value;
        }
      }
    }
    tag = tag->prev;
  }
  return NULL;
}

static const char* xmlreader_internal_get_prefix (xmlreader_t* reader, const char* namespace) {
  struct xmlreader_tag_t* tag = reader->tags;

  if (namespace == NULL)
    return NULL;

  int i = 0;
  while (tag != NULL) {
    if (tag->namespaces != NULL) {
      int len = array_length (tag->namespaces);
      for (i = 0; i < len; i++) {
        struct attribute_t* a= array_get (tag->namespaces, i);
        if (strcmp (a->value, namespace) == 0)
          return a->name;
      }
    }
    tag = tag->prev;
  }
  return NULL;
}

const char* xmlreader_get_namespace (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_get_namespace: reader is null");

  if (reader->tags == NULL)
    fatal ("xmlreader_get_name: reader->tags is null");

  const char* name = reader->tags->name;
  return xmlreader_internal_get_namespace (reader, name);
}

const char* xmlreader_attribute (xmlreader_t* reader, const char* namespace, const char* name) {
  if (reader == NULL)
    fatal ("xmlreader_attribute: reader is null");

  if (reader->nodetype != XML_START_ELEMENT)
    fatal ("xmlreader_attribute: nodetype is not XML_START_ELEMENT");

  int len = array_length (reader->attributes);
  if (len == 0)
    return NULL;

  const char* prefix = xmlreader_internal_get_prefix (reader, namespace);
  
  int i;
  struct attribute_t* a;
  
  if (prefix != NULL) {
    int prefix_len = strlen (prefix);
    
    for (i = 0; i < len; i++) {
      a = array_get (reader->attributes, i);
      if (strncmp (prefix, a->name, prefix_len) == 0 &&
          a->name[prefix_len] == ':' && a->name[prefix_len + 1] != '\0' && 
          strcmp (name, a->name + prefix_len+1) == 0)
        return a->value;
    }
  } else {
    for (i = 0; i < len; i++) {
      a = array_get (reader->attributes, i);
      if (a == NULL || a->name == NULL)
        fatal ("here");
      if (strcmp (name, a->name) == 0)
        return a->value;
    }
  }
  return NULL;
}
  
static void xmlreader_internal_push_tag (xmlreader_t* reader, const char* name) {
  printf ("push %s\n", name);
  
  struct xmlreader_tag_t* tag = malloc (sizeof (struct xmlreader_tag_t));
  if (tag == NULL)
    fatal ("xmlreader_internal_push_tag: malloc failed");

  tag->prev = reader->tags;
  tag->namespaces = NULL;
  tag->name = name;

  reader->tags = tag;
}

static struct xmlreader_tag_t* xmlreader_internal_pop_tag (xmlreader_t* reader) {
  if (reader->tags == NULL)
    fatal ("xmlreader_internal_pop_tag: reader->tags is null");

  struct xmlreader_tag_t* tag = reader->tags;
  reader->tags = tag->prev;
  printf ("pop %s\n", tag->name);
  return tag;
}

static uint8_t xmlreader_internal_getc (xmlreader_t* reader) {
  uint32_t c = 0;

  if (reader->saved != (uint32_t) -1) {
    c = (uint8_t) reader->saved;
    reader->saved = (uint32_t) -1;
  } else {
    c = bufio_reader_readbyte (reader->buf);
    if (reader->buf->err != 0) {
      reader->err = reader->buf->err;
    }
  }
  return c;
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

static inline bool is_space (uint32_t u) {
  return (u == ' ' || u == '\t' || u == '\r' || u == '\n');
}

static char* xmlreader_internal_name (xmlreader_t* reader) {
  uint32_t u;
  if (reader->saved != (uint32_t) -1) {
    u = reader->saved;
    reader->saved = (uint32_t) -1;
  } else { 
    u = bufio_reader_readrune (reader->buf);
    if (reader->buf->err != 0) {
      reader->err = reader->buf->err;
      return NULL;
    }
  }

  if (!is_name_start_char (u)) {
    reader->err = ERR_XML_SYNTAX;
    return NULL;
  }

  int len = 1024;
  char* result = malloc (sizeof (char) * len);
  if (result == NULL)
    fatal ("xmlreader_internal_name: malloc failed");

  char* ptr = result;
  int err = 0;

  err = utf8_append (ptr, u);
  if (err != 0) {
    reader->err = err;
    free (result);
    return NULL;
  }
  ptr += utf8_width_of_uint32 (u);
  int width = 0, offset = 0;
  
  while (1) {
    u = bufio_reader_readrune (reader->buf);
    if (reader->buf->err != 0) {
      reader->err = reader->buf->err;
      free (result);
      return NULL;
    }
    if (!is_name_char (u))
      break;

    width = utf8_width_of_uint32 (u);
    offset = ptr - result;
    if (offset + width >= len - 1) {
      len += 512;
      result = realloc (result, len);
      ptr = result + offset;
    }
    err = utf8_append (ptr, u);
    if (err != 0) {
      reader->err = err;
      free (result);
      return NULL;
    }
    ptr += width;
  }
  *ptr = '\0';
  // this u can be only of ' ', '=', '/', '>'
  reader->saved = (uint32_t) u;
  return result;
}

static void xmlreader_internal_space (xmlreader_t* reader, bool required) {
  uint32_t c = xmlreader_internal_getc (reader);
  if (reader->err != 0) return;
  
  if (required && !is_space (c)) {
    reader->err = ERR_XML_SYNTAX;
    return;
  }
  
  do {
    if (!is_space (c))
      break;
    
    c = bufio_reader_readbyte (reader->buf);
    if (reader->buf->err != 0) {
      reader->err = reader->buf->err;
      return;
    }
  } while (1);
  
  reader->saved = (uint32_t) c;
}

static char* xmlreader_internal_attribute_value (xmlreader_t* reader) {
  uint8_t c = xmlreader_internal_getc (reader);
  if (reader->err != 0) return NULL;

  uint8_t quote = 0;
  
  if (c == '"' || c == '\'')
    quote = c;
  else {
    reader->err = ERR_XML_SYNTAX;
    return NULL;
  }

  int len = 1024;
  char* value = malloc (sizeof (char) * len);
  if (value == NULL) {
    fatal ("xmlreader_internal_attribute_value: malloc failed");
    return NULL;
  }
  char* ptr = value;

  while (1) {
    c = xmlreader_internal_getc (reader);
    if (reader->err != 0) return NULL;

    if (c == quote) {
      *ptr = '\0';
      break;
    }

    int offset = ptr - value;
    if (offset == len - 1) {
      len += 512;
      value = realloc (value, len);
      if (value == NULL)
        fatal ("xmlreader_internal_attribute_value: realloc failed");

      ptr = value + offset;
    }
      
    *ptr++ = c;
  }

  return value;
}
    

static void xmlreader_internal_skip_text (xmlreader_t* reader) {
  int c;
  while (1) {
    c = bufio_reader_readbyte (reader->buf);
    if (reader->buf->err != 0) {
      reader->err = reader->buf->err;
      return;
    }
    if (c == '<') {
      reader->saved = (uint32_t) c;
      return;
    }
  }
}
  
const char* xmlreader_text (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_text: reader is null");

  char* text = NULL;
  int len = 4096;
  char* ptr = NULL;
  
  int type = 0;
  while (1) {
    type = xmlreader_next (reader);
    if (type == XML_ERROR)
      return text;
    else if (type == XML_START_ELEMENT)
      xmlreader_skip_element (reader);
    else if (type == XML_END_ELEMENT)
      break;
    else if (type == XML_TEXT) {
      if (text == NULL) {
        text = malloc (sizeof (char) * len);
        if (text == NULL)
          fatal ("xmlreader_text: malloc failed");
        ptr = text;
      }

      uint8_t c = xmlreader_internal_getc (reader);
      if (reader->err != 0) return NULL;

      *ptr++ = c;
    
      while (true) {
        c = bufio_reader_readbyte (reader->buf);
        if (reader->buf->err != 0) {
          reader->err = reader->buf->err;
          return NULL;
        }
        if (c == '<') {
          reader->saved = (uint32_t) c;
          break;
        }
        int offset = ptr - text;
        if (offset == len - 1) {
          len += 1024;
          text = realloc (text, len);
          if (text == NULL)
            fatal ("xmlreader_text: realloc failed");
          ptr = text + offset;
        }
        *ptr++ = c;
      }
    }
  }
  if (ptr != NULL)
    *ptr = '\0';
  return text;
}
  
    

int xmlreader_next (xmlreader_t* reader) {
  if (reader == NULL)
    fatal ("xmlreader_next: reader is null");

  uint8_t c = xmlreader_internal_getc (reader);
  if (reader->err != 0) return XML_ERROR;

  if (reader->nodetype == XML_START_ELEMENT && c == '/') {
    c = xmlreader_internal_getc (reader);
    if (reader->err != 0) return XML_ERROR;
    if (c != '>') {
      reader->err = ERR_XML_SYNTAX;
      return XML_ERROR;
    }

    struct xmlreader_tag_t* tag = xmlreader_internal_pop_tag (reader);
    if (tag == NULL) {
      reader->err = ERR_XML_SYNTAX;
      return XML_ERROR;
    }
    reader->attributes->length = 0;
    reader->nodetype = XML_END_ELEMENT;
    return XML_END_ELEMENT;
  }

  if (c != '<') {
    if (reader->nodetype == XML_TEXT) {
      xmlreader_internal_skip_text (reader);
      if (reader->err != 0) return XML_ERROR;
    } else {
      reader->saved = (uint32_t) c;
      reader->nodetype = XML_TEXT;
      return XML_TEXT;
    }
  }

  c = xmlreader_internal_getc (reader);
  if (reader->err != 0) return XML_ERROR;

  switch (c) {
  case '/': {
    char* name = xmlreader_internal_name (reader);
    if (reader->err != 0) return XML_ERROR;

    struct xmlreader_tag_t* tag = xmlreader_internal_pop_tag (reader);
    if (tag == NULL) {
      reader->err = ERR_XML_SYNTAX;
      return XML_ERROR;
    }
    
    if (strcmp (name, tag->name) != 0) {
      reader->err = ERR_XML_SYNTAX;
      return XML_ERROR;
    }
    xmlreader_internal_space (reader, false);
    if (reader->err != 0) return XML_ERROR;

    c = xmlreader_internal_getc (reader);
    if (reader->err != 0) return XML_ERROR;

    if (c != '>') {
      reader->err = ERR_XML_SYNTAX;
      return XML_ERROR;
    }

    reader->nodetype = XML_END_ELEMENT;
    return XML_END_ELEMENT;
  }
  case '?': {
    char* name = xmlreader_internal_name (reader);
    if (reader->err != 0) return XML_ERROR;

    if (strcmp ("xml", name) && reader->tags == NULL) {
      char* attr = NULL;
      char* value = NULL;
      uint8_t c = 0;
    
      do {
        xmlreader_internal_space (reader, true);
        if (reader->err != 0) return XML_ERROR;

        if (reader->saved == '?')
          break;

        attr = xmlreader_internal_name (reader);
        if (reader->err != 0) return XML_ERROR;
      
        xmlreader_internal_space (reader, true);
        if (reader->err != 0) return XML_ERROR;

        c = xmlreader_internal_getc (reader);
        if (reader->err != 0) return XML_ERROR;

        if (c != '=') {
          reader->err = ERR_XML_SYNTAX;
          return XML_ERROR;
        }
        
        xmlreader_internal_space (reader, false);
        if (reader->err != 0) return XML_ERROR;

        value = xmlreader_internal_attribute_value (reader);
        if (reader->err != 0) return XML_ERROR;
      
        if (strcmp ("version", attr) == 0 && strcmp (value, "1.0") != 0) {
          reader->err = ERR_XML_UNKNOWN_VERSION;
          return XML_ERROR;
        }
        if (strcmp ("encoding", attr) == 0 && strcmp (value, "UTF-8") != 0) {
          reader->err = ERR_XML_UNKNOWN_ENCODING;
          return XML_ERROR;
        }
        
      } while (1);

      c = xmlreader_internal_getc (reader);
      if (reader->err != 0) return XML_ERROR;
      if (c != '>') {
        reader->err = ERR_XML_SYNTAX;
        return XML_ERROR;
      }

      return xmlreader_next (reader);

    } else {
      // PI
      // skip up to "?>"
      uint8_t prev = 0;
      while (1) {
        c = xmlreader_internal_getc (reader);
        if (reader->err != 0) return XML_ERROR;

        if (prev == '?' && c == '>')
          break;
        prev = c;
      }
      return xmlreader_next (reader);
    }
  }

  case '!':
    c = xmlreader_internal_getc (reader);
    if (reader->err != 0) return XML_ERROR;

    if (c == '-') {
    } else if (c == '[') {
    } else {
      reader->err = ERR_XML_SYNTAX;
      return XML_ERROR;
    }
    
  case '[':
    // todo: skip
    return XML_ERROR;

  default: {
    reader->saved = (uint32_t) c;
    const char* name = xmlreader_internal_name (reader);
    if (reader->err != 0) return XML_ERROR;

    xmlreader_internal_push_tag (reader, name);

    bool spaced = false;
    do {
      spaced = false;
      c = xmlreader_internal_getc (reader);
      if (reader->err != 0) return XML_ERROR;

      if (is_space (c)) {
        xmlreader_internal_space (reader, false);
        if (reader->err != 0) return XML_ERROR;
        spaced = true;
      } else {
        reader->saved = (uint32_t) c;
      }

      c = xmlreader_internal_getc (reader);
      if (reader->err != 0) return XML_ERROR;
    
      if (c == '>') {
        reader->nodetype = XML_START_ELEMENT;
        return XML_START_ELEMENT;
      } else if (c == '/') {
        reader->saved = (uint32_t) c;
        reader->nodetype = XML_START_ELEMENT;
        return XML_START_ELEMENT;
      } else if (spaced) {
        reader->saved = (uint32_t) c;
        const char* attrname = xmlreader_internal_name (reader);
        if (reader->err != 0) return XML_ERROR;

        xmlreader_internal_space (reader, false);
        if (reader->err != 0) return XML_ERROR;

        c = xmlreader_internal_getc (reader);
        if (reader->err != 0) return XML_ERROR;

        if (c != '=') {
          reader->err = ERR_XML_SYNTAX;
          return XML_ERROR;
        }

        xmlreader_internal_space (reader, false);
        if (reader->err != 0) return XML_ERROR;

        const char* attrvalue = xmlreader_internal_attribute_value (reader);
        if (reader->err != 0) return XML_ERROR;

        if (strncmp ("xmlns", attrname, 5) == 0 && (attrname[5] == '\0' || attrname[5] == ':')) {
          char* prefix = (char*) attrname;
          char* colon = strchr (attrname, ':');
          if (colon != NULL)
            prefix = colon+1;
          
          struct attribute_t a = {prefix, attrvalue};
          if (reader->tags->namespaces == NULL)
            reader->tags->namespaces = array_new (sizeof (struct attribute_t), 2);
          
          array_append (reader->tags->namespaces, &a);
        } else {
          struct attribute_t attr = { attrname, attrvalue};
          array_append (reader->attributes, &attr);
        }        
      } else {
        reader->err = ERR_XML_SYNTAX;
        return XML_ERROR;
      }
    } while (1);

    reader->nodetype = XML_START_ELEMENT;
    return XML_START_ELEMENT;
  }
  }

  return XML_ERROR;
}

extern uint8_t decoding_table[256];

int xmlreader_base64 (xmlreader_t* reader, unsigned char** result, int* result_len) {
  if (reader == NULL)
    fatal ("xmlreader_base64: reader is null");

  char* data = (char*) xmlreader_text (reader);
  if (reader->err != 0) return -1;

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

int xmlreader_skip_element (xmlreader_t* reader) {
  while (1) 
    switch (xmlreader_next (reader)) {
    case XML_START_ELEMENT:
      xmlreader_skip_element (reader);
      break;
    case XML_END_ELEMENT:
      return 0;
    case XML_TEXT:
      xmlreader_internal_skip_text (reader);
      break;
    case XML_ERROR:
      return -1;
    }
}
