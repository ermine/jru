#ifndef _STREAM_DATA_H_
#define  _STREAM_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "jid/jid.h"


extern const char *ns_stream;

enum stream_error_condition_name_t
{
  STREAM_ERROR_CONDITION_NAME_BAD_FORMAT,
  STREAM_ERROR_CONDITION_NAME_BAD_NAMESPACE_PREFIX,
  STREAM_ERROR_CONDITION_NAME_CONFLICT,
  STREAM_ERROR_CONDITION_NAME_CONNECTION_TIMEOUT,
  STREAM_ERROR_CONDITION_NAME_HOST_GONE,
  STREAM_ERROR_CONDITION_NAME_HOST_UNKNOWN,
  STREAM_ERROR_CONDITION_NAME_IMPROPER_ADDRESSING,
  STREAM_ERROR_CONDITION_NAME_INTERNAL_SERVER_ERROR,
  STREAM_ERROR_CONDITION_NAME_INVALID_FROM,
  STREAM_ERROR_CONDITION_NAME_INVALID_NAMESPACE,
  STREAM_ERROR_CONDITION_NAME_INVALID_XML,
  STREAM_ERROR_CONDITION_NAME_NOT_AUTHORIZED,
  STREAM_ERROR_CONDITION_NAME_NOT_WELL_FORMED,
  STREAM_ERROR_CONDITION_NAME_POLICY_VIOLATION,
  STREAM_ERROR_CONDITION_NAME_REMOTE_CONNECTION_FAILED,
  STREAM_ERROR_CONDITION_NAME_RESET,
  STREAM_ERROR_CONDITION_NAME_RESOURCE_CONSTRAINT,
  STREAM_ERROR_CONDITION_NAME_RESTRICTED_XML,
  STREAM_ERROR_CONDITION_NAME_SEE_OTHER_HOST,
  STREAM_ERROR_CONDITION_NAME_SYSTEM_SHUTDOWN,
  STREAM_ERROR_CONDITION_NAME_UNDEFINED_CONDITION,
  STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_ENCODING,
  STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_FEATURE,
  STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_STANZA_TYPE,
  STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_VERSION,
};

enum stream_error_condition_name_t
enum_stream_error_condition_name_from_string (const char *value);
const char *enum_stream_error_condition_name_to_string (enum
							stream_error_condition_name_t);

struct stream_start_t
{
  jid_t *fTo;
  jid_t *fFrom;
  char *fId;
  char *fVersion;
  char *fLang;
};




struct stream_error_t
{
  langstring_t *fText;
  struct stream_condition_set_t
  {
    enum stream_error_condition_name_t fName;
    char *fExtra;
  } fCondition;
};


struct stream_start_t *stream_start_decode (xmlreader_t * reader);
int stream_start_encode (xmlwriter_t * writer, struct stream_start_t *data);
void stream_start_free (struct stream_start_t *data);
array_t *stream_features_decode (xmlreader_t * reader);
int stream_features_encode (xmlwriter_t * writer, array_t * data);
void stream_features_free (array_t * data);
struct stream_error_t *stream_error_decode (xmlreader_t * reader);
int stream_error_encode (xmlwriter_t * writer, struct stream_error_t *data);
void stream_error_free (struct stream_error_t *data);
#endif
