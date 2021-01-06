#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"CSM list file",3,127};
#ifdef NEWSGOLD
__root const char csmlist_fname[128]="4:\\ZBin\\etc\\CSMlist.txt";
#else 
__root const char csmlist_fname[128]="0:\\ZBin\\etc\\CSMlist.txt";
#endif

__root const CFG_HDR cfghdr23={CFG_CBOX,"Activation style",0,4};
__root const int ACTIVE_KEY_STYLE=0;
__root const CFG_CBOX_ITEM cfgcbox23[4]={"Short press","Long press","* + #","Enter Button"};

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr24={CFG_UINT,"Activation key",0,99};
__root const int ACTIVE_KEY=99;
#else
#ifdef ELKA
__root const CFG_HDR cfghdr24={CFG_UINT,"Activation key",0,99};
__root const int ACTIVE_KEY=0x15;
#else
__root const CFG_HDR cfghdr24={CFG_UINT,"Activation key",0,99};
__root const int ACTIVE_KEY=0x11;
#endif
#endif

__root const CFG_HDR cfghdr25={CFG_STR_WIN1251,"UnderIdleCSM_DESC",0,8};
__root const char UNDER_IDLE_CONSTR[9]="";

__root const CFG_HDR cfghdr2={CFG_CBOX,"Extra: on longpress",0,5};
__root const int ENA_LONG_PRESS=2;
__root const CFG_CBOX_ITEM cfgcbox2[5]={"As in FW","Do nothing","Hide all tasks","Launch XTask","Hide & Lock"};

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr3={CFG_CBOX,"Red button mode",0,3};
__root const int RED_BUT_MODE=2;
__root const CFG_CBOX_ITEM cfgcbox3[3]={"As in FW","Classic","Hide all tasks"};
#endif

__root const CFG_HDR cfghdr22={CFG_CBOX,"Enable if keyboard locked",0,2};
__root const int ENA_LOCK=1;
__root const CFG_CBOX_ITEM cfgcbox22[2]={"No","Yes"};

__root const CFG_HDR cfghdr27={CFG_CBOX,"Show NewStyleDaemons",0,2};
__root const int SHOW_DAEMONS=1;
__root const CFG_CBOX_ITEM cfgcbox27[2]={"No","Yes"};

__root const CFG_HDR cfghdr50={CFG_CBOX,"char style",0,2};
__root const int style=1;
__root const CFG_CBOX_ITEM cfgcbox28[2]={"Tasks:","T:"};

__root const CFG_HDR cfghdr49={CFG_CBOX,"use joy left to close tasks",0,2};
__root const int cleseri=0;
__root const CFG_CBOX_ITEM cfgcbox29[2]={"No","Yes"};

__root const CFG_HDR cfghdr28={CFG_STR_UTF8,"background",3,127};
__root const char background_img[128]="4:\\ZBin\\xtask3\\background.png";

__root const CFG_HDR cfghdr29={CFG_STR_UTF8,"cursor",3,127};
__root const char cursor_img[128]="4:\\ZBin\\xtask3\\cursor.png";

//__root const CFG_HDR cfghdr34={CFG_STR_UTF8,"selection img",3,127};
//__root const char selection_img[128]="4:\\ZBin\\xtask3\\selection.png";

//__root const CFG_HDR cfghdr35={CFG_STR_UTF8,"tasks img",3,127};
//__root const char tasks_img[128]="4:\\ZBin\\xtask3\\tasks.png";

//__root const CFG_HDR cfghdr36={CFG_STR_UTF8,"bookmarks img",3,127};
//__root const char bookmarks_img[128]="4:\\ZBin\\xtask3\\bookmarks.png";

__root const CFG_HDR cfghdr30={CFG_STR_UTF8,"icon list",3,127};
__root const char icon_list_path[128]="4:\\ZBin\\xtask3\\icon_list.txt";

__root const CFG_HDR cfghdr31={CFG_STR_UTF8,"bookmark list",3,127};
__root const char bokmark_list_path[128]="4:\\ZBin\\xtask3\\bookmark_list.txt";

//__root const CFG_HDR cfghdr32={CFG_STR_UTF8,"turnoff path",3,127};
//__root const char turnoff_path[128]="4:\\ZBin\\xtask3\\turnoff\\";

__root const CFG_HDR cfghdr56 = {CFG_COLOR, "task color/bookmark", 0, 0};
__root const char ctasks[4]={255,255,255,100};

__root const CFG_HDR cfghdr57 = {CFG_COLOR, "daemon color", 0, 0};
__root const char cdaemons[4]={255,255,255,100};

__root const CFG_HDR cfghdr58 = {CFG_COLOR, "info color", 0, 0};
__root const char cinfo[4]={255,255,255,100};

