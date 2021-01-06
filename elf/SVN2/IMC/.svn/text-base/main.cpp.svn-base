#include "..\inc\swilib.h"

#define RUS  {*lang=7;}
#define LAT  {*lang=1;}
#define T9   {*t9=5;}
#define iTAP {*t9=2;}
#define hl   {*hilo=0;}
#define Hl   {*hilo=1;}
#define HL   {*hilo=3;}
#define DIG   {*lang=0xFF;*t9=0x0;*hilo=0xFF;}

__arm xredraw(void)
{
  PendedRedrawGUI();
}

int shift(char * item)
{

  if ((item[0x0E]==7) || (item[0x0E]==1))
  {
    switch(item[0x0B])
    {
    case 0: item[0x0B]=1;break;
    case 1: item[0x0B]=3;break;
    case 3: item[0x0B]=0;break;
    }
    xredraw();
  }
  return(0);
}

int main(void * item, char * t9, char * hilo, char * lang)
{
  unsigned int ti;
  ti=((*t9)<<16)|(((*hilo)&0xF0)<<8)|((*lang));
  switch (ti)
  {
  case 0x0000F0FF:{RUS T9 Hl }break;
  case 0x00050007:{RUS iTAP}break;
  case 0x00020007:{LAT iTAP}break;
  case 0x00020001:{DIG}break;
  default : {RUS T9} break;
  }
  return(1);
}













