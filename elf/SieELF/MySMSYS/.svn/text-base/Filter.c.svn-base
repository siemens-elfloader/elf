#include "..\inc\swilib.h"
#include "config_data.h"
#include "sms_dat.h"
#include "Filter.h"

#define FILTER_ALL	0
#define FILTER_NEW	1
#define FILTER_DAT	2
#define FILTER_FILE	3
#define FILTER_NUM	4
#define FILTER_STR	5

SMS_DATA *GetDatFileByNSD(int n, int isfile)
{
  int i=0;
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(sdl->isfile==isfile)
    {
      if(i==n) return sdl;
      i++;
    }
    sdl=sdl->next;
  }
  return 0;
}

int GetDatFileSDLCount(int isfile)
{
  int i=0;
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(sdl->isfile==isfile)
    {
      i++;
    }
    sdl=sdl->next;
  }
  return i;
}

SMS_DATA *GetNumSD(int n, const char *num)
{
  int i=0, len, len2, lx;
  const char *p2, *pt;
  const char *p=num;
  SMS_DATA *sdl=sdltop;
  if(!p) return 0;
  if(*p=='+') p++;
  len=strlen(p);
  while(sdl)
  {
    len2=strlen((p2=sdl->Number));
    if(len2>len)
    {
      if((lx=len2-len)>3)
      {
	sdl=sdl->next;
	continue;
      }
      p2+=lx;
    }
    else
    {
      if((lx=len-len2)>3)
      {
	sdl=sdl->next;
	continue;
      }
      pt=p+lx;
    }
    if(!strcmp(pt, p2))
    {
      if(i==n) return sdl;
      i++;
    }
    sdl=sdl->next;
  }
  return 0;
}

int GetNumSDCount(const char *num)
{
  int i=0, len, len2, lx;
  const char *p2, *pt;
  const char *p=num;
  SMS_DATA *sdl=sdltop;
  if(!p) return 0;
  if(*p=='+') p++;
  len=strlen(p);
  while(sdl)
  {
    len2=strlen((p2=sdl->Number));
    if(len2>len)
    {
      if((lx=len2-len)>3)
      {
	sdl=sdl->next;
	continue;
      }
      p2+=lx;
    }
    else
    {
      if((lx=len-len2)>3)
      {
	sdl=sdl->next;
	continue;
      }
      pt=p+lx;
    }
    if(!strcmp(pt, p2))
    {
      i++;
    }
    sdl=sdl->next;
  }
  return i;
}

int w_charcmp_nocase(unsigned short *t1, unsigned short *t2, int len)
{
  int pos=0, cs, ds;
  while(pos<len)
  {
    cs=t1[pos];
    ds=t2[pos];
    if(cs<0x1000 && ds<0x1000)
    {
      extern int char16to8(int c);
      cs=char16to8(cs);
      ds=char16to8(ds);
      if(cs&0x40) cs&=0xDF;
      if(ds&0x40) ds&=0xDF;
    }
    cs-=ds;
    if(cs) return cs;
    pos++;
  }
  return 0;
}

unsigned short *wstrstr(WSHDR *wstr, WSHDR *ws)
{
  int len, len2, i=0;
  unsigned short *p, *p2;
  if(!wstr || !ws || !(len=ws->wsbody[0])) return 0;
  if((len2=wstr->wsbody[0])<len) return 0;
  p=ws->wsbody+1;
  p2=wstr->wsbody+1;
  while(len2-i>=len)
  {
    if(!w_charcmp_nocase(p, p2+i, len))
      return (p2+i);
    i++;
  }
  return 0;
}

SMS_DATA *GetStrSD(int n, const char *utf8_str)
{
  int i=0;
  WSHDR *ws, wsn;
  unsigned short wsb[64];
  ws=CreateLocalWS(&wsn, wsb, 64);
  utf8_2ws(ws, utf8_str, 64);
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(wstrstr(sdl->SMS_TEXT, ws))
    {
      if(i==n) return sdl;
      i++;
    }
    sdl=sdl->next;
  }
  return 0;
}

int GetStrSDCount(const char *utf8_str)
{
  int i=0;
  WSHDR *ws, wsn;
  unsigned short wsb[64];
  ws=CreateLocalWS(&wsn, wsb, 64);
  utf8_2ws(ws, utf8_str, 64);
  SMS_DATA *sdl=sdltop;
  while(sdl)
  {
    if(wstrstr(sdl->SMS_TEXT, ws))
      i++;
    sdl=sdl->next;
  }
  return i;
}

SMS_DATA *FilterFindSDL(int n)
{
  //GetCPUClock();
  switch(CFG_FILTEROP)
  {
  case FILTER_ALL:
    return (getSMSDataByType(n, 0));
  case FILTER_NEW:
    return (getSMSDataByType(n, TYPE_IN_N));
  case FILTER_DAT:
    return (GetDatFileByNSD(n, 0));
  case FILTER_FILE:
    return (GetDatFileByNSD(n, 1));
  case FILTER_NUM:
    return (GetNumSD(n, CFG_STRORNUM));
  case FILTER_STR:
    return (GetStrSD(n, CFG_STRORNUM));
  default:
    return 0;
  }
}

