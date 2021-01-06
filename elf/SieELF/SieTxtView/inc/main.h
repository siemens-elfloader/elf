#ifndef _MAIN_H_
#define _MAIN_H_

typedef struct {
	int start;
	int end;
} ROW_INDEX;
extern ROW_INDEX* rowindex;
extern int Quit_Required;
extern int winx, winy, winh, winw;
extern int curvisrow, visrowsperpage;
extern char apppath[];

#pragma inline
void patch_header(HEADER_DESC* head) {
    head->rc.x = 0;
    head->rc.y = YDISP;
    head->rc.x2 = ScreenW() - 1;
    head->rc.y2 = HeaderH() + YDISP;
}

#pragma inline
void patch_input(INPUTDIA_DESC* inp) {
    inp->rc.x = 0;
    inp->rc.y = HeaderH() + 1+YDISP;
    inp->rc.x2 = ScreenW() - 1;
    inp->rc.y2 = ScreenH() - SoftkeyH() - 1;
}

#pragma inline
void patch_rect(RECT* rc, int x, int y, int x2, int y2) {
    rc->x = x;
    rc->y = y;
    rc->x2 = x2;
    rc->y2 = y2;
}
int setReadPostion(void);
int reloadContent(void);
void createRowIndex(void);
void gotoTxtStart(void);
void gotoTxtEnd(void);
void gotoPercentage(WSHDR* ws);
void showSearch(void);
void updateCSMname(void);
#endif
