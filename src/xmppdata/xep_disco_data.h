#ifndef _XEP_DISCO_DATA_H_
#define  _XEP_DISCO_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"

struct disco_info_identity_t;
struct disco_info_feature_t;

extern const char *ns_disco_info;
extern const char *ns_disco_items;


struct disco_info_info_t
{
  const char *fNode;
  vlist_t *fIdentities;
  vlist_t *fFeatures;
};


struct disco_info_identity_t
{
  const char *fCategory;
  const char *fType;
};


struct disco_info_feature_t
{
  const char *fVar;
};


struct disco_info_info_t *disco_info_info_decode (xmlreader_t * reader);
int disco_info_info_encode (xmlwriter_t * writer,
			    struct disco_info_info_t *data);
struct disco_info_identity_t *disco_info_identity_decode (xmlreader_t *
							  reader);
int disco_info_identity_encode (xmlwriter_t * writer,
				struct disco_info_identity_t *data);
struct disco_info_feature_t *disco_info_feature_decode (xmlreader_t * reader);
int disco_info_feature_encode (xmlwriter_t * writer,
			       struct disco_info_feature_t *data);

#endif
