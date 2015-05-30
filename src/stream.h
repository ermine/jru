#ifndef _STREAM_H_
#define _STREAM_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include "xstream.h"
#include "jid/jid.h"
#include "account.h"

struct _stream_t;

struct _stream_t {
  int fd;
  int state;
  xmlreader_t reader;
  xmlwriter_t writer;
  jid_t* jid;
  const char* content_namespace;
  const char* lang;
  void* userdata;
  bool logging;
  extension_t* xmpp_error;
  char id[32];
  int (*session_handler) (struct _stream_t* strm, account_t* account, extension_t* ext);
};

typedef struct _stream_t stream_t;

struct stream_feature_t {
  int extension_type;
  bool (*is_mandatory) (stream_t*);
  bool (*need_to_restart) (void);
  int (*negotate) (stream_t* strm, account_t* account, void** data, extension_t* ext);
};

stream_t* stream_new (int fd, const char* content_namespace, const char* lang,
                      bool logging, void* userdata);
const char* stream_get_id (stream_t* strm);
int stream_start (stream_t* strm, account_t* account);
int stream_process (stream_t* strm, account_t* account, extension_t* ext);
int xstream_read (stream_t* strm, extension_t* ext);

#endif
