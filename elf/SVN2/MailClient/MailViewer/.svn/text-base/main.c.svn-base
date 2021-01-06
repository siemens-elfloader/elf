#include "..\..\inc\swilib.h"
#include "..\conf_loader.h"
#include "..\mailclient.h"
#include "..\rect_patcher.h"
#include "decode.h"
#include "strings.h"
#include "leak_debug.h"

const char ipc_daemon_name[]=IPC_DAEMON_NAME;
const char ipc_my_name[]=IPC_VIEWER_NAME;

extern int create_gui();
//===============================================================================================
int S_ICONS[8];
const char empty_str[]="";
const char eol[]="\r\n";
const char d_eol[]="\r\n\r\n";
// ------------------------------- Defines ----------------------------------------

const char wintranslation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0x5F,0xFD,0x83,0xB3,0x15,0xF0,0x63,0xF2,0x3C,0xBF,0x2D,0x52,0xF4,
  0xF8,0x2B,'I' ,'i' ,0xA3,0xE7,0x14,0xFA,0xF1,0xFC,0xF3,0x3E,0x5F,0x5F,0x5F,0xF5,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
  0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
};

const char koi8translation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0xF1,0xF3,0x5F,'i' ,0xF5,0xF0,0x63,0xF2,0x3C,0xBF,0xA3,0x52,0xF4,
  0xF8,0x2B,0x5F,0xF0,0xF2,0xE7,'I' ,0xF4,0xF1,0xFC,0xF3,0x3E,0x5F,0x83,0x5F,0xF5,

  0xEE,0xA0,0xA1,0xE6,0xA4,0xA5,0xE4,0xA3,0xE5,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,
  0xAF,0xEF,0xE0,0xE1,0xE2,0xE3,0xA6,0xA2,0xEC,0xEB,0xA7,0xE8,0xED,0xE9,0xE7,0xEA,
  0x9E,0x80,0x81,0x96,0x84,0x85,0x94,0x83,0x95,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,
  0x8F,0x9F,0x90,0x91,0x92,0x93,0x86,0x82,0x9C,0x9B,0x87,0x98,0x9D,0x99,0x97,0x9A
};

const unsigned short dos2unicode[128]=
{
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x002D,0x002D,0x002D,0x00A6,0x002B,0x00A6,0x00A6,0x00AC,
  0x00AC,0x00A6,0x00A6,0x00AC,0x002D,0x002D,0x002D,0x00AC,
  0x004C,0x002B,0x0054,0x002B,0x002D,0x002B,0x00A6,0x00A6,
  0x004C,0x0433,0x00A6,0x0054,0x00A6,0x003D,0x002B,0x00A6,
  0x00A6,0x0054,0x0054,0x004C,0x004C,0x002D,0x0433,0x002B,
  0x002B,0x002D,0x002D,0x002D,0x002D,0x00A6,0x00A6,0x002D,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,
  0x0401,0x0451,0x0404,0x0454,0x0407,0x0457,0x040E,0x045E,
  0x00B0,0x2022,0x00B7,0x0076,0x2116,0x00A4,0x00A6,0x00A0
};


unsigned int char8to16(int c, int type)
{
  if (c>=128)
  {
    switch(type)
    {
    case 1:
      //Win->Dos
      c=wintranslation[c-128];
      break;
    case 2:
      //Koi8->Dos
      c=koi8translation[c-128];
      break;
    case 3:
      break;
      //Dos
    }
    if (c<128) return(c);
    return(dos2unicode[c-128]);
  }
  return(c);
}


void ascii2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c,1));
  }
}

void koi2ws(WSHDR *ws, const char *s)
{
  char c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c,2));
  }
}

void dos2ws(WSHDR *ws, const char *s)
{
  int c;
  CutWSTR(ws,0);
  while((c=*s++))
  {
    wsAppendChar(ws,char8to16(c,3));
  }
}  


void delspaces(char *s)
{
  char *d = s;
  while(*s)
  {
    *d = *s;
    if((*s==0x0D && *(s+1)==0x0A) ||
       (*s==0x0A && *(s+1)==0x0D)) s++;
    s++; d++;
  }
  *d = 0;
}

// --------------------------------------------------------------------------------
extern char *unmime_header(const char *encoded_str, int default_charset);
// --------------------------------------------------------------------------------
const char mailer_db_name[]=MDB_NAME;
const char _percent_t[]="%t";

// --------------------------------------------------------------------------------
volatile int main_menu_id;
volatile int maillist_menu_id;
volatile int options_menu_id;
volatile int view_mail_id;
volatile int request_recount_mailmenu;
volatile int maincsm_id;
// -------------------------- Global Variables -------------------------------------
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

#pragma segment="ELFBEGIN"
void ElfKiller(void)
{
  Clean();
  kill_data(__segment_begin("ELFBEGIN"),(void (*)(void *))mfree_adr());
}
//-----------------------------------------------------------------------------------
volatile int daemon_present=-1; //Активен ли демон
POP_STAT *pop_stat;

int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Options"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};


SOFTKEY_DESC menu_sk2[]=
{
  {0x0000,0x0000,(int)""},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt2=
{
  menu_sk2,0
};
// ----------------------------------------------------------------------------------

volatile ML_VIEW *mails;

void FreeMailDB()
{
  ML_VIEW *ml_cur=(ML_VIEW *)mails;

  LockSched();
  mails=0;
  UnlockSched();
  ML_VIEW *ml_prev;
  while (ml_cur)
  {
    if(ml_cur->uidl)             debug_mfree(ml_cur->uidl, "FreeMailDB (1)");
    if(ml_cur->header)           debug_mfree(ml_cur->header, "FreeMailDB (2)");
    if(ml_cur->subject)          debug_mfree(ml_cur->subject, "FreeMailDB (3)");
    if(ml_cur->from)             debug_mfree(ml_cur->from, "FreeMailDB (4)");
    if(ml_cur->to)               debug_mfree(ml_cur->to, "FreeMailDB (5)");
    if(ml_cur->content_type)     debug_mfree(ml_cur->content_type, "FreeMailDB (6)");
    if(ml_cur->content_encoding) debug_mfree(ml_cur->content_encoding, "FreeMailDB (7)");
    if(ml_cur->date)             debug_mfree(ml_cur->date, "FreeMailDB (8)");
    ml_prev=ml_cur;
    ml_cur=ml_cur->next;
    debug_mfree(ml_prev, "FreeMailDB (8)");
  }
}

void InitHeaders();
int InitMailDB()
{
  char fname[256];
  int f;
  MAIL_DB mail_db;
  char *uidl;
  int n=0;

  ML_VIEW *ml_cur=(ML_VIEW *)&mails;
  unsigned int err;
  strcpy(fname,EML_PATH);
  {
    int len=strlen(fname);
    if (fname[len-1]!='\\')
    {
      fname[len-1]='\\';
      fname[len]=0;
    }
  }
  strcat(fname,mailer_db_name);
  FreeMailDB();
  if ((f=fopen(fname,A_BIN+A_ReadOnly,P_READ,&err))!=-1)
  {
    while (fread(f,&mail_db,sizeof(MAIL_DB),&err)==sizeof(MAIL_DB))
    {

      if(mail_db.magic!=MDB_MAGIC) break;
      ml_cur=ml_cur->next=debug_malloc(sizeof(ML_VIEW), "InitMailDB (1)");
      zeromem(ml_cur,sizeof(ML_VIEW));
      ml_cur->prev_state = ml_cur->state=mail_db.state;
      ml_cur->is_read=mail_db.is_read;
      ml_cur->mail_size=mail_db.mail_size;
      ml_cur->subject=debug_malloc(129, "InitMailDB (2)");
      memcpy(ml_cur->subject, mail_db.hdr, 128);
      if (mail_db.uidl_len)
      {
        uidl=debug_malloc(mail_db.uidl_len+1, "InitMailDB (3)");
        uidl[mail_db.uidl_len]=0;
        fread(f,uidl,mail_db.uidl_len,&err); 
        ml_cur->uidl=uidl;
      }
      else ml_cur->uidl=0;
      n++;
    }
    fclose(f,&err);
    InitHeaders(); 
  }
  return (n);
}

void write_mail_DB()
{
  int f;
  unsigned int err;
  char fname[128];

  ML_VIEW *ml_list=(ML_VIEW *)&mails;
  MAIL_DB mail_db;
  strcpy(fname,EML_PATH);
  strcat(fname,mailer_db_name);
  if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1)
  {
    while((ml_list=ml_list->next))
    {
      mail_db.magic=MDB_MAGIC;
      mail_db.uidl_len=(ml_list->uidl)?strlen(ml_list->uidl):NULL;
      mail_db.state=ml_list->state;
      mail_db.is_read=ml_list->is_read;
      mail_db.mail_size=ml_list->mail_size;
      strcpy(mail_db.hdr,ml_list->subject);      
      fwrite(f,&mail_db,sizeof(MAIL_DB),&err);
      if (mail_db.uidl_len) fwrite(f,ml_list->uidl,mail_db.uidl_len,&err);
    }
    fclose(f,&err);
  }
}

ML_VIEW *find_mlist_ByID(int id)
{
  ML_VIEW *ml_cur=(ML_VIEW *)(&mails);
  int i=0;
  while ((ml_cur=ml_cur->next))
  {
    if (i++==id) return (ml_cur);
  }
  return (0);
}

#pragma inline
int get_mlist_N()
{
  ML_VIEW *ml_cur=(ML_VIEW *)(&mails);
  int i=0;
  while ((ml_cur=ml_cur->next)) i++;
  return i;
}

