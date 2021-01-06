#include "include.h"
#include "inet.h"
#include "bookmarks.h"
#include "gui.h"
#include "rect_patcher.h"
#include "file_works.h"
#include "langpack.h"
#include "iconpack.h"
#include "file_works.h"

/******************************************************************************
 BookmarksList
*******************************************************************************/

BookmarksList * BookmarksList::Top = NULL;

BookmarksList::BookmarksList()
{
  Top = this;
  top_list = NULL;
  current_folder = NULL;
}

BookmarksList::~BookmarksList()
{
  FreeList();
  _safe_delete(current_folder);
}

void BookmarksList::FreeList()
{
  LockSched();
  ItemsList * il = top_list;
  top_list=0;
  UnlockSched();
  while(il)
  {
    ItemsList * il_prev = il;
    il = il->next;
    mfree(il_prev);
  }
}            

BookmarksList::ItemsList * BookmarksList::AddItemToList(const char* full_name, const char *name, ItemType type)
{
  int l_fname;
  ItemsList * il;
  ItemsList * in = (ItemsList *)malloc(sizeof(ItemsList) + (l_fname = strlen(full_name)) + strlen(name) + 2);
  in->fullname = (char *)in + sizeof(ItemsList);
  in->name = (char *)in + sizeof(ItemsList) + l_fname + 1;
  strcpy(in->fullname, full_name);
  strcpy(in->name, name);
  in->type = type;
  in->next = 0;
  il = top_list;
  if (il)
  {
    ItemsList * pr;
    pr=(ItemsList *)&top_list;
    while(stricmp(il->name, in->name)<0)
    {
      pr=il;
      il=il->next;
      if (!il) break;
    }
    in->next=il;
    pr->next= in;
  }
  else
  {
    top_list = in;
  }
  return (in);
}

