#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
#include "config_data.h"
#include "StrConst.h"

__root const CFG_HDR cfghdr0 = {CFG_STR_UTF8, LGP_CFG_MAIN_FOLDER, 3, 127};
__root const char CFG_MAIN_FOLDER[128] = "4:\\ZBin\\MySMSYS\\";

__root const CFG_HDR cfghdr1 = {CFG_STR_UTF8, LGP_CFG_SYSTEM_FOLDER, 3, 127};
__root const char CFG_SYSTEM_FOLDER[128] = "0:\\System\\";

__root const CFG_HDR cfghdr2 = {CFG_CHECKBOX, LGP_CFG_ENA_AUTO_SAF, 0, 3};
__root const int CFG_ENA_AUTO_SAF = 1;

//__root const CFG_HDR cfghdr9 = {CFG_CHECKBOX, LGP_CFG_ENA_AUTO_SAF_RT, 0, 3};
//__root const int CFG_ENA_AUTO_SAF_RT = 0;

__root const CFG_HDR cfghdr4 = {CFG_CHECKBOX, LGP_CFG_ENA_SAVE_SENT, 0, 3};
__root const int CFG_ENA_SAVE_SENT = 1;

//__root const CFG_HDR cfghdr5 = {CFG_CHECKBOX, LGP_CFG_ENA_AUTO_DEL_RP, 0, 3};
//__root const int CFG_ENA_AUTO_DEL_RP = 1;

//__root const CFG_HDR cfghdr6 = {CFG_CHECKBOX, LGP_CFG_ENA_EXIT_SAVE_DRAFT, 0, 3};
//__root const int CFG_ENA_EXIT_SAVE_DRAFT = 1;

//__root const CFG_HDR cfghdr8 = {CFG_CHECKBOX, LGP_CFG_ENA_AUTO_SAVE_DRAFT, 0, 3};
//__root const int CFG_ENA_AUTO_SAVE_DRAFT = 1;

__root const CFG_HDR cfghdra = {CFG_CHECKBOX, LGP_CFG_ENA_SNED_ON_BG, 0, 3};
__root const int CFG_ENA_SNED_ON_BG = 1;

//__root const CFG_HDR cfghdr3 = {CFG_CBOX, LGP_CFG_EXPORT_CHARSET, 0, 2};
//__root const int CFG_EXPORT_CHARSET = 1;
//#ifdef LANG_CN
//__root const CFG_CBOX_ITEM cfgcbox0[2] = {"ASCII", "UTF8"};
//#else
//__root const CFG_CBOX_ITEM cfgcbox0[2] = {"WIN1251", "UTF8"};
//#endif

__root const CFG_HDR cfghdr7 = {CFG_CBOX, LGP_CFG_TEXT_FONT, 0, 7};
__root const unsigned int CFG_TEXT_FONT = 1;
__root const CFG_CBOX_ITEM cfgcbox1[7] = 
{
	LGP_EDIT_FONT_DEFAULT, 
	LGP_EDIT_FONT_SMALL,
	LGP_EDIT_FONT_SMALL_BOLD,
	LGP_EDIT_FONT_MEDIUM,
	LGP_EDIT_FONT_MEDIUM_BOLD,
	LGP_EDIT_FONT_LARGE,
	LGP_EDIT_FONT_LARGE_BOLD
};


__root const CFG_HDR cfghdrb = {CFG_UTF8_STRING, LGP_CFG_DEFAULT_SENT_NUM, 0, 127};
__root const char CFG_DEFAULT_SENT_NUM[128] = "";

__root const CFG_HDR cfghdrc = {CFG_CBOX, LGP_CFG_DEFAULT_TAB, 0, 5};
__root const unsigned int CFG_DEFAULT_TAB = 0;
__root const CFG_CBOX_ITEM cfgcboxc[5] = 
{
	LGP_CFG_MAINMENU, 
	LGP_CFG_INBOX,
	LGP_CFG_SENT,
	LGP_CFG_DRAFT,
	LGP_CFG_FILTER,
};

/*
__root const CFG_HDR cfghdr8= {CFG_UTF8_STRING, "Utf8≤‚ ‘", 0, 127};
__root const char UTF8_TEST[128]="";
*/
__root const CFG_HDR cfghdr1_0 = {CFG_LEVEL, LGP_CFG_NOTIFY_SET, 1, 0};

__root const CFG_HDR cfghdr1_1 = {CFG_CHECKBOX, LGP_CFG_ENA_NOTIFY, 0, 3};
__root const int CFG_ENA_NOTIFY = 1;

//__root const CFG_HDR cfghdr1_2 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
//__root const unsigned int CFG_VIBRA_POWER = 50;

__root const CFG_HDR cfghdr1_2 = {CFG_CHECKBOX, LGP_CFG_ENA_VIBRA, 0, 3};
__root const int CFG_ENA_VIBRA = 1;

