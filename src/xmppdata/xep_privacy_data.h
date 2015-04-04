#ifndef _XEP_PRIVACY_DATA_H_
#define  _XEP_PRIVACY_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"

struct privacy_active_t;
struct privacy_default_t;
struct privacy_list_t;
struct privacy_item_t;

extern const char* ns_privacy;

enum privacy_item_action_t {
  PRIVACY_ITEM_ACTION_ALLOW,
  PRIVACY_ITEM_ACTION_DENY,
};

enum privacy_item_action_t enum_privacy_item_action_from_string(const xmlChar *value);
xmlChar *enum_privacy_item_action_to_string(enum privacy_item_action_t);
enum privacy_item_type_t {
  PRIVACY_ITEM_TYPE_GROUP,
  PRIVACY_ITEM_TYPE_JID,
  PRIVACY_ITEM_TYPE_SUBSCRIPTION,
};

enum privacy_item_type_t enum_privacy_item_type_from_string(const xmlChar *value);
xmlChar *enum_privacy_item_type_to_string(enum privacy_item_type_t);

struct privacy_privacy_t {
  struct privacy_active_t* fActive;
  struct privacy_default_t* fDefault;
  llist_t *fList;
};


struct privacy_active_t {
  const xmlChar * fName;
  const xmlChar * fExtra;
};


struct privacy_default_t {
  const xmlChar * fName;
  const xmlChar * fExtra;
};


struct privacy_list_t {
  const xmlChar * fName;
  llist_t *fItems;
};


struct privacy_item_t {
  enum privacy_item_action_t fAction;
  uint32_t * fOrder;
  enum privacy_item_type_t fType;
  const xmlChar * fValue;
  boolean_t fIq;
  boolean_t fMessage;
  boolean_t fPresence_in;
  boolean_t fPresence_out;
};


struct privacy_privacy_t* privacy_privacy_decode(xmlTextReaderPtr reader);
int privacy_privacy_encode(xmlTextWriterPtr writer, struct privacy_privacy_t* data);
struct privacy_active_t* privacy_active_decode(xmlTextReaderPtr reader);
int privacy_active_encode(xmlTextWriterPtr writer, struct privacy_active_t* data);
struct privacy_default_t* privacy_default_decode(xmlTextReaderPtr reader);
int privacy_default_encode(xmlTextWriterPtr writer, struct privacy_default_t* data);
struct privacy_list_t* privacy_list_decode(xmlTextReaderPtr reader);
int privacy_list_encode(xmlTextWriterPtr writer, struct privacy_list_t* data);
struct privacy_item_t* privacy_item_decode(xmlTextReaderPtr reader);
int privacy_item_encode(xmlTextWriterPtr writer, struct privacy_item_t* data);
#endif
