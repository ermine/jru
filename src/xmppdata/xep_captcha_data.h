#ifndef _XEP_CAPTCHA_DATA_H_
#define  _XEP_CAPTCHA_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "xep_xdata_data.h"


extern const char *ns_captcha;


struct captcha_captcha_t
{
  struct xdata_x_t *fXdata;
};


struct captcha_captcha_t *captcha_captcha_decode (xmlreader_t * reader);
int captcha_captcha_encode (xmlwriter_t * writer,
			    struct captcha_captcha_t *data);
void captcha_captcha_free (struct captcha_captcha_t *data);
#endif
