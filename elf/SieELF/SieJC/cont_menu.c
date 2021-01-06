#include "../inc/swilib.h"
#include "main.h"
#include "clist_util.h"
#include "jabber_util.h"
#include "string_util.h"
#include "JID_Enter_UI.h"
#include "vCard.h"
#include "lang.h"
#include "rect_patcher.h"

char *room_name;
char *room_jid;
MUC_ADMIN macmd;
int reason_pos;
extern void ConstructReasonDlg(char *name, char *jid, MUC_ADMIN muccmd);

#define MAX_ITEMS 12       // §®§Ñ§Ü§ã§Ú§Þ§Ñ§Ý§î§ß§à§Ö §Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§à §á§å§ß§Ü§ä§à§Ó §Þ§Ö§ß§ð

#define MI_CONF_LEAVE       1
#define MI_QUERY_VERSION    2
#define MI_LOGIN_LOGOUT     3
#define MI_DISCO_QUERY      4
#define MI_HISTORY_OPEN     5
#define MI_TIME_QUERY       6
#define MI_VCARD_QUERY      7
#define MI_MUC_ADMIN        8
#define MI_LASTACTIV_QUERY  9
#define MI_SUBSCRIBES_MENU  10
#define MI_CHANGECONTACT_VERSION  11
#define MI_CONF_CLEAR       12
char Menu_Contents[MAX_ITEMS-1];
int cmS_ICONS[MAX_ITEMS+1];


int Contact_MenuID;
int Req_Close_Cont_Menu=0;
const char contmenu_header[]=LG_MENUCONTACT;
int menusoftkeys[]={0,1,2};
HEADER_DESC contact_menuhdr={0,0,0,0,NULL,(int)contmenu_header,LGP_NULL};
SOFTKEY_DESC clmenu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB clmenu_skt=
{
  clmenu_sk,0
};


void contact_menu_ghook(void *data, int cmd);
int contact_menu_onkey(void *data, GUI_MSG *msg);
void contact_menu_iconhndl(void *data, int curitem, void *unk);

