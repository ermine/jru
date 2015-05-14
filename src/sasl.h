#ifndef _SASL_H_
#define _SASL_H_

#include "xmppdata/sasl_data.h"
#include "stream.h"
#include "account.h"

bool sasl_is_mandatory (stream_t* strm);
bool sasl_need_restart (void);
int sasl_negotate (stream_t* strm, account_t* account, struct sasl_mechanisms_t* sasl_mechanisms);

#endif
