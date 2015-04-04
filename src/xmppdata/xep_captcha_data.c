#include "xep_captcha_data.h"

const char* ns_captcha = "urn:xmpp:captcha";

struct captcha_captcha_t* captcha_captcha_decode(xmlTextReaderPtr reader) {
  struct captcha_captcha_t *elm = NULL;
 elm = malloc (sizeof (struct captcha_captcha_t*));
// element set
  return elm;
}

int captcha_captcha_encode(xmlTextWriterPtr writer, struct captcha_captcha_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "captcha", BAD_CAST ns_captcha) == -1)
 return -1;
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