int get_fsize(int f)
{
  int cur_pos;
  int fsize;
  unsigned int err;
  cur_pos=lseek(f,0,S_CUR,&err,&err);
  fsize=lseek(f,0,S_END,&err,&err);
  lseek(f,cur_pos,S_SET,&err,&err);
  return (fsize);
}

const char eml_not_found[]="Error! File not found!";

char *get_content_type(ML_VIEW *ml_list);
int get_ctype_index(char *str);
int get_param_from_string(char *str, char *param, char *to, int maxlen);
enum {MULTIPART, APPLICATION, TEXT, HTML};
char *strstr_nocase(const char *s1, const char *s2);
char *get_date(ML_VIEW *ml_list);

#define TM_YEAR_BASE 1900

int tdiff (int year, int month, int day, int hour, int min, int sec)
{
  static int day_tab[2][12] =
  {
	{0,  31, 28+31, 31+28+31, 30+31+28+31, 31+30+31+28+31, 30+31+30+31+28+31, 31+30+31+30+31+28+31, 31+31+30+31+30+31+28+31, 30+31+31+30+31+30+31+28+31, 31+30+31+31+30+31+30+31+28+31, 30+31+30+31+31+30+31+30+31+28+31},
	{0,  31, 29+31, 31+29+31, 30+31+29+31, 31+30+31+29+31, 30+31+30+31+29+31, 31+30+31+30+31+29+31, 31+31+30+31+30+31+29+31, 30+31+31+30+31+30+31+29+31, 31+30+31+31+30+31+30+31+29+31, 30+31+30+31+31+30+31+30+31+29+31},
  };
  int yday = day_tab[(year&3)?0:1][month-1] + day;

  int a4 = (year >> 2) + (TM_YEAR_BASE >> 2) - ! (year & 3);
  int b4 = (1970 >> 2) + (TM_YEAR_BASE >> 2) - ! (1970 & 3);

  int intervening_leap_days = (a4 - b4);
  int years = year - 1970;

  int days = (365 * years + intervening_leap_days
	      + (yday - 1));
  return (60 * (60 * (24 * days + (hour - 0))
		+ (min - 0))
	  + (sec - 0));
}

//------------------------------------------------------------------------------

int atoi (const char *str)
{
  int r = 0, n = 0;
  while(*str == ' ') str++;
  if(*str == '-') {n = 1; *str++;}
  while(*str >= '0' && *str <= '9')
  {
    r *= 10;
    r += *str - '0';
    str++;
  }
  return n?-r:r;
} 

//------------------------------------------------------------------------------

unsigned get_date_from_str(const char *str)
{
  static char *months[] =
  {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  static int day_tab[2][12] =
  {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
  };
  int year, month, day, hour, min, sec, cor;
  char *buf, b[128];
  const char *ptr;

  buf = strstr_nocase(str, ", ");

  if(buf) 
    str = buf + 2;
  
  for(ptr = str; *ptr && !((*ptr > 'A' && *ptr < 'Z') || 
                           (*ptr > 'a' && *ptr < 'z')); ptr++);

  if(!*ptr) 
  {
    buf = strstr_nocase(str, ".");
    if(!buf) return 0;
    
    buf = b;
    while(!(*str >= '0' && *str <= '9')) str++;
    while(*str >= '0' && *str <= '9')
    {
     *buf = *str;
     str++;
     buf++;
    }
    *buf = 0;
    buf = b;
    month = atoi(buf);
    
    while(!(*str >= '0' && *str <= '9')) str++;
    while(*str >= '0' && *str <= '9')
    {
     *buf = *str;
     str++;
     buf++;
    }
    *buf = 0;
    buf = b;
    day = atoi(buf);
    
    while(!(*str >= '0' && *str <= '9')) str++;
    while(*str >= '0' && *str <= '9')
    {
     *buf = *str;
     str++;
     buf++;
    }
    *buf = 0;
    buf = b;
    year = atoi(buf);
    
    while(!(*str >= '0' && *str <= '9')) str++;
    while(*str >= '0' && *str <= '9')
    {
     *buf = *str;
     str++;
     buf++;
    }
    *buf = 0;
    buf = b;
    hour = atoi(buf);

    while(!(*str >= '0' && *str <= '9')) str++;
    while(*str >= '0' && *str <= '9')
    {
     *buf = *str;
     str++;
     buf++;
    }
    *buf = 0;
    buf = b;
    min = atoi(buf);

    while(!(*str >= '0' && *str <= '9')) str++;
    while(*str >= '0' && *str <= '9')
    {
     *buf = *str;
     str++;
     buf++;
    }
    *buf = 0;
    buf = b;
    sec = atoi(buf);

    return (tdiff(year, month, day, hour, min, sec));    
  }
  buf = b;
  while(*str == ' ') str++;
  while(*str != ' ')
  {
   *buf = *str;
   str++;
   buf++;
  }
  *buf = 0;
  buf = b;
  day = atoi(buf);

  while(*str == ' ') str++;
  while(*str != ' ')
  {
   *buf = *str;
   str++;
   buf++;
  }
  *buf = 0;
  buf = b;

  for(int i = 0; i < 12; i++)
    if(strcmp_nocase(buf, months[i])==0) month=i+1;
  
  while(*str == ' ') str++;
  while(*str != ' ')
  {
   *buf = *str;
   str++;
   buf++;
  }
  *buf = 0;
  buf = b;

  year = atoi(buf);

  while(*str == ' ') str++;
  while(*str != ':')
  {
   *buf = *str;
   str++;
   buf++;
  }
  *buf = 0;
  buf = b;
  str++;

  hour = atoi(buf);

  while(*str != ':')
  {
   *buf = *str;
   str++;
   buf++;
  }
  *buf = 0;
  buf = b;
  str++;

  min = atoi(buf);

  while(*str != ' ')
  {
   *buf = *str;
   str++;
   buf++;
  }
  *buf = 0;
  buf = b;
  str++;

  sec = atoi(buf);
  cor = 0;
  while(*str == ' ') str++;
  if(*str == '+')
  {
    buf[0] = str[1];
    buf[1] = str[2];
    buf[2] = 0;
    cor = atoi(buf);
    hour -= cor;
    if(hour < 0)
    {
      hour += 24;
      day--;
    }
    if(!day)
    {
      month -=1;
      if(!month)
      {
        month = 12;
        day = 31;
        year--;
      }
      else
        if(year&3)
          day = day_tab[0][month-1];
        else
          day = day_tab[1][month-1];
    }
    cor = -cor;
  }
  if(*str == '-')
  {
    buf[0] = str[1];
    buf[1] = str[2];
    buf[2] = 0;
    cor = atoi(buf);
    hour += cor;
    if(hour > 24)
    {
      hour -= 24;
      day++;
    }
    if(day > day_tab[(year&3)?0:1][month-1])
    {
      day = 1;
      month++;
      if(month>12)
      {
        month = 1;
        year++;
      }
    }
  }
  return (tdiff(year, month, day, hour, min, sec));
}

//------------------------------------------------------------------------------

int get_received_date(char * str)
{
  char * r = strstr_nocase(str, "Received:"), *s, *line;
  if(!r) return 0;
  
  line = s = r;
  while(*s)
  {
    if((*s == '\r' || *s == '\n') && (s[1] == '\t' || s[1] == ' '))
      line = s+1;  //Ищем строку, начинающуюся с пробелов или табуляции
    if((*s == '\r' || *s == '\n') && ((s[1] >= 'a' && s[1] <= 'z') || 
                                      (s[1] >= 'A' && s[1] <= 'Z')))
      break;  //Последняя ли строка блока?
    s++;
  }
  while(*line && (*line == ' ' || *line == '\t')) line++;
  return get_date_from_str(line);
}

//------------------------------------------------------------------------------

void InitHeaders()
{
  int f, cd;
  unsigned int err;
  char fname[128]/*, d[128]*/;
  char *buf, *dec_str, *date;
  int fsize, flag=1;
  char *_eol;
  char *content_type;
  
  ML_VIEW *ml_cur=(ML_VIEW *)&mails, *prev, *next;
  while((ml_cur=ml_cur->next))
  {
    //if(!ml_cur->subject[0]) continue;
    cd = TEXT;
    if (ml_cur->header)
    {
      debug_mfree(ml_cur->header, "InitHeaders (1)");
      ml_cur->header=0;
    }
    
    ml_cur->timestamp = 0;
    snprintf(fname,127,"%s%s.eml",EML_PATH,ml_cur->uidl);
    if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1)
    {
      ml_cur->header=0;
      continue;
    }
    fsize=get_fsize(f);
    buf=debug_malloc(fsize+1, "InitHeaders (1)");
    fread(f,buf,fsize,&err);
    fclose(f,&err);
    buf[fsize]=0;

    if(strstr_nocase(buf, "Content-Disposition: attachment"))
      cd=APPLICATION;

    if(strstr_nocase(buf, "Content-Type: application"))
      cd=APPLICATION;

    _eol=strstr(buf,d_eol);
    if (_eol)
    {
      *_eol=0;
      buf=debug_realloc(buf,strlen(buf)+1, "InitHeaders (1)");
    }

    ml_cur->header=buf;
    content_type=get_content_type(ml_cur);  // Проверим кодировку
    
    if (get_param_from_string(content_type, "charset=", fname, 127))
      dec_str=unmime_header(buf, get_charset(fname));
    else
      dec_str=unmime_header(buf, UTF_8);
       
    if(!(ml_cur->timestamp = get_received_date(dec_str)))
    {    
      date=get_date(ml_cur);
      if (date)
      {
        date=strchr(date, ':')+1;
        while (*date==' ' || *date==0x09) date++;
        ml_cur->timestamp=get_date_from_str(date);
      }
    }
        
    debug_mfree(buf, "InitHeaders (2)");
    ml_cur->header=dec_str; 

    
    content_type=get_content_type(ml_cur);  // Проверим наличие аттачей
    if (content_type)
    {
      int l;
      l=get_ctype_index(content_type);
      if (l==APPLICATION || cd==APPLICATION)
      {
        ml_cur->is_attach=1;
      }
    } 
  }
  
/*  ml_cur = (ML_VIEW *)&mails;
  ml_cur = ml_cur->next;
  while(ml_cur)
  {
    strcpy(fname,EML_PATH);
    strcat(fname,"log.txt");
    if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Append,P_WRITE,&err))!=-1)
    {
      snprintf(d,127,"%d %s\n",ml_cur->timestamp, ml_cur->uidl);
  
      fwrite(f,d,strlen(d),&err);
      fclose(f,&err);
    }
    ml_cur = ml_cur->next;
    
  }*/
  while(flag)
  {
    flag = 0;
    ml_cur = (ML_VIEW *)&mails;
    prev = ml_cur;
    ml_cur = ml_cur->next;
    next = ml_cur->next;
    
    while(ml_cur && next)
    {
      if(ml_cur->timestamp < next->timestamp)
      {
        prev->next = ml_cur->next;
        ml_cur->next = next->next;
        next->next = ml_cur;
        flag = 1;
      }
      prev = ml_cur;
      ml_cur = ml_cur->next;
      next = ml_cur->next;      
    }
  }
  ml_cur = (ML_VIEW *)&mails;
  ml_cur = ml_cur->next;
}



