#include "../inc/swilib.h"
#include "rect_patcher.h"
#include "mainmenu.h"
#include "edit_settings.h"
#include "calc_object.h"
#include "gammaf.h"

#include <math.h>

//#define PI_CONST 3.141592653589793238
#define PI_CONST 3.1415926535897932384626433832795
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  int state;
  WSHDR *ws1;
  void *calc_gui;
}CHTYPE_GUI;

extern CALC_SETTINGS calc_set;

volatile int calc_gui_id;
volatile int chtype_gui_id;

extern double strtod(const char *_S, char **_Endptr);

extern void kill_data(void *p, void (*func_p)(void *));

WSHDR *ews;
const char empty_str[]="";
const char percent_t[]="%t";

double vars['z'-'a'];
double d_answer=0;

char operation[256];
int op_len=0;
int op_pos=0;

int req_recalc;

void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

const char *const keydesc[4][12]=
{
  { "1"    ,"2"   ,"3",
    "4"    ,"5"   ,"6",
    "7"    ,"8"   ,"9",
    "."    ,"0"   ,"#"},
    
  { "sin"  ,"*"   ,"/",
    "cos"  ,"+"   ,"-",
    "tan"  ,"("   ,")",
    "^2"   ,"sqrt"   ,"#"},
  
  { "asin" ,"ln"  ,"log",
    "acos" ,"e^"  ,"-",
    "atan" ,"10^" ,"pi",
    "^"    ,""    ,"#"},
  
  { "sh"   ,"ash" ,"ANS",
    "ch"   ,"ach" ,"abs",
    "th"   ,"ath" ,"!",
    "X"    ,"Y"   ,"#"}
  
};

int GetOperIndexByKey(int key)
{
  if (key>='1'&&key<='9')  return (key-'1');
  if (key=='0')   return (10);
  if (key=='*')   return (9);
  return (11);
}

void insert_operation(int op)
{
  if (op_len<sizeof(operation))
  {
    for(int i=op_len; i>=op_pos; i--)
    {
      operation[i+1]=operation[i];
    }
    operation[op_pos++]=op;
    op_len++;    
  } 
}

void remove_all_operation(void)
{
// Функция AC
  int i=0;
  while(i<=op_len)
  {
    operation[i]=0;
    i++;
  }
  op_pos=0;
  op_len=0;
}

void remove_operation(void)
{
  if (op_len && op_pos)
  {
    if (op_pos<=op_len)
    {
      int i=op_pos;
      while(i<op_len)
      {
        operation[i-1]=operation[i];
        i++;
      }
      op_pos--;
      op_len--;
    }    
  }  
}

int getXXXXwidth(int font)
{ 
  return (GetSymbolWidth('X',font)*4);
}

#pragma inline
int IsCharNumber(int c)
{
  return ((c>=DIG_1 && c<=DIG_0) || c==OP_NEG);
}

#pragma inline
int GetCharByIndex(int c)
{
  return (c==29?'-':c==9?'.':c==10?'0':c+'1');
}

#pragma inline 
int IsMathFunc(int c)
{
  return (c==OP_SIN ||
          c==OP_COS ||
          c==OP_TAN ||
          c==OP_ASIN ||
          c==OP_LN ||
          c==OP_LOG || 
          c==OP_ACOS ||
          c==OP_ATAN || 
          c==OP_SH ||
          c==OP_ASH || 
          c==OP_CH || 
          c==OP_ACH ||
          c==OP_ABS ||
          c==OP_TH ||
          c==OP_ATH ||
          c==OP_FAC);     
}

int IsPowFunc(int c)
{
  return (c==OP_SQUARE || c==OP_SQRT || c==OP_EPOW || c==OP_TENPOW || c==OP_POW);
}

/* Функция PRIOR возвpащает пpиоpитет аpифм. опеpации */
int PRIOR(int a)
{
  if (IsPowFunc(a)) return 5;
  if (IsMathFunc(a)) return 4;
  switch(a)
  {    
  case OP_MULT:   // *
  case OP_DIV:   // /
    return 3;
    
  case OP_PLUS:  // +
  case OP_MINUS:  // -
    return 2;
    
  case LEFTBRACKET:  // (
         return 1;
  }
  return (0);
}


typedef struct {
  jmp_buf jmp;
  double *stack;
  int sp; 
}DSTACK;

