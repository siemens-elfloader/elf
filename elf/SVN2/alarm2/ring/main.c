#include "..\..\inc\swilib.h"
#include <stdbool.h>
#include "..\alarm.h"

//******************************************************************************

unsigned int my_csm_id = 0;
unsigned int MAINGUI_ID = 0;

WSHDR *ws;
GBSTMR MyTmr;//таймер мигания подсветки
GBSTMR RestartTmr;//таймер рестарта эльфа
GBSTMR RestartMelodyTmr;//таймерперезапуска мелодии(когда закончится)
int scr_w=0;
int scr_h=0;
int ring_logo_x=0;
int text_coord_y=0;
ring_settings* ring;
char MyMelody[128];
int MyMelodyLen=0;

int old_light_kb;
int old_light_d;
int old_profile;

int HStopMelody=0;

typedef struct
{
  GUI gui;
}MAIN_GUI;

//******************************************************************************
int get_file_size(const char* fname)
{
  int f;
  unsigned int err;
  FSTATS fs;
  if ((f=GetFileStats(fname,&fs,&err))==-1)
    return f;
  return (fs.size);
}

void get_standard_melody()
{
  //TODO: поискать в фф похожую функцию (результат по строке из profile.pd)
  int f;
  unsigned int err;
  
  if((f=fopen(profile_pd_file,A_ReadOnly+A_BIN,P_READ,&err))==-1) return;
  unsigned int fsize=get_file_size(profile_pd_file);
  char* buf=malloc(fsize+1);
  char* buf2=buf;
  fread(f,buf,fsize,&err);
  fclose(f,&err);
  
  buf=strstr(buf,profile_pd_magic);
  if(!buf)
  {
    mfree(buf2);
    sprintf(MyMelody,txt_null);
    ShowMSG(1,(int)LGP_NOMELODY);
    return;
  }
  buf+=strlen(profile_pd_magic);
  int start=buf-buf2;
  int i=0;
  while ((buf[i]!=10)&&(buf[i+1]!=13)){
      i++;
  }
  strncpy(MyMelody,buf2+start,i+1);
  mfree(buf2);
}

void Play(char *fname)
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
      _sfo1.volume=ring->volume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      HStopMelody=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      HStopMelody=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      HStopMelody=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
    else
    {
#warning TODO: что-то еще сделать при отсутствии мелодии, а то так можно и проспать...
      ShowMSG(1,(int)LGP_NOMELODY);
    }
}

int findlength(char *file)//длительность мелодии в тиках
{
  FILE_PROP wl;
  zeromem(&wl, sizeof(wl));
  WSHDR *ff=AllocWS(128);
  str_2ws(ff,file,128);
  wl.filename=ff;
#ifdef NEWSGOLD
  WSHDR *fn=AllocWS(128);
  WSHDR *folder=AllocWS(128);
  
  bool is_mp3=(strcmp_nocase(file+strlen(file)-3,"mp3")==0)||(strcmp_nocase(file+strlen(file)-3,"aac")==0);
  
  char* f=file+strlen(file);
  while((*f!='\\') && (f!=file))
    f--;
  int a=f-file;
  str_2ws(fn,f+1,strlen(file)-a);
  str_2ws(folder,file,a+1);
  
  wl.type=is_mp3?0x1800:0x1000;
  GetFileProp(&wl,fn,folder);
  
  FreeWS(fn);
  FreeWS(folder);
#else
  wl.type=0x2000;
  GetFileProp(&wl,0,0);
#endif
  FreeWS(ff);
  
#ifdef NEWSGOLD
  return MyMelodyLen=((is_mp3?(wl.duration_mp3):(wl.duration_wav))*216)/1000;
#else
  return MyMelodyLen=(wl.duration_wav*216)/1000;
#endif
/*#ifdef NEWSGOLD
  return MyMelodyLen=GetWavLen(file)*216;
#else
  TWavLen wl;
  zeromem(&wl, sizeof(wl));
  wl.type=0x2000;
  wl.wfilename=AllocWS(128);
  str_2ws(wl.wfilename,file,128);
  GetWavLen(&wl);
  FreeWS(wl.wfilename);
  return MyMelodyLen=(wl.length*216)/1000;
#endif*/
}

