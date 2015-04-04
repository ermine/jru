#ifndef _TYPES_H_
#define _TYPES_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <time.h>

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t boolean_t;

enum extension_type;

typedef struct {
  int type;
  void* data;
} extension_t;

struct langstring_pair_t {
  const xmlChar* key;
  const xmlChar* string;
};

typedef struct {
  struct langstring_pair_t *map;
} langstring_t;

void langstring_add (langstring_t *map, const xmlChar *key, const xmlChar *string);
int langstring_decode (xmlTextReaderPtr reader, langstring_t *map);
int langstring_encode (xmlTextWriterPtr writer, const char* space, const char* local, langstring_t *map);

struct tm* datetime_parse(const xmlChar* value);
const xmlChar* datetime_to_string(struct tm* data);

struct _llist_t;
struct _llist_t {
  int type;
  void *data;
  struct _llist_t *next;
};
typedef struct _llist_t llist_t;

void llist_append(llist_t* root, void* data, int type);

boolean_t* strconv_parse_boolean(const xmlChar* value);
int *strconv_parse_int (const xmlChar* value);
uint *strconv_parse_uint (const xmlChar* value);
uint64_t *strconv_parse_int64 (const xmlChar* value);

const xmlChar* strconv_format_boolean(boolean_t* value);
const xmlChar* strconv_format_int(int32_t* value);
const xmlChar* strconv_format_uint(uint32_t* value);

unsigned char* base64_decode(const xmlChar* value);

#endif
