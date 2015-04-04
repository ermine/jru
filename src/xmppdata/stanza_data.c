#include "stanza_data.h"

const char* ns_stanza = "urn:ietf:params:xml:ns:xmpp-stanzas";

struct stanza_error_t* stanza_error_decode(xmlTextReaderPtr reader) {
  struct stanza_error_t *elm = NULL;
 elm = malloc (sizeof (struct stanza_error_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "text") == 0) && (strcmp ((char*) namespace, ns_stanza) == 0)) {
    langstring_decode (reader, elm->fText);
  } // for end part 1
  else if (strcmp ((char*) namespace, ns_stanza) != 0) {
// element set
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fCondition.fExtra = (value);
      } // any end
  } // while end
  return elm;
}

int stanza_error_encode(xmlTextWriterPtr writer, struct stanza_error_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "error", BAD_CAST ns_stanza) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

enum stanza_error_condition_name_t enum_stanza_error_condition_name_from_string(const xmlChar *value) {
return 0;
}
xmlChar *enum_stanza_error_condition_name_to_string(enum stanza_error_condition_name_t value) {
return NULL;
}