#ifndef _XMPP_PREP_H_
#define _XMPP_PREP_H_

#include "ustring.h"

void nodeprep (ustring_t *ustring);
int resourceprep (ustring_t *ustring);
void nameprep (ustring_t *ustring);

int strong_nodeprep (ustring_t *ustring);
void strong_resourceprep (ustring_t *ustring);
int strong_nameprep (ustring_t *ustring);
void nfkc (ustring_t *ustring);

#endif
