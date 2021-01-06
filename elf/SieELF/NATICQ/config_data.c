#include "..\inc\cfg_items.h"
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

__root const CFG_HDR cfghdr19={CFG_COORDINATES,"Idle icon position",0,0};
__root const unsigned int IDLEICON_X=0;
__root const unsigned int IDLEICON_Y=50;

__root const CFG_HDR cfghdr2_1={CFG_CBOX,"Enable logs",0,2};
__root const int LOG_ALL = 1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"No","Yes"};

__root const CFG_HDR cfghdr2_0={CFG_CBOX,"Log status changes",0,2};
__root const int LOG_STATCH = 0;
__root const CFG_CBOX_ITEM cfgcbox1_1[2]={"No","Yes"};

__root const CFG_HDR cfghdr15_0={CFG_CBOX,"Popup",0,3};
__root const int DEVELOP_IF = 0;
__root const CFG_CBOX_ITEM cfgcbox15_1[3]={"Allways", "If Kbd Unlock","Never"};

__root const CFG_HDR cfghdr16_0={CFG_CBOX,"Sort CList",0,2};
__root const int SORT_CLIST = 0;
__root const CFG_CBOX_ITEM cfgcbox8_1[2]={"By Name","By Status"};

__root const CFG_HDR cfghdr16_1={CFG_CBOX,"First letter",0,2};
__root const int FIRST_LETTER = 0;
__root const CFG_CBOX_ITEM cfgcbox16_1[2]={"Small","Big"};

__root const CFG_HDR cfghdr61={CFG_CHECKBOX,"Enable Auto Request XText",0,0};
__root const int ENA_AUTO_XTXT = 1;

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Notify power",1,0};
__root const CFG_HDR cfghdr18={CFG_UINT,"Sound Volume",0,6};
__root const unsigned int sndVolume=3;

__root const CFG_HDR cfghdr18_1={CFG_UINT,"Vibra power",0,100};
__root const unsigned int vibraPower=100;

__root const CFG_HDR cfghdr18_2={CFG_CBOX,"Vibration type",0,2};
__root const int VIBR_TYPE = 0;
__root const CFG_CBOX_ITEM cfgcbox18_2[2]={"Single","Double"};

__root const CFG_HDR cfghdr18_3={CFG_CBOX,"Vibra on connect",0,2};
__root const int VIBR_ON_CONNECT = 0;
__root const CFG_CBOX_ITEM cfgcbox18_3[2]={"No","Yes"};

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

//Illumination by BoBa 19.04.2007
__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"Illumination setup",1,0};
  __root const CFG_HDR cfghdr25={CFG_INT,"Display on Recv",0,100};
  __root const unsigned int ILL_DISP_RECV=10;

  __root const CFG_HDR cfghdr26={CFG_INT,"Keys on Recv",0,100};
  __root const unsigned int ILL_KEYS_RECV=10;

  __root const CFG_HDR cfghdr27={CFG_INT,"Timeout on Recv",0,60};
  __root const unsigned int ILL_RECV_TMR=10;

  __root const CFG_HDR cfghdr28={CFG_INT,"Fade on Recv",0,1000};
  __root const unsigned int ILL_RECV_FADE=256;

  __root const CFG_HDR cfghdr29={CFG_INT,"Display on Send",0,100};
  __root const unsigned int ILL_DISP_SEND=10;

  __root const CFG_HDR cfghdr30={CFG_INT,"Keys on Send",0,100};
  __root const unsigned int ILL_KEYS_SEND=0;

  __root const CFG_HDR cfghdr31={CFG_INT,"Timeout on Send",0,60};
  __root const unsigned int ILL_SEND_TMR=5;

  __root const CFG_HDR cfghdr32={CFG_INT,"Fade on Send",0,1000};
  __root const unsigned int ILL_SEND_FADE=256;

  __root const CFG_HDR cfghdr33={CFG_INT,"Fade on Off",0,1000};
  __root const unsigned int ILL_OFF_FADE=256;
__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};

//Fonts
__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"Font setup",1,0};
  __root const CFG_HDR cfghdr21={CFG_UINT,"My string color",0,1000};
  __root const unsigned int I_COLOR=3;

  __root const CFG_HDR cfghdr22={CFG_UINT,"Your string color",0,1000};
  __root const unsigned int TO_COLOR=2;

  __root const CFG_HDR cfghdr24={CFG_UINT,"FontSize",0,6};
  __root const unsigned int ED_FONT_SIZE=1;
__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Hosts and paths",1,0};
  __root const CFG_HDR cfghdr1_1={CFG_STR_WIN1251,"Host",0,127};
  __root const char NATICQ_HOST[128]="cbsie.dyndns.info";

  __root const CFG_HDR cfghdr1_2={CFG_UINT,"Port",0,65535};
  __root const unsigned int NATICQ_PORT=5050;

  __root const CFG_HDR cfghdr2={CFG_STR_UTF8,"History path",0,63};
  __root const char HIST_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\history";

  __root const CFG_HDR cfghdr23={CFG_STR_UTF8,"Smiles File",0,63};
  __root const char SMILE_FILE[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\smiles.cfg";

  __root const CFG_HDR cfghdr233={CFG_STR_UTF8,"Smiles .png path",0,63};
  __root const char SMILE_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\smiles";

  __root const CFG_HDR cfghdr234={CFG_STR_UTF8,"Images .png path",0,63};
  __root const char ICON_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\img";

  __root const CFG_HDR cfghdr235={CFG_STR_UTF8,"XStatus .png path",0,63};
  __root const char XSTATUSES_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\ximg";

  __root const CFG_HDR cfghdr236={CFG_STR_UTF8,"Templates path",0,63};
  __root const char TEMPLATES_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\templates";
__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Sounds setup",1,0};
  __root const CFG_HDR cfghdr13={CFG_STR_UTF8,"snd Startup",0,63};
  __root const char sndStartup[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndStartup.wav";

  __root const CFG_HDR cfghdr14={CFG_STR_UTF8,"snd SrvMsg",0,63};
  __root const char sndSrvMsg[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndSrvMsg.wav";

  __root const CFG_HDR cfghdr15={CFG_STR_UTF8,"snd Global",0,63};
  __root const char sndGlobal[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndGlobal.wav";

  __root const CFG_HDR cfghdr16={CFG_STR_UTF8,"snd Msg",0,63};
  __root const char sndMsg[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndMsg.wav";

  __root const CFG_HDR cfghdr17={CFG_STR_UTF8,"snd MsgSent",0,63};
  __root const char sndMsgSent[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndMsgSent.wav";
__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};
