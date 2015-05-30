#ifndef _XEP_IQREGISTER_DATA_H_
#define  _XEP_IQREGISTER_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "xep_xdata_data.h"
#include "xep_xoob_data.h"


extern const char *ns_iqregister;


struct iqregister_query_t
{
  struct iqregister_fields_set_t
  {
    bool fRegistered;
    char *fInstructions;
    char *fUsername;
    char *fNick;
    char *fPassword;
    char *fName;
    char *fFirst;
    char *fLast;
    char *fEmail;
    char *fAddress;
    char *fCity;
    char *fState;
    char *fZip;
    char *fPhone;
    char *fUrl;
    char *fDate;
    char *fMisc;
    char *fText;
    char *fKey;
  } fFields;
  bool fRemove;
  struct xdata_x_t *fXdata;
  struct xoob_x_t *fXoob;
};


struct iqregister_query_t *iqregister_query_decode (xmlreader_t * reader);
int iqregister_query_encode (xmlwriter_t * writer,
			     struct iqregister_query_t *data);
void iqregister_query_free (struct iqregister_query_t *data);
#endif
