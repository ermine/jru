#include <malloc.h>
#include <string.h>
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

char* jid_to_string (jid_t *jid) {
  if (jid->full != NULL)
    return jid->full;
  int len_domain = strlen (jid->domain);
  int len_node = 0, len_resource = 0 + 1;

  if (jid->node != NULL)
    len_node = strlen (jid->node) + 1;
  if (jid->resource != NULL)
    len_resource = strlen (jid->resource) + 1;
      
  jid->full = malloc (sizeof (char) * (len_domain + len_node + len_resource + 1));

  if (jid->node != NULL) {
    strcpy (jid->full, jid->node);
    jid->full[len_node - 1] = '@';
  }

  strcpy (jid->full + len_node, jid->domain);

  if (jid->resource != NULL)
    strcpy (jid->full + len_node + len_domain - 1, jid->resource);

  jid->full[len_node + len_domain + len_resource] = '\0';

  return jid->full;
}
