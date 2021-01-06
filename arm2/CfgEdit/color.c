#include "..\inc\swilib.h"
#include "rect_patcher.h"

extern char colors[4][4];
extern char black[4];
extern char white[4];
extern char transparent[4];

typedef struct
{
  GUI gui;
  WSHDR*ws1; 
  int r;
  int g;
  int b;
  int a;
  char *color;
  int current_column;
  char testcolor[4];
  int cstep;
}MAIN_GUI_2;


void method0_2(MAIN_GUI_2 *data)
{
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  DrawRectangle(0,YDISP,scr_w-1,scr_h-1,0,white,white);

  int fsize=GetFontYSIZE(FONT_SMALL)+1;
  int column_height=scr_h-fsize-fsize-YDISP;
  int column_width=scr_w/9;
  int start_column;
  int y_line;
  wsprintf(data->ws1,"%02X,%02X,%02X,%02X",data->r,data->g,data->b,data->a);

  DrawString(data->ws1,1,YDISP+1,scr_w-20,YDISP+fsize,FONT_SMALL,1,black,transparent);
  fsize+=3;
  for (int i=0;i!=4;i++)
  {
    start_column=column_width+2*i*column_width;
    if (data->current_column==i)
      DrawRectangle(start_column-2,YDISP+fsize-2,start_column+column_width+2,YDISP+fsize+column_height+2,
                    0,black,white);

    DrawRectangle(start_column,YDISP+fsize,start_column+column_width,YDISP+fsize+column_height,
                  0,black,colors[i]);
    switch(i)
    {
    case 0:
      y_line=YDISP+fsize+column_height-(data->r*column_height)/0xFF;
      break;
    case 1:
      y_line=YDISP+fsize+column_height-(data->g*column_height)/0xFF;
      break;      
    case 2:
      y_line=YDISP+fsize+column_height-(data->b*column_height)/0xFF;
      break;
    case 3:
      y_line=YDISP+fsize+column_height-(data->a*column_height)/0x64;
      break;
    }
    DrawLine(start_column,y_line,start_column+column_width,y_line,0,black);
  }
  setColor(data->r,data->g,data->b,data->a,data->testcolor);
  DrawRoundedFrame(scr_w-1-fsize,YDISP+1,scr_w-2,YDISP+fsize,2,2,0,black,data->testcolor);
}

void method1_2(MAIN_GUI_2 *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

void method2_2(MAIN_GUI_2 *data, void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  data->gui.state=0;
}

void method3_2(MAIN_GUI_2 *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
#ifdef ELKA    
  DisableIconBar(1);
#endif  
  data->gui.state=2;
}

void method4_2(MAIN_GUI_2 *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5_2(MAIN_GUI_2 *data, GUI_MSG *msg)
{
  int n;
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    if (msg->gbsmsg->msg==KEY_DOWN)
    {
       switch(msg->gbsmsg->submess)
       {
       case RIGHT_SOFT:
       case RED_BUTTON:
         return (1);
         
       case ENTER_BUTTON:
         setColor(data->r,data->g,data->b,data->a,data->color);
         return (1);
       }
    }
    if (msg->gbsmsg->msg==LONG_PRESS)  
      data->cstep=8;

    switch(msg->gbsmsg->submess)
    {
    case UP_BUTTON:
    case '2':
      switch(data->current_column)
      {
      case 0:
        if ((data->r+=data->cstep)>0xFF)
          data->r=0;
        break;
      case 1:
        if ((data->g+=data->cstep)>0xFF)
          data->g=0;
        break;
      case 2:
        if ((data->b+=data->cstep)>0xFF)
          data->b=0;
        break;
      case 3:
        if ((data->a+=((n=data->cstep)==8?n>>1:n))>0x64)
          data->a=0;
        break;
      }
      break;
      
    case LEFT_BUTTON:
    case '4':
      if (--data->current_column<0)
        data->current_column=3;
      break;  
    case RIGHT_BUTTON:
    case '6':
      if (++data->current_column>3)
        data->current_column=0;
      break;
      
    case DOWN_BUTTON:
    case '8':
      switch(data->current_column)
      {
      case 0:
        if ((data->r-=data->cstep)<0)
          data->r=0xFF;
        break;
      case 1:
        if ((data->g-=data->cstep)<0)
          data->g=0xFF;
        break;
      case 2:
        if ((data->b-=data->cstep)<0)
          data->b=0xFF;
        break;
      case 3:
        if ((data->a-=((n=data->cstep)==8?n>>1:n))<0)
          data->a=0x64;
        break;
      }
      break;
    }
  }
  if (msg->gbsmsg->msg==KEY_UP)
    data->cstep=1;
  DirectRedrawGUI();
  return(0);
}


void method7_2(MAIN_GUI_2 *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);
}

int method8_2(void){return(0);}

int method9_2(void){return(0);}

const void * const gui_methods_2[11]={
  (void *)method0_2,	//Redraw
  (void *)method1_2,	//Create
  (void *)method2_2,	//Close
  (void *)method3_2,	//Focus
  (void *)method4_2,	//Unfocus
  (void *)method5_2,	//OnKey
  0,
  (void *)method7_2,	//Destroy
  (void *)method8_2,
  (void *)method9_2,
  0
};

const RECT Canvas_2={0,0,0,0};

void EditColors(char *color)
{
  MAIN_GUI_2 *main_gui=malloc(sizeof(MAIN_GUI_2));
  zeromem(main_gui,sizeof(MAIN_GUI_2));
  main_gui->r=color[0];
  main_gui->g=color[1];
  main_gui->b=color[2];
  main_gui->a=color[3];
  main_gui->color=color;
  patch_rect((RECT*)&Canvas_2,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas_2);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods_2;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(main_gui);
}
