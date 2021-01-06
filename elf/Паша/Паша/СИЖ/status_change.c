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
//===============================================================================================
// ELKA Compatibility
#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}
//===============================================================================================


extern int My_Presence;
extern const char* PRESENCES[PRES_COUNT];
int StatChange_Menu_ID;

void Change_Status(char status)
{
    //CurrentStatus = status;
    GeneralFunc_flag1(StatChange_Menu_ID,1);
}

#define STATUSES_NUM 6

HEADER_DESC st_menuhdr={0,0,131,21,NULL,(int)LG_STATUSSEL,LGP_NULL};

int st_menusoftkeys[]={0,1,2};

// "online", "chat", "away", "xa", "dnd", "invisible"
MENUITEM_DESC st_menuitems[STATUSES_NUM]=
{
  {NULL,(int)LG_STONLINE,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_STCHAT,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_STAWAY,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_STXA,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_STDND,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)LG_STINVIS,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

void dummy(GUI *data){};
const MENUPROCS_DESC st_menuprocs[STATUSES_NUM]={
                                  dummy,
                                  dummy,
                                  dummy,
                                  dummy,
                                  dummy,
                                  dummy
                                 };

SOFTKEY_DESC st_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB st_menu_skt=
{
  st_menu_sk,3
};

WSHDR* ews;
char sTerminate=0;
char Selected_Status=0;

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  //-1 - do redraw
  if(msg->gbsmsg->submess==GREEN_BUTTON  || msg->keys==0x18)
  {
    sTerminate = 1;
    GeneralFunc_flag1(StatChange_Menu_ID,1);
    return 1;
  }
 
  if (msg->keys==0x0FF0) //Левый софт СГОЛД
  {
    return(1);
  }  
  return 0;
  //1: close
}

void ed1_ghook(GUI *data, int cmd)
{
  EDITCONTROL ec;
  static SOFTKEY_DESC stchsk={0x0018, 0x0000,(int)LG_OK};

  if (cmd==7)
  { 
    ExtractEditControl(data,2,&ec);
    wstrcpy(ews,ec.pWS);
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

  if(sTerminate)  // cmd==9 - нажатие на левую софт-кнопку "ОК"
 {
//     char q[10];
//     sprintf(q,"N=%d",cmd);
//     ShowMSG(1,(int)q);
   sTerminate=0;

/*
   size_t xz = wstrlen(ews)*2;
   char* body;
   if(xz)
   {
      body =  utf16_to_utf8((char**)ews,&xz);
      body[xz]='\0';
   }
   else body = NULL;
*/
     char* body;
     if(wstrlen(ews))
     {
       int res_len;
       body = malloc(wstrlen(ews)*2+1);
       ws_2utf8(ews, body, &res_len, wstrlen(ews)*2+1);
       body = realloc(body, res_len+1);
       body[res_len]='\0';
     }else body = NULL;

    PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
    extern long  strtol (const char *nptr,char **endptr,int base);
    ExtractEditControl(data,4,&ec);    // = priority
    wstrcpy(ews,ec.pWS);
    char ss[10];
    ws_2str(ews,ss,15);
    pr_info->priority = strtol (ss,0,10);
    pr_info->status=Selected_Status;
    pr_info->message=  body==NULL ? NULL : Mask_Special_Syms(body);
    mfree(body);
    SUBPROC((void*)Send_Presence,pr_info);
   }

  if(cmd==0x03)     // onDestroy
  {
    FreeWS(ews);
  }
}

HEADER_DESC ed1_hdr={0,0,131,21,NULL,(int)LG_STATUS,LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)dummy,
  0,
  &st_menu_skt,
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
  void *ma=malloc_adr();
  extern const char percent_t[];
  char textstatus[255]="";
  extern const char DEFTEX_ONLINE[];
  extern const char DEFTEX_CHAT[];
  extern const char DEFTEX_AWAY[];
  extern const char DEFTEX_XA[];
  extern const char DEFTEX_DND[];
  extern const char DEFTEX_INVISIBLE[];

 switch (curentstat)
  {
  case 0:
    strcpy(textstatus,DEFTEX_ONLINE);break;
  case 1:
    strcpy(textstatus,DEFTEX_CHAT);break;
  case 2:
    strcpy(textstatus,DEFTEX_AWAY);break;
  case 3:
    strcpy(textstatus,DEFTEX_XA);break;
  case 4:
    strcpy(textstatus,DEFTEX_DND);break;
  case 5:
    strcpy(textstatus,DEFTEX_INVISIBLE);
  }

  sTerminate =0;
  void *eq;
  EDITCONTROL ec;
  ews=AllocWS(256);

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  wsprintf(ews,percent_t,LG_ENTERTEXTSTATUS);
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,textstatus);
  ConstructEditControl(&ec,3,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,percent_t,LG_PRIORITY);
  ConstructEditControl(&ec,1,0x40,ews,256);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"0");
  ConstructEditControl(&ec,5,0x40,ews,2);
  AddEditControlToEditQend(eq,&ec,ma);

  patch_input(&ed1_desc);
  patch_header(&ed1_hdr);
  CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}

int menu_onKey(void *data, GUI_MSG *msg)
{
  if (msg->keys==0x3D)
  {
    Selected_Status=GetCurMenuItem(data);
    Disp_AddSettings_Dialog(Selected_Status);
    return(-1);
  }  
  
  if (msg->keys==0x0018)
  {
    Selected_Status=GetCurMenuItem(data);
    //Disp_AddSettings_Dialog();
    //sTerminate = 1;
    
    sTerminate=0;
    PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
    pr_info->priority = '00';
    pr_info->status=Selected_Status;
    pr_info->message=NULL;
    SUBPROC((void*)Send_Presence,pr_info);    
    return 1;
  }  
  return 0;
}

void menu_gHook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  
 /* if(sTerminate)
  {
    sTerminate=0;

    PRESENCE_INFO *pr_info = malloc(sizeof(PRESENCE_INFO));
    pr_info->priority = '00';
    pr_info->status=Selected_Status;
    pr_info->message=NULL;
    SUBPROC((void*)Send_Presence,pr_info);
   }  */
}

MENU_DESC st_tmenu=
{
  8,menu_onKey,menu_gHook,NULL,
  st_menusoftkeys,
  &st_menu_skt,
  1,//MENU_FLAG,
  NULL,
  st_menuitems,
  st_menuprocs,
  STATUSES_NUM
};

//int SS_ICONS[STATUSES_NUM];

void DispStatusChangeMenu()
{
  /*
  st_menuitems[0].icon = S_ICONS+IS_ONLINE;
  st_menuitems[1].icon = S_ICONS+IS_AWAY;
  st_menuitems[2].icon = S_ICONS+IS_NA;
  st_menuitems[3].icon = S_ICONS+IS_DND;
  st_menuitems[4].icon = S_ICONS+IS_OCCUPIED;
  st_menuitems[5].icon = S_ICONS+IS_FFC;
  st_menuitems[6].icon = S_ICONS+IS_INVISIBLE;
  st_menuhdr.icon=S_ICONS+CurrentStatus;
*/
  patch_header(&st_menuhdr);
  Selected_Status = 0;
  StatChange_Menu_ID = CreateMenu(0,0,&st_tmenu,&st_menuhdr,0,STATUSES_NUM,0,0);
}
