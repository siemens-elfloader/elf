#include "..\..\inc\swilib.h"
#include "sms_dat.h"
#include "rect_patcher.h"
#include "language.h"
#include "adrList.h"
#include "guiIdMan.h"
#include "main.h"
#include "edGui.h"
#include "createMenu.h"
#include "numList.h"
#include "MySMSYS_ipc.h"
#include "lgp_pic.h"
#include "CodeShow.h"
#include "popGui.h"
#include "config_data.h"
#include "string_works.h"
#include "NewDatReader.h"
#include "template.h"
#include "NativeAddressbook.h"
#include "CSMswaper.h"
#ifdef	LANG_CN
#define TEXT_INPUT_OPTION	ECT_CURSOR_STAY
#else
#define	TEXT_INPUT_OPTION	ECT_NORMAL_TEXT
#endif

HEADER_DESC ED_HDR={0,0,0,0,NULL,LGP_NULL,LGP_NULL};
const int ed_menusoftkeys[]={0,1,2};
SOFTKEY_DESC ed_menu_sk[]=
{
	{0x0018,0x0000,(int)LGP_NULL},
	{0x0001,0x0000,(int)LGP_NULL},
	{0x003D,0x0000,(int)LGP_DOIT_PIC}
};
const SOFTKEYSTAB ed_menu_skt=
{
	ed_menu_sk,0
};

HEADER_DESC ed_menuhdr={0,0,0,0,NULL,LGP_NULL/*(int)ELFNAME*/,LGP_NULL};

void ed_menu_reply(GUI *gui)
{
	int update=0;
	void *ed_gui=MenuGetUserPointer(gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)uo->dlg_csm;
	SGUI_ID *gstop=(SGUI_ID *)dlg_csm->gstop;
	if(gstop->id==dlg_csm->gui_id)
		update=1;
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	if(uo->sd)
	{
		if(uo->gui_type==ED_FVIEW)
		{
			SMS_DATA *sd=SdCopyOne(uo->sd);
			if(update)
				dlg_csm->gui_id=createEditGUI(dlg_csm, sd, ED_FREPLY, 0);
			else
				createEditGUI(dlg_csm, sd, ED_FREPLY, 0);
		}
		else
		{
			if(update)
				dlg_csm->gui_id=createEditGUI(dlg_csm, uo->sd, ED_REPLY, 0);
			else
				createEditGUI(dlg_csm, uo->sd, ED_REPLY, 0);
		}
	}
	GeneralFuncF1(1);
}

void ed_menu_edit(GUI *gui)
{
	int update=0;
	void *ed_gui=MenuGetUserPointer(gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)uo->dlg_csm;
	SGUI_ID *gstop=(SGUI_ID *)dlg_csm->gstop;
	if(gstop->id==dlg_csm->gui_id)
		update=1;
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	if(uo->sd)
	{
		if(uo->gui_type==ED_FVIEW)
		{
			SMS_DATA *sd=SdCopyOne(uo->sd);
			if(update)
				dlg_csm->gui_id=createEditGUI(dlg_csm, sd, ED_FEDIT, 0);
			else
				createEditGUI(dlg_csm, sd, ED_FEDIT, 0);
		}
		else
		{
			if(update)
				dlg_csm->gui_id=createEditGUI(dlg_csm, uo->sd, ED_EDIT, 0);
			else
				createEditGUI(dlg_csm, uo->sd, ED_EDIT, 0);
		}
	}
	GeneralFuncF1(1);
}

void ed_menu_exit(GUI *gui)
{
	void *ed_gui=MenuGetUserPointer(gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	GeneralFuncF1(1);
}

void ed_menu_del(GUI *gui)
{
	void *ed_gui=MenuGetUserPointer(gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);	
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	if(uo->sd)
	{
		if(uo->sd->isfile)
			deleteFile(uo->sd, 0);
		else
			deleteDat(uo->sd, 0);
		if(uo->gui_type!=ED_FVIEW) delSDList(uo->sd);
	}
	GeneralFuncF1(1);
}

int IsFileInArchive(const char *fpath);
void ed_menu_save_as_file(GUI *gui)
{
  void *ed_gui=MenuGetUserPointer(gui);
  USER_OP *uo=EDIT_GetUserPointer(ed_gui);
  DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
  SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);	
  if((uo->sd!=0)&&(uo->sd->isfile==0)&&(uo->sd->SMS_TEXT))
  {
    char time[32];
    char sdnum[32];
    SMS_DATA *sdx;
    WSHDR *ws=AllocWS(MAX_TEXT);
    wstrcpy(ws, uo->sd->SMS_TEXT);
    strcpy(time, uo->sd->Time);
    strcpy(sdnum, uo->sd->Number);
    if(saveFile(uo->sd->SMS_TEXT, uo->sd->Number, uo->sd, uo->sd->type, 2))
    {
      deleteDat(uo->sd, 0);
      delSDList(uo->sd);
      if(!(sdx=FindSdByTxtTimeNum(ws, time, sdnum))) //重新查找sd失败,直接返回列表
      {
	if(gstop!=0)
	{
	  GeneralFunc_flag1(gstop->id, 1);
	  popGS(dlg_csm);
	}
	else
	{
	  //如果完全出错,直接退出
	  GeneralFunc_flag1(dlg_csm->gui_id, 1);
	}
      }
      else
      {
	uo->sd=sdx;
	if(uo->sd->isfile)
	{
	  if(uo->sd->fname && IsFileInArchive(uo->sd->fname))
	    uo->dat_type=ARCHIVE_FILE;
	  else
	    uo->dat_type=NML_FILE;
	}
	else uo->dat_type=NML_DAT;
      }
    }
    FreeWS(ws);
  }
  GeneralFuncF1(1);
} 

void ed_menu_move_to_archive(GUI *gui)
{
	void *ed_gui=MenuGetUserPointer(gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);	
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	if(uo->sd)
	{
		int k=MoveToArchive(uo->sd);
		if(k==1)
		{
			if(!uo->sd->isfile) deleteDat(uo->sd, 0);
			if(uo->gui_type!=ED_FVIEW) delSDList(uo->sd);
		}
		else
			ShowFileErrCode(k);
	}
	GeneralFuncF1(1);
}