int BookmarksList::FindFilesInFolder(char * folder)  // SelectFile
{
  DIR_ENTRY de;
  unsigned int err;
  char *rev,*s,*d;
  int i, c, n=0;
  char path[256];
  char name[128];
  
  strcpy(path, folder);
  
  if(current_folder)
    delete current_folder;
  current_folder = new char[strlen(folder)+1];
  strcpy(current_folder, folder);
  
  FreeList();
  s=path;
  d=name;
  rev=0;

  char bookmarks_path[256];
  getSymbolicPath(bookmarks_path, "$bookmarks\\");
  if(strcmp(folder, bookmarks_path))
  {
    while((c=*s++))
    {
      *d++=c;
      if (c=='\\' && *s!='\0') rev=d;
    }
    *rev=0;
    AddItemToList(name, "...", IS_BACK);
    n++;
  }
  
  i=strlen(path);
  path[i++]='*';
  path[i]='\0';
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      i=strlen(de.folder_name);
      strcpy(path,de.folder_name);
      path[i++]='\\';
      strcpy(path+i,de.file_name);
      if (de.file_attr&FA_DIRECTORY)
      {
        i=strlen(path);
        path[i++]='\\';
        path[i]=0;
        AddItemToList(path, de.file_name, IS_FOLDER);
        n++;
      }
      else
      {
        if(Is_URL_File(de.file_name))
        {
          strcpy(name, de.file_name);
          del_ext(name);
          AddItemToList(path, name, IS_FILE);
          n++;
        }
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return n;
}

BookmarksList::ItemsList * BookmarksList::FindItemByNS(int *i, ItemType type)
{
  ItemsList *il;
  il = top_list;
  while(il)
  {
    if (il->type==type)
    {
      if (!(*i)) return (il);
      (*i)--;
    }    
    il=il->next;
  }
  return il;
}
  
BookmarksList::ItemsList * BookmarksList::FindItemByN(int n)
{
  ItemsList *il;
  il=FindItemByNS(&n, IS_BACK); if ((!n)&&(il)) return(il);
  il=FindItemByNS(&n, IS_FOLDER); if ((!n)&&(il)) return(il);
  il=FindItemByNS(&n, IS_FILE); if ((!n)&&(il)) return(il);
  return il;
}

/*******************************************************************************
 BookmarksMenu
*******************************************************************************/

SOFTKEY_DESC bookmarks_menu_sk[]=
{
  {0x0018,0x0000, NULL},
  {0x0001,0x0000, NULL},
  {0x003D,0x0000, (int)LGP_DOIT_PIC}
};

SOFTKEYSTAB bookmarks_menu_skt=
{
  bookmarks_menu_sk,0
};

void bookmarks_menu_ghook(void *data, int cmd)
{
  BookmarksMenu * bm = (BookmarksMenu *)MenuGetUserPointer(data);
  bm->gHook(data, cmd);
}

void bookmarks_menu_itemhndl(void * data, int curitem, void *unk)
{
  BookmarksMenu * bm = (BookmarksMenu *)MenuGetUserPointer(data);
  bm->ItemHandler(data, curitem, unk);
}

int bookmarks_menu_keyhook(void *data, GUI_MSG *msg)
{
  BookmarksMenu * bm = (BookmarksMenu *)MenuGetUserPointer(data);
  return bm->onKey(data, msg);
}

HEADER_DESC bookmarks_menu_hdr={0,0,0,0, NULL, NULL, LGP_NULL};

const int bookmarks_menu_softkeys[]={0,1,2};

const MENU_DESC bookmarks_menu_desc=
{
  8, bookmarks_menu_keyhook, bookmarks_menu_ghook, NULL,
  bookmarks_menu_softkeys,
  &bookmarks_menu_skt,
  0x11,
  bookmarks_menu_itemhndl,
  NULL,   //Items
  NULL,   //Procs
  NULL,   //n 
};

int BookmarksMenu::onKey(void * data, GUI_MSG * msg)
{
  URLFile * file;
  BookmarksList::ItemsList * il = list->FindItemByN(GetCurMenuItem(data));
  if(msg->keys==0x3D)
  {
    if (il) 
    {
      if (il->type==BookmarksList::IS_FOLDER || il->type==BookmarksList::IS_BACK)
      {
        int n = list->FindFilesInFolder(il->fullname); 
        Menu_SetItemCountDyn(data,n);
        SetCursorToMenuItem(data, 0);
        RefreshGUI();
      }
      else
      {
        if(il->type==BookmarksList::IS_FILE)
        {
          file = new URLFile;
          if(file->Read(il->fullname))
          {
            EDITCONTROL ec;
            EDIT_ExtractFocusedControl(input_data, &ec);
            WSHDR * ws=AllocWS(ec.maxlen);
            utf8_2ws(ws, file->url, ec.maxlen);
            EDIT_SetTextToFocused(input_data, ws);
            FreeWS(ws);
          }
          else
            MsgBoxError(1, (int)LangPack::Active->data[LGP_CantReadBookmark]);
          delete file;
          return GUI_RESULT_CLOSE;
        }
      }
    }
    return(-1);
  }
  if (msg->keys==0x18)
  {
    BookmarksOptions * bo = new BookmarksOptions;
    bo->Show(il);
  }
  return GUI_RESULT_OK;
}

void BookmarksMenu::gHook(void * data, int cmd)
{
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
    if(list->current_folder)
    {
      Menu_SetItemCountDyn(data, list->FindFilesInFolder(list->current_folder));
      SetCursorToMenuItem(data, 0);
    }
  }
  if (cmd==TI_CMD_DESTROY)
  {
    delete this;
  }
}

void BookmarksMenu::ItemHandler(void * data, int curitem, void * unk)
{
  BookmarksList::ItemsList * il = list->FindItemByN(curitem);
  WSHDR * ws;
  void * item=AllocMenuItem(data);
  int len;
  if (il)
  {
    len=strlen(il->name);
    ws=AllocMenuWS(data,len+4);
    str_2ws(ws, il->name, len);
  }
  else
  {
    ws=AllocMenuWS(data,10);
    ascii2ws(ws, LangPack::Active->data[LGP_Error]);
  }
  if(il->type == BookmarksList::IS_FOLDER || il->type == BookmarksList::IS_BACK)
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Folder]);
  else
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Bookmark]);
  SetMenuItemText(data, item, ws, curitem);
}

void BookmarksMenu::Show(void * inp_data)
{
  input_data=inp_data;
  
  char bookmarks_path[256];
  getSymbolicPath(bookmarks_path, "$bookmarks\\");
  
  bookmarks_menu_sk[0].lgp_id=(int)LangPack::Active->data[LGP_Options];
  bookmarks_menu_sk[1].lgp_id=(int)LangPack::Active->data[LGP_Back];
  
  patch_header(&bookmarks_menu_hdr, NULL, (int)LangPack::Active->data[LGP_Bookmarks]);
  CreateMenu(0, 0, &bookmarks_menu_desc, &bookmarks_menu_hdr, 0, list->FindFilesInFolder(bookmarks_path), this, NULL);
}

