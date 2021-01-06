#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"Enable hello message",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};

__root const CFG_HDR cfghdr1 = {CFG_UINT, "Refresh rate (1/10 sec):", 0, 50};
__root const unsigned int cfgUpTime=1;

__root const CFG_HDR cfghdr2 = {CFG_UINT, "Quantity:", 0, 10};
__root const unsigned int vibra_count=1;

__root const CFG_HDR cfghdr3 = {CFG_UINT, "Power:", 0, 100};
__root const unsigned int vibra_power=10;

//---------------------------------------------------------------
__root const CFG_HDR cfghdr4={CFG_LEVEL,"Melody adjustment",1,0};

__root const CFG_HDR cfghdr6_1={CFG_CBOX,"Play melody?",0,2};
__root const int ENA_WAV=1;
__root const CFG_CBOX_ITEM cfgcbox8[2]={"No","Yes"};

__root const CFG_HDR cfghdr6_2={CFG_STR_UTF8,"Lock melody:",0,127};
__root const char lockfname[128]="4:\\ZBin\\Snd\\Vibralocker\\Lock.wav";

__root const CFG_HDR cfghdr6_3={CFG_STR_UTF8,"Unlock melody:",0,127};
__root const char unlockfname[128]="4:\\ZBin\\Snd\\Vibralocker\\UnLock.wav";

__root const CFG_HDR cfghdr6_4={CFG_UINT,"Volume:",0,6};
__root const unsigned int MelVolume=3;

__root const CFG_HDR cfghdr5={CFG_LEVEL,"",0,0};

