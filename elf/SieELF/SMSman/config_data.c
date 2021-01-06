#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"



 __root const CFG_HDR cfghdr0 = {CFG_STR_UTF8,"SMS.dat路径",0,127};
 __root const char SMS_DAT_PATH[128]="0:\\system\\sms\\sms.dat";
	
 __root const CFG_HDR cfghdr1={CFG_CHECKBOX,"显示待机文字",0,0};
 __root const int SHOW_IDLE = 1;

 __root const CFG_HDR cfghdr_m02={CFG_LEVEL,"待机文字",1,0};
	 __root const CFG_HDR cfghdr00_0 = {CFG_STR_GB,"文字",0,127};
	 __root const char IDLETXT[128]="%d条新短信";
	 
	 __root const CFG_HDR cfghdr00_1={CFG_COORDINATES,"位置",0,0};
	 __root const unsigned int IDLE_X=10;
	 __root const unsigned int IDLE_Y=95;
 
	 __root const CFG_HDR cfghdr00_2={CFG_UINT,"字体",0,12};
	 __root const unsigned int IDLE_FNT=FONT_SMALL_BOLD;
	 
	 __root const CFG_HDR cfghdr00_3={CFG_CHECKBOX,"显示当0个新消息",0,0};
	 __root const int show0new = 0;
 __root const CFG_HDR cfghdr_m03={CFG_LEVEL,"",0,0};

//  __root const CFG_HDR cfghdr0 = {CFG_RECT, "Text Area", 0, 0};
//  __root const RECT cfgArea = {0,67,131,93};
 
 __root const CFG_HDR cfghdr2={CFG_CHECKBOX,"新消息通知",0,0};
 __root const int IN_NOTIFY = 1;

 __root const CFG_HDR cfghdr3 = {CFG_STR_UTF8,"提示音",0,127};
 __root const char InSMSSound[128]="2:\\Default\\MessageMelody.aac";
 
 
