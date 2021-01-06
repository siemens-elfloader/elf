#include "..\..\inc\swilib.h"
#include "main.h"
#include "sms_dat.h"
#include "rect_patcher.h"
#include "smsList.h"
#include "edGui.h"
#include "createMenu.h"
#include "adrList.h"
#include "language.h"

#include "guiIdMan.h"

#include "lgp_pic.h"
#include "CodeShow.h"
#include "popGui.h"
#include "config_data.h"

#include "CSMswaper.h"

#define MENU_MAX_TXT 30


typedef struct
{
  int type;
  int is_tab;
  DLG_CSM *dlg_csm;
}SML_OP; //sms list menu user pointer

typedef struct
{
	SMS_DATA *sd;
	DLG_CSM *dlg_csm;
}SL_UP; //sms list option menu user pointer.

//const HEADER_DESC sms_menuhdr_all={0,0,0,0,NULL,(int)LGP_ALL,LGP_NULL};
//const HEADER_DESC sms_menuhdr_in_r={0,0,0,0,NULL,(int)LGP_IN_R,LGP_NULL};
//const HEADER_DESC sms_menuhdr_in_n={0,0,0,0,NULL,(int)LGP_IN_N,LGP_NULL};
//const HEADER_DESC sms_menuhdr_out={0,0,0,0,NULL,(int)LGP_OUT,LGP_NULL};
//const HEADER_DESC sms_menuhdr_draft={0,0,0,0,NULL,(int)LGP_DRAFT,LGP_NULL};
//const HEADER_DESC sms_menuhdr_in_a={0,0,0,0,NULL,(int)LGP_IN_A,LGP_NULL};

//const HEADER_DESC sms_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};
//const int hdr_icon[]={(int)"0:\\ZBin\\MySMSYS\\new.png",0};
const HEADER_DESC sms_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

const HEADER_DESC slop_menuhdr={0,0,0,0,NULL,LGP_NULL,LGP_NULL};

//------------------------------------------------------

//#define SLOP_MENU_N 7
//#define SLOP_MENU_N_2 (SLOP_MENU_N-1)
#define SLOP_MENU_N_DAT 7
#define SLOP_MENU_N_FILE (SLOP_MENU_N_DAT-1)

const int slop_menusoftkeys[]={0,1,2};
/*
const SOFTKEY_DESC slop_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_SELECT},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};
*/
extern SOFTKEY_DESC ed_menu_sk[];
const SOFTKEYSTAB slop_menu_skt=
{
  ed_menu_sk,0
  //slop_menu_sk,0
};

//char slop_hdr_text[64];
//const HEADER_DESC slop_menu_hdr={0,0,0,0,NULL,(int)smshdr_text,LGP_NULL};

void slop_menu_reply(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	createEditGUI(su->dlg_csm, su->sd, ED_REPLY, 0);
}

void slop_menu_edit(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	createEditGUI(su->dlg_csm, su->sd, ED_EDIT, 0);
}

void slop_menu_exit(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	SGUI_ID *gstop=(SGUI_ID *)(su->dlg_csm->gstop);
	if(gstop)
	{
		GeneralFunc_flag1(gstop->id, 1);
		popGS(su->dlg_csm);
	}
	GeneralFuncF1(1);
}

void slop_menu_del(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	if(su->sd->isfile)
		deleteFile(su->sd, 0);
	else
		deleteDat(su->sd, 0);
	delSDList(su->sd);
}

void slop_menu_save_as_file(GUI *data)
{
  SL_UP *su=MenuGetUserPointer(data);
  GeneralFuncF1(1);
  if((!(su->sd->isfile))&&((su->sd->id)>0))
  {
    if(saveFile(su->sd->SMS_TEXT, su->sd->Number, su->sd, su->sd->type, 2))
    {
      deleteDat(su->sd, 0);
      delSDList(su->sd);
    }
  }
}

void slop_menu_export_txt(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	if(su->sd)
		ShowFileErrCode(ExportOneToTxt(su->sd));
}

