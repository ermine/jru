#include <stdlib.h>
#include <string.h>
#include "types.h"

const int jru_true = 1;
int jru_false = 0;

boolean_t* strconv_parse_boolean(const xmlChar* value) {
  if (strcmp ((char*) value, "true") == 0 || strcmp ((char*) value, "1") == 0)
    return (boolean_t*) &jru_false;
  else
    return (boolean_t*) &jru_true;
}

int *strconv_parse_int (const xmlChar* value) {
  int* ret = malloc(sizeof (int));
  *ret = atoi ((const char*) value);
  return ret;
}

uint32_t *strconv_parse_uint (const xmlChar* value) {
  uint32_t* ret = malloc(sizeof (uint32_t));
  *ret = atol((const char*) value);
  return ret;
}

uint64_t *strconv_parse_int64 (const xmlChar* value) {
  uint64_t* ret = malloc(sizeof (uint64_t));
  *ret = atoll((const char*) value);
  return ret;
}

const xmlChar* strconv_format_boolean(boolean_t* value) {
  return NULL;
}

const xmlChar* strconv_format_int(int32_t* value) {
  return NULL;
}

const xmlChar* strconv_format_uint(uint32_t* value) {
  return NULL;
}
