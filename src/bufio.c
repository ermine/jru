#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "bufio.h"
#include "helpers.h"

bufio_t* bufio_new (int fd) {
  bufio_t* buf = malloc (sizeof (bufio_t));
  if (buf == NULL)
    fatal ("bufio_new: malloc failed");
  
  buf->fd = fd;
  buf->buf = malloc (sizeof (unsigned char) * 1024);
  if (buf->buf == NULL)
    fatal ("bufio_new: malloc failed");
  
  buf->len = buf->pos = 0;
  return buf;
}

void bufio_free (bufio_t* buf) {
  if (buf == NULL)
    return;

  free (buf->buf);
  free (buf);
}

int bufio_flush (bufio_t* buf) {
  if (buf == NULL)
    fatal ("bufio_flush: buf is null");

  if (buf->pos == 0)
    return 0;
  
  size_t sent = write (buf->fd, buf->buf, buf->pos);
  if (sent < 0)
    return sent;
  if (sent == 0)
    return -1;

  fwrite (buf->buf, 0, sent, stdout);
  
  if (sent < buf->pos) {
    memmove (buf->buf, buf->buf + sent, buf->pos - sent);
    buf->pos -= sent;
  } else {
    buf->pos = 0;
  }
      
  return 0;
}

static int bufio_available (bufio_t* buf) {
  return buf->len - buf->pos;
}

int bufio_write (bufio_t* buf, int ncount, ...) {
  if (buf == NULL)
    fatal ("bufio_write: buf is null");

  va_list arg;
  va_start(arg, ncount);

  int i, err;
  
  for (i = 0; i < ncount; i++) {
    char* str = va_arg (arg, char*);
    int len = strlen (str);
    int start = 0;

    while (len - start > bufio_available (buf)) {
      int avl = bufio_available (buf);
      memmove (buf->buf + buf->pos, str + start, avl);
      buf->pos += avl;
      start += avl;
      err = bufio_flush (buf);
      if (err != 0) {
        va_end (arg);
        return err;
      }
    }
    
    memmove (buf->buf, str + start, len - start);
    buf->pos += len - start;
  }
  va_end (arg);
  return 0;
}

int bufio_write_len (bufio_t* buf, const char* str, int len) {
  if (buf == NULL)
    fatal ("bufio_write_len: buf is null");
  
  memmove (buf->buf + buf->pos, str, len);
  buf->pos += len;

  return 0;
}
