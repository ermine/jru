#include "hex.h"
#include "helpers.h"

void hex_of_binary (char* out, unsigned char* in, int in_len) {
  static const char* hextable = "0123456789abcdef";

  int i = 0;
  for (i = 0; i < in_len; i++) {
    *out++ = hextable[(*in >> 4) & 0xF];
    *out++ = hextable[(*in++) & 0xF];
  }
  *out = '\0';
}

void hex_of_int (char* out, uint64_t in) {
  static const char* hextable = "0123456789abcdef";

  int i = 0;
  for (i = 0; i < 64; i += 4) {
    if ((in >> i) == 0) break;
  }
  if (i > 4)
    i -= 4;
  
  for (; i >= 0; i -= 4) {
    *out++ = hextable[(in >> i) & 0xF];
  }
  *out = '\0';
}

uint64_t hex_to_int (const char* str) {
  uint64_t out = 0;
  char* ptr = (char*) str;

  while (1) {
    uint8_t i = 0;
    if (*ptr >= '0' && *ptr <= '9')
      i = *ptr - 48;
    else if (*ptr >= 'a' && *ptr <= 'f')
      i = *ptr - 39;
    else if (*ptr >= 'A' && *ptr <= 'F')
      i = *ptr - 55;
    else
      fatal ("hex_to_int: invalid input: %c", *ptr);
    out |= i;
    ptr++;
    if (*ptr == 0)
      break;
    out <<= 4;
  }
    
  return out;
}
