#include "..\..\inc\cfg_items.h"
#include "..\..\inc\swilib.h"
//Конфигурация


__root CFG_HDR cfghdr_01_begin={CFG_LEVEL,"Graphics",1,0};

__root  CFG_HDR cfghdr3_1={CFG_STR_UTF8,"Path",0,127};
__root  char folder_img[128]="0:\\ZBin\\Img\\";

__root CFG_HDR cfghdr01_01={CFG_UINT,"Alpha-chan threshold",0,255};
__root unsigned int ALPHA_THRESHOLD=128;

__root CFG_HDR cfghdr01_02={CFG_UINT,"PNG cache size",20,200};
__root unsigned int CACHE_PNG=50;

#if NEWSGOLD || X75
__root CFG_HDR cfghdr01_03={CFG_CBOX,"Default bit-depth",0,3};
__root unsigned int DEFAULT_COLOR = 2;
__root CFG_CBOX_ITEM cfgcbox01_03[3]={"8 bits","16 bits","24 bits+alpha"};
#else
__root CFG_HDR cfghdr01_03={CFG_CBOX,"Default bit-depth",0,3};
__root unsigned int DEFAULT_COLOR = 1;
__root CFG_CBOX_ITEM cfgcbox01_03[3]={"8 bits","16 bits","Draw Hook"};
#endif

__root CFG_HDR cfghdr_01_end={CFG_LEVEL,"",0,0};


__root CFG_HDR cfghdr_03_begin={CFG_LEVEL,"EDL System",1,0};


__root CFG_HDR cfghdr03_01={CFG_CHECKBOX,"First Lib Load",0,1};
__root int edl_ena = 1;

__root CFG_HDR cfghdr03_02 = {CFG_UINT, "Max Libs", 16, 1024};
__root unsigned int edl_sys_size = 128;

__root CFG_HDR cfghdr_03_end={CFG_LEVEL,"",0,0};



__root CFG_HDR cfghdr_05_begin={CFG_LEVEL,"Misc Settings",1,0};


__root CFG_HDR cfghdr05_01={CFG_CHECKBOX,"Enable Log Sound",0,1};
__root int log_sound = 1;

__root  CFG_HDR cfghdr05_02={CFG_STR_UTF8,"Path Daemons",0,127};
__root  char folder_daemons[128]="0:\\ZBin\\Daemons\\";

__root  CFG_HDR cfghdr05_03={CFG_KEYCODE,"break key",0,100};
__root int key_break='*';

__root CFG_HDR cfghdr05_04={CFG_CHECKBOX,"SUBPROC Daemons",0,1};
__root int subproc_daem = 1;

__root CFG_HDR cfghdr05_05 = {CFG_UINT, "SUBPROC Prio", 1, 255};
__root unsigned int subproc_prio = 128;




__root CFG_HDR cfghdr_05_end={CFG_LEVEL,"",0,0};
