#ifndef _XEP_DISCO_DATA_H_
#define  _XEP_DISCO_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"

struct disco_info_identity_t;
struct disco_info_feature_t;

extern const char* ns_disco_info;
extern const char* ns_disco_items;


struct disco_info_info_t {
  const xmlChar * fNode;
  llist_t *fIdentities;
  llist_t *fFeatures;
};


struct disco_info_identity_t {
  const xmlChar * fCategory;
  const xmlChar * fType;
};


struct disco_info_feature_t {
  const xmlChar * fVar;
};


struct disco_info_info_t* disco_info_info_decode(xmlTextReaderPtr reader);
int disco_info_info_encode(xmlTextWriterPtr writer, struct disco_info_info_t* data);
struct disco_info_identity_t* disco_info_identity_decode(xmlTextReaderPtr reader);
int disco_info_identity_encode(xmlTextWriterPtr writer, struct disco_info_identity_t* data);
struct disco_info_feature_t* disco_info_feature_decode(xmlTextReaderPtr reader);
int disco_info_feature_encode(xmlTextWriterPtr writer, struct disco_info_feature_t* data);

#endif
