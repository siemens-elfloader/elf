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
  __root const char NATICQ_HOST[128]="montana-cans.dyndns.org;freegw.alltime.ru;cbsie.dyndns.info";

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
  __root const CFG_HDR cfghdr4_1={CFG_COORDINATES,"Idle status icon",0,0};
  __root const unsigned int IDLEICON_X=110;
  __root const unsigned int IDLEICON_Y=52;
  
  __root const CFG_HDR cfghdrz68 = {CFG_CBOX,"xstastus idle",0,2};
  __root const int show_xstatus = 1;
  __root const CFG_CBOX_ITEM cfgcbox8z[2]={"No","Yes"};
  
  __root const CFG_HDR cfghdrz_1={CFG_COORDINATES,"Idle xstatus icon",0,0};
  __root const unsigned int IDLEICON_XX=110;
  __root const unsigned int IDLEICON_YX=82;
  
  __root const CFG_HDR cfghdr19_1={CFG_UINT,"smile background color",0,100};
  __root const unsigned int color_choose = 1;
/*
#ifdef ELKA
  __root const CFG_HDR cfghdr99={CFG_CBOX,"SLI Notify",0,2};
  __root const int SLI_TYPE = 1;
  __root const CFG_CBOX_ITEM cfgcbox18_4[2]={"Main","Everywhere"};
#endif
*/
  __root const CFG_HDR cfghdr65={CFG_UINT,"Vibra count in Vibra rem.",0,10};
  __root const unsigned int Vibra_cc=2;
  
  __root const CFG_HDR cfghdr66={CFG_STR_UTF8,"Player CSM",0,8};
  __root const char CsmAdr[9]="A068E244";  //el=A087B454 //es=A068E244
  
  __root const CFG_HDR cfghdr67={CFG_STR_WIN1251,"Now Playing txt",0,12};
  __root const char playing[13]="Now Playing:";

  __root const CFG_HDR cfghdr65z={CFG_UINT,"font (1=png/1xx=system)",0,115};
  __root const unsigned int fonto=109;

  __root const CFG_HDR cfghdr98={CFG_STR_UTF8,"Font path",0,63};
  __root const char fontpath[64]="2:\\font\\"; /*zbin\\img\\font\\*/

__root const CFG_HDR cfghd83 = {CFG_COORDINATES,"Main Msg Cordinates",0,0};
__root const unsigned int msg_d_x = 6;
__root const unsigned int msg_d_y = 85;

__root const CFG_HDR cfghdr65y={CFG_UINT,"ping/time/unread space",0,999999};
__root const unsigned int spaco1=10001;

__root const CFG_HDR cfghdr65u={CFG_UINT,"main msg space",0,999999};
__root const unsigned int spaco2=10001;

//Popup chat
  __root const CFG_HDR cfghdr4_2={CFG_CBOX,"Popup",0,4};
  __root const int DEVELOP_IF = 2;
  __root const CFG_CBOX_ITEM cfgcbox15_1[4]={"Allways", "If Kbd Unlock","Never", "After unlock"};
  
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
    __root const unsigned int I_COLOR=3;
  
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
    __root const unsigned int ACK_COLOR=4;
  
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

__root const CFG_HDR cfghdr699 = {CFG_COORDINATES,"Text position",0,0};
__root const unsigned int date_X2 = 140;
__root const unsigned int date_Y2 = 68;  

__root const CFG_HDR cfghdr698 = {CFG_CBOX,"Pause time on disconect",0,2};
__root const int Pause_Time = 1;
__root const CFG_CBOX_ITEM cfgcbox85[2]={"No","Yes"};

__root const CFG_HDR cfghdr_m70={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"Auto Ping/Unread",1,0};

__root const CFG_HDR cfghd66 = {CFG_COORDINATES,"Auto Ping Cordinates",0,0};
__root const unsigned int date_X = 140;
__root const unsigned int date_Y = 58;

__root const CFG_HDR cfghdr298 = {CFG_CBOX,"Show Unread",0,2};
__root const int Is_Unread_On = 1;
__root const CFG_CBOX_ITEM cfgcbox86[2]={"No","Yes"};

__root const CFG_HDR cfghd67 = {CFG_COORDINATES,"Unread Cordinates",0,0};
__root const unsigned int unread_X = 0;
__root const unsigned int unread_Y = 276;

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"Auto Status",1,0};

__root const CFG_HDR cfghdr668 = {CFG_CBOX,"On/Off",0,2};
__root const int Auto_Status = 1;
__root const CFG_CBOX_ITEM cfgcbox89[2]={"No","Yes"};

