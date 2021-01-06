#include "../inc/swilib.h"
#include "rect_patcher.h"
#include "language.h"
#include "NatICQ.h"
#include "manage_cl.h"
#include "strings.h"
#include "main.h"
#include "lang.h"

extern int S_ICONS[];
extern int CurrentPrivateStatus;

static const int mmanage_cl_softkeys[] = {0,1,2};

static SOFTKEY_DESC mmanage_cl_sk[] =
{
  {0x0018, 0x0000, (int)""},
  {0x0001, 0x0000, NULL},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB mmanage_cl_skt =
{
  mmanage_cl_sk, 0
};

static SOFTKEY_DESC acgd_sk[] =
{
  {0x0018, 0x0000, (int)""},
  {0x0001, 0x0000, NULL},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB acgd_skt =
{
  acgd_sk, 0
};


static const int pl_softkeys[] = {0,1,2};

static SOFTKEY_DESC pl_sk[] =
{
  {0x0018, 0x0000, (int)""},
  {0x0001, 0x0000, NULL},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

const SOFTKEYSTAB pl_skt =
{
  pl_sk, 0
};

typedef struct{
  unsigned int grp_id;
  char name[64];
}GRP_ARRAY;

int acgd_onkey(GUI *data, GUI_MSG *msg)
{
  TPKT *p;
  EDITCONTROL ec;
  unsigned int uin=0;
  unsigned int group=0;
  WSHDR *ws;
  int j;
  char name[64], *s;
  int len;
  GRP_ARRAY *grp=EDIT_GetUserPointer(data);
  
  if (msg->keys==0xFFF)
  {
    ExtractEditControl(data,2,&ec);
    ws=ec.pWS;
    for (int i=0; i<ws->wsbody[0]; i++)
    {
      uin*=10;
      uin+=(ws->wsbody[i+1]-'0');     
    }
    
    ExtractEditControl(data,4,&ec);
    ws=ec.pWS;
    s=name;
    for (int i=0; i<ws->wsbody[0] && i<64; i++)
    {
      *s++=char16to8(ws->wsbody[i+1]);
    }
    len=s-name;
    *s=0;
    
    EDIT_SetFocus(data, 6);
    j=EDIT_GetItemNumInFocusedComboBox(data);
    if (j) group=grp[j-1].grp_id;

    p=malloc(sizeof(PKT)+4+len);
    p->pkt.uin=uin;
    p->pkt.type=T_ADDCONTACT_WITH_GRP;
    p->pkt.data_len=len+4;
    *(unsigned int *)(p->data)=group;
    strncpy(p->data+4,name,len);
    SUBPROC((void *)SendAnswer,0,p);
    return (1);
  }
  return (0);
}

void acgd_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk_add={0x0FFF,0x0000,NULL};
  sk_add.lgp_id=(int)lgpData[LGP_Add];
  
  GRP_ARRAY *grp=EDIT_GetUserPointer(data);
  EDITCONTROL ec;
  int i, j;
  i=EDIT_GetFocus(data);
  if (cmd==3)
  {
    mfree(grp);   
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk_add,SET_SOFT_KEY_N);  
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==0x0D)
  {
    if (i==6)
    {
      WSHDR *ews=AllocWS(64);
      ExtractEditControl(data,i,&ec);
      if ((j=EDIT_GetItemNumInFocusedComboBox(data)))
      {
        ascii2ws(ews,grp[j-1].name);                              
      }
      else
      {
        ExtractEditControl(data,i-1,&ec);
        wstrcpy(ews,ec.pWS);
      }
      EDIT_SetTextToFocused(data,ews);
      FreeWS(ews);
    }
  }
}

void acgd_locret(void){}

HEADER_DESC acgd_hdr={0,0,0,0,NULL,(int)"Добавление контакта",LGP_NULL};

INPUTDIA_DESC acgd_desc=
{
  1,
  acgd_onkey,
  acgd_ghook,
  (void *)acgd_locret,
  0,
  &acgd_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
//  0x40000000 - Поменять местами софт-кнопки
  0x40000000
};

extern volatile CLIST *cltop;
int CreateAddContactGrpDialog(CLIST *cl_sel)
{
  WSHDR *ews;
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  GRP_ARRAY *grp=NULL;
  int grp_n=0;
  int to_combo=0;
  
  eq=AllocEQueue(ma,mfree_adr());
  ews=AllocWS(128);
  
  ascii2ws(ews,(char*)lgpData[LGP_EnterUin]);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);   //1
  
  PrepareEditControl(&ec);
  if (cl_sel)
  {
    wsprintf(ews,"%u",cl_sel->uin);
  }
  else
  {
    CutWSTR(ews,0);
  }
  ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ews,9);
  AddEditControlToEditQend(eq,&ec,ma);   //2
  
  
  ascii2ws(ews,lgpData[LGP_EnterName]);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);   //3
  
  PrepareEditControl(&ec);
  if (cl_sel)
  {
    if (cl_sel->name)
    {
      ascii2ws(ews,cl_sel->name);
    }
    else
    {
      wsprintf(ews,"%u",cl_sel->uin);
    }
  }
  else
  {
    CutWSTR(ews,0);
  }
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,64);
  AddEditControlToEditQend(eq,&ec,ma);   //4
  
  for (CLIST *cl=(CLIST *)cltop; cl!=0; cl=cl->next)
  {
    if (cl->isgroup)
    {
      GRP_ARRAY *cur_grp;
      grp=realloc(grp,(grp_n+1)*sizeof(GRP_ARRAY));
      cur_grp=grp+grp_n;
      cur_grp->grp_id=cl->group;
      strncpy(cur_grp->name, cl->name,64);
      cur_grp->name[63]=0;
      if (cl_sel)
      {
        if (cl_sel->group==cur_grp->grp_id)  to_combo=grp_n;
      }
      grp_n++;
    }
  }
  ascii2ws(ews,(char*)lgpData[LGP_ChooseGroup]);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);    //5
  
  
  PrepareEditControl(&ec);
  CutWSTR(ews,0);
  if(grp_n)
  {
    ascii2ws(ews,grp->name);
  }
  ConstructComboBox(&ec,ECT_COMBO_BOX,ECF_APPEND_EOL,ews,64,0,grp_n,1+to_combo);
  AddEditControlToEditQend(eq,&ec,ma);    //6
  
  patch_header(&acgd_hdr);
  patch_input(&acgd_desc);
  FreeWS(ews);
 
  return CreateInputTextDialog(&acgd_desc,&acgd_hdr,eq,1,grp);
}

