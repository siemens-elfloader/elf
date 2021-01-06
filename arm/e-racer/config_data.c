#include "..\inc\cfg_items.h"

//__root const CFG_HDR cfghdr0={CFG_UINT,"Pic",0,65535};
//__root const unsigned int npic=1;

//__root const CFG_HDR cfghdr0={CFG_UINT,"Скорость (1-7)",1,7};
//__root const unsigned int tm=6;

__root const CFG_HDR cfghdr0 = {CFG_CBOX, "Тип игры", 0, 2};
__root const unsigned int game = 0;
__root const CFG_CBOX_ITEM cfgcbox1_1[2] = {"До 1500 очков", "На рекорд"};

__root const CFG_HDR cfghdr1={CFG_STR_UTF8,"Путь к графике",0,127};
__root const char picg[128]="0:\\ZBin\\E-racer\\";

__root const CFG_HDR cfghdr2={CFG_UINT,"Громкость",0,6};
__root const unsigned int volume=5;

__root const CFG_HDR cfghdr3={CFG_UINT,"Шрифт",0,65535};
__root const unsigned int shrift=4;
