#include "starttls_data.h"
#include "helpers.h"

const char *ns_starttls = "urn:ietf:params:xml:ns:xmpp-tls";

struct starttls_starttls_t *
starttls_starttls_decode (xmlreader_t * reader)
{
  struct starttls_starttls_t *elm = NULL;
  elm = malloc (sizeof (struct starttls_starttls_t));
  if (elm == NULL)
    fatal ("starttls_starttls_t: malloc failed");
  memset (elm, 0, sizeof (struct starttls_starttls_t));
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
	  if ((strcmp (name, "required") == 0)
	      && (strcmp (namespace, ns_starttls) == 0))
	    {
	      elm->fRequired = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
starttls_starttls_encode (xmlwriter_t * writer,
			  struct starttls_starttls_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_starttls, "starttls");
  if (err != 0)
    return err;
  if (elm->fRequired)
    {
      err = xmlwriter_simple_element (writer, ns_starttls, "required", NULL);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct starttls_proceed_t *
starttls_proceed_decode (xmlreader_t * reader)
{
  struct starttls_proceed_t *elm = NULL;
  elm = malloc (sizeof (struct starttls_proceed_t));
  if (elm == NULL)
    fatal ("starttls_proceed_t: malloc failed");
  memset (elm, 0, sizeof (struct starttls_proceed_t));
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
starttls_proceed_encode (xmlwriter_t * writer, struct starttls_proceed_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_starttls, "proceed");
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct starttls_failure_t *
starttls_failure_decode (xmlreader_t * reader)
{
  struct starttls_failure_t *elm = NULL;
  elm = malloc (sizeof (struct starttls_failure_t));
  if (elm == NULL)
    fatal ("starttls_failure_t: malloc failed");
  memset (elm, 0, sizeof (struct starttls_failure_t));
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
starttls_failure_encode (xmlwriter_t * writer, struct starttls_failure_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_starttls, "failure");
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}
