#include "stream_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_stream = "http://etherx.jabber.org/streams";

struct stream_start_t *
stream_start_decode (xmlreader_t * reader)
{
  struct stream_start_t *elm = NULL;
  elm = malloc (sizeof (struct stream_start_t));
  if (elm == NULL)
    fatal ("stream_start_t: malloc failed");
  memset (elm, 0, sizeof (struct stream_start_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "to");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fTo = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "from");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fFrom = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "id");
  if (avalue != NULL)
    {
      elm->fId = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "version");
  if (avalue != NULL)
    {
      elm->fVersion = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "lang");
  if (avalue != NULL)
    {
      elm->fLang = (char *) avalue;
    }
  return elm;
}

int
stream_start_encode (xmlwriter_t * writer, struct stream_start_t *elm)
{
  int err = 0;
  err = xmlwriter_set_prefix (writer, "stream", ns_stream);
  if (err != 0)
    return err;
  err = xmlwriter_start_element (writer, ns_stream, "stream");
  if (err != 0)
    return err;
  if (elm->fTo != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "to", jid_to_string (elm->fTo));
      if (err != 0)
	return err;
    }
  if (elm->fFrom != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "from",
			     jid_to_string (elm->fFrom));
      if (err != 0)
	return err;
    }
  if (elm->fId != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "id", elm->fId);
      if (err != 0)
	return err;
    }
  if (elm->fVersion != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "version", elm->fVersion);
      if (err != 0)
	return err;
    }
  if (elm->fLang != NULL)
    {
      err = xmlwriter_attribute (writer, ns_xml, "lang", elm->fLang);
      if (err != 0)
	return err;
    }
  return 0;
}

void
stream_start_free (struct stream_start_t *data)
{
  if (data == NULL)
    return;
  if (data->fTo != NULL)
    {
      jid_free (data->fTo);
    }
  if (data->fFrom != NULL)
    {
      jid_free (data->fFrom);
    }
  if (data->fId != NULL)
    {
      free (data->fId);
    }
  if (data->fVersion != NULL)
    {
      free (data->fVersion);
    }
  if (data->fLang != NULL)
    {
      free (data->fLang);
    }
  free (data);
}

array_t *
stream_features_decode (xmlreader_t * reader)
{
  array_t *elm = array_new (sizeof (extension_t), 0);
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
	  extension_t ext;
	  int err = xstream_extension_decode (reader, &ext);
	  if (reader->err != 0)
	    return NULL;
	  if (err == ERR_EXTENSION_NOT_FOUND)
	    {
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	  else
	    {
	      array_append (elm, &ext);
	    }
	}
    }
  return elm;
}

int
stream_features_encode (xmlwriter_t * writer, array_t * elm)
{
  int err = 0;
  err = xmlwriter_set_prefix (writer, "stream", ns_stream);
  if (err != 0)
    return err;
  err = xmlwriter_start_element (writer, ns_stream, "features");
  if (err != 0)
    return err;
  int len = array_length (elm);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      extension_t *ext = array_get (elm, i);
      err = xstream_extension_encode (writer, ext->data, ext->type);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
stream_features_free (array_t * data)
{
  if (data == NULL)
    return;
  int len = array_length (data);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      extension_t *ext = array_get (data, i);
      xstream_extension_free (ext);
    }
  array_free (data);
}

struct stream_error_t *
stream_error_decode (xmlreader_t * reader)
{
  struct stream_error_t *elm = NULL;
  elm = malloc (sizeof (struct stream_error_t));
  if (elm == NULL)
    fatal ("stream_error_t: malloc failed");
  memset (elm, 0, sizeof (struct stream_error_t));
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
	      && (strcmp (namespace, ns_stream) == 0))
	    {
	      langstring_decode (reader, elm->fText);
	    }
	  else if (strcmp (namespace, ns_stream) != 0)
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fCondition.fExtra = (char *) value;
	    }
	}
    }
  return elm;
}

