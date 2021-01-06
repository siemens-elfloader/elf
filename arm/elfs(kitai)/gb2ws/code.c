
#include "..\inc\swilib.h"


#ifdef NEWSGOLD
#define CODEMAP_ADDR 0xA1568200  //-0xA157A24F
#else
#define CODEMAP_ADDR 0xA0FA0200
#endif


__thumb void ws2ascii(WSHDR *ws, char *s, int maxlen)
{
  unsigned short *codemap=(unsigned short *)(CODEMAP_ADDR+32004);
  int i,j=0;
  unsigned short temp;
  for(i=1; i<=ws->wsbody[0]; i++)
  {
    temp=ws->wsbody[i];
    if(temp < 256)
      s[j++] = (unsigned char)temp;
    else if(temp >= 0x4E00 && temp <= 0x9FA5)
    {
      s[j++] = (unsigned char)(codemap[temp-0x4E00]>>8);
      s[j++] = (unsigned char)((codemap[temp-0x4E00]<<8)>>8);
    }
    else
      s[j++] = '?';
    if(maxlen != 0 && j >= maxlen)
      break;
  }
  s[j] = 0;
}

__thumb void ascii2ws(WSHDR *ws, const char *s, int maxlen)
{
  unsigned short *codemap=(unsigned short *)CODEMAP_ADDR;
  char *p=(char *)s;
  unsigned char uc,uc2;
  ws->wsbody[0] = 0;
  while((uc=*p++) && (maxlen == 0 || p-s<=maxlen))
  {
    if(uc <= 128)
      wsAppendChar(ws,uc);
    else
    {
      uc2=*p++;
      if(uc2 < 128)
        wsAppendChar(ws, uc2);
      else
        wsAppendChar(ws, codemap[(uc-129)*127+(uc2-128)]);
    }
  }
}

#pragma diag_suppress=Pe177
__root static const int SWILIB_242_GB2WS @ "SWILIB_242_GB2WS" = (int)ascii2ws;
#pragma diag_default=Pe177

#pragma diag_suppress=Pe177
__root static const int SWILIB_243_WS2GB @ "SWILIB_243_WS2GB" = (int)ws2ascii;
#pragma diag_default=Pe177

