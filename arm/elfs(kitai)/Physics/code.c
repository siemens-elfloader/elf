
#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "code.h"


unsigned short *codemap;

void init_font_lib(void)
{
  int f;
  InitConfig(); 
  extern const char cnfont[];
  unsigned int ul;
  codemap = 0;
  f=fopen(cnfont,A_ReadOnly+A_BIN,P_READ,&ul);
  if(f != -1)
  {
    codemap=(unsigned short *)malloc(73808);
    if (fread(f,(void*)codemap,73808,&ul)!=73808)
    {
      mfree((void*)codemap);
      codemap = 0;
    }
    fclose(f,&ul);
  }
}

void free_font_lib(void)
{
  if (codemap)
  {
    mfree(codemap);
    codemap = 0;
  }
}

void ws2ascii(WSHDR *ws, char *s, int maxlen)
{
  int len=ws->wsbody[0];
  if(maxlen != 0 && len > maxlen)
    len = maxlen;
  if(codemap == 0)
  {
    ws_2str(ws, s, len);
    return;
  }
  int i,j=0;
  unsigned short temp;
  for(i=1; i<=len; i++)
  {
    temp=ws->wsbody[i];
    if(temp < 256)
      s[j++] = (unsigned char)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5)
    {
      s[j++] = (unsigned char)(codemap[temp-0x4E00+32004]>>8);
      s[j++] = (unsigned char)((codemap[temp-0x4E00+32004]<<8)>>8);
    }
    else
      s[j++] = '?';
  }
  s[j] = 0;
}

void ascii2ws(WSHDR *ws, const char *s, int maxlen)
{
  if(codemap == 0)
  {
    wsprintf(ws, "%t", s);
    return;
  }
  char *p=(char *)s;
  unsigned char uc,uc2;
  CutWSTR(ws,0);
  while((uc=*s++) && (maxlen == 0 || s-p<maxlen))
  {
    if(uc <= 128)
      wsAppendChar(ws,uc);
    else
    {
      uc2=*s++;
      if(uc2 < 128)
        wsAppendChar(ws, uc2);
      else
        wsAppendChar(ws, codemap[(uc-129)*127+(uc2-128)]);
    }
  }
}
