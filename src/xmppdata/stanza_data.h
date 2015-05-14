#ifndef _STANZA_DATA_H_
#define  _STANZA_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_stanza;

enum stanza_error_condition_name_t
{
  STANZA_ERROR_CONDITION_NAME_BAD_REQUEST,
  STANZA_ERROR_CONDITION_NAME_CONFLICT,
  STANZA_ERROR_CONDITION_NAME_FEATURE_NOT_IMPLEMENTED,
  STANZA_ERROR_CONDITION_NAME_FORBIDDEN,
  STANZA_ERROR_CONDITION_NAME_GONE,
  STANZA_ERROR_CONDITION_NAME_INTERNAL_SERVER_ERROR,
  STANZA_ERROR_CONDITION_NAME_ITEM_NOT_FOUND,
  STANZA_ERROR_CONDITION_NAME_JID_MALFORMED,
  STANZA_ERROR_CONDITION_NAME_NOT_ACCEPTABLE,
  STANZA_ERROR_CONDITION_NAME_NOT_ALLOWED,
  STANZA_ERROR_CONDITION_NAME_NOT_AUTHORIZED,
  STANZA_ERROR_CONDITION_NAME_PAYMENT_REQUIRED,
  STANZA_ERROR_CONDITION_NAME_POLICY_VIOLATION,
  STANZA_ERROR_CONDITION_NAME_RECIPIENT_UNAVAILABLE,
  STANZA_ERROR_CONDITION_NAME_REDIRECT,
  STANZA_ERROR_CONDITION_NAME_REGISTRATION_REQUIRED,
  STANZA_ERROR_CONDITION_NAME_REMOTE_SERVER_NOT_FOUND,
  STANZA_ERROR_CONDITION_NAME_REMOTE_SERVER_TIMEOUT,
  STANZA_ERROR_CONDITION_NAME_RESOURCE_CONSTRAINT,
  STANZA_ERROR_CONDITION_NAME_SERVICE_UNAVAILABLE,
  STANZA_ERROR_CONDITION_NAME_SUBSCRIPTION_REQUIRED,
  STANZA_ERROR_CONDITION_NAME_UNDEFINED_CONDITION,
  STANZA_ERROR_CONDITION_NAME_UNEXPECTED_REQUEST,
};

enum stanza_error_condition_name_t
enum_stanza_error_condition_name_from_string (const char *value);
const char *enum_stanza_error_condition_name_to_string (enum
							stanza_error_condition_name_t);

struct stanza_error_t
{
  langstring_t *fText;
  struct stanza_condition_set_t
  {
    enum stanza_error_condition_name_t fName;
    const char *fExtra;
  } fCondition;
};


struct stanza_error_t *stanza_error_decode (xmlreader_t * reader);
int stanza_error_encode (xmlwriter_t * writer, struct stanza_error_t *data);
#endif
