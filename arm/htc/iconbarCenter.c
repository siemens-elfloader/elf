#include "D:\ARM_ALL\inc\swilib.h"
#include "D:\ARM_ALL\inc\xtask_ipc.h"
#include "conf_loader.h"
#include "local_ipc.h"
#include "define.h"
#include "mylib.h"

const char ipc_my_name[32]=IPC_ICONBARCENTR_NAME;
const char ipc_grantee_name[]=IPC_GRANTEE_NAME;
const char ipc_control_name[]=IPC_CONTROL_NAME;
IPC_REQ gipc;

extern void kill_data(void *p, void (*func_p)(void *));
unsigned int oldHandlerAddr;
unsigned int* handlerAddr;
typedef void (*func)(short* num);
#pragma segment="ELFBEGIN"
const int minus11=-11;
CSM_RAM *under_idle;
GBSTMR timer;
GUI *datagui;
CSM_RAM *csm;
char s[40];
short* num;

extern const int volume_proplayer;
extern const int stat_proplayer;
extern const unsigned int volpro_icon;
extern const unsigned int statpro_icon;

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

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

typedef  unsigned short word;
extern unsigned long strtoul(const char *nptr,char **endptr,int base);

extern const int allcsm;
extern const int csm1;
extern const unsigned int csm1_icon;
extern const char csm1_name[64];
void taimer()
{
  int c;
  csm=((CSM_RAM *)(CSM_root()->csm_q->csm.first))->next;
  do
  {
    CSM_DESC *desc=csm->constr;
    sprintf(s,"%08X",desc);
  }
  while((csm=csm->next)&&(s!=csm1_name));
  c=strcmp(s,csm1_name);
  if((CSM_root()->csm_q->current_msg_processing_csm==csm))
  {
    if(c==0)
    {
      datagui=GetTopGUI();
      if(datagui)
      {
        if(csm1)
        {
          AddIconToIconBar(csm1_icon,num);
        }
      }
    }
  }
  GBS_StartTimerProc(&timer,50,taimer);
}

void GPRS()
{
  extern const int gprs_con;
  extern const int gprs_dis;
  extern const unsigned int gprss_icon;
  extern const unsigned int gprsc_icon;
  extern const unsigned int gprsd_icon;
  extern const int ena_gui_gprs;
  if(IsGPRS())//GPRS
  {
    if(IsGPRSEnabled())
    {
      if(IsGPRSConnected())
      {
        AddIconToIconBar(gprsc_icon,num);
      }
      else
        if(gprs_con)
        {
          AddIconToIconBar(gprss_icon,num);
        }
    }
    else
      if(gprs_dis)
      {
        AddIconToIconBar(gprsd_icon,num);
      }
  }
}

void EDGE()
{
  extern const int edge_con;
  extern const int edge_dis;
  extern const unsigned int edges_icon;
  extern const unsigned int edgec_icon;
  extern const unsigned int edged_icon;
  extern const int ena_gui_edge;
#ifdef CONFIG_EL
  if(IsEDGE())//EDGE
  {
    if(IsGPRSEnabled())
    {
      if(IsGPRSConnected())
      {
        AddIconToIconBar(edgec_icon,num);
      }
      else
        if(edge_con)
        {
          AddIconToIconBar(edges_icon,num);
        }
    }
    else
      if(edge_dis)
      {
        AddIconToIconBar(edged_icon,num);
      }
  }
#endif
#ifdef CONFIG_NSG
  if(*RamIsEDGE()==1)//EDGE
  {
    if(IsGPRSEnabled())
    {
      if(IsGPRSConnected())
      {
        AddIconToIconBar(edgec_icon,num);
      }
      else
        if(edge_con)
        {
          AddIconToIconBar(edges_icon,num);
        }
    }
    else
      if(edge_dis)
      {
        AddIconToIconBar(edged_icon,num);
      }
  }
#endif
}

