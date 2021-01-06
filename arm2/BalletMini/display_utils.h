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
int ChangeMenuSelection(VIEWDATA *vd, REFCACHE *rf, unsigned int cur_pos_ref);
int CreateInputBox(VIEWDATA *vd, REFCACHE *rf, unsigned int cur_pos_ref);
void createTextView(WSHDR *ws);
int CreateFindBox(VIEWDATA *vd);
int ShowLink(char *link);
void FindStringOnPage(VIEWDATA *vd);

#endif /* _DISPLAY_UTILS_H_ */
