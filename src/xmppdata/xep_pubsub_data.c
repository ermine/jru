#include "xep_pubsub_data.h"

const char* ns_pubsub_event = "http://jabber.org/protocol/pubsub#event";

struct pubsub_event_event_t* pubsub_event_event_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_event_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_event_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char *) namespace, ns_pubsub_event) == 0) && (strcmp ((char*) name, "collection") == 0)) {
struct pubsub_event_collection_t* newel = pubsub_event_collection_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
//tut
//Choice
elm->type = EXTENSION_TYPE_PUBSUB_EVENT_COLLECTION;
elm->u->fCollection = newel;
  }
  else if ((strcmp ((char *) namespace, ns_pubsub_event) == 0) && (strcmp ((char*) name, "configuration") == 0)) {
struct pubsub_event_configuration_t* newel = pubsub_event_configuration_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
//tut
//Choice
elm->type = EXTENSION_TYPE_PUBSUB_EVENT_CONFIGURATION;
elm->u->fConfiguration = newel;
  }
  else if ((strcmp ((char *) namespace, ns_pubsub_event) == 0) && (strcmp ((char*) name, "delete") == 0)) {
struct pubsub_event_delete_t* newel = pubsub_event_delete_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
//tut
//Choice
elm->type = EXTENSION_TYPE_PUBSUB_EVENT_DELETE;
elm->u->fDelete = newel;
  }
  else if ((strcmp ((char *) namespace, ns_pubsub_event) == 0) && (strcmp ((char*) name, "items") == 0)) {
struct pubsub_event_items_t* newel = pubsub_event_items_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
//tut
//Choice
elm->type = EXTENSION_TYPE_PUBSUB_EVENT_ITEMS;
elm->u->fItems = newel;
  }
  else if ((strcmp ((char *) namespace, ns_pubsub_event) == 0) && (strcmp ((char*) name, "purge") == 0)) {
struct pubsub_event_purge_t* newel = pubsub_event_purge_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
//tut
//Choice
elm->type = EXTENSION_TYPE_PUBSUB_EVENT_PURGE;
elm->u->fPurge = newel;
  }
  else if ((strcmp ((char *) namespace, ns_pubsub_event) == 0) && (strcmp ((char*) name, "subscription") == 0)) {
struct pubsub_event_subscription_t* newel = pubsub_event_subscription_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
//tut
//Choice
elm->type = EXTENSION_TYPE_PUBSUB_EVENT_SUBSCRIPTION;
elm->u->fSubscription = newel;
  }
  } // while end
  return elm;
}

int pubsub_event_event_encode(xmlTextWriterPtr writer, struct pubsub_event_event_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "event", BAD_CAST ns_pubsub_event) == -1)
 return -1;
//here condition
if (elm->u != NULL) {
if (xstream_extension_encode(writer, (void*)elm->u, elm->type) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct pubsub_event_collection_t* pubsub_event_collection_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_collection_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_collection_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
  if  (strcmp ((char*) namespace, ns_pubsub_event) != 0) {
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fType.fNode = avalue;
  }
      } // any end
  } // while end
  return elm;
}

int pubsub_event_collection_encode(xmlTextWriterPtr writer, struct pubsub_event_collection_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "collection", BAD_CAST ns_pubsub_event) == -1)
 return -1;
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_pubsub_event", elm->fNode) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct pubsub_event_configuration_t* pubsub_event_configuration_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_configuration_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_configuration_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
{
 if ((strcmp ((char*) namespace, "jabber:x:data") == 0) && (strcmp ((char *) name, "x") == 0)) {
struct xdata_x_t* newel = xdata_x_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
elm->fXdata = newel;
}
} // end here
  } // while end
  return elm;
}

int pubsub_event_configuration_encode(xmlTextWriterPtr writer, struct pubsub_event_configuration_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "configuration", BAD_CAST ns_pubsub_event) == -1)
 return -1;
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_pubsub_event", elm->fNode) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct pubsub_event_delete_t* pubsub_event_delete_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_delete_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_delete_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "redirect") == 0) && (strcmp ((char*) namespace, ns_pubsub_event) == 0)) {
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "url");
  if (avalue != NULL) {
  elm->fRedirect.fUrl = avalue;
  }
  } // for end part 1
  } // while end
  return elm;
}

