#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"


TDate date; 
TTime time; 

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;


extern void kill_data(void *p, void (*func_p)(void *));

const int minus11=-11;
int MAINCSM_ID=0;

extern const char ICONS_SD[128];
extern const char ICONS_RB[128];
extern const char ICONS_SR[128];
extern const char ICONS_UL[128];

extern const unsigned int CLOSE_BTN;
extern const int MODE;
extern const int DIRECT;
extern const unsigned int CALL_BTN;
extern const unsigned int CALL_BTN2;
extern const int ENA_LOCK;

int mode;
// 0-mode deal 
// 1-off
// 2-restart 
// 3-unlock
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

void method0(MAIN_GUI *data)
{
 /* DrawRoundedFrame(0,0, ScreenW()-1, ScreenH()-1, 0, 0, 0,
			GetPaletteAdrByColorIndex(23),
			GetPaletteAdrByColorIndex(23));
  */
   int x, y;
   
   switch(mode)  //图片显示位置
    {
    case 0:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_SR)/2;
        y = (ScreenH()-YDISP)/3 - GetImgHeight((int)ICONS_SR)/2;
        DrawImg(x, y, (int)ICONS_SR);
      }
      break;
    case 1:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_SD)/2;
        y = (ScreenH()-YDISP)/3 - GetImgHeight((int)ICONS_SD)/2;
        DrawImg(x, y, (int)ICONS_SD);
      }
      break;
    case 2:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_RB)/2;
        y = (ScreenH()-YDISP)/3 - GetImgHeight((int)ICONS_RB)/2;
        DrawImg(x, y, (int)ICONS_RB);
      }
      break;
    case 3:
      {
        x= ScreenW()/2 - GetImgWidth((int)ICONS_UL)/2;
        y = (ScreenH()-YDISP)/3 - GetImgHeight((int)ICONS_UL)/2;
        DrawImg(x, y, (int)ICONS_UL);
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

void DoIt(void) //功能定位
{
  switch(mode)
    {
      case 0:
               KbdLock();
      break;
      case 1:
               SwitchPhoneOff();           
      break;
      case 2:
               RebootPhone();
      break;
      case 3:
               KbdUnlock();
      break;
     }
  CloseCSM(MAINCSM_ID);
  MAINCSM_ID=0;
}


int method5(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI();

  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (msg->gbsmsg->submess==CLOSE_BTN)
    {
        CloseCSM(MAINCSM_ID); //There GeneralFunc challenge for Tech. GUI -> close GUI
        MAINCSM_ID=0;
    }

    switch(msg->gbsmsg->submess)
    {
    case RIGHT_BUTTON:
    case UP_BUTTON: 
      if(IsUnlocked())
      {
        mode++;
        if (mode==3) mode=0;
      }
      break;
    case LEFT_BUTTON:
    case DOWN_BUTTON:
     if(IsUnlocked())
     {
        mode--;
        if (mode==-1) mode=2;
     }
      break;
     case ENTER_BUTTON:
       switch(mode)
        {
          case 0:
             DoIt();
          break;
          case 1:
             DoIt();
          break;
          case 2:
             DoIt();
          break;
          case 3:
             DoIt();
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


void maincsm_onclose_GUI(CSM_RAM *csm)
{

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
  if(msg->msg == MSG_RECONFIGURE_REQ) // Perechityvanie configuration reported
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
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
  extern const int MODE_KBD2;
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&IsUnlocked()&&(m==MODE_KBD+0x193))
  {
    if (key==CALL_BTN) 
       {
         mode=MODE;
         Check();
       }
   }
  else if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))&&ENA_LOCK&&(m==MODE_KBD2+0x193))
     if ((key==CALL_BTN2)&&(DIRECT)) 
       {
         mode=3;
         Check();
       }
     else if ((key==CALL_BTN2)&&(DIRECT==0))     
         KbdUnlock();
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


int main()
{
  LockSched();
  InitConfig();  
  

  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  
  //#ifdef NEWSGOLD
    save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
    CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
    CreateCSM(&MAINCSM_d.maincsm,dummy,0);
    CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
    AddKeybMsgHook((void *)my_keyhook);
  /*#else
      if (!AddKeybMsgHook_end((void *)my_keyhook)) 
      {
        ShowMSG(1, (int) "TurnOff_d. Unable to register a handler!"); 
        SUBPROC((void *)Killer);
      }
      else
      {
        save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
        CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
        CreateCSM(&MAINCSM_d.maincsm,dummy,0);
        CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
      }
  #endif*/
    
  
  UnlockSched();
  return 0;
}
