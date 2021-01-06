#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"CSM list file",3,127};
#ifdef NEWSGOLD
__root const char csmlist_fname[128]="4:\\ZBin\\etc\\CSMlist.txt";
#else 
__root const char csmlist_fname[128]="0:\\ZBin\\etc\\CSMlist.txt";
#endif

__root const CFG_HDR cfghdr1={CFG_CBOX,"Enable hello message",0,2};
__root const int ENA_HELLO_MSG=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};


#ifdef NEWSGOLD
__root const CFG_HDR cfghdr3={CFG_CBOX,"Red button mode",0,3};
__root const int RED_BUT_MODE=2;
__root const CFG_CBOX_ITEM cfgcbox3[3]={"As in FW","Classic","Hide all tasks"};
#endif

__root const CFG_HDR cfghdr22={CFG_CBOX,"Enable if keyboard locked",0,2};
__root const int ENA_LOCK=0;
__root const CFG_CBOX_ITEM cfgcbox22[2]={"No","Yes"};

__root const CFG_HDR cfghdr4={CFG_STR_WIN1251,"Bookmark 1 name",1,31};
__root const char BM1NAME[32]="";
__root const CFG_HDR cfghdr5={CFG_STR_UTF8,"Bookmark 1 file",3,127};
__root const char BM1FILE[128]="";

__root const CFG_HDR cfghdr6={CFG_STR_WIN1251,"Bookmark 2 name",1,31};
__root const char BM2NAME[32]="";
__root const CFG_HDR cfghdr7={CFG_STR_UTF8,"Bookmark 2 file",3,127};
__root const char BM2FILE[128]="";

__root const CFG_HDR cfghdr8={CFG_STR_WIN1251,"Bookmark 3 name",1,31};
__root const char BM3NAME[32]="";
__root const CFG_HDR cfghdr9={CFG_STR_UTF8,"Bookmark 3 file",3,127};
__root const char BM3FILE[128]="";

__root const CFG_HDR cfghdr10={CFG_STR_WIN1251,"Bookmark 4 name",1,31};
__root const char BM4NAME[32]="";
__root const CFG_HDR cfghdr11={CFG_STR_UTF8,"Bookmark 4 file",3,127};
__root const char BM4FILE[128]="";

__root const CFG_HDR cfghdr12={CFG_STR_WIN1251,"Bookmark 5 name",1,31};
__root const char BM5NAME[32]="";
__root const CFG_HDR cfghdr13={CFG_STR_UTF8,"Bookmark 5 file",3,127};
__root const char BM5FILE[128]="";

__root const CFG_HDR cfghdr14={CFG_STR_WIN1251,"Bookmark 6 name",1,31};
__root const char BM6NAME[32]="";
__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"Bookmark 6 file",3,127};
__root const char BM6FILE[128]="";

__root const CFG_HDR cfghdr16={CFG_STR_WIN1251,"Bookmark 7 name",1,31};
__root const char BM7NAME[32]="";
__root const CFG_HDR cfghdr17={CFG_STR_UTF8,"Bookmark 7 file",3,127};
__root const char BM7FILE[128]="";

__root const CFG_HDR cfghdr18={CFG_STR_WIN1251,"Bookmark 8 name",1,31};
__root const char BM8NAME[32]="";
__root const CFG_HDR cfghdr19={CFG_STR_UTF8,"Bookmark 8 file",3,127};
__root const char BM8FILE[128]="";

__root const CFG_HDR cfghdr20={CFG_STR_WIN1251,"Bookmark 9 name",1,31};
__root const char BM9NAME[32]="";
__root const CFG_HDR cfghdr21={CFG_STR_UTF8,"Bookmark 9 file",3,127};
__root const char BM9FILE[128]="";
