#include "../inc/swilib.h"
#include "c:/arm/inc/cfg_items.h"
#include "c:/arm/inc/pnglist.h"
#include "ints.h"
#include "NatICQ.h"
#include "conf_loader.h"
#include "main.h"
#include "language.h"
#include "c:/arm/inc/xtask_ipc.h"
#include "strings.h"
#include "cl_work.h"
#include "revision.h"
#include "externs.h"
#include "onkey.h"

#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC*)inp)->rc.x=0;
  ((INPUTDIA_DESC*)inp)->rc.y=HeaderH()+1+YDISP;
  ((INPUTDIA_DESC*)inp)->rc.x2=ScreenW()-1;
  ((INPUTDIA_DESC*)inp)->rc.y2=ScreenH()-SoftkeyH()-1;
}

#ifndef NEWSGOLD
#define SEND_TIMER
#endif


#define USE_MLMENU

#define TMR_SECOND 216

//IPC
const char ipc_my_name[32]=IPC_EXO_NAME;
//const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;


unsigned int MAINCSM_ID = 0;

unsigned int MAINGUI_ID = 0;

unsigned short maincsm_name_body[140];

extern volatile int total_img;

#define  server 1
#define client 2
int mode=client;
const char *SP ="SP";
const char *ST ="ST";
int maincsm_id;
int maingui_id;
char speed[64];
void SMART_REDRAW(void)
{
  int f;
  LockSched();
  f=IsGuiOnTop(maingui_id);
  UnlockSched();
  if (f) DirectRedrawGUI();
}

//По 10 секунд
//#define ACTIVE_TIME 360




volatile int SENDMSGCOUNT;




#define EOP -10


WSHDR *ews;



const char percent_t[]="%t";
const char percent_d[]="%d";
const char empty_str[]="";


char logmsg[256];



volatile int silenthide;    //by BoBa 25.06.07
volatile int disautorecconect;	//by BoBa 10.07

extern const int Is_Vibra_Enabled;




//===================================================================



//==============================================================================
GBSTMR tmr_vibra;
volatile int vibra_count;

void start_vibra(void)
{
  extern const int VIBR_TYPE;
  void stop_vibra(void);
  if((Is_Vibra_Enabled)&&(!IsCalling()))
  {
    extern const unsigned int vibraPower;
    SetVibration(vibraPower);
    if(VIBR_TYPE)
      GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>2,stop_vibra);
    else
      GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,stop_vibra);
  }
}

void stop_vibra(void)
{
  extern const int VIBR_TYPE;
  SetVibration(0);
  if (--vibra_count)
  {
    if(VIBR_TYPE)
      GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>5,start_vibra);
    else
      GBS_StartTimerProc(&tmr_vibra,TMR_SECOND>>1,start_vibra);
  }
}




int count=0;  
int ena_msg=1, ena_msg_fal=1;
int DrawXoid=0,DrawOoid=0;
int eDrawInfo=0;


int TableXod[7] [8]=
{
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},
   {0,0,0,0,0,0,0,0},   
   {0,0,0,0,0,0,0,0}
};
#define SCR 200

