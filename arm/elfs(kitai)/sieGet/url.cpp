#include "include.h"
#include "inet.h"
#include "url.h"
#include "gui.h"
#include "log.h"
#include "daemon.h"
#include "rect_patcher.h"

extern "C"
{
  extern unsigned long strtoul(const char *, char **, int);
};

#define ST_ERR -1
#define ST_FINISH 0
#define ST_HOST 1
#define ST_PORT 2
#define ST_PATH 3
#define ST_PARAM 4
#define ST_FRAGMENT 5

char host_term[] = ":/?#";
int  host_st[] = {ST_PORT, ST_PATH, ST_PARAM, ST_FRAGMENT};
char port_term[] = ":/?#";
int  port_st[] = {ST_ERR, ST_PATH, ST_PARAM, ST_FRAGMENT};
char path_term[] = "?#";
int  path_st[] = {ST_PARAM, ST_FRAGMENT};
char param_term[] = "#";
int  param_st[] = {ST_FRAGMENT};

int URL::Parse(char * s_url)
{
  char * tmp = s_url;
  char * scheme_delim = strstr(tmp, "://");
  if (scheme_delim)
  {
    int schlen = scheme_delim-tmp;
    this->scheme = new char[schlen+1];
    strncpy(this->scheme, tmp, schlen);
    this->scheme[schlen] = 0;
    tmp += schlen+3;
  }
  else
  {
    this->scheme = new char[5];
    strcpy(this->scheme, "http");
  }
  int st = ST_HOST;
  int len = strlen(tmp);
  int clen = 0;
  while (st>0)
  {
    switch(st)
    {
    case ST_HOST:
      if (strchr(host_term, tmp[clen]) || !tmp[clen])
      {
        if (tmp[clen])
          st = host_st[strchr(host_term, tmp[clen])-host_term];
        else
          st = ST_FINISH;
        this->host = new char[clen+1];
        strncpy(this->host, tmp, clen);
        this->host[clen] = 0;
        tmp += clen+1;
        len -= clen+1;
        clen = 0;
      }
      else
        clen++;
      break;
    case ST_PORT:
      this->port = strtoul(tmp, &tmp, 10);
      if (tmp[clen])
        st = port_st[strchr(port_term, *tmp++)-port_term];
      else
        st = ST_FINISH;
      break;
    case ST_PATH:
      if (strchr(path_term, tmp[clen]) || !tmp[clen])
      {
        if (tmp[clen])
          st = path_st[strchr(path_term, tmp[clen])-path_term];
        else
          st = ST_FINISH;
        this->path = new char[clen+1];
        strncpy(this->path, tmp, clen);
        this->path[clen] = 0;
        tmp += clen+1;
        len -= clen+1;
        clen = 0;
      }
      else
        clen++;
      break;
    case ST_PARAM:
      if (strchr(param_term, tmp[clen]) || !tmp[clen])
      {
        if (tmp[clen])
          st = param_st[strchr(param_term, tmp[clen])-param_term];
        else
          st = ST_FINISH;
        this->param = new char[clen+1];
        strncpy(this->param, tmp, clen);
        this->param[clen] = 0;
        tmp += clen+1;
        len -= clen+1;
        clen = 0;
      }
      else
        clen++;
      break;
    case ST_FRAGMENT:
      if (!tmp[clen])
      {
        st = ST_FINISH;
        this->fragment = new char[clen+1];
        strncpy(this->fragment, tmp, clen);
        this->fragment[clen] = 0;
        tmp += clen+1;
        len -= clen+1;
        clen = 0;
      }
      else
        clen++;
      break;
    }
  }
  if (!this->port)
    this->port = 80;
  return 1;
}

void URL::Print(Log * log)
{
  char * msg = new char[128];
  if (scheme)
  {
    sprintf(msg, "Scheme: %s", scheme);
    log->Print(msg, CLR_Violet);
  }
  if (host)
  {
    sprintf(msg, "Host: %s", host);
    log->Print(msg, CLR_Violet);
  }
  sprintf(msg, "Port: %d", port);
  log->Print(msg, CLR_Violet);
  if (path)
  {
    sprintf(msg, "Path: %s", path);
    log->Print(msg, CLR_Violet);
  }
  if (param)
  {
    sprintf(msg, "Params: %s", param);
    log->Print(msg, CLR_Violet);
  }
  if (fragment)
  {
    sprintf(msg, "Fragment: %s", fragment);
    log->Print(msg, CLR_Violet);
  }
  delete msg;
}

URL::~URL()
{
  _safe_delete(fragment);
  _safe_delete(host);
  _safe_delete(param);
  _safe_delete(path);
  _safe_delete(scheme);
}

URL::URL()
{
  this->fragment = NULL;
  this->host = NULL;
  this->port = NULL;
  this->param = NULL;
  this->path = NULL;
  this->scheme = NULL;
}

/*******************************************************************************
  URLFile
*******************************************************************************/

URLFile::URLFile()
{
  url = NULL;
}

URLFile::~URLFile()
{
  _safe_delete(url);
}

int URLFile::Read(char * file)
{
  int f;
  unsigned int err;
  FSTATS fstat;
  if (GetFileStats(file, &fstat, &err)!=-1)
  {
    if((f=fopen(file, A_ReadOnly+A_BIN, P_READ, &err))!=-1)
    {
      if (url = new char[fstat.size+1])
      {
        url[fread(f, url, fstat.size, &err)]=0;
        fclose(f, &err);
        return 1;
      }
      fclose(f, &err);
    }
  }
  return 0;
}

int URLFile::Write(char * file)
{
  int hFile;
  unsigned int io_error;
  if ((hFile=fopen(file, A_WriteOnly + A_Truncate + A_Create + A_BIN, P_WRITE, &io_error))!=-1)
  {
    fwrite(hFile, url, strlen(url), &io_error);
    fclose(hFile, &io_error);
    return 1;
  }
  return 0;
}
