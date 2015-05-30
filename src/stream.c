#include <string.h>
#include <malloc.h>

#include "stream.h"
#include "helpers.h"
#include "jid/jid.h"
#include "errors.h"
#include "helpers.h"
#include "hex.h"
#include "array.h"

#include "xmppdata/stream_data.h"

enum stream_state_enum {
  STREAM_STATE_NONE,
  STREAM_STATE_START,
  STREAM_STATE_WANT_FEATURES,
  STREAM_STATE_NEGOTATE,
  STREAM_STATE_ESTABLISHED
};

struct stream_features_data_t {
  uint8_t iterator;
  void* data;
  array_t* features;
};

stream_t* stream_new (int fd, const char* content_namespace, const char* lang,
                      bool logging, void* userdata) {
  stream_t* strm = malloc (sizeof (stream_t));
  if (strm == NULL)
    fatal ("stream_new: malloc failed");
  memset (strm, 0, sizeof (stream_t));

  strm->fd = fd;
  strm->state = STREAM_STATE_NONE;
  xmlwriter_init (&strm->writer, fd);
  xmlreader_init (&strm->reader);

  strm->content_namespace = content_namespace;
  int err = xmlwriter_set_prefix (&strm->writer, NULL, content_namespace);
  if (err != 0)
    fatal ("stream_new: cannot set default namespace");
  
  strm->lang = lang;
  strm->logging = logging;
  strm->userdata = userdata;
  memcpy (strm->id, "0", 1);

  strm->userdata = malloc (sizeof (struct stream_features_data_t));
  if (strm->userdata == NULL)
    fatal ("stream_new: malloc failed");
  memset (strm->userdata, 0, sizeof (struct stream_features_data_t));

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

  if (strm->state != STREAM_STATE_NONE)
    fatal ("stream_start: strm->state is not STREAM_STATE_NONE");
  
  int err = 0;
  
  err = xmlwriter_start_stream (&strm->writer);
  if (err != 0) return err;

  struct stream_start_t sst;
  sst.fTo = jid_of_string (account->jid->domain);
  sst.fFrom = NULL;
  sst.fId = NULL;
  sst.fLang = strm->lang;
  sst.fVersion = "1.0";
  
  err = stream_start_encode (&strm->writer, &sst);
  if (err != 0) return err;
  jid_free (sst.fTo);

  err = xmlwriter_flush (&strm->writer);
  if (err != 0) return err;

  strm->state = STREAM_STATE_START;
  return 0;
}

static extension_t* array_find (array_t* array, int type) {
  int len = array_length (array);
  int i = 0;
  extension_t* ext = NULL;
  for (i = 0; i < len; i++) {
    ext = array_get (array, i);
    if (ext->type == type)
      return ext;
  }
  return NULL;
}

struct stream_feature_t starttls_feature;
struct stream_feature_t sasl_feature;
struct stream_feature_t bind_feature;
struct stream_feature_t session_feature;

static struct stream_feature_t* knownfeatures[4] = {
  //  &starttls_feature,
  &sasl_feature,
  &bind_feature,
  &session_feature
};
static const int knownfeatures_len = 3;

int stream_process (stream_t* strm, account_t* account, extension_t* ext) {
  if (strm == NULL)
    fatal ("stream_start: strm is null");
  if (account == NULL)
    fatal ("stream_start: account is null");


  int err = 0;
  
  switch (strm->state) {
  case STREAM_STATE_NONE:
    fatal ("stream_process: strm->state is STREAM_STATE_NONE");
    
  case STREAM_STATE_START: {
    if (ext->type != EXTENSION_TYPE_STREAM_START) return ERR_BAD_PROTOCOL;
  
    struct stream_start_t* s = (struct stream_start_t*) ext->data;
    if (s->fVersion != NULL && strcmp (s->fVersion, "1.0") != 0) return ERR_XMPP_VERSION;
    stream_start_free (ext->data);
    strm->state = STREAM_STATE_WANT_FEATURES;
    break;
  }

  case STREAM_STATE_WANT_FEATURES: {
    if (ext->type != EXTENSION_TYPE_STREAM_FEATURES) return ERR_BAD_PROTOCOL;

    struct stream_features_data_t* stream_data = strm->userdata;
    stream_data->features = ext->data;

    uint8_t i = 0;
    for (i = stream_data->iterator; i < knownfeatures_len; i++ ) {
      extension_t* feature = array_find (stream_data->features, knownfeatures[i]->extension_type);
      if (feature == NULL) {
        if (knownfeatures[i]->is_mandatory(strm))
          return ERR_FEATURE_IS_REQUIRED;
        else
          continue;
      }
      strm->state = STREAM_STATE_NEGOTATE;
      stream_data->iterator = i;
      err = knownfeatures[i]->negotate (strm, account, &stream_data->data, feature);
      if (err == 1) return 0;
      if (err != 0) return err;
      return 0;
    }
    stream_features_free (stream_data->features);
    free (strm->userdata);
    strm->userdata = NULL;
    strm->state = STREAM_STATE_ESTABLISHED;
    break;
  }

  case STREAM_STATE_NEGOTATE: {
    struct stream_features_data_t* stream_data = strm->userdata;
    err = knownfeatures[stream_data->iterator]->negotate (strm, account, &stream_data->data, ext);
    xstream_extension_free (ext);
    if (err == 1) return 0;
    if (err != 0) return err;
    
    if (knownfeatures[stream_data->iterator]->need_to_restart()) {
      stream_features_free (stream_data->features);
      xmlreader_reset (&strm->reader);
      xmlwriter_reset (&strm->writer);
      int err = xmlwriter_set_prefix (&strm->writer, NULL, strm->content_namespace);
      if (err != 0)
        fatal ("stream_new: cannot set default namespace");
      stream_data->iterator++;
      strm->state = STREAM_STATE_NONE;
      return stream_start (strm, account);
    }

    stream_data->iterator++;

    uint8_t i = 0;
    for (i = stream_data->iterator; i < knownfeatures_len; i++) {
      extension_t* feature = array_find (stream_data->features, knownfeatures[i]->extension_type);
      if (feature == NULL) {
        if (knownfeatures[i]->is_mandatory(strm))
          return ERR_FEATURE_IS_REQUIRED;
        else
          continue;
      }
      strm->state = STREAM_STATE_NEGOTATE;
      stream_data->iterator = i;
      err = knownfeatures[i]->negotate (strm, account, &stream_data->data, feature);
      if (err == 1) return 0;
      if (err != 0) return err;
      break;
    }

    stream_features_free (stream_data->features);
    free (strm->userdata);
    strm->userdata = NULL;
    strm->state = STREAM_STATE_ESTABLISHED;
    return 0;
  }
    
  case STREAM_STATE_ESTABLISHED:
    if (strm->session_handler != NULL)
      strm->session_handler (strm, account, ext);
    xstream_extension_free (ext);
    // break;
    
  default:
    fatal ("Unknown stream state");
  }
  return 0;
}
