#include <stdint.h>
#include <stdlib.h>

static unsigned char encoding_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
  'w', 'x', 'y', 'z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', '+', '/'
};

static unsigned int decoding_table[256] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0, 63,
  52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0, 0, 0, 0, 0,
  0, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
  41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
  
static int mod_table[] = {0, 2, 1};

char *base64_encode(const unsigned char *data, size_t len) {
  int output_len = 4 * ((len + 2) / 3);
  
  char *encoded_data = malloc(output_len + 1);
  if (encoded_data == NULL) return NULL;

  int i = 0, j = 0;
  for (i = 0, j = 0; i < len;) {
    
    uint32_t octet_a = i < len ? (unsigned char)data[i++] : 0;
    uint32_t octet_b = i < len ? (unsigned char)data[i++] : 0;
    uint32_t octet_c = i < len ? (unsigned char)data[i++] : 0;
    
    uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
    
    encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
  }
  
  for (i = 0; i < mod_table[len % 3]; i++)
    encoded_data[output_len - 1 - i] = '=';
  
  return encoded_data;
}


unsigned char *base64_decode(const char *data, size_t len) {
  if (len % 4 != 0)
    return NULL;
  
  int output_len = len / 4 * 3 + 1;
  if (data[len - 1] == '=') (output_len)--;
  if (data[len - 2] == '=') (output_len)--;
  
  unsigned char *decoded_data = malloc(output_len);
  if (decoded_data == NULL) return NULL;

  int i = 0, j = 0;
  for (i = 0, j = 0; i < len;) {
    
    uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
    
    uint32_t triple = (sextet_a << 3 * 6)
      + (sextet_b << 2 * 6)
      + (sextet_c << 1 * 6)
      + (sextet_d << 0 * 6);
    
    if (j < output_len) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
    if (j < output_len) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
    if (j < output_len) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
  }
  decoded_data[output_len] = '\0';
  return decoded_data;
}
