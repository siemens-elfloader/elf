#include "..\..\inc\swilib.h"
#include "..\..\inc\playsound.h"
#include "MySMSYS_ipc.h"
#include "adrList.h"
#include "rect_patcher.h"
#include "sms_dat.h"
#include "smsList.h"
#include "language.h"
#include "edGui.h"

#include "main.h"
#include "createMenu.h"

#include "guiIdMan.h"

#include "popGui.h"
#include "config_data.h"
#include "conf_loader.h"

#include "NewDatReader.h"
#include "string_works.h"
#include "iconpack.h"
#include "key_hook.h"
#include "CSMswaper.h"
#include "TabGui.h"

extern void kill_data(void *p, void (*func_p)(void *));

unsigned int DAEMON_CSM_ID=0;
unsigned int DIALOG_CSM_ID=0;
unsigned int DIALOG_GUI_ID=0;

unsigned int SNEDSMS_CSM_ID=0;

typedef struct
{
	CSM_DESC csmd;
	WSHDR name;
}DLGCSM_DESC;
typedef struct
{
	unsigned int csm_id;
	int code;
	char *fname;
}IPC_DATA_DAEMON;

typedef struct
{
	int ipc_msg;
}IPC_DATA_DLG;

#define MAX_DLG 32

typedef struct
{
  CSM_RAM csm;
}DEAMON_CSM;

int IPC_SUB_MSG=0;
int SMS_INDEX=0;
IPC_REQ daemon_ipc=
{
	my_ipc_name,
	my_ipc_name,
	NULL
};
IPC_DATA_DAEMON ipc_data_daemon;

IPC_REQ dlg_ipc=
{
	my_ipc_name,
	my_ipc_name,
	NULL
};
IPC_DATA_DLG ipc_data_dlg;
const int minus11=-11;

char *num_from_ipc=0;
char *text_utf8=0;
int opmsg_id=0;
WSHDR *text_ws=0;

int is_fview=0;
char filename[128]={0};
int new_sms_n=0;
char sms_dat[128];
char ems_admin_dat[128];
//---------------------------------------
//csm_id man

unsigned int DlgCsmIDs[MAX_DLG];

void dlgIDsInit(void)
{
	int i=0;
	for(;i<MAX_DLG;i++)
		DlgCsmIDs[i]=0;
}

int addCSMid(unsigned int *id_pool, unsigned int id)
{
	int i=0;
	for(;i<MAX_DLG;i++)
	{
		if(id_pool[i]==0)
		{
			id_pool[i]=id;
			return i;
		}
	}
	return -1;
}
void addCSMidForced0(unsigned int *id_pool, unsigned int id)
{
	CloseCSM(id_pool[0]);
	id_pool[0]=id;
}
void delCSMid(unsigned int *id_pool, unsigned int id)
{
	int i=0;
	for(;i<MAX_DLG;i++)
	{
		if(id_pool[i]==id)
		{
			id_pool[i]=0;
			return;
		}
	}
}

void closeAllDlgCSM(unsigned int *id_pool)
{
	int i=0;
	for(;i<MAX_DLG;i++)
	{
		if(id_pool[i]!=0)
		{
			CloseCSM(id_pool[i]);
			id_pool[i]=0;
		}
	}
}

int IsNoDlg(unsigned int *id_pool)
{
	int i=0;
	for(;i<MAX_DLG;i++)
	{
		if(id_pool[i])
			return 0;
	}
	return 1;
}

int IsCsmExist(void *dlg_csm)
{
  int i=0;
  unsigned int id;
  for(;i<MAX_DLG;i++)
  {
    if((id=DlgCsmIDs[i]))
    {
      if(FindCSMbyID(id)==dlg_csm)
	return 1;
    }
  }
  return 0;
}

int IsHaveDlgGuiOnTop(void)
{
  int i=0;
  unsigned int id;
  DLG_CSM *dlg_csm;
  SGUI_ID *gs;
  for(;i<MAX_DLG;i++)
  {
    if((id=DlgCsmIDs[i]))
    {
      if((dlg_csm=(DLG_CSM *)FindCSMbyID(id)))
      {
	gs=(SGUI_ID *)(dlg_csm->gstop);
	while(gs)
	{
	  if(IsGuiOnTop(gs->id)) return 1;
	  gs=gs->next;
	}
      }
    }
  }
  return 0;
}

int isTheLastDlg(unsigned int *id_pool, unsigned int id)
{
	return 0;
}

//---------------------------------------

const IPC_REQ smp_ipc=
{
  my_ipc_name,
  my_ipc_name,
  NULL
};

void SendSimpleIpcMsg(int submess)
{
  GBS_SendMessage(MMI_CEPID,MSG_IPC,submess,&smp_ipc);
}
//---------------------------------------
//main menu
const int main_menusoftkeys[]={0,1,2};
SOFTKEY_DESC main_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_NULL},
  {0x0001,0x0000,(int)LGP_NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};


const SOFTKEYSTAB main_menu_skt=
{
  main_menu_sk,0
};
HEADER_DESC main_menuhdr={0,0,0,0,NULL,(int)LGP_NULL,LGP_NULL};
#define MAIN_MENU_N 6

void mm_newsms(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	newSMS(dlg_csm);
}

void mm_insms_n(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_IN_N);
}

void mm_insms_r(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_IN_R);
}

void mm_insms_all(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_IN_ALL);
}

void mm_outsms(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_OUT);
}

void mm_draftsms(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, TYPE_DRAFT);
}
/*
void mm_allsms(GUI *gui)
{
	DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
	showSMSList(dlg_csm, 0);
}
*/
unsigned int CreateOthMenu(void *dlg_csm);

