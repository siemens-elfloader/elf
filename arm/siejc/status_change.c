/*
     SieNatJabber Project
    UI для смены своего статуса
*/
#include "../inc/swilib.h"
#include "main.h"
#include "jabber_util.h"
#include "status_change.h"
#include "string_util.h"
#include "conf_loader.h"
#include "lang.h"
#include "rect_patcher.h"
#include "roster_icons.h"

extern char My_Presence;
extern const char* PRESENCES[PRES_COUNT];
extern const char DEFTEX_ONLINE[];
extern const char DEFTEX_CHAT[];
extern const char DEFTEX_AWAY[];
extern const char DEFTEX_XA[];
extern const char DEFTEX_DND[];
extern const char DEFTEX_INVISIBLE[];
extern const char DEFTEX_OFFLINE[];

#define STATUSES_NUM 7

static const char * const status_texts[STATUSES_NUM]=
{
  DEFTEX_ONLINE,
  DEFTEX_CHAT,
  DEFTEX_AWAY,
  DEFTEX_XA,
  DEFTEX_DND,
  DEFTEX_INVISIBLE,
  DEFTEX_OFFLINE
};

/*
  Select status menu
*/

HEADER_DESC select_status_menu_header={0,0,131,21,NULL,(int)LG_STATUSSEL,LGP_NULL};

int select_status_menu_softkeys[]={0,1,2};

SOFTKEY_DESC select_status_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_EDIT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB select_status_menu_skt=
{
  select_status_menu_sk, 3
};

int select_status_menu_onkey(void *data, GUI_MSG *msg)
{
  if (msg->keys==0x18)
  {
    EditStatus(GetCurMenuItem(data));
    return(-1);
  }
  if (msg->keys==0x3D)
  {
    int i = GetCurMenuItem(data);
    extern ONLINEINFO OnlineInfo;
    char * status_text = malloc(strlen(status_texts[i])+1);
    strcpy(status_text, status_texts[i]);
    PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
    pr_info->priority = OnlineInfo.priority;
    pr_info->status = i;
    pr_info->message = status_text;
    //mfree(status_text);
    SUBPROC((void*)Send_Presence,pr_info);    
    return 1;
  }  
  return 0;
}

int select_status_menu_icons[STATUSES_NUM];

void select_status_menu_ghook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd == TI_CMD_DESTROY)
  {
    for(int i = 0; i < STATUSES_NUM; i ++)
      mfree((void *)select_status_menu_icons[i]);
  }
}

static const char * const select_status_menu_texts[STATUSES_NUM]=
{
  LG_STONLINE,
  LG_STCHAT,
  LG_STAWAY,
  LG_STXA,
  LG_STDND,
  LG_STINVIS,
  LG_STOFFLINE
};

