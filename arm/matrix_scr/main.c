#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "random.h"
#include "conf_loader.h"
#include "local_ipc.h"

const char ipc_my_name[]=IPC_TEXTINFO_NAME;
const IPC_REQ my_ipc={
  ipc_my_name,
  ipc_my_name,
  NULL
};

#define TMR_SECOND 216
GBSTMR mytmr;

void TimerProc(void)
{  
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}

const int minus11=-11;

extern const int cfg_time;
extern const int cfg_sec;
extern const unsigned int cfg_tx;
extern const unsigned int cfg_ty;

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

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

int speed=50;
int rnd=5,y=-10,rx,i,n=1;
int yy[66];
int xx[66],spd[66];
char OBLACK[]={0,0,0,8};
char OOBLACK[]={0,0,0,20};
char WHITE[]={255,255,255,100};
char GREEN[]={30,240,30,100};
char RED[]={255,0,0,100};
char *buf;
int bufsize=256;
int yy[66];
int xx[66];

void window(void)
{
  DrawRoundedFrame(0,0,131,175,0,0,0,OBLACK,OBLACK);
}

void line(int xpos,int y)
{
  DrawRoundedFrame(xpos,y,xpos,y+5,0,0,0,GREEN,GREEN);
  DrawRoundedFrame(xpos,y+5,xpos,y+7,0,0,0,WHITE,WHITE);
}

void time(void)
{
  WSHDR *ws=AllocWS(256);
  TDate date; TTime time; 
  GetDateTime(&date,&time); 
  if(cfg_sec!=1)
  {
    sprintf(buf,"%d:%02d",time.hour,time.min);
    wsprintf(ws,buf);
    DrawString(ws,cfg_tx+5,cfg_ty,cfg_tx+66,cfg_ty+22,0,2,WHITE,OOBLACK);
  }
  else
  {
    sprintf(buf,"%d:%02d:%02d",time.hour,time.min,time.sec);
    wsprintf(ws,buf);
    DrawString(ws,cfg_tx,cfg_ty,cfg_tx+72,cfg_ty+22,0,2,WHITE,OOBLACK);
  }
  FreeWS(ws);
}

GBSTMR matrix,chk;
void UpdateCSMname(void);

void timer(void)
{
  window();
  if(cfg_time==1)
   time();
  for(i=0;i<=65;i++)
  { 
    line(xx[i],yy[i]+=spd[i]);
    if(yy[i]>176) 
    {
      yy[i]-=186;
      spd[i]=random()/50;
      if (spd[i]>5) spd[i]=5;
      if (spd[i]<=0) spd[i]=1;
    } 
  }
  GBS_StartTimerProc(&matrix,262/speed,timer);
}
  
void OnRedraw(MAIN_GUI *data) // OnRedraw
{
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  // Тут можно создать переменные
  
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  // Тут можно освободить выделяемую память
  if(buf) mfree(buf); // Освобождаем память
  GBS_DelTimer(&matrix);
  data->gui.state=1;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  
  GBS_DelTimer(&matrix);
  if (data->gui.state!=2) return;
  RestartIDLETMR();
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int bt=msg->gbsmsg->submess;
    switch(bt)
    {
    case '#':
      GBS_DelTimer(&matrix);
      RestartIDLETMR();
      DirectRedrawGUI();
    }      
  }
  return(0);
}

/*
#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  mfree_adr(data);
}
#else*/
extern void kill_data(void *p, void (*func_p)(void *));
/*
void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
  mfree_adr(data);
}
#endif
*/

int method8(void){return(0);}


int method9(void){return(0);}

// Массив с методами, чтобы дать ОС информацию, какие когда вызывать
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

// Канвас для основного GUI
const RECT Canvas={0,0,129,129};

// Вызывается при создании главного CSM. В данном примере
// создаётся GUI, его ID записывается в MAINGUI_ID
// на всякий случай - вдруг понадобится ;)
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
   GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_UPDATE_STAT,&my_ipc);
}
/*
// Всё ясно из названия ;) оставить как есть
void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}*/
void ElfKiller(void)
{ 
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

// Вызывается при закрытии главного CSM. Тут и вызывается киллер
void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}

// Обработчик событий главного CSM
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
   if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  } 
  return(1); 
}

// Инициализация структуры MAINCSM
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

// Функция, которая устанавливает название этого CSM для X-Task.
/*void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"THE MATRIX");
  FreeWS(ws);
}
*/
static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"the matrix");
}

void check(void)
{
//  if(!IsUnlocked())
    GBS_StartTimerProc(&matrix,262/speed,timer);
  //GBS_StartTimerProc(&chk,262*10,check);
}


// Основная процедура. Она первой получает управление при старте эльфа.
int main()
{
  ShowMSG(1,(int)"Matrix has you!");
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  InitConfig();
  UpdateCSMname();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  for(i=0;i<=65;i++)
  {
    spd[i]=3;
    rx=random();
    yy[i]=rx;
    xx[i]=n;
    n+=2;
  }
  buf=(char *)malloc(bufsize); // Выделяем память и т.п.
  if(!buf) SUBPROC((void *)onClose); // Не получилось - выходим
  SUBPROC((void *)check);
  return 0;
}
