#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
 #pragma comment(lib, "ws2_32.lib")



#define EXIT( s )   do { WSACleanup(); exit((s));} while (0)
#define CLOSE( s )  if( closesocket(s)) error(1, errno, "close call error")
   
using namespace std;
char * program_name;
const int NLISTEN = 10;
 
 
void open2(SOCKET s, struct sockaddr_in *peer);
void init(char **argv)
{
    WSADATA wsadata;
    (program_name = strrchr( argv[0], '\\'))?program_name++:(program_name=argv[0]);
    WSAStartup( MAKEWORD(2,2), &wsadata);
}
 
 
int inet_aton(char * cp, struct in_addr * iap)
{
   int rc;
   rc = inet_addr(cp);
   if(rc == -1 && strcmp(cp, "255.255.255.255"))
     return 0;
   iap->s_addr = rc;
   return 1;
}
 
void error(int status, int err, char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "%s: ", program_name);
    va_end(ap);
    if(err)
     fprintf(stderr, ": %s (%d)\n", strerror(err), err);
     if(status)
      EXIT(status);
}
 
 
static void set_address(char * hname, char * sname, struct sockaddr_in * sap, char * protocol)
{
       struct servent *sp;
       struct hostent *hp;
       char *endp;
       short port;
 
       memset(sap, 0, sizeof(*sap));
       sap->sin_family = AF_INET;
       if(hname != NULL)
       {
         if(!inet_aton(hname, &sap->sin_addr))
         {
       hp = gethostbyname(hname);
       if(hp == NULL)
         error(1, 0, "unknown host: %s\n", hname);
         sap->sin_addr = *(struct in_addr *)hp->h_addr;
     }
    }
       else
         sap->sin_addr.s_addr = htonl( INADDR_ANY);
       port=strtol(sname, &endp, 0);
       if(*endp == '\0')
         sap->sin_port = htons(port);
       else
       {
       sp = getservbyname(sname, protocol);
       if(sp==NULL)
         error(1, 0, "unknown service: %s\n", sname);
         sap->sin_port = sp->s_port;
    }
}
 
 
 
SOCKET tcp_client(char *hname, char *sname)
{
    struct sockaddr_in peer;
    SOCKET s;
 
    set_address(hname, sname, &peer, "tcp");
    s=socket(AF_INET, SOCK_STREAM, 0);
    if(s == SOCKET_ERROR)
      error(1, GetLastError(), "socket error");
    if(connect(s, (struct sockaddr *)&peer, sizeof(peer)))
      error(1, GetLastError(), "connect error");
    return s;
}
 
void client(SOCKET s, struct sockaddr_in *peer,char *str,int h);
 void senddata(SOCKET s, struct sockaddr_in *peer,char *str);
 void recvdata(SOCKET s, struct sockaddr_in *peer);
int main(int argc, char *argv[])
{
    struct sockaddr_in peer;
    SOCKET s;
    char CMD[256],C[256];
    init(argv);
    printf("Enter host:\n");
	gets(C);
    s=tcp_client(C, "21");
	printf("Enter UserName:\n");
	gets(C);
	sprintf(CMD,"USER %s\r\n",C);
    client(s, &peer,CMD,2);
	printf("Enter Password:\n");
	gets(C);
	sprintf(CMD,"PASS %s\r\n",C);
    client(s, &peer,CMD,2);

	
	


	g:
	if(strstr(CMD,"EXIT")||strstr(CMD,"exit"))return EXIT_SUCCESS;
	printf("Enter command or exit...\r\n");
a:
	gets(CMD);

	if(strstr(CMD,"RECV")){client(s, &peer,0,3);goto a;}

	sprintf(CMD,"%s\r\n",CMD);
	client(s, &peer,CMD,2);
	goto g;
    return EXIT_SUCCESS;
}
 

void client(SOCKET s, struct sockaddr_in *peer,char *str,int h)
{
	if(h==1||h==2)
	{
	senddata(s,peer,str);
	}

	if(h==2||h==3)
	{
	recvdata(s,peer);
	}

}


void senddata(SOCKET s, struct sockaddr_in *peer,char *str)
{
	int len=strlen(str);
	int size=0;
	char *send_buf=new char(len);
	sprintf(send_buf,str);
	while(size!=len)
	{
		size+=send(s,send_buf+size,len-size,0);
		//printf("send:%s %d\r\n",send_buf+size,size);
	}
}

void recvdata(SOCKET s, struct sockaddr_in *peer)
{
	int size=1;
	char recv_buf[2024];
unsigned long mode = 1; //non-blocking mode
ioctlsocket( s, FIONBIO, &mode );

   while(size!=0)
	{

    size=recv(s, recv_buf, sizeof(recv_buf), 0);
	if(size<0)return;
    recv_buf[size]='\0';
    printf("%s\n",recv_buf);

	}

}


