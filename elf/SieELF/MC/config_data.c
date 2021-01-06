#include "..\inc\cfg_items.h"
#include "inc\lng.h"
#include "inc\mc.h"

__root const CFG_HDR cfghdr_m00 = { CFG_LEVEL, psz_sm_common, 1, 0 };

	__root const CFG_HDR cfghdr0 = { CFG_CHECKBOX, psz_savestate, 0, 2 };
	__root const int CONFIG_SAVE_PATH = 1;
	//__root const CFG_CBOX_ITEM cfgcbox0[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr1 = { CFG_CHECKBOX, psz_backexit, 0, 2 };
	__root const int CONFIG_BACK_EXIT = 0;
	//__root const CFG_CBOX_ITEM cfgcbox1[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr2 = { CFG_CHECKBOX, psz_sconchk, 0, 2 };
	__root const int CONFIG_CUR_DOWN_ON_CHECK = 1;
	//__root const CFG_CBOX_ITEM cfgcbox2[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr3 = { CFG_CHECKBOX, psz_loopnav, 0, 2 };
	__root const int CONFIG_LOOP_NAVIGATION_ENABLE = 1;
	//__root const CFG_CBOX_ITEM cfgcbox3[] = { psz_no, psz_yes };

__root const CFG_HDR cfghdr_m01 = { CFG_LEVEL, "", 0, 0 };


__root const CFG_HDR cfghdr_m10 = { CFG_LEVEL, psz_sm_gui, 1, 0 };

	__root const CFG_HDR cfghdr4 = { CFG_UINT, psz_scspeed, 0, 2000 };
	__root const int CONFIG_SCROLL_TEXT_SPEED = 10;

	__root const CFG_HDR cfghdr5 = { CFG_UINT, psz_scwait, 0, 200 };
	__root const int CONFIG_SCROLL_TEXT_WAIT = 10;

	__root const CFG_HDR cfghdr6 = { CFG_CHECKBOX, psz_useboldf, 0, 2 };
	__root const int CONFIG_USE_BOLD_FONT = 1;
	//__root const CFG_CBOX_ITEM cfgcbox6[] = { psz_no, psz_yes };

__root const CFG_HDR cfghdr_m11 = { CFG_LEVEL, "", 0, 0 };


__root const CFG_HDR cfghdr_m20 = { CFG_LEVEL, psz_sm_disks, 1, 0 };

	__root const CFG_HDR cfghdr7 = { CFG_CHECKBOX, psz_showhidden, 0, 2 };
	__root const int CONFIG_SHOW_HIDDEN = 1;
	//__root const CFG_CBOX_ITEM cfgcbox7[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr8 = { CFG_CHECKBOX, psz_showsystem, 0, 2 };
	__root const int CONFIG_SHOW_SYSTEM = 1;
	//__root const CFG_CBOX_ITEM cfgcbox8[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr9 = { CFG_CHECKBOX, psz_showhiddrv, 0, 2 };
	__root const int CONFIG_SHOW_SYSDRV = 1;
	//__root const CFG_CBOX_ITEM cfgcbox9[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr10 = { CFG_CHECKBOX, psz_showmmc, 0, 2 };
	__root const int CONFIG_SHOW_MMC = 1;
	//__root const CFG_CBOX_ITEM cfgcbox10[] = { psz_no, psz_yes };

__root const CFG_HDR cfghdr_m21 = { CFG_LEVEL, "", 0, 0 };


__root const CFG_HDR cfghdr_m30 = { CFG_LEVEL, psz_sm_configs, 1, 0 };

	__root const CFG_HDR cfghdr11 = { CFG_CHECKBOX, psz_loadicons, 0, 2 };
	__root const int CONFIG_LOAD_ICONS = 1;
	//__root const CFG_CBOX_ITEM cfgcbox11[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr12 = { CFG_CHECKBOX, psz_loadkeys, 0, 2 };
	__root const int CONFIG_LOAD_KEYS = 1;
	//__root const CFG_CBOX_ITEM cfgcbox12[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr13 = { CFG_CHECKBOX, psz_loadmui, 0, 2 };
	__root const int CONFIG_LOAD_MUI = 1;
	//__root const CFG_CBOX_ITEM cfgcbox13[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr14 = { CFG_CHECKBOX, psz_loadcs, 0, 2 };
	__root const int CONFIG_LOAD_CS = 1;
	//__root const CFG_CBOX_ITEM cfgcbox14[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr15 = { CFG_STR_UTF8, psz_configpath, 0, 63 };
	__root const char CONFIG_MCCONFIG_PATH[64] = "";

