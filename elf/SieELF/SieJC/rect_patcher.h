#ifndef _RECT_PATCHER_H_
#define _RECT_PATCHER_H_

// ELKA Compatibility
#pragma inline
void patch_rect(RECT * rc, int x, int y, int x2, int y2)
{
  rc->x = x;
  rc->y = y;
  rc->x2 = x2;
  rc->y2 = y2;
}

#pragma inline
void patch_header(HEADER_DESC * head)
{
  head->rc.x = 0;
  head->rc.y = YDISP;
  head->rc.x2 = ScreenW()-1;
  head->rc.y2 = HeaderH()+YDISP;
}

#pragma inline
void patch_input(INPUTDIA_DESC * inp)
{
  inp->rc.x = 0;
  inp->rc.y = HeaderH() + 1 + YDISP;
  inp->rc.x2 = ScreenW() - 1;
  inp->rc.y2 = ScreenH() - SoftkeyH() - 1;
}

#endif /* _RECT_PATCHER_H_ */
