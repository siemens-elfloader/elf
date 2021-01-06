#include "inc\lng.h"
#include "inc\mc.h"
#include "inc\zslib.h"

GBSTMR cmtm;

#define main_ind 0
#define misc_ind 1
#define view_ind 2
#define last_ind view_ind

int menu_id[last_ind+1]={0,0,0};

void CloseMenu()
{
	if (IsGuiOnTop(MAINGUI_ID))
	{
		for(int ii=0;ii<=last_ind;ii++)
			menu_id[ii]=0;
		return;
	}

	int ndr=0;
	for(int ii=0;ii<=last_ind;ii++)
		if (menu_id[ii])  
		{
			if (IsGuiOnTop(menu_id[ii]))
			{
				GeneralFunc_flag1(menu_id[ii],1);
				menu_id[ii] = 0;
			}
			else
				ndr = 1;
		}

		if (ndr)
			GBS_StartTimerProc(&cmtm,1,CloseMenu);
}

void CloseAllMenu()
{
	GeneralFuncF1(1);
	CloseMenu();
}





void MC_Exit(void)
{
	CloseMenu();
	DoExit();
}

void MC_AboutDlg(void)
{
	ShowMSG(2,(int)psz_about); 
}

void MC_Options(void)
{
	if (wsbuf)
	{
		str_2ws(wsbuf, successed_config_filename, MAX_PATH); 
		ExecuteFile(wsbuf, 0, 0);
	} 
}

void MC_Paste(void)
{
	DoPaste();
	CloseAllMenu();
}

void MC_Cancel(void)
{
	DoCancel();
	CloseAllMenu();
}

void MC_Copy(void)
{
	DoCopy();
	CloseAllMenu();
}

void MC_Move(void)
{
	DoMove();
	CloseAllMenu();
}

void MC_Delit(void)
{
	DoDel();
	CloseAllMenu();
}

void MC_Chk(void)
{
	DoChk();
	CloseAllMenu();
}

void MC_ChkAll(void)
{
	DoChkAll();
	CloseAllMenu();
}

void MC_UnChkAll(void)
{
	DoUnCAll();
	CloseAllMenu();
}

void MC_InvChk(void)
{
	DoInvChk();
	CloseAllMenu();
}

void MC_BMAdd(void)
{
	DoBMAdd();
	CloseAllMenu();
}

void MC_BMList(void)
{
	DoBMList();
	CloseAllMenu();
}

void MC_SRTName(void)
{
	DoSortN();
	CloseAllMenu();
}

void MC_SRTExt(void)
{
	DoSortE();
	CloseAllMenu();
}

void MC_SRTSize(void)
{
	DoSortS();
	CloseAllMenu();
}

void MC_SRTDate(void)
{
	DoSortD();
	CloseAllMenu();
}

void MC_SRTRev(void)
{
	DoSortR();
	CloseAllMenu();
}

void MC_Refresh(void)
{
	DoRefresh();
	CloseAllMenu();
}

void MC_Filter(void)
{
	DoFilter();
	CloseAllMenu();
}

void MC_FileProp(void)
{
	if ( DoFileProp() ) 
		CloseMenu();
}






HEADER_DESC tmenuhdr={0,0,0,0,0,LGP_NULL/*(int)sz_mcmenu*/,LGP_NULL};
int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_sk[]=
{
	{0x0018,0x0000,LGP_NULL/*(int)sz_select*/},
	{0x0001,0x0000,LGP_NULL/*(int)sz_back*/},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};
SOFTKEYSTAB menu_skt=
{
	menu_sk,0
};






MENUITEM_DESC opt_menuitems[]={
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *opt_menuprocs[]={
	(void *)MC_Open, 
	(void *)MM_File,
	(void *)MM_Oper,
	(void *)MC_FileProp,
	(void *)MM_View,
	(void *)MM_Misc,
	(void *)MC_Exit,
};

MENU_DESC opt_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	opt_menuitems,
	(MENUPROCS_DESC const*)opt_menuprocs,
	sizeof(opt_menuprocs)/sizeof(void *)
};



MENUITEM_DESC zip_opt_menuitems[]={
//	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *zip_opt_menuprocs[]={
//	(void *)MC_Open, 
	(void *)MM_File,
	(void *)MM_Oper,
	(void *)MC_FileProp,
	(void *)MM_View,
	(void *)MM_Misc,
	(void *)MC_Exit,
};

MENU_DESC zip_opt_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	zip_opt_menuitems,
	(MENUPROCS_DESC const*)zip_opt_menuprocs,
	sizeof(zip_opt_menuprocs)/sizeof(void *)
};





MENUITEM_DESC op_menuitems[]={
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *op_menuprocs[]={
	(void *)MC_Paste, 
	(void *)MC_Cancel, 
	(void *)MC_Copy, 
	(void *)MC_Move, 
	(void *)MC_Delit, 
	(void *)MC_Rename, 
	(void *)MC_NewDir, 
	(void *)MC_NewFile, 
};

MENU_DESC op_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	op_menuitems,
	(MENUPROCS_DESC const*)op_menuprocs,
	sizeof(op_menuprocs)/sizeof(void *)
};



