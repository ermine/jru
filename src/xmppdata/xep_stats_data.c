#include "xep_stats_data.h"

const char* ns_stats = "http://jabber.org/protocol/stats";

struct stats_stats_t* stats_stats_decode(xmlTextReaderPtr reader) {
  struct stats_stats_t *elm = NULL;
 elm = malloc (sizeof (struct stats_stats_t*));
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
const xmlChar* name = xmlTextReaderConstName (reader);
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
if ((strcmp ((char*) namespace, ns_stats) == 0) && (strcmp ((char*) name, "stat") == 0)) {
struct stats_stat_t* newel = stats_stat_decode(reader);
  if (newel == NULL) {
    return NULL;
  }
  llist_append((llist_t *)elm, (void*) newel, EXTENSION_TYPE_STATS_STAT);
}
}
  return elm;
}

int stats_stats_encode(xmlTextWriterPtr writer, struct stats_stats_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "query", BAD_CAST ns_stats) == -1)
 return -1;
llist_t* curr = (llist_t*)elm;
while (curr != NULL) {
if (stats_stat_encode(writer, curr->data) == -1)
 return -1;
curr = curr->next;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct stats_stat_t* stats_stat_decode(xmlTextReaderPtr reader) {
  struct stats_stat_t *elm = NULL;
 elm = malloc (sizeof (struct stats_stat_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "units");
  if (avalue != NULL) {
  elm->fUnits = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "value");
  if (avalue != NULL) {
  elm->fValue = avalue;
  }
  return elm;
}

int stats_stat_encode(xmlTextWriterPtr writer, struct stats_stat_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "stat", BAD_CAST ns_stats) == -1)
 return -1;
if (elm->fName != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "name", BAD_CAST "ns_stats", elm->fName) == -1)
 return -1;
}
if (elm->fUnits != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "units", BAD_CAST "ns_stats", elm->fUnits) == -1)
 return -1;
}
if (elm->fValue != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "value", BAD_CAST "ns_stats", elm->fValue) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