void ed_menu_export_txt(GUI *gui)
{
	void *ed_gui=MenuGetUserPointer(gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	if(uo->sd)
	{
		ShowFileErrCode(ExportOneToTxt(uo->sd));
	}
	GeneralFuncF1(1);
}

#define LGP_SAVE_TO_AB 0xD50

void ed_menu_save_ab(GUI *gui)
{
	void *ed_gui=MenuGetUserPointer(gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	CreateNAbCSM(uo->dlg_csm, ed_gui, TYPE_SAVE);
	GeneralFuncF1(1);
}

int Ed_SendSMS(void *gui);
void ed_menu_send(GUI *gui)
{
	void *ed_gui=MenuGetUserPointer(gui);
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(dlg_csm);
	}
	if(Ed_SendSMS(ed_gui)) DoSendBackGround(dlg_csm);
	GeneralFuncF1(1);
}

#define MENU_N_NML_FILE 7
#define MENU_N_NML_DAT 8
#define MENU_N_ARCHIVE_FILE 6

const MENUPROCS_DESC procs_nml_file[MENU_N_NML_FILE]=
{
	ed_menu_reply,
	ed_menu_edit,
	ed_menu_del,
	ed_menu_save_ab,
	ed_menu_export_txt,
	ed_menu_move_to_archive,
	ed_menu_exit,
};

int items_lgp_nml_file[MENU_N_NML_FILE]=
{
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_SAVE_TO_AB,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
};


const MENUPROCS_DESC procs_nml_dat[MENU_N_NML_DAT]=
{
	ed_menu_reply,
	ed_menu_edit,
	ed_menu_del,
	ed_menu_save_ab,
	ed_menu_save_as_file,
	ed_menu_export_txt,
	ed_menu_move_to_archive,
	ed_menu_exit,
};

int items_lgp_nml_dat[MENU_N_NML_DAT]=
{
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_SAVE_TO_AB,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
};

const MENUPROCS_DESC procs_archive_file[MENU_N_ARCHIVE_FILE]=
{
	ed_menu_reply,
	ed_menu_edit,
	ed_menu_del,
	ed_menu_save_ab,
	ed_menu_export_txt,
	ed_menu_exit,
};

int items_lgp_archive_file[MENU_N_ARCHIVE_FILE]=
{
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_SAVE_TO_AB,
	(int)LGP_NULL,
	(int)LGP_NULL,
};

int IsFileInArchive(const char *fpath)
{
  int len,c;
  char folder[128];
  strcpy(folder, CFG_MAIN_FOLDER);
  len=strlen(folder);
  c=folder[len-1];
  if(c!='\\' && c!='/')
  {
    folder[len]='\\';
    folder[len+1]=0;
  }
  strcat(folder, FLDR_ARCHIVE);
  if(!strncmp(fpath, folder, strlen(folder)))
    return 1;
  return 0;
}

#ifndef WITHOUT_OP_ICON

#ifdef NEWSGOLD
#ifdef ELKA
int ed_menu_item_icons[]={0x538,0};
#else
#ifdef S68
int ed_menu_item_icons[]={0x576,0};
#else
int ed_menu_item_icons[]={0x564,0};
#endif
#endif
#endif

#endif

void ed_menu_itemhndl(void *data, int curitem, void *user_pointer)
{
  void *ed_gui=MenuGetUserPointer(data);
  USER_OP *uo=EDIT_GetUserPointer(ed_gui);
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 150);
  if(curitem==0 && uo->sd && uo->sd->type==TYPE_DRAFT)
  {
    wsprintf(ws, PERCENT_T, lgp.LGP_SEND);
    goto GOGO;
  }
  switch(uo->dat_type)
  {
  case NML_FILE:
    if(curitem>=MENU_N_NML_FILE)
      goto ITEM_ERR;
    wsprintf(ws, PERCENT_T, items_lgp_nml_file[curitem]);
    break;
  case ARCHIVE_FILE:
    if(curitem>=MENU_N_ARCHIVE_FILE)
      goto ITEM_ERR;
    wsprintf(ws, PERCENT_T, items_lgp_archive_file[curitem]);
    break;
  case NML_DAT:
    if(curitem>=MENU_N_NML_DAT)
      goto ITEM_ERR;
    wsprintf(ws, PERCENT_T, items_lgp_nml_dat[curitem]);
    break;
  default:
ITEM_ERR:
  wsprintf(ws, PERCENT_T, lgp.LGP_ERR);
  }
GOGO:
#ifndef WITHOUT_OP_ICON
  SetMenuItemIconArray(data, item, ed_menu_item_icons);
  SetMenuItemIcon(data, curitem, 0);
#endif
  SetMenuItemText(data, item, ws, curitem);
}

#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);
int ed_menu_onkey(void *data, GUI_MSG *msg)
{
  int n;
  void *ed_gui;
  USER_OP *uo;
  if(!IsUnlocked()) TempLightOn(3, 0x7FFF);
  if(msg->keys==0x1)
  {
    return 1;
  }
  if((msg->keys==0x18)||(msg->keys==0x3D))
  {
    n=GetCurMenuItem(data);
  DO_PROC:
    ed_gui=MenuGetUserPointer(data);
    uo=EDIT_GetUserPointer(ed_gui);
    if(n==0 && uo->sd && uo->sd->type==TYPE_DRAFT)
    {
      ed_menu_send(data);
      return 1;
    }
    switch(uo->dat_type)
    {
    case NML_FILE:
      if(n>=MENU_N_NML_FILE)
	return 0;
      procs_nml_file[n](data);
      return 1;
    case ARCHIVE_FILE:
      if(n>=MENU_N_ARCHIVE_FILE)
	return 0;
      procs_archive_file[n](data);
      return 1;
    case NML_DAT:
      if(n>=MENU_N_NML_DAT)
	return 0;
      procs_nml_dat[n](data);
      return 1;
    default :
      return 0;
    }
  }
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    n=msg->gbsmsg->submess;
    if(n>='1' && n<='9')
    {
      n-='1';
      goto DO_PROC;
    }
  }
  return 0;
}

void ed_menu_ghook(void *data, int cmd)
{
  if(cmd==2) //create
  {
    WSHDR *hdr_t=AllocWS(32);
    wsprintf(hdr_t, PERCENT_T, lgp.LGP_OPTIONS);
    SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
  }
}
const MENU_DESC ed_menu=
{
  8,ed_menu_onkey,ed_menu_ghook,NULL,
  ed_menusoftkeys,
  &ed_menu_skt,
#ifdef WITHOUT_OP_ICON
  0x10,
#else
  0x11,//Right align
#endif
  ed_menu_itemhndl,
  0,//menuitems,
  0,//menuprocs,
  0
};

int createEditOpMenu(void *ed_gui)
{
	int item_n;
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	patch_option_header(&ed_menuhdr);
	switch(uo->dat_type)
	{
	case NML_FILE:
		item_n=MENU_N_NML_FILE;
		break;
	case ARCHIVE_FILE:
		item_n=MENU_N_ARCHIVE_FILE;
		break;
	case NML_DAT:
		item_n=MENU_N_NML_DAT;
		break;
	default:
		item_n=0;
	}
	return (CreateSLMenu_30or2(&ed_menu, &ed_menuhdr, 0, item_n, ed_gui));
}

#ifndef LANG_CN

//translit from smsman (c)titron
typedef struct
{
  char *r;
  char *e;
}trstruct;

