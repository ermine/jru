#ifndef _LLIST_H_
#define _LLIST_H_

struct _llist_t;
struct _llist_t {
  void* data;
  struct _llist_t* next;
};
typedef struct _llist_t llist_t;

void llist_append (llist_t** root, void* data);
void llist_free (llist_t* root);

struct _vlist_t;
struct _vlist_t {
  int type;
  void *data;
  struct _vlist_t *next;
};
typedef struct _vlist_t vlist_t;

void vlist_append (vlist_t** root, void* data, int type);
void vlist_free (vlist_t* root);
void* vlist_get (vlist_t* root, int type);

#endif
