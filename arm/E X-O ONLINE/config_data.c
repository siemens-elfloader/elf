#include "c:\arm\inc\cfg_items.h"
#include "language.h"
//Конфигурация

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_UINT,"UIN",0,0xFFFFFFFF};
__root const unsigned int UIN=0;

__root const CFG_HDR cfghdr1={CFG_STR_PASS,"Password",0,8};
__root const char PASS[9]="";

__root const CFG_HDR cfghdr1_1={CFG_UINT,"UIN противника",0,0xFFFFFFFF};
__root const unsigned int UIN_2=0;

//Network settings
__root const CFG_HDR cfghdr2={CFG_LEVEL,"Hosts and paths",1,0};
 // __root const CFG_HDR cfghdr2_1={CFG_STR_WIN1251,"Host",0,127};
 // __root const char NATICQ_HOST[128]="st-hunter.ru";

 // __root const CFG_HDR cfghdr2_2={CFG_UINT,"Default port",0,65535};
 // __root const unsigned int NATICQ_PORT=5050;
  
  __root const CFG_HDR cfghdr2_9={CFG_STR_UTF8,"Pictures path",0,127};
  __root const char PICTURES_PATH[128]=DEFAULT_DISK ":\\ZBin\\E-XO\\";

__root const CFG_HDR cfghdr3={CFG_LEVEL,"",0,0};

  
//Notify
__root const CFG_HDR cfghdr8={CFG_LEVEL,"Notify power",1,0};

  __root const CFG_HDR cfghdr8_0={CFG_CHECKBOX,"Вибрация",0,0};
  __root const int Is_Vibra_Enabled=1;

  __root const CFG_HDR cfghdr8_1={CFG_CHECKBOX,"При ходе соперника(онлайн)",0,0};
  __root const int ena_vibr=1;

  __root const CFG_HDR cfghdr8_2={CFG_UINT,"Vibra power",0,100};
  __root const unsigned int vibraPower=10;

  __root const CFG_HDR cfghdr8_3={CFG_CBOX,"Vibration type",0,2};
  __root const int VIBR_TYPE = 0;
  __root const CFG_CBOX_ITEM cfgcbox8_3[2]={"Single","Double"};

  __root const CFG_HDR cfghdr8_4={CFG_CBOX,"Vibra on connect",0,2};
  __root const int VIBR_ON_CONNECT = 1;
  __root const CFG_CBOX_ITEM cfgcbox8_4[2]={"No","Yes"};
  
__root const CFG_HDR cfghdr9={CFG_LEVEL,"",0,0};  


__root const CFG_HDR cfghdr4={CFG_LEVEL,LGP_INTERFACE,1,0};

  __root const CFG_HDR cfghdr4_1={CFG_UINT, LGP_FONT,0,23};
#ifdef ELKA
   __root const int FONT=9;
#else
#ifdef NEWSGOLD
  __root const int FONT=11;
#else
  __root const int FONT=7;  
#endif
#endif
  
__root const CFG_HDR cfghdr4_00={CFG_LEVEL,"",0,0};  
