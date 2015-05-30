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
  int err;
  char* buf;
  int length;
  int read_pos;
  int write_pos;
} bufio_reader_t;

void bufio_reader_init (bufio_reader_t* reader);
int bufio_reader_available (bufio_reader_t* reader);
int bufio_reader_fill (bufio_reader_t* reader, char* buf, int len);
void bufio_reader_free (bufio_reader_t* reader);
void bufio_reader_reset (bufio_reader_t* reader);
uint8_t bufio_reader_get_byte (bufio_reader_t* reader);
void bufio_reader_unget_byte (bufio_reader_t* reader);
uint32_t bufio_reader_get_rune (bufio_reader_t* reader);

#endif
