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
  elm->fNode = (const char*)avalue;
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
  vlist_append ((vlist_t**)&elm->fIdentities, (void*) newel, EXTENSION_TYPE_DISCO_INFO_IDENTITY);
  }
  else if ((strcmp ((char*) namespace, ns_disco_info) == 0) && (strcmp ((char*) name, "feature") == 0)) {
//here
struct disco_info_feature_t* newel = disco_info_feature_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  vlist_append ((vlist_t**)&elm->fFeatures, (void*) newel, EXTENSION_TYPE_DISCO_INFO_FEATURE);
  }
  } // while end
  return elm;
}

int disco_info_info_encode(xmlWriter_t* writer, struct disco_info_info_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_disco_info, "query");
if (err != 0) return err;
if (elm->fNode != NULL) {
err = xmlwriter_attribute (writer, ns_disco_info, "node", elm->fNode);
if (err != 0) return err;
}
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct disco_info_identity_t* disco_info_identity_decode(xmlTextReaderPtr reader) {
  struct disco_info_identity_t *elm = NULL;
 elm = malloc (sizeof (struct disco_info_identity_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "category");
  if (avalue != NULL) {
  elm->fCategory = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "type");
  if (avalue != NULL) {
  elm->fType = (const char*)avalue;
  }
  return elm;
}

int disco_info_identity_encode(xmlWriter_t* writer, struct disco_info_identity_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_disco_info, "identity");
if (err != 0) return err;
if (elm->fCategory != NULL) {
err = xmlwriter_attribute (writer, ns_disco_info, "category", elm->fCategory);
if (err != 0) return err;
}
if (elm->fType != NULL) {
err = xmlwriter_attribute (writer, ns_disco_info, "type", elm->fType);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct disco_info_feature_t* disco_info_feature_decode(xmlTextReaderPtr reader) {
  struct disco_info_feature_t *elm = NULL;
 elm = malloc (sizeof (struct disco_info_feature_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "var");
  if (avalue != NULL) {
  elm->fVar = (const char*)avalue;
  }
  return elm;
}

int disco_info_feature_encode(xmlWriter_t* writer, struct disco_info_feature_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_disco_info, "feature");
if (err != 0) return err;
if (elm->fVar != NULL) {
err = xmlwriter_attribute (writer, ns_disco_info, "var", elm->fVar);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

