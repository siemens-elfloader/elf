#include "../inc/swilib.h"
#include "naticq.h"
#include "history.h"
#include "language.h"

extern const char HIST_PATH[64];
extern const int LOG_ALL;
/*
  Добавлет строку в историю контакта CLIST
*/


static do_logwrite(unsigned int uin, char *text)
{
  volatile int hFile;
  unsigned int io_error = 0;
  char error[36];
  char fullname[128];
  snprintf(fullname,127,"%s\\%u.txt", HIST_PATH, uin);
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

void Add2History(CLIST *CListEx, char *header, char *message)
{
  static const char delim[] = "\r\n----------\r\n";
  int len;
  if (!LOG_ALL) return;
  len=sizeof(delim)+strlen(header)+strlen(message);
  char *text=malloc(len);
  strcpy(text,delim);
  strcat(text,header);
  strcat(text,message);
  SUBPROC((void*)do_logwrite,CListEx->uin,text);
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
  char hdr[] = "(System message)";
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
  Add2History(CListEx, hdr, message);
}
