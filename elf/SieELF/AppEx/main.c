#include "..\inc\swilib.h"
#include <stdbool.h>
#include "..\inc\playsound.h"

#define NO_SOUND 0x80000000
#define NEED_BEEP 0;

#pragma swi_number=0x0C4
__swi __arm void *GetBuffer(int n);

#pragma swi_number=0x034
__swi __arm void PlaySoundLoop(int n, int flag, int vibra);

#pragma swi_number=0x0BF
__swi __arm void SpellTime(void);

int main(WSHDR **ptr) {//ptr[0]=descr, ptr[1]=place
 char place[21];//§á§à§Ý§Ö "§Þ§Ö§ã§ä§à" §Þ§Ñ§Ü§ã§Ú§Þ§å§Þ 20 §ã§Ú§Þ§Ó§à§Ý§à§Ó
 IPC_REQ *ipc_multisim;

 ws_2str(ptr[1], place, sizeof(place)-1);
 if (place[0]!='.')//§Ö§ã§Ý§Ú §Ó §ß§Ñ§é§Ñ§Ý§Ö §ß§Ö§ä §ä§à§é§Ü§Ú...
  return NO_SOUND;//...§ä§à §ß§Ñ§Þ §ä§Ñ§Ü§à§Ö §ã§à§Ò§í§ä§Ú§Ö §ß§Ö §ß§å§Ø§ß§à

 GBS_SendMessage(MMI_CEPID, KEY_DOWN, RIGHT_SOFT);//§¿§Þ§å§Ý§ñ§è§Ú§ñ §ß§Ñ§Ø§Ñ§ä§Ú§ñ §á§â§Ñ§Ó§à§Û §ã§à§æ§ä-§Ü§ß§à§á§Ü§Ú, §é§ä§à§Ò§í §ß§Ö §Ó§Ú§ã§Ö§Ý §Õ§Ú§Ñ§Ý§à§Ô §Ú §ß§Ö §Ò§í§Ý§à "§µ§á§å§ë. §ß§Ñ§á§à§Þ."

 ipc_multisim=(IPC_REQ*)((char*)GetBuffer(0x4401)+4);//ipc_multisim -> §à§Ò§Ý§Ñ§ã§ä§î RAM §Õ§Ý§ñ §á§Ö§â§Ö§Þ§Ö§ß§ß§í§ç §á§Ñ§ä§é§Ñ, §Ó§í§Õ§Ö§Ý§Ö§ß§ß§Ñ§ñ §®§±
 if ((int)ipc_multisim==4)//§á§Ñ§ä§é §Ó§í§Ü§Ý§ð§é§Ö§ß?
  return NO_SOUND;//§Ù§ß§Ñ§é§Ú§ä, §Õ§Ö§Ý§Ñ§ä§î §ß§Ú§é§Ö§Ô§à §ß§Ö §ß§Ñ§Õ§à

 bool needShutdown=false, needTime=false, needExec=false;
 unsigned profile=0, sim=0xFF, vibra=0, alert=0xFF, tmp, a;
 char *p=place+1;

 while (*p) {
  switch ((*p)|0x20) {
  case 'a':
   if (!(*(++p)))//§ã§ä§â§à§Ü§Ñ §Ù§Ñ§Ü§à§ß§é§Ú§Ý§Ñ§ã§î?..
    goto l_perform_actions;//...§á§Ñ§â§Ñ§Þ§Ö§ä§â§à§Ó §ß§Ö§ä
   tmp=*p;
   if (tmp>'9')
    tmp=(tmp&0xDF)-7;
   tmp-='0';
   if (!(*(++p)))//§ã§ä§â§à§Ü§Ñ §Ù§Ñ§Ü§à§ß§é§Ú§Ý§Ñ§ã§î?..
    goto l_perform_actions;//...§á§Ñ§â§Ñ§Þ§Ö§ä§â§à§Ó §ß§Ö§ä
   if (tmp<=15)
    a=tmp<<4;
   else
    continue;
   tmp=*p;
   if (tmp>'9')
    tmp=(tmp&0xDF)-7;
   tmp-='0';
   if (tmp<=15)
    alert=a|tmp;
   break;
  case 'z':
   needShutdown=true;
   break;
  case 't':
   needTime=true;
   break;
  case 'v':
   if (!(*(++p)))//§ã§ä§â§à§Ü§Ñ §Ù§Ñ§Ü§à§ß§é§Ú§Ý§Ñ§ã§î?..
    goto l_perform_actions;//...§á§Ñ§â§Ñ§Þ§Ö§ä§â§à§Ó §ß§Ö§ä
   tmp=*p;
   if (tmp>'9')
    tmp=(tmp&0xDF)-7;
   tmp-='0';
   if (tmp<=15)//§à§Ô§â§Ñ§ß§Ú§é§Ö§ß§Ú§Ö §ß§Ñ §Ü§à§Ý-§Ó§à §Ó§Ú§Ò§â (15 - 1 §á§à§Ý§å§Ò§Ñ§Û§ä)
    vibra=tmp;
   break;
  case 'p':
   if (!(*(++p)))//§ã§ä§â§à§Ü§Ñ §Ù§Ñ§Ü§à§ß§é§Ú§Ý§Ñ§ã§î?..
    goto l_perform_actions;//...§á§Ñ§â§Ñ§Þ§Ö§ä§â§à§Ó §ß§Ö§ä
   tmp=*p-'0';
   if (tmp>0 && tmp<=8)
    profile=tmp;
   break;
  case 's':
   if (!(*(++p)))//§ã§ä§â§à§Ü§Ñ §Ù§Ñ§Ü§à§ß§é§Ú§Ý§Ñ§ã§î?..
    goto l_perform_actions;//...§á§Ñ§â§Ñ§Þ§Ö§ä§â§à§Ó §ß§Ö§ä
   tmp=*p;
   if (tmp>'9')
    tmp=(tmp&0xDF)-7;
   tmp-='0';
   if (tmp<=10)//§à§Ô§â§Ñ§ß§Ú§é§Ö§ß§Ú§Ö §ß§Ñ §Ü§à§Ý-§Ó§à §ã§Ú§Þ§à§Ü
    sim=tmp;
   break;
  case 'x':
   needExec=true; p++;
   goto l_perform_actions;//§à§ã§ä§Ñ§Ý§î§ß§Ñ§ñ §é§Ñ§ã§ä§î §ã§ä§â§à§Ü§Ú - §Ú§Þ§ñ §æ§Ñ§Û§Ý§Ñ
  }
  p++;
 }

l_perform_actions:

 if (profile!=0)
  SetProfile(profile-1);

 unsigned ret;
 if (IsCalling()) {
  ret=NEED_BEEP;//§á§Ú§Ü§ß§Ö§Þ §Ó§à §Ó§â§Ö§Þ§ñ §Ù§Ó§à§ß§Ü§Ñ
 }
 else {//§Ó§à §Ó§â§Ö§Þ§ñ §Ù§Ó§à§ß§Ü§Ñ §ß§Ö§Ý§î§Ù§ñ §Ó§à§ã§á§â. §Ù§Ó§å§Ü§Ú!
  ret=NO_SOUND;

  SetIllumination(0, 1, 0, 50);//§Ó§í§â§å§Ò§Ñ§Ö§Þ §á§à§Õ§ã§Ó§Ö§ä§Ü§å §Õ§Ú§ã§á§Ý§Ö§ñ
  SetIllumination(1, 1, 0, 50);//§Ó§í§â§å§Ò§Ñ§Ö§Þ §á§à§Õ§ã§Ó§Ö§ä§Ü§å §Ü§ß§à§á§à§Ü

  if (alert<0xFF)
   PlaySound(VOLUME_ORGANISER, MMI_CEPID, 0, alert, 0);

  if (vibra>0)
   PlaySoundLoop(0x2F, 1, vibra);

  if (needTime)
   SpellTime();
 }

 if (sim!=0xFF) {
  ipc_multisim->name_to="MultiSim";
  ipc_multisim->name_from="AppEx";
  ipc_multisim->data=(void*)sim;
  GBS_SendMessage(MMI_CEPID, MSG_IPC, 1, ipc_multisim);
 }

 if (needExec) {
  if (*p!='*') {//x0:\... - §Ú§Þ§ñ §æ§Ñ§Û§Ý§Ñ §Ú§Ù "§Þ§Ö§ã§ä§Ñ"
   if (*p) {
    int len=strlen(p)+1;
    WSHDR *ws=AllocWS(len<<1);
    str_2ws(ws, p, len);
    ExecuteFile(ws, NULL, NULL);
    FreeWS(ws);
   }
  }
  else {//x* - §Ú§Þ§ñ §æ§Ñ§Û§Ý§Ñ §Ú§Ù "§à§á§Ú§ã§Ñ§ß§Ú§ñ"
   ExecuteFile(ptr[0], NULL, NULL);
  }
 }

 if (needShutdown)
  SwitchPhoneOff();

 return ret;
}

