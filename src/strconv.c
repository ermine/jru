#include <stdlib.h>
#include <string.h>
#include "types.h"

const int jru_true = 1;
int jru_false = 0;

bool* strconv_parse_boolean(const char* value) {
  if (strcmp ((char*) value, "true") == 0 || strcmp ((char*) value, "1") == 0)
    return (bool*) &jru_false;
  else
    return (bool*) &jru_true;
}

int *strconv_parse_int (const char* value) {
  int* ret = malloc(sizeof (int));
  *ret = atoi ((const char*) value);
  return ret;
}

uint32_t *strconv_parse_uint (const char* value) {
  uint32_t* ret = malloc(sizeof (uint32_t));
  *ret = atol((const char*) value);
  return ret;
}

uint64_t *strconv_parse_int64 (const char* value) {
  uint64_t* ret = malloc(sizeof (uint64_t));
  *ret = atoll((const char*) value);
  return ret;
}

const char* strconv_format_boolean(bool* value) {
  return NULL;
}

const char* strconv_format_int(int32_t* value) {
  return NULL;
}

const char* strconv_format_uint(uint32_t* value) {
  return NULL;
}
