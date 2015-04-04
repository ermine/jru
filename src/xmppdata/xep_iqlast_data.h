#ifndef _XEP_IQLAST_DATA_H_
#define  _XEP_IQLAST_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_iqlast;


struct iqlast_last_t {
  uint32_t * fSeconds;
  const xmlChar * fExtra;
};


struct iqlast_last_t* iqlast_last_decode(xmlTextReaderPtr reader);
int iqlast_last_encode(xmlTextWriterPtr writer, struct iqlast_last_t* data);
#endif
