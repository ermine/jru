#ifndef _XEP_CAPS_DATA_H_
#define  _XEP_CAPS_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_caps;


struct caps_caps_t
{
  char *fExt;
  char *fHash;
  char *fNode;
  char *fVer;
};


struct caps_caps_t *caps_caps_decode (xmlreader_t * reader);
int caps_caps_encode (xmlwriter_t * writer, struct caps_caps_t *data);
void caps_caps_free (struct caps_caps_t *data);
#endif
