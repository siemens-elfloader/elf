/*
 ===============================
 菜单
 ===============================
 */

#include "..\..\inc\swilib.h"
#include "..\inc\main.h"
#include "..\inc\buff.h"
#include "..\inc\menu.h"
#include "..\inc\bookmark.h"
#include "..\inc\file.h"
#include "..\inc\bookmark.h"
#include "..\inc\edit.h"
#include "..\inc\code.h"
#include "..\inc\input.h"
#include "..\inc\search.h"
#include "..\inc\history.h"

//---------软键----------
int menusoftkeys[] = { 0, 1, 2 };
SOFTKEY_DESC menu_sk[] = { { 0x0018, 0x0000, (int) "选择" }, { 0x0001,
		0x0000, (int) "返回" }, { 0x003D, 0x0000, (int) LGP_DOIT_PIC } };

SOFTKEYSTAB menu_skt = { menu_sk, 0 };

void mainmenu_open(void) {
	GeneralFuncF1(1);
	open_select_file_gui(1);
}

void mainmenu_quit(void) {
	GeneralFuncF1(1);
	Quit_Required = 1;
}

void mainmenu_search(void) {
	GeneralFuncF1(1);
	showSearch();
}

void mainmenu_goto(void) {
	GeneralFuncF1(1);
	create_menu_goto();
}

void mainmenu_edit(void) {
	GeneralFuncF1(1);
	launchEditor();
}

IPC_REQ mss_ipc=
{
  "MySMSYS",
  "MySMSYS",
  NULL
};

#define SMSYS_IPC_SEND_WS 0x88 //基于ws新建短信,data=ws

void mainmenu_sendsms(void)
{
  GeneralFuncF1(1);
  if (!buffed) return;
  WSHDR *sbw = AllocWS(256);
  int len;
  if(!(len = maxVisualSize - rowindex[curvisrow].start)) return;
  if (len > 256) len = 256;
  str2ws_unicode(sbw, readBuffer + rowindex[curvisrow].start, len);
  LockSched();
  mss_ipc.data=sbw;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_SEND_WS,&mss_ipc);
  UnlockSched();
  
  //ShowMSG(1, (int)"to do");
}

void mainmenu_history(void)
{
  GeneralFuncF1(1);
  CreateHistoryMenu();
}

void mainmenu_set(void) {
	WSHDR *ws = AllocWS(150);
	char *t = malloc(128);
	strcpy(t, apppath);
	strcat(t, "SieTxtView.bcfg");
	wsprintf(ws, "%s", t);
	ExecuteFile(ws, 0, 0);
	mfree(t);
	FreeWS(ws);
}

void mainmenu_about(void) {
	ShowMSG(1, (int)"Siemens Text Viewer v0.4\nby HanikLZ\n2007");
}

const void *mainmenu_HNDLS[9] =
{ 
  (void *)mainmenu_open,
  (void *)mainmenu_history,
  (void *)mainmenu_search,
  (void *)mainmenu_goto,
  (void *)mainmenu_edit,
  (void *)mainmenu_sendsms,
  (void *)mainmenu_set,
  (void *)mainmenu_about,
  (void *)mainmenu_quit
};

const MENUITEM_DESC mainmenu_ITEMS[9] =
{ 
  { NULL, (int)"打开...", LGP_NULL, 0, NULL,MENU_FLAG3, MENU_FLAG2 },
  { NULL, (int)"历史...", LGP_NULL, 0, NULL,MENU_FLAG3, MENU_FLAG2 },
  { NULL, (int)"搜索...", LGP_NULL, 0, NULL,MENU_FLAG3, MENU_FLAG2 },
  { NULL, (int)"转到...", LGP_NULL, 0, NULL,MENU_FLAG3, MENU_FLAG2 },
  { NULL, (int)"编辑...", LGP_NULL, 0, NULL,MENU_FLAG3, MENU_FLAG2 },
  { NULL, (int)"发送短信...", LGP_NULL, 0,NULL, MENU_FLAG3, MENU_FLAG2 },
  { NULL, (int)"设置...", LGP_NULL, 0,NULL, MENU_FLAG3, MENU_FLAG2 },
  { NULL, (int)"关于", LGP_NULL, 0,NULL, MENU_FLAG3, MENU_FLAG2 },
  { NULL, (int)"退出", LGP_NULL, 0, NULL,MENU_FLAG3, MENU_FLAG2 }
};

HEADER_DESC mainmenu_HDR = { 0, 0, 0, 0, 0 //icon
		, (int)"Main Menu", LGP_NULL };

MENU_DESC mainmenu_STRUCT = { 8, NULL, NULL, NULL, menusoftkeys, &menu_skt, 0,
		0, mainmenu_ITEMS, (MENUPROCS_DESC const*) mainmenu_HNDLS,
				sizeof(mainmenu_HNDLS) / sizeof(void *) };

int create_menu_main(void) {
	patch_header(&mainmenu_HDR);
	return CreateMenu(0, 0, &mainmenu_STRUCT, &mainmenu_HDR, 0, 9, 0, 0);
}

void gotomenu_start(void) {
	GeneralFuncF1(1);
	gotoTxtStart();
}

void gotomenu_readed(void) {
	GeneralFuncF1(1);
	if (blhead) gotoBMKNode(blhead->next);
}

void gotomenu_end(void) {
	GeneralFuncF1(1);
	gotoTxtEnd();
}

void gotomenu_checkpoint(void) {
	GeneralFuncF1(1);
	gotoBMKNode(bltop);
}

void gotomenu_percentage(void) {
	GeneralFuncF1(1);
	launchInput(NULL, 3, 2, gotoPercentage);
}

void gotomenu_bookmark(void) {
	GeneralFuncF1(1);
	create_menu_bookmark();
}

void *gotomenu_HNDLS[6] = { (void *)gotomenu_start, (void *)gotomenu_end,
		(void *)gotomenu_readed, (void *)gotomenu_checkpoint, 
		(void *)gotomenu_percentage, 
		(void *)gotomenu_bookmark };

MENUITEM_DESC gotomenu_ITEMS[6] = { { NULL, (int)"开头", LGP_NULL, 0, NULL,
		MENU_FLAG3, MENU_FLAG2 }, { NULL, (int)"结尾", LGP_NULL, 0, NULL,
		MENU_FLAG3, MENU_FLAG2 }, { NULL, (int)"上一次", LGP_NULL, 0, NULL,
		MENU_FLAG3, MENU_FLAG2 }, { NULL, (int)"记录点", LGP_NULL, 0, NULL,
		MENU_FLAG3, MENU_FLAG2 }, { NULL, (int)"百分之...", LGP_NULL, 0, NULL,
		MENU_FLAG3, MENU_FLAG2 }, { NULL, (int)"书签...", LGP_NULL, 0,
		NULL, MENU_FLAG3, MENU_FLAG2 } };

HEADER_DESC gotomenu_HDR = { 0, 0, 0, 0, 0 //icon
		, (int)"转到...", LGP_NULL };

MENU_DESC gotomenu_STRUCT = { 8, NULL, NULL, NULL, menusoftkeys, &menu_skt, 0,
		0, gotomenu_ITEMS, (MENUPROCS_DESC const*) gotomenu_HNDLS,
				sizeof(gotomenu_HNDLS) / sizeof(void *) };

int create_menu_goto(void) {
	patch_header(&gotomenu_HDR);
	return CreateMenu(0, 0, &gotomenu_STRUCT, &gotomenu_HDR, 0, 6, 0, 0);
}
