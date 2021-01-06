
#include "..\inc\swilib.h"
#include "dict.h"
#include "about.h"
#include "menu.h"
#include "ed_gui.h"
#include "rect_patcher.h"
#include <stdbool.h>

typedef struct
{
  GUI gui;
}MAIN_GUI;

extern int start_index;
extern int highlight_item;
extern char **index;
extern bool m_f_err;
extern char pre_inputword[128];
extern const int wordcount;
extern int screenh;
extern int screenw;
extern int is_ed_started;

//config
extern const char cfg_gui_bg_color[4];
extern const unsigned int cfg_gui_font;
extern const char cfg_gui_color[4];
extern const unsigned int cfg_gui_sk_font;
extern const char cfg_gui_sk_color[4];

extern const unsigned int cfg_showfreeram;

extern void kill_data(void *p, void (*func_p)(void *));


int open_entry_index = 9;
unsigned int MAINGUI_ID = 0;


void soft_key(void)
{
  WSHDR *wsl = AllocWS(16);
  WSHDR *wsr = AllocWS(16);
  WSHDR *wsm = AllocWS(16);
  wsprintf(wsl, "Menu");
  wsprintf(wsr, "Exit");
  wsprintf(wsm, "Input");
  DrawString(wsl,2,screenh-GetFontYSIZE(cfg_gui_sk_font),screenw,screenh,cfg_gui_sk_font,32,cfg_gui_sk_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(wsr,screenw-get_string_width(wsr,cfg_gui_sk_font)-4,screenh-GetFontYSIZE(cfg_gui_sk_font),screenw,screenh,cfg_gui_sk_font,32,cfg_gui_sk_color,GetPaletteAdrByColorIndex(23)); 
  DrawString(wsm,screenw/2-get_string_width(wsm,cfg_gui_sk_font)/2,screenh-GetFontYSIZE(cfg_gui_sk_font),screenw,screenh,cfg_gui_sk_font,32,cfg_gui_sk_color,GetPaletteAdrByColorIndex(23)); 
  FreeWS(wsl);
  FreeWS(wsr);
  FreeWS(wsm);
}


void onRedraw(MAIN_GUI *data)
{
  DrawRectangle(0,YDISP,screenw,screenh,0,cfg_gui_bg_color,cfg_gui_bg_color);
  soft_key();
  if(is_ed_started)
  {
    WSHDR *ws = AllocWS(512);
    if(m_f_err)
    {
      wsprintf(ws, "%t\0", "");
    }
    else
    {
      construct_entry_text(ws, index[open_entry_index], 1, 1, 1);
    }
    DrawString(ws,5,YDISP,screenw,screenh-SoftkeyH(),cfg_gui_font,32,cfg_gui_color,GetPaletteAdrByColorIndex(23));
    if(cfg_showfreeram) show_freeram();
    FreeWS(ws);
  }
  else
    about();
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  int keycode = msg->gbsmsg->submess;
	if ( msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
	{
    switch( keycode )
    {
    case RIGHT_BUTTON:
    case DOWN_BUTTON:
      if(is_ed_started)
      {
        if( open_entry_index < wordcount-1 )
        {   
          open_entry_index ++;
          REDRAW();
        }
      }
      break;
    case LEFT_BUTTON:
    case UP_BUTTON:
      if(is_ed_started)
      {
        if( open_entry_index > 0 )
        {   
          open_entry_index --;
          REDRAW();
        }   
      }
      break;
    case RIGHT_SOFT:
      quit();
      break;
    case LEFT_SOFT:
      create_menu();
      break;
#ifndef NEWSGOLD
    case RED_BUTTON:
#endif
    case ENTER_BUTTON:
      create_ed();
      break;
      
    default:
      break;
    }
	}
	return(0);
}


void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)kill_data,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};

const RECT Canvas={0,0,0,0};

int create_gui()
{
  if(is_ed_started) open_entry_index = start_index+highlight_item;
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	zeromem(main_gui,sizeof(MAIN_GUI));	
	patch_rect((RECT*)&Canvas,0,0,screenw-1,screenh-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
	MAINGUI_ID=CreateGUI(main_gui);
	return MAINGUI_ID;
}
