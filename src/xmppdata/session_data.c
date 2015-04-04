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

int session_session_encode(xmlTextWriterPtr writer, struct session_session_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "session", BAD_CAST ns_session) == -1)
 return -1;
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

