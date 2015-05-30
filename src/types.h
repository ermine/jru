#ifndef _TYPES_H_
#define _TYPES_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <time.h>

#include <stdint.h>
#include <stdbool.h>

#include "stringpair.h"
#include "array.h"

enum extension_type;

typedef struct {
  int type;
  void* data;
} extension_t;

typedef stringpair_t langstring_t;

#define langstring_add(a,b,c) (stringpair_set((stringpair_t**) &(a), (b), (c)))

int langstring_decode (xmlreader_t* reader, langstring_t *map);
int langstring_encode (xmlwriter_t* writer, const char* space, const char* local, langstring_t *map);
void langstring_free (langstring_t* map);

struct tm* datetime_parse(const char* value);
const char* datetime_to_string(struct tm* data);

bool* strconv_parse_boolean(const char* value);
int *strconv_parse_int (const char* value);
uint32_t *strconv_parse_uint (const char* value);
uint64_t *strconv_parse_int64 (const char* value);

const char* strconv_format_boolean(bool* value);
const char* strconv_format_int(int32_t* value);
const char* strconv_format_uint(uint32_t* value);

#endif
