#include "..\inc\swilib.h"

#define BUFSIZE 500383

#define LOG



int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

char buf[BUFSIZE+1];

int sock;
int connect_state=0;
int pbuf=0;
int traf=0;



GBSTMR mytmr;

void start_again(void);

void create_connect(void)
{
  zeromem(buf,sizeof(buf));
  SOCK_ADDR sa;
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
    sa.port=htons(80);
 //   sa.ip=htonl(IP_ADDR(194,67,45,236));//94.100.178.193
    sa.ip=htonl(IP_ADDR(94,100,178,193));
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
      connect_state=1;
    }
    else
    {
      closesocket(sock);
      GBS_StartTimerProc(&mytmr, 12960, start_again);
    }
  }
  else
    GBS_StartTimerProc(&mytmr, 12960, start_again);
}

void start_again()
{
  if(IsGPRSConnected())
  {
   SUBPROC((void *)create_connect);
  }
  else
   GBS_StartTimerProc(&mytmr, 2160, start_again);
}

void send_req(void)
{
  char *req_buf=malloc(1200);
  sprintf(req_buf,"GET /index.xhtml?&city=%s HTTP/1.1\n"
            "Accept-Language: en-us\n"
              "Accept-Encoding: gzip, deflate\n"
                "User-Agent: Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)\n"
                  "Host: wap.weather.mail.ru\n"
                    "Connection: Close\n"
                      "\n"
                        , id_tower);
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;
  mfree(req_buf);
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
    connect_state=0;
  }
}

int buf_len=0;

void get_answer(void)
{
  int i=pbuf;
  if (connect_state<2) return;
  char s[1024];
  traf+=i=recv(sock,s,sizeof(s),0);
  if(i>0)
  {
    pbuf+=i;
    strcat(buf,s);
  }
  else
  {
    end_socket();
  }
}


//-------------------------------------------------------------//


int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{

  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
        if (connect_state==1)
        {
          //ShowMSG(1,(int)"send req");
          //Если посылали запрос
          SUBPROC((void *)send_req);
        }
        else
          {
          //  ShowMSG(1,(int)"create connect");
          SUBPROC((void *)create_connect);
          }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {
        //  ShowMSG(1,(int)"get_answer");
          //Если посылали send
          SUBPROC((void *)get_answer);
        }
        else
        {
      //    ShowMSG(1,(int)"create_connect");
          SUBPROC((void *)create_connect);
        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
    //    ShowMSG(1,(int)"sock remote closed");
        //Закрыт со стороны сервера
        if (connect_state) SUBPROC((void *)end_socket);
        break;
      case ENIP_SOCK_CLOSED:
  //      ShowMSG(1,(int)"sock closed");
        //Закрыт вызовом closesocket
        if (connect_state) SUBPROC((void *)end_socket);
        connect_state=3;
    //    GBS_StartTimerProc(&delaytmr, 262*10,Parsing);
        Parsing();
//        ShowMSG(1,(int)"all recv!");
        if(ENA_SCROLL)
        {
          SaveWeath();
          GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&gipc);
        }
        sock=-1;
        break;
      }
    }
  }

  return (1);
}








  start_again();

