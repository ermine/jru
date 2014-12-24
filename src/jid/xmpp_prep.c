#include <stdio.h>
#include <stdlib.h>
#include "xmpp_prep_tables.h"
#include "xmpp_prep_tables2.h"
#include <string.h>

#include "ustring.h"

/* http://unicode.org/reports/tr15/ */

#define hangulSBase 0xAC00
#define hangulLBase 0x1100
#define hangulVBase 0x1161
#define hangulTBase 0x11A7
#define hangulLCount 19
#define hangulVCount 21
#define hangulTCount 28
#define hangulNCount (hangulVCount * hangulTCount) /* 588 */
#define hangulSCount (hangulLCount * hangulNCount) /* 11172 */

static uint32_t get_bst (uint32_t arr[][3], uint32_t x, uint16_t s, uint16_t e) {
  if (s > e || x < arr[s][0] || x >  arr[e][1])
    return -1;
  else {
    uint16_t mid = s + (e-s)/2;
    uint32_t *amid = arr[mid];
    if (x < amid[0])
      return get_bst (arr, x, s, (mid-1));
    else if (x > amid[1])
      return get_bst (arr, x, (mid+1), e);
    else
      return amid[2];
  }
}

static uint32_t get_casemap (uint32_t x) {
  if (x > 0x40 && x < 0x5b)
    return  casemap[0][2];
  else
    return get_bst (casemap, x, 1, casemap_max_idx);
}

static int16_t get_dmap_idx (uint32_t x, int s, int e) {
  if (s > e)
    return -1;
  else {
    int mid = s + (e - s) / 2;
    dmap_t row = dmap[mid];
    if (x < row.code)
      return get_dmap_idx (x, s, (mid-1));
    else if (x > row.code + row.rows)
      return get_dmap_idx (x, mid+1, e);
    else
      return row.idx + x - row.code;
  }
}

static uint32_t get_composite (uint32_t ch1, int s, int e) {
  if (s > e)
    return -1;
  else {
    int mid = s + (e - s) / 2;
    if (ch1 < cmap_data[mid][0])
      return get_composite (ch1, s, (mid-1));
    else if (ch1 > cmap_data[mid][0])
      return get_composite (ch1, (mid+1), e);
    else
      return cmap_data[mid][1];
  }
}

static uint32_t get_comp (uint32_t ch1, uint32_t ch2, int s, int e) {
  if (s > e)
    return -1;
  else {
    int mid = s + (e - s) / 2;
    dmap_t row = cmap[mid];
    if (ch2 < row.code)
      return get_comp (ch1, ch2, s, (mid-1));
    else if (ch2 > row.code)
      return get_comp (ch1, ch2, mid+1, e);
    else
      return get_composite (ch1, row.idx, row.idx + row.rows);
  }
}

static uint32_t *get_decomp (uint32_t x) {
  if (x > 0x009F && x < 0x2FA1E) {
    int idx = get_dmap_idx (x, 0, dmap_max_idx);
    if (idx != -1) 
      return (uint32_t *) &dmap_data[idx];
  }
  return NULL;
}
  
static uint32_t compose_hangul (uint32_t ch1, uint32_t ch2) {
  /* check if two current characters are L and V */
  int32_t lindex = ch1 - hangulLBase;
  if (lindex >= 0 && lindex < hangulLCount) {
    uint32_t vindex = ch2 - hangulVBase;
    if (vindex >= 0 && vindex < hangulVBase) {
      /* make syllable of form LV */
      return hangulSBase + (lindex * hangulVCount + vindex) * hangulTCount;
    }
  }

  /* 2. check to see if two current characters are LV and T */
  int32_t sindex = ch1 - hangulSBase;
  if ((sindex >= 0 && sindex < hangulSCount) && ((sindex % hangulTCount) == 0)) {
    int32_t tindex = ch2 - hangulTBase;
    if (tindex > 0 && tindex < hangulTCount) {
      /* make syllable of form LVT */
      return ch1 + tindex;
    }
  }
  /* if neither case was true */
  return -1;
}

