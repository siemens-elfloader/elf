#include "../inc/swilib.h"
#include "history.h"
#include "string_util.h"
#include "lang.h"
extern const char HIST_PATH[128];
extern const char DEFAULT_DISC[128];

char q[40];

void Log(char* module, char* logstr)
{
  volatile int hFile;
  unsigned int io_error = 0;
  char fullname[] ="4:\\jlog.txt";
  fullname[0] = DEFAULT_DISC[0];
  char* buffer = malloc(65536);
  zeromem(buffer,65536);
  sprintf(buffer,"[%s]: %s\r\n",module, logstr);
  int buf_len = strlen(buffer);
  // Открываем файл на дозапись и создаём в случае неудачи
  hFile = fopen(fullname,A_ReadWrite +A_Create+ A_Append + A_BIN,P_READ+P_WRITE, &io_error);
  if(!io_error)
  {
    fwrite(hFile, buffer, buf_len-1, &io_error);
    fclose(hFile, &io_error);
  }
  else
  {
    sprintf(q, "Log:[%s] I/O Err #%u", module, io_error);
    LockSched();
    ShowMSG(1,(int)q); 
    UnlockSched();
  }
  mfree(buffer);
  
}

// Логгер потока для удобства отдельно
void Log_XMLStream(char* logstr, int size)
{
  volatile int hFile;
  unsigned int io_error = 0;
  char fullname[] ="4:\\test.xml";
  fullname[0] = DEFAULT_DISC[0];
  // Открываем файл (режим перезаписи)
  hFile = fopen(fullname,A_ReadWrite +A_Create+ A_Append + A_BIN,P_READ+P_WRITE, &io_error);
  if(!io_error)
  {
    fwrite(hFile, logstr, size, &io_error);
    fclose(hFile, &io_error);
  }
  else
  {
    sprintf(q, "Log_XMLStream: I/O Err  #%u", io_error);
    LockSched();
    ShowMSG(1,(int)q); 
    UnlockSched();
  } 
}

/*
  Добавлет строку в историю контакта CLIST
*/
typedef struct
{
  char *fname;
  char *buffer;
  unsigned int txt_len;
}HIST_RECORD_INFO;

//Context:HELPER
void _add2history(HIST_RECORD_INFO *info)
{
  volatile int hFile;
  unsigned int io_error = 0;
  // Открываем файл на дозапись и создаём в случае неудачи
  WSHDR *filename_WS = AllocWS(256);
  char *filename_utf8 = malloc(256);
  utf8_2ws(filename_WS, info->fname, 256);  // Перевели UTF-8 в UTF-16
  ws_2str(filename_WS, filename_utf8, 256); // Перевели UTF-16 в UTF-8 для файлов
  hFile = fopen(filename_utf8,A_ReadWrite + A_Append + A_BIN,P_READ+P_WRITE, &io_error);
  
  if(io_error==2) // нет файла
  {
    hFile = fopen(filename_utf8,A_ReadWrite+A_Create+ A_BIN,P_READ+P_WRITE, &io_error);
  }
  if(!io_error)
  {
    fwrite(hFile, info->buffer, info->txt_len-1, &io_error);
    fclose(hFile, &io_error);
  }
  else
  {
    sprintf(q, LG_ERRORWH, io_error);
    LockSched();
    ShowMSG(1,(int)q); 
    UnlockSched();
  }
  FreeWS(filename_WS);
  mfree(filename_utf8);
  mfree(info->fname);
  mfree(info->buffer);
  mfree(info);  
}

void Add2History(CLIST *CListEx, char *header, char *message)
{
  char *fullname = malloc(512);
  char delim[] = "\r\n----------\r\n";
  unsigned int delim_len = strlen(delim);
  message = convUTF8_to_ANSI_STR(message);
  header = convUTF8_to_ANSI_STR(header);
  unsigned int hdr_len = strlen(header);
  unsigned int msg_len = strlen(message);
  unsigned int buf_len = delim_len+hdr_len+msg_len+1;
  char *buffer = malloc(buf_len);
  strcpy(buffer, delim);
  strcat(buffer, header);
  strcat(buffer, message);
  mfree(message);
  mfree(header);
  strcpy(fullname, HIST_PATH);
  sprintf(fullname,"%s%s.txt", fullname, CListEx->JID);
  
  HIST_RECORD_INFO *info = malloc(sizeof(HIST_RECORD_INFO));
  info->fname   =  fullname;
  info->buffer  = buffer;
  info->txt_len = buf_len;
  
  // Отправляем в хелпер
  SUBPROC((void*)_add2history, info);
}
//EOL,EOF