const trstruct tr_r[]=
{
 {"\xC0","A"}, {"\xE0","a"},
 {"\xC1","B"}, {"\xE1","b"},
 {"\xC2","V"}, {"\xE2","v"},
 {"\xC3","G"}, {"\xE3","g"},
 {"\xC4","D"}, {"\xE4","d"},
 {"\xC5","E"}, {"\xE5","e"},
 {"\xA8","Yo"}, {"\xB8","yo"},
 {"\xC6","J"}, {"\xE6","j"},
 {"\xC7","Z"}, {"\xE7","z"},
 {"\xC8","I"}, {"\xE8","i"},
 {"\xC9","Y"}, {"\xE9","y"},
 {"\xCA","K"}, {"\xEA","k"},
 {"\xCB","L"}, {"\xEB","l"},
 {"\xCC","M"}, {"\xEC","m"},
 {"\xCD","N"}, {"\xED","n"},
 {"\xCE","O"}, {"\xEE","o"},
 {"\xCF","P"}, {"\xEF","p"},
 {"\xD0","R"}, {"\xF0","r"},
 {"\xD1","S"}, {"\xF1","s"},
 {"\xD2","T"}, {"\xF2","t"},
 {"\xD3","U"}, {"\xF3","u"},
 {"\xD4","F"}, {"\xF4","f"},
 {"\xD5","H"}, {"\xF5","h"},
 {"\xD6","C"}, {"\xF6","c"},
 {"\xD7","Ch"}, {"\xF7","ch"},
 {"\xD8","Sh"}, {"\xF8","sh"},
 {"\xD9","Sch"}, {"\xF9","sch"},
 {"\xDA","\""}, {"\xFA","\""},
 {"\xDB","Y"}, {"\xFB","Y"},
 {"\xDC","'"}, {"\xFC","'"},
 {"\xDD","E"}, {"\xFD","e"},
 {"\xDE","Yu"}, {"\xFE","yu"},
 {"\xDF","Ya"}, {"\xFF","ya"},
 "",""
};
/*
WSHDR *translit(WSHDR *ws0)
{
  int wlen, i, c, c1;
  const trstruct *p;
  char *txt;
  WSHDR *tws;
  extern int char16to8(int c);
  if(!ws0 || !(wlen=ws0->wsbody[0])) return 0;
  txt=malloc(wlen*2);
  zeromem(txt, wlen*2);
  for(i=0; i<wlen; i++)
  {
    c=ws0->wsbody[i+1];
    if(c<0x80)
    {
      txt[strlen(txt)]=c;
      continue;
    }
    c=char16to8(c)&0xff;
    p=tr_r;
    while((p->r) && (p->e))
    {
      c1=*(p->r);
      if(c1==c) strcat(txt, p->e);
      p++;
    }
    if(p->r) continue;
    else txt[strlen(txt)]=c;
  }
  tws=AllocWS(strlen(txt));
  wsprintf(tws,txt);
  mfree(txt);
  return (tws);
}

0x105, 'a'
0x107, 'c'
0x119, 'e'
0xF3, 'o'
0x142, 'l'
0x144, 'n'
0x15B, 's'
0x17C, 'z'
0x17A, 'z'*/
extern int char16to8(int c); //string_works.c
WSHDR *translit(WSHDR *ws0)
{
  int c;
  int wlen;
  if(!(wlen=ws0->wsbody[0])) return ws0;
  char *txt=malloc(wlen*2);
  zeromem(txt, wlen*2);
  for(int i=0; i<wlen; i++)
  {
    c=ws0->wsbody[i+1];
    if(c<0x80) goto ADD;
    switch(c) //PL
    {
    case 0x105:c='a';goto ADD;
    case 0x107:c='c';goto ADD;
    case 0x119:c='e';goto ADD;
    case 0x0F3:c='o';goto ADD;
    case 0x142:c='l';goto ADD;
    case 0x144:c='n';goto ADD;
    case 0x15B:c='s';goto ADD;
    case 0x17C:
    case 0x17A:c='z';goto ADD;
    }
    if(c<0x400) goto ADD;
    c=char16to8(c);
    for(int j=0; j<66; j++)
    {
      if(c==*tr_r[j].r)
      {
	c=0;
	strcat(txt, tr_r[j].e);
	j=66;
      }
    }
  ADD:
    if(c) txt[strlen(txt)]=c;
  }
  WSHDR *tws=AllocWS(strlen(txt));
  wsprintf(tws,PERCENT_T,txt);
  mfree(txt);
  return tws;
}

int add_translit(void *edsms_gui)
{
  EDITCONTROL ec;
  EDIT_ExtractFocusedControl(edsms_gui,&ec);
  WSHDR *ws0=translit(ec.pWS);
  if(ws0!=ec.pWS)
  {
    EDIT_SetTextToFocused(edsms_gui,ws0);
    FreeWS(ws0);
  }
  return 1;
}

#endif
int Ed_SendSMS(void *gui)
{
  EDITCONTROL ec;
  USER_OP *uo=EDIT_GetUserPointer(gui);
  NUM_LIST *nl=(NUM_LIST *)(uo->nltop);
  if(!(IsHaveNumInList(uo)))
  {
    MsgBoxError(1, (int)lgp.LGP_ERR_0NUM);
    return 0;
  }
  ExtractEditControl(gui,uo->focus_n,&ec);
  if(!(ec.pWS->wsbody[0]))
  {
    MsgBoxError(1, (int)"Nothing For Sent!");
    return 0;
  }
  while(nl)
  {
    if(strlen(nl->num))
    {
      WSHDR *ws=AllocWS(ec.pWS->wsbody[0]);
      wstrcpy(ws,ec.pWS);
      SNEDSMS_CSM_ID=SendSMS(ws,nl->num,MMI_CEPID,MSG_SMS_RX-1,6);
      if(CFG_ENA_SAVE_SENT) saveFile(ec.pWS, nl->num, uo->sd, TYPE_OUT, 2);
    }
    nl=nl->next;
  }
  //草稿发送完成删除
  if(uo->sd && uo->sd->type==TYPE_DRAFT)
  {
    if(!uo->sd->isfile) deleteDat(uo->sd, 0);
    else deleteFile(uo->sd, 0);
    delSDList(uo->sd);
    uo->sd=0;
  }
  uo->nd_sfd=0;
  return 1;
}

void Ed_SaveFile(WSHDR *txt, USER_OP *uo, int type)
{
  NUM_LIST *nl=(NUM_LIST *)(uo->nltop);
  SMS_DATA *sdx=0;
  while(nl)
  {
    sdx=(SMS_DATA *)saveFile(txt, nl->num, uo->sd, type, 2);
    nl=nl->next;
  }
  if(type==TYPE_DRAFT && uo->sd && uo->sd->type==TYPE_DRAFT && (int)sdx!=1 && sdx!=0)
  {
    if(!uo->sd->isfile && uo->sd->id)
      deleteDat(uo->sd, 0);
    delSDList(uo->sd);
    uo->sd=sdx;
  }
  uo->nd_sfd=0;
  //readAllSMS();
}

#ifdef LANG_CN
#define OPTION_N 5
#define OPTION_N_N (OPTION_N-1)
#else
#define OPTION_N 6
#define OPTION_N_N (OPTION_N-2)
#endif
void on_adr_ec(USR_MENU_ITEM *item) //MENU WOULD BE CLOSED FIRST
{
  if(item->type==0)
  {
    USER_OP *uo=EDIT_GetUserPointer(item->user_pointer);
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws, PERCENT_T, lgp.LGP_SEND);
      break;
    case 1:
      wsprintf(item->ws, PERCENT_T, lgp.LGP_ADRBK);
      break;
    case 2:
      wsprintf(item->ws, PERCENT_T, lgp.LGP_CANCEL);
      break;
    case 3:
      wsprintf(item->ws, PERCENT_T, (uo->sd->type==TYPE_DRAFT && uo->sd->isfile)?lgp.LGP_SAVE:lgp.LGP_SAVE_AS_DRAFT);
      break;
    case 4:
      wsprintf(item->ws, PERCENT_T, lgp.LGP_TEMPLATE);
      break;
#ifndef LANG_CN
    case 5:
      wsprintf(item->ws, PERCENT_T, lgp.LGP_TRANSLIT);
      break;
#endif
    }
  }
  else if(item->type==1)
  {
    USER_OP *uo=EDIT_GetUserPointer(item->user_pointer);
    DLG_CSM *dlg_csm=(DLG_CSM *)uo->dlg_csm;
    SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);
    switch(item->cur_item)
    {
    case 0:
      if((Ed_SendSMS(item->user_pointer))&&(gstop))
      {
	GeneralFunc_flag1(gstop->id, 1);
	popGS(dlg_csm);
	DoSendBackGround(dlg_csm);
      }
      break;
    case 1:
      CreateNAbCSM(dlg_csm, item->user_pointer, TYPE_SELECT);
      break;
    case 2:
      if(gstop)
      {
	GeneralFunc_flag1(gstop->id, 1);
	popGS(dlg_csm);
      }
      break;
    case 3:
      {
	EDITCONTROL ec;
	ExtractEditControl(item->user_pointer,uo->focus_n,&ec);
	Ed_SaveFile(ec.pWS, uo, TYPE_DRAFT);
      }
      if(!uo->sd || (CFG_ENA_EXIT_SAVE_DRAFT && gstop))
      {
	GeneralFunc_flag1(gstop->id, 1);
	popGS(dlg_csm);
      }
      break;
    case 4:
      CreateTplMenu(item->user_pointer);
      break;
#ifndef LANG_CN
    case 5:
      if(EDIT_GetFocus(item->user_pointer)==uo->focus_n)
	add_translit(item->user_pointer);
      break;
#endif
    }
  }
}

