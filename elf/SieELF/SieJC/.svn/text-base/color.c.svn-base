#include "../inc/swilib.h"
#include "color.h"
#include "string_util.h"
#include "lang.h"
#include "rect_patcher.h"

extern const char color_PATH[];
char * cur_color_name;

// Цвета

RGBA MAINBG_NOT_CONNECTED;
RGBA MAINBG_CONNECTED;
RGBA MAINBG_ERROR;
RGBA MAINFONT_NOT_CONNECTED = {200, 200, 200, 100};
RGBA MAINFONT_CONNECTED;
RGBA MAINFONT_ERROR;
RGBA MESSAGEWIN_BGCOLOR;
RGBA MESSAGEWIN_TITLE_BGCOLOR;
RGBA MESSAGEWIN_TITLE_FONT;
RGBA MESSAGEWIN_MY_BGCOLOR;
RGBA MESSAGEWIN_CH_BGCOLOR;
RGBA MESSAGEWIN_GCHAT_BGCOLOR_1;
RGBA MESSAGEWIN_CURSOR_BGCOLOR;
RGBA MESSAGEWIN_GCHAT_BGCOLOR_2;
RGBA MESSAGEWIN_SYS_BGCOLOR; 
RGBA MESSAGEWIN_STATUS_BGCOLOR; 
RGBA MESSAGEWIN_CHAT_FONT;
RGBA CURSOR;
RGBA CURSOR_BORDER;        
RGBA CLIST_F_COLOR_0;        
RGBA CLIST_F_COLOR_1;        
RGBA CONTACT_BG_0;         
RGBA CONTACT_BG_1;
RGBA lineColor;    
RGBA borderColor;

RGBA OnlineColor;
RGBA ChatColor;
RGBA AwayColor;
RGBA XAColor;
RGBA DNDColor;
RGBA InvisibleColor;
RGBA OfflineColor;
RGBA ErrorColor;
RGBA SubscribeColor;
RGBA SubscribedColor;
RGBA UnsubscribeColor;
RGBA UnsubscribedColor;

RGBA PRES_COLORS[PRES_COUNT];

