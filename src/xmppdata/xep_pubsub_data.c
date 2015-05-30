#include "xep_pubsub_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_pubsub_event = "http://jabber.org/protocol/pubsub#event";

struct pubsub_event_event_t *
pubsub_event_event_decode (xmlreader_t * reader)
{
  struct pubsub_event_event_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_event_t));
  if (elm == NULL)
    fatal ("pubsub_event_event_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_event_t));
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
	  if ((strcmp (namespace, ns_pubsub_event) == 0)
	      && (strcmp (name, "collection") == 0))
	    {
	      struct pubsub_event_collection_t *newel =
		pubsub_event_collection_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->type = EXTENSION_TYPE_PUBSUB_EVENT_COLLECTION;
	      elm->u->fCollection = newel;
	    }
	  else if ((strcmp (namespace, ns_pubsub_event) == 0)
		   && (strcmp (name, "configuration") == 0))
	    {
	      struct pubsub_event_configuration_t *newel =
		pubsub_event_configuration_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->type = EXTENSION_TYPE_PUBSUB_EVENT_CONFIGURATION;
	      elm->u->fConfiguration = newel;
	    }
	  else if ((strcmp (namespace, ns_pubsub_event) == 0)
		   && (strcmp (name, "delete") == 0))
	    {
	      struct pubsub_event_delete_t *newel =
		pubsub_event_delete_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->type = EXTENSION_TYPE_PUBSUB_EVENT_DELETE;
	      elm->u->fDelete = newel;
	    }
	  else if ((strcmp (namespace, ns_pubsub_event) == 0)
		   && (strcmp (name, "items") == 0))
	    {
	      struct pubsub_event_items_t *newel =
		pubsub_event_items_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->type = EXTENSION_TYPE_PUBSUB_EVENT_ITEMS;
	      elm->u->fItems = newel;
	    }
	  else if ((strcmp (namespace, ns_pubsub_event) == 0)
		   && (strcmp (name, "purge") == 0))
	    {
	      struct pubsub_event_purge_t *newel =
		pubsub_event_purge_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->type = EXTENSION_TYPE_PUBSUB_EVENT_PURGE;
	      elm->u->fPurge = newel;
	    }
	  else if ((strcmp (namespace, ns_pubsub_event) == 0)
		   && (strcmp (name, "subscription") == 0))
	    {
	      struct pubsub_event_subscription_t *newel =
		pubsub_event_subscription_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->type = EXTENSION_TYPE_PUBSUB_EVENT_SUBSCRIPTION;
	      elm->u->fSubscription = newel;
	    }
	}
    }
  return elm;
}

int
pubsub_event_event_encode (xmlwriter_t * writer,
			   struct pubsub_event_event_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "event");
  if (err != 0)
    return err;
  if (elm->u != NULL)
    {
      err = xstream_extension_encode (writer, (void *) elm->u, elm->type);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
pubsub_event_event_free (struct pubsub_event_event_t *data)
{
  if (data == NULL)
    return;
  if (data->u != NULL)
    {
      extension_t ext = { data->type, data->u };
      xstream_extension_free (&ext);
    }
  free (data);
}

struct pubsub_event_collection_t *
pubsub_event_collection_decode (xmlreader_t * reader)
{
  struct pubsub_event_collection_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_collection_t));
  if (elm == NULL)
    fatal ("pubsub_event_collection_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_collection_t));
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
	  if (strcmp (namespace, ns_pubsub_event) != 0)
	    {
	      const char *avalue;
	      avalue = xmlreader_attribute (reader, NULL, "node");
	      if (avalue != NULL)
		{
		  elm->fType.fNode = (char *) avalue;
		}
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	}
    }
  return elm;
}

int
pubsub_event_collection_encode (xmlwriter_t * writer,
				struct pubsub_event_collection_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "collection");
  if (err != 0)
    return err;
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  const char *name =
    enum_pubsub_event_collection_type_type_to_string (elm->fType.fType);
  err = xmlwriter_start_element (writer, ns_pubsub_event, name);
  if (err != 0)
    return err;
  if (elm->fType.fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fType.fNode);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