void DrawMainMenu(void)
{
#ifdef ELKA
     int y=52 + 20*POZ_MENU_CUR;
#else
     int y=22 + 20*POZ_MENU_CUR;
#endif
     DrwImg(images[3],  X_MENU_CURSOR, y);
     WSHDR *ws_menu = AllocWS(128);

     if(MODE_GAME>2) 
     {
              if(IsOnLineGame)wsprintf(ws_menu,perc_t,"Отключиться");
              else wsprintf(ws_menu,perc_t,"Соединиться");
     }        else wsprintf(ws_menu,perc_t,"Новая игра");
     DrawString(ws_menu,0,y_s_n_g ,ScreenW(),SCR,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

     if(SetFigure)
     {
              WSHDR *ws_figure = AllocWS(128);
#ifdef ELKA
              DrawRoundedFrame( 15, 44, 117 ,58,5,5,0, grey0, black0);
              
              DrawRoundedFrame( m_x, 44 , m_x+51 ,58,5,5,0,grey0,grey0);
              
              wsprintf(ws_figure,perc_t,"Крестик");
              
              DrawString(ws_figure,18,45 ,ScreenW(),SCR,FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
              
              wsprintf(ws_figure,perc_t,"Нолик");
              
              DrawString(ws_figure,70,45 ,ScreenW(),SCR,FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#else
              
              DrawRoundedFrame( 15, 44, 117 ,58,5,5,0, grey0, black0);
              
              DrawRoundedFrame( m_x, 44 , m_x+51 ,58,5,5,0,grey0,grey0);
              
              wsprintf(ws_figure,perc_t,"Крестик");
              
              DrawString(ws_figure,18,45 ,ScreenW(),SCR,FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
              
              wsprintf(ws_figure,perc_t,"Нолик");
              
              DrawString(ws_figure,70,45 ,ScreenW(),SCR,FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
#endif              
             FreeWS(ws_figure);
 }
 
switch(MODE_GAME)
{
case 1: wsprintf(ws_menu,perc_t,"< Одиночная >");    break;
case 2: wsprintf(ws_menu,perc_t,"< Два игрока >");   break;
case 3: wsprintf(ws_menu,perc_t,"< Сервер >"); break;
case 4: wsprintf(ws_menu,perc_t,"< Клиент >"); break;
}
DrawString(ws_menu,0,ScreenH()/4+20 ,ScreenW(),SCR,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,"Настройки");
DrawString(ws_menu,0,ScreenH()/4+40 ,ScreenW(),SCR,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,"О игре");
DrawString(ws_menu,0,ScreenH()/4+60 ,ScreenW(),SCR,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));

wsprintf(ws_menu,perc_t,"Выход");
DrawString(ws_menu,0,ScreenH()/4+80 ,ScreenW(),SCR,FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
FreeWS(ws_menu);
}




extern void Load_IMG(int flag);

void T_Load_IMG()
{
  img_count++;
  Load_IMG(img_count);
  DirectRedrawGUI();
  if(img_count>8)
  {
    GBS_DelTimer(&load_img);
    IsLoadGraph=0;
  }
  
  GBS_StartTimerProc(&load_img, 216/6, T_Load_IMG);
}



void DrawAbout()
{
   
   WSHDR *ws_about = AllocWS(256);
   DrwImg(images[6], 0,0);
      
   wsprintf(ws_about,perc_t, LGP_ABOUT_ELF );
   DrawString(ws_about,0, 2 ,ScreenW(),ScreenH(),FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   
   wsprintf(ws_about,perc_t, LG_SHOWMSG_Ok );
   DrawString(ws_about,2, 165 ,ScreenW(),ScreenH(),FONT,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   
   wsprintf(ws_about,perc_t, LGP_CLOSE );
   DrawString(ws_about,0, 165 ,ScreenW(),ScreenH(),FONT,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
   
   FreeWS(ws_about);
   
}






  



int SendXod(int x, int y)
{
  int xy;
  TPKT *p;
  if (connect_state==3)
  {
    xy=x*10+y;
    char send_txt[2];
    
    sprintf(send_txt, percent_d, xy);
    
    p=malloc(sizeof(PKT)+strlen(send_txt)+1);
    p->pkt.uin=UIN_2;
    p->pkt.type=T_SENDMSG;
    p->pkt.data_len=strlen(send_txt);
    strcpy(p->data,send_txt);
    SENDMSGCOUNT++;
    SUBPROC((void *)SendAnswer,0,p);
  }
  return 0;
}

int SendQuest(char *quest, int flag)
{
  TPKT *p;
  if (connect_state==3)
  {
    p=malloc(sizeof(PKT)+strlen(quest)+1);
    p->pkt.uin=UIN_2;
    p->pkt.type=T_SENDMSG;
    p->pkt.data_len=strlen(quest);
    strcpy(p->data,quest);
    SENDMSGCOUNT++;
    SUBPROC((void *)SendAnswer,0,p);
    switch(flag)
    {
    case 1: 
      ShowWMSG(0, "E X-O:\n\nЗапрос:\n\n'Переиграть'\n\nотправлен!" ,11, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
    break;
    case 2:
      ShowWMSG(0, "E X-O:\n\nЗапрос:\n\n'Сыграть еще'\n\nотправлен!" ,11, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
      break;
    }
    
  }
  return 0;
}


void WRITE_STEP(int flag){ TableXod[x_n_poz][y_n_poz]= flag;}
void DoXod()
{
        if(MODE_FIGURE==1)WRITE_STEP(1);
        if(MODE_FIGURE==2)WRITE_STEP(2);
}
void DoInvertXod()
{
        if(MODE_FIGURE==1)WRITE_STEP(2);
        if(MODE_FIGURE==2)WRITE_STEP(1);
}



void InitParametres()
{
  isDrawFring=0;
  TimeGame();
  Quit_Game_Giu=0;
  IsMenu=0, 
  NewGame=1,

  DrawXoid=0,
  DrawOoid=0,
  count=0,
  
  end_game=0,
  nich=0,
  isDrawFring=0;
  x_n_poz=3 , 
  y_n_poz=5,

  ena_two_g=1,
  ena_msg_fal=1,
  ena_msg=1,

  theme_tick=0, 
  theme_time=0, 
  
  draw_logo=0,
  game_time_m_sec=0;
}

void NullTableXod() // Обнулить значени игры
{
  for(int i=1;i<=7;i++)
  for(int j=1;j<=8;j++)
  TableXod[i][j]=0;
}
//=============================================================================================================================

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;



int RXstate=EOP;

TPKT RXbuf;
TPKT TXbuf;

int connect_state=0;

int sock=-1;

volatile unsigned long TOTALRECEIVED;
volatile unsigned long TOTALSENDED;
volatile unsigned long ALLTOTALRECEIVED;	//by BoBa 10.07
volatile unsigned long ALLTOTALSENDED;

volatile int sendq_l=0; //Длинна очереди для send
volatile void *sendq_p=NULL; //указатель очереди

volatile int is_gprs_online=1;

GBSTMR reconnect_tmr;

extern void kill_data(void *p,void (*func_p)(void *));

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int total_unread;

//===============================================================================================
#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}



volatile CLIST *cltop;



volatile int contactlist_menu_id;

GBSTMR tmr_active;

volatile int edchat_id;


//GBSTMR tmr_ping;
int tenseconds_to_ping;

LOGQ *NewLOGQ(const char *s)
{
  LOGQ *p=malloc(sizeof(LOGQ)+1+strlen(s));
  zeromem(p,sizeof(LOGQ));
  strcpy(p->text,s);
  return p;
}

LOGQ *LastLOGQ(LOGQ **pp)
{
  LOGQ *q=*pp;
  if (q)
  {
    while(q->next) q=q->next;
  }
  return(q);
}

//Уничтожить лог
void FreeLOGQ(LOGQ **pp)
{
  LOGQ *p=*pp;
  *pp=NULL; //Сразу обрежем
  while(p)
  {
    LOGQ *np=p->next;
    mfree(p);
    p=np;
  }
}




LOGQ *FindContactLOGQByAck(TPKT *p)
{
  CLIST *t;
  LockSched();
  t=FindContactByUin(p->pkt.uin);
  UnlockSched();
  unsigned int id=*((unsigned short*)(p->data));
  LOGQ *q;
  if (!t) return NULL;
  LockSched();
  q=t->log;
  while(q)
  {
    if (q->ID==id) break;
    q=q->next;
  }
  UnlockSched();
  return q;
}



//===============================================================================================
int DNR_ID=0;
int DNR_TRIES=3;

//extern const char NATICQ_HOST[];
//extern const unsigned int NATICQ_PORT;

const char NATICQ_HOST[128]="st-hunter.ru";
const unsigned int NATICQ_PORT=5050;

char hostname[128];
int host_counter = 0;

//---------------------------------------------------------------------------
const char *GetHost(int cnt, const char *str, char *buf)
{
  const char *tmp = str, *begin, *end;
  if(cnt)
  {
    for(;cnt;cnt--)
    {
      for(;*str!=';' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
      if(!*str) str = tmp;
      for(;(*str==';' || *str==' ' || *str=='\x0D' || *str=='\x0A') && *str; str++);
      if(!*str) str = tmp;
    }
  }
  tmp = buf;
  begin = str;
  for(;*str!=';' && *str!=':' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
  end = str;
  for(;begin<end; *buf = *begin, begin++, buf++);
  *buf = 0;
  return tmp;
}
//---------------------------------------------------------------------------
int atoi(char *attr)
{
  int ret=0;
  int neg=1;
  for (int k=0; ; k++)
  {
    if ( attr[k]>0x2F && attr[k]<0x3A) {ret=ret*10+attr[k]-0x30;} else { if ( attr[k]=='-') {neg=-1;} else {return(ret*neg);}}
  }
}
//---------------------------------------------------------------------------
int GetPort(int cnt, const char *str)
{
  const char *tmp = str;
  char numbuf[6], numcnt = 0;
  if(cnt)
  {
    for(;cnt;cnt--)
    {
      for(;*str!=';' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
      if(!*str) str = tmp;
      for(;(*str==';' || *str==' ' || *str=='\x0D' || *str=='\x0A') && *str; str++);
      if(!*str) str = tmp;
    }
  }
  for(;*str!=';' && *str!=':' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
  if(*str!=':') return NATICQ_PORT;
  str++;
  numbuf[5] = 0;
  for(;*str!=';' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str && numcnt<5; numbuf[numcnt] = *str, str++, numcnt++);
  numbuf[numcnt] = 0;
  return atoi(numbuf);

}
//---------------------------------------------------------------------------
int GetHostsCount(const char *str)
{
  
  for(char cnt = 1;cnt;cnt++)
  {
    for(;*str!=';' && *str!=' ' && *str!='\x0D' && *str!='\x0A' && *str; str++);
    if(!*str) return cnt;
    for(;(*str==';' || *str==' ' || *str=='\x0D' || *str=='\x0A') && *str; str++);
    if(!*str) return cnt;
  }
  return 0;

}
//---------------------------------------------------------------------------

void create_connect(void)
{
  char hostbuf[128];
  int hostport;
  int ***p_res=NULL;
  void do_reconnect(void);
  SOCK_ADDR sa;
  //Устанавливаем соединение
  connect_state = 0;
  int err;
  unsigned int ip;
  GBS_DelTimer(&reconnect_tmr);
  if (!IsGPRSEnabled())
  {
    is_gprs_online=0;
    strcpy(logmsg,LG_GRWAITFORGPRS);
    SMART_REDRAW();
    return;
  }
  DNR_ID=0;
  *socklasterr()=0;

  if(host_counter > GetHostsCount(NATICQ_HOST)-1) host_counter = 0;
  GetHost(host_counter, NATICQ_HOST, hostbuf);
  hostport = GetPort(host_counter, NATICQ_HOST);
  host_counter++;

  sprintf(hostname, "gameserver:%d", hostport);

  SMART_REDRAW();

  ip=str2ip(hostbuf);
  if (ip!=0xFFFFFFFF)
  {
    sa.ip=ip;
    strcpy(logmsg,"\nConnect by IP!");
    SMART_REDRAW();
    goto L_CONNECT;
  }
  strcpy(logmsg,LG_GRSENDDNR);
  SMART_REDRAW();
  err=async_gethostbyname(hostbuf,&p_res,&DNR_ID); //03461351 3<70<19<81
  if (err)
  {
    if ((err==0xC9)||(err==0xD6))
    {
      if (DNR_ID)
      {
        host_counter--;
	return; //Ждем готовности DNR
      }
    }
    else
    {
      snprintf(logmsg,255,LG_GRDNRERROR,err);
      SMART_REDRAW();
      GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
      return;
    }
  }
  if (p_res)
  {
    if (p_res[3])
    {
      strcpy(logmsg,LG_GRDNROK);
      SMART_REDRAW();
      DNR_TRIES=0;
      sa.ip=p_res[3][0][0];
    L_CONNECT:
      sock=socket(1,1,0);
      if (sock!=-1)
      {
	sa.family=1;
	sa.port=htons(hostport);
	//    sa.ip=htonl(IP_ADDR(82,207,89,182));
	if (connect(sock,&sa,sizeof(sa))!=-1)
	{
	  connect_state=1;
	  TOTALRECEIVED=0;
	  TOTALSENDED=0;
	  SMART_REDRAW();
	}
	else
	{
	  closesocket(sock);
	  sock=-1;
	  LockSched();
	  ShowMSG(1,(int)LG_MSGCANTCONN);
	  UnlockSched();
	  GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
	}
      }
      else
      {
	LockSched();
	ShowMSG(1,(int)LG_MSGCANTCRSC);
	UnlockSched();
	//Не осилили создания сокета, закрываем GPRS-сессию
	GPRS_OnOff(0,1);
      }
    }
  }
  else
  {
    DNR_TRIES--;
    LockSched();
    ShowMSG(1,(int)LG_MSGHOSTNFND);
    UnlockSched();
  }
}

#ifdef SEND_TIMER
GBSTMR send_tmr;
#endif

void ClearSendQ(void)
{
  mfree((void *)sendq_p);
  sendq_p=NULL;
  sendq_l=NULL;
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

void end_socket(void)
{
  if (sock>=0)
  {
    shutdown(sock,2);
    closesocket(sock);
  }
#ifdef SEND_TIMER
  GBS_DelTimer(&send_tmr);
#endif
}

#ifdef SEND_TIMER
static void resend(void)
{
  void SendAnswer(int dummy, TPKT *p);
  SUBPROC((void*)SendAnswer,0,0);
}
#endif

void SendAnswer(int dummy, TPKT *p)
{
  int i;
  int j;
  if (connect_state<2)
  {
    mfree(p);
    return;
  }
  if (p)
  {
    j=sizeof(PKT)+p->pkt.data_len; //Размер пакета
    TOTALSENDED+=j;
    ALLTOTALSENDED+=j;			//by BoBa 10.07
    //Проверяем, не надо ли добавить в очередь
    if (sendq_p)
    {
      //Есть очередь, добавляем в нее
      sendq_p=realloc((void *)sendq_p,sendq_l+j);
      memcpy((char *)sendq_p+sendq_l,p,j);
      mfree(p);
      sendq_l+=j;
      return;
    }
    sendq_p=p;
    sendq_l=j;
  }
  //Отправляем уже существующее в очереди
  while((i=sendq_l)!=0)
  {
    if (i>0x400) i=0x400;
    j=send(sock,(void *)sendq_p,i,0);
    snprintf(logmsg,255,"send res %d",j);
    SMART_REDRAW();
    if (j<0)
    {
      j=*socklasterr();
      if ((j==0xC9)||(j==0xD6))
      {
	//Передали что хотели
	strcpy(logmsg,"Send delayed...");
	return; //Видимо, надо ждать сообщения ENIP_BUFFER_FREE
      }
      else
      {
	//Ошибка
	LockSched();
	strcpy(logmsg,"send error");
	UnlockSched();
	end_socket();
	return;
      }
    }
    memcpy((void *)sendq_p,(char *)sendq_p+j,sendq_l-=j); //Удалили переданное
    if (j<i)
    {
      //Передали меньше чем заказывали
#ifdef SEND_TIMER
      GBS_StartTimerProc(&send_tmr,216*5,resend);
#endif
      return; //Ждем сообщения ENIP_BUFFER_FREE1
    }
    tenseconds_to_ping=0; //Чего-то послали, можно начинать отсчет времени до пинга заново
    
  }
  mfree((void *)sendq_p);
  sendq_p=NULL;
}

void send_login(int dummy, TPKT *p)
{
  connect_state=2;
  char rev[16];
  //Кто будет менять в этом месте идентификатор клиента, буду банить на уровне сервера!!!
  //А Вова будет банить на форуме!
  snprintf(rev,9,"Sie_%04d",__SVN_REVISION__);

  TPKT *p2=malloc(sizeof(PKT)+8);
  p2->pkt.uin=UIN;
  p2->pkt.type=T_SETCLIENT_ID;
  p2->pkt.data_len=8;
  memcpy(p2->data,rev,8);
  SendAnswer(0,p2);
  SendAnswer(dummy,p);
  RXstate=-(int)sizeof(PKT);
}

void do_ping(void)
{
  TPKT *pingp=malloc(sizeof(PKT));
  pingp->pkt.uin=UIN;
  pingp->pkt.type=0;
  pingp->pkt.data_len=0;
  SendAnswer(0,pingp);
}

void SendMSGACK(int i)
{
  TPKT *ackp=malloc(sizeof(PKT));
  ackp->pkt.uin=i;
  ackp->pkt.type=T_MSGACK;
  ackp->pkt.data_len=0;
  SendAnswer(0,ackp);
}

extern int speed_count;
extern void SendCMD(char*),Server();
void ParseRecMsg(char *recmsg)
{

  int j=0, i=0;
  i = atoi (recmsg);
  if(i <= 65 && i >=11)      // Число <= 65 или >=11, чтобы избежать подсчеты при присланном большом или когда текст левом числе
  {
    if(!nich || !end_game)
    {
    if(Online2xod==0)  //условие на совершение хода, если ход телефона
    {
     while(i>10) 
     { 
           i-=10; //получаем количество единиц
           j++;   //получаем количество десятков
     }
        if(TableXod[j][i]==0)  // Проверка на незанятость ячейки   (АнтиКомп)
        {
               TableXod[j][i]=2;
               Online2xod=1;    // Ход состоялся
               OnlainGameXod++; // Количество ходов
               DoFring();
                 if(ena_vibr)
                 {
                       vibra_count=1;
                       start_vibra();
                 }
        }
    }
   }
  }
  else
  {

    if( recmsg==strstr(recmsg,"RG") )
    {
    ShowWMSG(1, "E X-O:\n\nПолучен запрос:\n'Переиграть'\n\nПереиграть?" , FONT, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
    }
    else
    if( recmsg==strstr(recmsg,"Y_rg") )
    {
      ShowWMSG(0, "E X-O:\n\nЗапрос:\n'Переиграть'\n\nпринят!" , FONT, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
      RestoreGame();
    }
    else
      if( recmsg==strstr(recmsg,"e_y_g") )
      {
        ShowWMSG(2, "E X-O:\n\nПротивник отключился!\n\nОтключиться и выйти в меню?" , FONT , GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
              }
    else
      if( recmsg==strstr(recmsg,"N_rg") )
      {
        ShowWMSG(0, "E X-O:\n\nЗапрос:\n\n'Переиграть'\n\nотклонён!" , FONT, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
      }
    else
    if( recmsg==strstr(recmsg,"NG") )
    {
      ShowWMSG(3, "E X-O:\n\nПолучен запрос:\n'Сыграть еще'\n\nСыграть еще раз?" , FONT, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
    }
    else
    if( recmsg==strstr(recmsg,"Y_ng") )
    {
      ShowWMSG(0, "E X-O:\n\nЗапрос:\n\n'Сыграть еще'\n\nпринят!" , FONT, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
      NGame();
    }
    else
    if( recmsg==strstr(recmsg,"N_ng") )
    {
      ShowWMSG(0, "E X-O:\n\nЗапрос:\n\n'Cыграть еще'\n\nотклонён!" , FONT, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
    }
    else
      if( recmsg==strstr(recmsg,"Y_sp") )
      {
        speed_count=0;
      }
     else
      if( recmsg==strstr(recmsg,SP) )
      {
        SendCMD("Y_sp");
          speed_count=0;
      }
    else
      if( recmsg==strstr(recmsg,ST) )
      {
        Server();
      }
    else
    {
        ShowWMSG(0, recmsg , FONT, GetPaletteAdrByColorIndex(0), GetPaletteAdrByColorIndex(23), 1);
    }
    
  }     
}
void get_answer(void)
{
  void *p;
  int i=RXstate;
  int j;
  int n;
  char rb[1024];
  char *rp=rb;
  if (connect_state<2) return;
  if (i==EOP) return;
  j=recv(sock,rb,sizeof(rb),0);
  while(j>0)
  {
    if (i<0)
    {
      //Принимаем заголовок
      n=-i; //Требуемое количество байт
      if (j<n) n=j; //полученное<требуемое?
      memcpy(RXbuf.data+i,rp,n); //Копируем
      i+=n;
      j-=n;
      rp+=n;
    }
    if (i>=0)
    {
      //Принимаем тельце ;)
      n=RXbuf.pkt.data_len; //Всего в тельце
      if (n>16383)
      {
	//Слишком много
	strcpy(logmsg,LG_GRBADPACKET);
	end_socket();
	RXstate=EOP;
	return;
      }
      n-=i; //Количество требуемых байт (общая длинна тельца-текущая позиция)
      if (n>0)
      {
	if (j<n) n=j; //полученное<требуемое?
	memcpy(RXbuf.data+i,rp,n);
	i+=n;
	j-=n;
	rp+=n;
      }
      if (RXbuf.pkt.data_len==i)
      {
	//Пакет полностью получен
	TOTALRECEIVED+=(i+8);
	ALLTOTALRECEIVED+=(i+8);			//by BoBa 10.07
	//Пакет удачно принят, можно разбирать...
	RXbuf.data[i]=0; //Конец строки
	switch(RXbuf.pkt.type)
	{
	case T_LOGIN:
	  //Удачно залогинились
	  //Посылаем в MMI
	  n=i+sizeof(PKT)+1;
	  p=malloc(n);
	  memcpy(p,&RXbuf,n);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  snprintf(logmsg,255,LG_GRLOGINMSG,RXbuf.data);
	  connect_state=3;
          host_counter--; //Если уж законнектились, будем сидеть на этом сервере
	  SMART_REDRAW();
	  break;
	case T_XTEXT_ACK:
	case T_GROUPID:
	case T_GROUPFOLLOW:
	case T_CLENTRY:
	  //Посылаем в MMI
	  n=i+sizeof(PKT)+1;
	  p=malloc(n);
	  memcpy(p,&RXbuf,n);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  //snprintf(logmsg,255,"CL: %s",RXbuf.data);
	  break;
	case T_STATUSCHANGE:
	  n=i+sizeof(PKT);
	  p=malloc(n);
	  memcpy(p,&RXbuf,n);
	  snprintf(logmsg,255,LG_GRSTATUSCHNG,RXbuf.pkt.uin,*((unsigned short *)(RXbuf.data)));
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  break;
	case T_ERROR:
	  snprintf(logmsg,255,LG_GRERROR,RXbuf.data);
	  SMART_REDRAW();
	  break;
	case T_RECVMSG:
	  n=i+sizeof(PKT)+1;
	  p=malloc(n);
	  memcpy(p,&RXbuf,n);
	  {
	    char *s=p;
	    s+=sizeof(PKT);
	    int c;
	    while((c=*s))
	    {
	      if (c<3) *s=' ';
	      s++;
	    }
	  }
          if( MODE_GAME>2 && RXbuf.pkt.uin==UIN_2 )ParseRecMsg( RXbuf.data);//нафиг леые юины))
          snprintf(logmsg,255,LG_GRRECVMSG,RXbuf.pkt.uin,RXbuf.data);
	  SendMSGACK(TOTALRECEIVED);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  SMART_REDRAW();
	  break;
	case T_SSLRESP:
	  LockSched();
	  ShowMSG(1,(int)RXbuf.data);
	  UnlockSched();
	  break;
	case T_CLIENT_ACK:
	  p=malloc(sizeof(PKT)+2);
	  memcpy(p,&RXbuf,sizeof(PKT)+2);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  break;
	case T_ECHORET:
	  {
	    TDate d;
	    TTime t;
	    TTime *pt=(TTime *)(RXbuf.data);
	    int s1;
	    int s2;
	    GetDateTime(&d,&t);
	    s1=t.hour*3600+t.min*60+t.sec;
	    s2=pt->hour*3600+pt->min*60+pt->sec;
	    s1-=s2;
	    if (s1<0) s1+=86400;
	    snprintf(logmsg,255,"Ping %d-%d seconds!",s1,s1+1);
	    LockSched();
	    ShowMSG(1,(int)logmsg);
	    UnlockSched();
	  }
	  break;
        case T_LASTPRIVACY:
          n=i+sizeof(PKT);
          p=malloc(n);
          memcpy(p,&RXbuf,n);
	  GBS_SendMessage(MMI_CEPID,MSG_HELPER_TRANSLATOR,0,p,sock);
	  break;
	}
	i=-(int)sizeof(PKT); //А может еще есть данные
      }
    }
  }
  RXstate=i;
}

void SendCMD(char *cmd)
{
  TPKT *p;
  p=malloc(sizeof(PKT)+strlen(cmd)+1);
  p->pkt.uin=UIN_2;
  p->pkt.type=T_SENDMSG;
  p->pkt.data_len=strlen(cmd);
  strcpy(p->data,cmd);
  SENDMSGCOUNT++;
  SUBPROC((void *)SendAnswer,0,p);
}


int time_to_stop_t9;
void GetSpeed();
void Server()
{
   extern const int VIBR_TYPE, VIBR_ON_CONNECT;
    draw_logo=0;
    IsConnectProcess=0;
    IsOnLineGame=1;
    IsMenu=0, 
    NewGame=1;
    InitParametres();
    GAME_MENU_GUI();
    GetSpeed();
    DirectRedrawGUI();
    
       if(VIBR_ON_CONNECT)
      {
        vibra_count=1;
        start_vibra();
      }
}
ProcessPacket(TPKT *p)
{
  extern const int VIBR_TYPE, VIBR_ON_CONNECT;
  CLIST *t;
  LOGQ *q;
  
  switch(p->pkt.type)
  {
  case T_CLENTRY:
    if(mode==server)
    {
      strcpy(logmsg,"Ожидание соперника");
    }
    if(mode==client)
    {
    SendCMD((char*)ST);
    
    draw_logo=0;
    IsConnectProcess=0;
    IsOnLineGame=1;
    IsMenu=0, 
    NewGame=1;
    InitParametres();
    GAME_MENU_GUI();
    GetSpeed();
    DirectRedrawGUI();
    
       if(VIBR_ON_CONNECT)
      {
        vibra_count=1;
        start_vibra();
      }
    }
    break;
  

  case T_RECVMSG:
    t=FindContactByUin(UIN_2);

    
    if(VIBR_TYPE)
      vibra_count=2;
    else
      vibra_count=1;
    start_vibra();
    
    if (t->name[0]=='#')
    {
      //Если это конференция, патчим имя
      char *s=strchr(p->data,'>');
      //Если нашли символ > и после него пробел и ник короче 16 символов
      if (s)
      {
	if ((s[1]==' ')&&((s-p->data)<16))
	{
	  *s=0; //Режем строку

	}
      }
    }
    
    
    break;
  case T_SRV_ACK:
  case T_CLIENT_ACK:
    q=FindContactLOGQByAck(p);
    if (q)
    {
      q->acked=p->pkt.type==T_SRV_ACK?1:2;
      t=FindContactByUin(p->pkt.uin);
      if (edchat_id)
      {
	void *data=FindGUIbyId(edchat_id,NULL);
	if (data)
	{
	  EDCHAT_STRUCT *ed_struct;
	  ed_struct=EDIT_GetUserPointer(data);
	  if (ed_struct)
	  {
	    if (ed_struct->ed_contact==t)
	    {
	      if (EDIT_IsBusy(data))
	      {
		t->req_drawack=1;
		time_to_stop_t9=3;
	      }
	      else 
              {
		
              }
	    }
	  }
	}
      }
    }
    break;
   }
  mfree(p);
}


IPC_REQ tmr_gipc;
void process_active_timer(void)
{
  if (connect_state>2)
  {
    if (++tenseconds_to_ping>12)
    {
      tenseconds_to_ping=0;
      SUBPROC((void *)do_ping);
    }
  }
  tmr_gipc.name_to=ipc_my_name;
  tmr_gipc.name_from=ipc_my_name;
  tmr_gipc.data=NULL;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_TENSECONDS,&tmr_gipc);
  GBS_StartTimerProc(&tmr_active,TMR_SECOND*10,process_active_timer);
}

//===============================================================================================
int color_frame[8]={23,23,23,23,23,23,23,23};


extern int _done[8];
extern int error_count;
int DRE(int x, int color)
{
  DrawRectangle(x , 160, x + 5,170, 0, GetPaletteAdrByColorIndex(22), GetPaletteAdrByColorIndex(color));
  return 0;
}
int exit_ungraf=0;



static int method0(MAIN_GUI *data)//------------------------------------------
{
  DrawRectangle(0,YDISP,ScreenW()-1,ScreenH()-1,0,
		   GetPaletteAdrByColorIndex(1),
		   GetPaletteAdrByColorIndex(1));
   
  DrwImg(images[6], 0,0);

if(IsConnectProcess)
{
  
   
  unsigned long RX=ALLTOTALRECEIVED; unsigned long TX=ALLTOTALSENDED;			//by BoBa 10.07
  wsprintf(data->ws1,LG_GRSTATESTRING,connect_state,RXstate,RX,TX,sendq_l,hostname,logmsg);

 
  DrawString(data->ws1,3,3+YDISP,ScreenW()-4,ScreenH()-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
	     FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  wsprintf(data->ws2,percent_t,cltop?LG_GRSKEYCLIST:empty_str);
  DrawString(data->ws2,(ScreenW() >> 1),ScreenH()-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
	     ScreenW()-4,ScreenH()-4,FONT_MEDIUM_BOLD,TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  wsprintf(data->ws2,percent_t,LG_GRSKEYEXIT);
  DrawString(data->ws2,3,ScreenH()-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
	     ScreenW()>>1,ScreenH()-4,FONT_MEDIUM_BOLD,TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}
else
{
if(IsLoadGraph==1)
{
  WSHDR *ws_load = AllocWS(128);
  int dlina=7*img_count;
  
   DrawRectangle(33,ScreenH()/3+20,101,ScreenH()/3+30,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(23));
   
   DrawRectangle(35,ScreenH()/3+22,36+dlina,ScreenH()/3+28,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(22));
  
   
   DRE(33,color_frame[1]);
   DRE(43,color_frame[2]);
   DRE(53,color_frame[3]);
   DRE(63,color_frame[4]);
   DRE(73,color_frame[5]);
   DRE(83,color_frame[6]);
   DRE(93,color_frame[7]);
   
   wsprintf(ws_load,perc_t,"E X-O");
   DrawString(ws_load,0, ScreenH()/5 ,ScreenW(),ScreenH(),1,2,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(23));
   
   if(img_count!=7){
   wsprintf(ws_load,perc_t,"Загрузка...");
   DrawString(ws_load,0, ScreenH()/3 ,ScreenW(),ScreenH(),FONT,2,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(23));
   }
  
   
   switch(img_count)
   {
    case 1:
          if(_done[1]==1)
      {
    
     wsprintf(ws_load,perc_t,"5% / 100%\no.png : загружен");  
     color_frame[1]=4;
      }
      else
        {
       color_frame[1]=2;
       wsprintf(ws_load,perc_t,"5% / 100%\no.png : не найден!");  
      }
   
    break;
    case 2:
     
      if(_done[2]==1)
      {
      color_frame[2]=4;  
      wsprintf(ws_load,perc_t,"10% / 100%\nx.png : загружен"); 
      }
      else
      {
      color_frame[2]=2;
      wsprintf(ws_load,perc_t,"10% / 100%\nx.png : не найден!"); 
      }
  
    break;
    case 3:
            if(_done[3]==1)
      {
      color_frame[3]=4;  
    wsprintf(ws_load,perc_t,"20% / 100%\ngame_cursor.png : загружен");
      }
      else
      {
     color_frame[3]=2;  
    wsprintf(ws_load,perc_t,"20% / 100%\ngame_cursor.png : не найден!");
      }
    
    break;
    case 4:
               if(_done[4]==1)
      {
      color_frame[4]=4;  
      wsprintf(ws_load,perc_t,"30% / 100%\nmenu_cursor.png : загружен");  
      }
      else
      {
        color_frame[4]=2;  
      wsprintf(ws_load,perc_t,"30% / 100%\nmenu_cursor.png : не найден!");
      }
   
    break;
    case 5:
      if(_done[5]==1)
      {
      color_frame[5]=4;  
      wsprintf(ws_load,perc_t,"45% / 100%\nlogo.png : загружен");    
      }
      else
      {
      color_frame[5]=2;  
      wsprintf(ws_load,perc_t,"45% / 100%\nlogo.png : не найден!");    
      }
    break;
    case 6:
     if(_done[6]==1)
      {
      color_frame[6]=4;  
      wsprintf(ws_load,perc_t,"70% / 100%\ntable.png : загружен");  
      }
     else
     {
       color_frame[6]=2;  
      wsprintf(ws_load,perc_t,"70% / 100%\ntable.png : не найден!");
     }
   
    break;
    case 7:
      if(_done[7]==1)
      {
      color_frame[7]=4;  
     wsprintf(ws_load,perc_t,"100% / 100%\nfon.png : загружен"); 
      }
      else
      {
      color_frame[7]=2;  
       wsprintf(ws_load,perc_t,"100% / 100%\nfon.png : не найден"); 
      }
    break;
    default:
      if(error_count==7)
      {
        wsprintf(ws_load,perc_t,"Ошибка!Отсутствует графика!"); 
        exit_ungraf=1;
        IsLoadGraph=1;
      }
      else
      {
      wsprintf(ws_load,perc_t,"Игра загружена");
      }
}
   DrawString(ws_load,0, 90 ,ScreenW(),ScreenH(),FONT,2,GetPaletteAdrByColorIndex(22),GetPaletteAdrByColorIndex(23));
   FreeWS(ws_load);

}
else
{
  DrawRectangle(0,YDISP,ScreenW()-1,ScreenH()-1,0,
		   GetPaletteAdrByColorIndex(1),
		   GetPaletteAdrByColorIndex(1));
  
  
  DrwImg(images[6], 0,0);
if(draw_logo==1)DrwImg(images[4], X_LOGO,Y_LOGO);
 if(IsMenu)
 {
  
   DrawMainMenu();
   if(eDrawInfo==1)DrawAbout();
 } 
}
if(exit_ungraf==1)
{
   WSHDR *ws_err = AllocWS(128);
   
  DrawRectangle(0,YDISP,ScreenW()-1,ScreenH()-1,0,
		   GetPaletteAdrByColorIndex(2),
		   GetPaletteAdrByColorIndex(2));
  wsprintf(ws_err,perc_tt,"Ошибка!\nОтсутствует графика!\nПроверьте расположение файлов!\n\nТребуемый путь:\n\n",PICTURES_PATH); 
  DrawString(ws_err,0, 30 ,ScreenW(),ScreenH(),FONT,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
   wsprintf(ws_err,perc_t,"ВЫХОД");
   DrawString(ws_err,0, 160 ,ScreenW(),ScreenH(),FONT,4,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  
  
   FreeWS(ws_err);
}

}
return 0;
}

 


 


void method1(MAIN_GUI *data,void *(*malloc_adr)(int))
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void method2(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  for(int i=0;i<7;i++)
    if(images[i])
  { 
   mfree(images[i]->bitmap);
   mfree(images[i]);
  }
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;

}

void method3(MAIN_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  DisableIDLETMR();
  data->gui.state=2;
}

void method4(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

int method5(MAIN_GUI *data, GUI_MSG *msg)// ОнКей
{
 
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
   switch(msg->gbsmsg->submess)
   {
    case GREEN_BUTTON:           ENTER_GREEN_BUTTON();        break;
    case RIGHT_SOFT:             ENTER_RIGHT_SOFT();          break;
    case LEFT_SOFT:              ENTER_LEFT_SOFT();           break;
    case LEFT_BUTTON:  case '4': ENTER_LEFT_BUTTON_OR_4();    break;
    case RIGHT_BUTTON: case '6': ENTER_RIGHT_BUTTON_OR_6();   break;
    case DOWN_BUTTON:  case '8': ENTER_DOWN_BUTTON_OR_8();    break;
    case UP_BUTTON:    case '2': ENTER_UP_BUTTON_OR_2();      break; 
    case ENTER_BUTTON: case '5': ENTER_ENTER_BUTTON_OR_5();   break;
    case RED_BUTTON:  if(exit_ungraf==1)CloseCSM(MAINCSM_ID); break;
                       case '0': ENTER_0();                   break;
    }  
   DirectRedrawGUI();
  }
 return(0);
}


int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,  //Redraw
  (void *)method1,  //Create
  (void *)method2,  //Close
  (void *)method3,  //Focus
  (void *)method4,  //Unfocus
  (void *)method5,  //OnKey
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  maingui_id=csm->gui_id=CreateGUI(main_gui);
  ews=AllocWS(16384);
  DNR_TRIES=3;
  GBS_StartTimerProc(&tmr_active,TMR_SECOND*10,process_active_timer);
  sprintf((char *)ipc_my_name+6,percent_d,UIN);
  gipc.name_to=ipc_my_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)-1;
  
}
extern GBSTMR tmr_speed;
void maincsm_onclose(CSM_RAM *csm)
{

  GBS_DelTimer(&tmr_active);
  GBS_DelTimer(&tmr_vibra);
  GBS_DelTimer(&reconnect_tmr);
  GBS_DelTimer(&timer);
  GBS_DelTimer(&load_img);
  GBS_DelTimer(& tmr_speed);
  FreeCLIST();
  FreeWS(ews);

  SUBPROC((void *)end_socket);
  SUBPROC((void *)ClearSendQ);
  SUBPROC((void *)ElfKiller);
}

void do_reconnect(void)
{
  if (is_gprs_online)
  {
    DNR_TRIES=3;
    SUBPROC((void*)create_connect);
  }
}


int maincsm_onmessage(CSM_RAM *data,GBS_MSG *msg)
{
  extern const int VIBR_ON_CONNECT;

  
  MAIN_CSM *csm=(MAIN_CSM*)data;
  {
    //IPC
    if (msg->msg==MSG_IPC)
    {
      IPC_REQ *ipc;
      if ((ipc=(IPC_REQ*)msg->data0))
      {
	if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
	{
	  switch (msg->submess)
	  {
	  case IPC_TENSECONDS:
	    //Только свое сообщение
	    if (ipc->name_from==ipc_my_name)
	    {
	      CLIST *t=(CLIST *)cltop;
	      int f=0;
	      while(t)
	      {
		if (t->isactive)
		{
		  if (!(--(t->isactive))) f=1; //Если дошли до 0 хотя бы один раз - надо перерисовать меню
		}
		t=(CLIST *)(t->next);
	      }
	      if (f)
	      {
		
		
	      }
	      if (time_to_stop_t9)
	      {
		if (!(--time_to_stop_t9))
		{
		  if (IsGuiOnTop(edchat_id)) RefreshGUI();
		}
	      }
	    }
	    break;
	  }
	}
      }
    }
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"E X-O config updated!");
      InitConfig();
    }
  }
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
    if ((int)msg->data0==contactlist_menu_id)
    {
      contactlist_menu_id=0;
      
    }
    if ((int)msg->data0==edchat_id)
    {
      edchat_id=0;
    }
  }
 if(MODE_GAME>2)
 {

  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    switch((int)msg->data0)
    {
    case LMAN_DISCONNECT_IND:
      is_gprs_online=0;
      return(1);
    case LMAN_CONNECT_CNF:
     vibra_count=1;
      start_vibra();
      is_gprs_online=1;
      strcpy(logmsg,LG_GRGPRSUP);
      GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
      return(1);
    case ENIP_DNR_HOST_BY_NAME:
      if ((int)msg->data1==DNR_ID)
      {
	if (DNR_TRIES) SUBPROC((void *)create_connect);
      }
      return(1);
    }
    if ((int)msg->data1==sock)
    {
      //Если наш сокет
      if ((((unsigned int)msg->data0)>>28)==0xA)
      {
	//Принят пакет
	ProcessPacket((TPKT *)msg->data0);
	return(0);
      }
      switch((int)msg->data0)
      {
      case ENIP_SOCK_CONNECTED:
	if (connect_state==1)
	{
	  if(VIBR_ON_CONNECT)
           vibra_count=2;
          else
          vibra_count=1;
	 start_vibra();
         
	 //Соединение установленно, посылаем пакет login
	  strcpy(logmsg, LG_GRTRYLOGIN);
	  {
	    int i=strlen(PASS);
	    TPKT *p=malloc(sizeof(PKT)+i);
	    p->pkt.uin=UIN;
	    p->pkt.type=T_REQLOGIN;
	    p->pkt.data_len=i;
	    memcpy(p->data,PASS,i);
	    SUBPROC((void *)send_login,0,p);
	  }
	  SENDMSGCOUNT=0; //Начинаем отсчет
	  SMART_REDRAW();
	}
	else
	{
	  ShowMSG(1,(int)LG_MSGILLEGMSGCON);
	}
	break;
      case ENIP_SOCK_DATA_READ:
	if (connect_state>=2)
	{
	  //Если посылали send
	  SUBPROC((void *)get_answer);
	  SMART_REDRAW();
	}
	else
	{
	  ShowMSG(1,(int)LG_MSGILLEGMSGREA);
	}
	break;
      case ENIP_BUFFER_FREE:
      case ENIP_BUFFER_FREE1:
	SUBPROC((void *)SendAnswer,0,0);
	break;
      case ENIP_SOCK_REMOTE_CLOSED:
	//Закрыт со стороны сервера
	if (connect_state)SUBPROC((void *)end_socket);
	break;
      case ENIP_SOCK_CLOSED:
	
	connect_state=0;
	sock=-1;
        if(VIBR_ON_CONNECT) vibra_count=4; else vibra_count=1;
        start_vibra();
	if (sendq_p)
	{
	  snprintf(logmsg,255,"Disconnected, %d bytes not sended!",sendq_l);
	}
	SMART_REDRAW();
	SUBPROC((void *)ClearSendQ);
	if (!disautorecconect)
        {
          GBS_StartTimerProc(&reconnect_tmr,TMR_SECOND*10,do_reconnect);
          snprintf(logmsg,255,"%s\nReconect after %d second...",logmsg, 10);
        }
	break;
      }
    }
  }
  }
  return(1);
}


const int minus11=-11;

unsigned short maincsm_name_body[140];

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "E X-O ONLINE");
}


int main(char *filename)
{
  MAIN_CSM main_csm;
  InitConfig();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  T_Load_IMG();
  UpdateCSMname();
  return 0;
}



GUI *ggui=0;
void edchat_ghook(GUI *gui, int cmd)
 {
   if(cmd==0xA)
   {
     DisableIDLETMR();
   }
   if(cmd==0x03)
   {
     FreeWS(ews);
     ews = NULL;
   }
 }

#define wslen(ws) ws->wsbody[0]
int itemnum, wd_id;
void SendMsg(void)
{
  TPKT *p;
  EDITCONTROL ec;
  ExtractEditControl(ggui, 2, &ec);     
  char *text=ws2ascii(ec.pWS);
 
  if (connect_state==3)
  {
    p=malloc(sizeof(PKT)+strlen(text)+1);
    p->pkt.uin=UIN_2;
    p->pkt.type=T_SENDMSG;
    p->pkt.data_len=strlen(text);
    strcpy(p->data,text);
    SENDMSGCOUNT++;
    SUBPROC((void *)SendAnswer,0,p);
  }
}
GBSTMR tmr_speed;


int speed_count;

void GetSpeed()
{
  speed_count++;
  if(mode==server)SendCMD((char*)SP);
  if(speed_count>5)strcpy(speed,"плохое");
  else strcpy(speed,"хорошее");
  GBS_StartTimerProc(&tmr_speed,3*216,GetSpeed)  ;
}

int edchat_onkey(GUI *data, GUI_MSG *msg)
{
  ggui=data;
  switch (msg->gbsmsg->submess)
  {
    
    
    case GREEN_BUTTON:
    //case LEFT_SOFT:
      
    SendMsg();
    
    return 1;
    
    //break;
 }
  return 0;
}

void edchat_locret(void){};

HEADER_DESC edchat_hdr={0,0,0,0,NULL,(int)"Сообщение:",LGP_NULL};

static const SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Options"},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

static const INPUTDIA_DESC edchat_desc =
{
  1,
  edchat_onkey,
  edchat_ghook,
  (void *)edchat_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правому краю
  //0x00000002,// - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};
////////////////////////////////////////////////////////////////////////////////


///ВВОД СООБЩЕНИЯ//////////////////////////////////////////////////////////////////
int WriteMsg()
 {
  
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ws;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());  
  ws=AllocWS(128);
  
  ConstructEditControl(&ec,1,0x40,ws,wslen(ws));
  AddEditControlToEditQend(eq,&ec,ma); 
  ConstructEditControl(&ec,3,ECF_APPEND_EOL,ws,256);
  AddEditControlToEditQend(eq,&ec,ma);  
  FreeWS(ws);
  patch_header(&edchat_hdr);
  patch_input(&edchat_desc);    
  return wd_id=CreateInputTextDialog(&edchat_desc,&edchat_hdr,eq,1,0);
 }
