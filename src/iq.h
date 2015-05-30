#ifndef _IQ_H_
#define _IQ_H_

#include "xmppdata/client_data.h"
#include "stream.h"
#include "jid/jid.h"

typedef struct client_iq_t iq_t;

iq_t* iq_new (stream_t* strm, jid_t* from, jid_t* to, int type, void* payload,
              int extension_type);
void iq_free (iq_t* iq);

#endif
