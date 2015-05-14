#include "xep_caps_data.h"
#include "helpers.h"

const char *ns_caps = "http://jabber.org/protocol/caps";

struct caps_caps_t *
caps_caps_decode (xmlreader_t * reader)
{
  struct caps_caps_t *elm = NULL;
  elm = malloc (sizeof (struct caps_caps_t));
  if (elm == NULL)
    fatal ("caps_caps_t: malloc failed");
  memset (elm, 0, sizeof (struct caps_caps_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "ext");
  if (avalue != NULL)
    {
      elm->fExt = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "hash");
  if (avalue != NULL)
    {
      elm->fHash = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "node");
  if (avalue != NULL)
    {
      elm->fNode = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "ver");
  if (avalue != NULL)
    {
      elm->fVer = avalue;
    }
  if (xmlreader_skip_element (reader) != -1)
    return NULL;
  return elm;
}

int
caps_caps_encode (xmlwriter_t * writer, struct caps_caps_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_caps, "c");
  if (err != 0)
    return err;
  if (elm->fExt != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "ext", elm->fExt);
      if (err != 0)
	return err;
    }
  if (elm->fHash != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "hash", elm->fHash);
      if (err != 0)
	return err;
    }
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  if (elm->fVer != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "ver", elm->fVer);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}