/* 
  Инициализация цветов.
  В параметр нужно передать буффер конфига цветов
*/
void InitColor(char * color_cfg)
{
  CURSOR.r = color_cfg [44];
  CURSOR.g = color_cfg [45];
  CURSOR.b = color_cfg [46];
  CURSOR.a = color_cfg [47];

  OnlineColor.r = color_cfg [1196];
  OnlineColor.g = color_cfg [1197];
  OnlineColor.b = color_cfg [1198];
  OnlineColor.a = color_cfg [1199];
  PRES_COLORS[0] = OnlineColor;

  ChatColor.r = color_cfg [1244];
  ChatColor.g = color_cfg [1245];
  ChatColor.b = color_cfg [1246];
  ChatColor.a = color_cfg [1247];
  PRES_COLORS[1] = ChatColor;

  AwayColor.r = color_cfg [1292];
  AwayColor.g = color_cfg [1293];
  AwayColor.b = color_cfg [1294];
  AwayColor.a = color_cfg [1295];
  PRES_COLORS[2] = AwayColor;

  XAColor.r = color_cfg [1340];
  XAColor.g = color_cfg [1341];
  XAColor.b = color_cfg [1342];
  XAColor.a = color_cfg [1343];
  PRES_COLORS[3] = XAColor;

  DNDColor.r = color_cfg [1388];
  DNDColor.g = color_cfg [1389];
  DNDColor.b = color_cfg [1390];
  DNDColor.a = color_cfg [1391];
  PRES_COLORS[4] = DNDColor;

  InvisibleColor.r = color_cfg [1436];
  InvisibleColor.g = color_cfg [1437];
  InvisibleColor.b = color_cfg [1438];
  InvisibleColor.a = color_cfg [1439];
  PRES_COLORS[5] = InvisibleColor;

  OfflineColor.r = color_cfg [1484];
  OfflineColor.g = color_cfg [1485];
  OfflineColor.b = color_cfg [1486];
  OfflineColor.a = color_cfg [1487];
  PRES_COLORS[6] = OfflineColor;

  ErrorColor.r = color_cfg [1532];
  ErrorColor.g = color_cfg [1533];
  ErrorColor.b = color_cfg [1534];
  ErrorColor.a = color_cfg [1535];
  PRES_COLORS[7] = ErrorColor;

  SubscribeColor.r = color_cfg [1580];
  SubscribeColor.g = color_cfg [1581];
  SubscribeColor.b = color_cfg [1582];
  SubscribeColor.a = color_cfg [1583];
  PRES_COLORS[8] = SubscribeColor;

  SubscribedColor.r = color_cfg [1628];
  SubscribedColor.g = color_cfg [1629];
  SubscribedColor.b = color_cfg [1630];
  SubscribedColor.a = color_cfg [1631];
  PRES_COLORS[9] = SubscribedColor;

  UnsubscribeColor.r = color_cfg [1676];
  UnsubscribeColor.g = color_cfg [1677];
  UnsubscribeColor.b = color_cfg [1678];
  UnsubscribeColor.a = color_cfg [1679];
  PRES_COLORS[10] = UnsubscribeColor;

  UnsubscribedColor.r = color_cfg [1724];
  UnsubscribedColor.g = color_cfg [1725];
  UnsubscribedColor.b = color_cfg [1726];
  UnsubscribedColor.a = color_cfg [1727];
  PRES_COLORS[11] = UnsubscribedColor;

  CURSOR_BORDER.r = color_cfg [92];
  CURSOR_BORDER.g = color_cfg [93];
  CURSOR_BORDER.b = color_cfg [94];
  CURSOR_BORDER.a = color_cfg [95];
  
  CLIST_F_COLOR_0.r = color_cfg [140];
  CLIST_F_COLOR_0.g = color_cfg [141];
  CLIST_F_COLOR_0.b = color_cfg [142];
  CLIST_F_COLOR_0.a = color_cfg [143];
  
  CLIST_F_COLOR_1.r = color_cfg [188];
  CLIST_F_COLOR_1.g = color_cfg [189];
  CLIST_F_COLOR_1.b = color_cfg [190];
  CLIST_F_COLOR_1.a = color_cfg [191];
  
  CONTACT_BG_0.r = color_cfg [236];
  CONTACT_BG_0.g = color_cfg [237];
  CONTACT_BG_0.b = color_cfg [238];
  CONTACT_BG_0.a = color_cfg [239];
  
  CONTACT_BG_1.r = color_cfg [284];
  CONTACT_BG_1.g = color_cfg [285];
  CONTACT_BG_1.b = color_cfg [286];
  CONTACT_BG_1.a = color_cfg [287];
  
  lineColor.r = color_cfg [332];
  lineColor.g = color_cfg [333];
  lineColor.b = color_cfg [334];
  lineColor.a = color_cfg [335];
  
  borderColor.r = color_cfg [380];
  borderColor.g = color_cfg [381];
  borderColor.b = color_cfg [382];
  borderColor.a = color_cfg [383];
  
  MAINBG_NOT_CONNECTED.r = color_cfg [428];
  MAINBG_NOT_CONNECTED.g = color_cfg [429];
  MAINBG_NOT_CONNECTED.b = color_cfg [430];
  MAINBG_NOT_CONNECTED.a = color_cfg [431];
  
  MAINBG_CONNECTED.r = color_cfg [476];
  MAINBG_CONNECTED.g = color_cfg [477];
  MAINBG_CONNECTED.b = color_cfg [478];
  MAINBG_CONNECTED.a = color_cfg [479];
  
  MAINBG_ERROR.r = color_cfg [524];
  MAINBG_ERROR.g = color_cfg [525];
  MAINBG_ERROR.b = color_cfg [526];
  MAINBG_ERROR.a = color_cfg [527];
  
  MAINFONT_CONNECTED.r = color_cfg [572];
  MAINFONT_CONNECTED.g = color_cfg [573];
  MAINFONT_CONNECTED.b = color_cfg [574];
  MAINFONT_CONNECTED.a = color_cfg [575];
  
  MAINFONT_ERROR.r = color_cfg [620];
  MAINFONT_ERROR.g = color_cfg [621];
  MAINFONT_ERROR.b = color_cfg [622];
  MAINFONT_ERROR.a = color_cfg [623];
  
  MESSAGEWIN_BGCOLOR.r = color_cfg [668];
  MESSAGEWIN_BGCOLOR.g = color_cfg [669];
  MESSAGEWIN_BGCOLOR.b = color_cfg [670];
  MESSAGEWIN_BGCOLOR.a = color_cfg [671];
  
  MESSAGEWIN_CURSOR_BGCOLOR.r = color_cfg [908];
  MESSAGEWIN_CURSOR_BGCOLOR.g = color_cfg [909];
  MESSAGEWIN_CURSOR_BGCOLOR.b = color_cfg [910];
  MESSAGEWIN_CURSOR_BGCOLOR.a = color_cfg [911];
  
  MESSAGEWIN_TITLE_BGCOLOR.r = color_cfg [716];
  MESSAGEWIN_TITLE_BGCOLOR.g = color_cfg [717];
  MESSAGEWIN_TITLE_BGCOLOR.b = color_cfg [718];
  MESSAGEWIN_TITLE_BGCOLOR.a = color_cfg [719];
  
  MESSAGEWIN_TITLE_FONT.r = color_cfg [764];
  MESSAGEWIN_TITLE_FONT.g = color_cfg [765];
  MESSAGEWIN_TITLE_FONT.b = color_cfg [766];
  MESSAGEWIN_TITLE_FONT.a = color_cfg [767];
  
  MESSAGEWIN_MY_BGCOLOR.r = color_cfg [812];
  MESSAGEWIN_MY_BGCOLOR.g = color_cfg [813];
  MESSAGEWIN_MY_BGCOLOR.b = color_cfg [814];
  MESSAGEWIN_MY_BGCOLOR.a = color_cfg [815];
  
  MESSAGEWIN_CH_BGCOLOR.r = color_cfg [860];
  MESSAGEWIN_CH_BGCOLOR.g = color_cfg [861];
  MESSAGEWIN_CH_BGCOLOR.b = color_cfg [862];
  MESSAGEWIN_CH_BGCOLOR.a = color_cfg [863];
  
  MESSAGEWIN_GCHAT_BGCOLOR_1.r = color_cfg [956];
  MESSAGEWIN_GCHAT_BGCOLOR_1.g = color_cfg [957];
  MESSAGEWIN_GCHAT_BGCOLOR_1.b = color_cfg [958];
  MESSAGEWIN_GCHAT_BGCOLOR_1.a = color_cfg [959];
  
  MESSAGEWIN_GCHAT_BGCOLOR_2.r = color_cfg [1004];
  MESSAGEWIN_GCHAT_BGCOLOR_2.g = color_cfg [1005];
  MESSAGEWIN_GCHAT_BGCOLOR_2.b = color_cfg [1006];
  MESSAGEWIN_GCHAT_BGCOLOR_2.a = color_cfg [1007];
  
  MESSAGEWIN_SYS_BGCOLOR.r = color_cfg [1052];
  MESSAGEWIN_SYS_BGCOLOR.g = color_cfg [1053];
  MESSAGEWIN_SYS_BGCOLOR.b = color_cfg [1054];
  MESSAGEWIN_SYS_BGCOLOR.a = color_cfg [1055];
  
  MESSAGEWIN_STATUS_BGCOLOR.r = color_cfg [1100];
  MESSAGEWIN_STATUS_BGCOLOR.g = color_cfg [1101];
  MESSAGEWIN_STATUS_BGCOLOR.b = color_cfg [1102];
  MESSAGEWIN_STATUS_BGCOLOR.a = color_cfg [1103];
  
  MESSAGEWIN_CHAT_FONT.r = color_cfg [1148];
  MESSAGEWIN_CHAT_FONT.g = color_cfg [1149];
  MESSAGEWIN_CHAT_FONT.b = color_cfg [1150];
  MESSAGEWIN_CHAT_FONT.a = color_cfg [1151];  
}

