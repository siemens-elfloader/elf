#pragma swi_number=97
__swi __arm void ShowNativeMenu();

#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "..\inc\xtask_ipc.h"

extern const int ENA_HELLO_MSG;
extern const int ENA_RBM;
extern const int RED_BUT_MODE;
extern const int ENA_LONG_PRESS;
extern const int ENA_LOCK;
extern const int ENA_MEDIAC;
extern const int ENA_KEY2JOY;
extern const int ENA_K2J_MSG;
extern const int Key2Joy_KEY;
extern const int Key2Joy_KEY_LONG_PRESS;
extern const int ENA_NATIVE;
extern const int SIDE_STYLE;
extern const char playlist_fname;
extern const int SideDNS;
extern const int SideDNL;
extern const int SideUPS;
extern const int SideUPL;
extern const char player_path[128];
extern const char playlist_path[128];
extern const int ENA_PLAYER;
//extern WSHDR *resstr;
extern TDate date;
extern TTime time; 
extern int sh;
extern int sm;
extern int ss;
extern int sd;
extern int nh;
extern int nm;
extern int ns;
extern int nd;

int my_keyhook(int submsg, int msg);

int IsMediaActive(void)
{
  char s[40];
  sprintf(s,RamMediaIsPlaying());
#ifdef NEWSGOLD
  if (s[0]==1) return 1;
#else
  if (s[0]==2) return 1;// для SGOLD s[0]!=2    
#endif 
  return 0;
}
int IsIDLE(void)
{
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) return(1);
                                                           else return(0);
}

const int minus11=-11;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

const char ipc_my_name[32]="KeyMaster"; 
const char ipc_xtask_name[]=IPC_XTASK_NAME; 
IPC_REQ gipc;

void Idle(void)
{
   gipc.name_to=ipc_xtask_name; 
   gipc.name_from=ipc_my_name; 
   gipc.data=0; 
   GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_IDLE,&gipc);
}

extern void kill_data(void *p, void (*func_p)(void *));

void execelf(char const *exename, char const *fname) //fname-параметр (имя файла), передаваемый в эльф 
{
  WSHDR *ws=AllocWS(256); 
  str_2ws(ws,exename,strlen(exename)+1); 
  ExecuteFile(ws,0,(void*)fname); FreeWS(ws);
}

// 0 - disabled key2joy function
// 1 - enabled
int keymode;

// 0 - no press
// 1 - action succeeded
int keymode2;

// 0 - no press
// 1 - lonpress side button
int side_mode;

// 0 - no press
// 1 - ( Enter || Red )button was pressed on idle
int nat_red_mode;

// 0 - no press
// 1 - long press REDBUT
int mode_red;

// 0 - no press
// 1 - long press REDBUT
int mode_ext_red;

// 0 - no press
// 1 - long press Handsfree button
int media_mode;

int my_keyhook(int submsg, int msg)
{
  if (IsUnlocked()||ENA_LOCK){
#ifndef NEWSGOLD
  if (ENA_RBM){
  //Red button menu
  extern void CreateRBMenu(void); 
  if (IsIDLE() && (submsg==RED_BUTTON) && (msg==LONG_PRESS)){
      nat_red_mode=0;
      return 0;
  }
  if (IsIDLE() && (submsg==RED_BUTTON) && (msg==KEY_DOWN) && IsUnlocked()) {
        if (((int)GetTypeUSSD())!=8) return(0) ; else nat_red_mode=1;
        return(0);
  }
  if (IsIDLE() && (submsg==RED_BUTTON) && (msg==KEY_UP) && (nat_red_mode)){
      CreateRBMenu();
      nat_red_mode=0;
      return(2);}
    else if ((nat_red_mode) && (submsg==RED_BUTTON)) nat_red_mode=0;
  }
#endif
  
void *icsm=FindCSMbyID(CSM_root()->idle_id);
#ifndef NEWSGOLD
  //MediaControl
  if ((submsg==0x27) && (ENA_MEDIAC==1)){
    switch (msg){
    case (KEY_DOWN): break;
    case (KEY_UP): if (!IsIDLE())
      {
          GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON);
          GBS_SendMessage(MMI_CEPID,KEY_UP,ENTER_BUTTON);
      } break;
    case (LONG_PRESS): if (!IsIDLE())
          {
              GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_BUTTON);
              GBS_SendMessage(MMI_CEPID,KEY_UP,RIGHT_BUTTON);
          } break;
    }
  }
