#include "xep_privacy_data.h"
#include "helpers.h"

const char *ns_privacy = "jabber:iq:privacy";

struct privacy_privacy_t *
privacy_privacy_decode (xmlreader_t * reader)
{
  struct privacy_privacy_t *elm = NULL;
  elm = malloc (sizeof (struct privacy_privacy_t));
  if (elm == NULL)
    fatal ("privacy_privacy_t: malloc failed");
  memset (elm, 0, sizeof (struct privacy_privacy_t));
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
	  if ((strcmp (namespace, ns_privacy) == 0)
	      && (strcmp (name, "list") == 0))
	    {
	      struct privacy_list_t *newel = privacy_list_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      vlist_append ((vlist_t **) & elm->fList, (void *) newel,
			    EXTENSION_TYPE_PRIVACY_LIST);
	    }
	}			// case end
    }				// while end
  return elm;
}

int
privacy_privacy_encode (xmlwriter_t * writer, struct privacy_privacy_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_privacy, "query");
  if (err != 0)
    return err;
  if (elm->fActive != NULL)
    {
      err = privacy_active_encode (writer, elm->fActive);
      if (err != 0)
	return err;
    }
  if (elm->fDefault != NULL)
    {
      err = privacy_default_encode (writer, elm->fDefault);
      if (err != 0)
	return err;
    }
  {
    vlist_t *curr = (vlist_t *) elm->fList;
    while (curr != NULL)
      {
	err = privacy_list_encode (writer, curr->data);
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

struct privacy_active_t *
privacy_active_decode (xmlreader_t * reader)
{
  struct privacy_active_t *elm = NULL;
  elm = malloc (sizeof (struct privacy_active_t));
  if (elm == NULL)
    fatal ("privacy_active_t: malloc failed");
  memset (elm, 0, sizeof (struct privacy_active_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "name");
  if (avalue != NULL)
    {
      elm->fName = avalue;
    }
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm->fExtra = (const char *) value;
  return elm;
}

int
privacy_active_encode (xmlwriter_t * writer, struct privacy_active_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_privacy, "active");
  if (err != 0)
    return err;
  if (elm->fName != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "name", elm->fName);
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

struct privacy_default_t *
privacy_default_decode (xmlreader_t * reader)
{
  struct privacy_default_t *elm = NULL;
  elm = malloc (sizeof (struct privacy_default_t));
  if (elm == NULL)
    fatal ("privacy_default_t: malloc failed");
  memset (elm, 0, sizeof (struct privacy_default_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "name");
  if (avalue != NULL)
    {
      elm->fName = avalue;
    }
  const char *value = xmlreader_text (reader);
  if (reader->err != 0)
    return NULL;
  elm->fExtra = (const char *) value;
  return elm;
}

int
privacy_default_encode (xmlwriter_t * writer, struct privacy_default_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_privacy, "default");
  if (err != 0)
    return err;
  if (elm->fName != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "name", elm->fName);
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

struct privacy_list_t *
privacy_list_decode (xmlreader_t * reader)
{
  struct privacy_list_t *elm = NULL;
  elm = malloc (sizeof (struct privacy_list_t));
  if (elm == NULL)
    fatal ("privacy_list_t: malloc failed");
  memset (elm, 0, sizeof (struct privacy_list_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "name");
  if (avalue != NULL)
    {
      elm->fName = avalue;
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
	  if ((strcmp (namespace, ns_privacy) == 0)
	      && (strcmp (name, "item") == 0))
	    {
	      struct privacy_item_t *newel = privacy_item_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      vlist_append ((vlist_t **) & elm->fItems, (void *) newel,
			    EXTENSION_TYPE_PRIVACY_ITEM);
	    }
	}			// case end
    }				// while end
  return elm;
}

int
privacy_list_encode (xmlwriter_t * writer, struct privacy_list_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_privacy, "list");
  if (err != 0)
    return err;
  if (elm->fName != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "name", elm->fName);
      if (err != 0)
	return err;
    }
  {
    vlist_t *curr = (vlist_t *) elm->fItems;
    while (curr != NULL)
      {
	err = privacy_item_encode (writer, curr->data);
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

struct privacy_item_t *
privacy_item_decode (xmlreader_t * reader)
{
  struct privacy_item_t *elm = NULL;
  elm = malloc (sizeof (struct privacy_item_t));
  if (elm == NULL)
    fatal ("privacy_item_t: malloc failed");
  memset (elm, 0, sizeof (struct privacy_item_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "action");
  if (avalue != NULL)
    {
      elm->fAction = enum_privacy_item_action_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "order");
  if (avalue != NULL)
    {
      elm->fOrder = strconv_parse_uint (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "type");
  if (avalue != NULL)
    {
      elm->fType = enum_privacy_item_type_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "value");
  if (avalue != NULL)
    {
      elm->fValue = avalue;
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
	  if ((strcmp (name, "iq") == 0)
	      && (strcmp (namespace, ns_privacy) == 0))
	    {
	      elm->fIq = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }			// for end part 1
	  else if ((strcmp (name, "message") == 0)
		   && (strcmp (namespace, ns_privacy) == 0))
	    {
	      elm->fMessage = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }			// for end part 1
	  else if ((strcmp (name, "presence-in") == 0)
		   && (strcmp (namespace, ns_privacy) == 0))
	    {
	      elm->fPresence_in = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }			// for end part 1
	  else if ((strcmp (name, "presence-out") == 0)
		   && (strcmp (namespace, ns_privacy) == 0))
	    {
	      elm->fPresence_out = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
privacy_item_encode (xmlwriter_t * writer, struct privacy_item_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_privacy, "item");
  if (err != 0)
    return err;
  if (elm->fAction != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "action",
			     enum_privacy_item_action_to_string (elm->
								 fAction));
      if (err != 0)
	return err;
    }
  if (elm->fOrder != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "order",
			     strconv_format_uint (elm->fOrder));
      if (err != 0)
	return err;
    }
  if (elm->fType != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "type",
			     enum_privacy_item_type_to_string (elm->fType));
      if (err != 0)
	return err;
    }
  if (elm->fValue != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "value", elm->fValue);
      if (err != 0)
	return err;
    }
  if (elm->fIq)
    {
      err = xmlwriter_simple_element (writer, ns_privacy, "iq", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fMessage)
    {
      err = xmlwriter_simple_element (writer, ns_privacy, "message", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPresence_in)
    {
      err =
	xmlwriter_simple_element (writer, ns_privacy, "presence-in", NULL);
      if (err != 0)
	return err;
    }
  if (elm->fPresence_out)
    {
      err =
	xmlwriter_simple_element (writer, ns_privacy, "presence-out", NULL);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

enum privacy_item_action_t
enum_privacy_item_action_from_string (const char *value)
{
  if (strcmp (value, "allow") == 0)
    return PRIVACY_ITEM_ACTION_ALLOW;
  else if (strcmp (value, "deny") == 0)
    return PRIVACY_ITEM_ACTION_DENY;
  return 0;
}

const char *
enum_privacy_item_action_to_string (enum privacy_item_action_t value)
{
  switch (value)
    {
    case PRIVACY_ITEM_ACTION_ALLOW:
      return "allow";
    case PRIVACY_ITEM_ACTION_DENY:
      return "deny";
    }
  return NULL;
}

enum privacy_item_type_t
enum_privacy_item_type_from_string (const char *value)
{
  if (strcmp (value, "group") == 0)
    return PRIVACY_ITEM_TYPE_GROUP;
  else if (strcmp (value, "jid") == 0)
    return PRIVACY_ITEM_TYPE_JID;
  else if (strcmp (value, "subscription") == 0)
    return PRIVACY_ITEM_TYPE_SUBSCRIPTION;
  return 0;
}

const char *
enum_privacy_item_type_to_string (enum privacy_item_type_t value)
{
  switch (value)
    {
    case PRIVACY_ITEM_TYPE_GROUP:
      return "group";
    case PRIVACY_ITEM_TYPE_JID:
      return "jid";
    case PRIVACY_ITEM_TYPE_SUBSCRIPTION:
      return "subscription";
    }
  return NULL;
}
