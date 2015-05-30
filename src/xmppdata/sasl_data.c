#include "sasl_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_sasl = "urn:ietf:params:xml:ns:xmpp-sasl";

struct sasl_mechanisms_t *
sasl_mechanisms_decode (xmlreader_t * reader)
{
  struct sasl_mechanisms_t *elm = NULL;
  elm = malloc (sizeof (struct sasl_mechanisms_t));
  if (elm == NULL)
    fatal ("sasl_mechanisms_t: malloc failed");
  memset (elm, 0, sizeof (struct sasl_mechanisms_t));
  int type = 0;
  while (1)
    {
      type = xmlreader_next (reader);
      if (type == XML_END_ELEMENT)
	break;
      if (type == XML_ERROR)
	return NULL;
      if (type == XML_START_ELEMENT)
	{
	  const char *namespace = xmlreader_get_namespace (reader);
	  const char *name = xmlreader_get_name (reader);
	  if ((strcmp (name, "mechanism") == 0)
	      && (strcmp (namespace, ns_sasl) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      if (elm->fMechanism == NULL)
		elm->fMechanism = array_new (sizeof (char *), 0);
	      array_append (elm->fMechanism, (void *) &value);
	    }
	}
    }
  return elm;
}

int
sasl_mechanisms_encode (xmlwriter_t * writer, struct sasl_mechanisms_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_sasl, "mechanisms");
  if (err != 0)
    return err;
  int len = array_length (elm->fMechanism);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (elm->fMechanism, i);
      err =
	xmlwriter_simple_element (writer, ns_sasl, "mechanism",
				  (char *) value);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
sasl_mechanisms_free (struct sasl_mechanisms_t *data)
{
  if (data == NULL)
    return;
  int len = array_length (data->fMechanism);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (data->fMechanism, i);
      free (*value);
    }
  array_free (data->fMechanism);
  free (data);
}

