#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"
#include "rect_patcher.h"
#include <errno.h>

extern long  strtol (const char *nptr,char **endptr,int base);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

void GetKeyCodes(void *key);
void EditCoordinates(void *rect_or_xy, int is_rect);
extern void EditColors(char *color);

#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

unsigned int level=0;
CFG_HDR *levelstack[16];

int icon[]={0x58,0};
const int minus11=-11;

char cfg_name[256];

//Указатель на буфер конфигурации
char *cfg;
//Длинна файла конфигурации
int size_cfg;

CFG_HDR *cfg_h[512];
int total_items;

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Лев"},
  {0x0001,0x0000,(int)"Прав"},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

WSHDR *ews;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
  int sel_bcfg_id;
}MAIN_CSM;

int maincsm_id;

const char _percent_u[]="%u";
const char _percent_d[]="%d";
const char _percent_t[]="%t";

const char _mmc_etc_path[]="4:\\Zbin\\etc\\";
const char _data_etc_path[]="0:\\Zbin\\etc\\";

int create_ed(CFG_HDR *);
unsigned int char16to8(unsigned int c);

void ed1_locret(void){}

extern void open_select_file_gui(void *ed_gui, int type);


int IsFieldCorrect(void *data, int ec_index)
{
  EDITCONTROL ec;
  char ss[16];
  WSHDR *ws1;
  CFG_HDR *hp;
  int n; //Индекс элемента в массиве cfg_h
  int result=0;
  int err;
  unsigned int vui;
  int vi;
  ExtractEditControl(data,ec_index,&ec);
  if ((ec_index>1)&&(ec_index&1))
  {
    ws1=AllocWS(ec.pWS->maxlen);
    n=(ec_index-3)>>1; 
    hp=cfg_h[n];
    wstrcpy(ws1,ec.pWS);
    ws_2str(ws1,ss,15);
    *_Geterrno()=0;
    switch(hp->type)
    {
    case CFG_UINT:
      vui=strtoul(ss,0,10);
      if (vui<hp->min || vui>hp->max || !ws1->wsbody[0] || (err=*_Geterrno())==ERANGE)
      {
        if (vui<hp->min) {vui=hp->min; result=-1;}
        if (vui>hp->max) {vui=hp->max; result=1;}
        if (!ws1->wsbody[0]) {vui=hp->min; result=-1;}
        if (err==ERANGE) {vui=hp->max; result=1;}
        *((unsigned int *)(hp+1))=vui;
        wsprintf(ws1,_percent_u,vui);
        EDIT_SetTextToEditControl(data,ec_index,ws1);
      }
      break;
      
    case CFG_INT:
      vi=strtol(ss,0,10);
      if (vi<(int)hp->min || vi>(int)hp->max || !ws1->wsbody[0] || (err=*_Geterrno())==ERANGE)
      {
        if (vi<(int)hp->min) {vi=(int)hp->min; result=-1;}
        if (vi>(int)hp->max) {vi=(int)hp->max; result=1;}
        if (!ws1->wsbody[0]) {vi=(int)hp->min; result=-1;}
        if (err==ERANGE) {vi=(int)hp->max; result=1;}
        *((int *)(hp+1))=vi;
        wsprintf(ws1,_percent_d,vi);
        EDIT_SetTextToEditControl(data,ec_index,ws1);
      }
      break;
    }
    FreeWS(ws1);
  }
  return result;
}

void on_utf8ec(USR_MENU_ITEM *item)
{
  if (item->type==0)
  {
    switch(item->cur_item)
    {
    case 0:
      wsprintf(item->ws,_percent_t,"SelectFolder");
      break;
    case 1:
      wsprintf(item->ws,_percent_t,"SelectFile");
      break;
    }
  }
  if (item->type==1)
  {
    switch(item->cur_item)
    {
    case 0:
      open_select_file_gui(item->user_pointer, 0);
      break;
    case 1:
      open_select_file_gui(item->user_pointer, 1);
      break;
    }
  }   
}

int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  CFG_HDR *hp;
  int l;
  int i;
  int n;
  if (msg->keys==0xFFF)  // OK
  {
    return (1);    
  }
  if (msg->keys==0xFFE)  // Back
  {
    return (0xFF);
  }
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    l=msg->gbsmsg->submess;
    i=EDIT_GetFocus(data);
    if ((i>1)&&(i&1))
    {
      n=(i-3)>>1; //Индекс элемента в массиве cfg_h
      hp=cfg_h[n];
      if (l==LEFT_SOFT||l==ENTER_BUTTON)
      {
        if (l==ENTER_BUTTON)
        {
          if (hp->type==CFG_STR_UTF8)
          {
            EDIT_OpenOptionMenuWithUserItems(data,on_utf8ec,data,2);
            return (-1);
          }
        }
        switch(hp->type)
        {
        case CFG_COORDINATES:
          EditCoordinates((unsigned int *)(hp+1),0);
          break;
        case CFG_COLOR:
          EditColors((char *)(hp+1));
          break;
        case CFG_KEYCODE:
          GetKeyCodes((unsigned int *)(hp+1));
          break;
	case CFG_LEVEL:
	  level++;
	  levelstack[level]=hp;
	  level++;
	  return 1;
        case CFG_CHECKBOX:
          *((int *)(hp+1))=!*((int *)(hp+1));
          break;
        case CFG_RECT:
          EditCoordinates((unsigned int *)(hp+1),1);
          break;
          
        default:
          return(0);
        }
        return (-1);
      }
    }
  }
  return(0); //Do standart keys
  //1: close
}

