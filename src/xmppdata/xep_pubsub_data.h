#ifndef _XEP_PUBSUB_DATA_H_
#define  _XEP_PUBSUB_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "xep_xdata_data.h"
#include "jid/jid.h"

struct pubsub_event_collection_t;
struct pubsub_event_configuration_t;
struct pubsub_event_delete_t;
struct pubsub_event_items_t;
struct pubsub_event_purge_t;
struct pubsub_event_subscription_t;
struct pubsub_event_item_t;
struct pubsub_event_retract_t;

extern const char *ns_pubsub_event;

enum pubsub_event_collection_type_type_t
{
  PUBSUB_EVENT_COLLECTION_TYPE_TYPE_ASSOCIATE,
  PUBSUB_EVENT_COLLECTION_TYPE_TYPE_DISASSOCIATE,
};

enum pubsub_event_collection_type_type_t
enum_pubsub_event_collection_type_type_from_string (const char *value);
const char *enum_pubsub_event_collection_type_type_to_string (enum
							      pubsub_event_collection_type_type_t);
enum pubsub_event_subscription_subscription_t
{
  PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_NONE,
  PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_PENDING,
  PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_SUBSCRIBED,
  PUBSUB_EVENT_SUBSCRIPTION_SUBSCRIPTION_UNCONFIGURED,
};

enum pubsub_event_subscription_subscription_t
enum_pubsub_event_subscription_subscription_from_string (const char *value);
const char *enum_pubsub_event_subscription_subscription_to_string (enum
								   pubsub_event_subscription_subscription_t);

struct pubsub_event_event_t
{
  int type;
  union
  {
    struct pubsub_event_collection_t *fCollection;
    struct pubsub_event_configuration_t *fConfiguration;
    struct pubsub_event_delete_t *fDelete;
    struct pubsub_event_items_t *fItems;
    struct pubsub_event_purge_t *fPurge;
    struct pubsub_event_subscription_t *fSubscription;
  } *u;
};

struct pubsub_event_collection_t
{
  const char *fNode;
  struct pubsub_event_type_set_t
  {
    const char *fNode;
    enum pubsub_event_collection_type_type_t fType;
  } fType;
};


struct pubsub_event_configuration_t
{
  const char *fNode;
  struct xdata_x_t *fXdata;
};


struct pubsub_event_delete_t
{
  const char *fNode;
  struct pubsub_event_redirect_set_t
  {
    const char *fUrl;
  } fRedirect;
};


struct pubsub_event_items_t
{
  const char *fNode;
  vlist_t *fItems;
  vlist_t *fRetracts;
};


struct pubsub_event_item_t
{
  const char *fId;
  const char *fNode;
  const char *fPublisher;
  extension_t *fEvent;
};


struct pubsub_event_purge_t
{
  const char *fNode;
};


struct pubsub_event_retract_t
{
  const char *fId;
};


struct pubsub_event_subscription_t
{
  struct tm *fExpiry;
  jid_t *fJid;
  const char *fNode;
  const char *fSubid;
  enum pubsub_event_subscription_subscription_t fSubscription;
};


struct pubsub_event_event_t *pubsub_event_event_decode (xmlreader_t * reader);
int pubsub_event_event_encode (xmlwriter_t * writer,
			       struct pubsub_event_event_t *data);
struct pubsub_event_collection_t *pubsub_event_collection_decode (xmlreader_t
								  * reader);
int pubsub_event_collection_encode (xmlwriter_t * writer,
				    struct pubsub_event_collection_t *data);
struct pubsub_event_configuration_t
  *pubsub_event_configuration_decode (xmlreader_t * reader);
int pubsub_event_configuration_encode (xmlwriter_t * writer,
				       struct pubsub_event_configuration_t
				       *data);
struct pubsub_event_delete_t *pubsub_event_delete_decode (xmlreader_t *
							  reader);
int pubsub_event_delete_encode (xmlwriter_t * writer,
				struct pubsub_event_delete_t *data);
struct pubsub_event_items_t *pubsub_event_items_decode (xmlreader_t * reader);
int pubsub_event_items_encode (xmlwriter_t * writer,
			       struct pubsub_event_items_t *data);
struct pubsub_event_item_t *pubsub_event_item_decode (xmlreader_t * reader);
int pubsub_event_item_encode (xmlwriter_t * writer,
			      struct pubsub_event_item_t *data);
struct pubsub_event_purge_t *pubsub_event_purge_decode (xmlreader_t * reader);
int pubsub_event_purge_encode (xmlwriter_t * writer,
			       struct pubsub_event_purge_t *data);
struct pubsub_event_retract_t *pubsub_event_retract_decode (xmlreader_t *
							    reader);
int pubsub_event_retract_encode (xmlwriter_t * writer,
				 struct pubsub_event_retract_t *data);
struct pubsub_event_subscription_t
  *pubsub_event_subscription_decode (xmlreader_t * reader);
int pubsub_event_subscription_encode (xmlwriter_t * writer,
				      struct pubsub_event_subscription_t
				      *data);
#endif
