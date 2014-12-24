#include <malloc.h>
#include <string.h>
#include "jid.h"

jid_t *jid_of_string (const char *str) {
  char *node = NULL, *domain = NULL, *resource = NULL, *tmp = NULL;
  char *p = NULL;

  p = strchr (str, '@');
  tmp = (char *)str;

  if (p != NULL) {
    node = strndup (str, (p - str));
    tmp = ++p;
  }
  
  p = strchr (tmp, '/');
  if (p != NULL) {
    domain = strndup (tmp, (p - tmp));
    resource = strdup (++p);
  } else {
    domain = strdup (tmp);
  }

  jid_t *jid = malloc (sizeof (jid_t));
  jid->node = node;
  jid->domain = domain;
  jid->resource = resource;

  return jid;
}


void jid_free (jid_t *jid) {
  if (jid == NULL)
    return;

  if (jid->node != NULL)
    free (jid->node);

  if (jid->domain)
    free (jid->domain);

  if (jid->resource)
    free (jid->resource);

  free (jid);
}
