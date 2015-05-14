#ifndef _SASL_DATA_H_
#define  _SASL_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_sasl;

enum sasl_failure_condition_t
{
  SASL_FAILURE_CONDITION_ABORTED,
  SASL_FAILURE_CONDITION_ACCOUNT_DISABLED,
  SASL_FAILURE_CONDITION_CREDENTIALS_EXPIRED,
  SASL_FAILURE_CONDITION_ENCRYPTION_REQUIRED,
  SASL_FAILURE_CONDITION_INCORRECT_ENCODING,
  SASL_FAILURE_CONDITION_INVALID_AUTHZID,
  SASL_FAILURE_CONDITION_INVALID_MECHANISM,
  SASL_FAILURE_CONDITION_MALFORMED_REQUEST,
  SASL_FAILURE_CONDITION_MECHANISM_TOO_WEAK,
  SASL_FAILURE_CONDITION_NOT_AUTHORIZED,
  SASL_FAILURE_CONDITION_TEMPORARY_AUTH_FAILURE,
  SASL_FAILURE_CONDITION_TRANSITION_NEEDED,
};

enum sasl_failure_condition_t enum_sasl_failure_condition_from_string (const
								       char
								       *value);
const char *enum_sasl_failure_condition_to_string (enum
						   sasl_failure_condition_t);

struct sasl_mechanisms_t
{
  vlist_t *fMechanism;
};


struct sasl_auth_t
{
  const char *fMechanism;
  unsigned char *fData;
  int fData_len;
};


struct sasl_success_t
{
  unsigned char *fData;
  int fData_len;
};


struct sasl_challenge_t
{
  unsigned char *fData;
  int fData_len;
};


struct sasl_response_t
{
  unsigned char *fData;
  int fData_len;
};


struct sasl_failure_t
{
  langstring_t *fText;
  enum sasl_failure_condition_t fCondition;
};


struct sasl_mechanisms_t *sasl_mechanisms_decode (xmlreader_t * reader);
int sasl_mechanisms_encode (xmlwriter_t * writer,
			    struct sasl_mechanisms_t *data);
struct sasl_auth_t *sasl_auth_decode (xmlreader_t * reader);
int sasl_auth_encode (xmlwriter_t * writer, struct sasl_auth_t *data);
struct sasl_success_t *sasl_success_decode (xmlreader_t * reader);
int sasl_success_encode (xmlwriter_t * writer, struct sasl_success_t *data);
struct sasl_challenge_t *sasl_challenge_decode (xmlreader_t * reader);
int sasl_challenge_encode (xmlwriter_t * writer,
			   struct sasl_challenge_t *data);
struct sasl_response_t *sasl_response_decode (xmlreader_t * reader);
int sasl_response_encode (xmlwriter_t * writer, struct sasl_response_t *data);
struct sasl_failure_t *sasl_failure_decode (xmlreader_t * reader);
int sasl_failure_encode (xmlwriter_t * writer, struct sasl_failure_t *data);
#endif
