#include "..\..\inc\swilib.h"
#include "..\inc\main.h"
#include "..\inc\buff.h"
#include "..\inc\code.h"
#include "..\inc\menu.h"
#include "..\inc\conf_loader.h"

/*
int WriteLog(char *text, unsigned int len) { //µ÷ÊÔ
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
/*
void drawWait(void) {
	WSHDR* tws = AllocWS(30);
	wsprintf(tws, "Writing, please wait...");
	int drawx = winx + ((winw - Get_WS_width(tws, statfont)) >> 1);
	int drawy = winy + ((winh - GetFontYSIZE(statfont)) >> 1);
	DrawRectangle(drawx - 2, drawy - 2, winx + winw - drawx + 2, winy + winh
			- drawy + 2, 0,
	//GetPaletteAdrByColorIndex(bgcolor),
			//GetPaletteAdrByColorIndex(bgcolor)
			statbgcolor, statbgcolor);

	DrawString(tws, drawx, drawy, winw, winh, statfont, 
	TEXT_ALIGNRIGHT, statfontcolor, statbgcolor
	//GetPaletteAdrByColorIndex(fontcolor),
	//GetPaletteAdrByColorIndex(bgcolor)
	);
	FreeWS(tws);
}*/
int inp_onkey(GUI *gui, GUI_MSG *msg) {

	EDITCONTROL ec;

	if (msg->gbsmsg->submess == RED_BUTTON) {
		return 1;
	}

	if (msg->gbsmsg->submess == GREEN_BUTTON) {
		return 1;
	}

	if (msg->keys == 0x18) {
		ExtractEditControl(gui, 1, &ec);
		WSHDR* sbw = ec.pWS;
		int len = sbw->wsbody[0];
		int len1 = rowindex[curvisrow].start;
		int len2 = maxVisualSize - len1 > 256 ? 256 : maxVisualSize - len1;
		char* tb = malloc(len << 1);
		char* tb1 = NULL;
		ws2str_unicode(tb, sbw, &len);
		buffed = 0;
		tb1 = malloc(maxVisualSize + len - len2);
		memcpy(tb1, readBuffer, len1);
		memcpy(tb1 + len1, tb, len);
		if (maxVisualSize - len1 - len2 > 0)
			memcpy(tb1 + len1 + len, readBuffer + len1 + len2, maxVisualSize
						- len1 - len2);
		maxVisualSize += len - len2;
		mfree(readBuffer);
		mfree(tb);
		readBuffer = tb1;
		
		saveBlock();
		readSize = LOAD_SIZE - (LOAD_SIZE >> 3);
		if (loadBlock()) createRowIndex();
		/*
		 ExtractEditControl(gui, 1, &ec);    
		 wstrcpy(editstr, ec.pWS);
		 patch_header(&menuhdr);
		 menu_gui_id = CreateMenu(0, 0, &tmenu, &menuhdr, 0, 4, editstr, 0);*/
		return 1;
		//return -1; //do redraw
	}
	return 0; //Do standart keys
	//1: close
}

void inp_ghook(GUI *gui, int cmd) {

	static SOFTKEY_DESC sk = { 0x0018, 0x0000, (int)"±£´æ" };

	//WSHDR *editstr = EDIT_GetUserPointer(gui);

	if (cmd == 2) {
		//Called after onCreate
	}

	if (cmd == 3) {
		//ÍË³ö
		//FreeWS(tmostr);    
	}
	if (cmd == 7) {
		SetSoftKey(gui, &sk, SET_SOFT_KEY_N);
	}
}

void inp_locret(void) {
}

INPUTDIA_DESC inp_desc = { 1, inp_onkey, inp_ghook, (void *)inp_locret, 0,
		&menu_skt, { 0, 22, 131, 153 }, 4, 100, 101, 0, 0, 0x40000000 };

HEADER_DESC inp_hdr = { 0, 0, 131, 21,/*icon*/NULL, (int)"±à¼­", LGP_NULL };

int launchEditor(void) {
	if (!buffed)
		return 0;
	void *ma = malloc_adr();
	void *eq;
	int len = maxVisualSize - rowindex[curvisrow].start;
	if (!len) return 0;
	EDITCONTROL ec;
	WSHDR *sbw, wsn;// = AllocWS(256);
	unsigned short wsb[256];
	sbw=CreateLocalWS(&wsn, wsb, 256);
	PrepareEditControl(&ec);
	eq = AllocEQueue(ma, mfree_adr());
	if (len > 256) len = 256; //512,256
	str2ws_unicode(sbw, readBuffer + rowindex[curvisrow].start, len);
	ConstructEditControl(&ec, 4, 0x40, sbw, 256);
	AddEditControlToEditQend(eq, &ec, ma);
	patch_header(&inp_hdr);
	patch_input(&inp_desc);
	return CreateInputTextDialog(&inp_desc, &inp_hdr, eq, 1, 0);
}
