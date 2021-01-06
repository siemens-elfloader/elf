#include "../include.h"

#include "draw.h"

void Redraw()
{
  #ifdef ELKA
  DisableIconBar(1);
  if(mode)timer=100;
  else timer=100;
  #else
    if(mode)timer=30;
  else timer=60;
#endif


  //GBS_StartTimerProc((void*)Redraw,timer,);
  DirectRedrawGUI();
}

void DrawInstall()
{

lgpInitLangPack();
search_cache();
Redraw();
 /* WSHDR *ws=AllocWS(256);
  DrawRoundedFrame(0,0,W,H,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
  switch(istate)
  {
  case 0:case 1:
    {
wsprintf(ws,"Проверка подключения %d",istate);
if(istate==0){istate=1;SUBPROC((void*)create_connect);}
    }
  break;
  case 2:wsprintf(ws,"Проверка и загрузка ресурсов");
  //lgpInitLangPack();
  break;
  }
//search_cache();

DrawString(ws,0,0,ScreenW()-1,Get_WS_width(ws,FONT),FONT,0,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));

GBS_StartTimerProc(&tmr,10,DrawInstall); 	*/
}
