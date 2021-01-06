#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"
#include "TextInfo.h"
//Конфигурация

__root const CFG_HDR cfghdr0={CFG_UINT,"Refresh period, 1/10 sec",0,600};
__root const unsigned int REFRESH=20;

__root const CFG_HDR cfghdr0_0 = {CFG_CBOX, "Show In", 0, 3};
__root const int cfgShowIn = 2;
__root const CFG_CBOX_ITEM cfgcbox1_0[3] = {"Lock", "Unlock", "Both"};

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"Net setup",1,0};

__root const CFG_HDR cfghdr1_1 = {CFG_CBOX, "Net display", 0, 2};
__root const int NET_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox1[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr1_2={CFG_COORDINATES,"Net position",0,0};
__root const unsigned int NET_X=0;
__root const unsigned int NET_Y=20;

__root const CFG_HDR cfghdr1_3={CFG_COLOR,"Net color",0,0};
__root const char NET_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr1_4={CFG_UINT,"Net font",0,65535};
__root const unsigned int NET_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr1_5 = {CFG_CBOX, "Net fringing", 0, 2};
__root const int NET_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox13[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr1_6={CFG_COLOR,"Net fringing color",0,0};
__root const char NET_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr1_7={CFG_STR_WIN1251,"Net string format",0,15};
__root const char NET_FMT[16]="%c%ddB";

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //

__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"Temperature setup",1,0};

__root const CFG_HDR cfghdr2_1 = {CFG_CBOX, "Temperature display", 0, 2};
__root const int TEMP_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox2[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr2_2={CFG_COORDINATES,"Temperature position",0,0};
__root const unsigned int TEMP_X=36;
__root const unsigned int TEMP_Y=20;

__root const CFG_HDR cfghdr2_3={CFG_COLOR,"Temperature color",0,0};
__root const char TEMP_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr2_4={CFG_UINT,"Temperature font",0,65535};
__root const unsigned int TEMP_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr2_5 = {CFG_CBOX, "Temperature fringing", 0, 2};
__root const int TEMP_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox14[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr2_6={CFG_COLOR,"Temperature fringing color",0,0};
__root const char TEMP_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr2_7={CFG_STR_WIN1251,"Temp string format",0,15};
__root const char TEMP_FMT[16]="%d,%d°C";

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"Voltage setup",1,0};

__root const CFG_HDR cfghdr3_1 = {CFG_CBOX, "Voltage display", 0, 2};
__root const int VOLT_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox3[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr3_2={CFG_COORDINATES,"Voltage position",0,0};
__root const unsigned int VOLT_X=77;
__root const unsigned int VOLT_Y=20;

__root const CFG_HDR cfghdr3_3={CFG_COLOR,"Voltage color",0,0};
__root const char VOLT_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr3_4={CFG_UINT,"Voltage font",0,65535};
__root const unsigned int VOLT_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr3_5 = {CFG_CBOX, "Voltage fringing", 0, 2};
__root const int VOLT_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox15[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr3_6={CFG_COLOR,"Voltage fringing color",0,0};
__root const char VOLT_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr3_7={CFG_STR_WIN1251,"Voltage string format",0,15};
__root const char VOLT_FMT[16]="%d,%02dV";

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //

__root const CFG_HDR cfghdr_m41={CFG_LEVEL,"AccuCap setup",1,0};

__root const CFG_HDR cfghdr4_1 = {CFG_CBOX, "AccuCap display", 0, 2};
__root const int CAP_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox4[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr4_2={CFG_COORDINATES,"AccuCap position",0,0};
__root const unsigned int ACCU_X=110;
__root const unsigned int ACCU_Y=20;

__root const CFG_HDR cfghdr4_3={CFG_COLOR,"AccuCap color",0,0};
__root const char ACCU_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr4_4={CFG_UINT,"AccuCap font",0,65535};
__root const unsigned int ACCU_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr4_5 = {CFG_CBOX, "AccuCap fringing", 0, 2};
__root const int ACCU_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox16[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr34_6={CFG_COLOR,"AccuCap fringing color",0,0};
__root const char ACCU_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr4_7={CFG_STR_WIN1251,"AccuCap string format",0,15};
__root const char CAP_FMT[16]="%02d%%";

__root const CFG_HDR cfghdr_m40={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //

__root const CFG_HDR cfghdr_m51={CFG_LEVEL,"GPRS Traff setup",1,0};

__root const CFG_HDR cfghdr5_1 = {CFG_CBOX, "GPRS Traff display", 0, 2};
__root const int GPRS_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox5[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr5_2={CFG_COORDINATES,"GPRS position",0,0};
__root const unsigned int GPRS_X=93;
__root const unsigned int GPRS_Y=145;

__root const CFG_HDR cfghdr5_3={CFG_COLOR,"GPRS color",0,0};
__root const char GPRS_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr5_4={CFG_UINT,"GPRS font",0,65535};
__root const unsigned int GPRS_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr5_5 = {CFG_CBOX, "GPRS fringing", 0, 2};
__root const int GPRS_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox17[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr5_6={CFG_COLOR,"GPRS fringing color",0,0};
__root const char GPRS_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr_m50={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //

__root const CFG_HDR cfghdr_m61={CFG_LEVEL,"AvailRAM setup",1,0};

__root const CFG_HDR cfghdr6_1 = {CFG_CBOX, "AvailRAM display", 0, 2};
__root const int RAM_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox6[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr6_2={CFG_COORDINATES,"AvailRam position",0,0};
__root const unsigned int RAM_X=51;
__root const unsigned int RAM_Y=145;

__root const CFG_HDR cfghdr6_3={CFG_COLOR,"AvailRam color",0,0};
__root const char RAM_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr6_4={CFG_UINT,"AvailRam font",0,65535};
__root const unsigned int RAM_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr6_5 = {CFG_CBOX, "AvailRam fringing", 0, 2};
__root const int RAM_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox18[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr6_6={CFG_COLOR,"AvailRam fringing color",0,0};
__root const char RAM_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr_m60={CFG_LEVEL,"",0,0};

// -------------------------------------------------------------------------- //

__root const CFG_HDR cfghdr_m71={CFG_LEVEL,"CPULoad setup",1,0};

__root const CFG_HDR cfghdr7_1 = {CFG_CBOX, "CPULoad display", 0, 2};
__root const int CPU_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox7[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr7_2={CFG_COORDINATES,"CPULoad position",0,0};
__root const unsigned int CPU_X=0;
__root const unsigned int CPU_Y=145;

__root const CFG_HDR cfghdr7_3={CFG_COLOR,"CPULoad color",0,0};
__root const char CPU_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr7_4={CFG_UINT,"CPULoad font",0,65535};
__root const unsigned int CPU_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr7_5 = {CFG_CBOX, "CPULoad fringing", 0, 2};
__root const int CPU_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox19[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr7_6={CFG_COLOR,"CPULoad fringing color",0,0};
__root const char CPU_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr7_7={CFG_STR_WIN1251,"CPULoad string format",0,15};
__root const char CPU_FMT[16]="%02d%%";

__root const CFG_HDR cfghdr_m70={CFG_LEVEL,"",0,0};

//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr_m81={CFG_LEVEL,"Traff string format setup",1,0};

__root const CFG_HDR cfghdr8_1={CFG_STR_WIN1251,"Bytes string format",0,15};
__root const char BYTES_FMT[16]="%u%s";

__root const CFG_HDR cfghdr8_2={CFG_STR_WIN1251,"Bytes sign",0,7};
__root const char BYTES_SG[8]="B";

__root const CFG_HDR cfghdr8_3={CFG_STR_WIN1251,"KiloBytes sign",0,7};
__root const char KBYTES_SG[8]="KB";

__root const CFG_HDR cfghdr_m80={CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m91={CFG_LEVEL,"Flex setup",1,0};
//------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m101={CFG_LEVEL,"Flex '0' setup",1,0};

__root const CFG_HDR cfghdr9_1 = {CFG_CBOX, "Flex '0' display", 0, 2};
__root const int FLEX0_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox9[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr9_11 = {CFG_CBOX, "Show KB or MB", 0, 2};
__root const int cfgMB0 = 0;
__root const CFG_CBOX_ITEM cfgcbox9_1[2] = {"Show KB", "Show MB"};

__root const CFG_HDR cfghdr9_5={CFG_STR_WIN1251,"Flex '0' string format",0,15};
__root const char FLEX0_FMT[16]="%d Kb";

__root const CFG_HDR cfghdr9_2={CFG_COORDINATES,"Flex '0' position",0,0};
__root const unsigned int FLEX0_X=3;
__root const unsigned int FLEX0_Y=95;

__root const CFG_HDR cfghdr9_3={CFG_COLOR,"Flex '0' color",0,0};
__root const char FLEX0_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr9_4={CFG_UINT,"Flex '0' font",0,65535};
__root const unsigned int FLEX0_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr9_6 = {CFG_CBOX, "Flex '0' fringing", 0, 2};
__root const int FLEX0_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox20[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr9_7={CFG_COLOR,"Flex '0' fringing color",0,0};
__root const char FLEX0_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr_m100={CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m111={CFG_LEVEL,"Flex '4' setup",1,0};

__root const CFG_HDR cfghdr10_1 = {CFG_CBOX, "Flex '4' display", 0, 2};
__root const int FLEX4_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox10[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr10_11 = {CFG_CBOX, "Show KB or MB", 0, 2};
__root const int cfgMB4 = 0;
__root const CFG_CBOX_ITEM cfgcbox101[2] = {"Show KB", "Show MB"};

__root const CFG_HDR cfghdr10_5={CFG_STR_WIN1251,"Flex '4' string format",0,15};
__root const char FLEX4_FMT[16]="%d Kb";

__root const CFG_HDR cfghdr10_2={CFG_COORDINATES,"Flex '4' position",0,0};
__root const unsigned int FLEX4_X=3;
__root const unsigned int FLEX4_Y=106;

__root const CFG_HDR cfghdr10_3={CFG_COLOR,"Flex '4' color",0,0};
__root const char FLEX4_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr10_4={CFG_UINT,"Flex '4' font",0,65535};
__root const unsigned int FLEX4_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr10_6 = {CFG_CBOX, "Flex '4' fringing", 0, 2};
__root const int FLEX4_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox21[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr10_7={CFG_COLOR,"Flex '4' fringing color",0,0};
__root const char FLEX4_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr_m110={CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m121={CFG_LEVEL,"Free % '0' setup",1,0};
//------------------------------------------------------------------------------

__root const CFG_HDR cfghdr11_1 = {CFG_CBOX, "Free % '0' display", 0, 2};
__root const int PER0_ENA = 1;
__root const CFG_CBOX_ITEM cfgcbox11[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr10_51={CFG_STR_WIN1251,"Free '0' string format",0,15};
__root const char PER0_FMT[16]="%d%";

__root const CFG_HDR cfghdr11_2={CFG_COORDINATES,"Free % '0' position",0,0};
__root const unsigned int PER0_X=3;
__root const unsigned int PER0_Y=118;

__root const CFG_HDR cfghdr11_3={CFG_COLOR,"Free % '0' color",0,0};
__root const char PER0_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr11_4={CFG_UINT,"Free '0' font",0,65535};
__root const unsigned int PER0_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr11_5 = {CFG_CBOX, "Free '0' fringing", 0, 2};
__root const int PER0_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox22[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr11_6={CFG_COLOR,"Free '0' fringing color",0,0};
__root const char PER0_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr_m120={CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m131={CFG_LEVEL,"Free % '4' setup",1,0};

__root const CFG_HDR cfghdr12_1 = {CFG_CBOX, "Free % '4' display", 0, 2};
__root const int PER4_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox12[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr12_51={CFG_STR_WIN1251,"Free '4' string format",0,15};
__root const char PER4_FMT[16]="%d%";

__root const CFG_HDR cfghdr12_2={CFG_COORDINATES,"Free % '4' position",0,0};
__root const unsigned int PER4_X=3;
__root const unsigned int PER4_Y=131;

__root const CFG_HDR cfghdr12_3={CFG_COLOR,"Free % '4' color",0,0};
__root const char PER4_COLORS[4]={255,255,255,100};

__root const CFG_HDR cfghdr12_4={CFG_UINT,"Free '4' font",0,65535};
__root const unsigned int PER4_FONT=FONT_SMALL;

__root const CFG_HDR cfghdr12_5 = {CFG_CBOX, "Free '4' fringing", 0, 2};
__root const int PER4_FRINGING_ENA = 0;
__root const CFG_CBOX_ITEM cfgcbox23[2] = {"No", "Yes"};

__root const CFG_HDR cfghdr12_6={CFG_COLOR,"Free '4' fringing color",0,0};
__root const char PER4_FRINGING_COLORS[4]={0,255,0,100};

__root const CFG_HDR cfghdr_m130={CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
__root const CFG_HDR cfghdr_m90={CFG_LEVEL,"",0,0};
//------------------------------------------------------------------------------
