#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
 #define DEFAULT_DISK "4"
#else
 #define DEFAULT_DISK "0"
#endif

//Конфигурация

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"Setup Cash",1,0};
 __root const CFG_HDR cfghdr0={CFG_STR_WIN1251,"Number for Cash Request",0,31};
 __root const char CASHREQNUM[32]="*#";

 __root const CFG_HDR cfghdr000={CFG_UINT,"Auto cash check, hours",0,24};
 __root const unsigned int CHECK_HOURS=1;

 __root const CFG_HDR cfghdr01={CFG_CHECKBOX,"Enable Cash Trace",0,0};
 __root const int ENA_CASHTRACE = 1;
 
 __root const CFG_HDR cfghdr022={CFG_CHECKBOX,"Enable Op USSD Trace",0,0};
 __root const int ENA_AUTOCASHTRACE = 0; 

 __root const CFG_HDR cfghdr08={CFG_CHECKBOX,"Enable Cash Trace logging",0,0};
 __root const int ENA_CASHTRACELOG = 1;
 
 __root const CFG_HDR cfghdr02={CFG_STR_WIN1251,"Cash pattern 0",0,31};
 __root const char CashPat0[32]="alans #hrn";

 __root const CFG_HDR cfghdr03={CFG_STR_WIN1251,"Cash pattern 1",0,31};
 __root const char CashPat1[32]="onus #hrn";

 __root const CFG_HDR cfghdr04={CFG_STR_WIN1251,"Cash pattern 2",0,31};
 __root const char CashPat2[32]="# hv";

 __root const CFG_HDR cfghdr05={CFG_STR_WIN1251,"Cash pattern 3",0,31};
 __root const char CashPat3[32]="# Kb GPRS";

 __root const CFG_HDR cfghdr06 = {CFG_STR_UTF8,"Temp file path",0,127};
 __root const char cashTEMP_PATH[128]=DEFAULT_DISK ":\\ZBin\\var\\";

 __root const CFG_HDR cfghdr07 = {CFG_STR_UTF8,"Log file",0,127};
 __root const char cashLOG_FILE[128]=DEFAULT_DISK ":\\ZBin\\var\\CallCenter_cash.log";

 __root const CFG_HDR cfghdr072 = {CFG_STR_UTF8,"Log format",0,127};
 __root const char cashLOG_Format[128]="%02d.%02d.%04d %02d:%02d %.0s %d %d %d %d";

__root const CFG_HDR cfghdr073 = {CFG_CBOX, "Show In", 0, 3};
__root const int cfgShowIn = 1;
__root const CFG_CBOX_ITEM cfgcbox1[3] = {"Lock", "Unlock", "Both"};

 __root const CFG_HDR cfghdr19={CFG_COORDINATES,"Idle icon position",0,0};
 __root const unsigned int IDLE_X=0;
 __root const unsigned int IDLE_Y=95;

 __root const CFG_HDR cfghdr_m12={CFG_LEVEL,"Setup Progressbar",1,0};
  __root const CFG_HDR cfghdr10={CFG_COLOR,"Cash Progressbar 1",0,0};
  __root const char COLOR_CASHPB1[4]={0xFF,0x00,0x00,0x32};

  __root const CFG_HDR cfghdr11={CFG_COLOR,"Cash Progressbar 2",0,0};
  __root const char COLOR_CASHPB2[4]={0x00,0xFF,0x00,0x32};

  __root const CFG_HDR cfghdr12={CFG_COLOR,"Cash Progressbar 3",0,0};
  __root const char COLOR_CASHPB3[4]={0x00,0xFF,0xFF,0x32};

  __root const CFG_HDR cfghdr13={CFG_COLOR,"Cash Progressbar 4",0,0};
  __root const char COLOR_CASHPB4[4]={0xFF,0xFF,0x00,0x32};
  
  __root const CFG_HDR cfghdr14={CFG_COLOR,"Font Color",0,0};
  __root const char COLOR_TEXTPB[4]={0xFF,0xFF,0xFF,0x64};
  
  __root const CFG_HDR cfghdr15={CFG_UINT,"Font Size",0,100};
  __root const unsigned int TEXT_FONTSZ=FONT_NUMERIC_XSMALL;
  
 __root const CFG_HDR cfghdr_m13={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"Setup Vibra at Call",1,0};
 __root const CFG_HDR cfghdr7={CFG_CHECKBOX,"Use vibra",0,0};
 __root const int ENA_VIBRA = 1;

 __root const CFG_HDR cfghdr8={CFG_UINT,"Vibra power",0,100};
 __root const unsigned int vibraPower=50;

 __root const CFG_HDR cfghdr9={CFG_UINT,"Vibra duration (ms)",0,100};
 __root const unsigned int vibraDuration=200;
__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"",0,0};
 
__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"Setup MegaDial",1,0};
  __root const CFG_HDR cfghdr00={CFG_COLOR,"Color Menu background",0,0};
  __root const char COLOR_MENU_BK[4]={0xFF,0xFF,0x0,0x64};

  __root const CFG_HDR cfghdr1={CFG_COLOR,"Color Menu border",0,0};
  __root const char COLOR_MENU_BRD[4]={0x0,0x0,0x0,0x64};

  __root const CFG_HDR cfghdr2={CFG_COLOR,"Color Not selected",0,0};
  __root const char COLOR_NOTSELECTED[4]={0x0,0x0,0x0,0x64};

  __root const CFG_HDR cfghdr3={CFG_COLOR,"Color Selected",0,0};
  __root const char COLOR_SELECTED[4]={0xFF,0xFF,0xFF,0x64};

  __root const CFG_HDR cfghdr4={CFG_COLOR,"Color Selected background",0,0};
  __root const char COLOR_SELECTED_BG[4]={0x0,0x0,0xFF,0x64};

  __root const CFG_HDR cfghdr5={CFG_COLOR,"Color Selected border",0,0};
  __root const char COLOR_SELECTED_BRD[4]={0xFF,0xFF,0xFF,0x64};

  __root const CFG_HDR cfghdr6={CFG_COLOR,"Color Search mark",0,0};
  __root const char COLOR_SEARCH_MARK[4]={0xFF,0x0,0x0,0x64};
  
  __root const CFG_HDR cfghdr66={CFG_COLOR,"Color ScrollBar",0,0};
  __root const char COLOR_SCROLLBAR[4]={0x0,0x0,0x0,0x64};  
__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};
