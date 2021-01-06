#include "include.h"
#include "inet.h"
#include "files_menu.h"
#include "gui.h"
#include "rect_patcher.h"
#include "file_works.h"
#include "langpack.h"
#include "iconpack.h"

/*******************************************************************************
 FilesList
*******************************************************************************/

FilesMenu * FilesMenu::Top = NULL;

FilesList::FilesList()
{
  fltop = NULL;
}

FilesList::~FilesList()
{
  Free_FLIST();
}

void FilesList::Free_FLIST()
{
  LockSched();
  FLIST *fl=fltop;
  fltop=0;
  UnlockSched();
  while(fl)
  {
    FLIST *fl_prev=fl;
    fl=fl->next;
    mfree(fl_prev);
  }
}

FilesList::FLIST * FilesList::AddFileToList(const char* full_name, const char *name, FILE_TYPES type)
{
  int l_fname;
  FLIST *fl;
  FLIST *fn=(FLIST *)malloc(sizeof(FLIST)+(l_fname=strlen(full_name))+strlen(name)+2);
  fn->fullname=(char *)fn+sizeof(FLIST);
  fn->name=(char *)fn+sizeof(FLIST)+l_fname+1;
  strcpy(fn->fullname, full_name);
  strcpy(fn->name, name);
  fn->type=type;
  fn->next=0;
  fl=fltop;
  if (fl)
  {
    FLIST * pr;
    pr=(FLIST *)&fltop;
    while(stricmp(fl->name, fn->name)<0)
    {
      pr=fl;
      fl=fl->next;
      if (!fl) break;
    }
    fn->next=fl;
    pr->next=fn;
  }
  else
  {
    fltop=fn;
  }
  return (fn);
}

