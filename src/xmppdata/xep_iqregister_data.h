#ifndef _XEP_IQREGISTER_DATA_H_
#define  _XEP_IQREGISTER_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "xep_xdata_data.h"
#include "xep_xoob_data.h"


extern const char* ns_iqregister;


struct iqregister_query_t {
 struct iqregister_fields_set_t {
  boolean_t fRegistered;
  const xmlChar * fInstructions;
  const xmlChar * fUsername;
  const xmlChar * fNick;
  const xmlChar * fPassword;
  const xmlChar * fName;
  const xmlChar * fFirst;
  const xmlChar * fLast;
  const xmlChar * fEmail;
  const xmlChar * fAddress;
  const xmlChar * fCity;
  const xmlChar * fState;
  const xmlChar * fZip;
  const xmlChar * fPhone;
  const xmlChar * fUrl;
  const xmlChar * fDate;
  const xmlChar * fMisc;
  const xmlChar * fText;
  const xmlChar * fKey;
} fFields;
  boolean_t fRemove;
struct xdata_x_t* fXdata;
struct xoob_x_t* fXoob;
};


struct iqregister_query_t* iqregister_query_decode(xmlTextReaderPtr reader);
int iqregister_query_encode(xmlTextWriterPtr writer, struct iqregister_query_t* data);
#endif
