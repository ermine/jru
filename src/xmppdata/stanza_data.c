#include "stanza_data.h"
#include "helpers.h"

const char *ns_stanza = "urn:ietf:params:xml:ns:xmpp-stanzas";

struct stanza_error_t *
stanza_error_decode (xmlreader_t * reader)
{
  struct stanza_error_t *elm = NULL;
  elm = malloc (sizeof (struct stanza_error_t));
  if (elm == NULL)
    fatal ("stanza_error_t: malloc failed");
  memset (elm, 0, sizeof (struct stanza_error_t));
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
	      && (strcmp (namespace, ns_stanza) == 0))
	    {
	      langstring_decode (reader, elm->fText);
	    }			// for end part 1
	  else if (strcmp (namespace, ns_stanza) != 0)
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fCondition.fExtra = (const char *) value;
	    }			// any end
	}			// case end
    }				// while end
  return elm;
}

int
stanza_error_encode (xmlwriter_t * writer, struct stanza_error_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_stanza, "error");
  if (err != 0)
    return err;
  if (elm->fText != NULL)
    {
      err = langstring_encode (writer, ns_stanza, "text", elm->fText);
      if (err != 0)
	return err;
    }
  const char *name =
    enum_stanza_error_condition_name_to_string (elm->fCondition.fName);
  err = xmlwriter_start_element (writer, ns_stanza, name);
  if (err != 0)
    return err;
  if (elm->fCondition.fExtra != NULL)
    {
      err = xmlwriter_text (writer, elm->fCondition.fExtra);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

enum stanza_error_condition_name_t
enum_stanza_error_condition_name_from_string (const char *value)
{
  if (strcmp (value, "bad-request") == 0)
    return STANZA_ERROR_CONDITION_NAME_BAD_REQUEST;
  else if (strcmp (value, "conflict") == 0)
    return STANZA_ERROR_CONDITION_NAME_CONFLICT;
  else if (strcmp (value, "feature-not-implemented") == 0)
    return STANZA_ERROR_CONDITION_NAME_FEATURE_NOT_IMPLEMENTED;
  else if (strcmp (value, "forbidden") == 0)
    return STANZA_ERROR_CONDITION_NAME_FORBIDDEN;
  else if (strcmp (value, "gone") == 0)
    return STANZA_ERROR_CONDITION_NAME_GONE;
  else if (strcmp (value, "internal-server-error") == 0)
    return STANZA_ERROR_CONDITION_NAME_INTERNAL_SERVER_ERROR;
  else if (strcmp (value, "item-not-found") == 0)
    return STANZA_ERROR_CONDITION_NAME_ITEM_NOT_FOUND;
  else if (strcmp (value, "jid-malformed") == 0)
    return STANZA_ERROR_CONDITION_NAME_JID_MALFORMED;
  else if (strcmp (value, "not-acceptable") == 0)
    return STANZA_ERROR_CONDITION_NAME_NOT_ACCEPTABLE;
  else if (strcmp (value, "not-allowed") == 0)
    return STANZA_ERROR_CONDITION_NAME_NOT_ALLOWED;
  else if (strcmp (value, "not-authorized") == 0)
    return STANZA_ERROR_CONDITION_NAME_NOT_AUTHORIZED;
  else if (strcmp (value, "payment-required") == 0)
    return STANZA_ERROR_CONDITION_NAME_PAYMENT_REQUIRED;
  else if (strcmp (value, "policy-violation") == 0)
    return STANZA_ERROR_CONDITION_NAME_POLICY_VIOLATION;
  else if (strcmp (value, "recipient-unavailable") == 0)
    return STANZA_ERROR_CONDITION_NAME_RECIPIENT_UNAVAILABLE;
  else if (strcmp (value, "redirect") == 0)
    return STANZA_ERROR_CONDITION_NAME_REDIRECT;
  else if (strcmp (value, "registration-required") == 0)
    return STANZA_ERROR_CONDITION_NAME_REGISTRATION_REQUIRED;
  else if (strcmp (value, "remote-server-not-found") == 0)
    return STANZA_ERROR_CONDITION_NAME_REMOTE_SERVER_NOT_FOUND;
  else if (strcmp (value, "remote-server-timeout") == 0)
    return STANZA_ERROR_CONDITION_NAME_REMOTE_SERVER_TIMEOUT;
  else if (strcmp (value, "resource-constraint") == 0)
    return STANZA_ERROR_CONDITION_NAME_RESOURCE_CONSTRAINT;
  else if (strcmp (value, "service-unavailable") == 0)
    return STANZA_ERROR_CONDITION_NAME_SERVICE_UNAVAILABLE;
  else if (strcmp (value, "subscription-required") == 0)
    return STANZA_ERROR_CONDITION_NAME_SUBSCRIPTION_REQUIRED;
  else if (strcmp (value, "undefined-condition") == 0)
    return STANZA_ERROR_CONDITION_NAME_UNDEFINED_CONDITION;
  else if (strcmp (value, "unexpected-request") == 0)
    return STANZA_ERROR_CONDITION_NAME_UNEXPECTED_REQUEST;
  return 0;
}

const char *
enum_stanza_error_condition_name_to_string (enum stanza_error_condition_name_t
					    value)
{
  switch (value)
    {
    case STANZA_ERROR_CONDITION_NAME_BAD_REQUEST:
      return "bad-request";
    case STANZA_ERROR_CONDITION_NAME_CONFLICT:
      return "conflict";
    case STANZA_ERROR_CONDITION_NAME_FEATURE_NOT_IMPLEMENTED:
      return "feature-not-implemented";
    case STANZA_ERROR_CONDITION_NAME_FORBIDDEN:
      return "forbidden";
    case STANZA_ERROR_CONDITION_NAME_GONE:
      return "gone";
    case STANZA_ERROR_CONDITION_NAME_INTERNAL_SERVER_ERROR:
      return "internal-server-error";
    case STANZA_ERROR_CONDITION_NAME_ITEM_NOT_FOUND:
      return "item-not-found";
    case STANZA_ERROR_CONDITION_NAME_JID_MALFORMED:
      return "jid-malformed";
    case STANZA_ERROR_CONDITION_NAME_NOT_ACCEPTABLE:
      return "not-acceptable";
    case STANZA_ERROR_CONDITION_NAME_NOT_ALLOWED:
      return "not-allowed";
    case STANZA_ERROR_CONDITION_NAME_NOT_AUTHORIZED:
      return "not-authorized";
    case STANZA_ERROR_CONDITION_NAME_PAYMENT_REQUIRED:
      return "payment-required";
    case STANZA_ERROR_CONDITION_NAME_POLICY_VIOLATION:
      return "policy-violation";
    case STANZA_ERROR_CONDITION_NAME_RECIPIENT_UNAVAILABLE:
      return "recipient-unavailable";
    case STANZA_ERROR_CONDITION_NAME_REDIRECT:
      return "redirect";
    case STANZA_ERROR_CONDITION_NAME_REGISTRATION_REQUIRED:
      return "registration-required";
    case STANZA_ERROR_CONDITION_NAME_REMOTE_SERVER_NOT_FOUND:
      return "remote-server-not-found";
    case STANZA_ERROR_CONDITION_NAME_REMOTE_SERVER_TIMEOUT:
      return "remote-server-timeout";
    case STANZA_ERROR_CONDITION_NAME_RESOURCE_CONSTRAINT:
      return "resource-constraint";
    case STANZA_ERROR_CONDITION_NAME_SERVICE_UNAVAILABLE:
      return "service-unavailable";
    case STANZA_ERROR_CONDITION_NAME_SUBSCRIPTION_REQUIRED:
      return "subscription-required";
    case STANZA_ERROR_CONDITION_NAME_UNDEFINED_CONDITION:
      return "undefined-condition";
    case STANZA_ERROR_CONDITION_NAME_UNEXPECTED_REQUEST:
      return "unexpected-request";
    }
  return NULL;
}
