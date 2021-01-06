#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#define wslen(ws) ws->wsbody[0]

int CreateMainMenu(VIEWDATA *vd);
int CreateInputUrl();
int CreateBookmarksMenu();
int CreateFindDialog(VIEWDATA *vd);

#endif /* _MAIN_MENU_H_ */
