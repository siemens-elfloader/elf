#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

//����������
__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8, "��� �����", 1, 127};
__root const char fname[128] = "0:\\map";

__root const CFG_HDR cfghdr61={CFG_UINT,"������",0,512};
__root const int sizex = 240;

__root const CFG_HDR cfghdr62={CFG_UINT,"������",0,512};
__root const int sizey = 320;

__root const CFG_HDR cfghdr63={CFG_UINT,"�����������",0,19};
__root const int zoom = 14;

__root const CFG_HDR cfghdr64={CFG_CBOX,"������ ��������",0,3};
__root const int frmt = 0;
__root const CFG_CBOX_ITEM cfgcbox1[3]={"png","jpg","png"};

__root const CFG_HDR cfghdr65={CFG_CBOX,"������ �����",0,5};
__root const int map_type = 1;
__root const CFG_CBOX_ITEM cfgcbox2[5]={"roadmap","mobile","satellite", "terrain", "hybrid"};

__root const CFG_HDR cfghdr66={CFG_CBOX,"��� ����",0,3};
__root const int color = 0;
__root const CFG_CBOX_ITEM cfgcbox3[3]={"�������","�������","�����"};

__root const CFG_HDR cfghdr67 = {CFG_STR_UTF8, "��� �����(a-z)", 1, 2};
__root const char name[2] = "i";

__root const CFG_HDR cfghdr68 = {CFG_STR_UTF8, "����", 2, 3};
__root const char lang[3] = "ru";
