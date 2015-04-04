#ifndef _XEP_IQVERSION_DATA_H_
#define  _XEP_IQVERSION_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_iqversion;


struct iqversion_version_t {
  const xmlChar * fName;
  const xmlChar * fVersion;
  const xmlChar * fOs;
};


struct iqversion_version_t* iqversion_version_decode(xmlTextReaderPtr reader);
int iqversion_version_encode(xmlTextWriterPtr writer, struct iqversion_version_t* data);
#endif
