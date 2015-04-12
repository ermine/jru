#ifndef _STRINGMAP_H_
#define _STRINGMAP_H_

struct _stringpair_t;

struct _stringpair_t {
  const char* key;
  const char* value;
  struct _stringpair_t* next;
};

typedef struct _stringpair_t stringpair_t;

void stringpair_free (stringpair_t* stringpairs);

const char* stringpair_get (stringpair_t* stringpairs, const char* key);
void stringpair_set (stringpair_t** stringpairs, const char* key, const char* value);
void stringpair_delete (stringpair_t** stringpairs, const char* key);
void stringpair_delete_by_value (stringpair_t** root, const char* value);

#endif