void PushDoubleStack(DSTACK *dstack, double value)
{
  dstack->stack=realloc(dstack->stack,(dstack->sp+1)*sizeof(double));
  dstack->stack[dstack->sp]=value;
  dstack->sp++;
}

double PopDoubleStack(DSTACK *dstack)
{
  double a=0;
  if (dstack->sp)
  {
    a=dstack->stack[--dstack->sp];    
  }
  else
  {
    longjmp(dstack->jmp, 1);
  }
  return a;  
}

void ConstructDStackStruct(DSTACK *dstack)
{
  dstack->stack=NULL;
  dstack->sp=0;
}

void DestructDStackStruct(DSTACK *dstack)
{
  mfree(dstack->stack);
}

double FacN(double n)
{
  double ans;
  double frac, integer;
  frac=modf(n,&integer);
  if (frac==0)
  {
    ans=1;
    while(integer>1 && ans!=INFINITY)
    {
      ans*=integer--;
    }
  }
  else
  {
    ans=log(FacN(integer))+frac*log(integer+1);
  }
  return ans;
}

double ConvertAngleToRadians(double angle)
{
  double a=0;
  switch(calc_set.drg)
  {
  case DEGREES:
  default:
    a=angle*PI_CONST/180;
    break;
  case RADIANS:
    a=angle;
    break;
  case GRADS:
    a=angle*PI_CONST/200;
    break;
  }
  return (a);
}


double ConvertRadiansToAngle(double radian)
{
  double a=0;
  switch(calc_set.drg)
  {
  case DEGREES:
  default:
    a=radian*180/PI_CONST;
    break;
  case RADIANS:
    a=radian;
    break;
  case GRADS:
    a=radian*200/PI_CONST;
    break;
  }
  return (a);
}

double asinh(double a)
{
  return log(a+sqrt(pow(a,2)+1));
}

double acosh(double a)
{
  return a>=1?log(a+sqrt(pow(a,2)-1)):NAN;
}

double athh(double a)
{
  return log((1+a)/(1-a))/2;
}

