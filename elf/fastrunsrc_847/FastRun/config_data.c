//  ŒÕ‘»√!!!
#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

__root const CFG_HDR cfghdr0={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr2={CFG_LEVEL,"FastRun panel setup",1,0};

__root const CFG_HDR cfghdr_q_2={CFG_CHECKBOX,"Display FastRun panel",0,2};
__root const int FASTRUN_ENA = 1;

__root const CFG_HDR cfghdr1={CFG_LEVEL,"Setup keys",1,0};

__root const CFG_HDR cfghdr2334={CFG_CBOX,"Enable key activation style",0,2};
__root const int ENA_FR_LONGPRESS=1;
__root const CFG_CBOX_ITEM cfgcbox23[2]={"Short press","Long press"};

__root const CFG_HDR cfghdr3={CFG_UINT,"Enable key (DEC)",0,65535};
__root const int FR_CALL_BUTTON=GREEN_BUTTON;

__root const CFG_HDR cfghdr4={CFG_UINT,"Disable key (DEC)",0,65535};
__root const int FR_EXIT_BUTTON=GREEN_BUTTON;
__root const CFG_HDR cfghdr5={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr6={CFG_LEVEL,"Setup position",1,0};
__root const CFG_HDR cfghdr7={CFG_CBOX,"Position on screen",0,4};
__root const int DRAW_MODE=0;
__root const CFG_CBOX_ITEM cfgcbox1[4]={"Left","Right","Top","Bottom"};

__root const CFG_HDR cfghdr9={CFG_UINT,"Offset",0,320};
__root const unsigned int BEGIN=5;

__root const CFG_HDR cfghdr10={CFG_UINT,"Panel lenght",0,320};
__root const unsigned int LEN=165;

__root const CFG_HDR cfghdr6921={CFG_CBOX,"Pictures size",0,5};
__root const int FR_PIC_SIZE=0;
__root const CFG_CBOX_ITEM cfgcbox4433[5]={"16x16","24x24","32x32","48x48","64x64"};
__root const CFG_HDR cfghdr11={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr12={CFG_LEVEL,"Setup colors",1,0};
__root const CFG_HDR cfghdr60={CFG_COLOR,"Panel border col",0,0};
__root const char cfgPanBorderCol[4]={255,255,255,100};

__root const CFG_HDR cfghdr61={CFG_COLOR,"Panel BG col",0,0};
__root const char cfgPanBGCol[4]={255,255,255,37};

__root const CFG_HDR cfghdr62={CFG_COLOR,"Bookmark border col",0,0};
__root const char cfgBookBorderCol[4]={255,255,255,100};

__root const CFG_HDR cfghdr63={CFG_COLOR,"Bookmark BG col",0,0};
__root const char cfgBookBGCol[4]={255,255,255,37};
__root const CFG_HDR cfghdr13={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr124={CFG_LEVEL,"Setup bookmarks",1,0};
__root const CFG_HDR cfghdr14={CFG_STR_UTF8,"Bookmark 1 action",3,127};
__root const char BM1FILE_FR[128]="";
__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"Bookmark 1 icon",3,127};
__root const char BM1PIC_FR[128]="";

__root const CFG_HDR cfghdr17={CFG_STR_UTF8,"Bookmark 2 action",3,127};
__root const char BM2FILE_FR[128]="";
__root const CFG_HDR cfghdr18={CFG_STR_UTF8,"Bookmark 2 icon",3,127};
__root const char BM2PIC_FR[128]="";

__root const CFG_HDR cfghdr20={CFG_STR_UTF8,"Bookmark 3 action",3,127};
__root const char BM3FILE_FR[128]="";
__root const CFG_HDR cfghdr21={CFG_STR_UTF8,"Bookmark 3 icon",3,127};
__root const char BM3PIC_FR[128]="";

__root const CFG_HDR cfghdr23={CFG_STR_UTF8,"Bookmark 4 action",3,127};
__root const char BM4FILE_FR[128]="";
__root const CFG_HDR cfghdr24={CFG_STR_UTF8,"Bookmark 4 icon",3,127};
__root const char BM4PIC_FR[128]="";

__root const CFG_HDR cfghdr26={CFG_STR_UTF8,"Bookmark 5 action",3,127};
__root const char BM5FILE_FR[128]="";
__root const CFG_HDR cfghdr27={CFG_STR_UTF8,"Bookmark 5 icon",3,127};
__root const char BM5PIC_FR[128]="";

__root const CFG_HDR cfghdr29={CFG_STR_UTF8,"Bookmark 6 action",3,127};
__root const char BM6FILE_FR[128]="";
__root const CFG_HDR cfghdr30={CFG_STR_UTF8,"Bookmark 6 icon",3,127};
__root const char BM6PIC_FR[128]="";

__root const CFG_HDR cfghdr32={CFG_STR_UTF8,"Bookmark 7 action",3,127};
__root const char BM7FILE_FR[128]="";
__root const CFG_HDR cfghdr33={CFG_STR_UTF8,"Bookmark 7 icon",3,127};
__root const char BM7PIC_FR[128]="";

__root const CFG_HDR cfghdr35={CFG_STR_UTF8,"Bookmark 8 action",3,127};
__root const char BM8FILE_FR[128]="";
__root const CFG_HDR cfghdr36={CFG_STR_UTF8,"Bookmark 8 icon",3,127};
__root const char BM8PIC_FR[128]="";

__root const CFG_HDR cfghdr38={CFG_STR_UTF8,"Bookmark 9 action",3,127};
__root const char BM9FILE_FR[128]="";
__root const CFG_HDR cfghdr39={CFG_STR_UTF8,"Bookmark 9 icon",3,127};
__root const char BM9PIC_FR[128]="";

__root const CFG_HDR cfghdr41={CFG_STR_UTF8,"Bookmark 10 action",3,127};
__root const char BM10FILE_FR[128]="";
__root const CFG_HDR cfghdr42={CFG_STR_UTF8,"Bookmark 10 icon",3,127};
__root const char BM10PIC_FR[128]="";

__root const CFG_HDR cfghdr44={CFG_STR_UTF8,"Bookmark 11 action",3,127};
__root const char BM11FILE_FR[128]="";
__root const CFG_HDR cfghdr45={CFG_STR_UTF8,"Bookmark 11 icon",3,127};
__root const char BM11PIC_FR[128]="";

__root const CFG_HDR cfghdr47={CFG_STR_UTF8,"Bookmark 12 action",3,127};
__root const char BM12FILE_FR[128]="";
__root const CFG_HDR cfghdr48={CFG_STR_UTF8,"Bookmark 12 icon",3,127};
__root const char BM12PIC_FR[128]="";

__root const CFG_HDR cfghdr50={CFG_STR_UTF8,"Bookmark 13 action",3,127};
__root const char BM13FILE_FR[128]="";
__root const CFG_HDR cfghdr51={CFG_STR_UTF8,"Bookmark 13 icon",3,127};
__root const char BM13PIC_FR[128]="";

__root const CFG_HDR cfghdr53={CFG_STR_UTF8,"Bookmark 14 action",3,127};
__root const char BM14FILE_FR[128]="";
__root const CFG_HDR cfghdr54={CFG_STR_UTF8,"Bookmark 14 icon",3,127};
__root const char BM14PIC_FR[128]="";

__root const CFG_HDR cfghdr56={CFG_STR_UTF8,"Bookmark 15 action",3,127};
__root const char BM15FILE_FR[128]="";
__root const CFG_HDR cfghdr57={CFG_STR_UTF8,"Bookmark 15 icon",3,127};
__root const char BM15PIC_FR[128]="";
__root const CFG_HDR cfghdr158={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr66={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr67={CFG_LEVEL,"Idle panel setup",1,0};

__root const CFG_HDR cfghdr_c_2={CFG_CHECKBOX,"Display Idle panel",0,2};
__root const int IDLE_ENA = 1;

__root const CFG_HDR cfghdr199={CFG_LEVEL,"Setup keys",1,0};

__root const CFG_HDR cfghdr2434={CFG_CBOX,"Enable key activation style",0,2};
__root const int ENA_IDLE_LONGPRESS=1;
__root const CFG_CBOX_ITEM cfgcbox443[2]={"Short press","Long press"};

__root const CFG_HDR cfghdr389={CFG_UINT,"Enable key (DEC)",0,65535};
__root const int IDLE_CALL_BUTTON=RIGHT_SOFT;

__root const CFG_HDR cfghdr487={CFG_UINT,"Disable key (DEC)",0,65535};
__root const int IDLE_EXIT_BUTTON=RIGHT_SOFT;
__root const CFG_HDR cfghdr576={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr671={CFG_LEVEL,"Setup position",1,0};
__root const CFG_HDR cfghdr68={CFG_COORDINATES,"Coordinates",0,0};
__root const unsigned int x1=0;
__root const unsigned int y1=39;

__root const CFG_HDR cfghdr69={CFG_UINT,"Panel lenght",0,240};
__root const unsigned int LEN_ID=131;

__root const CFG_HDR cfghdr692={CFG_CBOX,"Pictures size",0,5};
__root const int IDLE_PIC_SIZE=0;
__root const CFG_CBOX_ITEM cfgcbox4434[5]={"16x16","24x24","32x32","48x48","64x64"};
__root const CFG_HDR cfghdr1112={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr672={CFG_LEVEL,"Setup colors",1,0};
__root const CFG_HDR cfghdr134={CFG_COLOR,"Panel enabled BG col",0,0};
__root const char cfgPanBGCol_ID_ena[4]={255,255,255,37};

__root const CFG_HDR cfghdr1343={CFG_COLOR,"Panel disabled BG col",0,0};
__root const char cfgPanBGCol_ID_dis[4]={255,255,255,16};

__root const CFG_HDR cfghdr135={CFG_COLOR,"Bookmark border col",0,0};
__root const char cfgBookBorderCol_ID[4]={255,255,255,100};

__root const CFG_HDR cfghdr136={CFG_COLOR,"Bookmark BG col",0,0};
__root const char cfgBookBGCol_ID[4]={255,255,255,20};

__root const CFG_HDR cfghdr137={CFG_COLOR,"Font col",0,0};
__root const char cfgFontCol_ID[4]={255,255,255,100};
__root const CFG_HDR cfghdr111={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr128={CFG_LEVEL,"Setup fonts",1,0};
__root const CFG_HDR cfghdr157={CFG_UINT,"Font Size",0,100};
__root const unsigned int TEXT_FONT=FONT_SMALL;
__root const CFG_HDR cfghdr138={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr673={CFG_LEVEL,"Setup bookmarks",1,0};
__root const CFG_HDR cfghdr73={CFG_STR_UTF8,"Bookmark 1 action",3,127};
__root const char BM1FILE_ID[128]="";
__root const CFG_HDR cfghdr74={CFG_STR_UTF8,"Bookmark 1 icon",3,127};
__root const char BM1PIC_ID[128]="";
__root const CFG_HDR cfghdr75={CFG_STR_WIN1251,"Bookmark 1 name",1,31};
__root const char BM1NAME[32]="";

__root const CFG_HDR cfghdr77={CFG_STR_UTF8,"Bookmark 2 action",3,127};
__root const char BM2FILE_ID[128]="";
__root const CFG_HDR cfghdr78={CFG_STR_UTF8,"Bookmark 2 icon",3,127};
__root const char BM2PIC_ID[128]="";
__root const CFG_HDR cfghdr79={CFG_STR_WIN1251,"Bookmark 2 name",1,31};
__root const char BM2NAME[32]="";

__root const CFG_HDR cfghdr81={CFG_STR_UTF8,"Bookmark 3 action",3,127};
__root const char BM3FILE_ID[128]="";
__root const CFG_HDR cfghdr82={CFG_STR_UTF8,"Bookmark 3 icon",3,127};
__root const char BM3PIC_ID[128]="";
__root const CFG_HDR cfghdr83={CFG_STR_WIN1251,"Bookmark 3 name",1,31};
__root const char BM3NAME[32]="";

__root const CFG_HDR cfghdr85={CFG_STR_UTF8,"Bookmark 4 action",3,127};
__root const char BM4FILE_ID[128]="";
__root const CFG_HDR cfghdr86={CFG_STR_UTF8,"Bookmark 4 icon",3,127};
__root const char BM4PIC_ID[128]="";
__root const CFG_HDR cfghdr87={CFG_STR_WIN1251,"Bookmark 4 name",1,31};
__root const char BM4NAME[32]="";

__root const CFG_HDR cfghdr89={CFG_STR_UTF8,"Bookmark 5 action",3,127};
__root const char BM5FILE_ID[128]="";
__root const CFG_HDR cfghdr90={CFG_STR_UTF8,"Bookmark 5 icon",3,127};
__root const char BM5PIC_ID[128]="";
__root const CFG_HDR cfghdr91={CFG_STR_WIN1251,"Bookmark 5 name",1,31};
__root const char BM5NAME[32]="";

__root const CFG_HDR cfghdr93={CFG_STR_UTF8,"Bookmark 6 action",3,127};
__root const char BM6FILE_ID[128]="";
__root const CFG_HDR cfghdr94={CFG_STR_UTF8,"Bookmark 6 icon",3,127};
__root const char BM6PIC_ID[128]="";
__root const CFG_HDR cfghdr95={CFG_STR_WIN1251,"Bookmark 6 name",1,31};
__root const char BM6NAME[32]="";

__root const CFG_HDR cfghdr97={CFG_STR_UTF8,"Bookmark 7 action",3,127};
__root const char BM7FILE_ID[128]="";
__root const CFG_HDR cfghdr98={CFG_STR_UTF8,"Bookmark 7 icon",3,127};
__root const char BM7PIC_ID[128]="";
__root const CFG_HDR cfghdr99={CFG_STR_WIN1251,"Bookmark 7 name",1,31};
__root const char BM7NAME[32]="";

__root const CFG_HDR cfghdr101={CFG_STR_UTF8,"Bookmark 8 action",3,127};
__root const char BM8FILE_ID[128]="";
__root const CFG_HDR cfghdr102={CFG_STR_UTF8,"Bookmark 8 icon",3,127};
__root const char BM8PIC_ID[128]="";
__root const CFG_HDR cfghdr103={CFG_STR_WIN1251,"Bookmark 8 name",1,31};
__root const char BM8NAME[32]="";

__root const CFG_HDR cfghdr105={CFG_STR_UTF8,"Bookmark 9 action",3,127};
__root const char BM9FILE_ID[128]="";
__root const CFG_HDR cfghdr106={CFG_STR_UTF8,"Bookmark 9 icon",3,127};
__root const char BM9PIC_ID[128]="";
__root const CFG_HDR cfghdr107={CFG_STR_WIN1251,"Bookmark 9 name",1,31};
__root const char BM9NAME[32]="";

__root const CFG_HDR cfghdr109={CFG_STR_UTF8,"Bookmark 10 action",3,127};
__root const char BM10FILE_ID[128]="";
__root const CFG_HDR cfghdr110={CFG_STR_UTF8,"Bookmark 10 icon",3,127};
__root const char BM10PIC_ID[128]="";
__root const CFG_HDR cfghdr113={CFG_STR_WIN1251,"Bookmark 10 name",1,31};
__root const char BM10NAME[32]="";

__root const CFG_HDR cfghdr133={CFG_STR_UTF8,"Bookmark 11 action",3,127};
__root const char BM11FILE_ID[128]="";
__root const CFG_HDR cfghdr114={CFG_STR_UTF8,"Bookmark 11 icon",3,127};
__root const char BM11PIC_ID[128]="";
__root const CFG_HDR cfghdr115={CFG_STR_WIN1251,"Bookmark 11 name",1,31};
__root const char BM11NAME[32]="";

__root const CFG_HDR cfghdr117={CFG_STR_UTF8,"Bookmark 12 action",3,127};
__root const char BM12FILE_ID[128]="";
__root const CFG_HDR cfghdr118={CFG_STR_UTF8,"Bookmark 12 icon",3,127};
__root const char BM12PIC_ID[128]="";
__root const CFG_HDR cfghdr119={CFG_STR_WIN1251,"Bookmark 12 name",1,31};
__root const char BM12NAME[32]="";

__root const CFG_HDR cfghdr121={CFG_STR_UTF8,"Bookmark 13 action",3,127};
__root const char BM13FILE_ID[128]="";
__root const CFG_HDR cfghdr122={CFG_STR_UTF8,"Bookmark 13 icon",3,127};
__root const char BM13PIC_ID[128]="";
__root const CFG_HDR cfghdr123={CFG_STR_WIN1251,"Bookmark 13 name",1,31};
__root const char BM13NAME[32]="";

__root const CFG_HDR cfghdr125={CFG_STR_UTF8,"Bookmark 14 action",3,127};
__root const char BM14FILE_ID[128]="";
__root const CFG_HDR cfghdr126={CFG_STR_UTF8,"Bookmark 14 icon",3,127};
__root const char BM14PIC_ID[128]="";
__root const CFG_HDR cfghdr127={CFG_STR_WIN1251,"Bookmark 14 name",1,31};
__root const char BM14NAME[32]="";

__root const CFG_HDR cfghdr129={CFG_STR_UTF8,"Bookmark 15 action",3,127};
__root const char BM15FILE_ID[128]="";
__root const CFG_HDR cfghdr130={CFG_STR_UTF8,"Bookmark 15 icon",3,127};
__root const char BM15PIC_ID[128]="";
__root const CFG_HDR cfghdr131={CFG_STR_WIN1251,"Bookmark 15 name",1,31};
__root const char BM15NAME[32]="";
