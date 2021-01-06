#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0 = {CFG_UINT, "Timer1 time (1/10 sec)", 1, 10000};
__root const unsigned int Time1 = 2;

__root const CFG_HDR cfghdr1={CFG_CHECKBOX,"Enable 2 timer",0,2};
__root const unsigned int EnTimer2=1;

__root const CFG_HDR cfghdr2 = {CFG_UINT, "Timer2 time (1/10 sec)", 1, 10000};
__root const unsigned int Time2 = 20;

__root const CFG_HDR cfghdr3={CFG_CHECKBOX,"Enable 3 timer",0,2};
__root const unsigned int EnTimer3=1;

__root const CFG_HDR cfghdr4 = {CFG_UINT, "Timer3 time (1/10 sec)", 1, 10000};
__root const unsigned int Time3 = 2000;
///////////////////////////

