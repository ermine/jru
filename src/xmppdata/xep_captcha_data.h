#ifndef _XEP_CAPTCHA_DATA_H_
#define  _XEP_CAPTCHA_DATA_H_

#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <string.h>
#include "xstream.h"
#include "types.h"
#include "xep_xdata_data.h"


extern const char* ns_captcha;


struct captcha_captcha_t {
struct xdata_x_t* fXdata;
};


struct captcha_captcha_t* captcha_captcha_decode(xmlTextReaderPtr reader);
int captcha_captcha_encode(xmlTextWriterPtr writer, struct captcha_captcha_t* data);
#endif
