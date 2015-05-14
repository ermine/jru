#include "xep_disco_data.h"
#include "helpers.h"

const char *ns_disco_info = "http://jabber.org/protocol/disco#info";
const char *ns_disco_items = "http://jabber.org/protocol/disco#items";

struct disco_info_info_t *
disco_info_info_decode (xmlreader_t * reader)
{
  struct disco_info_info_t *elm = NULL;
  elm = malloc (sizeof (struct disco_info_info_t));
  if (elm == NULL)
    fatal ("disco_info_info_t: malloc failed");
  memset (elm, 0, sizeof (struct disco_info_info_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "node");
  if (avalue != NULL)
    {
      elm->fNode = avalue;
    }
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
	  if ((strcmp (namespace, ns_disco_info) == 0)
	      && (strcmp (name, "identity") == 0))
	    {
	      struct disco_info_identity_t *newel =
		disco_info_identity_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      vlist_append ((vlist_t **) & elm->fIdentities, (void *) newel,
			    EXTENSION_TYPE_DISCO_INFO_IDENTITY);
	    }
	  else if ((strcmp (namespace, ns_disco_info) == 0)
		   && (strcmp (name, "feature") == 0))
	    {
	      struct disco_info_feature_t *newel =
		disco_info_feature_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      vlist_append ((vlist_t **) & elm->fFeatures, (void *) newel,
			    EXTENSION_TYPE_DISCO_INFO_FEATURE);
	    }
	}			// case end
    }				// while end
  return elm;
}

int
disco_info_info_encode (xmlwriter_t * writer, struct disco_info_info_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_disco_info, "query");
  if (err != 0)
    return err;
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  {
    vlist_t *curr = (vlist_t *) elm->fIdentities;
    while (curr != NULL)
      {
	err = disco_info_identity_encode (writer, curr->data);
	if (err != 0)
	  return err;
	curr = curr->next;
      }
  }
  {
    vlist_t *curr = (vlist_t *) elm->fFeatures;
    while (curr != NULL)
      {
	err = disco_info_feature_encode (writer, curr->data);
	if (err != 0)
	  return err;
	curr = curr->next;
      }
  }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct disco_info_identity_t *
disco_info_identity_decode (xmlreader_t * reader)
{
  struct disco_info_identity_t *elm = NULL;
  elm = malloc (sizeof (struct disco_info_identity_t));
  if (elm == NULL)
    fatal ("disco_info_identity_t: malloc failed");
  memset (elm, 0, sizeof (struct disco_info_identity_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "category");
  if (avalue != NULL)
    {
      elm->fCategory = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "type");
  if (avalue != NULL)
    {
      elm->fType = avalue;
    }
  if (xmlreader_skip_element (reader) != -1)
    return NULL;
  return elm;
}

int
disco_info_identity_encode (xmlwriter_t * writer,
			    struct disco_info_identity_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_disco_info, "identity");
  if (err != 0)
    return err;
  if (elm->fCategory != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "category", elm->fCategory);
      if (err != 0)
	return err;
    }
  if (elm->fType != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "type", elm->fType);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct disco_info_feature_t *
disco_info_feature_decode (xmlreader_t * reader)
{
  struct disco_info_feature_t *elm = NULL;
  elm = malloc (sizeof (struct disco_info_feature_t));
  if (elm == NULL)
    fatal ("disco_info_feature_t: malloc failed");
  memset (elm, 0, sizeof (struct disco_info_feature_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "var");
  if (avalue != NULL)
    {
      elm->fVar = avalue;
    }
  if (xmlreader_skip_element (reader) != -1)
    return NULL;
  return elm;
}

int
disco_info_feature_encode (xmlwriter_t * writer,
			   struct disco_info_feature_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_disco_info, "feature");
  if (err != 0)
    return err;
  if (elm->fVar != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "var", elm->fVar);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}