pubsub_event_collection_free (struct pubsub_event_collection_t *data)
{
  if (data == NULL)
    return;
  if (data->fNode != NULL)
    {
      free (data->fNode);
    }
  if (data->fType.fNode != NULL)
    {
      free (data->fType.fNode);
    }
  free (data);
}

struct pubsub_event_configuration_t *
pubsub_event_configuration_decode (xmlreader_t * reader)
{
  struct pubsub_event_configuration_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_configuration_t));
  if (elm == NULL)
    fatal ("pubsub_event_configuration_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_configuration_t));
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
	  {
	    if ((strcmp (namespace, "jabber:x:data") == 0)
		&& (strcmp (name, "x") == 0))
	      {
		struct xdata_x_t *newel = xdata_x_decode (reader);
		if (newel == NULL)
		  {
		    return NULL;
		  }
		elm->fXdata = newel;
	      }
	  }
	}
    }
  return elm;
}

int
pubsub_event_configuration_encode (xmlwriter_t * writer,
				   struct pubsub_event_configuration_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "configuration");
  if (err != 0)
    return err;
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  if (elm->fXdata != NULL)
    {
      err = xdata_x_encode (writer, elm->fXdata);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
pubsub_event_configuration_free (struct pubsub_event_configuration_t *data)
{
  if (data == NULL)
    return;
  if (data->fNode != NULL)
    {
      free (data->fNode);
    }
  if (data->fXdata != NULL)
    {
      xdata_x_free (data->fXdata);
    }
  free (data);
}

struct pubsub_event_delete_t *
pubsub_event_delete_decode (xmlreader_t * reader)
{
  struct pubsub_event_delete_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_delete_t));
  if (elm == NULL)
    fatal ("pubsub_event_delete_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_delete_t));
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
	  if ((strcmp (name, "redirect") == 0)
	      && (strcmp (namespace, ns_pubsub_event) == 0))
	    {
	      const char *avalue;
	      avalue = xmlreader_attribute (reader, NULL, "url");
	      if (avalue != NULL)
		{
		  elm->fRedirect.fUrl = (char *) avalue;
		}
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	}
    }
  return elm;
}

int
pubsub_event_delete_encode (xmlwriter_t * writer,
			    struct pubsub_event_delete_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "delete");
  if (err != 0)
    return err;
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  err = xmlwriter_start_element (writer, ns_pubsub_event, "redirect");
  if (err != 0)
    return err;
  if (elm->fRedirect.fUrl != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "url", elm->fRedirect.fUrl);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
pubsub_event_delete_free (struct pubsub_event_delete_t *data)
{
  if (data == NULL)
    return;
  if (data->fNode != NULL)
    {
      free (data->fNode);
    }
  if (data->fRedirect.fUrl != NULL)
    {
      free (data->fRedirect.fUrl);
    }
  free (data);
}

struct pubsub_event_items_t *
pubsub_event_items_decode (xmlreader_t * reader)
{
  struct pubsub_event_items_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_items_t));
  if (elm == NULL)
    fatal ("pubsub_event_items_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_items_t));
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
	  if ((strcmp (namespace, ns_pubsub_event) == 0)
	      && (strcmp (name, "item") == 0))
	    {
	      struct pubsub_event_item_t *newel =
		pubsub_event_item_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      if (elm->fItems == NULL)
		elm->fItems = array_new (sizeof (extension_t), 0);
	      array_append (elm->fItems, newel);
	    }
	  else if ((strcmp (namespace, ns_pubsub_event) == 0)
		   && (strcmp (name, "retract") == 0))
	    {
	      struct pubsub_event_retract_t *newel =
		pubsub_event_retract_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      if (elm->fRetracts == NULL)
		elm->fRetracts = array_new (sizeof (extension_t), 0);
	      array_append (elm->fRetracts, newel);
	    }
	}
    }
  return elm;
}