__root const CFG_HDR cfghdr_m000={CFG_LEVEL,"情景模式",1,0};

 __root const CFG_HDR cfghdr_m00={CFG_LEVEL,"情景模式1",1,0};
	 __root const CFG_HDR cfghdr0_1={CFG_CHECKBOX,"震动模式",0,0};
	 __root const int VIBR_1 = 1;
 
	 __root const CFG_HDR cfghdr0_2={CFG_UINT,"震动强度",0,100};
	 __root const unsigned int V_P_1=100;
 
	 __root const CFG_HDR cfghdr0_3={CFG_UINT,"震动次数",0,256};
	 __root const unsigned int V_C_1=60;
	 
	 __root const CFG_HDR cfghdr0_4={CFG_CHECKBOX,"提示音",0,0};
	 __root const int SOUND_1 = 1;
 
	 __root const CFG_HDR cfghdr0_5={CFG_UINT,"提示音量",0,24};
	 __root const unsigned int S_VOL_1=6;
 __root const CFG_HDR cfghdr_m01={CFG_LEVEL,"",0,0};

 //======================
 
 __root const CFG_HDR cfghdr_m10={CFG_LEVEL,"情景模式2",1,0};
	 __root const CFG_HDR cfghdr1_1={CFG_CHECKBOX,"震动模式",0,0};
	 __root const int VIBR_2 = 1;
 
	 __root const CFG_HDR cfghdr1_2={CFG_UINT,"震动强度",0,100};
	 __root const unsigned int V_P_2=100;
 
	 __root const CFG_HDR cfghdr1_3={CFG_UINT,"震动次数",0,256};
	 __root const unsigned int V_C_2=30;
	 
	 __root const CFG_HDR cfghdr1_4={CFG_CHECKBOX,"提示音",0,0};
	 __root const int SOUND_2 = 0;
 
	 __root const CFG_HDR cfghdr1_5={CFG_UINT,"提示音量",0,24};
	 __root const unsigned int S_VOL_2=6;
 __root const CFG_HDR cfghdr_m11={CFG_LEVEL,"",0,0};

 //======================
 
 __root const CFG_HDR cfghdr_m20={CFG_LEVEL,"情景模式3",1,0};
	 __root const CFG_HDR cfghdr2_0={CFG_CHECKBOX,"震动模式",0,0};
	 __root const int VIBR_3 = 0;
 
	 __root const CFG_HDR cfghdr2_2={CFG_UINT,"震动强度",0,100};
	 __root const unsigned int V_P_3=100;
 
	 __root const CFG_HDR cfghdr2_3={CFG_UINT,"震动次数",0,256};
	 __root const unsigned int V_C_3=60;
	 
	 __root const CFG_HDR cfghdr2_4={CFG_CHECKBOX,"提示音",0,0};
	 __root const int SOUND_3 = 0;
 
	 __root const CFG_HDR cfghdr2_5={CFG_UINT,"提示音量",0,24};
	 __root const unsigned int S_VOL_3=6;
 __root const CFG_HDR cfghdr_m21={CFG_LEVEL,"",0,0};

 //======================
 
 __root const CFG_HDR cfghdr_m30={CFG_LEVEL,"情景模式4",1,0};
	 __root const CFG_HDR cfghdr3_1={CFG_CHECKBOX,"震动模式",0,0};
	 __root const int VIBR_4 = 0;
 
	 __root const CFG_HDR cfghdr3_2={CFG_UINT,"震动强度",0,100};
	 __root const unsigned int V_P_4=100;
 
	 __root const CFG_HDR cfghdr3_3={CFG_UINT,"震动次数",0,256};
	 __root const unsigned int V_C_4=60;
	 
	 __root const CFG_HDR cfghdr3_4={CFG_CHECKBOX,"提示音",0,0};
	 __root const int SOUND_4 = 0;
 
	 __root const CFG_HDR cfghdr3_5={CFG_UINT,"提示音量",0,24};
	 __root const unsigned int S_VOL_4=6;
 __root const CFG_HDR cfghdr_m31={CFG_LEVEL,"",0,0};

 //======================
 
 __root const CFG_HDR cfghdr_m40={CFG_LEVEL,"情景模式5",1,0};
	 __root const CFG_HDR cfghdr4_1={CFG_CHECKBOX,"震动模式",0,0};
	 __root const int VIBR_5 = 0;
 
	 __root const CFG_HDR cfghdr4_2={CFG_UINT,"震动强度",0,100};
	 __root const unsigned int V_P_5=100;
 
	 __root const CFG_HDR cfghdr4_3={CFG_UINT,"震动次数",0,256};
	 __root const unsigned int V_C_5=60;
	 
	 __root const CFG_HDR cfghdr4_4={CFG_CHECKBOX,"提示音",0,0};
	 __root const int SOUND_5 = 0;
 
	 __root const CFG_HDR cfghdr4_5={CFG_UINT,"提示音量",0,24};
	 __root const unsigned int S_VOL_5=6;
 __root const CFG_HDR cfghdr_m41={CFG_LEVEL,"",0,0};

 //======================
 
 __root const CFG_HDR cfghdr_m50={CFG_LEVEL,"情景模式6",1,0};
	 __root const CFG_HDR cfghdr5_1={CFG_CHECKBOX,"震动模式",0,0};
	 __root const int VIBR_6 = 0;
 
	 __root const CFG_HDR cfghdr5_2={CFG_UINT,"震动强度",0,100};
	 __root const unsigned int V_P_6=100;
 
	 __root const CFG_HDR cfghdr5_3={CFG_UINT,"震动次数",0,256};
	 __root const unsigned int V_C_6=60;
	 
	 __root const CFG_HDR cfghdr5_4={CFG_CHECKBOX,"提示音",0,0};
	 __root const int SOUND_6 = 0;
 
	 __root const CFG_HDR cfghdr5_5={CFG_UINT,"提示音量",0,24};
	 __root const unsigned int S_VOL_6=6;
 __root const CFG_HDR cfghdr_m51={CFG_LEVEL,"",0,0};

 //======================
 
 __root const CFG_HDR cfghdr_m60={CFG_LEVEL,"情景模式7",1,0};
	 __root const CFG_HDR cfghdr6_1={CFG_CHECKBOX,"震动模式",0,0};
	 __root const int VIBR_7 = 0;
 
	 __root const CFG_HDR cfghdr6_2={CFG_UINT,"震动强度",0,100};
	 __root const unsigned int V_P_7=100;
 
	 __root const CFG_HDR cfghdr6_3={CFG_UINT,"震动次数",0,256};
	 __root const unsigned int V_C_7=60;
	 
	 __root const CFG_HDR cfghdr6_4={CFG_CHECKBOX,"提示音",0,0};
	 __root const int SOUND_7 = 0;
 
	 __root const CFG_HDR cfghdr6_5={CFG_UINT,"提示音量",0,24};
	 __root const unsigned int S_VOL_7=6;
 __root const CFG_HDR cfghdr_m61={CFG_LEVEL,"",0,0};

 //======================
 
 __root const CFG_HDR cfghdr_m70={CFG_LEVEL,"情景模式8",1,0};
	 __root const CFG_HDR cfghdr7_1={CFG_CHECKBOX,"震动模式",0,0};
	 __root const int VIBR_8 = 0;
 
	 __root const CFG_HDR cfghdr7_2={CFG_UINT,"震动强度",0,100};
	 __root const unsigned int V_P_8=100;
 
	 __root const CFG_HDR cfghdr7_3={CFG_UINT,"震动次数",0,256};
	 __root const unsigned int V_C_8=60;
	 
	 __root const CFG_HDR cfghdr7_4={CFG_CHECKBOX,"提示音",0,0};
	 __root const int SOUND_8 = 0;
 
	 __root const CFG_HDR cfghdr7_5={CFG_UINT,"提示音量",0,24};
	 __root const unsigned int S_VOL_8=6;
 __root const CFG_HDR cfghdr_m71={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m001={CFG_LEVEL,"",0,0};
