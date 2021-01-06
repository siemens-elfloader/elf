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

//Network settings
__root const CFG_HDR cfghdr2={CFG_LEVEL,"Hosts and paths",1,0};
  __root const CFG_HDR cfghdr2_1={CFG_STR_WIN1251,"Host",0,127};
  __root const char NATICQ_HOST[128]="freegw.alltime.ru; cbsie.dyndns.info";

  __root const CFG_HDR cfghdr2_2={CFG_UINT,"Default port",0,65535};
  __root const unsigned int NATICQ_PORT=5050;

  __root const CFG_HDR cfghdr2_3={CFG_STR_UTF8,"History path",0,63};
  __root const char HIST_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\history";

  __root const CFG_HDR cfghdr2_4={CFG_STR_UTF8,"Smiles File",0,63};
  __root const char SMILE_FILE[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\smiles.cfg";

  __root const CFG_HDR cfghdr2_5={CFG_STR_UTF8,"Smiles .png path",0,63};
  __root const char SMILE_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\smiles";

  __root const CFG_HDR cfghdr2_6={CFG_STR_UTF8,"Images .png path",0,63};
  __root const char ICON_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\img";

  __root const CFG_HDR cfghdr2_7={CFG_STR_UTF8,"XStatus .png path",0,63};
  __root const char XSTATUSES_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\ximg";

  __root const CFG_HDR cfghdr2_8={CFG_STR_UTF8,"Templates path",0,63};
  __root const char TEMPLATES_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\templates";
__root const CFG_HDR cfghdr3={CFG_LEVEL,"",0,0};

//View settings
__root const CFG_HDR cfghdr4={CFG_LEVEL,"Interface",1,0};
//Status icon on mainscreen position
  __root const CFG_HDR cfghdr4_1={CFG_COORDINATES,"Idle icon position",0,0};
  __root const unsigned int IDLEICON_X=110;
  __root const unsigned int IDLEICON_Y=52;
  
//Popup chat
  __root const CFG_HDR cfghdr4_2={CFG_CBOX,"Popup",0,3};
  __root const int DEVELOP_IF = 2;
  __root const CFG_CBOX_ITEM cfgcbox4_2[3]={"Allways", "If Kbd Unlock","Never"};
  
//Sorting
  __root const CFG_HDR cfghdr4_3={CFG_CBOX,"Sort CList",0,2};
  __root const int SORT_CLIST = 0;
  __root const CFG_CBOX_ITEM cfgcbox4_3[2]={"By Name","By Status"};

//First letter when typing
  __root const CFG_HDR cfghdr4_4={CFG_CBOX,"First letter",0,2};
  __root const int FIRST_LETTER = 0;
  __root const CFG_CBOX_ITEM cfgcbox4_4[2]={"Small","Big"};

  //Fonts and colors
  __root const CFG_HDR cfghdr4_5={CFG_LEVEL,"Font and colors",1,0};
    __root const CFG_HDR cfghdr4_5_1={CFG_UINT,"My string color",0,1000};
    __root const unsigned int I_COLOR=4;
  
    __root const CFG_HDR cfghdr4_5_2={CFG_UINT,"Your string color",0,1000};
    __root const unsigned int TO_COLOR=2;
  
    __root const CFG_HDR cfghdr4_5_3={CFG_UINT,"XStatus color",0,1000};
    __root const unsigned int X_COLOR=2;
  
    __root const CFG_HDR cfghdr4_5_4={CFG_UINT,"Main font size",0,6};
    __root const unsigned int ED_FONT_SIZE=1;
  
    __root const CFG_HDR cfghdr4_5_5={CFG_UINT,"Header font size",0,6};
    __root const unsigned int ED_H_FONT_SIZE=2;
  
    __root const CFG_HDR cfghdr4_5_6={CFG_UINT,"XStatus font size",0,6};
    __root const unsigned int ED_X_FONT_SIZE=1;
  
    __root const CFG_HDR cfghdr4_5_7={CFG_UINT,"My old string color",0,1000};
    __root const unsigned int O_I_COLOR=15;
  
    __root const CFG_HDR cfghdr4_5_8={CFG_UINT,"Your old string color",0,1000};
    __root const unsigned int O_TO_COLOR=14;
    
    __root const CFG_HDR cfghdr4_5_9={CFG_UINT,"XStatus old color",0,1000};
    __root const unsigned int O_X_COLOR=14;
  
    __root const CFG_HDR cfghdr4_5_10={CFG_UINT,"Main old font size",0,6};
    __root const unsigned int O_ED_FONT_SIZE=1;
  
    __root const CFG_HDR cfghdr4_5_11={CFG_UINT,"Header old font size",0,6};
    __root const unsigned int O_ED_H_FONT_SIZE=2;
  
    __root const CFG_HDR cfghdr4_5_12={CFG_UINT,"XStatus old font size",0,6};
    __root const unsigned int O_ED_X_FONT_SIZE=1;
  
    __root const CFG_HDR cfghdr4_5_13={CFG_UINT,"Acked color",0,1000};
    __root const unsigned int ACK_COLOR=3;
  
    __root const CFG_HDR cfghdr4_5_14={CFG_UINT,"Unacked color",0,1000};
    __root const unsigned int UNACK_COLOR=20;
  
  __root const CFG_HDR cfghdr4_6={CFG_LEVEL,"",0,0};  

  //Illumination by BoBa 19.04.2007
  __root const CFG_HDR cfghdr4_7={CFG_LEVEL,"Illumination setup",1,0};
    __root const CFG_HDR cfghdr4_7_1={CFG_INT,"Display on Recv",0,100};
    __root const unsigned int ILL_DISP_RECV=10;
  
    __root const CFG_HDR cfghdr4_7_2={CFG_INT,"Keys on Recv",0,100};
    __root const unsigned int ILL_KEYS_RECV=10;
  
    __root const CFG_HDR cfghdr4_7_3={CFG_INT,"Timeout on Recv",0,60};
    __root const unsigned int ILL_RECV_TMR=10;
  
    __root const CFG_HDR cfghdr4_7_4={CFG_INT,"Fade on Recv",0,1000};
    __root const unsigned int ILL_RECV_FADE=256;
  
    __root const CFG_HDR cfghdr4_7_5={CFG_INT,"Display on Send",0,100};
    __root const unsigned int ILL_DISP_SEND=10;
  
    __root const CFG_HDR cfghdr4_7_6={CFG_INT,"Keys on Send",0,100};
    __root const unsigned int ILL_KEYS_SEND=0;
  
    __root const CFG_HDR cfghdr4_7_7={CFG_INT,"Timeout on Send",0,60};
    __root const unsigned int ILL_SEND_TMR=5;
  
    __root const CFG_HDR cfghdr4_7_8={CFG_INT,"Fade on Send",0,1000};
    __root const unsigned int ILL_SEND_FADE=256;
  
    __root const CFG_HDR cfghdr4_7_9={CFG_INT,"Fade on Off",0,1000};
    __root const unsigned int ILL_OFF_FADE=256;
  __root const CFG_HDR cfghdr4_8={CFG_LEVEL,"",0,0};  
 
__root const CFG_HDR cfghdr5={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m71={CFG_LEVEL,"Online Time",1,0};

__root const CFG_HDR cfghdr1qe = {CFG_CBOX,"Show Online time",0,2};
__root const int Is_Online_On = 1;
__root const CFG_CBOX_ITEM cfgcbox87[2]={"No","Yes"};

__root const CFG_HDR cfghdr699 = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int ONTIME_X = 140;
__root const unsigned int ONTIME_Y = 68;  

__root const CFG_HDR cfghdr698 = {CFG_CBOX,"Pause time on disconect",0,2};
__root const int Pause_Time = 1;
__root const CFG_CBOX_ITEM cfgcbox85[2]={"No","Yes"};

__root const CFG_HDR cfghdr_m70={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"Main messages",1,0};

__root const CFG_HDR cfghdr1qt = {CFG_CBOX,"Show Online time",0,2};
__root const int Is_DRAWMAIN_On = 1;
__root const CFG_CBOX_ITEM cfgcbox89[2]={"No","Yes"};

__root const CFG_HDR cfghdr69u = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int MSG_X = 6;
__root const unsigned int MSG_Y = 85;  

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"Auto Ping/Unread",1,0};

__root const CFG_HDR cfghdr2qe = {CFG_CBOX,"Show Ping",0,2};
__root const int Show_Ping = 1;
__root const CFG_CBOX_ITEM cfgcbox88[2]={"No","Yes"};

__root const CFG_HDR cfghd66 = {CFG_COORDINATES,"Auto Ping Cordinates",0,0};
__root const unsigned int PING_X = 140;
__root const unsigned int PING_Y = 58;

__root const CFG_HDR cfghdr298 = {CFG_CBOX,"Show Unread",0,2};
__root const int Is_Unread_On = 1;
__root const CFG_CBOX_ITEM cfgcbox86[2]={"No","Yes"};

__root const CFG_HDR cfghd67 = {CFG_COORDINATES,"Unread Cordinates",0,0};
__root const unsigned int UNREAD_X = 0;
__root const unsigned int UNREAD_Y = 276;

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"Auto Status",1,0};

