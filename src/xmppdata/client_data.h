#ifndef _CLIENT_DATA_H_
#define  _CLIENT_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "jid/jid.h"
#include "stanza_data.h"


extern const char *ns_client;

enum client_iq_type_t
{
  CLIENT_IQ_TYPE_GET,
  CLIENT_IQ_TYPE_SET,
  CLIENT_IQ_TYPE_RESULT,
  CLIENT_IQ_TYPE_ERROR,
};

enum client_iq_type_t enum_client_iq_type_from_string (const char *value);
const char *enum_client_iq_type_to_string (enum client_iq_type_t);
enum client_presence_type_t
{
  CLIENT_PRESENCE_TYPE_SUBSCRIBE,
  CLIENT_PRESENCE_TYPE_SUBSCRIBED,
  CLIENT_PRESENCE_TYPE_UNSUBSCRIBE,
  CLIENT_PRESENCE_TYPE_UNSUBSCRIBED,
  CLIENT_PRESENCE_TYPE_UNAVAILABLE,
};

enum client_presence_type_t enum_client_presence_type_from_string (const char
								   *value);
const char *enum_client_presence_type_to_string (enum client_presence_type_t);
enum client_presence_show_t
{
  CLIENT_PRESENCE_SHOW_CHAT,
  CLIENT_PRESENCE_SHOW_AWAY,
  CLIENT_PRESENCE_SHOW_XA,
  CLIENT_PRESENCE_SHOW_DND,
};

enum client_presence_show_t enum_client_presence_show_from_string (const char
								   *value);
const char *enum_client_presence_show_to_string (enum client_presence_show_t);
enum client_message_type_t
{
  CLIENT_MESSAGE_TYPE_NORMAL,
  CLIENT_MESSAGE_TYPE_CHAT,
  CLIENT_MESSAGE_TYPE_GROUPCHAT,
  CLIENT_MESSAGE_TYPE_HEADLINE,
};

enum client_message_type_t enum_client_message_type_from_string (const char
								 *value);
const char *enum_client_message_type_to_string (enum client_message_type_t);

struct client_iq_t
{
  jid_t *fFrom;
  jid_t *fTo;
  const char *fId;
  enum client_iq_type_t fType;
  const char *fLang;
  extension_t *fPayload;
  struct stanza_error_t *fError;
};


struct client_presence_t
{
  jid_t *fFrom;
  jid_t *fTo;
  const char *fId;
  enum client_presence_type_t fType;
  const char *fLang;
  enum client_presence_show_t fShow;
  const char *fStatus;
  int *fPriority;
  vlist_t *fX;
  struct stanza_error_t *fError;
};


struct client_message_t
{
  jid_t *fFrom;
  jid_t *fTo;
  const char *fId;
  enum client_message_type_t fType;
  const char *fLang;
  const char *fThread;
  langstring_t *fSubject;
  langstring_t *fBody;
  vlist_t *fX;
  struct stanza_error_t *fError;
};


struct client_iq_t *client_iq_decode (xmlreader_t * reader);
int client_iq_encode (xmlwriter_t * writer, struct client_iq_t *data);
struct client_presence_t *client_presence_decode (xmlreader_t * reader);
int client_presence_encode (xmlwriter_t * writer,
			    struct client_presence_t *data);
struct client_message_t *client_message_decode (xmlreader_t * reader);
int client_message_encode (xmlwriter_t * writer,
			   struct client_message_t *data);
#endif
