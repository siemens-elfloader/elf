
#ifndef __DSOCKET_H__
#define __DSOCKET_H__


int socket_open_by_host(const char *host, unsigned short port);
int socket_open_by_ip(unsigned int ip, unsigned short port);


#endif
