#include "D:\ARM_ALL\inc\swilib.h"
#include "D:\ARM_ALL\inc\cfg_items.h"
#include "conf_loader.h"

#ifdef NEWSGOLD
  #define max_vol 15
#else
  #define max_vol 14
#endif

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

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

int tp;
GBSTMR timer;
extern const unsigned int refresh;//задаем через сколько секунд обновить
void StartClear()//”брать отображение после отрисовки, если ничего не нажато
{
  tp++;
  if(tp==refresh)
  {
    GBS_DelTimer(&timer);
    REDRAW();
  }
  GBS_StartTimerProc(&timer,217,StartClear);
}

int OptiImg(char* fname)
{
  char vol[128];
  extern const unsigned int icon_x;
  extern const unsigned int icon_y;
  extern const char icon_folder[128];
  sprintf(vol,"%s%s",icon_folder,fname);
  DrawImg(icon_x,icon_y,(int)vol);
  return(0);
}

void Img()
{
  char *p=RamVolumeStep();
  if(*p==0)
  {
    OptiImg("vol0.png");
  }
  if(*p==1)
  {
    OptiImg("vol1.png");
  }
  if(*p==2)
  {
    OptiImg("vol2.png");
  }
  if(*p==3)
  {
    OptiImg("vol3.png");
  }
  if(*p==4)
  {
    OptiImg("vol4.png");
  }
  if(*p==5)
  {
    OptiImg("vol5.png");
  }
  if(*p==6)
  {
    OptiImg("vol6.png");
  }
  if(*p==7)
  {
    OptiImg("vol7.png");
  }
  if(*p==8)
  {
    OptiImg("vol8.png");
  }
  if(*p==9)
  {
    OptiImg("vol9.png");
  }
  if(*p==10)
  {
    OptiImg("vol10.png");
  }
  if(*p==11)
  {
    OptiImg("vol11.png");
  }
  if(*p==12)
  {
    OptiImg("vol12.png");
  }
  if(*p==13)
  {
    OptiImg("vol13.png");
  }
  if(*p==14)
  {
    OptiImg("vol14.png");
  }
#ifdef NEWSGOLD
  if(*p==15)
  {
    OptiImg("vol15.png");
  }
 #endif
}

void Frame()
{
  int pos_status;
  extern const RECT position;
  extern const char color[4];
  extern const char colorR[4];
  extern const char colorF[4];
  DrawRectangle(position.x,position.y,position.x2,position.y2,0,colorR,colorF);
  pos_status=((position.x2-position.x-1)**RamVolumeStep())/max_vol;
  DrawRectangle(position.x+1,position.y+1,pos_status,position.y2-1,0,color,color);
}

void ShowVolume()
{
  void *icsm;
  extern const int ena_gui;
  #define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  if(ena_gui)
  {
    icsm=FindCSMbyID(CSM_root()->idle_id);
    if (icsm)
    {
      if(IsGuiOnTop(idlegui_id(icsm)))
      {
        if(ena_gui==2) return;
      }
      else
        if(ena_gui==1) return;
    }
    else
      if(ena_gui==1) return;
  }
  extern const int type_pic;
  if(*RamIsRunJava()==0)//ѕроверка на яву, если нету, то показываем √ромкость
  {
#ifdef ELKA
    extern const int ena_fon;
    if((!ena_fon)&&(!IsMediaPlayerInBackground()))return;
#endif
    switch(type_pic)
    {
    case 0:
      Img();
      break;
    case 1:
      Frame();
      break;
    }
  }
}

int my_keyhook(int submsg, int msg)
{
  char *p=RamVolumeStep();
  if(msg==KEY_DOWN)
  {
    if(IsPlayerOn()&&IsUnlocked())
    {
      switch(submsg)
      {
      case VOL_UP_BUTTON:
        if(*p<max_vol)
        {
          ShowVolume();
          StartClear();
        }
        break;
      case VOL_DOWN_BUTTON:
        if(*p>1)
        {
          ShowVolume();
          StartClear();
        }
        break;
      }
    }
  }
  return 0;
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
    }
  }
  return (1);
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  RemoveKeybMsgHook((void *)my_keyhook);
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"VolumeIndicator - (c) K-D, VedaN");
}

int main()
{
  InitConfig();
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  AddKeybMsgHook((void *)my_keyhook);
  return 0;
}
