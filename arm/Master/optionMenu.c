/*
 * 文件名: optionMenu.c
 * 作者: BingK(binghelingxi)
 *
 * 最后修改日期: 2008.07.26
 *
 * 作用: 建立主菜单，以及实现主菜单中的功能，如显示信息，情景模式控制菜单，清除配置等
 *
 */

#include "..\inc\swilib.h"
#include "rect_patcher.h"
#include "lang.h"
#include "main.h"
#include "optionMenu.h"
#include "getConfig.h"
#include "usedstr.h"
#include "string.h"

#define MAIN_MENU_ITEMS_N	10
#define	MAIN_MENU_ITEMS_N_1	9

int PATH_TYPE=0; //0,backup, 1,restore

const int mmenusoftkeys[]={0,1,2};

const SOFTKEY_DESC mmenu_sk[]=
{
	{0x0018,0x0000,(int)LGP_SELECT},
	{0x0001,0x0000,(int)LGP_BACK},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB mmenu_skt=
{
	mmenu_sk,0
};


void option_menu_ghook(void *data, int cmd)
{
	if (cmd==0x0A)
	{
		DisableIDLETMR();
	}
}

void menu_exit(GUI *gui)
{
	GeneralFuncF1(1);
	CloseCSM(MAIN_CSM_ID);
}

void menu_about(GUI *gui)
{
	GeneralFuncF1(1);
	ShowMSG(0, (int)COPYRIGHT);
}

void createProfileOnoffMenu(void);
void menu_profile(GUI *gui)
{
	GeneralFuncF1(1);
	createProfileOnoffMenu();
}

void deleteAllConfig(void);
void menu_del_all(GUI *gui)
{
	GeneralFuncF1(1);
	deleteAllConfig();
}

void deleteThis(void);
void menu_del_this(GUI *gui)
{
	GeneralFuncF1(1);
	deleteThis();
}

void delUnusedConfig(void);
void menu_del_unused(GUI *gui)
{
	GeneralFuncF1(1);
	delUnusedConfig();
}

void showPatchInfo(void);
void menu_info(GUI *gui)
{
	GeneralFuncF1(1);
	showPatchInfo();
}

void pathInputDlg(void);
void menu_backup(GUI *gui)
{
	GeneralFuncF1(1);
	PATH_TYPE=0;
	pathInputDlg();
}

void menu_restore(GUI *gui)
{
	GeneralFuncF1(1);
	PATH_TYPE=1;
	pathInputDlg();
}

void menu_quit_without_rs(GUI *gui)
{
	GeneralFuncF1(1);
	isRunScanerNeed=0;
	CloseCSM(MAIN_CSM_ID);
}

const MENUPROCS_DESC option_menu_HNDLS[MAIN_MENU_ITEMS_N]=
{
	menu_profile,
	menu_info,
	menu_del_this,
	menu_del_unused,
	menu_del_all,
	menu_backup,
	menu_restore,
	menu_about,
	menu_quit_without_rs,
	menu_exit,
};

const MENUITEM_DESC option_menu_ITEMS[MAIN_MENU_ITEMS_N]=
{
	{NULL,(int)LGP_PROFILE,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_PATCH_INFO,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_THIS,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_UNUSED,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_ALL,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_BACKUP,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_RESTORE,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_ABOUT,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_QUIT_WITHOUT_RS,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_QUIT,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const HEADER_DESC option_menu_header={0, 0, 0, 0,NULL,(int)LGP_OPTIONS,LGP_NULL};

const MENU_DESC option_menu=
{
	8,NULL,option_menu_ghook,NULL,
	mmenusoftkeys,
	&mmenu_skt,
	0x10,//MENU_FLAG,
	NULL,
	option_menu_ITEMS,//menuitems,
	option_menu_HNDLS,//menuprocs,
	MAIN_MENU_ITEMS_N
};

const MENUPROCS_DESC option_menu_HNDLS_1[MAIN_MENU_ITEMS_N_1]=
{
	menu_info,
	menu_del_this,
	menu_del_unused,
	menu_del_all,
	menu_backup,
	menu_restore,
	menu_about,
	menu_quit_without_rs,
	menu_exit,
};

const MENUITEM_DESC option_menu_ITEMS_1[MAIN_MENU_ITEMS_N_1]=
{
	{NULL,(int)LGP_PATCH_INFO,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_THIS,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_UNUSED,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DEL_ALL,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_BACKUP,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_RESTORE,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_ABOUT,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_QUIT_WITHOUT_RS,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_QUIT,		LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENU_DESC option_menu_1=
{
	8,NULL,option_menu_ghook,NULL,
	mmenusoftkeys,
	&mmenu_skt,
	0x10,//MENU_FLAG,
	NULL,
	option_menu_ITEMS_1,//menuitems,
	option_menu_HNDLS_1,//menuprocs,
	MAIN_MENU_ITEMS_N_1
};

void show_option_menu(void)
{
	PTC_CONFIG *ptcfg;
	patch_header(&option_menu_header);
	if(ptcfg=getPatchConfigItem(PTCFG_CUR))
	{
		if(ptcfg->disableProfile)
			CreateMenu(0, 0, &option_menu_1, &option_menu_header, 0, MAIN_MENU_ITEMS_N_1, 0, 0);
		else
			CreateMenu(0, 0, &option_menu, &option_menu_header, 0, MAIN_MENU_ITEMS_N, 0, 0);
	}
}

void deleteAllConfig(void)
{
	char path[128];
	char folder[128]=PATCH_DIR;
	char tp[128];
	DIR_ENTRY de;
	unsigned int err;
	strcat(folder, PTC_FOLDR);
	strcpy(path, folder);
	strcat(path, "*.ptc");
	if(FindFirstFile(&de, path, &err))
	{
		do
		{
			sprintf(tp, "%s%s", folder, de.file_name);
			unlink(tp, &err);
		}while(FindNextFile(&de,&err));
	}
	FindClose(&de,&err);
	fuckThemAll();
	patch_n=0;
	if(!readConfig(0, 0))
	{
		MsgBoxError(1, (int)LGP_RELOAD_CONFIG_ERR);
		CloseCSM(MAIN_CSM_ID);
	}
}

void deleteThis(void)
{
	char path[128];
	PTC_CONFIG *ptcfg=getPatchConfigItem(PTCFG_CUR);
	if(ptcfg)
	{
		FSTATS fstats;
		unsigned int err;
		sprintf(path, "%s%s%08s", PATCH_DIR, PTC_FOLDR, ptcfg->patchInfo->patchID);
		if(GetFileStats(path,&fstats,&err)!=-1)
		{
			unlink(path, &err);
		}
		reloadThisPatch(ptcfg);
	}
}



const HEADER_DESC profile_menu_header={0, 0, 0, 0,NULL,(int)LGP_PROFILE,LGP_NULL};

int profile_menu_onkey(void *data, GUI_MSG *msg)
{
	PTC_CONFIG *ptcfg;
	int c=GetCurMenuItem(data);
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
		int i=msg->gbsmsg->submess;
		switch(i)
		{
		case LEFT_SOFT:
			return 1;       
		case ENTER_BUTTON:
		case RIGHT_SOFT:
			{
				//int i=GetCurMenuItem(data);
				ptcfg=getPatchConfigItem(PTCFG_CUR);
				if(ptcfg)
				{
					setPatchOnOff(ptcfg, c);
					SetMenuItemIcon(data, c, getPatchOnOff(ptcfg, c));
					REDRAW();
				}
				return (-1);
			}
		}
	}
	return 0;
}

/*
char profileName[7][16]=
{
	LGP_PROFILE1,
	LGP_PROFILE2,
	LGP_PROFILE3,
	LGP_PROFILE4,
	LGP_PROFILE5,
	LGP_PROFILE6,
	LGP_PROFILE7,
};
*/
void profile_menu_iconhndl(void *data, int curitem, void *unk)
{
	PTC_CONFIG *ptcfg;
	void *item=AllocMenuItem(data);
	ptcfg=getPatchConfigItem(PTCFG_CUR);
	WSHDR *ws;
	int n=2;
	if(ptcfg)
	{
		ws=AllocMenuWS(data,128);
	#ifdef BUG
		gb2ws(ws, profileName[curitem], 128);
	#else
		//wsprintf(ws, PERCENT_T, profileName[curitem]);
#ifdef NEWSGOLD
		getProfileNameByN(ws, curitem, 0);
#else
		getProfileNameByN(curitem, ws, 0);
#endif
	#endif
		if(getPatchOnOff(ptcfg, curitem))
			n=1;
		else
			n=0;
	}
	else
	{
		ws=AllocMenuWS(data,16);
	#ifdef BUG
		gb2ws(ws, ERR_STR, 16);
	#else
		wsprintf(ws, PERCENT_T, ERR_STR);
	#endif
		n=2;
	}
	SetMenuItemIconArray(data, item, S_ICONS);
	SetMenuItemText(data, item, ws,curitem);
	SetMenuItemIcon(data, curitem, n);
}

void profile_menu_ghook(void *data, int cmd)
{
	if (cmd==0x0A)
		DisableIDLETMR();
}
const SOFTKEY_DESC profile_menu_sk[]=
{
	{0x0018,0x0000,(int)LGP_OK},
	{0x0001,0x0000,(int)LGP_ONOFF},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};
const SOFTKEYSTAB profile_menu_skt=
{
	profile_menu_sk,0
};

const MENU_DESC profile_menu=
{
	8,
	profile_menu_onkey,
	profile_menu_ghook,
	NULL,
	mmenusoftkeys,
	&profile_menu_skt,
	0x11,
	profile_menu_iconhndl,
	NULL,   //Items
	NULL,   //Procs
	0   //n
};

void createProfileOnoffMenu(void)
{
	patch_header(&profile_menu_header);
	CreateMenu(0, 0, &profile_menu, &profile_menu_header, 0, 7, 0, 0);
}


void delUnusedConfig(void)
{
	char patchID[16];
	char path[128];
	char folder[128]=PATCH_DIR;
	char tp[128];
	DIR_ENTRY de;
	unsigned int err;
	strcat(folder, PTC_FOLDR);
	strcpy(path, folder);
	strcat(path, "*.ptc");
	if(FindFirstFile(&de, path, &err))
	{
		do
		{
			strncpy(patchID, de.file_name, 8);
			patchID[8]=0;
			if(isPatchExistedByID(patchID))
			{
				sprintf(tp, "%s%s", folder, de.file_name);
				unlink(tp, &err);
			}
		}while(FindNextFile(&de,&err));
	}
	FindClose(&de,&err);
}
int infoOnKey(GUI *data, GUI_MSG *msg)
{
	if(msg->keys==0xFFF)  // OK
	{
		return (1);    
	}
	if(msg->keys==0xFFE)  // Back
	{
		return (0xFF);
	}
	return 0;
}
void infoGHook(GUI *data, int cmd)
{
	if(cmd==2)
	{
		EDIT_SetFocus(data, 0);
	}
}
void info_locret(void){}
HEADER_DESC INFO_HDR={0,0,0,0,NULL,(int)LGP_PATCH_INFO,LGP_NULL};
INPUTDIA_DESC INFO_DESC=
{
	1,
	infoOnKey,
	infoGHook,
	(void *)info_locret,
	0,
	&mmenu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000000
};
void showPatchInfo(void)
{
	PTC_CONFIG *ptcfg=getPatchConfigItem(PTCFG_CUR);
	if(ptcfg)
	{
		WSHDR *ws=AllocWS(256);
		WSHDR *ts=AllocWS(200);
		void *ma=malloc_adr();
		void *eq;
		EDITCONTROL ec;
		PrepareEditControl(&ec);
		eq=AllocEQueue(ma,mfree_adr());
		//Modify
		wsprintf(ws, PERCENT_T, LGP_PATCH_NAME);
		if(isUniFormat(ptcfg->patchInfo->patchName))
			uniFormatString2ws(ts, ptcfg->patchInfo->patchName);
		else
			wsprintf(ts, PERCENT_T, ptcfg->patchInfo->patchName);
		wstrcat(ws,ts);
		//wsprintf(ws, "%t%t", LGP_PATCH_NAME, ptcfg->patchInfo->patchName);
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
		AddEditControlToEditQend(eq,&ec,ma);
		
		wsprintf(ws, "%t%t", LGP_PATCH_AUTHOR, ptcfg->patchInfo->author);
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
		AddEditControlToEditQend(eq,&ec,ma);
		
		wsprintf(ws, "%t%t", LGP_PATCH_ID, ptcfg->patchInfo->patchID);
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
		AddEditControlToEditQend(eq,&ec,ma);
		
		wsprintf(ws, "%t%t", LGP_PATCH_VERSION, ptcfg->patchInfo->version);
		ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
		AddEditControlToEditQend(eq,&ec,ma);
		
		if(ptcfg->patchInfo->info)
		{
			//Modify
			wsprintf(ws, PERCENT_T, LGP_PATCH_INFO_OTH);
			if(isUniFormat(ptcfg->patchInfo->info))
				uniFormatString2ws(ts, ptcfg->patchInfo->info);
			else
				wsprintf(ts, PERCENT_T, ptcfg->patchInfo->info);
			wstrcat(ws,ts);
			//wsprintf(ws, "%t%t", LGP_PATCH_INFO_OTH, ptcfg->patchInfo->info);
			ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ws,256);
			AddEditControlToEditQend(eq,&ec,ma);
		}
		patch_header(&INFO_HDR);
		patch_input(&INFO_DESC);
		CreateInputTextDialog(&INFO_DESC, &INFO_HDR, eq, 1, 0);
		FreeWS(ws);
		FreeWS(ts);
	}
}

const SOFTKEY_DESC SK_BACKUP={0x0FFF,0x0000,(int)LGP_BACKUP};
const SOFTKEY_DESC SK_RESTORE={0x0FFF,0x0000,(int)LGP_RESTORE};

//fcopy form mc
#define BUF_SIZE 0x4000
int fcopy(char *dst, char *src)
{
	unsigned int err;
	int fi=-1, fo=-1;
	char *buff=0;
	int cb,left;
	int res=0;
	int attr=0;

	fi=fopen(src, A_ReadOnly + A_BIN, P_READ, &err);
	if(fi!=-1) 
	{
		fo=fopen(dst, A_ReadWrite+A_BIN+A_Create+A_Truncate, P_READ+P_WRITE, &err);
		if(fo!=-1) 
		{

			left=lseek(fi, 0, S_END, &err, &err);
			lseek(fi, 0, S_SET, &err, &err);
			if(left)
			{
				buff=malloc(BUF_SIZE);
				if(!buff)
					goto L_EXIT;
			}
			while (left) 
			{
				cb=left<BUF_SIZE?left:BUF_SIZE;
				left-=cb;
				if(fread(fi, buff, cb, &err)!=cb) 
					goto L_EXIT;
				if(fwrite(fo, buff, cb, &err)!=cb) 
					goto L_EXIT;
			}
			res=1;
			GetFileAttrib(src, (unsigned char*)&attr, &err);
			SetFileAttrib(dst, attr, &err);
		}
	}
L_EXIT:
	if(buff) 
		mfree(buff);
	if(fo!=-1) 
		fclose(fo, &err);
	if(fi!=-1) 
		fclose(fi, &err);
	return res;
}

void configRestore(char *path);
void configBackUp(char *path);

int pathInputOnKey(GUI *data, GUI_MSG *msg)
{
	EDITCONTROL ec;
	char path[128];
	if(msg->keys==0xFFF)
	{
		ExtractEditControl(data,2,&ec);
		ws_2str(ec.pWS, path, 127);
		if(PATH_TYPE)
			configRestore(path);
		else
			configBackUp(path);
		return 1;
	}
	if((msg->gbsmsg->msg==KEY_DOWN)&&(msg->gbsmsg->submess==ENTER_BUTTON))
	{
		EDIT_OpenOptionMenuWithUserItems(data,on_sdec,data,1);
		return -1;
	}
	return 0;
}

void pathInputGHook(GUI *data, int cmd)
{
	if(cmd==0x0A)
		DisableIDLETMR();
	if(cmd==7)
		SetSoftKey(data, PATH_TYPE?&SK_RESTORE:&SK_BACKUP, SET_SOFT_KEY_N);
}

INPUTDIA_DESC PATH_INPUT_DESC=
{
  1,
  pathInputOnKey,
  pathInputGHook,
  (void *)info_locret,
  0,
  &mmenu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};

HEADER_DESC PATH_INPUT_HDR={0,0,0,0,NULL,(int)LGP_ENTER_PATH,LGP_NULL};

void pathInputDlg(void)
{
	void *ma=malloc_adr();
	void *eq;
	EDITCONTROL ec;
	WSHDR *ews;
	
	PrepareEditControl(&ec);
	eq=AllocEQueue(ma,mfree_adr());
	ews=AllocWS(128);
	wsprintf(ews, PERCENT_T, PATH_TYPE?LGP_RESTORE_PATH:LGP_BACKUP_PATH);
	ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
	AddEditControlToEditQend(eq,&ec,ma);
	
	if(PATH_TYPE)
		str_2ws(ews,"0:\\Misc\\Patches\\",127);
	else
	{
		TDate date;
		TTime time;
		GetDateTime(&date, &time);
		wsprintf(ews, "0:\\Misc\\Patches\\ptc_%d%02d%02d\\",date.year,date.month,date.day);
	}
	ConstructEditControl(&ec,ECT_CURSOR_STAY,ECF_APPEND_EOL,ews,128);
	AddEditControlToEditQend(eq,&ec,ma);
	
	patch_header(&PATH_INPUT_HDR);
	patch_input(&PATH_INPUT_DESC);
	CreateInputTextDialog(&PATH_INPUT_DESC,&PATH_INPUT_HDR,eq,1,0);
	FreeWS(ews);
}

void mkpath(char *path)
{
	unsigned int ferr;
	char temp[128];
	int len=strlen(path);
	int i=0;
	if(isdir(path, &ferr))
		return;
	for(;i<len;i++)
	{
		if(path[i]=='\\')
		{
			temp[i]=0;
			if(!isdir(temp, &ferr))
				mkdir(temp, &ferr);
		}
		temp[i]=path[i];
	}
	mkdir(path, &ferr);
}

void configBackUp(char *path)
{
	int len=strlen(path);
	DIR_ENTRY de;
	unsigned int ferr;
	char folder[128]=PATCH_DIR;
	char ptemp[128];
	char tp[128];
	char srcpath[128];
	mkpath(path);
	strcat(folder, PTC_FOLDR);
	strcpy(srcpath, folder);
	strcat(srcpath, "*.ptc");
	if(FindFirstFile(&de, srcpath, &ferr))
	{
		do
		{
			if(path[len-1]!='\\')
				sprintf(ptemp, "%s\\%s", path, de.file_name);
			else
				sprintf(ptemp, "%s%s", path, de.file_name);
			sprintf(tp, "%s%s", folder, de.file_name);
			fcopy(ptemp, tp);
		}while(FindNextFile(&de,&ferr));
	}
	FindClose(&de,&ferr);
}


void configRestore(char *path)
{
	unsigned int ferr;
	int len=strlen(path);
	DIR_ENTRY de;
	char ptemp[128];
	char folder[128]=PATCH_DIR;
	char tp[128];
	char srcpath[128];
	if(!(isdir(path, &ferr)))
		return;
	if(path[len-1]=='\\')
		sprintf(srcpath, "%s*.ptc", path);
	else
		sprintf(srcpath, "%s\\*.ptc", path);
	strcat(folder, PTC_FOLDR);
	if(FindFirstFile(&de, srcpath, &ferr))
	{
		do
		{
			sprintf(ptemp, "%s%s", folder, de.file_name);
			if(path[len-1]=='\\')
				sprintf(tp, "%s%s", path, de.file_name);
			else
				sprintf(tp, "%s\\%s", path, de.file_name);
			fcopy(ptemp, tp);
		}while(FindNextFile(&de,&ferr));
	}
	FindClose(&de,&ferr);
	fuckThemAll();
	patch_n=0;
	if(!getAllPatchData())
	{
		MsgBoxError(1, (int)LGP_RELOAD_CONFIG_ERR);
		CloseCSM(MAIN_CSM_ID);
	}
}