int edOnKey(GUI *data, GUI_MSG *msg)
{
//0x29 keys, ENTER,no op
//0x05 keys, Green
//0x03 keys, ENTER,op
//0x3D keys, ENTER,select char
//0x1A keys, LSK
//0x01 keys, RSK
	USER_OP *uo=EDIT_GetUserPointer(data);
	int n=EDIT_GetFocus(data);
	DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
	SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);
	SMS_DATA *sdl=0;
	
	if(!IsUnlocked())
		TempLightOn(3, 0x7FFF);
		
	if(msg->keys==0x05)
	{
		if(uo->gui_type==ED_VIEW)
		{
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, uo->sd, (uo->sd->type==TYPE_DRAFT)?ED_EDIT:ED_REPLY, 0);
			else
				createEditGUI(uo->dlg_csm, uo->sd, (uo->sd->type==TYPE_DRAFT)?ED_EDIT:ED_REPLY, 0);
			return 1;
		}
		else if((uo->gui_type==ED_FVIEW)&&(uo->sd))
		{
			SMS_DATA *sd=SdCopyOne(uo->sd);
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, sd, (uo->sd->type==TYPE_DRAFT)?ED_FEDIT:ED_FREPLY, 0);
			else
				createEditGUI(uo->dlg_csm, sd, (uo->sd->type==TYPE_DRAFT)?ED_FEDIT:ED_FREPLY, 0);
			return 1;
		}
		else
		{
			if(!Ed_SendSMS(data))
				return 0;
			else
			{
			  popGS(uo->dlg_csm);
			  DoSendBackGround(uo->dlg_csm);
			  return 1;
			}
		}
		//popGS(uo->dlg_csm);
		//return 1;
	}
	else if((msg->keys==0x29)&&((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW)))
	{
		createEditOpMenu(data);
	}
	else if(msg->keys==0x18)
	{
		if((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))
		{
			createEditOpMenu(data);
		}
		else
		{
			if(n==uo->focus_n)
			{
				uo->adr_type=TYPE_TXT;
				EDIT_OpenOptionMenuWithUserItems(data,on_adr_ec,data,OPTION_N);
			}
			else if(n<=(uo->focus_n-2)) //号码位置
			{
				uo->adr_type=TYPE_SET;
				EDIT_OpenOptionMenuWithUserItems(data,on_adr_ec,data,OPTION_N_N);
			}
			return (-1);
		}
	}

	else if(msg->keys==0x1)
	{
		popGS(uo->dlg_csm);
		return 1;
	}
	else if(msg->keys==0x0F00)
	{
		uo->adr_type=TYPE_SET;
		CreateNAbCSM(dlg_csm, data, TYPE_SELECT);
	}
	if(((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))&&(!EDIT_IsBusy(data)))
	{
		int i=msg->gbsmsg->submess;
		EDITCONTROL ec;
		ExtractEditControl(data,n,&ec);
		//中键
		if((i==ENTER_BUTTON)&&(uo->gui_type!=ED_VIEW)&&(uo->gui_type!=ED_FVIEW))
		{
			if(n==uo->focus_n)
			{
				uo->adr_type=TYPE_TXT;
				EDIT_OpenOptionMenuWithUserItems(data,on_adr_ec,data,OPTION_N);
				//EDIT_OpenOptionMenuWithUserItems(data,on_ed_ec,data,3);
			}
			else if(n<=(uo->focus_n-2)) //号码位置
			{
				uo->adr_type=TYPE_SET;
				EDIT_OpenOptionMenuWithUserItems(data,on_adr_ec,data,OPTION_N_N);
			}
			return (-1);
		}
		//上方向, 侧上键
		if(((i==UP_BUTTON)||(i==VOL_UP_BUTTON)) //循环
				&&(n==1)
				&&(!(EDIT_IsMarkModeActive(data)))
				&&(EDIT_GetCursorPos(data)<=1)) //第一行第一个字符
		{
			EDIT_SetFocus(data, uo->focus_n);
			return (-1);
		}
		//下方向, 侧下键
		if(((i==DOWN_BUTTON)||(i==VOL_DOWN_BUTTON))
				&&(n==uo->focus_n)
				&&(!(EDIT_IsMarkModeActive(data)))
				&&(EDIT_GetCursorPos(data)>=(ec.pWS->wsbody[0]+1))) //最后一个字
		{
			EDIT_SetFocus(data, 1);
			return (-1);
		}
		//右方向键,下一条
		if((i==RIGHT_BUTTON)&&(uo->gui_type==ED_VIEW)&&(sdl=FindNextByType(uo->sd, uo->list_type)))
		{
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, sdl, ED_VIEW, uo->list_type);
			else
				createEditGUI(uo->dlg_csm, sdl, ED_VIEW, uo->list_type);
			return 1;
		}
		if((i==RIGHT_BUTTON)&&(uo->gui_type==ED_FVIEW)&&(sdl=FindNextMss(uo->sd)))
		{
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, sdl, ED_FVIEW, 0);
			else
				createEditGUI(uo->dlg_csm, sdl, ED_FVIEW, 0);
			return 1;
		}
		//左方向键,上一条
		if((i==LEFT_BUTTON)&&(uo->gui_type==ED_VIEW)&&(sdl=FindPrevByType(uo->sd, uo->list_type)))
		{
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, sdl, ED_VIEW, uo->list_type);
			else
				createEditGUI(uo->dlg_csm, sdl, ED_VIEW, uo->list_type);
			return 1;
		}
		if((i==LEFT_BUTTON)&&(uo->gui_type==ED_FVIEW)&&(sdl=FindPrevMss(uo->sd)))
		{
			int update=0;
			if(gstop->id==dlg_csm->gui_id)
				update=1;
			popGS(uo->dlg_csm);
			if(update)
				dlg_csm->gui_id=createEditGUI(uo->dlg_csm, sdl, ED_FVIEW, 0);
			else
				createEditGUI(uo->dlg_csm, sdl, ED_FVIEW, 0);
			return 1;
		}
		//*键,查看号码信息
		if((i=='*')&&((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))&&(uo->sd))
		{
			NUM_LIST *nl=(NUM_LIST *)(uo->nltop);
			WSHDR *msg=AllocWS(128);
		#ifdef NO_CS
			wsprintf(msg, "%t:\n%s", (uo->sd->type==TYPE_OUT||uo->sd->type==TYPE_DRAFT)?lgp.LGP_TO:lgp.LGP_FROM, nl->num);
		#else
			{
				char num[32];
				WSHDR csloc, *cs;
				unsigned short csb[30];
				cs=CreateLocalWS(&csloc,csb,30);
				strcpy(num, nl->num);
				GetProvAndCity(cs->wsbody, num);
				wsprintf(msg, "%t:\n%s\n%t:\n%w", (uo->sd->type==TYPE_OUT||uo->sd->type==TYPE_DRAFT)?lgp.LGP_TO:lgp.LGP_FROM, nl->num, lgp.LGP_CODESHOW, cs);
			}
		#endif
			ShowMSG_ws(1, msg);
		}
	}
	return 0;
}


