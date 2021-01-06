#include "..\inc\swilib.h"
#include "main.h"
#include "utils.h"
#include "editordialog.h"
#include "IdleLinks.h"
#include "conf_ex.h"

char sprintf_d[] = "%d";

extern int *S_ICONS;

// Здесь все что связано с диалогом добавления / удаления ярлычков

extern const int minus11;
int maincsm_id;
volatile int linkslist_menu_id;


int b_rename = 0;
int b_edit_from_linkslist = 0;

int current;

extern int Labels;


////////////////////////////////////////////////////////////////////////////////
// Меню "Options" //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void AddLink(GUI *data)
{
  b_rename = 0;
  CreateDialogForNewOrRenameLink(data, -1, "");
  GeneralFuncF1(1); // Назад
}

void RenameLink(GUI *data)
{
  b_rename = 1;
  extern TLabelData *TLabels;
  if (TLabels)
  {
    TLabelData *i = TLabels;
    int step =1;
    if (current != 0)
    {
      while(step != (current+1)/*i->next*/)
      {
        step++;
        if(i->next)
        {
          i = i->next;
        }
      }
    }
    char *tempstring;
    tempstring = malloc(strlen(i->LinkName) + 1);
    sprintf(tempstring, i->LinkName);
    del_ext(tempstring);
    CreateDialogForNewOrRenameLink(data, -1, tempstring);
    GeneralFuncF1(1); // Назад
    mfree(tempstring);
  }
}

void EditLink(GUI *data)
{
  extern TLabelData *TLabels;
  if (TLabels)
  {
    TLabelData *i = TLabels;
    int step =1;
    if (current != 0)
    {
      while(step != (current+1)/*i->next*/)
      {
        step++;
        if(i->next)
        {
          i = i->next;
        }
      }
    }
    OpenBcfgFromMenu(i->LinkName);
    if(!b_edit_from_linkslist)
    {
      GeneralFuncF1(1); // Назад
    }
  }
}

void RemoveLink(GUI *data)
{
  extern TLabelData *TLabels;
  if (TLabels)
  {
    TLabelData *i = TLabels;
    int step =1;
    if (current != 0)
    {
      while(step != (current+1)/*i->next*/)
      {
        step++;
        if(i->next)
        {
          i = i->next;
        }
      }
    }
    DeleteBcfg(i->LinkName);
    GeneralFuncF1(1); // Назад
  }
}

int options_softkeys[]={0,1,2};
SOFTKEY_DESC options_menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB options_menu_skt=
{
  options_menu_sk,0
};

HEADER_DESC options_menuhdr={0,0,0,0,NULL,(int)"Options",LGP_NULL};