MENU_DESC contact_menu=
{
  8,contact_menu_onkey,contact_menu_ghook,NULL,
  menusoftkeys,
  &clmenu_skt,
  0x11,
  contact_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

//////////////////////// Menu "muc#admin" ///////////////////////////
#define MAX_MUC_ADMIN_ITEMS 10

#define MA_CONF_KICK_THIS   1
#define MA_CONF_BAN_THIS    2
#define MA_CONF_VREJ_THIS   3
#define MA_CONF_VGR_THIS    4
#define MA_CONF_PARTICIPANT 5
#define MA_CONF_MEMBER      6
#define MA_CONF_MODERATOR   7
#define MA_CONF_MGR         8
#define MA_CONF_ADMIN       9
#define MA_CONF_OWNER       10

char MA_Menu_Contents[MAX_MUC_ADMIN_ITEMS-1];
const char ma_menu_header[]=LG_MUC_ADMIN;
int mamenusoftkeys[]={0,1,2};
HEADER_DESC ma_menuhdr={0,0,0,0,NULL,(int)ma_menu_header,LGP_NULL};
SOFTKEY_DESC ma_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB ma_menu_skt=
{
  ma_menu_sk,0
};

void ma_menu_ghook(void *data, int cmd);
int ma_menu_onkey(void *data, GUI_MSG *msg);
void ma_menu_iconhndl(void *data, int curitem, void *unk);

MENU_DESC ma_menu=
{
  8,ma_menu_onkey,ma_menu_ghook,NULL,
  mamenusoftkeys,
  &ma_menu_skt,
  0x10, // 0x11 §Ö§ã§Ý§Ú §ß§Ñ§Õ§à §Þ§Ö§ß§ð §ã §Ú§Ü§à§ß§Ü§Ñ§Þ§Ú
  ma_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

void InitMAMenuArray()
{
  for(int i=0;i<MAX_MUC_ADMIN_ITEMS;i++)MA_Menu_Contents[i]=0;
}

void Disp_MA_Menu()
{
  TRESOURCE *Act_contact = CList_GetActiveContact();
  InitMAMenuArray();
  int n_items=0;
  //§°§á§â§Ö§Õ§Ö§Ý§ñ§Ö§Þ, §Ü§Ñ§Ú§Ö §Ò§å§Õ§å§ä §á§å§ß§Ü§ä§í §Ó §Þ§Ö§ß§ð §Þ§Ö§ß§ð muc#admin §Õ§Ý§ñ §ä§Ö§Ü§å§ë§Ö§Ô§à §Ü§à§ß§ä§Ñ§Ü§ä§Ñ

TRESOURCE* MYMUCRES = CList_IsResourceInList(CList_FindMUCByJID(CList_FindContactByJID(Act_contact->full_name)->JID)->conf_jid);
//MYMUCRES->muc_privs.role); //§£§à§ä §ß§Ñ§ê§Ñ §â§à§Ý§î
//MYMUCRES->muc_privs.aff); //§£§à§ä §ß§Ñ§ê§Ñ §Ñ§æ§Ú§Ý§Ñ§ä§Ú§à§ß
//§Õ§Ñ §Ú§Ù§Ó§â§Ñ§ä§ß§à, §ß§à §á§à§é§Ö§Þ§å§ä§à §â§Ñ§Ò§à§ä§Ñ§Ö§ä
if (MYMUCRES->muc_privs.aff<AFFILIATION_ADMIN) //§¦§ã§Ý§Ú §Þ§í §Þ§Ö§Þ§Ò§Ö§â-§Þ§à§Õ§Ö§â§Ñ§ä§à§â §Ú§Ý§Ú §ß§à§ß§Ö-§Þ§à§Õ§Ö§â§Ñ§ä§à§â, §Ñ §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §ß§Ö §Þ§à§Õ§Ö§â§Ñ§ä§à§â(§ï§ä§à §Þ§í §â§Ñ§ß§î§ê§Ö §á§â§à§Ó§Ö§â§ñ§Ý§Ú, §Ü§à§Ô§Õ§Ñ §Õ§å§Þ§Ñ§Ý§Ú, §à§ä§à§Ò§â§Ñ§Ø§Ñ§ä§î §Ý§Ú muc#admin)
  {
   MA_Menu_Contents[n_items++]=MA_CONF_KICK_THIS; //§Ü§Ú§Ü§Ñ§ä§î §Þ§í §Þ§à§Ø§Ö§Þ §Ó§ã§Ö§ç, §Ü§ä§à §á§â§à§ê§Ö§Ý §é§Ö§â§Ö§Ù §å§ã§Ý§à§Ó§Ú§ñ
  if(Act_contact->muc_privs.role==ROLE_VISITOR) // §Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §Ó§Ú§Ù§Ú§ä§à§â, §Ö§Þ§å §Þ§à§Ø§ß§à §Õ§Ñ§Ó§Ñ§ä§î §Ô§à§Ý§à§ã
  {
       MA_Menu_Contents[n_items++]=MA_CONF_VGR_THIS;    
  }
  else  //§Ú§ß§Ñ§é§Ö §Ö§Ô§à §Þ§à§Ø§ß§à §ã§Õ§Ö§Ý§Ñ§ä§î §Ó§Ú§Ù§Ú§ä§à§â§à§Þ
  {
       MA_Menu_Contents[n_items++]=MA_CONF_VREJ_THIS;
  }
  //§Ó§ã§×, §ß§Ñ §ï§ä§à§Þ §ß§Ñ§ê§Ú §á§â§Ñ§Ó§Ñ §Ù§Ñ§Ü§à§ß§é§Ú§Ý§Ú§ã§î 
  }

  else
  {
  if(Act_contact->muc_privs.role!=ROLE_MODERATOR) //§Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §ß§Ö §Þ§à§Õ§Ö§â§Ñ§ä§à§â, §Ö§Ô§à §Þ§à§Ø§ß§à §Ü§Ú§Ü§Ñ§ä§î
  {
       MA_Menu_Contents[n_items++]=MA_CONF_KICK_THIS; 
  }
       
  if(MYMUCRES->muc_privs.aff==AFFILIATION_OWNER||MYMUCRES->muc_privs.aff>Act_contact->muc_privs.aff)
  {
      MA_Menu_Contents[n_items++]=MA_CONF_BAN_THIS; // §Ò§Ñ§ß§Ú§ä§î §Þ§à§Ø§ß§à §Ó§ã§Ö§ç §Ü§ä§à §ç§å§Ø§Ö §ß§Ñ§ã §á§à affiliation, §Ú§Ý§Ú §â§Ñ§Ó§ß§í, §Ö§ã§Ý§Ú §Þ§í §à§Ó§ß§Ö§â
  }
  
  if(Act_contact->muc_privs.role==ROLE_VISITOR) // §Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §Ó§Ú§Ù§Ú§ä§à§â, §Ö§Þ§å §Þ§à§Ø§ß§à §Õ§Ñ§Ó§Ñ§ä§î §Ô§à§Ý§à§ã
  {
       MA_Menu_Contents[n_items++]=MA_CONF_VGR_THIS;    
  }
  else if(Act_contact->muc_privs.aff<AFFILIATION_ADMIN) //§Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §ß§Ö §Ó§Ú§Ù§Ú§ä§à§â, §ß§Ö §Ñ§Õ§Þ§Ú§ß, §Ú §ß§Ö §à§Ó§ß§Ö§â, §Ö§Ô§à §Þ§à§Ø§ß§à §ã§Õ§Ö§Ý§Ñ§ä§î §Ó§Ú§Ù§Ú§ä§à§â§à§Þ
  {
       MA_Menu_Contents[n_items++]=MA_CONF_VREJ_THIS;
  }
  if(Act_contact->muc_privs.aff>AFFILIATION_NONE&&(MYMUCRES->muc_privs.aff>Act_contact->muc_privs.aff||MYMUCRES->muc_privs.aff==AFFILIATION_OWNER)) 
    //§Ö§ã§Ý§Ú §Ü§à§ß§ä§Ñ§Ü§ä §ß§Ö none §Ú §ç§å§Ø§Ö §ß§Ñ§ã §Ú§Ý§Ú §Ö§ã§Ý§Ú §Þ§í §à§Ó§ß§Ö§â, §Ö§Ô§à §Þ§à§Ø§ß§à §Õ§Ö§Ý§Ñ§ä§î §Þ§Ö§Þ§Ò§Ö§â§à§Þ
  {
       MA_Menu_Contents[n_items++]=MA_CONF_PARTICIPANT;
  }
  if(Act_contact->muc_privs.aff!=AFFILIATION_MEMBER&&(MYMUCRES->muc_privs.aff>Act_contact->muc_privs.aff||MYMUCRES->muc_privs.aff==AFFILIATION_OWNER)) 
    //§Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §ß§Ö §Þ§Ö§Þ§Ò§Ö§â §Ú §ç§å§Ø§Ö §ß§Ñ§ã, §Ö§Ô§à §Þ§à§Ø§ß§à §Õ§Ö§Ý§Ñ§ä§î §Þ§Ö§Þ§Ò§Ö§â§à§Þ (§Ú §Ñ§Õ§Þ§Ú§ß§à§Ó §ã §à§Ó§ß§Ö§â§Ñ§Þ§Ú §Þ§à§Ø§ß§à)
  {
       MA_Menu_Contents[n_items++]=MA_CONF_MEMBER;
  }
  if(Act_contact->muc_privs.role!=ROLE_MODERATOR) // §Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §ß§Ö §Þ§à§Õ§Ö§â§Ñ§ä§à§â, §Ö§Ô§à §Þ§à§Ø§ß§à §Õ§Ö§Ý§Ñ§ä§î §Þ§à§Õ§Ö§â§Ñ§ä§à§â§à§Þ
  {
      MA_Menu_Contents[n_items++]=MA_CONF_MODERATOR;
  }
  else if(Act_contact->muc_privs.aff<AFFILIATION_ADMIN) // §Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §Þ§à§Õ§Ö§â§Ñ§ä§à§â, §ß§à §ß§Ö §Ñ§Õ§Þ§Ú§ß §Ú§Ý§Ú §à§Ó§ß§Ö§â, §å §ß§Ö§Ô§à §Þ§à§Ø§ß§à §Ù§Ñ§Ò§Ú§â§Ñ§ä§î §Þ§à§Õ§Ö§â§Ñ§ä§à§â§Ñ
  {
      MA_Menu_Contents[n_items++]=MA_CONF_MGR;
  }
  if(Act_contact->muc_privs.aff!=AFFILIATION_ADMIN&&MYMUCRES->muc_privs.aff==AFFILIATION_OWNER) // §Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §ß§Ö §Ñ§Õ§Þ§Ú§ß §Ñ §Þ§í §à§Ó§ß§Ö§â, §Ö§Ô§à §Þ§à§Ø§à §Õ§Ö§Ý§Ñ§ä§î §Ñ§Õ§Þ§Ú§ß§à§Þ
  {
      MA_Menu_Contents[n_items++]=MA_CONF_ADMIN;
  }
  if(Act_contact->muc_privs.aff!=AFFILIATION_OWNER&&MYMUCRES->muc_privs.aff==AFFILIATION_OWNER) // §Ö§ã§Ý§Ú §ä§Ö§Ü§å§ë§Ú§Û §Ü§à§ß§ä§Ñ§Ü§ä §ß§Ö §à§Ó§ß§Ö§â §Ñ §Þ§í §à§Ó§ß§Ö§â, §Ö§Ô§à §Þ§à§Ø§ß§à §Õ§Ö§Ý§Ñ§ä§î §à§Ó§ß§Ö§â§à§Þ
  {
      MA_Menu_Contents[n_items++]=MA_CONF_OWNER; 
  }
  }
  patch_rect(&ma_menuhdr.rc,0,YDISP,ScreenW()-1,HeaderH()+YDISP);
  CreateMenu(0,0,&ma_menu,&ma_menuhdr,0,n_items,0,0);
}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//podpiska
#define MAX_CONTC_ITEMS 5

#define CONTC_SUBSCRIBE    1
#define CONTC_SUBSCRIBED   2
#define CONTC_UNSUBSCRIBED 3
#define CONTC_UNSUBSCRIBE  4

char CONTC_Menu_Contents[MAX_CONTC_ITEMS-1];
const char contc_menu_header[]="ÊÚÈ¨";
int contcmenusoftkeys[]={0,1,2};
HEADER_DESC contc_menuhdr={0,0,0,0,NULL,(int)contc_menu_header,LGP_NULL};
SOFTKEY_DESC contc_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB contc_menu_skt=
{
  contc_menu_sk,0
};

void contc_menu_ghook(void *data, int cmd);
int contc_menu_onkey(void *data, GUI_MSG *msg);
void contc_menu_iconhndl(void *data, int curitem, void *unk);

MENU_DESC contc_menu=
{
  8,contc_menu_onkey,contc_menu_ghook,NULL,
  contcmenusoftkeys,
  &contc_menu_skt,
  0x10, // 0x11 §Ö§ã§Ý§Ú §ß§Ñ§Õ§à §Þ§Ö§ß§ð §ã §Ú§Ü§à§ß§Ü§Ñ§Þ§Ú
  contc_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

void InitContMenuArray()
{
  for(int i=0;i<MAX_CONTC_ITEMS;i++)CONTC_Menu_Contents[i]=0;
}

void Disp_Cont_Menu()
{
//  TRESOURCE *Act_contact = CList_GetActiveContact();
//  CLIST* CLAct_contact=CList_FindContactByJID(CList_GetActiveContact()->full_name);
  InitContMenuArray();
  int n_items=0;
  CONTC_Menu_Contents[n_items++]=CONTC_SUBSCRIBE;//zaprosit` 
//  if((CLAct_contact->subscription == SUB_BOTH)||(CLAct_contact->subscription==SUB_FROM))
   {
       CONTC_Menu_Contents[n_items++]=CONTC_UNSUBSCRIBE; //Otozvat` podpisku
   }
//   if((Act_contact->status == PRESENCE_SUBSCRIBE))//§¦§ã§Ý§Ú §Ü§à§ß§ä§Ñ§Ü§ä §Ù§Ñ§á§â§Ó§ê§Ú§Ó§Ñ§Ö§ä §á§à§Õ§á§Ú§ã§Ü§å...
   {
     CONTC_Menu_Contents[n_items++]=CONTC_UNSUBSCRIBED;//otkazat`
     CONTC_Menu_Contents[n_items++]=CONTC_SUBSCRIBED;//soglasitsja
   }
  patch_rect(&contc_menuhdr.rc,0,YDISP,ScreenW()-1,HeaderH()+YDISP);
  if (n_items != 0) CreateMenu(0,0,&contc_menu,&contc_menuhdr,0,n_items,0,0);
}
/////////////////////////////////////////////////////////////////////

void contact_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)  // onFocus
  {
    DisableIDLETMR();
    if(Req_Close_Cont_Menu)
    {
      Req_Close_Cont_Menu=0;
      GeneralFunc_flag1(Contact_MenuID,1);
    }
  }
}

/*
§°§Ò§â§Ñ§Ò§à§ä§é§Ú§Ü §ß§Ñ§Ø§Ñ§ä§Ú§Û §Ü§Ý§Ñ§Ó§Ú§ê §Þ§Ö§ß§ð. §°§ä§ã§ð§Õ§Ñ §ã§Ý§Ö§Õ§å§Ö§ä §Ó§í§Ù§í§Ó§Ñ§ä§î §ß§Ö§à§Ò§ç§à§Õ§Ú§Þ§í§Ö §Õ§Ö§Û§ã§ä§Ó§Ú§ñ

*/
int contact_menu_onkey(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    switch(Menu_Contents[i])
    {
    case MI_CONF_LEAVE:
      {
        CLIST* room=CList_FindContactByJID(CList_GetActiveContact()->full_name);
        Send_Leave_Conference(room->JID);
        break;
      }
    case MI_CONF_CLEAR:
      {
        TRESOURCE *Reso_Ex = CList_GetActiveContact();
        KillMsgList(Reso_Ex->log);
        Reso_Ex->log = NULL;
        Reso_Ex->has_unread_msg=0;
        Reso_Ex->total_msg_count=0;
        break;
      }
    case MI_TIME_QUERY:
      {
        Send_Time_Request((CList_GetActiveContact()->full_name));
        break;
      }

    case MI_VCARD_QUERY:
      {
        if (!Show_vCard(CList_GetActiveContact()->full_name))
          Send_Vcard_Request((CList_GetActiveContact()->full_name));
        break;
      }

    case MI_LASTACTIV_QUERY:
    {
      Send_LastActivity_Request((CList_GetActiveContact()->full_name));
      break;
    }

    case MI_QUERY_VERSION:
      {

        Send_Version_Request(CList_GetActiveContact()->full_name);
        break;
      }

    case MI_LOGIN_LOGOUT:
      {

        char *pres_str = malloc(256);
        TRESOURCE *Transport = CList_GetActiveContact();
        if(Transport->status==PRESENCE_OFFLINE)
        {
          snprintf(pres_str,255,"<presence to='%s'/>", Transport->full_name);
        }
        else
        {
          snprintf(pres_str,255,"<presence to='%s' type='unavailable'/>", Transport->full_name);
        }
        SUBPROC((void*)_sendandfree,pres_str);
        break;
      }

    case MI_DISCO_QUERY:
      {
        Send_DiscoInfo_Request(CList_GetActiveContact()->full_name);
        break;
      }
      ////////////////////////HISTORY
    case MI_HISTORY_OPEN:
      {
	extern const char HIST_PATH[128];
        char *fn=malloc(1024);
        sprintf(fn,"%s%s.txt",HIST_PATH,CList_FindContactByJID(CList_GetActiveContact()->full_name)->JID);
        int len = strlen(fn)+16;
        WSHDR *wsfn = AllocWS(len);
        utf8_2ws(wsfn, fn, len);
        ExecuteFile(wsfn,NULL,NULL);
        FreeWS(wsfn);
        mfree(fn);
        break;
      }
      
    case MI_MUC_ADMIN:
      {
        Disp_MA_Menu();
        break;
      }
      
    case MI_SUBSCRIBES_MENU:
      {
        Disp_Cont_Menu();
        break;
      }

    case MI_CHANGECONTACT_VERSION:
      {
        Disp_JID_Enter_Dialog(CList_FindContactByJID(CList_GetActiveContact()->full_name));
        break;
      }      
    default:
      {
        MsgBoxError(1,(int)LG_UNKACTION);
      }
    }

    return 1;
  }
  //  Req_Close_Cont_Menu = 1;
  return 0;
}

