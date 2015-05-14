#include "client_data.h"
#include "helpers.h"

const char *ns_client = "jabber:client";

struct client_iq_t *
client_iq_decode (xmlreader_t * reader)
{
  struct client_iq_t *elm = NULL;
  elm = malloc (sizeof (struct client_iq_t));
  if (elm == NULL)
    fatal ("client_iq_t: malloc failed");
  memset (elm, 0, sizeof (struct client_iq_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "from");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fFrom = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "to");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fTo = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "id");
  if (avalue != NULL)
    {
      elm->fId = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "type");
  if (avalue != NULL)
    {
      elm->fType = enum_client_iq_type_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "lang");
  if (avalue != NULL)
    {
      elm->fLang = avalue;
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
	  if (strcmp (namespace, ns_client) != 0)
	    {
	      extension_t *newel = xstream_extension_decode (reader);
	      if (reader->err != 0)
		return NULL;
	      if (newel == NULL)
		{
		  if (xmlreader_skip_element (reader) == -1)
		    return NULL;
		}
	      else
		{
		  elm->fPayload = newel;
		}
	    }			// end of if strcmp
	  else
	    if ((strcmp (namespace, "urn:ietf:params:xml:ns:xmpp-stanzas") ==
		 0) && (strcmp (name, "error") == 0))
	    {
	      struct stanza_error_t *newel = stanza_error_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->fError = newel;
	    }
	}			// case end
    }				// while end
  return elm;
}

int
client_iq_encode (xmlwriter_t * writer, struct client_iq_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_client, "iq");
  if (err != 0)
    return err;
  if (elm->fFrom != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "from",
			     jid_to_string (elm->fFrom));
      if (err != 0)
	return err;
    }
  if (elm->fTo != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "to", jid_to_string (elm->fTo));
      if (err != 0)
	return err;
    }
  if (elm->fId != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "id", elm->fId);
      if (err != 0)
	return err;
    }
  if (elm->fType != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "type",
			     enum_client_iq_type_to_string (elm->fType));
      if (err != 0)
	return err;
    }
  if (elm->fLang != NULL)
    {
      err = xmlwriter_attribute (writer, ns_xml, "lang", elm->fLang);
      if (err != 0)
	return err;
    }
  if (elm->fPayload != NULL)
    {
      err =
	xstream_extension_encode (writer, elm->fPayload->data,
				  elm->fPayload->type);
      if (err != 0)
	return err;
    }
  if (elm->fError != NULL)
    {
      err = stanza_error_encode (writer, elm->fError);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct client_presence_t *
client_presence_decode (xmlreader_t * reader)
{
  struct client_presence_t *elm = NULL;
  elm = malloc (sizeof (struct client_presence_t));
  if (elm == NULL)
    fatal ("client_presence_t: malloc failed");
  memset (elm, 0, sizeof (struct client_presence_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "from");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fFrom = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "to");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fTo = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "id");
  if (avalue != NULL)
    {
      elm->fId = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "type");
  if (avalue != NULL)
    {
      elm->fType = enum_client_presence_type_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "lang");
  if (avalue != NULL)
    {
      elm->fLang = avalue;
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
	  if ((strcmp (name, "show") == 0)
	      && (strcmp (namespace, ns_client) == 0))
	    {
	      const char *s = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fShow = enum_client_presence_show_from_string (s);
	    }			// for end part 1
	  else if ((strcmp (name, "status") == 0)
		   && (strcmp (namespace, ns_client) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fStatus = (const char *) value;
	    }			// for end part 1
	  else if ((strcmp (name, "priority") == 0)
		   && (strcmp (namespace, ns_client) == 0))
	    {
	      const char *s = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fPriority = strconv_parse_int (s);
	    }			// for end part 1
	  else if (strcmp (namespace, ns_client) != 0)
	    {
	      extension_t *newel = xstream_extension_decode (reader);
	      if (reader->err != 0)
		return NULL;
	      if (newel == NULL)
		{
		  if (xmlreader_skip_element (reader) == -1)
		    return NULL;
		}
	      else
		{
		  vlist_append ((vlist_t **) & elm->fX, newel->data,
				newel->type);
		  free (newel);
		}
	    }
	  else
	    if ((strcmp (namespace, "urn:ietf:params:xml:ns:xmpp-stanzas") ==
		 0) && (strcmp (name, "error") == 0))
	    {
	      struct stanza_error_t *newel = stanza_error_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->fError = newel;
	    }
	}			// case end
    }				// while end
  return elm;
}

