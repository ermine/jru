#include "xep_captcha_data.h"
#include "helpers.h"
#include "errors.h"

const char *ns_captcha = "urn:xmpp:captcha";

struct captcha_captcha_t *
captcha_captcha_decode (xmlreader_t * reader)
{
  struct captcha_captcha_t *elm = NULL;
  elm = malloc (sizeof (struct captcha_captcha_t));
  if (elm == NULL)
    fatal ("captcha_captcha_t: malloc failed");
  memset (elm, 0, sizeof (struct captcha_captcha_t));
  if (xmlreader_skip_element (reader) == -1)
    return NULL;
  return elm;
}

int
captcha_captcha_encode (xmlwriter_t * writer, struct captcha_captcha_t *elm)
{
  int err = 0;
  err = xmlwriter_start_element (writer, ns_captcha, "captcha");
  if (err != 0)
    return err;
  if (elm->fXdata != NULL)
    {
    }
  err = xmlwriter_end_element (writer);
  if (err != 0)
    return err;
  return 0;
}

void
captcha_captcha_free (struct captcha_captcha_t *data)
{
  if (data == NULL)
    return;
  if (data->fXdata != NULL)
    {
    }
  free (data);
}
