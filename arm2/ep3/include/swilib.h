


/**
*  Переделанная swilib.h для gcc.
*  (c) Z.Vova
*/




#ifndef __SWILIB__
#define __SWILIB__

#include <sys/types.h>
#include <stdarg.h>
#include <sha.h>
#include <rsa.h>
#include <md5.h>
#include <obs.h>
#include <swihelper.h>
#include <png.h>

#ifndef _NULL
#define _NULL 0
#endif

#ifndef NULL
#define NULL   _NULL
#endif /* NULL */

#define __int16 short
typedef int HObj;
#ifndef __JMPBUF_DECL
#define __JMPBUF_DECL
typedef int jmp_buf[11];
#endif

#define true 1
#define false 0

#ifndef UNUSED
#define UNUSED(x) ((void)x)
#endif

/* ======================================================= */

#define PC_FOREGROUND         100
#define PC_BACKGROUND         101
#define PC_HEADERFOREGROUND   102
#define PC_HEADERBACKGROUND   103

#define PC_SELECTFOREGROUND   115
#define PC_SELECTBACKGROUND   116
#define PC_SELECTBORDER       117
#define PC_SELECTSHADOW       118

#define PC_LIGHTTEXTFOREGROUND 122
#define PC_LIGHTTEXTBACKGROUND 123

#define PC_SCROLLBARSLIDER    127
#define PC_SCROLLBAR          128
#define PC_WINDOWFOREGROUND   129
#define PC_WINDOWBACKGROUND   130

#define PC_BORDER             133
#define PC_BORDERSHADOW       134

#define PC_POPUPSELECTFOREGROUD 135
#define PC_POPUPSELECTBACKGROUD 136

#define PC_PROGRESSBACKGROUND 138
#define PC_PROGRESSFOREGROUND 139
#define PC_PROGRESSBORDER     140

/* =========================================== */

#define LMAN_CONNECT_CNF 0x80
#define LMAN_CONNECT_REJ_IND 0x81
#define LMAN_DISCONNECT_IND 0x82
//#define 0x83
#define LMAN_DISCONNECT_CNF 0x84
//#define 0x85
//#define 0x86
//#define 0x87
//#define 0x88
#define LMAN_LINK_UP_IND 0x89
#define ENIP_BUFFER_FREE 0x8A
#define ENIP_BUFFER_FREE1 0x8B
#define ENIP_SOCK_DATA_READ 0x8C
#define ENIP_SOCK_CONNECTED 0x8D
#define ENIP_SOCK_CLOSED 0x8E
#define ENIP_SOCK_REMOTE_CLOSED 0x8F
#define ENIP_SOCK_ACCEPTED 0x90
#define ENIP_SOCK_ICMP_ERROR 0x91
#define ENIP_DNR_HOST_BY_NAME 0x94


#ifdef NEWSGOLD

#ifdef ELKA
#define DISPLACE_OF_EDGUI 0x90
#define DISPLACE_OF_USSDREQGUI_ID 0x44
#define DISPLACE_OF_EDGUI_ID 0x4C
#define DISPLACE_OF_IDLEGUI_ID 0x2C
#define DISPLACE_OF_IDLECANVAS 0x20

#else
#define DISPLACE_OF_EDGUI 0x88
#define DISPLACE_OF_USSDREQGUI_ID 0x44
#define DISPLACE_OF_EDGUI_ID 0x4C
#define DISPLACE_OF_IDLEGUI_ID 0x2C
#define DISPLACE_OF_IDLECANVAS 0x18

#endif

#define DISPLACE_OF_INCOMMINGGUI 0x34
#define DISPLACE_OF_OUTGOINGGUI 0x30
#define MSG_INCOMMING_CALL 0x6000
#define MSG_STATE_OF_CALL 0x6009
#define MSG_END_CALL 0x600B

#define MSG_HELPER_TRANSLATOR 0xDEAE
#define MSG_RECONFIGURE_REQ 0xDEAF
#define MSG_IPC 0xDEB0

#define MSG_SMS_RX 0x5803

#define MSG_USSD_RX 0x60E2
#define MSG_AUTOUSSD_RX 0x60E5
typedef struct{
  int pid_from;
  int msg; //MSG_USSD_RX
  void *pkt;
  char unk1;
  char encoding_type;
  char pkt_length;
  char unk2;
  void *data1;
} GBS_USSD_MSG;



#define MSG_PLAYFILE_REPORT 0x70BC
#define MSG_CSM_DESTROYED 0x6400
#define MSG_CSM_DESTROY_NOTIFY 0x6402
#define MSG_GUI_DESTROYED 0x640E
#define MSG_IDLETMR_EXPIRED 0x6401
#define MMI_CEPID 0x4209
#define LGP_NULL 0x7FFFFFFF
#define SET_SOFT_KEY_N 0
#define LGP_DOIT_PIC 0x7FFFC0FB
#define SET_SOFT_KEY_M 2 //mid
#else

#define DISPLACE_OF_EDGUI 0x50
#define DISPLACE_OF_USSDREQGUI_ID 0x40
#define DISPLACE_OF_EDGUI_ID 0x4C
#define DISPLACE_OF_IDLEGUI_ID 0x28
#define DISPLACE_OF_IDLECANVAS 0x14