/* 
  Чтение конфига цветов
  В параметр нужно передать имя нужного конфига
*/
int ReadColor(const char * fname)
{
  unsigned int io_error = NULL;
  int hFile;
  FSTATS fstat;
  
  char * color_file = (char *)malloc(strlen(color_PATH) + strlen(cur_color_name) + 16);
  strcpy(color_file, color_PATH);
  strcat(color_file, fname);
  strcat(color_file, ".bcfg");
  
  if (GetFileStats(color_file, &fstat, &io_error) != -1)
  {
    if (!io_error)
    {
      if ((hFile = fopen(color_file, A_ReadOnly + A_BIN, P_READ, &io_error)) != -1)
      {
        if (!io_error)
        {
          char * buf = (char *)malloc(fstat.size + 1);
          fread(hFile, buf, fstat.size, &io_error);
          fclose(hFile, &io_error);
          InitColor(buf);
          mfree(buf);
          mfree(color_file);
          return 1;
        }
      }
    }
  }
  mfree(color_file);
  return 0;
}

/* Меню выбора цветовой схемы */
typedef struct
{
  void * next;
  char cfgname[64];
  char fullpath[128];
}SEL_COLOR;

int select_color_menu_onkey(void *gui, GUI_MSG *msg)
{
  SEL_COLOR * sbtop = MenuGetUserPointer(gui);
  if (msg->keys==0x3D)
  {
    int i=GetCurMenuItem(gui);
    for (int n = 0; n != i; n ++)
      sbtop = sbtop->next;
    if (sbtop)
    {
      if (cur_color_name) mfree(cur_color_name);
      cur_color_name = (char *)malloc(32);
      strcpy(cur_color_name, sbtop->cfgname);
      if (ReadColor(cur_color_name))
        return (1);
    }
  }
  if (msg->keys==0x18)
  {
    int i=GetCurMenuItem(gui);
    for (int n = 0; n != i; n ++)
      sbtop = sbtop->next;
    if (sbtop)
    {
      int len = strlen(sbtop->fullpath);
      WSHDR * ws = AllocWS(len + 4);
      str_2ws(ws, sbtop->fullpath, len);
      ExecuteFile(ws, 0, 0);
      FreeWS(ws);
    }
  }
  return (0);
}

