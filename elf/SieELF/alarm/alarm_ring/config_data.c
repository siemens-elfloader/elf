#include "..\..\inc\cfg_items.h"

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr0={CFG_CBOX,"ʹ��",0,4};
__root const unsigned int play_=1;
__root const CFG_CBOX_ITEM cfgcbox0[4]={"�ļ�","��׼","������","���"};
#else
__root const CFG_HDR cfghdr0={CFG_CBOX,"ʹ��",0,2};
__root const unsigned int play_=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"�ļ�","��׼"};
#endif

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"����",0,127};
__root const char melody[128]="2:\\Default\\AlarmMelody.wav";

__root const CFG_HDR cfghdr2={CFG_STR_GB,"���",0,63};
__root const char shcut[64]="ELSE_COUNT_DOWN";

__root const CFG_HDR cfghdr3={CFG_UINT,"��ǿ��",0,100};
__root const unsigned int vibra_power=50;

__root const CFG_HDR cfghdr4={CFG_UINT,"��������",0,50};
__root const int sndVolume=10;

__root const CFG_HDR cfghdr5={CFG_CHECKBOX,"���õ�һ�龰ģʽ",0,2};
__root const int profile=1;

__root const CFG_HDR cfghdr6={CFG_UINT,"���ּ��ʱ��(����)",0,60};
__root const int time=5;