#define DISPLACE_OF_INCOMMINGGUI 0x30
#define DISPLACE_OF_OUTGOINGGUI 0x2C
#define MSG_INCOMMING_CALL 0x08
#define MSG_STATE_OF_CALL 0x0B
#define MSG_END_CALL 0x0D

#define MSG_HELPER_TRANSLATOR 0x3F0
#define MSG_RECONFIGURE_REQ 0x3F1
#define MSG_IPC 0x3F2

#define MSG_SMS_RX 0xC2

#define MSG_USSD_RX 0x42
#define MSG_AUTOUSSD_RX 0x45

typedef struct{
  short pid_from;
  short msg; //MSG_USSD_RX
  void *pkt;
  char unk1;
  char encoding_type;
  char pkt_length;
  char unk2;
  void *data1;
} GBS_USSD_MSG;

#define MSG_CSM_DESTROYED 0x93
#define MSG_CSM_DESTROY_NOTIFY 0x92
#define MSG_GUI_DESTROYED 0x98
#define MSG_IDLETMR_EXPIRED 0x95
#define MMI_CEPID 0x4209
#define LGP_NULL 0x7FFF
#define SET_SOFT_KEY_N 1
#define LGP_DOIT_PIC 0x7FFFC0FB
#define SET_SOFT_KEY_M 2 //mid
#ifdef X75
#define MSG_PLAYFILE_REPORT 0x174
#else
#define MSG_PLAYFILE_REPORT 0x167
#endif

#endif

#define NAMECSM_MAGIC1 ((void *(*)(int))0x55AACCCC)
#define NAMECSM_MAGIC2 ((void (*)(void *))0x3333AA55)

typedef struct{
  unsigned long year;
  unsigned char month;
  unsigned char day;
} TDate;

typedef struct{
  unsigned char hour;
  unsigned char min;
  unsigned char sec;
  unsigned int millisec;
} TTime;

typedef struct{
  unsigned int type;
  unsigned int param2;
  unsigned short param3;
  unsigned short wstr[25];
}StructUSSDStr;

typedef struct{
  void *p1;
  void *p2;
  StructUSSDStr *pussdstr;
}StructUSSD;

typedef struct
{
  void *first;
  void *last;
  void (*data_mfree)(void *);
}LLQ;

typedef struct{
  int param0;
  int param1;
  int param2;
  int param3;
  int param4;
  int param5;
  int param6;
} GBSTMR;

typedef struct{
#ifdef NEWSGOLD
  int pid_from;
  int msg;
#else
  short pid_from;
  short msg;
#endif
  int submess;
  void *data0;
  void *data1;
} GBS_MSG;

typedef struct{
  void *p;
  int i;
}MUTEX;

typedef struct{
  void *next;
  void *prev;
  void /*CSM_DESC*/ *constr;
  int id;
  int state;
  int unk1;
  int unk2;
  LLQ gui_ll;
} CSM_RAM;

typedef struct{
  int (*onMessage)(CSM_RAM*,GBS_MSG*);
  void (*onCreate)(CSM_RAM*);
#ifdef NEWSGOLD
  int zero1;
  int zero2;
  int zero3;
  int zero4;
#endif
  void (*onClose)(CSM_RAM*);
  int datasize;
  int statesize;
  const int *states;
} CSM_DESC;

#ifdef NEWSGOLD
typedef struct{
  int id;
  CSM_RAM *current_msg_processing_csm;
  LLQ csm;
  LLQ cmd;
  LLQ csm_background;
} CSMQ;
#else
typedef struct{
  int id;
  CSM_RAM *current_msg_processing_csm;
  LLQ csm;
  LLQ cmd;
  int unk;
  int unk1;
  void *methods;
  int unk2;
  void *tmr;
  short cepid;
} CSMQ;
#endif

typedef struct{
#ifdef NEWSGOLD
  void *next;
  void *prev;
  int flag1;
  int parent_id;
  int prio;
  int (*proc)(CSMQ *, void *);
  CSMQ *csm_q;
  int id;
  int flag2;
#else
  void *next;
  void *prev;
  char flag1;
  int parent_id;
  int (*proc)(CSMQ *, void *);
  CSMQ *csm_q;
  CSM_RAM *cmd_csm;
#endif
}MMICMD;



typedef struct{
  int under_idle_id;
  int idle_id;
  CSMQ *csm_q;
} CSMROOT;

typedef struct{
  short x;
  short y;
  short x2;
  short y2;
} RECT;

typedef struct{
  char dummy[0x24];
} DRWOBJ;

typedef struct{
  unsigned short *wsbody;
  void *(*ws_malloc)(int);
  void (*ws_mfree)(void *);
  int isbody_allocated;
  unsigned short maxlen;
  unsigned short unk1;
} WSHDR;

typedef struct
{
  void *next;
  void *prev;
  void *data;
}EDITQ;

typedef struct
{
  void *next;
  void *prev;
}LLIST;

typedef struct
{
#ifdef NEWSGOLD
  const char *ext;
  int unical_id;
  char enabled_options;
  char obex_path_id;
  short menu_flag;
  const int *icon1;
  const int *icon2;
  int Open_lgpid;	//0x109
  int Options_lgpid;	//0x10A
  int Enter_lgpid;	//0x7FFFC0FB
  void *proc;
  void *altproc;
#else
  const char *ext;
  int unical_id;
  signed char enabled_options;
  unsigned char obex_path_id;
  unsigned short menu_flag;
  const int *icon1;
  const int *icon2; //skip on reg
  void *proc;
  void *altproc;
#endif
}REGEXPLEXT;

