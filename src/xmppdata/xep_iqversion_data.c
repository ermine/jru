#include "xep_iqversion_data.h"

const char* ns_iqversion = "jabber:iq:version";

struct iqversion_version_t* iqversion_version_decode(xmlTextReaderPtr reader) {
  struct iqversion_version_t *elm = NULL;
 elm = malloc (sizeof (struct iqversion_version_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "name") == 0) && (strcmp ((char*) namespace, ns_iqversion) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fName = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "version") == 0) && (strcmp ((char*) namespace, ns_iqversion) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fVersion = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "os") == 0) && (strcmp ((char*) namespace, ns_iqversion) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fOs = (value);
  } // for end part 1
  } // while end
  return elm;
}

int iqversion_version_encode(xmlTextWriterPtr writer, struct iqversion_version_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "query", BAD_CAST ns_iqversion) == -1)
 return -1;
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

