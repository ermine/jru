#ifndef _XEP_STATS_DATA_H_
#define  _XEP_STATS_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"

struct stats_stat_t;

extern const char *ns_stats;




struct stats_stat_t
{
  char *fName;
  char *fUnits;
  char *fValue;
};


array_t *stats_stats_decode (xmlreader_t * reader);
int stats_stats_encode (xmlwriter_t * writer, array_t * data);
void stats_stats_free (array_t * data);
struct stats_stat_t *stats_stat_decode (xmlreader_t * reader);
int stats_stat_encode (xmlwriter_t * writer, struct stats_stat_t *data);
void stats_stat_free (struct stats_stat_t *data);
#endif
