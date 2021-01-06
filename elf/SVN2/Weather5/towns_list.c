#include "../inc/swilib.h"
#include "rect_patcher.h"
#include "string_works.h"
#include "towns_list.h" 
#include "main.h"

//=================================== Список городов ===========================================
int Menu_ID;
const char *null_string = "";

char **towns_lines; //Массив указателей на строки
int twns_count=0;

void FreeLines(void)
{
  if (towns_lines) 
  {
    mfree(towns_lines[twns_count-1]);
    mfree(towns_lines);
  }
  towns_lines=NULL;
}

int LoadLines(void)
{
  FSTATS stat;
  char *fn;
  int f;
  unsigned int ul;
  int i;
  int fsize;
  char *p, *pp, *add_str;
  int c;

  FreeLines();
 
  extern const char TOWNS_PATH[];
  fn=(char *)TOWNS_PATH;
  
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
	towns_lines=realloc(towns_lines,(i+1)*sizeof(char *));
	towns_lines[i++]=pp;
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
  towns_lines=realloc(towns_lines,(i+1)*sizeof(char *));
  add_str = malloc(strlen(";Другой...")+1);
  strcpy(add_str, ";Другой...");
  towns_lines[i++]=add_str;  
  return i;
}


HEADER_DESC twns_menuhdr={0,0,131,21,NULL,(int)"Выбор города...",LGP_NULL};

int twns_menusoftkeys[]={0,1,2};
extern int edmessage_id;
extern WSHDR* ws_eddata;


SOFTKEY_DESC twns_menu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Отмена"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB twns_menu_skt=
{
  twns_menu_sk,3
};

void twns_menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  const char *p=strrchr(towns_lines[curitem],';')+1;
  ws=AllocMenuWS(data,strlen(p));
  ascii2ws(ws,p);
  SetMenuItemText(data, item, ws, curitem);
}

void twns_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int twns_menu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    if (twns_count && GetCurMenuItem(data) != twns_count-1)
    {
      extern int wd_id;
      extern char logbuf[1024];
      extern int page_num;
      extern int itemnum;
      
      const char *p=strrchr(towns_lines[GetCurMenuItem(data)],';')+1;
      strncpy(Town_ID,towns_lines[GetCurMenuItem(data)],p-towns_lines[GetCurMenuItem(data)]-1); 
      Town_ID[p-towns_lines[GetCurMenuItem(data)]-1]='\0';
      //ShowMSG(1, (int)Town_ID);
    
      sprintf(logbuf, null_string);
      page_num=1;
      itemnum=0;
      
      FreeLines();
      GeneralFunc_flag1(wd_id,1);
      GeneralFunc_flag1(Menu_ID,1);
      do_start_connection();
    }
    else
      if(twns_count && GetCurMenuItem(data) == twns_count-1)
      {
        extern int wd_id;
        FreeLines();
        GeneralFunc_flag1(wd_id,1);
        GeneralFunc_flag1(Menu_ID,1);
        CreateInputUrl();
      }
      else
        {
          FreeLines();
          GeneralFunc_flag1(Menu_ID,1);           
        }
  }
  
  if (msg->keys==0x01)
  {
    FreeLines();
  }  
  return(0);
}

static const MENU_DESC twns_menu=
{
  0,twns_menu_keyhook,twns_menu_ghook,NULL,
  twns_menusoftkeys,
  &twns_menu_skt,
  8,
  twns_menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  0
};

HEADER_DESC twns_menuhdr;

void DispTownsMenu()
{
  twns_count=LoadLines();
  patch_header(&twns_menuhdr);
  Menu_ID = CreateMenu(0,0,&twns_menu,&twns_menuhdr,0,twns_count,0,0);
}

//------------------------------------------------------------------------------

