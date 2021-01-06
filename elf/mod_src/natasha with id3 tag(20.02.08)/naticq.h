#ifndef _NATICQ_H_
  #define _NATICQ_H_
/*
  Типы данных, общие для всех модулей проекта
*/

typedef struct
{
  void *next;
  int acked;
  unsigned long ID;
  int type;
  char hdr[80]; //Заголовок
  char text[];
}LOGQ;

typedef struct
{
  void *next;
  void *prev;
  unsigned int isgroup;
  unsigned int uin;
  unsigned int group;
  char name[64];
  unsigned short state;
  unsigned short xstate;
#ifdef EVILFOX
  int bot_msg;
#endif
  int just_now;
  int change;
  int isunread;
  int unread_msg;
  int req_add;
  int req_drawack;
  LOGQ *log;
  char *answer;
  LOGQ *last_log;
  int isactive;
  int msg_count;
  char *xtext;
  int req_xtext;
}CLIST;

typedef struct
{
  unsigned long uin;
  unsigned short type;
  unsigned short data_len;
}PKT;

typedef struct
{
  PKT pkt;
  char data[16384];
}TPKT;

#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

enum ISTATUS {IS_OFFLINE,IS_INVISIBLE,IS_AWAY,IS_NA,IS_OCCUPIED,IS_DND,IS_DEPRESSION,IS_EVIL,IS_HOME,IS_LUNCH,
IS_WORK,IS_ONLINE,IS_FFC,IS_MSG,IS_UNKNOWN,IS_GROUP,IS_GROUPOFF,IS_NULLICON,
//
ICON_ADDCONTACT,
ICON_HEAD,
ICON_LOGO,
ICON_PING,
ICON_SETTINGS,
//
ICON_ALL_CAN_SEE,
ICON_VISLIST_CAN_SEE,
ICON_INVISLIST_CANNOT_SEE,
ICON_CONTACTLIST_CAN_SEE,
ICON_NOBODY_CAN_SEE,
//
TOTAL_ICONS,
//
IS_ANY=0xFFFFFFFF,IS_FILTER_T9KEY=0xFFFFFFFE};

/*
// Константы статусов
#define IS_OFFLINE 0
#define IS_INVISIBLE 1
#define IS_AWAY 2
#define IS_NA 3
#define IS_OCCUPIED 4
#define IS_DND 5
#define IS_DEPRESSION 6
#define IS_EVIL 7
#define IS_HOME 8
#define IS_LUNCH 9
#define IS_WORK 10
#define IS_ONLINE 11
#define IS_FFC 12
#define IS_MSG 13
#define IS_UNKNOWN 14
#define IS_GROUP 15
//#define IS_GROUPOFF 16
#define IS_NULLICON 17
#define IS_ANY 0xFFFFFFFF
#define IS_FILTER_T9KEY 0xFFFFFFFE
*/

#endif


