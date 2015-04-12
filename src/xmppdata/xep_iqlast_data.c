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
elm->fExtra = (const char*) value;
  return elm;
}

int iqlast_last_encode(xmlWriter_t* writer, struct iqlast_last_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_iqlast, "query");
if (err != 0) return err;
if (elm->fSeconds != NULL) {
err = xmlwriter_attribute (writer, ns_iqlast, "seconds", strconv_format_uint(elm->fSeconds));
if (err != 0) return err;
}
if (elm->fExtra != NULL) {
err = xmlwriter_text (writer, elm->fExtra);
if (err != 0) return err;
}
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