int
pubsub_event_items_encode (xmlwriter_t * writer,
			   struct pubsub_event_items_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "items");
  if (err != 0)
    return err;
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  {
    int len = array_length (elm->fItems);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fItems, i);
	err = pubsub_event_item_encode (writer, ext->data);
	if (err != 0)
	  return err;
      }
  }
  {
    int len = array_length (elm->fRetracts);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fRetracts, i);
	err = pubsub_event_retract_encode (writer, ext->data);
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
pubsub_event_items_free (struct pubsub_event_items_t *data)
{
  if (data == NULL)
    return;
  if (data->fNode != NULL)
    {
      free (data->fNode);
    }
  {
    int len = array_length (data->fItems);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	pubsub_event_item_free (array_get (data->fItems, i));
      }
    array_free (data->fItems);
  }
  {
    int len = array_length (data->fRetracts);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	pubsub_event_retract_free (array_get (data->fRetracts, i));
      }
    array_free (data->fRetracts);
  }
  free (data);
}

struct pubsub_event_item_t *
pubsub_event_item_decode (xmlreader_t * reader)
{
  struct pubsub_event_item_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_item_t));
  if (elm == NULL)
    fatal ("pubsub_event_item_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_item_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "id");
  if (avalue != NULL)
    {
      elm->fId = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "node");
  if (avalue != NULL)
    {
      elm->fNode = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "publisher");
  if (avalue != NULL)
    {
      elm->fPublisher = (char *) avalue;
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
	  if (strcmp (namespace, ns_pubsub_event) != 0)
	    {
	      extension_t *newel = malloc (sizeof (extension_t));
	      int err = xstream_extension_decode (reader, newel);
	      if (reader->err != 0)
		return NULL;
	      if (err == ERR_EXTENSION_NOT_FOUND)
		{
		  if (xmlreader_skip_element (reader) == -1)
		    return NULL;
		}
	      else
		{
		  elm->fEvent = newel;
		}
	    }
	}
    }
  return elm;
}

