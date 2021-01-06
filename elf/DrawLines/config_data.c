#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

//root
__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"Enable hello message",0,2};
__root const int ENA_HELLO_MSG=1;

__root const CFG_HDR cfghdr1 = {CFG_CBOX, "Show In", 0, 3};
__root const int cfgShowIn = 2;
__root const CFG_CBOX_ITEM cfgcbox1[3] = {"Lock", "Unlock", "Both"};

// 1
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"1",1,0};

__root const CFG_HDR cfghdr_1_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos1={0,0,0,0};

__root const CFG_HDR cfghdr_1_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color1[4]={0,255,0,50};

__root const CFG_HDR cfghdr_1_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv1[4]={0,255,0,64};

__root const CFG_HDR cfghdr1_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round1=5;

__root const CFG_HDR cfghdr1_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round1=5;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

// 2
__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"2",1,0};

__root const CFG_HDR cfghdr_2_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos2={0,0,0,0};

__root const CFG_HDR cfghdr_2_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color2[4]={0,255,0,50};

__root const CFG_HDR cfghdr_2_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv2[4]={0,255,0,50};

__root const CFG_HDR cfghdr2_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round2=5;

__root const CFG_HDR cfghdr2_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round2=5;

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

// 3
__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"3",1,0};

__root const CFG_HDR cfghdr_3_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos3={0,0,0,0};

__root const CFG_HDR cfghdr_3_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color3[4]={0,255,0,50};

__root const CFG_HDR cfghdr_3_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv3[4]={0,255,0,50};

__root const CFG_HDR cfghdr3_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round3=5;

__root const CFG_HDR cfghdr3_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round3=5;

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

// 4
__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"4",1,0};

__root const CFG_HDR cfghdr_4_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos4={0,0,0,0};

__root const CFG_HDR cfghdr_4_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color4[4]={0,255,0,50};

__root const CFG_HDR cfghdr_4_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv4[4]={0,255,0,50};

__root const CFG_HDR cfghdr4_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round4=5;

__root const CFG_HDR cfghdr4_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round4=5;

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

// 5
__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"5",1,0};

__root const CFG_HDR cfghdr_5_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos5={0,0,0,0};

__root const CFG_HDR cfghdr_5_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color5[4]={0,255,0,50};

__root const CFG_HDR cfghdr_5_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv5[4]={0,255,0,50};

__root const CFG_HDR cfghdr5_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round5=5;

__root const CFG_HDR cfghdr5_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round5=5;

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

// 6
__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"6",1,0};

__root const CFG_HDR cfghdr_6_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos6={0,0,0,0};

__root const CFG_HDR cfghdr_6_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color6[4]={0,255,0,50};

__root const CFG_HDR cfghdr_6_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv6[4]={0,255,0,50};

__root const CFG_HDR cfghdr6_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round6=5;

__root const CFG_HDR cfghdr6_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round6=5;

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};

// 7
__root const CFG_HDR cfghdr_m71={CFG_LEVEL,"7",1,0};

__root const CFG_HDR cfghdr_7_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos7={0,0,0,0};

__root const CFG_HDR cfghdr_7_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color7[4]={0,255,0,50};

__root const CFG_HDR cfghdr_7_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv7[4]={0,255,0,50};

__root const CFG_HDR cfghdr7_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round7=5;

__root const CFG_HDR cfghdr7_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round7=5;

__root const CFG_HDR cfghdr_m70={CFG_LEVEL,"",0,0};

// 8
__root const CFG_HDR cfghdr_m81={CFG_LEVEL,"8",1,0};

__root const CFG_HDR cfghdr_8_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos8={0,0,0,0};

__root const CFG_HDR cfghdr_8_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color8[4]={0,255,0,50};

__root const CFG_HDR cfghdr_8_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv8[4]={0,255,0,50};

__root const CFG_HDR cfghdr8_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round8=5;

__root const CFG_HDR cfghdr8_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round8=5;

__root const CFG_HDR cfghdr_m80={CFG_LEVEL,"",0,0};

// 9
__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"9",1,0};

__root const CFG_HDR cfghdr_9_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos9={0,0,0,0};

__root const CFG_HDR cfghdr_9_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color9[4]={0,255,0,50};

__root const CFG_HDR cfghdr_9_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv9[4]={0,255,0,50};

__root const CFG_HDR cfghdr9_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round9=5;

__root const CFG_HDR cfghdr9_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round9=5;

__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};

// 10
__root const CFG_HDR cfghdr_m101={CFG_LEVEL,"10",1,0};

__root const CFG_HDR cfghdr_10_1 = {CFG_RECT, "Позиция", 0, 0};
__root const RECT pos10={0,0,0,0};

__root const CFG_HDR cfghdr_10_2 = {CFG_COLOR, "Цвет", 0, 0};
__root const char color10[4]={0,255,0,50};

__root const CFG_HDR cfghdr_10_3={CFG_COLOR,"Цвет обводки",0,0};
__root const char color_obv10[4]={0,255,0,50};

__root const CFG_HDR cfghdr10_4={CFG_UINT,"Округл.угла х",0,0xFFFFFFFF};
__root const unsigned int x_round10=5;

__root const CFG_HDR cfghdr10_5={CFG_UINT,"Округл.угла y",0,0xFFFFFFFF};
__root const unsigned int y_round10=5;

__root const CFG_HDR cfghdr_m100={CFG_LEVEL,"",0,0};
