#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ustring.h"
#include "xmpp_prep.h"

static ustring_t *of_hlist (const char* str) {
  int len = 0;
  char *p = (char*) str;

  while (*p != '\0') {
    if (*p == ' ')
      len++;
    p++;
  }
  len++;

  ustring_t *ustring = malloc (sizeof (ustring_t));
  ustring->ucs4= malloc (sizeof (uint32_t) * len);
  ustring->len = len;
  uint32_t *usc4 = ustring->ucs4;

  char *start = (char*) str;
  p = start;
  int i = 0;
  
  for (i = 0; i < len; i++) {
    p = strchr (start, (int) ' ');
    if (p != NULL)
      *p++ = '\0';
    
    *usc4++ = (uint32_t) strtol (start, NULL, 16);
    start = p;
  }
  return ustring;
}
    
int main (int argc, char *argv[]) {
  FILE *fh;

  fh = fopen (argv[1], "r+");
  if (fh == NULL) {
    perror ("fopen");
    exit (EXIT_FAILURE);
  }

  char line[1024];
  int count = 0;
  
  while (!feof (fh)) {
    fgets (line, 1024, fh);

    if (line[0] == '\0' || line[0] == '#' || line[0] == '@')
      continue;

    printf ("Line: %s\n", line);
    
    char *p = NULL;
    
    char *c1 = line;
    p = strchr (c1, (int) ';');
    if (p != NULL)
      *p = '\0';
    ustring_t *u1 = of_hlist (c1);
    
    char *c2 = ++p;
    p = strchr (c2, ';');
    if (p != NULL)
      *p = '\0';
    ustring_t *u2 = of_hlist (c2);

    char *c3 = ++p;
    p = strchr (c3, ';');
    if (p != NULL)
      *p = '\0';
    ustring_t *u3 = of_hlist (c3);

    char *c4 = ++p;
    p = strchr (c4, ';');
    if (p != NULL)
      *p = '\0';
    ustring_t *u4 = of_hlist (c4);

    ustring_t *r4 = malloc (sizeof (ustring_t));
    r4->len = u4->len;
    r4->ucs4 = malloc (sizeof (uint32_t) * r4->len);
    memcpy (r4->ucs4, u4->ucs4, sizeof (uint32_t) * r4->len);

    char *c5 = ++p;
    p = strchr (c5, ';');
    if (p != NULL)
      *p = '\0';
    ustring_t *u5 = of_hlist (c5);
    
              
    /*
     * NFKC
     * c4 == NFKC(c1) == NFKC(c2) == NFKC(c3) == NFKC(c4) == NFKC(c5)
     */

    nfkc (u1);
    nfkc (u2);
    nfkc (u3);
    nfkc (u4);
    nfkc (u5)
;
    int b1 = ustring_compare (r4, u1);
    int b2 = ustring_compare (r4, u2);
    int b3 = ustring_compare (r4, u3);
    int b4 = ustring_compare (r4, u4);
    int b5 = ustring_compare (r4, u5);

    if (b1 && b2 && b3 && b4 && b5)
      printf ("(%d) this line proceed\n", count);
    else {
      printf ("failed\n\n");
      printf ("c4 = ");
      ustring_print_hex (r4);
      if (!b1) {
        printf ("c4 != nfkc u1\n");
        ustring_print_hex (u1);
      }
      if (!b2) {
        printf ("c4 != nfkc u2\n");
        ustring_print_hex (u2);
      }
      if (!b3) {
        printf ("c4 != nfkc u3\n");
        ustring_print_hex (u3);
      }
      if (!b4) {
        printf ("c4 != nfkc u4\n");
        ustring_print_hex (u4);
      }
      if (!b5) {
        printf ("c4 != nfkc u5\n");
        ustring_print_hex (u5);
      }
      
      // exit (EXIT_FAILURE);
    }
    ustring_free (u1);
    ustring_free (u2);
    ustring_free (u3);
    ustring_free (u4);
    ustring_free (u5); 
    ustring_free (r4);
   
    count++;
  }

  printf ("Proceed %d lines\n\n", count);

  fclose (fh);
  return 0;
}