void slop_menu_move_to_archive(GUI *data)
{
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	if(su->sd)
	{
		int k=MoveToArchive(su->sd);
		if(k==1)
		{
			if(!su->sd->isfile) deleteDat(su->sd, 0);
			delSDList(su->sd);
		}
		else
			ShowFileErrCode(k);
	}
}

void slop_menu_send(GUI *data)
{
	char *num;
	WSHDR *wst;
	SL_UP *su=MenuGetUserPointer(data);
	GeneralFuncF1(1);
	if(su->sd)
	{
		num=su->sd->Number;
		wst=su->sd->SMS_TEXT;
		if(strlen(num))
		{
			WSHDR *ws=AllocWS(wst->wsbody[0]);
			wstrcpy(ws, wst);
			SNEDSMS_CSM_ID=SendSMS(ws, num, MMI_CEPID, MSG_SMS_RX-1, 6);
			if(CFG_ENA_SAVE_SENT) saveFile(wst, num, su->sd, TYPE_OUT, 2);
			if(!su->sd->isfile) deleteDat(su->sd, 0);
			else deleteFile(su->sd, 0);
			delSDList(su->sd);
			DoSendBackGround(su->dlg_csm);
			//readAllSMS();
		}
	}
}

const MENUPROCS_DESC slop_procs_dat[SLOP_MENU_N_DAT]=
{
	slop_menu_reply,
	slop_menu_edit,
	slop_menu_del,
	slop_menu_save_as_file,
	slop_menu_export_txt,
	slop_menu_move_to_archive,
	slop_menu_exit,
};

int slop_lgp_dat[SLOP_MENU_N_DAT]=
{
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
};

const MENUPROCS_DESC slop_procs_file[SLOP_MENU_N_FILE]=
{
	slop_menu_reply,
	slop_menu_edit,
	slop_menu_del,
	slop_menu_export_txt,
	slop_menu_move_to_archive,
	slop_menu_exit,
};

int slop_lgp_file[SLOP_MENU_N_FILE]=
{
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
	(int)LGP_NULL,
};

void slop_menu_ghook(void *data, int cmd)
{
  if(cmd==3)
  {
    SL_UP *su=MenuGetUserPointer(data);
    mfree(su);
  }
  if(cmd==2) //create
  {
    WSHDR *hdr_t=AllocWS(32);
    wsprintf(hdr_t, PERCENT_T, lgp.LGP_OPTIONS);
    SetHeaderText(GetHeaderPointer(data), hdr_t, malloc_adr(), mfree_adr());
  }
}

