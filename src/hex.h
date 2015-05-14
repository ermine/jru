#ifndef _HEX_H_
#define _HEX_H_

#include <stdint.h>

void hex_of_binary (char* out, unsigned char* in, int in_len);

void hex_of_int (char* out, uint64_t in);
uint64_t hex_to_int (const char* str);

#endif
