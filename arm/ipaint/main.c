#include "C:\arm\inc\swilib.h"
#include "main.h"
#include "bmp/bmp.h"

const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
  BMP_HDR hdr;
  int x=0,y=0;
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
  WSHDR *ws5;
  int i1;
}MAIN_GUI;
const char color[4]={0,0,255,0};


static void OnRedraw(MAIN_GUI *data)//Перерисовка во время загрузки
{
  DrawRectangle(0,0,239,319,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(0));
  WSHDR * ws=AllocWS(256);
  switch(mode)
  {
  case 1:
    DrawRectangle(0,0,239,319,2,color,color);
    
    wsprintf(ws,"File:%s Bit:%d\nWidth:%d Height:%d",hdr.fname,hdr.MAP_HEAD.bibitcount,hdr.MAP_HEAD.biwidth,hdr.MAP_HEAD.biheight);
    DrawString(ws,0,0,239,319,9,2,GetPaletteAdrByColorIndex(2),0);
    
    
    break;
  case 0:DrwImg(hdr.img,x,y);break;
  }
  FreeWS(ws);
}
static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))//Тут делаем что либо при создании гуи
{
  #ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
  #endif
  data->ws1=AllocWS(256);//Выделяем память под строку
  data->gui.state=1;
}
static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))//Сдесь делаем что нить при закрытии гуи:)
{
  data->gui.state=0;
  FreeWS(data->ws1);//например, освобождаем память
  FreeWS(data->ws5);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

static int OnKey(MAIN_GUI *data, GUI_MSG *msg)//Ну это кей хук
{

  switch(msg->gbsmsg->msg)
  {      
  case KEY_UP: break;
    case LONG_PRESS: // Клавиша удерживается долго (повтор)
    case KEY_DOWN: // Клавиша нажата
      
 switch(msg->gbsmsg->submess)
  {
  case RIGHT_SOFT: return 1; // Выход RIGHT_SOFT
  case LEFT_SOFT:if(mode==1)mode=0;else mode=1;DirectRedrawGUI();break;
  case '4':x+=20;DirectRedrawGUI();break;
  case '6':x-=20;DirectRedrawGUI();break;
  case '2':y+=20;DirectRedrawGUI();break;
  case '8':y-=20;DirectRedrawGUI();break;
  case GREEN_BUTTON:break;
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

static void maincsm_oncreate(CSM_RAM *data)
{
  
static const RECT Canvas={0,0,239,319};
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
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
  mfree(hdr.img->bitmap);
  mfree(hdr.Bitmap);
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
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


void DrwImg(IMGHDR *img, int x, int y)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  DrawObject(&drwobj);
}

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"ipaint");
}




int main(char *exename, char *fname)
{

  hdr=readBmp(fname);
  SaveBmp(hdr.img,"4:\\test.bmp");
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  return 0;
}


