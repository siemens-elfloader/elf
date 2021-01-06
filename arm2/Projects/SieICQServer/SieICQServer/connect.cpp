#include <winsock2.h>
#include "connect.h"
char cbuff[1024];

int Connect()
{
if (WSAStartup ( 0x202, ( WSADATA * ) &cbuff [ 0 ] ) )goto error;
sock=socket ( AF_INET, SOCK_STREAM, 0 );
if(sock < 0)goto error;
dest_addr.sin_family=AF_INET;
dest_addr.sin_port=htons(PORT);
if(inet_addr(SERVERADDR)!=INADDR_NONE)
dest_addr.sin_addr.s_addr=inet_addr(SERVERADDR) ;
else
if(hst=gethostbyname(SERVERADDR))((unsigned long*)&dest_addr.sin_addr)[0]=((unsigned long**)hst->h_addr_list)[0][0];
else goto error;
if(connect(sock,(sockaddr*)&dest_addr,sizeof(dest_addr))== SOCKET_ERROR)goto error;
return 1;
error:
closesocket(sock);
WSACleanup();
return -1;
}

void Close()
{
closesocket(sock);
WSACleanup();
}