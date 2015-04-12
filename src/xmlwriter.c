#include <malloc.h>
#include <string.h>
#include "xmlwriter.h"
#include "helpers.h"
#include "bufio.h"
#include "array.h"
#include "jid/ustring.h"

const char* ns_xml = "http://www.w3.org/XML/1998/namespace";

struct pair_t {
  const char* p1;
  const char* p2;
};

xmlWriter_t* xmlwriter_new (int fd) {
  xmlWriter_t* writer = malloc (sizeof (xmlWriter_t));
  if (writer == NULL)
    fatal ("xmlwriter_new: malloc failed");
  
  memset (writer, 0, sizeof (xmlWriter_t));
  writer->buf = bufio_new (fd);
  writer->fd = fd;
  stringpair_set (&writer->namespaces, ns_xml, "xml");
  writer->local_namespaces = array_new (sizeof (array_t*), 0);
  writer->tags = array_new (sizeof (struct pair_t), 5);
  return writer;
}

void xmlwriter_free (xmlWriter_t* writer) {
  if (writer == NULL)
    return;

  stringpair_free (writer->namespaces);
  array_free (writer->local_namespaces);
  array_free (writer->tags);
  free (writer);
}

int xmlwriter_set_prefix (xmlWriter_t* writer, const char* prefix, const char* uri) {
  if (writer == NULL)
    fatal ("xmlwriter_set_prefix: writer is null");

	if (writer->openStartTag) {
		if (prefix == NULL)
      fatal ("xmlwriter_set_prefix: prefix is null inside opened start tag");

    int err = bufio_write (writer->buf, 5, "xmlns:", prefix,  "=\"", uri,  "\"");
    if (err != 0) return err;
	}
	stringpair_set (&writer->namespaces, uri, prefix);

  array_t* lns = NULL;
  if (array_length (writer->local_namespaces) >= writer->depth) {
    lns = array_new (sizeof (array_t*), 5);
    array_append (writer->local_namespaces, &lns);
  } else {
    lns = array_get (writer->local_namespaces, writer->depth);
  }
  array_append (lns, &uri);
  return 0;
}

void xmlwriter_unset_prefix (xmlWriter_t* writer, const char* prefix) {
  if (writer == NULL)
    fatal ("xmlwriter_unset_prefix: writer is null");

  stringpair_delete_by_value (&writer->namespaces, prefix);
  
}

int xmlwriter_start_stream (xmlWriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_start_stream: writer is null");

  return bufio_write (writer->buf, 1, "<?xml version=\"1.0\" encoding=\"utf-8\"?>");
}

int xmlwriter_end_stream(xmlWriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_end_stream: writer is null");

  int i, err = 0;
  for (i = writer->depth; i > 0; i--) {
    err = xmlwriter_end_element (writer);
    if (err != 0) return err;
  }
  return xmlwriter_flush (writer);
}

static int xmlwriter_close_start_element(xmlWriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_close_start_element: writer is null");

	if (writer->openStartTag) {
    int err = bufio_write (writer->buf, 1, ">");
    if (err != 0) return err;
		writer->openStartTag = false;
		writer->depth++;
	}
	return 0;
}

int xmlwriter_flush (xmlWriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_flush: writer is null");

  int err = xmlwriter_close_start_element (writer);
  if (err != 0) return err;

  return xmlwriter_flush (writer);
}

int xmlwriter_end_element (xmlWriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_end_element: writer is null");

  int err = 0;
  if (writer->openStartTag) {
		writer->openStartTag = false;
    return bufio_write (writer->buf, 1, "/>");
	}

  writer->depth--;
  struct pair_t* tag = array_get (writer->tags, writer->depth);
  err = bufio_write (writer->buf, 1, "</");
  if (err != 0) return err;
  if (tag->p1 != NULL) {
    err = bufio_write (writer->buf, 2, tag->p1, ":");
    if (err != 0) return err;
    err = bufio_write (writer->buf, 2, tag->p2, ">");
    if (err != 0) return err;
  }
  array_t* lns = array_get (writer->local_namespaces, writer->depth);
  int i, len = array_length (lns);
  for (i = 0; i < len; i++) {
    char* ns = array_get (lns, i);
    stringpair_delete (writer->namespaces, ns);
  }
  array_free (lns);
  array_slice (writer->local_namespaces, 0, writer->depth);
  array_slice (writer->tags, 0, writer->depth);
  return 0;
}

int xmlwriter_start_element (xmlWriter_t* writer, const char* space, const char* local) {
  if (writer == NULL)
    fatal ("xmlwriter_start_element: writer is null");

  int err = 0;

  err = xmlwriter_close_start_element (writer);
  if (err != 0) return err;

  const char* prefix = NULL;
  
  array_t* lns = NULL;
	if (array_length (writer->local_namespaces) < writer->depth+1) {
    lns = array_new (sizeof (array_t*), 5);
    array_append (writer->local_namespaces, &lns);
  }
  if (lns == NULL)
    lns = array_get (writer->local_namespaces, writer->depth);
  if (space != NULL) {
		prefix = stringpair_get (writer->namespaces, space);
    if (prefix == NULL) {
      // stringpair_set (writer->namespaces, space, empty_string);
      array_append (lns, &space);
		}
	}

  struct pair_t tag = { prefix, local};
  array_append (writer->tags, &tag);

  err = bufio_write (writer->buf, 1, "<");
  if (err != 0) return err;
  
  if (prefix != NULL) {
    err = bufio_write (writer->buf, 2, prefix, ":");
    if (err != 0) return err;
  }
  err = bufio_write (writer->buf, 1, local);
  if (err != 0) return err;
  
	writer->openStartTag = true;

  int i, len = array_length (lns);
  for (i = 0; i < len; i++) {
    const char* space = array_get (lns, i);
    prefix = stringpair_get (writer->namespaces, space);
    err = bufio_write (writer->buf, 1, " xmlns");
    if (err != 0) return err;

    if (prefix != NULL) {
      err = bufio_write (writer->buf, 2, ":", prefix);
      if (err != 0) return err;
    }

    err = bufio_write (writer->buf, 3, "=\"", space, "\"");
    if (err != 0) return err;
  }
  return 0;
}