int FilesList::FindFiles(char *str)  // SelectFile
{
  DIR_ENTRY de;
  unsigned int err;
  char *rev,*s,*d;
  int i, c, n=0;
  char path[256];
  char name[128];
  
  strcpy(path,str);
  Free_FLIST();
  s=path;
  d=name;
  rev=0;

  while((c=*s++))
  {
    *d++=c;
    if (c=='\\' && *s!='\0') rev=d;
  }
  if(rev==0)
    AddFileToList("ROOT", "...", IS_BACK);
  else
  {
    *rev=0;
    AddFileToList(name, "...", IS_BACK);
  }
  n++;
  
  i=strlen(path);
  path[i++]='*';
  path[i]='\0';
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      i=strlen(de.folder_name);
      strcpy(path, de.folder_name);
      path[i++]='\\';
      strcpy(path+i, de.file_name);
      if (de.file_attr&FA_DIRECTORY)
      {
        i=strlen(path);
        path[i++]='\\';
        path[i]=0;
        AddFileToList(path, de.file_name, IS_FOLDER);
        n++;
      }
      else
      {
        if(FilesMenu::Top->find_type != FilesMenu::FIND_FOLDERS)
        {
          AddFileToList(path, de.file_name, IS_FILE);
          n++;
        }
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return n;
}

FilesList::FLIST * FilesList::FindFileByNS(int *i, FILE_TYPES type)
{
  FLIST *fl;
  fl=fltop;
  while(fl)
  {
    if (fl->type==type)
    {
      if (!(*i)) return (fl);
      (*i)--;
    }    
    fl=fl->next;
  }
  return fl;
}
  
FilesList::FLIST * FilesList::FindFileByN(int n)
{
  FLIST *fl;
  fl=FindFileByNS(&n, IS_BACK); if ((!n)&&(fl)) return(fl);
  fl=FindFileByNS(&n, IS_FOLDER); if ((!n)&&(fl)) return(fl);
  fl=FindFileByNS(&n, IS_FILE); if ((!n)&&(fl)) return(fl);
  return fl;
}

/*******************************************************************************
 FilesMenu
*******************************************************************************/

SOFTKEY_DESC fmenu_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB fmenu_skt=
{
  fmenu_sk,0
};

void fmenu_ghook(void *data, int cmd)
{
  FilesMenu * bm = (FilesMenu *)MenuGetUserPointer(data);
  bm->gHook(data, cmd);
}

void fmenu_itemhndl(void *data, int curitem, void *unk)
{
  FilesMenu * bm = (FilesMenu *)MenuGetUserPointer(data);
  bm->ItemHandler(data, curitem, unk);
}

int fmenu_keyhook(void *data, GUI_MSG *msg)
{
  FilesMenu * bm = (FilesMenu *)MenuGetUserPointer(data);
  return bm->onKey(data, msg);
}

HEADER_DESC fmenu_hdr={0,0,0,0, NULL, NULL, LGP_NULL};

const int fmenu_softkeys[]={0,1,2};

const MENU_DESC fmenu_desc=
{
  8, fmenu_keyhook, fmenu_ghook, NULL,
  fmenu_softkeys,
  &fmenu_skt,
  0x11,
  fmenu_itemhndl,
  NULL,   //Items
  NULL,   //Procs
  NULL,   //n 
};

FilesMenu::FilesMenu()
{
  Top = this;
  list = new FilesList;
}

FilesMenu::~FilesMenu()
{
  delete list;
}

int FilesMenu::onKey(void * data, GUI_MSG *msg)
{
  FilesList::FLIST * fl = list->FindFileByN(GetCurMenuItem(data));
  if(msg->keys==0x3D)
  {
    if (fl) 
    {
      if (fl->type==FilesList::IS_FOLDER || fl->type==FilesList::IS_BACK)
      {      
        Menu_SetItemCountDyn(data, strcmp(fl->fullname,"ROOT")?list->FindFiles(fl->fullname):CreateRootMenu());
        SetCursorToMenuItem(data, 0);
        RefreshGUI();
      }
      else goto SAVE_PATH;
    }
    return(-1);
  }
  if (msg->keys==0x18)
  {
    if (fl)
    {
    SAVE_PATH:
      if(fl->type==FilesList::IS_FOLDER)
      {
        EDITCONTROL ec;
        EDIT_ExtractFocusedControl(input_data, &ec);
        WSHDR * ws=AllocWS(ec.maxlen);
        str_2ws(ws, fl->fullname, ec.maxlen);
        EDIT_SetTextToFocused(input_data, ws);
        FreeWS(ws);
        return GUI_RESULT_CLOSE;
      }
    }
  }
  return GUI_RESULT_OK;
}

void FilesMenu::gHook(void *data, int cmd)
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

void FilesMenu::ItemHandler(void *data, int curitem, void *unk)
{
  FilesList::FLIST * fl = list->FindFileByN(curitem);
  WSHDR * ws;
  void *item=AllocMenuItem(data);
  int len;
  if (fl)
  {
    len=strlen(fl->name);
    ws=AllocMenuWS(data,len+4);
    str_2ws(ws,fl->name,len);
  }
  else
  {
    ws=AllocMenuWS(data,10);
    ascii2ws(ws, LangPack::Active->data[LGP_Error]);
  }
  if(fl->type == FilesList::IS_FOLDER || fl->type == FilesList::IS_BACK)
    SetMenuItemIconArray(data, item, &IconPack::Active->data[IMG_Folder]);
  SetMenuItemText(data, item, ws, curitem);
}

int FilesMenu::CreateRootMenu()
{
  char path[32];
  unsigned int err;
  int n=0;
  list->Free_FLIST();
  for (int i=0; i!=5; i++)
  {
    path[0]=i+'0';
    path[1]=':';
    path[2]='\\';
    path[3]=0;
    if (isdir(path,&err))
    {
      list->AddFileToList(path, path, FilesList::IS_FOLDER);
      n++;
    }
  }
  return (n);
}

void FilesMenu::Show(void * inp_data, FIND_TYPES type)
{
  find_type=type;
  input_data=inp_data;
  int n=0;
  int c;
  EDITCONTROL ec;
  char path[128];
  char *s, *rev=0;
    
  ExtractEditControl(input_data, 4, &ec);
  ws_2str(ec.pWS, path, 127);
  s=path;
  while((c=*s++))
  {
    if (c=='\\' && *s!='\0') rev=s;  
  }
  if (!rev)
    n=CreateRootMenu();
  else
  {
    *rev=0;
    n = list->FindFiles(path);
  }
  fmenu_sk[0].lgp_id=(int)LangPack::Active->data[LGP_Select];
  fmenu_sk[1].lgp_id=(int)LangPack::Active->data[LGP_Back];
  patch_header(&fmenu_hdr, NULL, (int)LangPack::Active->data[LGP_SelectFolder]);
  CreateMenu(0, 0, &fmenu_desc, &fmenu_hdr, 0, n, this, NULL);
}

