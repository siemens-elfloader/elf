#include "..\..\inc\swilib.h"
#include "..\mailclient.h"


#pragma inline
void patch_rect(RECT* rc)
{
  StoreXYXYtoRECT(rc,0,YDISP,ScreenW()-1,ScreenH()-1);
}

const char *c_states[]=
{
  "Disconnected",
  "Verificating user",
  "Verificating pass",
  "Get stat",
  "Create UIDL list",
  "Create list",  
  "Process List",
  "Receive Headers",
  "Receive Mail",   
  "Delete Mail"
};

extern POP_STAT *pop_stat;
extern volatile int daemon_present;
extern volatile int options_menu_id;
extern void ascii2ws(WSHDR *ws, const char *s);
extern void send_req_checkmailbox(void);
extern void send_req_stopcheck(void);

volatile int stat_gui_id;
typedef struct
{
  GUI gui;
  WSHDR *ws1;
}MAIN_GUI;


void method0(MAIN_GUI *data)
{ 
  unsigned int scr_w=ScreenW();
  unsigned int scr_h=ScreenH();
  DrawRoundedFrame(0,YDISP,scr_w-1,scr_h-1,0,0,0,
		   GetPaletteAdrByColorIndex(0),
		   GetPaletteAdrByColorIndex(20));
  if (daemon_present==-1)
  {
    ascii2ws(data->ws1,"Daemon not runned!");
    DrawString(data->ws1,3,3+YDISP,scr_w-4,scr_h-4-GetFontYSIZE(FONT_MEDIUM),FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  }
  else
  {
    wsprintf(data->ws1,"State: %d POPState: %d\n%t\n%t",pop_stat->connect_state,
             pop_stat->pop_state,c_states[pop_stat->pop_state],pop_stat->log);
    DrawString(data->ws1,3,3+YDISP,scr_w-4,scr_h-4-GetFontYSIZE(FONT_MEDIUM),FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    
    wsprintf(data->ws1,"send/recv bytes: %u/%u\nReceived: %u/%u\nDeleted: %u",pop_stat->total_send,pop_stat->total_recv,
             pop_stat->pop3_recv,pop_stat->in_pop3,pop_stat->pop3_del);
    DrawString(data->ws1,3,scr_h/3+YDISP,scr_w-4,scr_h-4-GetFontYSIZE(FONT_MEDIUM),FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));  
  }
   
  ascii2ws(data->ws1,"Stop");
  DrawString(data->ws1,3,scr_h-4-GetFontYSIZE(FONT_MEDIUM),(scr_w>>1)-1,scr_h-4,FONT_MEDIUM,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
  ascii2ws(data->ws1,"Close");
  DrawString(data->ws1,(scr_w>>1),scr_h-4-GetFontYSIZE(FONT_MEDIUM),scr_w-4,scr_h-4,FONT_MEDIUM,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

void method1(MAIN_GUI *data,void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

void method2(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  data->gui.state=0;
}

void method3(MAIN_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void method4(MAIN_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

int method5(MAIN_GUI *data,GUI_MSG *msg)
{
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case LEFT_SOFT:
      send_req_stopcheck();
      break;
      
    case RIGHT_SOFT:
      if (pop_stat->connect_state==0 || daemon_present==-1)
        return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
      return (3);
      
      
    case GREEN_BUTTON:
      send_req_checkmailbox();
      break;
    }
  }
  return(0);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)kill_data, //method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

int create_gui()
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  stat_gui_id=CreateGUI(main_gui);
  if (options_menu_id) GeneralFunc_flag1(options_menu_id,1);
  return stat_gui_id;
}