static uint32_t composeTwo (uint32_t ch1, uint32_t ch2) {
  uint32_t newch = compose_hangul (ch1, ch2);
  if (newch != -1)
    return newch;
  if (ch2 > 767 && ch2 < 12443)
    return get_comp (ch1, ch2, 0, comps_max_idx);
  else
    return -1;
}  

static ustring_t *compose (uint32_t *result, uint8_t *res_class, size_t r_len) {
  int i = 0;
  uint8_t prevcc = 0;
  uint32_t ch1 = result[0];
  uint32_t *acc, *accp;
  acc = malloc (sizeof (uint32_t) * r_len);
  accp = acc;
  uint32_t *comps = malloc (sizeof (uint32_t) * r_len);
  uint32_t *compsp = comps;
  
  for (i = 1; i < r_len; i++) {
    uint32_t ch2 = result[i];
    uint8_t cc = res_class[i];
    uint32_t newch1;
    if (prevcc == 0 || cc > prevcc)
      newch1 = composeTwo (ch1, ch2);
    else
      newch1 = -1;
    if (newch1 != -1) {
      ch1 = newch1;
    } else if (cc == 0) {
      *accp++ = ch1;
      uint32_t *p;
      for (p = comps; p < compsp; p++) *accp++ = *p;
      compsp = comps;
      ch1 = ch2;
      prevcc = 0;
    } else {
      prevcc = cc;
      *compsp++ = ch2;
    }
  }
  *accp++ = ch1;
  if (compsp > comps) {
    uint32_t *p = NULL;
    for (p = comps; p < compsp; p++) *accp++ = *p;
  }
  free (comps);
  ustring_t *ustring = malloc (sizeof (ustring_t));
  ustring->ucs4 = acc;
  ustring->len = accp - acc;
  return ustring;
}

void nfkc (ustring_t *ustring) {
  if (ustring == NULL || ustring->ucs4 == NULL)
    return;

  uint32_t *result = malloc (sizeof (uint32_t) * ustring->len);
  uint8_t *res_class = malloc (sizeof (uint8_t) * ustring->len);
  
  uint32_t *resultp = result;
  uint8_t *res_classp = res_class;
  
  int i = 0, j = 0;

  size_t size = ustring->len;
  
  for (i = 0; i < ustring->len; i++) {
    uint32_t x = ustring->ucs4[i];
    if (x < 0xAC00 || x > 0xD7AF) {
      uint32_t *data = get_decomp (x);
      if (data == NULL) {
        *resultp++ = x;
        *res_classp++ = 0;
      } else {
        for (j = 0; j < 18 && data[j] != 0; j++) {
          if (i + j >= size - 1) {
            int offset = resultp - result;
            result = realloc (result, sizeof (uint32_t) * (size + 6));
            res_class = realloc (res_class, sizeof (uint8_t) * (size + 6));
            resultp = result + offset;
            res_classp = res_class + offset;
            size += 6;
          }
          *resultp++ = data[j] >> 8;
          *res_classp++ = data[j] & 0xFF;
        }
        if (ustring->len - i > size - (result - resultp)) {
          printf ("realloc2\n");
          int offset = resultp - result;
          result = realloc (result, sizeof (uint32_t) * (size + 6));
          res_class = realloc (res_class, sizeof (uint8_t) * (size + 6));
          resultp = result + offset;
          res_classp = res_class + offset;
          size += 6;
        }
      }
    } else {
      int32_t sindex = x - hangulSBase;
      if (sindex < 0 || sindex >= hangulSCount) {
        *resultp++ = x;
        *res_class = 0;
      } else {
        uint32_t l = hangulLBase + sindex / hangulNCount;
        uint32_t v = hangulVBase + (sindex % hangulNCount) / hangulTCount;
        uint32_t t = hangulTBase + sindex % hangulTCount;
        *resultp++ = l;
        *res_classp++ = 0;
        *resultp++ = v;
        *res_classp++ = 0;
        if (t != hangulTBase) {
          *resultp++ = t;
          *res_classp++ = 0;
        }
      }
    }
  }
            
  // canonical order
  size_t r_len = resultp - result;
  int prev = 0;

  for (i = 1; i < r_len; i++) {
    if (res_class[i] == 0 || res_class[prev] <= res_class[i]) {
      prev++;
      continue;
    } else {
      uint32_t tmp = result[prev];
      uint8_t tmp_cc = res_class[prev];
      result[prev] = result[i];
      res_class[prev] = res_class[i];
      result[i] = tmp;
      res_class[i] = tmp_cc;
      if (prev > 0)
        prev--;
      i = prev;
    }
  }

  ustring_t *ret = compose (result, res_class, r_len);

  free (result);
  free (res_class);
  free (ustring->ucs4);
  ustring->ucs4 = ret->ucs4;
  ustring->len = ret->len;
  free (ret);
}