#pragma inline 
size_t cstrlen(const char *s)
{
  const char *sc;
  for (sc = s; *sc != '\0' &&  *sc != '\r' &&  *sc != '\n' ; ++sc);
  return (sc - s);
}

#pragma inline 
char *strchr_nocase(const char *s, int c)
{ 
  int ch = toupper(c);
  
  for (; toupper(*s) != ch; ++s)
  if (*s == '\0')
    return (0);
  return ((char *)s);
}

#pragma inline 
char *strstr_nocase(const char *s1, const char *s2)
{  
  if (*s2 == '\0')
    return ((char *)s1);
  
  for (; (s1 = strchr_nocase(s1, *s2)) != 0; ++s1)
  {    
    const char *sc1, *sc2;
    
    for (sc1 = s1, sc2 = s2; ; )
    if (*++sc2 == '\0')
      return ((char *)s1);
    else if (toupper(*++sc1) != toupper(*sc2))
      break;
  }
  return (0);
}

char *cstrcpy(char *s1, const char *s2)
{
  char *s = s1;
  int c=*s2++;
  while(c!=0 && c!='\r' && c!='\n')
  {
    *s++=c;
    c=*s2++;
  }
  *s=0;
  return (s1);
}

char *get_string_from_header(ML_VIEW *ml_list, char *str)
{
  char *p;
  char *end;
  char *subject;
  int len, prev_len, c_len;

  if (!ml_list) return (0);
  if (ml_list->header)
  {
    len=strlen(str);
    p=ml_list->header;
    p-=2;
    do
    {
      p+=2;
      end=strstr(p,eol);
      if (!strncmp_nocase(p, str,len))
      {
        len=cstrlen(p);
        subject=debug_malloc(len+1, str);
        cstrcpy(subject,p);
        p+=len;
        while(*p!=0 && (*(p+2)=='\t' || *(p+2)==' '))
        {
          p+=2;
          prev_len=len;
          c_len=cstrlen(p);
          len+=c_len;
          subject=debug_realloc(subject,len+1, "get_string_from_header (realloc)");
          cstrcpy(subject+prev_len,p);
          p+=c_len;
        }
        return (subject);
      }
      if (!end) return (0);
      p=end;
    }
    while(*p!=0);
  }
  return 0;
}

char *get_subject(ML_VIEW *ml_list)
{
  char no_subject[]="Subject: <без темы>";
  char *subject;
  if (ml_list->subject[0]) return ml_list->subject;
  subject=get_string_from_header(ml_list, "subject:");
  if(!subject)
  {
    subject=(char *)debug_malloc(strlen(no_subject)+1, "get_subject (1)");
    strcpy(subject,no_subject);
  }

  strcpy(ml_list->subject, subject);
  debug_mfree(subject, "get_subject (1)");
  return (ml_list->subject);
}

char *get_date(ML_VIEW *ml_list)
{
  char *date;
  if (ml_list->date) return ml_list->date;
  date=get_string_from_header(ml_list, "date:");
  return (ml_list->date=date);
}

char *get_from(ML_VIEW *ml_list)
{
  char *from;
  if (ml_list->from) return ml_list->from;
  from=get_string_from_header(ml_list, "from:");
  return (ml_list->from=from);
}

char *get_to(ML_VIEW *ml_list)
{
  char *to;
  if (ml_list->to) return ml_list->to;
  to=get_string_from_header(ml_list, "to:");
  return (ml_list->to=to);
}

char *get_content_type(ML_VIEW *ml_list)
{
  char *content_type;
  if (ml_list->content_type) return ml_list->content_type;
  content_type=get_string_from_header(ml_list, "content-type:");
  return (ml_list->content_type=content_type);
}

char *get_content_encoding(ML_VIEW *ml_list)
{
  char *content_encoding;
  if (ml_list->content_encoding) return ml_list->content_encoding;
  content_encoding=get_string_from_header(ml_list, "content-transfer-encoding:");
  return (ml_list->content_encoding=content_encoding);
}

char *get_from_multipartheader(char *begin_h, char *end_h, char *str)
{
  char *p, *s;
  char *end;
  int len, prev_len, c_len;
  if (!end_h) return (0);
  if (begin_h)
  {
    len=strlen(str);
    p=begin_h;
    p-=2;
    do
    {
      p+=2;
      end=strstr(p,eol);
      if (!strncmp_nocase(p, str,len))
      {
        len=cstrlen(p);
        s=debug_malloc(len+1, "get_from_multipartheader (1)");
        cstrcpy(s,p);
        p+=len;
        while(*p!=0 && (*(p+2)=='\t' || *(p+2)==' '))
        {
          p+=2;
          prev_len=len;
          c_len=cstrlen(p);
          len+=c_len;
          s=debug_realloc(s,len+1, "get_from_multipartheader (1)");
          cstrcpy(s+prev_len,p);
          p+=c_len;
        }
        return (s);
      }
      if (!end) return (0);
      p=end;
    }
    while(*p && p<end_h );
  }
  return 0;
}

// Требуется для boundary= , name= , charset= 
int get_param_from_string(char *str, char *param, char *to, int maxlen)  // Выдеяет из строки вида charset="koi8-r" или charset=koi8-r подстроку и копирует ее в строку назначения
{
  int c, d;
  char *p, *s;
  p=strstr_nocase(str, param);
  if (!p) return (0);
  p+=strlen(param);
  if ((d=*p)=='\"')
  {
    c=d;
    p++;
  }
  else c=' ';  
  s=to;
  while((d=*p++) && maxlen-- && d!=c)
  {
    *to++=d;
  }
  *to=0;
  return (to-s);
}
//----------------------------------------------------------------------------------------------
typedef struct{
  void *next;
  int content_type;
  int transfer_encoding;
  int charset;
  int offset;
  int size;
  int textlen;
  char ct[256];
  char te[256];
  int scroll[512];
  int ec_n;
}MAIL_PART;

typedef struct{
  MAIL_PART *top;
  char *eml;
}MAIL_VIEW;

char *strstr_nocase(const char *s1, const char *s2);
enum {BIT8, BASE64, QPRINTABLE, BIT7};

void saveas_locret(void){}


int saveas_onkey(GUI *data, GUI_MSG *msg)
{
  MAIL_VIEW *mail_view;
  MAIL_PART *mail;
  int f, len;
  unsigned int err;
  EDITCONTROL ec;
  char *p, *decoded;
  size_t size = 0;
  char fname[128];
  mail_view=EDIT_GetUserPointer(data);
  if (msg->keys==0xFFF)
  {
    if (!mail_view)
    {
      ShowMSG(1,(int)"Can't save attach!");
      return (1);
    }
    mail=mail_view->top;
    p=mail_view->eml+mail->offset;
    size=mail->size;
    switch(mail->transfer_encoding)
    {
    case BASE64:
      decoded=base64_decode(p, &size);
      break;
      
    case QPRINTABLE:
      decoded=quoted_printable_decode(p, &size);
      break;
    case BIT8: case BIT7:
      len=size?size:strlen(p);
      decoded = debug_malloc(len+1, "saveas_onkey (1)");
      decoded[len] = 0;
      memcpy(decoded, p, len);
      break;
      
    default:
      ShowMSG(1,(int)"Unknown encoding!");
      return (1);
    } 
    if (!decoded) 
    {
      ShowMSG(1,(int)"Can't decode attach!");
      return (1);
    } 
    ExtractEditControl(data,2,&ec);
    ws_2str(ec.pWS,fname,128);
    if ((f=fopen(fname,A_WriteOnly+A_BIN+A_Truncate+A_Create, P_WRITE, &err))==-1)
    {
      debug_mfree(decoded, "saveas_onkey (1)");
      ShowMSG(1,(int)"Can't create file!");
      return (1);
    }
    fwrite(f, decoded, size, &err);
    debug_mfree(decoded, "saveas_onkey (2)");
    fclose(f, &err);
    ShowMSG(1,(int)"Succesfully saved!");
    return(1);
  }
  return(0); //Do standart keys
  //1: close
}