static void addIconBar(short* num)//Добавляем иконки в иконбар
{
  void *icsm;
  icsm=FindCSMbyID(CSM_root()->idle_id);
  #define idlegui_id(icsm) (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
  //Java
  extern const int java;
  extern const int two_java;
  extern const unsigned int java_icon;
  extern const unsigned int two_java_icon;
  extern const int ena_gui_java;
  //Громкость
  extern const int volume;
  extern const unsigned int vol_icon;
  extern const int only_sound;
  extern const int ena_gui_volume;
  //Профили
  extern const int profile;
  extern const unsigned int profile1_icon;
  extern const unsigned int profile2_icon;
  extern const unsigned int profile3_icon;
  extern const unsigned int profile4_icon;
  extern const unsigned int profile5_icon;
  extern const unsigned int profile6_icon;
  extern const unsigned int profile7_icon;
  extern const unsigned int profile8_icon;
  extern const int ena_gui_profile;
  //Фонарик
  extern const int lamp;
  extern const unsigned int lamp_icon;
  extern const int ena_gui_lamp;
  //Интернет
  extern const int inet;
  extern const int ena_inet;
  //Вибра
  extern const int vibra;
  extern const int vibra_off;
  extern const unsigned int vibra_icon;
  extern const unsigned int vibra_off_icon;
  extern const int ena_gui_vibra;
  //Будильник
  extern const int alarm;
  extern const unsigned int alarm_icon;
  extern const int ena_gui_alarm;
  //Камера
  extern const int camera;
  extern const unsigned int camera_icon;
  extern const int ena_gui_camera;
  //Медиаплеер
  extern const int mediapleer;
  extern const int sta_mediapleer;
  extern const unsigned int play_mediapleer_icon;
  extern const unsigned int pausa_mediapleer_icon;
  extern const unsigned int stop_mediapleer_icon;
  extern const int ena_gui_mediapleer;
  //Звук
  extern const int sounds;
  extern const int sounds_on;
  extern const unsigned int sound_on_icon;
  extern const unsigned int sound_off_icon;
  extern const int ena_gui_sounds;
  //Звонок
  extern const int call;
  extern const int decrypt;
  extern const unsigned int call_icon;
  extern const unsigned int decrypt_icon;
  extern const int ena_gui_call;
   //Расширенный
     extern const int ext_call;
     extern const unsigned int out_ext_call_icon;
     extern const unsigned int in_ext_call_icon;
     extern const unsigned int wait_ext_call_icon;
     extern const unsigned int talk_ext_call_icon;
     extern const int ena_gui_ext_call;
  //Блокировка
  extern const int lock;
  extern const int lock_off;
  extern const unsigned int lock_on_icon;
  extern const unsigned int lock_off_icon;
  extern const int ena_gui_lock;
  //Гарнитура
  extern const int nayshniki;
  extern const int nayshniki_mono;
  extern const unsigned int nayshniki_icon;
  extern const int ena_gui_nayshniki;
  //Bluetooth
  extern const int bt;
  extern const int bt_off;
  extern const unsigned int bt_vis_icon;
  extern const unsigned int bt_nvis_icon;
  extern const unsigned int bt_trans_icon;
  extern const unsigned int bt_ntrans_icon;
  extern const unsigned int bt_headset_icon;
  extern const unsigned int bt_off_icon;
  extern const int ena_gui_bt;
  //SMS
  extern const int sms;
  extern const int sms_both;
  extern const int ena_gui_sms;
  extern const unsigned int sms_send_icon;
  extern const unsigned int sms_recv_icon;
  extern const unsigned int sms_both_icon;
  //Сохранение файлов(MicroSD)
  extern const int microsd;
  extern const unsigned int microsd_icon;
  extern const int ena_gui_microsd;
  //Автомобиль
  extern const int car;
  extern const unsigned int car_icon;
  extern const int ena_gui_car;
  //irDa(S75)
  extern const int irda;
  extern const int irda_off;
  extern const unsigned int irda_icon;
  extern const unsigned int irda_trans_icon;
  extern const unsigned int irda_off_icon;
  extern const int ena_gui_irda;
  //Колонки(IMS-700)(S75)
  extern const int colonki;
  extern const unsigned int colonki_icon;
  extern const int ena_gui_colonki;
  //Радио(Е71)
  extern const int radio;
  extern const unsigned int radio_icon;
  extern const int ena_gui_radio;
  //OBEX
  extern const int obex;
  extern const unsigned int obex_icon;
  extern const int ena_gui_obex;
  //Набор номера
  extern const int typing;
  extern const unsigned int typing_icon;
  extern const int ena_gui_typing;
  //Пользователь
  extern const int user;
  extern const unsigned int user_icon;
  extern const int ena_gui_user;
#ifdef CONFIG_EL
  //MicroSD (c) Shadows-------------------
  #define RAMCACHE (*RamIsFileCache())
  typedef struct{
  int counter;
  int isdumping;
  char unkb[0x18];
  short bar1[6];
  short bar2[6];
  }ico_cache;
  ico_cache *ramcache=(void*)RAMCACHE;
#endif
  //Java
  if(java)
  {
    switch(ena_gui_java)
    {
    case 0:
      if(*RamIsRunJava()==1)
      {
        AddIconToIconBar(java_icon,num);
      }
      if(two_java)
      {
        if(*RamIsRunJava()==2)
        {
          AddIconToIconBar(two_java_icon,num);
        }
      }
      break;
    case 1:
      if(icsm)
      {
        if(IsGuiOnTop(idlegui_id(icsm)))
        {
          if(*RamIsRunJava()==1)
          {
            AddIconToIconBar(java_icon,num);
          }
          if(two_java)
          {
            if(*RamIsRunJava()==2)
            {
              AddIconToIconBar(two_java_icon,num);
            }
          }
        }
      }
      break;
    case 2:
      if(!icsm)
      {
        if(IsGuiOnTop(idlegui_id(icsm)))
        {
          if(*RamIsRunJava()==1)
          {
            AddIconToIconBar(java_icon,num);
          }
          if(two_java)
          {
            if(*RamIsRunJava()==2)
            {
              AddIconToIconBar(two_java_icon,num);
            }
          }
        }
      }
      break;
    }
  }
  //Громкость
  if(volume)
  {
    switch(only_sound)
    {
    case 0:
      if(IsPlayerOn())
      {
        AddIconToIconBar(*RamVolumeStep()+vol_icon,num);
      }
      break;
    case 1:
      if(GetPlayStatus()==2)
      {
        AddIconToIconBar(*RamVolumeStep()+vol_icon,num);
      }
      break;
    }
  }
  //Профили
  if(profile)
  {
    if(GetProfile()==0)
    {
      AddIconToIconBar(profile1_icon,num);
    }
    if(GetProfile()==1)
    {
      AddIconToIconBar(profile2_icon,num);
    }
    if(GetProfile()==2)
    {
      AddIconToIconBar(profile3_icon,num);
    }
    if(GetProfile()==3)
    {
      AddIconToIconBar(profile4_icon,num);
    }
    if(GetProfile()==4)
    {
      AddIconToIconBar(profile5_icon,num);
    }
    if(GetProfile()==5)
    {
      AddIconToIconBar(profile6_icon,num);
    }
    if(GetProfile()==6)
    {
      AddIconToIconBar(profile7_icon,num);
    }
    if(GetProfile()==7)
    {
      AddIconToIconBar(profile8_icon,num);
    }
  }
  //Фонарик
  if(lamp)
  {
    if(*RamLighterPower())
    {
      AddIconToIconBar(lamp_icon,num);
    }
  }
  //Интернет
  if(inet)
  {
    switch(ena_inet)
    {
    case 0://Отображаем всё
      GPRS();
      EDGE();
      break;
    case 1://Отображаем GPRS
      GPRS();
      break;
    case 2://Отображаем EDGE
      EDGE();
      break;
    }
  }
  //Вибра
  if(vibra)
  {
    if(GetVibraStatus())
    {
      AddIconToIconBar(vibra_icon,num);
    }
    if(vibra_off)
    {
      if(!GetVibraStatus())
      {
        AddIconToIconBar(vibra_off_icon,num);
      }
    }
  }
  //Будильник
  if(alarm)
  {
    if(*RamAlarm()==1)
    {
      AddIconToIconBar(alarm_icon,num);
    }
  }
  //Камера
  if(camera)
  {
    if(*RamIsRunCamera()==1)
    {
      AddIconToIconBar(camera_icon,num);
    }
  }
  //Медиаплеер
  if(mediapleer)
  {
    switch(sta_mediapleer)
    {
    case 0:
      if(IsPlayerOn())
      {
        AddIconToIconBar(play_mediapleer_icon,num);
      }
      break;
    case 1:
      if(GetPlayStatus()==2)
      {
        AddIconToIconBar(play_mediapleer_icon,num);
      }
      if(GetPlayStatus()==1)
      {
        AddIconToIconBar(pausa_mediapleer_icon,num);
      }
      if(GetPlayStatus()==0)
      {
        if(IsPlayerOn())
        {
          AddIconToIconBar(stop_mediapleer_icon,num);
        }
      }
      break;
    }
  }
  //Звук
  if(sounds)
  {
    switch(sounds_on)
    {
    case 0:
      if(*RamRingtoneStatus()==1)
      {
        AddIconToIconBar(sound_off_icon,num);
      }
      break;
    case 1:
      if(*RamRingtoneStatus()==0)
      {
        AddIconToIconBar(sound_on_icon,num);
      }
      if(*RamRingtoneStatus()==1)
      {
        AddIconToIconBar(sound_off_icon,num);
      }
      break;
    }
  }
  //Звонок
  if(call)
  {
    if(IsCalling())
    {
      if(decrypt)
      {
        if(isDecryption())
        {
          AddIconToIconBar(decrypt_icon,num);
        }
      }
      AddIconToIconBar(call_icon,num);
    }
  }
  if(ext_call)//Расширенный
  {
    if(*RamCallState()==1)
    {
      AddIconToIconBar(out_ext_call_icon,num);
    }
    if(*RamCallState()==2)
    {
      AddIconToIconBar(wait_ext_call_icon,num);
    }
    if(*RamCallState()==3)
    {
      AddIconToIconBar(in_ext_call_icon,num);
    }
    if(*RamCallState()==4)
    {
      AddIconToIconBar(talk_ext_call_icon,num);
    }
  }
  //Блокировка
  if(lock)
  {
    switch(lock_off)
    {
    case 0:
      if(!IsUnlocked())
      {
        AddIconToIconBar(lock_on_icon,num);
      }
      break;
    case 1:
      if(IsUnlocked())
      {
        AddIconToIconBar(lock_off_icon,num);
      }
      if(!IsUnlocked())
      {
        AddIconToIconBar(lock_on_icon,num);
      }
      break;
    }
  }
  //Гарнитура
  if(nayshniki)
  {
#ifdef ELKA
    if(GetAccessoryType()==15)
    {
      AddIconToIconBar(nayshniki_icon,num);
    }
#else
    if(GetAccessoryType()==19)
    {
      AddIconToIconBar(nayshniki_icon,num);
    }
    if(nayshniki_mono)
    {
      if(GetAccessoryType()==18)
      {
        AddIconToIconBar(nayshniki_icon,num);
      }
    }
#endif
  }
  //Bluetooth
  if(bt)
  {
    if(!GetCurrAudioPath())
    {
      AddIconToIconBar(bt_headset_icon,num);
    }
    else
    {
      if(BT_GetLocVisibility()==0)
      {
        if(GetPeripheryState(0,1)||GetPeripheryState(0,2))
        {
          AddIconToIconBar(bt_nvis_icon,num);
        }
        else
          if(GetPeripheryState(0,4))
          {
            AddIconToIconBar(bt_ntrans_icon,num);
          }
          else
            if(bt_off)
            {
              AddIconToIconBar(bt_off_icon,num);
            }
      }
      if(BT_GetLocVisibility()==1)
      {
        if(GetPeripheryState(0,1)||GetPeripheryState(0,2))
        {
          AddIconToIconBar(bt_vis_icon,num);
        }
        else
          if(GetPeripheryState(0,4))
          {
            AddIconToIconBar(bt_trans_icon,num);
          }
          else
            if(bt_off)
            {
              AddIconToIconBar(bt_off_icon,num);
            }
      }
    }
  }
  //SMS
  if(sms)
  {
    if(sms_both)
    {
      if(GetSMSState()==3)
      {
        AddIconToIconBar(sms_both_icon,num);
      }
    }
    if(GetSMSState()==2)
    {
      AddIconToIconBar(sms_recv_icon,num);
    }
    if(GetSMSState())
    {
      AddIconToIconBar(sms_send_icon,num);
    }
  }
  //Автомобиль
  if(car)
  {
    if(GetAccessoryType()==1||2||3||4||5||6||7||8||9||10||11)
    {
      AddIconToIconBar(car_icon,num);
    }
  }
  #ifdef CONFIG_NSG
  //irDa(S75)
  if(irda)
  {
    if(GetPeripheryState(1,1)||GetPeripheryState(1,2))
    {
      AddIconToIconBar(irda_icon,num);
    }
    else
    if(GetPeripheryState(1,4))
    {
      AddIconToIconBar(irda_trans_icon,num);
    }
    else
    if(irda_off)
    {
      if(!GetPeripheryState(1,1||2||4))
      {
        AddIconToIconBar(irda_off_icon,num);
      }
    }
  }
  #endif
  #ifdef CONFIG_NSG
  //Колонки(S75)
  if(colonki)
  {
    if(GetAccessoryType()==29)
    {
      AddIconToIconBar(colonki_icon,num);
    }
  }
  #endif
  #ifdef CONFIG_EL
  //Радио(E71)
  if(radio)
  {
    if((*RamIsRunJava()+0x3891E)||(*RamIsRunJava()+0x3890C)==1)//+Смещение для функции определения Радио (c) Visad
    {
      AddIconToIconBar(radio_icon,num);
    }
  }
  //Сохранение файлов(MicroSD)
  if(microsd)
  {
    if(((ramcache->isdumping<<0x12)<0))
    {
      AddIconToIconBar(microsd_icon,num);
    }
  }
  #endif
  //OBEX
  if(obex)
  {
    if(*RamIsSendReceiveBT()-1==2)//-Смещение для функции определения OBEX (c) funMarkus
    {
      AddIconToIconBar(obex_icon,num);
    }
  }
  //Набор номера
  if(typing)
  {
    if(*RamIsNumberTyping()==1)
    {
      AddIconToIconBar(typing_icon,num);
    }
  }
  //Пользователь
  if(user)
  {
    AddIconToIconBar(user_icon,num);
  }
}

