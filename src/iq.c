#include "iq.h"
#include "helpers.h"

iq_t* iq_new (stream_t* strm, jid_t* from, jid_t* to, int type, void* payload,
              int extension_type) {
  iq_t* iq = malloc (sizeof (iq_t));
  if (iq == NULL)
    fatal ("iq_new: malloc failed");
  memset (iq, 0, sizeof (iq_t));

  iq->fId = stream_get_id (strm);

  iq->fFrom = from;
  iq->fTo = to;
  iq->fType = type;

  if (payload != NULL) {
    if (type == CLIENT_IQ_TYPE_ERROR)
      iq->fError = payload;
    else {
      extension_t * ext = malloc (sizeof (extension_t));
      if (ext == NULL)
        fatal ("iq_new: malloc failed");
      ext ->type = extension_type;
      ext->data = payload;
      iq->fPayload = ext;
    }
  }
  return iq;
}
  
