#include "../inc/swilib.h"
#include "history.h"
#include "file_works.h"
#include "string_works.h"
#include "lang.h"

extern const int HISTORY_DEPTH;
const int MAX_FILE_SIZE = 32768;
const char *NEW_LINE = "\r\n";

void CheckHistory(const char *url)
{
  char *default_url;
  int f;
  unsigned ul;
  char * history_file = getSymbolicPath("$urlcache\\history.txt");
  if ((f = fopen(history_file, A_ReadOnly + A_Create + A_BIN, P_READ + P_WRITE, &ul)) == -1)
  {
    if ((f = fopen(history_file, A_WriteOnly+A_Create+A_BIN,P_READ+P_WRITE,&ul)) == -1)
    {
      LockSched();
      ShowMSG(1,(int)lgpData[LGP_HistoryFileFailed]);
      UnlockSched();
      mfree(history_file);
      return;
    }

    default_url = (char *) malloc(strlen(url) + 3);
    strcpy(default_url, url); strcat(default_url, NEW_LINE);
    
    fwrite(f,default_url,strlen(default_url), &ul);
    fclose(f, &ul);

    mfree(default_url);
    mfree(history_file);
    return;
  }
  fclose(f, &ul);
  mfree(history_file);
}

//------------------------------------------------------------------------------

char **GetHistory(int *cnt)
{
  char *history_buf,*s,*tmp;
  char **history;
  int f,flen,history_depth=0,i;
  unsigned ul;
  char * history_file = getSymbolicPath("$urlcache\\history.txt");
  f=fopen(history_file, A_ReadOnly+A_Create+A_BIN,P_READ+P_WRITE,&ul);
  if (f==-1)
  {
    LockSched();
    ShowMSG(1,(int)lgpData[LGP_HistoryFileFailed]);
    UnlockSched();
    *cnt=history_depth;
    mfree(history_file);
    return 0;
  }
  flen=lseek(f,0,2,&ul,&ul)+1;
  lseek(f,0,0,&ul,&ul);

  flen=(flen>MAX_FILE_SIZE)?MAX_FILE_SIZE:flen;
  history_buf=(char*)malloc(MAX_FILE_SIZE);
  history_buf[flen-1]=0;
  fread(f,history_buf,flen,&ul);
  fclose(f,&ul);

  history=(char**)malloc(sizeof(char *)*HISTORY_DEPTH);
  for(i=0;i<HISTORY_DEPTH;i++)
  history[i]=0;
  s=history_buf;
  tmp=history_buf;
  for(i=0;i<HISTORY_DEPTH&&s&&tmp<history_buf+flen;i++)
  {
    s=strstr(tmp,NEW_LINE);
    if(s)
    {
      history[i]=(char*)malloc(s-tmp+1);
      memcpy(history[i],tmp,s-tmp);
      history[i][s-tmp]=0;
      tmp=s+2;
      history_depth++;
    }
  }
  *cnt=history_depth;
  mfree(history_buf);
  mfree(history_file);
  return history;
}

//------------------------------------------------------------------------------

void AddURLToHistory(const char *url)
{
  char *history_buf, **history, *s, *tmp;
  int f, flen, history_depth = 0, i;
  unsigned ul;
  char * history_file = getSymbolicPath("$urlcache\\history.txt");
  if ((f=fopen(history_file, A_ReadWrite+A_Create+A_BIN,P_READ+P_WRITE,&ul))==-1)
  {
    LockSched();
    ShowMSG(1,(int)lgpData[LGP_HistoryFileFailed]);
    UnlockSched();
    mfree(history_file);
    return;
  }

  flen = lseek(f, 0, 2, &ul, &ul)+1;
  lseek(f, 0, 0, &ul, &ul);


  flen = (flen>MAX_FILE_SIZE)?MAX_FILE_SIZE:flen;
  history_buf = (char*)malloc(MAX_FILE_SIZE);
  history_buf[flen-1] = 0;
  fread(f,history_buf,flen,&ul);
  fclose(f,&ul);

  history = (char**)malloc(sizeof(char *) * HISTORY_DEPTH);
  for(i = 0; i < HISTORY_DEPTH; i++)
  history[i] = 0;

  s = history_buf;
  tmp = history_buf;
  for(i = 0; i < HISTORY_DEPTH && s && tmp < history_buf + flen; i++)
  {
    s = strstr(tmp, NEW_LINE);
    if(s)
    {
      history[i] = (char*)malloc(s - tmp + 1);
      memcpy(history[i], tmp, s-tmp);
      history[i][s-tmp] = 0;
      tmp = s + 2;
      history_depth++;
    }
  }
  for(i = 0; i < history_depth; i++)
  {
    if(!strcmp(history[i], url))
    {
      while(i)
      {
        s = history[i];
        history[i] = history[i-1];
        history[i-1] = s;
        i--;
      }
      break;
    }
  }
  if(strcmp(history[0], url))
  {
    if(history[HISTORY_DEPTH-1])
      mfree(history[HISTORY_DEPTH-1]);
    for(i = HISTORY_DEPTH-1; i>0; i--)
      history[i] = history[i-1];
    history[0] = (char*)malloc(strlen(url)+1);
    strcpy(history[0], url);
    history_depth++;
    history_depth = (history_depth>HISTORY_DEPTH)?HISTORY_DEPTH:history_depth;
  }


  tmp = history_buf;
  tmp[0] = 0;
  for(i = 0; i < history_depth; i++)
  {
    strcat(tmp, history[i]);
    strcat(tmp, NEW_LINE);
    mfree(history[i]);
  }
  mfree(history);

  unlink(history_file, &ul);

  f=fopen(history_file,A_WriteOnly+A_Create+A_BIN,P_READ+P_WRITE,&ul);
  if (f==-1)
  {
    LockSched();
    ShowMSG(1,(int)lgpData[LGP_HistoryFileFailed]);
    UnlockSched();
    mfree(history_buf);
    mfree(history_file);
    return;
  }
  fwrite(f,history_buf,strlen(history_buf), &ul);
  fclose(f, &ul);
  mfree(history_buf);
  mfree(history_file);
}
