#ifndef _BUFIO_H_
#define _BUFIO_H_

#include <stdint.h>

typedef struct {
  int fd;
  char* buf;
  int length;
  int pos;
} bufio_writer_t;

bufio_writer_t* bufio_writer_new (int fd);
void bufio_writer_free (bufio_writer_t* writer);
void bufio_writer_reset (bufio_writer_t* writer);
int bufio_writer_flush (bufio_writer_t* writer);
int bufio_writer_write (bufio_writer_t* writer, int ncount, ...);
int bufio_writer_write_len (bufio_writer_t* writer, const char* str, int len);

typedef struct {
  int fd;
  int err;
  char* buf;
  int length;
  int read_pos;
  int write_pos;
} bufio_reader_t;

bufio_reader_t* bufio_reader_new (int fd);
void bufio_reader_free (bufio_reader_t* reader);
void bufio_reader_reset (bufio_reader_t* reader);
uint8_t bufio_reader_readbyte (bufio_reader_t* reader);
uint32_t bufio_reader_readrune (bufio_reader_t* reader);

#endif
