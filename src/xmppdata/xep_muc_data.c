#include "xep_muc_data.h"
#include "helpers.h"

const char *ns_muc = "http://jabber.org/protocol/muc";
const char *ns_muc_user = "http://jabber.org/protocol/muc#user";
const char *ns_muc_owner = "http://jabber.org/protocol/muc#owner";
const char *ns_muc_admin = "http://jabber.org/protocol/muc#admin";

struct muc_enter_t *
muc_enter_decode (xmlreader_t * reader)
{
  struct muc_enter_t *elm = NULL;
  elm = malloc (sizeof (struct muc_enter_t));
  if (elm == NULL)
    fatal ("muc_enter_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_enter_t));
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
	  if ((strcmp (name, "history") == 0)
	      && (strcmp (namespace, ns_muc) == 0))
	    {
	      const char *avalue;
	      avalue = xmlreader_attribute (reader, NULL, "maxchars");
	      if (avalue != NULL)
		{
		  elm->fHistory.fMaxchars = strconv_parse_int (avalue);
		}
	      avalue = xmlreader_attribute (reader, NULL, "maxstanzas");
	      if (avalue != NULL)
		{
		  elm->fHistory.fMaxstanzas = strconv_parse_int (avalue);
		}
	      avalue = xmlreader_attribute (reader, NULL, "seconds");
	      if (avalue != NULL)
		{
		  elm->fHistory.fSeconds = strconv_parse_int (avalue);
		}
	      avalue = xmlreader_attribute (reader, NULL, "since");
	      if (avalue != NULL)
		{
		  elm->fHistory.fSince = datetime_parse (avalue);
		}
	      if (xmlreader_skip_element (reader) != -1)
		return NULL;
	    }			// for end part 1
	  else if ((strcmp (name, "password") == 0)
		   && (strcmp (namespace, ns_muc) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fPassword = (const char *) value;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
muc_enter_encode (xmlwriter_t * writer, struct muc_enter_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc, "x");
  if (err != 0)
    return err;
  err = xmlwriter_start_element (writer, ns_muc, "history");
  if (err != 0)
    return err;
  if (elm->fHistory.fMaxchars != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "maxchars",
			     strconv_format_int (elm->fHistory.fMaxchars));
      if (err != 0)
	return err;
    }
  if (elm->fHistory.fMaxstanzas != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "maxstanzas",
			     strconv_format_int (elm->fHistory.fMaxstanzas));
      if (err != 0)
	return err;
    }
  if (elm->fHistory.fSeconds != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "seconds",
			     strconv_format_int (elm->fHistory.fSeconds));
      if (err != 0)
	return err;
    }
  if (elm->fHistory.fSince != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "since",
			     datetime_to_string (elm->fHistory.fSince));
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  if (elm->fPassword != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_muc, "password", elm->fPassword);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct muc_user_action_t *
muc_user_action_decode (xmlreader_t * reader)
{
  struct muc_user_action_t *elm = NULL;
  elm = malloc (sizeof (struct muc_user_action_t));
  if (elm == NULL)
    fatal ("muc_user_action_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_user_action_t));
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
	  if ((strcmp (namespace, ns_muc_user) == 0)
	      && (strcmp (name, "invite") == 0))
	    {
	      struct muc_user_invite_t *newel =
		muc_user_invite_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      vlist_append ((vlist_t **) & elm->fInvite, (void *) newel,
			    EXTENSION_TYPE_MUC_USER_INVITE);
	    }
	  else if ((strcmp (name, "password") == 0)
		   && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fPassword = (const char *) value;
	    }			// for end part 1
	  else if ((strcmp (namespace, ns_muc_user) == 0)
		   && (strcmp (name, "status") == 0))
	    {
	      struct muc_user_status_t *newel =
		muc_user_status_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      vlist_append ((vlist_t **) & elm->fStatus, (void *) newel,
			    EXTENSION_TYPE_MUC_USER_STATUS);
	    }
	}			// case end
    }				// while end
  return elm;
}

