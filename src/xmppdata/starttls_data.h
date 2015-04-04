#ifndef _STARTTLS_DATA_H_
#define  _STARTTLS_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_starttls;


struct starttls_starttls_t {
  boolean_t fRequired;
};


struct starttls_proceed_t {
};


struct starttls_failure_t {
};


struct starttls_starttls_t* starttls_starttls_decode(xmlTextReaderPtr reader);
int starttls_starttls_encode(xmlTextWriterPtr writer, struct starttls_starttls_t* data);
struct starttls_proceed_t* starttls_proceed_decode(xmlTextReaderPtr reader);
int starttls_proceed_encode(xmlTextWriterPtr writer, struct starttls_proceed_t* data);
struct starttls_failure_t* starttls_failure_decode(xmlTextReaderPtr reader);
int starttls_failure_encode(xmlTextWriterPtr writer, struct starttls_failure_t* data);
#endif
