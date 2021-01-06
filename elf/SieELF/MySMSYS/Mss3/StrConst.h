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
#define LGP_CFG_MAIN_FOLDER "MySMSYS�ļ���"
#define LGP_CFG_SYSTEM_FOLDER "ϵͳ�ļ���"
#define LGP_CFG_ENA_NOTIFY "��������Ϣ����"
#define LGP_CFG_VIBRA_POWER "��ǿ��"
#define LGP_CFG_NOTIFY_SET "����Ϣ��������"
#define LGP_CFG_NOTIFY_TIME "����ʱ�䳤��(��)"
#define LGP_CFG_ENA_AUTO_SAF "�鿴ʱת��Ϊ�ļ�"
#define LGP_CFG_ENA_AUTO_SAF_RT "��ʱת��Ϊ�ļ�"
#define LGP_CFG_ENA_NEWSMS_ICON "������ʾ�¶���ͼ��"
#define LGP_CFG_ICONNEW_POS "ͼ������"
#define LGP_CFG_EXPORT_CHARSET "�����ı��ַ�����"
#define LGP_CFG_ENA_SAVE_SENT "�����ѷ��Ͷ���"
#define LGP_CFG_ENA_SOUND "ʹ����������"
#define LGP_CFG_SOUND_VOL "����"
#define LGP_CFG_SOUND_PATH "�����ļ�·��"
#define LGP_CFG_ENA_AUTO_DEL_RP "�Զ�ɾ����Ϣ����"
#define LGP_CFG_ENA_EXIT_SAVE_DRAFT "����ݸ���˳�"
#define LGP_CFG_TEXT_FONT "�ı�����"
#define LGP_EDIT_FONT_DEFAULT "ʹ��Ĭ��" 
#define LGP_EDIT_FONT_SMALL "С������"
#define LGP_EDIT_FONT_SMALL_BOLD "С����Ӵ�"
#define LGP_EDIT_FONT_MEDIUM "�к�����"
#define LGP_EDIT_FONT_MEDIUM_BOLD "������Ӵ�"
#define LGP_EDIT_FONT_LARGE "�������"
#define LGP_EDIT_FONT_LARGE_BOLD "������Ӵ�"
#ifdef ELKA
#define LGP_CFG_ENA_SLI "ʹ��SLI"
#endif
#define LGP_CFG_KEYHOOK_SETTING "���������������"
#define LGP_CFG_1ST_KEY "����1"
#define LGP_CFG_2ND_KEY "����2"
#define LGP_CFG_ICONBAR_SETTING "����Ϣͼ��������"
#define LGP_CFG_ENA_IB "ʹ��ͼ����"
#define LGP_CFG_ICON_IB "�¶���ͼ��ID"
#define LGP_CFG_ENA_AUTO_SAVE_DRAFT "�Զ�����ݸ�"
#define LGP_CFG_PROFILE1_SET "�龰ģʽ1"
#define LGP_CFG_PROFILE2_SET "�龰ģʽ2"
#define LGP_CFG_PROFILE3_SET "�龰ģʽ3"
#define LGP_CFG_PROFILE4_SET "�龰ģʽ4"
#define LGP_CFG_PROFILE5_SET "�龰ģʽ5"
#define LGP_CFG_PROFILE6_SET "�龰ģʽ6"
#define LGP_CFG_PROFILE7_SET "�龰ģʽ7"
#define LGP_CFG_PROFILE8_SET "�龰ģʽ8"

#ifdef MEGADIAL
#define LGP_CFG_MDSETTING "MegaDial����"
#define LGP_CFG_MDBGCOL "�б���ɫ"
#define LGP_CFG_MDMNBDCOL "�б����ɫ"
#define LGP_CFG_MDNSLCOL "δѡ����Ŀ��ɫ"
#define LGP_CFG_MDSLCOL "ѡ����Ŀ��ɫ"
#define LGP_CFG_MDSLBGCOL "ѡ����Ŀ����ɫ"
#define LGP_CFG_MDSLBDCOL "ѡ����Ŀ���ɫ"
#define LGP_CFG_MDSHMKCOL "�����ؼ�����ɫ"
#define LGP_CFG_ENA_MD "ʹ��MegaDial"
#define LGP_CFG_MDCSCOL "��������ɫ"
#endif

#define LGP_CFG_ENA_SNED_ON_BG "��̨���Ͷ���"
#define LGP_CFG_ICONSNED_IB "���ŷ���ͼ��ID"
#define LGP_CFG_DEFAULT_SENT_NUM "Ĭ�Ϸ��ͺ���"

#define LGP_CFG_FILTERSET "ɸѡ��ʾ����"
#define LGP_CFG_FILTEROP "ɸѡ��ʾѡ��"
#define LGP_FILTER_ALL "ȫ��"
#define LGP_FILTER_NEW "δ������"
#define LGP_FILTER_DAT "����SMS.dat"
#define LGP_FILTER_FILE "�����ļ�"
#define LGP_FILTER_NUM "����"
#define LGP_FILTER_STR "�ַ���"
#define LGP_CFG_STRORNUM "�ַ��������"
#define LGP_CFG_DEFAULT_TAB "Ĭ�ϱ�ǩ"
#define LGP_CFG_MAINMENU "���˵�"
#define LGP_CFG_INBOX "�ռ���"
#define LGP_CFG_SENT "�ѷ���"
#define LGP_CFG_FILTER "ɸѡ��ʾ"
#define LGP_CFG_DRAFT "�ݸ�"
#define LGP_CFG_ENA_VIBRA "ʹ����"
#define LGP_CFG_VIBRA_RHYTHM "�񶯽���"
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


