#include "..\inc\swilib.h"
#define DEBUG
// попытка сделать эффект горящего пламени
// автор начала Feanor
// далее уже пытаюсь развивать я (Z80)
// этот эльф не является заставкой или там для чего то подобного
// просто мне интересно вот и занимаюсь
const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
#ifdef ELKA
#define width 240
#define height 320
#else
#define width 132
#define height 176
#endif


int maxx=200;
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

  short screen[width*height];
  short screen2[width*height];
  int Rc=0;
  int Gc=0;
  int Bc=0;
  int countpallet=0;
  int palletka[256];
  
int rgb2bitmap16 (R,G,B)  // (c) mirr
{
  return ((B>>3)+((G>>2)<<5)+((R>>3)<<11));
}

/////////////////////////////// создадим палитру
void createpallet ()

{
for (int i=1; i<255; i++)
{
  palletka[i]=65535;
}

int ix=0;
 for (int i=1; i<85; i++)  // с черного в красный
{
Rc= ix;
countpallet++;
palletka [countpallet]= rgb2bitmap16 ( Rc, Gc,Bc);
ix++;
ix++;
ix++;

}

ix=0;
 for (int i=1; i<85; i++)  // с красного в желтый
{
    Gc= ix;


  countpallet++;
palletka [countpallet]= rgb2bitmap16 (Rc,Gc,Bc);
ix++;
ix++;
ix++;


}
ix=0;

 for (int i=1; i<85; i++)  // с желтого в белый
{
Bc=ix;
countpallet++;
palletka [countpallet]= rgb2bitmap16 (Rc,Gc,Bc);
ix++;
ix++;
ix++;

}


}



void filtr ()  // отфильтруем через палитру
{
int  indexcolor;
int indexx;

  for (int i=0; i<width*height; i++)
  {
    indexx= screen[i];
    indexcolor= palletka [indexx];
    screen2 [i]=indexcolor;
  }
}

//================================================================
unsigned int randseed;
#define random randint
#define randomize Randomize
unsigned int randint( int max )
{
  randseed *=0x08088405;
  randseed++;
  return (  (randseed % max)  );
}
void Randomize(){ // Вызываем при старте для случайной последовательности
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  //rndindex = (unsigned char)time.param;
  randseed=(time.min | (time.sec<<5));
}
//================================================================

  IMGHDR img; 
  GBSTMR timer;
void timer_proc(void){DirectRedrawGUI(); GBS_StartTimerProc(&timer,15,timer_proc);}
inline void SetPix(int x,int y,int cl)
{  
  if(x<0 || x>width-1 || y<1 || y>height) return;
  //cl--;
  if (cl<0) cl=0;
  else screen[x+y*width] =cl;
}
inline short GetPix(int x,int y)
{  
  return screen[x+y*width];
}

inline void Init()
{
  for (int i=1; i!=width-1; i++)
  {
    SetPix(i,height-1,randint(255));
  }
}
int clor=0;
void OnRedraw(MAIN_GUI *data)
{  
  Init();
int ypos=height-2;
  for(int x=0; x!=width; x++)
  {
        clor=((GetPix(x-1,ypos+1)+GetPix(x,ypos)+GetPix(x,ypos+1)+GetPix(x+1,ypos+1))/4);
        if (clor==GetPix(x,ypos)) clor=0;
        SetPix(x,ypos,clor);
      }
  for(int y=height-3; y!=1; y--)
      {
  for(int x=0; x!=width; x++)
  {
     clor=((GetPix(x-1,y+2)+GetPix(x,y)+GetPix(x,y+2)+GetPix(x+1,y+2))/4);
        if (clor==GetPix(x,y)) clor=0;
        if (clor<0) clor=0;
        SetPix(x,y,clor);
      }
  } 
  
  filtr ();
  
  
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,0,0,img.w,img.h);
  SetPropTo_Obj5(&drwobj,&rc,0,&img);
  DrawObject(&drwobj);
}
void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  createpallet ();
#ifdef ELKA
  DisableIconBar(1);
#endif
  Init();
  data->gui.state=1;
  img.bpnum=8;
  img.w=width;
  img.h=height;
  img.bitmap=(void*)screen2;
  timer_proc();
}
void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
  GBS_StopTimer(&timer);
}
void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}
void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}
int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case  RIGHT_SOFT : return(1);
    case '2':maxx+=10;break;
    case '8':maxx-=10;break;
    }
  }
  return(0);
}
extern void kill_data(void *p, void (*func_p)(void *));
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
kill_data(data,mfree_adr);
}

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
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,	
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,width-1,height-1};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
}
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}
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
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Flame");
  FreeWS(ws);
}
int main(char *exename, char *fname)
{
  

  
  
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  UpdateCSMname();
  Randomize();
  return 0;
}