__root const CFG_HDR cfghdr667={CFG_UINT,"Timeout (1min=12)",120,500};
__root const unsigned int AUTO_ENGADE=240;

__root const CFG_HDR cfghdr_13={CFG_CBOX,"GMT zone",0,33};
__root const int time_zone = 15;
__root const CFG_CBOX_ITEM cfgcbox_13[33]={"-12:00", "-11:00", "-10:00", "-09:00", "-08:00", "-07:00", "-06:00", "-05:00", "-04:00", "-03:30", "-03:00", "-02:00", "-01:00", "00:00", "+01:00", "+02:00", "+03:00", "+03:30", "+04:00", "+04:30", "+05:00", "+05:30", "+05:45", "+06:00", "+06:30", "+07:00", "+08:00", "+09:00", "+09:30", "+10:00", "+11:00", "+12:00", "+13:00"};

__root const CFG_HDR cfghdrzz_8={CFG_STR_WIN1251,"Hello mSG",0,23};
__root const char away_msg4[24]="Hello";

__root const CFG_HDR cfghdrzz_9={CFG_STR_WIN1251,"away message",0,63};
__root const char away_msg2[64]="im not here right now!";

__root const CFG_HDR cfghdr66_2 = {CFG_CBOX,"Reset timer",0,2};
__root const int Reset_timer = 1;
__root const CFG_CBOX_ITEM cfgcbox90[2]={"On Msg send","On key press"};

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"Extra config",1,0};

__root const CFG_HDR cfghdr467 = {CFG_CBOX,"Show with contacts",0,3};
__root const int TIME_OR_MSG = 2;
__root const CFG_CBOX_ITEM cfgcbox91[3]={"Time","Msg","Contacts"};

__root const CFG_HDR cfghdr780={CFG_CBOX,"Command send informer",0,2};
__root const int show_send_info = 0;
__root const CFG_CBOX_ITEM cfgcbox8_z[2]={"Off","On"};
/*
__root const CFG_HDR cfghdr780={CFG_UINT,"Autobot target",0,0xFFFFFFFF};
__root const unsigned int AUTOBOT_UIN=0;
*/
__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

//History
__root const CFG_HDR cfghdr6={CFG_LEVEL,"History",1,0};
  __root const CFG_HDR cfghdr6_8={CFG_CBOX,"Show Active",0,2};
  __root const int SHOW_ACTIVE = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_8[2]={"No","Yes"};
//Enable history logging
  __root const CFG_HDR cfghdr6_1={CFG_CBOX,"Enable logs",0,2};
  __root const int LOG_ALL = 1;
  __root const CFG_CBOX_ITEM cfgcbox6_1[2]={"No","Yes"};

//History type
  __root const CFG_HDR cfghdr6_2={CFG_CBOX,"History for",0,2};
  __root const int HISTORY_TYPE = 1;
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
  __root const CFG_HDR cfghdr6_7={CFG_CBOX,"History read buffer",0,7};
  __root const int HISTORY_BUFFER = 3;
  __root const CFG_CBOX_ITEM cfgcbox6_7[7]={"Disabled","128 bytes","256 bytes","512 bytes","1 kbyte","2 kbyte","4 kbyte"};
  
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
  
    __root const CFG_HDR cfghdr181={CFG_CBOX,"Extended sounds",0,2};
    __root const unsigned int extended_sounds = 0;
    __root const CFG_CBOX_ITEM cfgcbox18_3_2[2]={"No","Yes"};
    
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
    
    __root const CFG_HDR cfghdr15={CFG_STR_UTF8,"add online msg path",0,63};
    __root const char sndGlobal2[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\uins_on\\";
  
    __root const CFG_HDR cfghdr161={CFG_STR_UTF8,"add new msg path",0,63};
    __root const char sndMsg2[64]=DEFAULT_DISK ":\\ZBin\\NatICQ\\Sounds\\uins_msg\\";
  __root const CFG_HDR cfghdr8_6={CFG_LEVEL,"",0,0};
  

__root const CFG_HDR cfghdr9={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr11_9={CFG_STR_UTF8,"Small Ignor-list",0,255};
__root const char ignor_list[256]="";

/*
__root const CFG_HDR cfghdr11_9={CFG_STR_UTF8,"Black-list",0,255};
__root const char ignor_list[256]="";

__root const CFG_HDR cfghdr11_z={CFG_STR_UTF8,"Info",0,263};
__root const char mod_info[264]="mod based on revision 1845, mod date: 08.02.08 at 19:22! you can download (mod date: 08.02.08 at 17:37) from: http://evilfox.wab.ru/plus/naticq_mod_08.02.08.zip";
*/
