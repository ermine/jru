#include <malloc.h>
#include <string.h>
#include "xmlwriter.h"
#include "helpers.h"
#include "bufio.h"
#include "array.h"
#include "utf8.h"

const char* ns_xml = "http://www.w3.org/XML/1998/namespace";

static const char* empty_string = "";

struct pair_t {
  const char* p1;
  const char* p2;
};

void xmlwriter_init (xmlwriter_t* writer, int fd) {
  memset (writer, 0, sizeof (xmlwriter_t));
  writer->buf = bufio_writer_new (fd);
  stringpair_set (&writer->namespaces, ns_xml, "xml");
  writer->local_namespaces = array_new (sizeof (array_t*), 0);
  writer->tags = array_new (sizeof (struct pair_t), 5);
}

void xmlwriter_free (xmlwriter_t* writer) {
  if (writer == NULL)
    return;

  stringpair_free (writer->namespaces);
  array_free (writer->local_namespaces);
  array_free (writer->tags);
  free (writer);
}

void xmlwriter_reset (xmlwriter_t* writer) {
  bufio_writer_reset (writer->buf);
  stringpair_free (writer->namespaces);
  writer->namespaces = NULL;
  writer->openStartTag = false;
  int len = array_length (writer->local_namespaces);
  int i = 0;
  for (i = 0; i < len; i++) {
    array_t** l = array_get (writer->local_namespaces, i);
    array_free (*l);
  }
  array_slice (writer->local_namespaces, 0, 0);
  writer->depth = 0;
  array_slice (writer->tags, 0, 0);
  stringpair_set (&writer->namespaces, ns_xml, "xml");
}

int xmlwriter_set_prefix (xmlwriter_t* writer, const char* prefix, const char* uri) {
  if (writer == NULL)
    fatal ("xmlwriter_set_prefix: writer is null");

  if (prefix == NULL)
    prefix = empty_string;
  
	if (writer->openStartTag) {
		if (prefix == NULL)
      fatal ("xmlwriter_set_prefix: prefix is null inside opened start tag");

    int err = bufio_writer_write (writer->buf, 5, " xmlns:", prefix,  "=\"", uri,  "\"");
    if (err != 0) return err;
	}
	stringpair_set (&writer->namespaces, uri, prefix);

  if (array_length (writer->local_namespaces) <= writer->depth) {
    array_t* a = array_new (sizeof (array_t*), 5);
    array_append (writer->local_namespaces, &a);
  }
  array_t** lns = array_get_last (writer->local_namespaces);

  array_append (*lns, &uri);
  return 0;
}

void xmlwriter_unset_prefix (xmlwriter_t* writer, const char* prefix) {
  if (writer == NULL)
    fatal ("xmlwriter_unset_prefix: writer is null");

  stringpair_delete_by_value (&writer->namespaces, prefix);
  
}

int xmlwriter_start_stream (xmlwriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_start_stream: writer is null");

  return bufio_writer_write (writer->buf, 1, "<?xml version=\"1.0\" encoding=\"utf-8\"?>");
}

int xmlwriter_end_stream(xmlwriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_end_stream: writer is null");

  int i, err = 0;
  for (i = writer->depth-1; i > 0; i--) {
    err = xmlwriter_end_element (writer);
    if (err != 0) return err;
  }
  return xmlwriter_flush (writer);
}

static int xmlwriter_close_start_element(xmlwriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_close_start_element: writer is null");

	if (writer->openStartTag) {
    int err = bufio_writer_write (writer->buf, 1, ">");
    if (err != 0) return err;
		writer->openStartTag = false;
	}
	return 0;
}

int xmlwriter_flush (xmlwriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_flush: writer is null");

  int err = xmlwriter_close_start_element (writer);
  if (err != 0) return err;

  return bufio_writer_flush (writer->buf);
}

int xmlwriter_end_element (xmlwriter_t* writer) {
  if (writer == NULL)
    fatal ("xmlwriter_end_element: writer is null");

  writer->depth--;
  struct pair_t* tag = array_get_last (writer->tags);
  array_delete_last (writer->tags);

  array_t** lns = array_get_last (writer->local_namespaces);
  int i, len = array_length (*lns);
  for (i = 0; i < len; i++) {
    char* ns = array_get (*lns, i);
    stringpair_delete (&writer->namespaces, ns);
  }
  array_free (*lns);

  array_delete_last (writer->local_namespaces);
  
  int err = 0;
  if (writer->openStartTag) {
		writer->openStartTag = false;
    return bufio_writer_write (writer->buf, 1, "/>");
	}

  err = bufio_writer_write (writer->buf, 1, "</");
  if (err != 0) return err;
  if (tag->p1 != NULL && tag->p1 != empty_string) {
    err = bufio_writer_write (writer->buf, 2, tag->p1, ":");
    if (err != 0) return err;
  }
  err = bufio_writer_write (writer->buf, 2, tag->p2, ">");
  if (err != 0) return err;

  return 0;
}

