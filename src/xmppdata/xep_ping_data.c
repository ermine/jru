#include "xep_ping_data.h"

const char* ns_ping = "urn:xmpp:ping";

struct ping_ping_t* ping_ping_decode(xmlTextReaderPtr reader) {
  struct ping_ping_t *elm = NULL;
 elm = malloc (sizeof (struct ping_ping_t*));
if (xstream_skip(reader) != 0) {
    return NULL;
  }
  return elm;
}

int ping_ping_encode(xmlWriter_t* writer, struct ping_ping_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_ping, "ping");
if (err != 0) return err;
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

