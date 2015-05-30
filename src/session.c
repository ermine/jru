#include "xmppdata/session_data.h"
#include "iq.h"
#include "errors.h"

bool session_is_mandatory (stream_t* strm) {
  return false;
}

bool session_need_restart (void) {
  return false;
}

int session_negotate (stream_t* strm, account_t* account, void** data, extension_t* ext) {
  switch (ext->type) {
  case EXTENSION_TYPE_SESSION_SESSION: {
    struct session_session_t session;
    iq_t* iq = iq_new (strm, strm->jid, NULL, CLIENT_IQ_TYPE_SET, &session,
                       EXTENSION_TYPE_SESSION_SESSION);
    int err = client_iq_encode (&strm->writer, iq);
    if (err != 0) return err;
    iq_free (iq);
  
    err = xmlwriter_flush (&strm->writer);
    if (err != 0) return err;
    return 1;
  }
    
  case EXTENSION_TYPE_CLIENT_IQ: {
    iq_t* resp = ext->data;
    if (resp->fType == CLIENT_IQ_TYPE_RESULT) {
      return 0;
    }
    return ERR_BAD_PROTOCOL;
  }
  case EXTENSION_TYPE_STREAM_ERROR: {
    extension_t* error = malloc (sizeof (extension_t));
    memcpy (error, &ext, sizeof (extension_t));
    strm->xmpp_error = error;
    return ERR_XMPP_ERROR;
  }
  }
  return ERR_BAD_PROTOCOL;
}

struct stream_feature_t session_feature = {
  EXTENSION_TYPE_SESSION_SESSION,
  session_is_mandatory,
  session_need_restart,
  session_negotate
};