void saveas_ghook(GUI *data, int cmd)
{
  MAIL_VIEW *mail_view;
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Save!"};
  mail_view=EDIT_GetUserPointer(data);
  if (cmd==3)
  {
    debug_mfree(mail_view, "saveas_ghook (1)");
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}


HEADER_DESC saveas_hdr={0,0,0,0,NULL,(int)"Сохранение",LGP_NULL};

INPUTDIA_DESC saveas_desc =
{
  1,
  saveas_onkey,
  saveas_ghook,
  (void *)saveas_locret,
  0,
  &menu_skt,
  {0,NULL,NULL,NULL},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - Выровнять по правому краю
  //  0x00000002 - Выровнять по центру
  //  0x00000004 - Инверсия знакомест
  //  0x00000008 - UnderLine
  //  0x00000020 - Не переносить слова
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - Не двигается курсор
  //  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};

void create_save_as_dialog(MAIL_PART *top, char *eml)
{
  void *ma=malloc_adr();
  void *eq;  
  char *p;
  char fname[256];
  EDITCONTROL ec;
  MAIL_VIEW *mail_view;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  WSHDR *ews=AllocWS(128);
  WSHDR *filename;
  wsprintf(ews,"%t","Path Save File:");  
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,wslen(ews));
  AddEditControlToEditQend(eq,&ec,ma);
  
  p=top->ct;
  get_param_from_string(p, "name=", fname, 255);
    
  p=unmime_header(fname, top->charset);
  filename=AllocWS(strlen(p));
  ascii2ws(filename, p);
  str_2ws(ews, SAVE_AS_FOLDER, 127);
  wstrcat(ews, filename);
  FreeWS(filename);
  debug_mfree(p, "create_save_as_dialog (1)");
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);  
    
  
  mail_view=debug_malloc(sizeof(MAIL_VIEW), "create_save_as_dialog (1)");
  mail_view->top=top;
  mail_view->eml=eml;
  patch_header(&saveas_hdr);
  patch_input(&saveas_desc);
  FreeWS(ews);
  CreateInputTextDialog(&saveas_desc,&saveas_hdr,eq,1,mail_view);  
}



int IsUrl(WSHDR *ws, int pos, char *link)
{
  const char *valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$-_.+!*'(),%;:@&=/?#абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ~#";

  int len = wstrlen(ws);
  unsigned short *str = ws->wsbody+1, *tmp, *begin;
  tmp = str;
  
  begin = str = wstrstr(str, "http://", &len, 7);

  while(str && (begin-tmp <= pos))
  {
    while(len && strchr(valid, char16to8(*str))) {str++; len--;}
    if(str-tmp >= pos-2)
    {
      for(;begin < str; begin++, link++)
        *link = char16to8(*begin);
      link[str-begin] = 0;
      return 1;
    }
    begin = str = wstrstr(str, "http://", &len, 7);
  }

  len = wstrlen(ws);
  begin = str = wstrstr(tmp, "www.", &len, 4);
  while(str && (begin-tmp <= pos))
  {
    while(len && strchr(valid, char16to8(*str))) {str++; len--;}
    if(str-tmp >= pos-2)
    {
      for(;begin < str; begin++, link++)
        *link = char16to8(*begin);
      link[str-begin] = 0;
      return 1;
    }
    begin = str = wstrstr(str, "www.", &len, 4);
  }
  return 0;
}
  
HEADER_DESC ed1_hdr={0,0,0,0,NULL,(int)"Просмотр",LGP_NULL};

HEADER_DESC ed2_hdr={0,0,0,0,NULL,(int)"Информация",LGP_NULL};

void ed1_locret(void){}
void ed2_locret(void){}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  int l;
  int i,j;
  MAIL_VIEW *view_list;
  MAIL_PART *top, *prev;
  view_list=EDIT_GetUserPointer(data);
  if (!view_list) return (0);
  if (!view_list->eml) return (0);
  
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    l=msg->gbsmsg->submess;
    if (!EDIT_IsMarkModeActive(data))  // Только если не выделение
    {
      if (l==UP_BUTTON)
      {
        int pos;
        top=view_list->top;
        i=EDIT_GetFocus(data);
        
        prev = top;
        while(top)
        {
          if (top->ec_n==i)
          {
            pos = EDIT_GetCursorPos(data);
            if(pos == 1)
            {
              if(top == ((MAIL_PART *)view_list->top)->next)
              {
                EDIT_SetFocus(data,i-2);
                EDIT_SetCursorPos(data, 1);
              }
              else
              {
                EDIT_SetFocus(data,prev->ec_n);
                EDIT_SetCursorPos(data, prev->textlen+1);
              }
              return (-1);
            }
            
            for(j = 1; j < 512; j++)
              if(top->scroll[j]+1 >= pos)
              {
                EDIT_SetCursorPos(data, top->scroll[j-1]+1);
                return (-1);
              }
            return (-1);
          }
          prev = top;
          top=top->next;
        }
        EDIT_SetFocus(data,i-2);
        EDIT_SetCursorPos(data, 1);
        return (-1);
      }
      if (l==DOWN_BUTTON)
      {
        int pos;
        top=view_list->top;
        i=EDIT_GetFocus(data);
        
        while(top)
        {
          if (top->ec_n==i)
          {
            pos = EDIT_GetCursorPos(data);
            for(j = 1; j < 512; j++)
            {
              if(top->scroll[j]+1 > pos)
              {
                EDIT_SetCursorPos(data, top->scroll[j]+1);
                return (-1);
              }
              if(top->scroll[j] == top->textlen)
              {
                if(top->next)
                {
                  EDIT_SetFocus(data,((MAIL_PART *)top->next)->ec_n);
                  EDIT_SetCursorPos(data, 1);
                }
                return (-1);
              }
            }
            return (-1);
          }
          top=top->next;
        }
        EDIT_SetFocus(data,i+2);
        EDIT_SetCursorPos(data, 1);
        return (-1);
      }
 

    }
  }

  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    l=msg->gbsmsg->submess;
    if (l==LEFT_SOFT||l==ENTER_BUTTON)
    {
      i=EDIT_GetFocus(data);
      top=view_list->top;
      while(top)
      {
        if (top->ec_n==i)
          if (top->content_type==APPLICATION)
            break;
          else
          {
            if (l==ENTER_BUTTON)
            {
        
              int pos, len, f;
              char *link, fn[256];
              unsigned err;
              WSHDR *ews;
              EDITCONTROL ec;
              
              ExtractEditControl(data,i,&ec);
              ews = AllocWS(wstrlen(ec.pWS)+1);
              wstrcpy(ews,ec.pWS);
              pos = EDIT_GetCursorPos(data);
              len = wstrlen(ews);
          
              link = debug_malloc(len+1, "ed1_onkey (1)");
                      
              if(IsUrl(ews, pos, link))
              {
                snprintf(fn, 255, "%stmp%u.url", EML_PATH, GetTempName);                
                if ((f=fopen(fn,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1)
                {
                  fwrite(f,link,strlen(link),&err);
                  fclose(f,&err);
                  str_2ws(ews,fn,256);
                  ExecuteFile(ews,0,0);            
                  unlink(fn, &err);
                }                        
                debug_mfree(link, "ed1_onkey (1)");
                return (-1);
              }
              debug_mfree(link, "ed1_onkey (1)");
            }        
        }

        top=top->next;
      }
      if (!top) return (0);
      create_save_as_dialog(top, view_list->eml);
      return (-1);
    }
    if (l==VOL_UP_BUTTON)
    {
      i=EDIT_GetFocus(data);
      top=view_list->top;
      prev = top;
      while(top)
      {
        if (top->ec_n==i)
        {
          EDIT_SetFocus(data,prev->ec_n);
          EDIT_SetCursorPos(data, 1);
          break;
        }
        prev = top;
        top=top->next;
      }
      EDIT_SetFocus(data,i-2);
      EDIT_SetCursorPos(data, 1);
      return (-1);
    }
    if (l==VOL_DOWN_BUTTON)
    {
      i=EDIT_GetFocus(data);
      top=view_list->top;
      while(top)
      {
        if (top->ec_n==i)
        {
          if(top->next)
          {
            EDIT_SetFocus(data,((MAIL_PART *)top->next)->ec_n);
            EDIT_SetCursorPos(data, 1);
          }
          break;
        }
        top=top->next;
      }
      EDIT_SetFocus(data,i+2);
      EDIT_SetCursorPos(data, 1);
      return (-1);
    }
  }
  return(0); 
}

int ed2_onkey(GUI *data, GUI_MSG *msg)
{
  return(0); 
}

