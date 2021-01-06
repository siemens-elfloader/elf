#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0 = {CFG_CBOX, "Show in", 0, 3};
__root const int cfgShowIn = 0;
__root const CFG_CBOX_ITEM cfgcbox1[3] = {"Both", "Lock", "Unlock"};

__root const CFG_HDR cfghdr0i={CFG_STR_UTF8,"Pictures path",0,63};
__root const char PIC_PATH[64]=DEFAULT_DISK ":\\ZBin\\DiskMon";

__root const CFG_HDR cfghdr_m0={CFG_LEVEL,"Disk 0:",1,0};

__root const CFG_HDR cfghdr0_1 = {CFG_CHECKBOX, "Show", 0, 2};
__root const int cfgShow0 = 1;

__root const CFG_HDR cfghdr0_7={CFG_COORDINATES,"Picture pos",0,0};
__root const unsigned int PicX0=8;
__root const unsigned int PicY0=55;

__root const CFG_HDR cfghdr0_2={CFG_RECT, "Position", 0, 0};
__root const RECT cfgRect0 = {2, 65, 21, 100};

__root const CFG_HDR cfghdr0_3 = {CFG_CBOX, "Orientation", 0, 2};
__root const int cfgOrient0 = 1;
__root const CFG_CBOX_ITEM cfgcbox0_4[2] = {"Horizontal", "Vertical"};

__root const CFG_HDR cfghdr0_4={CFG_COLOR,"Border Color",0,0};
__root const char cfgBorderCol0[4]={0,0,0,100};

__root const CFG_HDR cfghdr0_5={CFG_COLOR,"Back Color",0,0};
__root const char cfgBGCol0[4]={0xFF,0xFF,0xFF,100};

__root const CFG_HDR cfghdr0_6={CFG_COLOR,"Fill Color",0,0};
__root const char cfgFillCol0[4]={0xFF,0xFF,0,100};

__root const CFG_HDR cfghdr_m01={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m1={CFG_LEVEL,"Disk 1:",1,0};

__root const CFG_HDR cfghdr1_1 = {CFG_CHECKBOX, "Show", 0, 2};
__root const int cfgShow1 = 1;

__root const CFG_HDR cfghdr1_7={CFG_COORDINATES,"Picture pos",0,0};
__root const unsigned int PicX1=31;
__root const unsigned int PicY1=55;

__root const CFG_HDR cfghdr1_2={CFG_RECT, "Position", 0, 0};
__root const RECT cfgRect1 = {25, 65, 44, 100};

__root const CFG_HDR cfghdr1_3 = {CFG_CBOX, "Orientation", 0, 2};
__root const int cfgOrient1 = 1;
__root const CFG_CBOX_ITEM cfgcbox1_4[2] = {"Horizontal", "Vertical"};

__root const CFG_HDR cfghdr1_4={CFG_COLOR,"Border Color",0,0};
__root const char cfgBorderCol1[4]={0,0,0,100};

__root const CFG_HDR cfghdr1_5={CFG_COLOR,"Back Color",0,0};
__root const char cfgBGCol1[4]={0xFF,0xFF,0xFF,100};

__root const CFG_HDR cfghdr1_6={CFG_COLOR,"Fill Color",0,0};
__root const char cfgFillCol1[4]={0xFF,0xFF,0,100};

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m2={CFG_LEVEL,"Disk 2:",1,0};

__root const CFG_HDR cfghdr2_1 = {CFG_CHECKBOX, "Show", 0, 2};
__root const int cfgShow2 = 1;

__root const CFG_HDR cfghdr2_7={CFG_COORDINATES,"Picture pos",0,0};
__root const unsigned int PicX2=54;
__root const unsigned int PicY2=55;

__root const CFG_HDR cfghdr2_2={CFG_RECT, "Position", 0, 0};
__root const RECT cfgRect2 = {48, 65, 67, 100};

__root const CFG_HDR cfghdr2_3 = {CFG_CBOX, "Orientation", 0, 2};
__root const int cfgOrient2 = 1;
__root const CFG_CBOX_ITEM cfgcbox2_4[2] = {"Horizontal", "Vertical"};

__root const CFG_HDR cfghdr2_4={CFG_COLOR,"Border Color",0,0};
__root const char cfgBorderCol2[4]={0,0,0,100};

__root const CFG_HDR cfghdr2_5={CFG_COLOR,"Back Color",0,0};
__root const char cfgBGCol2[4]={0xFF,0xFF,0xFF,100};

__root const CFG_HDR cfghdr2_6={CFG_COLOR,"Fill Color",0,0};
__root const char cfgFillCol2[4]={0xFF,0xFF,0,100};

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"Disk 4:",1,0};

__root const CFG_HDR cfghdr4_1 = {CFG_CHECKBOX, "Show", 0, 2};
__root const int cfgShow4 = 0;

__root const CFG_HDR cfghdr4_7={CFG_COORDINATES,"Picture pos",0,0};
__root const unsigned int PicX4=77;
__root const unsigned int PicY4=55;

__root const CFG_HDR cfghdr4_2={CFG_RECT, "Position", 0, 0};
__root const RECT cfgRect4 = {71, 65, 90, 100};

__root const CFG_HDR cfghdr4_3 = {CFG_CBOX, "Orientation", 0, 2};
__root const int cfgOrient4 = 1;
__root const CFG_CBOX_ITEM cfgcbox4_4[2] = {"Horizontal", "Vertical"};

__root const CFG_HDR cfghdr4_4={CFG_COLOR,"Border Color",0,0};
__root const char cfgBorderCol4[4]={0,0,0,100};

__root const CFG_HDR cfghdr4_5={CFG_COLOR,"Back Color",0,0};
__root const char cfgBGCol4[4]={0xFF,0xFF,0xFF,100};

__root const CFG_HDR cfghdr4_6={CFG_COLOR,"Fill Color",0,0};
__root const char cfgFillCol4[4]={0xFF,0xFF,0,100};

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"",0,0};
