#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//������������

__root  CFG_HDR cfghdr_m11={CFG_LEVEL,"������������",1,0};//1

__root  CFG_HDR cfghdr1_1={CFG_STR_UTF8,"����� Daemons",0,255};
__root  char folder_d[256]="0:\\ZBin\\Daemons\\";

__root CFG_HDR cfghdr2_22={CFG_CHECKBOX,"SUBPROC",0,0};
__root unsigned int subproc = 1;

__root  CFG_HDR cfghdr1_2={CFG_KEYCODE,"�� �������,���� ������:",0,100};
__root unsigned int key_break='*';

__root  CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};//1

__root CFG_HDR cfghdr_m21={CFG_LEVEL,"���������� �������",1,0};//2

__root  CFG_HDR cfghdr2_1={CFG_STR_UTF8,"���� � swi.blib",0,63};
__root  char swi_blib[64]="0:\\ZBin\\swi.blib";

__root CFG_HDR cfghdr2_2={CFG_CHECKBOX,"��������� swi.blib?",0,0};
__root unsigned int load_blib = 1;

__root CFG_HDR cfghdr2_3={CFG_CHECKBOX,"���������� �� ���������?",0,0};
__root unsigned int msg_conf = 1;

__root CFG_HDR cfghdr2_4={CFG_CHECKBOX,"���������� �� ����������?",0,0};
__root unsigned int msg_missed = 1;

__root CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};//2


__root  CFG_HDR cfghdr_m31={CFG_LEVEL,"�������",1,0};//3

__root  CFG_HDR cfghdr3_1={CFG_STR_UTF8,"����� �������",0,127};
__root  char folder_i[128]="0:\\ZBin\\Img\\";

__root CFG_HDR cfghdr3_2={CFG_CHECKBOX,"��������� �������?",0,0};
__root unsigned int png_load = 1;

__root  CFG_HDR cfghdr3_4={CFG_STR_UTF8,"����� lnk_*.png elf_*.png",0,63};
__root  char folder_e[64]="0:\\ZBin\\Img\\";

__root CFG_HDR cfghdr5={CFG_UINT,"����� ������������",0,255};
__root unsigned int ALPHA_THRESHOLD=128;

__root CFG_HDR cfghdr6={CFG_UINT,"������ ���� ��� �������",20,200};
__root unsigned int CACHE_PNG=90;

#if NEWSGOLD || X75
__root CFG_HDR cfghdr7={CFG_CBOX,"������� �����",0,3};
__root unsigned int DEFAULT_COLOR = 2;
__root CFG_CBOX_ITEM cfgcbox7_1[3]={"8 bits","16 ���","24 ���+�����"};
#else
__root CFG_HDR cfghdr7={CFG_CBOX,"������� �����",0,3};
__root unsigned int DEFAULT_COLOR = 1;
__root CFG_CBOX_ITEM cfgcbox7_1[2]={"8 ���","16 ���"};
#endif

__root CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};//3