void ed1_ghook(GUI *data, int cmd)
{
  int j;
  MAIL_VIEW *view_list=EDIT_GetUserPointer(data);
  MAIL_PART *m, *prev;
  if (cmd==3)
  {
    if (view_list)
    {
      m=view_list->top;
      while(m)
      {
        prev=m;
        m=m->next;
        debug_mfree(prev, "ed1_ghook (1)");
      }
      debug_mfree(view_list->eml, "ed1_ghook (2)");
      debug_mfree(view_list, "ed1_ghook (3)");
    }
  }
  if (cmd==0x0C)
  {
    j=EDIT_GetFocus(data);
    if (EDIT_GetUnFocus(data)<j) EDIT_SetCursorPos(data,1);
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

void ed2_ghook(GUI *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0
};

INPUTDIA_DESC ed2_desc=
{
  1,
  ed2_onkey,
  ed2_ghook,
  (void *)ed2_locret,
  0,
  &menu_skt2,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0
};

int get_ctype_index(char *str)
{
  char *p;
  p=strstr_nocase(str, "Content-Type:");
  if (p)
  {
    p+=strlen("Content-Type:");
    while(*p==' ') p++;
    if (!strncmp_nocase(p,"multipart",9))
      return MULTIPART;
    
    if (!strncmp_nocase(p,"application",11))
      return APPLICATION; 
    
    if (!strncmp_nocase(p,"text/plain",10))
      return TEXT;
    
    if (!strncmp_nocase(p,"text/html",9))
      return HTML;
    
    if (!strncmp_nocase(p,"image",5))
      return APPLICATION; 

    if (!strncmp_nocase(p,"message",5))
      return APPLICATION; 
  }
  return TEXT;
}

int get_cdisp_index(char *str)
{
  char *p;
  p=strstr_nocase(str, "Content-Disposition:");
  if (p)
  {
    p+=strlen("Content-Disposition:");
    while(*p==' ') p++;
    
    if (!strncmp_nocase(p,"attachment",10))
      return APPLICATION; 

    if (!strncmp_nocase(p,"inline",6))
      return TEXT; 
    
  }
  return TEXT;
}

int get_ctencoding_index(char *str)
{
  char *p;
  p=strstr_nocase(str, "Content-Transfer-Encoding:");
  if (p)
  {
    p+=26;
    while(*p==' ') p++;
    if (!strncmp_nocase(p,"8bit",4))
      return BIT8;
    
    if (!strncmp_nocase(p,"base64",6))
      return BASE64; 
    
    if (!strncmp_nocase(p,"quoted-printable",16))
      return QPRINTABLE;
    
    if (!strncmp_nocase(p,"7bit",4))
      return BIT8;
  }
  return BIT8;
}

#define UTF16_DIS_UNDERLINE (0xE002)
#define UTF16_ENA_UNDERLINE (0xE001)

void SearchUrl(WSHDR *ws, const char *s)
{
  const char *valid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789$-_.+!*'(),%;:@&=/?абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ~#";
  unsigned int wchar;
  CutWSTR(ws,0);
  while(wchar=*s)
  {
    if(s==strstr(s, "http://") || s == strstr(s, "www."))
    {
      wsAppendChar(ws,UTF16_ENA_UNDERLINE);
      while(*s && strchr(valid, *s))
      {
        wchar=(*s>=128)?win2unicode[*s-128]:*s;
        wsAppendChar(ws,wchar);
        s++;       
      }
      wsAppendChar(ws,UTF16_DIS_UNDERLINE);
      continue;
    }
    wsAppendChar(ws,(*s>=128)?win2unicode[*s-128]:*s);
    s++;
  }
}


const char default_ctype[]="Content-Type: text/plain; charset=\"windows-1251\"";
const char default_transfere[]="Content-Transfer-Encoding: 8bit";

MAIL_VIEW *ParseMailBody(void *eq,ML_VIEW *ml_list, void *ma)
{
  WSHDR *ws, *headers;
  MAIL_PART *top=0, *bot, *prev;
  MAIL_VIEW *view_list;
  EDITCONTROL ec;
  char *content_type, *content_encoding, *content_disposition;
  int f;
  unsigned int err;
  char fname[128], tmp[128];
  char *eml, *end_header;
  int size;
  int ed_toitem;
  int scrolls;
    
  headers=AllocWS(100);

  top=debug_malloc(sizeof(MAIL_PART), "ParseMailBody (1)");
  bot=top;
  top->next=0;
  top->offset=0;
  top->ec_n=-1;
  
  content_type=get_content_type(ml_list);
  strcpy(top->ct,content_type?content_type:default_ctype);
  top->content_type=get_ctype_index(content_type);
  
  content_encoding=get_content_encoding(ml_list);
  strcpy(top->te,content_encoding?content_encoding:default_transfere);
  top->transfer_encoding=get_ctencoding_index(content_encoding);
  
  snprintf(fname,127,"%s%s.eml",EML_PATH,ml_list->uidl);
  f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err);
  if (f==-1)
  {
    debug_mfree(top, "ParseMailBody (1)");
    return (0);
  }
  
  size=get_fsize(f);
  if (!size)
  {
    fclose(f, &err);
    debug_mfree(top, "ParseMailBody (2)");
    return (0);
  }
  eml=debug_malloc(size+1, "ParseMailBody (2)");
  fread(f, eml, size, &err);
  fclose(f, &err);
  eml[size]=0;
  end_header=strstr(eml, d_eol);
  if (!end_header || (end_header+4)==(eml+size))
  {
    debug_mfree(eml, "ParseMailBody (3)");
    debug_mfree(top, "ParseMailBody (4)");
    return (0);
  }
  strcpy(eml,end_header+4);
  size=strlen(eml);
  top->size=size;
  eml=debug_realloc(eml, size+1, "ParseMailBody (1)");
  top->charset=WIN_1251;
  top->textlen=0;
  while(bot)
  {
    size_t buf_size;
    char *p, *buf, *b_end;
    int i;
      
    switch(bot->content_type)
    {
    case HTML:
      p=bot->ct;
      i=get_param_from_string(p, "charset=", fname, 127);
      if (i)
        bot->charset=get_charset(fname);
      //else bot->charset=WIN_1251;
      switch(bot->transfer_encoding)
      {
      default:
      case BIT8:
        buf=debug_malloc(bot->size+1, "ParseMailBody (3)");
        strncpy(buf,eml+bot->offset,bot->size);
        buf[bot->size]=0;
        break;
         
      case BASE64:
        buf_size=bot->size;
        buf=base64_decode(eml+bot->offset, &buf_size);
        break;
          
      case QPRINTABLE:
        buf_size=bot->size;
        buf=quoted_printable_decode(eml+bot->offset, &buf_size);
        break;  
      }
      switch(bot->charset)
      {
      case WIN_1251:
      default:
        break;
   
      case KOI8_R:
        koi2win(buf, buf);
        break;
   
      case ISO_8859_5:
        iso885952win(buf, buf);
        break;

      case UTF_8:
        utf82win(buf, buf);
        break;
      }
      strip_html(buf);
      delspaces(buf);
      bot->textlen = strlen(buf);
      bot->scroll[0] = 0;
      scrolls = 1;
      for(int scrl = 0, dx_s = 0; buf[scrl]; scrl++, dx_s++)
        if(buf[scrl] == '\n' || (buf[scrl] == ' ' && dx_s > 50)) 
        {
          bot->scroll[scrolls++] = scrl;
          dx_s = 0;
        }
      bot->scroll[scrolls] = bot->textlen;
      ws=AllocWS(strlen(buf)*2+1);
      SearchUrl(ws, buf);
      CutWSTR(ws, wstrlen(ws)+1);
      //ascii2ws(ws, buf);
        
      PrepareEditControl(&ec);
      ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
      SetFontToEditCOptions(&ec.ed_options,1);
      ed_toitem=AddEditControlToEditQend(eq,&ec,ma); 
      bot->ec_n=ed_toitem;
      FreeWS(ws);
      debug_mfree(buf, "ParseMailBody (5)");

      ascii2ws(headers,"------------------");
      ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,headers,wslen(headers));
      SetFontToEditCOptions(&ec.ed_options,4);
      AddEditControlToEditQend(eq,&ec,ma);    

      break;
       
    case TEXT:
      p=bot->ct;
      i=get_param_from_string(p, "charset=", fname, 127);
      if (i)
        bot->charset=get_charset(fname);
      //else bot->charset=WIN_1251;
      switch(bot->transfer_encoding)
      {
      default:
      case BIT8:
        buf=debug_malloc(bot->size+1, "ParseMailBody (4)");
        strncpy(buf,eml+bot->offset,bot->size);
        buf[bot->size]=0;
        break;
         
      case BASE64:
        buf_size=bot->size;
        buf=base64_decode(eml+bot->offset, &buf_size);
        break;
          
      case QPRINTABLE:
        buf_size=bot->size;
        buf=quoted_printable_decode(eml+bot->offset, &buf_size);
        break;  
      }
      switch(bot->charset)
      {
      case WIN_1251:
      default:
        break;
   
      case KOI8_R:
        koi2win(buf, buf);
        break;
   
      case ISO_8859_5:
        iso885952win(buf, buf);
        break;

      case UTF_8:
        utf82win(buf, buf);
        break;
      }
      delspaces(buf);
      bot->textlen = strlen(buf);
      bot->scroll[0] = 0;
      scrolls = 1;
      for(int scrl = 0, dx_s = 0; buf[scrl]; scrl++, dx_s++)
        if(buf[scrl] == '\n' || (buf[scrl] == ' ' && dx_s > 50)) 
        {
          bot->scroll[scrolls++] = scrl;
          dx_s = 0;
        }
      bot->scroll[scrolls] = bot->textlen;
      ws=AllocWS(strlen(buf));
      SearchUrl(ws, buf);
      CutWSTR(ws, wstrlen(ws)+1);
//      ascii2ws(ws, buf);
        
      PrepareEditControl(&ec);
      ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
      SetFontToEditCOptions(&ec.ed_options,1);
      ed_toitem=AddEditControlToEditQend(eq,&ec,ma); 
      bot->ec_n=ed_toitem;
      FreeWS(ws);
      debug_mfree(buf, "ParseMailBody (6)");

      ascii2ws(headers,"------------------");
      ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,headers,wslen(headers));
      SetFontToEditCOptions(&ec.ed_options,4);
      AddEditControlToEditQend(eq,&ec,ma);    

      break;
      
    case MULTIPART:
      p=bot->ct;
      i=get_param_from_string(p, "charset=", fname, 127);
      if (i)
        bot->charset=get_charset(fname);
      i=get_param_from_string(p,"boundary=",fname,127);
      if (!i) break;
      p=strstr_nocase(eml,fname);
      while(p)
      {
        p+=i;
        if (!strncmp(p,"--\r\n",4)) break;
        
        p=strstr(p,eol);
        p+=2;

        buf=strstr(p,d_eol);
        buf+=4;
        
        b_end=strstr_nocase(p,fname);
        if (!b_end)  continue;
        
        prev=bot;
        while(prev->next) prev=prev->next;
        prev=prev->next=debug_malloc(sizeof(MAIL_PART), "ParseMailBody (5)");
        prev->next=0;
        prev->ec_n=-1;
        prev->offset=buf-eml;
        prev->size=b_end-buf;
        
        
        content_type=get_from_multipartheader(p,buf,"content-type:");
                
        if (content_type)
        {
          strcpy(prev->ct,content_type);  
          debug_mfree(content_type, "ParseMailBody (7)");
        }
        else strcpy(prev->ct,default_ctype);
        
        content_encoding=get_from_multipartheader(p,buf,"Content-Transfer-Encoding:");
        if (content_encoding)
        {
          cstrcpy(prev->te,content_encoding);     
          debug_mfree(content_encoding, "ParseMailBody (8)");
        }
        else strcpy(prev->te,default_transfere);

        content_disposition=get_from_multipartheader(p,buf,"Content-Disposition:");
                
        prev->content_type=get_ctype_index(prev->ct);
        
        if (content_disposition)
        {
          if(get_param_from_string(content_disposition,"name=",tmp,127))
          {
            strcat(prev->ct,"; filename=");
            strcat(prev->ct,tmp);
          }
          
          if(get_cdisp_index(content_disposition) != TEXT) 
            prev->content_type=APPLICATION;
          debug_mfree(content_disposition, "ParseMailBody (9)");
        }
        
        if (get_param_from_string(prev->ct, "charset=", tmp, 127))
          prev->charset=get_charset(tmp);
        else
          prev->charset = bot->charset;
        prev->transfer_encoding=get_ctencoding_index(prev->te);
        prev->textlen=0;
        p=b_end;

      } 
      break;
    case APPLICATION:
      p=bot->ct;
      i=get_param_from_string(p,"name=",fname,127);
      if (i<=0) 
        strcpy(fname, "noname");
      
      p=unmime_header(fname, bot->charset);
      
      bot->textlen = strlen(p);
      bot->scroll[0] = 0;
      bot->scroll[1] = bot->textlen;
   
      ws=AllocWS(strlen(p));
      ascii2ws(ws, p);
      debug_mfree(p, "ParseMailBody (10)");
      PrepareEditControl(&ec);   

      ConstructEditControl(&ec,ECT_READ_ONLY_SELECTED,ECF_APPEND_EOL,ws,wslen(ws));
      SetFontToEditCOptions(&ec.ed_options,1);
      ed_toitem=AddEditControlToEditQend(eq,&ec,ma); 
      bot->ec_n=ed_toitem;
      FreeWS(ws);

      ascii2ws(headers,"------------------");
      ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,headers,wslen(headers));
      SetFontToEditCOptions(&ec.ed_options,4);
      AddEditControlToEditQend(eq,&ec,ma);    

      break;
    default:
      bot->scroll[0] = 0;
      bot->scroll[1] = 22;
      bot->textlen = 22;
      ascii2ws(headers,"<unknown message type>");
      ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,headers,wslen(headers));
      SetFontToEditCOptions(&ec.ed_options,2);
      AddEditControlToEditQend(eq,&ec,ma);    


      ascii2ws(headers,"------------------");
      ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,headers,wslen(headers));
      SetFontToEditCOptions(&ec.ed_options,4);
      AddEditControlToEditQend(eq,&ec,ma);    

      break;
    }
    bot=bot->next;
    
  }
  view_list=debug_malloc(sizeof(MAIL_VIEW), "ParseMailBody (6)");
  view_list->top=top;
  view_list->eml=eml;
  FreeWS(headers);
  return (view_list);
}

