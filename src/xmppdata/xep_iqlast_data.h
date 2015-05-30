#ifndef _XEP_IQLAST_DATA_H_
#define  _XEP_IQLAST_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_iqlast;


struct iqlast_last_t
{
  uint32_t *fSeconds;
  char *fExtra;
};


struct iqlast_last_t *iqlast_last_decode (xmlreader_t * reader);
int iqlast_last_encode (xmlwriter_t * writer, struct iqlast_last_t *data);
void iqlast_last_free (struct iqlast_last_t *data);
#endif