#endif
  if ((submsg==0x27) && (ENA_PLAYER) && (!IsCalling()) && (msg==LONG_PRESS)){
    if (IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])){
      if (ENA_PLAYER==2) SUBPROC(GetFunctionPointer("ELSE_MUSIC_PLAY"));
      else execelf(player_path,playlist_path);
      media_mode=1;
      return 2;
    }
  }
  if ((submsg==0x27) && (media_mode)){ media_mode=0; return 2;}
  
//  Goto Native Menu
  if (ENA_NATIVE){
  if (IsIDLE() && (submsg==ENTER_BUTTON) && (msg==LONG_PRESS) && (IsNoJava()==0)){
      nat_red_mode=0;
      return 0;
  }
  if (IsIDLE() && (submsg==ENTER_BUTTON) && (msg==KEY_DOWN) && (IsNoJava()==0)){
      nat_red_mode=1;
      return(0);
  }
  if (IsIDLE() && (submsg==ENTER_BUTTON) && (msg==KEY_UP) && (IsNoJava()==0) && (nat_red_mode)){
      ShowNativeMenu();
      nat_red_mode=0;
      return(2);}
    else if ((nat_red_mode)&& (submsg==ENTER_BUTTON)) nat_red_mode=0;
  }
  
//Side keys
  if ((SIDE_STYLE==1) && !(IsIDLE())){
    if ((submsg==0x14)||(submsg==0xD)){
	GBS_SendMessage(MMI_CEPID,msg,UP_BUTTON);
	  return(2); 
      }
    if ((submsg==0x15)||(submsg==0xE)){
	GBS_SendMessage(MMI_CEPID,msg,DOWN_BUTTON);
	  return(2); 
      }
    }
  
    if ((SIDE_STYLE==2) && !(IsIDLE())){
    if ((submsg==0x14)||(submsg==0xD)){
	GBS_SendMessage(MMI_CEPID,msg,LEFT_BUTTON);
	  return(2); 
      }
    if ((submsg==0x15)||(submsg==0xE)){
	GBS_SendMessage(MMI_CEPID,msg,RIGHT_BUTTON);
	  return(2); 
      }
    }
  
    if ((SIDE_STYLE==3) && !(IsIDLE())){
    if ((submsg==0x14)||(submsg==0xD)){
      switch(msg){
      case KEY_DOWN: side_mode=0; return(2);
      case LONG_PRESS:
        side_mode=1; return(2);
      case KEY_UP:
        if (side_mode==0){
	GBS_SendMessage(MMI_CEPID,KEY_DOWN,SideUPS);
	GBS_SendMessage(MMI_CEPID,KEY_UP,SideUPS);
        }
        else{
	GBS_SendMessage(MMI_CEPID,KEY_DOWN,SideUPL);
	GBS_SendMessage(MMI_CEPID,KEY_UP,SideUPL);
        }
	  return(2); 
      }
    }
    if ((submsg==0x15)||(submsg==0xE)){
      switch(msg){
      case KEY_DOWN: side_mode=0; return(2);
      case LONG_PRESS:
        side_mode=1; return(2);
      case KEY_UP:
        if (side_mode==0){
	GBS_SendMessage(MMI_CEPID,KEY_DOWN,SideDNS);
	GBS_SendMessage(MMI_CEPID,KEY_UP,SideDNS);
        }
        else{
	GBS_SendMessage(MMI_CEPID,KEY_DOWN,SideDNL);
	GBS_SendMessage(MMI_CEPID,KEY_UP,SideDNL);
        }
	  return(2);
      }
    }
    }
    
  //Key2Joy init
  if ((ENA_KEY2JOY>0) && (submsg==Key2Joy_KEY)){
    if (Key2Joy_KEY_LONG_PRESS==1){                                         // Длинное нажатие
    switch (msg){
    case KEY_DOWN:
      if (keymode2==0) return KEYHOOK_BREAK; else return KEYHOOK_NEXT; 
    case KEY_UP:
      if (keymode2==0)
      {
        keymode2=1;
        GBS_SendMessage(MMI_CEPID,KEY_DOWN,Key2Joy_KEY);
        GBS_SendMessage(MMI_CEPID,KEY_UP,Key2Joy_KEY);
        return KEYHOOK_BREAK;
      }
      if (keymode2==1)
      {
        keymode2=0;
        return KEYHOOK_NEXT;
      }
      if (keymode2==2)
      {
        keymode2=0;
        return KEYHOOK_BREAK;
      }
    case LONG_PRESS:
      if ((IsUnlocked()||ENA_LOCK) && (keymode2==0))
      {
        keymode+=1;
        keymode2=2;
        if (keymode==2) keymode=0;
        if ((keymode==1)&&(ENA_K2J_MSG)) ShowMSG(1,(int)"Key2Joy开启!");
                                    else if (ENA_K2J_MSG) ShowMSG(1,(int)"Key2Joy关闭!");
      return KEYHOOK_BREAK;
      } else return KEYHOOK_NEXT;
    }
    
    
    } else{                                                                 // Короткое нажатие
      if (msg==KEY_DOWN) { if (keymode2==0) return KEYHOOK_BREAK; else return KEYHOOK_NEXT; };
      if (msg==LONG_PRESS){
        if (keymode2==0) { keymode2=1; GBS_SendMessage(MMI_CEPID,KEY_DOWN,Key2Joy_KEY); }
        return KEYHOOK_NEXT;
      }
      if (msg==KEY_UP){
        if (keymode2==0){
        keymode+=1;
        if (keymode==2) keymode=0;
        if ((keymode==1)&&(ENA_K2J_MSG)) ShowMSG(1,(int)"Key2Joy开启!");
                                    else if (ENA_K2J_MSG) ShowMSG(1,(int)"Key2Joy关闭!");
        return KEYHOOK_BREAK;
         } else{
           keymode2=0;
           return KEYHOOK_NEXT;
         }
    }
  }
  }

  
  //keypad2joy implementation
  if (keymode==1){
    if (submsg==0x38){
	GBS_SendMessage(MMI_CEPID,msg,DOWN_BUTTON);
	  return(2); 
      }
    if (submsg==0x32){
	GBS_SendMessage(MMI_CEPID,msg,UP_BUTTON);
	  return(2); 
      }
    if (submsg==0x34){
	GBS_SendMessage(MMI_CEPID,msg,LEFT_BUTTON);
	  return(2); 
      }
    if (submsg==0x36){
	GBS_SendMessage(MMI_CEPID,msg,RIGHT_BUTTON);
	  return(2); 
      }
    if (submsg==0x35){
       GBS_SendMessage(MMI_CEPID,msg,ENTER_BUTTON);
	  return(2); 
      }
    if ((submsg==0x37) && (ENA_KEY2JOY==2)){
	GBS_SendMessage(MMI_CEPID,msg,LEFT_SOFT);
	  return(2); 
      }
    if ((submsg==0x39) && (ENA_KEY2JOY==2)){
	GBS_SendMessage(MMI_CEPID,msg,RIGHT_SOFT);
	  return(2); 
      }
    if ((submsg==0x31) && (ENA_KEY2JOY==3)){
	GBS_SendMessage(MMI_CEPID,msg,LEFT_SOFT);
	  return(2); 
      }
    if ((submsg==0x33) && (ENA_KEY2JOY==3)){
	GBS_SendMessage(MMI_CEPID,msg,RIGHT_SOFT);
	  return(2); 
      }
    }

#ifndef NEWSGOLD
  //Red button
  if ((submsg==RED_BUTTON)&&(RED_BUT_MODE)&&(msg==LONG_PRESS))
  {
    Idle();
    return(2);
  }
#endif
return(0);
  } else return 0;
}

#pragma inline=forced

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

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"KeyMaster配置已更新!");
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"KeyMaster");
}

int main()
{
  InitConfig();

  keymode=0;
  media_mode=0;
  mode_red=0;
  GetDateTime(&date,&time);
//  resstr=AllocWS(128);
  ss=time.sec;
  sh=time.hour;
  sd=date.day;
  sm=time.min;  
  
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
  if (ENA_HELLO_MSG) ShowMSG(1,(int)"KeyMaster正在运行!");
  
  return 0;
}