__root const CFG_HDR cfghdr668 = {CFG_CBOX,"On/Off",0,2};
__root const int Auto_Status = 1;
__root const CFG_CBOX_ITEM cfgcbox8a[2]={"No","Yes"};

__root const CFG_HDR cfghdr667={CFG_UINT,"Timeout (1min=6)",72,500};
__root const unsigned int AUTO_ENGADE=108;

__root const CFG_HDR cfghdr_13={CFG_CBOX,"GMT zone",0,33};
__root const int time_zone = 15;
__root const CFG_CBOX_ITEM cfgcbox_13[33]={"-12:00", "-11:00", "-10:00", "-09:00", "-08:00", "-07:00", "-06:00", "-05:00", "-04:00", "-03:30", "-03:00", "-02:00", "-01:00", "00:00", "+01:00", "+02:00", "+03:00", "+03:30", "+04:00", "+04:30", "+05:00", "+05:30", "+05:45", "+06:00", "+06:30", "+07:00", "+08:00", "+09:00", "+09:30", "+10:00", "+11:00", "+12:00", "+13:00"};

__root const CFG_HDR cfghdrzz_8={CFG_STR_WIN1251,"Hello MsG",0,23};
__root const char away_msg1[24]="Hello";

__root const CFG_HDR cfghdrzz_9={CFG_STR_WIN1251,"away message",0,63};
__root const char away_msg2[64]="im not here right now!";

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};

