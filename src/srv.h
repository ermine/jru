#ifndef _SRV_H_
#define _SRV_H_

typedef struct {
  char *name;
  int prio;
  int weight;
  int port;
} srv_record;

struct _srv_list;

struct _srv_list {
  srv_record *data;
  struct _srv_list *next;
};

typedef struct _srv_list srv_list;

srv_list *srv_lookup(const char* service);

srv_record *srv_record_get(srv_list **srvs);

void srv_list_destroy (srv_list *srvlist);

#endif
