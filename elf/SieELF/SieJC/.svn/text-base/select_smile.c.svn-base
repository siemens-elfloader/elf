#include "../inc/swilib.h"
#include "../inc/pnglist.h"
#include "main.h"
#include "smiles.h"
#include "rect_patcher.h"
#include "select_smile.h"
#include "string_util.h"
#include "color.h"

extern int Is_Smiles_Enabled;

#define MAX_ICON_IN_ROW 32

typedef struct
{
  int icon_in_row;
  struct
  {
    IMGHDR *img;
    int wchar;
  }w_chars[MAX_ICON_IN_ROW];
}IMGH_SMILE;

typedef struct
{
  GUI gui;
  GUI * ed_gui;
  int view_line;
  int cur_pos_x;
  int cur_pos_y;
  int total_lines;
  IMGH_SMILE *icons;
  WSHDR *ws;
}SMILE_GUI;

extern S_SMILES *s_top;
extern DYNPNGICONLIST *SmilesImgList;

IMGHDR *FindSmileIMGHDR(int pic)
{
  DYNPNGICONLIST *d=SmilesImgList;
  IMGHDR *img=NULL;
  while(d)
  {
     if (d->icon==pic)
     {
       img=d->img;
       break;      
     }
     d=d->next;    
  }
  return img;
}

void DrwImg(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,GetPaletteAdrByColorIndex(100),GetPaletteAdrByColorIndex(101));
  DrawObject(&drwobj);
}

void PasteSmileToEditControl(GUI * ed_gui, int wchar)
{
  int pos = EDIT_GetCursorPos(ed_gui);
  EDITCONTROL ec;
  ExtractEditControl(ed_gui, 1, &ec);
  WSHDR * ed_ws = AllocWS(ec.pWS->wsbody[0] + 3);
  wstrcpy(ed_ws, ec.pWS);
  
  wsInsertChar(ed_ws, ' ', pos ++);
  wsInsertChar(ed_ws, wchar, pos ++);
  wsInsertChar(ed_ws, ' ', pos ++);
    
  EDIT_SetTextToEditControl(ed_gui, 1, ed_ws);
  EDIT_SetCursorPos(ed_gui, pos);
  FreeWS(ed_ws);
}

void PasteTextToEditControl(GUI * ed_gui, char * text)
{
  int c;
  char * p = text;
  int pos = EDIT_GetCursorPos(ed_gui);
  EDITCONTROL ec;
  ExtractEditControl(ed_gui, 1, &ec);
  WSHDR * ed_ws = AllocWS(ec.pWS->wsbody[0] + strlen(text) + 2);
  wstrcpy(ed_ws, ec.pWS);
  wsInsertChar(ed_ws, ' ', pos ++);
  while(c = * p ++)
    wsInsertChar(ed_ws, char8to16(c), pos ++);
  wsInsertChar(ed_ws, ' ', pos ++);
  EDIT_SetTextToEditControl(ed_gui, 1, ed_ws);
  EDIT_SetCursorPos(ed_gui, pos);
  FreeWS(ed_ws);
}

int RenderPage(SMILE_GUI *data, int is_draw)   //¬озвращает номер последней нарисованной линии
{
  int scr_w=ScreenW()-1;
  int scr_h=ScreenH()-1;
  int res=0;
  int font=FONT_SMALL;
  int font_size=GetFontYSIZE(font);
  int y=YDISP;
  int y2=y+font_size+2;
  S_SMILES *sm;
  for (int i=data->view_line, max=data->total_lines; i<max; i++)
  {
    int x = 1;
    int h_max=0;
    for (int k=0, m=data->icons[i].icon_in_row; k<m; k++)
    {
      IMGHDR *img=data->icons[i].w_chars[k].img;
      if (is_draw)
      {
        if (i==data->cur_pos_y && k==data->cur_pos_x)
        {
          DrawRectangle(x - 1, y2 - 1, x + img->w, y2 + img->h, 0,
                        color(CURSOR), color(CURSOR_BORDER));
        }
        DrwImg(img,  x,y2);
      }
      x += img->w + 1;
      if ((img->h + 1) > h_max) h_max = img->h + 1;
    }
    y2 += h_max + 1;
    if (y2 >= scr_h) break;
    res = i;
  }
  if (is_draw)
  {
    sm=FindSmileByUni(data->icons[data->cur_pos_y].w_chars[data->cur_pos_x].wchar);
    if (sm)
    {
      ascii2ws(data->ws,sm->lines->text);
      DrawString(data->ws,1,y+1,scr_w,y+1+font_size,font,0, color(CLIST_F_COLOR_0), GetPaletteAdrByColorIndex(23));
    }
  }
  return (res);  
}

static void method0(SMILE_GUI *data)
{
  int scr_w=ScreenW()-1;
  int scr_h=ScreenH()-1;
  DrawRectangle(0,YDISP,scr_w,scr_h,0, 
                color(MAINBG_CONNECTED),
                color(MAINBG_CONNECTED));
  RenderPage(data,1);
}

