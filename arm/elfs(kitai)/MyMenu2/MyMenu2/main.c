#include "..\..\inc\swilib.h"

#define COPYRIGHT	"MyMenu2\n(c)BingK(binghelingxi)"
#define ELFNAME		"MyMenu2"
//#define SK_SELECT	"Select"
//#define SK_BACK	"Back"
#define ERR_STR		"Error!"
#define CFG_PATH	"0:\\ZBin\\etc\\MyMenu2.cfg"
#define ELF_PATH	"0:\\ZBin\\utilities\\MyMenu2_Editor.elf"

#define LGP_SELECT	"选择"
#define LGP_EXIT	"离开"
//#define LGP_SELECT	0x39
//#define LGP_EXIT	0x28F

#define SP_CHAR		0x1F	//0x20
#define US_CHAR		0x1F
#define _80_CHAR	0x80

#define BUF_SIZE	(8*1024)
#define PATH_LEN	128
//#define menu_item_n	16
#define ADDR_LEN	8

#define FUNC_PT_START	0xA085DEA4
#define FUNC_PT_END	0xA0865BA3
#define FUNC_PT_PSIZE	0x80
#define FUNC_PT_OFFSET	0x10
#define MAX_FUNC	0xFA

#define TYPE_FILE	0
#define TYPE_SHORTCUT	1
#define TYPE_ADDRESS	2
#define TYPE_FOLDER	3

#define CHARSET_GB2312	0
#define CHARSET_UTF8	1
#define CHARSET_UNICODE	2

#ifdef ELKA
#define HEADER_X1	0
#define HEADER_Y1	24
#define HEADER_X2	239
#define HEADER_Y2	56
#else
#define HEADER_X1	0
#define HEADER_Y1	0
#define HEADER_X2	131
#define HEADER_Y2	0x16
#endif

#ifdef VKP
#ifdef ELKA
#define MENU_HEADER_ICON	0x491
#define MENU_ITEM_ICON		0x538
#else
#define MENU_HEADER_ICON	0x4BB
#define MENU_ITEM_ICON		0x564
#endif
const int MenuHeaderIcon[]={MENU_HEADER_ICON,0};
const int MenuItemIcon[]={MENU_ITEM_ICON,0};
#endif

//UTF8
//短信计数器|0:\ZBin\utilities\SMSCountReader.elf
typedef struct
{
	void *next;
	char *name;
	int name_len;
	char *path;
	int path_len;
	int type;
}MENU_LIST;

typedef struct
{
	CSM_RAM csm;
	int gui_id;
	char *buf;
	MENU_LIST *mltop;
}MAIN_CSM;
//char *buf;
//MENU_LIST *mltop;
//int char_set;

const int menusoftkeys[]={0, 1, 2};

const SOFTKEY_DESC menu_sk[]=
{
	{0x0018,0x0000,(int)LGP_SELECT},
	{0x0001,0x0000,(int)LGP_EXIT},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
	menu_sk,0
};

#ifdef VKP
const HEADER_DESC menuheader={HEADER_X1, HEADER_Y1, HEADER_X2, HEADER_Y2, (int *)MenuHeaderIcon, (int)ELFNAME, LGP_NULL};
#define PROCESSOR_MODE __thumb
#else
const HEADER_DESC menuheader={HEADER_X1, HEADER_Y1, HEADER_X2, HEADER_Y2, NULL, (int)ELFNAME, LGP_NULL};
#define PROCESSOR_MODE __arm
#endif

PROCESSOR_MODE void utf8_2str(char *str, char *utf8)
{
	
	char *p=utf8;
	int i=0;
	while(*p)
	{
		if(*p>=_80_CHAR)
			break;
		str[i]=*p;
		p++;
		i++;
	}
	if(*p)
	{
		if(str[i-1]!=US_CHAR)
		{
			str[i]=US_CHAR;
			i++;
		}
		while(*p)
		{
			str[i]=*p;
			p++;
			i++;
		}
	}
	str[i]=0;
}

