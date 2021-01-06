#ifndef _STRCONST_H_
#define _STRCONST_H_

#define CP_RIGHT "My SMS System C++\nv3 Beta\n(c)BingK\n(r)titron,Rst7"

extern const char IPC_NAME[];
extern const char FLDR_IN[];
//extern const char FLDR_OUT[];
extern const char FLDR_SENT[];
extern const char FLDR_DRAFT[];
extern const char FLDR_UNK[];
extern const char FLDR_ARCHIVE[];

extern const char PERCENT_T[];
extern const char PERCENT_S[];
extern const char num_fetion[];
extern const char STR_LINES[];
extern const char STR_UNK_TXTT[];
extern const char STR_UNK_TYPE[];

extern const char STR_UNK_NUM_UTF8[];
extern const char STR_NUMBER_UTF8[];
extern const char STR_TEXT_UTF8[];
extern const char STR_TO_UTF8[];
extern const char STR_FROM_UTF8[];
extern const char STR_TIME_UTF8[];
extern const char STR_UNK_UTF8[];
extern const char DEFAUT_HLP_STR[];

#ifdef LANG_CN
#define LGP_CFG_MAIN_FOLDER "MySMSYS文件夹"
#define LGP_CFG_SYSTEM_FOLDER "系统文件夹"
#define LGP_CFG_ENA_NOTIFY "弹出新信息窗口"
#define LGP_CFG_VIBRA_POWER "振动强度"
#define LGP_CFG_NOTIFY_SET "新信息提醒设置"
#define LGP_CFG_NOTIFY_TIME "提醒时间长度(秒)"
#define LGP_CFG_ENA_AUTO_SAF "查看时转换为文件"
#define LGP_CFG_ENA_AUTO_SAF_RT "即时转换为文件"
#define LGP_CFG_ENA_NEWSMS_ICON "待机显示新短信图标"
#define LGP_CFG_ICONNEW_POS "图标坐标"
#define LGP_CFG_EXPORT_CHARSET "导出文本字符编码"
#define LGP_CFG_ENA_SAVE_SENT "保存已发送短信"
#define LGP_CFG_ENA_SOUND "使用声音提醒"
#define LGP_CFG_SOUND_VOL "音量"
#define LGP_CFG_SOUND_PATH "声音文件路径"
#define LGP_CFG_ENA_AUTO_DEL_RP "自动删除信息报告"
#define LGP_CFG_ENA_EXIT_SAVE_DRAFT "保存草稿后退出"
#define LGP_CFG_TEXT_FONT "文本字体"
#define LGP_EDIT_FONT_DEFAULT "使用默认" 
#define LGP_EDIT_FONT_SMALL "小号字体"
#define LGP_EDIT_FONT_SMALL_BOLD "小字体加粗"
#define LGP_EDIT_FONT_MEDIUM "中号字体"
#define LGP_EDIT_FONT_MEDIUM_BOLD "中字体加粗"
#define LGP_EDIT_FONT_LARGE "大号字体"
#define LGP_EDIT_FONT_LARGE_BOLD "大字体加粗"
#ifdef ELKA
#define LGP_CFG_ENA_SLI "使用SLI"
#endif
#define LGP_CFG_KEYHOOK_SETTING "按键组合启动设置"
#define LGP_CFG_1ST_KEY "按键1"
#define LGP_CFG_2ND_KEY "按键2"
#define LGP_CFG_ICONBAR_SETTING "新信息图标栏设置"
#define LGP_CFG_ENA_IB "使用图标栏"
#define LGP_CFG_ICON_IB "新短信图标ID"
#define LGP_CFG_ENA_AUTO_SAVE_DRAFT "自动保存草稿"
#define LGP_CFG_PROFILE1_SET "情景模式1"
#define LGP_CFG_PROFILE2_SET "情景模式2"
#define LGP_CFG_PROFILE3_SET "情景模式3"
#define LGP_CFG_PROFILE4_SET "情景模式4"
#define LGP_CFG_PROFILE5_SET "情景模式5"
#define LGP_CFG_PROFILE6_SET "情景模式6"
#define LGP_CFG_PROFILE7_SET "情景模式7"
#define LGP_CFG_PROFILE8_SET "情景模式8"

#ifdef MEGADIAL
#define LGP_CFG_MDSETTING "MegaDial设置"
#define LGP_CFG_MDBGCOL "列表背景色"
#define LGP_CFG_MDMNBDCOL "列表外框色"
#define LGP_CFG_MDNSLCOL "未选中条目颜色"
#define LGP_CFG_MDSLCOL "选中条目颜色"
#define LGP_CFG_MDSLBGCOL "选中条目背景色"
#define LGP_CFG_MDSLBDCOL "选中条目外框色"
#define LGP_CFG_MDSHMKCOL "搜索关键字颜色"
#define LGP_CFG_ENA_MD "使用MegaDial"
#define LGP_CFG_MDCSCOL "区号秀颜色"
#endif

#define LGP_CFG_ENA_SNED_ON_BG "后台发送短信"
#define LGP_CFG_ICONSNED_IB "短信发送图标ID"
#define LGP_CFG_DEFAULT_SENT_NUM "默认发送号码"

