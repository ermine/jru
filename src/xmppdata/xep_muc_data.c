#include "xep_muc_data.h"

const char* ns_muc = "http://jabber.org/protocol/muc";
const char* ns_muc_user = "http://jabber.org/protocol/muc#user";
const char* ns_muc_owner = "http://jabber.org/protocol/muc#owner";
const char* ns_muc_admin = "http://jabber.org/protocol/muc#admin";

struct muc_enter_t* muc_enter_decode(xmlTextReaderPtr reader) {
  struct muc_enter_t *elm = NULL;
 elm = malloc (sizeof (struct muc_enter_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "history") == 0) && (strcmp ((char*) namespace, ns_muc) == 0)) {
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "maxchars");
  if (avalue != NULL) {
  elm->fHistory.fMaxchars = strconv_parse_int (avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "maxstanzas");
  if (avalue != NULL) {
  elm->fHistory.fMaxstanzas = strconv_parse_int (avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "seconds");
  if (avalue != NULL) {
  elm->fHistory.fSeconds = strconv_parse_int (avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "since");
  if (avalue != NULL) {
elm->fHistory.fSince = datetime_parse (avalue);
  }
  } // for end part 1
  else if ((strcmp ((char*) name, "password") == 0) && (strcmp ((char*) namespace, ns_muc) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fPassword = (value);
  } // for end part 1
  } // while end
  return elm;
}

int muc_enter_encode(xmlTextWriterPtr writer, struct muc_enter_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "x", BAD_CAST ns_muc) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct muc_user_action_t* muc_user_action_decode(xmlTextReaderPtr reader) {
  struct muc_user_action_t *elm = NULL;
 elm = malloc (sizeof (struct muc_user_action_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) namespace, ns_muc_user) == 0) && (strcmp ((char*) name, "invite") == 0)) {
//here
struct muc_user_invite_t* newel = muc_user_invite_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fInvite, (void*) newel, EXTENSION_TYPE_MUC_USER_INVITE);
  }
  else if ((strcmp ((char*) name, "password") == 0) && (strcmp ((char*) namespace, ns_muc_user) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fPassword = (value);
  } // for end part 1
  else if ((strcmp ((char*) namespace, ns_muc_user) == 0) && (strcmp ((char*) name, "status") == 0)) {
//here
struct muc_user_status_t* newel = muc_user_status_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fStatus, (void*) newel, EXTENSION_TYPE_MUC_USER_STATUS);
  }
  } // while end
  return elm;
}

int muc_user_action_encode(xmlTextWriterPtr writer, struct muc_user_action_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "x", BAD_CAST ns_muc_user) == -1)
 return -1;
//here condition
//here condition
//here condition
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct muc_user_status_t* muc_user_status_decode(xmlTextReaderPtr reader) {
  struct muc_user_status_t *elm = NULL;
 elm = malloc (sizeof (struct muc_user_status_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "code");
  if (avalue != NULL) {
  elm->fCode = strconv_parse_int (avalue);
  }
  return elm;
}

int muc_user_status_encode(xmlTextWriterPtr writer, struct muc_user_status_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "status", BAD_CAST ns_muc_user) == -1)
 return -1;
if (elm->fCode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "code", BAD_CAST "ns_muc_user", strconv_format_int(elm->fCode)) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct muc_user_decline_t* muc_user_decline_decode(xmlTextReaderPtr reader) {
  struct muc_user_decline_t *elm = NULL;
 elm = malloc (sizeof (struct muc_user_decline_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "from");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fFrom = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "to");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fTo = jid;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "reason") == 0) && (strcmp ((char*) namespace, ns_muc_user) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fReason = (value);
  } // for end part 1
  } // while end
  return elm;
}

int muc_user_decline_encode(xmlTextWriterPtr writer, struct muc_user_decline_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "decline", BAD_CAST ns_muc_user) == -1)
 return -1;
if (elm->fFrom != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "from", BAD_CAST "ns_muc_user", BAD_CAST jid_to_string(elm->fFrom)) == -1)
 return -1;
}
if (elm->fTo != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "to", BAD_CAST "ns_muc_user", BAD_CAST jid_to_string(elm->fTo)) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct muc_user_destroy_t* muc_user_destroy_decode(xmlTextReaderPtr reader) {
  struct muc_user_destroy_t *elm = NULL;
 elm = malloc (sizeof (struct muc_user_destroy_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "jid");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fJid = jid;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "reason") == 0) && (strcmp ((char*) namespace, ns_muc_user) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fReason = (value);
  } // for end part 1
  } // while end
  return elm;
}

int muc_user_destroy_encode(xmlTextWriterPtr writer, struct muc_user_destroy_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "destroy", BAD_CAST ns_muc_user) == -1)
 return -1;
if (elm->fJid != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "jid", BAD_CAST "ns_muc_user", BAD_CAST jid_to_string(elm->fJid)) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct muc_user_invite_t* muc_user_invite_decode(xmlTextReaderPtr reader) {
  struct muc_user_invite_t *elm = NULL;
 elm = malloc (sizeof (struct muc_user_invite_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "from");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fFrom = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "to");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fTo = jid;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "reason") == 0) && (strcmp ((char*) namespace, ns_muc_user) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fReason = (value);
  } // for end part 1
  } // while end
  return elm;
}

int muc_user_invite_encode(xmlTextWriterPtr writer, struct muc_user_invite_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "invite", BAD_CAST ns_muc_user) == -1)
 return -1;
