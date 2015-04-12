#include "roster_data.h"

const char* ns_roster = "jabber:iq:roster";

struct roster_roster_t* roster_roster_decode(xmlTextReaderPtr reader) {
  struct roster_roster_t *elm = NULL;
 elm = malloc (sizeof (struct roster_roster_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "ver");
  if (avalue != NULL) {
  elm->fVer = (const char*)avalue;
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
  vlist_append ((vlist_t**)&elm->fItems, (void*) newel, EXTENSION_TYPE_ROSTER_ITEM);
  }
  } // while end
  return elm;
}

int roster_roster_encode(xmlWriter_t* writer, struct roster_roster_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_roster, "query");
if (err != 0) return err;
if (elm->fVer != NULL) {
err = xmlwriter_attribute (writer, ns_roster, "ver", elm->fVer);
if (err != 0) return err;
}
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
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
  elm->fName = (const char*)avalue;
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
  vlist_append ((vlist_t**) &elm->fGroup, (void*) value, 0);
  } // for end part 1
  } // while end
  return elm;
}

int roster_item_encode(xmlWriter_t* writer, struct roster_item_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_roster, "item");
if (err != 0) return err;
if (elm->fApproved) {
err = xmlwriter_attribute (writer, ns_roster, "approved", strconv_format_boolean(elm->fApproved));
if (err != 0) return err;
}
if (elm->fAsk != 0) {
err = xmlwriter_attribute (writer, ns_roster, "ask", enum_roster_item_ask_to_string(elm->fAsk));
if (err != 0) return err;
}
if (elm->fJid != NULL) {
err = xmlwriter_attribute (writer, ns_roster, "jid", jid_to_string(elm->fJid));
if (err != 0) return err;
}
if (elm->fName != NULL) {
err = xmlwriter_attribute (writer, ns_roster, "name", elm->fName);
if (err != 0) return err;
}
if (elm->fSubscription != 0) {
err = xmlwriter_attribute (writer, ns_roster, "subscription", enum_roster_item_subscription_to_string(elm->fSubscription));
if (err != 0) return err;
}
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

enum roster_item_ask_t enum_roster_item_ask_from_string(const xmlChar *value) {
return 0;
}
const char* enum_roster_item_ask_to_string(enum roster_item_ask_t value) {
return NULL;
}
enum roster_item_subscription_t enum_roster_item_subscription_from_string(const xmlChar *value) {
return 0;
}
const char* enum_roster_item_subscription_to_string(enum roster_item_subscription_t value) {
return NULL;
}
