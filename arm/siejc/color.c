#include "../inc/swilib.h"
#include "color.h"
#include "string_util.h"
#include "lang.h"
#include "rect_patcher.h"
#include "conf_loader.h"

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
RGBA PRES_COLORS[PRES_COUNT];

/* 
  Инициализация цветов.
  В параметр нужно передать буффер конфига цветов
*/
RGBA Char4ToRGBA(const char in[4])
{
  RGBA result;
  result.r= in[0];
  result.g= in[1];
  result.b= in[2];
  result.a= in[3];
  return result;
}

void InitColor()
{
  extern const char CURSOR_c[];
  CURSOR = Char4ToRGBA(CURSOR_c);

  extern const char CURSOR_BORDER_c[];
  CURSOR_BORDER = Char4ToRGBA(CURSOR_BORDER_c);
  
  extern const char CLIST_F_COLOR_0_c[];
  CLIST_F_COLOR_0 = Char4ToRGBA(CLIST_F_COLOR_0_c);
  
  extern const char CLIST_F_COLOR_1_c[];
  CLIST_F_COLOR_1 = Char4ToRGBA(CLIST_F_COLOR_1_c);
  
  extern const char CONTACT_BG_0_c[];
  CONTACT_BG_0 = Char4ToRGBA(CONTACT_BG_0_c);
  
  extern const char CONTACT_BG_1_c[];
  CONTACT_BG_1 = Char4ToRGBA(CONTACT_BG_1_c);
  
//  extern const char lineColor_c[];
//  lineColor = Char4ToRGBA(lineColor_c);
  
//  extern const char borderColor_c[];
//  borderColor = Char4ToRGBA(borderColor_c);
  
  extern const char MAINBG_NOT_CONNECTED_c[];
  MAINBG_NOT_CONNECTED = Char4ToRGBA(MAINBG_NOT_CONNECTED_c);
  
  extern const char MAINBG_CONNECTED_c[];
  MAINBG_CONNECTED = Char4ToRGBA(MAINBG_CONNECTED_c);
  
  extern const char MAINBG_ERROR_c[];
  MAINBG_ERROR = Char4ToRGBA(MAINBG_ERROR_c);
  
  extern const char MAINFONT_CONNECTED_c[];
  MAINFONT_CONNECTED = Char4ToRGBA(MAINFONT_CONNECTED_c);
  
  extern const char MAINFONT_ERROR_c[];
  MAINFONT_ERROR = Char4ToRGBA(MAINFONT_ERROR_c);
  
  extern const char MESSAGEWIN_BGCOLOR_c[];
  MESSAGEWIN_BGCOLOR = Char4ToRGBA(MESSAGEWIN_BGCOLOR_c);
  
  extern const char MESSAGEWIN_CURSOR_BGCOLOR_c[];
  MESSAGEWIN_CURSOR_BGCOLOR = Char4ToRGBA(MESSAGEWIN_CURSOR_BGCOLOR_c);
  
  extern const char MESSAGEWIN_TITLE_BGCOLOR_c[];
  MESSAGEWIN_TITLE_BGCOLOR = Char4ToRGBA(MESSAGEWIN_TITLE_BGCOLOR_c);
  
  extern const char MESSAGEWIN_TITLE_FONT_c[];
  MESSAGEWIN_TITLE_FONT = Char4ToRGBA(MESSAGEWIN_TITLE_FONT_c);
  
  extern const char MESSAGEWIN_MY_BGCOLOR_c[];
  MESSAGEWIN_MY_BGCOLOR = Char4ToRGBA(MESSAGEWIN_MY_BGCOLOR_c);
  
  extern const char MESSAGEWIN_CH_BGCOLOR_c[];
  MESSAGEWIN_CH_BGCOLOR = Char4ToRGBA(MESSAGEWIN_CH_BGCOLOR_c);
  
  extern const char MESSAGEWIN_GCHAT_BGCOLOR_1_c[];
  MESSAGEWIN_GCHAT_BGCOLOR_1 = Char4ToRGBA(MESSAGEWIN_GCHAT_BGCOLOR_1_c);
  
  extern const char MESSAGEWIN_GCHAT_BGCOLOR_2_c[];
  MESSAGEWIN_GCHAT_BGCOLOR_2 = Char4ToRGBA(MESSAGEWIN_GCHAT_BGCOLOR_2_c);
  
  extern const char MESSAGEWIN_SYS_BGCOLOR_c[];
  MESSAGEWIN_SYS_BGCOLOR = Char4ToRGBA(MESSAGEWIN_SYS_BGCOLOR_c);
  
  extern const char MESSAGEWIN_STATUS_BGCOLOR_c[];
  MESSAGEWIN_STATUS_BGCOLOR = Char4ToRGBA(MESSAGEWIN_STATUS_BGCOLOR_c);
  
  extern const char MESSAGEWIN_CHAT_FONT_c[];
  MESSAGEWIN_CHAT_FONT = Char4ToRGBA(MESSAGEWIN_CHAT_FONT_c);
  
  extern const char OnlineColor_c[];
  PRES_COLORS[0] = Char4ToRGBA(OnlineColor_c);

  extern const char ChatColor_c[];
  PRES_COLORS[1] = Char4ToRGBA(ChatColor_c);

  extern const char AwayColor_c[];
  PRES_COLORS[2] = Char4ToRGBA(AwayColor_c);

  extern const char XAColor_c[];
  PRES_COLORS[3] = Char4ToRGBA(XAColor_c);

  extern const char DNDColor_c[];
  PRES_COLORS[4] = Char4ToRGBA(DNDColor_c);

  extern const char InvisibleColor_c[];
  PRES_COLORS[5] = Char4ToRGBA(InvisibleColor_c);

  extern const char OfflineColor_c[];
  PRES_COLORS[6] = Char4ToRGBA(OfflineColor_c);

  extern const char ErrorColor_c[];
  PRES_COLORS[7] = Char4ToRGBA(ErrorColor_c);

  extern const char SubscribeColor_c[];
  PRES_COLORS[8] = Char4ToRGBA(SubscribeColor_c);

  extern const char SubscribedColor_c[];
  PRES_COLORS[9] = Char4ToRGBA(SubscribedColor_c);

  extern const char UnsubscribeColor_c[];
  PRES_COLORS[10] = Char4ToRGBA(UnsubscribeColor_c);

  extern const char UnsubscribedColor_c[];
  PRES_COLORS[11] = Char4ToRGBA(UnsubscribedColor_c);
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
      if (InitColorSet(cur_color_name))
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
  if (cmd == TI_CMD_CREATE)
  {
    int cur_it=0;
    SEL_COLOR *sb = sbtop;
    while(sb)
    {
      if(!strcmp(sb->cfgname, cur_color_name)) break;
      sb = sb->next;
      cur_it++;
    }
    SetCursorToMenuItem(gui,cur_it);
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

int InitColorSet(const char *fname) //1 - удачно, 0 - неполучилось...
{
  extern const char color_PATH[];
  extern char * cur_color_name;
  int result = 0;
  char * color_file = (char *)malloc(strlen(color_PATH) + strlen(fname) + 16);
  strcpy(color_file, color_PATH);
  strcat(color_file, fname);
  strcat(color_file, ".bcfg");
  if (LoadColorSetData(color_file)<=0)
  {
    mfree(color_file);
    color_file = (char *)malloc(strlen(color_PATH) + 16);
    strcpy(color_file, color_PATH);
    strcat(color_file, "default.bcfg");
    if(LoadColorSetData(color_file)<=0)
    {
      if(SaveColorSetData(color_file))
      {
         if(LoadColorSetData(color_file)>0)
         {
           result = 1;
           ShowMSG(1,(int)"Create default color.");
         }
      };
    } else result = 1;
    if (cur_color_name) mfree(cur_color_name);
    cur_color_name = (char *)malloc(32);
    strcpy(cur_color_name, "default");
  } else result = 1;
  mfree(color_file);
  InitColor();
  return (result);
}
// EOL, EOF
