#include "..\..\inc\swilib.h"
#include "..\inc\main.h"
#include "..\inc\buff.h"
#include "..\inc\code.h"
#include "..\inc\file.h"
#include "..\inc\menu.h"
#include "..\inc\bookmark.h"
#include "..\inc\conf_loader.h"

BMKLIST *blhead= NULL;
BMKLIST *bltop= NULL;
char bmkfile[128];
int bmkchanged = 0;

void Free_BLIST(void) { //清空列表
	BMKLIST *bl;
	while (blhead) {
		bl = blhead;
		blhead = blhead->next;
		FreeWS(bl->preview);
		mfree(bl);
	}
	bltop = NULL;
}

BMKLIST *FindBLISTtByN(BMKLIST *bmklist, int n) {
	BMKLIST *bl = bmklist;
	int i = 0;
	while (bl && (i < n)) {
		bl = bl->next;
		i++;
	}
	return bl;
}

int readAddrInt(void) { //读取书签
	unsigned int err;
	char *nm=GetFileName(procfile);
	strcpy(bmkfile, apppath);
	strcat(bmkfile, "Bookmarks\\");
	if(!isdir(bmkfile, &err))
	  mkdir(bmkfile, &err);
	strcat(bmkfile, nm);
	strcat(bmkfile, ".bmk");
	Free_BLIST();
	int bmkfd = fopen(bmkfile, A_BIN + A_ReadOnly, P_READ, &err);
	if (bmkfd < 0) return 0;
	char* tb = malloc(8);
	BMKLIST *bl;
	bltop = bl = malloc(sizeof(BMKLIST));
	bltop->next = NULL;
	while (fread(bmkfd, tb, 8, &err) == 8) {
		bl->next = malloc(sizeof(BMKLIST));
		bl->next->address = (tb[0] << 24) | tb[1] << 16 | tb[2] << 8 | tb[3];
		bl->next->offset = (tb[4] << 24) | tb[5] << 16 | tb[6] << 8 | tb[7];
		bl->next->preview = NULL; //置为空，显示的时候才读取其中的内容
		bl = bl->next;
		bl->next = NULL;
	}
	bl = bltop;
	bltop = bltop->next;
	blhead = bltop;
	mfree(bl);
	mfree(tb);
	fclose(bmkfd, &err);
	return 1;
}

void writeBMKNode(unsigned int bmkfd, char* tb, BMKLIST *bl) {
	tb[0] = (bl->address >> 24) & 0xff;
	tb[1] = (bl->address >> 16) & 0xff;
	tb[2] = (bl->address >> 8) & 0xff;
	tb[3] = (bl->address) & 0xff;
	tb[4] = (bl->offset >> 24) & 0xff;
	tb[5] = (bl->offset >> 16) & 0xff;
	tb[6] = (bl->offset >> 8) & 0xff;
	tb[7] = (bl->offset) & 0xff;
	fwrite(bmkfd, tb, 8, &err);
}

int writeAddrInt(BMKLIST* bmklist) {
	int bmkfd = fopen(bmkfile, A_BIN + A_WriteOnly + A_Create + A_Truncate, P_WRITE, &err);
	if (bmkfd < 0) return 0;
	BMKLIST *bl= bmklist;
	char* tb = malloc(8);
	while (bl) {
		writeBMKNode(bmkfd, tb, bl);
		bl = bl->next;
	}
	mfree(tb);
	fclose(bmkfd, &err);
	return 1;
}

void writeSysBMKInt(void) {
	int bmkfd = fopen(bmkfile, A_BIN + A_WriteOnly + A_Create, P_WRITE, &err);
	if (bmkfd < 0) return;
	BMKLIST *bl= blhead;
	char* tb = malloc(8);
	bl->address = readStartAdr;
	bl->offset = rowindex[curvisrow].start;
	writeBMKNode(bmkfd, tb, bl);
	bl = bl->next;
	if (readStartAdr > bl->address || rowindex[curvisrow].start > bl->offset) {
		bl->address = readStartAdr;
		bl->offset = rowindex[curvisrow].start;
	}
	writeBMKNode(bmkfd, tb, bl);
	bl = bl->next;
	writeBMKNode(bmkfd, tb, bl);
	mfree(tb);
	fclose(bmkfd, &err);
}

void initBMKList(int start, int row) {
	int size = sizeof(BMKLIST);
	BMKLIST* bl = malloc(size);
	bl->address = start;
	bl->offset = row;
	bl->preview = NULL;
	bl->next = NULL;
	if (!blhead) {
		blhead = malloc(size);
		memcpy(blhead, bl, size);
	}
	bltop = blhead;
	for (int i = 0; i < 2; i++) {
		if (!(bltop->next)) {
			bltop->next = malloc(size);
			memcpy(bltop->next, bl, size);
		}
		bltop = bltop->next;
	}
	mfree(bl);
}