static void method1(SMILE_GUI *data,void *(*malloc_adr)(int))
{
  S_SMILES *sm=s_top;
  IMGHDR *img;
  int pic;
  int row_w=ScreenW();   // заведомо больша€ ширина чтобы начать с новой линии
  IMGH_SMILE *cur_img;
  while(sm)
  {
    pic=GetPicNByUnicodeSymbol(sm->uni_smile);
    img=FindSmileIMGHDR(pic);
    if (img)
    {
      row_w+=img->w + 1;
      if (row_w>(ScreenW()-1) || cur_img->icon_in_row>=MAX_ICON_IN_ROW)
      {
        row_w = img->w + 1;
        cur_img=data->icons=realloc(data->icons,(data->total_lines+1)*sizeof(IMGH_SMILE));
        cur_img+=data->total_lines;
        zeromem(cur_img,sizeof(IMGH_SMILE));
        data->total_lines++;
      }
      cur_img->w_chars[cur_img->icon_in_row].img=img;
      cur_img->w_chars[cur_img->icon_in_row].wchar=sm->uni_smile;
      cur_img->icon_in_row++;
    }
    sm=sm->next;
  }
  data->ws=AllocWS(50);
  data->gui.state=1;
}

static void method2(SMILE_GUI *data,void (*mfree_adr)(void *))
{
  data->gui.state=0;
  mfree(data->icons);
  FreeWS(data->ws);
}

static void method3(SMILE_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

static void method4(SMILE_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

static int method5(SMILE_GUI *data,GUI_MSG *msg)
{
  int i;
  int m=msg->gbsmsg->msg;
  int key=msg->gbsmsg->submess;
  S_SMILES *sm;
  if ((m==KEY_DOWN)||(m==LONG_PRESS))
  {
    if (key==GREEN_BUTTON || (key>='0' && key<='9'))
    {
      int c;
      int n=0;
      int d;
      if (key==GREEN_BUTTON) c=0;
      else if (key=='0') c=10;
      else c=key-'0';
      while(c>=(d=data->icons[n].icon_in_row) && n<data->total_lines)
      {
        c-=d;
        n++;
      }
      if (c>=0 && n<data->total_lines)
      {
        if (Is_Smiles_Enabled)
          PasteSmileToEditControl(data->ed_gui, data->icons[n].w_chars[c].wchar);
        else
          if (sm=FindSmileByUni(data->icons[n].w_chars[c].wchar))
            PasteTextToEditControl(data->ed_gui, sm->lines->text);
        return (1);
      }
    }
    else
    {
      switch(key)
      {
      case UP_BUTTON:
        if (data->cur_pos_y>0)
        {
          data->cur_pos_y--;
          if (data->cur_pos_y<=data->view_line) data->view_line=data->cur_pos_y;
        }
        else
        {
          data->cur_pos_y=data->total_lines-1;
          data->view_line=0;
          while(data->view_line<data->total_lines)
          {
            if (data->cur_pos_y==RenderPage(data,0)) break;
            data->view_line++;
          }
        }
        if (data->cur_pos_x>=(i=data->icons[data->cur_pos_y].icon_in_row)) data->cur_pos_x=i-1;  // ѕровер€ем на выход за пределы
        break;
        
      case DOWN_BUTTON:
        if (data->cur_pos_y<data->total_lines-1)
        {
          data->cur_pos_y++;
          if (data->cur_pos_y>RenderPage(data,0)) data->view_line++;
        }
        else
        {
          data->cur_pos_y=data->view_line=0;
        }
        if (data->cur_pos_x>=(i=data->icons[data->cur_pos_y].icon_in_row)) data->cur_pos_x=i-1;  // ѕровер€ем на выход за пределы
        break;
        
      case LEFT_BUTTON:
        if (data->cur_pos_x>0) data->cur_pos_x--;
        else data->cur_pos_x=data->icons[data->cur_pos_y].icon_in_row-1;
        break;
        
      case RIGHT_BUTTON:
        data->cur_pos_x++;
        if (data->cur_pos_x>=(i=data->icons[data->cur_pos_y].icon_in_row)) data->cur_pos_x=0;  // ѕереходим на первый в р€ду
        break;
        
      case LEFT_SOFT:
      case ENTER_BUTTON:
        if (Is_Smiles_Enabled)
          PasteSmileToEditControl(data->ed_gui, data->icons[data->cur_pos_y].w_chars[data->cur_pos_x].wchar);
        else
          if (sm=FindSmileByUni(data->icons[data->cur_pos_y].w_chars[data->cur_pos_x].wchar))
            PasteTextToEditControl(data->ed_gui, sm->lines->text);
        return (1);
      
    #ifndef NEWSGOLD
      case RED_BUTTON:
    #endif
      case RIGHT_SOFT:
        return (1);
      }
    }
  }
  DirectRedrawGUI();
  return(0);
}

static int method8(void){return(0);}

static int method9(void){return(0);}

extern void kill_data(void *p, void (*func_p)(void *));
static const void * const gui_methods[11]={
  (void *)method0,  //Redraw
  (void *)method1,  //Create
  (void *)method2,  //Close
  (void *)method3,  //Focus
  (void *)method4,  //Unfocus
  (void *)method5,  //OnKey
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)method8,
  (void *)method9,
  0
};

int CreateSmileSelectGUI(GUI * _ed_gui)
{
  static const RECT Canvas={0,0,0,0};
  SMILE_GUI *smile_gui=malloc(sizeof(SMILE_GUI));
  zeromem(smile_gui,sizeof(SMILE_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  smile_gui->gui.canvas=(void *)(&Canvas);
  smile_gui->gui.methods=(void *)gui_methods;
  smile_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  smile_gui->ed_gui=_ed_gui;
  return CreateGUI(smile_gui);
}
