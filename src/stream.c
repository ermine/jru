#include <string.h>
#include <malloc.h>

#include "stream.h"
#include "helpers.h"
#include "jid/jid.h"
#include "errors.h"
#include "helpers.h"
#include "hex.h"

#include "starttls.h"
#include "sasl.h"
#include "bind.h"
#include "session.h"

#include "xmppdata/stream_data.h"

stream_t* stream_new (int fd, const char* content_namespace, const char* lang,
                      bool logging, void* userdata) {
  stream_t* strm = malloc (sizeof (stream_t));
  if (strm == NULL)
    fatal ("stream_new: malloc failed");

  memset (strm, 0, sizeof (stream_t));

  strm->writer = xmlwriter_new (fd);
  strm->reader = xmlreader_new (fd);

  strm->content_namespace = content_namespace;
  int err = xmlwriter_set_prefix (strm->writer, NULL, content_namespace);
  if (err != 0)
    fatal ("stream_new: cannot set default namespace");
  
  strm->lang = lang;
  strm->logging = logging;
  strm->userdata = userdata;
  memcpy (strm->id, "0", 1);

  return strm;
}

const char* stream_get_id (stream_t* strm) {
  uint64_t id = hex_to_int (strm->id);
  id++;
  hex_of_int (strm->id, id);
  return strm->id;
}

int stream_start (stream_t* strm, account_t* account) {
  if (strm == NULL)
    fatal ("stream_start: strm is null");
  if (account == NULL)
    fatal ("stream_start: account is null");

  int err;

  err = xmlwriter_start_stream (strm->writer);
  if (err != 0) return err;

  struct stream_start_t sst;
  sst.fTo = jid_of_string (account->jid->domain);
  sst.fFrom = NULL;
  sst.fId = NULL;
  sst.fLang = strm->lang;
  sst.fVersion = "1.0";

  err = stream_start_encode (strm->writer, &sst);
  if (err != 0) return err;

  err = xmlwriter_flush (strm->writer);
  if (err != 0) return err;

  extension_t* ext = xstream_read (strm->reader);
  if (strm->reader->err != 0) return strm->reader->err;
  if (ext == NULL) return ERR_EXTENSION_NOT_FOUND;
  
  if (ext->type != EXTENSION_TYPE_STREAM_START) return ERR_BAD_PROTOCOL;
  
  struct stream_start_t* s = (struct stream_start_t*) ext->data;
  if (strcmp (s->fVersion, "1.0") != 0) return ERR_XMPP_VERSION;

  return 0;
}

int stream_negotate (stream_t* strm, account_t* account) {
  int err = 0;
  extension_t* ext = NULL;
  struct stream_features_t* features = NULL;

  err = stream_start (strm, account);
  if (err != 0) return err;

  ext = xstream_read (strm->reader);
  if (strm->reader->err != 0) return strm->reader->err;
  if (ext == NULL) return ERR_BAD_PROTOCOL;

  if (ext->type != EXTENSION_TYPE_STREAM_FEATURES) return ERR_BAD_PROTOCOL;
  features = (struct stream_features_t*) ext->data;

  struct starttls_starttls_t* starttls =
    (struct starttls_starttls_t*) vlist_get ((vlist_t*) features, EXTENSION_TYPE_STARTTLS_STARTTLS);
  if (starttls != NULL)
    // todo
    ;

  struct sasl_mechanisms_t* sasl_mechanisms =
    vlist_get ((vlist_t*) features, EXTENSION_TYPE_SASL_MECHANISMS);
  if (sasl_mechanisms == NULL)
    return ERR_BAD_PROTOCOL;

  err = sasl_negotate (strm, account, sasl_mechanisms);
  if (err != 0) return err;

  if (sasl_need_restart ()) {
    xmlreader_reset (strm->reader);
    xmlwriter_reset (strm->writer);
    int err = xmlwriter_set_prefix (strm->writer, NULL, strm->content_namespace);
    if (err != 0)
      fatal ("stream_new: cannot set default namespace");

    err = stream_start (strm, account);
    if (err != 0) return err;

    ext = xstream_read (strm->reader);
    if (strm->reader->err != 0) return strm->reader->err;
    if (ext == NULL) return ERR_BAD_PROTOCOL;

    if (ext->type != EXTENSION_TYPE_STREAM_FEATURES) return ERR_BAD_PROTOCOL;
    features = (struct stream_features_t*) ext->data;
  }

  struct bind_bind_t* bind = vlist_get ((vlist_t*) features, EXTENSION_TYPE_BIND_BIND);
  if (bind == NULL) return ERR_BAD_PROTOCOL;

  err = bind_negotate (strm, account, bind);
  if (err != 0) return err;

  struct session_session_t* session =
    vlist_get ((vlist_t*) features, EXTENSION_TYPE_SESSION_SESSION);
  if (session == NULL) return ERR_BAD_PROTOCOL;

  err = session_negotate (strm, account, session);
  if (err != 0) return err;
  
  return 0;
}
