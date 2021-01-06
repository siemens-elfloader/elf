#ifndef _MAIN_H_
#define _MAIN_H_

void UpdateCSMname(char *url, int mode);
void FreeViewUrl(void);
char *globalstr(const char *s);
int ReadUrlFile(char *url_file);
void RunOtherByURL(const char *url, int other);

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
  unsigned int view_line;
  unsigned int pos_cur_ref;
  int isPositionDataPresent;
  WSHDR *ws1;
  WSHDR *ws2;
}VIEW_GUI;

#endif /* _MAIN_H_ */
