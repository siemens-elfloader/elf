#include "..\inc\cfg_items.h"
//Конфигурация
__root const CFG_HDR cfghdr0={CFG_STR_UTF8,"CSM list file",3,127};
#ifdef NEWSGOLD
__root const char csmlist_fname[128]="4:\\ZBin\\etc\\CSMlist.txt";
#else 
__root const char csmlist_fname[128]="0:\\ZBin\\etc\\CSMlist.txt";
#endif

__root const CFG_HDR cfghdr2y={CFG_LEVEL,"Key Config",1,0};
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
  __root const CFG_HDR cfghdr3={CFG_CBOX,"Red button mode",0,5};
  __root const int RED_BUT_MODE=2;
  __root const CFG_CBOX_ITEM cfgcbox3[5]={"As in FW","Classic","Hide all tasks", "close all exept list","Next task"};

  __root const CFG_HDR cfghdr3q={CFG_CBOX,"Long Red button mode",0,2};
  __root const int LONG_RED_BUT_MODE=1;
  __root const CFG_CBOX_ITEM cfgcbox3q[2]={"Next task","Hide all tasks"};
#endif

  __root const CFG_HDR cfghdr22={CFG_CBOX,"Enable if keyboard locked",0,2};
  __root const int ENA_LOCK=1;
  __root const CFG_CBOX_ITEM cfgcbox22[2]={"No","Yes"};

  __root const CFG_HDR cfghdr49={CFG_CBOX,"use joy left to close tasks",0,2};
  __root const int cleseri=0;
  __root const CFG_CBOX_ITEM cfgcbox29[2]={"No","Yes"};

#ifdef NEWSGOLD
  __root const CFG_HDR cfghdr49a={CFG_CBOX,"use turn off red button idle",0,2};
  __root const int use_idle=1;
  __root const CFG_CBOX_ITEM cfgcbox29a[2]={"No","Yes"};
#endif 
  
  __root const CFG_HDR cfghdr49aa={CFG_CBOX,"green button in xtask = turn off",0,2};
  __root const int use_green=1;
  __root const CFG_CBOX_ITEM cfgcbox29ae[2]={"No","Yes"};

#ifdef NEWSGOLD
  __root const CFG_HDR cfghdr244={CFG_CBOX,"Use naticq call with vol- on ms",0,2};
  __root const int use_natioq=0;
  __root const CFG_CBOX_ITEM cfgcbox26a[2]={"No","Yes"};
#endif
__root const CFG_HDR cfghdrw1y={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr3a={CFG_STR_UTF8,"exept list",3,127};
__root const char exept_list[128]="NATICQ, MC, NRSS";

__root const CFG_HDR cfghdr27={CFG_CBOX,"Show NewStyleDaemons",0,2};
__root const int SHOW_DAEMONS=1;
__root const CFG_CBOX_ITEM cfgcbox27[2]={"No","Yes"};

__root const CFG_HDR cfghdr26={CFG_CBOX,"Show IDLE screen",0,2};
__root const int SHOW_IDLESCREEN=1;
__root const CFG_CBOX_ITEM cfgcbox26[2]={"No","Yes"};

__root const CFG_HDR cfghdr28={CFG_STR_UTF8,"xtask Path",3,127};
__root const char path_file[128]="0:\\ZBin\\xtask3\\";

__root const CFG_HDR cfghdrw={CFG_LEVEL,"Color Control",1,0};
  __root const CFG_HDR cfghdr26l={CFG_CBOX,"Use Trasnperency",0,2};
  __root const int use_trans=1;
  __root const CFG_CBOX_ITEM cfgcbox26l[2]={"No","Yes"};

  __root const CFG_HDR cfghdr56 = {CFG_COLOR, "task color/bookmark", 0, 0};
  __root const char ctasks[4]={255,255,255,100};

#ifdef ELKA
  __root const CFG_HDR cfghdr56g = {CFG_COLOR, "task selected color", 0, 0};
  __root const char ctasksi[4]={0,0,255,100};
#endif

  __root const CFG_HDR cfghdr57 = {CFG_COLOR, "daemon color", 0, 0};
  __root const char cdaemons[4]={255,0,0,100};

  __root const CFG_HDR cfghdr58 = {CFG_COLOR, "info color", 0, 0};
  __root const char cinfo[4]={240,180,0,100};
  
  __root const CFG_HDR cfghdr58q = {CFG_COLOR, "Side Progresbar line", 0, 0};
  __root const char Side1[4]={0,255,0,100};
  
  __root const CFG_HDR cfghdr58w = {CFG_COLOR, "Side Progresbar bar", 0, 0};
  __root const char Side2[4]={255,0,0,100};
  
  __root const CFG_HDR cfghdr58e = {CFG_COLOR, "Reboot bar color", 0, 0};
  __root const char rebc[4]={255,255,0,100};
  
__root const CFG_HDR cfghdrw1={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdrwz={CFG_LEVEL,"Idle task icons",1,0};
  __root const CFG_HDR cfghdr59 = {CFG_CBOX,"Idle Task Icons",0,2};
  __root const unsigned int IDLETASKS = 1;
  __root const CFG_CBOX_ITEM cfgcbox8a[2]={"No","Yes"};

  __root const CFG_HDR cfghdr3q1={CFG_CBOX,"Idle icons polarity",0,2};
  __root const int horizontality=1;
  __root const CFG_CBOX_ITEM cfgcbox3q1[2]={"Vertical","Horizontal"};

  __root const CFG_HDR cfghdr60={CFG_COORDINATES,"Idle Task position",0,0};
  __root const unsigned int IDLET_X=2; //2
  __root const unsigned int IDLET_Y=32;  //62
__root const CFG_HDR cfghdrw1x={CFG_LEVEL,"",0,0};

