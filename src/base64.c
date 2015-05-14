#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"
#include "base64.h"
#include "errors.h"

uint8_t decoding_table[256] = {
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62, 255, 255, 255, 63, 52, 
  53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255, 255, 255, 255, 255, 255, 
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 
  16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 255, 255, 
  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 
  42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 
};
  
int base64_decode(const char* data, int data_len, unsigned char** result, int* result_len) {
  if (data_len % 4 != 0)
    return ERR_BASE64_DECODE;
  
  char* src = (char*) data;
  int len = data_len;

  *result = malloc (len / 4 * 3 + 1);
  if (*result == NULL)
    fatal ("base64_decode: malloc failed");

  unsigned char* dst = *result;
  int dst_len = 0;
  int err = 0;
  
  while (len > 0) {
    int dlen = 4;
    uint8_t dbuf[4];
    int j = 0;
    for (j = 0; j < 4; j++) {
      if (len == 0) {
        err = ERR_BASE64_DECODE;
        break;
      }

      char in = src[0];
      src++;
      len--;
      if (in == '=') {
        if (j == 0 || j == 1) {
          // incorrect padding
          err = ERR_BASE64_DECODE;
          break;
        }
        if (j == 2) {
          // "==" is expected, the first "=" is already consumed.
          if (len == 0) {
            err = ERR_BASE64_DECODE;
            break;
          }
          if (src[0] != '=') {
            // incorrect padding
            err = ERR_BASE64_DECODE;
            break;
          }
          src++;
          len--;
        }
        if (len > 0) {
          // trailing garbage
          err = ERR_BASE64_DECODE;
        }
        dlen = j;
        break;
      }
      dbuf[j] = (unsigned char) decoding_table[(int) in];
      if (dbuf[j] == 0xFF) {
        err = ERR_BASE64_DECODE;
        break;
      }
    }
    if (err != 0)
      break;
    
    switch (dlen) {
    case 4:
      dst[2] = (dbuf[2] << 6 | dbuf[3]);
    case 3:
      dst[1] = dbuf[1] << 4 | dbuf[2] >> 2;
    case 2:
      dst[0] = dbuf[0] << 2 | dbuf[1] >> 4;
    }
    dst += 3;
    dst_len += dlen - 1;
  }
  *result_len = dst_len;
  
  return err;
}

char* base64_encode (const unsigned char* src, size_t src_len) {
  int dst_len = 4 * ((src_len + 2) / 3);
  
  char* dst = malloc(dst_len + 1);
  if (dst == NULL)
    fatal ("base64_encode: malloc failed");

  static const char* encodeStd = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  int len = src_len;
  unsigned char* ptr = (unsigned char*) src;
  char* dst_ptr = dst;

  while (len > 0) {
    uint8_t b0 = 0, b1 = 0, b2 = 0, b3 = 0;
    
    if (len > 2) {
      b3 = ptr[2] & 0x3F;
      b2 = ptr[2] >> 6;
    }
    if (len >= 2) {
      b2 |= (ptr[1] << 2) & 0x3F;
      b1 = ptr[1] >> 4;
    }
    if (len >= 1) {
      b1 |= (ptr[0] << 4) & 0x3F;
      b0 = ptr[0] >> 2;
    }

    dst_ptr[0] = encodeStd[b0];
    dst_ptr[1] = encodeStd[b1];
    dst_ptr[2] = encodeStd[b2];
    dst_ptr[3] = encodeStd[b3];

    if (len < 3) {
      dst_ptr[3] = '=';
      if (len < 2) {
        dst_ptr[2] = '=';
      }
    }

    ptr += 3;
    dst_ptr += 4;

    if (len < 3) {
      break;
    }
    len -= 3;
  }
  
  *dst_ptr = '\0';
  return dst;
}
