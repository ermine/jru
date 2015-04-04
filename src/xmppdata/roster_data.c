#include "roster_data.h"

const char* ns_roster = "jabber:iq:roster";

struct roster_roster_t* roster_roster_decode(xmlTextReaderPtr reader) {
  struct roster_roster_t *elm = NULL;
 elm = malloc (sizeof (struct roster_roster_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "ver");
  if (avalue != NULL) {
  elm->fVer = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) namespace, ns_roster) == 0) && (strcmp ((char*) name, "item") == 0)) {
//here
struct roster_item_t* newel = roster_item_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fItems, (void*) newel, EXTENSION_TYPE_ROSTER_ITEM);
  }
  } // while end
  return elm;
}

int roster_roster_encode(xmlTextWriterPtr writer, struct roster_roster_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "query", BAD_CAST ns_roster) == -1)
 return -1;
if (elm->fVer != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "ver", BAD_CAST "ns_roster", elm->fVer) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct roster_item_t* roster_item_decode(xmlTextReaderPtr reader) {
  struct roster_item_t *elm = NULL;
 elm = malloc (sizeof (struct roster_item_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "approved");
  if (avalue != NULL) {
elm->fApproved = strconv_parse_boolean(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "ask");
  if (avalue != NULL) {
//enum
elm->fAsk = enum_roster_item_ask_from_string(avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "jid");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fJid = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "subscription");
  if (avalue != NULL) {
//enum
elm->fSubscription = enum_roster_item_subscription_from_string(avalue);
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "group") == 0) && (strcmp ((char*) namespace, ns_roster) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
  llist_append((llist_t*)elm->fGroup, (void*) value, 0);
  } // for end part 1
  } // while end
  return elm;
}

int roster_item_encode(xmlTextWriterPtr writer, struct roster_item_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "item", BAD_CAST ns_roster) == -1)
 return -1;
if (elm->fApproved) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "approved", BAD_CAST "ns_roster", strconv_format_boolean(elm->fApproved)) == -1)
 return -1;
}
if (elm->fAsk != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "ask", BAD_CAST "ns_roster", BAD_CAST elm->fAsk) == -1)
 return -1;
}
if (elm->fJid != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "jid", BAD_CAST "ns_roster", BAD_CAST jid_to_string(elm->fJid)) == -1)
 return -1;
}
if (elm->fName != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "name", BAD_CAST "ns_roster", elm->fName) == -1)
 return -1;
}
if (elm->fSubscription != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "subscription", BAD_CAST "ns_roster", BAD_CAST elm->fSubscription) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum roster_item_ask_t enum_roster_item_ask_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_roster_item_ask_to_string(enum roster_item_ask_t value) {
return NULL;
}
enum roster_item_subscription_t enum_roster_item_subscription_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_roster_item_subscription_to_string(enum roster_item_subscription_t value) {
return NULL;
}
