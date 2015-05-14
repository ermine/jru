#include "xep_stats_data.h"
#include "helpers.h"

const char *ns_stats = "http://jabber.org/protocol/stats";

struct stats_stats_t *
stats_stats_decode (xmlreader_t * reader)
{
  struct stats_stats_t **elm = NULL;
  elm = malloc (sizeof (struct stats_stats_t **));
  if (elm == NULL)
    fatal ("stats_stats_t: malloc failed");
  *elm = NULL;
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
	      vlist_append ((vlist_t **) elm, (void *) newel,
			    EXTENSION_TYPE_STATS_STAT);
	    }
	}
    }
  return *elm;
}

int
stats_stats_encode (xmlwriter_t * writer, struct stats_stats_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_stats, "query");
  if (err != 0)
    return err;
  vlist_t *curr = (vlist_t *) elm;
  while (curr != NULL)
    {
//tut
      err = stats_stat_encode (writer, curr->data);
      if (err != 0)
	return err;
      curr = curr->next;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
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
      elm->fName = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "units");
  if (avalue != NULL)
    {
      elm->fUnits = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "value");
  if (avalue != NULL)
    {
      elm->fValue = avalue;
    }
  if (xmlreader_skip_element (reader) != -1)
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
