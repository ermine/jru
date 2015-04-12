#include "xep_iqregister_data.h"

const char* ns_iqregister = "jabber:iq:register";

struct iqregister_query_t* iqregister_query_decode(xmlTextReaderPtr reader) {
  struct iqregister_query_t *elm = NULL;
 elm = malloc (sizeof (struct iqregister_query_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "registered") == 0)) {
if (xstream_skip(reader) != 0) {
    return NULL;
  }
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "instructions") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fInstructions = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "username") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fUsername = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "nick") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fNick = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "password") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fPassword = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "name") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fName = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "first") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fFirst = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "last") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fLast = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "email") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fEmail = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "address") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fAddress = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "city") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fCity = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "state") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fState = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "zip") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fZip = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "phone") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fPhone = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "url") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fUrl = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "date") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fDate = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "misc") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fMisc = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "text") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fText = (const char*) value;
  }
  else if ((strcmp ((char*) namespace, ns_iqregister) == 0) && (strcmp ((char*) name, "key") == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fFields.fKey = (const char*) value;
  }
  else if ((strcmp ((char*) name, "remove") == 0) && (strcmp ((char*) namespace, ns_iqregister) == 0)) {
    elm->fRemove = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
else  if ((strcmp ((char*) namespace, "jabber:x:data") == 0) && (strcmp ((char *) name, "x") == 0)) {
struct xdata_x_t* newel = xdata_x_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
elm->fXdata = newel;
}
else  if ((strcmp ((char*) namespace, "jabber:x:oob") == 0) && (strcmp ((char *) name, "x") == 0)) {
struct xoob_x_t* newel = xoob_x_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
elm->fXoob = newel;
}
  } // while end
  return elm;
}

int iqregister_query_encode(xmlWriter_t* writer, struct iqregister_query_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_iqregister, "query");
if (err != 0) return err;
//here condition
//here condition
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

