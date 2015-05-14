#ifndef _XEP_XOOB_DATA_H_
#define  _XEP_XOOB_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_xoob;


struct xoob_x_t
{
  const char *fUrl;
  const char *fDesc;
};


struct xoob_x_t *xoob_x_decode (xmlreader_t * reader);
int xoob_x_encode (xmlwriter_t * writer, struct xoob_x_t *data);
#endif
