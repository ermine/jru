#ifndef _XEP_PRIVACY_DATA_H_
#define  _XEP_PRIVACY_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"

struct privacy_active_t;
struct privacy_default_t;
struct privacy_list_t;
struct privacy_item_t;

extern const char *ns_privacy;

enum privacy_item_action_t
{
  PRIVACY_ITEM_ACTION_ALLOW,
  PRIVACY_ITEM_ACTION_DENY,
};

enum privacy_item_action_t enum_privacy_item_action_from_string (const char
								 *value);
const char *enum_privacy_item_action_to_string (enum privacy_item_action_t);
enum privacy_item_type_t
{
  PRIVACY_ITEM_TYPE_GROUP,
  PRIVACY_ITEM_TYPE_JID,
  PRIVACY_ITEM_TYPE_SUBSCRIPTION,
};

enum privacy_item_type_t enum_privacy_item_type_from_string (const char
							     *value);
const char *enum_privacy_item_type_to_string (enum privacy_item_type_t);

struct privacy_privacy_t
{
  struct privacy_active_t *fActive;
  struct privacy_default_t *fDefault;
  array_t *fList;
};


struct privacy_active_t
{
  char *fName;
  char *fExtra;
};


struct privacy_default_t
{
  char *fName;
  char *fExtra;
};


struct privacy_list_t
{
  char *fName;
  array_t *fItems;
};


struct privacy_item_t
{
  enum privacy_item_action_t fAction;
  uint32_t *fOrder;
  enum privacy_item_type_t fType;
  char *fValue;
  bool fIq;
  bool fMessage;
  bool fPresence_in;
  bool fPresence_out;
};


struct privacy_privacy_t *privacy_privacy_decode (xmlreader_t * reader);
int privacy_privacy_encode (xmlwriter_t * writer,
			    struct privacy_privacy_t *data);
void privacy_privacy_free (struct privacy_privacy_t *data);
struct privacy_active_t *privacy_active_decode (xmlreader_t * reader);
int privacy_active_encode (xmlwriter_t * writer,
			   struct privacy_active_t *data);
void privacy_active_free (struct privacy_active_t *data);
struct privacy_default_t *privacy_default_decode (xmlreader_t * reader);
int privacy_default_encode (xmlwriter_t * writer,
			    struct privacy_default_t *data);
void privacy_default_free (struct privacy_default_t *data);
struct privacy_list_t *privacy_list_decode (xmlreader_t * reader);
int privacy_list_encode (xmlwriter_t * writer, struct privacy_list_t *data);
void privacy_list_free (struct privacy_list_t *data);
struct privacy_item_t *privacy_item_decode (xmlreader_t * reader);
int privacy_item_encode (xmlwriter_t * writer, struct privacy_item_t *data);
void privacy_item_free (struct privacy_item_t *data);
#endif