void ed1_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC ok={0x0FFF,0x0000,(int)"OK"};
  static SOFTKEY_DESC back={0x0FFE,0x0000,(int)"Back"};
  static SOFTKEY_DESC close={0x0FFE,0x0000,(int)"Close"};
  EDITCONTROL ec;
  int i;
  int n;
  int j;
  int vi;
  int utf8conv_res_len;
  unsigned int vui;
  char ss[16];
  char *p;
  TTime tt;
  TDate dd;

  CFG_HDR *hp;
  
  if (cmd==TI_CMD_CREATE)
  {
    //Create
    int need_to_jump=(int)EDIT_GetUserPointer(data);
    EDIT_SetFocus(data,need_to_jump);
  }
  if (cmd==TI_CMD_DESTROY)
  {
    i=EDIT_GetFocus(data);
    IsFieldCorrect(data,i);
  }
  if (cmd==TI_CMD_REDRAW)
  {
    i=EDIT_GetFocus(data);
    ExtractEditControl(data,i,&ec);
    if ((i>1)&&(i&1))
    {
      n=(i-3)>>1; //Индекс элемента в массиве cfg_h
      hp=cfg_h[n];
      wstrcpy(ews,ec.pWS);
      ws_2str(ews,ss,15);
      int need_set_sk=0;
      switch(hp->type)
      {
      case CFG_UINT:
        vui=strtoul(ss,0,10);
        *((unsigned int *)(hp+1))=vui;
        break;
      case CFG_INT:
        vi=strtol(ss,0,10);
        *((int *)(hp+1))=vi;
        break;
      case CFG_STR_UTF8:
        ws_2str(ews,(char *)(hp+1),hp->max);
        break;

      case CFG_UTF8_STRING_PASS:
      case CFG_UTF8_STRING:
        // ws_2utf8( WSHDR *from, char *to , int *result_length, int max_len);
        ws_2utf8(ews,(char *)(hp+1),&utf8conv_res_len,hp->max);
        break;        
        
      case CFG_STR_PASS:
      case CFG_STR_WIN1251:
        j=0;
        p=(char *)(hp+1);
        while(j<hp->max)
        {
          if (j>=ews->wsbody[0]) break;
          *p++=char16to8(ews->wsbody[j+1]);
          j++;
        }
        *p=0;
        break;
      case CFG_CBOX:
        *((int *)(hp+1))=EDIT_GetItemNumInFocusedComboBox(data)-1;
        break;
         
      case CFG_COORDINATES:
        wsprintf(ews,"%d,%d",*((int *)(hp+1)),*((int *)(hp+1)+1));
        EDIT_SetTextToFocused(data,ews);
        need_set_sk=1;
        break;
      case CFG_COLOR:
        wsprintf(ews,"%02X,%02X,%02X,%02X",*((char *)(hp+1)),*((char *)(hp+1)+1),*((char *)(hp+1)+2),*((char *)(hp+1)+3));
        EDIT_SetTextToFocused(data,ews);  
        need_set_sk=1;
        break;
      case CFG_KEYCODE:
        wsprintf(ews,"%02X",*((int *)(hp+1)));
        EDIT_SetTextToFocused(data,ews);  
        need_set_sk=1;
        break;
      case CFG_CHECKBOX:
        CutWSTR(ews,0);
        wsAppendChar(ews, *((int *)(hp+1))?CBOX_CHECKED:CBOX_UNCHECKED);
        EDIT_SetTextToFocused(data,ews);
        need_set_sk=1;
        break;
      case CFG_TIME:
        EDIT_GetTime(data,i,&tt);
        memcpy((char *)(hp+1),&tt,sizeof(TTime));
        break;
      case CFG_DATE:
        EDIT_GetDate(data,i,&dd);
        memcpy((char *)(hp+1),&dd,sizeof(TDate));
        break;  
      case CFG_RECT:
        {
          RECT *rc=(RECT *)(hp+1);
          wsprintf(ews,"RECT:%03d;%03d;%03d;%03d;",rc->x,rc->y,rc->x2,rc->y2);
          EDIT_SetTextToFocused(data,ews);    
        }
        need_set_sk=1;
        break;
      case CFG_LEVEL:
        need_set_sk=1;
        break;
        
      default:
        break;      
      }
      if (need_set_sk)
      {
        need_set_sk=0;
        SetSoftKey(data,&ok,SET_SOFT_KEY_N);
        SetSoftKey(data,level?&back:&close,!SET_SOFT_KEY_N);
      }
    }
  }
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
  if (cmd==TI_CMD_SUBFOCUS_CHANGE)
  {
    i=EDIT_GetUnFocus(data);
    IsFieldCorrect(data,i);
  }
  if (cmd==TI_CMD_COMBOBOX_FOCUS)
  {
    //onCombo
    i=EDIT_GetFocus(data);
    ExtractEditControl(data,i,&ec);
    if ((i>1)&&(i&1))
    {
      n=(i-3)>>1; //Индекс элемента в массиве cfg_h
      hp=cfg_h[n];
      if (hp->type==CFG_CBOX)
      {
        if ((j=EDIT_GetItemNumInFocusedComboBox(data)))
        {
          wsprintf(ews,_percent_t,((CFG_CBOX_ITEM*)((char *)hp+sizeof(CFG_HDR)+4))+(j-1));
        }
        else
        {
          ExtractEditControl(data,EDIT_GetFocus(data)-1,&ec);
          wstrcpy(ews,ec.pWS);
        }
        EDIT_SetTextToFocused(data,ews);
      }
    }
  }
}

