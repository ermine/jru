#include <stdio.h>
#include <unistd.h>

#include "xmlreader.h"
#include <string.h>

#include <xstream.h>
#include "types.h"
#include "account.h"
#include "stream.h"
#include "errors.h"
#include "helpers.h"
#include "xmppdata/client_data.h"

int xstream_extension_decode (xmlreader_t* reader, extension_t* ext) {
  int i = 0;

  const char* name = xmlreader_get_name (reader);
  const char* namespace = xmlreader_get_namespace (reader);

  void *(*decode) (xmlreader_t* reader);

  for (i = 0; i < extensions_len; i++) {
    if (strcmp ((char*) name, extensions[i].name) == 0 &&
        strcmp ((char*) namespace, extensions[i].namespace) == 0) {
      decode = extensions[i].decode;
      ext->type = extensions[i].type;
      ext->data = decode(reader);
      return reader->err;
    }
  }
  
  return ERR_EXTENSION_NOT_FOUND;
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

void xstream_extension_free (extension_t* ext) {
  if (ext == NULL)
    return;
  int i = 0;
  for (i = 0; i < extensions_len; i++) {
    if (extensions[i].type == ext->type) {
      extensions[i].free (ext->data);
    }
  }
}

int xstream_read (stream_t* strm, extension_t* ext) {
 again:
  xmlreader_stack_clean (&strm->reader, 1);
  xmlreader_read (&strm->reader);
  if (strm->reader.err == 0) {
    xmlreader_next (&strm->reader);
    int ret = xstream_extension_decode (&strm->reader, ext);
    strm->reader.iterator = 0;
    return ret;
  } else if (strm->reader.err == ERR_BUFIO_READER_END_OF_INPUT) {
    strm->reader.err = 0;
      char buf[4096];
      int ret = read (strm->fd, buf, bufio_reader_available (&strm->reader.bufio));
      if (ret > 0) {
        bufio_reader_fill (&strm->reader.bufio, buf, ret);
        goto again;
      } else if (ret == 0)
        return ERR_READ_CLOSE;
      else
        return ERR_READ_ERROR;
  } else
    return strm->reader.err;
}

int xstream_start (int fd, account_t* account) {
  int err = 0;
  stream_t* strm = stream_new (fd, ns_client, "ru", true, NULL);

  err = stream_start (strm, account);
  if (err != 0) return err;

  while (1) {
    extension_t ext;
    err = xstream_read (strm, &ext);
    if (err != 0) return err;
    err = stream_process (strm, account, &ext);
    if (err != 0) return err;
  }

}
