#include <malloc.h>
#include "llist.h"
#include "helpers.h"

void llist_append(llist_t** root, void* data) {
  llist_t* item = malloc (sizeof (llist_t));
  if (item == NULL)
    fatal ("llist_append: malloc failed");
      
  item->data = data;
  item->next = NULL;

  if (*root == NULL)
    *root = item;
  else {
    llist_t* curr = *root;

    while (curr->next != NULL)
      curr = curr->next;
    curr->next = item;
  }
}

void vlist_append(vlist_t** root, void* data, int type) {
  vlist_t* item = malloc (sizeof (vlist_t));
  if (item == NULL)
    fatal ("vlist_append: malloc failed");
  
  item->type = type;
  item->data = data;
  item->next = NULL;

  if (*root == NULL)
    *root = item;
  else {
    vlist_t* curr = *root;

    while (curr->next != NULL)
      curr = curr->next;
    curr->next = item;
  }
}

void* vlist_get (vlist_t* root, int type) {
  vlist_t* curr = root;
  while (curr != NULL) {
    if (curr->type == type)
      return curr->data;
    curr = curr->next;
  }
  return NULL;
}
