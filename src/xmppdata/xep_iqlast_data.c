#include "xep_iqlast_data.h"

const char* ns_iqlast = "jabber:iq:last";

struct iqlast_last_t* iqlast_last_decode(xmlTextReaderPtr reader) {
  struct iqlast_last_t *elm = NULL;
 elm = malloc (sizeof (struct iqlast_last_t*));
// element set
  const xmlChar *avalue;
  avalue = xmlTextReaderGetAttribute (reader, (const xmlChar*) "seconds");
  if (avalue != NULL) {
  elm->fSeconds = strconv_parse_uint (avalue);
  }
const xmlChar *value = xmlTextReaderConstValue (reader);
elm->fExtra = (value);
  return elm;
}

int iqlast_last_encode(xmlTextWriterPtr writer, struct iqlast_last_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "query", BAD_CAST ns_iqlast) == -1)
 return -1;
if (elm->fSeconds != NULL) {
if (xmlTextWriterWriteAttributeNS(writer, BAD_CAST "", BAD_CAST "seconds", BAD_CAST "ns_iqlast", strconv_format_uint(elm->fSeconds)) == -1)
 return -1;
}
if (elm->fExtra != NULL) {
if (xmlTextWriterWriteCDATA(writer, elm->fExtra) == -1)
 return -1;
}
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

