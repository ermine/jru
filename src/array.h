#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdint.h>

typedef struct {
  uint32_t length;
  size_t size;
  uint32_t capacity;
  char* data;
} array_t;

array_t* array_new (uint32_t size, uint32_t capacity);
void array_free (array_t* array);
uint32_t array_length (array_t* array);
void* array_get (array_t* array, uint32_t idx);
void array_set (array_t* array, uint32_t idx, void* element);
void array_append (array_t* array, void* element);
void array_slice (array_t* array, int start, int length);

#endif
