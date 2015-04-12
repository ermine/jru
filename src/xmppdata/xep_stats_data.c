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
  vlist_append ((vlist_t **) &elm, (void*) newel, EXTENSION_TYPE_STATS_STAT);
}
}
  return elm;
}

int stats_stats_encode(xmlWriter_t* writer, struct stats_stats_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_stats, "query");
if (err != 0) return err;
vlist_t* curr = (vlist_t*)elm;
while (curr != NULL) {
if (stats_stat_encode(writer, curr->data) == -1)
 return -1;
curr = curr->next;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

struct stats_stat_t* stats_stat_decode(xmlTextReaderPtr reader) {
  struct stats_stat_t *elm = NULL;
 elm = malloc (sizeof (struct stats_stat_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "name");
  if (avalue != NULL) {
  elm->fName = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "units");
  if (avalue != NULL) {
  elm->fUnits = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "value");
  if (avalue != NULL) {
  elm->fValue = (const char*)avalue;
  }
  return elm;
}

int stats_stat_encode(xmlWriter_t* writer, struct stats_stat_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_stats, "stat");
if (err != 0) return err;
if (elm->fName != NULL) {
err = xmlwriter_attribute (writer, ns_stats, "name", elm->fName);
if (err != 0) return err;
}
if (elm->fUnits != NULL) {
err = xmlwriter_attribute (writer, ns_stats, "units", elm->fUnits);
if (err != 0) return err;
}
if (elm->fValue != NULL) {
err = xmlwriter_attribute (writer, ns_stats, "value", elm->fValue);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

