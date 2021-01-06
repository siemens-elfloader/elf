#ifndef _MAILCLIENT_H_
  #define _MAILCLIENT_H_
/*
  Типы данных, общие для всех модулей проекта
*/

#define wslen(ws) ws->wsbody[0]

extern long  strtol (const char *nptr,char **endptr,int base);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);
unsigned int char8to16(int c, int type);

extern const char MAIL_LOGIN[];
extern const char MAIL_PASS[];
extern const char EML_PATH[];
extern const int DEFAULT_ACTION;
extern const unsigned int LOAD_IF_LESS;
extern const int IF_DEL_AUX;
extern const char POP3_ADRESS[];
extern const unsigned int POP3_PORT;
extern const char SAVE_AS_FOLDER[];
extern const int DEL_AFTER_LOAD;
extern void kill_data(void *p, void (*func_p)(void *));
extern const char SMSFORWARD[];

extern const char I_UNREAD[];
extern const char I_READ[];
extern const char I_HEADER[];
extern const char I_HEADER_ATT[];
extern const char I_MES_UNREAD_ATT[];
extern const char I_MES_READ_ATT[];
extern const char I_MES_DOWN[];
extern const char I_MES_DEL[];

#define M_LOAD_HEADER 0
#define M_LOAD_FULL 1
#define M_HEADERS_LOADED 2
#define M_FULL_LOADED 3
#define M_DELETE 4
#define M_IS_BIG_LETTER 0xFFFFFFFF

#define POP_GREETING 0
#define POP_VER_LOGIN 1
#define POP_VER_PASS 2
#define POP_GET_STAT 3
#define POP_GET_UIDL_LIST 4
#define POP_GET_LIST 5
#define POP_PROCESS_LIST 6
#define POP_RECEIVE_HEADERS 7
#define POP_RECEIVE_MESSAGE 8
#define POP_DELETE_MESSAGE 9

#define MDB_MAGIC 0x01024244
#define MDB_NAME "mails.db"

#define IPC_DAEMON_NAME "MailDaemon"
#define IPC_VIEWER_NAME "MailViewer"
//IPC messages

enum IPC_MSGS
{
  IPC_DAEMON_LOGON,
  IPC_DAEMON_LOGOFF,
  IPC_VIEWER_LOGON,
  IPC_VIEWER_LOGFF,
  IPC_CHECK_MAILBOX,
  IPC_LOADING_FINISHED,
  IPC_STOP_CHECKING,
  IPC_CHECK_DOUBLERUN
};

#pragma pack(1)
typedef struct
{
  unsigned int magic;
  unsigned short uidl_len;
  unsigned char state;
  unsigned char is_read;  
  unsigned int mail_size;
  char hdr[128];
}MAIL_DB;
#pragma pack()

typedef struct
{
  void *next;
  char *uidl;
  unsigned int state;
  unsigned int is_read;
  unsigned int mail_size;
  int num_in_list;
}ML_DAEMON;

typedef struct
{
  void *next;
  char *uidl;
  unsigned int state;
  unsigned int prev_state;
  unsigned int is_read;
  unsigned int is_attach;
  unsigned int mail_size;
  unsigned timestamp;
  char *header;
  char *subject;
  char *from;
  char *to;
  char *date;
  char *content_type;
  char *content_encoding;
}ML_VIEW;

typedef struct
{
  int connect_state;
  int pop_state;
  int in_pop3;
  int pop3_recv;
  int pop3_del;
  int total_recv;
  int total_send;
  char log[256];
}POP_STAT;
#endif