//History
__root const CFG_HDR cfghdr6={CFG_LEVEL,"History",1,0};
//Enable history logging
  __root const CFG_HDR cfghdr6_1={CFG_CBOX,"Enable logs",0,2};
  __root const int LOG_ALL = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_1[2]={"No","Yes"};
/*
//History type
  __root const CFG_HDR cfghdr6_2={CFG_CBOX,"History for",0,2};
  __root const int HISTORY_TYPE = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_2[2]={"All","Everyone"};
*/
//Enable status logging
  __root const CFG_HDR cfghdr6_3={CFG_CBOX,"Log status changes",0,2};
  __root const int LOG_STATCH = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_3[2]={"No","Yes"};

//Enable X-status logging
  __root const CFG_HDR cfghdr6_4={CFG_CBOX,"Log X-Text",0,2};
  __root const int LOG_XTXT = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_4[2]={"No","Yes"};
  
//Auto request X-status if entering to chat
  __root const CFG_HDR cfghdr6_5={CFG_CBOX,"Auto Request XText",0,2};
  __root const int ENA_AUTO_XTXT = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_5[2]={"No","Yes"};

//Don't log X-status, if it same as prevision
  __root const CFG_HDR cfghdr6_6={CFG_CBOX,"Not log same XText",0,2};
  __root const int NOT_LOG_SAME_XTXT = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_6[2]={"No","Yes"};

//Buffer for fill from history
  __root const CFG_HDR cfghdr6_7={CFG_CBOX,"History read buffer",0,6};
  __root const int HISTORY_BUFFER = 2;
  __root const CFG_CBOX_ITEM cfgcbox6_7[6]={"Disabled","128 bytes","256 bytes","512 bytes","1 kbyte","2 kbyte"};
  
__root const CFG_HDR cfghdr7={CFG_LEVEL,"",0,0};


//Notify
__root const CFG_HDR cfghdr8={CFG_LEVEL,"Notify power",1,0};

  __root const CFG_HDR cfghdr8_1={CFG_UINT,"Sound Volume",0,6};
  __root const unsigned int sndVolume=4;

  __root const CFG_HDR cfghdr8_2={CFG_UINT,"Vibra power",0,100};
  __root const unsigned int vibraPower=100;

  __root const CFG_HDR cfghdr8_3={CFG_CBOX,"Vibration type",0,2};
  __root const int VIBR_TYPE = 0;
  __root const CFG_CBOX_ITEM cfgcbox8_3[2]={"Single","Double"};

  __root const CFG_HDR cfghdr8_4={CFG_CBOX,"Vibra on connect",0,2};
  __root const int VIBR_ON_CONNECT = 0;
  __root const CFG_CBOX_ITEM cfgcbox8_4[2]={"No","Yes"};

  __root const CFG_HDR cfghdr8_5={CFG_LEVEL,"Sounds setup",1,0};
    
    __root const CFG_HDR cfghdr8_5_1={CFG_STR_UTF8,"snd Startup",0,63};
    __root const char sndStartup[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndStartup.wav";
  
    __root const CFG_HDR cfghdr8_5_2={CFG_STR_UTF8,"snd SrvMsg",0,63};
    __root const char sndSrvMsg[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndSrvMsg.wav";
  
    __root const CFG_HDR cfghdr8_5_3={CFG_STR_UTF8,"snd Global",0,63};
    __root const char sndGlobal[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndGlobal.wav";
  
    __root const CFG_HDR cfghdr8_5_4={CFG_STR_UTF8,"snd Msg",0,63};
    __root const char sndMsg[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndMsg.wav";
  
    __root const CFG_HDR cfghdr8_5_5={CFG_STR_UTF8,"snd MsgSent",0,63};
    __root const char sndMsgSent[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\sndMsgSent.wav";
    
    __root const CFG_HDR cfghdr161={CFG_STR_UTF8,"ext msg snd(uin.wav)",0,63};
    __root const char sndMsg2[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\uins_msg\\";
    
  __root const CFG_HDR cfghdr8_6={CFG_LEVEL,"",0,0};
  

__root const CFG_HDR cfghdr9={CFG_LEVEL,"",0,0};



