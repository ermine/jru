#include "session_data.h"

const char* ns_session = "urn:ietf:params:xml:ns:xmpp-session";

struct session_session_t* session_session_decode(xmlTextReaderPtr reader) {
  struct session_session_t *elm = NULL;
 elm = malloc (sizeof (struct session_session_t*));
if (xstream_skip(reader) != 0) {
    return NULL;
  }
  return elm;
}

int session_session_encode(xmlWriter_t* writer, struct session_session_t* elm) {
int err = 0;
err = xmlwriter_start_element (writer, ns_session, "session");
if (err != 0) return err;
err = xmlwriter_end_element(writer);
if (err != 0) return err;
  return 0;
}

