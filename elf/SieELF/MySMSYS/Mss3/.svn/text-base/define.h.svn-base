#ifndef _DEFINE_H_
#define _DEFINE_H_


#define TYPE_UNK	0
//#define TYPE_OUT	1
#define TYPE_SENT       1
#define TYPE_IN_R	2 //readed
#define TYPE_IN_N 3 //new
#define TYPE_DRAFT	4
#define TYPE_IN_ALL 5
#define TYPE_FILTER 0xF
//msg_type
#define ISSMS 0 //00000000
#define ISEMS 1 //00000001
#define ISREPORT 2 //00000010
#define ISDES 4 //00000100 //is destroyed, or not full received
#define IS7BIT 8 //00001000
#define ISUNKE 16 //00010000 //unk text encode type
#define ISUNKT 32 //00100000 //unk sms type
#define ISFILE 64 //01000000

#define MAX_TEXT 2048

//
#define SEGN_MAX 70
#define SEG7_MAX 160

typedef struct _SDLIST
{
  _SDLIST *next;
  _SDLIST *prev;
  int type;
  int dat_index;
  int opmsg_id;
  int msg_prop;
  int cnt_r;
  char *fname;
  char number[32];
  char time[32];
  WSHDR *text;
}SDLIST;

#define MSS_VERSION 2 //add type;
typedef struct _MSS_FILE_P1
{
  char header[8];
  int version;
  char time[32];
  char number[32];
}MSS_FILE_P1;


typedef struct _MSS_FILE_P2
{
  char header[8];
  int version;
  int type;
  char time[32];
  char number[32];
}MSS_FILE_P2;

#define MAX_FILE 10000

typedef struct _DLG_CSM
{
  CSM_RAM csm_ram;
  int gui_id;
  void *dlg;
}DLG_CSM;


typedef struct _DLGCSM_DESC
{
  CSM_DESC csm_desc;
  WSHDR csm_name;
}DLGCSM_DESC;

#define ELFFNAME "Mss3CPP"
#define ELFFNAMED "Mss3D"


#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);

#pragma swi_number=0x80CB
__swi __arm char *RamRingtoneStatus(); //0 on, 1, off

#pragma swi_number=0x27 
__swi __arm void AddIconToIconBar(int pic, short *num);

#ifdef NEWSGOLD
#ifdef ELKA
#define ICON_BLANK 0x538
#else
#ifdef S68
#define ICON_BLANK 0x574
#else
#define ICON_BLANK 0x564
#endif
#endif
#endif

#define LGP_SAVE_TO_AB 0xD50



#endif