void LightOff();
void LightOn()//мигалка подсветки
{
  if(ring->vibra_power) SetVibration(ring->vibra_power);
  SetIllumination(0,1,100,0);
  SetIllumination(1,1,100,0);
  GBS_StartTimerProc(&MyTmr,100,LightOff);
}

void LightOff()
{
  SetVibration(0);
  SetIllumination(0,1,50,0);
  SetIllumination(1,1,50,0);
  GBS_StartTimerProc(&MyTmr,100,LightOn);
}


IPC_REQ gipc={
  daemon_name,
  ring_name,
  NULL
};

void restart_melody()
{
  Play(MyMelody);
  GBS_StartTimerProc(&RestartMelodyTmr,MyMelodyLen,restart_melody);
}

void restart()
{
  GBS_DelTimer(&RestartTmr);
  gipc.data=ring;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,0,&gipc);
  GeneralFunc_flag1(((MAIN_CSM*)FindCSMbyID(my_csm_id))->gui_id,1);
}

//******************************************************************************

void OnRedraw()
{
  DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  DrawImg(ring_logo_x, 3, (int)ring_logo);
  
  str_2ws(ws,ring->name,63);
  DrawString(ws,0,text_coord_y,scr_w,scr_h,FONT_MEDIUM,3,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  
  TDate date; TTime time;
  GetDateTime(&date,&time);
  wsprintf(ws,"%d:%02d",time.hour,time.min);
  int y_coord=text_coord_y+GetFontYSIZE(FONT_MEDIUM)+3;
  DrawString(ws,0,y_coord,scr_w,172,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"%02d-%02d-%04d",date.day, date.month,date.year);
  y_coord+=GetFontYSIZE(FONT_SMALL)+2;
  DrawString(ws,0,y_coord,scr_w,scr_h,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws, percent_t, weekdays[GetWeek(&date)]);
  y_coord+=GetFontYSIZE(FONT_SMALL)+2;
  DrawString(ws,0,y_coord,scr_w,scr_h,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  ring_logo_x=(scr_w-GetImgWidth((int)ring_logo))/2;
  text_coord_y=3+8+GetImgHeight((int)ring_logo);
  ws=AllocWS(128);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
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

const RECT Canvas={0,0,131,175};
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
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  GBS_DelTimer(&MyTmr);
  GBS_DelTimer(&RestartMelodyTmr);
  GBS_DelTimer(&RestartTmr);
  SetVibration(0);
  SetIllumination(0,1,old_light_d,0);
  SetIllumination(1,1,old_light_kb,0);
  if (ring->set_profile)
    SetProfile(old_profile);
  PlayMelody_StopPlayback(HStopMelody);
  
  SUBPROC((void *)Killer);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), percent_t, ring_name);
}

//-------------------------      MAIN     ------------------------------------//

void init(){
  
  switch (ring->use){
  case 0:
    {
      strcpy(MyMelody,ring->melody);
    }break;
  case 1:
    {
      get_standard_melody();
    }break;
#ifndef NEWSGOLD
  case 2: AlarmClockRing(); return;
  case 3:
    {
      typedef void (*voidfunc)();
      voidfunc pp=(voidfunc)GetFunctionPointer((char *)ring->melody);
      if(pp!=0) pp();
      return;
    }
#endif
  }
  
  Play(MyMelody);
  
  scr_w=ScreenW()-1;
  scr_h=ScreenH()-1;
  
  old_light_d=GetIlluminationDataTable()[3];
  old_light_kb=GetIlluminationDataTable()[155];
  old_profile=GetProfile();
  
  if (ring->set_profile)
    SetProfile(0);
  LightOn();
  
  if(findlength((char *)MyMelody))
    GBS_StartTimerProc(&RestartMelodyTmr,MyMelodyLen,restart_melody);
  
  GBS_StartTimerProc(&RestartTmr,216*60*3,restart);
  
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  my_csm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
}

GBSTMR *calltmr;
void wait_calling(){
  
  if (!IsCalling()){
    init();
  }
  else{
    GBS_StartTimerProc(&calltmr,216*60,wait_calling);
  }
}

int main(char *exename, ring_settings* myring)
{
  if(myring->magic != MYMAGIC){
    ShowMSG(1,(int)LGP_STARTERROR);
    return 0;
  }
  ring=myring;
  wait_calling();
  return 0;
}

