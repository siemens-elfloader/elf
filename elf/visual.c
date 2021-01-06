#include "..\inc\swilib.h"

char testcolor[4];
char colors[4][4]={{0xFF,0,0,0x64},{0,0xFF,0,0x64},{0,0,0xFF,0x64},{0xC6,0xAA,0xAF,0x32}};
extern long  strtol (const char *nptr,char **endptr,int base);
extern unsigned long  strtoul (const char *nptr,char **endptr,int base);

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}


typedef struct
{
  GUI gui;
  WSHDR*ws1;
  int x_pos;
  int y_pos;
  unsigned int* x_pos_1;
  unsigned int* y_pos_1;  
}MAIN_GUI_1;

typedef struct
{
  GUI gui;
  WSHDR*ws1; 
  int r;
  int g;
  int b;
  int a;
  char* color;
  int current_column;
}MAIN_GUI_2;

const char Pointer[5]={0x27,0x27,0xFF,0x27,0x27};
const IMGHDR imgPointer = {5,5,0x1,(char *)Pointer};

void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}


void DrawWhiteScreen(void)
{
  DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,
                   GetPaletteAdrByColorIndex(0),
                   GetPaletteAdrByColorIndex(0));
}  

void method0_1(MAIN_GUI_1 *data)
{
  DrawWhiteScreen();
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  for (int y_0=0; y_0< scr_h;y_0+=10)
  {
    DrawLine(0,y_0,scr_w-1,y_0,1,colors[3]);
  }
  
  for (int x_0=0; x_0<scr_w;x_0+=10)
  {
    DrawLine(x_0,0,x_0, scr_h-1,1,colors[3]);
  }
  wsprintf(data->ws1,"%u,%u",data->x_pos,data->y_pos);
  DrwImg((IMGHDR *)&imgPointer,data->x_pos-2,data->y_pos-2,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
  DrawString(data->ws1,3,scr_h-11,scr_w-4,scr_h-1,SMALL_FONT,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
}

void method1_1(MAIN_GUI_1 *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

void method2_1(MAIN_GUI_1 *data, void (*mfree_adr)(void *))
{
  *data->x_pos_1=data->x_pos;
  *data->y_pos_1=data->y_pos;
  FreeWS(data->ws1);
  data->gui.state=0;
}

void method3_1(MAIN_GUI_1 *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4_1(MAIN_GUI_1 *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5_1(MAIN_GUI_1 *data, GUI_MSG *msg)
{
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
    case '1':
      if (--data->x_pos<0)
        data->x_pos=0;
      if (--data->y_pos <0)
        data->y_pos=0;
      break;
      
    case '2':
    case UP_BUTTON:
      if (--data->y_pos <0)
        data->y_pos=0;
      break;
      
    case '3':
      if (++data->x_pos >ScreenW()-1)
        data->x_pos=ScreenW()-1;
      if (--data->y_pos <0)
        data->y_pos=0;
      break;
     
    case '4':
    case LEFT_BUTTON:
      if (--data->x_pos<0)
        data->x_pos=0;
      break;
      
    case '6':
    case RIGHT_BUTTON:
      if (++data->x_pos >ScreenW()-1)
        data->x_pos=ScreenW()-1;
      break;
      
    case '7': 
      if (--data->x_pos<0)
        data->x_pos=0;      
      if (++data->y_pos >ScreenH()-1)
        data->y_pos=ScreenH()-1;
      break;
      
    case '8':
    case DOWN_BUTTON:
      if (++data->y_pos >ScreenH()-1)
        data->y_pos=ScreenH()-1;
      break;
      
    case '9': 
      if (++data->x_pos >ScreenW()-1)
        data->x_pos=ScreenW()-1;
      if (++data->y_pos >ScreenH()-1)
        data->y_pos=ScreenH()-1;
      break;      
      
    case RED_BUTTON:
      return (1);
    }
  }
  DirectRedrawGUI();
  return(0);
}

void method7_1(MAIN_GUI_1 *data, void (*mfree_adr)(void *))
{
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(data,mfree_adr);
}

int method8_1(void){return(0);}

int method9_1(void){return(0);}

const void * const gui_methods_1[11]={
  (void *)method0_1,	//Redraw
  (void *)method1_1,	//Create
  (void *)method2_1,	//Close
  (void *)method3_1,	//Focus
  (void *)method4_1,	//Unfocus
  (void *)method5_1,	//OnKey
  0,
  (void *)method7_1,	//Destroy
  (void *)method8_1,
  (void *)method9_1,
  0
};

const RECT Canvas_1={0,0,0,0};

void EditCoordinates(unsigned int*x, unsigned int* y)
{
  MAIN_GUI_1 *main_gui=malloc(sizeof(MAIN_GUI_1));
  zeromem(main_gui,sizeof(MAIN_GUI_1));
  main_gui->x_pos=*x;
  main_gui->y_pos=*y;
  main_gui->x_pos_1=x;
  main_gui->y_pos_1=y;
  patch_rect((RECT*)&Canvas_1,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas_1);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods_1;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(main_gui);
}


void method0_2(MAIN_GUI_2 *data)
{
  DrawWhiteScreen();
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  int column_height=scr_h-35;
  int column_width=scr_w/9;
  int start_column;
  int y_line;
  wsprintf(data->ws1,"%02X,%02X,%02X,%02X",data->r,data->g,data->b,data->a);
  DrawString(data->ws1,1,1,scr_w-20,12,SMALL_FONT,1,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(23));
  
  for (int i=0;i!=4;i++)
  {
    start_column=column_width+2*i*column_width;
    if (data->current_column==i)
      DrawRectangle(start_column-2,20-2,start_column+column_width+2,20+column_height+2,
                    0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(0));

    DrawRectangle(start_column,20,start_column+column_width,20+column_height,
                  0,GetPaletteAdrByColorIndex(1),colors[i]);
    switch(i)
    {
    case 0:
      y_line=20+column_height-(data->r*column_height)/0xFF;
      break;
    case 1:
      y_line=20+column_height-(data->g*column_height)/0xFF;
      break;      
    case 2:
      y_line=20+column_height-(data->b*column_height)/0xFF;
      break;
    case 3:
      y_line=20+column_height-(data->a*column_height)/0x64;
      break;
    }
    DrawLine(start_column,y_line,start_column+column_width,y_line,0,GetPaletteAdrByColorIndex(1));
  }
  setColor(data->r,data->g,data->b,data->a,testcolor);
  DrawRoundedFrame(scr_w-17,1,scr_w-2,16,2,2,0,GetPaletteAdrByColorIndex(1),testcolor);

}

void method1_2(MAIN_GUI_2 *data, void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(256);
  data->gui.state=1;
}

void method2_2(MAIN_GUI_2 *data, void (*mfree_adr)(void *))
{
  setColor(data->r,data->g,data->b,data->a,data->color);
  FreeWS(data->ws1);
  data->gui.state=0;
}

void method3_2(MAIN_GUI_2 *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
}

void method4_2(MAIN_GUI_2 *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method5_2(MAIN_GUI_2 *data, GUI_MSG *msg)
{
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
    case UP_BUTTON:
    case '2':
      switch(data->current_column)
      {
      case 0:
        if (++data->r>0xFF)
          data->r=0;
        break;
      case 1:
        if (++data->g>0xFF)
          data->g=0;
        break;
      case 2:
        if (++data->b>0xFF)
          data->b=0;
        break;
      case 3:
        if (++data->a>0x64)
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
    case RED_BUTTON:
      return (1);
      
    case DOWN_BUTTON:
    case '8':
      switch(data->current_column)
      {
      case 0:
        if (--data->r<0)
          data->r=0xFF;
        break;
      case 1:
        if (--data->g<0)
          data->g=0xFF;
        break;
      case 2:
        if (--data->b<0)
          data->b=0xFF;
        break;
      case 3:
        if (--data->a<0)
          data->a=0x64;
        break;
      }
      break;
    }
  }
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

void EditColors(char*color)
{
  MAIN_GUI_2 *main_gui=malloc(sizeof(MAIN_GUI_2));
  zeromem(main_gui,sizeof(MAIN_GUI_2));
  main_gui->r=*((char *)color);
  main_gui->g=*((char *)color+1);
  main_gui->b=*((char *)color+2);
  main_gui->a=*((char *)color+3);
  main_gui->color=color;
  patch_rect((RECT*)&Canvas_2,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas_2);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods_2;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  CreateGUI(main_gui);
}

