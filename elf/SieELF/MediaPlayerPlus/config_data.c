#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#include "lang.h"

__root const CFG_HDR cfghdr0 = {CFG_STR_GB,CS_CSMADDR,1,8};
__root const char CSMADR[9]="A0895D68";

__root const CFG_HDR cfghdr3_0={CFG_LEVEL, CS_NAMEDRW, 1, 0};

__root const CFG_HDR cfghdr9={CFG_COORDINATES, CS_POS, 0, 0};
__root const unsigned int pos_x=2;
__root const unsigned int pos_y=60;

__root const CFG_HDR cfghdr1={CFG_UINT, CS_LENGTH, 0, 512};
__root const unsigned int length=236;

__root const CFG_HDR cfghdr2={CFG_UINT, CS_FONT, 0, 16};
__root const unsigned int font=FONT_SMALL;

__root const CFG_HDR cfghdr3={CFG_COLOR, CS_COLOR, 0, 0};
__root const char color[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr4={CFG_COLOR, CS_FRMCOLOR, 0, 0};
__root const char frmcolor[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr5={CFG_UINT, CS_ATTR, 0, 512};
__root const unsigned int txt_attr=10;

__root const CFG_HDR cfghdr6={CFG_CHECKBOX, CS_SHOWLOCK, 0, 2};
__root const int ENA_LOCK=0;

__root const CFG_HDR cfghdr7={CFG_UINT, CS_SPEED, 0, 9999};
__root const unsigned int speed=10;

__root const CFG_HDR cfghdrb={CFG_CHECKBOX, CS_SHOW_GP, 0, 2};
__root const int show_gp=0;

__root const CFG_HDR cfghdra={CFG_CHECKBOX, CS_SHOW_EXT, 0, 2};
__root const int show_ext=1;

__root const CFG_HDR cfghdr3_1={CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr1_0={CFG_LEVEL, CS_FRMLEV, 1, 0};

__root const CFG_HDR cfghdr10={CFG_COLOR, CS_FRAMMAINCOLOR, 0, 0};
__root const char frmmain_color[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr12={CFG_COLOR, CS_FRMBGCOLOR, 0, 0};
__root const char frmbg_color[4]={255, 255, 255, 0};

__root const CFG_HDR cfghdr13={CFG_UINT, CS_XRND, 0, 512};
__root const unsigned int xrnd=2;

__root const CFG_HDR cfghdr14={CFG_UINT, CS_YRND, 0, 512};
__root const unsigned int yrnd=2;

__root const CFG_HDR cfghdr15={CFG_CBOX, CS_FRMSTYLE, 0, 2};
__root const int style=0;
__root const CFG_CBOX_ITEM cfgcbox0[2]={CS_SOLID_LINE, CS_BROKEN_LINE};

__root const CFG_HDR cfghdr1_1={CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr4_0={CFG_LEVEL, CS_LRCCTRL, 1, 0};

__root const CFG_HDR cfghdr30={CFG_CHECKBOX, CS_LRC_ENA, 0, 2};
__root const int ena_lrc=0;

__root const CFG_HDR cfghdr31={CFG_STR_UTF8,CS_LRC_DIR_PATH,3,127};
__root const char lrc_dir_path[128]="0:\\ZBin\\MediaPlayerPlus\\LRC\\";

__root const CFG_HDR cfghdr32={CFG_UINT, CS_LRC_FONT, 0, 16};
__root const unsigned int lrc_font=FONT_SMALL;

__root const CFG_HDR cfghdr33={CFG_COLOR, CS_LRC_COLOR, 0, 0};
__root const char lrc_color[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr34={CFG_COLOR, CS_LRC_FRMCOLOR, 0, 0};
__root const char lrc_frmcolor[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr36={CFG_UINT, CS_LRC_ATTR, 0, 512};
__root const unsigned int lrc_txt_attr=10;

__root const CFG_HDR cfghdr35={CFG_UINT, CS_LRC_SPEED, 0, 9999};
__root const unsigned int lrc_speed=20;

__root const CFG_HDR cfghdr4_1={CFG_LEVEL, "", 0, 0};
