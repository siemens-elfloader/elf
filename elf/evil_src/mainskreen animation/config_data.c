#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX,"Show copyright",0,2};
__root const int ENA_HELLO_MSG=0;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};

__root const CFG_HDR cfghdr1={CFG_COORDINATES,"Idle icon position",0,0};
__root const unsigned int IDLEICON_X=0;
__root const unsigned int IDLEICON_Y=50;

__root const CFG_HDR cfghdr2 = {CFG_UINT, "Speed", 0, 600};
__root const unsigned int REFRESH = 262;

__root const CFG_HDR cfghdr3 = {CFG_UINT, "count of png", 0, 100};
__root const unsigned int PNG = 17;

__root const CFG_HDR cfghdr6={CFG_STR_UTF8,"png path",0,63};
__root const char path[64]="4:\\ZBin\\anime\\";