int
muc_user_action_encode (xmlwriter_t * writer, struct muc_user_action_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_user, "x");
  if (err != 0)
    return err;
  if (elm->fDecline != NULL)
    {
      err = muc_user_decline_encode (writer, elm->fDecline);
      if (err != 0)
	return err;
    }
  if (elm->fDestroy != NULL)
    {
      err = muc_user_destroy_encode (writer, elm->fDestroy);
      if (err != 0)
	return err;
    }
  {
    vlist_t *curr = (vlist_t *) elm->fInvite;
    while (curr != NULL)
      {
	err = muc_user_invite_encode (writer, curr->data);
	if (err != 0)
	  return err;
	curr = curr->next;
      }
  }
  if (elm->fItem != NULL)
    {
      err = muc_user_item_encode (writer, elm->fItem);
      if (err != 0)
	return err;
    }
  if (elm->fPassword != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_muc_user, "password",
				  elm->fPassword);
      if (err != 0)
	return err;
    }
  {
    vlist_t *curr = (vlist_t *) elm->fStatus;
    while (curr != NULL)
      {
	err = muc_user_status_encode (writer, curr->data);
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

struct muc_user_status_t *
muc_user_status_decode (xmlreader_t * reader)
{
  struct muc_user_status_t *elm = NULL;
  elm = malloc (sizeof (struct muc_user_status_t));
  if (elm == NULL)
    fatal ("muc_user_status_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_user_status_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "code");
  if (avalue != NULL)
    {
      elm->fCode = strconv_parse_int (avalue);
    }
  if (xmlreader_skip_element (reader) != -1)
    return NULL;
  return elm;
}

int
muc_user_status_encode (xmlwriter_t * writer, struct muc_user_status_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_user, "status");
  if (err != 0)
    return err;
  if (elm->fCode != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "code",
			     strconv_format_int (elm->fCode));
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct muc_user_decline_t *
muc_user_decline_decode (xmlreader_t * reader)
{
  struct muc_user_decline_t *elm = NULL;
  elm = malloc (sizeof (struct muc_user_decline_t));
  if (elm == NULL)
    fatal ("muc_user_decline_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_user_decline_t));
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
	  if ((strcmp (name, "reason") == 0)
	      && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fReason = (const char *) value;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
muc_user_decline_encode (xmlwriter_t * writer, struct muc_user_decline_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_user, "decline");
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
  if (elm->fReason != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_muc_user, "reason",
				  elm->fReason);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct muc_user_destroy_t *
muc_user_destroy_decode (xmlreader_t * reader)
{
  struct muc_user_destroy_t *elm = NULL;
  elm = malloc (sizeof (struct muc_user_destroy_t));
  if (elm == NULL)
    fatal ("muc_user_destroy_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_user_destroy_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "jid");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fJid = jid;
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
	  if ((strcmp (name, "reason") == 0)
	      && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fReason = (const char *) value;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
muc_user_destroy_encode (xmlwriter_t * writer, struct muc_user_destroy_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_user, "destroy");
  if (err != 0)
    return err;
  if (elm->fJid != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "jid", jid_to_string (elm->fJid));
      if (err != 0)
	return err;
    }
  if (elm->fReason != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_muc_user, "reason",
				  elm->fReason);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct muc_user_invite_t *
muc_user_invite_decode (xmlreader_t * reader)
{
  struct muc_user_invite_t *elm = NULL;
  elm = malloc (sizeof (struct muc_user_invite_t));
  if (elm == NULL)
    fatal ("muc_user_invite_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_user_invite_t));
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
	  if ((strcmp (name, "reason") == 0)
	      && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fReason = (const char *) value;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
muc_user_invite_encode (xmlwriter_t * writer, struct muc_user_invite_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_user, "invite");
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
  if (elm->fReason != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_muc_user, "reason",
				  elm->fReason);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct muc_user_item_t *
muc_user_item_decode (xmlreader_t * reader)
{
  struct muc_user_item_t *elm = NULL;
  elm = malloc (sizeof (struct muc_user_item_t));
  if (elm == NULL)
    fatal ("muc_user_item_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_user_item_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "affiliation");
  if (avalue != NULL)
    {
      elm->fAffiliation = enum_muc_user_item_affiliation_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "jid");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fJid = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "nick");
  if (avalue != NULL)
    {
      elm->fNick = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "role");
  if (avalue != NULL)
    {
      elm->fRole = enum_muc_user_item_role_from_string (avalue);
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
	  if ((strcmp (name, "actor") == 0)
	      && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      const char *avalue;
	      avalue = xmlreader_attribute (reader, NULL, "jid");
	      if (avalue != NULL)
		{
		  jid_t *jid = jid_of_string (avalue);
		  elm->fActor.fJid = jid;
		}
	      if (xmlreader_skip_element (reader) != -1)
		return NULL;
	    }			// for end part 1
	  else if ((strcmp (name, "reason") == 0)
		   && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fReason = (const char *) value;
	    }			// for end part 1
	  else if ((strcmp (name, "continue") == 0)
		   && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      elm->fContinue = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
muc_user_item_encode (xmlwriter_t * writer, struct muc_user_item_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_user, "item");
  if (err != 0)
    return err;
  if (elm->fAffiliation != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "affiliation",
			     enum_muc_user_item_affiliation_to_string (elm->
								       fAffiliation));
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
  if (elm->fNick != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "nick", elm->fNick);
      if (err != 0)
	return err;
    }
  if (elm->fRole != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "role",
			     enum_muc_user_item_role_to_string (elm->fRole));
      if (err != 0)
	return err;
    }
  err = xmlwriter_start_element (writer, ns_muc_user, "actor");
  if (err != 0)
    return err;
  if (elm->fActor.fJid != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "jid",
			     jid_to_string (elm->fActor.fJid));
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  if (elm->fReason != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_muc_user, "reason",
				  elm->fReason);
      if (err != 0)
	return err;
    }
  if (elm->fContinue)
    {
      err = xmlwriter_simple_element (writer, ns_muc_user, "continue", NULL);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

enum muc_user_item_affiliation_t
enum_muc_user_item_affiliation_from_string (const char *value)
{
  if (strcmp (value, "admin") == 0)
    return MUC_USER_ITEM_AFFILIATION_ADMIN;
  else if (strcmp (value, "member") == 0)
    return MUC_USER_ITEM_AFFILIATION_MEMBER;
  else if (strcmp (value, "none") == 0)
    return MUC_USER_ITEM_AFFILIATION_NONE;
  else if (strcmp (value, "outcast") == 0)
    return MUC_USER_ITEM_AFFILIATION_OUTCAST;
  else if (strcmp (value, "owner") == 0)
    return MUC_USER_ITEM_AFFILIATION_OWNER;
  return 0;
}

const char *
enum_muc_user_item_affiliation_to_string (enum muc_user_item_affiliation_t
					  value)
{
  switch (value)
    {
    case MUC_USER_ITEM_AFFILIATION_ADMIN:
      return "admin";
    case MUC_USER_ITEM_AFFILIATION_MEMBER:
      return "member";
    case MUC_USER_ITEM_AFFILIATION_NONE:
      return "none";
    case MUC_USER_ITEM_AFFILIATION_OUTCAST:
      return "outcast";
    case MUC_USER_ITEM_AFFILIATION_OWNER:
      return "owner";
    }
  return NULL;
}

enum muc_user_item_role_t
enum_muc_user_item_role_from_string (const char *value)
{
  if (strcmp (value, "moderator") == 0)
    return MUC_USER_ITEM_ROLE_MODERATOR;
  else if (strcmp (value, "none") == 0)
    return MUC_USER_ITEM_ROLE_NONE;
  else if (strcmp (value, "participant") == 0)
    return MUC_USER_ITEM_ROLE_PARTICIPANT;
  else if (strcmp (value, "visitor") == 0)
    return MUC_USER_ITEM_ROLE_VISITOR;
  return 0;
}

const char *
enum_muc_user_item_role_to_string (enum muc_user_item_role_t value)
{
  switch (value)
    {
    case MUC_USER_ITEM_ROLE_MODERATOR:
      return "moderator";
    case MUC_USER_ITEM_ROLE_NONE:
      return "none";
    case MUC_USER_ITEM_ROLE_PARTICIPANT:
      return "participant";
    case MUC_USER_ITEM_ROLE_VISITOR:
      return "visitor";
    }
  return NULL;
}

muc_owner_configure_t *
muc_owner_configure_decode (xmlreader_t * reader)
{
  muc_owner_configure_t *elm = NULL;
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
	  if ((strcmp (namespace, "jabber:x:data") == 0)
	      && (strcmp (name, "x") == 0))
	    {
	      extension_t *newel = xstream_extension_decode (reader);
	      if (reader->err != 0)
		return NULL;
	      if (newel == NULL)
		{
		  return NULL;
		}
	      elm = (muc_owner_configure_t *) newel;
	    }
	  else
	    {
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	}
    }
  return elm;
}

int
muc_owner_configure_encode (xmlwriter_t * writer, muc_owner_configure_t * elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_owner, "query");
  if (err != 0)
    return err;
//here
  err = xdata_x_encode (writer, elm);
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

struct muc_admin_query_t *
muc_admin_query_decode (xmlreader_t * reader)
{
  struct muc_admin_query_t *elm = NULL;
  elm = malloc (sizeof (struct muc_admin_query_t));
  if (elm == NULL)
    fatal ("muc_admin_query_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_admin_query_t));
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
	  if ((strcmp (namespace, ns_muc_admin) == 0)
	      && (strcmp (name, "item") == 0))
	    {
	      struct muc_admin_item_t *newel = muc_admin_item_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      vlist_append ((vlist_t **) & elm->fItems, (void *) newel,
			    EXTENSION_TYPE_MUC_ADMIN_ITEM);
	    }
	}			// case end
    }				// while end
  return elm;
}

int
muc_admin_query_encode (xmlwriter_t * writer, struct muc_admin_query_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_admin, "query");
  if (err != 0)
    return err;
  {
    vlist_t *curr = (vlist_t *) elm->fItems;
    while (curr != NULL)
      {
	err = muc_admin_item_encode (writer, curr->data);
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

struct muc_admin_item_t *
muc_admin_item_decode (xmlreader_t * reader)
{
  struct muc_admin_item_t *elm = NULL;
  elm = malloc (sizeof (struct muc_admin_item_t));
  if (elm == NULL)
    fatal ("muc_admin_item_t: malloc failed");
  memset (elm, 0, sizeof (struct muc_admin_item_t));
  const char *avalue;
  avalue = xmlreader_attribute (reader, NULL, "affiliation");
  if (avalue != NULL)
    {
      elm->fAffiliation =
	enum_muc_admin_item_affiliation_from_string (avalue);
    }
  avalue = xmlreader_attribute (reader, NULL, "jid");
  if (avalue != NULL)
    {
      jid_t *jid = jid_of_string (avalue);
      elm->fJid = jid;
    }
  avalue = xmlreader_attribute (reader, NULL, "nick");
  if (avalue != NULL)
    {
      elm->fNick = avalue;
    }
  avalue = xmlreader_attribute (reader, NULL, "role");
  if (avalue != NULL)
    {
      elm->fRole = enum_muc_admin_item_role_from_string (avalue);
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
	  if ((strcmp (name, "actor") == 0)
	      && (strcmp (namespace, ns_muc_admin) == 0))
	    {
	      const char *avalue;
	      avalue = xmlreader_attribute (reader, NULL, "jid");
	      if (avalue != NULL)
		{
		  jid_t *jid = jid_of_string (avalue);
		  elm->fActor.fJid = jid;
		}
	      if (xmlreader_skip_element (reader) != -1)
		return NULL;
	    }			// for end part 1
	  else if ((strcmp (name, "reason") == 0)
		   && (strcmp (namespace, ns_muc_admin) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fReason = (const char *) value;
	    }			// for end part 1
	}			// case end
    }				// while end
  return elm;
}

int
muc_admin_item_encode (xmlwriter_t * writer, struct muc_admin_item_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_muc_admin, "item");
  if (err != 0)
    return err;
  if (elm->fAffiliation != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "affiliation",
			     enum_muc_admin_item_affiliation_to_string (elm->
									fAffiliation));
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
  if (elm->fNick != NULL)
    {
      err = xmlwriter_attribute (writer, NULL, "nick", elm->fNick);
      if (err != 0)
	return err;
    }
  if (elm->fRole != 0)
    {
      err =
	xmlwriter_attribute (writer, NULL, "role",
			     enum_muc_admin_item_role_to_string (elm->fRole));
      if (err != 0)
	return err;
    }
  err = xmlwriter_start_element (writer, ns_muc_admin, "actor");
  if (err != 0)
    return err;
  if (elm->fActor.fJid != NULL)
    {
      err =
	xmlwriter_attribute (writer, NULL, "jid",
			     jid_to_string (elm->fActor.fJid));
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  if (elm->fReason != NULL)
    {
      err =
	xmlwriter_simple_element (writer, ns_muc_admin, "reason",
				  elm->fReason);
      if (err != 0)
	return err;
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

enum muc_admin_item_affiliation_t
enum_muc_admin_item_affiliation_from_string (const char *value)
{
  if (strcmp (value, "admin") == 0)
    return MUC_ADMIN_ITEM_AFFILIATION_ADMIN;
  else if (strcmp (value, "member") == 0)
    return MUC_ADMIN_ITEM_AFFILIATION_MEMBER;
  else if (strcmp (value, "none") == 0)
    return MUC_ADMIN_ITEM_AFFILIATION_NONE;
  else if (strcmp (value, "outcast") == 0)
    return MUC_ADMIN_ITEM_AFFILIATION_OUTCAST;
  else if (strcmp (value, "owner") == 0)
    return MUC_ADMIN_ITEM_AFFILIATION_OWNER;
  return 0;
}

const char *
enum_muc_admin_item_affiliation_to_string (enum muc_admin_item_affiliation_t
					   value)
{
  switch (value)
    {
    case MUC_ADMIN_ITEM_AFFILIATION_ADMIN:
      return "admin";
    case MUC_ADMIN_ITEM_AFFILIATION_MEMBER:
      return "member";
    case MUC_ADMIN_ITEM_AFFILIATION_NONE:
      return "none";
    case MUC_ADMIN_ITEM_AFFILIATION_OUTCAST:
      return "outcast";
    case MUC_ADMIN_ITEM_AFFILIATION_OWNER:
      return "owner";
    }
  return NULL;
}

enum muc_admin_item_role_t
enum_muc_admin_item_role_from_string (const char *value)
{
  if (strcmp (value, "moderator") == 0)
    return MUC_ADMIN_ITEM_ROLE_MODERATOR;
  else if (strcmp (value, "none") == 0)
    return MUC_ADMIN_ITEM_ROLE_NONE;
  else if (strcmp (value, "participant") == 0)
    return MUC_ADMIN_ITEM_ROLE_PARTICIPANT;
  else if (strcmp (value, "visitor") == 0)
    return MUC_ADMIN_ITEM_ROLE_VISITOR;
  return 0;
}

const char *
enum_muc_admin_item_role_to_string (enum muc_admin_item_role_t value)
{
  switch (value)
    {
    case MUC_ADMIN_ITEM_ROLE_MODERATOR:
      return "moderator";
    case MUC_ADMIN_ITEM_ROLE_NONE:
      return "none";
    case MUC_ADMIN_ITEM_ROLE_PARTICIPANT:
      return "participant";
    case MUC_ADMIN_ITEM_ROLE_VISITOR:
      return "visitor";
    }
  return NULL;
}