int
stream_error_encode (xmlwriter_t * writer, struct stream_error_t *elm)
{
  int err = 0;
  err = xmlwriter_set_prefix (writer, "stream", ns_stream);
  if (err != 0)
    return err;
  err = xmlwriter_start_element (writer, ns_stream, "error");
  if (err != 0)
    return err;
  if (elm->fText != NULL)
    {
      err = langstring_encode (writer, ns_stream, "text", elm->fText);
      if (err != 0)
	return err;
    }
  const char *name =
    enum_stream_error_condition_name_to_string (elm->fCondition.fName);
  err = xmlwriter_start_element (writer, ns_stream, name);
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

void
stream_error_free (struct stream_error_t *data)
{
  if (data == NULL)
    return;
  if (data->fText != NULL)
    {
      langstring_free (data->fText);
    }
  if (data->fCondition.fExtra != NULL)
    {
      free (data->fCondition.fExtra);
    }
  free (data);
}

enum stream_error_condition_name_t
enum_stream_error_condition_name_from_string (const char *value)
{
  if (strcmp (value, "bad-format") == 0)
    return STREAM_ERROR_CONDITION_NAME_BAD_FORMAT;
  else if (strcmp (value, "bad-namespace-prefix") == 0)
    return STREAM_ERROR_CONDITION_NAME_BAD_NAMESPACE_PREFIX;
  else if (strcmp (value, "conflict") == 0)
    return STREAM_ERROR_CONDITION_NAME_CONFLICT;
  else if (strcmp (value, "connection-timeout") == 0)
    return STREAM_ERROR_CONDITION_NAME_CONNECTION_TIMEOUT;
  else if (strcmp (value, "host-gone") == 0)
    return STREAM_ERROR_CONDITION_NAME_HOST_GONE;
  else if (strcmp (value, "host-unknown") == 0)
    return STREAM_ERROR_CONDITION_NAME_HOST_UNKNOWN;
  else if (strcmp (value, "improper-addressing") == 0)
    return STREAM_ERROR_CONDITION_NAME_IMPROPER_ADDRESSING;
  else if (strcmp (value, "internal-server-error") == 0)
    return STREAM_ERROR_CONDITION_NAME_INTERNAL_SERVER_ERROR;
  else if (strcmp (value, "invalid-from") == 0)
    return STREAM_ERROR_CONDITION_NAME_INVALID_FROM;
  else if (strcmp (value, "invalid-namespace") == 0)
    return STREAM_ERROR_CONDITION_NAME_INVALID_NAMESPACE;
  else if (strcmp (value, "invalid-xml") == 0)
    return STREAM_ERROR_CONDITION_NAME_INVALID_XML;
  else if (strcmp (value, "not-authorized") == 0)
    return STREAM_ERROR_CONDITION_NAME_NOT_AUTHORIZED;
  else if (strcmp (value, "not-well-formed") == 0)
    return STREAM_ERROR_CONDITION_NAME_NOT_WELL_FORMED;
  else if (strcmp (value, "policy-violation") == 0)
    return STREAM_ERROR_CONDITION_NAME_POLICY_VIOLATION;
  else if (strcmp (value, "remote-connection-failed") == 0)
    return STREAM_ERROR_CONDITION_NAME_REMOTE_CONNECTION_FAILED;
  else if (strcmp (value, "reset") == 0)
    return STREAM_ERROR_CONDITION_NAME_RESET;
  else if (strcmp (value, "resource-constraint") == 0)
    return STREAM_ERROR_CONDITION_NAME_RESOURCE_CONSTRAINT;
  else if (strcmp (value, "restricted-xml") == 0)
    return STREAM_ERROR_CONDITION_NAME_RESTRICTED_XML;
  else if (strcmp (value, "see-other-host") == 0)
    return STREAM_ERROR_CONDITION_NAME_SEE_OTHER_HOST;
  else if (strcmp (value, "system-shutdown") == 0)
    return STREAM_ERROR_CONDITION_NAME_SYSTEM_SHUTDOWN;
  else if (strcmp (value, "undefined-condition") == 0)
    return STREAM_ERROR_CONDITION_NAME_UNDEFINED_CONDITION;
  else if (strcmp (value, "unsupported-encoding") == 0)
    return STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_ENCODING;
  else if (strcmp (value, "unsupported-feature") == 0)
    return STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_FEATURE;
  else if (strcmp (value, "unsupported-stanza-type") == 0)
    return STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_STANZA_TYPE;
  else if (strcmp (value, "unsupported-version") == 0)
    return STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_VERSION;
  return 0;
}

const char *
enum_stream_error_condition_name_to_string (enum stream_error_condition_name_t
					    value)
{
  switch (value)
    {
    case STREAM_ERROR_CONDITION_NAME_BAD_FORMAT:
      return "bad-format";
    case STREAM_ERROR_CONDITION_NAME_BAD_NAMESPACE_PREFIX:
      return "bad-namespace-prefix";
    case STREAM_ERROR_CONDITION_NAME_CONFLICT:
      return "conflict";
    case STREAM_ERROR_CONDITION_NAME_CONNECTION_TIMEOUT:
      return "connection-timeout";
    case STREAM_ERROR_CONDITION_NAME_HOST_GONE:
      return "host-gone";
    case STREAM_ERROR_CONDITION_NAME_HOST_UNKNOWN:
      return "host-unknown";
    case STREAM_ERROR_CONDITION_NAME_IMPROPER_ADDRESSING:
      return "improper-addressing";
    case STREAM_ERROR_CONDITION_NAME_INTERNAL_SERVER_ERROR:
      return "internal-server-error";
    case STREAM_ERROR_CONDITION_NAME_INVALID_FROM:
      return "invalid-from";
    case STREAM_ERROR_CONDITION_NAME_INVALID_NAMESPACE:
      return "invalid-namespace";
    case STREAM_ERROR_CONDITION_NAME_INVALID_XML:
      return "invalid-xml";
    case STREAM_ERROR_CONDITION_NAME_NOT_AUTHORIZED:
      return "not-authorized";
    case STREAM_ERROR_CONDITION_NAME_NOT_WELL_FORMED:
      return "not-well-formed";
    case STREAM_ERROR_CONDITION_NAME_POLICY_VIOLATION:
      return "policy-violation";
    case STREAM_ERROR_CONDITION_NAME_REMOTE_CONNECTION_FAILED:
      return "remote-connection-failed";
    case STREAM_ERROR_CONDITION_NAME_RESET:
      return "reset";
    case STREAM_ERROR_CONDITION_NAME_RESOURCE_CONSTRAINT:
      return "resource-constraint";
    case STREAM_ERROR_CONDITION_NAME_RESTRICTED_XML:
      return "restricted-xml";
    case STREAM_ERROR_CONDITION_NAME_SEE_OTHER_HOST:
      return "see-other-host";
    case STREAM_ERROR_CONDITION_NAME_SYSTEM_SHUTDOWN:
      return "system-shutdown";
    case STREAM_ERROR_CONDITION_NAME_UNDEFINED_CONDITION:
      return "undefined-condition";
    case STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_ENCODING:
      return "unsupported-encoding";
    case STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_FEATURE:
      return "unsupported-feature";
    case STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_STANZA_TYPE:
      return "unsupported-stanza-type";
    case STREAM_ERROR_CONDITION_NAME_UNSUPPORTED_VERSION:
      return "unsupported-version";
    }
  return NULL;
}
