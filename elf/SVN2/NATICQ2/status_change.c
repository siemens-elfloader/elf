/*
  Интерфейс и функции смены своего статуса
*/
#include "../inc/swilib.h"
#include "../inc/cfg_items.h"
#include "../inc/pnglist.h"
#include "NatICQ.h"
#include "main.h"
#include "status_change.h"
#include "strings.h"
#include "lang.h"

//===============================================================================================
// ELKA Compatibility
#pragma inline
static void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC *)head)->rc.x=0;
  ((HEADER_DESC *)head)->rc.y=YDISP;
  ((HEADER_DESC *)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC *)head)->rc.y2=HeaderH()-1+YDISP;
}
#pragma inline
void patch_input(const INPUTDIA_DESC* inp)
{
  ((INPUTDIA_DESC *)inp)->rc.x = 0;
  ((INPUTDIA_DESC *)inp)->rc.y = HeaderH() + 1 + YDISP;
  ((INPUTDIA_DESC *)inp)->rc.x2=ScreenW() - 1;
  ((INPUTDIA_DESC *)inp)->rc.y2=ScreenH() - SoftkeyH() - 1;
}
//===============================================================================================

extern const char TEMPLATES_PATH[];
static const char XS_FILE_NAME[]="XStatuses.txt";


char *XStatusText;

extern int CurrentStatus;
extern int CurrentXStatus;
extern  int S_ICONS[];

#pragma inline
static void Change_Status(int status)
{
  CurrentStatus=status;
  set_my_status();
  SUBPROC((void*)WriteDefSettings);
}

#pragma inline
static void Change_XStatus(int xstatus)
{
  CurrentXStatus=xstatus;
  set_my_xstatus();
  SUBPROC((void*)WriteDefSettings);
}

///////////////////////////////////////////////////////////////////////////////
#pragma inline
static unsigned int GetStatusIndexInMenu(unsigned int status)
{
  switch(status)
  {
  case IS_ONLINE: {return 0;}
  case IS_AWAY: {return 1;}
  case IS_NA: {return 2;}
  case IS_DND: {return 3;}
  case IS_OCCUPIED: {return 4;}
  case IS_FFC: {return 5;}
  case IS_INVISIBLE: {return 6;}
  case IS_DEPRESSION: return 7;
  case IS_EVIL: return 8;
  case IS_HOME: return 9;
  case IS_LUNCH: return 10;
  case IS_WORK: return 11;
  }
  return 0;
}

#pragma inline 
static unsigned int GetStatusInMenuByPos(int pos)
{
  switch(pos)
  {
  case 0:
    return IS_ONLINE;
  case 1:
    return IS_AWAY;
  case 2:
    return IS_NA;
  case 3:
    return IS_DND;
  case 4:
    return IS_OCCUPIED;
  case 5:
    return IS_FFC;
  case 6:
    return IS_INVISIBLE;
  case 7:
    return IS_DEPRESSION;
  case 8:
    return IS_EVIL;
  case 9:
    return IS_HOME;
  case 10:
    return IS_LUNCH;
  case 11:
    return IS_WORK;
  }
  return IS_UNKNOWN;
}

static int st_onkey(void *data, GUI_MSG *msg)
{
  int i;
  if (msg->keys==0x18 || msg->keys==0x3D)
  {
    i=GetCurMenuItem(data);
    Change_Status(GetStatusInMenuByPos(i));
    return (1);
  }
  return (0);
}
    
///////////////////////////////////////////////////////////////////////////////

#define STATUSES_NUM 12

static char * menutexts[STATUSES_NUM]=
{
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};

void st_icons_set(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  extern const char percent_t[];
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  wsprintf(ws,percent_t,menutexts[curitem]);
  SetMenuItemIconArray(data,item,S_ICONS+GetStatusInMenuByPos(curitem));
  SetMenuItemText(data, item, ws, curitem);
}

static HEADER_DESC st_menuhdr={0,0,0,0,NULL,NULL,LGP_NULL};

static const int st_menusoftkeys[]={0,1,2};

static SOFTKEY_DESC st_menu_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB st_menu_skt=
{
  st_menu_sk,0
};

