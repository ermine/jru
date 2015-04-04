#ifndef _SESSION_DATA_H_
#define  _SESSION_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char* ns_session;


struct session_session_t {
};


struct session_session_t* session_session_decode(xmlTextReaderPtr reader);
int session_session_encode(xmlTextWriterPtr writer, struct session_session_t* data);
#endif
