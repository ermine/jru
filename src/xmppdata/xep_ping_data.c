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

int ping_ping_encode(xmlTextWriterPtr writer, struct ping_ping_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "ping", BAD_CAST ns_ping) == -1)
 return -1;
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