void InitMenuArray()
{
  for(int i=0;i<MAX_ITEMS;i++)Menu_Contents[i]=0;
}

/*
§°§Ò§â§Ñ§Ò§à§ä§é§Ú§Ü §á§à§ñ§Ó§Ý§Ö§ß§Ú§ñ §á§å§ß§Ü§ä§à§Ó §Õ§Ú§ß§Ñ§Þ§Ú§é§Ö§ã§Ü§à§Ô§à §Þ§Ö§ß§ð
§´§å§ä §Þ§í §ã§Ñ§Þ§Ú §ã§à§Ù§Õ§Ñ§×§Þ §Ü§Ñ§Ø§Õ§í§Û §á§å§ß§Ü§ä, §å§Ü§Ñ§Ù§í§Ó§Ñ§ñ §Õ§Ý§ñ §ß§Ö§Ô§à §Ú§Ü§à§ß§Ü§å §Ú §ä§Ö§Ü§ã§ä.
§±§â§Ú §ã§à§Ù§Õ§Ñ§ß§Ú§Ú §Þ§í §à§á§Ú§â§Ñ§Ö§Þ§ã§ñ §ß§Ñ §Õ§Ñ§ß§ß§í§Ö §Þ§Ñ§ã§ã§Ú§Ó§Ñ Menu_Contents, §Ó §Ü§à§ä§à§â§à§Þ §à§á§Ú§ã§Ñ§ß§à,
§Ü§Ñ§Ü§Ú§Ö §á§å§ß§Ü§ä§í §Ú §Ó §Ü§Ñ§Ü§à§Þ §á§à§â§ñ§Õ§Ü§Ö §ß§Ö§à§Ò§ç§à§Õ§Ú§Þ§à §ã§à§Ù§Õ§Ñ§ä§î.
*/
void contact_menu_iconhndl(void *data, int curitem, void *unk)
{
  //  cmS_ICONS[0]=(int)cmdummy_icon;
  WSHDR *ws;
  char test_str[48];
  void *item=AllocMenuItem(data);
  strcpy(test_str,"(´íÎó)");

  TRESOURCE *Act_contact = CList_GetActiveContact();

  switch(Menu_Contents[curitem])
  {
  case MI_CONF_LEAVE:
    {
      strcpy(test_str,LG_ABANDON);
      break;
    }
  case MI_CONF_CLEAR:
    {
      strcpy(test_str,LG_MUCCLEAR);
      break;
    }

  case MI_QUERY_VERSION:
    {
      strcpy(test_str,LG_VERCLIENT);
      break;
    }

  case MI_DISCO_QUERY:
    {
      strcpy(test_str,LG_INFOFDISC);
      break;
    }
  case MI_TIME_QUERY:
    {
      strcpy(test_str,LG_QUERYTIME);
      break;
    }

  case MI_VCARD_QUERY:
    {
      strcpy(test_str,LG_QUERYVCARD);
      break;
    }

  case MI_LASTACTIV_QUERY:
    {
      strcpy(test_str,LG_QUERYLAST);
      break;
    }

  case MI_HISTORY_OPEN:
    {
      strcpy(test_str,LG_OHISTORY);
      break;
    }
  case MI_LOGIN_LOGOUT:
    {
      if(Act_contact->status==PRESENCE_OFFLINE)
      {
        strcpy(test_str,LG_ON);
      }
      else
      {
        strcpy(test_str,LG_OFF);
      }
      break;
    }
    
  case MI_MUC_ADMIN:
    {
      strcpy(test_str,LG_MUC_ADMIN);
      break;
    }
    
  case MI_SUBSCRIBES_MENU:
    {
      strcpy(test_str,LG_SUBSCR);
      break;
    }
  case MI_CHANGECONTACT_VERSION:
    {
      strcpy(test_str,LG_EDIT);
      break;
    }

  }
  //ShowMSG(1,(int)test_str);
  ws=AllocMenuWS(data,strlen(test_str));
  ascii2ws(ws, test_str);

  SetMenuItemIconArray(data,item,cmS_ICONS+Menu_Contents[curitem]);
  SetMenuItemText(data,item,ws,curitem);
  //SetMenuItemIcon(data,curitem,Menu_Contents[curitem]);  // 0 = §Ú§ß§Õ§Ö§Ü§ã §Ú§Ü§à§ß§Ü§Ú
  /*
  CLIST *t;
  WSHDR *ws;
  void *item=AllocMenuItem(data);

  t=FindContactByN(curitem);
  if (t)
  {
  ws=AllocMenuWS(data,strlen(t->name));
  wsprintf(ws,percent_t,t->name);
}
  else
  {
  ws=AllocMenuWS(data,10);
  wsprintf(ws,"error");
}
  SetMenuItemIconArray(data,item,S_ICONS);
  SetMenuItemText(data,item,ws,curitem);
  SetMenuItemIcon(data,curitem,GetIconIndex(t));
  */
};

