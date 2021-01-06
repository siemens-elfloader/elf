#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

__root const CFG_HDR cfghdr0={CFG_UINT,"选择按键",0,100};
__root const unsigned int CALL_BTN=UP_BUTTON;

__root const CFG_HDR cfghdr1_1={CFG_CHECKBOX,"启用",0,2};
__root const int active=1;

__root const CFG_HDR cfghdr1={CFG_CBOX,"标签个数",0,15};
__root const int count=14;
__root const CFG_CBOX_ITEM cfgcbox2[15]={"1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};

////////////
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"标签1",1,0};

__root const CFG_HDR cfghdr11_1={CFG_CBOX,"类型",0,3};
__root const int type1=1;
__root const CFG_CBOX_ITEM cfgcbox4[3]={"文件","捷径","地址"};


__root const CFG_HDR cfghdr2_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic1[128]="1183";

__root const CFG_HDR cfghdr2_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file1[128]="ELSE_DEVELP_MNU";

__root const CFG_HDR cfghdr2_3={7,"坐标",0,0};
__root const unsigned int x1=1;
__root const unsigned int y1=15;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};
/////////////////

__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"标签2",1,0};

__root const CFG_HDR cfghdr12_1={CFG_CBOX,"类型",0,3};
__root const int type2=0;
__root const CFG_CBOX_ITEM cfgcbox5[3]={"文件","捷径","地址"};


__root const CFG_HDR cfghdr3_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic2[128]="833";

__root const CFG_HDR cfghdr3_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file2[128]=DEFAULT_DISK ":\\ZBin\\utilities\\CfgEdit.elf";

__root const CFG_HDR cfghdr3_3={7,"坐标",0,0};
__root const unsigned int x2=1;
__root const unsigned int y2=30;

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};
///////////////////
__root const CFG_HDR cfghdr_m16={CFG_LEVEL,"标签3",1,0};

__root const CFG_HDR cfghdr13_1={CFG_CBOX,"类型",0,3};
__root const int type3=1;
__root const CFG_CBOX_ITEM cfgcbox6[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr4_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic3[128]="681";

__root const CFG_HDR cfghdr4_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file3[128]="STUP_SILENTALER";

__root const CFG_HDR cfghdr4_3={7,"坐标",0,0};
__root const unsigned int x3=1;
__root const unsigned int y3=45;

__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"",0,0};
////////////////
__root const CFG_HDR cfghdr_m18={CFG_LEVEL,"标签4",1,0};

