#include "..\inc\cfg_items.h"
#include "..\inc\swilib.h"

/*
#ifdef NEWSGOLD
 #define DEFAULT_DISK "4"
#else
 #define DEFAULT_DISK "0"
#endif
*/

__root const CFG_HDR cfghdr_m5={CFG_LEVEL,"�������ܿ���",1,0};

__root const CFG_HDR cfghdr1_1 = {CFG_CHECKBOX,"������",0,0};
__root const int big_font=0;

__root const CFG_HDR cfghdr1_2 = {CFG_CHECKBOX,"���Ž�ֹ",0,0};
__root const int disable_when_calling=1;

__root const CFG_HDR cfghdr1_3 = {CFG_CHECKBOX,"�������",0,0};
__root const int cfg_disable_one_number=1;

__root const CFG_HDR cfghdr1_4 = {CFG_CHECKBOX,"��ʾ������",0,0};
__root const int cfg_cs_enable=1;

__root const CFG_HDR cfghdr1_5 = {CFG_CHECKBOX,"����������",0,0};
__root const int cfg_cs_part=0;

__root const CFG_HDR cfghdr10_6 = {CFG_CHECKBOX,"��ͷ����ʾ",0,0};
__root const int show_pic=0;

__root const CFG_HDR cfghdr1_7 = {CFG_CHECKBOX,"��ͷ������",0,0};
__root const int resampled=0;

#ifndef NEWSGOLD
__root const CFG_HDR cfghdr1_8 = {CFG_CHECKBOX,"Ĭ�϶��Ž���",0,0};
__root const int dewin=0;
#endif

__root const CFG_HDR cfghdr1_9 = {CFG_CHECKBOX,"���ź���",0,0};
__root const int smsn=1;

__root const CFG_HDR cfghdr1_10 = {CFG_CHECKBOX,"����������",0,0};
__root const int smsc=0;

__root const CFG_HDR cfghdr1_11 = {CFG_CHECKBOX,"������Ч",0,0};
__root const int voice=0;

