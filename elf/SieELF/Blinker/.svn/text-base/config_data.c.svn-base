#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr0 = {CFG_CBOX, "检测事件", 0, 4};
__root const int cfgEvents = 0;
__root const CFG_CBOX_ITEM cfgcbox0[4] = {"全部", "电话", "短信", "其它"};
#else
__root const CFG_HDR cfghdr0 = {CFG_CBOX, "检测事件",0,3};
__root const int cfgEvents=2;
__root const CFG_CBOX_ITEM cfgcbox0[3]={"电话","短信", "全部"};
#endif

__root const CFG_HDR cfghdr9 = {CFG_UINT, "最多事件", 0, 20};
__root const unsigned int cfgMaxEv = 5;

__root const CFG_HDR cfghdr1 = {CFG_UINT, "检测时间周期, sec", 0, 600};
__root const unsigned int cfgInterval = 10;

__root const CFG_HDR cfghdr2 = {CFG_CHECKBOX, "只在锁键盘时作用", 0, 2};
__root const int cfgLockOnly = 1;

__root const CFG_HDR cfghdr3 = {CFG_UINT, "闪光时间间隔, 1/10 sec", 0, 100};
__root const unsigned int cfgPeriod = 2;

__root const CFG_HDR cfghdr4 = {CFG_UINT, "闪光亮度", 0, 100};
__root const unsigned int cfgBright = 50;

__root const CFG_HDR cfghdr5 = {CFG_CHECKBOX, "键盘灯闪", 0, 2};
__root const int cfgKbd = 1;

__root const CFG_HDR cfghdr6 = {CFG_CHECKBOX, "屏幕闪", 0, 2};
__root const int cfgDispl = 1;

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr7 = {CFG_CHECKBOX, "动感闪光", 0, 2};
__root const int cfgDyn = 1;
#else
__root const CFG_HDR cfghdr8 = {CFG_CHECKBOX, "指示灯闪光", 0, 2};
__root const int cfgLighter = 1;
#endif

__root const CFG_HDR cfghdr10={CFG_CHECKBOX,"使用振动",0,2};
__root const int use_vib=1;

__root const CFG_HDR cfghdr11={CFG_UINT,"振动强度",0,100};
__root const unsigned int vibra_pow=50;

__root const CFG_HDR cfghdr12={CFG_CHECKBOX,"使用声音",0,2};
__root const int use_snd=1;

__root const CFG_HDR cfghdr13={CFG_CBOX,"声音类型",0,2};
__root const int sound_type = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"内置","文件"};

__root const CFG_HDR cfghdr14={CFG_UINT,"内置声音ID",0,65535};
__root const unsigned int sndNum=10;

__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"声音文件路径",0,127};
__root const char snd_file[128]="";

__root const CFG_HDR cfghdr16={CFG_UINT,"音量",0,6};
__root const unsigned int sndVolume=3;
