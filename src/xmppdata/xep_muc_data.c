#include "xep_muc_data.h"
#include "helpers.h"
#include "errors.h"

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
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	  else if ((strcmp (name, "password") == 0)
		   && (strcmp (namespace, ns_muc) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fPassword = (char *) value;
	    }
	}
    }
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

void
muc_enter_free (struct muc_enter_t *data)
{
  if (data == NULL)
    return;
  if (data->fHistory.fMaxchars != NULL)
    {
      free (data->fHistory.fMaxchars);
    }
  if (data->fHistory.fMaxstanzas != NULL)
    {
      free (data->fHistory.fMaxstanzas);
    }
  if (data->fHistory.fSeconds != NULL)
    {
      free (data->fHistory.fSeconds);
    }
  if (data->fHistory.fSince != NULL)
    {
      free (data->fHistory.fSince);
    }
  if (data->fPassword != NULL)
    {
      free (data->fPassword);
    }
  free (data);
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
	      if (elm->fInvite == NULL)
		elm->fInvite = array_new (sizeof (extension_t), 0);
	      array_append (elm->fInvite, newel);
	    }
	  else if ((strcmp (name, "password") == 0)
		   && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fPassword = (char *) value;
	    }
	  else if ((strcmp (namespace, ns_muc_user) == 0)
		   && (strcmp (name, "status") == 0))
	    {
	      struct muc_user_status_t *newel =
		muc_user_status_decode (reader);
	      if (newel == NULL)
		{
		  return NULL;
		}
	      if (elm->fStatus == NULL)
		elm->fStatus = array_new (sizeof (extension_t), 0);
	      array_append (elm->fStatus, newel);
	    }
	}
    }
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
    int len = array_length (elm->fInvite);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fInvite, i);
	err = muc_user_invite_encode (writer, ext->data);
	if (err != 0)
	  return err;
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
    int len = array_length (elm->fStatus);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fStatus, i);
	err = muc_user_status_encode (writer, ext->data);
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
muc_user_action_free (struct muc_user_action_t *data)
{
  if (data == NULL)
    return;
  if (data->fDecline != NULL)
    {
    }
  if (data->fDestroy != NULL)
    {
    }
  {
    int len = array_length (data->fInvite);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	muc_user_invite_free (array_get (data->fInvite, i));
      }
    array_free (data->fInvite);
  }
  if (data->fItem != NULL)
    {
    }
  if (data->fPassword != NULL)
    {
      free (data->fPassword);
    }
  {
    int len = array_length (data->fStatus);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	muc_user_status_free (array_get (data->fStatus, i));
      }
    array_free (data->fStatus);
  }
  free (data);
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
  if (xmlreader_skip_element (reader) == -1)
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

void
muc_user_status_free (struct muc_user_status_t *data)
{
  if (data == NULL)
    return;
  if (data->fCode != NULL)
    {
      free (data->fCode);
    }
  free (data);
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
	      elm->fReason = (char *) value;
	    }
	}
    }
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

void
muc_user_decline_free (struct muc_user_decline_t *data)
{
  if (data == NULL)
    return;
  if (data->fFrom != NULL)
    {
      jid_free (data->fFrom);
    }
  if (data->fTo != NULL)
    {
      jid_free (data->fTo);
    }
  if (data->fReason != NULL)
    {
      free (data->fReason);
    }
  free (data);
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
	      elm->fReason = (char *) value;
	    }
	}
    }
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

void
muc_user_destroy_free (struct muc_user_destroy_t *data)
{
  if (data == NULL)
    return;
  if (data->fJid != NULL)
    {
      jid_free (data->fJid);
    }
  if (data->fReason != NULL)
    {
      free (data->fReason);
    }
  free (data);
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
	      elm->fReason = (char *) value;
	    }
	}
    }
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

void
muc_user_invite_free (struct muc_user_invite_t *data)
{
  if (data == NULL)
    return;
  if (data->fFrom != NULL)
    {
      jid_free (data->fFrom);
    }
  if (data->fTo != NULL)
    {
      jid_free (data->fTo);
    }
  if (data->fReason != NULL)
    {
      free (data->fReason);
    }
  free (data);
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
      elm->fNick = (char *) avalue;
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
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	  else if ((strcmp (name, "reason") == 0)
		   && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fReason = (char *) value;
	    }
	  else if ((strcmp (name, "continue") == 0)
		   && (strcmp (namespace, ns_muc_user) == 0))
	    {
	      elm->fContinue = true;
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	      continue;
	    }
	}
    }
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

void
muc_user_item_free (struct muc_user_item_t *data)
{
  if (data == NULL)
    return;
  if (data->fJid != NULL)
    {
      jid_free (data->fJid);
    }
  if (data->fNick != NULL)
    {
      free (data->fNick);
    }
  if (data->fActor.fJid != NULL)
    {
      jid_free (data->fActor.fJid);
    }
  if (data->fReason != NULL)
    {
      free (data->fReason);
    }
  if (data->fContinue)
    {
    }
  free (data);
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
	      muc_owner_configure_t *newel = xdata_x_decode (reader);
	      if (newel == NULL)
		return NULL;
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
  err = xdata_x_encode (writer, elm);
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
muc_owner_configure_free (muc_owner_configure_t * data)
{
  if (data == NULL)
    return;
  xdata_x_free (data);
  free (data);
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
	      if (elm->fItems == NULL)
		elm->fItems = array_new (sizeof (extension_t), 0);
	      array_append (elm->fItems, newel);
	    }
	}
    }
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
    int len = array_length (elm->fItems);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	extension_t *ext = array_get (elm->fItems, i);
	err = muc_admin_item_encode (writer, ext->data);
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
muc_admin_query_free (struct muc_admin_query_t *data)
{
  if (data == NULL)
    return;
  {
    int len = array_length (data->fItems);
    int i = 0;
    for (i = 0; i < len; i++)
      {
	muc_admin_item_free (array_get (data->fItems, i));
      }
    array_free (data->fItems);
  }
  free (data);
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
      elm->fNick = (char *) avalue;
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
	      if (xmlreader_skip_element (reader) == -1)
		return NULL;
	    }
	  else if ((strcmp (name, "reason") == 0)
		   && (strcmp (namespace, ns_muc_admin) == 0))
	    {
	      const char *value = xmlreader_text (reader);
	      if (reader->err != 0)
		return NULL;
	      elm->fReason = (char *) value;
	    }
	}
    }
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

void
muc_admin_item_free (struct muc_admin_item_t *data)
{
  if (data == NULL)
    return;
  if (data->fJid != NULL)
    {
      jid_free (data->fJid);
    }
  if (data->fNick != NULL)
    {
      free (data->fNick);
    }
  if (data->fActor.fJid != NULL)
    {
      jid_free (data->fActor.fJid);
    }
  if (data->fReason != NULL)
    {
      free (data->fReason);
    }
  free (data);
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