HEADER_DESC ed1_hdr={0,0,0,0,NULL,(int)"Edit Config",LGP_NULL};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
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


void ErrorMsg(const char *msg);
void UpdateCSMname(const char *fname);

int LoadCfg(char *cfgname)
{
  int f;
  unsigned int err;
  FSTATS fstat;
  if (cfgname!=cfg_name)  strncpy(cfg_name,cfgname,255);
  int result=0;
  
  if (GetFileStats(cfgname,&fstat,&err)!=-1)
  {
    if ((f=fopen(cfgname,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
    {
      size_cfg=fstat.size;
      if (size_cfg<=0)
      {
        ErrorMsg("Zero lenght of .bcfg file!");
      }
      else
      {
        cfg=malloc((size_cfg+3)&(~3));
        if (fread(f,cfg,size_cfg,&err)!=size_cfg)
        {
          ErrorMsg("Can't read .bcfg file!");
          mfree(cfg);
        }
        else result=1;
      }
      fclose(f,&err);
    }
  } 
  return result;
}

typedef struct
{
  void *next;
  char cfgname[64];
  char fullpath[128];
}SEL_BCFG;


SEL_BCFG *sbtop;

//------------------- Т9 ------------------//

//Ключи для поиска по T9
static const char table_T9Key[256]=
"11111111111111111111111111111111"
"10001**0***0000*012345678900***0"
"0222333444555666777788899991*110"
"122233344455566677778889999111*1"
"11111111111111111111111111111111"
"11111111311111111111111131111111"
"22223333444455566677778888899999"
"22223333444455566677778888899999";


char T9Key[32];
int sel_bcfg_id;
char bcfg_hdr_text[32];
char bcfgmenu_sk_r[16];
volatile int prev_bcfg_itemcount;

SEL_BCFG *FindBCFGByNS(int *i)
{
  SEL_BCFG *t;
  t=(SEL_BCFG *)sbtop;
  char *s;
  char *d;
  int c;
  while(t)
  {
   s=T9Key;
   d=t->cfgname;
   while(c=*s++)
   {
    if(c!=table_T9Key[*d++]) goto L_NOT9;
   }
   if(!(*i)) return(t);
   (*i)--;
 L_NOT9:
    t=t->next;
  }
  return(t);
}

int CountBCFG(void)
{
  int l=-1;
  FindBCFGByNS(&l);
  l=-1-l;
  return l;
}

SEL_BCFG *FindBCFGByN(int i)
{
  SEL_BCFG *t;
  t=FindBCFGByNS(&i);
  return t;
}

//----------------------------------//

void ClearT9Key(void)
{
  zeromem(T9Key,sizeof(T9Key));
}

void UpdateBCFGHeader(void)
{
  if (strlen(T9Key))
  {
    strcpy(bcfg_hdr_text,"Input T9:");
    strcat(bcfg_hdr_text,T9Key);
    strcpy(bcfgmenu_sk_r,"<C");
  }
  else
  {
    strcpy(bcfg_hdr_text,"Select BCFG");
    strcpy(bcfgmenu_sk_r,"Close");
  }
}

void AddT9Key(int chr)
{
  int l=strlen(T9Key);
  if (l<(sizeof(T9Key)-1))
  {
    T9Key[l]=chr;
  }
}

void BackSpaceT9(void)
{
  int l=strlen(T9Key);
  if (l)
  {
    l--;
    T9Key[l]=0;
  }
}

void RecountMenuBCFG()
{
  int i;
  void *data;
  UpdateBCFGHeader();
  if (!sel_bcfg_id) return; //Нечего считать
  data=FindGUIbyId(sel_bcfg_id,NULL);

  i=CountBCFG();
  if (i!=prev_bcfg_itemcount)
  {
    prev_bcfg_itemcount=i;
    Menu_SetItemCountDyn(data,i);
  }
  SetCursorToMenuItem(data,0);
  if (IsGuiOnTop(sel_bcfg_id)) RefreshGUI();
}

//-------------------------------------------//


int selbcfg_menu_onkey(void *gui, GUI_MSG *msg)
{
  SEL_BCFG *t;
  int i;  
  i=GetCurMenuItem(gui);
  if (msg->keys==0x3D || msg->keys==0x18)
  {
    t=FindBCFGByN(i);
    if (t)
    {
      ClearT9Key();
      MAIN_CSM *csm=(MAIN_CSM *)FindCSMbyID(maincsm_id);
      if (LoadCfg(t->fullpath))
      {
        UpdateCSMname(t->fullpath);
        csm->gui_id=create_ed(0);
        return (1);
      }
    }
  } 
  
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    int key=msg->gbsmsg->submess;
    if (((key>='0')&&(key<='9'))||(key=='#')||(key=='*'))
    {
      AddT9Key(key);
      RecountMenuBCFG();
      return(-1);
    }
  }  
  if (msg->keys==1)
  {
    if (strlen(T9Key))
    {
      BackSpaceT9();
      RecountMenuBCFG();
      return(-1);
    }
  }
 
  return (0);
}

void selbcfg_menu_ghook(void *gui, int cmd)
{
  SEL_BCFG *sbtop=MenuGetUserPointer(gui);
  if (cmd==TI_CMD_DESTROY)
  {
    while(sbtop)
    {
      SEL_BCFG *sb=sbtop;
      sbtop=sbtop->next;
      mfree(sb);
    }    
  }
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}

void selbcfg_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  SEL_BCFG  *t;
  WSHDR *ws;
  int len;
  void *item=AllocMenuItem(gui);
  t=FindBCFGByN(cur_item);
  if (t)
  {
    len=strlen(t->cfgname);
    len=strlen(t->cfgname);
    ws=AllocMenuWS(gui,len+4);
    wsprintf(ws,_percent_t,t->cfgname);
  }
  else
  {
    ws=AllocMenuWS(gui,10);
    wsprintf(ws,_percent_t,"Ошибка");
  }
  SetMenuItemText(gui, item, ws, cur_item);
}

int selbcfg_softkeys[]={0,1,2};
SOFTKEY_DESC selbcfg_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)bcfgmenu_sk_r},
  {0x003D,0x0000,(int)"+"}
};

