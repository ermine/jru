#include "xmppdata/starttls_data.h"
#include "stream.h"
#include "account.h"
#include "errors.h"
#include "xmppdata/extensions.h"

bool starttls_is_mandatory (stream_t* strm) {
  // todo: check config: required, enabled, disabled
  return false;
}

bool starttls_need_restart (void) {
  return true;
}

int starttls_negotate (stream_t* strm, account_t* account, void** data, extension_t* ext) {
  switch (ext->type) {
  case EXTENSION_TYPE_STARTTLS_STARTTLS: {
    // struct starttls_starttls_t* starttls = ext->data;

    struct starttls_starttls_t sp;
    int err = starttls_starttls_encode (&strm->writer, &sp);
    if (err != 0) return err;
  
    err = xmlwriter_flush (&strm->writer);
    if (err != 0) return err;
    return 1;
  }

  case EXTENSION_TYPE_STARTTLS_PROCEED: {
    return 0;
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

struct stream_feature_t starttls_feature = {
  EXTENSION_TYPE_STARTTLS_STARTTLS,
  starttls_is_mandatory,
  starttls_need_restart,
  starttls_negotate,
};