/*
#define MI_CONF_LEAVE       1
#define MI_CONF_KICK_THIS   2
#define MI_CONF_BAN_THIS    3
#define MI_CONF_VREJ_THIS   4
#define MI_CONF_VGR_THIS    5
#define MI_QUERY_VERSION    6
*/
extern const char PATH_TO_PIC[128];

char ICON_CONF_LEAVE[128];// = {(int)PATH_TO_PIC"menu_muc_leave.png",0};
char ICON_CONF_KICK_THIS[128];
char ICON_CONF_BAN_THIS[128];
char ICON_CONF_VREJ_THIS[128];
char ICON_CONF_VGR_THIS[128];
char ICON_QUERY_VERSION[128];
char ICON_LOGIN_LOGOUT[128];
char ICON_QUERY_DISCO[128];
char ICON_HISTORY_OPEN[128];
char ICON_QUERY_TIME[128];
char ICON_QUERY_VCARD[128];
char ICON_MUC_ADMIN[128];
char ICON_QUERY_LASTACTIV[128];
char ICON_SUBSCRIBE_MENU[128];

void Init_Icon_array()
{
  TRESOURCE *Act_contact = CList_GetActiveContact();

  strcpy(ICON_CONF_LEAVE, PATH_TO_PIC);strcat(ICON_CONF_LEAVE, "menu_muc_leave.png");
  strcpy(ICON_QUERY_VERSION, PATH_TO_PIC);strcat(ICON_QUERY_VERSION, "menu_version.png");
  strcpy(ICON_QUERY_DISCO, PATH_TO_PIC);strcat(ICON_QUERY_DISCO, "menu_disco.png");
  strcpy(ICON_HISTORY_OPEN, PATH_TO_PIC);strcat(ICON_HISTORY_OPEN, "menu_history.png");
  strcpy(ICON_QUERY_TIME, PATH_TO_PIC);strcat(ICON_QUERY_TIME, "menu_time.png");
  strcpy(ICON_QUERY_VCARD, PATH_TO_PIC);strcat(ICON_QUERY_VCARD, "menu_vcard.png");
  strcpy(ICON_QUERY_LASTACTIV, PATH_TO_PIC);strcat(ICON_QUERY_LASTACTIV, "menu_idle.png");
  strcpy(ICON_LOGIN_LOGOUT, PATH_TO_PIC);
  strcpy(ICON_MUC_ADMIN, PATH_TO_PIC);strcat(ICON_MUC_ADMIN, "menu_kick.png");
  strcpy(ICON_SUBSCRIBE_MENU, PATH_TO_PIC);strcat(ICON_SUBSCRIBE_MENU, "menu_kick.png");  
  if(Act_contact->entry_type==T_TRANSPORT)
    if(Act_contact->status==PRESENCE_OFFLINE)
    {
      strcat(ICON_LOGIN_LOGOUT, "menu_version.png");
    }
    else strcat(ICON_LOGIN_LOGOUT, "menu_no_icon.png");

  for(int i=0;i<=MAX_ITEMS;i++)cmS_ICONS[i]=0;
  cmS_ICONS[MI_CONF_LEAVE]=(int)ICON_CONF_LEAVE;
  cmS_ICONS[MI_QUERY_VERSION]=(int)ICON_QUERY_VERSION;
  cmS_ICONS[MI_DISCO_QUERY]=(int)ICON_QUERY_DISCO;
  cmS_ICONS[MI_HISTORY_OPEN]=(int)ICON_HISTORY_OPEN;
  cmS_ICONS[MI_TIME_QUERY]=(int)ICON_QUERY_TIME;
  cmS_ICONS[MI_VCARD_QUERY]=(int)ICON_QUERY_VCARD;
  cmS_ICONS[MI_LASTACTIV_QUERY]=(int)ICON_QUERY_LASTACTIV;  
  cmS_ICONS[MI_LOGIN_LOGOUT]=(int)ICON_LOGIN_LOGOUT;
  cmS_ICONS[MI_MUC_ADMIN]=(int)ICON_MUC_ADMIN;
  cmS_ICONS[MI_SUBSCRIBES_MENU]=(int)  ICON_SUBSCRIBE_MENU;
  cmS_ICONS[MI_CHANGECONTACT_VERSION]=(int)  ICON_SUBSCRIBE_MENU;
  cmS_ICONS[MI_CONF_CLEAR]=(int)ICON_SUBSCRIBE_MENU;
}

