#include "xep_time_data.h"
#include "helpers.h"

const char *ns_time = "urn:xmpp:time";

struct time_time_t *
time_time_decode (xmlreader_t * reader)
{
  struct time_time_t *elm = NULL;
  elm = malloc (sizeof (struct time_time_t));
  if (elm == NULL)
    fatal ("time_time_t: malloc failed");
  memset (elm, 0, sizeof (struct time_time_t));
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
	  if ((strcmp (name, "tz") == 0)
	      && (strcmp (namespace, ns_time) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fTz = (const char *) value;
	    }			// for end part 1
	  else if ((strcmp (name, "utc") == 0)
		   && (strcmp (namespace, ns_time) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fUtc = (const char *) value;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
time_time_encode (xmlwriter_t * writer, struct time_time_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_time, "time");
  if (err != 0)
    return err;
  if (elm->fTz != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_time, "tz", elm->fTz);
      if (err != 0)
	return err;
    }
  if (elm->fUtc != NULL)
    {
      err = xmlwriter_simple_element (writer, ns_time, "utc", elm->fUtc);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}
