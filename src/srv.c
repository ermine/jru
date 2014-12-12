/*
 * FC 2052 A DNS RR for specifying the location of services (DNS SRV)
 */

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <arpa/nameser.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>

#include "srv.h"

static void srv_list_sort(srv_list** list) {
  srv_list *head = *list;
  srv_list *t, *t1, *t2, *tt;

  if (head == NULL)
    return;
  
  t1 = head->next;
  while (t1 != NULL) {
    t2 = t1->next;
    for (t = head; t != t1; t = t->next) {
      int reorder =
        (t1->data->prio < t->data->prio) ? 1 :
        (t1->data->weight == 0) ? 0 :
        (t->data->weight == 0) ? 1 : 0;
      if (reorder) {
        t1->next = t;
        for (tt=head; tt->next != t1; tt=tt->next);
        tt->next = t2;
        if (t == head)
          head = t1;
        else {
          for (tt=head; tt->next != t; tt=tt->next);
          tt->next = t1;
        }
        break;
      }
    }
    t1 = t2;
  }
  *list = head;
}

srv_list *srv_lookup (const char* service) {
  int rc;
  unsigned char answer[NS_PACKETSZ];
  HEADER *header;

  if (!(_res.options & RES_INIT)) {
    rc = res_init ();
    if (rc != 0) {
      perror ("res_init");
      return NULL;
    }
  }
  
  rc = res_query(service, C_IN, T_SRV, answer, NS_PACKETSZ);
  if (rc == -1) {
    perror ("res_query");
    return NULL;
  }

  unsigned char *cp, *tcp, *eom;
  
  header = (HEADER *) answer;
  cp = answer + HFIXEDSZ;
  eom = answer + rc;

  uint32_t ancount = ntohs (header->ancount) + ntohs (header->nscount);
  uint32_t qdcount = ntohs (header->qdcount);

  for (; qdcount > 0 && cp < eom; qdcount--) {
    rc = dn_skipname (cp, eom);
    rc += QFIXEDSZ;
    if (rc < 0) {
      perror("dn_skipname");
      return NULL;
    }
    cp += rc;
  }

  char r_name[MAXDNAME+1];
  uint16_t r_class __attribute__ ((unused));
  uint16_t r_type, r_len;
  uint16_t r_ttl __attribute__ ((unused));
  srv_list *srvlist = NULL;
  srv_list *curr = NULL;

  for (; ancount > 0 && cp < eom; ancount--) {
    rc = dn_expand (answer, eom, cp, (void *) r_name, MAXDNAME);
    if (rc < 0) {
      perror("dn_expand");
      return NULL;
    }
    
    cp += rc;

    NS_GET16(r_type, cp);
    NS_GET16(r_class, cp);
    NS_GET32(r_ttl, cp);
    NS_GET16(r_len, cp);

    if(cp + r_len > eom) /* is this check necessary? */
      r_len = eom - cp;
    
    tcp = cp;

    if (r_type == T_SRV) {
      if (INT16SZ * 3 <= r_len) {
        srv_record *srr;
        uint16_t prio, weight, port;
        
        NS_GET16(prio, tcp);
        NS_GET16(weight, tcp);
        NS_GET16(port, tcp);
        
        rc = dn_expand(answer, eom, tcp, (void *) r_name, MAXDNAME);
        if (rc > 0) {
          srr = malloc (sizeof (srv_record));
          srr->prio = prio;
          srr->weight = weight;
          srr->port = port;
          srr->name = strndup(r_name, rc);
          if (srvlist == NULL) {
            srvlist = malloc (sizeof (srv_list));
            srvlist->data = srr;
            srvlist->next = NULL;
            curr = srvlist;
          } else {
            curr->next = malloc (sizeof (srv_list));
            curr = curr->next;
            curr->data = srr;
            curr->next = NULL;
          }
        }
      }
    }
    
    cp += r_len;
  }

  if (srvlist != NULL)
    srv_list_sort (&srvlist);
  return srvlist;
}

void srv_list_destroy (srv_list *list) {
  srv_list *curr = list;
  while (curr != NULL) {
    free (curr->data->name);
    free (curr->data);
    curr = curr->next;
  }
}

srv_record *srv_record_get(srv_list **srvs) {
  if (*srvs == NULL)
    return NULL;

  uint32_t total = 0;
  srv_list *curr = *srvs;
  uint32_t priority = curr->data->prio;
  while (curr != NULL) {
    if (curr->data->prio != priority)
      break;
    total += curr->data->weight;
    curr = curr->next;
  }

  // TODO: init seed()
  int selection = rand() / (RAND_MAX / (total + 1) + 1);
  curr = *srvs;

  srv_list *prev = NULL;
  srv_record *srv = NULL;
  
  while (curr != NULL) {
    if (curr->data->prio != priority) {
      if (prev != NULL)
        prev->next = curr->next;
      else
        *srvs = curr->next;
      srv = curr->data;
      free (curr);
      break;
    }
    selection -= curr->data->weight;
    if (selection <= 0) {
      if (prev != NULL)
        prev->next = curr->next;
      else
        *srvs = curr->next;
      srv = curr->data;
      free (curr);
      break;
    }
    prev = curr;
    curr = curr->next;
  }
  return srv;
}



static void srv_list_display(srv_list *srvs) __attribute__ ((unused));

static void srv_list_display(srv_list *srvs) {
  srv_list *curr = srvs;
  while (curr != NULL) {
    srv_record *srv = curr->data;
    printf("%s %d %d %d\n", srv->name, srv->prio, srv->weight, srv->port);
    curr = curr->next;
  }
  printf("\n");
}