MENUITEM_DESC zip_op_menuitems[]={
//	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
//	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *zip_op_menuprocs[]={
//	(void *)MC_Paste, 
//	(void *)MC_Cancel, 
	(void *)MC_Copy, 
//	(void *)MC_Move, 
//	(void *)MC_Delit, 
//	(void *)MC_Rename, 
//	(void *)MC_NewDir, 
//	(void *)MC_NewFile, 
};

MENU_DESC zip_op_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	zip_op_menuitems,
	(MENUPROCS_DESC const*)zip_op_menuprocs,
	sizeof(zip_op_menuprocs)/sizeof(void *)
};




MENUITEM_DESC mis_menuitems[]={
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *mis_menuprocs[]={
	(void *)MM_BM,
	(void *)MC_DrvInf,
	(void *)MC_Options,
	(void *)MC_AboutDlg,
};

MENU_DESC mis_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	mis_menuitems,
	(MENUPROCS_DESC const*)mis_menuprocs,
	sizeof(mis_menuprocs)/sizeof(void *)
};



MENUITEM_DESC fl_menuitems[]={
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *fl_menuprocs[]={
	(void *)MC_Chk,
	(void *)MC_ChkAll,
	(void *)MC_UnChkAll,
	(void *)MC_InvChk,
};

MENU_DESC fl_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	fl_menuitems,
	(MENUPROCS_DESC const*)fl_menuprocs,
	sizeof(fl_menuprocs)/sizeof(void *)
};



MENUITEM_DESC bm_menuitems[]={
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *bm_menuprocs[]={
	(void *)MC_BMAdd,
	(void *)MC_BMList,
};

MENU_DESC bm_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	bm_menuitems,
	(MENUPROCS_DESC const*)bm_menuprocs,
	sizeof(bm_menuprocs)/sizeof(void *)
};

MENUITEM_DESC st_menuitems[]={
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *st_menuprocs[]={
	(void *)MC_SRTName,
	(void *)MC_SRTExt,
	(void *)MC_SRTSize,
	(void *)MC_SRTDate,
	(void *)MC_SRTRev,
};

MENU_DESC st_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	st_menuitems,
	(MENUPROCS_DESC const*)st_menuprocs,
	sizeof(st_menuprocs)/sizeof(void *)
};

MENUITEM_DESC vw_menuitems[]={
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
	{NULL,LGP_NULL,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};
void *vw_menuprocs[]={
	(void *)MM_Sort,
	(void *)MC_Filter,
	(void *)MC_Refresh,
};

MENU_DESC vw_menu=
{
	8,NULL,NULL,NULL,
	menusoftkeys,
	&menu_skt,
	0,
	NULL,
	vw_menuitems,
	(MENUPROCS_DESC const*)vw_menuprocs,
	sizeof(vw_menuprocs)/sizeof(void *)
};

void MM_Main(void)
{
	if (IsInZip())
		menu_id[main_ind] = CreateMenu(0,0,&zip_opt_menu,&tmenuhdr,0,1,0,0);
	else
		menu_id[main_ind] = CreateMenu(0,0,&opt_menu,&tmenuhdr,0,1,0,0);
}

void MM_Oper(void)
{
	if (IsInZip())
		CreateMenu(0,0,&zip_op_menu,&tmenuhdr,0,1,0,0);
	else
		CreateMenu(0,0,&op_menu,&tmenuhdr,0,1,0,0);
}

void MM_Misc(void)
{
	menu_id[misc_ind] = CreateMenu(0,0,&mis_menu,&tmenuhdr,0,1,0,0);
}

void MM_File(void)
{
	CreateMenu(0,0,&fl_menu,&tmenuhdr,0,1,0,0);
}

void MM_BM(void)
{
	CreateMenu(0,0,&bm_menu,&tmenuhdr,0,1,0,0);
}

void MM_Sort(void)
{
	CreateMenu(0,0,&st_menu,&tmenuhdr,0,1,0,0);
}

void MM_View(void)
{
	menu_id[view_ind] = CreateMenu(0,0,&vw_menu,&tmenuhdr,0,1,0,0);
}


#pragma inline
void patch_header(HEADER_DESC* head)
{
	head->rc.x=0;
	head->rc.y=YDISP;
	head->rc.x2=ScreenW()-1;
	head->rc.y2=HeaderH()+YDISP-1;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
	inp->rc.x=0;
	inp->rc.y=HeaderH()+1+YDISP;
	inp->rc.x2=ScreenW()-1;
	inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

void InitAllMD()
{
	patch_header(&tmenuhdr);

	extern HEADER_DESC txt_inp_hdr;
	extern INPUTDIA_DESC txt_inp_desc;
	extern HEADER_DESC file_prop_hdr;
	extern INPUTDIA_DESC file_prop_desc;
	extern HEADER_DESC disk_prop_hdr;
	extern INPUTDIA_DESC disk_prop_desc;

	patch_header(&txt_inp_hdr);
	patch_input(&txt_inp_desc);
	txt_inp_desc.rc.y+=20;
	txt_inp_desc.rc.x+=10;
	patch_header(&file_prop_hdr);
	patch_input(&file_prop_desc);
	patch_header(&disk_prop_hdr);
	patch_input(&disk_prop_desc);
}