int FilterGetCountSDL(void)
{
  //GetCPUClock();
  switch(CFG_FILTEROP)
  {
  case FILTER_ALL:
    return (getCountByType(0));
  case FILTER_NEW:
    return (getCountByType(TYPE_IN_N));
  case FILTER_DAT:
    return (GetDatFileSDLCount(0));
  case FILTER_FILE:
    return (GetDatFileSDLCount(1));
  case FILTER_NUM:
    return (GetNumSDCount(CFG_STRORNUM));
  case FILTER_STR:
    return (GetStrSDCount(CFG_STRORNUM));
  default:
    return 0;
  }
}

SMS_DATA *GetNextNumSDL(SMS_DATA *sdl, const char *num)
{
  if(!sdl) return 0;
  int len, len2, lx;
  const char *p2, *pt;
  const char *p=num;
  if(!p) return 0;
  if(*p=='+') p++;
  len=strlen(p);
  sdl=sdl->next;
  while(sdl)
  {
    len2=strlen((p2=sdl->Number));
    if(len2>len)
    {
      if((lx=len2-len)>3)
      {
	sdl=sdl->next;
	continue;
      }
      p2+=lx;
    }
    else
    {
      if((lx=len-len2)>3)
      {
	sdl=sdl->next;
	continue;
      }
      pt=p+lx;
    }
    if(!strcmp(pt, p2))
      return sdl;
    sdl=sdl->next;
  }
  return 0;
}

SMS_DATA *GetNextStrSDL(SMS_DATA *sdl, const char *utf8_str)
{
  if(!sdl) return 0;
  WSHDR *ws, wsn;
  unsigned short wsb[64];
  ws=CreateLocalWS(&wsn, wsb, 64);
  utf8_2ws(ws, utf8_str, 64);
  sdl=sdl->next;
  while(sdl)
  {
    if(wstrstr(sdl->SMS_TEXT, ws))
    {
      return sdl;
    }
    sdl=sdl->next;
  }
  return 0;
}

SMS_DATA *FindNextFilterSDL(SMS_DATA *sdl)
{
  if(!sdl) return 0;
  //GetCPUClock();
  switch(CFG_FILTEROP)
  {
  case FILTER_ALL:
    return (FindNextByType(sdl, 0));
  case FILTER_NEW:
    return (FindNextByType(sdl, TYPE_IN_N));
  case FILTER_DAT:
    sdl=sdl->next;
    while(sdl)
    {
      if(!sdl->isfile) return sdl;
      sdl=sdl->next;
    }
    return 0;
  case FILTER_FILE:
    sdl=sdl->next;
    while(sdl)
    {
      if(sdl->isfile) return sdl;
      sdl=sdl->next;
    }
    return 0;
  case FILTER_NUM:
    return (GetNextNumSDL(sdl, CFG_STRORNUM));
  case FILTER_STR:
    return (GetNextStrSDL(sdl, CFG_STRORNUM));
  default:
    return 0;
  }
}


SMS_DATA *GetPrevNumSDL(SMS_DATA *sdl, const char *num)
{
  if(!sdl) return 0;
  int len, len2, lx;
  const char *p2, *pt;
  const char *p=num;
  if(!p) return 0;
  if(*p=='+') p++;
  len=strlen(p);
  sdl=sdl->prev;
  while(sdl)
  {
    len2=strlen((p2=sdl->Number));
    if(len2>len)
    {
      if((lx=len2-len)>3)
      {
	sdl=sdl->prev;
	continue;
      }
      p2+=lx;
    }
    else
    {
      if((lx=len-len2)>3)
      {
	sdl=sdl->prev;
	continue;
      }
      pt=p+lx;
    }
    if(!strcmp(pt, p2))
      return sdl;
    sdl=sdl->prev;
  }
  return 0;
}

SMS_DATA *GetPrevStrSDL(SMS_DATA *sdl, const char *utf8_str)
{
  if(!sdl) return 0;
  WSHDR *ws, wsn;
  unsigned short wsb[64];
  ws=CreateLocalWS(&wsn, wsb, 64);
  utf8_2ws(ws, utf8_str, 64);
  sdl=sdl->prev;
  while(sdl)
  {
    if(wstrstr(sdl->SMS_TEXT, ws))
      return sdl;
    sdl=sdl->prev;
  }
  return 0;
}

SMS_DATA *FindPrevFilterSDL(SMS_DATA *sdl)
{
  if(!sdl) return 0;
  //GetCPUClock();
  switch(CFG_FILTEROP)
  {
  case FILTER_ALL:
    return (FindPrevByType(sdl, 0));
  case FILTER_NEW:
    return (FindPrevByType(sdl, TYPE_IN_N));
  case FILTER_DAT:
    sdl=sdl->prev;
    while(sdl)
    {
      if(!sdl->isfile) return sdl;
      sdl=sdl->prev;
    }
    return 0;
  case FILTER_FILE:
    sdl=sdl->prev;
    while(sdl)
    {
      if(sdl->isfile) return sdl;
      sdl=sdl->prev;
    }
    return 0;
  case FILTER_NUM:
    return (GetPrevNumSDL(sdl, CFG_STRORNUM));
  case FILTER_STR:
    return (GetPrevStrSDL(sdl, CFG_STRORNUM));
  default:
    return 0;
  }
}