int create_view(ML_VIEW *ml_list)
{
  MAIL_VIEW *view_list;
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  WSHDR *ws, *headers;
  char *from, *to, *subject;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  headers=AllocWS(100);
  from=get_from(ml_list);
  if (from)
  {
    from=strchr(from, ':')+1;
    while (*from==' ' || *from==0x09) from++;
    ws=AllocWS(strlen(from));
    ascii2ws(ws,from);
    ascii2ws(headers,"From: ");
    
    ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,headers,wslen(headers));
    SetFontToEditCOptions(&ec.ed_options,2);
    AddEditControlToEditQend(eq,&ec,ma);
    
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
    SetFontToEditCOptions(&ec.ed_options,1);
    AddEditControlToEditQend(eq,&ec,ma); 
    FreeWS(ws);
  }
  
  to=get_to(ml_list);
  if (to)
  {
    to=strchr(to, ':')+1;
    while (*to==' ' || *to==0x09) to++;
    ws=AllocWS(strlen(to));
    ascii2ws(ws,to);
    ascii2ws(headers,"To: ");
    
    ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,headers,wslen(headers));
    SetFontToEditCOptions(&ec.ed_options,2);
    AddEditControlToEditQend(eq,&ec,ma);
    
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
    SetFontToEditCOptions(&ec.ed_options,1);
    AddEditControlToEditQend(eq,&ec,ma); 
    FreeWS(ws);
  }
  
  subject=get_subject(ml_list);
  if (subject)
  {
    subject=strchr(subject, ':')+1;
    while (*subject==' ' || *subject==0x09) subject++;
    ws=AllocWS(strlen(subject));
    ascii2ws(ws,subject);
    ascii2ws(headers,"Subject: ");
    
    ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,headers,wslen(headers));
    SetFontToEditCOptions(&ec.ed_options,2);
    AddEditControlToEditQend(eq,&ec,ma);
    
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
    SetFontToEditCOptions(&ec.ed_options,1);
    AddEditControlToEditQend(eq,&ec,ma); 
    FreeWS(ws);
  }
  ascii2ws(headers,"------------------");
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,headers,wslen(headers));
  SetFontToEditCOptions(&ec.ed_options,4);
  AddEditControlToEditQend(eq,&ec,ma);  
  
  view_list=ParseMailBody(eq,ml_list,ma);    
  FreeWS(headers);
  patch_header(&ed1_hdr);
  patch_input(&ed1_desc);  
  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,view_list);
}  

//----------------------------------------------------------------------------------------------
/*void ConvertTime(TDate *d, TTime *t, struct tm *dos )
{
  t->hour=dos->tm_hour;
  t->min=dos->tm_min;
  t->sec=dos->tm_sec;
  t->millisec=0;
  d->day=dos->tm_mday;
  d->year=dos->tm_year+1900;
  d->month=dos->tm_mon+1;
  
}*/
//----------------------------------------------------------------------------------------------

void PrintTimeDate(char *p, unsigned long x)
{
  unsigned int sec,min,hrs,mon,yrs;
  unsigned int day,iday,day4,yrs4;
  const int DMonth[]={0,31,59,90,120,151,181,212,243,273,304,334,365};
  unsigned long tmpx = x;
  
  x-=946684800;
  sec=x%60;
  min=(x/60)%60;
  hrs=(x/3600)%24;
  iday=x/86400;
  yrs4=x/((4*365+1)*86400);
  day4=iday%(4*365+1);
  iday=(day4==(31+28));
  if (day4>=(31+28)) day4--;
  yrs=(yrs4<<2)+day4/365;
  day=day4%365;
  mon=0;
  while (DMonth[++mon]<=day);
  day-=DMonth[mon-1];
  if (iday) day++;
  day++;
  if (yrs>99) yrs=0;
  
  
  TDateTimeSettings *ts=RamDateTimeSettings();
  TDate d;
  TTime t;  
  
  t.hour=hrs;
  t.min=min;
  t.sec=sec;
  t.millisec=0;
  d.day=day;
  d.year=yrs+2000;
  d.month=mon;
 
  x=tmpx+GetTimeZoneShift(&d,&t,ts->timeZone)*60;
 
  x-=946684800;
  sec=x%60;
  min=(x/60)%60;
  hrs=(x/3600)%24;
  iday=x/86400;
  yrs4=x/((4*365+1)*86400);
  day4=iday%(4*365+1);
  iday=(day4==(31+28));
  if (day4>=(31+28)) day4--;
  yrs=(yrs4<<2)+day4/365;
  day=day4%365;
  mon=0;
  while (DMonth[++mon]<=day);
  day-=DMonth[mon-1];
  if (iday) day++;
  day++;
  if (yrs>99) yrs=0;
  
  sprintf(p,"%02d:%02d:%02d %02d.%02d.%04d",hrs,min,sec,day,mon,yrs+2000);
}

//----------------------------------------------------------------------------------------------

