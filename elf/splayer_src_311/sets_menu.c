#include "../inc/swilib.h"
#include "../inc/stdbool.h"
#include "main.h"
#include "langpack.h"
#include "mainmenu.h"
#include "sets_menu.h"

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
extern const char PIC_DIR[];
extern const char EXENAME[];   // SPlayer cfg editor.elf
char cfgxname[256];
extern bool EditPL;
/*
#define MAX_SETS_ITEMS 4

#define SET_EDIT_PL        1
#define COORDINATES        2
#define COLOURS            3
#define REFRESH            4

int Sets_MenuID;
int Req_Close_Sets_Menu=0;
char Menu_Contents[MAX_SETS_ITEMS];
int stS_ICONS[MAX_SETS_ITEMS+1];

int setsmenusoftkeys[]={0,1,2};
HEADER_DESC sets_menuhdr={0,0,0,0,NULL,(int)LG_Sets_Menu,LGP_NULL};
SOFTKEY_DESC sets_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_SELECT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB sets_menu_skt=
{
  sets_menu_sk,0
};

void sets_menu_iconhndl(void *data, int curitem, void *unk);

void sets_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)  // onFocus
  {
    DisableIDLETMR();
    if(Req_Close_Sets_Menu)
    {
      Req_Close_Sets_Menu=0;
      GeneralFunc_flag1(Sets_MenuID,1);
    }
  }
}
*/
/*
Обработчик нажатий клавиш меню. Отсюда следует вызывать необходимые действия

*//*
int sets_menu_onkey(void *data, GUI_MSG *msg)
{
  int i=GetCurMenuItem(data);
  if(msg->keys==0x18 || msg->keys==0x3D)
  {
    switch(Menu_Contents[i])
    {
    case SET_EDIT_PL:
      {
        EditPL=!(EditPL);
        RefreshGUI();
        GeneralFunc_flag1(Sets_MenuID,1);
        break;
      }
      
    case COORDINATES:
      {
        WSHDR *ws=AllocWS(256);
        str_2ws(ws,EXENAME,strlen(EXENAME)+1);
        sprintf(cfgxname,"%s%s",PIC_DIR,"skin.cfg");
        ExecuteFile(ws,0,(char*)cfgxname);
        FreeWS(ws);
        break;
      }

    case COLOURS:
      {
        WSHDR *ws=AllocWS(256);
        str_2ws(ws,EXENAME,strlen(EXENAME)+1);
        sprintf(cfgxname,"%s%s",PIC_DIR,"colour.cfg");
        ExecuteFile(ws,0,(char*)cfgxname);
        FreeWS(ws);
        break;
      }

    case REFRESH:
      {
        sprintf(cfgxname,"%s%s",PIC_DIR,"skin.cfg");
        load_skin(cfgxname);
        sprintf(cfgxname,"%s%s",PIC_DIR,"colour.cfg");
        load_skin(cfgxname);
        GeneralFunc_flag1(Sets_MenuID,1);
        break;
      }

    default:
      {
        MsgBoxError(1,(int)LG_Error_1);
      }
    }

    return 0; // Закрыть автоматически или нет   AAA
  }
  //  Req_Close_Sets_Menu = 1;
  return 0;
}

MENU_DESC sets_menu=
{
  8,sets_menu_onkey,sets_menu_ghook,NULL,
  setsmenusoftkeys,
  &sets_menu_skt,
  0x11, // 0x11 если надо меню с иконками, иначе 0x10
  sets_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  MAX_SETS_ITEMS   //n
};

extern int icon_array[2];

void sets_menu_iconhndl(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  char test_str[48];
  void *item=AllocMenuItem(data);
  strcpy(test_str,"(ошибка)");

  switch(Menu_Contents[curitem])
  {
  case SET_EDIT_PL:
    {
      strcpy(test_str,LG_SetEditPL);
      break;
    }
  case COORDINATES:
    {
      strcpy(test_str,LG_Coordinates);
      break;
    }
  case COLOURS:
    {
      strcpy(test_str,LG_Colours);
      break;
    }
  case REFRESH:
    {
      strcpy(test_str,LG_Refresh);
      break;
    }
  }
  ws=AllocMenuWS(data,strlen(test_str));
  wsprintf(ws,"%t",test_str);

  if(curitem==0) {SetMenuItemIconArray(data,item,icon_array+(EditPL?0:1));}
  else {SetMenuItemIconArray(data,item,stS_ICONS+Menu_Contents[curitem]);}
  SetMenuItemText(data,item,ws,curitem);
};

void Init_Icon_array()
{
  char coordinatespic[128];
  char colourspic[128];
  char refreshpic[128];
  strcpy(coordinatespic,PIC_DIR);strcat(coordinatespic,"coordinates.png");
  strcpy(colourspic,PIC_DIR);strcat(colourspic,"colours.png");
  strcpy(refreshpic,PIC_DIR);strcat(refreshpic,"refresh.png");
  
 // for(int i=0;i<=MAX_SETS_ITEMS;i++)stS_ICONS[i]=0;
  
#ifndef NO_PNG
  
 // stS_ICONS[SET_EDIT_PL]=
  stS_ICONS[COORDINATES]=(int)coordinatespic;
  stS_ICONS[COLOURS]=(int)colourspic;
  stS_ICONS[REFRESH]=(int)refreshpic;
  
#else
 // stS_ICONS[SET_EDIT_PL] = 0;
 // menuitems[SET_EDIT_PL].icon = stS_ICONS;
  stS_ICONS[COORDINATES] = 0;
  menuitems[COORDINATES].icon = S_ICONS+1;
  stS_ICONS[COLOURS] = 0;
  menuitems[COLOURS].icon = stS_ICONS+2;
  stS_ICONS[REFRESH] = 0;
  menuitems[REFRESH].icon = stS_ICONS+3;
#endif
}*/
/*
void InitMenuArray()
{
  for(int i=1;i<MAX_SETS_ITEMS;i++) {Menu_Contents[i]=0;}
}*/
/*
void Disp_Sets_Menu()
{
 // InitMenuArray();
  Init_Icon_array();
  
  Menu_Contents[0]=SET_EDIT_PL;
  Menu_Contents[1]=COORDINATES;
  Menu_Contents[2]=COLOURS;
  Menu_Contents[3]=REFRESH;
  
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  
  patch_rect(&sets_menuhdr.rc,0,YDISP,ScreenW()-1,HeaderH()+YDISP);
  Sets_MenuID=CreateMenu(0,0,&sets_menu,&sets_menuhdr,0,MAX_SETS_ITEMS,0,0);
}*/

