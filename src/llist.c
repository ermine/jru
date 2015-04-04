#include "types.h"

void llist_append(llist_t *root, void* data) {
  llist_t *curr = root;

  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = malloc (sizeof (llist_t));
  curr->next->data = data;
  curr->next->next = NULL;
}
