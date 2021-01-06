#include "inc\mc.h"
#include "inc\mui.h"

char* yesno[2];

int fa_attr;
int fa_ro, fa_hd, fa_sy, fa_ar, fa_sb;

int empty_onkey(GUI *gui, GUI_MSG *msg){return(0);}

int file_prop_onkey(GUI *gui, GUI_MSG *msg)
{
	if (msg->keys==26)
	{
		if (pathbuf)
		{
			fa_attr=0;
			if (fa_ro) fa_attr|=FA_READONLY;
			if (fa_hd) fa_attr|=FA_HIDDEN;
			if (fa_sy) fa_attr|=FA_SYSTEM;
			if (fa_ar) fa_attr|=FA_ARCHIVE;

			int res = 1;
			EnumSel(M_SetAttr, (int) &res);

			if (!res)
				MsgBoxError(1, (int) muitxt(ind_err_attrset));
			else
				DoRefresh();
		} 
	}
	int i=EDIT_GetFocus(gui)-1;
	int key=msg->gbsmsg->submess;
	if (i==1 && ((key>='0' && key<='9') || key=='#' /*|| key=='*' ||
												   #ifdef NEWSGOLD
												   key==RIGHT_SOFT
												   #else
												   key==LEFT_SOFT
												   #endif*/
												   )) return -1;
	return 0; //Do standart keys
}

void empty_ghook(GUI *gui, int cmd){};

void file_prop_ghook(GUI *gui, int cmd)
{
	EDITCONTROL ec;
	if (cmd == 7)
	{
		int i = EDIT_GetFocus(gui) - 1;
		if (i == 8 || i == 10 || i == 12 || i == 14 || i == 16)
		{
			int j=EDIT_GetItemNumInFocusedComboBox(gui)-1;
			if (i ==  8) fa_ro = j != 0 ? 1 : 0;
			if (i == 10) fa_hd = j != 0 ? 1 : 0;
			if (i == 12) fa_sy = j != 0 ? 1 : 0;
			if (i == 14) fa_ar = j != 0 ? 1 : 0;
			if (i == 16) fa_sb = j != 0 ? 1 : 0;
		}
	}
	else if (cmd == 0x0D)
	{
		int j;
		int i = EDIT_GetFocus(gui);
		WSHDR* buff = AllocWS(64);
		ExtractEditControl(gui, i, &ec);
		if ((j = EDIT_GetItemNumInFocusedComboBox(gui)))
		{
			wsprintf(buff, _t, yesno[j - 1]);
		}
		else
		{
			ExtractEditControl(gui, EDIT_GetFocus(gui) - 1, &ec);
			wstrcpy(buff, ec.pWS);
		}
		EDIT_SetTextToFocused(gui, buff);
		FreeWS(buff);
	}
}

void empty_locret(void) {}

SOFTKEY_DESC empty_menu_sk[]= { { 0, 0, 0 } };

SOFTKEYSTAB empty_menu_skt =
{
	empty_menu_sk, 0
};

HEADER_DESC file_prop_hdr = { 0, 0, 0, 0, NULL, 0, LGP_NULL };
INPUTDIA_DESC file_prop_desc =
{
	1,
	file_prop_onkey,
	file_prop_ghook,
	(void *)empty_locret,
	0,
	&empty_menu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000000
};

void prep_hd(EDITCONTROL* ec)
{
	ec->ed_options.bitmask = 2|8;
	ec->ed_options.font = 2;
	ec->ed_options.pen[3] = 100;
	ec->ed_options.pen[2] = 0x80;
} 

void prep_inf(EDITCONTROL* ec)
{
	ec->ed_options.bitmask = 2;
	ec->ed_options.font = 1;
}

void _AddText(WSHDR* wsText, EDITCONTROL* pEc, void* eq, void* ma, int type, int addEOL)
{
	ConstructEditControl(pEc, type, (addEOL ? ECF_APPEND_EOL : 0) | ECF_SKIP, wsText, MAX_PATH);
	if (type == ECT_HEADER)
		prep_hd(pEc);
	else
		prep_inf(pEc);
	AddEditControlToEditQend(eq, pEc, ma);
}

#pragma inline
void AddText(WSHDR* wsText, EDITCONTROL* pEc, void* eq, void* ma, int type)
{
	_AddText(wsText, pEc, eq, ma, type, 0);
}

#pragma inline
void AddTextLine(WSHDR* wsText, EDITCONTROL* pEc, void* eq, void* ma, int type)
{
	_AddText(wsText, pEc, eq, ma, type, 1);
}

void AddAttrRow(WSHDR* buff, EDITCONTROL* pEc, void* eq, void* ma, char* szAttrName, int attrValue, int ftype)
{
	wsprintf(buff, _tc, szAttrName);
	AddText(buff, pEc, eq, ma, ECT_READ_ONLY);

	wsprintf(buff, _t, yesno[attrValue]);
	if (ftype == TYPE_COMMON_FILE || ftype == TYPE_COMMON_DIR)
	{
		ConstructComboBox(pEc, ECT_COMBO_BOX, ECF_APPEND_EOL, buff, 32, 0, 2, attrValue+1);
		prep_inf(pEc);
		AddEditControlToEditQend(eq, pEc, ma);
	}
	else
	{
		AddTextLine(buff, pEc, eq, ma, ECT_READ_ONLY);
	}
}

