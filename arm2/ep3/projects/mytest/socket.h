/*
* Библиотека Socket (c++)
* Использование сименс функций
* (с) Danil_e71 2012
*/


#ifndef SOCKET_H
#define SOCKET_H


class Socket
{
public:
int sock;
//standart methods
Socket();
~Socket();
//main methods
void connect(char *hst,int port);
void send(char *bf);
//other methods
void onmessage(int msg);//put this method into onmessage
void SetRecieveBuf(unsigned int size);//set recieve buf
//virtual methods
void (*on_recv)(char *data,int size);
void (*on_connect)();
void (*on_closed)();
void (*on_error)(int err);
};

//own class
unsigned int inet_addr(char *name);

#endif
