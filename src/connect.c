#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include "srv.h"

void error(const char* msg) {
  perror (msg);
  exit (EXIT_FAILURE);
}

int tcp6_connect(const char *hostname, const int port) {
  int sock;
  struct sockaddr_in6 addr;
  struct hostent *hostento;

  sock = socket (AF_INET6, SOCK_STREAM, 0);
  if (sock < 0)
    return -1;

  char *prefix = "_xmpp-client._tcp.";
  char *name = malloc (sizeof (char) * strlen (prefix) + strlen (hostname) + 1);
  memcpy(name, prefix, strlen (prefix));
  memcpy(name + strlen (prefix), hostname, strlen (hostname));
  name[strlen(prefix)+strlen(hostname)] = '\0';

  printf("Ready name: %s\n", name);

  srv_list *srvlist = srv_lookup(name);
  free (name);

  if (srvlist != NULL) {
    while (1) {
      srv_record *srv = srv_record_get (&srvlist);
      if (srv == NULL) {
        srv_list_destroy (srvlist);
        break;
      }
  
      hostento = gethostbyname2(srv->name, AF_INET6);
      free (srv->name);

      if (hostento == NULL) {
        free (srv);
        continue;
      }
      
      bzero ((char*) &addr, sizeof (addr));
      addr.sin6_flowinfo = 0;
      addr.sin6_family = AF_INET6;
      memmove ((char*) &addr.sin6_addr.s6_addr, (char*) hostento->h_addr, hostento->h_length);
      addr.sin6_port = htons (srv->port);
      free (srv);
      
      if (connect (sock, (struct sockaddr*)  &addr, sizeof (addr)) < 0)
        continue;
      else {
        srv_list_destroy (srvlist);
        return sock;
      }
    }
  }

  // No success connect via SRV, now try A

  hostento = gethostbyname2(hostname, AF_INET6);
  if (hostento == NULL)
    return -1;

  bzero ((char*) &addr, sizeof (addr));
  addr.sin6_flowinfo = 0;
  addr.sin6_family = AF_INET6;
  memmove ((char*) &addr.sin6_addr.s6_addr, (char*) hostento->h_addr, hostento->h_length);
  addr.sin6_port = htons (port);
  
  if (connect (sock, (struct sockaddr*)  &addr, sizeof (addr)) < 0)
    return -1;

  return sock;
}

int tcp4_connect(const char *hostname, const int port) {
  int sock;
  struct hostent *hostento;
  struct sockaddr_in addr;

  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    return -1;

  char *prefix = "_xmpp-client._tcp.";
  char *name = malloc (sizeof (char) * strlen (prefix) + strlen (hostname) + 1);
  memcpy(name, prefix, strlen (prefix));
  memcpy(name + strlen (prefix), hostname, strlen (hostname));
  name[strlen(prefix)+strlen(hostname)] = '\0';

  printf("Ready name: %s\n", name);

  srv_list *srvlist = srv_lookup(name);
  free (name);

  if (srvlist != NULL) {
    while (1) {
      srv_record *srv = srv_record_get (&srvlist);
      if (srv == NULL) {
        srv_list_destroy (srvlist);
        break;
      }
      
      hostento = gethostbyname2(srv->name, AF_INET);
      free (srv->name);

      if (hostento == NULL) {
        free (srv);
        continue;
      }

      bzero((char*) &addr, sizeof(addr));
      addr.sin_family = AF_INET;
      memmove ((char *) &addr.sin_addr.s_addr, (char *) hostento->h_addr, hostento->h_length);
      addr.sin_port = htons (srv->port);
      free (srv);
      
      if (connect(sock, (struct sockaddr *) &addr, sizeof (addr)) < 0)
        continue;
      else {
        srv_list_destroy (srvlist);
        return sock;
      }
    }
  }

  // No success connect via SRV, now try A

  hostento = gethostbyname2(hostname, AF_INET);
  if (hostento == NULL)
    return -1;

  bzero((char*) &addr, sizeof(addr));
  addr.sin_family = AF_INET;
  memmove ((char *) &addr.sin_addr.s_addr, (char *) hostento->h_addr, hostento->h_length);
  addr.sin_port = htons (port);
  
  if (connect(sock, (struct sockaddr *) &addr, sizeof (addr)) < 0)
    return -1;
  
  return sock;
}