int create_info_view(ML_VIEW *ml_list)
{
  void *ma=malloc_adr();
  void *eq;
  int f, fsize;
  unsigned err;
  EDITCONTROL ec;
  WSHDR *ws, *headers;
  char buf[128], *date, dbuf[256];
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  headers=AllocWS(100);

  date=get_date(ml_list);
  if (date)
  {
    date=strchr(date, ':')+1;
    while (*date==' ' || *date==0x09) date++;
    memcpy(dbuf, date, 255);
    dbuf[255] = 0;
    fsize = get_date_from_str(dbuf);
    PrintTimeDate(buf, fsize);

    ws=AllocWS(strlen(buf));
    ascii2ws(ws,buf);
    ascii2ws(headers,"Отправлено: ");
    
    ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,headers,wslen(headers));
    SetFontToEditCOptions(&ec.ed_options,2);
    AddEditControlToEditQend(eq,&ec,ma);
    
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
    SetFontToEditCOptions(&ec.ed_options,1);
    AddEditControlToEditQend(eq,&ec,ma); 
    FreeWS(ws);
  }

    
  if(fsize=get_received_date(ml_list->header))
  {
    buf[0] = 0;
    PrintTimeDate(buf, fsize);
    
    ws=AllocWS(strlen(buf));
    ascii2ws(ws,buf);
    ascii2ws(headers,"Получено: ");
    
    ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,headers,wslen(headers));
    SetFontToEditCOptions(&ec.ed_options,2);
    AddEditControlToEditQend(eq,&ec,ma);
    
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
    SetFontToEditCOptions(&ec.ed_options,1);
    AddEditControlToEditQend(eq,&ec,ma); 
    FreeWS(ws);
  }

  snprintf(buf,127,"%d",ml_list->mail_size);
  strcat(buf, " байт");
  
  ws=AllocWS(strlen(buf));
  ascii2ws(ws,buf);
  ascii2ws(headers,"Размер: ");
  
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,headers,wslen(headers));
  SetFontToEditCOptions(&ec.ed_options,2);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
  SetFontToEditCOptions(&ec.ed_options,1);
  AddEditControlToEditQend(eq,&ec,ma); 
  FreeWS(ws);
    
  snprintf(buf,127,"%s%s.eml",EML_PATH,ml_list->uidl);
  if ((f=fopen(buf,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
  {
    fsize=get_fsize(f);
    fclose(f,&err);
  }
  
  snprintf(buf,127,"%d",fsize);
  strcat(buf, " байт");
  
  ws=AllocWS(strlen(buf));
  ascii2ws(ws,buf);
  ascii2ws(headers,"Скачано: ");
  
  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,headers,wslen(headers));
  SetFontToEditCOptions(&ec.ed_options,2);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL | ECF_DISABLE_T9,ws,wslen(ws));
  SetFontToEditCOptions(&ec.ed_options,1);
  AddEditControlToEditQend(eq,&ec,ma); 
  FreeWS(ws);
  
  ascii2ws(headers,"------------------");
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,headers,wslen(headers));
  SetFontToEditCOptions(&ec.ed_options,4);
  AddEditControlToEditQend(eq,&ec,ma);  
  
  FreeWS(headers);
  patch_header(&ed2_hdr);
  patch_input(&ed2_desc);  
  return CreateInputTextDialog(&ed2_desc,&ed2_hdr,eq,1,0);
}  

//----------------------------------------------------------------------------------------------


int GetIconIndex(ML_VIEW *m_list)
{
  if (!m_list) return (7);
  int l=m_list->state;
  switch (l)
  {
  case M_FULL_LOADED:
    if (m_list->is_read)
      return (m_list->is_attach?5:1);
    else
      return (m_list->is_attach?4:0);
    
  case M_HEADERS_LOADED:
    return (m_list->is_attach?3:2);
  case M_LOAD_FULL:
    return 6;
  case M_DELETE:
    return 7;
  }
  return 0;
}

// ---------------------------------------------------------------------------------

void send_req_checkmailbox(void)
{
  if (daemon_present!=-1)
  {
    IPC_REQ *ipc=malloc(sizeof(IPC_REQ)); //debug_malloc(sizeof(IPC_REQ), "send_req_checkmailbox (1)");
    ipc->name_to=ipc_daemon_name;
    ipc->name_from=ipc_my_name;
    ipc->data=0;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_MAILBOX,ipc);
  }  
}

void send_req_stopcheck(void)
{
  if (daemon_present!=-1)
  {
    IPC_REQ *ipc=malloc(sizeof(IPC_REQ)); //debug_malloc(sizeof(IPC_REQ), "send_req_stopcheck (1)");
    ipc->name_to=ipc_daemon_name;
    ipc->name_from=ipc_my_name;
    ipc->data=0;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_STOP_CHECKING,ipc);
  }    
}


void check_mailbox(GUI *data)
{
  send_req_checkmailbox();
}

void set_state_for_all(int state)
{
  ML_VIEW *mail_cur=(ML_VIEW *)&mails;
  while((mail_cur=mail_cur->next))
  {
    mail_cur->prev_state = mail_cur->state;
    mail_cur->state=state;
  }
}

void set_state_download(GUI *data)
{
  ML_VIEW *cur_menu;
  cur_menu=MenuGetUserPointer(data);
  cur_menu->prev_state = cur_menu->state;
  cur_menu->state=M_LOAD_FULL;
  GeneralFuncF1(2);
}

void set_state_not_download(GUI *data)
{
  ML_VIEW *cur_menu;
  cur_menu=MenuGetUserPointer(data);
  cur_menu->state=cur_menu->prev_state;
  GeneralFuncF1(2);
}

void set_state_delete(GUI *data)
{
  ML_VIEW *cur_menu;
  cur_menu=MenuGetUserPointer(data);
  cur_menu->prev_state = cur_menu->state;
  cur_menu->state=M_DELETE;
  GeneralFuncF1(2);
}

void set_state_not_delete(GUI *data)
{
  ML_VIEW *cur_menu;
  cur_menu=MenuGetUserPointer(data);
  cur_menu->state=cur_menu->prev_state;
  GeneralFuncF1(2);
}

void set_state_download_all(GUI *data)
{
  set_state_for_all(M_LOAD_FULL);
  GeneralFuncF1(2);
}

void set_state_delete_all(GUI *data)
{
  set_state_for_all(M_DELETE);
  GeneralFuncF1(2);
}

void delete_record(GUI *data)
{
  ML_VIEW *cur_menu;
  cur_menu=MenuGetUserPointer(data);
  ML_VIEW *mail_cur=(ML_VIEW *)&mails;
  ML_VIEW *ml_prev=mail_cur;
  while((mail_cur=mail_cur->next))
  {
    if(!(strcmp(mail_cur->uidl,cur_menu->uidl)))
    {
      ml_prev->next=mail_cur->next;

      if(mail_cur->uidl)             debug_mfree(mail_cur->uidl, "delete_record (1)");
      if(mail_cur->header)           debug_mfree(mail_cur->header, "delete_record (2)");
      if(mail_cur->subject)          debug_mfree(mail_cur->subject, "delete_record (3)");
      if(mail_cur->from)             debug_mfree(mail_cur->from, "delete_record (4)");
      if(mail_cur->to)               debug_mfree(mail_cur->to, "delete_record (5)");
      if(mail_cur->content_type)     debug_mfree(mail_cur->content_type, "delete_record (6)");
      if(mail_cur->content_encoding) debug_mfree(mail_cur->content_encoding, "delete_record (7)");
      if(mail_cur->date)             debug_mfree(mail_cur->date, "delete_record (8)");
      debug_mfree(mail_cur, "delete_record (9)");

      request_recount_mailmenu=1;
      break;        
    }
    ml_prev=mail_cur;
  }
  GeneralFuncF1(2);
}
    
void delete_all_records(GUI *data)
{
  FreeMailDB();
  request_recount_mailmenu=1;
  GeneralFuncF1(2);
}  

void show_info(GUI *data)
{
  ML_VIEW *cur_menu;
  cur_menu=MenuGetUserPointer(data);
  create_info_view(cur_menu);
  GeneralFuncF1(2);
}

void back(GUI *data)
{
  GeneralFuncF1(1);
}


#define OPTIONS_ITEMS_N 11
HEADER_DESC options_menuhdr={0,0,0,0,NULL,(int)"Опции",LGP_NULL};