SOFTKEY_DESC SK_OPTIONS={0x0018,0x0000,(int)LGP_NULL};
SOFTKEY_DESC SK_ADRBK={0x0F00,0x0000,(int)LGP_NULL};
SOFTKEY_DESC SK_CANCEL={0x0001,0x0000,(int)LGP_NULL};
SOFTKEY_DESC SK_OP_PIC={0x0029,0x0000,(int)LGP_OPTION_PIC};

#define TI_CMD_GOTOTOP 0x5

//const int ed_hdr_icon[]={0x4BD,0};
#ifdef NEWSGOLD
#ifdef ELKA
int EDHDRIC_VIEW[]={0x2A5,0};
int EDHDRIC_EDIT[]={0x4DB,0};
int EDHDRIC_ADRBK[]={0x28C,0};
#else
int EDHDRIC_VIEW[]={0x29A,0};
int EDHDRIC_EDIT[]={0x505,0};
int EDHDRIC_ADRBK[]={0x1A1,0};
#endif
#endif
//extern void SetHeaderIcon(void *hdr_pointer, const int *icon, void *malloc_adr, void *mfree_adr);
void edGHook(GUI *data, int cmd)
{
  USER_OP *uo=EDIT_GetUserPointer(data);
  if(cmd==TI_CMD_CREATE)
  {
    if((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))
      EDIT_SetFocus(data, 1); //从号码开始看
    else
      EDIT_SetFocus(data, uo->focus_n);//光标跳到文本位置
  }
  else if(cmd==TI_CMD_DESTROY)
  {
	  //auto save at exit
//	  if((uo->gui_type==ED_VIEW)
//	     &&(CFG_ENA_AUTO_SAF)
//	       &&(!uo->sd->isfile)
//		 &&(uo->sd->id)
//		   &&(uo->sd->msg_type!=ISREPORT || !CFG_ENA_AUTO_DEL_RP))
//	  {
//	    if(saveFile(uo->sd->SMS_TEXT, uo->sd->Number, uo->sd, uo->sd->type, 0))
//	      deleteDat(uo->sd, 1);
//	  }
    if(uo->nd_sfd && uo->gui_type!=ED_VIEW && uo->gui_type!=ED_FVIEW && (CFG_ENA_AUTO_SAVE_DRAFT))
    {
      EDITCONTROL ec;
      ExtractEditControl(data, uo->focus_n, &ec);
      if(ec.pWS->wsbody[0])
      {
	Ed_SaveFile(ec.pWS, uo, TYPE_DRAFT);
      }
    }
    if((CFG_ENA_AUTO_DEL_RP)&&(uo->gui_type==ED_VIEW)&&(uo->sd)&&(uo->sd->msg_type&ISREPORT)&&(uo->sd->id > 0)&&(!uo->sd->isfile))
    {
      if(IsSdInList(uo->sd) && deleteDat(uo->sd, 0))
	delSDList(uo->sd);
    }
    if(((uo->gui_type==ED_FREE)
	||(uo->gui_type==ED_FVIEW)
	  ||(uo->gui_type==ED_FEDIT)
	    ||(uo->gui_type==ED_FREPLY)
	      )&&(uo->sd))
    {
      FreeSdOne(uo->sd);
    }
    FreeNumList(uo);
    mfree(uo);
  }
  else if(cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  else if(cmd==TI_CMD_GOTOTOP)
  {
    const char *lgpN;
    switch(uo->gui_type)
    {
    case ED_VIEW:
    case ED_FVIEW:
      lgpN=lgp.LGP_VIEW;
      break;
    case ED_EDIT:
    case ED_FEDIT:
      lgpN=lgp.LGP_EDIT;
      break;
    case ED_NEW:
    case ED_FREE:
      lgpN=lgp.LGP_NEW;
      break;
    case ED_REPLY:
    case ED_FREPLY:
      lgpN=lgp.LGP_REPLY;
      break;
    default:
      lgpN=0;
      break;
    }
    if(lgpN) UpdateDlgCsmName(uo->dlg_csm, lgpN);
  }
  else if(cmd==TI_CMD_REDRAW)
  {
    NUM_LIST *nl;
    EDITCONTROL ec;
    char time[32];
    char num[32];
    WSHDR txtl, *text;
    unsigned short txtb[MAX_TEXT];
    SMS_DATA *sdx;
    DLG_CSM *dlg_csm=(DLG_CSM *)(uo->dlg_csm);
    SGUI_ID *gstop=(SGUI_ID *)(dlg_csm->gstop);	
    int n=EDIT_GetFocus(data);
    text=CreateLocalWS(&txtl, txtb, MAX_TEXT);
    
    //---
    if(!uo->sd)
    {
      GeneralFuncF1(1);
      return;
    }
//check sd in list
    if((uo->gui_type==ED_VIEW)&&(!IsSdInList(uo->sd)))
    {
      ExtractEditControl(data, uo->focus_n, &ec);
      wstrcpy(text, ec.pWS);
      if(uo->focus_n>2) //简单判断时间是否存在
      {
	ExtractEditControl(data, uo->focus_n-2, &ec);
	ws_2str(ec.pWS, time, 31);
      }
      else
	time[0]=0;
      nl=uo->nltop;
      if(nl) strcpy(num, nl->num);
      else num[0]=0;
      if(!(sdx=FindSdByTxtTimeNum(text, time, num)))
      {
	if(gstop)
	{
	  GeneralFunc_flag1(gstop->id, 1);
	  popGS(dlg_csm);
	}
	else
	{
	  //如果完全出错,直接退出
	  GeneralFunc_flag1(dlg_csm->gui_id, 1);
	}
      }
      else
	uo->sd=sdx;
    }
    
    
    //set mid softkey
    if((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))
      SetSoftKey(data,&SK_OP_PIC,SET_SOFT_KEY_M);
    
    //num to name at unfocus
    if((uo->gui_type!=ED_VIEW)&&(uo->gui_type!=ED_FVIEW))
    {
      int u=EDIT_GetUnFocus(data);
      if(u<=(uo->focus_n-2) && (nl=GetNumListCur(uo, u)))
      {
	if(isNum(nl->name))
	{
	  if(findNameByNum(text, nl->num))
	  {
	    wstrcpy(nl->name, text);
	    EDIT_SetTextToEditControl(data, u, text);
	  }
	}
      }
    }
    
//auto save as file
    if((uo->gui_type==ED_VIEW)
       &&(CFG_ENA_AUTO_SAF)
	 &&(!uo->sd->isfile)
	   //&&(uo->sd->type!=TYPE_IN_N) //set status first
	   &&(uo->sd->id)
	     &&(!(uo->sd->msg_type&ISDES))
	       &&(!(uo->sd->msg_type&ISUNKE))
	       &&(!(uo->sd->msg_type&ISUNKT))
	       &&(!(uo->sd->msg_type&ISREPORT) || !CFG_ENA_AUTO_DEL_RP))      
    {
      wstrcpy(text, uo->sd->SMS_TEXT);
      strcpy(time, uo->sd->Time);
      strcpy(num, uo->sd->Number);
      if(saveFile(uo->sd->SMS_TEXT, uo->sd->Number, uo->sd, uo->sd->type, 2))
      {
	deleteDat(uo->sd, 0);
	delSDList(uo->sd);
	if(!(sdx=FindSdByTxtTimeNum(text, time, num))) //重新查找sd失败,直接返回列表
	{
	  if(gstop!=0)
	  {
	    GeneralFunc_flag1(gstop->id, 1);
	    popGS(dlg_csm);
	  }
	  else
	  {
	    //如果完全出错,直接退出
	    GeneralFunc_flag1(dlg_csm->gui_id, 1);
	  }
	}
	else
	{
	  uo->sd=sdx;
	  //update dat type
	  if(uo->sd->isfile)
	  {
	    if(uo->sd->fname && IsFileInArchive(uo->sd->fname))
	      uo->dat_type=ARCHIVE_FILE;
	    else
	      uo->dat_type=NML_FILE;
	  }
	  else uo->dat_type=NML_DAT;
	}
      }
    }
    
    //set status
    if((uo->gui_type==ED_VIEW)
       &&(uo->sd->type==TYPE_IN_N)
	 &&(!(uo->sd->msg_type&ISDES)))
      newToRead(uo->sd);
//-------------------
    {
      ExtractEditControl(data, uo->focus_n, &ec);
      WSHDR *hdr_t=AllocWS(64);
      void *hdr_p=GetHeaderPointer(data);
      void *ma=malloc_adr();
      void *mf=mfree_adr();
      int z=0;
      extern int IsWsSmall(WSHDR *ws);
      if(uo->gui_type==ED_VIEW || uo->gui_type==ED_FVIEW)
      {
	if(uo->sd)
	{
	  if(!(z=uo->sd->cnt_r))
	  {
	    if(!ec.pWS->wsbody[0])
	      z=1;
	    else if((uo->sd->msg_type&IS7BIT)||(IsWsSmall(ec.pWS)))
	      z=(ec.pWS->wsbody[0]-1)/SEG7_MAX+1;
	    else
	      z=(ec.pWS->wsbody[0]-1)/SEGN_MAX+1;
	  }
	}
      }
      else
      {
	if(uo->chr_cnt!=ec.pWS->wsbody[0])
	{
	  uo->chr_cnt=ec.pWS->wsbody[0];
	  uo->nd_sfd=1;
	}
	if(!ec.pWS->wsbody[0]) z=1;
	else if(IsWsSmall(ec.pWS)) z=(ec.pWS->wsbody[0]-1)/SEG7_MAX+1;
	else z=(ec.pWS->wsbody[0]-1)/SEGN_MAX+1;
      }
#ifdef DEBUG
      wsprintf(hdr_t, "%t:%d,p:%d", lgp.LGP_CHAR_COUNT, ec.pWS->wsbody[0], EDIT_GetCursorPos(data));
#else
      wsprintf(hdr_t, "%t: %d %d", lgp.LGP_CHAR_COUNT, ec.pWS->wsbody[0], z);
#endif
      SetHeaderText(hdr_p, hdr_t, ma, mf);
      if((uo->gui_type==ED_VIEW)||(uo->gui_type==ED_FVIEW))
	SetHeaderIcon(hdr_p, EDHDRIC_VIEW, ma, mf);
      else
      {
	if(n<=(uo->focus_n-2))
	  SetHeaderIcon(hdr_p, EDHDRIC_ADRBK, ma, mf);
	else
	  SetHeaderIcon(hdr_p, EDHDRIC_EDIT, ma, mf);
      }
    }
    
    //check number
    if((uo->gui_type!=ED_VIEW)&&(uo->gui_type!=ED_FVIEW)&&(n<=(uo->focus_n-2))&&(nl=GetNumListCur(uo, n)))
    {
      ExtractEditControl(data,n,&ec);
      if(isNum(ec.pWS))
      {
	char num[50];
	ws_2str(ec.pWS, num, 49);
	if(strcmp(num, nl->num))
	{
	  strcpy(nl->num, num);
	  str_2ws(nl->name, num, 50);
	}
      }
      else
      {
	if(wstrcmp_nocase(ec.pWS, nl->name))
	{
	  DelNumList(uo, nl);
	  if((uo->focus_n-2)>1) //多于一个号码就直接删除这个
	  {
	    EDIT_RemoveEditControl(data, n);
	    (uo->focus_n)--;
	    if(n>(uo->focus_n-2))
	      n=(uo->focus_n-2);
	    if(n>0)
	      EDIT_SetFocus(data, n);
	  }
	  else
	  {
	    EDIT_SetTextToEditControl(data, n, ((NUM_LIST *)(uo->nltop))->name);
	    SetSoftKey(data,&SK_CANCEL,!SET_SOFT_KEY_N);
	  }
	}
      }
    }
    if(!EDIT_IsBusy(data))
    {
      ExtractEditControl(data,n,&ec);
      if((n<=(uo->focus_n-2))&&(ec.pWS->wsbody[0]==0)&&(uo->gui_type!=ED_VIEW))
	SetSoftKey(data,&SK_ADRBK,SET_SOFT_KEY_N);
      else
	SetSoftKey(data,&SK_OPTIONS,SET_SOFT_KEY_N);
    }
  }
}

void ed_locret(void)
{
  ;
}

const INPUTDIA_DESC ED_DESC=
{
	1,
	edOnKey,
	edGHook,
	(void *)ed_locret,
	0,
	&ed_menu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000000
};

const INPUTDIA_DESC ED_DESC_RO=
{
	1,
	edOnKey,
	edGHook,
	(void *)ed_locret,
	0,
	&ed_menu_skt,
	{0,0,0,0},
	FONT_SMALL,
	100,
	101,
	0,
	0,
	0x40000002
};

#define EDIT_FONT_DEFAULT 0
#define EDIT_FONT_SMALL 1
#define EDIT_FONT_SMALL_BOLD 2
#define EDIT_FONT_MEDIUM 3
#define EDIT_FONT_MEDIUM_BOLD 4
#define EDIT_FONT_LARGE 5
#define EDIT_FONT_LARGE_BOLD 6

int createEditGUI(void *dlg_csm, SMS_DATA *sd, int type, int list_type) //edit, view
{
  int gui_id;
  void *ma=malloc_adr();
  void *eq;
  WSHDR *ews, ewsn;
  unsigned short ewsb[MAX_TEXT];
  const INPUTDIA_DESC *edd;
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  ews=CreateLocalWS(&ewsn, ewsb, MAX_TEXT);
//----------- uo
  USER_OP *uo=malloc(sizeof(USER_OP));
  zeromem(uo, sizeof(USER_OP));

  AddToNumList(uo);
  uo->sd=sd; //?
  uo->dlg_csm=dlg_csm;
  strcpy(((NUM_LIST *)(uo->nltop))->num, sd->Number);
  uo->gui_type=type;
  uo->list_type=list_type;
  uo->focus_n=0;
  if(uo->sd->isfile)
  {
    if(uo->sd->fname && IsFileInArchive(uo->sd->fname))
      uo->dat_type=ARCHIVE_FILE;
    else
      uo->dat_type=NML_FILE;
  }
  else
    uo->dat_type=NML_DAT;
//----------
  eq=AllocEQueue(ma,mfree_adr());
  PrepareEditControl(&ec);
  PrepareEditCOptions(&ec_options);
//-----------

//----------- header

//------------

//------------ num
  {
    char *pnn;
    WSHDR *wsname, wsnamen;
    unsigned short wsnameb[50];
    int is_fetion=0;
    if(strlen(sd->Number))
    {
      pnn=sd->Number;
    DO_NUM:
#ifdef LANG_CN
      wsname=CreateLocalWS(&wsnamen, wsnameb, 50);
      if(!strncmp(num_fetion, pnn, 5)) is_fetion=1;
      if(!findNameByNum(wsname, is_fetion?(pnn+5):pnn))
	str_2ws(ews, pnn, 50);
      else
      {
	if(is_fetion) wsprintf(ews, "%w(%t)", wsname, lgp.LGP_FETION);
	else wstrcpy(ews, wsname);
      }
#else
      if(!findNameByNum(ews, pnn))
	str_2ws(ews, pnn, 50);
#endif
    }
    else
    {
      if((type==ED_VIEW || type==ED_FVIEW))
	wsprintf(ews, "%c", ' ');
      else
      {
	if((type==ED_FREE || type==ED_NEW) && strlen((pnn=(char *)CFG_DEFAULT_SENT_NUM)))
	{
	  //is number
	  for(int xl=0; xl<strlen(pnn); xl++)
	  {
	    if(pnn[xl]<'0' || pnn[xl]>'9')
	      goto N_BLANK;
	  }
	  strcpy(((NUM_LIST *)(uo->nltop))->num, pnn);
	  goto DO_NUM;
	}
	else
      N_BLANK:
	  CutWSTR(ews, 0);
      }
    }
#ifdef DEBUG
    {
      if(strlen(sd->Number))
      {
	WSHDR *ws=AllocWS(50);
	str_2ws(ws, sd->Number, 50);
	wsAppendChar(ews, '|');
	wstrcat(ews, ws);
	FreeWS(ws);
      }
    }
#endif
    wstrcpy(((NUM_LIST *)(uo->nltop))->name, ews);
    ConstructEditControl(&ec,(type==ED_VIEW||type==ED_FVIEW)?ECT_READ_ONLY:ECT_NORMAL_TEXT,ECF_DEFAULT_DIGIT+ECF_APPEND_EOL,ews,256);
    SetFontToEditCOptions(&ec_options,EDIT_FONT_SMALL);
    CopyOptionsToEditControl(&ec,&ec_options);
    AddEditControlToEditQend(eq,&ec,ma);
    uo->focus_n++;
  }
//------------
//------------ time
  if((type==ED_FVIEW)||(type==ED_VIEW)&&strlen(sd->Time)) //time
  {
    str_2ws(ews, sd->Time, 256);
    ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
    AddEditControlToEditQend(eq,&ec,ma);
    uo->focus_n++;
  }
//------------
//------------ line
  str_2ws(ews, STR_LINES,256);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);
  uo->focus_n++;
//------------
//------------ TXT
  if(sd->SMS_TEXT)
  {
    wstrcpy(ews, sd->SMS_TEXT);
    uo->chr_cnt=ews->wsbody[0];
  }
  else
    CutWSTR(ews, 0);
  switch(type)
  {
  case ED_VIEW:
  case ED_FVIEW:
    ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,MAX_TEXT);
    break;
  case ED_FREE:
  case ED_EDIT:
  case ED_FEDIT:
    ConstructEditControl(&ec,TEXT_INPUT_OPTION,ECF_APPEND_EOL|ECF_DEFAULT_BIG_LETTER,ews,MAX_TEXT);
    break;
  case ED_NEW:
  case ED_REPLY:
  case ED_FREPLY:
    CutWSTR(ews, 0);
    ConstructEditControl(&ec,TEXT_INPUT_OPTION,ECF_APPEND_EOL|ECF_DEFAULT_BIG_LETTER,ews,MAX_TEXT);
    break;
  default:
    ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,ews,MAX_TEXT);
    break;
  }
  //
  SetFontToEditCOptions(&ec_options,CFG_TEXT_FONT);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
  uo->focus_n++;
