#include "swilib.h"
const int minus11=-11;

extern int myf(int a, int b, int r);
extern void cpyscr(short *src, short *dst);

GBSTMR tmr;

unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

int x0 = 50;
int y0 = 50;
int r = 30;
int f = 2;

short screen[240*320], dst[240*320];
IMGHDR  img;

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

inline void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

inline void DrawLinza()
{
  int i,j;
  for (i=0; i<320; i++)
  {
    for (j = 0; j < 240; j++)
    {
      if (((j-x0)*(j-x0) + (i-y0)*(i-y0)) <= (r*r))
      {
        dst[i*240+j] = screen[myf(y0,i,f)*240+myf(x0,j,f)];
      }
      else
      {
        dst[i*240+j] = screen[i*240+j];
      }
    }
  }
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  DrwImg(&img, 0, 0, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(2));  
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}


int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {      
   int bt=msg->gbsmsg->submess;
    switch(bt)
    {
    case '2':
      {
        f++;
        DrawLinza();
        REDRAW();
      }break;
    case '8':
      {
        f--;
        DrawLinza();
        REDRAW();
      }break;
    case '4':
      {
        r--;
        DrawLinza();
        REDRAW();
      }break;
    case '6':
      {
        r++;
        DrawLinza();
        REDRAW();
      }break;
    case RED_BUTTON:
      return(1); 
    case RIGHT_BUTTON:
      {
          x0++;
          DrawLinza();
          REDRAW();
      }
        break;
     case LEFT_BUTTON:
       {
           x0--;
           DrawLinza();
           REDRAW();
       }
        break;        
      case UP_BUTTON:
        {
            y0--;
            DrawLinza();
            REDRAW();
        }
        break;
    case DOWN_BUTTON:
      {
          y0++;
          DrawLinza();
          REDRAW();
      }break;
    }
  }
  if (msg->gbsmsg->msg==LONG_PRESS)
  {
    int bt=msg->gbsmsg->submess; 
    switch(bt)
    {
    case '4':
      {
        r-=5;
        DrawLinza();
        REDRAW();
      }break;
    case '6':
      {
        r+=5;
        DrawLinza();
        REDRAW();
      }break;
    case UP_BUTTON:
      {
        y0-=5;
        DrawLinza();
        REDRAW();
      }break;
    case DOWN_BUTTON:
      {
        y0+=5;
        DrawLinza();
        REDRAW();
      }break;
    case LEFT_BUTTON:
      {
        x0-=5;
        DrawLinza();
        REDRAW();
      }break;
    case RIGHT_BUTTON:
      {
        x0+=5;
        DrawLinza();
        REDRAW();
      }
    }
  }
  return(0);
}


extern void kill_data(void *p, void (*func_p)(void *));


int method8(void){return(0);}


int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
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

inline void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"sssss");
}

void tmr_proc()
{
  cpyscr(RamScreenBuffer(), (short*)screen);
  DrawImg(0,0,1);  
  img.w=ScreenW()-1;
  img.h=ScreenH()-1;
  img.bpnum = 8;
  img.bitmap = (char*)dst;
  DrawLinza();
  GBS_StopTimer(&tmr); 
}

int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  UpdateCSMname();

  GBS_StartTimerProc(&tmr, 648, tmr_proc);    
  return 0;
}
