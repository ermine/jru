#ifndef _STARTTLS_DATA_H_
#define  _STARTTLS_DATA_H_

#include "xmlreader.h"
#include "xmlwriter.h"
#include <string.h>
#include "xstream.h"
#include "types.h"


extern const char *ns_starttls;


struct starttls_starttls_t
{
  bool fRequired;
};


struct starttls_proceed_t
{
};


struct starttls_failure_t
{
};


struct starttls_starttls_t *starttls_starttls_decode (xmlreader_t * reader);
int starttls_starttls_encode (xmlwriter_t * writer,
			      struct starttls_starttls_t *data);
struct starttls_proceed_t *starttls_proceed_decode (xmlreader_t * reader);
int starttls_proceed_encode (xmlwriter_t * writer,
			     struct starttls_proceed_t *data);
struct starttls_failure_t *starttls_failure_decode (xmlreader_t * reader);
int starttls_failure_encode (xmlwriter_t * writer,
			     struct starttls_failure_t *data);
#endif
