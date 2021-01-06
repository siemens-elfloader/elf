#include "..\inc\swilib.h"
#include "..\conf_loader.h"
CSM_DESC icsmd;
void (*old_icsm_onClose)(CSM_RAM*);
int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);
extern const unsigned int CALL_BUTTON;
extern const char PATH[64];
int mode_enter;
int mode;

void ExecuteElf()
{
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,PATH,128);
  ExecuteFile(ws,NULL,NULL);
  FreeWS(ws);
}

int my_keyhook(int submsg, int msg)
{
  if (submsg!=CALL_BUTTON) return(0);
  switch(msg)
  {
  case KEY_DOWN:
    if (mode_enter==2)
    {
      GBS_SendMessage(MMI_CEPID,KEY_UP,CALL_BUTTON);
      return (0);
    }
    mode_enter=0;
    return (2);
  case KEY_UP:
    if (mode==1)mode=0;
    if (mode_enter==0)
    {
      mode_enter=2;
      GBS_SendMessage(MMI_CEPID,KEY_DOWN,CALL_BUTTON);
      return (2);
    }
    if (mode_enter==2)
    {
      mode_enter=0;
      return (0);
    }
    mode_enter=0;
    return (2);      
  case LONG_PRESS:
    mode_enter=1;
    if(mode==0)
    {
      if (IsUnlocked()) ExecuteElf();
    }
    mode=1;
    break;
  }
return(2); 
}

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


int MyIDLECSM_onMessage(CSM_RAM* data, GBS_MSG* msg)
{
  if(msg->msg == MSG_RECONFIGURE_REQ) 
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
         ShowMSG(1,(int)"Настройки FastRun обновлены!");
      InitConfig();
    }
  }
 int csm_result=old_icsm_onMessage(data, msg);
 return(csm_result);
}

 void MyIDLECSM_onClose(CSM_RAM *data)
{
  RemoveKeybMsgHook((void *)my_keyhook);
  extern void seqkill(void *data, void(*next_in_seq)(CSM_RAM *), void *data_to_kill, void *seqkiller);
  extern void *ELF_BEGIN;
  seqkill(data,old_icsm_onClose,&ELF_BEGIN,SEQKILLER_ADR());
}


int main(void)
{
 InitConfig();
 LockSched();
 CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
 memcpy(&icsmd,icsm->constr,sizeof(icsmd));
 old_icsm_onMessage=icsmd.onMessage;
 icsmd.onMessage=MyIDLECSM_onMessage;
 old_icsm_onClose=icsmd.onClose;
 icsmd.onClose=MyIDLECSM_onClose;
 icsm->constr=&icsmd;
 AddKeybMsgHook((void *)my_keyhook);
 UnlockSched();
 return 0;
}

