#ifndef _BASE64_H_
#define _BASE64_H_

#include <stdint.h>
extern uint8_t decoding_table[256];

int base64_decode(const char* value, int value_len, unsigned char** result, int* result_len);
char* base64_encode (const unsigned char* data, size_t len);

#endif