void Disp_Contact_Menu()
{
  int n_items=0;
  InitMenuArray();
  Init_Icon_array();
  TRESOURCE *Act_contact = CList_GetActiveContact();
  // §´§Ö§á§Ö§â§î §à§á§â§Ö§Õ§Ö§Ý§ñ§Ö§Þ, §Ü§Ñ§Ü§Ú§Ö §á§å§ß§Ü§ä§í §å §ß§Ñ§ã §Ò§å§Õ§å§ä, §Ú §ã§Ü§à§Ý§î§Ü§à
  if(!Act_contact)return;
  if(Act_contact->entry_type==T_CONF_ROOT)
  {
    if(Act_contact->status!=PRESENCE_OFFLINE) Menu_Contents[n_items++]=MI_CONF_LEAVE;
    Menu_Contents[n_items++]=MI_HISTORY_OPEN;
    Menu_Contents[n_items++]=MI_DISCO_QUERY;
    if(Act_contact->total_msg_count) Menu_Contents[n_items++]=MI_CONF_CLEAR;
  }

  if((Act_contact->entry_type==T_CONF_NODE)&&(Act_contact->status!=PRESENCE_OFFLINE))
  {
    TRESOURCE* MYMUCRES = CList_IsResourceInList(CList_FindMUCByJID(CList_FindContactByJID(Act_contact->full_name)->JID)->conf_jid);
    Menu_Contents[n_items++]=MI_QUERY_VERSION;
    Menu_Contents[n_items++]=MI_DISCO_QUERY;
    Menu_Contents[n_items++]=MI_VCARD_QUERY;
    Menu_Contents[n_items++]=MI_TIME_QUERY;
    Menu_Contents[n_items++]=MI_LASTACTIV_QUERY;
  if(!(MYMUCRES->muc_privs.role<ROLE_MODERATOR)&&(MYMUCRES->muc_privs.aff>Act_contact->muc_privs.aff||(MYMUCRES->muc_privs.aff<AFFILIATION_ADMIN&&Act_contact->muc_privs.role<ROLE_MODERATOR))||MYMUCRES->muc_privs.aff==AFFILIATION_OWNER)
    {
      Menu_Contents[n_items++]=MI_MUC_ADMIN;
    }
  }

  if((Act_contact->entry_type==T_NORMAL)||(Act_contact->entry_type==T_VIRTUAL))
  {
    Menu_Contents[n_items++]=MI_QUERY_VERSION;
    Menu_Contents[n_items++]=MI_HISTORY_OPEN;
    Menu_Contents[n_items++]=MI_DISCO_QUERY;
    Menu_Contents[n_items++]=MI_VCARD_QUERY;
    Menu_Contents[n_items++]=MI_TIME_QUERY;
    Menu_Contents[n_items++]=MI_LASTACTIV_QUERY;
    Menu_Contents[n_items++]=MI_SUBSCRIBES_MENU;
    Menu_Contents[n_items++]=MI_CHANGECONTACT_VERSION;
  }

  if(Act_contact->entry_type==T_TRANSPORT)
  {
    Menu_Contents[n_items++]=MI_LOGIN_LOGOUT;
    Menu_Contents[n_items++]=MI_QUERY_VERSION;
    Menu_Contents[n_items++]=MI_DISCO_QUERY;
    Menu_Contents[n_items++]=MI_VCARD_QUERY;
    Menu_Contents[n_items++]=MI_TIME_QUERY;
    Menu_Contents[n_items++]=MI_LASTACTIV_QUERY;
    Menu_Contents[n_items++]=MI_SUBSCRIBES_MENU;
    Menu_Contents[n_items++]=MI_CHANGECONTACT_VERSION;
  }
  
  if(n_items)
  {
    patch_rect(&contact_menuhdr.rc,0,YDISP,ScreenW()-1,HeaderH()+YDISP);
    Contact_MenuID=CreateMenu(0,0,&contact_menu,&contact_menuhdr,0,n_items,0,0);
  }
  //else
  //{
  //MsgBoxError(1,(int)LG_NOSUPACTION);
  //}
}

