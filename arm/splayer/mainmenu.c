#include "../inc/swilib.h"
#include "main.h"
#include "mainmenu.h"
#include "langpack.h"
#include "lang.h"
#include "playlist.h"
#include "ID3Genres.h"
#include "item_info.h"
#include "sets_menu.h"
#include "FM.h"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

/*
 Тут делаю главное меню...
 Все работает норм! И графика пашет. Так что здесь пока можно ничего не трогать,
 пока новые пункты не добавлять...
*/
// Ну да ладно! это не помешает!

// Mr. Anderstand:
// Переделал все...

//==============================================================================
// ELKA Compatibility
//#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
//#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}
//==============================================================================
extern const char PIC_DIR[];
extern const char EXENAME[];   // SPlayer cfg editor.elf
char cfgname[256];
extern unsigned short EditPL;
extern int CurrentTrack[TCPL];
extern int CurrentPL;
extern unsigned int TC[TCPL];
void inp_locret(void){}
ID3TAGDATA *MainTag;

#define N_ITEMS 7

int MainMenu_ID;

void SetNextPlayedOn()
{
  SetNextPlayed();
  GeneralFuncF1(1);
}

// ID3 tags
void ShowID3()
{
  if(CurrentTrack[CurrentPL]!=0&&TC[CurrentPL]!=0)
  {
    MainTag=malloc(sizeof(ID3TAGDATA));
    ReadID3v1(GetCurrentTrack(CurrentTrack[CurrentPL]), MainTag);
    if(ReadID3v1(GetCurrentTrack(CurrentTrack[CurrentPL]), MainTag)) {Disp_Info(MainTag);}
    mfree(MainTag);
  }
  else
  {
    MsgBoxError(0,(int)lgpData[LGP_Is_not_selected]);
  }
  GeneralFuncF1(1);
}

void FM()
{
  ShowFM();
  GeneralFuncF1(1);
}

void Sets_Menu()
{
  Disp_Sets_Menu();
  GeneralFuncF1(1);
}

void Settings()   //Настройки  AAA
{
  extern const char *successed_config_filename;
  WSHDR *ws;
  ws=AllocWS(150);
  str_2ws(ws,successed_config_filename,128);
  ExecuteFile(ws,0,0);
  FreeWS(ws);
  GeneralFuncF1(1);
};

void AboutDlg()
{
  /*
  WSHDR * ews = AllocWS(512);
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  wsprintf(ews,"%t","SPlayer v 0.7.6.0\n\nАвторы (c):\nMr.Anderstand\nBlind007\nDemonGloom\n\nОформление (r):\nVedan");
  ConstructEditControl(&ec,1,0x40,ews,512);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&info_desc,&info_about,eq,1,0);
  FreeWS(ews);
  */
  ShowMSG(0,(int)"(r)\nIlya_ZX\n-Shadow-\nCaptain SISka\nVedan\nGanster and The_Zen\nDIEsel\nShadows");
  char info[128];
  sprintf(info,"SPlayer v%s\n(c): \nAnderstand\nBlind007\nDemonGloom",LG_Version);
  ShowMSG(0,(int)info);
  GeneralFuncF1(1);
};
/////////////////////////////////////////////Об эльфе///////////////////////////////////////////////////

void Exit_SPlayer()
{
  QuitCallbackProc(0);
}

HEADER_DESC menuhdr={0,0,131,21,NULL,NULL,LGP_NULL};

int mmenusoftkeys[]={0,1,2};

int icon_array[2];

/*
static const char * const menutexts[N_ITEMS]=
{
  LG_SetNextPlayed,
  LG_ShowID3,
  LG_FM,
  LG_Sets_Menu,
  LG_Settings,
  LG_AboutDlg,
  LG_Exit_SPlayer
};
*/
// Убрал постоянность, чтобы можно было изменить текст - Vedan
// И присваиваем текстовым значениям нули, потому что и так уже загружены
static char * menutexts[N_ITEMS]=
{
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL
};


/*
MENUITEM_DESC menuitems[N_ITEMS]=
{
  {0,(int)"Позиционирование",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Редактирование",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Настройки",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Об эльфе...",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {0,(int)"Выход",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};*/

void *menuprocs[N_ITEMS]={
                          (void *)SetNextPlayedOn,
                          (void *)ShowID3,
                          (void *)FM,
                          (void *)Sets_Menu,
                          (void *)Settings,
                          (void *)AboutDlg,
                          (void *)Exit_SPlayer
                         };
/*
static const MENUPROCS_DESC menuprocs[N_ITEMS]={
                          Coordinates,
                          SetEditPL,
                          Settings,
                          AboutDlg,
                          Exit_SPlayer
                         };*/