__root const CFG_HDR cfghdr_m31 = { CFG_LEVEL, "", 0, 0 };


__root const CFG_HDR cfghdr_m40 = { CFG_LEVEL, psz_sm_confirms, 1, 0 };

	__root const CFG_HDR cfghdr16 = { CFG_CHECKBOX, psz_confirmexit, 0, 2 };
	__root const int CONFIG_CONFIRM_EXIT = 0;
	//__root const CFG_CBOX_ITEM cfgcbox16[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr17 = { CFG_CHECKBOX, psz_confirmdel, 0, 2 };
	__root const int CONFIG_CONFIRM_DELETE = 1;
	//__root const CFG_CBOX_ITEM cfgcbox17[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr18 = { CFG_CHECKBOX, psz_confirmdelr, 0, 2 };
	__root const int CONFIG_CONFIRM_DELETERO = 1;
	//__root const CFG_CBOX_ITEM cfgcbox18[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr19 = { CFG_CHECKBOX, psz_confirmcopy, 0, 2 };
	__root const int CONFIG_CONFIRM_COPY = 1;
	//__root const CFG_CBOX_ITEM cfgcbox19[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr20 = { CFG_CHECKBOX, psz_confirmmove, 0, 2 };
	__root const int CONFIG_CONFIRM_MOVE = 1;
	//__root const CFG_CBOX_ITEM cfgcbox20[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr21 = { CFG_CHECKBOX, psz_confirmrepl, 0, 2 };
	__root const int CONFIG_CONFIRM_REPLACE = 1;
	//__root const CFG_CBOX_ITEM cfgcbox21[] = { psz_no, psz_yes };

__root const CFG_HDR cfghdr_m41 = { CFG_LEVEL, "", 0, 0 };


__root const CFG_HDR cfghdr_m50 = { CFG_LEVEL, psz_sm_autoexit, 1, 0 };

	__root const CFG_HDR cfghdr22 = { CFG_UINT, psz_autoexit_after, 0, 2000 };
	__root const int CONFIG_AUTO_EXIT_AFTER_MIN = 30;

	__root const CFG_HDR cfghdr23 = { CFG_CHECKBOX, psz_autoexit_on_background, 0, 2 };
	__root const int CONFIG_ENABLE_BACKGROUND_EXIT = 0;
	//__root const CFG_CBOX_ITEM cfgcbox23[] = { psz_no, psz_yes };

__root const CFG_HDR cfghdr_m51 = { CFG_LEVEL, "", 0, 0 };


__root const CFG_HDR cfghdr_m60 = { CFG_LEVEL, psz_sm_zip, 1, 0 };

	__root const CFG_HDR cfghdr24 = { CFG_CHECKBOX, psz_zip_enable, 0, 2 };
	__root const int CONFIG_ZIP_ENABLE = 1;
	//__root const CFG_CBOX_ITEM cfgcbox24[] = { psz_no, psz_yes };

	__root const CFG_HDR cfghdr25 = { CFG_CBOX, psz_zip_detect_by, 0, 2 };
	__root const int CONFIG_ZIP_DETECT_BY = 0;
	__root const CFG_CBOX_ITEM cfgcbox25[] = { psz_content, psz_extension };

	__root const CFG_HDR cfghdr26 = { CFG_STR_UTF8, psz_temppath, 0, 63 };
	__root const char CONFIG_TEMP_PATH[64] = DEFAULT_DISK":\\Temp";

	__root const CFG_HDR cfghdr27 = { CFG_CHECKBOX, psz_cleartemp, 0, 2 };
	__root const int CONFIG_DELETE_TEMP_FILES_ON_EXIT = 0;
	//__root const CFG_CBOX_ITEM cfgcbox27[] = { psz_no, psz_yes };

__root const CFG_HDR cfghdr_m61 = { CFG_LEVEL, "", 0, 0 };

