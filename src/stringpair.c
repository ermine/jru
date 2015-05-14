#include <malloc.h>
#include "stringpair.h"
#include "helpers.h"

void stringpair_free (stringpair_t* stringpairs) {
  if (stringpairs == NULL)
    return;

  stringpair_t* curr = stringpairs;
  while (curr != NULL) {
    stringpair_t* next = curr->next;
    free (curr);
    curr = next;
  }
}

const char* stringpair_get (stringpair_t* root, const char* key) {
  if (root == NULL)
    return NULL;

  stringpair_t* curr = root;
  while (curr != NULL) {
    if (curr->key == key)
      return curr->value;
    curr = curr->next;
  }
  return NULL;
}

void stringpair_set (stringpair_t** root, const char* key, const char* value) {
  stringpair_t* pair = malloc (sizeof (stringpair_t));
  pair->key = key;
  pair->value = value;
  pair->next = NULL;

  if (*root == NULL)
    *root = pair;
  else {
    stringpair_t* curr = *root;
    while (curr->next != NULL)
      curr = curr->next;
    curr->next = pair;
  }
}

void stringpair_delete (stringpair_t** root, const char* key) {
  if (*root == NULL)
    return;

  stringpair_t* curr = *root;
  stringpair_t* prev = NULL;
  
  while (curr != NULL) {
    if (curr->key == key) {
      if (prev == NULL)
        *root = curr->next;
      else
        prev->next = curr->next;
      break;
    }
    prev = curr;
    curr = curr->next;
  }
}
  

void stringpair_delete_by_value (stringpair_t** root, const char* value) {
  if (*root == NULL)
    return;

  stringpair_t* curr = *root;
  stringpair_t* prev = NULL;
  
  while (curr != NULL) {
    if (curr->value == value) {
      if (prev == NULL)
        *root = curr->next;
      else
        prev->next = curr->next;
      break;
    }
    prev = curr;
    curr = curr->next;
  }
}