PROCESSOR_MODE void AddtoMenuList(MAIN_CSM *csm, char *name, int name_len, char *path, int path_len,int type)
{
	MENU_LIST *ml=malloc(sizeof(MENU_LIST));
	ml->next=0;
	ml->name=name;
	ml->name_len=name_len;
	ml->path=path;
	ml->path_len=path_len;
	ml->type=type;
	if(!csm->mltop)
	{
		csm->mltop=ml;
	}
	else
	{
		MENU_LIST *ml_t=csm->mltop;
		while(ml_t->next)
			ml_t=ml_t->next;
		ml_t->next=ml;
	}
}

PROCESSOR_MODE void FreeMenuList(MAIN_CSM *csm)
{
	if(csm->mltop)
	{
		MENU_LIST *ml=csm->mltop;
		MENU_LIST *ml_t;
		while(ml)
		{
			ml_t=ml->next;
			mfree(ml);
			ml=ml_t;
		}
	}
	csm->mltop=0;
}

PROCESSOR_MODE MENU_LIST *get_mlitem(MENU_LIST *mltop, int curitem)
{
	MENU_LIST *ml;
	ml=mltop;
	int i=0;
	while(ml)
	{
		if(i==curitem)
			return (ml);
			//break;
		i++;
		ml=ml->next;
	}
	return 0;
}

PROCESSOR_MODE char *strchrinline(char *s, char chr)
{
	char *p=s;
	char *t=0;
	while(*p)
	{
		//if((*p==0x0D)||(*p==0x0A))
		if(*p<SP_CHAR)
			break;
		if(*p==chr)
			t=p;
		p++;
	}
	return (t);
}



PROCESSOR_MODE char *gotoRealPos(char *p)
{
	char *pp=p;
	while(*pp)
	{
		if(*pp>=SP_CHAR)
			break;
		pp++;
	}
	return pp;
}

PROCESSOR_MODE char *gotoLineEnd(char *p)
{
	char *pp=p;
	while(*pp)
	{
		if(*pp<SP_CHAR)
			break;
		pp++;
	}
	return pp;
}

PROCESSOR_MODE int CheckType(char *p)
{
	char *pp=p;
	if((*(p+1)!=':')&&(*(p+2)!='\\')) //':\'
	{
		if((*p=='A')&&((*(p+1)=='0')||(*(p+1)=='1'))) //A0,A1
			return TYPE_ADDRESS;
		else
			return TYPE_SHORTCUT;
	}
	pp=gotoLineEnd(pp);
	if(*(pp-1)=='\\')
		return TYPE_FOLDER;
	return TYPE_FILE;
}