typedef struct
{
  int zero;
  unsigned const int *icon1;
  int unical_id;
  char obex_path_id;
  char unk;
  unsigned short menu_flag;
  char enabled_options;
  char not_used[3];
  WSHDR* ext;
  void *proc;
  void *altproc;
  unsigned const int *icon2;
}REGEXPLEXT_ARM_NEW;

#ifdef NEWSGOLD
typedef struct
{
  RECT *canvas;
  void *methods;
  void *definition;
  char state;
  char unk2;
  char unk3;
  char unk4;
  int color1;
  int color2;
  LLQ item_ll;
  int unk5;
  char unk6;
  char unk7;
  char unk8;
  char unk9;
  int unk10;
  int flag30;
}GUI;
#else
typedef struct
{
  RECT *canvas;
  void *methods;
  void *definition;
  char state;
  char unk2;
  char unk3;
  char unk4;
  int color1;
//  int color2;
  LLQ item_ll;
  int unk5;
  char unk6;
  char unk7;
  char unk8;
  char unk9;
  int unk10;
  int flag30;
}GUI;
#endif


typedef struct
{
  char zero;
  char unk1;
  short keys;
  GBS_MSG *gbsmsg;
}GUI_MSG;



//Keyhook return codes
//Process key to next keyhook and to gui
#define KEYHOOK_NEXT (0)
//Process key only to next keyhook, not to gui
#define KEYHOOK_NEXT_NOT2GUI (1)
//Break process and exit without processing in gui
#define KEYHOOK_BREAK (2)
//Break process and exit with or not processing in gui (selected by prev values 0/1)
#define KEYHOOK_ENDQ (3)


//Constants
//Attributes
#define FA_READONLY 0x0001
#define FA_HIDDEN 0x0002
#define FA_SYSTEM 0x0004
#define FA_DIRECTORY 0x0010
#define FA_ARCHIVE 0x0020

//Seek
#define S_SET 0
#define S_CUR 1
#define S_END 2

//Permissions
#define P_WRITE 0x100
#define P_READ 0x80

//Access
#define A_ReadOnly 0
#define A_WriteOnly 1
#define A_ReadWrite 2
#define A_NoShare 4
#define A_Append 8
#define A_Exclusive 0x10
#define A_MMCStream 0x20
#define A_Create 0x100
#define A_Truncate 0x200
#define A_FailCreateOnExist 0x400
#define A_FailOnReopen 0x800

#define A_TXT 0x4000
#define A_BIN 0x8000

// kbd msg:
#define KEY_DOWN        0x193
#define KEY_UP          0x194
#define LONG_PRESS      0x195
// 196 - sent 1 second after last key release, but not always?
// 197 - ? unknown kbd msg
// 198 - ? unknown kbd msg

// For kbd msg:
// submsg - scan Code:
#ifdef NEWSGOLD
#define LEFT_SOFT       0x01
#define RIGHT_SOFT      0x04
#define GREEN_BUTTON    0x0B
#define RED_BUTTON      0x0C
#define VOL_UP_BUTTON   0x0D
#define VOL_DOWN_BUTTON 0x0E
#define UP_BUTTON       0x3B
#define DOWN_BUTTON     0x3C
#define LEFT_BUTTON     0x3D
#define RIGHT_BUTTON    0x3E
#define ENTER_BUTTON	0x1A
#ifdef ELKA
#define POC_BUTTON 0x15
#define MEDIA_BUTTON	0x11
#define EL_PLAY_BUTTON	0x1D
#else
#define INTERNET_BUTTON 0x11
#endif
#define PLAY_BUTTON	0x15
#define CAMERA_BUTTON	0x14
#else
#define LEFT_SOFT       0x01
#define RIGHT_SOFT      0x04
#define GREEN_BUTTON    0x0B
#define RED_BUTTON      0x0C
#ifdef X75
#define VOL_UP_BUTTON   0x14
#define VOL_DOWN_BUTTON 0x15
#else
#define VOL_UP_BUTTON   0x0D
#define VOL_DOWN_BUTTON 0x0E
#endif
#define UP_BUTTON       0x3B
#define DOWN_BUTTON     0x3C
#define LEFT_BUTTON     0x3D
#define RIGHT_BUTTON    0x3E
#define ENTER_BUTTON	0x1A
#define INTERNET_BUTTON     0x11
#endif
#define PTT_BUTTON	0x27
// '*', '#', '0'-'9'

//Draw flags
#define TEXT_ALIGNLEFT 1
#define TEXT_ALIGNMIDDLE 2
#define TEXT_ALIGNRIGHT 4
#define TEXT_UNDERLINE 8
#define TEXT_INVERT 16
#define TEXT_OUTLINE 32
#define TEXT_PASSWORD 64
#define TEXT_NOFORMAT 128
#define TEXT_INVERT2 256

#define RECT_DOT_OUTLINE 1
#define RECT_FILL_WITH_PEN 2
#define RECT_DRAW_INVERT 4

#define LINE_DOTTED 1
#define LINE_DOTTED2 2

//Fonts

#ifdef NEWSGOLD

#ifdef ELKA

