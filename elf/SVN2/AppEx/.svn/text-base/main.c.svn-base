#include "..\inc\swilib.h"
#include <stdbool.h>
#include "..\inc\playsound.h"

#define NO_SOUND 0x80000000
#define NEED_BEEP 0;

int main(WSHDR **ptr) {//ptr[0]=descr, ptr[1]=place
 char place[21];//поле "место" максимум 20 символов
 IPC_REQ *ipc_multisim;

 ws_2str(ptr[1], place, sizeof(place)-1);
 if (place[0]!='.')//если в начале нет точки...
  return NO_SOUND;//...то нам такое событие не нужно

 GBS_SendMessage(MMI_CEPID, KEY_DOWN, RIGHT_SOFT);//Ёмул€ци€ нажати€ правой софт-кнопки, чтобы не висел диалог и не было "”пущ. напом."

 ipc_multisim=(IPC_REQ*)((char*)GetBuffer(0x4401)+4);//ipc_multisim -> область RAM дл€ переменных патча, выделенна€ ћѕ
 if ((int)ipc_multisim==4)//патч выключен?
  return NO_SOUND;//значит, делать ничего не надо

 bool needShutdown=false, needTime=false, needExec=false;
 unsigned profile=0, sim=0xFF, vibra=0, alert=0xFF, tmp, a;
 char *p=place+1;

 while (*p) {
  switch ((*p)|0x20) {
  case 'a':
   if (!(*(++p)))//строка закончилась?..
    goto l_perform_actions;//...параметров нет
   tmp=*p;
   if (tmp>'9')
    tmp=(tmp&0xDF)-7;
   tmp-='0';
   if (!(*(++p)))//строка закончилась?..
    goto l_perform_actions;//...параметров нет
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
   if (!(*(++p)))//строка закончилась?..
    goto l_perform_actions;//...параметров нет
   tmp=*p;
   if (tmp>'9')
    tmp=(tmp&0xDF)-7;
   tmp-='0';
   if (tmp<=15)//ограничение на кол-во вибр (15 - 1 полубайт)
    vibra=tmp;
   break;
  case 'p':
   if (!(*(++p)))//строка закончилась?..
    goto l_perform_actions;//...параметров нет
   tmp=*p-'0';
   if (tmp>0 && tmp<=8)
    profile=tmp;
   break;
  case 's':
   if (!(*(++p)))//строка закончилась?..
    goto l_perform_actions;//...параметров нет
   tmp=*p;
   if (tmp>'9')
    tmp=(tmp&0xDF)-7;
   tmp-='0';
   if (tmp<=10)//ограничение на кол-во симок
    sim=tmp;
   break;
  case 'x':
   needExec=true; p++;
   goto l_perform_actions;//остальна€ часть строки - им€ файла
  }
  p++;
 }

l_perform_actions:

 if (profile!=0)
  SetProfile(profile-1);

 unsigned ret;
 if (IsCalling()) {
  ret=NEED_BEEP;//пикнем во врем€ звонка
 }
 else {//во врем€ звонка нельз€ воспр. звуки!
  ret=NO_SOUND;

  SetIllumination(0, 1, 0, 50);//вырубаем подсветку диспле€
  SetIllumination(1, 1, 0, 50);//вырубаем подсветку кнопок

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
  if (*p!='*') {//x0:\... - им€ файла из "места"
   if (*p) {
    int len=strlen(p)+1;
    WSHDR *ws=AllocWS(len<<1);
    str_2ws(ws, p, len);
    ExecuteFile(ws, NULL, NULL);
    FreeWS(ws);
   }
  }
  else {//x* - им€ файла из "описани€"
   ExecuteFile(ptr[0], NULL, NULL);
  }
 }

 if (needShutdown)
  SwitchPhoneOff();

 return ret;
}