void select_status_menu_itemhandler(void *data, int curitem, void *unk)
{
  void * item = AllocMLMenuItem(data);
  WSHDR * ws1 = AllocMenuWS(data, strlen(select_status_menu_texts[curitem]));
  ascii2ws(ws1, select_status_menu_texts[curitem]);
  WSHDR * ws2 = AllocMenuWS(data, strlen(status_texts[curitem]));
  utf8_2ws(ws2, status_texts[curitem], strlen(status_texts[curitem])*2);
  SetMenuItemIconArray(data, item, select_status_menu_icons + curitem);
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

static const ML_MENU_DESC select_status_menu_struct=
{
  8,
  select_status_menu_onkey,
  select_status_menu_ghook,
  NULL,
  select_status_menu_softkeys,
  &select_status_menu_skt,
  0x11,
  select_status_menu_itemhandler,
  NULL,
  NULL,
  STATUSES_NUM,
  1
};

void ShowStatusSelectMenu()
{
  select_status_menu_icons[0] = (int)Roster_getIconByStatus(NULL, PRESENCE_ONLINE);
  select_status_menu_icons[1] = (int)Roster_getIconByStatus(NULL, PRESENCE_CHAT);
  select_status_menu_icons[2] = (int)Roster_getIconByStatus(NULL, PRESENCE_AWAY);
  select_status_menu_icons[3] = (int)Roster_getIconByStatus(NULL, PRESENCE_XA);
  select_status_menu_icons[4] = (int)Roster_getIconByStatus(NULL, PRESENCE_DND);
  select_status_menu_icons[5] = (int)Roster_getIconByStatus(NULL, PRESENCE_INVISIBLE);
  select_status_menu_icons[6] = (int)Roster_getIconByStatus(NULL, PRESENCE_OFFLINE);
  if (My_Presence < PRESENCE_OFFLINE)
    select_status_menu_header.icon = &select_status_menu_icons[My_Presence];
  
  patch_header(&select_status_menu_header);
  CreateMultiLinesMenu(NULL, NULL, &select_status_menu_struct, &select_status_menu_header, My_Presence < PRESENCE_OFFLINE ? My_Presence: 0, STATUSES_NUM);
}

/*
  Edit status
*/

int edit_status_menu_softkeys[]={0,1,2};

SOFTKEY_DESC edit_status_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_EDIT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB edit_status_menu_skt=
{
  edit_status_menu_sk, 3
};

int edit_status_menu_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  if(msg->gbsmsg->submess==GREEN_BUTTON  || msg->keys == 0x18)
  {
    ExtractEditControl(data, 2, &ec);
    char * status_text = malloc(1024);
    if(ec.pWS->wsbody[0])
    {
      int res_len;
      //status_text = malloc(ec.pWS->wsbody[0] * 2 + 1);
      ws_2utf8(ec.pWS, status_text, &res_len, ec.pWS->wsbody[0] * 2 + 1);
      status_text = realloc(status_text, res_len + 1);
      status_text[res_len]='\0';
      strcpy((char *)status_texts[(int)EDIT_GetUserPointer(data)], status_text);
    }
    else
    {
      extern const char empty_t[];
      sprintf(status_text, empty_t);
      sprintf((char *)status_texts[(int)EDIT_GetUserPointer(data)], empty_t);
    }
    
    PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
    EDITCONTROL ec2;
    ExtractEditControl(data, 4, &ec2);
    char *status_prior = malloc(10);
    ws_2str(ec2.pWS, status_prior, 10);
    extern const char percent_d[];
    sscanf(status_prior, percent_d, &pr_info->priority);
    pr_info->status = (int)EDIT_GetUserPointer(data);
    pr_info->message = status_text; //неосвобождать
//    if (status_text) mfree(status_text);
    extern ONLINEINFO OnlineInfo;
    if(pr_info->priority!=OnlineInfo.priority)
    SUBPROC((void*)Send_Presence,pr_info);
    else mfree(pr_info);
    SaveConfigData(successed_config_filename);
    mfree(status_prior);
    return 1;
  }
  if (msg->keys==0x0FF0) //Левый софт СГОЛД
  {
    return(1);
  }
  return 0;
}

void edit_status_menu_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec;
  static SOFTKEY_DESC stchsk={0x0018, 0x0000,(int)LG_OK};

  if (cmd == TI_CMD_REDRAW)
  {
    ExtractEditControl(data, 2, &ec);
#ifndef NEWSGOLD
  static const SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)LG_CLOSE};
#endif  
    //OnRun
#ifdef NEWSGOLD
    SetSoftKey(data,&stchsk,0);
#else
    SetSoftKey(data,&stchsk,1);
    if (ec.pWS->wsbody[0]==0)
      SetSoftKey(data,&sk_cancel,SET_SOFT_KEY_N==0?1:0);    
#endif
  }

  if(cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}

HEADER_DESC edit_status_menu_header={0,0,131,21,NULL,(int)LG_STATUS,LGP_NULL};

void edit_status_menu_locret(void){}

INPUTDIA_DESC edit_status_menu_struct=
{
  1,
  edit_status_menu_onkey,
  edit_status_menu_ghook,
  (void *)edit_status_menu_locret,
  0,
  &edit_status_menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

void EditStatus(int status_n)
{
  WSHDR * ws = AllocWS(256);
  EDITCONTROL ec;
  void * ma = malloc_adr();
  void * eq = AllocEQueue(ma,mfree_adr());
  
  PrepareEditControl(&ec);

  ascii2ws(ws, LG_ENTERTEXTSTATUS);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);

  utf8_2ws(ws, status_texts[status_n], strlen(status_texts[status_n])*2);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 256);
  AddEditControlToEditQend(eq, &ec, ma);

  ascii2ws(ws, LG_PRIORITY);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq, &ec, ma);
  
  extern ONLINEINFO OnlineInfo;
  wsprintf(ws, "%d",OnlineInfo.priority);
  ConstructEditControl(&ec, ECT_FIXED_STR_NUM, ECF_APPEND_EOL, ws, 2);
  AddEditControlToEditQend(eq, &ec, ma);

  patch_input(&edit_status_menu_struct);
  patch_header(&edit_status_menu_header);
  CreateInputTextDialog(&edit_status_menu_struct, &edit_status_menu_header, eq, 1, (void *)status_n);
  FreeWS(ws);
}

//EOL,EOF
