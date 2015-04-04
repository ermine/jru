#ifndef _BIND_DATA_H_
#define  _BIND_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "jid/jid.h"


extern const char* ns_bind;


struct bind_bind_t {
  const xmlChar * fResource;
  jid_t * fJid;
};


struct bind_bind_t* bind_bind_decode(xmlTextReaderPtr reader);
int bind_bind_encode(xmlTextWriterPtr writer, struct bind_bind_t* data);
#endif
