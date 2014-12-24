#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "connect.h"

/* #include <libxml/xmlreader.h> */

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
  /*
  ` int fd = 
  ` XmlTextReaderPtr reader = xmlReaderForFd(fd, NULL, NULL, XML_PARSE_NOENT
  ` | XML_PARSE_NOBLANKS
  ` | XML_PARSE_NOCDATA);
  */
  }
  config_destroy (config);
  return 0;

 failure:
  config_destroy (config);
  exit (EXIT_FAILURE);
}
  