int xmlwriter_start_element (xmlwriter_t* writer, const char* space, const char* local) {
  if (writer == NULL)
    fatal ("xmlwriter_start_element: writer is null");

  int err = 0;
  writer->depth++;

  err = xmlwriter_close_start_element (writer);
  if (err != 0) return err;

  const char* prefix = NULL;
  
  array_t* lns = NULL;
	if (array_length (writer->local_namespaces) < writer->depth) {
    lns = array_new (sizeof (array_t*), 5);
    array_append (writer->local_namespaces, &lns);
  } else {
    lns = *(array_t**) array_get (writer->local_namespaces, writer->depth-1);
  }
  if (space != NULL) {
		prefix = stringpair_get (writer->namespaces, space);
    if (prefix == NULL) {
      prefix = empty_string;
      stringpair_set (&writer->namespaces, space, NULL);
      array_append (lns, &space);
		}
	}

  struct pair_t tag = { prefix, local};
  array_append (writer->tags, &tag);

  err = bufio_writer_write (writer->buf, 1, "<");
  if (err != 0) return err;
  
  if (prefix != NULL && prefix != empty_string) {
    err = bufio_writer_write (writer->buf, 2, prefix, ":");
    if (err != 0) return err;
  }
  err = bufio_writer_write (writer->buf, 1, local);
  if (err != 0) return err;
  
	writer->openStartTag = true;

  int i, len = array_length (lns);
  for (i = 0; i < len; i++) {
    const char** aspace = array_get (lns, i);
    const char* aprefix = stringpair_get (writer->namespaces, *aspace);
    err = bufio_writer_write (writer->buf, 1, " xmlns");
    if (err != 0) return err;

    if (aprefix != NULL && aprefix != empty_string) {
      err = bufio_writer_write (writer->buf, 2, ":", prefix);
      if (err != 0) return err;
    }

    err = bufio_writer_write (writer->buf, 3, "=\"", *aspace, "\"");
    if (err != 0) return err;
  }
  return 0;
}

int xmlwriter_simple_element (xmlwriter_t* writer, const char* space, const char* local,
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

static int xmlwriter_escapetext (xmlwriter_t* writer, const char* text) {
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
      err = bufio_writer_write_len (writer->buf, text + last, i - width - last);
      if (err != 0) return err;
    }
    err = bufio_writer_write (writer->buf, 1, esc);
    if (err != 0) return err;
    last = i;
  }
  if (last < len) {
    err = bufio_writer_write (writer->buf, 1, text + last);
    if (err != 0) return err;
  }
  return 0;
}

int xmlwriter_text (xmlwriter_t* writer, const char* text) {
  if (writer == NULL)
    fatal ("xmlwriter_text: writer is null");

  int err = 0;
  err = xmlwriter_close_start_element (writer);
  if (err != 0) return err;

  err = xmlwriter_escapetext (writer, text);
  
	return err;
}

int xmlwriter_base64 (xmlwriter_t* writer, const unsigned char* data, const int data_len) {
  if (writer == NULL)
    fatal ("xmlwriter_base64: writer is null");

	int err = xmlwriter_close_start_element (writer);
  if (err != 0) return err;

  static const char* encodeStd = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  
  int len = data_len;
  unsigned char* ptr = (unsigned char*) data;

  while (len > 0) {
    uint8_t b0 = 0, b1 = 0, b2 = 0, b3 = 0;
    char dst[5] = {0,0,0,0,0};
    
    if (len > 2) {
      b3 = ptr[2] & 0x3F;
      b2 = ptr[2] >> 6;
    }
    if (len >= 2) {
      b2 |= (ptr[1] << 2) & 0x3F;
      b1 = ptr[1] >> 4;
    }
    if (len >= 1) {
      b1 |= (ptr[0] << 4) & 0x3F;
      b0 = ptr[0] >> 2;
    }

    dst[0] = encodeStd[b0];
    dst[1] = encodeStd[b1];
    dst[2] = encodeStd[b2];
    dst[3] = encodeStd[b3];

    if (len < 3) {
      dst[3] = '=';
      if (len < 2) {
        dst[2] = '=';
      }
    }

    err = bufio_writer_write (writer->buf, 1, dst);
    if (err != 0) return err;

    if (len < 3)
      break;

    ptr += 3;
    len -= 3;
  }
  return 0;
}

int xmlwriter_attribute (xmlwriter_t* writer, const char* space, const char* local,
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
  if (prefix != NULL && prefix != empty_string)
    err = bufio_writer_write (writer->buf, 5, " ", prefix, ":", local, "=\"");
  else
    err = bufio_writer_write(writer->buf, 3, " ", local, "=\"");
  if (err != 0) return err;
  
  err = xmlwriter_escapetext (writer, value);
  if (err != 0) return err;
  
  err = bufio_writer_write (writer->buf, 1, "\"");

	return err;
}

