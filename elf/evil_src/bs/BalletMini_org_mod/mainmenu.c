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

extern int view_url_mode;
extern char *view_url;
extern char *goto_url;
extern int maincsm_id;

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
  char *name, *url, path[256], *tmp;
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

    getSymbolicPath(path,curBookmarksDir);
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
      else // url не загружен
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
char bmkpic[128];
char dirpic[128];

void selurl_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  URL_STRUCT *ustop=user_pointer;
  WSHDR *ws;
  int len;
  for (int n=0; n!=cur_item; n++) ustop=ustop->next;
  void *item=AllocMenuItem(gui);
  if (!S_ICONS[0])
  {
    getSymbolicPath(bmkpic,"$resources\\bookmark.png");
    getSymbolicPath(dirpic,"$resources\\folder.png");
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
};
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
  
  char rootpath[128];
  getSymbolicPath(rootpath,"$bookmarks\\");
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

// ----------------------------------------------------------------------------------
int history_menu_onkey(void *gui, GUI_MSG *msg) //history
{
  char **history = MenuGetUserPointer(gui);

  int i = GetCurMenuItem(gui);
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    if (history[i])
    {
      goto_url=malloc(strlen(history[i])+3);
      goto_url[0] = '0'; goto_url[1] = '/';      
      strcpy(goto_url+2,history[i]);
      return (0xFF);
    }
    return(1);
  }

/*
  if (msg->keys==0x3D)
  {
    int i=GetCurMenuItem(gui);
    for (int n=0; n!=i; n++) ustop=ustop->next;
    if (ustop)
    {
      if (ReadUrlFile(ustop->fullpath))
      {
        goto_url=malloc((l=strlen(view_url))+1);
        memcpy(goto_url,view_url,l+1);
        return (0xFF);
      }
    }
  }
  if(msg->keys==0x18)
  {
    create_options_menu();
    return(1);
  }
*/
  return (0);
}

void history_menu_ghook(void *gui, int cmd)
{
  extern const int HISTORY_DEPTH;
  int i;
  char **history = MenuGetUserPointer(gui);
  if (cmd==3)
  {
    for(i = 0; i < HISTORY_DEPTH; i++)
      if(history[i])
        mfree(history[i]);
    mfree(history);
  }
  if (cmd==0x0A)
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

int history_softkeys[]={0,1,2};
SOFTKEY_DESC history_sk[]=
{
  {0x0018,0x0000,(int)"Go"},
  {0x0001,0x0000,(int)"Cancel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB history_skt=
{
  history_sk,0
};

HEADER_DESC history_HDR={0,0,0,0,NULL,(int)"History:",LGP_NULL};

MENU_DESC history_STRUCT=
{
  8,history_menu_onkey,history_menu_ghook,NULL,
  history_softkeys,
  &history_skt,
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
  patch_header(&history_HDR);
  return CreateMenu(0,0,&history_STRUCT,&history_HDR,0,depth,history,0);
}

//------------------------------------------------------------------------------

SOFTKEY_DESC input_menu_sk[]=
{
  {0x0018,0x0000,(int)"Go"},
  {0x0001,0x0000,(int)"Cnacel"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB input_menu_skt=
{
  input_menu_sk,0
};


HEADER_DESC input_url_hdr={0,0,0,0,NULL,(int)"Adress:",LGP_NULL};

static void input_url_ghook(GUI *data, int cmd)
{
  SOFTKEY_DESC sk={0x0FFF,0x0000,(int)lgpData[LGP_Go]};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

static void input_url_locret(void){}

static int input_url_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  WSHDR *ws;
  char *s;
  if (msg->keys==0xFFF || msg->keys == 0x18)
  {
    ExtractEditControl(data,1,&ec);
    ws = ec.pWS;
    s = goto_url = (char *)malloc(ws->wsbody[0]+3);
    *s++='0';
    *s++='/';
    for (int i=0; i<ws->wsbody[0]; i++) *s++=char16to8(ws->wsbody[i+1]);
    *s = 0;
    goto_url = ToWeb(goto_url,0);
    return (0xFF);
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
  &input_menu_skt,
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
        break;
      case MODE_URL:
        for(url_start = view_url; *url_start && *url_start != '/'; url_start++);
        for(; *url_start && *url_start == '/'; url_start++);
        break;
      default:
        url_start=lgpData[LGP_Absent]; // HACK, symbols will be taken from the bottom table part
        break;
      }
    }
  }
  ews->wsbody[0]=0;
  for(int i=0;i<strlen(url_start);i++)
    ews->wsbody[++ews->wsbody[0]]=url_start[i];

  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);   //2

  FreeWS(ews);
  patch_header(&input_url_hdr);
  patch_input(&input_url_desc);
  return CreateInputTextDialog(&input_url_desc,&input_url_hdr,eq,1,0);
}

//------------------------------------------------------------------------------

static void mm_goto_url(GUI *gui)
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

static void mm_goto_bookmarks(GUI *gui)
{
  MAIN_CSM *main_csm;
  int bookmark_menu_id;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    char path[128];
    getSymbolicPath(path,"$bookmarks\\");
    bookmark_menu_id=CreateBookmarksMenu(path);
    main_csm->sel_bmk=bookmark_menu_id;
  } 
  GeneralFuncF1(1);
}


static void mm_search(GUI *gui)
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


static void mm_goto_history(GUI *gui)
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

static void mm_options(GUI *gui)
{
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
}

static void mm_quit(GUI *gui)
{
  MAIN_CSM *main_csm;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    FreePageStack();
    goto_url = 0;
    GeneralFunc_flag1(main_csm->view_id,0xFF);
//    GeneralFunc_flag1(1,main_csm->view_id);
    GeneralFuncF1(1);
  }
  else
  {
    GeneralFuncF1(1);
  }
}

