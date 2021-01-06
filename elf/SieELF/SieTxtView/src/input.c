#include "..\..\inc\swilib.h"
#include "..\inc\main.h"
#include "..\inc\buff.h"
#include "..\inc\code.h"
#include "..\inc\menu.h"
#include "..\inc\conf_loader.h"

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

void (*inp1_action)(WSHDR*);
int inp1_onkey(GUI *gui, GUI_MSG *msg) {

	EDITCONTROL ec;

	if (msg->gbsmsg->submess == RED_BUTTON) {
		return 1;
	}

	if (msg->gbsmsg->submess == GREEN_BUTTON) {

	}

	if (msg->keys == 0x18) {
		ExtractEditControl(gui, 1, &ec);
		if (inp1_action) inp1_action(ec.pWS);
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

void inp1_ghook(GUI *gui, int cmd) {

	static SOFTKEY_DESC sk1 = { 0x0018, 0x0000, (int)"确定" };

	//WSHDR *editstr = EDIT_GetUserPointer(gui);

	if (cmd == 2) {
		//Called after onCreate
	}

	if (cmd == 3) {
		//退出
		//FreeWS(tmostr);    
	}
	if (cmd == 7) {
		SetSoftKey(gui, &sk1, SET_SOFT_KEY_N);
	}
}

void inp1_locret(void) {
}

INPUTDIA_DESC inp1_desc = { 1, inp1_onkey, inp1_ghook, (void *)inp1_locret, 0,
		&menu_skt, { 0, 22, 131, 153 }, 4, 100, 101, 0, 0, 0x40000000 };

HEADER_DESC inp1_hdr = { 0, 0, 131, 21,/*icon*/NULL, (int)"输入", LGP_NULL };

int launchInput(WSHDR* content, int maxlen, int type, void (*ac)(WSHDR*)) {
	inp1_action = ac;
	void *ma = malloc_adr();
	void *eq;
	EDITCONTROL ec;
	PrepareEditControl(&ec);
	eq = AllocEQueue(ma, mfree_adr());
	ConstructEditControl(&ec, type, 0x40, content, maxlen);
	AddEditControlToEditQend(eq, &ec, ma);
	patch_header(&inp1_hdr);
	patch_input(&inp1_desc);
	return CreateInputTextDialog(&inp1_desc, &inp1_hdr, eq, 1, content);
}