#define MAX_ITEMS 4

int SetsMenu_ID;

void Set_Edit_PL()
{
  EditPL=!(EditPL);
  RefreshGUI();
  GeneralFuncF1(1);
}
      
void Coordinates()
{
  WSHDR *ws=AllocWS(256);
  str_2ws(ws,EXENAME,strlen(EXENAME)+1);
  sprintf(cfgxname,"%s%s",PIC_DIR,"skin.cfg");
  ExecuteFile(ws,0,(char*)cfgxname);
  FreeWS(ws);
}

void Colours()
{
  WSHDR *ws=AllocWS(256);
  str_2ws(ws,EXENAME,strlen(EXENAME)+1);
  sprintf(cfgxname,"%s%s",PIC_DIR,"colour.cfg");
  ExecuteFile(ws,0,(char*)cfgxname);
  FreeWS(ws);
}

void Refresh1()
{
  Refresh();
  GeneralFuncF1(1);
}

HEADER_DESC sets_menuhdr={0,0,131,21,NULL,NULL,LGP_NULL};

int sets_menusoftkeys[]={0,1,2};

extern int icon_array[2];
/*
static const char * const sets_menutexts[MAX_ITEMS]=
{
  LG_SetEditPL,
  LG_Coordinates,
  LG_Colours,
  LG_Refresh
};
*/

static char * sets_menutexts[MAX_ITEMS]=
{
  NULL,
  NULL,
  NULL,
  NULL
};

void *sets_menuprocs[MAX_ITEMS]={
                          (void *)Set_Edit_PL,
                          (void *)Coordinates,
                          (void *)Colours,
                          (void *)Refresh1
                         };

