#ifndef _USTRING_H_
#define _USTRING_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct {
  uint32_t *ucs4;
  size_t len;
} ustring_t;

int utf8_width (uint8_t ch);
int decode_utf8 (ustring_t *ustring, const char *str, size_t len);
int encode_ustring (ustring_t *ustring, char** str);
void ustring_free (ustring_t *ustring);
void ustring_print (ustring_t *usring);
void ustring_print_hex (ustring_t *usring);
int ustring_compare (ustring_t *ustring1, ustring_t *ustring2);

#endif
