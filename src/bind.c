#include "bind.h"
#include "iq.h"
#include "errors.h"
#include "xmppdata/extensions.h"

bool bind_is_mandatory (stream_t* strm) {
  return true;
}

bool bind_need_restart (void) {
  return false;
}

int bind_negotate (stream_t* strm, account_t* account, struct bind_bind_t* bind) {
  if (account->jid->resource != NULL)
    bind->fResource = account->jid->resource;

  jid_t* to = jid_of_string (account->jid->domain);
  iq_t* iq = iq_new (strm, NULL, to, CLIENT_IQ_TYPE_SET, bind,
                     EXTENSION_TYPE_BIND_BIND);
  int err = client_iq_encode (strm->writer, iq);
  if (err != 0) return err;

  err = xmlwriter_flush (strm->writer);
  if (err != 0) return err;
  
  extension_t* ext = xstream_read (strm->reader);
  if (strm->reader->err != 0) return strm->reader->err;
  if (ext == NULL) return ERR_BAD_PROTOCOL;
  switch (ext->type) {
  case EXTENSION_TYPE_CLIENT_IQ: {
    iq_t* iq = ext->data;
    if (iq->fType == CLIENT_IQ_TYPE_RESULT) {
      if (iq->fPayload != NULL && iq->fPayload->type == EXTENSION_TYPE_BIND_BIND) {
        struct bind_bind_t* bind = iq->fPayload->data;
        if (bind->fJid != NULL) {
          strm->jid = bind->fJid;
          return 0;
        } else
          return ERR_BAD_PROTOCOL;
      }
    }
    return ERR_BAD_PROTOCOL;
  }
  case EXTENSION_TYPE_STREAM_ERROR:
    strm->xmpp_error = ext;
    return ERR_XMPP_ERROR;
  }
  return ERR_BAD_PROTOCOL;
}
