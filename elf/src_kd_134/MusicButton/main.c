#include "C:\ARM_ALL\inc\swilib.h"
#include "C:\ARM_ALL\inc\mplayer.h"

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;
GBSTMR my_timer;
int count=0;

typedef void (*func)();
#ifdef EL71SW45
func PlayerButtom=(func)0xA06FB309,//����� ������ ������
   PlayStopButton=(func)0xA06A2720;//����� ������ ��������
#endif
#ifdef S75SW47
func PlayerButtom=(func)0xA0333441,//����� ������ ������
   PlayStopButton=(func)0xA052D317;//����� ������ ��������
#endif
#ifdef S75SW52
func PlayerButtom=(func)0xA033386D,//����� ������ ������
   PlayStopButton=(func)0xA052DA03;//����� ������ ��������
#endif

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

void ButtonPleer()
{
  if(IsUnlocked())//��� ������������� ����������
  {
   PlayerButtom();
  }
  if(IsPlayerOn())//��� ���������� ������
  {
   if(!IsUnlocked())//��� ���������� ����������
   {
    MPlayer_Mute();//��������� ����
   }
  }
}

void ButtonPlayStop()
{
  if(IsUnlocked())//��� ������������� ����������
  {
   PlayStopButton();
  }
  if(IsPlayerOn())//��� ���������� ������
  {
   if(!IsUnlocked())//��� ���������� ����������
   {
    PlayStopButton();
   }
  }
}

void PeremotkaNazad()
{
  Send_MPlayer_Command(PLAYER_RWN,0);//��������� �����
}

void PeremotkaVpered()
{
  Send_MPlayer_Command(PLAYER_FWD,0);//��������� �����
}

int my_keyhook(int submsg, int msg)
{
  //�������� ������� ������
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
  if(IsPlayerOn())//��� ���������� ������
  {
   if(!IsUnlocked())//��� ���������� ����������
   {
   count++;//������� ���������, ������� ������ ���, ��� ��������� ����
   if(count==1)//���� ������ 1 �������, �� �������� ������
   {
   //Send_MPlayer_Command(PLAYER_NRM,0);//���������� ���������������
   PlayStopButton();
   GBS_DelTimer(&my_timer);
   }
   GBS_StartTimerProc(&my_timer,216,PeremotkaNazad);
   }
  }
  }
  if(submsg==0x4)
  {
  if(IsPlayerOn())//��� ���������� ������
  {
   if(!IsUnlocked())//��� ���������� ����������
   {
   count++;//������� ���������, ������� ������ ���, ��� ��������� ����
   if(count==1)//���� ������ 1 �������, �� �������� ������
   {
   Send_MPlayer_Command(PLAYER_NRM,0);//���������� ���������������
   GBS_DelTimer(&my_timer);
   }
   GBS_StartTimerProc(&my_timer,216,PeremotkaVpered);
   }
  }
  }
  }
  //������ ������� ������
  if (msg==LONG_PRESS)
  {
  if(submsg==0x11)
  {
  MPlayer_Next();//��������� ����
  }
  if(submsg==0x1D)
  {
  MPlayer_Prev();//���������� ����
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