static void stmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static const MENU_DESC st_tmenu=
{
  8,st_onkey,stmenu_ghook,NULL,
  st_menusoftkeys,
  &st_menu_skt,
  0x11,//MENU_FLAG,
  st_icons_set,
  NULL,//st_menuitems,
  NULL,
  STATUSES_NUM
};


void DispStatusChangeMenu()
{
  *((int **)(&st_menuhdr.icon))=S_ICONS+CurrentStatus;
  patch_header(&st_menuhdr);
  
  //Инициализация ленгпака
  st_menuhdr.lgp_id=(int)lgpData[LGP_ChgStatus];
  st_menu_sk[0].lgp_id=(int)lgpData[LGP_Select];
  st_menu_sk[1].lgp_id=(int)lgpData[LGP_Back];
  
  menutexts[0]=(char *)lgpData[LGP_StOnline];
  menutexts[1]=(char *)lgpData[LGP_StAway];
  menutexts[2]=(char *)lgpData[LGP_StNa];
  menutexts[3]=(char *)lgpData[LGP_StDnd];
  menutexts[4]=(char *)lgpData[LGP_StOccup];
  menutexts[5]=(char *)lgpData[LGP_StFfc];
  menutexts[6]=(char *)lgpData[LGP_StInvis];
  menutexts[7]=(char *)lgpData[LGP_StDepression];
  menutexts[8]=(char *)lgpData[LGP_StEvil];
  menutexts[9]=(char *)lgpData[LGP_StHome];
  menutexts[10]=(char *)lgpData[LGP_StLunch];
  menutexts[11]=(char *)lgpData[LGP_StWork];
  
  CreateMenu(0,0,&st_tmenu,&st_menuhdr,GetStatusIndexInMenu(CurrentStatus),STATUSES_NUM,0,0);
}

//--------------------------------
// XStatuses
//--------------------------------
extern DYNPNGICONLIST *XStatusesImgList;
extern int *XStatusesIconArray;
extern volatile int total_xstatuses;

SOFTKEY_DESC edit_x_sk[]=
{
  {0x0018,0x0000,(int)"Save!"},
  {0x0001,0x0000,(int)""},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB edit_x_skt=
{
  edit_x_sk,0
};

void edit_xstatus_locret(void){}

void ReplaceStr(char **str, int start_prev, int prev_len, char *next, int next_len)
{
  char *d, *buf;
  char *s=*str;
  if (s)
  {
    d=buf=malloc(strlen(s)+next_len-prev_len+1);
    if (start_prev)
    {
      memcpy(buf, s, start_prev);
      buf+=start_prev;
    }
    if (next_len)
    {
      memcpy(buf,next,next_len);
      buf+=next_len;
    }
    strcpy(buf, s+start_prev+prev_len);
    mfree(s);
    *str=d;
  }
}

int edit_xstatus_onkey(GUI *data, GUI_MSG *msg)
{
  WSHDR *ws;
  char *s, *d, tmp[132];
  int cur_x_st;
  int len, l;
  int is_any_change=0;
  if (msg->keys==0xFFF)
  {
    cur_x_st=(int)EDIT_GetUserPointer(data);
    EDITCONTROL ec;
    ExtractEditControl(data,2,&ec);   // Комментарий
    ws=ec.pWS;
    
    s=GetXStatusStr(cur_x_st*3,&len);
    d=tmp;

    if (s)
    {
      l=ws->wsbody[0];
      for (int i=0; i<l; i++) 
      {
        *d++=char16to8(ws->wsbody[i+1]);
      }
      *d=0;
      if (len!=l || strncmp(s,tmp,len))
      {
        ReplaceStr(&XStatusText,s-XStatusText,len,tmp,l);
        is_any_change=1;
      }
    }

    ExtractEditControl(data,4,&ec);   // Короткий икс статус
    ws=ec.pWS;
    
    s=GetXStatusStr(cur_x_st*3+1,&len);
    d=tmp;

    if (s)
    {
      l=ws->wsbody[0];
      for (int i=0; i<l; i++) 
      {
        *d++=char16to8(ws->wsbody[i+1]);
      }
      *d=0;
      if (len!=l || strncmp(s,tmp,len))
      {
        ReplaceStr(&XStatusText,s-XStatusText,len,tmp,l);
        is_any_change=1;
      }
    }
    
    ExtractEditControl(data,6,&ec);   // Длинный икс статус
    ws=ec.pWS;
    
    s=GetXStatusStr(cur_x_st*3+2,&len);
    d=tmp;

    if (s)
    {
      l=ws->wsbody[0];
      for (int i=0; i<l; i++) 
      {
        *d++=char16to8(ws->wsbody[i+1]);
      }
      *d=0;
      if (len!=l || strncmp(s,tmp,len))
      {
        ReplaceStr(&XStatusText,s-XStatusText,len,tmp,l);
        is_any_change=1;
      }
    }
    
    if (is_any_change)
    {
      SaveXStatusText();
    }
    return (1);
  }
  return (0);
}

void edit_xstatus_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Save!"};
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
  }
}

