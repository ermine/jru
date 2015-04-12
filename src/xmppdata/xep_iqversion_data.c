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
elm->fName = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "version") == 0) && (strcmp ((char*) namespace, ns_iqversion) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fVersion = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "os") == 0) && (strcmp ((char*) namespace, ns_iqversion) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fOs = (const char*) value;
  } // for end part 1
  } // while end
  return elm;
}

int iqversion_version_encode(xmlWriter_t* writer, struct iqversion_version_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_iqversion, "query");
if (err != 0) return err;
//here condition
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

