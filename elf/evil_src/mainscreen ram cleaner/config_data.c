#include "..\inc\cfg_items.h"
//Конфигурация

__root const CFG_HDR cfghdr0 = {CFG_UINT, "Min ram for refresh(KB)", 0, 7000};
__root const unsigned int refresh = 1300;

__root const CFG_HDR cfghdr1={CFG_CBOX,"Show message",0,2};
__root const int message=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};
