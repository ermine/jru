#ifndef _CONNECT_H_
#define _CONNECT_H_

#include "account.h"

#define DEFAULT_PORT 5222
#define SRV_PREFIX "_xmpp-client._tcp."


int tcp6_connect(const account_t *account);
int tcp4_connect(const account_t *account);

#endif
