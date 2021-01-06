#include "..\..\inc\swilib.h"
#include "type.h"
#include "rect_patcher.h"
#include "lang.h"

extern WSHDR *ws_edit_functmp;
extern WSHDR *ws_edit_nametmp;
extern MENU_LIST *ml_edit_tmp;
extern unsigned int EDGUI_ID;
extern void open_select_file_gui(void *ed_gui, int type);


const HEADER_DESC edheader={0, 0, 0, 0, NULL, (int)LGP_EDIT, LGP_NULL};
const SOFTKEY_DESC ed_sk[]=
{
	{0x0018,0x0000,(int)LGP_NULL},
	{0x0001,0x0000,(int)LGP_NULL},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB ed_skt=
{
	ed_sk,0
};

//void openfunc_list(void *ed_gui)
//{
//	
//}


void on_exmenu(USR_MENU_ITEM *item)
{
	if (item->type==0)
	{
		switch(item->cur_item)
		{
		case 0:
			gb2ws(item->ws, LGP_SLECET_FOLDER, 16);
			break;
		case 1:
			gb2ws(item->ws, LGP_SLECET_FILE, 16);
			break;
		//case 2:
		//	gb2ws(item->ws, "使用菜单索引", 16);
		//	break;
		}
	}
	if (item->type==1)
	{
		switch(item->cur_item)
		{
		case 0:
			open_select_file_gui(item->user_pointer, 0);
			break;
		case 1:
			open_select_file_gui(item->user_pointer, 1);
			break;
		}
	}
}

int ed_onkey(GUI *data, GUI_MSG *msg)
{
	int i=EDIT_GetFocus(data);
	if(i==4)
	{
		if (msg->gbsmsg->msg==KEY_DOWN)
		{
			if (msg->gbsmsg->submess==ENTER_BUTTON)
			{
				EDIT_OpenOptionMenuWithUserItems(data, on_exmenu, data, 2);
				return -1;
			}
		}
	}
	return 0;
}

void ed_ghook(GUI *data, int cmd)
{
	if (cmd==0x0A)
	{
		DisableIDLETMR();
	}
	if (cmd==0x07)
	{
		EDITCONTROL ec;
		ExtractEditControl(data,2,&ec);
		wstrcpy(ws_edit_nametmp, ec.pWS);
		
		ExtractEditControl(data,4,&ec);
		wstrcpy(ws_edit_functmp, ec.pWS);
	}
}

void ed_locret(void){;}
INPUTDIA_DESC ed_desc=
{
	1,
	ed_onkey,
	ed_ghook,
	(void *)ed_locret,
	0,
	&ed_skt,
	{0,0,0,0},
	4,
	100,
	101,
	0,
	0,
	0x40000000
};

void edit_ml(MENU_LIST *ml)
{
	ml_edit_tmp=ml;
	if(!ml_edit_tmp)
		return;
	void *ma=malloc_adr();
	void *eq;
	EDITCONTROL ec;
	WSHDR *ws;
	WSHDR *ws2;
	eq=AllocEQueue(ma,mfree_adr());
	ws=AllocWS(256);
	ws2=AllocWS(256);
	
	PrepareEditControl(&ec);
	wsprintf(ws,_percent_t, LGP_NAME);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws,ws->wsbody[0]);
	AddEditControlToEditQend(eq,&ec,ma);
	
	PrepareEditControl(&ec);
	utf8_2ws(ws2, ml->name, ml->name_len);
	ConstructEditControl(&ec,ECT_CURSOR_STAY,ECF_SET_CURSOR_END,ws2,128);
	AddEditControlToEditQend(eq,&ec,ma);
	
	PrepareEditControl(&ec);
	wsprintf(ws,_percent_t, LGP_FUNC);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ws,ws->wsbody[0]);
	AddEditControlToEditQend(eq,&ec,ma);
	
	PrepareEditControl(&ec);
	utf8_2ws(ws2, ml->func, ml->func_len);
	ConstructEditControl(&ec,ECT_CURSOR_STAY,ECF_SET_CURSOR_END,ws2,128);
	AddEditControlToEditQend(eq,&ec,ma);
	
	patch_header(&edheader);
	patch_input(&ed_desc);
	EDGUI_ID=CreateInputTextDialog(&ed_desc,&edheader,eq,1,0);
	
	FreeWS(ws);
	FreeWS(ws2);
}

