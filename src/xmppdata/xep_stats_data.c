#include "xep_stats_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_stats = "http://jabber.org/protocol/stats";

array_t *
stats_stats_decode (xmlreader_t * reader)
{
  array_t *elm = array_new (sizeof (extension_t), 0);
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
	  const char *name = xmlreader_get_name (reader);
	  const char *namespace = xmlreader_get_namespace (reader);
	  if ((strcmp (namespace, ns_stats) == 0)
	      && (strcmp (name, "stat") == 0))
	    {
	      struct stats_stat_t *newel = stats_stat_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      array_append (elm, newel);
	    }
	}
    }
  return elm;
}

int
stats_stats_encode (xmlwriter_t * writer, array_t * elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_stats, "query");
  if (err != 0)
    return err;
  int len = array_length (elm);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      struct stats_stat_t *data = array_get (elm, i);
      err = stats_stat_encode (writer, data);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
stats_stats_free (array_t * data)
{
  if (data == NULL)
    return;
  int len = array_length (data);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      struct stats_stat_t **item = array_get (data, i);
      stats_stat_free (item);
    }
  array_free (data);
}

struct stats_stat_t *
stats_stat_decode (xmlreader_t * reader)
{
  struct stats_stat_t *elm = NULL;
  elm = malloc (sizeof (struct stats_stat_t));
  if (elm == NULL)
    fatal ("stats_stat_t: malloc failed");
  memset (elm, 0, sizeof (struct stats_stat_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "name");
  if (avalue != NULL)
    {
      elm->fName = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "units");
  if (avalue != NULL)
    {
      elm->fUnits = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "value");
  if (avalue != NULL)
    {
      elm->fValue = (char *) avalue;
    }
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
stats_stat_encode (xmlwriter_t * writer, struct stats_stat_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_stats, "stat");
  if (err != 0)
    return err;
  if (elm->fName != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "name", elm->fName);
      if (err != 0)
	return err;
    }
  if (elm->fUnits != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "units", elm->fUnits);
      if (err != 0)
	return err;
    }
  if (elm->fValue != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "value", elm->fValue);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
stats_stat_free (struct stats_stat_t *data)
{
  if (data == NULL)
    return;
  if (data->fName != NULL)
    {
      free (data->fName);
    }
  if (data->fUnits != NULL)
    {
      free (data->fUnits);
    }
  if (data->fValue != NULL)
    {
      free (data->fValue);
    }
  free (data);
}
