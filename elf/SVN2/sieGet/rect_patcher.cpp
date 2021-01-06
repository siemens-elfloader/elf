#include "include.h"
#include "rect_patcher.h"

void patch_rect(RECT *rc, int x, int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

void patch_header(HEADER_DESC * head, int * icon, int lgp_id)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
  head->icon=icon;
  head->lgp_id=lgp_id;
}

void patch_header_small(HEADER_DESC * head)
{
  head->rc.x=3;
  head->rc.y=HeaderH()+YDISP;
  head->rc.x2=ScreenW()-6;
#ifdef ELKA
  head->rc.y2=HeaderH()*2+YDISP;
#else
  head->rc.y2=HeaderH()+0x11;
#endif
}

void patch_input(INPUTDIA_DESC * inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

