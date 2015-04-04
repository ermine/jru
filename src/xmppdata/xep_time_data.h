#ifndef _XEP_TIME_DATA_H_
#define  _XEP_TIME_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_time;


struct time_time_t {
  const xmlChar * fTz;
  const xmlChar * fUtc;
};


struct time_time_t* time_time_decode(xmlTextReaderPtr reader);
int time_time_encode(xmlTextWriterPtr writer, struct time_time_t* data);
#endif
