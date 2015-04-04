#ifndef _XEP_IQTIME_DATA_H_
#define  _XEP_IQTIME_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_iqtime;


struct iqtime_time_t {
  const xmlChar * fUtc;
  const xmlChar * fTz;
  const xmlChar * fDisplay;
};


struct iqtime_time_t* iqtime_time_decode(xmlTextReaderPtr reader);
int iqtime_time_encode(xmlTextWriterPtr writer, struct iqtime_time_t* data);
#endif