BookmarksMenu::BookmarksMenu()
{
  list = new BookmarksList;
}

BookmarksMenu::~BookmarksMenu()
{
  delete list;
}

/*******************************************************************************
  Опции
*******************************************************************************/

void Edit(GUI * data)
{
  BookmarksOptions * options = (BookmarksOptions *)MenuGetUserPointer(data);
  BookmarksInput * input = new BookmarksInput;
  if(options->il->type==BookmarksList::IS_FILE)
    input->Show(BookmarksInput::EditBookmark, options->il);
  if(options->il->type==BookmarksList::IS_FOLDER)
    input->Show(BookmarksInput::RenameFolder, options->il);
  GeneralFunc_flag1(options->gui_id, 1);
}

void AddBookmark(GUI *data)
{
  BookmarksOptions * options = (BookmarksOptions *)MenuGetUserPointer(data);
  BookmarksInput * input = new BookmarksInput;
  input->Show(BookmarksInput::CreateBookmark, options->il);
  GeneralFunc_flag1(options->gui_id, 1);
}

void AddFolder(GUI *data)
{
  BookmarksOptions * options = (BookmarksOptions *)MenuGetUserPointer(data);
  BookmarksInput * input = new BookmarksInput;
  input->Show(BookmarksInput::CreateFolder, options->il);
  GeneralFunc_flag1(options->gui_id, 1);
}

void Delete(GUI *data)
{
  unsigned int io_error;
  
  BookmarksOptions * options = (BookmarksOptions *)MenuGetUserPointer(data);
  if(options->il->type==BookmarksList::IS_FOLDER)
  {
    if(!rmdir(options->il->fullname, &io_error))
      MsgBoxError(1, (int)LangPack::Active->data[LGP_FolderNotEmpty]);
  }
  if(options->il->type==BookmarksList::IS_FILE)
    unlink(options->il->fullname, &io_error);
  GeneralFunc_flag1(options->gui_id, 1);
}

SOFTKEY_DESC bookmarks_options_sk[]=
{
  {0x0018,0x0000, NULL},
  {0x0001,0x0000, NULL},
  {0x003D,0x0000, (int)LGP_DOIT_PIC}
};

SOFTKEYSTAB bookmarks_options_skt=
{
  bookmarks_options_sk,0
};

#define OPTIONS_ITEMS_N 4
HEADER_DESC bookmarks_options_hdr={0,0,0,0,NULL, NULL ,LGP_NULL};

MENUITEM_DESC bookmarks_options_items[OPTIONS_ITEMS_N]=
{
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2},
};

const MENUPROCS_DESC bookmarks_options_procs[OPTIONS_ITEMS_N]=
{
  Edit,
  AddBookmark,
  AddFolder,
  Delete
};

void bookmarks_options_ghook(void *data, int cmd)
{
  BookmarksOptions * bo = (BookmarksOptions *)MenuGetUserPointer(data);
  bo->gHook(data, cmd);
}

const int bookmarks_options_softkeys[]={0,1,2};

MENU_DESC bookmarks_options_desc=
{
  8,NULL, bookmarks_options_ghook,NULL,
  bookmarks_options_softkeys,
  &bookmarks_options_skt,
  0x10,
  NULL,
  bookmarks_options_items,   //Items
  bookmarks_options_procs,   //Procs
  OPTIONS_ITEMS_N //n
};

void BookmarksOptions::gHook(void * data, int cmd)
{
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_DESTROY)
  {
    delete this;
  }
}

