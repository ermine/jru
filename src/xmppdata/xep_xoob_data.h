#ifndef _XEP_XOOB_DATA_H_
#define  _XEP_XOOB_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_xoob;


struct xoob_x_t {
  const xmlChar * fUrl;
  const xmlChar * fDesc;
};


struct xoob_x_t* xoob_x_decode(xmlTextReaderPtr reader);
int xoob_x_encode(xmlTextWriterPtr writer, struct xoob_x_t* data);
#endif
