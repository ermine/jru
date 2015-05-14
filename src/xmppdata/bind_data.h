#ifndef _BIND_DATA_H_
#define  _BIND_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "jid/jid.h"


extern const char *ns_bind;


struct bind_bind_t
{
  const char *fResource;
  jid_t *fJid;
};


struct bind_bind_t *bind_bind_decode (xmlreader_t * reader);
int bind_bind_encode (xmlwriter_t * writer, struct bind_bind_t *data);
#endif
