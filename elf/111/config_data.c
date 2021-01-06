#include "..\inc\cfg_items.h"
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
  __root const char NATICQ_HOST[128]="cbsie.dyndns.info; ig.kibab.com; ig.boba.su; himoza.org; ig3.boba.su";

  __root const CFG_HDR cfghdr2_2={CFG_UINT,"Default port",0,65535};
  __root const unsigned int NATICQ_PORT=5050;

  __root const CFG_HDR cfghdr2_3={CFG_UINT,"Reconnect timeout",0,65535};
  __root const unsigned int RECONNECT_TIME=10;
  
  __root const CFG_HDR cfghdr2_4={CFG_STR_UTF8,"History path",0,63};
  __root const char HIST_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\history\\";

  __root const CFG_HDR cfghdr2_5={CFG_STR_UTF8,"Smiles File",0,63};
  __root const char SMILE_FILE[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\smiles.cfg";

  __root const CFG_HDR cfghdr2_6={CFG_STR_UTF8,"Smiles .png path",0,63};
  __root const char SMILE_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\smiles\\";

  __root const CFG_HDR cfghdr2_7={CFG_STR_UTF8,"Images .png path",0,63};
  __root const char ICON_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\img\\";

  __root const CFG_HDR cfghdr2_8={CFG_STR_UTF8,"XStatus .png path",0,63};
  __root const char XSTATUSES_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\ximg\\";

  __root const CFG_HDR cfghdr2_9={CFG_STR_UTF8,"Templates path",0,63};
  __root const char TEMPLATES_PATH[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\templates\\";
  
#ifdef NEWSGOLD  
  __root const CFG_HDR cfghdr2_9_1={CFG_UINT,"First status icon",0,10000};
  __root const unsigned int ST_FIRST=8000;
  
  __root const CFG_HDR cfghdr2_9_2={CFG_UINT,"First xstatus icon",0,10000};
  __root const unsigned int X_FIRST=8100;
#endif
  
__root const CFG_HDR cfghdr3={CFG_LEVEL,"",0,0};

//View settings
__root const CFG_HDR cfghdr4={CFG_LEVEL,"Interface",1,0};
//Status icon on mainscreen position

#ifdef NEWSGOLD
  __root const CFG_HDR cfghdr4_0={CFG_CBOX,"Show icon on",0,4};
  __root const unsigned int ICON_ON = 1;
  __root const CFG_CBOX_ITEM cfgcbox4_0_1[4]={"None","IDLE","Iconbar","Everywhere"};
  
  __root const CFG_HDR cfghdr4_0_2={CFG_CHECKBOX,"XStatus in iconbar",0,1};
  __root const unsigned int XST_IC = 0;
#endif

  __root const CFG_HDR cfghdr4_1={CFG_COORDINATES,"Idle icon position",0,0};
  __root const unsigned int IDLEICON_X=0;
  __root const unsigned int IDLEICON_Y=50;
  
//Popup chat
  __root const CFG_HDR cfghdr4_2={CFG_CBOX,"Popup",0,3};
  __root const int DEVELOP_IF = 0;
  __root const CFG_CBOX_ITEM cfgcbox4_2[3]={"Allways", "If Kbd Unlock","Never"};

//Strong away
  __root const CFG_HDR cfghdr4_3={CFG_CBOX,"Notify when occupied",0,2};
  __root const int STRONG_AWAY = 0;
  __root const CFG_CBOX_ITEM cfgcbox4_3[2]={"Notify", "Don't notify"};
  
//Sorting
  __root const CFG_HDR cfghdr4_4={CFG_CBOX,"Sort CList",0,2};
  __root const int SORT_CLIST = 0;
  __root const CFG_CBOX_ITEM cfgcbox4_4[2]={"By Name","By Status"};

//First letter when typing
  __root const CFG_HDR cfghdr4_5={CFG_CBOX,"First letter",0,2};
  __root const int FIRST_LETTER = 0;
  __root const CFG_CBOX_ITEM cfgcbox4_5[2]={"Small","Big"};
  
  // tridog, 01.05.2009
  // Опциональное отобрадение контакта loopbak
  __root const CFG_HDR cfghdr4_6={CFG_CHECKBOX,"Show loopback",0,2};
  __root const int b_loopback=1;
  //

  //Fonts and colors
  __root const CFG_HDR cfghdr4_7={CFG_LEVEL,"Font and colors",1,0};
    __root const CFG_HDR cfghdr4_7_1={CFG_UINT,"My string color",0,1000};
    __root const unsigned int I_COLOR=3;
  
    __root const CFG_HDR cfghdr4_7_2={CFG_UINT,"Your string color",0,1000};
    __root const unsigned int TO_COLOR=2;
  
    __root const CFG_HDR cfghdr4_7_3={CFG_UINT,"XStatus color",0,1000};
    __root const unsigned int X_COLOR=2;
  
    __root const CFG_HDR cfghdr4_7_4={CFG_UINT,"Main font size",0,6};
    __root const unsigned int ED_FONT_SIZE=1;
  
    __root const CFG_HDR cfghdr4_7_5={CFG_UINT,"Header font size",0,6};
    __root const unsigned int ED_H_FONT_SIZE=2;
  
    __root const CFG_HDR cfghdr4_7_6={CFG_UINT,"XStatus font size",0,6};
    __root const unsigned int ED_X_FONT_SIZE=1;
  
    __root const CFG_HDR cfghdr4_7_7={CFG_UINT,"My old string color",0,1000};
    __root const unsigned int O_I_COLOR=15;
  
    __root const CFG_HDR cfghdr4_7_8={CFG_UINT,"Your old string color",0,1000};
    __root const unsigned int O_TO_COLOR=14;
    
    __root const CFG_HDR cfghdr4_7_9={CFG_UINT,"XStatus old color",0,1000};
    __root const unsigned int O_X_COLOR=14;
  
    __root const CFG_HDR cfghdr4_7_10={CFG_UINT,"Main old font size",0,6};
    __root const unsigned int O_ED_FONT_SIZE=1;
  
    __root const CFG_HDR cfghdr4_7_11={CFG_UINT,"Header old font size",0,6};
    __root const unsigned int O_ED_H_FONT_SIZE=2;
  
    __root const CFG_HDR cfghdr4_7_12={CFG_UINT,"XStatus old font size",0,6};
    __root const unsigned int O_ED_X_FONT_SIZE=1;
  
    __root const CFG_HDR cfghdr4_7_13={CFG_UINT,"Acked color",0,1000};
    __root const unsigned int ACK_COLOR=4;
  
    __root const CFG_HDR cfghdr4_7_14={CFG_UINT,"Unacked color",0,1000};
    __root const unsigned int UNACK_COLOR=20;
  
  __root const CFG_HDR cfghdr4_8={CFG_LEVEL,"",0,0};  

  //Illumination by BoBa 19.04.2007
  __root const CFG_HDR cfghdr4_9={CFG_LEVEL,"Illumination setup",1,0};
    __root const CFG_HDR cfghdr4_9_1={CFG_INT,"Display on Recv",0,100};
    __root const unsigned int ILL_DISP_RECV=10;
  
    __root const CFG_HDR cfghdr4_9_2={CFG_INT,"Keys on Recv",0,100};
    __root const unsigned int ILL_KEYS_RECV=10;
  
    __root const CFG_HDR cfghdr4_9_3={CFG_INT,"Timeout on Recv",0,60};
    __root const unsigned int ILL_RECV_TMR=10;
  
    __root const CFG_HDR cfghdr4_9_4={CFG_INT,"Fade on Recv",0,1000};
    __root const unsigned int ILL_RECV_FADE=256;
  
    __root const CFG_HDR cfghdr4_9_5={CFG_INT,"Display on Send",0,100};
    __root const unsigned int ILL_DISP_SEND=10;
  
    __root const CFG_HDR cfghdr4_9_6={CFG_INT,"Keys on Send",0,100};
    __root const unsigned int ILL_KEYS_SEND=0;
  
    __root const CFG_HDR cfghdr4_9_7={CFG_INT,"Timeout on Send",0,60};
    __root const unsigned int ILL_SEND_TMR=5;
  
    __root const CFG_HDR cfghdr4_9_8={CFG_INT,"Fade on Send",0,1000};
    __root const unsigned int ILL_SEND_FADE=256;
  
    __root const CFG_HDR cfghdr4_9_9={CFG_INT,"Fade on Off",0,1000};
    __root const unsigned int ILL_OFF_FADE=256;
  __root const CFG_HDR cfghdr4_10={CFG_LEVEL,"",0,0};  
  
  // tridog, 18 april 2009
  // Делаем многопрофильность
  __root const CFG_HDR cfghdr4_11={CFG_LEVEL,"Name in X-Task",1,0};
    
    // Выводить ли иконку непрочитанных сообщений
    __root const CFG_HDR cfghdr4_11_1={CFG_CHECKBOX,"Icon on unread message",0,2};
    __root const int b__task_unread_icon=1;
    
    // Выводить ли количество непрочитанных сообщений
    __root const CFG_HDR cfghdr4_11_2={CFG_CHECKBOX,"Count unreaded messages",0,2};
    __root const int b__task_unread_count=0;
    
    // UIN/Profile name
    __root const CFG_HDR cfghdr4_11_3={CFG_CBOX,"Show in X-Task",0,2};
    __root const int task_show = 0;
    __root const CFG_CBOX_ITEM cfgcbox4_11_3[2]={"UIN", "Profile"};
              
  __root const CFG_HDR cfghdr4_12={CFG_LEVEL,"",0,0}; 
  //
 
__root const CFG_HDR cfghdr5={CFG_LEVEL,"",0,0};

//History
__root const CFG_HDR cfghdr6={CFG_LEVEL,"History",1,0};
//Enable history logging
  __root const CFG_HDR cfghdr6_1={CFG_CBOX,"Enable logs",0,2};
  __root const int LOG_ALL = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_1[2]={"No","Yes"};

//History type
  __root const CFG_HDR cfghdr6_2={CFG_CBOX,"History for",0,2};
  __root const int HISTORY_TYPE = 0;
  __root const CFG_CBOX_ITEM cfgcbox6_2[2]={"All","Everyone"};

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
  __root const int ENA_AUTO_XTXT = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_5[2]={"No","Yes"};

//Don't log X-status, if it same as prevision
  __root const CFG_HDR cfghdr6_6={CFG_CBOX,"Not log same XText",0,2};
  __root const int NOT_LOG_SAME_XTXT = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_6[2]={"No","Yes"};

//Buffer for fill from history
  __root const CFG_HDR cfghdr6_7={CFG_CBOX,"History read buffer",0,6};
  __root const int HISTORY_BUFFER = 3;
  __root const CFG_CBOX_ITEM cfgcbox6_7[6]={"Disabled","128 bytes","256 bytes","512 bytes","1 kbyte","2 kbyte"};
  
__root const CFG_HDR cfghdr7={CFG_LEVEL,"",0,0};


//Notify
__root const CFG_HDR cfghdr8={CFG_LEVEL,"Notify power",1,0};

  __root const CFG_HDR cfghdr8_1={CFG_UINT,"Sound Volume",0,6};
  __root const unsigned int sndVolume=3;

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
  __root const CFG_HDR cfghdr8_6={CFG_LEVEL,"",0,0};
  

__root const CFG_HDR cfghdr9={CFG_LEVEL,"",0,0};



