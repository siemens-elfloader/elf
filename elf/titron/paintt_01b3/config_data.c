#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

// 8

__root const CFG_HDR cfghdr0={CFG_CBOX,"��������",0,3};
#ifdef NEWSGOLD
__root const int DEF_PICT_MOD=2;
#else
__root const int DEF_PICT_MOD=1;
#endif
__root const CFG_CBOX_ITEM cfgcbox0[]={"8���","16���","24���+�����"};

__root const CFG_HDR cfghdr8={CFG_CHECKBOX,"������ ����",0,0};
__root const int SWOW_SL = 1;

#if ELKA
__root const CFG_HDR cfghdr1={CFG_CHECKBOX,"�� ���� �����",0,0};
__root const int UseFullScr = 1;
#endif

// __root const CFG_HDR cfghdr2={CFG_CBOX,"��� ��� ������",0,2};
// __root const int DEF_ZOOM_MOD=0;
// __root const CFG_CBOX_ITEM cfgcbox1[]={"1x","2x"};

__root const CFG_HDR cfghdr3={CFG_STR_UTF8,"����� ��������",0,63};
__root const char SAVE_PATH[64]=DEFAULT_DISK ":\\ZBin\\Paintt\\save";

__root const CFG_HDR cfghdr4={CFG_CHECKBOX,"������������ SetCpuClockTempHi",0,0};
__root const int UseHiCPU = 1;

__root const CFG_HDR cfghdr_m1={CFG_LEVEL,"���� ���� ������������",1,0};
	__root const CFG_HDR cfghdr5={CFG_COLOR,"���� 1",0,0};
	__root const char B_COL_1[4]={0,255,255,100};

	__root const CFG_HDR cfghdr6={CFG_COLOR,"���� 2",0,0};
	__root const char B_COL_2[4]={255,140,255,100};
	
	__root const CFG_HDR cfghdr7={CFG_INT,"������ ��������� ����",0,20};
	__root const unsigned int SQ_SZ=5;
__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


