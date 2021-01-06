#include "..\..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define PROFILE_PD_DISC "1"
#else
#define PROFILE_PD_DISC "0"
#endif


#ifndef NEWSGOLD
__root const CFG_HDR cfghdr0={CFG_CBOX,"模式",0,4};
__root const unsigned int play_=1;
__root const CFG_CBOX_ITEM cfgcbox0[4]={"文件","标准","默认","地址入口"};
#else
__root const CFG_HDR cfghdr0={CFG_CBOX,"模式",0,2};
__root const unsigned int play_=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"文件","标准"};
#endif

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"文件",0,127};
__root const char melody[128]="2:\\Default\\AlarmMelody.wav";

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr2={CFG_STR_WIN1251,"地址入口",0,63};
__root const char shcut[64]="ELSE_COUNT_DOWN";
#else
__root const CFG_HDR cfghdr2={CFG_CHECKBOX,"MP3闹钟音频",0,2};
__root const int mp3=0;
#endif

__root const CFG_HDR cfghdr3={CFG_UINT,"振动强度",0,100};
__root const unsigned int vibra_power=50;

__root const CFG_HDR cfghdr4={CFG_UINT,"音量",0,50};
__root const int sndVolume=10;

__root const CFG_HDR cfghdr5={CFG_CHECKBOX,"运行时切换情景1",0,2};
__root const int profile=1;

__root const CFG_HDR cfghdr6={CFG_UINT,"重复时间(分钟)",0,60};
__root const int time=5;

__root const CFG_HDR cfghdr7={CFG_STR_UTF8,"闹钟文件位置读取地址",0,63};
__root const char profile_pd_file[64]=PROFILE_PD_DISC":\\\x1F\xE7\xB3\xBB\xE7\xBB\x9F\\hmi\\profile.pd";



