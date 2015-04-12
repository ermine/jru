#include "xep_xoob_data.h"

const char* ns_xoob = "jabber:x:oob";

struct xoob_x_t* xoob_x_decode(xmlTextReaderPtr reader) {
  struct xoob_x_t *elm = NULL;
 elm = malloc (sizeof (struct xoob_x_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "url") == 0) && (strcmp ((char*) namespace, ns_xoob) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fUrl = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "desc") == 0) && (strcmp ((char*) namespace, ns_xoob) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fDesc = (const char*) value;
  } // for end part 1
  } // while end
  return elm;
}

int xoob_x_encode(xmlWriter_t* writer, struct xoob_x_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_xoob, "x");
if (err != 0) return err;
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

