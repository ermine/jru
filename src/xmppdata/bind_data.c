#include "bind_data.h"

const char* ns_bind = "urn:ietf:params:xml:ns:xmpp-bind";

struct bind_bind_t* bind_bind_decode(xmlTextReaderPtr reader) {
  struct bind_bind_t *elm = NULL;
 elm = malloc (sizeof (struct bind_bind_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "resource") == 0) && (strcmp ((char*) namespace, ns_bind) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fResource = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "jid") == 0) && (strcmp ((char*) namespace, ns_bind) == 0)) {
const xmlChar* s = xmlTextReaderConstValue(reader);
  jid_t *jid = jid_of_string((const char*) s);
elm->fJid = jid;
  } // for end part 1
  } // while end
  return elm;
}

int bind_bind_encode(xmlTextWriterPtr writer, struct bind_bind_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "bind", BAD_CAST ns_bind) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

