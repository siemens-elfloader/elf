#include "../inc/swilib.h"
#include "main.h"
#include "string_util.h"
#include "clist_util.h"
#include "lang.h"
#include "smiles.h"
#include "../inc/pnglist.h"
#include "rect_patcher.h"
#include "select_smile.h"
//=================================== Команды ===========================================
int Templates_Menu_ID;
int Select_Menu_ID;

int Mode;
//0 - Смайлы
//1 - Команды
//2 - Шаблоны сообщений
//3 - Ресурсы контакта

char **commands_lines; //Массив указателей на строки
int tmpl_num=0;

void FreeTemplates(void)
{
  if (commands_lines) mfree(commands_lines);
  commands_lines=NULL;
}

extern const char COMMANDS_PATH[];
extern const char MESSAGES_PATH[];
extern const char SMILE_FILE[];

extern CLIST* cltop;
int LoadTemplates_new(void)
{
   int i=0;
   FreeTemplates();
   TRESOURCE *ResList = CList_FindContactByJID(CList_GetActiveContact()->full_name)->res_list;
   while(ResList)
    {
      if((ResList->name)&&(ResList->status!=6)) //бывает что имя ресурса незадано
      {
     commands_lines=realloc(commands_lines,(i+1)*sizeof(char *));
     commands_lines[i++]= convUTF8_to_ANSI_STR(ResList->name);
      }
      ResList=ResList->next;
    };
   return i;
}
int LoadTemplates(void)
{
  FSTATS stat;
  char fn[256];
  int f;
  unsigned int ul;
  int i;
  int fsize;
  char *p;
  char *pp;
  int c;
  FreeTemplates();
  
  switch (Mode)
  {
  case 0:
    strcpy(fn, SMILE_FILE);
    break;
  case 1:
    strcpy(fn, COMMANDS_PATH);
    break;
  case 2:
    strcpy(fn, MESSAGES_PATH);
    break;
  }

  if (GetFileStats(fn,&stat,&ul)==-1) return 0;
  if ((fsize=stat.size)<=0) return 0;
  if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return 0;

  p=malloc(fsize+1);
  p[fread(f,p,fsize,&ul)]=0;
  fclose(f,&ul);
  i=0;
  pp=p;
  for(;;)
  {
    c=*p;
    if (c<32)
    {
      if (pp&&(pp!=p))
      {
	commands_lines=realloc(commands_lines,(i+1)*sizeof(char *));
	commands_lines[i++]=pp;
      }
      pp=NULL;
      if (!c) break;
      *p=0;
    }
    else
    {
      if (pp==NULL) pp=p;
    }
    p++;
  }
  return i;
}


char clm_hdr_text[48];
void UpdateTemplatesMenu_header(void)
{
  switch (Mode)
  {
  case 0:
    strcpy(clm_hdr_text, LG_SELSMILE);
    break;
  case 1:
    strcpy(clm_hdr_text,LG_SELCOMMAND);
    break;
  case 2:
    strcpy(clm_hdr_text,LG_SELTEMPLATE);
    break;
  case 3:
    strcpy(clm_hdr_text,LG_CONTRESOURCES);
    break;
  }
}

HEADER_DESC tmpl_menuhdr={0,0,131,21,NULL,(int)clm_hdr_text,LGP_NULL};

int tmpl_menusoftkeys[]={0,1,2};
extern int edmessage_id;

void SetCmdToEditMessage(char *command)
{
  void *data=FindGUIbyId(edmessage_id,NULL);
  
  EDITCONTROL ec;
  ExtractEditControl(data,1,&ec);
  int pos=EDIT_GetCursorPos(data);
  WSHDR *ws_me = AllocWS(ec.pWS->wsbody[0]+strlen(command));

  switch (Mode)
  {
  case 1:
    {
      ascii2ws(ws_me,command);
      WSHDR * ws = AllocWS(wstrlen(ec.pWS) + wstrlen(ws_me));
      wstrcpy(ws, ws_me);
      wstrcat(ws, ec.pWS);
      EDIT_SetTextToEditControl(data, 1, ws);
      EDIT_SetCursorPos(data, pos + strlen(command));
      FreeWS(ws);
    }
    break;
   
  case 0:
  case 2:
    {
      int c;
      char *p=command;
      wstrcpy(ws_me,ec.pWS);
      while(c=*p++)
        wsInsertChar(ws_me,char8to16(c),pos++);
      EDIT_SetTextToEditControl(data,1,ws_me);
      EDIT_SetCursorPos(data,pos);
    }
    break;
   
  case 3:
    {
      int msglen = wstrlen(ec.pWS);
      ascii2ws(ws_me,command);
      WSHDR * ws = AllocWS(msglen + wstrlen(ws_me)+2);
      if (pos==1)
      {
        pos = pos+2;
        wsprintf(ws, "%w: %w",ws_me, ec.pWS);
      }
      else
      {
        wstrncpy(ws, ec.pWS, pos-1);
        wstrcat(ws, ws_me);
        if((pos+1)!=msglen)
        {
          WSHDR * ws2 = AllocWS(msglen-pos+1);
          wstrcpybypos(ws2, ec.pWS, pos, msglen-pos+1);
          wstrcat(ws, ws2);
          FreeWS(ws2);
        }
      }
      EDIT_SetTextToEditControl(data, 1, ws);
      EDIT_SetCursorPos(data, pos + strlen(command));
      FreeWS(ws);
    }
    break;    
  }
  FreeWS(ws_me);
  GeneralFunc_flag1(Templates_Menu_ID,1);
}