__root const CFG_HDR cfghdr1_5 = {CFG_UTF8_STRING, LGP_CFG_VIBRA_RHYTHM, 0, 127};
__root const char CFG_VIBRA_RHYTHM[128] = "90;10;60;20;70;40;;80;30;50;";

__root const CFG_HDR cfghdr1_3 = {CFG_UINT, LGP_CFG_NOTIFY_TIME, 0, 100};
__root const int CFG_NOTIFY_TIME = 4;

//__root const CFG_HDR cfghdr1_4 = {CFG_CHECKBOX, LGP_CFG_ENA_NEWSMS_ICON, 0, 3};
//__root const int CFG_ENA_NEWSMS_ICON = 1;

/*
__root const CFG_HDR cfghdr1_5= {CFG_STR_UTF8, LGP_CFG_ICONNEW_PATH, 0, 127};
#ifdef NEWSGOLD
#ifdef ELKA
__root const char CFG_ICONNEW_PATH[128] = "426";//"0:\\ZBin\\MySMSYS\\new.png";
#else
__root const char CFG_ICONNEW_PATH[128] = "467";//"0:\\ZBin\\MySMSYS\\new.png";
#endif
#endif

__root const CFG_HDR cfghdr1_6= {CFG_COORDINATES, LGP_CFG_ICONNEW_POS, 0, 0};
__root const unsigned int CFG_ICONNEW_POS_X = 2;
__root const unsigned int CFG_ICONNEW_POS_Y = 140;
*/
__root const CFG_HDR cfghdr1_7 = {CFG_CHECKBOX, LGP_CFG_ENA_SOUND, 0, 3};
__root const int CFG_ENA_SOUND = 1;

__root const CFG_HDR cfghdr1_8= {CFG_STR_UTF8, LGP_CFG_SOUND_PATH, 3, 127};
__root const char CFG_SOUND_PATH[128] = "2:\\Default\\MessageMelody.wav";

//__root const CFG_HDR cfghdr1_a = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
//__root const unsigned int CFG_SOUND_VOL = 5;

//#ifdef ELKA
//__root const CFG_HDR cfghdr1_5 = {CFG_CHECKBOX, LGP_CFG_ENA_SLI, 0, 3};
//__root const int CFG_ENA_SLI = 1;
//#endif

//------------------------ profile
/*
__root const CFG_HDR cfghdr1_10 = {CFG_LEVEL, LGP_CFG_PROFILE1_SET, 1, 0};

__root const CFG_HDR cfghdr1_11 = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL1 = 5;

__root const CFG_HDR cfghdr1_12 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER1 = 50;

__root const CFG_HDR cfghdr1_19 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr1_20 = {CFG_LEVEL, LGP_CFG_PROFILE2_SET, 1, 0};

__root const CFG_HDR cfghdr1_21 = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL2 = 0;

__root const CFG_HDR cfghdr1_22 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER2 = 50;

__root const CFG_HDR cfghdr1_29 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr1_30 = {CFG_LEVEL, LGP_CFG_PROFILE3_SET, 1, 0};

__root const CFG_HDR cfghdr1_31 = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL3 = 5;

__root const CFG_HDR cfghdr1_32 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER3 = 50;

__root const CFG_HDR cfghdr1_39 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr1_40 = {CFG_LEVEL, LGP_CFG_PROFILE4_SET, 1, 0};

__root const CFG_HDR cfghdr1_41 = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL4 = 5;

__root const CFG_HDR cfghdr1_42 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER4 = 50;

__root const CFG_HDR cfghdr1_49 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr1_50 = {CFG_LEVEL, LGP_CFG_PROFILE5_SET, 1, 0};

__root const CFG_HDR cfghdr1_51 = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL5 = 5;

__root const CFG_HDR cfghdr1_52 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER5 = 50;

__root const CFG_HDR cfghdr1_59 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr1_60 = {CFG_LEVEL, LGP_CFG_PROFILE6_SET, 1, 0};

__root const CFG_HDR cfghdr1_61 = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL6 = 5;

__root const CFG_HDR cfghdr1_62 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER6 = 50;

__root const CFG_HDR cfghdr1_69 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr1_70 = {CFG_LEVEL, LGP_CFG_PROFILE7_SET, 1, 0};

__root const CFG_HDR cfghdr1_71 = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL7 = 5;

__root const CFG_HDR cfghdr1_72 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER7 = 50;

__root const CFG_HDR cfghdr1_79 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr1_80 = {CFG_LEVEL, LGP_CFG_PROFILE8_SET, 1, 0};

__root const CFG_HDR cfghdr1_81 = {CFG_UINT, LGP_CFG_SOUND_VOL, 0, 10};
__root const unsigned int CFG_SOUND_VOL8 = 2;

__root const CFG_HDR cfghdr1_82 = {CFG_UINT, LGP_CFG_VIBRA_POWER, 0, 100};
__root const unsigned int CFG_VIBRA_POWER8 = 50;

__root const CFG_HDR cfghdr1_89 = {CFG_LEVEL, "", 0, 0};
*/
//-----------------------------

