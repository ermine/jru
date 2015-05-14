#ifndef _ROSTER_DATA_H_
#define  _ROSTER_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "jid/jid.h"

struct roster_item_t;

extern const char *ns_roster;

enum roster_item_ask_t
{
  ROSTER_ITEM_ASK_SUBSCRIBE,
};

enum roster_item_ask_t enum_roster_item_ask_from_string (const char *value);
const char *enum_roster_item_ask_to_string (enum roster_item_ask_t);
enum roster_item_subscription_t
{
  ROSTER_ITEM_SUBSCRIPTION_BOTH,
  ROSTER_ITEM_SUBSCRIPTION_FROM,
  ROSTER_ITEM_SUBSCRIPTION_NONE,
  ROSTER_ITEM_SUBSCRIPTION_REMOVE,
  ROSTER_ITEM_SUBSCRIPTION_TO,
};

enum roster_item_subscription_t
enum_roster_item_subscription_from_string (const char *value);
const char *enum_roster_item_subscription_to_string (enum
						     roster_item_subscription_t);

struct roster_roster_t
{
  const char *fVer;
  vlist_t *fItems;
};


struct roster_item_t
{
  bool *fApproved;
  enum roster_item_ask_t fAsk;
  jid_t *fJid;
  const char *fName;
  enum roster_item_subscription_t fSubscription;
  vlist_t *fGroup;
};


struct roster_roster_t *roster_roster_decode (xmlreader_t * reader);
int roster_roster_encode (xmlwriter_t * writer, struct roster_roster_t *data);
struct roster_item_t *roster_item_decode (xmlreader_t * reader);
int roster_item_encode (xmlwriter_t * writer, struct roster_item_t *data);
#endif
