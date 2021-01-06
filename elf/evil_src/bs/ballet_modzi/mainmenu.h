#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#define wslen(ws) ws->wsbody[0]

int CreateMainMenu(VIEWDATA *vd);
int CreateInputUrl();
//int CreateBookmarksMenu();
int CreateBookmarksMenu(char *dir);

#endif /* _MAIN_MENU_H_ */
