#include "xep_caps_data.h"

const char* ns_caps = "http://jabber.org/protocol/caps";

struct caps_caps_t* caps_caps_decode(xmlTextReaderPtr reader) {
  struct caps_caps_t *elm = NULL;
 elm = malloc (sizeof (struct caps_caps_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "ext");
  if (avalue != NULL) {
  elm->fExt = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "hash");
  if (avalue != NULL) {
  elm->fHash = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "node");
  if (avalue != NULL) {
  elm->fNode = avalue;
  }
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "ver");
  if (avalue != NULL) {
  elm->fVer = avalue;
  }
  return elm;
}

int caps_caps_encode(xmlTextWriterPtr writer, struct caps_caps_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "c", BAD_CAST ns_caps) == -1)
 return -1;
if (elm->fExt != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "ext", BAD_CAST "ns_caps", elm->fExt) == -1)
 return -1;
}
if (elm->fHash != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "hash", BAD_CAST "ns_caps", elm->fHash) == -1)
 return -1;
}
if (elm->fNode != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "node", BAD_CAST "ns_caps", elm->fNode) == -1)
 return -1;
}
if (elm->fVer != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "ver", BAD_CAST "ns_caps", elm->fVer) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