const int PR_LIST_ID[5]=
{
  PL_ALL_CAN_SEE,
  PL_INVISLIST_CANNOT_SEE,
  PL_CONTACTLIST_CAN_SEE,
  PL_VISLIST_CAN_SEE,
  PL_NOBODY_CAN_SEE
};
 

void SetPrivateStatus(int status)
{
  TPKT *p;
  p=malloc(sizeof(PKT)+1);
  p->pkt.uin=0;
  p->pkt.type=T_SETPRIVACY;
  p->pkt.data_len=1;
  p->data[0]=status;
  CurrentPrivateStatus=status;
  SUBPROC((void *)SendAnswer,0,p);
}

int GetPrivatePosInMenu(void)
{
  int i=0;
  for (; i<5; i++)
  {
    if (PR_LIST_ID[i]==CurrentPrivateStatus) break;
  }
  return (i);
}

#define PRIVATE_LIST_MAX 5

static void PL_VisibleForAll(GUI *data)
{
  SetPrivateStatus(PL_ALL_CAN_SEE);
  GeneralFuncF1(1);
}

static void PL_VisibleOnlyForVisList(GUI *data)
{
  SetPrivateStatus(PL_VISLIST_CAN_SEE);
  GeneralFuncF1(1);
}

static void PL_VisibleForAllExceptInvisList(GUI *data)
{
  SetPrivateStatus(PL_INVISLIST_CANNOT_SEE);
  GeneralFuncF1(1);
}

static void PL_VisibleOnlyForContactList(GUI *data)
{
  SetPrivateStatus(PL_CONTACTLIST_CAN_SEE);
  GeneralFuncF1(1);
}
static void PL_InvisibleForAll(GUI *data)
{
  SetPrivateStatus(PL_NOBODY_CAN_SEE);
  GeneralFuncF1(1);
}

