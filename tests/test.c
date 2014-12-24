#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ustring.h"
#include "xmpp_prep.h"

int main(int argc, char *argv[]) {
  if (argc < 2)
    return -1;

  char *text = argv[1];
  ustring_t *ustring = malloc (sizeof (ustring_t));
  ustring->ucs4 = NULL;

  if (decode_utf8 (ustring, text, strlen(text)) < 0)
    printf ("error!\n");

  resourceprep (ustring);
  ustring_print (ustring);
  
  ustring_free (ustring);

  return 0;
}
      
