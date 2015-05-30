#include <stdlib.h>
#include "utf8.h"
#include "errors.h"
#include "helpers.h"

int utf8_width (const uint8_t ch) {
  if (ch >= 000 && ch < 128)
    return 1;
  else if (ch > 191 && ch < 224) {
    return 2;
  } else if (ch > 223 && ch < 240) {
    return 3;
  } else if (ch > 239 && ch < 248) {
    return 4;
  } else
    return ERR_MALFORMED_UTF8;
}

int utf8_append (char* str, uint32_t u) {
  if (str == NULL)
    fatal ("utf8_append: str is null");
  
  if (u < 0x80)
    *str = (char) u;
  else if (u <= 0x7ff) {
    *str++ = (char) (0xc0 | (u >> 6));
    *str = (char) (0x80 | (u & 0x3f));
  } else if (u <= 0xffff) {
    if (u >= 0xd800 && u < 0xe000)
      return ERR_MALFORMED_UNICODE;
    *str++ = (char) (0xe0 | (u >> 12));
    *str++ = (char) (0x80 | ((u >> 6) & 0x3f));
    *str = (char) (0x80 | (u & 0x3f));
  } else if (u <= 0x10ffff) {
    *str++ = (char) (0xf0 | (u >> 18));
    *str++ = (char) (0x80 | ((u >> 12) & 0x3f));
    *str++ = (char) (0x80 | ((u >> 6)  & 0x3f));
    *str = (char) (0x80 | (u & 0x3f));
  } else 
    return ERR_MALFORMED_UNICODE;

  return 0;
}

int utf8_width_of_uint32 (uint32_t u) {
  if (u < 0x80)
    return 1;
  else if (u < 0x800)
    return 2;
  else if (u < 0x10000)
    return 3;
  else if (u < 0x110000)
    return 4;
  return ERR_MALFORMED_UNICODE;
}

