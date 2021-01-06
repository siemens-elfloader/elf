#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0={CFG_CHECKBOX, "锁键盘时启动", 0, 2};
__root const int ENA_LOCK=0;

__root const CFG_HDR cfghdr10={CFG_LEVEL, "方框一", 1, 0};

__root const CFG_HDR cfghdr1c={CFG_CHECKBOX, "启用", 0, 2};
__root const int enable1=0;

__root const CFG_HDR cfghdr11={CFG_RECT, "位置", 0, 239};
__root const RECT pos1={0, 0, 0, 0};

__root const CFG_HDR cfghdr12={CFG_COLOR, "颜色", 0, 0};
__root const char color1[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr1e={CFG_COLOR, "背景色", 0, 0};
__root const char bg_col1[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr13={CFG_CBOX, "样式", 0, 2};
__root const int style1=0;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"实线", "虚线"};

__root const CFG_HDR cfghdr1a={CFG_UINT, "X弯曲", 0, 239};
__root const unsigned int xrnd1=0;

__root const CFG_HDR cfghdr1b={CFG_UINT, "Y弯曲", 0, 319};
__root const unsigned int yrnd1=0;

__root const CFG_HDR cfghdr14={CFG_STR_GB, "文字", 1, 127};
__root const char string1[128]="";

__root const CFG_HDR cfghdr1d={CFG_COORDINATES, "文字位置", 0, 0};
__root const unsigned int str_x1=0;
__root const unsigned int str_y1=0;

__root const CFG_HDR cfghdr15={CFG_UINT, "文字字体", 0, 16};
__root const unsigned int font1=FONT_SMALL;

__root const CFG_HDR cfghdr16={CFG_COLOR, "文字颜色", 0, 0};
__root const char str_col1[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr17={CFG_COLOR, "文字边框颜色", 0, 0};
__root const char strfr_col1[4]={0, 0, 0, 80};

__root const CFG_HDR cfghdr19={CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr20={CFG_LEVEL, "方框二", 1, 0};

__root const CFG_HDR cfghdr2c={CFG_CHECKBOX, "启用", 0, 2};
__root const int enable2=0;

__root const CFG_HDR cfghdr21={CFG_RECT, "位置", 0, 239};
__root const RECT pos2={0, 0, 0, 0};

__root const CFG_HDR cfghdr22={CFG_COLOR, "颜色", 0, 0};
__root const char color2[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr2e={CFG_COLOR, "背景色", 0, 0};
__root const char bg_col2[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr23={CFG_CBOX, "样式", 0, 2};
__root const int style2=0;
__root const CFG_CBOX_ITEM cfgcbox2[2]={"实线", "虚线"};

__root const CFG_HDR cfghdr2a={CFG_UINT, "X弯曲", 0, 239};
__root const unsigned int xrnd2=0;

__root const CFG_HDR cfghdr2b={CFG_UINT, "Y弯曲", 0, 319};
__root const unsigned int yrnd2=0;

__root const CFG_HDR cfghdr24={CFG_STR_GB, "文字", 1, 127};
__root const char string2[128]="";

__root const CFG_HDR cfghdr2d={CFG_COORDINATES, "文字位置", 0, 0};
__root const unsigned int str_x2=0;
__root const unsigned int str_y2=0;

__root const CFG_HDR cfghdr25={CFG_UINT, "文字字体", 0, 16};
__root const unsigned int font2=FONT_SMALL;

__root const CFG_HDR cfghdr26={CFG_COLOR, "文字颜色", 0, 0};
__root const char str_col2[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr27={CFG_COLOR, "文字边框颜色", 0, 0};
__root const char strfr_col2[4]={0, 0, 0, 80};

__root const CFG_HDR cfghdr29={CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr30={CFG_LEVEL, "方框三", 1, 0};

__root const CFG_HDR cfghdr3c={CFG_CHECKBOX, "启用", 0, 2};
__root const int enable3=0;

__root const CFG_HDR cfghdr31={CFG_RECT, "位置", 0, 239};
__root const RECT pos3={0, 0, 0, 0};

__root const CFG_HDR cfghdr32={CFG_COLOR, "颜色", 0, 0};
__root const char color3[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr3e={CFG_COLOR, "背景色", 0, 0};
__root const char bg_col3[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr33={CFG_CBOX, "样式", 0, 2};
__root const int style3=0;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"实线", "虚线"};

__root const CFG_HDR cfghdr3a={CFG_UINT, "X弯曲", 0, 239};
__root const unsigned int xrnd3=0;

__root const CFG_HDR cfghdr3b={CFG_UINT, "Y弯曲", 0, 319};
__root const unsigned int yrnd3=0;

__root const CFG_HDR cfghdr34={CFG_STR_GB, "文字", 1, 127};
__root const char string3[128]="";

__root const CFG_HDR cfghdr3d={CFG_COORDINATES, "文字位置", 0, 0};
__root const unsigned int str_x3=0;
__root const unsigned int str_y3=0;

__root const CFG_HDR cfghdr35={CFG_UINT, "文字字体", 0, 16};
__root const unsigned int font3=FONT_SMALL;

__root const CFG_HDR cfghdr36={CFG_COLOR, "文字颜色", 0, 0};
__root const char str_col3[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr37={CFG_COLOR, "文字边框颜色", 0, 0};
__root const char strfr_col3[4]={0, 0, 0, 80};

__root const CFG_HDR cfghdr39={CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr40={CFG_LEVEL, "方框四", 1, 0};

__root const CFG_HDR cfghdr4c={CFG_CHECKBOX, "启用", 0, 2};
__root const int enable4=0;

__root const CFG_HDR cfghdr41={CFG_RECT, "位置", 0, 239};
__root const RECT pos4={0, 0, 0, 0};

__root const CFG_HDR cfghdr42={CFG_COLOR, "颜色", 0, 0};
__root const char color4[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr4e={CFG_COLOR, "背景色", 0, 0};
__root const char bg_col4[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr43={CFG_CBOX, "样式", 0, 2};
__root const int style4=0;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"实线", "虚线"};

__root const CFG_HDR cfghdr4a={CFG_UINT, "X弯曲", 0, 239};
__root const unsigned int xrnd4=0;

__root const CFG_HDR cfghdr4b={CFG_UINT, "Y弯曲", 0, 319};
__root const unsigned int yrnd4=0;

__root const CFG_HDR cfghdr44={CFG_STR_GB, "文字", 1, 127};
__root const char string4[128]="";

__root const CFG_HDR cfghdr4d={CFG_COORDINATES, "文字位置", 0, 0};
__root const unsigned int str_x4=0;
__root const unsigned int str_y4=0;

__root const CFG_HDR cfghdr45={CFG_UINT, "文字字体", 0, 16};
__root const unsigned int font4=FONT_SMALL;

__root const CFG_HDR cfghdr46={CFG_COLOR, "文字颜色", 0, 0};
__root const char str_col4[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr47={CFG_COLOR, "文字边框颜色", 0, 0};
__root const char strfr_col4[4]={0, 0, 0, 80};

__root const CFG_HDR cfghdr49={CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr50={CFG_LEVEL, "方框五", 1, 0};

__root const CFG_HDR cfghdr5c={CFG_CHECKBOX, "启用", 0, 2};
__root const int enable5=0;

__root const CFG_HDR cfghdr51={CFG_RECT, "位置", 0, 239};
__root const RECT pos5={0, 0, 0, 0};

__root const CFG_HDR cfghdr52={CFG_COLOR, "颜色", 0, 0};
__root const char color5[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr5e={CFG_COLOR, "背景色", 0, 0};
__root const char bg_col5[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr53={CFG_CBOX, "样式", 0, 2};
__root const int style5=0;
__root const CFG_CBOX_ITEM cfgcbox5[2]={"实线", "虚线"};

__root const CFG_HDR cfghdr5a={CFG_UINT, "X弯曲", 0, 239};
__root const unsigned int xrnd5=0;

__root const CFG_HDR cfghdr5b={CFG_UINT, "Y弯曲", 0, 319};
__root const unsigned int yrnd5=0;

__root const CFG_HDR cfghdr54={CFG_STR_GB, "文字", 1, 127};
__root const char string5[128]="";

__root const CFG_HDR cfghdr5d={CFG_COORDINATES, "文字位置", 0, 0};
__root const unsigned int str_x5=0;
__root const unsigned int str_y5=0;

__root const CFG_HDR cfghdr55={CFG_UINT, "文字字体", 0, 16};
__root const unsigned int font5=FONT_SMALL;

__root const CFG_HDR cfghdr56={CFG_COLOR, "文字颜色", 0, 0};
__root const char str_col5[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr57={CFG_COLOR, "文字边框颜色", 0, 0};
__root const char strfr_col5[4]={0, 0, 0, 80};

__root const CFG_HDR cfghdr59={CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr60={CFG_LEVEL, "方框六", 1, 0};

__root const CFG_HDR cfghdr6c={CFG_CHECKBOX, "启用", 0, 2};
__root const int enable6=0;

__root const CFG_HDR cfghdr61={CFG_RECT, "位置", 0, 239};
__root const RECT pos6={0, 0, 0, 0};

__root const CFG_HDR cfghdr62={CFG_COLOR, "颜色", 0, 0};
__root const char color6[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr6e={CFG_COLOR, "背景色", 0, 0};
__root const char bg_col6[4]={0, 0, 0, 0};

__root const CFG_HDR cfghdr63={CFG_CBOX, "样式", 0, 2};
__root const int style6=0;
__root const CFG_CBOX_ITEM cfgcbox6[2]={"实线", "虚线"};

__root const CFG_HDR cfghdr6a={CFG_UINT, "X弯曲", 0, 239};
__root const unsigned int xrnd6=0;

__root const CFG_HDR cfghdr6b={CFG_UINT, "Y弯曲", 0, 319};
__root const unsigned int yrnd6=0;

__root const CFG_HDR cfghdr64={CFG_STR_GB, "文字", 1, 127};
__root const char string6[128]="";

__root const CFG_HDR cfghdr6d={CFG_COORDINATES, "文字位置", 0, 0};
__root const unsigned int str_x6=0;
__root const unsigned int str_y6=0;

__root const CFG_HDR cfghdr65={CFG_UINT, "文字字体", 0, 16};
__root const unsigned int font6=FONT_SMALL;

__root const CFG_HDR cfghdr66={CFG_COLOR, "文字颜色", 0, 0};
__root const char str_col6[4]={255, 255, 255, 80};

__root const CFG_HDR cfghdr67={CFG_COLOR, "文字边框颜色", 0, 0};
__root const char strfr_col6[4]={0, 0, 0, 80};

__root const CFG_HDR cfghdr69={CFG_LEVEL, "", 0, 0};