int
client_presence_encode (xmlwriter_t * writer, struct client_presence_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_client, "presence");
  if (err != 0)
    return err;
  if (elm->fFrom != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "from",
			     jid_to_string (elm->fFrom));
      if (err != 0)
	return err;
    }
  if (elm->fTo != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "to", jid_to_string (elm->fTo));
      if (err != 0)
	return err;
    }
  if (elm->fId != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "id", elm->fId);
      if (err != 0)
	return err;
    }
  if (elm->fType != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "type",
			     enum_client_presence_type_to_string (elm->
								  fType));
      if (err != 0)
	return err;
    }
  if (elm->fLang != NULL)
    {
      err = xmlwriter_attribute (writer, ns_xml, "lang", elm->fLang);
      if (err != 0)
	return err;
    }
  if (elm->fShow != 0)
    {
      err =
	xmlwriter_simple_element (writer, ns_client, "show",
				  enum_client_presence_show_to_string (elm->
								       fShow));
      if (err != 0)
	return err;
    }
  if (elm->fStatus != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_client, "status", elm->fStatus);
      if (err != 0)
	return err;
    }
  if (elm->fPriority != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_client, "priority",
				  strconv_format_int (elm->fPriority));
      if (err != 0)
	return err;
    }
  {
    vlist_t *curr = (vlist_t *) elm->fX;
    while (curr != NULL)
      {
	err = xstream_extension_encode (writer, curr->data, curr->type);
	if (err != 0)
	  return err;
	curr = curr->next;
      }
  }
  if (elm->fError != NULL)
    {
      err = stanza_error_encode (writer, elm->fError);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct client_message_t *
client_message_decode (xmlreader_t * reader)
{
  struct client_message_t *elm = NULL;
  elm = malloc (sizeof (struct client_message_t));
  if (elm == NULL)
    fatal ("client_message_t: malloc failed");
  memset (elm, 0, sizeof (struct client_message_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "from");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fFrom = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "to");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fTo = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "id");
  if (avalue != NULL)
    {
      elm->fId = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "type");
  if (avalue != NULL)
    {
      elm->fType = enum_client_message_type_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "lang");
  if (avalue != NULL)
    {
      elm->fLang = avalue;
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
	  if ((strcmp (name, "thread") == 0)
	      && (strcmp (namespace, ns_client) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fThread = (const char *) value;
	    }			// for end part 1
	  else if ((strcmp (name, "subject") == 0)
		   && (strcmp (namespace, ns_client) == 0))
	    {
	      langstring_decode (reader, elm->fSubject);
	    }			// for end part 1
	  else if ((strcmp (name, "body") == 0)
		   && (strcmp (namespace, ns_client) == 0))
	    {
	      langstring_decode (reader, elm->fBody);
	    }			// for end part 1
	  else if (strcmp (namespace, ns_client) != 0)
	    {
	      extension_t *newel = xstream_extension_decode (reader);
	      if (reader->err != 0)
		return NULL;
	      if (newel == NULL)
		{
		  if (xmlreader_skip_element (reader) == -1)
		    return NULL;
		}
	      else
		{
		  vlist_append ((vlist_t **) & elm->fX, newel->data,
				newel->type);
		  free (newel);
		}
	    }
	  else
	    if ((strcmp (namespace, "urn:ietf:params:xml:ns:xmpp-stanzas") ==
		 0) && (strcmp (name, "error") == 0))
	    {
	      struct stanza_error_t *newel = stanza_error_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm->fError = newel;
	    }
	}			// case end
    }				// while end
  return elm;
}

