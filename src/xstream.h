#ifndef _XSTREAM_H_
#define _XSTREAM_H_
#include "xmppdata/extensions.h"

#include "xmlreader.h"
#include "xmlwriter.h"
#include "account.h"

#include "types.h"

struct xstream_extension_t {
  const char* namespace;
  const char* name;
  enum extension_type type;
  void *(*decode) (xmlreader_t* reader);
  int (*encode) (xmlwriter_t* writer, void *data);
};

extern struct xstream_extension_t extensions[];
extern int extensions_len;

extension_t* xstream_read (xmlreader_t* reader);

extension_t *xstream_extension_decode (xmlreader_t* reader);
int xstream_extension_get_type(const char* space, const char* local);
int xstream_extension_encode (xmlwriter_t* writer, void* data, int type);

int xstream_start (int fd, account_t* account);


#endif
