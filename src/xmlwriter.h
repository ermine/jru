#ifndef _XMLWRITER_H_
#define _XMLWRITER_H_

#include <stdbool.h>
#include "stringpair.h"
#include "bufio.h"
#include "array.h"

extern const char* ns_xml;

typedef struct {
  int fd;
  bufio_t* buf;
  stringpair_t* namespaces;
  bool openStartTag;
  array_t* local_namespaces;
  int depth;
  array_t* tags;
} xmlWriter_t;

xmlWriter_t* xmlwriter_new (int fd);
void xmlwriter_free (xmlWriter_t* writer);

int xmlwriter_start_stream (xmlWriter_t* writer);
int xmlwriter_end_stream (xmlWriter_t* writer);
int xmlwriter_start_element (xmlWriter_t* writer, const char* stace, const char* local);
int xmlwriter_end_element (xmlWriter_t* writer);
int xmlwriter_flush (xmlWriter_t* writer);
int xmlwriter_simple_element (xmlWriter_t* writer, const char* space, const char* local, const char* value);
int xmlwriter_text (xmlWriter_t* writer, const char* text);
int xmlwriter_base64 (xmlWriter_t* writer, const char* data);
int xmlwriter_attribute (xmlWriter_t* writer, const char* space, const char* local, const char* value);


#endif
