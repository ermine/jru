#include "xep_disco_data.h"

const char* ns_disco_info = "http://jabber.org/protocol/disco#info";
const char* ns_disco_items = "http://jabber.org/protocol/disco#items";

struct disco_info_info_t* disco_info_info_decode(xmlTextReaderPtr reader) {
  struct disco_info_info_t *elm = NULL;
 elm = malloc (sizeof (struct disco_info_info_t*));
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
 if ((strcmp ((char*) namespace, ns_disco_info) == 0) && (strcmp ((char*) name, "identity") == 0)) {
//here
struct disco_info_identity_t* newel = disco_info_identity_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fIdentities, (void*) newel, EXTENSION_TYPE_DISCO_INFO_IDENTITY);
  }
  else if ((strcmp ((char*) namespace, ns_disco_info) == 0) && (strcmp ((char*) name, "feature") == 0)) {
//here
struct disco_info_feature_t* newel = disco_info_feature_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t*)elm->fFeatures, (void*) newel, EXTENSION_TYPE_DISCO_INFO_FEATURE);
  }
  } // while end
  return elm;
}

int disco_info_info_encode(xmlTextWriterPtr writer, struct disco_info_info_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "query", BAD_CAST ns_disco_info) == -1)
 return -1;
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_disco_info", elm->fNode) == -1)
 return -1;
}
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct disco_info_identity_t* disco_info_identity_decode(xmlTextReaderPtr reader) {
  struct disco_info_identity_t *elm = NULL;
 elm = malloc (sizeof (struct disco_info_identity_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "category");
  if (avalue != NULL) {
  elm->fCategory = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
  elm->fType = avalue;
  }
  return elm;
}

int disco_info_identity_encode(xmlTextWriterPtr writer, struct disco_info_identity_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "identity", BAD_CAST ns_disco_info) == -1)
 return -1;
if (elm->fCategory != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "category", BAD_CAST "ns_disco_info", elm->fCategory) == -1)
 return -1;
}
if (elm->fType != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "type", BAD_CAST "ns_disco_info", elm->fType) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct disco_info_feature_t* disco_info_feature_decode(xmlTextReaderPtr reader) {
  struct disco_info_feature_t *elm = NULL;
 elm = malloc (sizeof (struct disco_info_feature_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "var");
  if (avalue != NULL) {
  elm->fVar = avalue;
  }
  return elm;
}

int disco_info_feature_encode(xmlTextWriterPtr writer, struct disco_info_feature_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "feature", BAD_CAST ns_disco_info) == -1)
 return -1;
if (elm->fVar != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "var", BAD_CAST "ns_disco_info", elm->fVar) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

