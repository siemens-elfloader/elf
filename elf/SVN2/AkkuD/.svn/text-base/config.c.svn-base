#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

//Координаты
__root const CFG_HDR cfghdr0={CFG_UTF8_STRING,"Log file path",0,127};
__root const  char LOGPATH[128]="0:\\zbin\\akkud_log.txt";

__root const CFG_HDR cfghdr2asda={CFG_UINT,"Estimating interval,hours",1,25};
__root const  int LOOKBACKHOURS=4;


__root const CFG_HDR cfghdr_logop={CFG_LEVEL,"Logging",1,0};

#define LOG_OPT(name,namestr,enabled) __root const CFG_HDR cfghdr_##name={CFG_CHECKBOX,namestr,0,2};\
__root const int logopt_##name=enabled;

LOG_OPT(cpuclock,"CPU clock",1)
LOG_OPT(net,"NET level",1)
LOG_OPT(cpuload,"CPU load",0)
LOG_OPT(iscalling,"IsCalling",0)
LOG_OPT(gprs,"GPRS state",0)
LOG_OPT(lte,"Living time estimated",1)

__root const CFG_HDR cfghdr3_end={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr0asdasasf={CFG_UTF8_STRING,"Icon file path",0,127};
__root const  char ICON[128]="0:\\zbin\\akkud_icon.png";

__root const CFG_HDR cfghdr0dsrrwre={CFG_UTF8_STRING,"Accum table(optional)",0,127};
__root const  char ATAB[128]="0:\\zbin\\akkud_tab.dat";

__root const CFG_HDR cfghdr1={CFG_CBOX,"Enable",0,2};
__root const int ENABLED=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr1_adad = {CFG_CBOX, "Data src", 0, 3};
__root const int AKKUSRC = 0;
__root const CFG_CBOX_ITEM cfgcboxkei9rsd[3] = {"GetAkkuCapacity()", "GetAkku(param1,param2)","*RamCap()"};

__root const CFG_HDR cfghdr2sdf={CFG_UINT,"GetAkku param1(I DONT KNOW IT!)",0,64000};
__root const  int GETAKKUPARAM1=0;

__root const CFG_HDR cfghdr2sdfs={CFG_UINT,"GetAkku param2(I DONT KNOW IT!)",0,64000};
__root const  int GETAKKUPARAM2=0;

__root const CFG_HDR cfghdr2={CFG_UINT,"Upd interval,sec",1,64000};
__root const  int INTERVAL=120;

__root const CFG_HDR cfghdr1asdads0 = {CFG_CBOX, "Show in", 0, 3};
__root const int cfgShowIn = 1;
__root const CFG_CBOX_ITEM cfgcboxasdasdad1[3] = { "Lock", "Unlock","Both"};

__root const CFG_HDR cfghdr0_4={CFG_COLOR,"Text Color",0,0};
__root const char TEXTCOLOR[4]={0xFF,0xFF,0x1B,100};

__root const CFG_HDR cfghdr0_5={CFG_COLOR,"Fringing Color",0,0};
__root const char FRINGCOLOR[4]={0,0,0,100};

__root const CFG_HDR cfghdr1_7={CFG_COORDINATES,"Position",0,0};
__root const unsigned int XCOORD=1;
__root const unsigned int YCOORD=136;

