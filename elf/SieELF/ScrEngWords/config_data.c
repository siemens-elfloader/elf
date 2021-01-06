#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#include "lang.h"


__root const CFG_HDR cfghdr0={CFG_COORDINATES, cfgPOS, 0, 0};
__root const unsigned int pos_x=2;
__root const unsigned int pos_y=80;

__root const CFG_HDR cfghdr1={CFG_UINT, cfgWIDTH, 0, 512};
__root const unsigned int width=120;

__root const CFG_HDR cfghdr2={CFG_UINT, cfgFONT, 0, 16};
__root const unsigned int font=FONT_SMALL;

__root const CFG_HDR cfghdr4={CFG_UINT, cfgATTR, 0, 512};
__root const unsigned int txt_attr=10;

__root const CFG_HDR cfghdr5={CFG_COLOR, cfgWD_COLOR, 0, 0};
__root const char word_color[4]={0, 0, 0, 100};

__root const CFG_HDR cfghdr6={CFG_COLOR, cfgWS_FRM_COLOR, 0, 0};
__root const char word_frm_color[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr7={CFG_COLOR, cfgFRM_COLOR, 0, 0};
__root const char rnd_frm_color[4]={0, 0, 0, 100};

__root const CFG_HDR cfghdr8={CFG_CHECKBOX, cfgENALOCK, 0, 2};
__root const int enalock=0;

__root const CFG_HDR cfghdr9={CFG_STR_UTF8,cfgDATA_PATH,3,127};
__root const char datafile_path[128]="0:\\ZBin\\CET4.txt";