//////////////////////// Menu "muc#admin" ///////////////////////////
void ma_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)  // onFocus
  {
    DisableIDLETMR();
  }
}

int ma_menu_onkey(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  MUC_ADMIN admin_cmd;
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    CLIST* room=CList_FindContactByJID(CList_GetActiveContact()->full_name);
    char* nick = Get_Resource_Name_By_FullJID(CList_GetActiveContact()->full_name);
    if(MA_Menu_Contents[i]==MA_CONF_KICK_THIS)admin_cmd=ADM_KICK;
    if(MA_Menu_Contents[i]==MA_CONF_BAN_THIS)admin_cmd=ADM_BAN;
    if(MA_Menu_Contents[i]==MA_CONF_VREJ_THIS)admin_cmd=ADM_VOICE_REMOVE;
    if(MA_Menu_Contents[i]==MA_CONF_VGR_THIS)admin_cmd=ADM_VOICE_GRANT;
    if(MA_Menu_Contents[i]==MA_CONF_PARTICIPANT)admin_cmd=ADM_PARTICIPANT;
    if(MA_Menu_Contents[i]==MA_CONF_MEMBER)admin_cmd=ADM_MEMBER;
    if(MA_Menu_Contents[i]==MA_CONF_MODERATOR)admin_cmd=ADM_MODERATOR;
    if(MA_Menu_Contents[i]==MA_CONF_MGR)admin_cmd=ADM_MODERATOR_REMOVE;
    if(MA_Menu_Contents[i]==MA_CONF_ADMIN)admin_cmd=ADM_ADMIN;
    if(MA_Menu_Contents[i]==MA_CONF_OWNER)admin_cmd=ADM_OWNER;
    ConstructReasonDlg(room->JID, nick, admin_cmd);
    //MUC_Admin_Command(room->JID, nick, admin_cmd, "SieJC_muc#admin");
    return 1;
  }
  return 0;
}