void ParseOperation(DSTACK *dstack, int operation)
{
  double a, b, ans;
  switch (operation)
  {
  case OP_SIN:    // sin
    a=PopDoubleStack(dstack);
    ans=sin(ConvertAngleToRadians(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_MULT:    // *
    a=PopDoubleStack(dstack);
    b=PopDoubleStack(dstack);
    ans=b*a;
    PushDoubleStack(dstack, ans);
    break;
  case OP_DIV:    // /
    a=PopDoubleStack(dstack);
    b=PopDoubleStack(dstack);
    ans=b/a;
    PushDoubleStack(dstack, ans);
    break;
  case OP_COS:    // cos
    a=PopDoubleStack(dstack);
    ans=cos(ConvertAngleToRadians(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_PLUS:    // +
    a=PopDoubleStack(dstack);
    b=PopDoubleStack(dstack);
    ans=b+a;
    PushDoubleStack(dstack, ans);
    break;    
  case OP_MINUS:    // -
    a=PopDoubleStack(dstack);
    b=PopDoubleStack(dstack);
    ans=b-a;
    PushDoubleStack(dstack, ans);
    break;
  case OP_TAN:    // tan
    a=PopDoubleStack(dstack);
    ans=tan(ConvertAngleToRadians(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_SQUARE:    // ^2
    a=PopDoubleStack(dstack);
    ans=pow(a, 2);
    PushDoubleStack(dstack, ans);
    break;
  case OP_SQRT:    // sqrt
    a=PopDoubleStack(dstack);
    ans=sqrt(a);
    PushDoubleStack(dstack, ans);
    break;
  case OP_ASIN:    // asin
    a=PopDoubleStack(dstack);
    ans=ConvertRadiansToAngle(asin(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_LN:   // ln
    a=PopDoubleStack(dstack);
    ans=log(a);
    PushDoubleStack(dstack, ans);
    break;
  case OP_LOG:   // log 10
    a=PopDoubleStack(dstack);
    ans=log10(a);
    PushDoubleStack(dstack, ans);
    break;
  case OP_ACOS:   // acos
    a=PopDoubleStack(dstack);
    ans=ConvertRadiansToAngle(acos(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_EPOW:    // e^
    a=PopDoubleStack(dstack);
    ans=exp(a);
    PushDoubleStack(dstack, ans);
    break;
  case OP_ATAN:    // atan
    a=PopDoubleStack(dstack);
    ans=ConvertRadiansToAngle(atan(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_TENPOW:    // 10^
    a=PopDoubleStack(dstack);
    ans=pow(10, a);
    PushDoubleStack(dstack, ans);
    break;
  case OP_POW:     // ^
    a=PopDoubleStack(dstack);
    b=PopDoubleStack(dstack);
    ans=pow(b, a);
    PushDoubleStack(dstack, ans);
    break;
  case OP_SH:    // sinh
    a=PopDoubleStack(dstack);
    ans=sinh(ConvertAngleToRadians(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_ASH:    // asinh
    a=PopDoubleStack(dstack);
    ans=ConvertRadiansToAngle(asinh(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_CH:    // cosh
    a=PopDoubleStack(dstack);
    ans=cosh(ConvertAngleToRadians(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_ACH:    // acosh
    a=PopDoubleStack(dstack);
    ans=ConvertRadiansToAngle(acosh(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_TH:    // tanh
    a=PopDoubleStack(dstack);
    ans=tanh(ConvertAngleToRadians(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_ATH:    // atanh
    a=PopDoubleStack(dstack);
    ans=ConvertRadiansToAngle(athh(a));
    PushDoubleStack(dstack, ans);
    break;
  case OP_ABS:    // abs
    a=PopDoubleStack(dstack);
    ans=fabs(a);
    PushDoubleStack(dstack, ans);
    break;
  case OP_FAC:   // !
    a=PopDoubleStack(dstack);
    ans=gamma(a+1);
    PushDoubleStack(dstack, ans);
    break;
  }
}

void calc_answer()
{
  char *s;
  int c;
  int i=op_len;
  char stack[256];
  int stack_depth=0;
  s=operation;
  DSTACK dstack;
  char *d,value[128];
  double ans=0;
  ConstructDStackStruct(&dstack);
  if (setjmp(dstack.jmp))
  {
    ans=NAN;
    goto L_ERROR;
  }
  while(i)
  {
    c=*s++;
    if (IsCharNumber(c))
    {
      double a;
      d=value;
      do {
        *d++=GetCharByIndex(c);
        i--;
        c=*s++;
      } while (IsCharNumber(c) && i);
      *d=0;
      a=strtod(value, NULL);
      PushDoubleStack(&dstack, a);
      if (!i) break;
    }
    if (c==NUM_PI)  // пи
    {
      double a=PI_CONST;
      PushDoubleStack(&dstack, a);
    }
    else if (c==NUM_ANS)   // ANS
    {
      PushDoubleStack(&dstack, d_answer);
    }
    else if (c==NUM_A)   // X
    {
      PushDoubleStack(&dstack, calc_set.x);
    }
    else if (c==NUM_B)   // Y
    {
      PushDoubleStack(&dstack, calc_set.y);
    }
      else if (c>=VAR_A && c<=VAR_Z)
      {
        PushDoubleStack(&dstack, vars[c-VAR_A]);
      }
      else if (c==RIGHTBRACKET)   // Закрывающаяся скобка
      {
        while(stack_depth && stack[--stack_depth]!=LEFTBRACKET)
        {
          ParseOperation(&dstack, stack[stack_depth]);
        }
      }
      else if (c==LEFTBRACKET)  // Открывающаяся скобка
      {
        stack[stack_depth++]=c;
      }
    else if (c==OP_MULT || c==OP_DIV || c==OP_PLUS || c==OP_MINUS || IsMathFunc(c) || IsPowFunc(c))  // Если знак операции
    {
      if (!stack_depth)  // Если стек пуст
      {
        stack[stack_depth++]=c;
      }
      else if (PRIOR(c)>PRIOR(stack[stack_depth-1]))  // Если приоритет поступившей операции больше того что на вершине стека
      {
        stack[stack_depth++]=c;
      }
      else
      {
        while(stack_depth && (PRIOR(stack[stack_depth-1])>=PRIOR(c)))
        {
          ParseOperation(&dstack, stack[--stack_depth]);
        }
        stack[stack_depth++]=c;
      }
    }
    i--;
  }
  while(stack_depth)
  {
    ParseOperation(&dstack, stack[--stack_depth]);
  }
  ans=PopDoubleStack(&dstack);
L_ERROR:
  DestructDStackStruct(&dstack);
  d_answer=ans;
}
  
void MainOnRedraw(CHTYPE_GUI *data)
{
  unsigned int scr_w=ScreenW();
  unsigned int scr_h=ScreenH();
  unsigned int need_height;
  unsigned int need_width;
  unsigned int start_y;
  unsigned int start_x;
  unsigned int XXXXwidth=getXXXXwidth(FONT_SMALL);
  unsigned int Ysize=GetFontYSIZE(FONT_SMALL);
  
  need_height=Ysize*4+5*2*3+5*2;
  need_width=XXXXwidth*3+5*2*2+5*2;
  
  start_y=need_height<scr_h?(scr_h-need_height)>>1:0;
  start_x=need_width<scr_w?(scr_w-need_width)>>1:0;
  
  DrawRoundedFrame(start_x,start_y,start_x+need_width,start_y+need_height,3,3,0,
                   GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  
  for (int y=0; y<4; y++)
  {
    for (int x=0; x<3; x++)
    {
      unsigned int x_frame=start_x+XXXXwidth*x+5*2*x;
      unsigned int y_frame=start_y+Ysize*y+5*2*y;
      
      
      wsprintf(data->ws1,percent_t,keydesc[data->state][y*3+x]);
      
      unsigned int str_width=Get_WS_width(data->ws1,FONT_SMALL);
      unsigned int x_str=x_frame+((XXXXwidth-str_width)>>1)+5;
      
      DrawRoundedFrame(x_frame,y_frame,x_frame+XXXXwidth+5*2,y_frame+Ysize+5*2,3,3,0,
                       GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
      DrawString(data->ws1,x_str,y_frame+5,x_str+str_width,y_frame+Ysize+5,
                 FONT_SMALL,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
    }
  }

}

void MainOnCreate(CHTYPE_GUI *data,void *(*malloc_adr)(int))
{
  data->ws1=AllocWS(128);
  data->gui.state=1;
}

void MainOnClose(CHTYPE_GUI *data,void (*mfree_adr)(void *))
{
  FreeWS(data->ws1);
  data->gui.state=0;
}

void MainOnFocus(CHTYPE_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void MainOnUnfocus(CHTYPE_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}


int MainOnKey(CHTYPE_GUI *data,GUI_MSG *msg)
{
  int i=msg->gbsmsg->submess;
  DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (((i>='0')&&(i<='9'))||(i=='*'))
    {
      insert_operation(GetOperIndexByKey(i)+((data->state)*12));
      if (calc_set.auto_recalc) req_recalc=1;
      return (1);
    }
    if (i=='#')
    {
      if (++data->state>3) return (1);
      return (-1);
    }
    if (i==RIGHT_SOFT)
    {
      return (1);
    }
  }
  return(0);
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)MainOnRedraw, //Redraw
  (void *)MainOnCreate,	//Create
  (void *)MainOnClose,	//Close
  (void *)MainOnFocus,	//Focus
  (void *)MainOnUnfocus,	//Unfocus
  (void *)MainOnKey,	//OnKey
  0,
  (void *)kill_data, //method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};


RECT Canvas={0,0,0,0};
void OpenChangeTypeGui(void *calc_gui)
{
  CHTYPE_GUI *chtype_gui=malloc(sizeof(CHTYPE_GUI));
  zeromem(chtype_gui,sizeof(CHTYPE_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  chtype_gui->gui.canvas=(void *)(&Canvas);
  chtype_gui->gui.flag30=2;
  chtype_gui->gui.methods=(void *)gui_methods;
  chtype_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  chtype_gui->calc_gui=calc_gui;
  chtype_gui->state=1;
  chtype_gui_id=CreateGUI(chtype_gui);
}


void ed1_locret(void){}


int ed1_onkey(GUI *data, GUI_MSG *msg)
{
  int focus;
  int i;
  i=msg->gbsmsg->submess;
  
  focus=EDIT_GetFocus(data);
  if (msg->keys==0xFFF)
  {
    ShowMainMenu();
    return (-1);
  }
  if (focus==4)
  {
    if (msg->keys==0xFFE)
    {
      remove_operation();
      if (calc_set.auto_recalc) req_recalc=1;
      return (-1);    
    }
    if (msg->gbsmsg->msg==KEY_DOWN)
    {
      if (((i>='0')&&(i<='9'))||(i=='*'))
      {
        insert_operation(GetOperIndexByKey(i));
        if (calc_set.auto_recalc) req_recalc=1;
        return(-1);
      }
      if (i=='#')
      {
        if (IsGuiOnTop(calc_gui_id))
        {
          if(!chtype_gui_id)
          {
            OpenChangeTypeGui(data);
            return(-1);
          }
        }
      } 
    }
    
    if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
    {
      if (i==LEFT_BUTTON)
      {
        if (op_pos) op_pos--;
        return(-1);
      }
      if (i==RIGHT_BUTTON)
      {
        if (op_pos<op_len) op_pos++;
        return(-1);
      }
    }
  }
  
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    if (i==GREEN_BUTTON) 
    {
      req_recalc=1;
      return(-1);
    }
  }
  return(0);
}

void ed1_ghook(GUI *data, int cmd)
{
  char *s;
  int c;
  int i;
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Options"};
  static SOFTKEY_DESC sk_del={0x0FFE,0x0FFE,(int)"< C"};
  if (cmd==TI_CMD_CREATE)
  {
    op_len=0;
    req_recalc=0;
    EDIT_SetFocus(data, 4);
  }
  if (cmd==TI_CMD_REDRAW)
  {
    i=EDIT_GetFocus(data);
    if (i==4)
    {
      int k=0;
      CutWSTR(ews,0);
      if (op_len)
      {
        SetSoftKey(data,&sk_del,SET_SOFT_KEY_N==1?0:1);
        s=operation;
        i=0;
        while (i<op_len)
        {
          const char *op;
          c=*s++;
          op=keydesc[0][c];
          while(c=*op++)
          {
            wsAppendChar(ews,c);
            if (i<op_pos) k++;
          }
          i++;
        }
      }
      EDIT_SetTextToEditControl(data,4,ews);
      EDIT_SetCursorPos(data,k+1);
    }
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    if (req_recalc)
    {
      char revpn[256];
      req_recalc=0;
      calc_answer();
      sprintf(revpn, calc_set.fmt, d_answer);
      wsprintf(ews, revpn);
      EDIT_SetTextToEditControl(data,2,ews);
    }
  }
  if (cmd==TI_CMD_FOCUS)
  {
    DisableIDLETMR();
  }
}

HEADER_DESC ed1_hdr={0,0,0,0,NULL,(int)"Calculator",LGP_NULL};

SOFTKEY_DESC menu_sk[] =
{
  {0x0018, 0x0000, (int)"Options"},
  {0x0001, 0x0000, (int)"Close"},
  {0x003D, 0x0000, (int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt =
{
  menu_sk, 0
};

INPUTDIA_DESC ed1_desc=
{
  1,
  ed1_onkey,
  ed1_ghook,
  (void *)ed1_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,

//  0x00000001 - Выровнять по правому краю
//  0x00000002 - Выровнять по центру
//  0x00000004 - Инверсия знакомест
//  0x00000008 - UnderLine
//  0x00000020 - Не переносить слова
//  0x00000200 - bold
  0,

//  0x00000002 - ReadOnly
//  0x00000004 - Не двигается курсор
  0x40000000 // Поменять местами софт-кнопки
};


int create_ed(void)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;

  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  
  wsprintf(ews,percent_t,"Answer:");
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);  // 1
  
  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,0,128);
  AddEditControlToEditQend(eq,&ec,ma);  // 2   Ответ 
  
  wsprintf(ews,percent_t,"----------");
  ConstructEditControl(&ec,ECT_HEADER,0x40,ews,ews->wsbody[0]);
  AddEditControlToEditQend(eq,&ec,ma);   // 3

  ConstructEditControl(&ec,ECT_NORMAL_TEXT,0x40,0,128);
  AddEditControlToEditQend(eq,&ec,ma);  // 4 

  patch_header(&ed1_hdr);
  patch_input(&ed1_desc);
  return CreateInputTextDialog(&ed1_desc,&ed1_hdr,eq,1,0);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
    if ((int)msg->data0==chtype_gui_id)
    {
      chtype_gui_id=0;
    }
  }
  return(1);
}

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  ews=AllocWS(256);
  ReadCalcSettings();
  csm->gui_id=calc_gui_id=create_ed();
}

void maincsm_onclose(CSM_RAM *csm)
{
  WriteCalcSettings();
  FreeWS(ews);
  SUBPROC((void *)Killer);
}

const int minus11=-11;

unsigned short maincsm_name_body[20];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
    maincsm_onmessage,
    maincsm_oncreate,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose,
sizeof(MAIN_CSM),
1,
&minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), "SCalka");
}


int main(const char *elf_name, const char *fname)
{
  MAIN_CSM csm;
  UpdateCSMname();
  LockSched();
  CreateCSM(&MAINCSM.maincsm,&csm,0);
  UnlockSched();
  return 0;
}

