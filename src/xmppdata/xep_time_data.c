#include "xep_time_data.h"

const char* ns_time = "urn:xmpp:time";

struct time_time_t* time_time_decode(xmlTextReaderPtr reader) {
  struct time_time_t *elm = NULL;
 elm = malloc (sizeof (struct time_time_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "tz") == 0) && (strcmp ((char*) namespace, ns_time) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fTz = (const char*) value;
  } // for end part 1
  else if ((strcmp ((char*) name, "utc") == 0) && (strcmp ((char*) namespace, ns_time) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fUtc = (const char*) value;
  } // for end part 1
  } // while end
  return elm;
}

int time_time_encode(xmlWriter_t* writer, struct time_time_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_time, "time");
if (err != 0) return err;
//here condition
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

