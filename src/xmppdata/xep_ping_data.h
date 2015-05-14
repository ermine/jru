#ifndef _XEP_PING_DATA_H_
#define  _XEP_PING_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_ping;


struct ping_ping_t
{
};


struct ping_ping_t *ping_ping_decode (xmlreader_t * reader);
int ping_ping_encode (xmlwriter_t * writer, struct ping_ping_t *data);
#endif
