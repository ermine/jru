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
elm->fTz = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "utc") == 0) && (strcmp ((char*) namespace, ns_time) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fUtc = (value);
  } // for end part 1
  } // while end
  return elm;
}

int time_time_encode(xmlTextWriterPtr writer, struct time_time_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "time", BAD_CAST ns_time) == -1)
 return -1;
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

