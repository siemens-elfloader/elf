#ifndef _DISPLAY_UTILS_H_
#define _DISPLAY_UTILS_H_

#include "view.h"

void scrollDown(VIEWDATA *vd, int amount);
void scrollUp(VIEWDATA *vd, int amount);
unsigned int SearchNextDisplayLine(VIEWDATA *vd, LINECACHE *p/*, unsigned int *max_h*/);
int LineDown(VIEWDATA *vd);
int LineUp(VIEWDATA *vd);
int RenderPage(VIEWDATA *vd, int do_draw);
REFCACHE *FindReferenceByBegin(VIEWDATA *vd, unsigned int rawpos);
REFCACHE *FindReferenceFirst(VIEWDATA *vd, unsigned int rawpos);
REFCACHE *FindReference(VIEWDATA *vd, unsigned int ref);
int FindReferenceById(VIEWDATA *vd, unsigned int id, int i);
int ChangeMenuSelection(VIEWDATA *vd, REFCACHE *rf);
int CreateInputBox(VIEWDATA *vd, REFCACHE *rf);
void createTextView(WSHDR *ws);
void input_box_onkey_options(USR_MENU_ITEM *item);

#endif /* _DISPLAY_UTILS_H_ */
