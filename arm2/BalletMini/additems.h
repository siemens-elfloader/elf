#ifndef _ADDITEMS_H_
#define _ADDITEMS_H_

#include "view.h"

void AddNewStyle(VIEWDATA *vd);

void AddBeginRef(VIEWDATA *vd);

void AddBeginRefZ(VIEWDATA *vd);

void AddEndRef(VIEWDATA *vd);

void AddTextItem(VIEWDATA *vd, const char *text, int len);

void AddBrItem(VIEWDATA *vd);

void AddPItem(VIEWDATA *vd);

void AddPictureItemIndex(VIEWDATA *vd, int index);

void AddPictureItem(VIEWDATA *d, void *picture);

void AddPictureItemRGBA(VIEWDATA *vd, void *picture, int width, int height);

void AddPictureItemFrame(VIEWDATA *vd,int width,int height);

void AddPictureItemHr(VIEWDATA *vd);

void AddRadioButton(VIEWDATA *vd, int checked);

void AddCheckBoxItem(VIEWDATA *vd, int checked);

void AddInputItem(VIEWDATA *vd, unsigned int pos);

void AddButtonItem(VIEWDATA *vd, const char *text, int len);

void AddDropDownList(VIEWDATA *vd);

void AddToRefCache(VIEWDATA *vd);

#endif /* _ADDITEMS_H_ */
