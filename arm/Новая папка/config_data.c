#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
//Конфигурация


__root  CFG_HDR cfghdr1={CFG_STR_UTF8,"Daemons",0,255};
__root  char folder_d[256]="0:\\ZBin\\Daemons\\";

__root  CFG_HDR cfghdr2={CFG_STR_UTF8,"swi.blib",0,63};
__root  char swi_blib[64]="0:\\ZBin\\swi.blib";

__root  CFG_HDR cfghdr_m11={CFG_LEVEL,"PNG",1,0};

__root  CFG_HDR cfghdr3={CFG_STR_UTF8,"Img",0,127};
__root  char folder_i[128]="0:\\ZBin\\Img\\";

__root  CFG_HDR cfghdr4={CFG_STR_UTF8,"elf_small.png, elf_big.png",0,127};
__root  char folder_e[128]="0:\\ZBin\\Img\\";

__root CFG_HDR cfghdr5={CFG_UINT,"Alpha-chan threshold",0,255};
__root unsigned int ALPHA_THRESHOLD=128;

__root CFG_HDR cfghdr6={CFG_UINT,"PNG cache size",20,200};
__root unsigned int CACHE_PNG=50;

#if NEWSGOLD || X75
__root CFG_HDR cfghdr7={CFG_CBOX,"Default bit-depth",0,3};
__root unsigned int DEFAULT_COLOR = 2;
__root CFG_CBOX_ITEM cfgcbox7_1[3]={"8 bits","16 bits","24 bits+alpha"};
#else
__root CFG_HDR cfghdr7={CFG_CBOX,"Default bit-depth",0,2};
__root unsigned int DEFAULT_COLOR = 1;
__root CFG_CBOX_ITEM cfgcbox7_1[2]={"8 bits","16 bits"};
#endif

__root CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};



