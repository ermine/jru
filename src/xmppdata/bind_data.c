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
elm->fResource = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "jid") == 0) && (strcmp ((char*) namespace, ns_bind) == 0)) {
const xmlChar* s = xmlTextReaderConstValue(reader);
  jid_t *jid = jid_of_string((const char*) s);
elm->fJid = jid;
  } // for end part 1
  } // while end
  return elm;
}

int bind_bind_encode(xmlWriter_t* writer, struct bind_bind_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_bind, "bind");
if (err != 0) return err;
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

