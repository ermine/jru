#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include "array.h"
#include "helpers.h"

const uint32_t DEFAULT_CAPACITY = 16;

array_t* array_new(uint32_t size, uint32_t capacity) {
  array_t* array = malloc (sizeof (array_t));
  if (array == NULL)
    fatal("arraynew: malloc failed");
  array->length = 0;
  array->size = size;
  array->capacity = (capacity == 0) ? DEFAULT_CAPACITY : capacity;
  array->data = malloc (array->size * array->capacity);
  if (array->data == NULL)
    fatal("array_new: malloc failed");
  return array;
}

void array_free (array_t* array) {
  if (array == NULL) return;
  free (array->data);
  free (array);
}

uint32_t array_length (array_t* array) {
  if (array == NULL)
    fatal ("array_length: array is null");
  return array->length;
}

void* array_get (array_t* array, uint32_t idx) {
  if (array == NULL)
    fatal ("array_get: array is null");
  if (idx > array->length)
    fatal ("array_get: idx %d is lager that array length %d", idx, array->length);
  return array->data + idx * array->length;
}

void array_set (array_t* array, uint32_t idx, void* element) {
  if (array == NULL)
    fatal ("aggay_get: array is null");
  if (idx > array->length)
    fatal ("array_set: idx %d is lager that array length %d", idx, array->length);
  if (element == NULL)
    fatal ("array_set: element is null");
  memmove (array->data + idx * array->size, element, array->size);
}

void array_append (array_t* array, void* element) {
  if (array == NULL)
    fatal ("array_append: array is null");
  if (element == NULL)
    fatal ("array_append: element is null");
  if (array->length >= array->capacity) {
    int newcapacity = array->length >> 1;
    char* newdata = realloc (array->data, newcapacity * array->size);
    if (newdata == NULL)
      fatal ("array_append: realloc failed");
    array->capacity = newcapacity;
    array->data = newdata;
  }
  array->length = array->length + 1;
  array_set (array, array->length, element);
}
  
void array_slice (array_t* array, int start, int length) {
  if (array == NULL)
    fatal ("array_slice: array is null");

  if (start < 0 || start > array->length)
    fatal ("array_slice: start %d is out of bounds", start);

  if (length < 0 || start + length > array->length)
    fatal ("array_slice: end %d is out of bounds", length);
  
  if (start > 0)
    memmove (array->data, array->data + start * array->size, length * array->size);
  array->length = length;
}
