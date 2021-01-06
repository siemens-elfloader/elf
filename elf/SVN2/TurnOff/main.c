#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"

#ifdef DAEMON
typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;
#endif

extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;
int MAINCSM_ID=0;


extern const char ICONS_SD[128];
extern const char ICONS_RB[128];
extern const char ICONS_SR[128];

extern const int SND_ENA;
extern const unsigned int VOLUME;
extern const char SND_SD[128];
extern const char SND_RB[128];
extern const char SND_SR[128];

extern const unsigned int CLOSE_BTN;
extern const int MODE;

extern const int WHAT_DO;
extern const unsigned int PROFILE;

#ifdef DAEMON
extern const unsigned int CALL_BTN;
#endif
int mode;
//  0 - ждущий режим
//  1 - выключение
//  2 - перезагрузка

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM_GUI;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

//int PLAY_ID;
void Play(const char *fname)
{
  if ((!IsCalling())&&SND_ENA)
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
      _sfo1.volume=VOLUME;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      /*PLAY_ID=*/PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      /*PLAY_ID=*/PlayFile(0xC, sndPath, sndFName, 0,MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      /*PLAY_ID=*/PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
  }
}

void method0(MAIN_GUI *data)
{
 /* DrawRoundedFrame(0,0, ScreenW()-1, ScreenH()-1, 0, 0, 0,
			GetPaletteAdrByColorIndex(23),
			GetPaletteAdrByColorIndex(23));
  */
   int x, y;
   
   switch(mode)
    {
    case 0:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_SR)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_SR)/2;
        DrawImg(x, y, (int)ICONS_SR);
      }
      break;
    case 1:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_SD)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_SD)/2;
        DrawImg(x, y, (int)ICONS_SD);
      }
      break;
    case 2:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_RB)/2;
        y = (ScreenH()-YDISP)/2 - GetImgHeight((int)ICONS_RB)/2;
        DrawImg(x, y, (int)ICONS_RB);
      }
      break;
    }  
}

void method1(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void method2(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  FreeWS(data->ws2);
  data->gui.state=0;
}

void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void DoIt(void)
{
  switch(mode)
    {
      case 0:
        if (WHAT_DO) KbdLock();
          else
            SetProfile(PROFILE-1);
      break;
      case 1:
        SwitchPhoneOff();
      break;
      case 2:
        RebootPhone();
      break;
     }
  CloseCSM(MAINCSM_ID);
  MAINCSM_ID=0;
}

double GetWavkaLength(const char *fname) //тиков
{
  int f;
  unsigned int ul;
  
  int DataLength;//4
  int BytePerSec;//28  
  

  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    lseek(f,4,S_SET,&ul,&ul);
    fread(f,&DataLength,sizeof(DataLength),&ul);
    
    lseek(f,28,S_SET,&ul,&ul);
    fread(f,&BytePerSec,sizeof(BytePerSec),&ul);
    
    fclose(f,&ul);
    
    return (((((double)DataLength/(double)BytePerSec)*(double)1000)*0.216)+50);
  }
    else
      return 0;
}

GBSTMR mytmr;

int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();

  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (msg->gbsmsg->submess==CLOSE_BTN)
    {
        CloseCSM(MAINCSM_ID); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
        MAINCSM_ID=0;
    }
  
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_BUTTON:
    case UP_BUTTON: 
      {
        mode++;
        if (mode==3) mode=0;
      }
      break;
    case LEFT_BUTTON:
    case DOWN_BUTTON:
        mode--;
        if (mode==-1) mode=2;
      break;
     case ENTER_BUTTON:
       switch(mode)
        {
          case 0:
            Play(SND_SR);
            if (SND_ENA) GBS_StartTimerProc(&mytmr,(int)GetWavkaLength(SND_SR),DoIt); else DoIt();
          break;
          case 1:
            Play(SND_SD);
            if (SND_ENA) GBS_StartTimerProc(&mytmr,(int)GetWavkaLength(SND_SD),DoIt); else DoIt();
          break;
          case 2:
            Play(SND_RB);
            if (SND_ENA) GBS_StartTimerProc(&mytmr,(int)GetWavkaLength(SND_RB),DoIt); else DoIt();
          break;
        }
      break;     
    }
  }

  return(0);
}

void method7(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data, mfree_adr);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0, 0, 0, 0};

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

void maincsm_oncreate_GUI(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM_GUI*csm=(MAIN_CSM_GUI*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

#ifndef DAEMON
static void ELF_KILLER(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
#endif
void maincsm_onclose_GUI(CSM_RAM *csm)
{
#ifndef DAEMON
  SUBPROC((void *)ELF_KILLER);
#endif
}

int maincsm_onmessage_GUI(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM_GUI *csm=(MAIN_CSM_GUI*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  
  /*if (msg->msg==MSG_PLAYFILE_REPORT)
    {
      if ((msg->submess>>16)==PLAY_ID) 
      { 
        if (((msg->submess&0xFFFF)==7)||((msg->submess&0xFFFF)==5)) DoIt();
      }
        else
          PLAY_ID=0;
    }*/  
  
  return(1);
}

unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name_GUI;
}MAINCSM =
{
  {
    maincsm_onmessage_GUI,
    maincsm_oncreate_GUI,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose_GUI,
sizeof(MAIN_CSM_GUI),
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

#ifdef DAEMON
void Check()
{
  LockSched();
  char dummy[sizeof(MAIN_CSM_GUI)];
  //UpdateCSMname_GUI();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,2);
  UnlockSched();
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      ShowMSG(1,(int)"TurnOff config updated!");
    }
  }

  /*if (msg->msg==MSG_PLAYFILE_REPORT)
    {
      //DoIt();
      ShowMSG(1, (int)PLAY_ID);
      if ((msg->submess>>16)==PLAY_ID) 
      { 
        if (((msg->submess&0xFFFF)==7)||((msg->submess&0xFFFF)==5)) DoIt();
      }
        else
          PLAY_ID=0;
    }  */
  
  return(1);
}  

int my_keyhook(int key, int m)
{
  extern const int MODE_KBD;
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==MODE_KBD+0x193))
     if (key==CALL_BTN) 
       {
         mode=MODE;
         Check();
       }
  
  return 0;
}

static void maincsm_oncreate(CSM_RAM *data)
{

}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  if (MAINCSM_ID) CloseCSM(MAINCSM_ID);
  RemoveKeybMsgHook((void *)my_keyhook);  
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

static const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM_d =
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
  wsprintf((WSHDR *)(&MAINCSM_d.maincsm_name),"TurnOff_d");
}
#endif

void UpdateCSMname_GUI(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name_GUI),"TurnOff");
}

int main()
{
  LockSched();
  InitConfig();  
  
#ifdef DAEMON
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  
  #ifdef NEWSGOLD
    save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
    CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
    CreateCSM(&MAINCSM_d.maincsm,dummy,0);
    CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
    AddKeybMsgHook((void *)my_keyhook);
  #else
      if (!AddKeybMsgHook_end((void *)my_keyhook)) 
      {
        ShowMSG(1, (int) "TurnOff_d. Невозможно зарегистрировать обработчик!"); 
        SUBPROC((void *)Killer);
      }
      else
      {
        save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
        CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
        CreateCSM(&MAINCSM_d.maincsm,dummy,0);
        CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
      }
  #endif
    
#else  
  mode=MODE;      
  char dummy[sizeof(MAIN_CSM_GUI)];
  UpdateCSMname_GUI();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
#endif  
  
  UnlockSched();
  return 0;
}
