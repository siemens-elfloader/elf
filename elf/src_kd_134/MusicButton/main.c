#include "C:\ARM_ALL\inc\swilib.h"
#include "C:\ARM_ALL\inc\mplayer.h"

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;
GBSTMR my_timer;
int count=0;

typedef void (*func)();
#ifdef EL71SW45
func PlayerButtom=(func)0xA06FB309,//Адрес кнопки плеера
   PlayStopButton=(func)0xA06A2720;//Адрес кнопки плейстоп
#endif
#ifdef S75SW47
func PlayerButtom=(func)0xA0333441,//Адрес кнопки плеера
   PlayStopButton=(func)0xA052D317;//Адрес кнопки плейстоп
#endif
#ifdef S75SW52
func PlayerButtom=(func)0xA033386D,//Адрес кнопки плеера
   PlayStopButton=(func)0xA052DA03;//Адрес кнопки плейстоп
#endif

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

void ButtonPleer()
{
  if(IsUnlocked())//При разблокировке клавиатуры
  {
   PlayerButtom();
  }
  if(IsPlayerOn())//При включенном плэере
  {
   if(!IsUnlocked())//При блокировке клавиатуры
   {
    MPlayer_Mute();//Выключить звук
   }
  }
}

void ButtonPlayStop()
{
  if(IsUnlocked())//При разблокировке клавиатуры
  {
   PlayStopButton();
  }
  if(IsPlayerOn())//При включенном плэере
  {
   if(!IsUnlocked())//При блокировке клавиатуры
   {
    PlayStopButton();
   }
  }
}

void PeremotkaNazad()
{
  Send_MPlayer_Command(PLAYER_RWN,0);//Перемотка назад
}

void PeremotkaVpered()
{
  Send_MPlayer_Command(PLAYER_FWD,0);//Перемотка вперёд
}

int my_keyhook(int submsg, int msg)
{
  //Короткое нажатие клавиш
  if (msg==KEY_UP)
  {
  if(submsg==0x11)
  {
  ButtonPleer();
  }
  if(submsg==0x1D)
  {
  ButtonPlayStop();
  }
  if(submsg==0x1)
  {
  if(IsPlayerOn())//При включенном плэере
  {
   if(!IsUnlocked())//При блокировке клавиатуры
   {
   count++;//счетчик поставили, плюсует каждый раз, как дергается войд
   if(count==1)//если прошла 1 секунда, то вырубаем таймер
   {
   //Send_MPlayer_Command(PLAYER_NRM,0);//Продолжить воспроизведение
   PlayStopButton();
   GBS_DelTimer(&my_timer);
   }
   GBS_StartTimerProc(&my_timer,216,PeremotkaNazad);
   }
  }
  }
  if(submsg==0x4)
  {
  if(IsPlayerOn())//При включенном плэере
  {
   if(!IsUnlocked())//При блокировке клавиатуры
   {
   count++;//счетчик поставили, плюсует каждый раз, как дергается войд
   if(count==1)//если прошла 1 секунда, то вырубаем таймер
   {
   Send_MPlayer_Command(PLAYER_NRM,0);//Продолжить воспроизведение
   GBS_DelTimer(&my_timer);
   }
   GBS_StartTimerProc(&my_timer,216,PeremotkaVpered);
   }
  }
  }
  }
  //Долгое нажатие клавиш
  if (msg==LONG_PRESS)
  {
  if(submsg==0x11)
  {
  MPlayer_Next();//Следующий трек
  }
  if(submsg==0x1D)
  {
  MPlayer_Prev();//Предыдущий трек
  }
  }
  return 0;
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  return (1);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  AddKeybMsgHook((void *)my_keyhook);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  RemoveKeybMsgHook((void *)my_keyhook);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MusicButton - (c) KIBER-DEMON, funMarkus");
}

int main()
{
  CSM_RAM *save_cmpc;
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  save_cmpc=CSM_root()->csm_q->current_msg_processing_csm;
  CSM_root()->csm_q->current_msg_processing_csm=CSM_root()->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,dummy,0);
  CSM_root()->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  return 0;
}