//----------	
	
  if (type==ED_VIEW || type==ED_FVIEW)
    edd=&ED_DESC_RO;
  else
    edd=&ED_DESC;
  patch_header(&ED_HDR);
  patch_input(edd);
  gui_id=CreateInputTextDialog(edd, &ED_HDR, eq, 1, uo);
  pushGS(dlg_csm, gui_id);
  return gui_id;
}

int newSMS(void *dlg_csm)
{
	SMS_DATA *sd=AllocSD();
	return (createEditGUI(dlg_csm, sd, ED_FREE, 0));
}
int viewTheLastNew(void *dlg_csm)
{
	SMS_DATA *sd=GetTheLastNew(0);
	if(!sd)
		return 0;
	return(createEditGUI(dlg_csm, sd, ED_VIEW, TYPE_IN_N));
}

int newSMSWithNum(void *dlg_csm, char *num)
{
	SMS_DATA *sd;
	if(!num)
		return 0;
	sd=AllocSD();
	strcpy(sd->Number, num);
	mfree(num);
	return (createEditGUI(dlg_csm, sd, ED_FREE, 0));
}

int newSMSWithUtf8Text(void *dlg_csm, char *text_utf8)
{
	SMS_DATA *sd;
	WSHDR *ws;
	if(!text_utf8)
		return 0;
	sd=malloc(sizeof(SMS_DATA));
	zeromem(sd, sizeof(SMS_DATA));
	ws=AllocWS(MAX_TEXT);
	sd->SMS_TEXT=ws;
	utf8_2ws(ws, text_utf8, MAX_TEXT);
	mfree(text_utf8);
	return (createEditGUI(dlg_csm, sd, ED_FREE, 0));
}

