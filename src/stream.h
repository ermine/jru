#ifndef _STREAM_H_
#define _STREAM_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include "xstream.h"
#include "jid/jid.h"
#include "account.h"

typedef struct {
  int fd;
  xmlreader_t* reader;
  xmlwriter_t* writer;
  jid_t* jid;
  const char* content_namespace;
  const char* lang;
  void* userdata;
  bool logging;
  extension_t* xmpp_error;
  char id[32];
} stream_t;

stream_t* stream_new (int fd, const char* content_namespace, const char* lang,
                      bool logging, void* userdata);
const char* stream_get_id (stream_t* strm);
int stream_start (stream_t* strm, account_t* account);
int stream_negotate (stream_t* strm, account_t* account);

#endif
