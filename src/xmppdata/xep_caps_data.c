#include "xep_caps_data.h"

const char* ns_caps = "http://jabber.org/protocol/caps";

struct caps_caps_t* caps_caps_decode(xmlTextReaderPtr reader) {
  struct caps_caps_t *elm = NULL;
 elm = malloc (sizeof (struct caps_caps_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "ext");
  if (avalue != NULL) {
  elm->fExt = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "hash");
  if (avalue != NULL) {
  elm->fHash = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = (const char*)avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "ver");
  if (avalue != NULL) {
  elm->fVer = (const char*)avalue;
  }
  return elm;
}

int caps_caps_encode(xmlWriter_t* writer, struct caps_caps_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_caps, "c");
if (err != 0) return err;
if (elm->fExt != NULL) {
err = xmlwriter_attribute (writer, ns_caps, "ext", elm->fExt);
if (err != 0) return err;
}
if (elm->fHash != NULL) {
err = xmlwriter_attribute (writer, ns_caps, "hash", elm->fHash);
if (err != 0) return err;
}
if (elm->fNode != NULL) {
err = xmlwriter_attribute (writer, ns_caps, "node", elm->fNode);
if (err != 0) return err;
}
if (elm->fVer != NULL) {
err = xmlwriter_attribute (writer, ns_caps, "ver", elm->fVer);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

