#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
__root const CFG_HDR cfghdr0 = {CFG_CBOX, "����¼�", 0, 4};
__root const int cfgEvents = 0;
__root const CFG_CBOX_ITEM cfgcbox0[4] = {"ȫ��", "�绰", "����", "����"};
#else
__root const CFG_HDR cfghdr0 = {CFG_CBOX, "����¼�",0,3};
__root const int cfgEvents=2;
__root const CFG_CBOX_ITEM cfgcbox0[3]={"�绰","����", "ȫ��"};
#endif

__root const CFG_HDR cfghdr9 = {CFG_UINT, "����¼�", 0, 20};
__root const unsigned int cfgMaxEv = 5;

__root const CFG_HDR cfghdr1 = {CFG_UINT, "���ʱ������, sec", 0, 600};
__root const unsigned int cfgInterval = 10;

__root const CFG_HDR cfghdr2 = {CFG_CHECKBOX, "ֻ��������ʱ����", 0, 2};
__root const int cfgLockOnly = 1;

__root const CFG_HDR cfghdr3 = {CFG_UINT, "����ʱ����, 1/10 sec", 0, 100};
__root const unsigned int cfgPeriod = 2;

__root const CFG_HDR cfghdr4 = {CFG_UINT, "��������", 0, 100};
__root const unsigned int cfgBright = 50;

__root const CFG_HDR cfghdr5 = {CFG_CHECKBOX, "���̵���", 0, 2};
__root const int cfgKbd = 1;

__root const CFG_HDR cfghdr6 = {CFG_CHECKBOX, "��Ļ��", 0, 2};
__root const int cfgDispl = 1;

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr7 = {CFG_CHECKBOX, "��������", 0, 2};
__root const int cfgDyn = 1;
#else
__root const CFG_HDR cfghdr8 = {CFG_CHECKBOX, "ָʾ������", 0, 2};
__root const int cfgLighter = 1;
#endif

__root const CFG_HDR cfghdr10={CFG_CHECKBOX,"ʹ����",0,2};
__root const int use_vib=1;

__root const CFG_HDR cfghdr11={CFG_UINT,"��ǿ��",0,100};
__root const unsigned int vibra_pow=50;

__root const CFG_HDR cfghdr12={CFG_CHECKBOX,"ʹ������",0,2};
__root const int use_snd=1;

__root const CFG_HDR cfghdr13={CFG_CBOX,"��������",0,2};
__root const int sound_type = 0;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"����","�ļ�"};

__root const CFG_HDR cfghdr14={CFG_UINT,"��������ID",0,65535};
__root const unsigned int sndNum=10;

__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"�����ļ�·��",0,127};
__root const char snd_file[128]="";

__root const CFG_HDR cfghdr16={CFG_UINT,"����",0,6};
__root const unsigned int sndVolume=3;