void mm_oth(GUI *gui)
{
  DLG_CSM *dlg_csm=MenuGetUserPointer(gui);
  CreateOthMenu(dlg_csm);
}


int MENU_TEXT[MAIN_MENU_N]=
{
  LGP_NULL,
  LGP_NULL,
  LGP_NULL,
  LGP_NULL,
  LGP_NULL,
  //LGP_NULL,
  LGP_NULL
};

const MENUPROCS_DESC procs_mmenu[MAIN_MENU_N]=
{
  mm_newsms,
  mm_insms_n,
  mm_insms_all,
  mm_outsms,
  mm_draftsms,
  //mm_allsms,
  mm_oth,
};

int MM_ITEM_ICONS[]={0x564,0x564,0x564,0x564,0x564,0x564,0x564,0};
int MM_HDR_ICONS[]={0x5C5, 0};

int main_menu_onkey(void *data, GUI_MSG *msg)
{
#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);
  int n;
  if(!IsUnlocked()) TempLightOn(3, 0x7FFF);

  if((msg->keys==0x1)/* || (msg->keys==0x28)*/)
  {
    void *dlg_csm=MenuGetUserPointer(data);
    popGS(dlg_csm);
    return 1;
  }
  if((msg->keys==0x18)||(msg->keys==0x3D)/*||(msg->keys==0x27)*/)
  {
    n=GetCurMenuItem(data);
  DO_P:
    if(n<0 || n>=MAIN_MENU_N)
      return 0;
    procs_mmenu[n](data);
    return 0;
  }
  if(msg->gbsmsg->msg==KEY_DOWN)
  {
    n=msg->gbsmsg->submess;
    if(n>='1' && n<='9')
    {
      n-='1';
      goto DO_P;
    }
    if(n=='*')
    {
      extern int ShowCount(void); //ed_gui.c
      UpdateDlgCsmName(MenuGetUserPointer(data), lgp.LGP_STATISTICS);
      ShowCount();
    }
  }
  return 0;
}

const char MM_FORMAT[]="%t%c%d";
void main_menu_itemhndl(void *data, int curitem, void *user_pointer)
{
  void *item=AllocMenuItem(data);
  WSHDR *ws=AllocMenuWS(data, 150);
  switch(curitem)
  {
  //case 6:
  case 5:
  case 0:
    wsprintf(ws, PERCENT_T, MENU_TEXT[curitem]);
    break;
  case 1:
    wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(TYPE_IN_N));
    break;
  case 2:
    wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(TYPE_IN_ALL));
    break;
  case 3:
    wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(TYPE_OUT));
    break;
  case 4:
    wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(TYPE_DRAFT));
    break;
  //case 5:
  //  wsprintf(ws, MM_FORMAT, MENU_TEXT[curitem], 0xE01D, getCountByType(0));
  //  break;
  default:
    wsprintf(ws, PERCENT_T, lgp.LGP_ERR);
    break;
  }
  SetMenuItemIconArray(data, item, MM_ITEM_ICONS);
  SetMenuItemIcon(data, curitem, curitem);
  SetMenuItemText(data, item, ws, curitem);
}
void main_menu_ghook(void *gui, int cmd)
{
  if(cmd==5)
  {
    void *dlg_csm=MenuGetUserPointer(gui);
    UpdateDlgCsmName(dlg_csm, lgp.LGP_MSS_MAINMENU);
  }
  if(cmd==7)
  {
    SetHeaderIcon(GetHeaderPointer(gui), MM_HDR_ICONS, malloc_adr(), mfree_adr());
  }
  if(cmd==0xA)
  {
    DisableIDLETMR();
  }
}
const MENU_DESC main_menu=
{
  8,main_menu_onkey,main_menu_ghook,NULL,
  main_menusoftkeys,
  &main_menu_skt,
  0x11,//
  main_menu_itemhndl,
  NULL,//main_menuitems,//menuitems,
  NULL, //main_menuprocs,//menuprocs,
  MAIN_MENU_N
};

int CreateMainMenu(DLG_CSM *dlg_csm)
{
  int id;
  patch_header(&main_menuhdr);
  id=CreateSLMenu(&main_menu, &main_menuhdr, 0, MAIN_MENU_N, dlg_csm);
  pushGS(dlg_csm, id);
  return id;
}

//--------------------------------------------------

int dialogcsm_onmessage(CSM_RAM *data,GBS_MSG* msg)
{
	DLG_CSM *csm=(DLG_CSM *)data;
	if(msg->msg==MSG_GUI_DESTROYED)
	{
		if((int)msg->data0==csm->gui_id)
			data->state=-3;
	}
	return 1;
}

static unsigned short dialogcsm_name_body[32]={7,'M','y','S','M','S','Y','S'};
void UpdateDlgCsmName(DLG_CSM *csm, const char *lgp)
{
  DLGCSM_DESC *dcd=csm->csm.constr;
  WSHDR *name=&dcd->name;
  if(!name->wsbody || name->wsbody==dialogcsm_name_body)
    name->wsbody=malloc(32*sizeof(short));
  wsprintf(name, PERCENT_T, lgp);
}

