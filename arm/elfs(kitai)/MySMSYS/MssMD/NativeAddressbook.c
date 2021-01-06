#include "..\..\inc\swilib.h"
#include "sms_dat.h"
#include "NativeAddressbook.h"
#include "edGui.h"
#include "numList.h"
#include "guiIdMan.h"
#include "main.h"
#include "language.h"
#include "adrList.h"
#include "string_works.h"
//extern void InsertAsTxt(void *ed_gui, char *num);
//extern void SetNumToED(void *ed_gui, char *num, WSHDR *name);
//extern int findNameByNum(WSHDR *name_to, char *num);
//extern void addCSMidForced0(unsigned int *id_pool, unsigned int id);
//extern int addCSMid(unsigned int *id_pool, unsigned int id);
//extern void delCSMid(unsigned int *id_pool, unsigned int id);
//extern int num_2ws(WSHDR *ws, const char *num, int maxlen);
//extern int ws_2num(WSHDR *ws, char *num, int maxlen);
//extern int IsCsmExist(void *dlg_csm);
//extern int IsGuiExist(CSM_RAM *csm, GUI *gui);
/*
int StartSelectNum(void *ed_gui)
{
  GetCPUClock();
  USER_OP *uo=EDIT_GetUserPointer(ed_gui);
  NativeAbData *nabd=AllocNativeAbData();
  uo->nab_data=nabd;
  if(uo->nab_flag==NAB_NS) uo->nab_flag=NAB_DN;
  return (OpenNativeAddressbook(4, 1, 0, nabd));
}

int SetNumberToED(void *ed_gui) //return, 0: no data, 1: suc, 2: no free
{
  GetCPUClock();
  USER_OP *uo=EDIT_GetUserPointer(ed_gui);
  NativeAbData *nabd;
  char num[50];
  WSHDR *wn, *wloc, wlocn;
  unsigned short wlocb[150];
  if(!(nabd=uo->nab_data))
    return 0;
  if(uo->nab_flag==NAB_DN)
  {
    uo->nab_flag=NAB_AF;
    return 2;
  }
  if(GetNativeAbDataStatus(nabd, 0)==1)
  {
    if((wn=GetNumFromNativeAbData(nabd, GetNativeAbDataType(nabd, 0), 0))!=0)
    {
      ws_2str(wn, num, 49);
      if(uo->adr_type==TYPE_SET)
      {
	wloc=CreateLocalWS(&wlocn, wlocb, 150);
	if(!findNameByNum(wloc, num))
	  wstrcpy(wloc, wn);
	SetNumToED(ed_gui, num, wloc);
      }
      else if(uo->adr_type==TYPE_TXT)
      {
	InsertAsTxt(ed_gui, num);
      }
      FreeWS(wn);
    }
  }
  FreeNativeAbData(nabd);
  uo->nab_data=0;
  return 1;
}

int StartSaveNum(void *ed_gui)
{
  GetCPUClock();
  USER_OP *uo=EDIT_GetUserPointer(ed_gui);
  NUM_LIST *nl;
  NativeAbData *nabd;
  WSHDR *wloc, wlocn;
  unsigned short wlocb[50];
  if(!(nl=GetNumListCur(uo, EDIT_GetFocus(ed_gui))))
  {
    if(!(nl=GetNumListCur(uo, 1)))
      return 0;
  }
  if(!nl->num || !strlen(nl->num))
    return 0;
  nabd=AllocNativeAbData();
  uo->nab_data=nabd;
  if(uo->nab_flag==NAB_NS) uo->nab_flag=NAB_DN;
  wloc=CreateLocalWS(&wlocn, wlocb, 50);
  num_2ws(wloc, nl->num, 50);
  SetNumToNativeAbData(nabd, 0x1D, wloc);
  return (OpenNativeAddressbook(6, 0, 0, nabd));
}

int FreeSaveNAbData(void *ed_gui)
{
  GetCPUClock();
  NativeAbData *nabd;
  USER_OP *uo=EDIT_GetUserPointer(ed_gui);
  if(!(nabd=uo->nab_data))
    return 0;
  if(uo->nab_flag==NAB_DN)
  {
    uo->nab_flag=NAB_AF;
    return 2;
  }
  FreeNativeAbData(nabd);
  uo->nab_data=0;
  return 1;
}
*/
typedef struct
{
  CSM_RAM csm;
  NativeAbData *nab_data;
  void *ed_gui;
  void *dlg_csm;
  int ab_csm_id;
  int type;
}AB_CSM;


