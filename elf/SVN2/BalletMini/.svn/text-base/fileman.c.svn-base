#include "../inc/swilib.h"
#include "string_works.h"
#include "upload.h"
#include "fileman.h"
#include "rect_patcher.h"
#include "lang.h"


typedef struct
{
  void *next;
  int is_folder;
  char *fullname;  
  char *name;  
}FLIST;

volatile FLIST *fltop;

void Free_FLIST(void)
{
  LockSched();
  FLIST *fl=(FLIST *)fltop;
  fltop=0;
  UnlockSched();
  while(fl)
  {
    FLIST *fl_prev=fl;
    fl=fl->next;
    mfree(fl_prev);
  }
}

enum TYPES {IS_BACK, IS_FOLDER, IS_FILE}; 
const char back_fl[]="..";
void *glob_data;

FLIST *AddToFListFM(const char* full_name, const char *name, int is_folder)
{
  int l_fname;
  FLIST *fl;
  FLIST *fn=malloc(sizeof(FLIST)+(l_fname=strlen(full_name))+strlen(name)+2);
  fn->fullname=(char *)fn+sizeof(FLIST);
  fn->name=(char *)fn+sizeof(FLIST)+l_fname+1;
  strcpy(fn->fullname,full_name);
  strcpy(fn->name,name);
  fn->is_folder=is_folder;
  fn->next=0;
  fl=(FLIST *)fltop;
  if (fl)
  {
    FLIST *pr;
    pr=(FLIST *)&fltop;
    while(strcmp_nocase(fl->name,fn->name)<0)
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

int FindFilesFM(char *str)
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
    if (c=='\\' && *s!='\0') 
      rev=d;
  }
  if(rev==0)
    AddToFListFM(lgpData[LGP_Root],back_fl,IS_BACK);
  else
  {
    *rev=0;
    AddToFListFM(name,back_fl,IS_BACK);
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
      strcpy(path,de.folder_name);
      path[i++]='\\';
      strcpy(path+i,de.file_name);
      if (de.file_attr&FA_DIRECTORY)
      {
        i=strlen(path);
        path[i++]='\\';
        path[i]=0;
        name[0]='\\';
        strcpy(name+1,de.file_name);
        AddToFListFM(path,name,IS_FOLDER);
        n++;
      }
      else
      {
        AddToFListFM(path,de.file_name,IS_FILE);
        n++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return n;
}

FLIST *FindFLISTtByNS(int *i, int si)
{
  FLIST *fl;
  fl=(FLIST *)fltop;
  while(fl)
  {
    if (fl->is_folder==si)
    {
      if (!(*i)) return (fl);
      (*i)--;
    }    
    fl=fl->next;
  }
  return fl;
}
  
FLIST *FindFLISTtByN(int n)
{
  FLIST *fl;
  fl=FindFLISTtByNS(&n,IS_BACK); if ((!n)&&(fl)) return(fl);
  fl=FindFLISTtByNS(&n,IS_FOLDER); if ((!n)&&(fl)) return(fl);
  fl=FindFLISTtByNS(&n,IS_FILE); if ((!n)&&(fl)) return(fl);
  return fl;
}

  

char header[128];

int CreateRootMenu()
{
  char path[32];
  unsigned int err;
  int n=0;
  Free_FLIST();
  for (int i=0; i!=5; i++)
  {
    path[0]=i+'0';
    path[1]=':';
    path[2]='\\';
    path[3]=0;
    if (isdir(path,&err))
    {
      AddToFListFM(path,path,IS_FOLDER);
      n++;
    }
  }
  strcpy(header,lgpData[LGP_Root]);
  return (n);
}

int filelist_menu_onkey(void *data, GUI_MSG *msg)
{
  FLIST *fl;
  int i, n;
  i=GetCurMenuItem(data);
  fl=FindFLISTtByN(i);
  
  func cbk_func = (func)(MenuGetUserPointer(data));
  
  if (msg->keys==0x3D)
  {
    if (fl) 
    {
      if (fl->is_folder==IS_FOLDER || fl->is_folder==IS_BACK)
      {
        int len;
        if (strcmp(fl->fullname,lgpData[LGP_Root]))
        {
          strncpy(header,fl->fullname,sizeof(header)-1);
          len=strlen(fl->fullname);
          header[len>sizeof(header)-1?sizeof(header)-1:len]=0;
          n=FindFilesFM(fl->fullname);
        }
        else
        {
          n=CreateRootMenu();
        }         
        Menu_SetItemCountDyn(data,n);
        SetCursorToMenuItem(data, 0);
        RefreshGUI();
      }
      else
      {
        cbk_func(glob_data, fl->fullname, fl->name);        
        return (1);
      }
    }
    //    GeneralFunc_F1(1);
    return(-1);
  }
  if (msg->keys==0x18)
  {
    if (fl)
    {
      if (fl->is_folder!=IS_BACK)
      {
        cbk_func(glob_data, fl->fullname, fl->name);       
        return (1);
      }      
    }   
    return (-1);
  }
  return (0);
}

void filelist_menu_ghook(void *data, int cmd)
{
  if (cmd==3)
  {
    Free_FLIST();
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

void filelist_menu_iconhndl(void *data, int curitem, void *user_pointer)
{
  FLIST *fl; 
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  int len;
  fl=FindFLISTtByN(curitem);
  if (fl)
  {
    len=strlen(fl->name);
    ws=AllocMenuWS(data,len+4);
    if (fl->is_folder==IS_BACK || fl->is_folder==IS_FOLDER)
    {
      str_2ws(ws,fl->name,len);
      wsInsertChar(ws,0x0002,1);
      wsInsertChar(ws,0xE008,1);
    }
    else
    {
      str_2ws(ws,fl->name,len);
    }
  }
  else
  {
    ws=AllocMenuWS(data,10);
    wsprintf(ws, lgpData[LGP_Error]);
  }
  SetMenuItemText(data, item, ws, curitem);
}

int fmenusoftkeys[]={0,1,2};
SOFTKEY_DESC fmenu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB fmenu_skt=
{
  fmenu_sk,0
};

HEADER_DESC filelist_HDR={0,0,0,0,NULL,(int)header,LGP_NULL};

MENU_DESC filelist_STRUCT=
{
  8,filelist_menu_onkey,filelist_menu_ghook,NULL,
  fmenusoftkeys,
  &fmenu_skt,
  0x10,
  filelist_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int open_fm(func cbk_func, void* data)
{
  char path[128] = "0:\\";
  char *s, *rev=0;
  int n, c, len;
  
  glob_data = data;
  
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
    strncpy(header,path,sizeof(header)-1);
    len=strlen(path);
    header[len>sizeof(header)-1?sizeof(header)-1:len]=0;
    n=FindFilesFM(path);
  }    
  patch_header(&filelist_HDR);
  fmenu_sk[0].lgp_id=(int)lgpData[LGP_Select];
  fmenu_sk[1].lgp_id=(int)lgpData[LGP_Close];
  return CreateMenu(0,0,&filelist_STRUCT,&filelist_HDR,0,n,(void*)cbk_func,0);
}
