#ifndef _XEP_IQREGISTER_DATA_H_
#define  _XEP_IQREGISTER_DATA_H_

#include <libxml/xmlreader.h>
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "xep_xdata_data.h"
#include "xep_xoob_data.h"


extern const char* ns_iqregister;


struct iqregister_query_t {
 struct iqregister_fields_set_t {
  boolean_t fRegistered;
  const char* fInstructions;
  const char* fUsername;
  const char* fNick;
  const char* fPassword;
  const char* fName;
  const char* fFirst;
  const char* fLast;
  const char* fEmail;
  const char* fAddress;
  const char* fCity;
  const char* fState;
  const char* fZip;
  const char* fPhone;
  const char* fUrl;
  const char* fDate;
  const char* fMisc;
  const char* fText;
  const char* fKey;
} fFields;
  boolean_t fRemove;
struct xdata_x_t* fXdata;
struct xoob_x_t* fXoob;
};


struct iqregister_query_t* iqregister_query_decode(xmlTextReaderPtr reader);
int iqregister_query_encode(xmlWriter_t* writer, struct iqregister_query_t* data);
#endif