int maincsm_onmessage(CSM_RAM* data,GBS_MSG* msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  {
  if (msg->msg==MSG_IPC)
  {
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp(ipc->name_to,ipc_my_name)==0)//strcmp_nocase
      {
        switch (msg->submess)
        {
          if(volume_proplayer)
          {
          case IPC_SHOW_PP_VOLUME0:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME1:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+1,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME2:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+2,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME3:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+3,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME4:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+4,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME5:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+5,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME6:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+6,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME7:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+7,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME8:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+8,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME9:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+9,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME10:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+10,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME11:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+11,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME12:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+12,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME13:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+13,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME14:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+14,num);
            }
            break;
          case IPC_SHOW_PP_VOLUME15:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(volpro_icon+15,num);
            }
            break;
            }
          if(stat_proplayer)
          {
          case IPC_SHOW_PP_STATUS16:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(statpro_icon,num);
            }
            break;
          case IPC_SHOW_PP_STATUS17:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(statpro_icon+1,num);
            }
            break;
          case IPC_SHOW_PP_STATUS18:
            ipc->data=(void *)((int)(ipc->data)+1);
            if (ipc->name_from==ipc_control_name)
            {
              AddIconToIconBar(statpro_icon+2,num);
            }
            break;
          }
        }
      }
    }
  }
  }
  if(msg->msg == MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      extern const int ena_req;
      if(ena_req) ShowMSG(1,(int)"Конфиг IconbarCentr обновлен!");
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
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

static unsigned short maincsm_name_body[140];

typedef struct
{
  char check_name[8];
  int addr;
}ICONBAR_H;

struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
  ICONBAR_H iconbar_handler;
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
  sizeof(CSM_RAM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  },
  {
    "IconBar"
  }
};

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"IconbarCentr v1.0 - (c) KIBER-DEMON");
}

void SetIconBarHandler()
{
  MAINCSM.iconbar_handler.addr=(int)addIconBar;
}

int main()
{
  InitConfig();
  CSMROOT *csmr;
  CSM_RAM *save_cmpc;
  CSM_RAM main_csm;
  UpdateCSMname();
  SetIconBarHandler();
  LockSched();
  csmr=CSM_root();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  extern const int ena_msg;
  if (ena_msg) ShowMSG(1,(int)"IconbarCentr установлен!");
  return 0;
}
