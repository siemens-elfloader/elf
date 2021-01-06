
#include "C:\arm\inc\cfg_items.h"
#include "C:\arm\inc\swilib.h"


//Путь и имя
__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Каталог",1,127};
__root const char folder[128]="4:\\dicts\\";

__root const CFG_HDR cfghdr2={CFG_CBOX,"Битрейт",0,3};
__root const  int bitrate=0;
__root const CFG_CBOX_ITEM cfgcbox2[]={"4.750","7.400","12.200"};

__root const CFG_HDR cfghdr3={CFG_CBOX,"Amr mode",0,3};
__root const  int amrmode=0;
__root const CFG_CBOX_ITEM cfgcbox3[]={"0","4","7"};

__root const CFG_HDR cfghdr4={CFG_UINT,"Макс. hазмер(кб)",1,1014*1024};
__root const int size=7000;
