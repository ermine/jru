#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "config.h"
#include "connect.h"
#include "xstream.h"

int main(int argc, char* argv[]) {
  config_t *config = config_load ("config.yaml");

  if (config != NULL && config->accounts != NULL) {
    account_t first_account = config->accounts[0];
  
    int sock;

    sock = tcp6_connect (&first_account);
    if (sock < 0) {
      perror ("Unable to use ipv6");
      sock = tcp4_connect(&first_account);
      if (sock < 0) {
        perror ("Unable to use ipv4");
        goto failure;
      }
    }
      
    char* msg = "<dd/>";
    size_t ret = write (sock, msg, strlen(msg));
    if (ret < 0) {
      perror ("write");
      goto failure;
    } else {
      printf ("sent %d\n", (int) ret);
    }

    xstream_read (sock);

    config_destroy (config);
    return 0;
  }
  
 failure:
  printf ("failure\n");
  config_destroy (config);
  exit (EXIT_FAILURE);
}
  