static const SOFTKEY_DESC input_menu_sk[]=
{
  {0x0018,0x0000,(int)"Найти"},
  {0x0001,0x0000,(int)"Отмена"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB input_menu_skt=
{
  input_menu_sk,0
};


static const HEADER_DESC input_url_hdr={0,0,0,0,NULL,(int)"Название города",LGP_NULL};

static void input_url_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Найти"};
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

char * ToWeb(char *src)                   //конвертируем ссылку
{
  int cnt = 0, i, j;
  char *ret;
  char hex[] = "0123456789ABCDEF";
  for(i = 0; src[i]; i++)                 //считаем русские символы
    if((unsigned char)src[i] >= 0x80) cnt++;
  ret = malloc(strlen(src) + cnt*3 + 1);  //выделяем память под строку
  for(i = 0, j = 0; src[i]; i++)
    if((unsigned char)src[i] >= 0x80)
    {
      ret[j++] = '%';
      ret[j++] = hex[(src[i]>>4)&0xF];
      ret[j++] = hex[src[i]     &0xF];   //получаем замену
    }
    else
      ret[j++] = src[i];
  ret[j] = 0;
  mfree(src);                             //освобождаем память от исходной строки
  return ret;
}



static int input_url_onkey(GUI *data, GUI_MSG *msg)
{
  EDITCONTROL ec;
  WSHDR *ws;
  char *s, *url;
  extern int page_num;
  extern int itemnum;
  extern int request_type;
  extern char logbuf[1024];
  if (msg->keys==0xFFF)
  {
    ExtractEditControl(data,1,&ec);
    ws = ec.pWS;
    s = url = (char *)malloc(ws->wsbody[0]+1);
    for (int i=0; i<ws->wsbody[0] && i < 49; i++) *s++=char16to8(ws->wsbody[i+1]);
    *s = 0;
    strcpy(Town_ID, url);
    url = ToWeb(url);
    strcpy(Town_Name, url);
    GeneralFuncF1(1);
    
    page_num=1;
    itemnum=0;
    request_type = SEARCH;
    sprintf(logbuf, null_string);
    do_start_connection();

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
  EDITCONTROL ec;
  
  
  eq=AllocEQueue(ma,mfree_adr());    // Extension
  WSHDR *ews=AllocWS(1024);

  CutWSTR(ews, 0);
  
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40| ECF_DEFAULT_BIG_LETTER,ews,1024);
  AddEditControlToEditQend(eq,&ec,ma);   //2

  FreeWS(ews);
  patch_header(&input_url_hdr);
  patch_input(&input_url_desc);
  return CreateInputTextDialog(&input_url_desc,&input_url_hdr,eq,1,0);
}

//------------------------------------------------------------------------------

HEADER_DESC twns_srch_menuhdr={0,0,131,21,NULL,(int)"Выбор города",LGP_NULL};

int twns_srch_menusoftkeys[]={0,1,2};

SOFTKEY_DESC twns_srch_menu_sk[]=
{
  {0x0018,0x0000,(int)"Выбор"},
  {0x0001,0x0000,(int)"Отмена"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB twns_srch_menu_skt=
{
  twns_srch_menu_sk,3
};

void twns_srch_menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  const char *p=Towns[curitem].TownName;
  ws=AllocMenuWS(data,strlen(p));
  ascii2ws(ws,p);
  SetMenuItemText(data, item, ws, curitem);
}

void twns_srch_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int twns_srch_menu_keyhook(void *data, GUI_MSG *msg)
{
  int curitem = GetCurMenuItem(data);
  
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    if (TownsCnt)
    {
      extern int wd_id;
      extern char logbuf[1024];
      extern int page_num;
      extern int itemnum;
      extern int request_type;
      
      strcpy(Town_ID,Towns[curitem].TownID); 
      strcpy(Town_Name,Towns[curitem].TownName); 

      sprintf(logbuf, null_string);
      page_num=1;
      itemnum=0;
      
      mfree(Towns);
      Towns = 0;
      
      request_type = GET_TOWN;
      GeneralFunc_flag1(Menu_ID,1);
      do_start_connection();
    }
      else
        {
          GeneralFunc_flag1(Menu_ID,1);           
        }
  }
  
  if (msg->keys==0x01)
  {
    FreeLines();
  }  
  return(0);
}

static const MENU_DESC twns_srch_menu=
{
  0,twns_srch_menu_keyhook,twns_srch_menu_ghook,NULL,
  twns_srch_menusoftkeys,
  &twns_srch_menu_skt,
  8,
  twns_srch_menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  0
};

HEADER_DESC twns_srch_menuhdr;

void DispTownsSrchMenu()
{
  patch_header(&twns_srch_menuhdr);
  Menu_ID = CreateMenu(0,0,&twns_srch_menu,&twns_srch_menuhdr,0,TownsCnt,0,0);
}
