#ifndef _CONNECT_H_
#define _CONNECT_H_

int tcp6_connect(const char *hostname, const int port);
int tcp4_connect(const char *hostname, const int port);

#endif
