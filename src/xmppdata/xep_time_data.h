#ifndef _XEP_TIME_DATA_H_
#define  _XEP_TIME_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_time;


struct time_time_t
{
  char *fTz;
  char *fUtc;
};


struct time_time_t *time_time_decode (xmlreader_t * reader);
int time_time_encode (xmlwriter_t * writer, struct time_time_t *data);
void time_time_free (struct time_time_t *data);
#endif
