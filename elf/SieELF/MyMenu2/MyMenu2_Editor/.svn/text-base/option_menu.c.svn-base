#include "..\..\inc\swilib.h"
#include "type.h"
#include "rect_patcher.h"
#include "lang.h"

extern void save_file(void);
extern int menu_item_n;
extern MENU_LIST *ml_edit_tmp;
extern MENU_LIST *mltop;
extern void edit_ml(MENU_LIST *ml);
extern unsigned int MAIN_GUI_ID;
extern void AddtoMenuList(char *name, int name_len, char *func, int func_len, int type, int IsEdited);


#define MAIN_MENU_ITEMS_N 6

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

const HEADER_DESC option_menu_header={0, 0, 0, 0,NULL,(int)LGP_OPTIONS,LGP_NULL};

int option_menu_keyhook(void *data, GUI_MSG *msg)
{
	return(0);
}

void option_menu_ghook(void *data, int cmd)
{
	if (cmd==0x0A)
	{
		DisableIDLETMR();
	}
}

void menu_edit(GUI *gui)
{
	edit_ml(ml_edit_tmp);
	GeneralFuncF1(1);
}

void menu_add(GUI *gui)
{
	MENU_LIST *ml=malloc(sizeof(MENU_LIST));
	char *name=malloc(128);
	char *func=malloc(128);
	ml->next=0;
	ml->prev=0;
	ml->name=name;
	ml->func=func;
	ml->name_len=0;
	ml->func_len=0;
	ml->type=0;
	ml->IsEdited=1;
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
	menu_item_n++;
	edit_ml(ml);
	GeneralFuncF1(1);
}

void menu_insert(GUI *gui)
{
	MENU_LIST *ml=malloc(sizeof(MENU_LIST));
	char *name=malloc(128);
	char *func=malloc(128);
	ml->next=0;
	ml->prev=0;
	ml->name=name;
	ml->func=func;
	ml->name_len=0;
	ml->func_len=0;
	ml->type=0;
	ml->IsEdited=1;
	if (ml_edit_tmp)
	{
		MENU_LIST *ml_t=ml_edit_tmp->next;
		ml->next=ml_t;
		ml_edit_tmp->next=ml;
		ml->prev=ml_edit_tmp;
		if(ml_t)
			ml_t->prev=ml;
	}
	else
	{
		if (!mltop)
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
	menu_item_n++;
	edit_ml(ml);
	GeneralFuncF1(1);
}

void menu_del(GUI *gui)
{
	void *igui;
	if (ml_edit_tmp==mltop)
	{
		mltop=ml_edit_tmp->next;
		mltop->prev=0;
		if(ml_edit_tmp->IsEdited)
		{
			mfree(ml_edit_tmp->name);
			mfree(ml_edit_tmp->func);
		}
		mfree(ml_edit_tmp);
		ml_edit_tmp=mltop;
	}
	else if (ml_edit_tmp)
	{
		MENU_LIST *ml_n=ml_edit_tmp->next;
		MENU_LIST *ml_p=ml_edit_tmp->prev;
		if(ml_edit_tmp->IsEdited)
		{
			mfree(ml_edit_tmp->name);
			mfree(ml_edit_tmp->func);
		}
		if(ml_p)
			ml_p->next=ml_n;
		if(ml_n)
			ml_n->prev=ml_p;
		mfree(ml_edit_tmp);
		ml_edit_tmp=ml_p;
	}
	else
		goto end;
	if (menu_item_n)
		menu_item_n--;
	save_file();
	igui=FindGUIbyId(MAIN_GUI_ID, NULL);
	if (igui)
	{
		Menu_SetItemCountDyn(igui, menu_item_n);
		RefreshGUI();
	}
end:
	GeneralFuncF1(1);
}

void menu_moveup(GUI *gui)
{
	MENU_LIST *ml_n;
	MENU_LIST *ml_p;
	void *igui;
	if (ml_edit_tmp==mltop)
		goto end;
	if (!ml_edit_tmp)
		goto end;
	ml_p=ml_edit_tmp->prev;
	if(!(ml_n=ml_edit_tmp->next))
		ml_p->next=0;
	else
	{	ml_n->prev=ml_p;
		ml_p->next=ml_n;
	}
	if(ml_p==mltop)
	{
		mltop=ml_edit_tmp;
		ml_edit_tmp->prev=0;
		ml_edit_tmp->next=ml_p;
		ml_p->prev=ml_edit_tmp;
	}
	else
	{
		MENU_LIST *ml=ml_p->prev;
		ml->next=ml_edit_tmp;
		ml_edit_tmp->next=ml_p;
		ml_edit_tmp->prev=ml;
		ml_p->prev=ml_edit_tmp;
	}
	save_file();
	igui=FindGUIbyId(MAIN_GUI_ID, NULL);
	if (igui)
	{
		RefreshGUI();
	}
end:
	GeneralFuncF1(1);
}


void menu_movedown(GUI *gui)
{
	MENU_LIST *ml_n;
	MENU_LIST *ml_p;
	void *igui;
	if (!ml_edit_tmp)
		goto end;
	if(!(ml_n=ml_edit_tmp->next))
		goto end;
	ml_p=ml_edit_tmp->prev;
	if(ml_edit_tmp==mltop)
	{
		mltop=ml_n;
		ml_n->prev=0;
	}
	else
	{
		ml_n->prev=ml_p;
		ml_p->next=ml_n;
	}
	if(!(ml_n->next))
	{
		ml_edit_tmp->next=0;
		ml_n->next=ml_edit_tmp;
		ml_edit_tmp->prev=ml_n;
	}
	else
	{
		MENU_LIST *ml=ml_n->next;
		ml->prev=ml_edit_tmp;
		ml_edit_tmp->next=ml;
		ml_edit_tmp->prev=ml_n;
		ml_n->next=ml_edit_tmp;
	}
	save_file();
	igui=FindGUIbyId(MAIN_GUI_ID, NULL);
	if (igui)
	{
		RefreshGUI();
	}
end:
	GeneralFuncF1(1);
}

const MENUPROCS_DESC option_menu_HNDLS[MAIN_MENU_ITEMS_N]=
{
	menu_edit,
	menu_add,
	menu_insert,
	menu_del,
	menu_moveup,
	menu_movedown
};

const MENUITEM_DESC option_menu_ITEMS[MAIN_MENU_ITEMS_N]=
{
	{NULL,(int)LGP_EDIT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_ADD,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_INSERT,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DELETE,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_UP,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
	{NULL,(int)LGP_DOWN,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENU_DESC option_menu=
{
	8,option_menu_keyhook,option_menu_ghook,NULL,
	mmenusoftkeys,
	&mmenu_skt,
	0x10,//MENU_FLAG,
	NULL,
	option_menu_ITEMS,//menuitems,
	option_menu_HNDLS,//menuprocs,
	MAIN_MENU_ITEMS_N
};

void show_option_menu(void)
{
	patch_header(&option_menu_header);
	CreateMenu(0, 0, &option_menu, &option_menu_header, 0, MAIN_MENU_ITEMS_N, 0, 0);
}
