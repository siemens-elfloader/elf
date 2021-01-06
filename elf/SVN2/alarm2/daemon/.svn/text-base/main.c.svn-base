#include "..\..\inc\swilib.h"
#include <stdbool.h>
#include "..\alarm.h"

GBSTMR mytmr;           //таймер проверки времени
GBSTMR *restarttmr;     //таймер повтора звонка
ring_settings* ring;

int IDLECSM_ID=-1;

MYLIST* MySettings[7];
int coord[2]={0,0};
int imgw=0;
int imgh=0;

WSHDR *ews;
int alarm_wd=-1;
TDate date;
TTime time;
bool show_icon=false;
bool need_save_ms=false;

//******************************************************************************

void free_alarms(){
  for (int i=0;i<7;i++){
    MYLIST* l = MySettings[i];
    while(l){
      MYLIST* b = l->next;
      mfree(l);
      l=b;
    }
  }
}

void LoadAlarmConfig(){
  volatile int hFile;
  unsigned int io_error = 0;
  int len=0;
  FSTATS fstat;
  char* data;
  if (GetFileStats(default_cfgfile,&fstat,&io_error)!=-1)
  {
    if ((hFile=fopen(default_cfgfile,A_ReadOnly+A_BIN,P_READ,&io_error))!=-1)
    {
      len=fstat.size;
      if (len>0){
        data=malloc(len+1);
        fread(hFile,data,len,&io_error);
        
        coord[0]=*data;
        coord[1]=*(data+sizeof(int));
        
        int count[7];
        for(int i=0; i<7; i++){
          count[i]=data[2*sizeof(int)+i];
        }
        len=7+2*sizeof(int);
        
        free_alarms();
        for(int i=0; i<7; i++){
          MYLIST *b;
          for (int j=0; j<count[i]; j++){
            MYLIST *l=malloc(sizeof(MYLIST)+1);
            memcpy(l,data+len,sizeof(MYLIST));
            len+=sizeof(MYLIST);
            l->next=0;
            if (j){
              b->next=l;
            }
            else{
              MySettings[i]=l;
            }
            b=l;
          }
        }
        mfree(data);
      }
      fclose(hFile,&io_error);
    }
  }
  imgw=GetImgWidth((int)icon_ms);
  imgh=GetImgHeight((int)icon_ms);
}

void start_ring(){
  ExecuteFile(ews,0,ring);
}

GBSTMR CountTmr[9]={0,0,0,0,0,0,0,0,0};

void start_check(void)
{
  GetDateTime(&date,&time);
  alarm_wd = GetWeek(&date);
  
  MYLIST *l=MySettings[alarm_wd];
  while (l){
    if (l->status==true){
      show_icon=true;
      if((time.hour==l->hour)&&(time.min==l->min)){
        ring=&(l->ring);
        start_ring();
        for(int i = 0; i < l->ring.count; ++i){
          GBS_StartTimerProc(&(CountTmr[i]),216*60*(ring->restart_time)*(i+1),start_ring);
        }
        //ExecuteFile(ews,0,&(l->ring));
      }
    }
    l=l->next;
  }
  
  GBS_StartTimerProc(&mytmr,216*60,start_check);
}

void save_ms(){
  int size = ScreenW()*ScreenH()*2;
  char* data = malloc(size);
  memcpy(data,RamScreenBuffer(),size);
  volatile int hFile;
  unsigned int io_error = 0;
  hFile = fopen(ms_pic,A_WriteOnly + A_Create + A_BIN,P_WRITE, &io_error);
  if(hFile!=-1)
  {
    fwrite(hFile, data, size, &io_error);
    fclose(hFile, &io_error);
  }
  mfree(data);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if (msg->msg == MSG_IPC)
  {
    IPC_REQ *ipc=(IPC_REQ*)((msg)->data0);
    if (ipc)
    {
      if (strcmp_nocase(ipc->name_to,daemon_name) == 0)
      {
        ring=ipc->data;
        GBS_StartTimerProc(&restarttmr,216*60*(ring->restart_time),start_ring);
      }
    }
  }
  
  CSM_RAM *icsm;
  if ((icsm=FindCSMbyID(CSM_root()->idle_id)))
  {
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
    if (IsGuiOnTop(idlegui_id))
    {
      GUI *igui=GetTopGUI();
      if (igui)
      {
#ifdef ELKA
        {
          void *canvasdata = BuildCanvas();
#else
          void *idata = GetDataOfItemByID(igui, 2);
          if (idata)
          {
            void *canvasdata = ((void **)idata)[DISPLACE_OF_IDLECANVAS / 4];
#endif
          DrawCanvas(canvasdata, coord[0], coord[1], coord[0] + imgh, coord[1] + imgh, 1);
          if (need_save_ms){//сохраняем картинку для конфигуратора
            save_ms();
            need_save_ms=false;
          }
          if( IsUnlocked() && show_icon )
          {
            DrawImg(coord[0], coord[1], (int)icon_ms);
          }
        }
      }
    }
  }
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    if (strcmp_nocase(alarm_name,(char *)msg->data0)==0)
    {
      LoadAlarmConfig();
      need_save_ms=true;
    }
  }

  return(1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  ews=AllocWS(128);
  str_2ws(ews,ring_elf,strlen(ring_elf));
  start_check();
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  free_alarms();
  GBS_DelTimer(&mytmr);
  SUBPROC((void *)Killer);
}

static const struct
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),daemon_name);
}

int main(void)
{
  for(int i = 0; i < 7; ++i)
  {
    MySettings[i]=0;
  }
  LoadAlarmConfig();
  
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();

  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();

  return 0;
}

