#pragma segment="CONFIG_C"
#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//Конфигурация

//#define ELKA


__root const CFG_HDR ch0={CFG_CHECKBOX,"Enable TalkKeyboard",0,2};
__root const unsigned int spc_keyvol=1;


__root const CFG_HDR ch27={CFG_CHECKBOX,"Enable talk about net",0,2};
__root const unsigned int spc_net=1;




__root const CFG_HDR ch3={CFG_UINT,"Speech when power lower: (0-off)",0,100};
__root const unsigned int spc_level=100;

__root const CFG_HDR cl9={CFG_LEVEL,"Talk time setup",1,0};

__root const CFG_HDR ch12={CFG_CHECKBOX,"Don't say zero minutes",0,2};
__root const unsigned int spc_min=0;

__root const CFG_HDR ch2={CFG_CHECKBOX,"Enable Talk Every Hour",0,2};
__root const unsigned int spc_kukvol=1;


__root const CFG_HDR ch19={CFG_CHECKBOX,"Enable Talk in locked",0,2};
__root const unsigned int spc_kukloc=1;



__root const CFG_HDR ch20={CFG_UINT,"Key to speech in unlock ",0,256};
__root const unsigned int spc_kukkey=UP_BUTTON;


__root const CFG_HDR _l9={CFG_LEVEL,"",0,0};




#ifdef NEWSGOLD

__root const CFG_HDR ch4={CFG_UINT,"Volume:(8-auto,7/9-vl.prof-/+1)",0,9};
__root const unsigned int spc_vol=7;

__root const CFG_HDR ch28={CFG_CHECKBOX,"Disable talk when player plaing",0,2};
#ifdef ELKA
__root const unsigned int spc_ign=0;
#else
__root const unsigned int spc_ign=1;
#endif




#else
__root const CFG_HDR ch4={CFG_UINT,"Volume:",0,6};
__root const unsigned int spc_vol=3;
#endif




__root const CFG_HDR ch5={CFG_UINT,"Moorning:",0,24};
__root const unsigned int spc_mn=8;

__root const CFG_HDR ch6={CFG_UINT,"Evening:",0,24};
__root const unsigned int spc_en=23;
__root const CFG_HDR _l1={CFG_LEVEL,"",0,0};



#ifndef NOHEADSET
__root const CFG_HDR cl3={CFG_LEVEL,"Headset setup",1,0};

__root const CFG_HDR ch37={CFG_CHECKBOX,"Pause/exit on Headset disconnect",0,2};
__root const unsigned int exitOnHeadDisc=0;


__root const CFG_HDR ch8={CFG_CBOX,"Keyboard State",0,3};
__root const unsigned int keyb_state=2;
__root const CFG_CBOX_ITEM cb8[3]={"Only lock","Only unlock","Ignore"};

__root const CFG_HDR ch9={CFG_UINT,"Critical battery power",0,100};
__root const unsigned int batt_level=0;

#ifdef NEWSGOLD
#ifndef ELKA
__root const CFG_HDR ch18={CFG_CHECKBOX,"Kill player on Incoming cals",0,2};
__root const unsigned int killPlr=1;
#endif
#endif

//__root const CFG_HDR ch17={CFG_CBOX,"Enable RamMediaIsPlaying",0,2};
//__root const unsigned int allow_rmp=1;
//__root const CFG_CBOX_ITEM cb17[2]={"No","Yes"};

__root const CFG_HDR _l3={CFG_LEVEL,"",0,0};

__root const CFG_HDR cl4={CFG_LEVEL,"ID3 Tags setup",1,0};
__root const CFG_HDR c9 = {CFG_STR_WIN1251,"Mediaplayer CSM (0-off)",1,8};
#ifdef ELKA
__root const char CsmAdr[9]="A087B454"; //for el71v45
#else
__root const char CsmAdr[9]="A068E244"; //for s75v47
#endif



__root const CFG_HDR c15={CFG_RECT,"Rect of ID3",0,0};
#ifdef ELKA
__root const RECT cTgr = {0,120,240-1,120+11};
#else
__root const RECT cTgr = {0,65,132-1,65+11};
#endif


__root const CFG_HDR ch11={CFG_UINT,"Font size",0,11};
__root const unsigned int cfnt=FONT_SMALL_BOLD;


__root const CFG_HDR c17={CFG_COLOR,"Tag color",0,0};
__root const char clr[4]={255,255,32,100};

//#ifdef ELKA
__root const CFG_HDR ch21={CFG_UINT,"Key prev",0,255};
__root const unsigned int key_prev=VOL_UP_BUTTON;
__root const CFG_HDR ch22={CFG_UINT,"Key next",0,255};
__root const unsigned int key_next=VOL_DOWN_BUTTON;

//#endif
__root const CFG_HDR _l4={CFG_LEVEL,"",0,0};


#endif

#ifdef ELKA
__root const CFG_HDR cl2={CFG_LEVEL,"AudioBuffer setup",1,0};
__root const CFG_HDR ch7={CFG_CBOX,"Enable AudioBuffer config",0,3};
__root const unsigned int allowbuf=1;
__root const CFG_CBOX_ITEM cb78[3]={"Disable","Enable only Headset","Auto on player"};



__root const CFG_HDR ch14={CFG_UINT,"RAM AudBufOffset",0x00000000,0xFFFFFFFF};
__root const unsigned int audcfg=0x0;
//__root const unsigned int audcfg=0xA8F5798C;

__root const CFG_HDR ch15={CFG_UINT,"Nof Buffers:",0,10};
__root const unsigned int buff_nof=5;

__root const CFG_HDR ch16={CFG_UINT,"Buffer Size: x10",0,30};
__root const unsigned  int buff_size=20;
__root const CFG_HDR _l2={CFG_LEVEL,"",0,0};
#endif


__root const CFG_HDR ch13={CFG_CHECKBOX,"Enable refresh message",0,2};
__root const int REFMSG=0;



__root const CFG_HDR ch1={CFG_CHECKBOX,"Enable hello message",0,2};
__root const int ALLOW_HELLO_MSG=0;


//__root const CFG_HDR ch11={CFG_UINT,"Refresh time in ticks (1s=262)",1,5240};
//__root const unsigned int refres2=131;