SOFTKEYSTAB selbcfg_skt=
{
  selbcfg_sk,0
};
HEADER_DESC selbcfg_HDR={0,0,0,0,NULL,(int)bcfg_hdr_text,LGP_NULL};

MENU_DESC selbcfg_STRUCT=
{
  8,selbcfg_menu_onkey,selbcfg_menu_ghook,NULL,
  selbcfg_softkeys,
  &selbcfg_skt,
  0x10,
  selbcfg_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

int CreateSelectBCFGMenu()
{
  UpdateBCFGHeader();
  unsigned int err;
  DIR_ENTRY de;
  const char *s;
  SEL_BCFG *sb;
  int n_bcfg=0;
  char str[128];
  if (!isdir((s=_mmc_etc_path),&err))
  {
    s=_data_etc_path;
  }
  strcpy(str,s);
  strcat(str,"*.bcfg");
  if (FindFirstFile(&de,str,&err))
  {
    do
    {
      if (!(de.file_attr&FA_DIRECTORY))
      {
        extern int strcmp_nocase(const char *s, const char *d);
        sb=malloc(sizeof(SEL_BCFG));
        strcpy(sb->fullpath,s);
        strcat(sb->fullpath,de.file_name);
        strcpy(sb->cfgname,de.file_name);
        sb->cfgname[strlen(de.file_name)-5]=0;
        sb->next=0;
        if (sbtop)
        {
          SEL_BCFG *sbr, *sbt;
          sbr=(SEL_BCFG *)&sbtop;
          sbt=sbtop;
          while(strcmp_nocase(sbt->cfgname,sb->cfgname)<0)
          {
            sbr=sbt;
            sbt=sbt->next;
            if (!sbt) break;
          }
          sb->next=sbt;
          sbr->next=sb;
        }
        else
        {
          sbtop=sb;
        }
        n_bcfg++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  prev_bcfg_itemcount=n_bcfg;
  patch_header(&selbcfg_HDR);
  return sel_bcfg_id=CreateMenu(0,0,&selbcfg_STRUCT,&selbcfg_HDR,0,n_bcfg,sbtop,0);
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(256);
  
  char *s=cfg_name;
  int find_cfg=1;
  if (*s>='0' && *s<='9' && *(s+1)==':')  // Наверное путь к bcfg :)
  {
    if (LoadCfg(s))
    {
      UpdateCSMname(s);
      csm->gui_id=create_ed(0);
      find_cfg=0;
    }
  }
  if (find_cfg)
  {
    UpdateCSMname("Select BCFG");
    csm->sel_bcfg_id=CreateSelectBCFGMenu();    
  }
  csm->csm.state=0;
  csm->csm.unk1=0;
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void SaveConfig(void)
{
  unsigned int ul;
  int f=fopen(cfg_name,A_ReadWrite+A_Create+A_Truncate+A_BIN,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    fwrite(f,cfg,size_cfg,&ul);
    fclose(f,&ul);
  }
  GBS_SendMessage(MMI_CEPID, MSG_RECONFIGURE_REQ,0,cfg_name);
}

void maincsm_onclose(CSM_RAM *csm)
{
  FreeWS(ews);
  if (cfg) mfree(cfg);
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  CFG_HDR *hp;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      if (level)
      {
	hp=levelstack[level];
        levelstack[level]=NULL;
	level--;
	csm->gui_id=create_ed(hp);
	return (1);
      }
      if ((int)msg->data1==1)
	SaveConfig();
      else 
	csm->csm.state=-3;
      csm->gui_id=0;
    }
    if ((int)msg->data0==csm->sel_bcfg_id)
    {
      if (csm->gui_id==0)
        csm->csm.state=-3;
      csm->sel_bcfg_id=0;
    }
  }
  if ((msg->msg==MSG_RECONFIGURE_REQ)&&(cfg_name==(char *)msg->data0))
  {
    csm->csm.state=-3;
  }
  return(1);
}

unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0, 
  0, 
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

typedef struct
{
  unsigned short u;
  char dos;
  char win;
  char koi8;
} TUNICODE2CHAR;

const TUNICODE2CHAR unicode2char[]=
{
  // CAPITAL Cyrillic letters (base)
  0x410,0x80,0xC0,0xE1, // А
  0x411,0x81,0xC1,0xE2, // Б
  0x412,0x82,0xC2,0xF7, // В
  0x413,0x83,0xC3,0xE7, // Г
  0x414,0x84,0xC4,0xE4, // Д
  0x415,0x85,0xC5,0xE5, // Е
  0x416,0x86,0xC6,0xF6, // Ж
  0x417,0x87,0xC7,0xFA, // З
  0x418,0x88,0xC8,0xE9, // И
  0x419,0x89,0xC9,0xEA, // Й
  0x41A,0x8A,0xCA,0xEB, // К
  0x41B,0x8B,0xCB,0xEC, // Л
  0x41C,0x8C,0xCC,0xED, // М
  0x41D,0x8D,0xCD,0xEE, // Н
  0x41E,0x8E,0xCE,0xEF, // О
  0x41F,0x8F,0xCF,0xF0, // П
  0x420,0x90,0xD0,0xF2, // Р
  0x421,0x91,0xD1,0xF3, // С
  0x422,0x92,0xD2,0xF4, // Т
  0x423,0x93,0xD3,0xF5, // У
  0x424,0x94,0xD4,0xE6, // Ф
  0x425,0x95,0xD5,0xE8, // Х
  0x426,0x96,0xD6,0xE3, // Ц
  0x427,0x97,0xD7,0xFE, // Ч
  0x428,0x98,0xD8,0xFB, // Ш
  0x429,0x99,0xD9,0xFD, // Щ
  0x42A,0x9A,0xDA,0xFF, // Ъ
  0x42B,0x9B,0xDB,0xF9, // Ы
  0x42C,0x9C,0xDC,0xF8, // Ь
  0x42D,0x9D,0xDD,0xFC, // Э
  0x42E,0x9E,0xDE,0xE0, // Ю
  0x42F,0x9F,0xDF,0xF1, // Я
  // CAPITAL Cyrillic letters (additional)
  0x402,'_',0x80,'_', // _ .*.*
  0x403,'_',0x81,'_', // _ .*.*
  0x409,'_',0x8A,'_', // _ .*.*
  0x40A,'_',0x8C,'_', // _ .*.*
  0x40C,'_',0x8D,'_', // _ .*.*
  0x40B,'_',0x8E,'_', // _ .*.*
  0x40F,'_',0x8F,'_', // _ .*.*
  0x40E,0xF6,0xA1,'_', // Ў ...*
  0x408,0x4A,0xA3,0x4A, // _ .*.*
  0x409,0x83,0xA5,0xBD, // _ .*..
  0x401,0xF0,0xA8,0xB3, // Ё
  0x404,0xF2,0xAA,0xB4, // Є
  0x407,0xF4,0xAF,0xB7, // Ї
  0x406,0x49,0xB2,0xB6, // _ .*..
  0x405,0x53,0xBD,0x53, // _ .*.*
  // SMALL Cyrillic letters (base)
  0x430,0xA0,0xE0,0xC1, // а
  0x431,0xA1,0xE1,0xC2, // б
  0x432,0xA2,0xE2,0xD7, // в
  0x433,0xA3,0xE3,0xC7, // г
  0x434,0xA4,0xE4,0xC4, // д
  0x435,0xA5,0xE5,0xC5, // е
  0x436,0xA6,0xE6,0xD6, // ж
  0x437,0xA7,0xE7,0xDA, // з
  0x438,0xA8,0xE8,0xC9, // и
  0x439,0xA9,0xE9,0xCA, // й
  0x43A,0xAA,0xEA,0xCB, // к
  0x43B,0xAB,0xEB,0xCC, // л
  0x43C,0xAC,0xEC,0xCD, // м
  0x43D,0xAD,0xED,0xCE, // н
  0x43E,0xAE,0xEE,0xCF, // о
  0x43F,0xAF,0xEF,0xD0, // п
  0x440,0xE0,0xF0,0xD2, // р
  0x441,0xE1,0xF1,0xD3, // с
  0x442,0xE2,0xF2,0xD4, // т
  0x443,0xE3,0xF3,0xD5, // у
  0x444,0xE4,0xF4,0xC6, // ф
  0x445,0xE5,0xF5,0xC8, // х
  0x446,0xE6,0xF6,0xC3, // ц
  0x447,0xE7,0xF7,0xDE, // ч
  0x448,0xE8,0xF8,0xDB, // ш
  0x449,0xE9,0xF9,0xDD, // щ
  0x44A,0xEA,0xFA,0xDF, // ъ
  0x44B,0xEB,0xFB,0xD9, // ы
  0x44C,0xEC,0xFC,0xD8, // ь
  0x44D,0xED,0xFD,0xDC, // э
  0x44E,0xEE,0xFE,0xC0, // ю
  0x44F,0xEF,0xFF,0xD1, // я
  // SMALL Cyrillic letters (additional)
  0x452,'_',0x90,'_', // _ .*.*
  0x453,'_',0x83,'_', // _ .*.*
  0x459,'_',0x9A,'_', // _ .*.*
  0x45A,'_',0x9C,'_', // _ .*.*
  0x45C,'_',0x9D,'_', // _ .*.*
  0x45B,'_',0x9E,'_', // _ .*.*
  0x45F,'_',0x9F,'_', // _ .*.*
  0x45E,0xF7,0xA2,'_', // ў ...*
  0x458,0x6A,0xBC,0x6A, // _ .*.*
  0x491,0xA3,0xB4,0xAD, // _ .*..
  0x451,0xF1,0xB8,0xA3, // ё
  0x454,0xF3,0xBA,0xA4, // є
  0x457,0xF5,0xBF,0xA7, // ї
  0x456,0x69,0xB3,0xA6, // _ .*..
  0x455,0x73,0xBE,0x73, // _ .*.*
  0x0A0,'_',0xA0,0x20, // space .*..
  0x0A4,'_',0xA4,0xFD, // ¤   .*..
  0x0A6,'_',0xA6,'_', // ¦   .*.*
  0x0B0,0xF8,0xB0,0x9C, // °
  0x0B7,0xFA,0xB7,0x9E, // ·
  // 0x2022,,0x95,0x95, //    .*..
  // 0x2116,0xFC,0xB9,0x23, // №   ...*
  // 0x2219,,0xF9,0x9E, //    .*..
  // 0x221A,0xFB,,0x96, // v   ..*.
  // 0x25A0,0xFE,,0x94, // ¦
  0x0000,0,0,0
};

unsigned int char16to8(unsigned int c)
{
  const TUNICODE2CHAR *p=unicode2char;
  unsigned int i;
  if (c<32) return(' ');
  if (c<128) return(c);
  while((i=p->u))
  {
    if (c==i)
    {
      return(p->win);
    }
    p++;
  }
  c&=0xFF;
  if (c<32) return(' ');
  return(c);
}

void UpdateCSMname(const char *fname)
{
  char *s;
//  int i;
  WSHDR *ws=AllocWS(256);
  if ((s=strrchr(fname,'\\'))==0)
  {
    if ((s=strrchr(fname,'/'))==0)
    {
      if ((s=strrchr(fname,':'))==0) s=(char *)fname-1;
    }
  }
  s++;
  str_2ws(ws,s,128);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Config: %w",ws);
  FreeWS(ws);
}

void ErrorMsg(const char *msg)
{
  LockSched();
  ShowMSG(1,(int)msg);
  UnlockSched();
}
char picpath[]="0:\\zbin\\img\\cfgedit.png";
int main(const char *elf_name, const char *fname)
{
  picpath[0]=elf_name[0];
  MAIN_CSM main_csm;
  if (fname) strncpy(cfg_name,fname,255);
  zeromem(&main_csm,sizeof(MAIN_CSM));
  UpdateCSMname(fname);
  LockSched();
  maincsm_id=CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  return 0;
}

int getnumwidth(unsigned int num)
{
  int i=1;
  while(num>=10) 
  {
    num/=10;
    i++;
  }
  return (i);  
}

int create_ed(CFG_HDR *need_to_focus)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  char *p=cfg;
  int n=size_cfg;
  CFG_HDR *hp;
  int need_to_jump=3;

  int i;
  unsigned int curlev=0;
  CFG_HDR *parent=NULL;
  CFG_HDR *parents[16];

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());

  //Имя конфигурации
  ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,(WSHDR *)(&MAINCSM.maincsm_name),256);
  AddEditControlToEditQend(eq,&ec,ma); //EditControl 1
  parents[0]=NULL;

  total_items=0;
  while(n>=sizeof(CFG_HDR))
  {
    hp=(CFG_HDR*)p;
    cfg_h[total_items]=hp;
    //Добавляем заголовок итема
    wsprintf(ews,"%t:",hp->name);
    if (hp->type==CFG_LEVEL)
    {
      if (hp->min)
      {
        if ((curlev==level)&&(parent==levelstack[level]))
	{
	  ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ews,256);
	  AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+2
	}
      }
      else
	if (curlev)
	{
	  parent=parents[curlev];
	  curlev--;
	}
    }
    else
    {
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        if (hp->type!=CFG_CHECKBOX)
        {
          ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
        }
        else 
        {
          ConstructEditControl(&ec,ECT_HEADER,ECF_NORMAL_STR,ews,256);
        }
	AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+2
      }
    }
    n-=sizeof(CFG_HDR);
    p+=sizeof(CFG_HDR);
    switch(hp->type)
    {
    case CFG_UINT:
      n-=sizeof(unsigned int);
      if (n<0)
      {
      L_ERRCONSTR:
        wsprintf(ews,"Unexpected EOF!!!");
      L_ERRCONSTR1:
        ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
        AddEditControlToEditQend(eq,&ec,ma);
        goto L_ENDCONSTR;
      }
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        wsprintf(ews,_percent_u,*((unsigned int *)p));
	ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_MINUS|ECF_DISABLE_POINT,ews,getnumwidth(hp->max));
	AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+3
      }
      p+=sizeof(unsigned int);
      break;
    case CFG_INT:
      n-=sizeof(int);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        int k1,k2;
        unsigned int min,max;
        wsprintf(ews,_percent_d,*((int *)p));
        min=(k1=hp->min)>=0?k1:(-k1)*10;
        max=(k2=hp->max)>=0?k2:(-k2)*10;
	ConstructEditControl(&ec,ECT_NORMAL_NUM,ECF_APPEND_EOL|ECF_DISABLE_POINT,ews,getnumwidth(min>max?min:max));
        if (k1>=0 && k2>=0) ec.flag|=ECF_DISABLE_MINUS;
	AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+3
      }
      p+=sizeof(int);
      break;
    case CFG_STR_UTF8:
      n-=(hp->max+1+3)&(~3);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        str_2ws(ews,p,hp->max);
	ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,hp->max);
	AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+3
      }
      p+=(hp->max+1+3)&(~3);
      break;
    case CFG_STR_WIN1251:
      n-=(hp->max+1+3)&(~3);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        wsprintf(ews,_percent_t,p);
	ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,hp->max);
	AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+3
      }
      p+=(hp->max+1+3)&(~3);
      break;

    case CFG_UTF8_STRING:
      n-=(hp->max+1+3)&(~3);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        utf8_2ws(ews,p,hp->max);
	ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL,ews,hp->max);
	AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+3
      }
      p+=(hp->max+1+3)&(~3);
      break;
    case CFG_UTF8_STRING_PASS:
      n-=(hp->max+1+3)&(~3);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        utf8_2ws(ews,p,hp->max);
	ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL|ECF_PASSW,ews,hp->max);
	AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+3
      }
      p+=(hp->max+1+3)&(~3);
      break;      
    case CFG_CBOX:
      n-=hp->max*sizeof(CFG_CBOX_ITEM)+4;
      if (n<0) goto L_ERRCONSTR;
      i=*((int *)p);
      if (i>=hp->max)
      {
        wsprintf(ews,"Bad index in combobox!!!");
        goto L_ERRCONSTR1;
      }
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        wsprintf(ews,_percent_t,((CFG_CBOX_ITEM*)(p+4))+i);
	ConstructComboBox(&ec,7,ECF_APPEND_EOL,ews,32,0,hp->max,i+1);
	AddEditControlToEditQend(eq,&ec,ma);
      }
      p+=hp->max*sizeof(CFG_CBOX_ITEM)+4;
      break;
      
    case CFG_STR_PASS:
      n-=(hp->max+1+3)&(~3);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        wsprintf(ews,_percent_t,p);
	ConstructEditControl(&ec,ECT_NORMAL_TEXT,ECF_APPEND_EOL|ECF_PASSW,ews,hp->max);
	AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+3
      }
      p+=(hp->max+1+3)&(~3);
      break;
    case CFG_COORDINATES:
      n-=8;
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        wsprintf(ews,"%d,%d",*((int *)p),*((int *)p+1));
	ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,ews,10);
	AddEditControlToEditQend(eq,&ec,ma); 
      }
      p+=8;
      break;
    case CFG_COLOR:
      n-=4;
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        wsprintf(ews,"%02X,%02X,%02X,%02X",*((char *)p),*((char *)p+1),*((char *)p+2),*((char *)p+3));
	ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,ews,12);
	AddEditControlToEditQend(eq,&ec,ma);
      }
      p+=4;
      break;
    case CFG_KEYCODE:
      n-=4;
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        wsprintf(ews,"%02X",*(int *)p);
	ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,ews,12);
	AddEditControlToEditQend(eq,&ec,ma);
      }
      p+=4;
      break;

    case CFG_LEVEL:
      if (n<0) goto L_ERRCONSTR;
      wsprintf(ews,_percent_t,"Enter");
      if (hp->min)
      {
	if ((curlev==level)&&(parent==levelstack[level]))
	{
          int n_edit;
	  EDITC_OPTIONS ec_options;
	  ConstructEditControl(&ec,ECT_READ_ONLY_SELECTED,ECF_APPEND_EOL,ews,256);
	  SetPenColorToEditCOptions(&ec_options,2);
	  SetFontToEditCOptions(&ec_options,1);
	  CopyOptionsToEditControl(&ec,&ec_options);
	  n_edit=AddEditControlToEditQend(eq,&ec,ma); //EditControl n*2+3
          if (need_to_focus)
          {
            if (need_to_focus==hp)  need_to_jump=n_edit;
          }
	  total_items++;
	}
	curlev++;
	parents[curlev]=parent;
	parent=hp;
      }
      continue;
    case CFG_CHECKBOX:
      n-=4;
      if (n<0) goto L_ERRCONSTR;
      CutWSTR(ews,0);
      wsAppendChar(ews, *((int *)p)?CBOX_CHECKED:CBOX_UNCHECKED);
      if ((curlev==level)&&(parent==levelstack[level]))
      {
	ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,ews,1);
	AddEditControlToEditQend(eq,&ec,ma);           
      }
      p+=4;
      break;
    case CFG_TIME:
      n-=sizeof(TTime);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        TTime *tt=(TTime *)p;
	ConstructEditControl(&ec,ECT_TIME,ECF_APPEND_EOL,0,0);
        ConstructEditTime(&ec,tt);
	AddEditControlToEditQend(eq,&ec,ma);  
      }
      p+=sizeof(TTime);
      break;
      
    case CFG_DATE:
      n-=sizeof(TDate);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        TDate *dd=(TDate *)p;
	ConstructEditControl(&ec,ECT_CALENDAR,ECF_APPEND_EOL,0,0);
        ConstructEditDate(&ec,dd);
	AddEditControlToEditQend(eq,&ec,ma);  
      }
      p+=sizeof(TDate);
      break;
      
    case CFG_RECT:
      n-=sizeof(RECT);
      if (n<0) goto L_ERRCONSTR;
      if ((curlev==level)&&(parent==levelstack[level]))
      {
        EDITC_OPTIONS ec_options;
        RECT *rc=(RECT *)p;
        wsprintf(ews,"RECT:%03d;%03d;%03d;%03d;",rc->x,rc->y,rc->x2,rc->y2);
	ConstructEditControl(&ec,ECT_LINK,ECF_APPEND_EOL,ews,ews->wsbody[0]);
        SetFontToEditCOptions(&ec_options,1);
	CopyOptionsToEditControl(&ec,&ec_options);
	AddEditControlToEditQend(eq,&ec,ma);  
      }
      p+=sizeof(RECT);
      break;
      
    default:
      wsprintf(ews,"Unsupported item %d",hp->type);
      ConstructEditControl(&ec,ECT_HEADER,ECF_APPEND_EOL,ews,256);
      AddEditControlToEditQend(eq,&ec,ma);
      goto L_ENDCONSTR;
    }
    if ((curlev==level)&&(parent==levelstack[level])) total_items++;
  }
L_ENDCONSTR:
  patch_header(&ed1_hdr);
  patch_input(&ed1_desc);
  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,(void *)need_to_jump);
}
