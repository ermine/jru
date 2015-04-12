#include <stdio.h>
#include <string.h>

#include "ustring.h"
#include "helpers.h"

#define MalformedUTF8 -1
#define MalformedUnicode -2


static uint8_t utf8_width_of_uint32 (uint32_t u) {
  if (u < 0x80)
    return 1;
  else if (u < 0x800)
    return 2;
  else if (u < 0x10000)
    return 3;
  else if (u < 0x110000)
    return 4;
  return MalformedUnicode;
}

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
    return MalformedUTF8;
}
  
int decode_utf8 (ustring_t *ustring, const char *str, const size_t len) {
  if (ustring == NULL)
    fatal ("decode_utf8: ustring is null");
  if  (ustring->ucs4 != NULL)
    fatal ("decode_utf8: ustring->ucs4 is not null");
  
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
    return -3;

  ustring->len = ulen;

  uint32_t *p = ustring->ucs4;
  
  for (i = 0; i < len; i++) {
    uint8_t u1 = (uint8_t) str[i];
    if (u1 >= 0 && u1 < 128)
      *p++ = (uint32_t) u1;
    else if (u1 > 191 && u1 < 224) {
      uint8_t u2 = (uint8_t) str[++i];
      if (u2 >> 6 != 0b10)
        return MalformedUTF8;
      else
        *p++ = ((u1 & 0x1f)  << 6) | (u2 & 0x3f);
    } else if (u1 > 223 && u1 < 240) {
      uint8_t u2 = (uint8_t) str[++i];
      uint8_t u3 = (uint8_t) str[++i];
      if ((u2 >> 6 != 0b10) || (u3 >> 6 != 0b10))
        return MalformedUTF8;
      else {
        uint32_t code = 
          ((u1 & 0x0f) << 12) | ((u2 & 0x3f) < 6) | (u3 & 0x3f);
        if (code >= 0xd800 && code <= 0xdf00)
          return MalformedUTF8;
        else
          *p++ = code;
      }
    } else if (u1 > 239 && u1 < 248) {
      uint8_t u2 = (uint8_t) str[++i];
      uint8_t u3 = (uint8_t) str[++i];
      uint8_t u4 = (uint8_t) str[++i];
      if ((u2 >> 6 != 0b10) || (u3 >> 6 != 0b10) || (u4 >> 6 != 0b10))
        return MalformedUTF8;
      else
        *p++ = ((u1 & 0x07) << 18) | ((u2 & 0x3f) << 12) | ((u3 & 0x3f) << 6) | (u4 & 0x3f);
    }
    else
      return MalformedUTF8;
  }
  return 0;
}
            
int encode_ustring (ustring_t *ustring, char **str) {
  int i = 0;
  int len = 0;

  if (ustring == NULL)
    fatal ("encode_ustring: ustring is null");
  if (ustring->ucs4 == NULL || ustring->len == 0)
    fatal ("encode_ustring: ustring->ucs4 is null");

  for (i = 0; i < ustring->len; i++) {
    int width = utf8_width_of_uint32 (ustring->ucs4[i]);
    if (width < 1)
      return width;
    len += width;
  }

  *str = malloc (sizeof (uint8_t) * len);
  char *p = *str;
  
  for (i = 0; i < ustring->len; i++) {
    uint32_t ucs4 = ustring->ucs4[i];
  
    if (ucs4 < 0x80)
      *p++ = (char) ucs4;
    else if (ucs4 <= 0x7ff) {
      *p++ = (char) (0xc0 | (ucs4 >> 6));
      *p++ = (char) (0x80 | (ucs4 & 0x3f));
    } else if (ucs4 <= 0xffff) {
      if (ucs4 >= 0xd800 && ucs4 < 0xe000)
        return MalformedUnicode;
      *p++ = (char) (0xe0 | (ucs4 >> 12));
      *p++ = (char) (0x80 | ((ucs4 >> 6) & 0x3f));
      *p++ = (char) (0x80 | (ucs4 & 0x3f));
    }
    else if (ucs4 <= 0x10ffff) {
      *p++ = (char) (0xf0 | (ucs4 >> 18));
      *p++ = (char) (0x80 | ((ucs4 >> 12) & 0x3f));
      *p++ = (char) (0x80 | ((ucs4 >> 6)  & 0x3f));
      *p++ = (char) (0x80 | (ucs4 & 0x3f));
    }
    else 
      return MalformedUnicode;
  }
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
  size_t ret = encode_ustring (ustring, &result);

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