int add2bmk(int start, int row) {
	BMKLIST* bl = bltop->next;
	while (bl) {
		if (start == bl->address && row == bl->offset) return 0;
		bl = bl->next;
	}
	bl = malloc(sizeof(BMKLIST));
	bl->address = start;
	bl->offset = row;
	bl->preview = AllocWS(20);
	int len = 20;
	if (row + len > maxVisualSize - 1) len = maxVisualSize - row - 1;
	str2ws_unicode(bl->preview, readBuffer + row, len);
	bl->next = bltop->next;
	bltop->next = bl;
	return 1;
}

int deletebmk(int n) {
	BMKLIST* bl = bltop;
	if (--n >= 0)
		bl = FindBLISTtByN(bltop->next, n);
	if (bl && bl->next) {
		BMKLIST* del = bl->next;
		bl->next = del->next;
		FreeWS(del->preview);
		mfree(del);
		return 1;
	} else
		return 0;
}

int getBMKMount(BMKLIST* bmklist) {
	int i = 0;
	BMKLIST *bl = bmklist;
	while (bl) {
		i++;
		bl = bl->next;
	}
	return i;
}

int gotoBMKNode(BMKLIST* bl) {
	if (!bl) return 0;
	curvisrow = bl->offset;
	if (readStartAdr != bl->address) {
		initBuffer();
		readStartAdr = bl->address;
		loadBlock();
		createRowIndex();
	}
	for (int i = 0; i < visualRows; i++) {
		if (rowindex[i].end > curvisrow) {
			curvisrow = i;
			break;
		}
	}
	return 1;
}

int bmklist_menu_onkey(void *data, GUI_MSG *msg) {
	int keycode = msg->keys;
	int i = GetCurMenuItem(data);
	BMKLIST* bl;
	bl = FindBLISTtByN(bltop->next, i);
	if (keycode == 0x3D || keycode == 0x18) {
		if (gotoBMKNode(bl)) {
			GeneralFuncF1(1);
			return 1;
		}
	} else if (keycode == 0x14) { //'*' 添加
		if (add2bmk(readStartAdr, rowindex[curvisrow].start)) {
			bmkchanged = 1;
			Menu_SetItemCountDyn(data, getBMKMount(bltop->next));
		}
	} else if (keycode == 0x15) { //'#' 删除
		if (deletebmk(i)) {
			bmkchanged = 1;
			Menu_SetItemCountDyn(data, getBMKMount(bltop->next));
			SetCursorToMenuItem(data, i - 1 > 0 ? i - 1 : 0);
		}
	}
	return 0;
}

void bmklist_menu_ghook(void *data, int cmd) {
	if (cmd == 3 && bmkchanged && acbm != 2) {
		writeAddrInt(blhead);
		bmkchanged = 0;
	}
}

void bmklist_menu_iconhndl(void *data, int curitem, void *unk) {
	BMKLIST *t;
	WSHDR *ws;
	void *item = AllocMenuItem(data);
	t = FindBLISTtByN(bltop->next, curitem);
	if (t) { 
		if (!t->preview) {
			t->preview = getOffsetWS(t->address, t->offset, 10);
		}
		ws = AllocMenuWS(data, t->preview->wsbody[0]);
		wstrcpy(ws, t->preview);
	} else {
		ws = AllocMenuWS(data, 10);
		wsprintf(ws, "lable %d", curitem);
	}
	//SetMenuItemIconArray(data, item, S_ICONS);
	SetMenuItemText(data, item, ws, curitem);
	SetMenuItemIcon(data, curitem, 0);
}

HEADER_DESC bmklist_HDR = { 0, 0, 0, 0, 0, (int)"书签", LGP_NULL };

MENU_DESC bmklist_STRUCT = { 8, bmklist_menu_onkey, bmklist_menu_ghook, NULL,
		menusoftkeys, &menu_skt, 1 + 0x10, bmklist_menu_iconhndl, NULL, //Items
		NULL, //Procs
		0 //n
		};

int create_menu_bookmark(void) {
	initBMKList(readStartAdr, rowindex[curvisrow].start);
	patch_header(&bmklist_HDR);
	return CreateMenu(0, 0, &bmklist_STRUCT, &bmklist_HDR, 0,
			getBMKMount(bltop->next), 0, 0);
}
