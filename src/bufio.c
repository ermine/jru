#include <stdlib.h>

#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "bufio.h"
#include "helpers.h"
#include "utf8.h"
#include "errors.h"

bufio_writer_t* bufio_writer_new (int fd) {
  bufio_writer_t* writer = malloc (sizeof (bufio_writer_t));
  if (writer == NULL)
    fatal ("bufio_writer_new: malloc failed");
  
  writer->fd = fd;
  writer->buf = malloc (sizeof (unsigned char) * 1024);
  if (writer->buf == NULL)
    fatal ("bufio_writer_new: malloc failed");
  
  writer->length = 1024;
  writer->pos = 0;
  return writer;
}

void bufio_writer_free (bufio_writer_t* writer) {
  if (writer == NULL)
    return;

  free (writer->buf);
  free (writer);
}

void bufio_writer_reset (bufio_writer_t* writer) {
  writer->pos = 0;
}

int bufio_writer_flush (bufio_writer_t* writer) {
  if (writer == NULL)
    fatal ("bufio_writer_flush: writer is null");

  if (writer->pos == 0)
    return 0;
  
  size_t sent = write (writer->fd, writer->buf, writer->pos);
  if (sent < 0)
    return sent;
  if (sent == 0)
    return ERR_IO_CLOSE;

  fwrite ("OUT: ", 1, 5, stdout);
  fwrite (writer->buf, 1, sent, stdout);
  fwrite ("\n", 1, 1, stdout);
  fflush (stdout);
  
  if (sent < writer->pos) {
    memmove (writer->buf, writer->buf + sent, writer->pos - sent);
    writer->pos -= sent;
  } else {
    writer->pos = 0;
  }
      
  return 0;
}

static inline int bufio_writer_available (bufio_writer_t* writer) {
  return writer->length - writer->pos;
}

int bufio_writer_write (bufio_writer_t* writer, int ncount, ...) {
  if (writer == NULL)
    fatal ("bufio_writer_write: writer is null");

  va_list arg;
  va_start (arg, ncount);

  int i, err;
  
  for (i = 0; i < ncount; i++) {
    char* str = va_arg (arg, char*);
    if (str == NULL)
      continue;
    int len = strlen (str);
    int start = 0;

    while (len - start > bufio_writer_available (writer)) {
      int avl = bufio_writer_available (writer);
      memmove (writer->buf + writer->pos, str + start, avl);
      writer->pos += avl;
      start += avl;
      err = bufio_writer_flush (writer);
      if (err != 0) {
        va_end (arg);
        return err;
      }
    }

    if (len - start > 0) {
      memmove (writer->buf + writer->pos, str + start, len - start);
      writer->pos += len - start;
    }
  }
  va_end (arg);
  return 0;
}

int bufio_writer_write_len (bufio_writer_t* writer, const char* str, int len) {
  if (writer == NULL)
    fatal ("bufio_writer_write_len: writer is null");
  
  memmove (writer->buf + writer->pos, str, len);
  writer->pos += len;

  return 0;
}

void bufio_reader_init (bufio_reader_t* reader) {
  memset (reader, 0, sizeof (bufio_reader_t));
  reader->buf = malloc (sizeof (unsigned char) * 4096);
  if (reader->buf == NULL)
    fatal ("bufio_reader_new: malloc failed");
  
  reader->length = 4096;
  reader->read_pos = reader->write_pos = 0;
  
}

void bufio_reader_free (bufio_reader_t* reader) {
  if (reader == NULL)
    return;

  free (reader->buf);
}

void bufio_reader_reset (bufio_reader_t* reader) {
  reader->err = 0;
  reader->read_pos = reader->write_pos = 0;
}  

inline int bufio_reader_available (bufio_reader_t* reader) {
  return reader->length - reader->write_pos;
}

 int bufio_reader_fill (bufio_reader_t* reader, char* buf, int len) {
  if (reader->read_pos > 0) {
    memmove (reader->buf, reader->buf + reader->read_pos, reader->write_pos - reader->read_pos);
      reader->write_pos -= reader->read_pos;
      reader->read_pos = 0;
    }

  if (reader->write_pos == reader->length)
    fatal ("bufio_reader_fill: buffer is full");

  len = (reader->length - reader->write_pos < len) ? reader->length - reader->write_pos : len;
  memmove (reader->buf + reader->write_pos, buf, len);
  
  fwrite ("IN: ", 1, 4, stdout);
  fwrite (reader->buf + reader->write_pos, 1, len, stdout);
  fwrite ("\n", 1, 1, stdout);
  fflush (stdout);
  
  reader->err = 0;
  reader->write_pos += len;
  return len;
}

uint8_t bufio_reader_get_byte (bufio_reader_t* reader) {
  if (reader == NULL)
    fatal ("bufio_reader_get_byte: reader is null");

  if (reader->read_pos == reader->write_pos) {
    reader->err = ERR_BUFIO_READER_END_OF_INPUT;
    return 0;
  }
    
  uint8_t c = (uint8_t) reader->buf[reader->read_pos];
  reader->read_pos++;
  return c;
}

void bufio_reader_unget_byte (bufio_reader_t* reader) {
  reader->read_pos--;
}

uint32_t bufio_reader_get_rune (bufio_reader_t* reader) {
  uint8_t c1 = bufio_reader_get_byte (reader);
  if (reader->err != 0) return 0;

  int width = utf8_width (c1);
  if (width > 0 && width - 1 + reader->read_pos > reader->write_pos) {
    reader->read_pos--;
    reader->err = ERR_BUFIO_READER_END_OF_INPUT;
    return 0;
  }
  
  switch (width) {
  case 1:
    return (uint32_t) c1;
  case 2: {
    uint8_t c2 = bufio_reader_get_byte (reader);
    if (reader->err != 0) return 0;
    if (c2 >> 6 != 0b10) {
      reader->err = ERR_MALFORMED_UTF8;
      return 0;
    } else
      return ((c1 & 0x1f)  << 6) | (c2 & 0x3f);
  }
  case 3: {
    uint8_t c2 = bufio_reader_get_byte (reader);
    if (reader->err != 0) return 0;
    uint8_t c3 = bufio_reader_get_byte (reader);
    if (reader->err != 0) return 0;
    if ((c2 >> 6 != 0b10) || (c3 >> 6 != 0b10)) {
      reader->err = ERR_MALFORMED_UTF8;
      return 0;
    } else {
      uint32_t code = 
        ((c1 & 0x0f) << 12) | ((c2 & 0x3f) < 6) | (c3 & 0x3f);
      if (code >= 0xd800 && code <= 0xdf00) {
        reader->err = ERR_MALFORMED_UTF8;
        return 0;
      } else
        return code;
    }
  }
  case 4: {
    uint8_t c2 = bufio_reader_get_byte (reader);
    if (reader->err != 0) return 0;
    uint8_t c3 = bufio_reader_get_byte (reader);
    if (reader->err != 0) return 0;
    uint8_t c4 = bufio_reader_get_byte (reader);
    if (reader->err != 0) return 0;

    if ((c2 >> 6 != 0b10) || (c3 >> 6 != 0b10) || (c4 >> 6 != 0b10)) {
      reader->err = ERR_MALFORMED_UTF8;
      return 0;
    } else
      return ((c1 & 0x07) << 18) | ((c2 & 0x3f) << 12) | ((c3 & 0x3f) << 6) | (c4 & 0x3f);
    break;
  }
  default:
    reader->err = width;
    return 0;
  }
}