__root const CFG_HDR cfghdr1_9 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr2_0 = {CFG_LEVEL, LGP_CFG_KEYHOOK_SETTING, 1, 0};

__root const CFG_HDR cfghdr2_1 = {CFG_UINT, LGP_CFG_1ST_KEY, 0, 100};
__root const unsigned int KEY1 = '*';

__root const CFG_HDR cfghdr2_2 = {CFG_UINT, LGP_CFG_2ND_KEY, 0, 100};
__root const unsigned int KEY2 = '#';

__root const CFG_HDR cfghdr2_9 = {CFG_LEVEL, "", 0, 0};

__root const CFG_HDR cfghdr3_0 = {CFG_LEVEL, LGP_CFG_ICONBAR_SETTING, 1, 0};

__root const CFG_HDR cfghdr3_1 = {CFG_CHECKBOX, LGP_CFG_ENA_IB, 0, 3};
__root const int CFG_ENA_IB = 1;

__root const CFG_HDR cfghdr3_2 = {CFG_UINT, LGP_CFG_ICON_IB, 0, 9999};
#ifdef NEWSGOLD
#ifdef ELKA
__root const unsigned int CFG_ICON_IB = 597;
#else
__root const unsigned int CFG_ICON_IB = 475;
#endif
#endif
/*
__root const CFG_HDR cfghdr3_3 = {CFG_UINT, LGP_CFG_ICONSNED_IB, 0, 9999};
#ifdef NEWSGOLD
#ifdef ELKA
__root const unsigned int CFG_ICONSNED_IB = 428;
#else
__root const unsigned int CFG_ICONSNED_IB = 477;
#endif
#endif
*/
__root const CFG_HDR cfghdr3_9 = {CFG_LEVEL, "", 0, 0};


//-------------------
//megadial

/*
#ifdef MEGADIAL
__root const CFG_HDR cfghdr10_0 = {CFG_LEVEL, LGP_CFG_MDSETTING, 1, 0};

__root const CFG_HDR cfghdr107 = {CFG_CHECKBOX, LGP_CFG_ENA_MD, 0, 3};
__root const int CFG_ENA_MD = 1;

__root const CFG_HDR cfghdr100={CFG_COLOR,LGP_CFG_MDBGCOL,0,0};
__root const char COLOR_MENU_BK[4]={0xFF,0xFF,0x0,0x64};

__root const CFG_HDR cfghdr101={CFG_COLOR,LGP_CFG_MDMNBDCOL,0,0};
__root const char COLOR_MENU_BRD[4]={0x0,0x0,0x0,0x64};

__root const CFG_HDR cfghdr102={CFG_COLOR,LGP_CFG_MDNSLCOL,0,0};
__root const char COLOR_NOTSELECTED[4]={0x0,0x0,0x0,0x64};

__root const CFG_HDR cfghdr103={CFG_COLOR,LGP_CFG_MDSLCOL,0,0};
__root const char COLOR_SELECTED[4]={0xFF,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr104={CFG_COLOR,LGP_CFG_MDSLBGCOL,0,0};
__root const char COLOR_SELECTED_BG[4]={0x0,0x0,0xFF,0x64};

__root const CFG_HDR cfghdr105={CFG_COLOR,LGP_CFG_MDSLBDCOL,0,0};
__root const char COLOR_SELECTED_BRD[4]={0x0,0x0,0xFF,0x64};

__root const CFG_HDR cfghdr106={CFG_COLOR,LGP_CFG_MDSHMKCOL,0,0};
__root const char COLOR_SEARCH_MARK[4]={0xFF,0x0,0x0,0x64};

#ifdef LANG_CN
__root const CFG_HDR cfghdr108={CFG_COLOR,LGP_CFG_MDCSCOL,0,0};
__root const char COLOR_CODE_SHOW[4]={0xFF,0xFF,0xFF,0x64};
#endif

__root const CFG_HDR cfghdr10_9 = {CFG_LEVEL, "", 0, 0};
#endif

*/
__root const CFG_HDR cfghdr11_0 = {CFG_LEVEL, LGP_CFG_FILTERSET, 1, 0};

__root const CFG_HDR cfghdr11_1 = {CFG_CBOX, LGP_CFG_FILTEROP, 0, 6};
__root const unsigned int CFG_FILTEROP = 0;
__root const CFG_CBOX_ITEM cfgcbox11_1[6] = 
{
	LGP_FILTER_ALL, 
	LGP_FILTER_NEW,
        LGP_FILTER_DAT,
        LGP_FILTER_FILE,
	LGP_FILTER_NUM,
	LGP_FILTER_STR,
};

__root const CFG_HDR cfghdr11_2 = {CFG_UTF8_STRING, LGP_CFG_STRORNUM, 0, 31};
__root const char CFG_STRORNUM[32] = "";

__root const CFG_HDR cfghdr11_9 = {CFG_LEVEL, "", 0, 0};
//-------------------
