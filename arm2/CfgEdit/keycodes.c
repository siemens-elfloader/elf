#include "..\inc\swilib.h"
#include "rect_patcher.h"
extern void ascii2ws(WSHDR *ws, const char *s);
#define UTF16_FONT_SMALL_BOLD (0xE013)

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  unsigned int keyscancode;
  unsigned int *keymodecode;
  char needexit;
}KEY_GUI;

extern const char *key_names[63];


char str[10];
int code=0;
void OnReadraw_key(KEY_GUI *data)
{

  char black[4]={0x00,0x00,0x00,0x64};
  char white[4]={0xFF,0xFF,0xFF,0x64};
  char transparent[4]={0x00,0x00,0x00,0x00};

  int scr_w=ScreenW();
  int scr_h=ScreenH();
  int fsize=GetFontYSIZE(FONT_SMALL)+1;
    DrawRectangle(0,YDISP,scr_w-1,scr_h-1,0,white,white);
    ////////////////////////////////////////////////////////////////////////////
    // tridog, 05.08.09 ////////////////////////////////////////////////////////
    // Точим окошко выбора CFG_KEY на елках ////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    if(data->needexit)
    {
    //  wsprintf(data->ws1,"Нажмите <Enter> для подтверждения.\nНажмите  <Red> или <Left> для выхода.");
      ascii2ws(data->ws1,"Нажмите <Enter> для подтверждения.\nНажмите  <Red> или <Left> для выхода.");
      DrawString(data->ws1,3,YDISP + 1 + fsize,scr_w-4,YDISP + fsize*5,FONT_SMALL,1,black,transparent);
    }
    else
    {
    //  wsprintf(data->ws1,"Нажмите любую клавишу\nДлинный левый нав. для обнуления");
      ascii2ws(data->ws1,"Нажмите любую клавишу\nДлинный левый нав. для обнуления");
      
      DrawString(data->ws1,3,YDISP + 1 + fsize,scr_w-4,YDISP + fsize*5,FONT_SMALL,1,black,transparent);
    }   
    wsprintf(data->ws1,"HEX: %c%02X",UTF16_FONT_SMALL_BOLD,data->keyscancode);
    DrawString(data->ws1,3,YDISP + 1 + fsize*7,scr_w-4,YDISP + fsize*8,FONT_SMALL,1,black,transparent);    
    wsprintf(data->ws1,"DEC: %c%u",UTF16_FONT_SMALL_BOLD,data->keyscancode);
    DrawString(data->ws1,3,YDISP + 1 + fsize*8,scr_w-4,YDISP + fsize*9,FONT_SMALL,1,black,transparent); 
    sprintf(str,"%u",data->keyscancode);
    code=StrToInt(str,0);
    //wsprintf(data->ws1,"%c%s",UTF16_FONT_SMALL_BOLD,key_names[code]);
    ascii2ws(data->ws1,key_names[code]);
    DrawString(data->ws1,3,YDISP + 1 + fsize*9,scr_w-4,YDISP + fsize*10,FONT_SMALL,1,black,transparent); 
    ////////////////////////////////////////////////////////////////////////////
}

void OnCreate_key(KEY_GUI *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

void method2_key(KEY_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  data->gui.state=0;
}

void OnFocus_key(KEY_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
#ifdef ELKA  
  DisableIconBar(1);
#endif  
  data->gui.state=2;
}

void method4_key(KEY_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5_key(KEY_GUI *data, GUI_MSG *msg)
{
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    if(msg->gbsmsg->msg==LONG_PRESS&&msg->gbsmsg->submess==LEFT_BUTTON)
    {
      data->keyscancode=0;
      DirectRedrawGUI();
      
    }
    else
    {
    if (msg->gbsmsg->msg==KEY_DOWN)
    {
      if(data->needexit)
      {
       switch(msg->gbsmsg->submess)
       {
       case RED_BUTTON:
       case LEFT_SOFT:
         return (1);
       case ENTER_BUTTON:
         data->keymodecode[0] = data->keyscancode;
         return(1);
       }
       data->needexit = 0;
      } else
      data->needexit = 1;
    }
   
  data->keyscancode = msg->gbsmsg->submess;
  DirectRedrawGUI();
    }
  }
  return(0);
}

void method7_key(KEY_GUI *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);
}

int method8_key(void){return(0);}

int method9_key(void){return(0);}

const void * const gui_methods_key[11]={
  (void *)OnReadraw_key,//Redraw
  (void *)OnCreate_key,	//Create
  (void *)method2_key,	//Close
  (void *)OnFocus_key,	//Focus
  (void *)method4_key,	//Unfocus
  (void *)method5_key,	//OnKey
  0,
  (void *)method7_key,	//Destroy
  (void *)method8_key,
  (void *)method9_key,
  0
};

const RECT Canvas_key={0,0,0,0};

void GetKeyCodes(void *key)
{
  KEY_GUI *keygui=malloc(sizeof(KEY_GUI));
  zeromem(keygui,sizeof(KEY_GUI));
  unsigned int *modekode=key;
    keygui->keymodecode=key;
    keygui->keyscancode=modekode[0];
    keygui->needexit=0;
  patch_rect((RECT*)&Canvas_key,0,YDISP,ScreenW()-1,ScreenH()-1);
  keygui->gui.canvas=(void *)(&Canvas_key);
  keygui->gui.flag30=2;
  keygui->gui.methods=(void *)gui_methods_key;
  keygui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(keygui);
}