void ma_menu_iconhndl(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  char test_str[48];
  void *item=AllocMenuItem(data);
  strcpy(test_str,"(´íÎó)");

  TRESOURCE *Act_contact = CList_GetActiveContact();

  switch(MA_Menu_Contents[curitem])
  {
  case MA_CONF_KICK_THIS:
    {
      strcpy(test_str,LG_KIK);
      break;
    }
  case MA_CONF_BAN_THIS:
    {
      strcpy(test_str,LG_BAN);
      break;
    }
  case MA_CONF_VREJ_THIS:
    {
      strcpy(test_str,LG_LVOISE);
      break;
    }
  case MA_CONF_VGR_THIS:
    {
      strcpy(test_str,LG_GVOISE);
      break;
    }

  case MA_CONF_PARTICIPANT:
    {
      strcpy(test_str,LG_PARTICIPANT);
      break;
    }

  case MA_CONF_MEMBER:
    {
      strcpy(test_str,LG_MEMBER);
      break;
    }
  case MA_CONF_MGR:
    {
      strcpy(test_str,LG_MODERATOR_REMOVE);
      break;   
    }
    
  case MA_CONF_MODERATOR:
    {
      strcpy(test_str,LG_MODERATOR);
      break;
    }

  case MA_CONF_ADMIN:
    {
      strcpy(test_str,LG_ADMIN);
      break;
    }

  case MA_CONF_OWNER:
    {
      strcpy(test_str,LG_OWNER);
      break;
    }
  }

  ws=AllocMenuWS(data,strlen(test_str));
  ascii2ws(ws, test_str);

  SetMenuItemText(data,item,ws,curitem);
}

