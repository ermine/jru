#ifndef _XEP_STATS_DATA_H_
#define  _XEP_STATS_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"

struct stats_stat_t;

extern const char* ns_stats;


typedef llist_t stats_stats_t;


struct stats_stat_t {
  const xmlChar * fName;
  const xmlChar * fUnits;
  const xmlChar * fValue;
};


struct stats_stats_t* stats_stats_decode(xmlTextReaderPtr reader);
int stats_stats_encode(xmlTextWriterPtr writer, struct stats_stats_t* data);
struct stats_stat_t* stats_stat_decode(xmlTextReaderPtr reader);
int stats_stat_encode(xmlTextWriterPtr writer, struct stats_stat_t* data);
#endif
