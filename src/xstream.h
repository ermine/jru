#ifndef _XSTREAM_H_
#define _XSTREAM_H_
#include "xmppdata/extensions.h"

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>

#include "types.h"

struct xstream_extension_t {
  const char* namespace;
  const char* name;
  enum extension_type type;
  void *(*decode) (xmlTextReaderPtr reader);
  int (*encode) (xmlTextWriterPtr writer, void *data);
};

extern struct xstream_extension_t extensions[];
extern int extensions_len;

void xstream_read (int sock);

extension_t *xstream_extension_decode (xmlTextReaderPtr reader);
int xstream_extension_get_type(const char* space, const char* local);
int xstream_extension_encode (xmlTextWriterPtr writer, void* data, int type);
int xstream_skip (xmlTextReaderPtr reader);
unsigned char* xmlTextReaderReadBase64(xmlTextReaderPtr reader);


#endif
