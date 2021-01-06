#include "C:\ARM_ALL\inc\swilib.h"
#include "conf_loader.h"

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;
GBSTMR my_timer;
int count=0;

void Play(const char *fname)
{
  extern const unsigned int sndvolume;
  if (!IsCalling())
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
  _sfo1.volume=sndvolume;
  #ifdef NEWSGOLD
  _sfo1.unk6=1;
  _sfo1.unk7=1;
  _sfo1.unk9=2;
  PlayFile(0x10, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  #ifdef X75
  _sfo1.unk4=0x80000000;
  _sfo1.unk5=1;
  PlayFile(0xC, sndPath, sndFName, 0,MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #else
  _sfo1.unk5=1;
  PlayFile(0xC, sndPath, sndFName, MMI_CEPID, MSG_PLAYFILE_REPORT, &_sfo1);
  #endif
  #endif
  FreeWS(sndPath);
  FreeWS(sndFName);
  }
  }
}

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

CSM_RAM *under_idle;

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
  extern const int ena_req;
  if (ena_req) ShowMSG(1,(int)"Конфиг AutoNet'a обновлен!");
  InitConfig();
  }
  }
  return (1);
}

void AutoNet()
{
  extern const char sounds[128];
  extern const unsigned int pischalka;
  extern const unsigned int profile;
  extern const int deistvie_net;
  switch (deistvie_net)//Выбор действия из конфига
  {
  case 0:
  if(IsUnlocked())//При разблокированной клаве
  {
  KbdLock();//Заблокировать клаву
  }
  break;
  case 1:
  Play(sounds);//Воспроизвести звук из заданной папки
  break;
  case 2:
  PlaySound(1,0,0,pischalka,0);//Воспроизвести звучок из прошивки
  break;
  case 3:
  SetProfile(profile-1);//Установить заданный профиль
  break;
  case 4:
  ShowMSG(2,(int)"Неактивная сеть!");//Вывести сообщение о неактивной сети
  break;
  case 5:
  SwitchPhoneOff();;//Выключить телефон
  break;
  case 6:
  NetOff();//Отключить поиск сети(для NSG и EL)
  break;
  }
  //GBS_DelTimer(&my_timer);//Отключить таймер
}

static void maincsm_oncreate(CSM_RAM *data)
{
  extern const unsigned int time_timer;
  if(*RamNetOnline()==0)//Только при неактивной сети
  {
  GBS_StartTimerProc(&my_timer,time_timer*232,AutoNet);//Установить таймер
  }
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"AutoNet - (c) KIBER-DEMON");
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
  extern const int ena_msg;
  if (ena_msg) ShowMSG(1,(int)"AutoNet установлен!");
  return 0;
}