MENUITEM_DESC options_menu_ITEMS[5]=
{
  {NULL,(int)"Add",                       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Rename",               LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Edit",           LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL,(int)"Delete", LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENUPROCS_DESC options_menu_HNDLS[7]=
{
  AddLink,
  RenameLink,
  EditLink,
  RemoveLink,
};

const MENU_DESC options_menu_STRUCT=
{
  0,NULL,NULL,NULL,
  options_softkeys,
  &options_menu_skt,
  0x200+0x10,
  NULL,
  options_menu_ITEMS,   //Items
  options_menu_HNDLS,   //Procs
  4 //n
};



////////////////////////////////////////////////////////////////////////////////
// Меню со списком ярлычков ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


static const int menusoftkeys[] = {0,1,2};

static SOFTKEY_DESC menu_linkslist_sk[]=
{
  {0x0018, 0x0000, (int)"Options"},
  {0x0001, 0x0000, (int)"Exit"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_linkslist_skt =
{
  menu_linkslist_sk, 0
};

  extern int *S_ICONS;
  
static HEADER_DESC menu_linkslist_hdr = {0, 0, 0, 0, 0, (int)"Links Editor", LGP_NULL};

int menu_linkslist_onkey(void *data, GUI_MSG *msg)
{
switch(msg->keys)
  {
  case 0x0018:
    {
      b_edit_from_linkslist = 0;
      current = GetCurMenuItem(data);
      patch_header_small((HEADER_DESC*)(&options_menuhdr));
      CreateMenu(1,0,&options_menu_STRUCT,&options_menuhdr,0,4,0,0);
      return(-1);
    }
  case 0x0001:
    {
      CloseCSM(maincsm_id);
      return(-1);
    }
  case 0x003D:
    {
      b_edit_from_linkslist = 1;
      current = GetCurMenuItem(data);
      EditLink(NULL);
      return(-1);
    }
  }
  return(0);
}

void menu_linkslist_iconhndl(void *data, int curitem, void *unk)
{
  void *item=AllocMLMenuItem(data);
  
  WSHDR *ws2;
  WSHDR *ws4;
  
  // Находим нужный элемент списка
  extern TLabelData *TLabels;
  if (TLabels)
  {
    TLabelData *i = TLabels;
    int step =1;
    if (curitem != 0)
    {
      while(step != (curitem+1)/*i->next*/)
      {
        step++;
        if(i->next)
        {
          i = i->next;
        }
      }
    }
 
    WSHDR ws1loc, *ws1;
    unsigned short num[128];
    ws1=CreateLocalWS(&ws1loc,num,128);
    char linknamedelext[256] = "";
    strcpy(linknamedelext, i->LinkName);
    del_ext(linknamedelext);
    str_2ws(ws1, linknamedelext, 128);
    WSHDR ws3loc, *ws3;
    unsigned short num3[128];
    ws3=CreateLocalWS(&ws3loc,num3,128);
    str_2ws(ws3, i->FileName, strlen(i->FileName));
    ws2=AllocMenuWS(data,ws1->wsbody[0]);
    wstrcpy(ws2,ws1);
    ws4=AllocMenuWS(data,ws3->wsbody[0]);
    wstrcpy(ws4,ws3);
  
    SetMenuItemIconArray(data, item, S_ICONS+i->PicNumder);
#ifdef LOG
    char* temp = malloc(50);
    sprintf(temp, "item: %d, icon number: %d", curitem, i->PicNumder);
    log("EITOR_MENU", "draw menu count: ", temp);
    mfree(temp);
#endif
    SetMLMenuItemText(data, item, ws2, ws4, curitem);
  }
}

void menu_linkslist_ghook(void *data, int cmd)
{

  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static const ML_MENU_DESC menu_linkslist=
{
  8,menu_linkslist_onkey,menu_linkslist_ghook,NULL,
  menusoftkeys,
  &menu_linkslist_skt,
  0x11, //+0x400
  menu_linkslist_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0,   //n
  1 //Добавочных строк
};

////////////////////////////////////////////////////////////////////////////////
// Отдельный CSM под это дело //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void EDITOR_onCreate(CSM_RAM *data)
{
  patch_header(&menu_linkslist_hdr);
#ifdef LOG
  char *temp = malloc(5);
  sprintf(temp, sprintf_d, Labels);
  log("editor", "Create menu with items count is", temp);
  mfree(temp);
#endif
  linkslist_menu_id=CreateMultiLinesMenu(0,0,&menu_linkslist,&menu_linkslist_hdr,0,Labels);
}

void EDITOR_MenuRecount()
{
  void *mnu;
  mnu=FindGUIbyId(linkslist_menu_id,NULL);
  Menu_SetItemCountDyn(mnu,Labels);
}


extern int b_dooble;
void EDITOR_onClose(CSM_RAM *csm)
{
  if (b_dooble)
  {
    SUBPROC((void *)ElfKiller);
  }
}

int EDITOR_onMessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  } 
  if(msg->msg==MSG_RECONFIGURE_REQ)
  {
    FreeBcfgs();
    LoadBcfgs();
    EDITOR_MenuRecount();
  }
  return(1); 
}

static unsigned short EDITOR_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}EDITORCSM =
{
  {
  EDITOR_onMessage,
  EDITOR_onCreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  EDITOR_onClose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    EDITOR_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void EDITOR_SetName(void)
{
  wsprintf((WSHDR *)(&EDITORCSM.maincsm_name),"IL Editor");
}

void EDITOR_Create()
{
  LockSched();
  char dummy[sizeof(MAIN_CSM)];
  EDITOR_SetName();
  maincsm_id=CreateCSM(&EDITORCSM.maincsm,dummy,2);
  UnlockSched();
}


