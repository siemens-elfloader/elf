#include "..\inc\cfg_items.h"
//Конфигурация
//__root const CFG_HDR cfghdr0={CFG_CBOX,"Type",0,3};
//__root const int type1=2;
//__root const CFG_CBOX_ITEM cfgcbox4[3]={"File","Shortcut","Adress"};

__root const CFG_HDR cfghdr0 = {CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibraPower=100;

__root const CFG_HDR cfghdr1 = {CFG_UINT, "Vibra cycle(max 5k)", 0, 5000};
__root const unsigned int vibra = 3;

__root const CFG_HDR cfghdr2 = {CFG_CBOX, "Show copyright text at startup", 0, 2};
__root const int zajebalo = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr_m1_1={CFG_LEVEL,"First vibra in cycle",1,0};

__root const CFG_HDR cfghdr1_0 = {CFG_UINT, "vibra lenght 1/10sec(max 1k)", 0, 1000};
__root const unsigned int TMR_SECOND = 10;

__root const CFG_HDR cfghdr1_1 = {CFG_UINT, "pause vibra 1/10sec(max 1k)", 0, 1000};
__root const unsigned int TMR_SECOND2 = 30;

__root const CFG_HDR cfghdr_m1_0={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m2_1={CFG_LEVEL,"Second vibra in cycle",1,0};

__root const CFG_HDR cfghdr2_0 = {CFG_UINT, "vibra lenght 1/10sec(max 1k)", 0, 1000};
__root const unsigned int TMR_SECOND3 = 10;

__root const CFG_HDR cfghdr2_1 = {CFG_UINT, "pause vibra 1/10sec(max 1k)", 0, 1000};
__root const unsigned int TMR_SECOND4 = 30;

__root const CFG_HDR cfghdr_m2_0={CFG_LEVEL,"",0,0};