__root const CFG_HDR cfghdr1_12 = {CFG_CBOX, "���Ⱥ���", 0, 5};
__root const int priority = 0;
__root const CFG_CBOX_ITEM cfgcbox1[5]={"�绰����","��˾����","�ƶ�����","�������","�������2"};

 
__root const CFG_HDR cfghdr_m4={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m15={CFG_LEVEL,"��Ļ�������",1,0};


__root const CFG_HDR cfghdr5_0 = {CFG_COORDINATES,"���ź�������",0,0};
__root const int startX = 6;
#ifdef ELKA
__root const int startY = 56;
#else
  #ifdef S68
__root const int startY = 38;
  #else
__root const int startY = 18;
  #endif
#endif
__root const CFG_HDR cfghdr5_1 = {CFG_UINT,"�������ͷ������ֵ",0,200};
__root const int startfix = 0;

__root const CFG_HDR cfghdr5_2 = {CFG_UINT,"�б�����ֵ",0,200};
__root const int startfix2 = 0;

__root const CFG_HDR cfghdr5_3 = {CFG_COLOR,"��������ɫ",0,99};
__root const int cfg_cs_font_color=2;

__root const CFG_HDR cfghdr5_4 = {CFG_COLOR,"�����㱳��",0,99};
__root const int CS_NUMBER_BG=6;

__root const CFG_HDR cfghdr5_5 = {CFG_CBOX,"�������ַѡ��",0,10};
 __root const int cfg_cs_adrs = 1;
 __root const CFG_CBOX_ITEM cfgcbox3[10]={"����","S65/CX65","SK65","C65/SL65","CX70","M65","C7C","CX7A","E71/EL71/M81/S68/SL75/S75","����"};

__root const CFG_HDR cfghdr5_6 = {CFG_UINT,"����������",0,0xFFFFFFFF};
__root const int cfg_cs_adr=0;

__root const CFG_HDR cfghdr_m14={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m3={CFG_LEVEL,"����ǰ׺ѡ��",1,0};

__root const CFG_HDR cfghdr11_11 = {CFG_CHECKBOX,"IP������չ",0,0};
__root const int ipx2=0;

__root const CFG_HDR cfghdr11_12 = {CFG_CHECKBOX,"IP���+00",0,0};
__root const int ip00=0;

__root const CFG_HDR cfghdr11_13 = {CFG_UINT,"����IP",0,0xFFFFFFFF};
__root const int cfg_ip_number1 = 17951;

__root const CFG_HDR cfghdr11_14 = {CFG_UINT,"���κ͹���IP",0,0xFFFFFFFF};
__root const int cfg_ip_number2 = 12593;

__root const CFG_HDR cfghdr11_15={CFG_UINT,"IP�����ȼ�",0,99};
#ifdef ELKA
__root const int ACTIVE_KEY=0x0E;
#else
#ifdef NEWSGOLD
__root const int ACTIVE_KEY=LEFT_SOFT;
#else
__root const int ACTIVE_KEY=RIGHT_SOFT;
#endif
#endif

__root const CFG_HDR cfghdr_m2={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m7={CFG_LEVEL,"ѡ�������ɫ",1,0};

__root const CFG_HDR cfghdr2_1={CFG_COLOR,"������ɫ",0,99};
__root const int COLOR_SELECTED=1;

__root const CFG_HDR cfghdr2_2={CFG_COLOR,"������ɫ",0,99};
__root const int COLOR_NUMBER=1;

__root const CFG_HDR cfghdr2_3={CFG_COLOR,"ѡ��������",0,99};
__root const int COLOR_SELECTED_BG=6;

__root const CFG_HDR cfghdr2_4={CFG_COLOR,"ѡ�����߿�",0,99};
__root const int COLOR_SELECTED_BRD=23;

__root const CFG_HDR cfghdr2_5={CFG_COLOR,"�����ʶ����",0,99};
__root const int COLOR_NUMBER_BG=23;

__root const CFG_HDR cfghdr2_6={CFG_COLOR,"�����ʶ�߿�",0,99};
__root const int COLOR_NUMBER_BRD=1;

__root const CFG_HDR cfghdr_m6={CFG_LEVEL,"",0,0};



__root const CFG_HDR cfghdr_m9={CFG_LEVEL,"�˵�������ɫ",1,0};

__root const CFG_HDR cfghdr3_0={CFG_COLOR,"�˵�����",0,99};
__root const int COLOR_MENU_BK=23;

__root const CFG_HDR cfghdr3_1={CFG_COLOR,"�˵��߿�",0,99};
__root const int COLOR_MENU_BRD=1;

__root const CFG_HDR cfghdr3_2={CFG_COLOR,"δѡ������",0,99};
__root const int COLOR_NOTSELECTED=0;

__root const CFG_HDR cfghdr3_3={CFG_COLOR,"��������ɫ",0,99};
__root const int COLOR_SCROLLBAR=0;  

__root const CFG_HDR cfghdr3_4={CFG_COLOR,"����������",0,99};
__root const int COLOR_SCROLLBAR_BG=0;  

__root const CFG_HDR cfghdr3_5={CFG_COLOR,"��ѡ��ʶ",0,0};
__root const char COLOR_SEARCH_MARK[4]={0xFF,0x0,0x0,0x64};

__root const CFG_HDR cfghdr3_6={CFG_COLOR,"��ѡδ��ʶ",0,0};
__root const char COLOR_SEARCH_UNMARK[4]={0xFF,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr_m8={CFG_LEVEL,"",0,0};

//��
__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"��ͨ������",1,0};

 __root const CFG_HDR cfghdr4_1={CFG_CBOX, "ʹ����", 0, 4};
 __root const int ENA_VIBRA = 0;
 __root const CFG_CBOX_ITEM cfgcbox2[4]={"��", "����", "ȥ��", "ȫ��"};

__root const CFG_HDR cfghdr4_2={CFG_UINT,"��ǿ��",0,100};
__root const unsigned int vibraPower=20;

__root const CFG_HDR cfghdr4_3={CFG_UINT,"����ʱ��(ms)",0,100};
__root const unsigned int vibraDuration=50;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m13={CFG_LEVEL,"��������趨",1,0};

__root const CFG_HDR cfghdr6_1={CFG_STR_UTF8,"ͨ��¼��ַ",3,127};
__root const char root_dir[128]="0:\\\x1F\xE7\xB3\xBB\xE7\xBB\x9F\\apo\\addr";

__root const CFG_HDR cfghdr6_2={CFG_UINT,"��Ч����",0,10};
__root const unsigned int volume=6;

__root const CFG_HDR cfghdr6_4={CFG_CBOX, "�б�߶�", 0, 2};
__root const int list_num = 0;
__root const CFG_CBOX_ITEM cfgcbox4[2]={"����", "����"};

__root const CFG_HDR cfghdr6_5 = {CFG_CHECKBOX,"���ŷ���",0,0};
__root const int sms_list=1;

__root const CFG_HDR cfghdr6_6={CFG_STR_GB,"û�к�����ʾ",3,63};
__root const char no_num[64]="û�绰";

__root const CFG_HDR cfghdr_m12={CFG_LEVEL,"",0,0};

/*

__root const CFG_HDR cfghdr_m23={CFG_LEVEL,"Setup Cash",1,0};

 __root const CFG_HDR cfghdr10_0={CFG_STR_WIN1251,"Number for Cash Request",0,31};
 __root const char CASHREQNUM[32]="*#";

 __root const CFG_HDR cfghdr10_000={CFG_UINT,"Auto cash check, hours",0,24};
 __root const unsigned int CHECK_HOURS=1;

 __root const CFG_HDR cfghdr10_01={CFG_CHECKBOX,"Enable Cash Trace",0,0};
 __root const int ENA_CASHTRACE = 1;
 
 __root const CFG_HDR cfghdr10_022={CFG_CHECKBOX,"Enable Op USSD Trace",0,0};
 __root const int ENA_AUTOCASHTRACE = 0; 

 __root const CFG_HDR cfghdr10_08={CFG_CHECKBOX,"Enable Cash Trace logging",0,0};
 __root const int ENA_CASHTRACELOG = 1;
 
 __root const CFG_HDR cfghdr02={CFG_STR_WIN1251,"Cash pattern 0",0,31};
 __root const char CashPat0[32]="alans #hrn";

 __root const CFG_HDR cfghdr10_03={CFG_STR_WIN1251,"Cash pattern 1",0,31};
 __root const char CashPat1[32]="onus #hrn";

 __root const CFG_HDR cfghdr10_04={CFG_STR_WIN1251,"Cash pattern 2",0,31};
 __root const char CashPat2[32]="# hv";

 __root const CFG_HDR cfghdr10_05={CFG_STR_WIN1251,"Cash pattern 3",0,31};
 __root const char CashPat3[32]="# Kb GPRS";

 __root const CFG_HDR cfghdr10_06 = {CFG_STR_UTF8,"Temp file path",0,127};
 __root const char cashTEMP_PATH[128]=DEFAULT_DISK ":\\ZBin\\var\\";

 __root const CFG_HDR cfghdr10_07 = {CFG_STR_UTF8,"Log file",0,127};
 __root const char cashLOG_FILE[128]=DEFAULT_DISK ":\\ZBin\\var\\CallCenter_cash.log";

 __root const CFG_HDR cfghdr10_072 = {CFG_STR_UTF8,"Log format",0,127};
 __root const char cashLOG_Format[128]="%02d.%02d.%04d %02d:%02d %.0s %d %d %d %d";

__root const CFG_HDR cfghdr10_073 = {CFG_CBOX, "Show In", 0, 3};
__root const int cfgShowIn = 1;
__root const CFG_CBOX_ITEM cfgcbox1[3] = {"Lock", "Unlock", "Both"};

 __root const CFG_HDR cfghdr10_19={CFG_COORDINATES,"Idle icon position",0,0};
 __root const unsigned int IDLE_X=0;
 __root const unsigned int IDLE_Y=95;
 
 
 
 
  __root const CFG_HDR cfghdr10_10={CFG_COLOR,"Cash Progressbar 1",0,0};
  __root const char COLOR_CASHPB1[4]={0xFF,0x00,0x00,0x32};

  __root const CFG_HDR cfghdr10_11={CFG_COLOR,"Cash Progressbar 2",0,0};
  __root const char COLOR_CASHPB2[4]={0x00,0xFF,0x00,0x32};

  __root const CFG_HDR cfghdr10_12={CFG_COLOR,"Cash Progressbar 3",0,0};
  __root const char COLOR_CASHPB3[4]={0x00,0xFF,0xFF,0x32};

  __root const CFG_HDR cfghdr10_13={CFG_COLOR,"Cash Progressbar 4",0,0};
  __root const char COLOR_CASHPB4[4]={0xFF,0xFF,0x00,0x32};
  
  __root const CFG_HDR cfghdr10_14={CFG_COLOR,"Font Color",0,0};
  __root const char COLOR_TEXTPB[4]={0xFF,0xFF,0xFF,0x64};
  
  __root const CFG_HDR cfghdr10_15={CFG_UINT,"Font Size",0,100};
  __root const unsigned int TEXT_FONTSZ=FONT_NUMERIC_XSMALL;
  

__root const CFG_HDR cfghdr_m22={CFG_LEVEL,"",0,0};
*/