void _FileProp(FILEINF *file)
{
	if (!pathbuf || !file) return;

	file_prop_hdr.lgp_id = (int) muitxt(ind_prop);

	char sbuff[128];
	char sbuff2[128];
	void *ma=malloc_adr();
	void *eq=AllocEQueue(ma,mfree_adr());
	int f;
	EDITCONTROL ec;
	PrepareEditControl(&ec);

	WSHDR *buff=AllocWS(MAX_PATH);


	//Full Path
	wsprintf(buff, _tc, muitxt(ind_fullname));
	AddTextLine(buff, &ec, eq, ma, ECT_HEADER);
	CurFullPath(file->sname);
	str_2ws(buff, pathbuf, MAX_PATH);
	AddTextLine(buff, &ec, eq, ma, ECT_NORMAL_TEXT);

	//Size
	wsprintf(buff, _tc, muitxt(ind_size));
	AddTextLine(buff, &ec, eq, ma, ECT_HEADER);
	if (IsMultiChk()>1 || file->attr & FA_DIRECTORY)
	{
		CHKDS_PARAM param;
		param.gsize=0;
		param.gcsize=0;
		param.count=0;
		EnumSel(M_DirSize, (int)&param);

		sz2s(param.gsize, sbuff);
		sz2s(param.gcsize, sbuff2);
		if (file->ftype == TYPE_ZIP_FILE || file->ftype == TYPE_ZIP_DIR)
			wsprintf(buff, "%t: %t\n%t: %t\n%t: %d\n%t: %d" ,
				muitxt(ind_global),
				sbuff,
				muitxt(ind_cglobal),
				sbuff2,
				muitxt(ind_folders),
				param.count>>16,
				muitxt(ind_files),
				param.count & 0xffff);
		else
			wsprintf(buff, "%t: %t\n%t: %d\n%t: %d" ,
				muitxt(ind_global),
				sbuff,
				muitxt(ind_folders),
				param.count>>16,
				muitxt(ind_files),
				param.count & 0xffff);
	} 
	else
	{
		if (file->ftype == TYPE_ZIP_FILE)
			wsprintf(buff, "%t: %u %t\n%t: %u %t",
				muitxt(ind_ncsize),
				file->size,
				muitxt(ind_byte),
				muitxt(ind_csize),
				file->csize,
				muitxt(ind_byte));
		else
			wsprintf(buff, "%u %t", 
				file->size,
				muitxt(ind_byte));
	}
	AddTextLine(buff, &ec, eq, ma, ECT_READ_ONLY);

	//Date
	wsprintf(buff, _tc, muitxt(ind_date));
	AddTextLine(buff, &ec, eq, ma, ECT_HEADER);
	fdt2s(file->time, sbuff);
	str_2ws(buff, sbuff, 16);
	AddTextLine(buff, &ec, eq, ma, ECT_READ_ONLY);

	//Attr
	wsprintf(buff, _tc, muitxt(ind_attr));
	AddTextLine(buff, &ec, eq, ma, ECT_HEADER);

	AddAttrRow(buff, &ec, eq, ma, muitxt(ind_readonly), (file->attr & FA_READONLY ? 1 : 0), file->ftype);
	AddAttrRow(buff, &ec, eq, ma, muitxt(ind_hidden), (file->attr & FA_HIDDEN ? 1 : 0), file->ftype);
	AddAttrRow(buff, &ec, eq, ma, muitxt(ind_system), (file->attr & FA_SYSTEM ? 1 : 0), file->ftype);
	AddAttrRow(buff, &ec, eq, ma, muitxt(ind_arh), (file->attr & FA_ARCHIVE ? 1 : 0), file->ftype);

	if (file->ftype == TYPE_COMMON_DIR)
	{
		wsprintf(buff, _tc, muitxt(ind_subdirs));
		ConstructEditControl(&ec, ECT_HEADER,ECF_NORMAL_STR | ECF_APPEND_EOL,buff,MAX_PATH);
		prep_hd(&ec);
		prep_inf(&ec);
		ec.ed_options.bitmask = ec.ed_options.bitmask | 8;
		AddEditControlToEditQend(eq, &ec, ma); //15
		f = 0;
		wsprintf(buff, _t, yesno[f]);
		ConstructComboBox(&ec, ECT_COMBO_BOX, ECF_APPEND_EOL, buff, 32, 0, 2, f + 1);
		prep_inf(&ec);
		AddEditControlToEditQend(eq, &ec, ma); //16*
	}

	CreateInputTextDialog(&file_prop_desc,&file_prop_hdr,eq,1,0);

	FreeWS(buff);
}
