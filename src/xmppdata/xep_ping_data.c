#include "xep_ping_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_ping = "urn:xmpp:ping";

struct ping_ping_t *
ping_ping_decode (xmlreader_t * reader)
{
  struct ping_ping_t *elm = NULL;
  elm = malloc (sizeof (struct ping_ping_t));
  if (elm == NULL)
    fatal ("ping_ping_t: malloc failed");
  memset (elm, 0, sizeof (struct ping_ping_t));
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
ping_ping_encode (xmlwriter_t * writer, struct ping_ping_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_ping, "ping");
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
ping_ping_free (struct ping_ping_t *data)
{
  if (data == NULL)
    return;
  free (data);
}
