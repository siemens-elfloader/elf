
#include <swilib.h>
#include <arpa/inet.h>
#include <spl/coreevent.h>
#include <string.h>
#include <fcntl.h>
#include <spl/socket.h>
#include "socket.h"


int socket_open_by_host(const char *host, unsigned short port)
{
    struct in_addr adr;
    adr.s_addr = gethostbyname(host);
    if(adr.s_addr == (unsigned int)-1) {
        printf("Can`t resolve ip\n");
        return -1;
    }

    printf("Connecting to %s(%s)\n", host, inet_ntoa(adr));

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        printf("Can`t create socket\n");
        return -1;
    }

    printf("socket: %d\n", sock);

    struct sockaddr_in sa;

    sa.sin_family = AF_INET;
    sa.sin_addr = adr;
    sa.sin_port = htons(port);

    printf("Connecting...\n");
    if( connect(sock, (struct sockaddr*)&sa, sizeof sa) ){
        printf("Can`t connect\n");
        close(sock);
        return -1;
    }
    return sock;
}


int socket_open_by_ip(unsigned int ip, unsigned short port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        printf("Can`t create socket\n");
        return -1;
    }

    printf("socket: %d\n", sock);

    struct in_addr adr = {.s_addr = ip};
    struct sockaddr_in sa;

    sa.sin_family = AF_INET;
    sa.sin_addr = adr;
    sa.sin_port = htons(port);

    printf("Connecting...\n");
    if( connect(sock, (struct sockaddr*)&sa, sizeof sa) ){
        printf("Can`t connect\n");
        close(sock);
        return -1;
    }
    printf("Done.\n");

    return sock;
}


