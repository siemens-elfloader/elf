#ifndef _MAIN_H_
#define _MAIN_H_

void FreeViewUrl(void);
char *globalstr(const char *s);
int ReadUrlFile(char *url_file);

typedef struct
{
  CSM_RAM csm;
  int view_id;
  int goto_url;
  int sel_bmk;
  int main_menu_id;
}MAIN_CSM;

enum I_INPUTMODE {MODE_FILE, MODE_URL, MODE_BOOKMARKS, MODE_NONE};

void FreeRawText(VIEWDATA *vd);

typedef struct
{
  GUI gui;
  VIEWDATA *vd;
  int cached;
  WSHDR *ws1;
  WSHDR *ws2;
}VIEW_GUI;

#endif /* _MAIN_H_ */
