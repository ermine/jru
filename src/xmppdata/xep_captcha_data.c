#include "xep_captcha_data.h"

const char* ns_captcha = "urn:xmpp:captcha";

struct captcha_captcha_t* captcha_captcha_decode(xmlTextReaderPtr reader) {
  struct captcha_captcha_t *elm = NULL;
 elm = malloc (sizeof (struct captcha_captcha_t*));
// element set
  return elm;
}

int captcha_captcha_encode(xmlWriter_t* writer, struct captcha_captcha_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_captcha, "captcha");
if (err != 0) return err;
//here condition
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