__root const CFG_HDR cfghdr14_1={CFG_CBOX,"类型",0,3};
__root const int type4=1;
__root const CFG_CBOX_ITEM cfgcbox7[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr5_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic4[128]="940";

__root const CFG_HDR cfghdr5_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file4[128]="FLSH_FLEXDINBOX";

__root const CFG_HDR cfghdr5_3={7,"坐标",0,0};
__root const unsigned int x4=1;
__root const unsigned int y4=60;

__root const CFG_HDR cfghdr_m17={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"标签5",1,0};

__root const CFG_HDR cfghdr15_1={CFG_CBOX,"类型",0,3};
__root const int type5=1;
__root const CFG_CBOX_ITEM cfgcbox8[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr6_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic5[128]="948";

__root const CFG_HDR cfghdr6_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file5[128]="STUP_CTIME_DATE";

__root const CFG_HDR cfghdr6_3={7,"坐标",0,0};
__root const unsigned int x5=1;
__root const unsigned int y5=75;

__root const CFG_HDR cfghdr_m19={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m22={CFG_LEVEL,"标签6",1,0};


__root const CFG_HDR cfghdr16_1={CFG_CBOX,"类型",0,3};
__root const int type6=1;
__root const CFG_CBOX_ITEM cfgcbox9[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr7_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic6[128]="938";

__root const CFG_HDR cfghdr7_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file6[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr7_3={7,"坐标",0,0};
__root const unsigned int x6=1;
__root const unsigned int y6=90;

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};
/////////
__root const CFG_HDR cfghdr_m26={CFG_LEVEL,"标签7",1,0};


__root const CFG_HDR cfghdr17_1={CFG_CBOX,"类型",0,3};
__root const int type7=1;
__root const CFG_CBOX_ITEM cfgcbox10[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr8_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic7[128]="679";

__root const CFG_HDR cfghdr8_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file7[128]="STUP_CONCT_IRDA";

__root const CFG_HDR cfghdr8_3={7,"坐标",0,0};
__root const unsigned int x7=116;
__root const unsigned int y7=15;

__root const CFG_HDR cfghdr_m25={CFG_LEVEL,"",0,0};

/////////////
__root const CFG_HDR cfghdr_m28={CFG_LEVEL,"标签8",1,0};


__root const CFG_HDR cfghdr18_1={CFG_CBOX,"类型",0,3};
__root const int type8=1;
__root const CFG_CBOX_ITEM cfgcbox11[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr9_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic8[128]="659";

__root const CFG_HDR cfghdr9_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file8[128]="STUP_CONCT_BLUE";

__root const CFG_HDR cfghdr9_3={7,"坐标",0,0};
__root const unsigned int x8=116;
__root const unsigned int y8=30;

__root const CFG_HDR cfghdr_m27={CFG_LEVEL,"",0,0};

/////////
__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"标签9",1,0};


__root const CFG_HDR cfghdr19_1={CFG_CBOX,"类型",0,3};
__root const int type9=1;
__root const CFG_CBOX_ITEM cfgcbox12[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr10_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic9[128]="686";

__root const CFG_HDR cfghdr10_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file9[128]="STUP_CONCT_GPRS";

__root const CFG_HDR cfghdr10_3={7,"坐标",0,0};
__root const unsigned int x9=115;
__root const unsigned int y9=45;

__root const CFG_HDR cfghdr_m29={CFG_LEVEL,"",0,0};


///////
__root const CFG_HDR cfghdr_m32={CFG_LEVEL,"标签10",1,0};


__root const CFG_HDR cfghdr20_1={CFG_CBOX,"类型",0,3};
__root const int type10=1;
__root const CFG_CBOX_ITEM cfgcbox13[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr21_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic10[128]="839";

__root const CFG_HDR cfghdr21_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file10[128]="MESG_CREATE_NEW";

__root const CFG_HDR cfghdr21_3={7,"坐标",0,0};
__root const unsigned int x10=116;
__root const unsigned int y10=60;

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"",0,0};
////////

__root const CFG_HDR cfghdr_m34={CFG_LEVEL,"标签11",1,0};


__root const CFG_HDR cfghdr22_5={CFG_CBOX,"类型",0,3};
__root const int type11=1;
__root const CFG_CBOX_ITEM cfgcbox14[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr22_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic11[128]="867";

__root const CFG_HDR cfghdr22_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file11[128]="MESG_SMSARCHIVE";

__root const CFG_HDR cfghdr22_3={7,"坐标",0,0};
__root const unsigned int x11=116;
__root const unsigned int y11=75;

__root const CFG_HDR cfghdr_m33={CFG_LEVEL,"",0,0};

////////
__root const CFG_HDR cfghdr_m36={CFG_LEVEL,"标签12",1,0};


__root const CFG_HDR cfghdr23_5={CFG_CBOX,"类型",0,3};
__root const int type12=1;
__root const CFG_CBOX_ITEM cfgcbox15[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr23_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic12[128]="913";

__root const CFG_HDR cfghdr23_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file12[128]="MESG_CHG_SETTGS";

__root const CFG_HDR cfghdr23_3={7,"坐标",0,0};
__root const unsigned int x12=116;
__root const unsigned int y12=90;

__root const CFG_HDR cfghdr_m35={CFG_LEVEL,"",0,0};
////////
__root const CFG_HDR cfghdr_m38={CFG_LEVEL,"标签13",1,0};


__root const CFG_HDR cfghdr24_5={CFG_CBOX,"类型",0,3};
__root const int type13=1;
__root const CFG_CBOX_ITEM cfgcbox16[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr24_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic13[128]=DEFAULT_DISK ":\\ZBin\\img\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr24_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file13[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr24_3={7,"坐标",0,0};
__root const unsigned int x13=40;
__root const unsigned int y13=15;

__root const CFG_HDR cfghdr_m37={CFG_LEVEL,"",0,0};

///////
__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"标签14",1,0};


__root const CFG_HDR cfghdr25_5={CFG_CBOX,"类型",0,3};
__root const int type14=1;
__root const CFG_CBOX_ITEM cfgcbox17[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr25_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic14[128]=DEFAULT_DISK ":\\ZBin\\img\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr25_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file14[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr25_3={7,"坐标",0,0};
__root const unsigned int x14=60;
__root const unsigned int y14=15;

__root const CFG_HDR cfghdr_m39={CFG_LEVEL,"",0,0};
///////////
__root const CFG_HDR cfghdr_m42={CFG_LEVEL,"标签15",1,0};


__root const CFG_HDR cfghdr26_5={CFG_CBOX,"类型",0,3};
__root const int type15=1;
__root const CFG_CBOX_ITEM cfgcbox18[3]={"文件","捷径","地址"};

__root const CFG_HDR cfghdr26_1={CFG_STR_UTF8,"图标",0,127};
__root const char pic15[128]=DEFAULT_DISK ":\\ZBin\\img\\IdleLinks\\bud.png";

__root const CFG_HDR cfghdr26_2={CFG_STR_UTF8,"文件/捷径/地址",0,127};
__root const char file15[128]="ELSE_ALARMCLOCK";

__root const CFG_HDR cfghdr26_3={7,"坐标",0,0};
__root const unsigned int x15=80;
__root const unsigned int y15=15;

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"",0,0};

/////
__root const CFG_HDR cfghdr_m24={CFG_LEVEL,"选项设置",1,0};
__root const CFG_HDR cfghdr8={CFG_CBOX,"选项",0,2};
__root const int vybor=1;
__root const CFG_CBOX_ITEM cfgcbox3[2]={"颜色","图片"};

__root const CFG_HDR cfghdr51={CFG_STR_UTF8,"图片",0,127};
__root const char chpic[128]=DEFAULT_DISK ":\\ZBin\\img\\IdleLinks\\choose.png";

__root const CFG_HDR cfghdr121={8,"选项颜色",0,0};
__root const char cl[4]={255,255,0,100};

__root const CFG_HDR cfghdr122={8,"边框颜色",0,0};
__root const char frcol[4]={0,0,255,100};

__root const CFG_HDR cfghdr_m23={CFG_LEVEL,"",0,0};





/////
  /*
  0-Left_SOFT
  1-Right_soft
  2-up
  3-down
  4-left
  5-right
  6-vol up
  7-vol down
  */
