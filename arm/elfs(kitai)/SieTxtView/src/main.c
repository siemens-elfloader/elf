/*
 * Copyright (c) 2007, MDVSC
 * All rights reserved.
 *
 * 文件名称：main.c
 * 文件标识：无
 * 摘 要：程序的主界面等
 *
 * 当前版本：0.9
 * 作 者：H.Z.
 * 完成日期：2007年11月29日
 *
 */
#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
#include "..\inc\conf_loader.h"
#include "..\inc\buff.h"
#include "..\inc\code.h"
#include "..\inc\main.h"
#include "..\inc\menu.h"
#include "..\inc\file.h"
#include "..\inc\bookmark.h"
#include "..\inc\edit.h"
#include "..\inc\search.h"
#include "..\inc\input.h"
#include "..\inc\history.h"

int curvisrow, dvisrow, visrowsperpage;
//当前显示行/显示目标行偏移/每页显示最大行数

int Quit_Required = 0;
char apppath[128];
#define ROW_INDEX_SIZE 100
const int minus11 = - 11;
unsigned short maincsm_name_body[140];
volatile int GUIStarted = 0;
volatile int Terminate = 0;
volatile int Busy = 0;
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

int MsgBoxResult = - 1;
const RECT Canvas = { 0, 0, 0, 0 };

int maxrowindexsize;
ROW_INDEX* rowindex= NULL;
int rowindexlen;

int winx, winy, winh, winw;
char procfile[128];

int op_failed=0;
typedef struct {
	GUI gui;
//  WSHDR *ws1;
//  WSHDR *ws2;
//  int i1;
} MAIN_GUI;

typedef struct {
	CSM_RAM csm;
	int gui_id;
} MAIN_CSM;
/*
 int WriteLog(char *text, unsigned int len) { //调试
 if (!text)
 return 0;
 unsigned int ul;
 int f = fopen("4:\\test.log", A_BIN + A_ReadWrite + A_Create + A_Truncate,
 P_READ + P_WRITE, &ul);
 if (f != -1) {
 fwrite(f, text, len, &ul);
 fclose(f, &ul);
 return 1;
 }
 return 0;
 }*/

void createRowIndex(void) {

	mfree(rowindex);
	maxrowindexsize = ROW_INDEX_SIZE;
	rowindex = malloc(maxrowindexsize * sizeof(ROW_INDEX));
	int w = 0, bg = 0;
	int sw = - 1, et = 0;
	int c;
	rowindexlen = 0;
	rowindex[rowindexlen].start = et = visualOffset;
	rowindex[rowindexlen].end = 0;
	visualRows = 0;
	for (int i = visualOffset; i < maxVisualSize; i += 2) {
		if (i == visualSize)
			visualRows = rowindexlen;
		c = (readBuffer[i + 1] << 8) | readBuffer[i];
		if (c == '\r')
			continue;
		else if (c == '\n')
			et = i;
		else {
			if (sw < 0) {
				if ((c > 0x2f && c < 0x3a) || (c > 0x40 && c < 0x5b) || (c
						> 0x60 && c < 0x7b)) {
					sw = i;
					bg = (w == 0);
				}
			} else {
				if (!((c > 0x2f && c < 0x3a) || (c > 0x40 && c < 0x5b) || (c
						> 0x60 && c < 0x7b))) {
					sw = - 1;
				}
			}

			w += GetSymbolWidth(c, font);
			if (w < winw) {
				w += colsplit;
				continue;
			} else {
				// 横向超出屏幕了
				if (sw > 0 && !bg) {
					// 有英文置位标志
					i = et = sw;
				} else {
					et = i;
				}
				i -= 2;
			}
		}
		rowindex[rowindexlen++].end = et;
		et -= 2;
		w = 0;

		if (rowindexlen > maxrowindexsize - 1) {
			ROW_INDEX* s = malloc((maxrowindexsize + ROW_INDEX_SIZE)
					* sizeof(ROW_INDEX));
			memcpy(s, rowindex, rowindexlen * sizeof(ROW_INDEX));
			maxrowindexsize += ROW_INDEX_SIZE;
			mfree(rowindex);
			rowindex = s;
		}
		rowindex[rowindexlen].start = i + 2;
		rowindex[rowindexlen].end = 0;
		sw = - 1;
	}
	if (maxVisualSize == 0) return;
	if (!rowindex[rowindexlen].end)
		rowindex[rowindexlen].end = maxVisualSize;
	if (!visualRows)
		visualRows = rowindexlen;
	/*
	 char *s = malloc(100);
	 sprintf(s, "%d, %d", rowindex[rowindexlen].start, rowindex[rowindexlen].end);
	 ShowMSG(1, (int)s);
	 mfree(s);*/
}

