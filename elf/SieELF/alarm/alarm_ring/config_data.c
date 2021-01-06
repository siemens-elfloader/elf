#include "..\..\inc\cfg_items.h"

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr0={CFG_CBOX,"使用",0,4};
__root const unsigned int play_=1;
__root const CFG_CBOX_ITEM cfgcbox0[4]={"文件","标准","闹钟铃","快捷"};
#else
__root const CFG_HDR cfghdr0={CFG_CBOX,"使用",0,2};
__root const unsigned int play_=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"文件","标准"};
#endif

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"音乐",0,127};
__root const char melody[128]="2:\\Default\\AlarmMelody.wav";

__root const CFG_HDR cfghdr2={CFG_STR_GB,"快捷",0,63};
__root const char shcut[64]="ELSE_COUNT_DOWN";

__root const CFG_HDR cfghdr3={CFG_UINT,"震动强度",0,100};
__root const unsigned int vibra_power=50;

__root const CFG_HDR cfghdr4={CFG_UINT,"闹铃音量",0,50};
__root const int sndVolume=10;

__root const CFG_HDR cfghdr5={CFG_CHECKBOX,"设置第一情景模式",0,2};
__root const int profile=1;

__root const CFG_HDR cfghdr6={CFG_UINT,"续闹间隔时间(分钟)",0,60};
__root const int time=5;
