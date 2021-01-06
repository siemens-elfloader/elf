#include <swilib.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "socket.h"
#include <arpa/inet.h>

class SOCKET
{
    private:
    int sock;
    int connect_state;
    int PORT;
    char *HOST;
    unsigned int IP(const char *);
    int BUFFSIZE;
    int MAXBUF;



    public:
    SOCKET(char *,int);
    virtual ~SOCKET();
    void set_bufsize(int,int);
    void connectr();
    int sendr(char *);
    int recvr();
    char *buf;
};

SOCKET::SOCKET(char *h,int p)
{
HOST=new char(strlen(h));
buf = new char(BUFFSIZE);
strcpy(HOST,h);
PORT=p;
BUFFSIZE=2024;
MAXBUF=2024*1024;
}

SOCKET::~SOCKET()
{
    delete HOST;
    delete buf;
}

unsigned int SOCKET::IP(const char *ip)
{
    unsigned int A,B,C,D;
    sscanf(ip,"%d.%d.%d.%d",&A,&B,&C,&D);
    return IP_ADDR(A,B,C,D);
}

void SOCKET::connectr()
{
struct sockaddr_in addr;
sock = _socket(AF_INET, SOCK_STREAM, 0);

if(sock!=0)
{
    addr.sin_family = AF_INET;
    addr.sin_port=htons ( PORT );
    addr.sin_addr.s_addr = _htonl(IP(HOST));

    if(_connect(sock, (struct sockaddr *)&addr, sizeof(addr))!=-1)
    {
        connect_state=1;
    }
}
else
{
    connect_state=0;
}

}

int SOCKET::sendr(char *request)
{
    if(!buf)buf = new char(BUFFSIZE);

    connect_state=2;

    return _send(sock,request,strlen(request),0);
}


int SOCKET::recvr()
{

    int j=0;
    int pbuf=0;
    while((j=_recv(sock,buf+pbuf,BUFFSIZE,0))>0)//получаем весь ответ
    {
        pbuf+=j;
        buf[pbuf] = 0;
        buf=(char*)realloc(buf,pbuf+BUFFSIZE);
        if(pbuf>MAXBUF)
        {

            //
        }
    }

buf[pbuf]=0;
return pbuf;
}


void SOCKET::set_bufsize(int size,int max_size)
{
    BUFFSIZE=size;
    MAXBUF=max_size;
}