SOFTKEY_DESC mmenu_sk[]=
{
  {0x0018,0x0000,NULL},
  {0x0001,0x0000,NULL},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB mmenu_skt=
{
  mmenu_sk,0
};

int S_ICONS[N_ITEMS];

void menuitemhandler(void *data, int curitem, void *unk)
{
  WSHDR *ws;
  void *item=AllocMenuItem(data);
  ws=AllocMenuWS(data,strlen(menutexts[curitem]));
  wsprintf(ws,"%t",menutexts[curitem]);
  switch(curitem)
  {
  case 0:
    SetMenuItemIconArray(data,item,S_ICONS+0);
    break;
  case 1:
    SetMenuItemIconArray(data,item,S_ICONS+1);
    break;
  case 2:
    SetMenuItemIconArray(data,item,S_ICONS+2);
    break;
  case 3:
    SetMenuItemIconArray(data,item,S_ICONS+3);
    break;
  case 4:
    SetMenuItemIconArray(data,item,S_ICONS+4);
    break;
  case 5:
    SetMenuItemIconArray(data,item,S_ICONS+5);
    break;
  case 6:
    SetMenuItemIconArray(data,item,S_ICONS+6);
    break;
  }
  SetMenuItemText(data, item, ws, curitem);
}

void mmenu_ghook(void *data, int cmd)
{
  if (cmd==0x0A)
  {
    DisableIDLETMR();
  }
}

static int mmenu_keyhook(void *data, GUI_MSG *msg)
{
  if ((msg->keys==0x18)||(msg->keys==0x3D))
  {
    ((void (*)(void))(menuprocs[GetCurMenuItem(data)]))();
  }
  return(0);
}

static const MENU_DESC tmenu=
{
  8,mmenu_keyhook,mmenu_ghook,NULL,
  mmenusoftkeys,
  &mmenu_skt,
#ifndef NO_PNG
  0x11,
#else
  0x10,
#endif
  menuitemhandler,
  NULL, //menuitems,
  NULL, //menuprocs,
  N_ITEMS
};

//int S_ICONS[N_ITEMS];
/*
char setnexttrackpic[128];
char showid3pic[128];
char fmpic[128];
char setsmenupic[128];
char settingspic[128];
char aboutpic[128];
char exitpic[128];
*/

#ifndef NO_PNG
char pic[TOTAL_ITEMS][128];
#endif

void MM_Show()  // Люблю порядок... Ниче так килобайт почти из воздуха! :)   AAA
{
#ifndef NO_PNG
  /*
  // Картинка В очередь
  strcpy(setnexttrackpic,PIC_DIR);
  strcat(setnexttrackpic,"setnexttrack.png");
  S_ICONS[0] = (int)setnexttrackpic;

  // Картинка Атрибуты
  strcpy(showid3pic,PIC_DIR);
  strcat(showid3pic,"showid3.png");
  S_ICONS[1] = (int)showid3pic;

  // Картинка Файловый менеджер
  strcpy(fmpic,PIC_DIR);
  strcat(fmpic,"fm.png");
  S_ICONS[2] = (int)fmpic;
  
  // Картинка Коордиаты
  strcpy(setsmenupic,PIC_DIR);
  strcat(setsmenupic,"setsmenu.png");
  S_ICONS[3] = (int)setsmenupic;

  // Картинка Настройки
  strcpy(settingspic,PIC_DIR);
  strcat(settingspic,"settings.png");
  S_ICONS[4] = (int)settingspic;

  // Картинка Об эльфе...
  strcpy(aboutpic,PIC_DIR);
  strcat(aboutpic,"about.png");
  S_ICONS[5] = (int)aboutpic;

  // Картинка Выход
  strcpy(exitpic,PIC_DIR);
  strcat(exitpic,"exit.png");
  S_ICONS[6] = (int)exitpic;
*/
  for(unsigned int i=0; i<TOTAL_ITEMS; i++)
  {
    strcpy(pic[i],PIC_DIR);
    strcat(pic[i],items[i]);
    strcat(pic[i],PNGEXT);
    S_ICONS[i] = (int)pic[i];
  }
  
  
  
#else
  /*
  S_ICONS[0] = 0;
  menuitems[0].icon = S_ICONS;
  S_ICONS[1] = 0;
  menuitems[1].icon = S_ICONS+1;
  S_ICONS[2] = 0;
  menuitems[2].icon = S_ICONS+2;
  S_ICONS[3] = 0;
  menuitems[3].icon = S_ICONS+3;
  S_ICONS[4] = 0;
  menuitems[4].icon = S_ICONS+4;
  S_ICONS[5] = 0;
  menuitems[5].icon = S_ICONS+5;
  S_ICONS[6] = 0;
  menuitems[6].icon = S_ICONS+6;
  */
/*  for(unsigned int i=0; i<TOTAL_ITEMS; i++)
  {
    S_ICONS[i] = 0;
  }*/
#endif  
  
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  
  patch_header(&menuhdr);
  MainMenu_ID = CreateMenu(0,0,&tmenu,&menuhdr,0,N_ITEMS,0,0);
}

void initMainMenuLangPack() //Инициализировать язык для Главного Меню - Vedan
{
  mmenu_sk[0].lgp_id=(int)lgpData[LGP_SELECT];
  mmenu_sk[1].lgp_id=(int)lgpData[LGP_BACK];
  menuhdr.lgp_id=(int)lgpData[LGP_Menu];
  menutexts[0]=(char *)lgpData[LGP_SetNextPlayed];
  menutexts[1]=(char *)lgpData[LGP_ShowID3];
  menutexts[2]=(char *)lgpData[LGP_FM];
  menutexts[3]=(char *)lgpData[LGP_Sets_Menu];
  menutexts[4]=(char *)lgpData[LGP_Settings];
  menutexts[5]=(char *)lgpData[LGP_AboutDlg];
  menutexts[6]=(char *)lgpData[LGP_Exit_SPlayer];

}
