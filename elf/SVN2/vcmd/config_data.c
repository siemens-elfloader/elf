#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX, "Enable messages", 0, 2};
__root const int ENA_MSGS=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No", "Yes"};

__root const CFG_HDR cfghdr1={CFG_UINT, "Interval between commands", 1, 60};
__root const unsigned int INTERVAL_NEXTCMD=1;

__root const CFG_HDR cfghdr2={CFG_STR_UTF8, "Commands config file", 3, 127};
__root const char vcmdcfg_fname[128]=DEFAULT_DISK ":\\ZBin\\etc\\vcmd.cfg";

__root const CFG_HDR cfghdr3={CFG_STR_UTF8, "Quit sound file", 3, 127};
__root const char quit_fname[128]=DEFAULT_DISK ":\\Sounds\\vcmd\\quit.wav";