void InsertAsTxt(void *ed_gui, WSHDR *num)
{
  WSHDR csloc, *wcs;
  EDITCONTROL ec;
  unsigned short csb[MAX_TEXT];
  //WSHDR *wnum, wnumn;
  //unsigned short wnumb[50];
  int k=EDIT_GetCursorPos(ed_gui);
  USER_OP *uo=EDIT_GetUserPointer(ed_gui);
  int n=EDIT_GetFocus(ed_gui);
  if(n!=(uo->focus_n))
    return;
  if(k<=0)
    return;
  wcs=CreateLocalWS(&csloc,csb,MAX_TEXT);
  //wnum=CreateLocalWS(&wnumn,wnumb,50);
  //wsprintf(wnum, PERCENT_S, num);
  ExtractEditControl(ed_gui,n,&ec);
  wstrcpy(wcs, ec.pWS);
  wsInsert(wcs, num, k-1, MAX_TEXT);
  EDIT_SetTextToEditControl(ed_gui, n, wcs);
  EDIT_SetCursorPos(ed_gui, k+num->wsbody[0]);
}

void SetNumToED(void *ed_gui, WSHDR *num, WSHDR *name)
{
	//EDITCONTROL ec;
	NUM_LIST *nl;
	USER_OP *uo=EDIT_GetUserPointer(ed_gui);
	int n=EDIT_GetFocus(ed_gui);
	if(n>(uo->focus_n-2))
		return;
	if(!(nl=GetNumListCur(uo, n)))
		return;
	//strcpy(nl->num, num);
	//ExtractEditControl(ed_gui,n,&ec);
	ws_2num(num, nl->num, 49);
	wstrcpy(nl->name, name);
	EDIT_SetTextToEditControl(ed_gui, n, name);
}

