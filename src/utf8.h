#ifndef _UTF8_H_
#define _UTF8_H_

#include <stdint.h>

int utf8_width (uint8_t b);
int utf8_append (char* array, uint32_t u);
int utf8_width_of_uint32 (uint32_t u);

#endif
