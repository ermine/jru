#ifndef _XMLWRITER_H_
#define _XMLWRITER_H_

#include <stdbool.h>
#include "stringpair.h"
#include "bufio.h"
#include "array.h"

extern const char* ns_xml;

typedef struct {
  bufio_writer_t* buf;
  stringpair_t* namespaces;
  bool openStartTag;
  array_t* local_namespaces;
  int depth;
  array_t* tags;
} xmlwriter_t;

void xmlwriter_init (xmlwriter_t* writer, int fd);
void xmlwriter_free (xmlwriter_t* writer);
void xmlwriter_reset (xmlwriter_t* writer);
int xmlwriter_set_prefix (xmlwriter_t* writer, const char* prefix, const char* uri);
void xmlwriter_unset_prefix (xmlwriter_t* writer, const char* prefix);
int xmlwriter_start_stream (xmlwriter_t* writer);
int xmlwriter_end_stream (xmlwriter_t* writer);
int xmlwriter_start_element (xmlwriter_t* writer, const char* stace, const char* local);
int xmlwriter_end_element (xmlwriter_t* writer);
int xmlwriter_flush (xmlwriter_t* writer);
int xmlwriter_simple_element (xmlwriter_t* writer, const char* space, const char* local, const char* value);
int xmlwriter_text (xmlwriter_t* writer, const char* text);
int xmlwriter_base64 (xmlwriter_t* writer, const unsigned char* data, const int data_len);
int xmlwriter_attribute (xmlwriter_t* writer, const char* space, const char* local, const char* value);


#endif
