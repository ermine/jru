#ifndef _JID_H_
#define _JID_H_

typedef struct {
  char *node;
  char *domain;
  char *resource;
  char *full;
} jid_t;

jid_t *jid_of_string (const char* str);
void jid_free (jid_t *jid);

#endif
