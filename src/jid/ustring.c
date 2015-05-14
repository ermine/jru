#include <stdio.h>
#include <string.h>
#include "utf8.h"
#include "errors.h"

#include "ustring.h"
#include "helpers.h"

int ustring_decode_utf8 (ustring_t *ustring, const char *str, const size_t len) {
  if (ustring == NULL)
    fatal ("ustring_decode_utf8: ustring is null");
  if  (ustring->ucs4 != NULL)
    fatal ("ustring_decode_utf8: ustring->ucs4 is not null");
  
  int i = 0;
  int ulen = 0;
  
  for (i = 0; i < len; ) {
    int width = utf8_width ((uint8_t) str[i]);
    if (width < 1) return width;
    ulen += width;
    i += width;
  }
    
  ustring->ucs4 = malloc (sizeof (uint32_t) * ulen);
  if (ustring->ucs4 == NULL)
    fatal ("decode_utf8: malloc failed");

  ustring->len = ulen;

  uint32_t *p = ustring->ucs4;
  
  for (i = 0; i < len; i++) {
    uint8_t u1 = (uint8_t) str[i];
    int width = utf8_width (u1);
    switch (width) {
    case 1:
      *p++ = (uint32_t) u1;
      break;
    case 2: {
      uint8_t u2 = (uint8_t) str[++i];
      if (u2 >> 6 != 0b10)
        return ERR_MALFORMED_UTF8;
      else
        *p++ = ((u1 & 0x1f)  << 6) | (u2 & 0x3f);
      break;
    }
    case 3: {
      uint8_t u2 = (uint8_t) str[++i];
      uint8_t u3 = (uint8_t) str[++i];
      if ((u2 >> 6 != 0b10) || (u3 >> 6 != 0b10))
        return ERR_MALFORMED_UTF8;
      else {
        uint32_t code = 
          ((u1 & 0x0f) << 12) | ((u2 & 0x3f) < 6) | (u3 & 0x3f);
        if (code >= 0xd800 && code <= 0xdf00)
          return ERR_MALFORMED_UTF8;
        else
          *p++ = code;
      }
      break;
    }
    case 4: {
      uint8_t u2 = (uint8_t) str[++i];
      uint8_t u3 = (uint8_t) str[++i];
      uint8_t u4 = (uint8_t) str[++i];
      if ((u2 >> 6 != 0b10) || (u3 >> 6 != 0b10) || (u4 >> 6 != 0b10))
        return ERR_MALFORMED_UTF8;
      else
        *p++ = ((u1 & 0x07) << 18) | ((u2 & 0x3f) << 12) | ((u3 & 0x3f) << 6) | (u4 & 0x3f);
      break;
    }
    default:
      return ERR_MALFORMED_UTF8;
    }
  }
  return 0;
}
            
int ustring_encode_utf8 (ustring_t *ustring, char **out) {
  int i = 0;
  int len = 0;

  if (ustring == NULL)
    fatal ("ustring_encode_utf8: ustring is null");
  if (ustring->ucs4 == NULL || ustring->len == 0)
    fatal ("ustring_encode_utf8: ustring->ucs4 is null");

  for (i = 0; i < ustring->len; i++) {
    int width = utf8_width_of_uint32 (ustring->ucs4[i]);
    if (width < 1)
      return width;
    len += width;
  }

  *out = malloc (sizeof (uint8_t) * len + 1);
  if (*out == NULL)
    fatal ("ustring_encode_ut8: malloc failed");
  
  char* ptr = *out;
  
  for (i = 0; i < ustring->len; i++) {
    uint32_t ucs4 = ustring->ucs4[i];
  
    if (ucs4 < 0x80)
      *ptr++ = (char) ucs4;
    else if (ucs4 <= 0x7ff) {
      *ptr++ = (char) (0xc0 | (ucs4 >> 6));
      *ptr++ = (char) (0x80 | (ucs4 & 0x3f));
    } else if (ucs4 <= 0xffff) {
      if (ucs4 >= 0xd800 && ucs4 < 0xe000)
        return ERR_MALFORMED_UNICODE;
      *ptr++ = (char) (0xe0 | (ucs4 >> 12));
      *ptr++ = (char) (0x80 | ((ucs4 >> 6) & 0x3f));
      *ptr++ = (char) (0x80 | (ucs4 & 0x3f));
    }
    else if (ucs4 <= 0x10ffff) {
      *ptr++ = (char) (0xf0 | (ucs4 >> 18));
      *ptr++ = (char) (0x80 | ((ucs4 >> 12) & 0x3f));
      *ptr++ = (char) (0x80 | ((ucs4 >> 6)  & 0x3f));
      *ptr++ = (char) (0x80 | (ucs4 & 0x3f));
    }
    else 
      return ERR_MALFORMED_UNICODE;
  }
  *ptr = 0;
  return len;
}

void ustring_free (ustring_t *ustring) {
  if (ustring != NULL) {
    if (ustring->ucs4 != NULL)
      free (ustring->ucs4);
    free (ustring);
  }
}

void ustring_print_hex (ustring_t *ustring) {
  if (ustring == NULL)
    fatal ("ustring_print_hex: ustring is null");
  if (ustring->ucs4 == NULL)
    fatal ("ustring_print_hex: ustring->ucs4 is null");

  int i = 0;
  for (i = 0; i < ustring->len; i++)
    printf("%04X ", ustring->ucs4[i]);

  printf("\n");
}

void ustring_print (ustring_t *ustring) {
  if (ustring == NULL)
    fatal ("ustring_print: ustring is null");
  if (ustring->ucs4 == NULL)
    fatal ("ustring_print: ustring->ucs4 is null");
  
  char *result = NULL;
  size_t ret = ustring_encode_utf8 (ustring, &result);

  if (result == NULL || ret < 0) {
    printf ("another error!\n");
    return;
  }

  char *text2 = strndup (result, ret);
  printf ("result: %d %d '%s'\n", (int) ret, (int) ustring->len, text2);

  free (text2);
  free (result);
}

int ustring_compare (ustring_t *u1, ustring_t *u2) {
  if (u1 == NULL || u2 == NULL || u1->ucs4 == NULL || u2->ucs4 == NULL)
    return 0;
  if (u1->len != u2->len)
    return 0;

  if (memcmp (u1->ucs4, u2->ucs4, u1->len) == 0)
    return 1;
  return 0;
}
