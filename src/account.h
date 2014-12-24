#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "jid/jid.h"

typedef struct {
  jid_t *jid;
  char *password;
  int port;
  char *ip;
} account_t;

#endif
