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

int StatChange_Menu_ID;
char Selected_Status;

void Change_Status(char status)
{
  GeneralFunc_flag1(StatChange_Menu_ID,1);
}

#define STATUSES_NUM 6

HEADER_DESC status_change_menu_header={0,0,131,21,NULL,(int)LG_STATUSSEL,LGP_NULL};

int status_change_menu_softkeys[]={0,1,2};

SOFTKEY_DESC status_change_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_EDIT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB status_change_menu_skt=
{
  status_change_menu_sk, 3
};

static const char * const status_texts[STATUSES_NUM]=
{
  DEFTEX_ONLINE,
  DEFTEX_CHAT,
  DEFTEX_AWAY,
  DEFTEX_XA,
  DEFTEX_DND,
  DEFTEX_INVISIBLE
};

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  if(msg->gbsmsg->submess==GREEN_BUTTON  || msg->keys==0x18)
  {
    ExtractEditControl(data, 2, &ec);
    char * status_text = NULL;
    if(ec.pWS->wsbody[0])
    {
      int res_len;
      status_text = malloc(ec.pWS->wsbody[0] * 2 + 1);
      ws_2utf8(ec.pWS, status_text, &res_len, ec.pWS->wsbody[0] * 2 + 1);
      status_text = realloc(status_text, res_len + 1);
      status_text[res_len]='\0';
    }
    PRESENCE_INFO * pr_info = malloc(sizeof(PRESENCE_INFO));
    extern long  strtol (const char *nptr,char **endptr,int base);
    ExtractEditControl(data, 4, &ec);    // = priority
    char ss[10];
    ws_2str(ec.pWS, ss, 15);
    pr_info->priority = strtol (ss,0,10);
    pr_info->status = Selected_Status;
    pr_info->message = status_text ? Mask_Special_Syms(status_text) : NULL;
    if (status_text) mfree(status_text);
    SUBPROC((void*)Send_Presence,pr_info);
    GeneralFunc_flag1(StatChange_Menu_ID,1);
    return 1;
  }
  if (msg->keys==0x0FF0) //Левый софт СГОЛД
  {
    return(1);
  }
  return 0;
}

void ed1_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec;
  static SOFTKEY_DESC stchsk={0x0018, 0x0000,(int)LG_OK};

  if (cmd==7)
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

  if(cmd==0x0A)   // Фокусирование
  {
     DisableIDLETMR();   // Отключаем таймер выхода по таймауту
  }
}

HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)LG_STATUS,LGP_NULL};

void ed1_locret(void){}

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &status_change_menu_skt,
  {0,22,131,153},
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

void Disp_AddSettings_Dialog(char curentstat)
{
  WSHDR * ws = AllocWS(256);
  EDITCONTROL ec;
  void * ma = malloc_adr();
  void * eq = AllocEQueue(ma,mfree_adr());
  
  PrepareEditControl(&ec);

  ascii2ws(ws, LG_ENTERTEXTSTATUS);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);

  ascii2ws(ws, status_texts[curentstat]);
  ConstructEditControl(&ec, 4, ECF_APPEND_EOL, ws, 256);
  AddEditControlToEditQend(eq, &ec, ma);

  ascii2ws(ws, LG_PRIORITY);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, ws->wsbody[0]);
  AddEditControlToEditQend(eq, &ec, ma);

  wsprintf(ws, "0");
  ConstructEditControl(&ec, ECT_FIXED_STR_NUM, ECF_APPEND_EOL, ws, 2);
  AddEditControlToEditQend(eq, &ec, ma);

  patch_input(&ed1_desc);
  patch_header(&ed1_hdr);
  CreateInputTextDialog(&ed1_desc, &ed1_hdr, eq, 1, (void *)curentstat);
  FreeWS(ws);
}

int status_change_menu_onkey(void *data, GUI_MSG *msg)
{
  if (msg->keys==0x18)
  {
    Selected_Status = GetCurMenuItem(data);
    Disp_AddSettings_Dialog(Selected_Status);
    return(-1);
  }
  if (msg->keys==0x3D)
  {
    Selected_Status = GetCurMenuItem(data);
    char * status_text = ANSI2UTF8(status_texts[Selected_Status], strlen(status_texts[Selected_Status]));
    PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
    pr_info->priority = 0;
    pr_info->status = Selected_Status;
    pr_info->message = Mask_Special_Syms(status_text);
    mfree(status_text);
    SUBPROC((void*)Send_Presence,pr_info);    
    return 1;
  }  
  return 0;
}

int status_change_menu_icons[STATUSES_NUM];

void status_change_menu_ghook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd == TI_CMD_DESTROY)
  {
    for(int i = 0; i < STATUSES_NUM; i ++)
      mfree((void *)status_change_menu_icons[i]);
  }
}

static const char * const status_change_menu_texts[STATUSES_NUM]=
{
  LG_STONLINE,
  LG_STCHAT,
  LG_STAWAY,
  LG_STXA,
  LG_STDND,
  LG_STINVIS
};

void status_change_menu_itemhandler(void *data, int curitem, void *unk)
{
  void * item = AllocMLMenuItem(data);
  WSHDR * ws1 = AllocMenuWS(data, strlen(status_change_menu_texts[curitem]));
  ascii2ws(ws1, status_change_menu_texts[curitem]);
  WSHDR * ws2 = AllocMenuWS(data, strlen(status_texts[curitem]));
  ascii2ws(ws2, status_texts[curitem]);
  SetMenuItemIconArray(data, item, status_change_menu_icons + curitem);
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

static const ML_MENU_DESC status_change_menu_struct=
{
  8,
  status_change_menu_onkey,
  status_change_menu_ghook,
  NULL,
  status_change_menu_softkeys,
  &status_change_menu_skt,
  0x11,
  status_change_menu_itemhandler,
  NULL,
  NULL,
  STATUSES_NUM,
  1
};

void DispStatusChangeMenu()
{
  status_change_menu_icons[0] = (int)Roster_getIconByStatus(NULL, PRESENCE_ONLINE);
  status_change_menu_icons[1] = (int)Roster_getIconByStatus(NULL, PRESENCE_CHAT);
  status_change_menu_icons[2] = (int)Roster_getIconByStatus(NULL, PRESENCE_AWAY);
  status_change_menu_icons[3] = (int)Roster_getIconByStatus(NULL, PRESENCE_XA);
  status_change_menu_icons[4] = (int)Roster_getIconByStatus(NULL, PRESENCE_DND);
  status_change_menu_icons[5] = (int)Roster_getIconByStatus(NULL, PRESENCE_INVISIBLE);

  patch_header(&status_change_menu_header);
  Selected_Status = 0;
  StatChange_Menu_ID = CreateMultiLinesMenu(NULL, NULL, &status_change_menu_struct, &status_change_menu_header, My_Presence < PRESENCE_OFFLINE ? My_Presence: 0, STATUSES_NUM);
}
