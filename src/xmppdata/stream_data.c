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
  elm->fId = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "version");
  if (avalue != NULL) {
  elm->fVersion = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "lang");
  if (avalue != NULL) {
elm->fLang = (const char*) avalue;
  }
  return elm;
}

int stream_start_encode(xmlWriter_t* writer, struct stream_start_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_stream, "stream");
if (err != 0) return err;
if (elm->fTo != NULL) {
err = xmlwriter_attribute (writer, ns_stream, "to", jid_to_string(elm->fTo));
if (err != 0) return err;
}
if (elm->fFrom != NULL) {
err = xmlwriter_attribute (writer, ns_stream, "from", jid_to_string(elm->fFrom));
if (err != 0) return err;
}
if (elm->fId != NULL) {
err = xmlwriter_attribute (writer, ns_stream, "id", elm->fId);
if (err != 0) return err;
}
if (elm->fVersion != NULL) {
err = xmlwriter_attribute (writer, ns_stream, "version", elm->fVersion);
if (err != 0) return err;
}
if (elm->fLang != NULL) {
err = xmlwriter_attribute (writer, ns_xml, "lang", elm->fLang);
if (err != 0) return err;
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
      vlist_append((vlist_t**) &elm, newel->data, newel->type);
free(newel);
     }
     ret = xmlTextReaderRead (reader);
}
  return elm;
}

int stream_features_encode(xmlWriter_t* writer, struct stream_features_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_stream, "features");
if (err != 0) return err;
vlist_t* curr = (vlist_t*)elm;
while (curr != NULL) {
if (xstream_extension_encode (writer, curr->data, curr->type) == -1)
 return -1;
curr = curr->next;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
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
elm->fCondition.fExtra = (const char*) value;
      } // any end
  } // while end
  return elm;
}

int stream_error_encode(xmlWriter_t* writer, struct stream_error_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_stream, "error");
if (err != 0) return err;
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

enum stream_error_condition_name_t enum_stream_error_condition_name_from_string(const xmlChar *value) {
return 0;
}
const char* enum_stream_error_condition_name_to_string(enum stream_error_condition_name_t value) {
return NULL;
}