PROCESSOR_MODE int read_cfg(MAIN_CSM *csm)
{
	int f;
	char path[]=CFG_PATH;
	unsigned int err;
	char *p;
	int name_len;
	int path_len;
	int item_n=0;
	int size=0;
	//MAIN_CSM *csm=(MAIN_CSM*)data;
	p=csm->buf;
	FreeMenuList(csm);
	csm->mltop=0; //必须初始化
	if((f=fopen(path, A_ReadOnly, P_READ, &err))==-1)
	{
		path[0]='4';
		if((f=fopen(path, A_ReadOnly, P_READ, &err))==-1)
			return 0;
	}
	size=fread(f, csm->buf, BUF_SIZE, &err);
	fclose(f, &err);
	if(size<3)
		return 0;
	csm->buf[size]=0;
	//if(*p==0xEF && *(p+1)==0xBB && *(p+2)==0xBF)
	//{
	//	char_set=CHARSET_UTF8;
	//	p+=3;
	//}
	//else if(*p==0xFF && *(p+1)==0xFE && *(p+2)==0xED)
	//{
	//	char_set=CHARSET_UNICODE;
	//	p+=3;
	//}
	//else
	//	char_set=CHARSET_GB2312;
	while(*p)
	{
		p=gotoRealPos(p);
		char *pp=strchrinline(p, '|');
		if(pp)
		{
			name_len=pp-p;
			pp++; // '|'
			pp=gotoRealPos(pp);
			char *p2=pp;
			p2=gotoLineEnd(p2);
			path_len=p2-pp;
			AddtoMenuList(csm, p, name_len, pp, path_len, CheckType(pp));
			p=p2;
		}
		else
		{
			pp=p;
			pp=gotoLineEnd(pp);
			path_len=pp-p;
			int type=CheckType(p);
			char *p2;
			switch(type)
			{
			case TYPE_ADDRESS:
			case TYPE_SHORTCUT:
				name_len=path_len;
				p2=p;
				break;
			case TYPE_FILE:
			{
				p2=strchrinline(p, '\\');
				char *p3=strchrinline(p, '.');
				if(p2)
				{
					p2++;
					if(p3)
						name_len=p3-p2;
					else
						name_len=pp-p2;
				}
				else
				{
					name_len=path_len;
					p2=p;
				}
				break;
			}
			case TYPE_FOLDER:
			{
				//p2=strchrinline(p, '\\');
				char *p3=strchrinline(p, '\\');
				p2=p3-1;
				do
				{
					if(*p2=='\\')
						break;
					p2--;
				}
				while(*p2>=SP_CHAR);
				p2++;
				name_len=p3-p2;
				break;
			}
			}
			AddtoMenuList(csm, p2, name_len, p, path_len, type);
			p=pp;
		}
		item_n++;
		p=gotoRealPos(p);
	}
	return item_n;
}

#pragma inline=forced
PROCESSOR_MODE int toupper(int c)
{
	if ((c>='a')&&(c<='z')) c+='A'-'a';
	return(c);
}

PROCESSOR_MODE int strncmpNoCase(const char *s1,const char *s2,unsigned int n)
{
	int i;
	int c;
	while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
	return(i);
}

#ifdef NEWSGOLD
PROCESSOR_MODE unsigned int GetFunctionPointByName(char *name)
{
	char *p=(char *)FUNC_PT_START;
	int len=strlen(name);
	if(len==0)
		return 0;
	while((char *)FUNC_PT_END-p>0)
	{
		if(!strncmpNoCase(p, name, len))
			return (*(unsigned int *)(p+FUNC_PT_OFFSET));
		p+=FUNC_PT_PSIZE;
	}
	return 0;
}
#endif

PROCESSOR_MODE void run_address(unsigned int address) 
{
	void (*runaddr)(void);
	runaddr=(void (*)())address;
	if (runaddr) 
	{
		runaddr();
	}
}

PROCESSOR_MODE void run_shortcut(char *shortcut) 
{
#ifdef NEWSGOLD
	run_address(GetFunctionPointByName(shortcut));
#else
	run_address((unsigned int)GetFunctionPointer(shortcut));
#endif
}

PROCESSOR_MODE int chr2num(char chr)
{
	if(chr>='0'&&chr<='9')
		return (chr-('0'-0));
	if(chr>='A'&&chr<='Z')
		//return (chr-0x37);
		return (chr-('A'-0xA));
	if(chr>='a'&&chr<='z')
		//return (chr-0x57);
		return (chr-('a'-0xA));
	return 0;
}

void run_file(MENU_LIST *ml);
void run_folder(MENU_LIST *ml);