#define FONT_LARGE 0
#define FONT_LARGE_BOLD 1
#define FONT_LARGE_ITALIC 2
#define FONT_LARGE_ITALIC_BOLD 3
#define FONT_MEDIUM 4
#define FONT_MEDIUM_BOLD 5
#define FONT_MEDIUM_ITALIC 6
#define FONT_MEDIUM_ITALIC_BOLD 7
#define FONT_NUMERIC_SMALL 8
#define FONT_NUMERIC_SMALL_BOLD 9
#define FONT_NUMERIC_XSMALL 8
#define FONT_SMALL 8
#define FONT_SMALL_BOLD 9
#define FONT_SMALL_ITALIC 10
#define FONT_SMALL_ITALIC_BOLD 11
#define FONT_NUMERIC_LARGE 0
#define FONT_NUMERIC_MEDIUM 4

//#define SMALL_FONT 8
//#define MIDDLE_FONT 4

#else //#ifdef ELKA

#define FONT_LARGE 0
#define FONT_LARGE_BOLD 1
#define FONT_LARGE_ITALIC 2
#define FONT_LARGE_ITALIC_BOLD 3
#define FONT_MEDIUM 4
#define FONT_MEDIUM_BOLD 5
#define FONT_MEDIUM_ITALIC 6
#define FONT_MEDIUM_ITALIC_BOLD 7
#define FONT_NUMERIC_SMALL 8
#define FONT_NUMERIC_SMALL_BOLD 9
#define FONT_NUMERIC_XSMALL 10
#define FONT_SMALL 11
#define FONT_SMALL_BOLD 12
#define FONT_SMALL_ITALIC 13
#define FONT_SMALL_ITALIC_BOLD 14
#define FONT_NUMERIC_LARGE 15
#define FONT_NUMERIC_MEDIUM 16

//#define SMALL_FONT 11
//#define MIDDLE_FONT 4

#endif //#ifdef ELKA

#else //#ifdef NEWSGOLD

#define FONT_LARGE 0
#define FONT_LARGE_BOLD 1
#define FONT_LARGE_ITALIC 0
#define FONT_LARGE_ITALIC_BOLD 1
#define FONT_MEDIUM 2
#define FONT_MEDIUM_BOLD 3
#define FONT_MEDIUM_ITALIC 2
#define FONT_MEDIUM_ITALIC_BOLD 3
#define FONT_NUMERIC_SMALL 4
#define FONT_NUMERIC_SMALL_BOLD 5
#define FONT_NUMERIC_XSMALL 6
#define FONT_SMALL 7
#define FONT_SMALL_BOLD 8
#define FONT_SMALL_ITALIC 7
#define FONT_SMALL_ITALIC_BOLD 8
#define FONT_NUMERIC_LARGE 9
#define FONT_NUMERIC_MEDIUM 10

//#define MIDDLE_FONT 3
//#define SMALL_FONT 7

#endif //#ifdef NEWSGOLD

// Phone info IDs
#define PI_BASE_INFO1   0 // mch_x75idbi14
#define PI_BASE_INFO2   1 // m75i14#main_1.0_V79.27.1
#define PI_BASE_INFO3   2 // M_x75plat_MP_main_1.0
#define PI_BASE_INFO4   3 // M_minosemea_TH
#define PI_BUILD        4 // OFFICIAL
#define PI_DATETIME1	5	// �����-�� ��� ����
#define PI_DATETIME2    6
#define PI_SW_NUMBER    7 // ������ ��������
#define PI_VENDOR       8 // = SIEMENS :)
#define PI_MODEL        9 // ������ ��������
#define PI_LG           10 // = LangPack
#define PI_T9           11 // = T9


#ifdef NEWSGOLD
#define FIRST_UCS2_BITMAP 0xE12A
#else
#define FIRST_UCS2_BITMAP 0xE137
#endif


#define HEADLINE_STANDART        0x0
#define HEADLINE_FULLSCREEN      0x1
#define BODY_STANDART            0x2
#define BODY_TAB                 0x3
#define BOTTOM_STANDART          0x4
#define BOTTOM_FULLSCREEN        0x5
#define POPUP_OPTIONS            0x6
#define POPUP_FEEDBACK           0x7
#define SELECTION_1_LINE         0x8
#define SELECTION_2_LINE         0x9
#define SELECTION_3_LINE         0xA
#define SELECTION_ICON_ONLY      0xB
#define POPUP_SEARCH_LINE        0xC
#define POPUP_QUICK_ACCESS_FIELD 0xD
#define PROGRESS_STATUSBAR       0xE
#define TAB_SELECTED             0xF
#define TAB_UNSELECTED           0x10
#define STATUSBAR_STANDART       0x11
#define STATUSBAR_FULLSCREEN     0x12

typedef struct
{
#ifdef ELKA
  unsigned short w;
  unsigned short h;
  int bpnum; //For BW=1, 8bit=5, 16bit=8, 0x80 - packed
#else
  unsigned char w;
  unsigned char h;
  unsigned short bpnum; //For BW=1, 8bit=5, 16bit=8, 0x80 - packed
#endif
  unsigned char *bitmap;
}IMGHDR;

typedef struct
{
  RECT rc;
  int *icon;
  int lgp_id;
  int lgp_null; //LGP_NULL
}HEADER_DESC;

typedef struct
{
  int *icon;
  int lgp_id_small;
  int lgp_id_large;
  int zero;
  const int *softkeys; //{6,0x22,0x1D}
  int flag1; //0
  int flag2; //0x59D
}MENUITEM_DESC;

