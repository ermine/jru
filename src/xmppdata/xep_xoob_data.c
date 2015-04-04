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
elm->fUrl = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "desc") == 0) && (strcmp ((char*) namespace, ns_xoob) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fDesc = (value);
  } // for end part 1
  } // while end
  return elm;
}

int xoob_x_encode(xmlTextWriterPtr writer, struct xoob_x_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "x", BAD_CAST ns_xoob) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

