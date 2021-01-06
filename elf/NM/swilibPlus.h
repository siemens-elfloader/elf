#include "..\inc\swilib.h"

typedef struct _EAM_DATA
{
  short dat_index; //
  char unk_FF[2];
  int opmsg_id; //browser killer, -1
  char unk[8];
}EAM_DATA;
typedef struct
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
}INDEX_ID_DATA;

typedef struct _RAM_EMS_ADMIN
{
//  char unk_FF[0x10];
  int unk;
  EAM_DATA data[101];
}RAM_EMS_ADMIN;
typedef struct
{
  void *next;
  void *prev;
  INDEX_ID_DATA *index_id_data;
  //short unk0; //0xB2 pdu_size ?
  //short unk1; //0x4077 SMS_SIMIF_SM_CEPID ?
  //int unk2; //0x190 ?
  //void *unk3; //a list ?
}SMS_DATA_LIST;
typedef struct
{
  CSM_RAM ss_csm;
  void *unk;
  int ss_gui_id; //draw screensaver
  int keylock_gui_id; //keylock screen
}SS_RAM;

typedef struct
{
  int flag; //8,a,b
  int (*onkey)(void *, GUI_MSG *); //,null
  void (*ghook)(void *, int ); //,null
  void *locret; //,null
  const int *softkeys;//,null
  const SOFTKEYSTAB *softkeystab; //,null
}TABGUI_DESC;

typedef struct
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
}POPUP_DESC;

typedef struct
{
  char unk0;
  char unk1;
  short pos_index;
}SMS_POS_INDEX_DATA;

typedef struct
{
  SMS_DATA_LIST *first;
  SMS_DATA_LIST *last;
  void *unk_proc; //0xA09DA18D //S7Cv47
}SMS_DATA_LLIST;

typedef struct
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
}SMS_DATA_ROOT;

typedef struct
{
  void *next; //0
  void *prev; //0
  int flag_data; //type?
  void *data; //pkt_num
}AbNumList;

typedef struct
{
  AbNumList *first;
  AbNumList *last;
  void *mfree_adr;
  void *unk;
}NativeAbData;
typedef struct
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
}TVIEW_DESC;


//////////////////////////////////////////////////////////////////////////
#pragma swi_number=0x2D5
__swi __arm void UnpackNumPkt(PKT_NUM *pkt, char *buf, int maxlen);
#pragma swi_number=0x2A5
__swi __arm void *GetMultiLinesMenuGUI(void *malloc_adr, void *mfree_adr);
#pragma swi_number=0x2A7
__swi __arm void SetMenuToGUI(void *gui, const void *menu_desc);
#pragma swi_number=0x2A6
__swi __arm void SetHeaderToMenu(void *gui, const HEADER_DESC *hdr, void *malloc_adr);
#pragma swi_number=0x2BB
__swi __arm void *GetTabGUI(void *malloc_adr, void *mfree_adr);
#pragma swi_number=0x2BC
__swi __arm void SetGUIDefinition(void *gui, const void *definition);
#pragma swi_number=0x2BD
__swi __arm int SetGUIToTabGUI(void *tabgui, int n, const int *tabicons, void *gui);
#pragma swi_number=0x2BE
__swi __arm int SetCursorTab(void *tab_gui, int n);
#pragma swi_number=0x2BF
__swi __arm int UpdateTab1stItem(void *tab_gui, int unk_0);
#pragma swi_number=0x68
__swi __arm SS_RAM *GetScreenSaverRAM(void);
#pragma swi_number=0x2B3
__swi __arm NativeAbData *AllocNativeAbData(void);
#pragma swi_number=0x2B7
__swi __arm int GetNativeAbDataStatus(NativeAbData *nab, int n); //9,not filled, 1, filled
#pragma swi_number=0x2B5
__swi __arm int GetNativeAbDataType(NativeAbData *nab, int n);
#pragma swi_number=0x2B6
__swi __arm WSHDR *GetNumFromNativeAbData(NativeAbData *nab, int type, int unk0); //unk0=0
#pragma swi_number=0x2D3
__swi __arm int GetFilledNAbDataCount(NativeAbData *nab);
#pragma swi_number=0x2D4
__swi __arm void *GetDataFromNAbData(NativeAbData *nab, int n);
#pragma swi_number=0x2B4
__swi __arm int FreeNativeAbData(NativeAbData *ab_data);
#pragma swi_number=0x2B8
__swi __arm int SetNumToNativeAbData(NativeAbData *abd, int unk, WSHDR *num);
#pragma swi_number=0x2B9
__swi __arm unsigned int OpenNativeAddressbook(int type, int unk1, int unk2, void *data);
#pragma swi_number=0x2AE
__swi __arm void *GetHeaderPointer(void *gui);
#pragma swi_number=0x2AF
__swi __arm void SetHeaderText(void *hdr_pointer, WSHDR *txt, void *malloc_adr, void *mfree_adr);
#pragma swi_number=0x2AB
__swi __arm void *GetPopupUserPointer(void *gui);
#pragma swi_number=0x2C4
__swi __arm int GetProfileVolumeSetting(int profile, int type);
#pragma swi_number=0x2AA
__swi __arm int CreatePopupGUI_ws(int flag, void *user_pointer, const POPUP_DESC *, WSHDR *msg);
#pragma swi_number=0x2A9
__swi __arm int CreatePopupGUI(int flag, void *user_pointer, const POPUP_DESC *, int lgp_msg);
#pragma swi_number=0x82C5
__swi __arm RAM_EMS_ADMIN *RAM_EMS_Admin();
#pragma swi_number=0x2B2
__swi __arm int GetSmsPosIndex(SMS_POS_INDEX_DATA *buf, int data_id);
#pragma swi_number=0x82B1
__swi __arm SMS_DATA_ROOT *SmsDataRoot();
#pragma swi_number=0x2AC
__swi __arm int DeleteSMS(int index, short *del_cnt); //return 0x3E8
#pragma swi_number=0x2C0
__swi __arm int GetCursorTab(void *tab_gui);
#pragma swi_number=0x2C1
__swi __arm void *GetGuiByTab(void *tab_gui, int n);
#pragma swi_number=0x2AD
__swi __arm int SetSmsStatus(int index, int type);
#pragma swi_number=0x2A4
__swi __arm void *GetMenuGUI(void *malloc_adr, void *mfree_adr);
#pragma swi_number=0x007F
__swi __arm int IsPlayerOn();

#pragma swi_number=0x2DA
__swi __arm void *TViewGetUserPointer(void *gui);
#pragma swi_number=0x2D6
__swi __arm void *TViewGetGUI(void *malloc_adr, void *mfree_adr);
#pragma swi_number=0x2D7
__swi __arm void TViewSetDefinition(void *gui, const TVIEW_DESC *);
#pragma swi_number=0x2D8
__swi __arm void TViewSetText(void *gui, WSHDR *text, void *malloc_adr, void *mfree_adr);
#pragma swi_number=0x2D9
__swi __arm void TViewSetUserPointer(void *gui,void *user_pointer);





/**/
