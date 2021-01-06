#ifndef _NAVIGATION_H_
  #define _NAVIGATION_H_

#include "IdleLinks.h"

TLabelData *GetLeftLink();
TLabelData *GetRightLink();
TLabelData *GetDownLink();
TLabelData *GetUpLink();
TLabelData *GetFirstLink();
TLabelData *PrepareCompareSourseForFindNextLink(int key);
int CheckNextLink(int key, TLabelData *SelectedLabel, TLabelData *PrepareLabel, TLabelData *LastNextLabel);
void FindNextLink(int key);

#endif