int xmlwriter_simple_element (xmlWriter_t* writer, const char* space, const char* local,
                              const char* value) {
  if (writer == NULL)
    fatal ("xmlwriter_simple_element: writer is null");

  int err = 0;

  err = xmlwriter_start_element (writer, space, local);
  if (err != 0) return err;
  
  err = xmlwriter_text (writer, value);
  if (err != 0) return err;
  
  err = xmlwriter_end_element (writer);
	return err;
}

static int xmlwriter_escapetext (xmlWriter_t* writer, const char* text) {
  if (writer == NULL)
    fatal ("xmlwriter_escapetext: writer is null");

  char* esc;
  int last = 0;
  int i;

  int len = strlen (text);
  int err = 0;
  
  for (i = 0; i < len; ) {
    uint8_t ch = (uint8_t) text[i];
    int width = utf8_width (ch);
    if (width < 1)
      fatal ("xmlwriter_escapetext: width is less than 1");
        
    i += width;
    if (width == 1) {
      switch (ch) {
        case '"':
          esc = "&quot;"; break;
        case '\'':
          esc = "&apos;"; break;
        case '&':
          esc = "&amp;"; break;
        case '<':
          esc = "&lt;"; break;
        case '>':
          esc = "&gt;"; break;
        case '\t':
          esc = "#x9;"; break;
      case '\n':
        esc = "#xA;"; break;
        case '\r':
          esc = "#xD;"; break;
        default:
          // if !isInCharacterRange(r) || (r == 0xFFFD && width == 1) {
          // esc = esc_fffd;
          // break;
          // }
          continue;
        }
    } else {
        continue;
    }
    if (last < i - width) {
      err = bufio_write_len (writer->buf, text + last, i - width - last);
      if (err != 0) return err;
    }
    err = bufio_write (writer->buf, 1, esc);
    if (err != 0) return err;
    last = i;
  }
  if (last < len) {
    err = bufio_write (writer->buf, 1, text + last);
    if (err != 0) return err;
  }
  return 0;
}

int xmlwriter_text (xmlWriter_t* writer, const char* text) {
  if (writer == NULL)
    fatal ("xmlwriter_text: writer is null");

  int err = 0;
  err = xmlwriter_close_start_element (writer);
  if (err != 0) return err;

  err = xmlwriter_escapetext (writer, text);
  
	return err;
}

extern unsigned char encoding_table[];
extern int mod_table[];


int xmlwriter_base64 (xmlWriter_t* writer, const char* data) {
  if (writer == NULL)
    fatal ("xmlwriter_base64: writer is null");

	int err = xmlwriter_close_start_element (writer);
  if (err != 0) return err;
  
  int len = strlen (data);
  int i = 0;
  unsigned char encoded_data[4];
  
  for (i = 0; i < len;) {
    uint32_t octet_a = i < len ? (unsigned char)data[i++] : 0;
    uint32_t octet_b = i < len ? (unsigned char)data[i++] : 0;
    uint32_t octet_c = i < len ? (unsigned char)data[i++] : 0;
    
    uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

    encoded_data[0] = encoding_table[(triple >> 3 * 6) & 0x3F];
    encoded_data[1] = encoding_table[(triple >> 2 * 6) & 0x3F];
    encoded_data[2] = encoding_table[(triple >> 1 * 6) & 0x3F];
    encoded_data[3] = encoding_table[(triple >> 0 * 6) & 0x3F];
    
    err = bufio_write (writer->buf, 1, encoded_data);
    if (err != 0) return err;
  }

  for (i = 0; i < mod_table[len % 3]; i++) {
    err = bufio_write (writer->buf, 1, "=");
    if (err != 0) return err;
  }
  
  return 0;
}

int xmlwriter_attribute (xmlWriter_t* writer, const char* space, const char* local,
                          const char* value) {
  if (writer == NULL)
    fatal ("xmlwriter_attribute: writer is null");
  
	if (!writer->openStartTag) {
    // error `attribute after ">"`
    return -1;
  }

  const char* prefix = NULL;
  if (space != NULL) {
    prefix = stringpair_get (writer->namespaces, space);
    if (prefix == NULL) {
      // error ("no prefix for namespace " + space)
      return -1;
    }
  }
  int err = 0;
  if (prefix != NULL)
    err = bufio_write (writer->buf, 5, " ", prefix, ":", local, "=\"");
  else
    err = bufio_write(writer->buf, 3, " ", local, "=\"");
  if (err != 0) return err;
  
  err = xmlwriter_escapetext (writer, value);
  if (err != 0) return err;
  
  err = bufio_write (writer->buf, 1, "\"");

	return err;
}