PROCESSOR_MODE void run_ml(MENU_LIST *ml)
{
	switch(ml->type)
	{
	case TYPE_FILE:
		run_file(ml);
		break;
	case TYPE_SHORTCUT:
	{
		char ShortCut[32];
		char *p=ml->path;
		int i=0;
		int j=0;
		for(;j<ml->path_len;j++)
		{
			if(p[j]>='A')
			{
				ShortCut[i]=p[j];
				i++;
			}
			
		}
		ShortCut[i]=0;
		run_shortcut(ShortCut);
		break;
	}
	case TYPE_ADDRESS:
	{
		if(ml->path_len==ADDR_LEN)
		{
			int i;
			unsigned int addr=0;
			char *p=ml->path;
			for(i=0;i<ADDR_LEN;i++)
			{
				addr=chr2num(p[i])+addr*0x10;
			}
			run_address(addr);
		}
		break;
	}
	case TYPE_FOLDER:
		run_folder(ml);
		break;
	}
}
/*
typedef struct
{
  int mode; //0-normal mode, 1-select mode 
  int dir_enum; //0x26 by default
  WSHDR* path_to_file; //path to file
  WSHDR* file_name; //put cursor to this file
  int unk5;
  int is_exact_dir;
  int unk7;
  int unk8;
  int unk9; // _1
  int unk10;
  int unk11;
  WSHDR* full_filename;
  int unk13;
  int (*user_handler)(void*); //called in select mode
  void* this_struct_addr;
  int unk16;
  int unk17_26[10]; 
}NativeExplorerData;*/

//by benj9
// all params: if 0, not applied
//exp_mode		equ		0	; 0=normal, 1=file selection, 3+4=folder selection
//exp_def_folder	equ		4	; eg. 1=sound, 9=pictures. 0x26: use folder in st_exp_cust_folder_ws
//exp_cust_folder_ws	equ		8	; if st_exp_def_folder=0x26, use base folder stored in this ws
//exp_preselection_ws	equ		0xC	; start selection in explorer with file/folder stored in ws
//exp_lock_navigation	equ		0x14	; if 1, lock navigation with drives and higher folders
//exp_1			equ		0x20	; always 1
//exp_filter_start	equ		0x24	; func checks files/folders to be shown at start
//exp_dest_ws		equ		0x2C	; dest file/folder (if mode >0)
//exp_filter_scroll	equ		0x34	; func checks files to be shown by scrolling
//exp_report_csm	equ		0x38	; *csm to report about everything

//#pragma swi_number=0x254
//__swi __arm int StartNativeExplorer(NativeExplorerData* data);


void strpath_2ws(WSHDR *ws, char *path, int len)
{
	char utf8[PATH_LEN];
	char str[PATH_LEN];
	strncpy(utf8, path, len);
	utf8[len]=0;
	utf8_2str(str, utf8);
	str_2ws(ws, str, PATH_LEN);
}

void run_folder(MENU_LIST *ml)
{
	WSHDR *ws=AllocWS(PATH_LEN);
	strpath_2ws(ws, ml->path, ml->path_len);
	NativeExplorerData data;
	zeromem(&data,sizeof(NativeExplorerData));
	data.mode=0;
	data.dir_enum=0x26;
	data.path_to_file=ws;
	data.is_exact_dir=1;
	data.full_filename=ws;
	data.unk9=1;
	//data.this_struct_addr=&data;
	StartNativeExplorer(&data);
	FreeWS(ws);
}

void run_file(MENU_LIST *ml)
{
	//char utf8[PATH_LEN];
	//char str[PATH_LEN];
	//strncpy(utf8, ml->path, ml->path_len);
	//utf8[ml->path_len]=0;
	//utf8_2str(str, utf8);
	WSHDR *ws=AllocWS(PATH_LEN);
	strpath_2ws(ws, ml->path, ml->path_len);
	//str_2ws(ws, str, PATH_LEN);
	ExecuteFile(ws, 0, 0);
	FreeWS(ws);
}
void run_mymenu2_editor(void)
{
	WSHDR *ws=AllocWS(PATH_LEN);
	char elf_path[]=ELF_PATH;
	strpath_2ws(ws, elf_path, strlen(elf_path));
	ExecuteFile(ws, 0, 0);
	FreeWS(ws);
}

