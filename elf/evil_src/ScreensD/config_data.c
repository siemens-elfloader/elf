#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX,"Show Copyright",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};

__root const CFG_HDR cfghdr64={CFG_UINT,"sec to start",0,2000};
__root const unsigned int LAIKS=30;

__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"screensaver path",0,63};
__root const char screenpath[64]="4:\\zbin\\screensavers\\screensaver.elf";
