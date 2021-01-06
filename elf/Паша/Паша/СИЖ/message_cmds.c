#include "../inc/swilib.h"
#include "main.h"
#include "string_util.h"
#include "clist_util.h"
#include "lang.h"
#include "smiles.h"
#include "../inc/pnglist.h"

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
    case 1:
      strcpy(fn,COMMANDS_PATH);
    break;
    case 2:
      strcpy(fn,MESSAGES_PATH);
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
extern WSHDR* ws_eddata;

void SetCmdToEditMessage(char *command)
{
  void *data=FindGUIbyId(edmessage_id,NULL);
  
  EDITCONTROL ec;
  ExtractEditControl(data,1,&ec);
  int pos=EDIT_GetCursorPos(data);
  WSHDR *ws_me = AllocWS(ec.pWS->wsbody[0]+strlen(command));
  //utf8_2ws(ws_me, command, strlen(command));

  switch (Mode)
  {
    case 1:
      ascii2ws(ws_me,command);
      wstrcpy(ws_eddata, ws_me);
      wstrcat(ws_eddata,ec.pWS);
      EDIT_SetTextToEditControl(data, 1, ws_eddata);
      EDIT_SetCursorPos(data,pos + strlen(command));
    break;
   
    case 2:
    //case 3:
      {
	int c;
	char *p=command;
	wstrcpy(ws_me,ec.pWS);

        while(c=*p++)
          {
            wsInsertChar(ws_me,char8to16(c),pos++);
          }
        EDIT_SetTextToEditControl(data,1,ws_me);
        EDIT_SetCursorPos(data,pos);
      }
    break;
   
    case 3:
      {
      ascii2ws(ws_me,command);
      if (pos==1)
      {
      pos = pos+2;
      wsprintf(ws_eddata, "%w: %w",ws_me, ec.pWS);
      }
      else wsprintf(ws_eddata, "%w%w",ec.pWS, ws_me);
      EDIT_SetTextToEditControl(data, 1, ws_eddata);
      EDIT_SetCursorPos(data,pos + strlen(command));
      }
    break;    
  } 
  FreeWS(ws_me);
  FreeTemplates();
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
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  extern const char percent_t[];
  ws=AllocMenuWS(data,strlen(commands_lines[curitem]));
  if (Mode == 3) wsprintf(ws,percent_t,commands_lines[curitem]);
  else ascii2ws(ws,commands_lines[curitem]);
  SetMenuItemText(data, item, ws, curitem);
}

void tmpl_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int tmpl_menu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    if (tmpl_num) SetCmdToEditMessage(commands_lines[GetCurMenuItem(data)]);
       else
         {
           FreeTemplates();
           GeneralFunc_flag1(Templates_Menu_ID,1);           
         }
  }
  
  if (msg->keys==0x01)
  {
    FreeTemplates();
    GeneralFunc_flag1(Select_Menu_ID,1);
  }  
  return(0);
}

static const MENU_DESC tmpl_menu=
{
  0,tmpl_menu_keyhook,tmpl_menu_ghook,NULL,
  tmpl_menusoftkeys,
  &tmpl_menu_skt,
  8,
  tmpl_menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  0
};

HEADER_DESC tmpl_menuhdr;

void DispTemplatesMenu()
{
  UpdateTemplatesMenu_header();
  if (Mode == 3) tmpl_num=LoadTemplates_new();
  else tmpl_num=LoadTemplates();
  patch_header(&tmpl_menuhdr);
  Templates_Menu_ID = CreateMenu(0,0,&tmpl_menu,&tmpl_menuhdr,0,tmpl_num,0,0);
}

//================================== Меню выбора ===============================
#ifdef NEWSGOLD
#define SEL_MANU_ITEMS_NUM 5
#else
#define SEL_MANU_ITEMS_NUM 4
#endif

HEADER_DESC sel_menuhdr={0,0,131,21,NULL,(int)LG_SELECT2,LGP_NULL};

int sel_menusoftkeys[]={0,1,2};

static const char * const sel_menutexts[SEL_MANU_ITEMS_NUM]=
{
  LG_SMILE,
  LG_COMMANDS,
  LG_MSGTEMPLATE,
  LG_CONTRESOURCE
#ifdef NEWSGOLD
  , LG_CLOSEDLG  
#endif
};

SOFTKEY_DESC sel_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB sel_menu_skt=
{
  tmpl_menu_sk,3
};

