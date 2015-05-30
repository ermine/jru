#include "xep_disco_data.h"
#include "helpers.h"
#include "errors.h"

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
      elm->fNode = (char *) avalue;
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
	      if (elm->fIdentities == NULL)
		elm->fIdentities = array_new (sizeof (extension_t), 0);
	      array_append (elm->fIdentities, newel);
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
	      if (elm->fFeatures == NULL)
		elm->fFeatures = array_new (sizeof (extension_t), 0);
	      array_append (elm->fFeatures, newel);
	    }
	}
    }
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
    int len = array_length (elm->fIdentities);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fIdentities, i);
	err = disco_info_identity_encode (writer, ext->data);
	if (err != 0)
	  return err;
      }
  }
  {
    int len = array_length (elm->fFeatures);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fFeatures, i);
	err = disco_info_feature_encode (writer, ext->data);
	if (err != 0)
	  return err;
      }
  }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
disco_info_info_free (struct disco_info_info_t *data)
{
  if (data == NULL)
    return;
  if (data->fNode != NULL)
    {
      free (data->fNode);
    }
  {
    int len = array_length (data->fIdentities);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	disco_info_identity_free (array_get (data->fIdentities, i));
      }
    array_free (data->fIdentities);
  }
  {
    int len = array_length (data->fFeatures);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	disco_info_feature_free (array_get (data->fFeatures, i));
      }
    array_free (data->fFeatures);
  }
  free (data);
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
      elm->fCategory = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "type");
  if (avalue != NULL)
    {
      elm->fType = (char *) avalue;
    }
  if (xmlreader_skip_element (reader) == -1)
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

void
disco_info_identity_free (struct disco_info_identity_t *data)
{
  if (data == NULL)
    return;
  if (data->fCategory != NULL)
    {
      free (data->fCategory);
    }
  if (data->fType != NULL)
    {
      free (data->fType);
    }
  free (data);
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
      elm->fVar = (char *) avalue;
    }
  if (xmlreader_skip_element (reader) == -1)
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

void
disco_info_feature_free (struct disco_info_feature_t *data)
{
  if (data == NULL)
    return;
  if (data->fVar != NULL)
    {
      free (data->fVar);
    }
  free (data);
}
