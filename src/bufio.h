#ifndef _BUFIO_H_
#define _BUFIO_H_

typedef struct {
  int fd;
  char* buf;
  int len;
  int pos;
} bufio_t;

bufio_t* bufio_new ();
void bufio_free (bufio_t* buf);
int bufio_write (bufio_t* buf, int ncount, ...);
int bufio_write_len (bufio_t* buf, const char* str, int len);

#endif