HEADER_DESC edit_xstatus_hdr={0,0,0,0,NULL,NULL,LGP_NULL};

INPUTDIA_DESC edit_xstatus_desc =
{
  1,
  edit_xstatus_onkey,
  edit_xstatus_ghook,
  (void *)edit_xstatus_locret,
  0,
  &edit_x_skt,
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


static void EditXStatus(int xstatus)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  char *s;
  int len;
  int c;
   
  eq=AllocEQueue(ma,mfree_adr());    
  WSHDR *ews=AllocWS(128);
  ascii2ws(ews, (char*)lgpData[LGP_Comment] );   // Коментарий
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);    //1
  
  CutWSTR(ews,0);
  s=GetXStatusStr(xstatus*3, &len);
  if (s)
  {
    while((c=*s++) && len)
    {
      wsAppendChar(ews,char8to16(c));
      len--;
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,20);
  AddEditControlToEditQend(eq,&ec,ma);   //2
  
  ascii2ws(ews,"Short X:");      // Короткий Икс Статус
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);   //3
  
  CutWSTR(ews,0);
  s=GetXStatusStr(xstatus*3+1, &len);
  if (s)
  {
    while((c=*s++) && len)
    {
      wsAppendChar(ews,char8to16(c));
      len--;
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);   //4
  
  ascii2ws(ews,"Large X:");     // Длинный Икс Статус
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);   //5
  
  CutWSTR(ews,0);
  s=GetXStatusStr(xstatus*3+2, &len);
  if (s)
  {
    while((c=*s++) && len)
    {
      wsAppendChar(ews,char8to16(c));
      len--;
    }
  }
  PrepareEditControl(&ec);
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,ews,128);
  AddEditControlToEditQend(eq,&ec,ma);   //6
  
  FreeWS(ews);
  patch_header(&edit_xstatus_hdr);
  patch_input(&edit_xstatus_desc);
  CreateInputTextDialog(&edit_xstatus_desc,&edit_xstatus_hdr,eq,1,(void *)xstatus);  
}

static int xst_onkey(void *data, GUI_MSG *msg)
{
  int i;
  i=GetCurMenuItem(data);
  if (msg->keys==0x18)
  {
    EditXStatus(i);
    return(0);
  }
  if (msg->keys==0x3D)
  {
    Change_XStatus(i);
    return(1);
  }
  return (0);
}

static void xst_ghook(void *data, int cmd)
{
  PNGTOP_DESC *pltop=PNG_TOP();
  if (cmd==9)
  {
    pltop->dyn_pltop=NULL;
  }
  if (cmd==0x0A)
  {
    pltop->dyn_pltop=XStatusesImgList;
    DisableIDLETMR();
    //Загрузка текста при фокусе
    LoadXStatusText();
  }
}