void BookmarksOptions::Show(BookmarksList::ItemsList * _il)
{
  
  int to_remove[OPTIONS_ITEMS_N+1];
  int n = NULL;
  
  //il = _il;
  patch_header_small(&bookmarks_options_hdr);
  
  if (il = _il)
  {
    switch(il->type)
    {
    case BookmarksList::IS_BACK:
      to_remove[++n] = 0;
      to_remove[++n] = 3;
      break;
    case BookmarksList::IS_FOLDER:
      bookmarks_options_items[0].lgp_id_small = (int)LangPack::Active->data[LGP_RenameFolder];
      bookmarks_options_items[3].lgp_id_small = (int)LangPack::Active->data[LGP_DeleteFolder];
      break;
    case BookmarksList::IS_FILE:
      bookmarks_options_items[0].lgp_id_small = (int)LangPack::Active->data[LGP_EditBookmark];
      bookmarks_options_items[3].lgp_id_small = (int)LangPack::Active->data[LGP_DeleteBookmark];
      break;
    }
  }
  else
  {
    to_remove[++n] = 0;
    to_remove[++n] = 3;
  }
  to_remove[0] = n;
  
  if (n == OPTIONS_ITEMS_N) return;
  
  bookmarks_options_items[1].lgp_id_small = (int)LangPack::Active->data[LGP_AddBookmark];
  bookmarks_options_items[2].lgp_id_small = (int)LangPack::Active->data[LGP_AddFolder];
  
  bookmarks_options_hdr.lgp_id = (int)LangPack::Active->data[LGP_Options];
  
  bookmarks_options_sk[0].lgp_id = (int)LangPack::Active->data[LGP_Select];
  bookmarks_options_sk[1].lgp_id = (int)LangPack::Active->data[LGP_Back];
  
  gui_id = CreateMenu(1, NULL, &bookmarks_options_desc, &bookmarks_options_hdr, NULL, OPTIONS_ITEMS_N, this, to_remove);
}

BookmarksOptions::BookmarksOptions()
{
  gui_id = NULL;
  il = NULL;
}

BookmarksOptions::~BookmarksOptions()
{
}

/******************************************************************************
  BookmarksInput
*******************************************************************************/

int bookmarks_input_onkey(GUI *gui, GUI_MSG *msg)
{
  BookmarksInput * bi = (BookmarksInput *)EDIT_GetUserPointer(gui);
  return bi->onKey(gui, msg);
}

void bookmarks_input_ghook(GUI *gui, int cmd)
{
  BookmarksInput * bi = (BookmarksInput *)EDIT_GetUserPointer(gui);
  bi->gHook(gui, cmd);
}

void bookmarks_input_locret(void) {};

SOFTKEY_DESC bookmarks_input_sk[]=
{
  {0x0018,0x0000,(int)"OK"},
  {0x0001,0x0000, NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB bookmarks_input_skt=
{
  bookmarks_input_sk,0
};

HEADER_DESC bookmarks_input_hdr={0,0,0,0,NULL, NULL,LGP_NULL};

INPUTDIA_DESC bookmarks_input_desc=
{
  1,
  bookmarks_input_onkey,
  bookmarks_input_ghook,
  (void *)bookmarks_input_locret,
  0,
  &bookmarks_input_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000// Поменять софт-кнопки
};

char * BookmarksInput::extract_name(GUI * gui)
{
  EDITCONTROL ec;
  char * tmp_name;
  char * full_name;
  
  ExtractEditControl(gui, name_pos, &ec);
  if(!wstrlen(ec.pWS)) return NULL;
  
  tmp_name = new char[ec.maxlen];
  ws_2str(ec.pWS, tmp_name, ec.maxlen);
  full_name = new char[strlen(BookmarksList::Top->current_folder) + strlen(tmp_name) + 12];
  strcpy(full_name, BookmarksList::Top->current_folder);
  strcat(full_name, tmp_name);
  delete tmp_name;
  return full_name;
}

char * BookmarksInput::extract_link(GUI * gui)
{
  EDITCONTROL ec;
  char * tmp_link;
  char * link;
  int link_len;
  
  ExtractEditControl(gui, url_pos, &ec);
  if(!wstrlen(ec.pWS))return NULL;

  tmp_link = new char[512];
  ws_2utf8(ec.pWS, tmp_link, &link_len, 511);
  link = new char[link_len+1];
  strcpy(link, tmp_link);
  delete tmp_link;
  return link;
}

int BookmarksInput::onKey(GUI *gui, GUI_MSG *msg)
{
  unsigned int io_error;
  if (msg->keys==0xFF0)
  {
    return GUI_RESULT_CLOSE;
  }
  if(msg->keys==0xFFF)
  {
    if(mode == CreateFolder || mode == RenameFolder)
    {
      if (name) delete name;
      if (!(name = extract_name(gui))) goto NO_NAME;
      if (isdir(name, &io_error)) goto SAME_FOLDER;
      if(mode == CreateFolder)
        mkdir(name, &io_error);
      if(mode == RenameFolder)
        fmove(il->fullname, name, &io_error);
    }
    if(mode==CreateBookmark || mode==EditBookmark)
    {
      if (name) delete name;
      if (!(name = extract_name(gui))) goto NO_NAME;
      URLFile * url_file = new URLFile;
      if (!(url_file->url = extract_link(gui))) goto NO_URL;
      strcat(name, ".url");
      if(mode == CreateBookmark)
        if (is_file_exists(name)) goto SAME_FILE;
      if(mode == EditBookmark)
        unlink(il->fullname, &io_error);
      url_file->Write(name);
      delete url_file;
    }
    return GUI_RESULT_CLOSE;
  }
  return GUI_RESULT_OK;
NO_NAME:
  MsgBoxError(1, (int)LangPack::Active->data[LGP_EnterName]);
  return GUI_RESULT_OK;
NO_URL:
  MsgBoxError(1, (int)LangPack::Active->data[LGP_EnterUrl]);
  return GUI_RESULT_OK;
SAME_FOLDER:
  MsgBoxError(1, (int)LangPack::Active->data[LGP_FolderExists]);
  return GUI_RESULT_OK;
SAME_FILE:
  MsgBoxError(1, (int)LangPack::Active->data[LGP_FileExists]);
  return GUI_RESULT_OK;
}

void BookmarksInput::gHook(GUI *gui, int cmd)
{
  EDITCONTROL ec;
  static const SOFTKEY_DESC sk_ok={0x0FFF,0x0000,(int)"OK"};
  static const SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)LangPack::Active->data[LGP_Cancel]};
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_DESTROY)
  {
    delete this;
  }
  if (cmd==TI_CMD_REDRAW)
  {
    SetSoftKey(gui, &sk_ok, SET_SOFT_KEY_N); // Устанавливаем на правый софткей текст "OK"
    ExtractEditControl(gui, EDIT_GetFocus(gui), &ec); // Извлекаем выделенный EDITCONTROL
    if (ec.pWS->wsbody[0] == 0 || EDIT_GetCursorPos(gui) == 1) // Если строка пуста или курсор в начале строки
      SetSoftKey(gui, &sk_cancel, SET_SOFT_KEY_N==0?1:0); // Ставим на левй софткей текст "Cancel"
  }
}