int pubsub_event_delete_encode(xmlTextWriterPtr writer, struct pubsub_event_delete_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "delete", BAD_CAST ns_pubsub_event) == -1)
 return -1;
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_pubsub_event", elm->fNode) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct pubsub_event_items_t* pubsub_event_items_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_items_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_items_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) namespace, ns_pubsub_event) == 0) && (strcmp ((char*) name, "item") == 0)) {
//here
struct pubsub_event_item_t* newel = pubsub_event_item_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fItems, (void*) newel, EXTENSION_TYPE_PUBSUB_EVENT_ITEM);
  }
  else if ((strcmp ((char*) namespace, ns_pubsub_event) == 0) && (strcmp ((char*) name, "retract") == 0)) {
//here
struct pubsub_event_retract_t* newel = pubsub_event_retract_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fRetracts, (void*) newel, EXTENSION_TYPE_PUBSUB_EVENT_RETRACT);
  }
  } // while end
  return elm;
}

int pubsub_event_items_encode(xmlTextWriterPtr writer, struct pubsub_event_items_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "items", BAD_CAST ns_pubsub_event) == -1)
 return -1;
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_pubsub_event", elm->fNode) == -1)
 return -1;
}
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct pubsub_event_item_t* pubsub_event_item_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_item_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_item_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "id");
  if (avalue != NULL) {
  elm->fId = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "publisher");
  if (avalue != NULL) {
  elm->fPublisher = avalue;
  }
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
if (strcmp ((char*) namespace, ns_pubsub_event) != 0) {
// zzz
  extension_t* newel = xstream_extension_decode (reader);
  if (newel == NULL) {
if (xstream_skip(reader) != 0) {
    return NULL;
  }
} else {
elm->fEvent = newel;
}
} // end of if strcmp
  } // while end
  return elm;
}

int pubsub_event_item_encode(xmlTextWriterPtr writer, struct pubsub_event_item_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "item", BAD_CAST ns_pubsub_event) == -1)
 return -1;
if (elm->fId != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "id", BAD_CAST "ns_pubsub_event", elm->fId) == -1)
 return -1;
}
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_pubsub_event", elm->fNode) == -1)
 return -1;
}
if (elm->fPublisher != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "publisher", BAD_CAST "ns_pubsub_event", elm->fPublisher) == -1)
 return -1;
}
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct pubsub_event_purge_t* pubsub_event_purge_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_purge_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_purge_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = avalue;
  }
  return elm;
}

int pubsub_event_purge_encode(xmlTextWriterPtr writer, struct pubsub_event_purge_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "purge", BAD_CAST ns_pubsub_event) == -1)
 return -1;
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_pubsub_event", elm->fNode) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct pubsub_event_retract_t* pubsub_event_retract_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_retract_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_retract_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "id");
  if (avalue != NULL) {
  elm->fId = avalue;
  }
  return elm;
}

int pubsub_event_retract_encode(xmlTextWriterPtr writer, struct pubsub_event_retract_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "retract", BAD_CAST ns_pubsub_event) == -1)
 return -1;
if (elm->fId != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "id", BAD_CAST "ns_pubsub_event", elm->fId) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct pubsub_event_subscription_t* pubsub_event_subscription_decode(xmlTextReaderPtr reader) {
  struct pubsub_event_subscription_t *elm = NULL;
 elm = malloc (sizeof (struct pubsub_event_subscription_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "expiry");
  if (avalue != NULL) {
elm->fExpiry = datetime_parse (avalue);
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "jid");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fJid = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "subid");
  if (avalue != NULL) {
  elm->fSubid = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "subscription");
  if (avalue != NULL) {
//enum
elm->fSubscription = enum_pubsub_event_subscription_subscription_from_string(avalue);
  }
  return elm;
}

int pubsub_event_subscription_encode(xmlTextWriterPtr writer, struct pubsub_event_subscription_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "subscription", BAD_CAST ns_pubsub_event) == -1)
 return -1;
if (elm->fExpiry != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "expiry", BAD_CAST "ns_pubsub_event", datetime_to_string(elm->fExpiry)) == -1)
 return -1;
}
if (elm->fJid != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "jid", BAD_CAST "ns_pubsub_event", BAD_CAST jid_to_string(elm->fJid)) == -1)
 return -1;
}
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_pubsub_event", elm->fNode) == -1)
 return -1;
}
if (elm->fSubid != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "subid", BAD_CAST "ns_pubsub_event", elm->fSubid) == -1)
 return -1;
}
if (elm->fSubscription != 0) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "subscription", BAD_CAST "ns_pubsub_event", BAD_CAST elm->fSubscription) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum pubsub_event_collection_type_type_t enum_pubsub_event_collection_type_type_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_pubsub_event_collection_type_type_to_string(enum pubsub_event_collection_type_type_t value) {
return NULL;
}
enum pubsub_event_subscription_subscription_t enum_pubsub_event_subscription_subscription_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_pubsub_event_subscription_subscription_to_string(enum pubsub_event_subscription_subscription_t value) {
return NULL;
}
