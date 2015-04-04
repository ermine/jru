#ifndef _XEP_PING_DATA_H_
#define  _XEP_PING_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_ping;


struct ping_ping_t {
};


struct ping_ping_t* ping_ping_decode(xmlTextReaderPtr reader);
int ping_ping_encode(xmlTextWriterPtr writer, struct ping_ping_t* data);
#endif
