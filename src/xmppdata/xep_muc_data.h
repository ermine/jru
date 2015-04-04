#ifndef _XEP_MUC_DATA_H_
#define  _XEP_MUC_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "jid/jid.h"
#include "xep_xdata_data.h"

struct muc_user_decline_t;
struct muc_user_destroy_t;
struct muc_user_invite_t;
struct muc_user_item_t;
struct muc_admin_item_t;
struct muc_user_status_t;

extern const char* ns_muc;
extern const char* ns_muc_user;
extern const char* ns_muc_owner;
extern const char* ns_muc_admin;


struct muc_enter_t {
 struct muc_history_set_t {
  int * fMaxchars;
  int * fMaxstanzas;
  int * fSeconds;
  struct tm* fSince;
} fHistory;
  const xmlChar * fPassword;
};


struct muc_enter_t* muc_enter_decode(xmlTextReaderPtr reader);
int muc_enter_encode(xmlTextWriterPtr writer, struct muc_enter_t* data);
enum muc_user_item_affiliation_t {
  MUC_USER_ITEM_AFFILIATION_ADMIN,
  MUC_USER_ITEM_AFFILIATION_MEMBER,
  MUC_USER_ITEM_AFFILIATION_NONE,
  MUC_USER_ITEM_AFFILIATION_OUTCAST,
  MUC_USER_ITEM_AFFILIATION_OWNER,
};

enum muc_user_item_affiliation_t enum_muc_user_item_affiliation_from_string(const xmlChar *value);
xmlChar *enum_muc_user_item_affiliation_to_string(enum muc_user_item_affiliation_t);
enum muc_user_item_role_t {
  MUC_USER_ITEM_ROLE_MODERATOR,
  MUC_USER_ITEM_ROLE_NONE,
  MUC_USER_ITEM_ROLE_PARTICIPANT,
  MUC_USER_ITEM_ROLE_VISITOR,
};

enum muc_user_item_role_t enum_muc_user_item_role_from_string(const xmlChar *value);
xmlChar *enum_muc_user_item_role_to_string(enum muc_user_item_role_t);

struct muc_user_action_t {
  struct muc_user_decline_t* fDecline;
  struct muc_user_destroy_t* fDestroy;
  llist_t *fInvite;
  struct muc_user_item_t* fItem;
  const xmlChar * fPassword;
  llist_t *fStatus;
};


struct muc_user_status_t {
  int * fCode;
};


struct muc_user_decline_t {
  jid_t * fFrom;
  jid_t * fTo;
  const xmlChar * fReason;
};


struct muc_user_destroy_t {
  jid_t * fJid;
  const xmlChar * fReason;
};


struct muc_user_invite_t {
  jid_t * fFrom;
  jid_t * fTo;
  const xmlChar * fReason;
};


struct muc_user_item_t {
  enum muc_user_item_affiliation_t fAffiliation;
  jid_t * fJid;
  const xmlChar * fNick;
  enum muc_user_item_role_t fRole;
 struct muc_user_actor_set_t {
  jid_t * fJid;
} fActor;
  const xmlChar * fReason;
  boolean_t fContinue;
};


struct muc_user_action_t* muc_user_action_decode(xmlTextReaderPtr reader);
int muc_user_action_encode(xmlTextWriterPtr writer, struct muc_user_action_t* data);
struct muc_user_status_t* muc_user_status_decode(xmlTextReaderPtr reader);
int muc_user_status_encode(xmlTextWriterPtr writer, struct muc_user_status_t* data);
struct muc_user_decline_t* muc_user_decline_decode(xmlTextReaderPtr reader);
int muc_user_decline_encode(xmlTextWriterPtr writer, struct muc_user_decline_t* data);
struct muc_user_destroy_t* muc_user_destroy_decode(xmlTextReaderPtr reader);
int muc_user_destroy_encode(xmlTextWriterPtr writer, struct muc_user_destroy_t* data);
struct muc_user_invite_t* muc_user_invite_decode(xmlTextReaderPtr reader);
int muc_user_invite_encode(xmlTextWriterPtr writer, struct muc_user_invite_t* data);
struct muc_user_item_t* muc_user_item_decode(xmlTextReaderPtr reader);
int muc_user_item_encode(xmlTextWriterPtr writer, struct muc_user_item_t* data);

typedef struct xdata_x_t* muc_owner_configure_t;


muc_owner_configure_t* muc_owner_configure_decode(xmlTextReaderPtr reader);
int muc_owner_configure_encode(xmlTextWriterPtr writer, muc_owner_configure_t* data);
enum muc_admin_item_affiliation_t {
  MUC_ADMIN_ITEM_AFFILIATION_ADMIN,
  MUC_ADMIN_ITEM_AFFILIATION_MEMBER,
  MUC_ADMIN_ITEM_AFFILIATION_NONE,
  MUC_ADMIN_ITEM_AFFILIATION_OUTCAST,
  MUC_ADMIN_ITEM_AFFILIATION_OWNER,
};

enum muc_admin_item_affiliation_t enum_muc_admin_item_affiliation_from_string(const xmlChar *value);
xmlChar *enum_muc_admin_item_affiliation_to_string(enum muc_admin_item_affiliation_t);
enum muc_admin_item_role_t {
  MUC_ADMIN_ITEM_ROLE_MODERATOR,
  MUC_ADMIN_ITEM_ROLE_NONE,
  MUC_ADMIN_ITEM_ROLE_PARTICIPANT,
  MUC_ADMIN_ITEM_ROLE_VISITOR,
};

enum muc_admin_item_role_t enum_muc_admin_item_role_from_string(const xmlChar *value);
xmlChar *enum_muc_admin_item_role_to_string(enum muc_admin_item_role_t);

struct muc_admin_query_t {
  llist_t *fItems;
};


struct muc_admin_item_t {
  enum muc_admin_item_affiliation_t fAffiliation;
  jid_t * fJid;
  const xmlChar * fNick;
  enum muc_admin_item_role_t fRole;
 struct muc_admin_actor_set_t {
  jid_t * fJid;
} fActor;
  const xmlChar * fReason;
};


struct muc_admin_query_t* muc_admin_query_decode(xmlTextReaderPtr reader);
int muc_admin_query_encode(xmlTextWriterPtr writer, struct muc_admin_query_t* data);
struct muc_admin_item_t* muc_admin_item_decode(xmlTextReaderPtr reader);
int muc_admin_item_encode(xmlTextWriterPtr writer, struct muc_admin_item_t* data);
#endif
