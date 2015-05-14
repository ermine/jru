#include <stdio.h>

#include "xmlreader.h"
#include <string.h>

#include <xstream.h>
#include "types.h"
#include "account.h"
#include "stream.h"
#include "errors.h"
#include "helpers.h"
#include "xmppdata/client_data.h"

extension_t* xstream_extension_decode (xmlreader_t* reader) {
  int i = 0;

  const char* name = xmlreader_get_name (reader);
  const char* namespace = xmlreader_get_namespace (reader);

  void *(*decode) (xmlreader_t* reader);

  for (i = 0; i < extensions_len; i++) {
    if (strcmp ((char*) name, extensions[i].name) == 0 &&
        strcmp ((char*) namespace, extensions[i].namespace) == 0) {
      decode = extensions[i].decode;
      extension_t* ext = malloc (sizeof (extension_t));
      if (ext == NULL)
        fatal ("xstream_extension_decode: malloc failed");
      ext->type = extensions[i].type;
      ext->data = decode(reader);
      return ext;
    }
  }
  return NULL;
}

int xstream_extension_encode (xmlwriter_t* writer, void* data, int type) {
  int i;
  int (*encoder)(xmlwriter_t* writer, void* data);

  for (i = 0; i < extensions_len; i++) {
    if (extensions[i].type == type) {
      encoder = extensions[i].encode;
      return encoder(writer, data);
    }
  }
  return ERR_EXTENSION_NOT_FOUND;
}

extension_t* xstream_read (xmlreader_t* reader) {
  switch (xmlreader_next (reader)) {
  case XML_START_ELEMENT:
    return xstream_extension_decode (reader);
  case XML_END_ELEMENT:
    return NULL;
  case XML_TEXT:
    break;
  case XML_ERROR:
    return NULL;
  }
  return NULL;
}

int xstream_start (int fd, account_t* acc) {
  stream_t* strm = stream_new (fd, ns_client, "ru", true, NULL);

  int err = stream_negotate (strm, acc);
  return err;
}