void drawTextByDefaultFont(int row) {
	if (!rowindex || !buffed)
		return;
	WSHDR* tws = AllocWS(1);
	tws->wsbody[0] = 1;
	int dx = winx;
	int dy = winy;
	int drow = row + visrowsperpage;
	if (drow > rowindexlen)
		drow = rowindexlen;
	for (; row <= drow; row++) {
		for (int j = rowindex[row].start; j < rowindex[row].end; j += 2) {
			tws->wsbody[1] = (readBuffer[j + 1] << 8) | readBuffer[j];
			DrawString(tws, dx, dy, winw, winh, font, TEXT_ALIGNLEFT,
					fontcolor, bgcolor);
			dx += GetSymbolWidth(tws->wsbody[1], font) + colsplit;
		}
		/*
		 wsprintf(tws, "%d", rowindex[row].end);
		 DrawString(tws,
		 dx,
		 dy,
		 winw, winh,
		 font,
		 TEXT_ALIGNLEFT,
		 fontcolor,
		 bgcolor
		 );*/
		dx = 0;
		dy += GetFontYSIZE(font) + rowsplit;
	}
	FreeWS(tws);
}

float getPercetange(void) {
	float r = curvisrow, r1 = readStartAdr;
	r /= visualRows - visrowsperpage;
	r = r * readSize / fileSize;
	r1 /= fileSize;
	return r + r1;
}

void drawScrollBar(void) {
	DrawRectangle(winx + winw - 2, winy, winx + winw, winy + winh, 0,
	//GetPaletteAdrByColorIndex(bgcolor),
			//GetPaletteAdrByColorIndex(bgcolor)
			scrollbgcolor, scrollbgcolor);
	int indh = 10;
	int indy = getPercetange() * (winh - indh);
	DrawRectangle(winx + winw - 2, indy, winx + winw, indy + indh, 0,
	//GetPaletteAdrByColorIndex(bgcolor),
			//GetPaletteAdrByColorIndex(bgcolor)
			scrollindcolor, scrollindcolor);
}

void drawStatusBar(void) {
	DrawRectangle(winx, winy + winh - GetFontYSIZE(statfont)-1, winx + winw, winy
			+ winh, 0,
	//GetPaletteAdrByColorIndex(bgcolor),
			//GetPaletteAdrByColorIndex(bgcolor)
			statbgcolor, statbgcolor);
	WSHDR* ws = AllocWS(50);
	TDate d;
	TTime t;
	GetDateTime(&d, &t);

	int progress = (int)((getPercetange()) * 1000);
	if (progress > 1000)
		progress = 1000;
	/*
	 int progress = (r + r1) * 1000;
	 if (progress > 1000) progress = 1000;
	 
	 r = r * readSize / fileSize;
	 r1 /= fileSize;
	 int progress = (int)((r + r1) * 1000);
	 if (progress > 1000) progress = 1000;*/
	
	wsprintf(ws, "%d%d%d.%d%c %d%d:%d%d", progress / 1000 % 10, progress / 100
			% 10, progress /10 % 10, progress % 10, '%', t.hour / 10, t.hour
			% 10, t.min / 10, t.min % 10);
	//wsprintf(ws, "%d", progress);
	DrawString(ws, winx, winy + winh - GetFontYSIZE(statfont), winw-2, winh,
			statfont, 
			TEXT_ALIGNMIDDLE, statfontcolor, statbgcolor
	//GetPaletteAdrByColorIndex(fontcolor),
	//GetPaletteAdrByColorIndex(bgcolor)
	);
	FreeWS(ws);
}

void drawMain(void) {
#ifdef ELKA
	DisableIconBar(1);
#endif
	DrawRectangle(winx, winy, winw, winh, 0,
	//border-type 0=outline 1=dotted 2=inline
			bgcolor, bgcolor);
	drawTextByDefaultFont(curvisrow);
}

