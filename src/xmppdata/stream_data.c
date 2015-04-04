#include "stream_data.h"

const char* ns_stream = "http://etherx.jabber.org/streams";

struct stream_start_t* stream_start_decode(xmlTextReaderPtr reader) {
  struct stream_start_t *elm = NULL;
 elm = malloc (sizeof (struct stream_start_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "to");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fTo = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "from");
  if (avalue != NULL) {
  jid_t *jid = NULL;
  jid = jid_of_string ((const char*) avalue);
  elm->fFrom = jid;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "id");
  if (avalue != NULL) {
  elm->fId = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "version");
  if (avalue != NULL) {
  elm->fVersion = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "xml:lang");
  if (avalue != NULL) {
elm->fLang = avalue;
  }
  return elm;
}

int stream_start_encode(xmlTextWriterPtr writer, struct stream_start_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "stream", BAD_CAST ns_stream) == -1)
 return -1;
if (elm->fTo != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "to", BAD_CAST "ns_stream", BAD_CAST jid_to_string(elm->fTo)) == -1)
 return -1;
}
if (elm->fFrom != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "from", BAD_CAST "ns_stream", BAD_CAST jid_to_string(elm->fFrom)) == -1)
 return -1;
}
if (elm->fId != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "id", BAD_CAST "ns_stream", elm->fId) == -1)
 return -1;
}
if (elm->fVersion != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "version", BAD_CAST "ns_stream", elm->fVersion) == -1)
 return -1;
}
if (elm->fLang != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "xml", BAD_CAST "lang", BAD_CAST "http://www.w3.org/XML/1998/namespace", BAD_CAST elm->fLang) == -1)
 return -1;
}
  return 0;
}

struct stream_features_t* stream_features_decode(xmlTextReaderPtr reader) {
  struct stream_features_t *elm = NULL;
 elm = malloc (sizeof (struct stream_features_t*));
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
    extension_t *newel = xstream_extension_decode (reader);
    if (newel != NULL) {
      llist_append((llist_t*)elm, newel->data, newel->type);
free(newel);
     }
     ret = xmlTextReaderRead (reader);
}
  return elm;
}

int stream_features_encode(xmlTextWriterPtr writer, struct stream_features_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "features", BAD_CAST ns_stream) == -1)
 return -1;
llist_t* curr = (llist_t*)elm;
while (curr != NULL) {
if (xstream_extension_encode (writer, curr->data, curr->type) == -1)
 return -1;
curr = curr->next;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct stream_error_t* stream_error_decode(xmlTextReaderPtr reader) {
  struct stream_error_t *elm = NULL;
 elm = malloc (sizeof (struct stream_error_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "text") == 0) && (strcmp ((char*) namespace, ns_stream) == 0)) {
    langstring_decode (reader, elm->fText);
  } // for end part 1
  else if (strcmp ((char*) namespace, ns_stream) != 0) {
// element set
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fCondition.fExtra = (value);
      } // any end
  } // while end
  return elm;
}

int stream_error_encode(xmlTextWriterPtr writer, struct stream_error_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "error", BAD_CAST ns_stream) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum stream_error_condition_name_t enum_stream_error_condition_name_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_stream_error_condition_name_to_string(enum stream_error_condition_name_t value) {
return NULL;
}
