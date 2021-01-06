#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"


#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

// Настройка клавиш

__root const CFG_HDR cfghdr0={CFG_LEVEL,"Keys",1,0};

  __root const CFG_HDR cfghdr0_1={CFG_KEYCODE,"Activate key",0,100};
  __root const unsigned int BCFG_CALL_BTN=RIGHT_SOFT;
  
  __root const CFG_HDR cfghdr0_2={CFG_CBOX,"Activate press type",0,2};
  __root const unsigned int BCFG_CALL_TYPE = 0;
  __root const CFG_CBOX_ITEM cfgcbox1[2]={"Short","Long"};

  __root const CFG_HDR cfghdr0_3={CFG_KEYCODE,"Close key",0,100};
  __root const unsigned int BCFG_CLOSE_BTN=RIGHT_SOFT;

__root const CFG_HDR cfghdr1={CFG_LEVEL,"",0,0};

// Настройка отображения

__root const CFG_HDR cfghdr2={CFG_LEVEL,"View",1,0};

  __root const CFG_HDR cfghdr2_1={CFG_CBOX,"Show on",0,3};
  __root const unsigned int BCFG_KBD_STATE = 1;
  __root const CFG_CBOX_ITEM cfgcbox2[3]={"Lock keyboard","Unlock keyboard", "Both"};
  
  __root const CFG_HDR cfghdr2_2={CFG_CBOX,"Cycled navigation",0,3};
  __root const unsigned int BCFG_CYCLED = 1;
  __root const CFG_CBOX_ITEM cfgcbox3[3]={"None","In current line", "Go to next line"};

__root const CFG_HDR cfghdr3={CFG_LEVEL,"",0,0};

// Настройка выбора

__root const CFG_HDR cfghdr4={CFG_LEVEL,"Select",1,0};

  __root const CFG_HDR cfghdr4_1={CFG_CBOX,"Select type",0,2};
  __root const int BCFG_SELECT_TYPE=1;
  __root const CFG_CBOX_ITEM cfgcbox4[2]={"Color","Picture"};

  __root const CFG_HDR cfghdr4_2={CFG_STR_UTF8,"Select picture",0,127};
  __root const char chpic[128]=DEFAULT_DISK ":\\ZBin\\IdleLinks\\choose.png";

  __root const CFG_HDR cfghdr14_3={8,"Cursor background color",0,0};
  __root const char cl[4]={185,113,13,50};

  __root const CFG_HDR cfghdr4_4={8,"Cursor color",0,0};
  __root const char frcol[4]={255,255,255,100};
  
  __root const CFG_HDR cfghdr4_5={CFG_UINT,"Cursor round on X",0,0xFFFFFFFF};
  __root const unsigned int BCFG_ROUND_X = 0;
  
  __root const CFG_HDR cfghdr4_6={CFG_UINT,"Cursor round on Y",0,0xFFFFFFFF};
  __root const unsigned int BCFG_ROUND_Y = 0;
  
__root const CFG_HDR cfghdr5={CFG_LEVEL,"",0,0};

//