if (elm->fFrom != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "from", BAD_CAST "ns_muc_user", BAD_CAST jid_to_string(elm->fFrom)) == -1)
 return -1;
}
if (elm->fTo != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "to", BAD_CAST "ns_muc_user", BAD_CAST jid_to_string(elm->fTo)) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct muc_user_item_t* muc_user_item_decode(xmlTextReaderPtr reader) {
  struct muc_user_item_t *elm = NULL;
 elm = malloc (sizeof (struct muc_user_item_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "affiliation");
  if (avalue != NULL) {
//enum
elm->fAffiliation = enum_muc_user_item_affiliation_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "jid");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fJid = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "nick");
  if (avalue != NULL) {
  elm->fNick = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "role");
  if (avalue != NULL) {
//enum
elm->fRole = enum_muc_user_item_role_from_string(avalue);
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "actor") == 0) && (strcmp ((char*) namespace, ns_muc_user) == 0)) {
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "jid");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fActor.fJid = jid;
  }
  } // for end part 1
  else if ((strcmp ((char*) name, "reason") == 0) && (strcmp ((char*) namespace, ns_muc_user) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fReason = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "continue") == 0) && (strcmp ((char*) namespace, ns_muc_user) == 0)) {
    elm->fContinue = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  } // while end
  return elm;
}

int muc_user_item_encode(xmlTextWriterPtr writer, struct muc_user_item_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "item", BAD_CAST ns_muc_user) == -1)
 return -1;
if (elm->fAffiliation != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "affiliation", BAD_CAST "ns_muc_user", BAD_CAST elm->fAffiliation) == -1)
 return -1;
}
if (elm->fJid != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "jid", BAD_CAST "ns_muc_user", BAD_CAST jid_to_string(elm->fJid)) == -1)
 return -1;
}
if (elm->fNick != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "nick", BAD_CAST "ns_muc_user", elm->fNick) == -1)
 return -1;
}
if (elm->fRole != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "role", BAD_CAST "ns_muc_user", BAD_CAST elm->fRole) == -1)
 return -1;
}
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum muc_user_item_affiliation_t enum_muc_user_item_affiliation_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_muc_user_item_affiliation_to_string(enum muc_user_item_affiliation_t value) {
return NULL;
}
enum muc_user_item_role_t enum_muc_user_item_role_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_muc_user_item_role_to_string(enum muc_user_item_role_t value) {
return NULL;
}
muc_owner_configure_t* muc_owner_configure_decode(xmlTextReaderPtr reader) {
  muc_owner_configure_t *elm = NULL;
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
  if (xmlTextReaderNodeType (reader) == 15) {
    break;
  }
 const xmlChar* name = xmlTextReaderConstName (reader);
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
if ((strcmp ((char*) namespace, "jabber:x:data") == 0) && (strcmp ((char *) name, "x") == 0)) {
  extension_t* newel = xstream_extension_decode (reader);
  if (newel == NULL) {
    return NULL;
  }
// here?
elm = (muc_owner_configure_t*)(newel);
} else {
if (xstream_skip(reader) != 0) {
    return NULL;
  }
}
}
  return elm;
}

int muc_owner_configure_encode(xmlTextWriterPtr writer, muc_owner_configure_t* elm) {
  return 0;
}

struct muc_admin_query_t* muc_admin_query_decode(xmlTextReaderPtr reader) {
  struct muc_admin_query_t *elm = NULL;
 elm = malloc (sizeof (struct muc_admin_query_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) namespace, ns_muc_admin) == 0) && (strcmp ((char*) name, "item") == 0)) {
//here
struct muc_admin_item_t* newel = muc_admin_item_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fItems, (void*) newel, EXTENSION_TYPE_MUC_ADMIN_ITEM);
  }
  } // while end
  return elm;
}

int muc_admin_query_encode(xmlTextWriterPtr writer, struct muc_admin_query_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "query", BAD_CAST ns_muc_admin) == -1)
 return -1;
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct muc_admin_item_t* muc_admin_item_decode(xmlTextReaderPtr reader) {
  struct muc_admin_item_t *elm = NULL;
 elm = malloc (sizeof (struct muc_admin_item_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "affiliation");
  if (avalue != NULL) {
//enum
elm->fAffiliation = enum_muc_admin_item_affiliation_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "jid");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fJid = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "nick");
  if (avalue != NULL) {
  elm->fNick = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "role");
  if (avalue != NULL) {
//enum
elm->fRole = enum_muc_admin_item_role_from_string(avalue);
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "actor") == 0) && (strcmp ((char*) namespace, ns_muc_admin) == 0)) {
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "jid");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fActor.fJid = jid;
  }
  } // for end part 1
  else if ((strcmp ((char*) name, "reason") == 0) && (strcmp ((char*) namespace, ns_muc_admin) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fReason = (value);
  } // for end part 1
  } // while end
  return elm;
}

int muc_admin_item_encode(xmlTextWriterPtr writer, struct muc_admin_item_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "item", BAD_CAST ns_muc_admin) == -1)
 return -1;
if (elm->fAffiliation != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "affiliation", BAD_CAST "ns_muc_admin", BAD_CAST elm->fAffiliation) == -1)
 return -1;
}
if (elm->fJid != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "jid", BAD_CAST "ns_muc_admin", BAD_CAST jid_to_string(elm->fJid)) == -1)
 return -1;
}
if (elm->fNick != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "nick", BAD_CAST "ns_muc_admin", elm->fNick) == -1)
 return -1;
}
if (elm->fRole != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "role", BAD_CAST "ns_muc_admin", BAD_CAST elm->fRole) == -1)
 return -1;
}
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum muc_admin_item_affiliation_t enum_muc_admin_item_affiliation_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_muc_admin_item_affiliation_to_string(enum muc_admin_item_affiliation_t value) {
return NULL;
}
enum muc_admin_item_role_t enum_muc_admin_item_role_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_muc_admin_item_role_to_string(enum muc_admin_item_role_t value) {
return NULL;
}
