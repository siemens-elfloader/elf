#include "../../inc/swilib.h"
#include "strings.h"


char *MakeGlobalString(const char *first, int breakchar, const char *last)
{
  int l;
  char *p;
  p=malloc((l=strlen(first))+strlen(last)+2);
  strcpy(p,first);
  if (breakchar)
    p[l++]=breakchar;
  strcpy(p+l,last);
  return p;
}

int strcmp_nocase(const char *s, const char *d)
{
  int cs;
  int ds;
  do
  {
    cs=*s++;
    if (cs&0x40) cs&=0xDF;
    ds=*d++;
    if (ds&0x40) ds&=0xDF;
    cs-=ds;
    if (cs) break;
  }
  while(ds);
  return(cs);
}


unsigned int char16to8(unsigned int c)
{
  if (c<128) return(c);
  c&=0xFF;
  if (c<32) return(' ');
  return(c);
}


unsigned short * wstrstr(unsigned short *ws, char *str, int *wslen, int len)
{
  char *s;
  unsigned short *w;
  int l;
 
  while(*wslen >= len)
  {
    s = str;
    w = ws;
    l = len;
    for(; (char16to8(*w) == *s) && l; w++, s++, l--);     
    if(!l) return ws;
    ws++;
    (*wslen)--;
  }
  return 0;
  
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strncmp_nocase(const char *s1,const char *s2,unsigned int n)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
  return(i);
}



