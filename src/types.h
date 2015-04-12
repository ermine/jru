#ifndef _TYPES_H_
#define _TYPES_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <time.h>

#include <stdint.h>
#include <stdbool.h>

#include "stringpair.h"
#include "llist.h"

typedef uint8_t boolean_t;

enum extension_type;

typedef struct {
  int type;
  void* data;
} extension_t;

typedef stringpair_t langstring_t;

#define langstring_add(a,b,c) (stringpair_set((stringpair_t**) &(a), (b), (c)))

int langstring_decode (xmlTextReaderPtr reader, langstring_t *map);
int langstring_encode (xmlTextWriterPtr writer, const char* space, const char* local, langstring_t *map);

struct tm* datetime_parse(const xmlChar* value);
const char* datetime_to_string(struct tm* data);

boolean_t* strconv_parse_boolean(const xmlChar* value);
int *strconv_parse_int (const xmlChar* value);
uint *strconv_parse_uint (const xmlChar* value);
uint64_t *strconv_parse_int64 (const xmlChar* value);

const char* strconv_format_boolean(boolean_t* value);
const char* strconv_format_int(int32_t* value);
const char* strconv_format_uint(uint32_t* value);

unsigned char* base64_decode(const xmlChar* value);

#endif