static void xst_itemh(void *data, int curitem, void *unk)
{
  void *item=AllocMLMenuItem(data);
  WSHDR ws1loc, *ws1, *ws2;
  unsigned short num[128];
  WSHDR ws3loc, *ws3, *ws4;
  unsigned short num3[128];
  char ss[128];
  char *s;
  int l;
  extern const char percent_t[];
  
  ws1=CreateLocalWS(&ws1loc,num,128);
  ws3=CreateLocalWS(&ws3loc,num3,128);
  
  if (s=GetXStatusStr(curitem*3+1,&l))
  {
    memset(ss,0,128);
    if (l>127) l=127;
    strncpy(ss,s,l);
    wsprintf(ws1,percent_t,ss);
  }
  else
  {
    wsprintf(ws1,"Short XS %d",curitem);
  }
  if (s=GetXStatusStr(curitem*3+2,&l))
  {
    memset(ss,0,128);
    if (l>127) l=127;
    strncpy(ss,s,l);
    wsprintf(ws3,percent_t,ss);
  }
  else
  {
    wsprintf(ws3,"Large XS %d",curitem);
  }
  ws2=AllocMenuWS(data,ws1->wsbody[0]);

  wstrcpy(ws2,ws1);
  ws4=AllocMenuWS(data,ws3->wsbody[0]);
  wstrcpy(ws4,ws3);
  SetMenuItemIconArray(data, item, XStatusesIconArray+curitem);
  SetMLMenuItemText(data, item, ws2, ws4, curitem);
}

static SOFTKEY_DESC xst_menu_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

static const SOFTKEYSTAB xst_menu_skt=
{
  xst_menu_sk,0
};

static HEADER_DESC xst_menuhdr={0,0,0,0,NULL,NULL,LGP_NULL};

static const ML_MENU_DESC xst_menu=
{
  8,xst_onkey,xst_ghook,NULL,
  st_menusoftkeys,
  &xst_menu_skt,
  0x11,
  xst_itemh,
  NULL,
  NULL,
  0,
  1
};

void DispXStatusChangeMenu(void)
{
  patch_header(&xst_menuhdr);
  *((int **)(&xst_menuhdr.icon))=XStatusesIconArray+CurrentXStatus;
  
  //Инициализация ленгпака
  xst_menuhdr.lgp_id=(int)lgpData[LGP_ChgXStatus];
  edit_xstatus_hdr.lgp_id=(int)lgpData[LGP_MnuXStatus];
  xst_menu_sk[0].lgp_id=(int)lgpData[LGP_Text];
  xst_menu_sk[1].lgp_id=(int)lgpData[LGP_Back];
 
  CreateMultiLinesMenu(0,0,&xst_menu,&xst_menuhdr,CurrentXStatus,total_xstatuses);
}

void LoadXStatusText(void)
{
  FSTATS stat;
  const char _slash[]="\\";
  char fn[256];
  int f;
  unsigned int ul;
  int fsize;
  char *p, *s;
  int c;
  FreeXStatusText();
  strcpy(fn,TEMPLATES_PATH);
  if (fn[strlen(fn)-1]!='\\') strcat(fn,_slash);
  strcat(fn,XS_FILE_NAME);
  if (GetFileStats(fn,&stat,&ul)==-1) return;
  if ((fsize=stat.size)<=0) return;
  if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return;
  p=XStatusText=malloc(fsize+2);
  s=p+1;
  s[fread(f,s,fsize,&ul)]=0;
  fclose(f,&ul);
  while((c=*s++)!=0)
  {
    if (c==10)
    {
      c=13;
      if (*s==13) s++;   // пропускаем
    }
    else if (c==13)
    {
      if (*s==10) s++;  // пропускаем
    }
    *p++=c;
  }
  *p=0;
}

void SaveXStatusText(void)
{
  int f;
  char fn[256];
  const char _slash[]="\\";
  unsigned int ul;
  if (!XStatusText) return;
  strcpy(fn,TEMPLATES_PATH);
  if (fn[strlen(fn)-1]!='\\') strcat(fn,_slash);
  strcat(fn,XS_FILE_NAME);
  if ((f=fopen(fn,A_ReadWrite+A_Create+A_Truncate+A_BIN,P_READ+P_WRITE,&ul))==-1) return;
  fwrite(f,XStatusText,strlen(XStatusText),&ul);
  fclose(f,&ul);
}

void FreeXStatusText(void)
{
  mfree(XStatusText);
  XStatusText=NULL;
}

char *GetXStatusStr(int n, int *len)
{
  int l=0;
  int c;
  char *p=XStatusText;
  char *pp;
  if (len) *len=0;
  if (!p) return p;
  while(n)
  {
    while((c=*p++)>=32);
    if (!c) return NULL;
    n--;
  }
  pp=p;
  while((*pp++)>=32) l++;
  if (len) *len=l;
  return p;
}
