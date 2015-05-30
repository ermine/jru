#include "xep_iqversion_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_iqversion = "jabber:iq:version";

struct iqversion_version_t *
iqversion_version_decode (xmlreader_t * reader)
{
  struct iqversion_version_t *elm = NULL;
  elm = malloc (sizeof (struct iqversion_version_t));
  if (elm == NULL)
    fatal ("iqversion_version_t: malloc failed");
  memset (elm, 0, sizeof (struct iqversion_version_t));
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
	  if ((strcmp (name, "name") == 0)
	      && (strcmp (namespace, ns_iqversion) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fName = (char *) value;
	    }
	  else if ((strcmp (name, "version") == 0)
		   && (strcmp (namespace, ns_iqversion) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fVersion = (char *) value;
	    }
	  else if ((strcmp (name, "os") == 0)
		   && (strcmp (namespace, ns_iqversion) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fOs = (char *) value;
	    }
	}
    }
  return elm;
}

int
iqversion_version_encode (xmlwriter_t * writer,
			  struct iqversion_version_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_iqversion, "query");
  if (err != 0)
    return err;
  if (elm->fName != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqversion, "name", elm->fName);
      if (err != 0)
	return err;
    }
  if (elm->fVersion != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqversion, "version",
				  elm->fVersion);
      if (err != 0)
	return err;
    }
  if (elm->fOs != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_iqversion, "os", elm->fOs);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
iqversion_version_free (struct iqversion_version_t *data)
{
  if (data == NULL)
    return;
  if (data->fName != NULL)
    {
      free (data->fName);
    }
  if (data->fVersion != NULL)
    {
      free (data->fVersion);
    }
  if (data->fOs != NULL)
    {
      free (data->fOs);
    }
  free (data);
}
