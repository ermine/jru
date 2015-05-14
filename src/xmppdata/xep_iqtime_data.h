#ifndef _XEP_IQTIME_DATA_H_
#define  _XEP_IQTIME_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_iqtime;


struct iqtime_time_t
{
  const char *fUtc;
  const char *fTz;
  const char *fDisplay;
};


struct iqtime_time_t *iqtime_time_decode (xmlreader_t * reader);
int iqtime_time_encode (xmlwriter_t * writer, struct iqtime_time_t *data);
#endif