static void dialogcsm_oncreate(CSM_RAM *data)
{
  DLG_CSM *csm=(DLG_CSM *)data;
  csm->gstop=0;
/*  if(
     (IPC_SUB_MSG!=SMSYS_IPC_FVIEW)
       &&(IPC_SUB_MSG!=SMSYS_IPC_NEWSMS)
	 &&(IPC_SUB_MSG!=SMSYS_IPC_NEWSMS_NUM)
	   &&(IPC_SUB_MSG!=SMSYS_IPC_SEND_UTF8)
	     &&(IPC_SUB_MSG!=SMSYS_IPC_NEW_IN_WIN)
	       )
  {
    readAllSMS();
  }*/
  switch(IPC_SUB_MSG)
  {
  case MY_SMSYS_IPC_START:
  case SMSYS_IPC_MAIN:
    //csm->gui_id=CreateMainMenu(csm);
    csm->gui_id=CreateTabMenu(csm);
    break;
  case SMSYS_IPC_NEWSMS:
    csm->gui_id=newSMS(csm);
    break;
  case SMSYS_IPC_IN_NEW:
    csm->gui_id=showSMSList(csm, TYPE_IN_N);
    break;
  case SMSYS_IPC_IN_RD:
    csm->gui_id=showSMSList(csm, TYPE_IN_R);
    break;
  case SMSYS_IPC_OUT:
    csm->gui_id=showSMSList(csm, TYPE_OUT);
    break;
  case SMSYS_IPC_DRAFT:
    csm->gui_id=showSMSList(csm, TYPE_DRAFT);
    break;
  case SMSYS_IPC_ALL:
    csm->gui_id=showSMSList(csm, 0);
    break;
  case SMSYS_IPC_TLAST:
    if(!(csm->gui_id=viewTheLastNew(csm)))
      data->state=-3;//csm->gui_id=CreateTabMenu(csm);
      //csm->gui_id=CreateMainMenu(csm);
    break;
  case SMSYS_IPC_IN_ALL:
    csm->gui_id=showSMSList(csm, TYPE_IN_ALL);
    break;
  case SMSYS_IPC_NEW_IN_WIN:
    if(!(csm->gui_id=StartIncomingWin(csm)))
      data->state=-3; //close
    break;
  case SMSYS_IPC_NEWSMS_NUM:
    if((!num_from_ipc)||(!(csm->gui_id=newSMSWithNum(csm, num_from_ipc))))
      data->state=-3;//csm->gui_id=CreateTabMenu(csm);//csm->gui_id=CreateMainMenu(csm);
    num_from_ipc=0;
    break;
  case SMSYS_IPC_SEND_UTF8:
    if((!text_utf8)||(!(csm->gui_id=newSMSWithUtf8Text(csm, text_utf8))))
      data->state=-3;//csm->gui_id=CreateTabMenu(csm);//csm->gui_id=CreateMainMenu(csm);
    text_utf8=0;
    break;
  case SMSYS_IPC_QN_OPMSG:
  case SMSYS_IPC_QR_OPMSG:
  case SMSYS_IPC_VIEW_OPMSG:
  case SMSYS_IPC_REPLY_OPMSG:
    if(!(csm->gui_id=DoByOpmsgId(csm, IPC_SUB_MSG, opmsg_id)))
      data->state=-3;//csm->gui_id=CreateTabMenu(csm);//csm->gui_id=CreateMainMenu(csm);
    opmsg_id=0;
    break;
  case SMSYS_IPC_SEND_WS:
    if(!text_ws || !(csm->gui_id=CreateSmsWS(csm, text_ws)))
      data->state=-3;
    text_ws=0;
    break;
  case SMSYS_IPC_FVIEW:
    if (!strlen(filename) || !(csm->gui_id=ViewFile(csm, filename)))
      data->state=-3; //close
    //{
    //  readAllSMS();
    //  csm->gui_id=CreateMainMenu(csm);
    //}
    filename[0]=0;
    break;
  default:
    data->state=-3;//csm->gui_id=CreateTabMenu(csm);//csm->gui_id=CreateMainMenu(csm);
  }
  if(addCSMid(DlgCsmIDs, csm->csm.id)<0)
    addCSMidForced0(DlgCsmIDs, csm->csm.id);
}

void FreeCsmd(void *csmd)
{
	mfree(csmd);
}
static void dialogcsm_onclose(CSM_RAM *data)
{
  DLG_CSM *dlg_csm=(DLG_CSM *)data;
  DLGCSM_DESC *dcd=dlg_csm->csm.constr;
  delCSMid(DlgCsmIDs, dlg_csm->csm.id);
  if(dcd->name.wsbody!=dialogcsm_name_body && dcd->name.wsbody!=0)
    mfree(dcd->name.wsbody);
  mfree(dcd);
}

const DLGCSM_DESC DIALOGCSM =
{
  {
    dialogcsm_onmessage,
    dialogcsm_oncreate,
#ifdef NEWSGOLD
    0,
    0,
    0,
    0,
#endif
    dialogcsm_onclose,
    sizeof(DLG_CSM),
    1,
    &minus11
  },
  {
    dialogcsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    31
  }
};


GBSTMR ld_tmr;

int is_readall=0;
extern int CheckAll(void);
unsigned int CreateDialogCSM(void)
{
  DLG_CSM dlg_csm;
  DLGCSM_DESC *dcd=malloc(sizeof(DLGCSM_DESC));
  zeromem(&dlg_csm, sizeof(DLG_CSM));
  memcpy(dcd, &DIALOGCSM, sizeof(DLGCSM_DESC));
  if(!cltop) SUBPROC((void *)ConstructListN);
  if(IPC_SUB_MSG!=SMSYS_IPC_FVIEW)
  {
    if(sdltop)
    {
      if(!is_readall) SUBPROC((void *)CheckAll);
    }
    else
    {
      GBS_DelTimer(&ld_tmr);
      SUBPROC((void *)ReadAllSmsN);
    }
  }
  //if(sdltop && IPC_SUB_MSG!=SMSYS_IPC_FVIEW) SUBPROC((void *)CheckAll);
  //if(!sdltop && IPC_SUB_MSG!=SMSYS_IPC_FVIEW) SUBPROC((void *)readAllSMS);
  LoadLangPack();
  LoadIconPack();
  return (CreateCSM(&dcd->csmd,&dlg_csm,2));
}


