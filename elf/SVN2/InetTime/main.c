
#include "..\inc\swilib.h"
#include "..\inc\pnglist.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include <time.h>
const int minus11=-11;
unsigned short maincsm_name_body[140];
int MAINCSM_ID=0;



extern void kill_data(void *p, void (*func_p)(void *));
void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


void clse(){
  if (MAINCSM_ID){
         CloseCSM(                  MAINCSM_ID);
         MAINCSM_ID=0;
  }
}


int sock;
int connect_state;
char buf[512];

int pbuf;



typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;
/*
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;
*/



/*
int atoi(char *attr)
{
  int ret=0;
  int neg=1;
  for (int k=0; ; k++)
  {
    if ( attr[k]>0x2F && attr[k]<0x3A) {ret=ret*10+attr[k]-0x30;} else { if ( attr[k]=='-') {neg=-1;} else {return(ret*neg);}}
  }
}
*/
extern const char HOST[128];
void create_connect(void)
{
  unsigned int ip;  
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state=0;
  pbuf=0;
  sock=socket(1,1,0);
  if (sock!=-1)
  {
    sa.family=1;
//    sa.port=htons(37);
//    sa.ip=htonl(IP_ADDR(212,192,122,109));    
    sa.port=htons(13);
//    sa.ip=htonl(IP_ADDR(89,178,137,184));    

    sa.ip=htonl(IP_ADDR(192,43,244,18));          
    
    ip=str2ip(HOST);
  if (ip!=0xFFFFFFFF)    sa.ip=ip;      
    
    if (connect(sock,&sa,sizeof(sa))!=-1)
    {
        //    ShowMSG(1,(int)"state 2");
      connect_state=1;
    }
    else{
      ShowMSG(1,(int)"Can`t conect");

      closesocket(sock);
//     CloseCSM( MAINCSM_ID);
             SUBPROC((void *)clse);
    }
  }
}


char req_buf[256];

void send_req(void)
{
  sprintf(req_buf,"\r\n");
  send(sock,req_buf,strlen(req_buf),0);
  connect_state=2;

}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
}

void get_answer(void)
{

  int i=pbuf;
  if (i==511)
    end_socket();
  else
  {
    i=recv(sock,buf+i,511-i,0);
    if (i>=0)
    {
      pbuf+=i;
    }
    else
    {

      end_socket();
      //sock=-1;
      
    }
  }
//  void Parsing();
//          Parsing();
}





 void ConvertTime(TDate *d,TTime *t, struct tm *dos ){
  t->hour=dos->tm_hour;
  t->min=dos->tm_min;
  t->sec=dos->tm_sec;
  t->millisec=0;
  d->day=dos->tm_mday;
  d->year=dos->tm_year+1900;
  d->month=dos->tm_mon+1;
  
}

void Parsing()
{
  //example of ans: 54462 07-12-28 18:55:44 00 0 0 744.7 UTC(NIST) *

  
  if (pbuf<24){  ShowMSG(1,(int)"Not all data transmited");
//    if (pbuf!=4){  ShowMSG(1,(int)"Not all data transmited");
//     CloseCSM( MAINCSM_ID);
  return;
  }
//  LockSched();  

  char *s;
  long  a;
 
  //sscanf (buf,"%d",&a);
  
//  ShowMSG(1,(int)buf);
  long t1;
    struct tm nist;
    memset(&nist,0,sizeof(nist));
   
  sscanf (buf,"%d %d-%d-%d %d:%d:%d",&t1,&nist.tm_year,&nist.tm_mon,&nist.tm_mday,&nist.tm_hour,&nist.tm_min,&nist.tm_sec);
  nist.tm_year+=100;
  nist.tm_mon-=1;  
//   nist.tm_isdst=1;
  a=mktime(&nist);

  s=  ctime((const long*)&a);
//  ShowMSG(1,(int)s);


  int b;
  TDateTimeSettings *ts=RamDateTimeSettings();
  TDate d;
  TTime t;  
 
  struct tm *dos;
  dos=gmtime(&a);   
  ConvertTime(&d,&t,dos);
  b=GetTimeZoneShift(&d,&t,ts->timeZone);
  a+=b*60;
  dos=gmtime(&a);   
  ConvertTime(&d,&t,dos);
  

 


SetDateTime(&d,&t);

s=  ctime((const long*)&a);
  ShowMSG(1,(int)s);
//  SUBPROC((void *)ElfKiller);
// CloseCSM( MAINCSM_ID);

//     CloseCSM( MAINCSM_ID);
}








void maincsm_oncreate(CSM_RAM *data)
{
//  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
//  zeromem(main_gui,sizeof(MAIN_GUI));
/*  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  */
  csm->csm.state=0;
  csm->csm.unk1=0;
//  csm->gui_id=CreateGUI(main_gui);    

  SUBPROC((void *)create_connect);

}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  
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

         
          //Если посылали запрос
          SUBPROC((void *)send_req);
         
        }
        else
        {

          SUBPROC((void *)create_connect); 
         
        }
        break;
      case ENIP_SOCK_DATA_READ:
        if (connect_state==2)
        {

         
          //Если посылали send
          SUBPROC((void *)get_answer);
         
        }
        else
        {

        }
        break;
      case ENIP_SOCK_REMOTE_CLOSED:
        //Закрыт со стороны сервера
        if (connect_state) SUBPROC((void *)end_socket);
//                CloseCSM( MAINCSM_ID);
        break;
      case ENIP_SOCK_CLOSED:
        //Закрыт вызовом closesocket
        if (connect_state) SUBPROC((void *)end_socket);
            SUBPROC((void *)Parsing);


        connect_state=3;
        sock=-1;
        SUBPROC((void *)clse);
        
//         CloseCSM( MAINCSM_ID);
        break;
      }
    }
    
  }
  return(1);
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
    maincsm_onmessage,
    maincsm_oncreate,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose,
sizeof(MAIN_CSM),
1,
&minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"DayTime Protocol (13)");
}



int main()
{
  memset(buf,0,sizeof(buf));
  InitConfig();
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);

  UnlockSched();
  return 0;
}







int itemnum, wd_id;


#define wslen(ws) ws->wsbody[0]
