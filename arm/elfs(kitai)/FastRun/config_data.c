#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_CBOX,"Display",0,4};
__root const int DRAW_MODE=0;
__root const CFG_CBOX_ITEM cfgcbox1[4]={"Left","Right","Top","Bottom"};

__root const CFG_HDR cfghdr2={CFG_STR_UTF8,"Path of 'FastRun'",0,63};
__root const char PATH[64]=DEFAULT_DISK":\\ZBin\\FastRun\\FastRun.elf";

__root const CFG_HDR cfghdr46={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr47={CFG_LEVEL,"Buttons",1,0};

__root const CFG_HDR cfghdr3={CFG_UINT,"Activation key",0,65535};
__root const unsigned int CALL_BUTTON=11;

__root const CFG_HDR cfghdr48={CFG_UINT,"Exit Key",0,65535};
__root const int EXIT_BUTTON=11;

__root const CFG_HDR cfghdr49={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr50={CFG_LEVEL,"Positioning",1,0};

__root const CFG_HDR cfghdr51={CFG_UINT,"Indent from the start screen",0,400};
__root const unsigned int BEGIN=0;

__root const CFG_HDR cfghdr52={CFG_UINT,"Distance between points",0,100};
__root const unsigned int OFFSET=2;

__root const CFG_HDR cfghdr53={CFG_UINT,"Bar length",0,400};
__root const unsigned int LEN=93;

__root const CFG_HDR cfghdr4={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr5={CFG_LEVEL,"Setup. Bookmarks",1,0};

__root const CFG_HDR cfghdr6={CFG_STR_UTF8,"File 1",3,127};
__root const char BM1FILE[128]="";
__root const CFG_HDR cfghdr7={CFG_STR_UTF8,"File 2 ",3,127};
__root const char BM2FILE[128]="";
__root const CFG_HDR cfghdr8={CFG_STR_UTF8,"file 3",3,127};
__root const char BM3FILE[128]="";
__root const CFG_HDR cfghdr9={CFG_STR_UTF8,"File 4",3,127};
__root const char BM4FILE[128]="";
__root const CFG_HDR cfghdr10={CFG_STR_UTF8,"File 5",3,127};
__root const char BM5FILE[128]="";
__root const CFG_HDR cfghdr11={CFG_STR_UTF8,"File 6",3,127};
__root const char BM6FILE[128]="";
__root const CFG_HDR cfghdr12={CFG_STR_UTF8,"File 7",3,127};
__root const char BM7FILE[128]="";
__root const CFG_HDR cfghdr13={CFG_STR_UTF8,"File 8",3,127};
__root const char BM8FILE[128]="";
__root const CFG_HDR cfghdr14={CFG_STR_UTF8,"File 9",3,127};
__root const char BM9FILE[128]="";
__root const CFG_HDR cfghdr15={CFG_STR_UTF8,"File 10",3,127};
__root const char BM10FILE[128]="";
__root const CFG_HDR cfghdr16={CFG_STR_UTF8,"File 11",3,127};
__root const char BM11FILE[128]="";
__root const CFG_HDR cfghdr17={CFG_STR_UTF8,"File 12",3,127};
__root const char BM12FILE[128]="";
__root const CFG_HDR cfghdr18={CFG_STR_UTF8,"File 13",3,127};
__root const char BM13FILE[128]="";
__root const CFG_HDR cfghdr19={CFG_STR_UTF8,"File 14",3,127};
__root const char BM14FILE[128]="";
__root const CFG_HDR cfghdr20={CFG_STR_UTF8,"File 15",3,127};
__root const char BM15FILE[128]="";

__root const CFG_HDR cfghdr21={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr22={CFG_LEVEL,"Setup. Icons",1,0};

__root const CFG_HDR cfghdr23={CFG_STR_UTF8,"Icon 1",3,127};
__root const char BM1PIC[128]="";
__root const CFG_HDR cfghdr24={CFG_STR_UTF8,"Icon 2",3,127};
__root const char BM2PIC[128]="";
__root const CFG_HDR cfghdr25={CFG_STR_UTF8,"Icon 3",3,127};
__root const char BM3PIC[128]="";
__root const CFG_HDR cfghdr26={CFG_STR_UTF8,"Icon 4",3,127};
__root const char BM4PIC[128]="";
__root const CFG_HDR cfghdr27={CFG_STR_UTF8,"Icon 5",3,127};
__root const char BM5PIC[128]="";
__root const CFG_HDR cfghdr28={CFG_STR_UTF8,"Icon 6",3,127};
__root const char BM6PIC[128]="";
__root const CFG_HDR cfghdr29={CFG_STR_UTF8,"Icon 7",3,127};
__root const char BM7PIC[128]="";
__root const CFG_HDR cfghdr30={CFG_STR_UTF8,"Icon 8",3,127};
__root const char BM8PIC[128]="";
__root const CFG_HDR cfghdr31={CFG_STR_UTF8,"Icon 9",3,127};
__root const char BM9PIC[128]="";
__root const CFG_HDR cfghdr32={CFG_STR_UTF8,"Icon 10",3,127};
__root const char BM10PIC[128]="";
__root const CFG_HDR cfghdr33={CFG_STR_UTF8,"Icon 11",3,127};
__root const char BM11PIC[128]="";
__root const CFG_HDR cfghdr34={CFG_STR_UTF8,"Icon 12",3,127};
__root const char BM12PIC[128]="";
__root const CFG_HDR cfghdr35={CFG_STR_UTF8,"Icon 13",3,127};
__root const char BM13PIC[128]="";
__root const CFG_HDR cfghdr36={CFG_STR_UTF8,"Icon 14",3,127};
__root const char BM14PIC[128]="";
__root const CFG_HDR cfghdr37={CFG_STR_UTF8,"Icon 15",3,127};
__root const char BM15PIC[128]="";
__root const CFG_HDR cfghdr38={CFG_STR_UTF8,"Icon 'X'",3,127};
__root const char BMXPIC[128]=DEFAULT_DISK":\\ZBin\\FastRun\\img\\no_icon.png";

__root const CFG_HDR cfghdr39={CFG_LEVEL,"",0,0};
__root const CFG_HDR cfghdr40={CFG_LEVEL,"Setup.Color",1,0};

__root const CFG_HDR cfghdr41={CFG_COLOR,"Bar Frame color",0,0};
__root const char cfgPanBorderCol[4]={255,255,255,100};

__root const CFG_HDR cfghdr42={CFG_COLOR,"Bar Background Color",0,0};
__root const char cfgPanBGCol[4]={255,255,255,20};

__root const CFG_HDR cfghdr43={CFG_COLOR,"Bookmark Frame Color",0,0};
__root const char cfgBookBorderCol[4]={255,255,255,100};

__root const CFG_HDR cfghdr44={CFG_COLOR,"Bookmark Backround Color",0,0};
__root const char cfgBookBGCol[4]={255,255,255,20};

__root const CFG_HDR cfghdr54={CFG_LEVEL,"",0,0};
__root const int SELECTED=0;