typedef struct
{
  short key1;
  short key2;
  int lgp_id;
}SOFTKEY_DESC;

typedef struct
{
  const SOFTKEY_DESC *desc;
  int n;
}SOFTKEYSTAB;

typedef void ( *MENUPROCS_DESC)(GUI *);

typedef struct
{
  int flag; //0,8 etc
  int (*onkey)(void *, GUI_MSG *);
  void (*ghook)(void *, int ); //GUI * gui, int cmd
  void *proc3;
  const int *softkeys; //{6,0x22,0x1D}, mb default for all items, if item.softkeys==NULL
  const SOFTKEYSTAB *softkeystab;
  int flags2; //2
//  0x00000001 //Icons presens
//  0x00000002 //
//  0x00000008 //
//  0x00000010 //Enable scroll text
//  0x00000020 //
//  0x00000040 //Disable scrollbar
//  0x00000080 //Enable "big letters" check
//  0x00000100 //Right align
//  0x00000200 //
//  0x00000400 //Disable breakline
//  0x00000800
//  0x00001000
//  0x00004000
//  0x00008000 //
//  0x00010000 //Enable search???
//  0x40000000
//  0x80000000

  void (*itemproc)(void *, int, void *); //Called when draw item
  const MENUITEM_DESC *items; //Table of items desc;
  const MENUPROCS_DESC *procs;//  void ** procs; //Table of procs when item selected
  int n_items; //Number of items
}MENU_DESC;

typedef struct
{
  int flag; //0,8 etc
  int (*onkey)(void *, GUI_MSG *);
  void (*ghook)(void *, int ); //GUI * gui, int cmd
  void *proc3;
  const int *softkeys; //{6,0x22,0x1D}, mb default for all items, if item.softkeys==NULL
  const SOFTKEYSTAB *softkeystab;
  int flags2; //2
  void (*itemproc)(void *, int, void *); //Called when draw item
  const MENUITEM_DESC *items; //Table of items desc;
  const MENUPROCS_DESC *procs;//  void ** procs; //Table of procs when item selected
  int n_items; //Number of items
  int n_lines; //Number of lines in selected item
}ML_MENU_DESC;

#pragma pack(1)
typedef struct{
#ifdef NEWSGOLD
  char unk0[40];
  unsigned int file_size;
  short file_attr;
  unsigned int create_date_time;
  char unk1[2];
  char folder_name[128];
  char unk2;
  char file_name[128];
  char unk3[11];
  short wsfolder_name[128+1];
  short wsfile_name[128+1];
#else
  char unk1[14];
  short file_attr;
  unsigned int create_date_time;
  unsigned int file_size;
  char unk2[16];
  char folder_name[128];
  char unk3;
  char file_name[271];
#endif
}DIR_ENTRY;
#pragma pack()

typedef struct
{
  char unk1;
  char unk2;
  char unk3;
  char unk4;
  unsigned int size;
  char unk5[28];
  int file_attr;
}FSTATS;


typedef struct
{
  unsigned short ch_number;
  unsigned short ci;
  unsigned short lac;
  char power;
  char c1;
  char c2;
  char unk;
  unsigned short unk2;
}RAMNET;

//-----------------------------------------

typedef struct
{
  int one;
  int (*onKey)(GUI *gui, GUI_MSG *msg);
  void (*global_hook_proc)(GUI *gui, int cmd);
  void *locret;
  int zero1;
  const SOFTKEYSTAB *softkeystab;
  RECT rc;
  int font;
  int _100;
  int _101;
  int zero2;
//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  int zero3;
//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
//  0x40000000 - Поменять местами софт-кнопки
  int _0x40000000;
}INPUTDIA_DESC;

typedef struct
{
  char type;
  void *user_pointer;
  unsigned short cur_item;
  WSHDR *ws;
}USR_MENU_ITEM;

typedef struct
{
  unsigned short invert;  // |1
  unsigned short bitmask;
  char font;              // |2
  char align;             // |4
  char pen[4];            // |8
  char brush[4];          // |0x10
}EDITC_OPTIONS;

#pragma pack(2)
typedef struct
{
  char type;
  char unk2[3];
  int flag;
  char zero_cbox;  // if text input field: lang 0 - default, 2 - english
  char unk5;
  EDITC_OPTIONS ed_options;
  short maxlen;
  short num_of_items_cbox;
  short start_item_cbox;
  short unk9;
  short unk10;
  short unk11;
  int unk12;
  WSHDR *pWS;
}EDITCONTROL;
#pragma pack()

//EditControlTypes
#define ECT_READ_ONLY 0
#define ECT_HEADER 1
#define ECT_NUMBER_TYPING 2
#define ECT_NORMAL_TEXT 3
#define ECT_CURSOR_STAY 4
#define ECT_FIXED_STR_NUM 5
#define ECT_NORMAL_NUM 6
#define ECT_COMBO_BOX 7
#define ECT_READ_ONLY_SELECTED 8
#define ECT_LINK 9
#define ECT_CALENDAR 10
#define ECT_TIME 11

//EditControlFlags
#define ECF_NORMAL_STR 0
#define ECF_SKIP 4
#define ECF_INVISIBLE_CURSOR 8
#define ECF_PASSW 0x10
#define ECF_DELSTR 0x20
#define ECF_APPEND_EOL 0x40
#define ECF_SET_CURSOR_END 0x80

