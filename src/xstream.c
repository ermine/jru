#include <stdio.h>
#include <libxml/xmlreader.h>
#include <string.h>
#include <unistd.h>

#include <xstream.h>
#include "types.h"

extension_t *xstream_extension_decode (xmlTextReaderPtr reader) {
  xmlChar *name, *namespace;
  int i;

  name = xmlTextReaderName (reader);
  namespace = xmlTextReaderNamespaceUri (reader);

  void *(*decode) (xmlTextReaderPtr reader);

  for (i = 0; i < extensions_len; i++) {
    if (strcmp ((char*) name, extensions[i].name) == 0 &&
        strcmp ((char*) namespace, extensions[i].namespace) == 0) {
      decode = extensions[i].decode;
      return decode(reader);
    }
  }
  return NULL;
}

int xstream_extension_encode (xmlWriter_t* writer, void* data, int type) {
  int i;
  int (*encoder)(xmlWriter_t* writer, void* data);

  for (i = 0; i < extensions_len; i++) {
    if (extensions[i].type == type) {
      encoder = extensions[i].encode;
      return encoder(writer, data);
    }
  }
  return -2;
}

int xstream_socket_read(void* context, char* buffer, int len) {
  printf("IN: ");
  int ret = read ((*(int*) context), (void*) buffer, len);
  if (ret > 0)
    fwrite(buffer, sizeof(char), ret, stdout);
  return ret;
}

int xstream_socket_close(void* context) {
  return close(*(int*) context);
}

xmlWriter_t* xstream_writer_init (int fd) {
  return xmlwriter_new (fd);
}

xmlTextReaderPtr xstream_reader_init(int sock) {
  xmlTextReaderPtr reader;

  reader = xmlReaderForIO (xstream_socket_read, xstream_socket_close, (void*) &sock,
                           NULL, NULL,
                           XML_PARSE_NOENT | XML_PARSE_NOBLANKS | XML_PARSE_NOCDATA);
  return reader;
}

void xstream_read (xmlTextReaderPtr reader) {
  int ret;

  ret = xmlTextReaderRead (reader);
  while (ret == 1) {
    //      processNode (reader);
    ret = xmlTextReaderRead (reader);
  }
  xmlFreeTextReader (reader);
  if (ret != 0) {
    printf ("failed to parse\n");
  }
}

int xstream_skip (xmlTextReaderPtr reader) {
  int ret = xmlTextReaderRead (reader);
  while (ret == 1) {
    switch (xmlTextReaderNodeType (reader)) {
    case XML_READER_TYPE_ELEMENT:
      xstream_skip (reader);
      break;
    case XML_READER_TYPE_END_ELEMENT:
      return 0;
    }
  }
  return ret;
}

unsigned char* xmlTextReaderReadBase64(xmlTextReaderPtr reader) {
  const xmlChar *value = xmlTextReaderConstValue (reader);
  if (value == NULL)
    return NULL;

  return base64_decode(value);
}
