#include "bind_data.h"
#include "helpers.h"

const char *ns_bind = "urn:ietf:params:xml:ns:xmpp-bind";

struct bind_bind_t *
bind_bind_decode (xmlreader_t * reader)
{
  struct bind_bind_t *elm = NULL;
  elm = malloc (sizeof (struct bind_bind_t));
  if (elm == NULL)
    fatal ("bind_bind_t: malloc failed");
  memset (elm, 0, sizeof (struct bind_bind_t));
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
	  if ((strcmp (name, "resource") == 0)
	      && (strcmp (namespace, ns_bind) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fResource = (const char *) value;
	    }			// for end part 1
	  else if ((strcmp (name, "jid") == 0)
		   && (strcmp (namespace, ns_bind) == 0))
	    {
	      const char *s = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      jid_t *jid = jid_of_string ((const char *) s);
	      elm->fJid = jid;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
bind_bind_encode (xmlwriter_t * writer, struct bind_bind_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_bind, "bind");
  if (err != 0)
    return err;
  if (elm->fResource != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_bind, "resource",
				  elm->fResource);
      if (err != 0)
	return err;
    }
  if (elm->fJid != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_bind, "jid",
				  jid_to_string (elm->fJid));
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}