const IPC_REQ my_ipc_n=
{
	my_ipc_name,
	my_ipc_name,
	NULL
};

GBSTMR chk_tmr;
int tindex=0;
int isnewp=0;
//extern int ReadThisSms(int index);
//GBSTMR n_update_tmr;
/*
void CheckNewProc(void)
{
  if(IsHaveNewSMS())
  {
    GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEW_IN_WIN,&my_ipc_n);
  }
}
*/
void DoNewProc(void)
{
  if(tindex)
  {
    ReadThisSms(tindex, 1);
    tindex=0;
  }
  if(CFG_ENA_NOTIFY) GBS_SendMessage(MMI_CEPID,MSG_IPC,SMSYS_IPC_NEW_IN_WIN,&my_ipc_n);
  else if(!IsNoDlg(DlgCsmIDs))
  {
    //readAllSMS();
    if(IsHaveDlgGuiOnTop()) RefreshGUI();
  }
  isnewp=0;
}

extern short PLAY_ID;
/*
void UpdateNProc(void)
{
	new_sms_n=(SmsDataRoot())->cnt_in_new_sms_dat;
	if((!IsHaveNewSMS())&&(CFG_ENA_NOTIFY))
	{
		SetVibration(0);
		if(PLAY_ID)
		{
			PlayMelody_StopPlayback(PLAY_ID);
			PLAY_ID=0;
		}
	}
}
*/

void UpdateNProc(void)
{
  if(!IsNoDlg(DlgCsmIDs))
  {
    //readAllSMS();
    if(tindex)
    {
      ReadThisSms(tindex, 1);
      tindex=0;
    }
    if(IsHaveDlgGuiOnTop())
    {
      RefreshGUI();
      GBS_SendMessage(MMI_CEPID,KEY_DOWN,0x63); //update screen
    }
  }
}

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}
/*
int GetIcon(void)
{
  int is_file=0, c;
  const char *p=CFG_ICONNEW_PATH;
  while((c=*p++))
  {
    if(c<'0' || c>'9')
    {
      is_file=1;
      break;
    }
  }
  p=CFG_ICONNEW_PATH;
  if(is_file)
  {
    if(IsFileExist(p))
      return (int)p;
  }
  else
    return (str2int(p));
  return 0;
}
*/
void InitDatPath(void)
{
  int x, xl;
  strcpy(sms_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(sms_dat))>0)
    x=sms_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    sms_dat[xl]='\\';
    sms_dat[xl+1]=0;
  }
  strcat(sms_dat, "SMS\\SMS.dat");
  strcpy(ems_admin_dat, CFG_SYSTEM_FOLDER);
  if((xl=strlen(ems_admin_dat))>0)
    x=ems_admin_dat[xl-1];
  if((x!='\\')&&(x!='/'))
  {
    ems_admin_dat[xl]='\\';
    ems_admin_dat[xl+1]=0;
  }
  strcat(ems_admin_dat, "SMS\\EMS_Admin.dat");
}

//int NEW_SMS_ICON;
void InitSetting(void)
{
  InitConfig();
  InitDatPath();
//  NEW_SMS_ICON=GetIcon();
}

#ifdef ELKA

#pragma swi_number=0x36
__swi __arm void SLI_SetState(unsigned char state);

GBSTMR sli_tmr;
int sli_cnt=0;
int sli_sta=0;


void STOP_SLI(void)
{
  GBS_DelTimer(&sli_tmr);
  sli_cnt=0;
  sli_sta=0;
  SLI_SetState(0);
}

void SLI_PROC(void)
{
  if(sli_cnt==1) SLI_SetState(0);
  else if(sli_cnt==0) SLI_SetState(1);
  
  if(sli_cnt>5) sli_cnt=0;
  else sli_cnt++;
  if(new_sms_n>0) GBS_StartTimerProc(&sli_tmr, 216/6, SLI_PROC);
  else STOP_SLI();
}

#endif


int IsSSOnTop(void)
{
//  extern SS_RAM *GetScreenSaverRam(void);
  SS_RAM *ss_ram;
  if(!(ss_ram=GetScreenSaverRAM())) return 0;
  if((ss_ram->ss_gui_id) && IsGuiOnTop(ss_ram->ss_gui_id))
    return 1;
  if((ss_ram->keylock_gui_id) && IsGuiOnTop(ss_ram->keylock_gui_id))
    return 1;
  return 0;
}

#ifdef MEGADIAL
//int MDgui_id=0;
#endif

