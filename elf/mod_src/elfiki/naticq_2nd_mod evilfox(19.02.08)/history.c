#include "../inc/swilib.h"
#include "naticq.h"
#include "history.h"
#include "language.h"

extern const char HIST_PATH[64];
extern const int LOG_ALL;
#ifdef EVILFOX
#else
extern const int HISTORY_TYPE;
#endif
extern const unsigned int UIN;
/*
  Добавлет строку в историю контакта CLIST
*/
#ifdef EVILFOX
static do_logwrite(const char *n_a_m_e_z, char *text)
{
  volatile int hFile;
  unsigned int io_error = 0;
  char error[36];
  char fullname[128];
  snprintf(fullname,127,"%s\\%u\\%s.txt", HIST_PATH, UIN, n_a_m_e_z);
  hFile = fopen(fullname,A_ReadWrite + A_Create + A_Append + A_BIN,P_READ+P_WRITE, &io_error);
  if(hFile!=-1)
  {
    fwrite(hFile, text, strlen(text), &io_error);
    fclose(hFile, &io_error);
  }
  else
  {
    snprintf(error,35, LG_HISTIOERR, io_error);
    LockSched();
    ShowMSG(1,(int)error); 
    UnlockSched();
  }
  mfree(text);
}
#else
static do_logwrite(unsigned int uin, char *text)
{
  volatile int hFile;
  unsigned int io_error = 0;
  unsigned int ul;
  char error[36];
  char fullname[128];
  char hist_path[128];
  if(HISTORY_TYPE)
    snprintf(hist_path,127,"%s\\%u",HIST_PATH, UIN);
  else
    snprintf(hist_path,127,"%s",HIST_PATH);
  if (!isdir(hist_path,&ul))
  {
    mkdir(hist_path,&ul);
  }
  snprintf(fullname,127,"%s\\%u.txt", hist_path, uin);
  // Открываем файл на дозапись и создаём в случае неудачи
  hFile = fopen(fullname,A_ReadWrite + A_Create + A_Append + A_BIN,P_READ+P_WRITE, &io_error);
  if(hFile!=-1)
  {
    fwrite(hFile, text, strlen(text), &io_error);
    fclose(hFile, &io_error);
  }
  else
  {
    snprintf(error,35, LG_HISTIOERR, io_error);
    LockSched();
    ShowMSG(1,(int)error); 
    UnlockSched();
  }
  mfree(text);
}
#endif

void Add2History(CLIST *CListEx, char *header, char *message, int direction)
{
  static const char *delim = "\r\n--------------<>-%04d\r\n";
  int len;
  if (!LOG_ALL) return;
  len=strlen(delim)+strlen(header)+strlen(message);
  char *text=malloc(len+1);
  sprintf(text,delim,direction);
  strcat(text,header);
  strcat(text,message);
#ifdef EVILFOX
  SUBPROC((void*)do_logwrite,CListEx->name,text);
#else
  SUBPROC((void*)do_logwrite,CListEx->uin,text);
#endif
}

extern LOGQ *NewLOGQ(const char *s);
extern int AddLOGQ(LOGQ **queue, LOGQ *p);

//Делает ярким последний икс-статус, а остальные тусклыми
void ActivateLastX(LOGQ *p)
{
  LOGQ *q = p, *lastX = 0;
  while(q)
  {
    if((q->type&0x0F) == 3)
    {
      lastX = q;
      q->type = 0x13;
    }
    q = q->next;
  }
  if(lastX) lastX->type = 3;
}

//Добавить элемент в лог первым
void AddFirstLOGQ(CLIST *t, LOGQ *p)
{
  LOGQ *q = t->log;
  if(!p) return;
  t->log = p;
  while(p->next)
    p = p->next;
  p->next = q;
  ActivateLastX(t->log);
}

//Удаляем лог с заданного элемента
void DeleteLOGQ(LOGQ *p)
{
  if(!p) return;
  if(p->next) DeleteLOGQ(p->next);
  mfree(p);
}

//Проверка что в логе не только иксстасусы
int CheckLOGQ(CLIST *t)
{
  LOGQ *p = t->log;
  if(!p) return 0;
  for(; p->next && (p->type&0x0F)==3; p=p->next);
  if(p->next)
    if((p->type&0x0F)!=3)
      return 1;
  DeleteLOGQ(t->log);
  t->log = 0;
  return 0;
}

