#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_CBOX,"Show copyright",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"No","Yes"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"where to show",0,2};
__root const int everywhere=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"Main only","All"};

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"png path",0,63};
__root const char path[64]="4:\\ZBin\\lampo4ki\\";

__root const CFG_HDR cfghdr3={CFG_CBOX,"Screen size",0,2};
__root const int SSSS=0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"240x320","132x176"};
