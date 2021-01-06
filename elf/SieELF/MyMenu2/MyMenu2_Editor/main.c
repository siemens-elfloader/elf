#include "..\..\inc\swilib.h"
#include "type.h"
#include "rect_patcher.h"
#include "lang.h"



#define CFG_PATH	"0:\\ZBin\\etc\\MyMenu2.cfg"
#define CFG_PATH_DEBUG	"0:\\ZBin\\etc\\MyMenu2.cfg"

#define SP_CHAR		0x1F	//0x20
#define US_CHAR		0x1F
#define _80_CHAR	0x80

#define BUF_SIZE	(8*1024)
#define PATH_LEN	128
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



extern void kill_data(void *p, void (*func_p)(void *));
extern void show_option_menu(void);

void edit_ml(MENU_LIST *ml);

char *buf;
MENU_LIST *mltop;
unsigned int EDGUI_ID=0;
unsigned int MAIN_GUI_ID=0;
int menu_item_n=0;
WSHDR *ws_edit_nametmp;
WSHDR *ws_edit_functmp;
MENU_LIST *ml_edit_tmp;

const int menusoftkeys[]={0, 1, 2};

const SOFTKEY_DESC menu_sk[]=
{
	{0x0018,0x0000,(int)LGP_MENU},
	{0x0001,0x0000,(int)LGP_EXIT},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB menu_skt=
{
	menu_sk,0
};

const HEADER_DESC menuheader={0, 0, 0, 0, NULL, (int)ELFNAME, LGP_NULL};


void utf8_2str(char *str, char *utf8)
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

void AddtoMenuList(char *name, int name_len, char *func, int func_len, int type, int IsEdited)
{
	MENU_LIST *ml=malloc(sizeof(MENU_LIST));
	ml->next=0;
	ml->prev=0;
	ml->name=name;
	ml->name_len=name_len;
	ml->func=func;
	ml->func_len=func_len;
	ml->type=type;
	ml->IsEdited=IsEdited;
	if(!mltop)
	{
		mltop=ml;
	}
	else
	{
		MENU_LIST *ml_t=mltop;
		while(ml_t->next)
			ml_t=ml_t->next;
		ml_t->next=ml;
		ml->prev=ml_t;
	}
}

void FreeMenuList(void)
{
	if(mltop)
	{
		MENU_LIST *ml=mltop;
		MENU_LIST *ml_t;
		while(ml)
		{
			ml_t=ml->next;
			if(ml->IsEdited)
			{
				mfree(ml->name);
				mfree(ml->func);
			}
			mfree(ml);
			ml=ml_t;
		}
	}
}

MENU_LIST *get_mlitem(int curitem)
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

char *strchrinline(char *s, char chr)
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



char *gotoRealPos(char *p)
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

char *gotoLineEnd(char *p)
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

int CheckType(char *p)
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

int read_cfg(void)
{
	FreeMenuList();
	mltop=0; //必须初始化
	int f;
	char path[]=CFG_PATH;
	unsigned int err;
	if((f=fopen(path, A_ReadOnly, P_READ, &err))==-1)
	{
		path[0]='4';
		if((f=fopen(path, A_ReadOnly, P_READ, &err))==-1)
			return 0;
	}
	int size=0;
	size=fread(f, buf, BUF_SIZE, &err);
	fclose(f, &err);
	if(size<3)
		return 0;
	buf[size]=0;
	char *p=buf;
	int name_len;
	int func_len;
	int item_n=0;
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
			func_len=p2-pp;
			AddtoMenuList(p, name_len, pp, func_len, CheckType(pp), 0);
			p=p2;
		}
		else
		{
			pp=p;
			pp=gotoLineEnd(pp);
			func_len=pp-p;
			int type=CheckType(p);
			char *p2;
			switch(type)
			{
			case TYPE_ADDRESS:
			case TYPE_SHORTCUT:
				name_len=func_len;
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
					name_len=func_len;
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
			AddtoMenuList(p2, name_len, p, func_len, type, 0);
			p=pp;
		}
		item_n++;
		p=gotoRealPos(p);
	}
	return item_n;
}

void save_file(void)
{
	char temp[256];
	MENU_LIST *ml=mltop;
	int f;
	unsigned int err;
	if(!ml)
		return;
	if((f=fopen(CFG_PATH_DEBUG, A_ReadWrite+A_Create+A_Truncate+A_BIN, P_READ+P_WRITE, &err))==-1)
		return;
	//do
	while(ml)
	{
		if(ml==mltop)
		{
			temp[0]=0xEF; //UTF8 文件头
			temp[1]=0xBB;
			temp[2]=0xBF;
			fwrite(f, temp, 3, &err);
		}
		strncpy(temp, ml->name, ml->name_len);
		temp[ml->name_len]='|';
		temp[ml->name_len+1]=0;
		strncat(temp, ml->func, ml->func_len);
		temp[ml->name_len+1+ml->func_len]='\n';
		temp[ml->name_len+2+ml->func_len]=0;
		fwrite(f, temp, ml->name_len+2+ml->func_len, &err);
		ml=ml->next;
	}
	//while(ml=ml->next);
	fclose(f, &err);
}