int DoByOpmsgId(void *dlg_csm, int msg, int opmsg_id)
{
	SMS_DATA *sd;
	if((!opmsg_id)||(!(sd=FindSDByOpmsgId(opmsg_id))))
		return 0;
	switch(msg)
	{
	case SMSYS_IPC_VIEW_OPMSG:
		return (createEditGUI(dlg_csm, sd, ED_VIEW, TYPE_IN_ALL));
	case SMSYS_IPC_REPLY_OPMSG:
		return (createEditGUI(dlg_csm, sd, ED_REPLY, 0));
	case SMSYS_IPC_QR_OPMSG:
		return (createEditGUI(dlg_csm, sd, ED_EDIT, 0));
	case SMSYS_IPC_QN_OPMSG:
		{
			SMS_DATA *sdx=malloc(sizeof(SMS_DATA));
			WSHDR *ws=AllocWS(MAX_TEXT);
			zeromem(sdx, sizeof(SMS_DATA));
			sdx->SMS_TEXT=ws;
			wstrcpy(ws, sd->SMS_TEXT);
			return (createEditGUI(dlg_csm, sdx, ED_FREE, 0));
		}
	}
	return 0;
}

int CreateSmsWS(void *dlg_csm, WSHDR *text)
{
  SMS_DATA *sd;
  WSHDR *ws;
  if(!text) return 0;
  sd=AllocSD();
  ws=AllocWS(text->wsbody[0]);
  wstrcpy(ws, text);
  FreeWS(text);
  sd->SMS_TEXT=ws;
  return (createEditGUI(dlg_csm, sd, ED_FREE, 0));
}

unsigned int ViewFile(void *dlg_csm, char *fname)
{
	SMS_DATA *sd;
	if(!strlen(fname))
		return 0;
	sd=malloc(sizeof(SMS_DATA));
	zeromem(sd, sizeof(SMS_DATA));
	if(!ReadMSS(fname, sd))
	{
		FreeSdOne(sd);
		return 0;
	}
	return (createEditGUI(dlg_csm, sd, ED_FVIEW, 0));
}
#define IDYES	0
#define IDNO	1
typedef struct
{
  int type;
  char *path;
}PI_UP;
void DeleteAllMss_proc(int id)
{
	if(id==IDYES)
		DeleteAllMss();
}
void delallproc(void)
{
	MsgBoxYesNo(1, (int)lgp.LGP_DEL_ALL_MSS, DeleteAllMss_proc);
}
int PathInputOnKey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  char path[128];
  PI_UP *iu=EDIT_GetUserPointer(data);
  if(msg->keys==0x1A)
  {
    int k;
    ExtractEditControl(data,2,&ec);
    ws_2str(ec.pWS, path, 128);
    if(iu->type==INPUT_EXP_TXT)
    {
      k=ExportAllToOneTxt(path);
      if(k>0)
      {
	char msg[64];
    	sprintf(msg, lgp.LGP_EXPORT_N, k);
	ShowMSG_offproc(1, msg, delallproc);
      }
      else
	ShowFileErrCode(k);
    }
    else if(iu->type==INPUT_COV_DAT)
    {
      PathInputDlg(INPUT_COV_TXT, path);
    }
    else if(iu->type==INPUT_COV_TXT && iu->path)
    {
      k=CovDatToTxt(iu->path, path);
      if(k>0)
      {
	char msg[64];
    	sprintf(msg, lgp.LGP_EXPORT_N, k);
	ShowMSG(1, (int)msg);
      }
      else
	ShowFileErrCode(k);
    }
    return 1;
  }
  return 0;
}