#define ECF_DISABLE_NUM 0x100
#define ECF_DISABLE_SMALL_LETTERS 0x200
#define ECF_DISABLE_BIG_LETTERS 0x400

#define ECF_DEFAULT_BIG_LETTER 0x1000  // Enable big letter after ". "
#define ECF_DISABLE_T9 0x2000
#define ECF_DEFAULT_ITAP 0x4000
#define ECF_DEFAULT_DIGIT 0x8000

#define ECF_DISABLE_EOLCHAR 0x10000  // In chartable
#define ECF_DISABLE_MINUS 0x20000  // Also disable #
#define ECF_DISABLE_POINT 0x40000  // Also disable *
#define ECF_LONGDIEZ_EQ_QUESTION 0x80000
#define ECF_ENABLE_TEXT_FORMAT 0x800000
#define ECF_MARKED 0x2000000
#define ECF_GRAY 0x4000000

//TextInput Dialog ghook commands
#define TI_CMD_CREATE          2
#define TI_CMD_DESTROY         3
#define TI_CMD_REDRAW          7
#define TI_CMD_UNFOCUS         9
#define TI_CMD_FOCUS           10
#define TI_CMD_SUBFOCUS_CHANGE 12
#define TI_CMD_COMBOBOX_FOCUS  13

/*
!!!! DELETED !!!!
!!!! Use EDIT_GetCursorPos & EDIT_SetCursorPos
#ifdef NEWSGOLD
#ifdef ELKA
#define EDIT_CURSOR_POS(DATA) (((int ****)DATA)[0x90/4][0x8C/4][0x28/4][0x38/4])
#else
#define EDIT_CURSOR_POS(DATA) (((short ****)DATA)[0x88/4][0x84/4][0x28/4][0x34/2])
#endif
#else
#define EDIT_CURSOR_POS(DATA) (((short ****)DATA)[0x50/4][0x4C/4][0x28/4][0x30/2])
#endif
*/
//Menu flags and screen displace
#ifdef NEWSGOLD
#ifdef ELKA
#define MENU_FLAG3 3
#define MENU_FLAG2 0x5A2
#define YDISP (24)
#else
#define MENU_FLAG3 3
#define MENU_FLAG2 0x59D
#define YDISP (0)
#endif
#else
#define MENU_FLAG3 3
#define MENU_FLAG2 0x578
#define YDISP (0)
#endif


#define VOLUME 0x12
#define VOLUME_ALARMCLOCK 0xD
#define VOLUME_INCALL 2

typedef struct
{
#ifdef NEWSGOLD
  short field_0;
  char no_data;
  char item_type;
  int field_4;
  void *data;
#else
  char field_0;
  char no_data;
  char field_2;
  char item_type;
  int field_4;
  void *data;
#endif
}AB_UNPRES_ITEM;

typedef struct{
#ifdef NEWSGOLD
  short NrOfFlds;
  short number_of_records;
  short NrAllocFlds;
  short field_6;
  short NrJ;
  char field_A;
  char field_B;
  AB_UNPRES_ITEM *record_list;
  char EntTp;
  char field_11;
  short EntId;
  int field_14;
  int field_18;
#else
  short field_0;
  short field_2;
  short field_4;
  short number_of_records;
  short field_8;
  short field_A;
  AB_UNPRES_ITEM *record_list;
  char field_10;
  char field_11;
  short field_12;
  int field_14;
  int field_18;
#endif
}AB_UNPRES;

#pragma pack(1)
typedef struct
{
  char _1D;
  char format;
  char data_size;
  char _0_1;
  char _0_2;
//  char _0_3;
  char data[128];
}PKT_NUM;
#pragma pack()

//================================
// Sockets
//================================
typedef struct
{
  sa_family_t family; //1
  unsigned short port; //network order
  unsigned int ip; //network order
  unsigned int unk1;
  unsigned int unk2;
}SOCK_ADDR;

#pragma pack(2)
typedef struct
{
  unsigned short _0x0080;
  unsigned short _0xFFFF;
  unsigned short _0x0000;
}REGSOCKCEPID_DATA;
#pragma pack()

typedef struct
{
  char body[0x204];
}CTX_NAPDEF;

typedef struct
{
  unsigned int len;
  CTX_NAPDEF *ctx_napdef;
  unsigned int zero;
  CTX_NAPDEF napdef;
}NAP_PARAM_CONT;

typedef struct
{
#ifdef NEWSGOLD
  int zero;
  void *native_profile;
  char _1;
  char _4;
  unsigned short _0;
  NAP_PARAM_CONT *NapParameterContainer;
#else
  char unk1;
  char *unk;
  char one;
  char isactivated;
#endif
}LMAN_DATA;

#define IP_ADDR(A,B,C,D) (((unsigned long)A<<24)|((unsigned long)B<<16)|((unsigned long)C<<8)|((unsigned long)D<<0))

typedef struct{
#ifdef NEWSGOLD
  unsigned short repeat_num;  //0 - non limited
  unsigned short unk;
  int time_between_play;
  int play_first; // 0 - play all
  int volume;
  int unk5;
  int unk6;
  int unk7;
  int unk8;
  int unk9;
#else
#ifdef X75
  unsigned short repeat_num;  //0 - non limited
  unsigned short unk;
  int time_between_play;
  int play_first; // 0 - play all
  int volume;
  int unk4;     //0x80000000
  int unk5;     //1
  int unk6;     //0
  int unk7;
#else
  unsigned short repeat_num;  //0 - non limited
  unsigned short unk;
  int time_between_play;
  int play_first; // 0 - play all
  int volume;
  int unk5;
  int unk6;
#endif
#endif
}PLAYFILE_OPT;