int GetHistory(CLIST *t, int bufsize)
{
  LOGQ *log, *head;
  static const char *delim = "\r\n--------------<>-000";
  volatile int hFile;
  unsigned int io_error = 0;
  char fullname[128], *s, *b, *e, *text, *str, *buf;
  int i, delimlen = strlen(delim)+3, direction;

//  unsigned uin = t->uin;

  
  if(CheckLOGQ(t)) return 0;
  
  buf = text = malloc(bufsize);
  text[0] = 0;
  text[bufsize-1] = 0;
#ifdef EVILFOX
    snprintf(fullname,127,"%s\\%u\\%s.txt", HIST_PATH, UIN, t->name);
#else
  if(HISTORY_TYPE)
    snprintf(fullname,127,"%s\\%u\\%u.txt", HIST_PATH, UIN, uin);
  else
    snprintf(fullname,127,"%s\\%u.txt", HIST_PATH, uin);
#endif
  // Открываем файл на чтение
  hFile = fopen(fullname,A_ReadOnly + A_BIN,P_READ, &io_error);
  if(hFile!=-1)
  {
    lseek(hFile, -(bufsize-1), S_END, &io_error, &io_error);
    i = fread(hFile, text, bufsize-1, &io_error);
    text[i] = 0;
    fclose(hFile, &io_error);
    s = strstr(text, delim);  
    
    head = NewLOGQ("");
    head->next = 0;
    
    while(s && text)
    {
      direction = (*(s+delimlen-3))-0x30; 
      text = s+delimlen;
      s = strstr(text, delim); 
      e = !s?(text+strlen(text)):s;
      
      str = malloc(e-text+1);
      if(e-text > 0) memcpy(str, text, e-text);
      str[e-text] = 0; 

//      snprintf(fullname, 127, "\r\n-----\r\n%08X\r\n%08X, %d\r\n%08X, %d\r\n----\r\n", text, e, direction, s, e-text);
      b = strstr(str, "\r\n");

      
//      log = NewLOGQ(fullname);
      if(b)
      {
        log = NewLOGQ(b+2);
        if(b-str >= 0) memcpy(log->hdr, str, b-str);
        log->hdr[b-str] = 0;
      }
      else
      {
        log = NewLOGQ("");
        strcpy(log->hdr, str);
      }
      
      log->type = direction|0x10;
      log->acked = 0;
      log->ID=0xFFFFFFFF;
      
      AddLOGQ(&head, log);
      
      //mfree(log);
      mfree(str);
    }
    AddFirstLOGQ(t, head->next);
    mfree(head);
      
  }

  mfree(buf);
  return 0;
}

void GetStatusById(char *buffer, int id)
{
  
  // ??? Тут надо разбираться со статусами
  // Похоже, не все коды верные...
switch(id)
{
case 0: {strcpy(buffer,"Online");break;}
case 1: {strcpy(buffer, "Invisible");break;}
case 2: {strcpy(buffer, "Away");break;}
case 3: {strcpy(buffer, "N/A");break;}
case 4: {strcpy(buffer, "Occupied");break;}
case 5: {strcpy(buffer, "DND");break;}
case 6: {strcpy(buffer, "Online");break;}
case 7: {strcpy(buffer, "FFC");break;}
default: {sprintf(buffer, "UNK: %d", id);}
}
}

void LogStatusChange(CLIST *CListEx)
{
  extern const int LOG_STATCH;
  if(!LOG_STATCH){return;}
  if(CListEx->state>7){return;}
  if(CListEx->log==NULL){return;}
  char hdr[] = "(System message) ";
  char msg[] = "%s меняет статус на %s\r\n";
  char message[100];
  char nickname[64];
  char status[20];
  if(CListEx->name)
  {
    strcpy(nickname, CListEx->name);
  }
  else
  {
    snprintf(nickname,63, "%u", CListEx->uin);
  }
  GetStatusById(status, CListEx->state);
  sprintf(message, msg, nickname, status);
  Add2History(CListEx, hdr, message, 0);
}
