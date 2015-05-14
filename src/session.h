#ifndef _SESSION_H_
#define _SESSION_H_

#include "xmppdata/session_data.h"
#include "stream.h"
#include "account.h"

bool session_is_mandatory (stream_t* strm);
bool session_need_restart (void);
int session_negotate (stream_t* strm, account_t* account, struct session_session_t* session);

#endif