typedef struct
{
 char data[0xB2];
}PDU;

typedef struct
{
  const char *name_to;
  const char *name_from;
  void *data;
}IPC_REQ;

typedef struct
{
  unsigned short type; //00
  WSHDR *wfilename; //04
  int unk_08 ; //08
  int unk_0C; //0C
  int unk_10 ; //10
  int unk_14 ; //14
  long length; //18 <-- return
  int unk_1C; //1C
  int unk_20 ; //20
} TWavLen;


typedef struct
{
  char yearNormBudd; //1 - norm, 2 - buddhist
  char dateFormat;
  char timeFormat; //0-24h, 1-12h
  char timeZone; //internal representation
  char isAutoTime1;
  char isAutoTime2;
}TDateTimeSettings;

typedef struct
{
#ifdef NEWSGOLD
  unsigned int type;  //from debugger 0x400 general(size) | 0x4000 picture, | 0xA800(3gp) video, | 0x1000 audio (wav/midi), 0x1800 (mp3/aac)
  WSHDR *filename;
  WSHDR *resolution_ws;
  int uid;
  unsigned short width;
  unsigned short height;
  WSHDR *duration_mp3_ws;
  unsigned int duration_mp3;
  WSHDR *duration_wav_ws;
  unsigned int duration_wav;
  WSHDR *tag_title_ws;
  WSHDR *tag_artist_ws;
  WSHDR *tag_album_ws;
  WSHDR *tag_track_ws;
  WSHDR *tag_year_ws;
  WSHDR *unk_tag_2_ws;
  WSHDR *bitrate_ws;
  WSHDR *audio_frequency_ws;
  WSHDR *size_ws;
#else
  unsigned short type;  // | 0x8000 picture, | 0x4000 video, | 0x2000 audio
  WSHDR *filename;
  WSHDR *text_resol;
  int uid;
  unsigned short width;
  unsigned short height;
  WSHDR *duration_wav_ws;
  unsigned int duration_wav;
  WSHDR *video_ws;
  int video_len;
#endif
} FILE_PROP;

typedef struct
{
  int mode; //0-normal mode, 1-select mode
  int dir_enum; //0x26 by default
  WSHDR* path_to_file; //path to file
  WSHDR* file_name; //put cursor to this file
  int unk5;
  int is_exact_dir;
  int unk7;
  int unk8;
  int unk9;
  int unk10;
  int unk11;
  WSHDR* full_filename;
  int unk13;
  int (*user_handler)(void*); //called in select mode
  void* this_struct_addr;
  int unk16;
  int unk17_26[10];
}NativeExplorerData;

typedef int  ( MenuSearchCallBack)(void *gui,WSHDR * searchstr);  // return -1


typedef struct POPUP_DESC
{
  int flag; //8, 0
  int (*onkey)(void *, GUI_MSG *);
  void (*ghook)(void *, int );
  void *proc3; //locret
  const int *softkeys;
  const SOFTKEYSTAB *softkeystab;
  int flags2; //1
  int lgp_null; //?
  const int *icons;
  int zero0; //0
  int font; //2
  int _100;
  int _101;
  int time; //0
} POPUP_DESC;

typedef struct SMS_POS_INDEX_DATA
{
  char unk0;
  char unk1;
  short pos_index;
} SMS_POS_INDEX_DATA;

typedef struct INDEX_ID_DATA
{
  void *unk_proc0; //0xA09D901D S7Cv47
  void *unk_proc1; //0xA09D9025 S7Cv47
  short index; //1,2,3 ...
  char unk[6];
  short unk1; //another index ?
  char cnt_all;
  char cnt_received; // =cnt0;
  unsigned short *data_id; //depend on cnt, for GetSmsPosIndex to get pos_index
  short unk2; //0, 0x700
  short unk3; //0
  char unk4; // 3
  char unk5; //0,3
  char type; // 0, in read, 1, in new, 3,sent
  char new_cnt_data; // ?
} INDEX_ID_DATA;

typedef struct SMS_DATA_LIST
{
  void *next;
  void *prev;
  INDEX_ID_DATA *index_id_data;
  //short unk0; //0xB2 pdu_size ?
  //short unk1; //0x4077 SMS_SIMIF_SM_CEPID ?
  //int unk2; //0x190 ?
  //void *unk3; //a list ?
} SMS_DATA_LIST;

typedef struct SMS_DATA_LLIST
{
  SMS_DATA_LIST *first;
  SMS_DATA_LIST *last;
  void *unk_proc; //0xA09DA18D //S7Cv47
} SMS_DATA_LLIST;

typedef struct SMS_DATA_ROOT
{
  SMS_DATA_LLIST in_msg;
  SMS_DATA_LLIST out_msg;
  short unk_0xFFFF;
  short unk_0_1;
  short cnt_msg_in_read;
  short cnt_in_new_sms_dat;
  short cnt_in_new_opwv; //? ems ?
  short cnt_sms_sent;
  short cnt_sms_draft;
  short unk_0_2;
  short cnt_freespace_data; // -0x28 == ?
  short cnt_in_data;
  short cnt_new_in_data;
  short cnt_sent_data;
  short cnt_draft_data;
  short unk_0_3; //maybe sending box
} SMS_DATA_ROOT;