void nodeprep (ustring_t *ustring) {
  if (ustring == NULL || ustring->ucs4 == NULL)
    return;

  int i = 0, j = 0;
  uint32_t *result = malloc (sizeof (uint32_t) * ustring->len);
  if (result == NULL)
    return;
  uint32_t *p = result;
  
  for (i = 0; i < ustring->len; i++) {
    uint32_t x = ustring->ucs4[i];
    uint32_t v = get_casemap (x);
    if (v == -1)
      *p++ = x;
    else if (v == 0)
      ;
    else if (v & b_mc) {
      uint16_t *z = fmap[v >> b_shift];
      for (j = 0; j < 4 && z[j] != 0; j++) {
        *p++ = z[j];
      }
    }
    else
      *p++ = x + (v >> b_shift);
  }
  ustring->len = p - result;
  free (ustring->ucs4);
  ustring->ucs4 = result;

  nfkc (ustring);
}

void resourceprep (ustring_t *ustring) {
  int i = 0, j = 0;

  for (i = 0; i < ustring->len; i++) {
    if (get_casemap (ustring->ucs4[i]) == 0) {
      for (j = i+1; j < ustring->len; j++)
        ustring->ucs4[j-1] = ustring->ucs4[j];
      ustring->len--;
    }
  }
  nfkc (ustring);
}
  
/* Check prohibited symbols and bidi */
static int check_prohibits (int p, ustring_t *ustring) {
  int i = 0;
  int dir;

  if (ustring->len == 0)
    return 0;
  
  uint32_t x = ustring->ucs4[i];
  uint8_t v = get_bst (prohibits, x, 0, prohibits_max_idx);
  if (v == -1)
    dir = b_l;
  else if (v & p)
    return -1;
  else if (v & b_randal)
    dir = b_randal;
  else
    dir = b_l;
  
  for (i = 1; i < ustring->len; i++) {
    uint32_t x = ustring->ucs4[i];
    uint8_t v = get_bst (prohibits, x, 0, prohibits_max_idx);
    if (v == -1)
      if (i + 1 == ustring->len && dir == b_randal)
        return -1;
      else
        ;
    else if (v & p)
      return -1;
    else if (!(v & dir) && (v & b_randal || v & b_l))
      return -1;
  }
  return 0;
}

int strong_nodeprep (ustring_t *ustring) {
  nodeprep (ustring);
  return check_prohibits (b_nodeprep_prohibit, ustring);
}

int strong_resourceprep (ustring_t *ustring) {
  resourceprep (ustring);
  return check_prohibits (b_resourceprep_prohibit, ustring);
}

/* for domains */
void nameprep (ustring_t *ustring) {
  int i = 0, j = 0;
  uint32_t *result = malloc (sizeof (uint32_t) * ustring->len);
  uint32_t *p = result;
  for (i = 0; i < ustring->len; i++) {
    uint32_t v = get_casemap (ustring->ucs4[i]);
    if (v == -1)
      *p++ = ustring->ucs4[i];
    else if (v == 0)
      ;
    else if (v & b_mc) {
      uint16_t *z = fmap[v >> b_shift];
      for (j = 0; j < 4 && z[j] != 0; j++) {
        *p++ = z[j];
      }
    }
    else
      *p++ = ustring->ucs4[i] + (v >> b_shift);
  }
  free (ustring->ucs4);
  ustring->ucs4 = result;
  ustring->len = p - result;
  nfkc (ustring);
}

int strong_nameprep (ustring_t *ustring) {
  nameprep (ustring);
  return check_prohibits (b_nameprep_prohibit, ustring);
}

