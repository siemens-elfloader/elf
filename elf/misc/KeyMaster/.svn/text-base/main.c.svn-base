#pragma swi_number=97
__swi __arm void ShowNativeMenu();

#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "conf_loader.h"
#include "..\inc\xtask_ipc.h"

extern const int RED_BUT_MODE;
extern const int ENA_LONG_PRESS;
extern const int ENA_LOCK;
extern const int ENA_MEDIAC;
extern const int ENA_KEY2JOY;
extern const int Key2Joy_KEY;
extern const int Key2Joy_KEY_LONG_PRESS;
extern const int ENA_NATIVE;
extern const int SIDE_STYLE;
extern const char playlist_fname;
extern const int SideDNS;
extern const int SideDNL;
extern const int SideUPS;
extern const int SideUPL;

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
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
  if (IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) return(1);
                                                           else return(0);
}


CSM_DESC icsmd;
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
void (*old_icsm_onClose)(CSM_RAM*);

WSHDR *ws_nogui;

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

//extern void kill_data(void *p, void (*func_p)(void *));

//void ElfKiller(void)
//{
//  extern void *ELF_BEGIN;
//  FreeWS(ws_nogui);
//  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
//}

void execelf(char *exename, char *fname) //fname-параметр (имя файла), передаваемый в эльф 
{
  WSHDR *ws=AllocWS(256); 
  str_2ws(ws,exename,strlen(exename)+1); 
  ExecuteFile(ws,0,fname); FreeWS(ws);
}

// 0 - disabled key2joy function
// 1 - enabled
int keymode;
// 0 - no press
// 1 - lonpress Key2Joy button
int keymode2;

// 0 - no press
// 1 - lonpress side button
int side_mode;

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
  char s[40];
  sprintf(s,RamMediaIsPlaying());
  
  void *icsm=FindCSMbyID(CSM_root()->idle_id);
#ifndef NEWSGOLD
  //MediaControl
  if ((submsg==0x27) && (ENA_MEDIAC==1)){
    switch (msg){
    case (KEY_DOWN): break;
    case (KEY_UP):{
      if (media_mode==1){
//        execelf("0:\\Sounds\\All.m3u","");
        media_mode=0;
        break;
      }
      else if (!IsIDLE())
      {
          GBS_SendMessage(MMI_CEPID,KEY_DOWN,ENTER_BUTTON);
          GBS_SendMessage(MMI_CEPID,KEY_UP,ENTER_BUTTON);
      }
    }
    case (LONG_PRESS):{
      if (IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])){
        if (media_mode==0) SUBPROC(GetFunctionPointer("ELSE_MUSIC_PLAY"));
        media_mode=1;
      }
          else if (!IsIDLE())
          {
              GBS_SendMessage(MMI_CEPID,KEY_DOWN,RIGHT_BUTTON);
              GBS_SendMessage(MMI_CEPID,KEY_UP,RIGHT_BUTTON);
          }
    }
    }
  }
#endif
//  Goto Native Menu
  if ((IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])) && (submsg==ENTER_BUTTON) && (msg==KEY_UP) && (IsNoJava()==0)){
      ShowNativeMenu();
      return(2);
  }

  //Side keys
  if ((SIDE_STYLE==1) && !(IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))){
    if ((submsg==0x14)||(submsg==0xD)){
	GBS_SendMessage(MMI_CEPID,msg,UP_BUTTON);
	  return(2); 
      }
    if ((submsg==0x15)||(submsg==0xE)){
	GBS_SendMessage(MMI_CEPID,msg,DOWN_BUTTON);
	  return(2); 
      }
    }
  
    if ((SIDE_STYLE==2) && !(IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))){
    if ((submsg==0x14)||(submsg==0xD)){
	GBS_SendMessage(MMI_CEPID,msg,LEFT_BUTTON);
	  return(2); 
      }
    if ((submsg==0x15)||(submsg==0xE)){
	GBS_SendMessage(MMI_CEPID,msg,RIGHT_BUTTON);
	  return(2); 
      }
    }
  
    if ((SIDE_STYLE==3) && !(IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))){
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
    if (msg==LONG_PRESS) keymode2=1;
    if (msg==KEY_UP){
      if ((Key2Joy_KEY_LONG_PRESS==1) && (keymode2==1)){
        keymode+=1;
        keymode2=0;
        if (keymode==2) keymode=0;
        if (keymode==1) ShowMSG(1,(int)"Key2Joy On!");
                        else ShowMSG(1,(int)"Key2Joy Off!");
        return 2;
      } else if (keymode2==0) return(0);
      if ((Key2Joy_KEY_LONG_PRESS==0) && (keymode2==0)){
        keymode+=1;
        if (keymode==2) keymode=0;
        if (keymode==1) ShowMSG(1,(int)"Key2Joy On!");
                        else ShowMSG(1,(int)"Key2Joy Off!");
        return 2;
      } else{
        keymode=0;
        return(0);
      }
    }
  }

  
  //keypad2joy implementation
  if ((keymode==1) && !(IsGuiOnTop(((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4]))){
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

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
  csm_result = old_icsm_onMessage(data, msg); //Вызываем старый обработчик событий
  
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"KeyMaster config updated!");
      InitConfig();
    }
  }
  return csm_result;  
}
void MyIDLECSM_onClose(CSM_RAM *data)
{
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  FreeWS(ws_nogui);
  RemoveKeybMsgHook((void *)my_keyhook);
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}

int main(void)
{
  InitConfig();
  LockSched();
  keymode=0;
  media_mode=0;
  mode_red=0;
  /*
  if (!AddKeybMsgHook_end((void *)my_keyhook))
  {
    ShowMSG(1,(int)"Невозможно зарегистрировать обработчик!");
    SUBPROC((void *)ElfKiller);
  }
  else*/
  {
    AddKeybMsgHook((void *)my_keyhook);
    extern const int ENA_HELLO_MSG;
    if (ENA_HELLO_MSG) ShowMSG(1,(int)"KeyMaster установлен!");
    {
      CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
      memcpy(&icsmd,icsm->constr,sizeof(icsmd));
      old_icsm_onClose=icsmd.onClose;
      old_icsm_onMessage=icsmd.onMessage;
      icsmd.onClose=MyIDLECSM_onClose;
      icsmd.onMessage=MyIDLECSM_onMessage;
      icsm->constr=&icsmd;
    }
    ws_nogui=AllocWS(256);
  }
  UnlockSched();
  return 0;
}
