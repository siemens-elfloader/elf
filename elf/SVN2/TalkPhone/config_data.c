#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_CBOX,"������������� ��������",0,2};
__root const int on_off=1;
__root const CFG_CBOX_ITEM cfgcbox1[2]={"���","��"};

__root const CFG_HDR cfghdr1={CFG_CBOX,"������ ��� ����. ����.",0,2};
__root const int keypad_lock=0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"���","��"};

__root const CFG_HDR cfghdr2={CFG_UINT,"����� �� �������",0,65535};
__root const unsigned int CALL_BUTTON=53;

//---------------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"��������� �������",1,0};

__root const CFG_HDR cfghdr1_1={CFG_TIME,"������� �",0,0};
__root const TTime TimeFrom={8,0};

__root const CFG_HDR cfghdr1_2={CFG_TIME,"����������",0,0};
__root const TTime TimeTo={22,0};

__root const CFG_HDR cfghdr1_3={CFG_UINT,"����� ������=",0,59};
__root const unsigned int begin_minute=0;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"��������� �����",1,0};

__root const CFG_HDR cfghdr2_1={CFG_UINT,"���������",0,6};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"���� � ����� � *.wav",0,127};
__root const char folder_path[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TalkPhone\\";

__root const CFG_HDR cfghdr2_3={CFG_CBOX,"�������������� ������ ���",0,2};
__root const int PLAY_PARAM=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"�������","��"};

__root const CFG_HDR cfghdr2_4={CFG_CBOX,"�������������� �� ������ ������",0,2};
__root const int PLAY_PARAM_BTN_CALL=1;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"�������","��"};

__root const CFG_HDR cfghdr2_5={CFG_STR_UTF8,"���� � ����� ��������",0,127};
__root const char kurant_path[128]=DEFAULT_DISK ":\\ZBin\\sndElfs\\TalkPhone\\x.wav";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"��������� ������",1,0};

__root const CFG_HDR cfghdr3_1={CFG_CBOX,"���������� ������",0,2};
__root const int show_icon=1;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"���","��"};

__root const CFG_HDR cfghdr3_2={CFG_COORDINATES,"������� ������",0,0};
__root const unsigned int cfgX=0;
__root const unsigned int cfgY=30;

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

//---------------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"��������� �����",1,0};

__root const CFG_HDR cfghdr4_1={CFG_CBOX,"������������ �����",0,2};
__root const int Is_Vibra_Enabled=1;
__root const CFG_CBOX_ITEM cfgcbox6[2]={"���","��"};

__root const CFG_HDR cfghdr4_2 = {CFG_UINT, "���-�� ��������", 0, 10};
__root const unsigned int vibra_count = 4;

__root const CFG_HDR cfghdr4_3 = {CFG_UINT, "�������� ��������", 0, 100};
__root const unsigned int vibra_power = 50;

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};