int abcsm_onmessage(CSM_RAM *data,GBS_MSG* msg)
{
  AB_CSM *abcsm=(AB_CSM *)data;
  NativeAbData *nabd;
  char num[50];
  WSHDR *wn, *wloc, wlocn;
  unsigned short wlocb[150];
  USER_OP *uo;
  int status;
  if((msg->msg==MSG_CSM_DESTROYED)&&((int)msg->data0==abcsm->ab_csm_id))
  {
//    GetCPUClock();
    if(!(nabd=abcsm->nab_data))
      goto CLOSE_CSM;
    //GetCPUClock();
    if((abcsm->type==TYPE_SELECT)
       && IsCsmExist(abcsm->dlg_csm) 
       && IsGuiExist(abcsm->dlg_csm, abcsm->ed_gui)
	 &&(uo=EDIT_GetUserPointer(abcsm->ed_gui)) 
	   //&& abcsm->type==TYPE_SELECT
	     && ((status=GetNativeAbDataStatus(nabd, 0))!=9))
      {
	if((wn=GetNumFromNativeAbData(nabd, GetNativeAbDataType(nabd, 0), 0))!=0)
	{
	  if((uo->adr_type==TYPE_SET)&&(status==1))
	  {
	    ws_2num(wn, num, 49);
	    wloc=CreateLocalWS(&wlocn, wlocb, 150);
	    if(!findNameByNum(wloc, num))
	      wstrcpy(wloc, wn);
	    SetNumToED(abcsm->ed_gui, wn, wloc);
	  }
	  else if((uo->adr_type==TYPE_TXT)&&((status==1)||(status==5)))
	  {
	    InsertAsTxt(abcsm->ed_gui, wn);
	  }
	  FreeWS(wn);
	}
	//FreeNativeAbData(nabd);
	//abcsm->nab_data=0;
      }
    FreeNativeAbData(nabd);
    abcsm->nab_data=0;
  CLOSE_CSM:
    data->state=-3;
    abcsm->ab_csm_id=0;
  }
  return 1;
}
void abcsm_oncreate(CSM_RAM *data)
{
  AB_CSM *abcsm=(AB_CSM *)data;
  USER_OP *uo;
  NUM_LIST *nl;
  NativeAbData *nabd;
  WSHDR *wloc, wlocn;
  unsigned short wlocb[50];
//  GetCPUClock();
  if(!IsCsmExist(abcsm->dlg_csm) || !IsGuiExist(abcsm->dlg_csm, abcsm->ed_gui))
  {
    goto CLOSE_CSM;
  }
  nabd=AllocNativeAbData();
  abcsm->nab_data=nabd;
  if(!abcsm->ed_gui || !(uo=EDIT_GetUserPointer(abcsm->ed_gui)))
    goto CLOSE_CSM;
  if(abcsm->type==TYPE_SELECT)
  {
    
    if(uo->adr_type==TYPE_SET)
      abcsm->ab_csm_id=OpenNativeAddressbook(4, 1, 0, nabd);
    else if(uo->adr_type==TYPE_TXT)
      abcsm->ab_csm_id=OpenNativeAddressbook(0xB, 0, 0, nabd);
    else
      goto CLOSE_CSM;
  }
  else if(abcsm->type==TYPE_SAVE)
  {
    //uo=EDIT_GetUserPointer(abcsm->ed_gui);
    if(!(nl=GetNumListCur(uo, EDIT_GetFocus(abcsm->ed_gui))))
    {
      if(!(nl=GetNumListCur(uo, 1)))
	goto CLOSE_CSM;
    }
    if(!nl->num || !strlen(nl->num))
      goto CLOSE_CSM;
    wloc=CreateLocalWS(&wlocn, wlocb, 50);
    num_2ws(wloc, nl->num, 50);
    SetNumToNativeAbData(nabd, 0x1D, wloc);
    abcsm->ab_csm_id=OpenNativeAddressbook(6, 0, 0, nabd);
  }
  else
CLOSE_CSM:
    data->state=-3;
  if(addCSMid(DlgCsmIDs, abcsm->csm.id)<0)
    addCSMidForced0(DlgCsmIDs, abcsm->csm.id);
}
void abcsm_onclose(CSM_RAM *data)
{
  AB_CSM *abcsm=(AB_CSM *)data;
//  GetCPUClock();
  if(abcsm->nab_data)
    FreeNativeAbData(abcsm->nab_data);
  if(abcsm->ab_csm_id)
    CloseCSM(abcsm->ab_csm_id);
  delCSMid(DlgCsmIDs, abcsm->csm.id);
}
const int minus11_2=-11;

unsigned short abcsm_name_body[32];
const struct
{
  CSM_DESC abcsm;
  WSHDR abcsm_name;
}ABCSM_DESC=
{
  {
    abcsm_onmessage,
    abcsm_oncreate,
#ifdef NEWSGOLD
    0,
    0,
    0,
    0,
#endif
    abcsm_onclose,
    sizeof(AB_CSM),
    1,
    &minus11_2
  },
  {
    abcsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    31
  }
};
/*
const CSM_DESC abcsm=
{
  abcsm_onmessage,
  abcsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  abcsm_onclose,
  sizeof(AB_CSM),
  1,
  &minus11_2
};
*/
int CreateNAbCSM(void *dlg_csm, void *ed_gui, int type)
{
  AB_CSM data;
  //int id;
  zeromem(&data, sizeof(AB_CSM));
  data.ed_gui=ed_gui;
  data.dlg_csm=dlg_csm;
  data.type=type;
  wsprintf((WSHDR *)(&ABCSM_DESC.abcsm_name), PERCENT_T, lgp.LGP_CALL_ADDRESSBOOK);
  //id=CreateCSM(&abcsm, &data, 0);
  //return id;
  return (CreateCSM(&(ABCSM_DESC.abcsm), &data, 0));
}