static void private_list_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static MENUITEM_DESC private_list_ITEMS[PRIVATE_LIST_MAX]=
{
  {S_ICONS+ICON_ALL_CAN_SEE,         (int)LG_ALL_CAN_SEE,           LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {S_ICONS+ICON_INVISLIST_CANNOT_SEE,(int)LG_INVISLIST_CANNOT_SEE,  LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {S_ICONS+ICON_CONTACTLIST_CAN_SEE, (int)LG_CONTACTLIST_CAN_SEE,   LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {S_ICONS+ICON_VISLIST_CAN_SEE,     (int)LG_VISLIST_CAN_SEE,       LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {S_ICONS+ICON_NOBODY_CAN_SEE,      (int)LG_NOBODY_CAN_SEE,        LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

static const MENUPROCS_DESC private_list_HNDLS[PRIVATE_LIST_MAX]=
{
  PL_VisibleForAll,
  PL_VisibleForAllExceptInvisList,
  PL_VisibleOnlyForContactList,
  PL_VisibleOnlyForVisList,
  PL_InvisibleForAll
};

static HEADER_DESC private_list_HDR={0,0,NULL,NULL,NULL,NULL,LGP_NULL};

static const MENU_DESC private_list_MNU=
{
  8,NULL,private_list_ghook,NULL,
  pl_softkeys,
  &pl_skt,
  0x11,
  NULL,
  private_list_ITEMS,
  private_list_HNDLS,
  PRIVATE_LIST_MAX
};


int CreatePrivateStatusMenu(void)
{
  patch_header(&private_list_HDR);
  
  //Инициализация ленгпака
  private_list_HDR.lgp_id=(int)lgpData[LGP_PrivStatus];
  private_list_ITEMS[0].lgp_id_small=(int)lgpData[LGP_All_Can_See]; 
  private_list_ITEMS[1].lgp_id_small=(int)lgpData[LGP_Vislist_Can_See];
  private_list_ITEMS[2].lgp_id_small=(int)lgpData[LGP_Invislist_Cannot_See]; 
  private_list_ITEMS[3].lgp_id_small=(int)lgpData[LGP_ContactList_Can_See];
  private_list_ITEMS[4].lgp_id_small=(int)lgpData[LGP_Nobody_Can_See]; 

  
  return CreateMenu(0,0,&private_list_MNU,&private_list_HDR,GetPrivatePosInMenu(),PRIVATE_LIST_MAX,0,0);  
}

static void AddContactGrp(GUI *data)
{
  CreateAddContactGrpDialog(NULL);  
}

static void PrivateStatus(GUI *data)
{
  CreatePrivateStatusMenu();
}

#define M_MANAGE_CL_MAX 2

static void mmanage_cl_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static MENUITEM_DESC mmanage_cl_ITEMS[M_MANAGE_CL_MAX]=
{
  {NULL, NULL, LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL, NULL, LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

static const MENUPROCS_DESC mmanage_cl_HNDLS[M_MANAGE_CL_MAX]=
{
  AddContactGrp,
  PrivateStatus,
};

static HEADER_DESC mmanage_cl_HDR={0,0,NULL,NULL,NULL,NULL,LGP_NULL};

static const MENU_DESC mmanage_cl_MNU=
{
  8,NULL,mmanage_cl_ghook,NULL,
  mmanage_cl_softkeys,
  &mmanage_cl_skt,
  0,
  NULL,
  mmanage_cl_ITEMS,
  mmanage_cl_HNDLS,
  M_MANAGE_CL_MAX
};

int CreateManageCLMenu(void)
{
  patch_header(&mmanage_cl_HDR);
  
  mmanage_cl_HDR.lgp_id=(int)lgpData[LGP_ManageList];
  mmanage_cl_ITEMS[0].lgp_id_small=(int)lgpData[LGP_AddCont]; 
  mmanage_cl_ITEMS[1].lgp_id_small=(int)lgpData[LGP_PrivStatus];
  
  mmanage_cl_sk[0].lgp_id=(int)lgpData[LGP_Select];
  mmanage_cl_sk[1].lgp_id=(int)lgpData[LGP_Close];
  
  acgd_sk[1].lgp_id=(int)lgpData[LGP_Close];
  
  pl_sk[0].lgp_id=(int)lgpData[LGP_Select];
  pl_sk[1].lgp_id=(int)lgpData[LGP_Close];
  
  return CreateMenu(0,0,&mmanage_cl_MNU,&mmanage_cl_HDR,0,M_MANAGE_CL_MAX,0,0);
}
