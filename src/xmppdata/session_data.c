#include "session_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_session = "urn:ietf:params:xml:ns:xmpp-session";

struct session_session_t *
session_session_decode (xmlreader_t * reader)
{
  struct session_session_t *elm = NULL;
  elm = malloc (sizeof (struct session_session_t));
  if (elm == NULL)
    fatal ("session_session_t: malloc failed");
  memset (elm, 0, sizeof (struct session_session_t));
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
session_session_encode (xmlwriter_t * writer, struct session_session_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_session, "session");
  if (err != 0)
    return err;
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
session_session_free (struct session_session_t *data)
{
  if (data == NULL)
    return;
  free (data);
}
