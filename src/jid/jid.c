#include <malloc.h>
#include <string.h>
#include <string.h>
#include "jid.h"
#include "helpers.h"
#include "xmpp_prep.h"

jid_t *jid_of_string (const char *str) {
  char* node = NULL;
  char* domain = NULL;
  char* resource = NULL;
  
  int len = strlen (str);
  char* end = NULL;
  
  end = strchr (str, '/');
  if (end != NULL) {
    if (*(end+1) != '\0')
      resource = strdup (end+1);
  } else
    end = str+len;

  char* at = memchr (str, '@', end - str);
  if (at != NULL) {
    node = strndup (str, at - str);
    domain = strndup (at+1, end - at - 1);
  } else
    domain = strndup (str, end - str);

  jid_t *jid = malloc (sizeof (jid_t));
  if (jid == NULL)
    fatal ("jid_of_string: malloc failed");
  
  jid->node = node;
  jid->domain = domain;
  jid->resource = resource;
  jid->full = NULL;

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
  if (jid == NULL)
    fatal ("jid_to_string is null");
  
  if (jid->full != NULL)
    return jid->full;
  int len_domain = strlen (jid->domain);
  int len_node = 0, len_resource = 0 + 1;

  if (jid->node != NULL)
    len_node = strlen (jid->node) + 1;
  if (jid->resource != NULL)
    len_resource = strlen (jid->resource) + 1;
      
  jid->full = malloc (sizeof (char) * (len_domain + len_node + len_resource + 1));
  if (jid->full == NULL)
    fatal ("jid_to_string: malloc failed");

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

int jid_resourceprep (const char* str, char** result) {
  ustring_t ustring = { NULL, 0};
  int err = ustring_decode_utf8 (&ustring, str, strlen (str));
  if (err != 0) return err;
  resourceprep (&ustring);

  err = ustring_encode_utf8 (&ustring, result);
  if (err < 0) return err;

  return 0;
}
