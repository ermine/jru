#ifndef _XSTREAM_H_
#define _XSTREAM_H_
#include "xmppdata/extensions.h"

#include <libxml/xmlreader.h>
#include "xmlwriter.h"

#include "types.h"

struct xstream_extension_t {
  const char* namespace;
  const char* name;
  enum extension_type type;
  void *(*decode) (xmlTextReaderPtr reader);
  int (*encode) (xmlWriter_t* writer, void *data);
};

extern struct xstream_extension_t extensions[];
extern int extensions_len;

xmlTextReaderPtr xstream_reader_init (int sock);
void xstream_read (xmlTextReaderPtr reader);

extension_t *xstream_extension_decode (xmlTextReaderPtr reader);
int xstream_extension_get_type(const char* space, const char* local);
int xstream_extension_encode (xmlWriter_t* writer, void* data, int type);
int xstream_skip (xmlTextReaderPtr reader);
unsigned char* xmlTextReaderReadBase64(xmlTextReaderPtr reader);


#endif