void save_ml(void)
{
	char *name=malloc(128);
	char *func=malloc(128);
	int utf8conv_res_len;
	ws_2utf8(ws_edit_nametmp, name, &utf8conv_res_len, 128);
	ws_2str(ws_edit_functmp, func, 128);
	if (ml_edit_tmp)
	{
		if(ml_edit_tmp->IsEdited)
		{
			mfree(ml_edit_tmp->name);
			mfree(ml_edit_tmp->func);
		}
		ml_edit_tmp->name=name;
		ml_edit_tmp->func=func;
		ml_edit_tmp->name_len=strlen(name);
		ml_edit_tmp->func_len=strlen(func);
		ml_edit_tmp->type=CheckType(func);
		ml_edit_tmp->IsEdited=1;
	}
	ml_edit_tmp=0;
	save_file();
	//ShowMSG(1, (int)"Menu Changed");
}

int menu_onkey(void *data, GUI_MSG *msg)
{
	MENU_LIST *ml=get_mlitem(GetCurMenuItem(data));
	ml_edit_tmp=ml;
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
		int i=msg->gbsmsg->submess;
		switch(i)
		{
		case RIGHT_SOFT:
			return 1;
		case ENTER_BUTTON:
			if(ml)
			{
				edit_ml(ml);
			}
			return -1;
		case LEFT_SOFT:
			show_option_menu();
			return -1;
		case '*':
			ShowMSG(1, (int)COPYRIGHT);
			return 0;
		}
		if(i>='0'&&i<='9')
		{
			if(i=='0')
				i=9;
			else
				i-='1';
			ml=get_mlitem(i);
			if(ml)
			{
				edit_ml(ml);
			}
			return -1;
		}
	}
	return 0;
}

void menu_ghook(void *data, int cmd)
{
	if (cmd==0x0A)
		DisableIDLETMR();
	//if (cmd==3)
}

void menu_iconhndl(void *data, int curitem, void *unk)
{
	MENU_LIST *ml;
	void *item=AllocMenuItem(data);
	ml=get_mlitem(curitem);
	WSHDR *ws;
	if(ml)
	{
		ws=AllocMenuWS(data, ml->name_len+2);
		utf8_2ws(ws, ml->name, ml->name_len);
	}
	else
	{
		ws=AllocMenuWS(data,16);
		wsprintf(ws, _percent_t, ERR_STR);
	}
	//SetMenuItemIconArray(data, item, &MenuItenIcon);
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
	0x10,
	menu_iconhndl,
	NULL,   //Items
	NULL,   //Procs
	0   //n
};


void maincsm_oncreate(CSM_RAM *data)
{
	ws_edit_nametmp=AllocWS(128);
	ws_edit_functmp=AllocWS(128);
	buf=malloc(BUF_SIZE);
	MAIN_CSM *csm=(MAIN_CSM*)data;
	menu_item_n=read_cfg();
	patch_header(&menuheader);
	csm->gui_id=MAIN_GUI_ID=CreateMenu(0, 0, &main_menu, &menuheader, 0, menu_item_n, 0, 0);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	if (msg->msg==MSG_GUI_DESTROYED)
	{
		if ((int)msg->data0==csm->gui_id)
			csm->csm.state=-3;
		if ((int)msg->data0==EDGUI_ID)
		{
			if ((int)msg->data1==1)
			{
				save_ml();
				void *gui=FindGUIbyId(csm->gui_id, NULL);
				if (gui)
				{
					Menu_SetItemCountDyn(gui, menu_item_n);
					RefreshGUI();
				}
				//csm->gui_id=CreateMenu(0, 0, &main_menu, &menuheader, 0, menu_item_n, 0, 0);
			}
			EDGUI_ID=0;
		}
	}
	return(1);
}


void Killer(void)
{
	mfree(buf);
	FreeMenuList();
	FreeWS(ws_edit_functmp);
	FreeWS(ws_edit_nametmp);
	extern void *ELF_BEGIN;
	extern void kill_data(void *p, void (*func_p)(void *));
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
	SUBPROC((void *)Killer);
}

const int minus11=-11;
const unsigned short maincsm_name_body[140];

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

void UpdateCSMname(void)
{
	wsprintf((WSHDR *)(&MAINCSM.maincsm_name), ELFNAME);
}

int main(void)
{
	char dummy[sizeof(MAIN_CSM)];
	UpdateCSMname();
	LockSched();
	CreateCSM(&MAINCSM.maincsm,dummy,0);
	UnlockSched();
	return 0;
}


