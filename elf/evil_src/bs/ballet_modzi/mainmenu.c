#include "..\inc\swilib.h"
#include "rect_patcher.h"
#include "view.h"
#include "main.h"
#include "string_works.h"
#include "mainmenu.h"
#include "conf_loader.h"
#include "urlstack.h"
#include "history.h"
#include "file_works.h"
#include "lang.h"
#include "url_utils.h"

extern int view_url_mode;
extern char *view_url;
extern char *goto_url;
extern int maincsm_id;

//----------------------------------- Add bookmark -----------------------------
char curBookmarksDir[128];

int CreateBookmarksMenu(char *dir);

typedef struct
{
  void *next;
  char urlname[64];
  char fullpath[128];
}URL_STRUCT;

//------------------------------------------------------------------------------


SOFTKEY_DESC add_bookmark_sk[]=
{
  {0x0018,0x0000,(int)"Add"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB add_bookmark_skt=
{
  add_bookmark_sk,0
};


HEADER_DESC add_bookmark_hdr={0,0,0,0,NULL,(int)"Bookmark...",LGP_NULL};

static void add_bookmark_ghook(GUI *data, int cmd)
{
  SOFTKEY_DESC sk={0x0FFF,0x0000,(int)lgpData[LGP_Save]};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

static void add_bookmark_locret(void){}

static int add_bookmark_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  WSHDR *ws;
  char *name, *url, *path, *tmp;
  unsigned ul;
  int f;

  if (msg->keys==0xFFF)
  {
    ExtractEditControl(data,2,&ec);
    ws = ec.pWS;
    name = (char *)malloc(256);
    ws_2str(ws, name, 256);

    ExtractEditControl(data,4,&ec);
    ws = ec.pWS;
    tmp = url = (char *)malloc(ws->wsbody[0]+3);
    for (int i=0; i<ws->wsbody[0]; i++) *url++=char16to8(ws->wsbody[i+1]);
    *url = 0;
    url = tmp;

    path = getSymbolicPath(curBookmarksDir);
    strcat(path, name);
    strcat(path, ".url");
    unlink(path,&ul); // it will duplicate, if name changed :(
    f=fopen(path,A_WriteOnly+A_Create+A_BIN,P_READ+P_WRITE,&ul);
    if (f!=-1)
    {
      url = ToWeb(url, 0);
      fwrite(f,url,strlen(url),&ul);
      fclose(f,&ul);
    }
    mfree(url);
    mfree(name);
    return (1);
  }
  return (0);
}

static const INPUTDIA_DESC add_bookmark_desc =
{
  1,
  add_bookmark_onkey,
  add_bookmark_ghook,
  (void *)add_bookmark_locret,
  0,
  &add_bookmark_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  //  0x00000001 - ????????? ?? ??????? ????
  //  0x00000002 - ????????? ?? ??????
  //  0x00000004 - ???????? ?????????
  //  0x00000008 - UnderLine
  //  0x00000020 - ?? ?????????? ?????
  //  0x00000200 - bold
  0,
  //  0x00000002 - ReadOnly
  //  0x00000004 - ?? ????????? ??????
  //  0x40000000 - ???????? ??????? ????-??????
  0x40000000
};


int CreateAddBookmark(GUI *data)
{
  void *ma=malloc_adr();
  void *eq;
  MAIN_CSM *main_csm;
  VIEW_GUI *p;
  EDITCONTROL ec;
  char *url_start;
  int flag = 0;
  char *buf;
  
  eq=AllocEQueue(ma,mfree_adr());    // Extension
  WSHDR *ews=AllocWS(1024);

  URL_STRUCT *ustop = MenuGetUserPointer(data);

  if(data) // edit
  {
    // read url file
    int f;
    unsigned int err;
    int fsize;
    FSTATS stat;
    if (GetFileStats(ustop->fullpath,&stat,&err)!=-1)
    {
      if ((fsize=stat.size)>0)
      {
        if ((f=fopen(ustop->fullpath,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
        {
          buf=malloc(fsize+1);
          buf[fread(f,buf,fsize,&err)]=0;
          fclose(f,&err);
          flag = 1;
        }
      }
    }
  }
  
  ascii2ws(ews,lgpData[LGP_NameHeader]);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,wslen(ews));
  AddEditControlToEditQend(eq,&ec,ma);
      
  if(flag) // edit bookmark
  {
    str_2ws(ews,ustop->urlname,64);
  }
  else // add bookmark
  {
    if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
    {
      p=FindGUIbyId(main_csm->view_id,NULL);
      if (p->vd->title)
        ascii2ws(ews,p->vd->title);
      else
        ascii2ws(ews,lgpData[LGP_NewBookmark]);
    }
  }
    
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,64);
  AddEditControlToEditQend(eq,&ec,ma);   //2

  ascii2ws(ews,lgpData[LGP_LinkHeader]);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,wslen(ews));
  AddEditControlToEditQend(eq,&ec,ma);

  if(flag) // edit bookmark
  {
    ascii2ws(ews,buf);
    mfree(buf);
  }
  else // add bookmark
  {
    if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
    {
      p=FindGUIbyId(main_csm->view_id,NULL);
      if (p->vd->pageurl)
      {
        for(url_start = p->vd->pageurl; *url_start && *url_start != '/'; url_start++);
        for(; *url_start && *url_start == '/'; url_start++);
        str_2ws(ews,url_start,strlen(url_start));
      }
      else // url ?? ????????
      {
        switch(view_url_mode)
        {
        case MODE_FILE:
          str_2ws(ews,view_url,255);
          break;
        case MODE_URL:
          for(url_start = view_url; *url_start && *url_start != '/'; url_start++);
          for(; *url_start && *url_start == '/'; url_start++);
          str_2ws(ews,url_start,strlen(url_start));
          break;
        default:
          str_2ws(ews,lgpData[LGP_Absent],32);
          break;
        }
      }
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);   //2
  
  FreeWS(ews);
  patch_header(&add_bookmark_hdr);
  patch_input(&add_bookmark_desc);
  return CreateInputTextDialog(&add_bookmark_desc,&add_bookmark_hdr,eq,1,0);
}

static void do_add_bookmark(GUI *data)
{
  CreateAddBookmark(0);
  GeneralFuncF1(2);
}
//------------------------------------------------------------------------------

static void do_edit_bookmark(GUI *data)
{
  CreateAddBookmark(data);
  GeneralFuncF1(2);
}

//------------------------------------------------------------------------------

static void do_delete_bookmark(GUI *data)
{
  URL_STRUCT *ustop = MenuGetUserPointer(data);
  unsigned ul;
  if(ustop)
    if(ustop->fullpath)
      unlink(ustop->fullpath,&ul);
  GeneralFuncF1(2);
}
  
//------------------------------------------------------------------------------

void back(GUI *data)
{
  GeneralFuncF1(1);
}


#define OPTIONS_ITEMS_N 4
HEADER_DESC options_menuhdr={0,0,0,0,NULL,(int)"Options:",LGP_NULL};

MENUITEM_DESC options_menu_ITEMS[OPTIONS_ITEMS_N]=
{
  {NULL,(int)"Add",       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //0
  {NULL,(int)"Edit",      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //1
  {NULL,(int)"Delete",    LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //2
  {NULL,(int)"Back",      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //3
};

const MENUPROCS_DESC options_menu_HNDLS[OPTIONS_ITEMS_N]=
{
  do_add_bookmark,
  do_edit_bookmark,
  do_delete_bookmark,
  back,
};

int menusoftkeys[]={0,1,2};
SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Options"},
  {0x0001,0x0000,(int)"Close"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

MENU_DESC options_menu_STRUCT=
{
  0,(void *)NULL,(void*)NULL,NULL,
  menusoftkeys,
  &menu_skt,
  8,
  NULL,
  options_menu_ITEMS,   //Items
  options_menu_HNDLS,   //Procs
  OPTIONS_ITEMS_N //n
};

void create_options_menu(URL_STRUCT *ustop)
{
  int to_remove[OPTIONS_ITEMS_N+1];
  int n = 0;
  if(!ustop)
  {
    to_remove[++n]=1;
    to_remove[++n]=2;
  }
  to_remove[0]=n;
  patch_header_small((HEADER_DESC*)(&options_menuhdr));
  CreateMenu(1,0,&options_menu_STRUCT,&options_menuhdr,0,OPTIONS_ITEMS_N,ustop,to_remove);
}

// ----------------------------------------------------------------------------------

int selurl_menu_onkey(void *gui, GUI_MSG *msg) //bookmarks
{
  int l;
  URL_STRUCT *ustop=MenuGetUserPointer(gui);

  int i=GetCurMenuItem(gui);
  for (int n=0; n!=i; n++) ustop=ustop->next;
  if (ustop)
  {
    if (msg->keys==0x3D)
    {
      if (!strcmp(ustop->fullpath+(strlen(ustop->fullpath)-4),".url")) // file
      {
        if (ReadUrlFile(ustop->fullpath))
        {
          goto_url=malloc((l=strlen(view_url))+1);
          memcpy(goto_url,view_url,l+1);
          return (0xFF);
        }
        return(1);
      }
      else // dir
      {
        MAIN_CSM *main_csm;
        int bookmark_menu_id;
        if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
        {
          main_csm->sel_bmk=0;
          GeneralFuncF1(1);
          bookmark_menu_id=CreateBookmarksMenu(ustop->fullpath);
          main_csm->sel_bmk=bookmark_menu_id;
        }
      }
    }
    if(msg->keys==0x18)
    {
      create_options_menu(ustop);
      return(1);
    }
  }
  else
  {
    if(msg->keys==0x18)
    {
      create_options_menu(0);
      return(1);
    }
  }
  return (0);
}

void selurl_menu_ghook(void *gui, int cmd)
{
  URL_STRUCT *ustop=MenuGetUserPointer(gui);
  if (cmd==3)
  {
    
    while(ustop)
    {
      URL_STRUCT *us=ustop;
      ustop=ustop->next;
      mfree(us);
    }    
  }
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

int S_ICONS[2];
char *bmkpic;
char *dirpic;

void selurl_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  URL_STRUCT *ustop=user_pointer;
  WSHDR *ws;
  int len;
  for (int n=0; n!=cur_item; n++) ustop=ustop->next;
  void *item=AllocMenuItem(gui);
  if (!S_ICONS[0])
  {
    bmkpic = getSymbolicPath("$resources\\bookmark.png");
    dirpic = getSymbolicPath("$resources\\folder.png");
    S_ICONS[0] = (int)bmkpic;
    S_ICONS[1] = (int)dirpic;
  }
  if (ustop)
  {
    len=strlen(ustop->urlname);
    ws=AllocMenuWS(gui,len+4);
    //ascii2ws(ws,ustop->urlname);
    str_2ws(ws,ustop->urlname,64);
    if (!strcmp(ustop->fullpath+(strlen(ustop->fullpath)-4),".url"))
      SetMenuItemIconArray(gui,item,S_ICONS+0);
    else
      SetMenuItemIconArray(gui,item,S_ICONS+1);
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    ascii2ws(ws,lgpData[LGP_Error]);
  }
  SetMenuItemText(gui, item, ws, cur_item);
}

int selurl_softkeys[]={0,1,2};
SOFTKEY_DESC selurl_sk[]=
{
  {0x0018,0x0000,(int)"Options"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB selurl_skt=
{
  selurl_sk,0
};

HEADER_DESC selurl_HDR={0,0,0,0,NULL,(int)"Select Bookmark:",LGP_NULL};


MENU_DESC selurl_STRUCT=
{
  8,selurl_menu_onkey,selurl_menu_ghook,NULL,
  selurl_softkeys,
  &selurl_skt,
  0x11,
  selurl_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

//-----
/*
#define   MAX_SEARCH_ENGINES 32

SOFTKEY_DESC search_sk[]=
{
  {0x0018,0x0000,(int)"Search"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB search_skt=
{
  search_sk,0
};

static int search_engine_count=0;
static int selected_search_engine=0;
static char * search_engines[MAX_SEARCH_ENGINES];

static void free_search_engines()
{
  LockSched();
  char ** p=search_engines;
  for(int i=search_engine_count-1;i>=0;i--) mfree(*p++);
  search_engine_count=0;
  UnlockSched();
};

static void get_search_engines()
{
  free_search_engines();  
      
  char **sep=search_engines;
  unsigned int err;
  DIR_ENTRY de;
  char str[128];  
  
  extern char SEARCH_PATH[256];
  char * s=SEARCH_PATH;
  strcpy(str,s);
  strcat(str,"*.url");
  if (FindFirstFile(&de,str,&err))
  {
    do
    {
      if (!(de.file_attr&FA_DIRECTORY))
      {
        if(search_engine_count>=MAX_SEARCH_ENGINES) break;        
        int l=strlen(de.file_name); 
        char * s=malloc(strlen(de.file_name)+1);
        strcpy(s,de.file_name);
        s[l-4]=0;
        search_engine_count++;
        *sep++=s;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  
  if(selected_search_engine>=search_engine_count) selected_search_engine=search_engine_count-1;
};

void search_locret(void){}

int search_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  if (msg->keys==0xFFF)
  {
    if(selected_search_engine<0)return 0;

    //query
    ExtractEditControl(data,2,&ec);
    WSHDR *ws = ec.pWS;
    int ql=ws->wsbody[0];
    
    //read url file    
    int f,fsize;
    unsigned int err;
    
    char *s, *url;
    FSTATS stat;
    char url_file[256];
    
    extern char SEARCH_PATH[256];
    sprintf(url_file,"%s%s.url",SEARCH_PATH,search_engines[selected_search_engine]);
    
    if (GetFileStats(url_file,&stat,&err)==-1) goto fail;
    if ((fsize=stat.size)<=0)  goto fail;
    if ((f=fopen(url_file,A_ReadOnly+A_BIN,P_READ,&err))==-1) goto fail;    
    
    url=(char*)malloc(fsize+1);
    url[fread(f,url,fsize,&err)]=0;    
    fclose(f,&err);  
    s=url;
    while(*s>32) s++;
    *s=0;
    fsize=strlen(url);
    
    //build search url    
    goto_url=malloc(2+fsize+ql+2);    
    goto_url[0]='0';
    goto_url[1]='/';          
    
    s=strstr(url,"%s");
    if(s)
      {
      int ofs=s-url;
      memcpy(goto_url+2,url,ofs);
      s=goto_url+2+ofs;
      for (int i=0; i<ql; i++) *s++=char16to8(ws->wsbody[i+1]);
      memcpy(goto_url+2+ofs+ql,url+ofs+2,fsize-ofs-1);
      }
    else
      {
      memcpy(goto_url+2,url,fsize);  
      s=goto_url+2+fsize;
      for (int i=0; i<ql; i++) *s++=char16to8(ws->wsbody[i+1]);
      *s = 0;  
      };       
    mfree(url);
   
    goto_url = ToWeb(goto_url,0);
    
    return (0xFF);     
    
  fail:
    ShowMSG(2,(int)lgpData[LGP_Error]);
    return (0);
  }
  return (0);
}

void search_ghook(GUI *data, int cmd)
{
  SOFTKEY_DESC sk={0x0FFF,0x0000,(int)lgpData[LGP_Search]};
  
//  if (cmd==2)
//  {
    //Create
//  }
  
  if(cmd==0x03)     // onDestroy
  {
    free_search_engines();
  }  
  
  if (cmd==7)
  {
    //OnRun
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
  
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  
  if (cmd==0x0D)
  {
    //onCombo
    int cbi=EDIT_GetFocus(data);
    if(cbi==4)
      {
      WSHDR * ews=AllocWS(128);    
      selected_search_engine=EDIT_GetItemNumInFocusedComboBox(data)-1;
      if(selected_search_engine>=0&&selected_search_engine<search_engine_count)
        {
        str_2ws(ews,search_engines[selected_search_engine],128);
        EDIT_SetTextToFocused(data,ews);
        };
      FreeWS(ews);
      };
  }
}

HEADER_DESC search_hdr={0,0,0,0,NULL,(int)"Search:",0x7FFFFFFF};

INPUTDIA_DESC search_desc=
{
  1,
  search_onkey,
  search_ghook,
  (void *)search_locret,
  0,
  &search_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};


static int CreateSearchDialog()
{
  get_search_engines();

  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  WSHDR * ews=AllocWS(1024);

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  ascii2ws(ews,lgpData[LGP_TextHeader]);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"");
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ascii2ws(ews,lgpData[LGP_SearchEngine]);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);
  
  wsprintf(ews,"");
  ConstructComboBox(&ec,7,ECF_APPEND_EOL,ews,32,0,search_engine_count,selected_search_engine+1);
  AddEditControlToEditQend(eq,&ec,ma);
  
  FreeWS(ews);
  patch_header(&search_hdr);
  patch_input(&search_desc);
  return CreateInputTextDialog(&search_desc,&search_hdr,eq,1,0);  
};*/
//-----

int CreateBookmarksMenu(char *dir)
{
  strcpy(curBookmarksDir,dir);
  unsigned int err;
  DIR_ENTRY de;
  URL_STRUCT *ustop=0, *usbot=0;
  URL_STRUCT *us;
  int n_url=0;
  char path[128];
  sprintf(path,"%s*",dir);
  
  char *rootpath;
  rootpath=getSymbolicPath("$bookmarks\\");
  if (strcmp(dir,rootpath))
  {
    us=malloc(sizeof(URL_STRUCT));
    int last=strlen(dir)-1;
    for (int i=0;i<strlen(dir)-1;i++)
    {
      if (dir[i]=='\\') last=i+1;
    }
    memcpy(us->fullpath,dir,last);
    us->fullpath[last]=NULL;
    strcpy(us->urlname,"...");
    us->next=0;
    if (usbot)
    {
      usbot->next=us;
      usbot=us;
    }
    else
    {
      ustop=us;
      usbot=us;
    }
    n_url++;
  }
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      if (de.file_attr&FA_DIRECTORY) // dir
      {
        us=malloc(sizeof(URL_STRUCT));
        strcpy(us->fullpath,dir);
        strcat(us->fullpath,de.file_name);
        strcat(us->fullpath,"\\");
        strcpy(us->urlname,de.file_name);
        us->next=0;
        if (usbot)
        {
          usbot->next=us;
          usbot=us;
        }
        else
        {
          ustop=us;
          usbot=us;
        }
        n_url++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      if (!(de.file_attr&FA_DIRECTORY)&&!strcmp(de.file_name+(strlen(de.file_name)-4),".url")) // file
      {
        us=malloc(sizeof(URL_STRUCT));
        strcpy(us->fullpath,dir);
        strcat(us->fullpath,de.file_name);
        strcpy(us->urlname,de.file_name);
        us->urlname[strlen(de.file_name)-4]=0;
        us->next=0;
        if (usbot)
        {
          usbot->next=us;
          usbot=us;
        }
        else
        {
          ustop=us;
          usbot=us;
        }
        n_url++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  patch_header(&selurl_HDR);
  return CreateMenu(0,0,&selurl_STRUCT,&selurl_HDR,0,n_url,ustop,0);
}
/*
typedef enum
{
  IS_BACK,
  IS_FOLDER,
  IS_FILE
}BListType;

char * bookmarks_current_folder;

typedef struct
{
  void * next;
  BListType type;
  char * fullname;  
  char * name;  
}BList;

typedef enum
{
  EditBookmark,
  CreateBookmark,
  RenameFolder,
  CreateFolder
}EditBookmarkMode;

EditBookmarkMode edit_mode;

SOFTKEY_DESC edit_bookmark_sk[]=
{
  {0x0018,0x0000,(int)"Add"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB edit_bookmark_skt=
{
  edit_bookmark_sk,0
};

HEADER_DESC edit_bookmark_hdr={0,0,0,0,NULL,(int)"Bookmark...",LGP_NULL};

static void edit_bookmark_ghook(GUI * gui, int cmd)
{
  EDITCONTROL ec;
  SOFTKEY_DESC sk_ok={0x0FFF,0x0000,(int)lgpData[LGP_Ok]};
  SOFTKEY_DESC sk_cancel={0x0FF0,0x0000,(int)lgpData[LGP_Cancel]};
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd == TI_CMD_REDRAW)
  {
    SetSoftKey(gui, &sk_ok, SET_SOFT_KEY_N); // Устанавливаем на правый софткей текст "OK"
    ExtractEditControl(gui, EDIT_GetFocus(gui), &ec); // Извлекаем выделенный EDITCONTROL
    if (ec.pWS->wsbody[0] == 0 || EDIT_GetCursorPos(gui) == 1) // Если строка пуста или курсор в начале строки
      SetSoftKey(gui, &sk_cancel, SET_SOFT_KEY_N==0?1:0); // Ставим на левй софткей текст "Cancel"
  }
}

static void edit_bookmark_locret(void){}

char * edit_bookmark_extract_name(GUI * gui)
{
  EDITCONTROL ec;
  char * tmp_name;
  char * full_name;
  
  ExtractEditControl(gui, 2, &ec);
  if(!ec.pWS->wsbody[0]) return NULL;
  
  tmp_name = (char *)malloc(ec.maxlen);
  ws_2str(ec.pWS, tmp_name, ec.maxlen);
  full_name = (char *)malloc(strlen(bookmarks_current_folder) + strlen(tmp_name) + 12);
  strcpy(full_name, bookmarks_current_folder);
  strcat(full_name, tmp_name);
  mfree(tmp_name);
  return full_name;
}

char * edit_bookmark_extract_link(GUI * gui)
{
  EDITCONTROL ec;
  char * tmp_link;
  char * link;
  int link_len;
  
  ExtractEditControl(gui, 4, &ec);
  if(!ec.pWS->wsbody[0]) return NULL;

  tmp_link = (char *)malloc(ec.maxlen);
  ws_2utf8(ec.pWS, tmp_link, &link_len, 511);
  link = (char *)malloc(link_len + 1);
  strcpy(link, tmp_link);
  mfree(tmp_link);
  return link;
}

static int edit_bookmark_onkey(GUI * gui, GUI_MSG * msg)
{
  unsigned int io_error;
  if (msg->keys==0xFF0)
  {
    return 1;
  }
  if(msg->keys==0xFFF)
  {
    BList * bl = (BList *)EDIT_GetUserPointer(gui);
    if(edit_mode == CreateFolder || edit_mode == RenameFolder)
    {
      char * name;
      if (!(name = edit_bookmark_extract_name(gui))) goto NO_NAME;
      if (isdir(name, &io_error))
      {
        mfree(name);
        goto SAME_FOLDER;
      }
      if(edit_mode == CreateFolder)
        mkdir(name, &io_error);
      if(edit_mode == RenameFolder)
        fmove(bl->fullname, name, &io_error);
      mfree(name);
    }
    if(edit_mode == CreateBookmark || edit_mode == EditBookmark)
    {
      char * name;
      char * url;
      if (!(name = edit_bookmark_extract_name(gui))) goto NO_NAME;
      if (!(url = edit_bookmark_extract_link(gui)))
      {
        mfree(name);
        goto NO_URL;
      }
      strcat(name, ".url");
      if (edit_mode == CreateBookmark || strcmp(bl->fullname, name) != 0)
      {
        if (ballet_fexists(name))
        {
          mfree(name);
          mfree(url);
          goto SAME_FILE;
        }
      }
      if(edit_mode == EditBookmark)
        unlink(bl->fullname, &io_error);
      int hFile = fopen(name, A_WriteOnly + A_Create + A_BIN, P_WRITE, &io_error);
      //url = ToWeb(url, 0);
      char * tmp_url = URL_reencode_escapes(url);
      fwrite(hFile, tmp_url, strlen(tmp_url), &io_error);
      fclose(hFile,&io_error);
      mfree(name);
      mfree(url);
      mfree(tmp_url);
    }
    return 1;
  }
  return 0;
NO_NAME:
  MsgBoxError(1, (int)lgpData[LGP_EnterName]);
  return 0;
NO_URL:
  MsgBoxError(1, (int)lgpData[LGP_EnterURL]);
  return 0;
SAME_FOLDER:
  MsgBoxError(1, (int)lgpData[LGP_FolderExists]);
  return 0;
SAME_FILE:
  MsgBoxError(1, (int)lgpData[LGP_FileExists]);
  return 0;
}

static const INPUTDIA_DESC edit_bookmark_desc =
{
  1,
  edit_bookmark_onkey,
  edit_bookmark_ghook,
  (void *)edit_bookmark_locret,
  0,
  &edit_bookmark_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};


int show_edit_bookmark_menu(BList * bl, EditBookmarkMode mode)
{
  edit_mode = mode;
  void * ma = malloc_adr();
  void * eq = AllocEQueue(ma, mfree_adr());    // Extension
  MAIN_CSM * main_csm;
  VIEW_GUI * p;
  EDITCONTROL ec;
  const char empty_str[] = "";
  WSHDR * ws = AllocWS(1024);

  ascii2ws(ws, lgpData[LGP_NameHeader]);
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
  AddEditControlToEditQend(eq,&ec,ma);
  
  switch(edit_mode)
  {
  case EditBookmark:
  case RenameFolder:
    str_2ws(ws, bl->name, strlen(bl->name));
    break;
  case CreateBookmark:
    if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
    {
      p=FindGUIbyId(main_csm->view_id,NULL);
      if (p->vd->title)
#ifdef CHINA
        utf8_2ws(ws,p->vd->title,strlen(p->vd->title));
#else
        ascii2ws(ws, p->vd->title);
#endif
      else
        ascii2ws(ws, lgpData[LGP_NewBookmark]);
    }
    break;
  default: wsprintf(ws, empty_str);
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 64);
  AddEditControlToEditQend(eq,&ec,ma);
  
  if(edit_mode == CreateBookmark || edit_mode == EditBookmark)
  {
    ascii2ws(ws, lgpData[LGP_LinkHeader]);
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_HEADER, ECF_APPEND_EOL, ws, wstrlen(ws));
    AddEditControlToEditQend(eq,&ec,ma);
    
    if (edit_mode == CreateBookmark) // Add new bookmark
    {
      if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
      {
        p=FindGUIbyId(main_csm->view_id,NULL);
        if (p->vd->pageurl)
        {
          char * url_start;
          for(url_start = p->vd->pageurl; *url_start && *url_start != '/'; url_start++);
          for(; *url_start && *url_start == '/'; url_start++);
          utf8_2ws(ws, url_start, strlen(url_start));
        }
        else // url не загружен
        {
          switch(view_url_mode)
          {
          case MODE_FILE:
            str_2ws(ws, view_url, 255);
            break;
          case MODE_URL:
            {
              char * url_start;
              for(url_start = view_url; *url_start && *url_start != '/'; url_start++);
              for(; *url_start && *url_start == '/'; url_start++);
              utf8_2ws(ws, url_start, strlen(url_start));
            }
            break;
          default:
            ascii2ws(ws, lgpData[LGP_Absent]);
            break;
          }
        }
      }
    }
    else // Edit exists bookmark
    {
      // read url file
      int hFile;
      unsigned int io_error;
      FSTATS fstat;
      if (GetFileStats(bl->fullname, &fstat, &io_error) != -1)
      {
        if (fstat.size > 0)
        {
          if ((hFile = fopen(bl->fullname, A_ReadOnly + A_BIN, P_READ, &io_error)) != -1)
          {
            char * url = (char *)malloc(fstat.size + 1);
            url[fread(hFile, url, fstat.size, &io_error)] = NULL;
            fclose(hFile, &io_error);
            URL_unescape(url);
            utf8_2ws(ws, url, strlen(url));
            mfree(url);
            goto Add_link;
          }
        }
      }
      ascii2ws(ws, lgpData[LGP_Absent]);
    }
  Add_link:
    PrepareEditControl(&ec);
    ConstructEditControl(&ec, ECT_NORMAL_TEXT, ECF_APPEND_EOL, ws, 511);
    AddEditControlToEditQend(eq,&ec,ma);
  }

  FreeWS(ws);
  
  switch(edit_mode)
  {
  case EditBookmark:
  case RenameFolder:
    edit_bookmark_hdr.lgp_id=(int)lgpData[LGP_Edit];
    break;
  case CreateBookmark:
    edit_bookmark_hdr.lgp_id=(int)lgpData[LGP_NewBookmark];
    break;
  case CreateFolder:
    edit_bookmark_hdr.lgp_id=(int)lgpData[LGP_NewFolder];
    break;
  }

  patch_header(&edit_bookmark_hdr);
  patch_input(&edit_bookmark_desc);
  return CreateInputTextDialog(&edit_bookmark_desc, &edit_bookmark_hdr, eq, 1, bl);
}

//--------------------------- Bookmarks options --------------------------------

void bookmarks_options_edit(GUI * data)
{
  BList * bl = (BList *)MenuGetUserPointer(data);
  if(bl->type == IS_FILE)
    show_edit_bookmark_menu(bl, EditBookmark);
  if(bl->type == IS_FOLDER)
    show_edit_bookmark_menu(bl, RenameFolder);
  GeneralFuncF1(2);
}

void bookmarks_options_add_bookmark(GUI *data)
{
  BList * bl = (BList *)MenuGetUserPointer(data);
  show_edit_bookmark_menu(bl, CreateBookmark);
  GeneralFuncF1(2);
}

void bookmarks_options_add_folder(GUI *data)
{
  BList * bl = (BList *)MenuGetUserPointer(data);
  show_edit_bookmark_menu(bl, CreateFolder);
  GeneralFuncF1(2);
}

void bookmarks_options_delete(GUI *data)
{
  unsigned int io_error;
  BList * bl = (BList *)MenuGetUserPointer(data);
  if(bl->type == IS_FOLDER)
  {
    if(!rmdir(bl->fullname, &io_error))
      MsgBoxError(1, (int)lgpData[LGP_FolderNotEmpty]);
  }
  if(bl->type == IS_FILE)
    unlink(bl->fullname, &io_error);
  GeneralFuncF1(2);
}

#define OPTIONS_ITEMS_N 4
HEADER_DESC bookmarks_options_header={0,0,0,0,NULL,(int)"Options:",LGP_NULL};

MENUITEM_DESC bookmarks_options_items[OPTIONS_ITEMS_N]=
{
  {NULL,(int)"Edit",          LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //0
  {NULL,(int)"Add bookmark",  LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //1
  {NULL,(int)"Add folder",    LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //2
  {NULL,(int)"Delete",        LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //3
};

const MENUPROCS_DESC bookmarks_options_procs[OPTIONS_ITEMS_N]=
{
  bookmarks_options_edit,
  bookmarks_options_add_bookmark,
  bookmarks_options_add_folder,
  bookmarks_options_delete,
};

int bookmarks_options_softkeys[]={0,1,2};

SOFTKEY_DESC bookmarks_options_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB bookmarks_options_skt=
{
  bookmarks_options_sk,0
};

MENU_DESC bookmarks_options_struct=
{
  8, NULL, NULL, NULL,
  bookmarks_options_softkeys,
  &bookmarks_options_skt,
  0x10,
  NULL,
  bookmarks_options_items,   //Items
  bookmarks_options_procs,   //Procs
  OPTIONS_ITEMS_N //n
};

void show_bookmarks_options(BList * bl)
{
  int to_remove[OPTIONS_ITEMS_N + 1];
  int n = 0;
  if (bl)
  {
    switch(bl->type)
    {
    case IS_BACK:
      to_remove[++ n] = 0;
      to_remove[++ n] = 3;
      break;
    }
  }
  else
  {
    to_remove[++n] = 0;
    to_remove[++n] = 3;
  }
  
  if(! bl)
  {
    to_remove[++ n] = 1;
    to_remove[++ n] = 2;
  }
  to_remove[0] = n;
  patch_header_small((HEADER_DESC*)(&bookmarks_options_header));
  
  bookmarks_options_header.lgp_id=(int)lgpData[LGP_Options];
  
  bookmarks_options_items[0].lgp_id_small=(int)lgpData[LGP_Edit];
  bookmarks_options_items[1].lgp_id_small=(int)lgpData[LGP_NewBookmark];
  bookmarks_options_items[2].lgp_id_small=(int)lgpData[LGP_NewFolder];
  bookmarks_options_items[3].lgp_id_small=(int)lgpData[LGP_Delete];
  
  bookmarks_options_sk[0].lgp_id=(int)lgpData[LGP_Select];
  bookmarks_options_sk[1].lgp_id=(int)lgpData[LGP_Back];
  
  CreateMenu(1, 0, &bookmarks_options_struct, &bookmarks_options_header, 0, OPTIONS_ITEMS_N, bl, to_remove);
}

//------------------------------- Bookmarks menu -------------------------------

volatile BList * bl_top;

void Free_BList(void)
{
  LockSched();
  BList * bl = (BList *)bl_top;
  bl_top = NULL;
  UnlockSched();
  while(bl)
  {
    BList * bl_prev = bl;
    bl = bl->next;
    mfree(bl_prev);
  }
  if(bookmarks_current_folder)
    mfree(bookmarks_current_folder);
  bookmarks_current_folder = NULL;
}

BList * AddToFList(const char* full_name, const char *name, BListType type)
{
  int l_fname;
  BList * bn = malloc(sizeof(BList)+(l_fname=strlen(full_name))+strlen(name)+2);
  bn->fullname=(char *)bn + sizeof(BList);
  bn->name=(char *)bn+sizeof(BList)+l_fname+1;
  strcpy(bn->fullname,full_name);
  strcpy(bn->name,name);
  bn->type = type;
  bn->next = NULL;
  BList * bl=(BList *)bl_top;
  if (bl)
  {
    BList * pr =(BList *)&bl_top;
    while(strcmp_nocase(bl->name, bn->name) < 0)
    {
      pr = bl;
      bl = bl->next;
      if (!bl) break;
    }
    bn->next = bl;
    pr->next = bn;
  }
  else
  {
    bl_top = bn;
  }
  return (bn);
}

int FindFiles(char * str)
{
  DIR_ENTRY de;
  unsigned int err;
  char *rev,*s,*d;
  int i, c, n=0;
  char path[256];
  char name[128];
  
  strcpy(path,str);
  
  Free_BList();
  
  bookmarks_current_folder = (char *)malloc(strlen(str) + 1);
  strcpy(bookmarks_current_folder, str);
  
  s=path;
  d=name;
  rev=0;
  
  char * bookmarks_path = getSymbolicPath("$bookmarks\\");
  const char back[]="...";
  if(strcmp_nocase(bookmarks_current_folder, bookmarks_path) != 0)
  {
    while((c=*s++))
    {
      *d++ = c;
      if (c == '\\' && *s != '\0')
        rev=d;
    }
    *rev = 0;
    AddToFList(name, back, IS_BACK);
    n++;
  }
  mfree(bookmarks_path);
  
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
        strcpy(name, de.file_name);
        AddToFList(path,name,IS_FOLDER);
        n ++;
      }
      else
      {
        i = strlen(de.file_name);
        strncpy(name, de.file_name, i - 4);
        name[i - 4] = NULL;
        AddToFList(path, name, IS_FILE);
        n ++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  return n;
}

BList * FindBListByNS(int * i, BListType type)
{
  BList * bl = (BList *)bl_top;
  while(bl)
  {
    if (bl->type == type)
    {
      if (!(*i)) return (bl);
      (*i)--;
    }    
    bl = bl->next;
  }
  return bl;
}
  
BList * FindBListByN(int n)
{
  BList * bl;
  bl = FindBListByNS(&n, IS_BACK);   if ((!n)&&(bl)) return(bl);
  bl = FindBListByNS(&n, IS_FOLDER); if ((!n)&&(bl)) return(bl);
  bl = FindBListByNS(&n, IS_FILE);   if ((!n)&&(bl)) return(bl);
  return bl;
}

int bookmarks_menu_onkey(void *data, GUI_MSG *msg)
{
  BList * bl = FindBListByN(GetCurMenuItem(data));
  
  if (msg->keys==0x3D)
  {
    if (bl) 
    {
      if (bl->type == IS_FOLDER || bl->type == IS_BACK)
      {
        Menu_SetItemCountDyn(data, FindFiles(bl->fullname));
        SetCursorToMenuItem(data, 0);
        RefreshGUI();
      }
      else
      {
        if (ReadUrlFile(bl->fullname))
        {
          int len = strlen(view_url);
          _safe_free(goto_url);
          goto_url = URL_reencode_escapes(view_url);
          return (0xFF);
        }      
        return (1);
      }
    }
    return(-1);
  }
  if (msg->keys==0x18)
  {
    show_bookmarks_options(bl);
    return (-1);
  }
  return (0);
}

int bookmarks_menu_icons[2];

void bookmarks_menu_ghook(void *data, int cmd)
{
  if (cmd == TI_CMD_DESTROY)
  {
    for(int i = 0; i < 2; i++)
      if (bookmarks_menu_icons[i])
        mfree((void *)bookmarks_menu_icons[i]);
    Free_BList();   
  }
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
    if(bookmarks_current_folder)
    {
      Menu_SetItemCountDyn(data, FindFiles(bookmarks_current_folder));
      SetCursorToMenuItem(data, 0);
    }
  }
}

void bookmarks_menu_iconhndl(void * data, int curitem, void * user_pointer)
{
  WSHDR * ws;
  void * item = AllocMenuItem(data);
  BList * bl = FindBListByN(curitem);
  if (bl)
  {
    int len = strlen(bl->name);
    ws = AllocMenuWS(data, len + 4);
    str_2ws(ws, bl->name, len);
    if (bl->type == IS_BACK || bl->type == IS_FOLDER)
      SetMenuItemIconArray(data, item, &bookmarks_menu_icons[1]);
    else
      SetMenuItemIconArray(data, item, &bookmarks_menu_icons[0]);
  }
  else
  {
    ws = AllocMenuWS(data, 10);
    ascii2ws(ws, lgpData[LGP_Error]);
  }
  SetMenuItemText(data, item, ws, curitem);
}

int bookmarks_menu_softkeys[]={0,1,2};
SOFTKEY_DESC bookmarks_menu_sk[]=
{
  {0x0018,0x0000,(int)"Options"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB bookmarks_menu_skt=
{
  bookmarks_menu_sk,0
};

HEADER_DESC bookmarks_menu_header={0,0,0,0,NULL,NULL,LGP_NULL};

MENU_DESC bookmarks_menu_struct=
{
  8, bookmarks_menu_onkey, bookmarks_menu_ghook, NULL,
  bookmarks_menu_softkeys,
  &bookmarks_menu_skt,
  0x11,
  bookmarks_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int CreateBookmarksMenu()
{
  bookmarks_current_folder = NULL;
  char * bm_pic = getSymbolicPath("$resources\\bookmark.png");
  char * dir_pic = getSymbolicPath("$resources\\folder.png");
  bookmarks_menu_icons[0] = (int)bm_pic;
  bookmarks_menu_icons[1] = (int)dir_pic;
  
  char * bookmarks_path = getSymbolicPath("$bookmarks\\");
  patch_header(&bookmarks_menu_header);
  bookmarks_menu_sk[0].lgp_id=(int)lgpData[LGP_Options];
  bookmarks_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  bookmarks_menu_header.lgp_id=(int)lgpData[LGP_SelectBookmarkHeader];
  int gui_id = CreateMenu(0, 0, &bookmarks_menu_struct, &bookmarks_menu_header, 0, FindFiles(bookmarks_path), 0, 0);
  mfree(bookmarks_path);
  return gui_id;
}
*/
//--------------------------------- Search menu --------------------------------

#define   MAX_SEARCH_ENGINES 32

SOFTKEY_DESC search_menu_sk[]=
{
  {0x0018,0x0000,(int)"Search"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB search_menu_skt=
{
  search_menu_sk,0
};

static int search_engine_count=0;
static int selected_search_engine=0;
static char * search_engines[MAX_SEARCH_ENGINES];

static void free_search_engines()
{
  LockSched();
  char ** p=search_engines;
  for(int i=search_engine_count-1;i>=0;i--) mfree(*p++);
  search_engine_count=0;
  UnlockSched();
};

static void get_search_engines()
{
  free_search_engines();  
      
  char **sep=search_engines;
  unsigned int err;
  DIR_ENTRY de;
  char str[128];  
  
  char * search_path = getSymbolicPath("$search\\");
  char * s=search_path;
  strcpy(str,s);
  strcat(str,"*.url");
  if (FindFirstFile(&de,str,&err))
  {
    do
    {
      if (!(de.file_attr&FA_DIRECTORY))
      {
        if(search_engine_count>=MAX_SEARCH_ENGINES) break;        
        int l=strlen(de.file_name); 
        char * s=malloc(strlen(de.file_name)+1);
        strcpy(s,de.file_name);
        s[l-4]=0;
        search_engine_count++;
        *sep++=s;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de, &err);
  mfree(search_path);
  if(selected_search_engine>=search_engine_count) selected_search_engine=search_engine_count-1;
};

void search_menu_locret(void){}

#ifdef CHINA
char word[61];
#endif

int search_menu_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  if (msg->keys==0xFFF)
  {
    if(selected_search_engine<0)return 0;

    //query
    ExtractEditControl(data,2,&ec);
    WSHDR *ws = ec.pWS;
    int ql=ws->wsbody[0];
    
    //read url file    
    int f,fsize;
    unsigned int err;
    
    char *s, *url;
    FSTATS stat;
    char url_file[256];
    
    char * search_path = getSymbolicPath("$search\\");
    sprintf(url_file,"%s%s.url", search_path, search_engines[selected_search_engine]);
    mfree(search_path);
    if (GetFileStats(url_file,&stat,&err)==-1) goto fail;
    if ((fsize=stat.size)<=0)  goto fail;
    if ((f=fopen(url_file,A_ReadOnly+A_BIN,P_READ,&err))==-1) goto fail;    
    
    url=(char*)malloc(fsize+1);
    url[fread(f,url,fsize,&err)]=0;    
    fclose(f,&err);  
    s=url;
    while(*s>32) s++;
    *s=0;
    fsize=strlen(url);
    
    //build search url
    _safe_free(goto_url);
#ifdef CHINA
    int utf8conv_res_len;
    ws_2utf8(ws,word,&utf8conv_res_len,61);
    goto_url=malloc(2+fsize+strlen(word)+2); 
#else
     goto_url=malloc(2+fsize+ql+2); 
#endif
    goto_url[0]='0';
    goto_url[1]='/';          
    
    s=strstr(url, "%s");
    if(s)
    {
      int ofs=s-url;
      memcpy(goto_url+2,url,ofs);
      s=goto_url+2+ofs;
      for (int i=0; i<ql; i++) *s++=char16to8(ws->wsbody[i+1]);
      memcpy(goto_url+2+ofs+ql,url+ofs+2,fsize-ofs-1);
    }
    else
    {
      memcpy(goto_url+2,url,fsize);  
      s=goto_url+2+fsize;
      for (int i=0; i<ql; i++) *s++=char16to8(ws->wsbody[i+1]);
      *s = 0;  
    };       
    mfree(url);
#ifdef CHINA
#else
    goto_url = ToWeb(goto_url,0);
#endif
    
    return (0xFF);     
    
  fail:
    ShowMSG(2,(int)lgpData[LGP_Error]);
    return (0);
  }
  return (0);
}

void search_menu_ghook(GUI *data, int cmd)
{
  SOFTKEY_DESC sk={0x0FFF,0x0000,(int)lgpData[LGP_Search]};
  
  if(cmd == TI_CMD_DESTROY)
  {
    free_search_engines();
  }
  if (cmd == TI_CMD_REDRAW)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd == TI_CMD_COMBOBOX_FOCUS)
  {
    int cbi=EDIT_GetFocus(data);
    if(cbi==4)
    {
      WSHDR * ews=AllocWS(128);    
      selected_search_engine=EDIT_GetItemNumInFocusedComboBox(data)-1;
      if(selected_search_engine>=0&&selected_search_engine<search_engine_count)
      {
        str_2ws(ews,search_engines[selected_search_engine],128);
        EDIT_SetTextToFocused(data,ews);
      };
      FreeWS(ews);
    };
  }
}

HEADER_DESC search_menu_header={0,0,0,0,NULL,(int)"Search:",0x7FFFFFFF};

INPUTDIA_DESC search_menu_struct=
{
  1,
  search_menu_onkey,
  search_menu_ghook,
  (void *)search_menu_locret,
  0,
  &search_menu_skt,
  {0,0,0,0},
  FONT_SMALL,
  100,
  101,
  0,
  0,
  0x40000000
};


static int CreateSearchDialog()
{
  get_search_engines();

  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  WSHDR * ews=AllocWS(1024);

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  ascii2ws(ews,lgpData[LGP_TextHeader]);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);

  wsprintf(ews,"");
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);
  
  ascii2ws(ews,lgpData[LGP_SearchEngine]);
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);
  
  wsprintf(ews,"");
  ConstructComboBox(&ec,7,ECF_APPEND_EOL,ews,32,0,search_engine_count,selected_search_engine+1);
  AddEditControlToEditQend(eq,&ec,ma);
  
  FreeWS(ews);
  patch_header(&search_menu_header);
  patch_input(&search_menu_struct);
  search_menu_sk[0].lgp_id=(int)lgpData[LGP_Search];
  search_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  search_menu_header.lgp_id=(int)lgpData[LGP_SearchHeader];
  return CreateInputTextDialog(&search_menu_struct, &search_menu_header, eq, 1, 0);  
};

//------------------------------- History menu ---------------------------------

int history_menu_onkey(void *gui, GUI_MSG *msg) //history
{
  char **history = MenuGetUserPointer(gui);

  int i = GetCurMenuItem(gui);
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    if (history[i])
    {
      _safe_free(goto_url);
      goto_url=malloc(strlen(history[i])+3);
      goto_url[0] = '0'; goto_url[1] = '/';      
      strcpy(goto_url+2,history[i]);
      return (0xFF);
    }
    return(1);
  }
  return (0);
}

void history_menu_ghook(void *gui, int cmd)
{
  extern const int HISTORY_DEPTH;
  int i;
  char **history = MenuGetUserPointer(gui);
  if (cmd == TI_CMD_DESTROY)
  {
    for(i = 0; i < HISTORY_DEPTH; i++)
      if(history[i])
        mfree(history[i]);
    mfree(history);
  }
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}

void history_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  char **history=user_pointer;
  int len;
  WSHDR *ws;
  void *item=AllocMenuItem(gui);

  if (history[cur_item])
  {
    len=strlen(history[cur_item]);
    ws=AllocMenuWS(gui,len+4);
    str_2ws(ws,history[cur_item],64);
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    ascii2ws(ws,lgpData[LGP_Error]);
  }
  SetMenuItemText(gui, item, ws, cur_item);
}

int history_menu_softkeys[]={0,1,2};
SOFTKEY_DESC history_menu_sk[]=
{
  {0x0018,0x0000,(int)"Go"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB history_menu_skt=
{
  history_menu_sk,0
};

HEADER_DESC history_menu_header={0,0,0,0,NULL,(int)"History:",LGP_NULL};

MENU_DESC history_menu_struct=
{
  8, history_menu_onkey, history_menu_ghook, NULL,
  history_menu_softkeys,
  &history_menu_skt,
  0x10,
  history_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int CreateHistoryMenu()
{
  int depth;
  char **history;
  history = GetHistory(&depth);
  if (!depth) return 0;
  patch_header(&history_menu_header);
  history_menu_sk[0].lgp_id=(int)lgpData[LGP_Go];
  history_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  history_menu_header.lgp_id=(int)lgpData[LGP_HistoryHeader];
  return CreateMenu(0, 0, &history_menu_struct, &history_menu_header, 0, depth, history, 0);
}

//--------------------------------- Url input ----------------------------------

SOFTKEY_DESC input_url_sk[]=
{
  {0x0018,0x0000, NULL},
  {0x0001,0x0000, NULL},
  {0x003D,0x0000, (int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB input_url_skt=
{
  input_url_sk,0
};


HEADER_DESC input_url_header={0,0,0,0,NULL,NULL,LGP_NULL};

static void input_url_ghook(GUI *data, int cmd)
{
  SOFTKEY_DESC sk={0x0FFF,0x0000,(int)lgpData[LGP_Go]};
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_REDRAW)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

static void input_url_locret(void){}

static int input_url_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF || msg->keys == 0x18)
  {
    EDITCONTROL ec;
    ExtractEditControl(data,1,&ec);
    _safe_free(goto_url);
    char * s = goto_url = (char *)malloc(ec.pWS->wsbody[0]+3);
    *s++='0';
    *s++='/';
    for (int i=0; i<ec.pWS->wsbody[0]; i++) *s++=char16to8(ec.pWS->wsbody[i+1]);
    *s = 0;
#ifdef CHINA
#esle
    goto_url = ToWeb(goto_url,0);
#endif
    return 0xFF;
  }
  return (0);
}

static const INPUTDIA_DESC input_url_desc =
{
  1,
  input_url_onkey,
  input_url_ghook,
  (void *)input_url_locret,
  0,
  &input_url_skt,
  {0,0,0,0},
  FONT_SMALL,
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


int CreateInputUrl()
{
  void *ma=malloc_adr();
  void *eq;
  char *url_start;
  EDITCONTROL ec;
  
  eq=AllocEQueue(ma,mfree_adr());    // Extension
  WSHDR *ews=AllocWS(1024);

  MAIN_CSM *main_csm;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    VIEW_GUI *p=FindGUIbyId(main_csm->view_id,NULL);
    if (p->vd->pageurl)
    {
      for(url_start = p->vd->pageurl; *url_start && *url_start != '/'; url_start++);
      for(; *url_start && *url_start == '/'; url_start++);
    }
    else
    {
      switch(view_url_mode)
      {
      case MODE_FILE:
        url_start=view_url;
        URL_unescape(url_start);
        break;
      case MODE_URL:
        for(url_start = view_url; *url_start && *url_start != '/'; url_start++);
        for(; *url_start && *url_start == '/'; url_start++);
        URL_unescape(url_start);
        break;
      default:
        url_start=lgpData[LGP_Absent]; // HACK, symbols will be taken from the bottom table part
        break;
      }
    }
  }
  utf8_2ws(ews, url_start, 1024);
  
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT, ECF_APPEND_EOL, ews, 1024);
  AddEditControlToEditQend(eq,&ec,ma); //2

  FreeWS(ews);
  patch_header(&input_url_header);
  patch_input(&input_url_desc);
  input_url_sk[0].lgp_id=(int)lgpData[LGP_Go];
  input_url_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  input_url_header.lgp_id=(int)lgpData[LGP_AddressHeader];
  return CreateInputTextDialog(&input_url_desc, &input_url_header, eq,1,0);
}

//--------------------------------- Main menu ----------------------------------

static void main_menu_goto_url(GUI *gui)
{
  MAIN_CSM *main_csm;
  int goto_url_id;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    goto_url_id=CreateInputUrl();
    main_csm->goto_url=goto_url_id;
  } 
  GeneralFuncF1(1);  
}

static void main_menu_goto_bookmarks(GUI *gui)
{
   MAIN_CSM *main_csm;
  int bookmark_menu_id;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    char *path;
    path = getSymbolicPath("$bookmarks\\");
    bookmark_menu_id=CreateBookmarksMenu(path);
    main_csm->sel_bmk=bookmark_menu_id;
  } 
  GeneralFuncF1(1);
}


static void main_menu_search(GUI *gui)
{
  MAIN_CSM *main_csm;
  int search_id;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    search_id=CreateSearchDialog();
    main_csm->goto_url=search_id;
  } 
  GeneralFuncF1(1);
}


static void main_menu_goto_history(GUI *gui)
{
  MAIN_CSM *main_csm;
  int history_menu_id;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    history_menu_id=CreateHistoryMenu();
    main_csm->sel_bmk=history_menu_id;
  } 
  GeneralFuncF1(1);
}

static void main_menu_options(GUI *gui)
{
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

static void main_menu_quit(GUI *gui)
{
  MAIN_CSM *main_csm;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    FreePageStack();
    _safe_free(goto_url);
    GeneralFunc_flag1(main_csm->view_id,0xFF);
    GeneralFuncF1(1);
  }
  else
  {
    GeneralFuncF1(1);
  }
}
/*
static const int main_menu_softkeys[]={0,1,2};

SOFTKEY_DESC main_menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB main_menu_skt=
{
  main_menu_sk,0
};

#define MAIN_MENU_ITEMS_N 6
HEADER_DESC main_menu_header={0,0,0,0,NULL,(int)"Menu:",LGP_NULL};

MENUITEM_DESC main_menu_items[MAIN_MENU_ITEMS_N]=
{
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //0
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //1
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //2
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //3
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //3
  {NULL, NULL, LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}  //4
};

static const MENUPROCS_DESC main_menu_procs[MAIN_MENU_ITEMS_N]=
{
  main_menu_goto_url,
  main_menu_goto_bookmarks,
  main_menu_goto_history,
  main_menu_options,
  main_menu_search,
  main_menu_quit
};

static void main_menu_ghook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}

static const MENU_DESC main_menu_struct=
{
  8, NULL, main_menu_ghook, NULL,
  main_menu_softkeys,
  &main_menu_skt,
  0x10,//MENU_FLAG,
  NULL,
  main_menu_items,//menuitems,
  main_menu_procs,//menuprocs,
  MAIN_MENU_ITEMS_N
};

int CreateMainMenu(VIEWDATA *vd)
{
  MAIN_CSM * main_csm;
  int main_menu_id;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    patch_header(&main_menu_header);
    main_menu_sk[0].lgp_id=(int)lgpData[LGP_Select];
    main_menu_sk[1].lgp_id=(int)lgpData[LGP_Back];
    main_menu_header.lgp_id=(int)lgpData[LGP_Menu];
    main_menu_items[0].lgp_id_small=(int)lgpData[LGP_GoTo];
    main_menu_items[1].lgp_id_small=(int)lgpData[LGP_Bookmarks];
    main_menu_items[2].lgp_id_small=(int)lgpData[LGP_History];
    main_menu_items[3].lgp_id_small=(int)lgpData[LGP_Settings];
    main_menu_items[4].lgp_id_small=(int)lgpData[LGP_Search];
    main_menu_items[5].lgp_id_small=(int)lgpData[LGP_Exit];
  
    main_menu_id=CreateMenu(0, 0, &main_menu_struct, &main_menu_header, 0, MAIN_MENU_ITEMS_N, vd, 0);
    main_csm->main_menu_id=main_menu_id;
  }
  return main_menu_id;
}
*/

typedef struct
{
  GUI gui;
  VIEWDATA *vd;
  WSHDR *ws;
}SMILE_GUI;

int pos;
extern char menu_img2[];
extern char menu_img[];
#ifdef NEWSGOLD
int font=11;
#else
int font=7;
#endif

extern const char colorz[4];

void draw_data()
{
  int scr_w=ScreenW()-1;
  int scr_h=ScreenH()-1;
/*  DrawRectangle(0,YDISP,scr_w,scr_h,0,
                GetPaletteAdrByColorIndex(1),
                GetPaletteAdrByColorIndex(1));*/
#ifdef ELKA
  DisableIconBar(1);
  WSHDR *ws=AllocWS(128);
//  DrawRectangle(0, 180, 100, 300, 0, GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  sprintf(menu_img2, "%s\\menu_back.png", menu_img);
  DrawImg(0,180,(int)menu_img2);
  sprintf(menu_img2, "%s\\cursor_menu.png", menu_img);
  DrawImg(0,160+(pos*20),(int)menu_img2);
//  DrawRectangle(0, 160+(pos*20), 100, 180+(pos*20), 0, GetPaletteAdrByColorIndex(3),GetPaletteAdrByColorIndex(3));
  
  ascii2ws(ws, lgpData[LGP_GoTo]);
  DrawString(ws, 2,181,Get_WS_width(ws,9)+3, 181+GetFontYSIZE(9), 9, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Bookmarks]);
  DrawString(ws, 2,201,Get_WS_width(ws,9)+3, 201+GetFontYSIZE(9), 9, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Search]);
  DrawString(ws, 2,221,Get_WS_width(ws,9)+3, 221+GetFontYSIZE(9), 9, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_History]);
  DrawString(ws, 2,241,Get_WS_width(ws,9)+3, 241+GetFontYSIZE(9), 9, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Settings]);
  DrawString(ws, 2,261,Get_WS_width(ws,9)+3, 261+GetFontYSIZE(9), 9, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Exit]);
  DrawString(ws, 2,281,Get_WS_width(ws,9)+3, 281+GetFontYSIZE(9), 9, 0, colorz,GetPaletteAdrByColorIndex(23));
//  DrawRectangle(0, 300, 240, 320, 0, GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
//  DrawRectangle(0, 301, 240, 320, 0, GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
  sprintf(menu_img2, "%s\\lower_menu.png", menu_img);
  DrawImg(0,300,(int)menu_img2);
  ascii2ws(ws, lgpData[LGP_Menu]);
  DrawString(ws, 2,301,Get_WS_width(ws,9)+3, 301+GetFontYSIZE(9), 9, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Back]);
  DrawString(ws, 238-Get_WS_width(ws,9),301,240, 301+GetFontYSIZE(9), 9, 0, colorz,GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
#else
#ifdef C65
  WSHDR *ws=AllocWS(128);
  sprintf(menu_img2, "%s\\menu_back.png", menu_img);
  DrawImg(0,44,(int)menu_img2);
  sprintf(menu_img2, "%s\\cursor_menu.png", menu_img);
  DrawImg(0,32+(pos*12),(int)menu_img2);
  ascii2ws(ws, lgpData[LGP_GoTo]);
  DrawString(ws, 2,45,Get_WS_width(ws,font)+3, 45+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Bookmarks]);
  DrawString(ws, 2,57,Get_WS_width(ws,font)+3, 57+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Search]);
  DrawString(ws, 2,69,Get_WS_width(ws,font)+3, 69+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_History]);
  DrawString(ws, 2,81,Get_WS_width(ws,font)+3, 81+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Settings]);
  DrawString(ws, 2,93,Get_WS_width(ws,font)+3, 93+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Exit]);
  DrawString(ws, 2,105,Get_WS_width(ws,font)+3, 105+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  sprintf(menu_img2, "%s\\lower_menu.png", menu_img);
  DrawImg(0,117,(int)menu_img2);
  ascii2ws(ws, lgpData[LGP_Menu]);
  DrawString(ws, 2,119,Get_WS_width(ws,font)+3, 119+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  ascii2ws(ws, lgpData[LGP_Back]);
  DrawString(ws, 130-Get_WS_width(ws,font),119,132, 119+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
#else
  WSHDR *ws=AllocWS(128);
  sprintf(menu_img2, "%s\\menu_back.png", menu_img);
  DrawImg(0,91,(int)menu_img2);
  sprintf(menu_img2, "%s\\cursor_menu.png", menu_img);
  DrawImg(0,78+(pos*12),(int)menu_img2);
#ifdef EVILFOX
  wsprintf(ws, lgpData[LGP_GoTo]);
#else
  ascii2ws(ws, lgpData[LGP_GoTo]);
#endif
  DrawString(ws, 2,91,Get_WS_width(ws,font)+3, 91+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX
  wsprintf(ws, lgpData[LGP_Bookmarks]);
#else
  ascii2ws(ws, lgpData[LGP_Bookmarks]);
#endif
  DrawString(ws, 2,103,Get_WS_width(ws,font)+3, 103+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX
  wsprintf(ws, lgpData[LGP_Search]);
#else
  ascii2ws(ws, lgpData[LGP_Search]);
#endif
  DrawString(ws, 2,115,Get_WS_width(ws,font)+3, 115+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX
  wsprintf(ws, lgpData[LGP_History]);
#else
  ascii2ws(ws, lgpData[LGP_History]);
#endif
  DrawString(ws, 2,127,Get_WS_width(ws,font)+3, 127+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX
  wsprintf(ws, lgpData[LGP_Settings]);
#else
  ascii2ws(ws, lgpData[LGP_Settings]);
#endif
  DrawString(ws, 2,139,Get_WS_width(ws,font)+3, 139+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX
  wsprintf(ws, lgpData[LGP_Exit]);
#else
  ascii2ws(ws, lgpData[LGP_Exit]);
#endif
  DrawString(ws, 2,151,Get_WS_width(ws,font)+3, 151+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  sprintf(menu_img2, "%s\\lower_menu.png", menu_img);
  DrawImg(0,163,(int)menu_img2);
#ifdef EVILFOX
  wsprintf(ws, lgpData[LGP_Menu]);
#else
  ascii2ws(ws, lgpData[LGP_Menu]);
#endif
  DrawString(ws, 2,165,Get_WS_width(ws,font)+3, 165+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
#ifdef EVILFOX
  wsprintf(ws, lgpData[LGP_Back]);
#else
  ascii2ws(ws, lgpData[LGP_Back]);
#endif
  DrawString(ws, 130-Get_WS_width(ws,font),165,132, 165+GetFontYSIZE(font), font, 0, colorz,GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
#endif
#endif
}

static void method0(SMILE_GUI *data)
{
  draw_data();
}

static void method1(SMILE_GUI *data,void *(*malloc_adr)(int))
{
  data->ws=AllocWS(50);
  data->gui.state=1;
  draw_data();
}

static void method2(SMILE_GUI *data,void (*mfree_adr)(void *))
{
#ifdef ELKA
  DisableIconBar(0);
#endif
  data->gui.state=0;
  FreeWS(data->ws);
}

static void method3(SMILE_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

static void method4(SMILE_GUI *data,void (*mfree_adr)(void *))
{
#ifdef ELKA
  DisableIconBar(0);
#endif
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

static int method5(SMILE_GUI *data,GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
  int key=msg->gbsmsg->submess;
  if((m==KEY_DOWN)||(m==LONG_PRESS))
  {
    if (key==RIGHT_SOFT)
    {
        return (1);
    }
    if (key==DOWN_BUTTON)
    {
      pos++;
      if (pos==7) pos=1;
    }
    if (key==UP_BUTTON)
    {
      pos--;
      if (pos==0) pos=6;
    }
    if((key==ENTER_BUTTON || key == LEFT_SOFT) && (m==KEY_DOWN))
    {
      if(pos==1) main_menu_goto_url(NULL);
      if(pos==2) main_menu_goto_bookmarks(NULL);
      if(pos==3) main_menu_search(NULL);
      if(pos==4) main_menu_goto_history(NULL);
      if(pos==5) main_menu_options(NULL);
      if(pos==6) main_menu_quit(NULL);
    }
  }
  DirectRedrawGUI();
  return(0);
}

static int method8(void){return(0);}

static int method9(void){return(0);}

extern void kill_data(void *p, void (*func_p)(void *));
static const void * const gui_methods[11]={
  (void *)method0,  //Redraw
  (void *)method1,  //Create
  (void *)method2,  //Close
  (void *)method3,  //Focus
  (void *)method4,  //Unfocus
  (void *)method5,  //OnKey
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)method8,
  (void *)method9,
  0
};

int CreateMainMenu(VIEWDATA *vd)
{
  pos=1;
  static const RECT Canvas={0,0,0,0};
  SMILE_GUI *smile_gui=malloc(sizeof(SMILE_GUI));
  zeromem(smile_gui,sizeof(SMILE_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  smile_gui->gui.canvas=(void *)(&Canvas);
  smile_gui->gui.methods=(void *)gui_methods;
  smile_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  smile_gui->vd=vd;
  return CreateGUI(smile_gui);
}