void BookmarksInput::Show(EDIT_MODE _mode, BookmarksList::ItemsList * _il)
{
  il = _il;
  mode = _mode;
  _safe_delete(name);
  _safe_delete(url);
  
  URLFile * urlfile = NULL;
  WSHDR *ws = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;

  eq=AllocEQueue(ma,mfree_adr());

  if(mode==EditBookmark)
  {
    urlfile = new URLFile;
    urlfile->Read(il->fullname);
  }
  ascii2ws(ws, LangPack::Active->data[LGP_Name]);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
  AddEditControlToEditQend(eq,&ec,ma);
  
  switch(mode)
  {
  case EditBookmark: str_2ws(ws, il->name, strlen(il->name)); break;
  case RenameFolder: str_2ws(ws, il->name, strlen(il->name)); break;
  default: wsprintf(ws, "");
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, 4, ECF_APPEND_EOL, ws, 64);
  name_pos = AddEditControlToEditQend(eq,&ec,ma);
  
  if(mode == CreateBookmark || mode == EditBookmark)
  {
    ascii2ws(ws, "URL:");
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
    
    utf8_2ws(ws, mode == CreateBookmark?"":urlfile->url, 511);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, 4, ECF_APPEND_EOL, ws, 511);
    url_pos = AddEditControlToEditQend(eq,&ec,ma);
  }

  FreeWS(ws);
  _safe_delete(urlfile);
  
  switch(mode)
  {
  case EditBookmark:
    patch_header(&bookmarks_input_hdr, NULL, (int)LangPack::Active->data[LGP_EditBookmark]);
    break;
  case CreateBookmark:
    patch_header(&bookmarks_input_hdr, NULL, (int)LangPack::Active->data[LGP_AddBookmark]);
    break;
  case RenameFolder:
    patch_header(&bookmarks_input_hdr, NULL, (int)LangPack::Active->data[LGP_RenameFolder]);
    break;
  case CreateFolder:
    patch_header(&bookmarks_input_hdr, NULL, (int)LangPack::Active->data[LGP_AddFolder]);
    break;
  }
  bookmarks_input_sk[1].lgp_id=(int)LangPack::Active->data[LGP_Cancel];
  
  patch_input(&bookmarks_input_desc);
  gui_id = CreateInputTextDialog(&bookmarks_input_desc,&bookmarks_input_hdr, eq, 1, this);
}

BookmarksInput::BookmarksInput()
{
  name = NULL;
  url = NULL;
}

BookmarksInput::~BookmarksInput()
{
  _safe_delete(name);
  _safe_delete(url);
}