int daemoncsm_onmessage(CSM_RAM *data,GBS_MSG* msg)
{
#ifdef NEWSGOLD

#ifdef ELKA
#define MSG_EMS_FFS_WRITE 0x6105
#else
#define MSG_EMS_FFS_WRITE 0x61CB
#endif

#ifdef ELKA
#define MSG_EMS_INCOMING 0x6106 //ELKA,来自smsman
#else
#define MSG_EMS_INCOMING 0x61CC
#define MSG_EMS_INCOMING_2 0x61D6
#endif

#endif 
//0x61CC ?? SMS_incoming
//如果使用Browser-killer之类的补丁,将不会有新信息弹出窗口,使用这个MSG可以进行检查是否来新短信了

#ifdef ELKA
	//if(/*(CFG_ENA_NOTIFY)&&*/(msg->msg==MSG_EMS_INCOMING)&&IsHaveNewSMS())
#else
	//if(/*(CFG_ENA_NOTIFY)&&*/(msg->msg==MSG_EMS_INCOMING)&&IsHaveNewSMS())
//	if((CFG_ENA_NOTIFY)&&(msg->msg==MSG_EMS_INCOMING_2))
//	if((CFG_ENA_NOTIFY)&&((msg->msg==MSG_EMS_INCOMING) || (msg->msg==MSG_EMS_INCOMING_2)))
#endif
	//{
	//  if(!IsTimerProc(&chk_tmr)) //接收到MSG半秒之后开始检查,直接开始检查会死机.
	//    GBS_StartTimerProc(&chk_tmr, 216/2, DoNewProc);
	//    //GBS_StartTimerProc(&chk_tmr, 216/2, CheckNewProc);
	//}
	if(msg->msg==MSG_EMS_FFS_WRITE)
	{
	  int x;
	  if((int)msg->data1!=0x8)
	  {
	    if(IsThisSmsNewIn((int)msg->data0))// SUBPROC((void *)DoNewProc);
	    {
	      if(IsTimerProc(&chk_tmr)) GBS_DelTimer(&chk_tmr);
	      isnewp=1;
	      tindex=(int)msg->data0;
	      GBS_StartTimerProc(&chk_tmr, 216/2, DoNewProc);
	    }
	  }
	  else/* if((int)msg->data1==0x8 && !IsNoDlg(DlgCsmIDs))*/
	  {
	    if((x=CheckThisSMS((int)msg->data0)))
	    {
	      if(x==1)
	      {
		if(!IsTimerProc(&chk_tmr) || !isnewp)
		{
		  GBS_DelTimer(&chk_tmr);
		  tindex=(int)msg->data0;
		  GBS_StartTimerProc(&chk_tmr, 216/2, UpdateNProc);
		}
		//SUBPROC((void *)UpdateNProc);
		//if(!IsTimerProc(&n_update_tmr)/* && !IsTimerProc(&chk_tmr)*/)
		//  GBS_StartTimerProc(&n_update_tmr, 216*2/3, UpdateNProc);
	      }
	      else if(x==2)
	      {
		if(IsHaveDlgGuiOnTop()) RefreshGUI();
	      }
	    }
	  }
	  
	  //new_sms_n=(SmsDataRoot())->cnt_in_new_sms_dat;
	  //if(!new_sms_n) 
	  new_sms_n=getCountByType(TYPE_IN_N);
	  if((CFG_ENA_NOTIFY)&&(!new_sms_n)) //主要用于simoco链接手机时会读取所有短信并将其设置为已读
	  {
	    SetVibration(0);
	    if(PLAY_ID)
	    {
	      PlayMelody_StopPlayback(PLAY_ID);
	      PLAY_ID=0;
	    }
	  }
#ifdef ELKA
	  if(CFG_ENA_SLI)
	  {
	    if(new_sms_n>0)
	    {
	      sli_sta=1;
	      SLI_PROC();
	    }
	    else if(sli_sta) STOP_SLI();
	  }
#endif
	  //char str[64];
	  //sprintf(str, "submess:0x%X\ndata0:0x%08X\ndata1:0x%08X", msg->submess, msg->data0, msg->data1);
	  //ShowMSG(0, (int)str);
	  //WSHDR *ws=AllocWS(64);
	  //wsprintf(ws, "submess:0x%X\ndata0:0x%08X\ndata1:0x%08X", msg->submess, msg->data0, msg->data1);
	  //ShowMSG_ws(0, ws);
	  //        submess,data0,data1
	  //NEW in 97,index,0x408
	  //set to read 97,index,0x8
	  //del 97,index,0x8
	  //if(!IsTimerProc(&n_update_tmr) && !IsTimerProc(&chk_tmr))
	  //  GBS_StartTimerProc(&n_update_tmr, 216, UpdateNProc);
	}
	if(msg->msg==MSG_RECONFIGURE_REQ)
	{
	  extern const char *successed_config_filename;
	  if(!strcmp_nocase(successed_config_filename,(char *)msg->data0))
	  {
	    InitSetting();
	    ShowMSG(1,(int)lgp.LGP_CONFIG_UPDATE);
	    if(!cltop) SUBPROC((void *)ConstructListN);
	    if(!sdltop) SUBPROC((void *)ReadAllSmsN);
	  }
	}
	if(PLAY_ID && (msg->msg==MSG_INCOMMING_CALL || IsCalling()))
	{
	  PlayMelody_StopPlayback(PLAY_ID);
	  PLAY_ID=0;
	}
	if(msg->msg==MSG_PLAYFILE_REPORT && PLAY_ID) 
	{
	  GBS_PSOUND_MSG *pmsg=(GBS_PSOUND_MSG *)msg;
	  if(pmsg->handler==PLAY_ID)
	  {
	    int z=pmsg->cmd;
	    if(z==M_SAE_PLAYBACK_ERROR || z==M_SAE_PLAYBACK_DONE)
	      PLAY_ID=0;
	  }
	}
	if(msg->msg==MSG_IPC)
	{
	  IPC_REQ *ipc;
	  if((ipc=(IPC_REQ *)msg->data0))
	  {
	    if(!strcmp(ipc->name_to, my_ipc_name))
	    {
	      if(msg->submess==MY_SMSYS_IPC_START)
	      {
		IPC_DATA_DAEMON *ipcd=(IPC_DATA_DAEMON *)ipc->data;
		if((ipcd)&&(ipcd->csm_id!=DAEMON_CSM_ID))
		{
		  switch(ipcd->code)
		  {
		  case MY_SMSYS_CREATE:
		    {
		      daemon_ipc.data=&ipc_data_daemon;
		      ipc_data_daemon.csm_id=ipcd->csm_id;
		      ipc_data_daemon.code=MY_SMSYS_CLOSE;
		      ipc_data_daemon.fname=0;
		      GBS_SendMessage(MMI_CEPID,MSG_IPC,MY_SMSYS_IPC_START,&daemon_ipc);
		      IPC_SUB_MSG=MY_SMSYS_IPC_START;
		      CreateDialogCSM();
		    }
		    break;
		  case MY_SMSYS_CLOSE:
		    CloseCSM(ipcd->csm_id);
		    break;
		  case MY_SMSYS_FVIEW:
		    daemon_ipc.data=&ipc_data_daemon;
		    ipc_data_daemon.csm_id=ipcd->csm_id;
		    ipc_data_daemon.code=MY_SMSYS_CLOSE;
		    ipc_data_daemon.fname=0;
		    if(ipcd->fname)
		      strcpy(filename, ipcd->fname);
		    else
		      filename[0]=0;
		    GBS_SendMessage(MMI_CEPID,MSG_IPC,MY_SMSYS_IPC_START,&daemon_ipc);
		    IPC_SUB_MSG=SMSYS_IPC_FVIEW;
		    CreateDialogCSM();
		    break;
		  }
		}
	      }
	      else if((msg->submess > 0)&&(msg->submess <= SMSYS_IPC_MSG_MAX))
	      {
		IPC_SUB_MSG=msg->submess;
		CreateDialogCSM();
	      }
	      else if(msg->submess == SMSYS_IPC_ARCHIVE)
	      {
		SUBPROC((void *)OpenArchive);
	      }
	      else if(msg->submess == SMSYS_IPC_NEW_IN_WIN)
	      {
		IPC_SUB_MSG=msg->submess;
		CreateDialogCSM();
	      }
	      else if(msg->submess == SMSYS_IPC_NEWSMS_NUM)
	      {
		num_from_ipc=(char *)ipc->data;
		IPC_SUB_MSG=msg->submess;
		CreateDialogCSM();
	      }
	      else if(msg->submess == SMSYS_IPC_SEND_UTF8)
	      {
		text_utf8=(char *)ipc->data;
		IPC_SUB_MSG=msg->submess;
		CreateDialogCSM();
	      }
	      else if((msg->submess >= SMSYS_IPC_VIEW_OPMSG)&&(msg->submess <= SMSYS_IPC_QN_OPMSG))
	      {
		opmsg_id=(int)ipc->data;
		IPC_SUB_MSG=msg->submess;
		CreateDialogCSM();
	      }
	      else if(msg->submess==SMSYS_IPC_SEND_WS)
	      {
		text_ws=(WSHDR *)ipc->data;
		IPC_SUB_MSG=msg->submess;
		CreateDialogCSM();
	      }
	      else if(msg->submess == SMSYS_IPC_FVIEW)
	      {
		IPC_SUB_MSG=SMSYS_IPC_FVIEW;
		if(ipc->data)
		{
		  strcpy(filename, (char *)ipc->data);
		  mfree(ipc->data);
		}
		else
		  filename[0]=0;
		CreateDialogCSM();
	      }
	      else if(msg->submess == SMSYS_IPC_UPDATE_CLIST)
	      {
		SUBPROC((void *)ConstructList);
	      }
	      else if(msg->submess == SMSYS_IPC_SMS_DATA_UPDATE)
	      {
		if(IsHaveDlgGuiOnTop()) RefreshGUI();
	      }
	    }
	  }
	}
	if(msg->msg==MSG_CSM_DESTROYED)
	{
	  if(SNEDSMS_CSM_ID)
	  {
	    if((int)msg->data0==SNEDSMS_CSM_ID)
	      SNEDSMS_CSM_ID=0;
	    else if(!FindCSMbyID(SNEDSMS_CSM_ID))
	      SNEDSMS_CSM_ID=0;
	  }
	}
	CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
	if((new_sms_n>0)&& (CFG_ENA_NEWSMS_ICON)/* && (NEW_SMS_ICON)*/)
	{
#define idlegui_id (((int *)icsm)[DISPLACE_OF_IDLEGUI_ID/4])
	  if(IsGuiOnTop(idlegui_id) || IsSSOnTop())
	  {
#ifdef MEGADIAL
	    if(!cltop) SUBPROC((void *)ConstructListN);
#endif
	    GUI *igui=GetTopGUI();
	    if(igui)
	    {
	      DrawImg(CFG_ICONNEW_POS_X, CFG_ICONNEW_POS_Y, ip.dis_smsnew);
	    }
	  }
	}
#ifdef MEGADIAL
#define DISPLACE_OF_EDGUI_ID2 0x38 //use number
#define edialgui_id (((int *)icsm)[DISPLACE_OF_EDGUI_ID/4])
#define edialgui_id2 (((int *)icsm)[DISPLACE_OF_EDGUI_ID2/4])
#define EDIAL_IPC_NAME "EDialCrt"
#define EDIAL_MSG_CRT	1
/*	if(msg->msg==MSG_GUI_DESTROYED)
	{
	  if(MDgui_id && (int)msg->data0==MDgui_id)
	  {
	    extern void CloseMegaDial(void);
	    //GetCPUClock();
	    CloseMegaDial();
	    MDgui_id=0;
	  }
	}*/
	if(msg->msg==MSG_IPC)
	{
	  IPC_REQ *ipc;
	  if((ipc=(IPC_REQ *)msg->data0))
	  {
	    if(!strcmp(ipc->name_to, EDIAL_IPC_NAME))
	    {
	      if(msg->submess==EDIAL_MSG_CRT)
	      {
		extern const int CFG_ENA_MD;
		if(!cltop) SUBPROC((void *)ConstructListN);
		if(CFG_ENA_MD && (IsGuiOnTop(edialgui_id) || IsGuiOnTop(edialgui_id2)))
		{
		  GUI *igui=GetTopGUI();
		  if(igui)
		  {
		    extern void DoMegaDial(void *igui);
		    DoMegaDial(igui);
		  }
		  return 1;
		}
	      }
	    }
	  }
	}
	//int z;
	//if(IsGuiOnTop((z=edialgui_id)) || IsGuiOnTop((z=edialgui_id2)))
	extern const int CFG_ENA_MD;
	if(CFG_ENA_MD && (IsGuiOnTop(edialgui_id)/* || IsGuiOnTop(edialgui_id2)*/))
	{
	  if(!cltop) SUBPROC((void *)ConstructListN);
	  GUI *igui=GetTopGUI();
	  if(igui)
	  {
	//    MDgui_id=z;
	    extern void DoMegaDial(void *igui);
	    DoMegaDial(igui);
	  }
	}
#endif
	//isexit_ss();
	//if(new_sms_n>0) replace_allss_methods();
	return 1;
}

