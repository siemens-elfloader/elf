#include "include.h"
#include "gui.h"
#include "list.h"
#include "dialog.h"
#include "iconpack.h"
#include "rect_patcher.h"

List * List::Active = NULL;

SOFTKEY_DESC list_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB list_skt=
{
  list_sk,0
};

TDaemonList * ListOptions::DaemonList = NULL;

void list_ghook(void * data, int cmd)
{
  List * list = List::Active;
  list->gHook(data, cmd);
}

void list_itemhndl(void * data, int curitem, void * unk)
{
  List * list = List::Active;
  list->ItemHandler(data, curitem, unk);
}

int list_keyhook(void * data, GUI_MSG *msg)
{
  List * list = List::Active;
  return list->onKey(data, msg);
}

HEADER_DESC list_hdr={0,0,0,0, NULL, NULL, LGP_NULL};

const int list_softkeys[]={0,1,2};

static const ML_MENU_DESC list_desc=
{
  8, list_keyhook, list_ghook, NULL,
  list_softkeys,
  &list_skt,
  0x200+0x11,
  list_itemhndl,
  NULL,   // Items
  NULL,   // Procs
  NULL,   // n
  1       // Добавочных строк  
};

int List::onKey(void * data, GUI_MSG * msg)
{
if (msg->keys==0x18)
   {
   ListOptions * opt = new ListOptions;
   opt->Show();
   }
else
if (msg->keys==0x1)
   {
   dl->Save(0); 
   //ShowMSG(2,(int)"Saved!");
   return GUI_RESULT_CLOSE;
   };

if (msg->gbsmsg->msg == KEY_DOWN)
    {
    switch(msg->gbsmsg->submess)
      {      
      case ENTER_BUTTON:
        {
          int idx=GetCurMenuItem(data);
          dl->daemons[idx].mode^=MODE_ENABLED_NEW;
          RefreshGUI();
        }
        break;
      }
    };
  return GUI_RESULT_OK;
}

void List::gHook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
    Menu_SetItemCountDyn(data, dl->count);
  }
}


void List::ItemHandler(void * data, int curitem, void * unk)
{
  WSHDR * ws1, * ws2;
  TDaemon * d=dl->daemons+curitem;  
  void * item=AllocMLMenuItem(data);
  ws1=AllocMenuWS(data, strlen(d->name) + 1);
  str_2ws(ws1, d->name, strlen(d->name));
  
  ws2=AllocMenuWS(data, 64);
  wsprintf(ws2,"%d kb",d->size/1024);  
  SetMenuItemIconArray(data, item, &IconPack::Active->mode_data[d->mode]);
  SetMLMenuItemText(data, item, ws1, ws2, curitem);
}

void List::Show()
{
  patch_header(&list_hdr, &IconPack::Active->data[IMG_About], (int)"Pandemonium");
  
  list_sk[0].lgp_id = (int)"Menu";
  list_sk[1].lgp_id = (int)"Close";
  
  gui_id = CreateMultiLinesMenu(NULL, NULL, &list_desc, &list_hdr, NULL, dl->count); 
}

List::List()
{
  Active = this;
  gui_id = NULL;
  dl=new TDaemonList();
  ListOptions::DaemonList=dl;
}

List::~List()
{
  delete dl;
}

/*******************************************************************************
  Опции
*******************************************************************************/

void list_options_update_callback(int ans)
{
if(ans==IDYES)
  RebootPhone();
else
  ShowMSG(2,(int)"Updated!");
};

void list_options_update(GUI * data)
{
    ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
    extern const int ASK_FOR_REBOOT;
    ListOptions::DaemonList->Save(1);    
    
    if(ListOptions::DaemonList->reboot_required&&ASK_FOR_REBOOT)
      MsgBoxYesNo(1,(int)"Reboot?",list_options_update_callback);
    else
      ShowMSG(2,(int)"Updated!");
    GeneralFunc_flag1(list_opt->gui_id, 1);
};

extern char *successed_config_filename;


void do_edit_config()
{
  int len = strlen(successed_config_filename);
  WSHDR * ws = AllocWS(len);
  str_2ws(ws, successed_config_filename, len);
  ExecuteFile(ws, 0, 0);
  FreeWS(ws);
};

void  list_options_reboot(GUI * data)
{
    ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
    ListOptions::DaemonList->Save(0);
    RebootPhone();
    GeneralFunc_flag1(list_opt->gui_id, 1);
};

void  list_options_edit_config(GUI * data)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  do_edit_config();  
  GeneralFunc_flag1(list_opt->gui_id, 1);
};

void  list_options_about(GUI * data)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  ShowMSG(2,(int)"PANDEMONIUM v2.0\n(c)captain_SISka,Borman,The_Zen");
  GeneralFunc_flag1(list_opt->gui_id, 1);
};
 
  
SOFTKEY_DESC list_options_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB list_options_skt=
{
  list_options_sk,0
};

#define LIST_OPTIONS_ITEMS_N 4
HEADER_DESC list_options_hdr={0,0,0,0,NULL,NULL,LGP_NULL};

MENUITEM_DESC list_options_items[LIST_OPTIONS_ITEMS_N]=
{
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, NULL, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENUPROCS_DESC list_options_procs[LIST_OPTIONS_ITEMS_N]=
{
  list_options_update,
  list_options_reboot,
  list_options_edit_config,  
  list_options_about,  
};

void list_options_ghook(void * data, int cmd)
{
  ListOptions * list_opt = (ListOptions *)MenuGetUserPointer(data);
  list_opt->gHook(data, cmd);
}

const int list_options_softkeys[]={0,1,2};

MENU_DESC list_options_desc=
{
  8, NULL, list_options_ghook,NULL,
  list_options_softkeys,
  &list_options_skt,
  0x11,
  NULL,
  list_options_items,   //Items
  list_options_procs,   //Procs
  LIST_OPTIONS_ITEMS_N //n
};

void ListOptions::gHook(void * data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd == TI_CMD_DESTROY)
  {
    delete this;
  }
}

void ListOptions::Show()
{ 
  patch_header_small(&list_options_hdr);
  
  list_options_items[0].icon = &IconPack::Active->data[IMG_Update];
  list_options_items[1].icon = &IconPack::Active->data[IMG_Reboot];
  list_options_items[2].icon = &IconPack::Active->data[IMG_Config];
  list_options_items[3].icon = &IconPack::Active->data[IMG_About];
  
  list_options_items[0].lgp_id_small = (int)"Update";
  list_options_items[1].lgp_id_small = (int)"Reboot";
  list_options_items[2].lgp_id_small = (int)"Edit config";
  list_options_items[3].lgp_id_small = (int)"About...";
  
   list_options_sk[0].lgp_id = (int)"Select";
   list_options_sk[1].lgp_id = (int)"Back";

  
   list_options_hdr.lgp_id = (int)"Options";
  
   gui_id = CreateMenu(1, 0, &list_options_desc, &list_options_hdr, 0, LIST_OPTIONS_ITEMS_N, this, NULL);
}

ListOptions::ListOptions()
{

}

ListOptions::~ListOptions()
{
}
