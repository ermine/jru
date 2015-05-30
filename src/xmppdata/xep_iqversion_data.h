#ifndef _XEP_IQVERSION_DATA_H_
#define  _XEP_IQVERSION_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_iqversion;


struct iqversion_version_t
{
  char *fName;
  char *fVersion;
  char *fOs;
};


struct iqversion_version_t *iqversion_version_decode (xmlreader_t * reader);
int iqversion_version_encode (xmlwriter_t * writer,
			      struct iqversion_version_t *data);
void iqversion_version_free (struct iqversion_version_t *data);
#endif