int menu_onkey(void *data, GUI_MSG *msg)
{
	MAIN_CSM *csm=MenuGetUserPointer(data);
	MENU_LIST *ml=get_mlitem(csm->mltop, GetCurMenuItem(data));
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
		int i=msg->gbsmsg->submess;
		switch(i)
		{
		case RIGHT_SOFT:
			return 1;
		case ENTER_BUTTON:
		case LEFT_SOFT:
			if(ml)
				run_ml(ml);
			return 0;
		case '*':
			ShowMSG(1, (int)COPYRIGHT);
			return 0;
		case '#':
			run_mymenu2_editor();
			return 1;
		}
		if(i>='0'&&i<='9')
		{
			if(i=='0')
				i=9;
			else
				i-='1';
			ml=get_mlitem(csm->mltop, i);
			if(ml)
				run_ml(ml);
			return 0;
		}
		//if(i=='*')
		//{
		//	ShowMSG(1, (int)CP_MSG);
		//	return 0;
		//}
	}
	return 0;
}

void menu_ghook(void *data, int cmd)
{
	if (cmd==0x0A)
		DisableIDLETMR();
}

void menu_iconhndl(void *data, int curitem, void *unk)
{
	MENU_LIST *ml;
	MAIN_CSM *csm=MenuGetUserPointer(data);
	void *item=AllocMenuItem(data);
	ml=get_mlitem(csm->mltop, curitem);
	WSHDR *ws;
	if(ml)
	{
		ws=AllocMenuWS(data, ml->name_len+2);
		utf8_2ws(ws, ml->name, ml->name_len);
	}
	else
	{
		ws=AllocMenuWS(data,16);
		wsprintf(ws,ERR_STR);
	}
	#ifdef VKP
	SetMenuItemIconArray(data, item, MenuItemIcon);
	#endif
	SetMenuItemText(data,item,ws,curitem);
}

const MENU_DESC main_menu=
{
	8,
	menu_onkey,
	menu_ghook,
	NULL,
	menusoftkeys,
	&menu_skt,
#ifdef	VKP
	0x11,
#else
	0x10,
#endif
	menu_iconhndl,
	NULL,   //Items
	NULL,   //Procs
	0   //n
};

void maincsm_oncreate(CSM_RAM *data)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	csm->buf=malloc(BUF_SIZE);
	csm->mltop=0; //必须初始化
	csm->gui_id=CreateMenu(0, 0, &main_menu, &menuheader, 0, read_cfg(csm), csm, 0);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
	{
		csm->csm.state=-3;
	}
	return(1);
}

void Killer(MAIN_CSM *csm)
{
#ifdef VKP
/*	buf=0; //退出时将RAM地址置零
	mltop=0;*/
#else
	extern void *ELF_BEGIN;
	extern void kill_data(void *p, void (*func_p)(void *));
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
#endif
}

void maincsm_onclose(CSM_RAM *data)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	mfree(csm->buf);
	FreeMenuList(csm);
#ifndef	VKP
	SUBPROC((void *)Killer,csm);
#endif
}

const int minus11=-11;
const unsigned short maincsm_name_body[16]={7,'M', 'y', 'M', 'e', 'n', 'u', '2'};

const struct
{
	CSM_DESC maincsm;
	WSHDR maincsm_name;
}MAINCSM =
{
	{
		maincsm_onmessage,
		maincsm_oncreate,
#ifdef NEWSGOLD
		0,
		0,
		0,
		0,
#endif
		maincsm_onclose,
		sizeof(MAIN_CSM),
		1,
		&minus11
	},
	{
		(unsigned short *)maincsm_name_body,
		NAMECSM_MAGIC1,
		NAMECSM_MAGIC2,
		0x0,
		139
	}
};

#ifndef VKP
void UpdateCSMname(void)
{
	wsprintf((WSHDR *)(&MAINCSM.maincsm_name), ELFNAME);
}
#endif

int main(void)
{
#ifdef VKP
/*	if(buf||mltop) //检测是否已经有mymenu启动
	{
		MsgBoxError(1, (int)ERR_STR);
		return 0;
	}*/
#endif
	char dummy[sizeof(MAIN_CSM)];
	zeromem(dummy, sizeof(MAIN_CSM));
#ifndef VKP
	UpdateCSMname();
#endif
	LockSched();
	CreateCSM(&MAINCSM.maincsm,dummy,0);
	UnlockSched();
	return 0;
}

