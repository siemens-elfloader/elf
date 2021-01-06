#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"Показывать окошко приветствия",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"Нет","Да"};

__root const CFG_HDR cfghdr1 = {CFG_UINT, "Частота обновления (1/10 sec):", 0, 50};
__root const unsigned int cfgUpTime=1;

__root const CFG_HDR cfghdr2 = {CFG_UINT, "Кол-во вибраций:", 0, 10};
__root const unsigned int vibra_count=1;

__root const CFG_HDR cfghdr3 = {CFG_UINT, "Мощность вибраций:", 0, 100};
__root const unsigned int vibra_power=10;

//---------------------------------------------------------------
__root const CFG_HDR cfghdr4={CFG_LEVEL,"Настройки мелодии",1,0};

__root const CFG_HDR cfghdr6_1={CFG_CBOX,"Проигрывать мелодию?",0,2};
__root const int ENA_WAV=1;
__root const CFG_CBOX_ITEM cfgcbox8[2]={"Нет","Да"};

__root const CFG_HDR cfghdr6_2={CFG_STR_UTF8,"Мелодия блокировки:",0,127};
__root const char lockfname[128]="4:\\ZBin\\Snd\\Vibralocker\\Lock.wav";

__root const CFG_HDR cfghdr6_3={CFG_STR_UTF8,"Мелодия разблокировки:",0,127};
__root const char unlockfname[128]="4:\\ZBin\\Snd\\Vibralocker\\UnLock.wav";

__root const CFG_HDR cfghdr6_4={CFG_UINT,"Громкость:",0,6};
__root const unsigned int MelVolume=3;

__root const CFG_HDR cfghdr5={CFG_LEVEL,"",0,0};