#define LGP_CFG_FILTERSET "筛选显示设置"
#define LGP_CFG_FILTEROP "筛选显示选项"
#define LGP_FILTER_ALL "全部"
#define LGP_FILTER_NEW "未读短信"
#define LGP_FILTER_DAT "来自SMS.dat"
#define LGP_FILTER_FILE "来自文件"
#define LGP_FILTER_NUM "号码"
#define LGP_FILTER_STR "字符串"
#define LGP_CFG_STRORNUM "字符串或号码"
#define LGP_CFG_DEFAULT_TAB "默认标签"
#define LGP_CFG_MAINMENU "主菜单"
#define LGP_CFG_INBOX "收件箱"
#define LGP_CFG_SENT "已发送"
#define LGP_CFG_FILTER "筛选显示"
#define LGP_CFG_DRAFT "草稿"
#define LGP_CFG_ENA_VIBRA "使用振动"
#define LGP_CFG_VIBRA_RHYTHM "振动节奏"
#endif

#ifdef LANG_EN
#define LGP_CFG_MAIN_FOLDER "MySMSYS Folder"
#define LGP_CFG_SYSTEM_FOLDER "System Folder"
#define LGP_CFG_ENA_NOTIFY "Popup New SMS"
#define LGP_CFG_VIBRA_POWER "Vibra Power"
#define LGP_CFG_NOTIFY_SET "Notify Setup"
#define LGP_CFG_NOTIFY_TIME "Notify Time (s)"
#define LGP_CFG_ENA_AUTO_SAF "Auto Save As File At View"
#define LGP_CFG_ENA_AUTO_SAF_RT "Auto Save As File Real Time"
#define LGP_CFG_ENA_NEWSMS_ICON "Show NewSMS Icon Idle"
#define LGP_CFG_ICONNEW_POS "Icon Position"
#define LGP_CFG_EXPORT_CHARSET "Export Text Charset"
#define LGP_CFG_ENA_SAVE_SENT "Save Sent SMS"
#define LGP_CFG_ENA_SOUND "Enable Sound Notify"
#define LGP_CFG_SOUND_VOL "Volume"
#define LGP_CFG_SOUND_PATH "Sound File Path"
#define LGP_CFG_ENA_AUTO_DEL_RP "Auto Delete Message Report"
#define LGP_CFG_ENA_EXIT_SAVE_DRAFT "Exit After Save Draft"
#define LGP_CFG_TEXT_FONT "Text Font"
#define LGP_EDIT_FONT_DEFAULT "Default" 
#define LGP_EDIT_FONT_SMALL "Small"
#define LGP_EDIT_FONT_SMALL_BOLD "Small+Bold"
#define LGP_EDIT_FONT_MEDIUM "Medium"
#define LGP_EDIT_FONT_MEDIUM_BOLD "Medium+Bold"
#define LGP_EDIT_FONT_LARGE "Large"
#define LGP_EDIT_FONT_LARGE_BOLD "Large+Bold"
#ifdef ELKA
#define LGP_CFG_ENA_SLI "Enable SLI"
#endif
#define LGP_CFG_KEYHOOK_SETTING "KeyHook Settings"
#define LGP_CFG_1ST_KEY "1st Key"
#define LGP_CFG_2ND_KEY "2nd Key"
#define LGP_CFG_ICONBAR_SETTING "Iconbar Settings"
#define LGP_CFG_ENA_IB "Enable Iconbar"
#define LGP_CFG_ICON_IB "New SMS Picture ID"
#define LGP_CFG_ENA_AUTO_SAVE_DRAFT "Auto Save Draft"
#define LGP_CFG_PROFILE1_SET "Profile1"
#define LGP_CFG_PROFILE2_SET "Profile2"
#define LGP_CFG_PROFILE3_SET "Profile3"
#define LGP_CFG_PROFILE4_SET "Profile4"
#define LGP_CFG_PROFILE5_SET "Profile5"
#define LGP_CFG_PROFILE6_SET "Profile6"
#define LGP_CFG_PROFILE7_SET "Profile7"
#define LGP_CFG_PROFILE8_SET "Profile8"

#ifdef MEGADIAL
#define LGP_CFG_MDSETTING "MegaDial Settings"
#define LGP_CFG_MDBGCOL "Color Menu background"
#define LGP_CFG_MDMNBDCOL "Color Menu border"
#define LGP_CFG_MDNSLCOL "Color Not selected"
#define LGP_CFG_MDSLCOL "Color Selected"
#define LGP_CFG_MDSLBGCOL "Color Selected background"
#define LGP_CFG_MDSLBDCOL "Color Selected border"
#define LGP_CFG_MDSHMKCOL "Color Search mark"
#define LGP_CFG_ENA_MD "Enable MegaDial"
#endif

#define LGP_CFG_ENA_SNED_ON_BG "Send SMS on Background"
#define LGP_CFG_ICONSNED_IB "Sending Picture ID"
#define LGP_CFG_DEFAULT_SENT_NUM "Default Sent Number"
#define LGP_CFG_FILTERSET "Filter Settings"
#define LGP_CFG_FILTEROP "Filter Options"
#define LGP_FILTER_ALL "All"
#define LGP_FILTER_NEW "New SMS"
#define LGP_FILTER_DAT "From SMS.dat"
#define LGP_FILTER_FILE "From Files"
#define LGP_FILTER_NUM "Number"
#define LGP_FILTER_STR "Strings"
#define LGP_CFG_STRORNUM "Str Or Num"
#define LGP_CFG_DEFAULT_TAB "Default Tab"
#define LGP_CFG_MAINMENU "MainMenu"
#define LGP_CFG_INBOX "Inbox"
#define LGP_CFG_SENT "Sent"
#define LGP_CFG_FILTER "Filter"
#define LGP_CFG_DRAFT "Draft"
#define LGP_CFG_ENA_VIBRA "Enable Vibra"
#define LGP_CFG_VIBRA_RHYTHM "Vibra Rhythm"
#endif

#endif