void LdProc(void)
{
  if(!cltop) SUBPROC((void *)ConstructListN);
  if(!sdltop) SUBPROC((void *)ReadAllSmsN);
}
//extern int MyKeyHook(int submsg, int msg);
//extern void restore_allss_methods(void);
//extern void replace_allss_methods(void);
//extern void isexit_ss(void);
void daemoncsm_oncreate(CSM_RAM *data)
{
  daemon_ipc.data=&ipc_data_daemon;
  ipc_data_daemon.csm_id=DAEMON_CSM_ID;
  if(is_fview&&strlen(filename))
  {
    ipc_data_daemon.code=MY_SMSYS_FVIEW;
    ipc_data_daemon.fname=filename;
  }
  else
  {
    ipc_data_daemon.code=MY_SMSYS_CREATE;
    ipc_data_daemon.fname=0;
  }
  GBS_SendMessage(MMI_CEPID,MSG_IPC,MY_SMSYS_IPC_START,&daemon_ipc);
  AddKeybMsgHook((void *)MyKeyHook);
  GBS_StartTimerProc(&ld_tmr, 216*2, LdProc);
#ifdef MEGADIAL
  extern void InitIcons(void);
  InitIcons();
#endif
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void daemoncsm_onclose(CSM_RAM *csm)
{
  //restore_allss_methods();
  GBS_DelTimer(&chk_tmr);
  GBS_DelTimer(&ld_tmr);
  RemoveKeybMsgHook((void *)MyKeyHook);
  closeAllDlgCSM(DlgCsmIDs);
  FreeCLIST();
  freeSDList();
#ifdef ELKA
  STOP_SLI();
#endif
  //GBS_DelTimer(&n_update_tmr);
  FreeLangPack();
  FreeIconPack();
#ifdef MEGADIAL
  extern void CloseMegaDial(void);
  CloseMegaDial();
  extern void RestoreMegaDial(void);
  RestoreMegaDial();
#endif
  SUBPROC((void *)ElfKiller);
}

static unsigned short daemoncsm_name_body[32];

#define ICONBAR
#ifdef ICONBAR

void addIconBar(short* num)
{
#pragma swi_number=0x27 
__swi __arm void AddIconToIconBar(int pic, short *num);
  if(CFG_ENA_IB)
  {
	if(SNEDSMS_CSM_ID) AddIconToIconBar(CFG_ICONSNED_IB, num);
	else if(new_sms_n>0) AddIconToIconBar(CFG_ICON_IB, num);
  }
}


typedef struct
{
  char check_name[8];
  int addr;
}ICONBAR_H;
#endif
static const struct
{
  CSM_DESC daemoncsm;
  WSHDR daemoncsm_name;
#ifdef ICONBAR
  ICONBAR_H iconbar_handler;
#endif
}DAEMONCSM =
{
  {
    daemoncsm_onmessage,
    daemoncsm_oncreate,
#ifdef NEWSGOLD
    0,
    0,
    0,
    0,
#endif
    daemoncsm_onclose,
    sizeof(DEAMON_CSM),
    1,
    &minus11
  },
  {
    daemoncsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    31
  }
#ifdef ICONBAR
  ,
  {
    "IconBar",
    (int)addIconBar
  }
#endif
};

void UpdateDaemonCSMname(void)
{
  wsprintf((WSHDR *)(&DAEMONCSM.daemoncsm_name),ELFNAME_D);
}

int main(char *exename, char *fname)
{
  DEAMON_CSM d_csm;
  CSM_RAM *save_cmpc;
  CSMROOT *csmr=CSM_root();
  zeromem(&d_csm, sizeof(DEAMON_CSM));
  UpdateDaemonCSMname();
  dlgIDsInit();
  InitSetting();
  ZeroIconPack();
  LoadIconPack();
  LoadLangPack();
  if(fname)
  {
    if ( fname[0] < '0' || fname[0] > '4' || fname[1] != ':' || strlen(fname) > 128 )
    {
      SUBPROC((void *)ElfKiller);
      return 0;
    }
    strcpy(filename, fname);
    is_fview=1;
  }
  LockSched();
  save_cmpc=csmr->csm_q->current_msg_processing_csm;
  csmr->csm_q->current_msg_processing_csm=csmr->csm_q->csm.first;
  DAEMON_CSM_ID=CreateCSM(&DAEMONCSM.daemoncsm,&d_csm,0);
  csmr->csm_q->current_msg_processing_csm=save_cmpc;
  UnlockSched();
  // for swaper
  InitUnderIdleCSM();
#ifdef ICONBAR
  //SetIconBarHandler();
#endif
  return 0;
}

//--------------------------------------------------------
//Others Menu
#define OTH_MENU_N 8
/*
const SOFTKEY_DESC oth_menu_sk[]=
{
  {0x0018,0x0000,(int)LGP_SELECT},
  {0x0001,0x0000,(int)LGP_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};
*/

extern SOFTKEY_DESC ed_menu_sk[];
const SOFTKEYSTAB oth_menu_skt=
{
  ed_menu_sk,0
  //oth_menu_sk,0
};

void OpenConfig(void)
{
  extern const char *successed_config_filename;
  WSHDR *file=AllocWS(128);
  str_2ws(file, successed_config_filename, 128);
  ExecuteFile(file, 0, 0);
  FreeWS(file);
}

void oth_menu_config(GUI *data)
{
  GeneralFuncF1(1);
  OpenConfig();
}

void oth_save_one_txt(GUI *data)
{
  GeneralFuncF1(1);
  PathInputDlg(INPUT_EXP_TXT, 0);
}

void oth_move_all_mss(GUI *data)
{
  int k;
  char msg[64];
  GeneralFuncF1(1);
  k=MoveAllMssToArchive();
  sprintf(msg, lgp.LGP_MOVE_MSSARCHIVER_N, k);
  ShowMSG(1, (int)msg);
}


void oth_open_archive(GUI *data)
{
  GeneralFuncF1(1);
  OpenArchive();
}

void oth_about(GUI *data)
{
  GeneralFuncF1(1);
  ShowMSG_noff(1, COPY_RIGHT);
}

void oth_cov_dat_txt(GUI *data)
{
  GeneralFuncF1(1);
  PathInputDlg(INPUT_COV_DAT, 0);
}
/*
void oth_save_all_as_file(GUI *data)
{
  char msg[64];
  GeneralFuncF1(1);
  sprintf(msg, STR_SAF_N, SaveAllAsFile());
  ShowMSG(1, (int)msg);;
}
*/

void oth_del_all(GUI *data) //mss
{
  GeneralFuncF1(1);
  extern void delallproc(void);// ed_gui.c
  delallproc();
}

void oth_show_count(GUI *data) //mss
{
  DLG_CSM *dlg_csm=MenuGetUserPointer(data);
  GeneralFuncF1(1);
  extern int ShowCount(void); //ed_gui.c
  UpdateDlgCsmName(dlg_csm, lgp.LGP_STATISTICS);
  ShowCount();
}


const MENUPROCS_DESC oth_menuprocs[OTH_MENU_N]=
{
  oth_menu_config,
  oth_open_archive,
  oth_save_one_txt,
  oth_move_all_mss,
  oth_cov_dat_txt,
  oth_del_all,
  oth_show_count,
  oth_about,
};

MENUITEM_DESC oth_menuitems[OTH_MENU_N]=
{
  {NULL,(int)LGP_NULL,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_NULL,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_NULL,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_NULL,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_NULL,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_NULL,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_NULL,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)LGP_NULL,	LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

void oth_menu_ghook(void *data, int cmd)
{
  if(cmd==5)
  {
    DLG_CSM *dlg_csm=MenuGetUserPointer(data);
    UpdateDlgCsmName(dlg_csm, lgp.LGP_OTHERS);
  }
}
const MENU_DESC oth_menu=
{
  8,NULL,oth_menu_ghook,NULL,
  main_menusoftkeys,
  &oth_menu_skt,
  0x10,//Right align
  NULL,
  oth_menuitems,//menuitems,
  oth_menuprocs,//menuprocs,
  OTH_MENU_N
};

HEADER_DESC oth_menuhdr={0,0,0,0,NULL,(int)LGP_NULL,LGP_NULL};

unsigned int CreateOthMenu(void *dlg_csm)
{
  patch_header(&oth_menuhdr);
  return (CreateSLMenu(&oth_menu, &oth_menuhdr, 0, OTH_MENU_N, dlg_csm));
}

//open archive
void OpenArchive(void)
{
  int len, c;
  char folder[128];
  unsigned int err;
  NativeExplorerData data;
  WSHDR *ws, wsn;
  unsigned short wsb[128];
  ws=CreateLocalWS(&wsn, wsb, 128);
  strcpy(folder, CFG_MAIN_FOLDER);
  len=strlen(folder);
  c=folder[len-1];
  if(c!='\\' && c!='/')
  {
    folder[len]='\\';
    folder[len+1]=0;
  }
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  strcat(folder, FLDR_ARCHIVE);
  if(!isdir(folder, &err))
    mkdir(folder, &err);
  if(!isdir(folder, &err))
    return;
  str_2ws(ws, folder, 128);
  zeromem(&data,sizeof(NativeExplorerData));
  data.mode=0;
  data.dir_enum=0x26;
  data.path_to_file=ws;
  data.is_exact_dir=1;
  data.full_filename=ws;
  data.unk9=1;
  StartNativeExplorer(&data);
}


