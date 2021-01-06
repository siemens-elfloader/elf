#include "..\inc\swilib.h"

void main(WSHDR *ws1)
{
  //Патчим строку на предмет win1251 (c)Rst7
  int i=1;
  int c;
  while(i<=ws1->wsbody[0])
  {
    c=ws1->wsbody[i];
    if (c==0xA8) c=0x401;
    if (c==0xAA) c=0x404;
    if (c==0xAF) c=0x407;
    if (c==0xB8) c=0x451;
    if (c==0xBA) c=0x454;
    if (c==0xBF) c=0x457;
    if ((c>=0xC0)&&(c<0x100)) c+=0x350;
    ws1->wsbody[i++]=c;
  }
}