struct sasl_auth_t *
sasl_auth_decode (xmlreader_t * reader)
{
  struct sasl_auth_t *elm = NULL;
  elm = malloc (sizeof (struct sasl_auth_t));
  if (elm == NULL)
    fatal ("sasl_auth_t: malloc failed");
  memset (elm, 0, sizeof (struct sasl_auth_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "mechanism");
  if (avalue != NULL)
    {
      elm->fMechanism = (char *) avalue;
    }
  if (xmlreader_base64 (reader, &elm->fData, &elm->fData_len) != 0)
    return NULL;
  return elm;
}

int
sasl_auth_encode (xmlwriter_t * writer, struct sasl_auth_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_sasl, "auth");
  if (err != 0)
    return err;
  if (elm->fMechanism != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "mechanism", elm->fMechanism);
      if (err != 0)
	return err;
    }
  if (elm->fData != NULL)
    {
      err = xmlwriter_base64 (writer, elm->fData, elm->fData_len);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
sasl_auth_free (struct sasl_auth_t *data)
{
  if (data == NULL)
    return;
  if (data->fMechanism != NULL)
    {
      free (data->fMechanism);
    }
  if (data->fData != NULL)
    {
      free (data->fData);
    }
  free (data);
}

struct sasl_success_t *
sasl_success_decode (xmlreader_t * reader)
{
  struct sasl_success_t *elm = NULL;
  elm = malloc (sizeof (struct sasl_success_t));
  if (elm == NULL)
    fatal ("sasl_success_t: malloc failed");
  memset (elm, 0, sizeof (struct sasl_success_t));
  if (xmlreader_base64 (reader, &elm->fData, &elm->fData_len) != 0)
    return NULL;
  return elm;
}

int
sasl_success_encode (xmlwriter_t * writer, struct sasl_success_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_sasl, "success");
  if (err != 0)
    return err;
  if (elm->fData != NULL)
    {
      err = xmlwriter_base64 (writer, elm->fData, elm->fData_len);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
sasl_success_free (struct sasl_success_t *data)
{
  if (data == NULL)
    return;
  if (data->fData != NULL)
    {
      free (data->fData);
    }
  free (data);
}

struct sasl_challenge_t *
sasl_challenge_decode (xmlreader_t * reader)
{
  struct sasl_challenge_t *elm = NULL;
  elm = malloc (sizeof (struct sasl_challenge_t));
  if (elm == NULL)
    fatal ("sasl_challenge_t: malloc failed");
  memset (elm, 0, sizeof (struct sasl_challenge_t));
  if (xmlreader_base64 (reader, &elm->fData, &elm->fData_len) != 0)
    return NULL;
  return elm;
}

int
sasl_challenge_encode (xmlwriter_t * writer, struct sasl_challenge_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_sasl, "challenge");
  if (err != 0)
    return err;
  if (elm->fData != NULL)
    {
      err = xmlwriter_base64 (writer, elm->fData, elm->fData_len);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
sasl_challenge_free (struct sasl_challenge_t *data)
{
  if (data == NULL)
    return;
  if (data->fData != NULL)
    {
      free (data->fData);
    }
  free (data);
}

struct sasl_response_t *
sasl_response_decode (xmlreader_t * reader)
{
  struct sasl_response_t *elm = NULL;
  elm = malloc (sizeof (struct sasl_response_t));
  if (elm == NULL)
    fatal ("sasl_response_t: malloc failed");
  memset (elm, 0, sizeof (struct sasl_response_t));
  if (xmlreader_base64 (reader, &elm->fData, &elm->fData_len) != 0)
    return NULL;
  return elm;
}

int
sasl_response_encode (xmlwriter_t * writer, struct sasl_response_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_sasl, "response");
  if (err != 0)
    return err;
  if (elm->fData != NULL)
    {
      err = xmlwriter_base64 (writer, elm->fData, elm->fData_len);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
sasl_response_free (struct sasl_response_t *data)
{
  if (data == NULL)
    return;
  if (data->fData != NULL)
    {
      free (data->fData);
    }
  free (data);
}

struct sasl_failure_t *
sasl_failure_decode (xmlreader_t * reader)
{
  struct sasl_failure_t *elm = NULL;
  elm = malloc (sizeof (struct sasl_failure_t));
  if (elm == NULL)
    fatal ("sasl_failure_t: malloc failed");
  memset (elm, 0, sizeof (struct sasl_failure_t));
  int type = 0;
  while (1)
    {
      type = xmlreader_next (reader);
      if (type == XML_END_ELEMENT)
	break;
      if (type == XML_ERROR)
	return NULL;
      if (type == XML_START_ELEMENT)
	{
	  const char *namespace = xmlreader_get_namespace (reader);
	  const char *name = xmlreader_get_name (reader);
	  if ((strcmp (name, "text") == 0)
	      && (strcmp (namespace, ns_sasl) == 0))
	    {
	      langstring_decode (reader, elm->fText);
	    }
	  else if (strcmp (namespace, ns_sasl) != 0)
	    {
	      elm->fCondition =
		enum_sasl_failure_condition_from_string (name);
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	}
    }
  return elm;
}

int
sasl_failure_encode (xmlwriter_t * writer, struct sasl_failure_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_sasl, "failure");
  if (err != 0)
    return err;
  if (elm->fText != NULL)
    {
      err = langstring_encode (writer, ns_sasl, "text", elm->fText);
      if (err != 0)
	return err;
    }
  if (elm->fCondition != 0)
    {
      const char *name =
	enum_sasl_failure_condition_to_string (elm->fCondition);
      err = xmlwriter_simple_element (writer, ns_sasl, name, NULL);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
sasl_failure_free (struct sasl_failure_t *data)
{
  if (data == NULL)
    return;
  if (data->fText != NULL)
    {
      langstring_free (data->fText);
    }
  if (data->fCondition != 0)
    {
    }
  free (data);
}

enum sasl_failure_condition_t
enum_sasl_failure_condition_from_string (const char *value)
{
  if (strcmp (value, "aborted") == 0)
    return SASL_FAILURE_CONDITION_ABORTED;
  else if (strcmp (value, "account-disabled") == 0)
    return SASL_FAILURE_CONDITION_ACCOUNT_DISABLED;
  else if (strcmp (value, "credentials-expired") == 0)
    return SASL_FAILURE_CONDITION_CREDENTIALS_EXPIRED;
  else if (strcmp (value, "encryption-required") == 0)
    return SASL_FAILURE_CONDITION_ENCRYPTION_REQUIRED;
  else if (strcmp (value, "incorrect-encoding") == 0)
    return SASL_FAILURE_CONDITION_INCORRECT_ENCODING;
  else if (strcmp (value, "invalid-authzid") == 0)
    return SASL_FAILURE_CONDITION_INVALID_AUTHZID;
  else if (strcmp (value, "invalid-mechanism") == 0)
    return SASL_FAILURE_CONDITION_INVALID_MECHANISM;
  else if (strcmp (value, "malformed-request") == 0)
    return SASL_FAILURE_CONDITION_MALFORMED_REQUEST;
  else if (strcmp (value, "mechanism-too-weak") == 0)
    return SASL_FAILURE_CONDITION_MECHANISM_TOO_WEAK;
  else if (strcmp (value, "not-authorized") == 0)
    return SASL_FAILURE_CONDITION_NOT_AUTHORIZED;
  else if (strcmp (value, "temporary-auth-failure") == 0)
    return SASL_FAILURE_CONDITION_TEMPORARY_AUTH_FAILURE;
  else if (strcmp (value, "transition-needed") == 0)
    return SASL_FAILURE_CONDITION_TRANSITION_NEEDED;
  return 0;
}

const char *
enum_sasl_failure_condition_to_string (enum sasl_failure_condition_t value)
{
  switch (value)
    {
    case SASL_FAILURE_CONDITION_ABORTED:
      return "aborted";
    case SASL_FAILURE_CONDITION_ACCOUNT_DISABLED:
      return "account-disabled";
    case SASL_FAILURE_CONDITION_CREDENTIALS_EXPIRED:
      return "credentials-expired";
    case SASL_FAILURE_CONDITION_ENCRYPTION_REQUIRED:
      return "encryption-required";
    case SASL_FAILURE_CONDITION_INCORRECT_ENCODING:
      return "incorrect-encoding";
    case SASL_FAILURE_CONDITION_INVALID_AUTHZID:
      return "invalid-authzid";
    case SASL_FAILURE_CONDITION_INVALID_MECHANISM:
      return "invalid-mechanism";
    case SASL_FAILURE_CONDITION_MALFORMED_REQUEST:
      return "malformed-request";
    case SASL_FAILURE_CONDITION_MECHANISM_TOO_WEAK:
      return "mechanism-too-weak";
    case SASL_FAILURE_CONDITION_NOT_AUTHORIZED:
      return "not-authorized";
    case SASL_FAILURE_CONDITION_TEMPORARY_AUTH_FAILURE:
      return "temporary-auth-failure";
    case SASL_FAILURE_CONDITION_TRANSITION_NEEDED:
      return "transition-needed";
    }
  return NULL;
}
