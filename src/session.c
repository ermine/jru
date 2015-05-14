#include "session.h"
#include "iq.h"
#include "errors.h"

bool session_is_mandatory (stream_t* strm) {
  return false;
}

bool session_need_restart (void) {
  return false;
}

int session_negotate (stream_t* strm, account_t* account, struct session_session_t* session) {
  iq_t* iq = iq_new (strm, strm->jid, NULL, CLIENT_IQ_TYPE_SET, session,
                     EXTENSION_TYPE_SESSION_SESSION);
  int err = client_iq_encode (strm->writer, iq);
  if (err != 0) return err;
  free (iq);
  
  err = xmlwriter_flush (strm->writer);
  if (err != 0) return err;

  extension_t* ext = xstream_read (strm->reader);
  if (strm->reader->err != 0) return strm->reader->err;
  if (ext == NULL) return ERR_BAD_PROTOCOL;
  switch (ext->type) {
  case EXTENSION_TYPE_CLIENT_IQ: {
    iq_t* resp = ext->data;
    if (resp->fType == CLIENT_IQ_TYPE_RESULT) {
      free (resp);
      return 0;
    }
    free (resp);
    return ERR_BAD_PROTOCOL;
  }
  case EXTENSION_TYPE_STREAM_ERROR:
    strm->xmpp_error = ext;
    return ERR_XMPP_ERROR;
  }
  return ERR_BAD_PROTOCOL;
}
