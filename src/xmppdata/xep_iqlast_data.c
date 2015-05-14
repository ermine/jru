#include "xep_iqlast_data.h"
#include "helpers.h"

const char *ns_iqlast = "jabber:iq:last";

struct iqlast_last_t *
iqlast_last_decode (xmlreader_t * reader)
{
  struct iqlast_last_t *elm = NULL;
  elm = malloc (sizeof (struct iqlast_last_t));
  if (elm == NULL)
    fatal ("iqlast_last_t: malloc failed");
  memset (elm, 0, sizeof (struct iqlast_last_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "seconds");
  if (avalue != NULL)
    {
      elm->fSeconds = strconv_parse_uint (avalue);
    }
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm->fExtra = (const char *) value;
  return elm;
}

int
iqlast_last_encode (xmlwriter_t * writer, struct iqlast_last_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_iqlast, "query");
  if (err != 0)
    return err;
  if (elm->fSeconds != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "seconds",
			     strconv_format_uint (elm->fSeconds));
      if (err != 0)
	return err;
    }
  if (elm->fExtra != NULL)
    {
      err = xmlwriter_text (writer, elm->fExtra);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}