SOFTKEY_DESC sets_menu_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB sets_menu_skt=
{
  sets_menu_sk,0
};

int stS_ICONS[MAX_ITEMS];

void sets_menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  ws=AllocMenuWS(data,strlen(sets_menutexts[curitem]));
  wsprintf(ws,"%t",sets_menutexts[curitem]);
#ifndef NO_PNG
  switch(curitem)
  {
  case 0:
    SetMenuItemIconArray(data,item,icon_array+(EditPL?0:1));
    break;
  case 1:
    SetMenuItemIconArray(data,item,stS_ICONS+1);
    break;
  case 2:
    SetMenuItemIconArray(data,item,stS_ICONS+2);
    break;
  case 3:
    SetMenuItemIconArray(data,item,stS_ICONS+3);
    break;
  }
#else
  switch(curitem)
  {
  case 0:
    SetMenuItemIconArray(data,item,icon_array+(EditPL?0:1));
    break;
  }
#endif
  SetMenuItemText(data, item, ws, curitem);
}

void sets_menu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int sets_menu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(sets_menuprocs[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC sets_tmenu=
{
  8,sets_menu_keyhook,sets_menu_ghook,NULL,
  sets_menusoftkeys,
  &sets_menu_skt,
  0x11,
  sets_menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  MAX_ITEMS
};

/*
char coordinatespic[128];
char colourspic[128];
char refreshpic[128];
*/

#ifndef NO_PNG
char pic2[TOTAL_ITEMS_2][128];
#endif

void Disp_Sets_Menu()
{
#ifndef NO_PNG
  /*
  strcpy(coordinatespic,PIC_DIR);strcat(coordinatespic,"coordinates.png");
  strcpy(colourspic,PIC_DIR);strcat(colourspic,"colours.png");
  strcpy(refreshpic,PIC_DIR);strcat(refreshpic,"refresh.png");
  // Картинка В очередь
 // stS_ICONS[0] = (int);

  // Картинка Атрибуты
  stS_ICONS[1] = (int)coordinatespic;

  // Картинка Коордиаты
  stS_ICONS[2] = (int)colourspic;

  // Картинка Настройки
  stS_ICONS[3] = (int)refreshpic;
  */
  for(unsigned int i=0; i<TOTAL_ITEMS_2; i++)
  {
    strcpy(pic2[i],PIC_DIR);
    strcat(pic2[i],items2[i]);
    strcat(pic2[i],PNGEXT);
    stS_ICONS[i+1] = (int)pic2[i];
  }

#else
 // stS_ICONS[0] = 0;
 // menuitems[0].icon = stS_ICONS;
  /*
  stS_ICONS[1] = 0;
  menuitems[1].icon = stS_ICONS+1;
  stS_ICONS[2] = 0;
  menuitems[2].icon = stS_ICONS+2;
  stS_ICONS[3] = 0;
  menuitems[3].icon = stS_ICONS+3;
  */
/*  for(unsigned int i=1; i<TOTAL_ITEMS_2; i++)
  {
    stS_ICONS[i] = 0;
  }*/
#endif  
  
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  
//  patch_rect(&sets_menuhdr.rc,0,YDISP,ScreenW()-1,HeaderH()+YDISP);
  patch_header(&sets_menuhdr);
  SetsMenu_ID = CreateMenu(0,0,&sets_tmenu,&sets_menuhdr,0,MAX_ITEMS,0,0);
}

void initSetsMenuLangPack() //Инициализировать язык для Меню Инструментов - Vedan
{
  sets_menu_sk[0].lgp_id=(int)lgpData[LGP_SELECT];
  sets_menu_sk[1].lgp_id=(int)lgpData[LGP_BACK];
  sets_menuhdr.lgp_id=(int)lgpData[LGP_Sets_Menu];
  sets_menutexts[0]=(char *)lgpData[LGP_SetEditPL];
  sets_menutexts[1]=(char *)lgpData[LGP_Coordinates];
  sets_menutexts[2]=(char *)lgpData[LGP_Colours];
  sets_menutexts[3]=(char *)lgpData[LGP_Refresh];
}