#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);
int slop_menu_onkey(void *data, GUI_MSG *msg)
{
  int n;
  SL_UP *su;
  if(!IsUnlocked()) TempLightOn(3, 0x7FFF);
  if(msg->keys==0x1)
  {
    return 1;
  }
  if((msg->keys==0x18)||(msg->keys==0x3D))
  {
    n=GetCurMenuItem(data);
  DO_PROC:
    su=MenuGetUserPointer(data);
    if(!su->sd)
      return 1;
    if(n==0 && su->sd->type==TYPE_DRAFT)
    {
      slop_menu_send(data);
      return 1;
    }
    if(su->sd->isfile)
    {
      if(n>=SLOP_MENU_N_FILE)
	return 0;
      slop_procs_file[n](data);
      return 1;
    }
    else
    {
      if(n>=SLOP_MENU_N_DAT)
	return 0;
      slop_procs_dat[n](data);
      return 1;
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

#ifndef WITHOUT_OP_ICON

#ifdef NEWSGOLD
#ifdef ELKA
int slop_item_icons[]={0x538,0};
#else
#ifdef S68
int slop_item_icons[]={0x576,0};
#else
int slop_item_icons[]={0x564,0};
#endif
#endif
#endif

#endif

void slop_menu_itemhndl(void *data, int curitem, void *user_pointer)
{
  SL_UP *su=MenuGetUserPointer(data);
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 150);
  if(su->sd)
  {
    if(curitem==0 && su->sd->type==TYPE_DRAFT)
    {
      wsprintf(ws, PERCENT_T, lgp.LGP_SEND);
      goto GO_P;
    }
    if(su->sd->isfile)
    {
      if(curitem>=SLOP_MENU_N_FILE)
	goto SLOP_ERR;
      wsprintf(ws, PERCENT_T, slop_lgp_file[curitem]);
    }
    else
    {
      if(curitem>=SLOP_MENU_N_DAT)
	goto SLOP_ERR;
      wsprintf(ws, PERCENT_T, slop_lgp_dat[curitem]);
    }
  }
  else
SLOP_ERR:
  wsprintf(ws, PERCENT_T, lgp.LGP_ERR);
GO_P:
#ifndef WITHOUT_OP_ICON
  SetMenuItemIconArray(data, item, slop_item_icons);
  SetMenuItemIcon(data, curitem, 0);
#endif
  SetMenuItemText(data, item, ws, curitem);
}

const MENU_DESC slop_menu=
{
  8,slop_menu_onkey,slop_menu_ghook,NULL,
  slop_menusoftkeys,
  &slop_menu_skt,
#ifdef WITHOUT_OP_ICON
  0x10,
#else
  0x11,//Right align
#endif
  slop_menu_itemhndl,
  0,//menuitems,
  0,//menuprocs,
  0
};
int CreateslOpMenu(DLG_CSM *dlg_csm, SMS_DATA *sd, int type)
{
	int item_n;
	SL_UP *su=malloc(sizeof(SL_UP));
	su->dlg_csm=dlg_csm;
	su->sd=sd;

	//patch_header(&sms_menuhdr);
	patch_option_header(&slop_menuhdr);
	if(sd->isfile==1)
		item_n=SLOP_MENU_N_FILE;
	else
		item_n=SLOP_MENU_N_DAT;
	return (CreateSLMenu_30or2(&slop_menu,&slop_menuhdr,0,item_n, su));
//	if(!sd)
//		return (CreateSLMenu(&slop_menu_3,&sms_menuhdr,0, 1, su));
//	if(sd->isfile==1)
//		return (CreateSLMenu(&slop_menu_2,&sms_menuhdr,0,SLOP_MENU_N_FILE, su));
//	else
//		return (CreateSLMenu(&slop_menu,&sms_menuhdr,0,SLOP_MENU_N_DAT, su));
}

//------------------------------------------------------

const int sms_menusoftkeys[]={0,1,2};

SOFTKEY_DESC sms_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB sms_menu_skt=
{
  sms_menu_sk,0
};

int sms_menu_onkey(void *data, GUI_MSG *msg)
{
  SML_OP *so=MenuGetUserPointer(data);
  SMS_DATA *sd=getSMSDataByType(GetCurMenuItem(data), so->type);
  int n=GetMenuItemCount(data);
	
  if(!IsUnlocked())
    TempLightOn(3, 0x7FFF);

  if(msg->keys==0x05)
  {
    if(n) createEditGUI(so->dlg_csm, sd, (sd->type==TYPE_DRAFT)?ED_EDIT:ED_REPLY, 0);
  }
  else if((msg->keys==0x18))//||(msg->keys==0x3D))
  {
    //if(!n)
    //	CreateslOpMenu(so->dlg_csm, 0, so->type);
    //else
    if(n) CreateslOpMenu(so->dlg_csm, sd, so->type);
    else return 1;
  }
  else if(msg->keys==0x3D)
  {
    if(n) createEditGUI(so->dlg_csm, sd, ED_VIEW, so->type);
    else return 1;
  }
  else if(msg->keys==0x1)
  {
    popGS(so->dlg_csm);
    return 1;
  }
  if((msg->gbsmsg->msg==KEY_DOWN)&&(n>0)&&(sd))
  {
    int i=msg->gbsmsg->submess;
    if((i=='7')) //key 7 for delete
    {
      if(sd->isfile)
	deleteFile(sd, 0);
      else
	deleteDat(sd, 0);
      delSDList(sd);
      //Menu_SetItemCountDyn(data, getCountByType(so->type));
      RefreshGUI();
      return (-1);
    }
    else if((i=='9')&&(!sd->isfile))
    {
      if(saveFile(sd->SMS_TEXT, sd->Number, sd, sd->type, 2))
      {
	int k=GetCurMenuItem(data);
	deleteDat(sd, 0);
	delSDList(sd);
	SetCursorToMenuItem(data, (k==(n-1))?k:(k+1));
      }
      RefreshGUI();
      return (-1);
    }
    else if((i=='*')) //*键,查看号码信息
    {
      WSHDR *msg=AllocWS(128);
#ifdef NO_CS
      wsprintf(msg, "%t:\n%s", (sd->type==TYPE_OUT||sd->type==TYPE_DRAFT)?lgp.LGP_TO:lgp.LGP_FROM, sd->Number);
#else
      {
	char num[32];
	WSHDR csloc, *cs;
	unsigned short csb[30];
	cs=CreateLocalWS(&csloc,csb,30);
	strcpy(num, sd->Number);
	GetProvAndCity(cs->wsbody, num);
	wsprintf(msg, "%t:\n%s\n%t:\n%w", (sd->type==TYPE_OUT||sd->type==TYPE_DRAFT)?lgp.LGP_TO:lgp.LGP_FROM, sd->Number, lgp.LGP_CODESHOW, cs);
      }
#endif
      ShowMSG_ws(1, msg);
    }
    else if((i=='8'))
    {
      int k;
      //	extern int ExportOneToTxt(SMS_DATA *sd);
      k=ExportOneToTxt(sd);
      ShowFileErrCode(k);
    }
    else if(i=='4')
    {	
      int k;
      //extern int MoveToArchive(SMS_DATA *sd);
      k=MoveToArchive(sd);
      if(k==1)
      {
	if(!sd->isfile) deleteDat(sd, 0);
	delSDList(sd);
	RefreshGUI();
	return (-1);
      }
      ShowFileErrCode(k);
    }
    else if(i==RIGHT_BUTTON && !so->is_tab)
    {
      createEditGUI(so->dlg_csm, sd, ED_EDIT, 0);
      return 1;
    }
    else if(i==LEFT_BUTTON && !so->is_tab)
    {
      return 1;
    }
  }
  return 0;
}

#ifdef ELKA
#define ICON_UNK 0x5B8
#define ICON_OUT 0x5B8
#define ICON_IN_R 0x5B5
#define ICON_IN_N	0x5B6
#define ICON_DRAFT 0x5B2
#define ICON_IN_ALL 0x5B5
#define ICON_LINE 0x537
#else
#define ICON_UNK 0x5E4
#define ICON_OUT 0x5E4
#define ICON_IN_R 0x5E1
#define ICON_IN_N	0x5E2
#define ICON_DRAFT 0x5DE
#define ICON_IN_ALL 0x5E1
#define ICON_LINE 0x563
#endif

//const int hdr_icon[]={0X5D0,0};
//main 0x347
//sent 0x515
//draft 0x5C4
//inbox 0x5C5
//edit 0x4BD
//view 0x29A
//adrbk 0x290
/*
const int HDRIC_UNK[]={0x347, 0};
const int HDRIC_OUT[]={0x515, 0};
const int HDRIC_IN_R[]={0x5C5, 0};
const int HDRIC_IN_N[]={0x5C5, 0};
const int HDRIC_DRAFT[]={0x5C4, 0};
const int HDRIC_IN_ALL[]={0x5C5, 0};
*/
int SL_HDR_ICONS[7][2]=
{
#ifdef NEWSGOLD
#ifdef ELKA
  {0x2AB, 0},
  {0x5A4, 0},
  {0x2AB, 0},
  {0x2AB, 0},
  {0x598, 0},
  {0x2AB, 0},
  {0,0}
#else
  {0x347, 0},
  {0x515, 0},
  {0x5C5, 0},
  {0x5C5, 0},
  {0x5C4, 0},
  {0x5C5, 0},
  {0,0}
#endif
#endif
};
//extern void SetHeaderIcon(void *hdr_pointer, const int *icon, void *malloc_adr, void *mfree_adr);
#ifdef S68
int SL_ICONS[8]={0, 0, 0, 0, 0, 0, 0x575, 0};
int ESL_ICONS[8]={0, 0, 0, 0, 0, 0, 0x575, 0};
#else
int SL_ICONS[8]={ICON_UNK, ICON_OUT, ICON_IN_R, ICON_IN_N, ICON_DRAFT, ICON_IN_ALL, ICON_LINE, 0};
int ESL_ICONS[8]={ICON_UNK, ICON_OUT, ICON_IN_R, ICON_IN_N, ICON_DRAFT, ICON_IN_ALL, ICON_LINE, 0};
#endif
void sms_menu_itemhndl(void *data, int curitem, void *user_pointer)
{
	SML_OP *so=(SML_OP *)user_pointer;
	int type=so->type;
	int isems=0;
	void *item=AllocMLMenuItem(data);
	WSHDR *ws1=AllocMenuWS(data, MENU_MAX_TXT);
	WSHDR *ws2=AllocMenuWS(data, 150);
	WSHDR wsloc, *wn;
	unsigned short wsb[150];
	wn=CreateLocalWS(&wsloc,wsb,150);
	SMS_DATA *sdl=getSMSDataByType(curitem, type);
	if(sdl)
	{
		if(sdl->SMS_TEXT)
			wstrncpy(ws1, sdl->SMS_TEXT, MENU_MAX_TXT);
		else
			goto AL_ERR;
			
		if(!strlen(sdl->Number))
			CutWSTR(ws2, 0);
	#ifdef LANG_CN
		else
		{
			int is_fetion=0;
			if(!strncmp(num_fetion, sdl->Number, 5)) is_fetion=1;
			if(findNameByNum(wn, is_fetion?(sdl->Number+5):sdl->Number))
			{
				if(is_fetion) wsprintf(ws2, "%w(%t)", wn, lgp.LGP_FETION);
				else	wstrcpy(ws2, wn);
			}
			else
				wsprintf(ws2, PERCENT_S, sdl->Number);
		}
	#else
		else if(findNameByNum(wn, sdl->Number))
			wstrcpy(ws2, wn);
		else
			wsprintf(ws2, PERCENT_S, sdl->Number);
	#endif
	}
	else
	{
AL_ERR:
		wsprintf(ws1, PERCENT_T, lgp.LGP_ERR);
		CutWSTR(ws2, 0);
	}
	if(sdl)
	{
	  extern int IsWsSmall(WSHDR *ws);
	  if((sdl->msg_type&ISEMS) || sdl->cnt_r>1)
	    isems=1;
	  else
	  {
	    if((sdl->msg_type&IS7BIT) || IsWsSmall(sdl->SMS_TEXT))
	    {
	      if(sdl->SMS_TEXT->wsbody[0]>SEG7_MAX) isems=1;
	    }
	    else
	    {
	      if(sdl->SMS_TEXT->wsbody[0]>SEGN_MAX) isems=1;
	    }
	  }
	}
	SetMenuItemIconArray(data, item, (isems)?ESL_ICONS:SL_ICONS);
	SetMenuItemIcon(data, curitem, (sdl)?(sdl->type):6);
	SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

const char SM_FORMAT[]="%t%c%d/%d";
const SOFTKEY_DESC SK_VIEW_PIC={0x003D,0x0000,(int)LGP_VIEW_PIC};
SOFTKEY_DESC SK_OK2={0x0018,0x0000,LGP_NULL};
void sms_menu_ghook(void *data, int cmd)
{
  SML_OP *so=MenuGetUserPointer(data);
  if(cmd==0x0A)
  {
    int n=getCountByType(so->type);
    int cur=GetCurMenuItem(data);
    if(cur>=n) SetCursorToMenuItem(data, 0);
    Menu_SetItemCountDyn(data, n);
    //patch_header(&sms_menuhdr);
    DisableIDLETMR();
  }
  else if(cmd==7)
  {
    //extern void SetMenuSoftKey(void *gui, const SOFTKEY_DESC *,int n);
    int n=getCountByType(so->type);
    int cur_n=GetCurMenuItem(data)+1;
    if(!n) cur_n=0;
    WSHDR *hdr_t=AllocWS(64);
    void *hdr_p=GetHeaderPointer(data);
    void *ma=malloc_adr();
    void *mf=mfree_adr();
    switch(so->type)
    {
    case 0:
      wsprintf(hdr_t, SM_FORMAT, lgp.LGP_ALL, 0xE01D, cur_n, n);
      break;
    case TYPE_IN_R:
      wsprintf(hdr_t, SM_FORMAT, lgp.LGP_IN_R, 0xE01D, cur_n, n);
      break;
    case TYPE_IN_N:
      wsprintf(hdr_t, SM_FORMAT, lgp.LGP_IN_N, 0xE01D, cur_n, n);
      break;
    case TYPE_OUT:
      wsprintf(hdr_t, SM_FORMAT, lgp.LGP_OUT, 0xE01D, cur_n, n);
      break;
    case TYPE_DRAFT:
      wsprintf(hdr_t, SM_FORMAT, lgp.LGP_DRAFT, 0xE01D, cur_n, n);
      break;
    case TYPE_IN_ALL:
      wsprintf(hdr_t, SM_FORMAT, lgp.LGP_IN_A, 0xE01D, cur_n, n);
      break;
    case TYPE_FILTER:
      wsprintf(hdr_t, SM_FORMAT, lgp.LGP_FILTER, 0xE01D, cur_n, n);
      break;
    default:
      CutWSTR(hdr_t, 0);
      break;
    }
    SetHeaderText(hdr_p, hdr_t, ma, mf);
    extern int MM_HDR_ICONS[]; //main.c
    if(!so->is_tab) SetHeaderIcon(hdr_p, SL_HDR_ICONS[(so->type>6)?0:so->type], ma, mf);
    else SetHeaderIcon(hdr_p, MM_HDR_ICONS, ma, mf);
    //if(n) SetSoftKey(data,&SK_VIEW_PIC,SET_SOFT_KEY_M);
    if(n) SetMenuSoftKey(data,&SK_VIEW_PIC,SET_SOFT_KEY_M);
    else SetMenuSoftKey(data,&SK_OK2,SET_SOFT_KEY_N);
  }
  else if(cmd==3)
  {
    mfree(so);
  }
  else if(cmd==5)
  {
    const char *lgpN;
    switch(so->type)
    {
    case 0:
      lgpN=lgp.LGP_ALL;
      break;
    case TYPE_IN_R:
      lgpN=lgp.LGP_IN_R;
      break;
    case TYPE_IN_N:
      lgpN=lgp.LGP_IN_N;
      break;
    case TYPE_OUT:
      lgpN=lgp.LGP_OUT;
      break;
    case TYPE_DRAFT:
      lgpN=lgp.LGP_DRAFT;
      break;
    case TYPE_IN_ALL:
      lgpN=lgp.LGP_IN_A;
      break;
    case TYPE_FILTER:
      lgpN=lgp.LGP_FILTER;
      break;
    default:
      lgpN=0;
    }
    if(lgpN) UpdateDlgCsmName(so->dlg_csm, lgpN);
  }
}
const ML_MENU_DESC sms_menu=
{
  8,sms_menu_onkey,sms_menu_ghook,NULL,
  sms_menusoftkeys,
  &sms_menu_skt,
  0x11,//0x11,
  sms_menu_itemhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  1 //line
};

void *GetSLUserPointer(void *dlg_csm, int type, int is_tab)
{
  SML_OP *so=malloc(sizeof(SML_OP));
  so->type=type;
  so->is_tab=is_tab;
  so->dlg_csm=dlg_csm;
  return so;
}

int showSMSList(void *dlg_csm, int type)
{
  unsigned int id;
  SML_OP *so=GetSLUserPointer(dlg_csm, type, 0);//=malloc(sizeof(SML_OP));
  //so->type=type;
  //so->is_tab=0;
  //so->dlg_csm=dlg_csm;
  patch_header(&sms_menuhdr);
  id=CreateMLMenu(&sms_menu,&sms_menuhdr,0,getCountByType(type), so);
  pushGS(dlg_csm, id);
  return id;
}