void sel_menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  extern const char percent_t[];
  ws=AllocMenuWS(data,strlen(sel_menutexts[curitem]));
  wsprintf(ws,percent_t,sel_menutexts[curitem]);
  SetMenuItemText(data, item, ws, curitem);
}

void sel_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

void AddSmile(GUI *data);
static int sel_menu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    Mode = GetCurMenuItem(data);
    #ifdef NEWSGOLD
      if (Mode==4)//Закрыть нах
      {
        GeneralFunc_flag1(edmessage_id, 1);
        return(1);
      }
    #endif    
    
    if (Mode==0) AddSmile(data); //Диалог выбора смайлегов
      else
        DispTemplatesMenu();    
      
    GeneralFunc_flag1(Select_Menu_ID,1);
  }
  return(0);
}

static const MENU_DESC sel_menu=
{
  0,sel_menu_keyhook,sel_menu_ghook,NULL,
  sel_menusoftkeys,
  &sel_menu_skt,
  0x10,
  sel_menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  SEL_MANU_ITEMS_NUM
};

void DispSelectMenu()
{
  patch_header(&sel_menuhdr);
  Select_Menu_ID = CreateMenu(0,0,&sel_menu,&sel_menuhdr,0,SEL_MANU_ITEMS_NUM,0,0);
}

//================================== Смайлеги ==================================
extern S_SMILES *s_top;
extern DYNPNGICONLIST *SmilesImgList;

void as_locret(void){}

int as_onkey(GUI *data,GUI_MSG *msg)
{
  void *edmessage=FindGUIbyId(edmessage_id,NULL);
  
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
    case GREEN_BUTTON:
    case ENTER_BUTTON:
      msg->keys=0xFFF;
    }
  }
  if (msg->keys==0xFFF)
  {
    int uni_smile;
    WSHDR *ed_ws;
    EDITCONTROL ec;
    int pos;
    pos=EDIT_GetCursorPos(data);
    EDIT_ExtractFocusedControl(data,&ec);
    uni_smile=ec.pWS->wsbody[pos];
    
    pos=EDIT_GetCursorPos(edmessage);
    ExtractEditControl(edmessage,1,&ec);
    ed_ws=AllocWS(ec.pWS->wsbody[0]+3);
    wstrcpy(ed_ws,ec.pWS);     
    
    wsInsertChar(ed_ws,' ',pos++);
    wsInsertChar(ed_ws,uni_smile,pos++);
    wsInsertChar(ed_ws,' ',pos++);
    
    EDIT_SetTextToEditControl(edmessage,1,ed_ws);
    EDIT_SetCursorPos(edmessage,pos);
    FreeWS(ed_ws);
    return (1);
  }
  return(0);
}

void as_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC ask={0x0FFF,0x0000,(int)LG_SELECT};
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }
  if (cmd == 0x0A)
  {
    pltop->dyn_pltop=SmilesImgList;
    DisableIDLETMR();
  }
  if (cmd == 7)
  {
    EDITCONTROL ec;
    int pos;
    
    SetSoftKey(data,&ask,SET_SOFT_KEY_N);
    EDIT_ExtractFocusedControl(data,&ec);
    pos=EDIT_GetCursorPos(data);
    EDIT_SetTextInvert(data,pos,1);
  }
  if (cmd==0x0C)
  {
    EDIT_SetCursorPos(data,1);
  }
}

HEADER_DESC as_hdr={0,0,NULL,NULL,NULL,(int)LG_SELSMILE,LGP_NULL};

INPUTDIA_DESC as_desc=
{
  1,
  as_onkey,
  as_ghook,
  (void *)as_locret,
  0,
  &tmpl_menu_skt,
  {0,NULL,NULL,NULL},
  4,
  100,
  101,
  2,
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

void AddSmile(GUI *data)
{
  //EDCHAT_STRUCT *ed_struct=MenuGetUserPointer(data);
  void *edmessage=FindGUIbyId(edmessage_id,NULL);
  S_SMILES *smiles,*st;
  WSHDR *ws1;
  int n;
  
  st=smiles=(S_SMILES *)&s_top;
  n=0;
  while((st=st->next)) n++;
  if (!n) return;
  ws1=AllocWS(n);
  
  st=smiles;
  while((st=st->next)) wsAppendChar(ws1,st->uni_smile);
  
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ws1,ws1->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);
  patch_header(&as_hdr);
  patch_input(&as_desc);
  CreateInputTextDialog(&as_desc,&as_hdr,eq,1,edmessage);
  FreeWS(ws1);
  GeneralFuncF1(1);
}