void pageChange(int dv) {
	if (!buffed)
		return;
	curvisrow += dv;
	/*
	 if (visualSize == maxVisualSize && curvisrow > rowindexlen - visrowsperpage) {
	 curvisrow = rowindexlen - visrowsperpage + 1;
	 if (curvisrow < 0) curvisrow = 0;
	 return;
	 }*/
	if (curvisrow < 0) {
		//载入上一块
		if (setPrevBlock()) {
			loadBlock();
			createRowIndex();
			curvisrow += visualRows;
		}
	}

	else if (curvisrow > visualRows) {
		//载入下一块
		curvisrow -= visualRows;
		if (setNextBlock()) {
			visualOffset = rowindex[visualRows].end - visualSize;
			loadBlock();
			createRowIndex();
		} else
			curvisrow += visualRows;
	}
	if (curvisrow > rowindexlen - visrowsperpage) {
		curvisrow = rowindexlen - visrowsperpage + 1;
	}
	if (curvisrow < 0)
		curvisrow = 0;
	if (acbm == 1)
		writeSysBMKInt();
}

void adjustText() {
	if (readOffset1 != 0)
		readOffset1 = 0;
	else
		readOffset1 = 1;
	loadBlock();
	createRowIndex();
}

void gotoTxtStart(void) {
	if (readStartAdr != 0) {
		initBuffer();
		loadBlock();
		createRowIndex();
	}
	curvisrow = 0;
}

void gotoTxtEnd(void) {
	if (readStartAdr < fileSize - LOAD_SIZE + (LOAD_SIZE >> 3)) {
		readSize = LOAD_SIZE - (LOAD_SIZE >> 3);
		readStartAdr = fileSize - readSize;
		if (readStartAdr < 0)
			readStartAdr = 0;
		loadBlock();
		visualOffset = 0;
		createRowIndex();
	}
	curvisrow = visualRows - visrowsperpage + 1;
	if (curvisrow < 0)
		curvisrow = 0;
}

void showSearch(void) {
	WSHDR* ws= NULL;
	if (searchstr) {
		ws = AllocWS(searchstrlen >> 1);
		str2ws_unicode(ws, searchstr, searchstrlen);
	}
	launchInput(ws, 0xff, 4, procSearchResult);
}

void onRedraw(MAIN_GUI* data) {
	drawMain();
	if (scroll)
		drawScrollBar();
	if (status)
		drawStatusBar();
}

void onCreate(MAIN_GUI* data, void *(*malloc_adr)(int)) {
	//  data->ws1=AllocWS(256);
	//  data->ws2=AllocWS(256);
	data->gui.state = 1;
}

void onClose(MAIN_GUI* data, void(*mfree_adr)(void*)) {
	//  FreeWS(data->ws1);
	//  FreeWS(data->ws2);
	data->gui.state = 0;
}

void onFocus(MAIN_GUI* data, void *(*malloc_adr)(int), void(*mfree_adr)(void*)) {
	data->gui.state = 2;
	if (Terminate && !Busy)
		GeneralFuncF1(1);
	else
		DirectRedrawGUI();
}

void onUnfocus(MAIN_GUI* data, void(*mfree_adr)(void*)) {
	if (data->gui.state != 2)
		return;
	data->gui.state = 1;
}

int onKey(MAIN_GUI* data, GUI_MSG* msg) {
	//int result = 0;
	if (msg->gbsmsg->msg == KEY_DOWN) {
		switch (msg->gbsmsg->submess) {
		case RED_BUTTON:
			Quit_Required = 1;
			/*result = 1;*/
			return 1;
		case GREEN_BUTTON:
			launchEditor();
			break;
		case ENTER_BUTTON:
			break;
		case LEFT_SOFT:
			create_menu_goto();
			break;
		case RIGHT_SOFT:
			create_menu_main();
			break;
		case '2':
		case UP_BUTTON:
			pageChange( - 1);
			REDRAW();
			break;
		case '1':
			searchBackward();
			break;
		case '3':
			if (!searchstr)
				showSearch();
			else {
				searchForward();
                                REDRAW();
                        }
			break;
		case '4':
		case LEFT_BUTTON:
		case VOL_UP_BUTTON:
			pageChange( -visrowsperpage);
			REDRAW();
			break;
		case '5':
			break;
		case '6':
		case RIGHT_BUTTON:
		case VOL_DOWN_BUTTON:
			pageChange(visrowsperpage);
			REDRAW();
			break;
		case '7':
			break;
		case '8':
		case DOWN_BUTTON:
			pageChange(1);
			REDRAW();
			break;
		case '9':
                      break;
		case '0':
                  if (!buffed)
				return 0;
			if (!bltop)
				initBMKList(readStartAdr, rowindex[curvisrow].start);
			else {
				bltop->address = readStartAdr;
				bltop->offset = rowindex[curvisrow].start;
				if (acbm != 2)
					writeSysBMKInt();
			}
                        ShowMSG(1, (int)"Check point!");
                        break;
		case '*':
			break;
		case '#':
			adjustText();
			REDRAW();
			break;
		default:
			break;
		}

	} else if (msg->gbsmsg->msg == LONG_PRESS) {
		switch (msg->gbsmsg->submess) {
		case RED_BUTTON:
			Quit_Required = 1;
			/*result = 1;*/
			break;
		case GREEN_BUTTON:

			break;
		case ENTER_BUTTON:
			break;
		case LEFT_SOFT:
			break;
		case RIGHT_SOFT:
			break;
		case '2':
		case UP_BUTTON:
			pageChange( - 1);
			REDRAW();
			break;
		case '1':
			gotoTxtStart();
			REDRAW();
			break;
		case '3':
			showSearch();
			REDRAW();
			break;
		case '4':
		case LEFT_BUTTON:
		case VOL_UP_BUTTON:
			pageChange( -visrowsperpage);
			REDRAW();
			break;
		case '5':
			break;
		case '6':
		case RIGHT_BUTTON:
		case VOL_DOWN_BUTTON:
			pageChange(visrowsperpage);
			REDRAW();
			break;
		case '7':
			gotoTxtEnd();
                        REDRAW();
			break;
		case '8':
		case DOWN_BUTTON:
			pageChange(1);
			REDRAW();
			break;
		case '9':
		case '0':
		case '*':
			break;
		case '#':
			break;
		default:
			break;
		}
	}
	return 0;
}

