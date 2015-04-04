#ifndef _XEP_CAPS_DATA_H_
#define  _XEP_CAPS_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_caps;


struct caps_caps_t {
  const xmlChar * fExt;
  const xmlChar * fHash;
  const xmlChar * fNode;
  const xmlChar * fVer;
};


struct caps_caps_t* caps_caps_decode(xmlTextReaderPtr reader);
int caps_caps_encode(xmlTextWriterPtr writer, struct caps_caps_t* data);
#endif
