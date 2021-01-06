#include "C:/arm/inc/swilib.h"
#include "elfsubmainmenu.h"
#include "elfgroop.h"
#include "main.h"

#define LEVELS_NUM 4
//---------------------------------Для соединения-------------------------------
//int request_type=GET_INFO;
int sock;//тип соединения
int connect_state;//статус соединения
char buf[65546];//буфер
char logbuf[1024];//лог
int pbuf;
char INFO_ID[50];
//request_type = SEARCH;
   /* sprintf(logbuf, null_string);
    do_start_connection();*/
//------------------------------------------------------------------------------
//-----------------------------Соединение---------------------------------------


void create_connect(void)
{

  DrawRoundedFrame(0,0,0+131,0+175,0,0,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(2));
  /*SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
 
  sa.family=1;
  sa.port=htons(80);
  sa.ip=htonl(IP_ADDR(212,48,138,20));
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
    if(request_type==GET_INFO)
      sa.ip=htonl(IP_ADDR());
    if(request_type==SEARCH)
      sa.ip=htonl(IP_ADDR());
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
      REDRAW();
    }
    else
      closesocket(sock);
  }*/
};

void Connect(void)
{
  SUBPROC((void *)create_connect);
};

