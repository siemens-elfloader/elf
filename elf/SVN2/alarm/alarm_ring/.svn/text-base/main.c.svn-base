#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
#include "conf_loader.h"
#include "..\alarm.h"

unsigned short maincsm_name_body[140];
unsigned int my_csm_id = 0;
unsigned int MAINGUI_ID = 0;

extern const char melody[128];
extern const unsigned int play_;
extern const unsigned int vibra_power;
extern const char shcut[64];
extern const int sndVolume;
extern const int profile;
extern const int time;
extern char IMG[];

GBSTMR mytmr;
const int minus11=-11;
WSHDR *ws;
int scr_w;
int scr_h;

int old_light_kb;
int old_light_d;
int old_profile;
GBSTMR restarttmr;
GBSTMR restartmelody;
int file_length;

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

int get_file_size(char* fname)
{
  int f;
  unsigned int err;
  FSTATS fs;
  if ((f=GetFileStats(fname,&fs,&err))==-1)
    return f;
  return (fs.size);
}

int tmp;
void restart_melody();
int findlength(char *playy)
{
#ifdef NEWSGOLD
  file_length=GetWavLen(playy)*216;
  return(file_length);
#else
  TWavLen wl;
  zeromem(&wl, sizeof(wl));
  wl.type=0x2000;
  wl.wfilename=AllocWS(128);
  str_2ws(wl.wfilename,playy,128);
  GetWavLen(&wl);
  FreeWS(wl.wfilename);
  file_length=wl.length/1000*216;
  return (file_length);
#endif
}

void Play(const char *fname)
{
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      
      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=sndVolume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      tmp=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      tmp=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      tmp=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
    else
    {
      ShowMSG(1,(int)no_melody);
    }
}

int play_standart_melody()
{
  int f;
  int i=0;
  unsigned int err;
  unsigned int fsize=get_file_size(profile_pd_file);
  
  if((f=fopen(profile_pd_file,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
  char* buf=malloc(fsize+1);
  char* buf2=buf;
  fread(f,buf,fsize,&err);
  fclose(f,&err);
  
  buf=strstr(buf,alarm_str);
  if(!buf)
  {
    mfree(buf2);
    CloseCSM(my_csm_id);
    ShowMSG(1,(int)no_melody);
    return 0;
  }
  buf+=strlen(alarm_str);
  while ((buf[i]!=10)&&(buf[i+1]!=13))
  {
      i++;
  }
  buf[i+1]=0;
  Play(buf);
  if(findlength(buf))
    GBS_StartTimerProc(&restartmelody,file_length,restart_melody);
  mfree(buf2);
  return 1;
}

void restart_melody()
{
  if (play_==1)
    play_standart_melody();
  else if (play_==0)
    Play(melody);
  GBS_StartTimerProc(&restartmelody,file_length,restart_melody);
}

void LightOff();
void LightOn()
{
  if(vibra_power) SetVibration(vibra_power);
  SetIllumination(0,1,100,0);
  SetIllumination(1,1,100,0);
  GBS_StartTimerProc(&mytmr,100,LightOff);
}

void LightOff()
{
  SetVibration(0);
  GBS_StartTimerProc(&mytmr,100,LightOn);
}

typedef struct
{
  char signature[16];
  unsigned short picnum;
  unsigned short unk1;
  char w; 
  char h; 
  char Compr_Bits;  
}PICHDR;

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void draw_pic()
{
    IMGHDR img;
    img.w = 52;
    img.h = 52;
    img.bpnum = 0x88;
    img.bitmap = IMG;
    DrwImg(&img,37,5, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
}

const char ipc_alarm_name[]="alarm";
const char ipc_alarm_ring_name[]="alarm_ring";

const IPC_REQ gipc={
  ipc_alarm_name,
  ipc_alarm_ring_name,
  NULL
};

void restart()
{
  GBS_DelTimer(&restarttmr);
  GBS_SendMessage(MMI_CEPID,MSG_IPC,time,&gipc);
  GeneralFunc_flag1(((MAIN_CSM*)FindCSMbyID(my_csm_id))->gui_id,1);
}

void OnRedraw()
{
  DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  draw_pic();
  
  TDate date; TTime time;
  GetDateTime(&date,&time);
  wsprintf(ws,"%d:%02d",time.hour,time.min);
  DrawString(ws,0,75,scr_w,172,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"%02d-%02d-%04d",date.day, date.month,date.year);
  DrawString(ws,0,90,scr_w,scr_h,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws, percent_t, alarm_name);
  DrawString(ws,0,60,scr_w,scr_h,FONT_SMALL,3,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  
  TDate date1;
  GetDateTime(&date1,0);
  char wd = GetWeek(&date1);
  wsprintf(ws, percent_t, wd2[wd]);
  DrawString(ws,0,105,scr_w,scr_h,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  ws=AllocWS(128);
  SetIllumination(1,1,100,0);
  SetIllumination(0,1,100,0);
  GBS_StartTimerProc(&restarttmr,216*60*5,restart);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  GBS_DelTimer(&restarttmr);
  FreeWS(ws);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:  return(1);
    case LEFT_SOFT: restart(); break;
#ifdef NEWSGOLD
    case RED_BUTTON:  return(1);
#endif
    }
  }
  return(0);
}

  extern void kill_data(void *p, void (*func_p)(void *));
#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
}
#endif

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
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
  
  LightOn();
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{  
  GBS_DelTimer(&mytmr);
  GBS_DelTimer(&restartmelody);
  SetVibration(0);
  SetIllumination(0,1,old_light_d,0);
  SetIllumination(1,1,old_light_kb,0);  
  if (profile)
    SetProfile(old_profile);
  
  PlayMelody_StopPlayback(tmp);
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"alarm ring");
}

void play_sound()
{
  switch (play_)
  {
  case 1:
      {
        if(play_standart_melody())
        {
          LockSched();
          char dummy[sizeof(MAIN_CSM)];
          UpdateCSMname();
          my_csm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
          UnlockSched();
        }
      } 
      break;
  case 0:
    {
      LockSched();
      char dummy[sizeof(MAIN_CSM)];
      UpdateCSMname();
      my_csm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
      UnlockSched();
      Play(melody);
      if(findlength((char *)melody))
        GBS_StartTimerProc(&restartmelody,file_length,restart_melody);
    } break;
#ifndef NEWSGOLD
  case 2: AlarmClockRing(); break;
  case 3:
    {
      typedef void (*voidfunc)();
      voidfunc pp=(voidfunc)GetFunctionPointer((char *)shcut);
      if(pp!=0) pp();
    }
/*#else
  case 3:
    {
      typedef void (*voidfunc)();
      voidfunc pp=(voidfunc)(GetFunctionPointer((char *)shcut)+0x10);
      if(pp!=0) pp();
    }*/
#endif
  }
}

int main(char *exename, const char *fname)
{
  InitConfig();
  if(strcmp_nocase(fname,param_new_cfg) == 0) return 0;
  scr_w=ScreenW()-1;
  scr_h=ScreenH()-1;
  
  old_light_d=GetIlluminationDataTable()[3];
  old_light_kb=GetIlluminationDataTable()[155];
  old_profile=GetProfile();
  
  if (profile)
    SetProfile(0);
  
  if (!IsCalling())
  {
    play_sound();
  }
  else
  {
    GBSTMR *calltmr;
    GBS_StartTimerProc(&calltmr,216*60*5,play_sound);
  }
  return 0;
}
