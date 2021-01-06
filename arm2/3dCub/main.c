#include "..\inc\swilib.h"
//#include "..\inc\local_ipc.h"
#include "../inc/xtask_ipc.h"
#include "main.h"
//#include "language.h"
#include "print.h"
#include "math.h"

const char _s[]="%s";

#pragma inline=forced
int toupper(int c)
{
  if((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strncmpNoCase(const char *s1,const char *s2,unsigned int n)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))&&(--n)) if (!c) break;
  return(i);
}


#define ITEMS 10

typedef struct
{
  float x;
  float y;
  float z;
}CRD;

float side=0.5;
float OX=0.0,OY=0.0;
float xt[10], yt[10];   
float xt2[10], yt2[10];   
CRD crd[]=
{
 {20.0, 20.0, 20.0},
 {70.0, 20.0, 20.0},
 {70.0, 70.0, 20.0},
 {20.0, 70.0, 20.0},
 {20.0, 20.0, 20.0},
 {20.0, 20.0,-20.0},
 {70.0, 20.0,-20.0},
 {70.0, 70.0,-20.0},
 {20.0, 70.0,-20.0},
 {20.0, 20.0,-20.0}
};

CRD crd2[]=
{
 {20.0, 20.0, 20.0},
 {70.0, 20.0, 20.0},
 {70.0, 70.0, 20.0},
 {20.0, 70.0, 20.0},
 {20.0, 20.0, 20.0},
 {20.0, 20.0,-20.0},
 {70.0, 20.0,-20.0},
 {70.0, 70.0,-20.0},
 {20.0, 70.0,-20.0},
 {20.0, 20.0,-20.0}
};

void line(int x,int y,int x2,int y2)
{
  DrawLine(x,y,x2,y2,0,"\xFF\xFF\xFF\x64");  
}
GBSTMR timer;
void *canvasdata;
void Draw1Cub()
{
  float OldX,OldY,OldZ;
  float  a=0.05, b=0.01, c=0.03;
 
  for(int i=0; i<ITEMS; i++)
   {
     xt[i]=( crd[i].x*side) + (ScreenW()/2)  + OX;
     yt[i]=(-crd[i].y*side) + (ScreenH()/2) - OY;
   }

  for (int i=0; i<ITEMS-1; i++)
    line (xt[i], yt[i], xt[i+1], yt[i+1]);

  for(int i=0;i<4;i++)
    line (xt[i], yt[i], xt[i+5], yt[i+5]);


  for(int i = 0; i < ITEMS; i++)
   {
     OldX = crd[i].x;
     //crd[i].x = crd[i].x * cos(a) - crd[i].y * sin(a);
     //crd[i].y = OldX * sin(a) + crd[i].y * cos(a);

     OldZ = crd[i].z;
     crd[i].z = OldZ * cos(b) - crd[i].x * sin(b);
     crd[i].x = OldZ * sin(b) + crd[i].x * cos(b);

     OldY = crd[i].y;
     crd[i].y = OldY * cos(c) - crd[i].z * sin(c);
     crd[i].z = OldY * sin(c) + crd[i].z * cos(c);
   }  
}

void Draw2Cub()
{
  float OldX,OldY,OldZ;
 float  a=0.05, b=0.01, c=0.03;
 
  for(int i=0; i<ITEMS; i++)
   {
     xt2[i]=( crd2[i].x*side) + (ScreenW()/2)  + OX;
     yt2[i]=(-crd2[i].y*side) + (ScreenH()/2) - OY;
   }

  for (int i=0; i<ITEMS-1; i++)
    line (xt2[i], yt2[i], xt2[i+1], yt2[i+1]);

  for(int i=0;i<4;i++)
    line (xt2[i], yt2[i], xt2[i+5], yt2[i+5]);


  for(int i = 0; i < ITEMS; i++)
   {
     OldX = crd2[i].x;
     //crd[i].x = crd[i].x * cos(a) - crd[i].y * sin(a);
     //crd[i].y = OldX * sin(a) + crd[i].y * cos(a);

     OldZ = crd2[i].z;
     crd2[i].z = OldZ * cos(b) - crd2[i].x * sin(b);
     crd2[i].x = OldZ * sin(b) + crd2[i].x * cos(b);

     OldY = crd2[i].y;
     crd2[i].y = OldY * cos(c) - crd2[i].z * sin(c);
     crd2[i].z = OldY * sin(c) + crd2[i].z * cos(c);
   }  
}
int g=0;
static void OnRedraw(MAIN_GUI *data)
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  DrawRoundedFrame(0,0,ScreenW()-1,ScreenH()-1,0,0,0,"\x00\x00\x00\x64","\x00\x00\x00\x64");
  
  Draw1Cub();
 // Draw2Cub();
  g++;
  if(g==4)
  {
  side+=0.01;
  g=0;
  }
  char *s=malloc(64);
  sprintf(s,"X=%3.2f Y=%3.2f Scale=%3.4f", OX,OY,side);
  PrintField(2,ScreenH()-GetFontYSIZE(8)-5,s,0,108,1);
  mfree(s);
  GBS_StartTimerProc(&timer,10,OnRedraw);
}
static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  SetCanvasFlag(1);
  data->gui.state=1;
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  GBS_DelTimer(&timer);
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  DirectRedrawGUI(); 

  if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
    switch(msg->gbsmsg->submess)
    {
     case RIGHT_BUTTON : OX+=10; break;
     case LEFT_BUTTON : OX-=10; break;
     case DOWN_BUTTON : OY-=10; break;
     case UP_BUTTON : OY+=10; break;
     case '*' : case VOL_DOWN_BUTTON: if(side>0.1) side-=0.1; else side=0.1; break;
     case '#' : case VOL_UP_BUTTON: side+=0.10; break;
     case RED_BUTTON: case RIGHT_SOFT: return 1;   
    }
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  (void *)kill_data,
  (void *)method8,
  (void *)method9,
  0
};


const RECT Canvas={0,0,0,0};
int menus_id;
static void maincsm_oncreate(CSM_RAM *data)
{
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  menus_id = csm->gui_id=CreateGUI(main_gui);   
}


//---------------------------------------------------------------------------//

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}


void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)
{  
  GBS_DelTimer(&timer);
  SUBPROC((void *)ElfKiller);
}


static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }

  return(1);
}


static const struct
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"3dCub");
}


int main(char *exename, char *fname)
{ 
  MAIN_CSM main_csm;
//  InitConfig();
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();

  PrintLibInit(1);
  return 0;
}

