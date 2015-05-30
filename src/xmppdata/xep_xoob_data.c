#include "xep_xoob_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_xoob = "jabber:x:oob";

struct xoob_x_t *
xoob_x_decode (xmlreader_t * reader)
{
  struct xoob_x_t *elm = NULL;
  elm = malloc (sizeof (struct xoob_x_t));
  if (elm == NULL)
    fatal ("xoob_x_t: malloc failed");
  memset (elm, 0, sizeof (struct xoob_x_t));
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
	  if ((strcmp (name, "url") == 0)
	      && (strcmp (namespace, ns_xoob) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fUrl = (char *) value;
	    }
	  else if ((strcmp (name, "desc") == 0)
		   && (strcmp (namespace, ns_xoob) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fDesc = (char *) value;
	    }
	}
    }
  return elm;
}

int
xoob_x_encode (xmlwriter_t * writer, struct xoob_x_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_xoob, "x");
  if (err != 0)
    return err;
  if (elm->fUrl != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_xoob, "url", elm->fUrl);
      if (err != 0)
	return err;
    }
  if (elm->fDesc != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_xoob, "desc", elm->fDesc);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
xoob_x_free (struct xoob_x_t *data)
{
  if (data == NULL)
    return;
  if (data->fUrl != NULL)
    {
      free (data->fUrl);
    }
  if (data->fDesc != NULL)
    {
      free (data->fDesc);
    }
  free (data);
}
