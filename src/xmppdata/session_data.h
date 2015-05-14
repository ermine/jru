#ifndef _SESSION_DATA_H_
#define  _SESSION_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_session;


struct session_session_t
{
};


struct session_session_t *session_session_decode (xmlreader_t * reader);
int session_session_encode (xmlwriter_t * writer,
			    struct session_session_t *data);
#endif