void select_color_menu_ghook(void *gui, int cmd)
{
  SEL_COLOR *sbtop = MenuGetUserPointer(gui);
  if (cmd == TI_CMD_DESTROY)
  {
    while(sbtop)
    {
      SEL_COLOR *sb = sbtop;
      sbtop = sbtop->next;
      mfree(sb);
    }    
  }
  if (cmd == TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}

extern int icon_array[2];

void select_color_menu_iconhndl(void *gui, int cur_item, void *user_pointer)
{
  SEL_COLOR * sbtop = user_pointer;
  WSHDR * ws;
  void * item = AllocMenuItem(gui);
  for (int n = 0; n != cur_item; n ++)
    sbtop = sbtop->next;
  if (sbtop)
  {
    int len = strlen(sbtop->cfgname);
    ws = AllocMenuWS(gui, len + 4);
    str_2ws(ws, sbtop->cfgname, len);
    SetMenuItemIconArray(gui, item, icon_array + (strcmp(sbtop->cfgname, cur_color_name)?1:0));
  }
  else
  {
    ws = AllocMenuWS(gui, 10);
    ascii2ws(ws, "Error");
    SetMenuItemIconArray(gui, item, icon_array);
  }
  SetMenuItemText(gui, item, ws, cur_item);
}

int select_color_menu_softkeys[]={0,1,2};

SOFTKEY_DESC select_color_menu_sk[]=
{
  {0x0018,0x0000,(int)LG_EDIT},
  {0x0001,0x0000,(int)LG_BACK},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB select_color_menu_skt=
{
  select_color_menu_sk,0
};

HEADER_DESC select_color_menu_header = {0, 0, 0, 0, NULL, (int)LG_COLOR, LGP_NULL};

MENU_DESC select_color_menu_struct=
{
  8, select_color_menu_onkey, select_color_menu_ghook, NULL,
  select_color_menu_softkeys,
  &select_color_menu_skt,
  0x11,
  select_color_menu_iconhndl,
  NULL,   //Items
  NULL,   //Procs
  0   //n
};

void ShowSelectColorMenu()
{
  unsigned int err;
  DIR_ENTRY de;
  SEL_COLOR *sbtop = NULL;
  SEL_COLOR *sb;
  int n_bcfg=0;
  char str[128];
  strcpy(str, color_PATH);
  strcat(str, "*.bcfg");
  if (FindFirstFile(&de, str, &err))
  {
    do
    {
      if (!(de.file_attr & FA_DIRECTORY))
      {
        sb = malloc(sizeof(SEL_COLOR));
        strcpy(sb->fullpath, color_PATH);
        strcat(sb->fullpath, de.file_name);
        strcpy(sb->cfgname, de.file_name);
        sb->cfgname[strlen(de.file_name) - 5] = NULL;
        sb->next = NULL;
        if (sbtop)
        {
          SEL_COLOR * sbr, * sbt;
          sbr = (SEL_COLOR *)&sbtop;
          sbt = sbtop;
          while(stricmp(sbt->cfgname, sb->cfgname) < 0)
          {
            sbr = sbt;
            sbt = sbt->next;
            if (!sbt) break;
          }
          sb->next = sbt;
          sbr->next = sb;
        }
        else
        {
          sbtop = sb;
        }
        n_bcfg++;
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  icon_array[0]=GetPicNByUnicodeSymbol(CBOX_CHECKED);
  icon_array[1]=GetPicNByUnicodeSymbol(CBOX_UNCHECKED);
  patch_header(&select_color_menu_header);
  CreateMenu(0, 0, &select_color_menu_struct, &select_color_menu_header, 0, n_bcfg, sbtop, 0);
}