int
pubsub_event_item_encode (xmlwriter_t * writer,
			  struct pubsub_event_item_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "item");
  if (err != 0)
    return err;
  if (elm->fId != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "id", elm->fId);
      if (err != 0)
	return err;
    }
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  if (elm->fPublisher != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "publisher", elm->fPublisher);
      if (err != 0)
	return err;
    }
  if (elm->fEvent != NULL)
    {
      err =
	xstream_extension_encode (writer, elm->fEvent->data,
				  elm->fEvent->type);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
pubsub_event_item_free (struct pubsub_event_item_t *data)
{
  if (data == NULL)
    return;
  if (data->fId != NULL)
    {
      free (data->fId);
    }
  if (data->fNode != NULL)
    {
      free (data->fNode);
    }
  if (data->fPublisher != NULL)
    {
      free (data->fPublisher);
    }
  if (data->fEvent != NULL)
    {
      xstream_extension_free (data->fEvent);
      free (data->fEvent);
    }
  free (data);
}

struct pubsub_event_purge_t *
pubsub_event_purge_decode (xmlreader_t * reader)
{
  struct pubsub_event_purge_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_purge_t));
  if (elm == NULL)
    fatal ("pubsub_event_purge_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_purge_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "node");
  if (avalue != NULL)
    {
      elm->fNode = (char *) avalue;
    }
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
pubsub_event_purge_encode (xmlwriter_t * writer,
			   struct pubsub_event_purge_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "purge");
  if (err != 0)
    return err;
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
pubsub_event_purge_free (struct pubsub_event_purge_t *data)
{
  if (data == NULL)
    return;
  if (data->fNode != NULL)
    {
      free (data->fNode);
    }
  free (data);
}

struct pubsub_event_retract_t *
pubsub_event_retract_decode (xmlreader_t * reader)
{
  struct pubsub_event_retract_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_retract_t));
  if (elm == NULL)
    fatal ("pubsub_event_retract_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_retract_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "id");
  if (avalue != NULL)
    {
      elm->fId = (char *) avalue;
    }
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
pubsub_event_retract_encode (xmlwriter_t * writer,
			     struct pubsub_event_retract_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "retract");
  if (err != 0)
    return err;
  if (elm->fId != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "id", elm->fId);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
pubsub_event_retract_free (struct pubsub_event_retract_t *data)
{
  if (data == NULL)
    return;
  if (data->fId != NULL)
    {
      free (data->fId);
    }
  free (data);
}

struct pubsub_event_subscription_t *
pubsub_event_subscription_decode (xmlreader_t * reader)
{
  struct pubsub_event_subscription_t *elm = NULL;
  elm = malloc (sizeof (struct pubsub_event_subscription_t));
  if (elm == NULL)
    fatal ("pubsub_event_subscription_t: malloc failed");
  memset (elm, 0, sizeof (struct pubsub_event_subscription_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "expiry");
  if (avalue != NULL)
    {
      elm->fExpiry = datetime_parse (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "jid");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fJid = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "node");
  if (avalue != NULL)
    {
      elm->fNode = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "subid");
  if (avalue != NULL)
    {
      elm->fSubid = (char *) avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "subscription");
  if (avalue != NULL)
    {
      elm->fSubscription =
	enum_pubsub_event_subscription_subscription_from_string (avalue);
    }
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
pubsub_event_subscription_encode (xmlwriter_t * writer,
				  struct pubsub_event_subscription_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_pubsub_event, "subscription");
  if (err != 0)
    return err;
  if (elm->fExpiry != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "expiry",
			     datetime_to_string (elm->fExpiry));
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
  if (elm->fNode != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "node", elm->fNode);
      if (err != 0)
	return err;
    }
  if (elm->fSubid != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "subid", elm->fSubid);
      if (err != 0)
	return err;
    }
  if (elm->fSubscription != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "subscription",
			     enum_pubsub_event_subscription_subscription_to_string
			     (elm->fSubscription));
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
pubsub_event_subscription_free (struct pubsub_event_subscription_t *data)
{
  if (data == NULL)
    return;
  if (data->fExpiry != NULL)
    {
      free (data->fExpiry);
    }
  if (data->fJid != NULL)
    {
      jid_free (data->fJid);
    }
  if (data->fNode != NULL)
    {
      free (data->fNode);
    }
  if (data->fSubid != NULL)
    {
      free (data->fSubid);
    }
  free (data);
}

enum pubsub_event_collection_type_type_t
enum_pubsub_event_collection_type_type_from_string (const char *value)
{
  if (strcmp (value, "associate") == 0)
    return PUBSUB_EVENT_COLLECTION_TYPE_TYPE_ASSOCIATE;
  else if (strcmp (value, "disassociate") == 0)
    return PUBSUB_EVENT_COLLECTION_TYPE_TYPE_DISASSOCIATE;
  return 0;
}

const char *
enum_pubsub_event_collection_type_type_to_string (enum
						  pubsub_event_collection_type_type_t
						  value)
{
  switch (value)
    {
    case PUBSUB_EVENT_COLLECTION_TYPE_TYPE_ASSOCIATE:
      return "associate";
    case PUBSUB_EVENT_COLLECTION_TYPE_TYPE_DISASSOCIATE:
      return "disassociate";
    }
  return NULL;
}

enum pubsub_event_subscription_subscription_t
enum_pubsub_event_subscription_subscription_from_string (const char *value)
{
  if (strcmp (value, "none") == 0)
    return PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_NONE;
  else if (strcmp (value, "pending") == 0)
    return PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_PENDING;
  else if (strcmp (value, "subscribed") == 0)
    return PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_SUBSCRIBED;
  else if (strcmp (value, "unconfigured") == 0)
    return PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_UNCONFIGURED;
  return 0;
}

const char *
enum_pubsub_event_subscription_subscription_to_string (enum
						       pubsub_event_subscription_subscription_t
						       value)
{
  switch (value)
    {
    case PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_NONE:
      return "none";
    case PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_PENDING:
      return "pending";
    case PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_SUBSCRIBED:
      return "subscribed";
    case PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_UNCONFIGURED:
      return "unconfigured";
    }
  return NULL;
}
