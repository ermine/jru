#ifndef _JID_H_
#define _JID_H_

typedef struct {
  char *node;
  char *domain;
  char *resource;
  char *full;
} jid_t;

jid_t *jid_of_string (const char* str);
char* jid_to_string (jid_t *jid);
void jid_free (jid_t *jid);

int jid_resourceprep (const char* str, char** result);

#endif
