#ifndef _BIND_H_
#define _BIND_H_

#include "xmppdata/bind_data.h"
#include "stream.h"
#include "account.h"

bool bind_is_mandatory (stream_t* strm);
bool bind_need_restart (void);
int bind_negotate (stream_t* strm, account_t* account, struct bind_bind_t* bind);

#endif