void PathInputGHook(GUI *data, int cmd)
{
  if(cmd==0x0A)
    DisableIDLETMR();
  else if(cmd==TI_CMD_DESTROY)
  {
    PI_UP *iu=EDIT_GetUserPointer(data);
    if(iu->path)
      mfree(iu->path);
    mfree(iu);
  }
}

INPUTDIA_DESC PATH_INPUT_DESC=
{
  1,
  PathInputOnKey,
  PathInputGHook,
  (void *)ed_locret,
  0,
  &ed_menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};

void PathInputDlg(int type, char *path)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  WSHDR *ews;
  TDate date;
  TTime time;
  PI_UP *iu=malloc(sizeof(PI_UP));
  iu->type=type;
  if(path)
  {
    iu->path=malloc(128);
    strcpy(iu->path, path);
  }
  else
    iu->path=0;
  GetDateTime(&date, &time);
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ews=AllocWS(128);
  wsprintf(ews, PERCENT_T, lgp.LGP_PLS_INPUT_PATH);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);
  if(type==INPUT_COV_DAT)
    wsprintf(ews, "%sSMS\\SMS.dat", CFG_SYSTEM_FOLDER);
  else
    wsprintf(ews, "%sText\\%d%02d%02d.txt", CFG_MAIN_FOLDER, date.year, date.month, date.day);
  ConstructEditControl(&ec,ECT_CURSOR_STAY,ECF_APPEND_EOL,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);
  patch_header(&ED_HDR);
  patch_input(&PATH_INPUT_DESC);
  CreateInputTextDialog(&PATH_INPUT_DESC,&ED_HDR,eq,1,iu);
  FreeWS(ews);
}

int ED_ShowMsg_OnKey(GUI *gui, GUI_MSG *msg)
{
  int c=msg->keys;
  if(c==0x29 || c==0x1A || c==0x1)
    return 1;
  return 0;
}
void ED_ShowMsg_GHook(GUI *gui, int cmd)
{
  if(cmd==TI_CMD_CREATE)
  {
    WSHDR *hdr_t=EDIT_GetUserPointer(gui);
    if(hdr_t) SetHeaderText(GetHeaderPointer(gui), hdr_t, malloc_adr(), mfree_adr());
  }
  /*
  if(cmd==TI_CMD_REDRAW)
  {
    WSHDR *hdr_t=EDIT_GetUserPointer(gui);
    if(hdr_t)
    {
      WSHDR *hdr2=AllocWS(hdr_t->wsbody[0]);
      wstrcpy(hdr2, hdr_t);
      SetHeaderText(GetHeaderPointer(gui), hdr2, malloc_adr(), mfree_adr());
    }
  }
  else if(cmd==TI_CMD_DESTROY)
  {
    WSHDR *hdr_t=EDIT_GetUserPointer(gui);
    if(hdr_t) FreeWS(hdr_t);
  }*/
}
const INPUTDIA_DESC ED_ShowMsg=
{
  1,
  ED_ShowMsg_OnKey,
  ED_ShowMsg_GHook,
  (void *)ed_locret,
  0,
  &ed_menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000002
};

int CreateSimpleShowMsgGui(WSHDR *header, WSHDR *msgtxt)
{
  void *ma=malloc_adr();
  void *eq;
  WSHDR *hdr_t;
//  WSHDR *ews, ewsn, *hdr_t;
  int cc;
//  unsigned short ewsb[MAX_TEXT];
  EDITCONTROL ec;
  EDITC_OPTIONS ec_options;
  if(!msgtxt)
    return 0;
  PrepareEditControl(&ec);
  PrepareEditCOptions(&ec_options);
  eq=AllocEQueue(ma,mfree_adr());
//  ews=CreateLocalWS(&ewsn, ewsb, MAX_TEXT);
  if(header && (cc=header->wsbody[0]))
  {
    hdr_t=AllocWS(cc);
    wstrcpy(hdr_t, header);
  }
  else
    hdr_t=0;
  ConstructEditControl(&ec,ECT_READ_ONLY,ECF_APPEND_EOL,msgtxt,msgtxt->wsbody[0]);
  SetFontToEditCOptions(&ec_options,EDIT_FONT_SMALL);
  CopyOptionsToEditControl(&ec,&ec_options);
  AddEditControlToEditQend(eq,&ec,ma);
  patch_header(&ED_HDR);
  patch_input(&ED_ShowMsg);
  return (CreateInputTextDialog(&ED_ShowMsg,&ED_HDR,eq,1,hdr_t));
}

int ShowCount(void)
{
  WSHDR *hdr, hdrn, *msg, msgn;
  unsigned short hdrb[128], msgb[512];
  unsigned int err;
  SMS_DATA_ROOT *sdr=SmsDataRoot();
  hdr=CreateLocalWS(&hdrn, hdrb, 128);
  msg=CreateLocalWS(&msgn, msgb, 512);
  wsprintf(hdr, PERCENT_T, lgp.LGP_STATISTICS);
  wsprintf(msg, "%t: %c%d\n----------------\n%d%c %t\n%t: %c%d%c\n%t: %c%d%c\n%t: %c%d%c\n%t: %c%d\n----------------\n%d%c %t\n%t: %c%d%c\n%t: %c%d%c\n%t: %c%d\n----------------\n%dKb%c\n%t%c%c%c",
	   lgp.LGP_ALL,
	   0xE013,
	   getCountByType(0),
	   GetCountByIsFileType(0, 0),
	   0xE012,
	   lgp.LGP_IN_SMSDAT,
	   lgp.LGP_IN_A,
	   0xE013,
	   GetCountByIsFileType(0, TYPE_IN_ALL),
	   0xE012,
	   lgp.LGP_OUT,
	   0xE013,
	   GetCountByIsFileType(0, TYPE_OUT),
	   0xE012,
	   lgp.LGP_DRAFT,
	   0xE013,
	   GetCountByIsFileType(0, TYPE_DRAFT),
	   0xE012,
	   lgp.LGP_DAT_FREE,
	   0xE013,
	   100 - sdr->cnt_in_data - sdr->cnt_new_in_data - sdr->cnt_sent_data - sdr->cnt_draft_data -sdr->unk_0_3,
	   GetCountByIsFileType(1, 0),
	   0xE012,
	   lgp.LGP_IS_MSSFILE,
	   lgp.LGP_IN_A,
	   0xE013,
	   GetCountByIsFileType(1, TYPE_IN_ALL),
	   0xE012,
	   lgp.LGP_OUT,
	   0xE013,
	   GetCountByIsFileType(1, TYPE_OUT),
	   0xE012,
	   lgp.LGP_DRAFT,
	   0xE013,
	   GetCountByIsFileType(1, TYPE_DRAFT),
	   GetFreeFlexSpace(CFG_MAIN_FOLDER[0]-'0', &err)/1024,
	   0xE012,
	   lgp.LGP_DISK_FREE,
	   0xE013,
	   CFG_MAIN_FOLDER[0],
	   0xE012
	   );
  return (CreateSimpleShowMsgGui(hdr, msg));
}
