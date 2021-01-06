#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(linker, "/ENTRY:main")
#define HOST_NAME   "wasm.ru"
#define URL_NAME    "/pub/21/files/lockfileswork/RawRead.rar" 
#define FILE_NAME   "RawRead.rar"
#define HEADER_SIZE 400





int main()
{

struct sockaddr_in servaddr;
    struct hostent *hp;
    int sock_id;
    char message[10240*1024] = {0};
    int msglen;
    char request[3000] = "GET /main.php HTTP/1.0\n"
    "From: Mainerz\nUser-Agent: Crazy\n\n";


    if((sock_id = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Couldn't get a socket.\n"); exit(EXIT_FAILURE);
    }



    memset(&servaddr,0,sizeof(servaddr));

    if((hp = gethostbyname("site.ru")) == NULL) {
        printf("Couldn't get an address.\n"); exit(EXIT_FAILURE);
    }

    memcpy((char *)&servaddr.sin_addr.s_addr, (char *)hp->h_addr, hp->h_length);

    //fill int port number and type
    servaddr.sin_port = htons(80);
    servaddr.sin_family = AF_INET;

    //make the connection
    if(connect(sock_id, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        //fprintf(stderr, "Couldn't connect.\n");
    }
    //send(sock_id,request,strlen(request),0);
    //msglen = recv(sock_id,message,10240*1024,0);
	//std::cout << message;
  printf(message);
  _getch();
	return 0;
}