void saveProcFile(void) {
	char *t = malloc(128);
	strcpy(t, apppath);
	strcat(t, "history.ini");
	int
			f = fopen(t, A_BIN + A_WriteOnly + A_Create + A_Truncate, P_WRITE,
					&err);
	mfree(t);
	if (f < 0)
		return;
	fwrite(f, procfile, 128, &err);
	fclose(f, &err);
}

extern void kill_data(void* p, void(*func_p)(void*));

void Killer(void) {
	extern void* ELF_BEGIN;
	kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

int method8(void) {
	return 0;
}

int method9(void) {
	return 0;
}

const void* const gui_methods[11] = { (void*)onRedraw, //Redraw
		(void*)onCreate, //Create
		(void*)onClose, //Close
		(void*)onFocus, //Focus
		(void*)onUnfocus, //Unfocus
		(void*)onKey, //OnKey
		0, (void*)kill_data, //Destroy
		(void*)method8, (void*)method9, 0 };

void maincsm_oncreate(CSM_RAM* data) {
	MAIN_GUI* main_gui = malloc(sizeof(MAIN_GUI));
	MAIN_CSM* csm = (MAIN_CSM*)data;
	zeromem(main_gui, sizeof(MAIN_GUI));
	patch_rect((RECT*) &Canvas, 0, 0, ScreenW() - 1, ScreenH() - 1);
	main_gui->gui.canvas = (void*)(&Canvas);
	main_gui->gui.flag30 = 2;
	main_gui->gui.methods = (void*)gui_methods;
	main_gui->gui.item_ll.data_mfree = (void(*)(void*))mfree_adr();
	csm->csm.state = 0;
	csm->csm.unk1 = 0;
	csm->gui_id = CreateGUI(main_gui);
	MAINGUI_ID = csm->gui_id;
	if(op_failed) open_select_file_gui(1);
}

void maincsm_onclose(CSM_RAM* csm) {
	if (acbm != 2)
		writeSysBMKInt();
	fclose(fd, &err);
	Free_BLIST();
	freeSearchStr();
	mfree(readBuffer);
	//saveProcFile();
	SaveHistory();
	FreeHList();
	SUBPROC((void*)Killer);
}

int maincsm_onmessage(CSM_RAM* data, GBS_MSG* msg)
{
  MAIN_CSM* csm = (MAIN_CSM*)data;
  if (Quit_Required)
  {
    GeneralFuncF1(1);
  }
  if ((msg->msg == MSG_GUI_DESTROYED) && ((int)msg->data0 == csm->gui_id))
  {
    csm->csm.state = - 3;
  } 
  else
  {
    if (msg->msg == MSG_IDLETMR_EXPIRED)
    {
      ShowMSG(1, (int)"what?");
      return 0;
    }
    else
    {
      if (msg->msg == MSG_RECONFIGURE_REQ)
      {
	reloadContent();
	CutHList(maxhis);
      }
    }
  }
  return 1;
}

const struct {
	CSM_DESC maincsm;
	WSHDR maincsm_name;
} MAINCSM = { { maincsm_onmessage, maincsm_oncreate,
#ifdef NEWSGOLD
		0, 0, 0, 0,
#endif 
		maincsm_onclose, sizeof(MAIN_CSM), 1, &minus11 }

, { maincsm_name_body, NAMECSM_MAGIC1, NAMECSM_MAGIC2, 0x0, 139 } };

void updateCSMname(void) {
  if(!strlen(procfile))
    wsprintf((WSHDR*)(&MAINCSM.maincsm_name), "SieTxtView");
  else
  {
    //char* GetFileName(char* fname);
    char *p=GetFileName(procfile);
    WSHDR *ws, wsn;
    unsigned short wsb[128];
    ws=CreateLocalWS(&wsn, wsb, 128);
    str_2ws(ws, p, 128);
    wsprintf((WSHDR*)(&MAINCSM.maincsm_name), "STV:%w", ws);
  }
}

int setReadPostion(void) {
	initBuffer();
	readAddrInt();
	initBMKList(0, 0);
	readStartAdr = blhead->address;
	curvisrow = blhead->offset;
	loadBlock();
	createRowIndex();
	for (int i = 0; i < visualRows; i++) {
		if (rowindex[i].end > curvisrow) {
			curvisrow = i;
			break;
		}
	}
	visrowsperpage = udiv((GetFontYSIZE(font) + rowsplit), (winh + rowsplit));
	if (status)
		visrowsperpage--;
	return 1;
}

int reloadContent(void) {
	int charset_old = charset;
	int rowsplit_old = rowsplit;
	int colsplit_old = colsplit;
	int font_old = font;
	int status_old = status;
	InitConfig();
	if (charset != charset_old) {
		openFile(procfile);
		setReadPostion();
	} else {
		if (rowsplit_old != rowsplit)
			visrowsperpage = sdiv((GetFontYSIZE(font) + rowsplit), (winh
					+ rowsplit));
		if (colsplit_old != colsplit || font_old != font) {
			if (!rowindex)
				return 0;
			int c = rowindex[curvisrow].start;
			createRowIndex();
			for (curvisrow = 0; curvisrow < rowindexlen; curvisrow++) {
				if (rowindex[curvisrow].start > c)
					break;
			}
		}
		if (status_old != status) {
			if (status) visrowsperpage--; else visrowsperpage++;
		}
	}
	return 1;
}

/*
void setProcFile(void)
{
//  char *t = malloc(128);
  char path[128];
  strcpy(path, apppath);
  strcat(path, "history.ini");
  zeromem(procfile, sizeof(procfile));
  int f = fopen(path, A_BIN + A_ReadOnly, P_READ, &err);
//  mfree(t);
  if (f < 0)
  {
    return;
  }
  fread(f, procfile, 128, &err);
  fclose(f, &err);
}
*/

void gotoPercentage(WSHDR* ws) {
	if (!ws)
		return;
	curvisrow = 0;
	int c = 0;
	for (int i = 1; i <= ws->wsbody[0]; i++) {
		c = c * 10 + (ws->wsbody[i] - 0x30);
	}
	float f = c / 100.0;
	initBuffer();
	readStartAdr = fileSize * f;
	if (readStartAdr < 0)
		readStartAdr = 0;
	if (readStartAdr > fileSize - LOAD_SIZE + (LOAD_SIZE >> 3)) {
		readStartAdr = 0;
		gotoTxtEnd();
	} else {
		loadBlock();
		createRowIndex();
	}
}

int main(char* exename, char* fname) {
	//获取程序目录
	int c;
	char *s = exename, *t;
	while ((c = *s++)) {
		if (c == '\\' && *s != '\0')
			t = s;
	}
	if (t)
		*t = 0;
	strcpy(apppath, exename);
	InitConfig();
	winx = winy = 0;
	winw = ScreenW();
	winh = ScreenH();
	ReadHistory();
	if (!fname) SetProcfile();
		//setProcFile();
	else
		strcpy(procfile, fname);
	if (openFile(procfile)) {
		setReadPostion();
		AddPathToHList(procfile);
	}
	else op_failed=1;
	/*
	 char *s = malloc(50);
	 sprintf(s, "%d,%d\n%d,%d", visualSize, visualRows, visualOffset, fileSize);
	 ShowMSG(1, (int)s);
	 mfree(s);
	 */
	updateCSMname();
	char dummy[sizeof(MAIN_CSM)];
	MAINCSM_ID = CreateCSM(&MAINCSM.maincsm, dummy, 0);
	return 0;
}
