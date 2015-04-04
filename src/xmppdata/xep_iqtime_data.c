#include "xep_iqtime_data.h"

const char* ns_iqtime = "jabber:iq:time";

struct iqtime_time_t* iqtime_time_decode(xmlTextReaderPtr reader) {
  struct iqtime_time_t *elm = NULL;
 elm = malloc (sizeof (struct iqtime_time_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "utc") == 0) && (strcmp ((char*) namespace, ns_iqtime) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fUtc = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "tz") == 0) && (strcmp ((char*) namespace, ns_iqtime) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fTz = (value);
  } // for end part 1
  else if ((strcmp ((char*) name, "display") == 0) && (strcmp ((char*) namespace, ns_iqtime) == 0)) {
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fDisplay = (value);
  } // for end part 1
  } // while end
  return elm;
}

int iqtime_time_encode(xmlTextWriterPtr writer, struct iqtime_time_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "query", BAD_CAST ns_iqtime) == -1)
 return -1;
//here condition
//here condition
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

