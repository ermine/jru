#include "roster_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_roster = "jabber:iq:roster";

struct roster_roster_t *
roster_roster_decode (xmlreader_t * reader)
{
  struct roster_roster_t *elm = NULL;
  elm = malloc (sizeof (struct roster_roster_t));
  if (elm == NULL)
    fatal ("roster_roster_t: malloc failed");
  memset (elm, 0, sizeof (struct roster_roster_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "ver");
  if (avalue != NULL)
    {
      elm->fVer = (char *) avalue;
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
	  if ((strcmp (namespace, ns_roster) == 0)
	      && (strcmp (name, "item") == 0))
	    {
	      struct roster_item_t *newel = roster_item_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      if (elm->fItems == NULL)
		elm->fItems = array_new (sizeof (extension_t), 0);
	      array_append (elm->fItems, newel);
	    }
	}
    }
  return elm;
}

int
roster_roster_encode (xmlwriter_t * writer, struct roster_roster_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_roster, "query");
  if (err != 0)
    return err;
  if (elm->fVer != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "ver", elm->fVer);
      if (err != 0)
	return err;
    }
  {
    int len = array_length (elm->fItems);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fItems, i);
	err = roster_item_encode (writer, ext->data);
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
roster_roster_free (struct roster_roster_t *data)
{
  if (data == NULL)
    return;
  if (data->fVer != NULL)
    {
      free (data->fVer);
    }
  {
    int len = array_length (data->fItems);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	roster_item_free (array_get (data->fItems, i));
      }
    array_free (data->fItems);
  }
  free (data);
}

struct roster_item_t *
roster_item_decode (xmlreader_t * reader)
{
  struct roster_item_t *elm = NULL;
  elm = malloc (sizeof (struct roster_item_t));
  if (elm == NULL)
    fatal ("roster_item_t: malloc failed");
  memset (elm, 0, sizeof (struct roster_item_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "approved");
  if (avalue != NULL)
    {
      elm->fApproved = strconv_parse_boolean (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "ask");
  if (avalue != NULL)
    {
      elm->fAsk = enum_roster_item_ask_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "jid");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fJid = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "name");
  if (avalue != NULL)
    {
      elm->fName = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "subscription");
  if (avalue != NULL)
    {
      elm->fSubscription = enum_roster_item_subscription_from_string (avalue);
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
	  if ((strcmp (name, "group") == 0)
	      && (strcmp (namespace, ns_roster) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      if (elm->fGroup == NULL)
		elm->fGroup = array_new (sizeof (char *), 0);
	      array_append (elm->fGroup, (void *) &value);
	    }
	}
    }
  return elm;
}

int
roster_item_encode (xmlwriter_t * writer, struct roster_item_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_roster, "item");
  if (err != 0)
    return err;
  if (elm->fApproved)
    {
      err =
	xmlwriter_attribute (writer, NULL, "approved",
			     strconv_format_boolean (elm->fApproved));
      if (err != 0)
	return err;
    }
  if (elm->fAsk != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "ask",
			     enum_roster_item_ask_to_string (elm->fAsk));
      if (err != 0)
	return err;
    }
  if (elm->fJid != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "jid", jid_to_string (elm->fJid));
      if (err != 0)
	return err;
    }
  if (elm->fName != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "name", elm->fName);
      if (err != 0)
	return err;
    }
  if (elm->fSubscription != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "subscription",
			     enum_roster_item_subscription_to_string (elm->
								      fSubscription));
      if (err != 0)
	return err;
    }
  int len = array_length (elm->fGroup);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (elm->fGroup, i);
      err =
	xmlwriter_simple_element (writer, ns_roster, "group", (char *) value);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
roster_item_free (struct roster_item_t *data)
{
  if (data == NULL)
    return;
  if (data->fApproved)
    {
      free (data->fApproved);
    }
  if (data->fJid != NULL)
    {
      jid_free (data->fJid);
    }
  if (data->fName != NULL)
    {
      free (data->fName);
    }
  int len = array_length (data->fGroup);
  int i = 0;
  for (i = 0; i < len; i++)
    {
      char **value = array_get (data->fGroup, i);
      free (*value);
    }
  array_free (data->fGroup);
  free (data);
}

enum roster_item_ask_t
enum_roster_item_ask_from_string (const char *value)
{
  if (strcmp (value, "subscribe") == 0)
    return ROSTER_ITEM_ASK_SUBSCRIBE;
  return 0;
}

const char *
enum_roster_item_ask_to_string (enum roster_item_ask_t value)
{
  switch (value)
    {
    case ROSTER_ITEM_ASK_SUBSCRIBE:
      return "subscribe";
    }
  return NULL;
}

enum roster_item_subscription_t
enum_roster_item_subscription_from_string (const char *value)
{
  if (strcmp (value, "both") == 0)
    return ROSTER_ITEM_SUBSCRIPTION_BOTH;
  else if (strcmp (value, "from") == 0)
    return ROSTER_ITEM_SUBSCRIPTION_FROM;
  else if (strcmp (value, "none") == 0)
    return ROSTER_ITEM_SUBSCRIPTION_NONE;
  else if (strcmp (value, "remove") == 0)
    return ROSTER_ITEM_SUBSCRIPTION_REMOVE;
  else if (strcmp (value, "to") == 0)
    return ROSTER_ITEM_SUBSCRIPTION_TO;
  return 0;
}

const char *
enum_roster_item_subscription_to_string (enum roster_item_subscription_t
					 value)
{
  switch (value)
    {
    case ROSTER_ITEM_SUBSCRIPTION_BOTH:
      return "both";
    case ROSTER_ITEM_SUBSCRIPTION_FROM:
      return "from";
    case ROSTER_ITEM_SUBSCRIPTION_NONE:
      return "none";
    case ROSTER_ITEM_SUBSCRIPTION_REMOVE:
      return "remove";
    case ROSTER_ITEM_SUBSCRIPTION_TO:
      return "to";
    }
  return NULL;
}
