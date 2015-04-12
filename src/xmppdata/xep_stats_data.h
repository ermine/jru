#ifndef _XEP_STATS_DATA_H_
#define  _XEP_STATS_DATA_H_

#include <libxml/xmlreader.h>
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"

struct stats_stat_t;

extern const char* ns_stats;


typedef vlist_t stats_stats_t;


struct stats_stat_t {
  const char* fName;
  const char* fUnits;
  const char* fValue;
};


struct stats_stats_t* stats_stats_decode(xmlTextReaderPtr reader);
int stats_stats_encode(xmlWriter_t* writer, struct stats_stats_t* data);
struct stats_stat_t* stats_stat_decode(xmlTextReaderPtr reader);
int stats_stat_encode(xmlWriter_t* writer, struct stats_stat_t* data);
#endif