SOFTKEY_DESC tmpl_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_CANCEL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB tmpl_menu_skt=
{
  tmpl_menu_sk,3
};

void tmpl_menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR * ws = AllocMenuWS(data,strlen(commands_lines[curitem]));
  void * item = AllocMenuItem(data);
  ascii2ws(ws, commands_lines[curitem]);
  SetMenuItemText(data, item, ws, curitem);
}

void tmpl_menu_ghook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd == TI_CMD_DESTROY)
  {
    FreeTemplates();
  }
}

static int tmpl_menu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    if (tmpl_num)
      SetCmdToEditMessage(commands_lines[GetCurMenuItem(data)]);
    else
      GeneralFunc_flag1(Templates_Menu_ID, 1);
  }
  if (msg->keys==0x01)
  {
    GeneralFunc_flag1(Select_Menu_ID,1);
  }  
  return(0);
}

static const MENU_DESC tmpl_menu=
{
  8,tmpl_menu_keyhook,tmpl_menu_ghook,NULL,
  tmpl_menusoftkeys,
  &tmpl_menu_skt,
  0x10,
  tmpl_menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  0
};

HEADER_DESC tmpl_menuhdr;

void DispTemplatesMenu()
{
  UpdateTemplatesMenu_header();
  if (Mode == 3) tmpl_num = LoadTemplates_new();
  else tmpl_num = LoadTemplates();
  patch_header(&tmpl_menuhdr);
  Templates_Menu_ID = CreateMenu(0,0,&tmpl_menu,&tmpl_menuhdr,0,tmpl_num,0,0);
}

//================================== Меню выбора ===============================
#define SEL_MENU_ITEMS_NUM 5

void select_smile(GUI * data)
{
  Mode = 0;
  void * ed_gui = NULL;
  if (ed_gui = FindGUIbyId(edmessage_id, NULL))
    CreateSmileSelectGUI(ed_gui);
  GeneralFunc_flag1(Select_Menu_ID, 1);
}

void select_command(GUI * data)
{
  Mode = 1;
  DispTemplatesMenu();
  GeneralFunc_flag1(Select_Menu_ID, 1);
}

void select_template(GUI * data)
{
  Mode = 2;
  DispTemplatesMenu();
  GeneralFunc_flag1(Select_Menu_ID, 1);
}

void select_nick(GUI * data)
{
  Mode = 3;
  DispTemplatesMenu();
  GeneralFunc_flag1(Select_Menu_ID, 1);
}

void select_close(GUI * data)
{
  GeneralFunc_flag1(edmessage_id, 1);
  GeneralFunc_flag1(Select_Menu_ID, 1);
}

HEADER_DESC sel_menu_header={0,0,131,21,NULL,(int)LG_SELECT2,LGP_NULL};

int sel_menu_softkeys[]={0,1,2};

MENUITEM_DESC sel_menu_items[SEL_MENU_ITEMS_NUM]=
{
  {NULL, (int)LG_SMILE,         LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, (int)LG_COMMANDS,      LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, (int)LG_MSGTEMPLATE,   LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, (int)LG_CONTRESOURCE,  LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, (int)LG_CLOSEDLG,      LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENUPROCS_DESC sel_menu_procs[SEL_MENU_ITEMS_NUM]=
{
  select_smile,
  select_command,
  select_template,
  select_nick,
  select_close
};

SOFTKEY_DESC sel_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB sel_menu_skt=
{
  sel_menu_sk,3
};

void sel_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

MENU_DESC sel_menu_struct=
{
  8, NULL, sel_menu_ghook, NULL,
  sel_menu_softkeys,
  &sel_menu_skt,
  0x11,
  NULL,
  sel_menu_items, //menuitems,
  sel_menu_procs, //menuprocs,
  SEL_MENU_ITEMS_NUM
};

void DispSelectMenu()
{
  FSTATS fstat;
  unsigned int io_error = NULL;
  int to_remove[SEL_MENU_ITEMS_NUM + 1];
  int n = NULL;
  
  if (GetFileStats(SMILE_FILE, &fstat, &io_error) == -1 || !s_top || !SmilesImgList)
    to_remove[++n] = 0; // Не показываем пункт "Смайлы"
  if (GetFileStats(COMMANDS_PATH, &fstat, &io_error) == -1)
    to_remove[++n] = 1; // Не показываем пункт "Комманды"
  if (GetFileStats(MESSAGES_PATH, &fstat, &io_error) == -1)
    to_remove[++n] = 2; // Не показываем пункт "Шаблоны"
  
#ifndef NEWSGOLD
  to_remove[++n] = 4; // Не показываем пункт "Закрыть" для сголд
#endif
  
  to_remove[0] = n;
  if (n == SEL_MENU_ITEMS_NUM) return;
  
  patch_header(&sel_menu_header);
  Select_Menu_ID = CreateMenu(0, 0, &sel_menu_struct, &sel_menu_header, 0, SEL_MENU_ITEMS_NUM, 0, to_remove);
}