MENUITEM_DESC options_menu_ITEMS[OPTIONS_ITEMS_N]=
{
  {NULL,(int)"Проверить почту",     LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //0
  {NULL,(int)"Догрузить",           LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //1
  {NULL,(int)"Не загружать",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //2
  {NULL,(int)"Удалить",             LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //3
  {NULL,(int)"Не удалять",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //4
  {NULL,(int)"Удалить все",         LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //5
  {NULL,(int)"Удалить запись",      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //6
  {NULL,(int)"Очистить список",     LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //7
  {NULL,(int)"Догрузить все",       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //8
  {NULL,(int)"Информация",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //9
  {NULL,(int)"Назад",               LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //10
};

const MENUPROCS_DESC options_menu_HNDLS[OPTIONS_ITEMS_N]=
{
  check_mailbox,
  set_state_download,
  set_state_not_download,
  set_state_delete,
  set_state_not_delete,
  set_state_delete_all,
  delete_record,
  delete_all_records,
  set_state_download_all,
  show_info,
  back,  
};

MENU_DESC options_menu_STRUCT=
{
  0,(void *)NULL,(void*)NULL,NULL,
  menusoftkeys,
  &menu_skt,
  8,
  NULL,
  options_menu_ITEMS,   //Items
  options_menu_HNDLS,   //Procs
  OPTIONS_ITEMS_N //n
};

void create_options_menu(ML_VIEW *i)
{
  int to_remove[OPTIONS_ITEMS_N+1];
  int n;

  n=0;
  if (i)
  {
    if (i->state==M_FULL_LOADED || i->state==M_LOAD_FULL)
      to_remove[++n]=1;

    if (i->state!=M_LOAD_FULL)
      to_remove[++n]=2;
    
    if (i->state==M_DELETE)
    {
      to_remove[++n]=1;
      to_remove[++n]=3;
    }
    else
      to_remove[++n]=4;
  }
  else
  {
    to_remove[++n]=1;
    to_remove[++n]=2;
    to_remove[++n]=3;
    to_remove[++n]=4;
    to_remove[++n]=5;
    to_remove[++n]=6;
    to_remove[++n]=7;
    to_remove[++n]=8;
    to_remove[++n]=9;
  }
    
  if (get_mlist_N()==1)
  {
    to_remove[++n]=5;
    to_remove[++n]=7;
    to_remove[++n]=8;
  }
  if (daemon_present==-1)
  {
    to_remove[++n]=0;
  }
  to_remove[0]=n;
  if (n==OPTIONS_ITEMS_N) return;
  patch_header_small((HEADER_DESC*)(&options_menuhdr));
  options_menu_id=CreateMenu(1,0,&options_menu_STRUCT,&options_menuhdr,0,OPTIONS_ITEMS_N,i,to_remove);
}

// ----------------------------------------------------------------------------------

HEADER_DESC maillist_menuhdr={0,0,0,0,NULL,(int)"Входящие",LGP_NULL};


int maillist_menu_onkey(void *data, GUI_MSG *msg)
{
  ML_VIEW *mail_cur;
  int i;
  int keycode;
  keycode=msg->keys;
  i=GetCurMenuItem(data);
  mail_cur=find_mlist_ByID(i);
  switch(keycode)
  {
  case 0x18:
    //    GeneralFunc_F1(1);
    create_options_menu(mail_cur);
    return(-1);
    
  case 0x3D:
    if (!mail_cur) return (0);
    if (mail_cur->state==M_FULL_LOADED)
    {
      if(!mail_cur->is_read)
      {
        mail_cur->is_read=1;
        SUBPROC((void *)write_mail_DB);
      }
    }
    view_mail_id=create_view(mail_cur);
    return(-1);
  } 
  return(0);
}

void maillist_menu_ghook(void *data, int cmd)
{
  if (cmd==2)
  {
    InitMailDB();
    Menu_SetItemCountDyn(data,get_mlist_N());
  }    
  if (cmd==0x0A)
  {
    DisableIDLETMR();
    if (request_recount_mailmenu)
    {
      request_recount_mailmenu=0;
      Menu_SetItemCountDyn(data,get_mlist_N());
    }
  }
}

void maillist_menu_iconhndl(void *data, int curitem, void *unk)
{
  ML_VIEW *mail_cur;
  WSHDR *ws;
  char *subject;

  mail_cur=find_mlist_ByID(curitem);
  if (!mail_cur) return;
  void *item=AllocMenuItem(data);
  subject=get_subject(mail_cur);

  if (subject)
  {
    subject=strchr(subject,':')+1;
    while(*subject==' ') subject++;
    ws=AllocMenuWS(data,strlen(subject));
    wsprintf(ws,_percent_t,subject);
  }
  else    
  {
    ws=AllocMenuWS(data,10);
    wsprintf(ws,_percent_t,"Ошибка");
  }
  SetMenuItemIconArray(data,item,S_ICONS+GetIconIndex(mail_cur));
  SetMenuItemText(data,item,ws,curitem);
  SetMenuItemIcon(data,curitem,0);
}


MENU_DESC maillist_menu=
{
  8,maillist_menu_onkey,maillist_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x11,
  maillist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};




//------------------------------------------------------------------------------------

void main_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

int main_menu_onkey(void *data, GUI_MSG *msg)
{
  if (msg->keys==0x18)
  {
    return(-1);
  }

  return(0);
}


void CreateMailList(void)
{
  patch_header(&maillist_menuhdr);
  maillist_menu_id=CreateMenu(0,0,&maillist_menu,&maillist_menuhdr,0,0,0,0);
}

void Incoming(GUI *data)
{
  CreateMailList();
  if (pop_stat && daemon_present!=-1)
  {
    if (pop_stat->connect_state!=0)
    {
      create_gui();
    }
  }
}

void Outgoing(GUI *data)
{
}


void Options(GUI *data)
{
  WSHDR *ws1, ws1loc;
  unsigned short ws1num[128];
  ws1=CreateLocalWS(&ws1loc,ws1num,128);
  str_2ws(ws1,successed_config_filename,128);
  ExecuteFile(ws1,0,0);
}

void StatScr(GUI *data)
{
  create_gui();
}

void About(GUI *data)
{
  ShowMSG(2, (int)"MailClient v0.1\n(C) by Kren\nRst7/CBSIE");
}

void Exit(GUI *data)
{
  GeneralFuncF1(1);
}

HEADER_DESC mainmenu_HDR={0,0,0,0,NULL,(int)"MailViewer",LGP_NULL};


MENUITEM_DESC mainmenu_ITEMS[6]=
{
  {NULL,(int)"Входящие",  LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Исходящие", LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Настройки", LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Статистика",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Об эльфе",  LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Выход",     LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

const MENUPROCS_DESC  mainmenu_HNDLS[6]=
{
  Incoming,
  Outgoing,
  Options,
  StatScr,
  About,
  Exit,
};


MENU_DESC mainmenu_STRUCT=
{
  8,main_menu_onkey,main_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0x11,
  NULL,
  mainmenu_ITEMS,   //Items
  mainmenu_HNDLS,   //Procs
  6   //n
};


IPC_REQ gipc;
// ------------------------  Creating CSM -------------------------------- //
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  patch_header(&mainmenu_HDR);

  gipc.name_to=ipc_my_name;
  gipc.name_from=ipc_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);

  csm->gui_id=main_menu_id=CreateMenu(0,0,&mainmenu_STRUCT,&mainmenu_HDR,0,6,0,0);
}

void maincsm_onclose(CSM_RAM *csm)
{
  gipc.name_to=ipc_daemon_name;
  gipc.name_from=ipc_my_name;
  gipc.data=0;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_VIEWER_LOGFF,&gipc);
  FreeMailDB();
  SUBPROC((void *)ElfKiller);
}

void ReInitConfig(void)
{
  InitConfig();
  S_ICONS[0]=(int)I_UNREAD;
  S_ICONS[1]=(int)I_READ;
  S_ICONS[2]=(int)I_HEADER;
  S_ICONS[3]=(int)I_HEADER_ATT;
  S_ICONS[4]=(int)I_MES_UNREAD_ATT;
  S_ICONS[5]=(int)I_MES_READ_ATT;
  S_ICONS[6]=(int)I_MES_DOWN;
  S_ICONS[7]=(int)I_MES_DEL;  
}

extern volatile int stat_gui_id;

void CheckDoubleRun(void)
{
  if ((int)(gipc.data)>1)
  {
    LockSched();
    CloseCSM(maincsm_id);
    ShowMSG(1,(int)"MailViewer already started!");
    UnlockSched();
  }
  else
  {
    gipc.name_to=ipc_daemon_name;
    gipc.name_from=ipc_my_name;
    gipc.data=0;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_VIEWER_LOGON,&gipc);
  }
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      ShowMSG(1,(int)"MailViewer config updated!");
      ReInitConfig();
    }
  }
  if (msg->msg==MSG_IPC)  // Пришло сообщение, возможно от демона
  { 
    IPC_REQ *ipc;
    if ((ipc=(IPC_REQ*)msg->data0))
    {
      if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
      {
        switch (msg->submess)
        {
        case IPC_DAEMON_LOGON:
          if (daemon_present)
          {
            daemon_present=0;
            pop_stat=ipc->data;
            ipc->name_to=ipc->name_from;
            ipc->name_from=ipc_my_name;
            ipc->data=0;
            GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_VIEWER_LOGON,ipc);
          }
          break;
          
        case IPC_DAEMON_LOGOFF:
          if (!daemon_present)   // только если демон до этого заходил
          {
            daemon_present=-1;   // Демон вышел
            pop_stat=NULL;
          }
          break;
          
        case IPC_CHECK_MAILBOX:
          switch ((int)(ipc->data))
          {
          case 1:
            if (!stat_gui_id)
              create_gui();
            break;
            
          case 0:
            ShowMSG(1,(int)"Can't connect!");
            break;
          }
          mfree(ipc);
          //debug_mfree(ipc, "csm1");
          break;
          
         
        case IPC_LOADING_FINISHED:
          if (maillist_menu_id && stat_gui_id)
          {
            GeneralFunc_flag1(stat_gui_id,2);
          }
          mfree(ipc);
          //debug_mfree(ipc, "csm2");
          break;
          
        case IPC_CHECK_DOUBLERUN:
          ipc->data=(void *)((int)(ipc->data)+1);
          //Если приняли свое собственное сообщение, значит запускаем чекер
          if (ipc->name_from==ipc_my_name) SUBPROC((void *)CheckDoubleRun);
          break;
        }
      }
    }
  }
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
    if ((int)msg->data0==maillist_menu_id)
    {
      maillist_menu_id=0;
    }
    if ((int)msg->data0==options_menu_id)
    {
      options_menu_id=0;
      if ((int)msg->data1==2)
      {
        SUBPROC((void *)write_mail_DB);
      }   
    }
    if ((int)msg->data0==stat_gui_id)
    {
      stat_gui_id=0;
      if ((int)msg->data1==2) 
      {
        if (maillist_menu_id)
        {
          InitMailDB();
          request_recount_mailmenu=1;
          if (IsGuiOnTop(maillist_menu_id)) RefreshGUI();
        }
      }
      if ((int)msg->data1==3)
      {
        if (maillist_menu_id)
          GeneralFunc_flag1(maillist_menu_id,1);
      }
    }
  }
  return(1);
}


const int minus11=-11;
unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};


void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"MailViewer");
}


int main()
{
  MAIN_CSM main_csm;
  ReInitConfig();
  LockSched();
  UpdateCSMname();
  maincsm_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
}
