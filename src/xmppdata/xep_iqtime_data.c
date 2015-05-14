#include "xep_iqtime_data.h"
#include "helpers.h"

const char *ns_iqtime = "jabber:iq:time";

struct iqtime_time_t *
iqtime_time_decode (xmlreader_t * reader)
{
  struct iqtime_time_t *elm = NULL;
  elm = malloc (sizeof (struct iqtime_time_t));
  if (elm == NULL)
    fatal ("iqtime_time_t: malloc failed");
  memset (elm, 0, sizeof (struct iqtime_time_t));
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
	  if ((strcmp (name, "utc") == 0)
	      && (strcmp (namespace, ns_iqtime) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fUtc = (const char *) value;
	    }			// for end part 1
	  else if ((strcmp (name, "tz") == 0)
		   && (strcmp (namespace, ns_iqtime) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fTz = (const char *) value;
	    }			// for end part 1
	  else if ((strcmp (name, "display") == 0)
		   && (strcmp (namespace, ns_iqtime) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fDisplay = (const char *) value;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
iqtime_time_encode (xmlwriter_t * writer, struct iqtime_time_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_iqtime, "query");
  if (err != 0)
    return err;
  if (elm->fUtc != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_iqtime, "utc", elm->fUtc);
      if (err != 0)
	return err;
    }
  if (elm->fTz != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_iqtime, "tz", elm->fTz);
      if (err != 0)
	return err;
    }
  if (elm->fDisplay != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_iqtime, "display",
				  elm->fDisplay);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}
