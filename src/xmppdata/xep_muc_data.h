#ifndef _XEP_MUC_DATA_H_
#define  _XEP_MUC_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
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

extern const char *ns_muc;
extern const char *ns_muc_user;
extern const char *ns_muc_owner;
extern const char *ns_muc_admin;


struct muc_enter_t
{
  struct muc_history_set_t
  {
    int *fMaxchars;
    int *fMaxstanzas;
    int *fSeconds;
    struct tm *fSince;
  } fHistory;
  char *fPassword;
};


struct muc_enter_t *muc_enter_decode (xmlreader_t * reader);
int muc_enter_encode (xmlwriter_t * writer, struct muc_enter_t *data);
void muc_enter_free (struct muc_enter_t *data);
enum muc_user_item_affiliation_t
{
  MUC_USER_ITEM_AFFILIATION_ADMIN,
  MUC_USER_ITEM_AFFILIATION_MEMBER,
  MUC_USER_ITEM_AFFILIATION_NONE,
  MUC_USER_ITEM_AFFILIATION_OUTCAST,
  MUC_USER_ITEM_AFFILIATION_OWNER,
};

enum muc_user_item_affiliation_t
enum_muc_user_item_affiliation_from_string (const char *value);
const char *enum_muc_user_item_affiliation_to_string (enum
						      muc_user_item_affiliation_t);
enum muc_user_item_role_t
{
  MUC_USER_ITEM_ROLE_MODERATOR,
  MUC_USER_ITEM_ROLE_NONE,
  MUC_USER_ITEM_ROLE_PARTICIPANT,
  MUC_USER_ITEM_ROLE_VISITOR,
};

enum muc_user_item_role_t enum_muc_user_item_role_from_string (const char
							       *value);
const char *enum_muc_user_item_role_to_string (enum muc_user_item_role_t);

struct muc_user_action_t
{
  struct muc_user_decline_t *fDecline;
  struct muc_user_destroy_t *fDestroy;
  array_t *fInvite;
  struct muc_user_item_t *fItem;
  char *fPassword;
  array_t *fStatus;
};


struct muc_user_status_t
{
  int *fCode;
};


struct muc_user_decline_t
{
  jid_t *fFrom;
  jid_t *fTo;
  char *fReason;
};


struct muc_user_destroy_t
{
  jid_t *fJid;
  char *fReason;
};


struct muc_user_invite_t
{
  jid_t *fFrom;
  jid_t *fTo;
  char *fReason;
};


struct muc_user_item_t
{
  enum muc_user_item_affiliation_t fAffiliation;
  jid_t *fJid;
  char *fNick;
  enum muc_user_item_role_t fRole;
  struct muc_user_actor_set_t
  {
    jid_t *fJid;
  } fActor;
  char *fReason;
  bool fContinue;
};


struct muc_user_action_t *muc_user_action_decode (xmlreader_t * reader);
int muc_user_action_encode (xmlwriter_t * writer,
			    struct muc_user_action_t *data);
void muc_user_action_free (struct muc_user_action_t *data);
struct muc_user_status_t *muc_user_status_decode (xmlreader_t * reader);
int muc_user_status_encode (xmlwriter_t * writer,
			    struct muc_user_status_t *data);
void muc_user_status_free (struct muc_user_status_t *data);
struct muc_user_decline_t *muc_user_decline_decode (xmlreader_t * reader);
int muc_user_decline_encode (xmlwriter_t * writer,
			     struct muc_user_decline_t *data);
void muc_user_decline_free (struct muc_user_decline_t *data);
struct muc_user_destroy_t *muc_user_destroy_decode (xmlreader_t * reader);
int muc_user_destroy_encode (xmlwriter_t * writer,
			     struct muc_user_destroy_t *data);
void muc_user_destroy_free (struct muc_user_destroy_t *data);
struct muc_user_invite_t *muc_user_invite_decode (xmlreader_t * reader);
int muc_user_invite_encode (xmlwriter_t * writer,
			    struct muc_user_invite_t *data);
void muc_user_invite_free (struct muc_user_invite_t *data);
struct muc_user_item_t *muc_user_item_decode (xmlreader_t * reader);
int muc_user_item_encode (xmlwriter_t * writer, struct muc_user_item_t *data);
void muc_user_item_free (struct muc_user_item_t *data);

typedef struct xdata_x_t *muc_owner_configure_t;


muc_owner_configure_t *muc_owner_configure_decode (xmlreader_t * reader);
int muc_owner_configure_encode (xmlwriter_t * writer,
				muc_owner_configure_t * data);
void muc_owner_configure_free (muc_owner_configure_t * data);
enum muc_admin_item_affiliation_t
{
  MUC_ADMIN_ITEM_AFFILIATION_ADMIN,
  MUC_ADMIN_ITEM_AFFILIATION_MEMBER,
  MUC_ADMIN_ITEM_AFFILIATION_NONE,
  MUC_ADMIN_ITEM_AFFILIATION_OUTCAST,
  MUC_ADMIN_ITEM_AFFILIATION_OWNER,
};

enum muc_admin_item_affiliation_t
enum_muc_admin_item_affiliation_from_string (const char *value);
const char *enum_muc_admin_item_affiliation_to_string (enum
						       muc_admin_item_affiliation_t);
enum muc_admin_item_role_t
{
  MUC_ADMIN_ITEM_ROLE_MODERATOR,
  MUC_ADMIN_ITEM_ROLE_NONE,
  MUC_ADMIN_ITEM_ROLE_PARTICIPANT,
  MUC_ADMIN_ITEM_ROLE_VISITOR,
};

enum muc_admin_item_role_t enum_muc_admin_item_role_from_string (const char
								 *value);
const char *enum_muc_admin_item_role_to_string (enum muc_admin_item_role_t);

struct muc_admin_query_t
{
  array_t *fItems;
};


struct muc_admin_item_t
{
  enum muc_admin_item_affiliation_t fAffiliation;
  jid_t *fJid;
  char *fNick;
  enum muc_admin_item_role_t fRole;
  struct muc_admin_actor_set_t
  {
    jid_t *fJid;
  } fActor;
  char *fReason;
};


struct muc_admin_query_t *muc_admin_query_decode (xmlreader_t * reader);
int muc_admin_query_encode (xmlwriter_t * writer,
			    struct muc_admin_query_t *data);
void muc_admin_query_free (struct muc_admin_query_t *data);
struct muc_admin_item_t *muc_admin_item_decode (xmlreader_t * reader);
int muc_admin_item_encode (xmlwriter_t * writer,
			   struct muc_admin_item_t *data);
void muc_admin_item_free (struct muc_admin_item_t *data);
#endif
