#ifndef _XMLREADER_H_
#define _XMLREADER_H_

#include "bufio.h"
#include "array.h"
#include "stringpair.h"

typedef enum {
  XML_ERROR = -1,
  XML_START_ELEMENT = 1,
  XML_END_ELEMENT,
  XML_TEXT
} xmlreader_nodetype_enum;


struct xmlreader_tag_t;

struct xmlreader_tag_t {
  struct xmlreader_tag_t* prev;
  const char* name;
  array_t* namespaces;
};

typedef struct {
  int err;
  bufio_reader_t* buf;
  uint32_t saved;
  xmlreader_nodetype_enum nodetype;
  array_t* attributes;
  struct xmlreader_tag_t* tags;
} xmlreader_t;

xmlreader_t* xmlreader_new (int fd);
void xmlreader_free (xmlreader_t* reader);
void xmlreader_reset (xmlreader_t* reader);
int xmlreader_next (xmlreader_t* reader);
xmlreader_nodetype_enum xmlreader_nodetype (xmlreader_t* reader);
const char* xmlreader_get_name (xmlreader_t* reader);
const char* xmlreader_get_namespace (xmlreader_t* reader);
const char* xmlreader_attribute (xmlreader_t* reader, const char* space, const char* local);
const char* xmlreader_text (xmlreader_t* reader);
int xmlreader_skip_element (xmlreader_t* reader);
int xmlreader_base64 (xmlreader_t* reader, unsigned char** result, int* result_len);

#endif
