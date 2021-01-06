#include "../inc/swilib.h"
#include "gui.h"
#include "main.h"
#include "strings2.h"
#include "swaper.h"


typedef struct
{
  GUI gui;
  WSHDR *ws;
}SMILE_GUI;

extern int total_d;
extern NAMELIST * volatile nltop;
extern int main_poX;
extern int main_poY;
extern const unsigned int IDLET_X;
extern const unsigned int IDLET_Y;
extern char icon_text[];
int key_on;
int set_runit;
int total_idle_icons;
int icon_pos=1;

void SearchIcon2(WSHDR *ramed, int w, int show, int main_icon, int mainx, int mainy)
{
  char buffer[256];
  //ws_2str(ramed, buffer, 64);
  convWS_to_ANSI(ramed, buffer);
  if(strstr(buffer, "NATICQ")>0) strcpy(buffer, "NATICQ");
  if(strstr(buffer, "SieJC")>0) strcpy(buffer, "SieJC");
  if(strstr(buffer, "MC:")>0) strcpy(buffer, "MC");
  if(strstr(buffer, "BM:")>0) strcpy(buffer, "BM:");
  if(strstr(buffer, "Config:")>0) strcpy(buffer, "CfgEditor");
  if(main_icon) if(strstr(buffer, "IDLE")>0) strcpy(buffer, "navaico");
  char p2[]="||";
  char *s,*s1,*s2;
  int len;
  if((s1=strstr(icon_text,buffer))>0)
  {
    s1+=strlen(buffer);
    if((s2=strstr(s1,p2))>0)
    {
      len=s2-s1-1;
      s=malloc(len+1);
      strncpy(s,s1+1,len);
      s[len]='\0';
      if(main_icon)
      {
        DrawImg(mainx,mainy,(int)s);
        main_poX=main_poX+13;
        total_idle_icons++;
        if(key_on) set_runit=1;
      }
      else
      {
      if(show) DrawImg(17,w+1,(int)s);
      DrawImg(102,w+1,(int)s);
      }
      mfree(s);
    }
  }
}

static void method0(SMILE_GUI *data,void *(*malloc_adr)(int))
{
  total_d=GetNumberOfDialogs()-1;
  NAMELIST *nl=nltop;
  main_poX=IDLET_X;
  main_poY=IDLET_Y;
  total_idle_icons=0;
  DrawImg(IDLET_X-12+icon_pos*13,IDLET_Y,(int)"4:\\ZBin\\xtask3\\tasks.png");
  while(nl)
  {
    NAMELIST *p=nl;
    if(nl->is_daemon) { } else {
      set_runit=0;
      SearchIcon2(nl->name, main_poX, 0, 1, main_poX, main_poY);
      if(set_runit==1) CSMtoTop(((CSM_RAM *)(nl->p))->id,-1);
    }
    nl=p->next;
  }
}


static void method1(SMILE_GUI *data,void *(*malloc_adr)(int))
{
  data->ws=AllocWS(50);
  data->gui.state=1;
}

static void method2(SMILE_GUI *data,void (*mfree_adr)(void *))
{
  data->gui.state=0;
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
  int m=msg->gbsmsg->msg;
  int key=msg->gbsmsg->submess;
  if ((m==KEY_DOWN)||(m==LONG_PRESS))
  {
    if (key==RED_BUTTON||key==RIGHT_SOFT) return(1);
    if (key==LEFT_BUTTON) {icon_pos++; if (total_idle_icons<icon_pos) icon_pos--;}
    if (key==RIGHT_BUTTON) {icon_pos--; if (icon_pos==0) icon_pos++;}
    if (key==ENTER_BUTTON) {key_on=1; DirectRedrawGUI(); return(1);}
    DirectRedrawGUI();
  }
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

#pragma inline
void patch_rect(const RECT*rcc,int x,int y, int x2, int y2)
{
  RECT *rc=(RECT *)rcc;
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}

int CreateSmileSelectGUI()
{
  static const RECT Canvas={0,0,0,0};
  SMILE_GUI *smile_gui=malloc(sizeof(SMILE_GUI));
  zeromem(smile_gui,sizeof(SMILE_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  smile_gui->gui.canvas=(void *)(&Canvas);
  smile_gui->gui.methods=(void *)gui_methods;
  smile_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
//  smile_gui->ed_struct=ed_struct;
  return CreateGUI(smile_gui);
}
