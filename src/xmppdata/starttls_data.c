#include "starttls_data.h"

const char* ns_starttls = "urn:ietf:params:xml:ns:xmpp-tls";

struct starttls_starttls_t* starttls_starttls_decode(xmlTextReaderPtr reader) {
  struct starttls_starttls_t *elm = NULL;
 elm = malloc (sizeof (struct starttls_starttls_t*));
// element set
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
//while here0
const xmlChar* namespace = xmlTextReaderConstNamespaceUri (reader);
const xmlChar* name = xmlTextReaderConstName (reader);
 if ((strcmp ((char*) name, "required") == 0) && (strcmp ((char*) namespace, ns_starttls) == 0)) {
    elm->fRequired = true;
  if (xstream_skip (reader) != 0) {
    return NULL;
  }
  continue;
  } // for end part 1
  } // while end
  return elm;
}

int starttls_starttls_encode(xmlTextWriterPtr writer, struct starttls_starttls_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "starttls", BAD_CAST ns_starttls) == -1)
 return -1;
//here condition
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct starttls_proceed_t* starttls_proceed_decode(xmlTextReaderPtr reader) {
  struct starttls_proceed_t *elm = NULL;
 elm = malloc (sizeof (struct starttls_proceed_t*));
if (xstream_skip(reader) != 0) {
    return NULL;
  }
  return elm;
}

int starttls_proceed_encode(xmlTextWriterPtr writer, struct starttls_proceed_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "proceed", BAD_CAST ns_starttls) == -1)
 return -1;
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

struct starttls_failure_t* starttls_failure_decode(xmlTextReaderPtr reader) {
  struct starttls_failure_t *elm = NULL;
 elm = malloc (sizeof (struct starttls_failure_t*));
if (xstream_skip(reader) != 0) {
    return NULL;
  }
  return elm;
}

int starttls_failure_encode(xmlTextWriterPtr writer, struct starttls_failure_t* elm) {
if (xmlTextWriterStartElementNS(writer, NULL, BAD_CAST "failure", BAD_CAST ns_starttls) == -1)
 return -1;
if (xmlTextWriterEndElement(writer) == -1)
  return -1;
  return 0;
}

