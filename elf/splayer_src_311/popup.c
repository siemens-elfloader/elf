#include "../inc/swilib.h"
#include "main.h"

unsigned short x2=0;
unsigned short y2=0;
unsigned short x=0;
unsigned short y=0;
unsigned short g=1;

char Cor[4];

GBSTMR show;


void ShowPPP(void) {}

void PlayPopup(unsigned short xp, unsigned short yp, unsigned short xp2, unsigned short yp2, const char *Color)
{
  g=0;
  strcpy(Cor,Color);
  x=xp;
  y=yp;
  unsigned short xm2=xp2/4;
  unsigned short ym2=yp2/4;
  for(unsigned short i=0;i<3;i++)
  {
    x2+=xm2;
    y2+=ym2;
    REDRAW();
    GBS_StartTimerProc(&show,200,ShowPPP);
    GBS_DelTimer(&show);
  }
  x2=xp2;
  y2=yp2;
  REDRAW();
  GBS_StartTimerProc(&show,632,ShowPPP);
  GBS_DelTimer(&show);
  g=1;
}

void CrPopup()
{
 // if(g)return;
  unsigned short ry=y+5;
  unsigned short rx=x+23;
 // DrawLine(x, y+3, x+4, y+3, 0, Color);
  // DrawLine(x+15, y+3, x2, y+3, 0, Color);
 // DrawLine(x, y, x2, y, 1, Color);
 /* DrawLine(x2, y+3, x2, y2, 0, Color);
  DrawLine(x2, y2, x, y2, 0, Color);
  DrawLine(x, y2, x, y+3, 0, Color);*/
  
  DrawLine(x+8, ry, x+10, y, 0, Cor);
  DrawLine(x+10, y, x+20, y, 0, Cor);
  DrawLine(x+20, y, rx, ry, 0, Cor);
  
  DrawRoundedFrame(x,ry,x2,y2,4,4,0,Cor,0);
  
}