static const int mmenusoftkeys[]={0,1,2};

SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

#define MAIN_MENU_ITEMS_N 6
HEADER_DESC main_menuhdr={0,0,0,0,NULL,(int)"Menu:",LGP_NULL};

MENUITEM_DESC main_menu_ITEMS[MAIN_MENU_ITEMS_N]=
{
  {NULL,(int)"Go to",      LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //0
  {NULL,(int)"Bookmarks",  LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //1
  {NULL,(int)"History",    LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //2
  {NULL,(int)"Settings",   LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //3
  {NULL,(int)"Search",     LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}, //3
  {NULL,(int)"Exit",       LGP_NULL, 0, NULL, MENU_FLAG3, MENU_FLAG2}  //4
};

static const MENUPROCS_DESC main_menu_HNDLS[MAIN_MENU_ITEMS_N]=
{
  mm_goto_url,
  mm_goto_bookmarks,
  mm_goto_history,
  mm_options,
  mm_search,
  mm_quit
};

static int mainmenu_keyhook(void *data, GUI_MSG *msg)
{
  return(0);
}

static void mainmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static const MENU_DESC mainmenu=
{
  8,mainmenu_keyhook,mainmenu_ghook,NULL,
  mmenusoftkeys,
  &mmenu_skt,
  0x10,//MENU_FLAG,
  NULL,
  main_menu_ITEMS,//menuitems,
  main_menu_HNDLS,//menuprocs,
  MAIN_MENU_ITEMS_N
};

int CreateMainMenu(VIEWDATA *vd)
{
  MAIN_CSM *main_csm;
  int main_menu_id;
  if ((main_csm=(MAIN_CSM *)FindCSMbyID(maincsm_id)))
  {
    patch_header(&main_menuhdr);
    main_menu_id=CreateMenu(0,0,&mainmenu,&main_menuhdr,0,MAIN_MENU_ITEMS_N,vd,0);
    main_csm->main_menu_id=main_menu_id;
  }
  return main_menu_id;
}

void initMainMenuLangPack()
{
  add_bookmark_sk[0].lgp_id=(int)lgpData[LGP_Add];
  add_bookmark_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  add_bookmark_hdr.lgp_id=(int)lgpData[LGP_BookmarkHeader];
  options_menuhdr.lgp_id=(int)lgpData[LGP_OptionsHeader];
  options_menu_ITEMS[0].lgp_id_small=(int)lgpData[LGP_Add];
  options_menu_ITEMS[1].lgp_id_small=(int)lgpData[LGP_Edit];
  options_menu_ITEMS[2].lgp_id_small=(int)lgpData[LGP_Delete];
  options_menu_ITEMS[3].lgp_id_small=(int)lgpData[LGP_Back];
  menu_sk[0].lgp_id=(int)lgpData[LGP_Options];
  menu_sk[1].lgp_id=(int)lgpData[LGP_Close];
  selurl_sk[0].lgp_id=(int)lgpData[LGP_Options];
  selurl_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  selurl_HDR.lgp_id=(int)lgpData[LGP_SelectBookmarkHeader];
  search_sk[0].lgp_id=(int)lgpData[LGP_Search];
  search_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  search_hdr.lgp_id=(int)lgpData[LGP_SearchHeader];
  history_sk[0].lgp_id=(int)lgpData[LGP_Go];
  history_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  history_HDR.lgp_id=(int)lgpData[LGP_HistoryHeader];
  input_menu_sk[0].lgp_id=(int)lgpData[LGP_Go];
  input_menu_sk[1].lgp_id=(int)lgpData[LGP_Cancel];
  input_url_hdr.lgp_id=(int)lgpData[LGP_AddressHeader];
  mmenu_sk[0].lgp_id=(int)lgpData[LGP_Select];
  mmenu_sk[1].lgp_id=(int)lgpData[LGP_Back];
  main_menuhdr.lgp_id=(int)lgpData[LGP_Menu];
  main_menu_ITEMS[0].lgp_id_small=(int)lgpData[LGP_GoTo];
  main_menu_ITEMS[1].lgp_id_small=(int)lgpData[LGP_Bookmarks];
  main_menu_ITEMS[2].lgp_id_small=(int)lgpData[LGP_History];
  main_menu_ITEMS[3].lgp_id_small=(int)lgpData[LGP_Settings];
  main_menu_ITEMS[4].lgp_id_small=(int)lgpData[LGP_Search];
  main_menu_ITEMS[5].lgp_id_small=(int)lgpData[LGP_Exit];
}
