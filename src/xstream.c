#include <stdlib.h>
#include <stdio.h>
#include "connect.h"

/* #include <libxml/xmlreader.h> */

int main(int argc, char* argv[]) {
  int sock;

  if (argc < 2) {
    printf("usage: xstream servername\n");
    exit (EXIT_FAILURE);
  }

  int port = 5222;
  
  sock = tcp6_connect (argv[1], port);
  if (sock < 0) {
    perror ("Unable to use ipv6");
    sock = tcp4_connect(argv[1], port);
    if (sock < 0) {
      perror ("Unable to use ipv4");
      exit (EXIT_FAILURE);
    }
  }
  /*
  ` int fd = 
  ` XmlTextReaderPtr reader = xmlReaderForFd(fd, NULL, NULL, XML_PARSE_NOENT
  ` | XML_PARSE_NOBLANKS
  ` | XML_PARSE_NOCDATA);
  */
  return 0;
}
  