int
client_message_encode (xmlwriter_t * writer, struct client_message_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_client, "message");
  if (err != 0)
    return err;
  if (elm->fFrom != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "from",
			     jid_to_string (elm->fFrom));
      if (err != 0)
	return err;
    }
  if (elm->fTo != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "to", jid_to_string (elm->fTo));
      if (err != 0)
	return err;
    }
  if (elm->fId != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "id", elm->fId);
      if (err != 0)
	return err;
    }
  if (elm->fType != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "type",
			     enum_client_message_type_to_string (elm->fType));
      if (err != 0)
	return err;
    }
  if (elm->fLang != NULL)
    {
      err = xmlwriter_attribute (writer, ns_xml, "lang", elm->fLang);
      if (err != 0)
	return err;
    }
  if (elm->fThread != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_client, "thread", elm->fThread);
      if (err != 0)
	return err;
    }
  if (elm->fSubject != NULL)
    {
      err = langstring_encode (writer, ns_client, "subject", elm->fSubject);
      if (err != 0)
	return err;
    }
  if (elm->fBody != NULL)
    {
      err = langstring_encode (writer, ns_client, "body", elm->fBody);
      if (err != 0)
	return err;
    }
  {
    vlist_t *curr = (vlist_t *) elm->fX;
    while (curr != NULL)
      {
	err = xstream_extension_encode (writer, curr->data, curr->type);
	if (err != 0)
	  return err;
	curr = curr->next;
      }
  }
  if (elm->fError != NULL)
    {
      err = stanza_error_encode (writer, elm->fError);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

enum client_iq_type_t
enum_client_iq_type_from_string (const char *value)
{
  if (strcmp (value, "get") == 0)
    return CLIENT_IQ_TYPE_GET;
  else if (strcmp (value, "set") == 0)
    return CLIENT_IQ_TYPE_SET;
  else if (strcmp (value, "result") == 0)
    return CLIENT_IQ_TYPE_RESULT;
  else if (strcmp (value, "error") == 0)
    return CLIENT_IQ_TYPE_ERROR;
  return 0;
}

const char *
enum_client_iq_type_to_string (enum client_iq_type_t value)
{
  switch (value)
    {
    case CLIENT_IQ_TYPE_GET:
      return "get";
    case CLIENT_IQ_TYPE_SET:
      return "set";
    case CLIENT_IQ_TYPE_RESULT:
      return "result";
    case CLIENT_IQ_TYPE_ERROR:
      return "error";
    }
  return NULL;
}

enum client_presence_type_t
enum_client_presence_type_from_string (const char *value)
{
  if (strcmp (value, "subscribe") == 0)
    return CLIENT_PRESENCE_TYPE_SUBSCRIBE;
  else if (strcmp (value, "subscribed") == 0)
    return CLIENT_PRESENCE_TYPE_SUBSCRIBED;
  else if (strcmp (value, "unsubscribe") == 0)
    return CLIENT_PRESENCE_TYPE_UNSUBSCRIBE;
  else if (strcmp (value, "unsubscribed") == 0)
    return CLIENT_PRESENCE_TYPE_UNSUBSCRIBED;
  else if (strcmp (value, "unavailable") == 0)
    return CLIENT_PRESENCE_TYPE_UNAVAILABLE;
  return 0;
}

const char *
enum_client_presence_type_to_string (enum client_presence_type_t value)
{
  switch (value)
    {
    case CLIENT_PRESENCE_TYPE_SUBSCRIBE:
      return "subscribe";
    case CLIENT_PRESENCE_TYPE_SUBSCRIBED:
      return "subscribed";
    case CLIENT_PRESENCE_TYPE_UNSUBSCRIBE:
      return "unsubscribe";
    case CLIENT_PRESENCE_TYPE_UNSUBSCRIBED:
      return "unsubscribed";
    case CLIENT_PRESENCE_TYPE_UNAVAILABLE:
      return "unavailable";
    }
  return NULL;
}

enum client_presence_show_t
enum_client_presence_show_from_string (const char *value)
{
  if (strcmp (value, "chat") == 0)
    return CLIENT_PRESENCE_SHOW_CHAT;
  else if (strcmp (value, "away") == 0)
    return CLIENT_PRESENCE_SHOW_AWAY;
  else if (strcmp (value, "xa") == 0)
    return CLIENT_PRESENCE_SHOW_XA;
  else if (strcmp (value, "dnd") == 0)
    return CLIENT_PRESENCE_SHOW_DND;
  return 0;
}

const char *
enum_client_presence_show_to_string (enum client_presence_show_t value)
{
  switch (value)
    {
    case CLIENT_PRESENCE_SHOW_CHAT:
      return "chat";
    case CLIENT_PRESENCE_SHOW_AWAY:
      return "away";
    case CLIENT_PRESENCE_SHOW_XA:
      return "xa";
    case CLIENT_PRESENCE_SHOW_DND:
      return "dnd";
    }
  return NULL;
}

enum client_message_type_t
enum_client_message_type_from_string (const char *value)
{
  if (strcmp (value, "normal") == 0)
    return CLIENT_MESSAGE_TYPE_NORMAL;
  else if (strcmp (value, "chat") == 0)
    return CLIENT_MESSAGE_TYPE_CHAT;
  else if (strcmp (value, "groupchat") == 0)
    return CLIENT_MESSAGE_TYPE_GROUPCHAT;
  else if (strcmp (value, "headline") == 0)
    return CLIENT_MESSAGE_TYPE_HEADLINE;
  return 0;
}

const char *
enum_client_message_type_to_string (enum client_message_type_t value)
{
  switch (value)
    {
    case CLIENT_MESSAGE_TYPE_NORMAL:
      return "normal";
    case CLIENT_MESSAGE_TYPE_CHAT:
      return "chat";
    case CLIENT_MESSAGE_TYPE_GROUPCHAT:
      return "groupchat";
    case CLIENT_MESSAGE_TYPE_HEADLINE:
      return "headline";
    }
  return NULL;
}