//////////SUBSCRIBE
void contc_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)  // onFocus
  {
    DisableIDLETMR();
  }
}

int contc_menu_onkey(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    char* jid=CList_FindContactByJID(CList_GetActiveContact()->full_name)->JID;
//    char* nick = Get_Resource_Name_By_FullJID(CList_GetActiveContact()->full_name);
    switch(CONTC_Menu_Contents[i])
    {
    case CONTC_SUBSCRIBE:
      {
        Send_ShortPresence(jid,8);
      break;    
      }
    case CONTC_SUBSCRIBED:
      {
        Send_ShortPresence(jid,9);
      break;    
      }
    case CONTC_UNSUBSCRIBE:
      {
        Send_ShortPresence(jid,10);
      break;    
      }
    case CONTC_UNSUBSCRIBED:
      {
        Send_ShortPresence(jid,11);
      break;    
      }
 default:
    {
      MsgBoxError(1,(int)LG_UNKACTION);
    }      
    }
    return 1;
  }
  return 0;
}

void contc_menu_iconhndl(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  char test_str[48];
  void *item=AllocMenuItem(data);
  strcpy(test_str,"(´íÎó)");

  TRESOURCE *Act_contact = CList_GetActiveContact();

  switch(CONTC_Menu_Contents[curitem])
  {
  case CONTC_SUBSCRIBE:
    {
      strcpy(test_str,LG_SUBSCRIBE);
      break;
    }
  case CONTC_SUBSCRIBED:
    {
      strcpy(test_str,LG_SUBSCRIBED);
      break;
    }
  case CONTC_UNSUBSCRIBED:
    {
      strcpy(test_str,LG_UNSUBSCRIBED);
      break;
    }
  case CONTC_UNSUBSCRIBE:
    {
      strcpy(test_str,LG_UNSUBSCRIBE);
      break;
    }
  }

  ws=AllocMenuWS(data,strlen(test_str));
  ascii2ws(ws, test_str);
  SetMenuItemText(data,item,ws,curitem);
}

//=====================================================

int reason_onkey(GUI *gui, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg == KEY_DOWN)
  {
    if ((msg->gbsmsg->submess == GREEN_BUTTON) || (msg->keys == 0x0018))
    {
      EDITCONTROL ec;
      char *s = malloc(256);
      int len;
      ExtractEditControl(gui, reason_pos, &ec);
      ws_2utf8(ec.pWS, s, &len, 256);
      MUC_Admin_Command(room_name, room_jid, macmd, s);
      mfree(s);
      return 1;
    }
  }
  return 0;
}

void reason_ghook(GUI *gui, int cmd)
{
  if (cmd == 7)
  {
    static SOFTKEY_DESC sk = {0x0018, 0x0000, (int)LG_OK};
#ifdef NEWSGOLD
    SetSoftKey(gui, &sk, 0);
#else
    SetSoftKey(gui, &sk, 1);
#endif
  }
}

void reason_locret(void) {};

SOFTKEY_DESC reason_sk[]=
{
  {0x0018,0x0000,(int)LG_OK},
  {0x0001,0x0000,(int)LG_CLOSE},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB reason_skt=
{
  reason_sk,0
};

HEADER_DESC reason_hdr={0,0,0,0,NULL,(int)LG_REASON,LGP_NULL};

INPUTDIA_DESC reason_desc=
{
  1,
  reason_onkey,
  reason_ghook,
  (void *)reason_locret,
  0,
  &reason_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

void ConstructReasonDlg(char *name, char *jid, MUC_ADMIN muccmd)
{
  switch (muccmd)
  {
  case ADM_KICK:
  case ADM_BAN:
    {
      room_name = name;
      room_jid = jid;
      macmd = muccmd;
      
      WSHDR *ws = AllocWS(256);
      EDITCONTROL ec;
      void *ma=malloc_adr();
      void *eq=AllocEQueue(ma,mfree_adr());
      
      wsprintf(ws, "SieJC_muc#admin");
      PrepareEditControl(&ec);
      ConstructEditControl(&ec, 4, 0, ws, 256);
      reason_pos = AddEditControlToEditQend(eq,&ec,ma);
      
      patch_header(&reason_hdr);
      patch_input(&reason_desc);
      CreateInputTextDialog(&reason_desc,&reason_hdr,eq,1,NULL);
      break;
    }
  default:
    {
      MUC_Admin_Command(name, jid, muccmd, "");
    }
  }
}