typedef struct AbNumList
{
  void *next; //0
  void *prev; //0
  int flag_data; //type?
  void *data; //pkt_num
} AbNumList;

typedef struct NativeAbData
{
  AbNumList *first;
  AbNumList *last;
  void *mfree_adr;
  void *unk;
} NativeAbData;

typedef struct SS_RAM
{
  CSM_RAM ss_csm;
  void *unk;
  int ss_gui_id; //draw screensaver
  int keylock_gui_id; //keylock screen
} SS_RAM;

typedef struct TABGUI_DESC
{
  int flag; //8,a,b
  int (*onkey)(void *, GUI_MSG *); //,null
  void (*ghook)(void *, int ); //,null
  void *locret; //,null
  const int *softkeys;//,null
  const SOFTKEYSTAB *softkeystab; //,null
} TABGUI_DESC;


typedef struct EAM_DATA
{
  short dat_index; //
  char unk_FF[2];
  int opmsg_id; //browser killer, -1
  char unk[8];
} EAM_DATA;

typedef struct RAM_EMS_ADMIN
{
//  char unk_FF[0x10];
  int unk;
  EAM_DATA data[101];
} RAM_EMS_ADMIN;


typedef struct TVIEW_DESC
{
  int flag;
  int (*onkey)(void *, GUI_MSG *);
  void (*ghook)(void *, int);
  void (*locret)(void);
  const int *softkeys;
  const SOFTKEYSTAB *softkeystab;
  RECT rc;
  int font;
  int unk1; //0x64, 0x81
  int unk2; //0x65, 0x82
  int unk3; //0
  int unk4; //0,1,2
} TVIEW_DESC;

typedef struct LIGHT_PARAM
{
	char timeout; // Таймаут гашения
	char unk0; // Нечто загадочтное, бывает 0, или 5
	char perm_illum; // Не совсем понятно, похоже уровень, который будет удерживаться при вызове IllumTimeRequest,
                            //переписывается вызовом SaveMaxIllumination(), и зачем-то ограничено 80%
	char max_illum; // Ну здесь как известно яркость подсветки
} LIGHT_PARAM;

typedef struct I2C_MSG
{
  char chip_addr; // 7-ми битный адрес чипа(см.datasheet)
#ifdef NEWSGOLD
  char unk1;
  char unk2;
  char unk3;
  short nRegister; // номер регистра
#else
  char  unk1;
  short nRegister;// номер регистра
  char  unk2;
  char  tf; // Суда дописываеться потом самой ф-ей байтик как бы ID ф-ии
            // (1 - i2c_transfer, 2 - i2c_receive, 4 - i2c_unknown)
#endif
  short cb_data;
  int (*callback)(void *i2c_msg);
  void *data;
  int size;   //размер данных
} I2C_MSG;


#define DRAWBUFFER_DEPTH_TYPE_16BIT 4
#define DRAWBUFFER_DEPTH_TYPE_32BIT 5

#define TP_PIXEL_8BIT  0xC0
#define TP_PIXEL_16BIT 0xE000

typedef struct{
  int  bpnum;    // 16bit = 8, 32bit = 0x0A, 0x80 - packed
  int  w;
  int  h;
  int  zero;     // 0x00000000
  int  tp_pixel; // Пиксель прозрачности 16 бит 0xE000, 8 бит 0xC0
  char *bitmap;
}EIMGHDR;

#define LCD_DISPQUEUE_CEPID 0x4200

#ifdef NEWSGOLD
#ifdef ELKA
#define LCD_DISPLAY_LAYER 0x6423

#else  /*ELKA*/
#define LCD_DISPLAY_LAYER 0x6422

#endif  /* ELKA */
#else  /* NEWSGOLD */
#define LCD_DISPLAY_LAYER 0

#endif  /* NEWSGOLD */

typedef struct{
  int    w;       // Ширина экрана
  int    h;       // Высота экрана
  RECT   unk_rc;  //
  RECT   rc;      // Глобальные границы отрисовки
  void  *buf;     // Адрес буфера экрана
  char   depth;   // Глубина цвета
  char   unk_space[139];
}LCDLAYER;


typedef struct {
 #ifdef NEWSGOLD
   unsigned int    id;         // ID группы (первый байт от CepID)
   char           *name;       // Указатель на имя, создаваемого Nucleus таска
   unsigned short  prio;       // Приоритет, создаваемого Nucleus таска
   unsigned short  stacksize;  // Размер стека, создаваемого Nucleus таска
   unsigned int    maxmembers; // Максимальное количество членов в группе
 #else
   unsigned char   id;         // ID группы (первый байт от CepID)
   unsigned char   prio;       // Приоритет, создаваемого Nucleus таска
   unsigned short  stacksize;  // Размер стека, создаваемого Nucleus таска
   unsigned short  maxmembers; // Максимальное количество членов в группе
 #endif
}PGROUP;


typedef struct
{
    int a;
}GBSPROC;
typedef short Word16;
 typedef long int Word32 ;
 typedef signed char Word8;
typedef unsigned char UWord8;
#ifdef __USE_SPL__
#include <spl/process.h>
#include <spl/memctl.h>
#endif

/* хедеры эльфпака */
#include <ep3/loader.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "directswicall.h"
void kill_elf();

#ifdef __cplusplus
}
#endif

#endif


