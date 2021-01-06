#include "C:\arm\inc\swilib.h"
//Мой второй эльф-написан с нуля!!

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






__arm void RedrawScreen()//Собственно функция перерисовки процесса игры
{
 GBSTMR tmr;
  char bgcol[4]={255,0,0,255};
  WSHDR *str = AllocWS(64);
  DrawRoundedFrame(0,0,ScreenW(),ScreenH(),0,0,0,NULL,bgcol);
  wsprintf(str,"%t","Выберите диск для установки Elfpack.bcfg");
  DrawString(str,1, 50 ,239,320,9,4,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  GBS_StartTimerProc(&tmr,20,RedrawScreen);
}




static void OnRedraw(MAIN_GUI *data)//Перерисовка во время загрузки
{}
__arm static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))//Тут делаем что либо при создании гуи
{
  #ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
  #endif
  data->ws1=AllocWS(256);//Выделяем память под строку
  data->gui.state=1;
}
__arm static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))//Сдесь делаем что нить при закрытии гуи:)
{
  //GBS_DelTimer(&tmr);//Убиваем таймеры
  data->gui.state=0;
  FreeWS(data->ws1);//например, освобождаем память
  FreeWS(data->ws5);
}

__arm static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
}

__arm static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
  //GBS_DelTimer(&tmr);//Убиваем таймеры

  if (data->gui.state!=2) return;
  data->gui.state=1;
}

__arm static int OnKey(MAIN_GUI *data, GUI_MSG *msg)//Ну это кей хук
{

  switch(msg->gbsmsg->msg)
  {      
  case KEY_UP: break;
    case LONG_PRESS: // Клавиша удерживается долго (повтор)
    case KEY_DOWN: // Клавиша нажата
      
 switch(msg->gbsmsg->submess)
  {
   case GREEN_BUTTON: RedrawScreen(); break;
   case RIGHT_SOFT: return 1; // Выход RIGHT_SOFT
  }
  
  
       switch(msg->gbsmsg->submess)
         { 
         
         case LEFT_SOFT:  break;
         case RED_BUTTON: break;
         
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

__arm static void maincsm_oncreate(CSM_RAM *data)
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

__arm void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

__arm static void maincsm_onclose(CSM_RAM *csm)
{
  
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

__arm static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{

  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
 if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    
  }
  return(1);
}

__no_init const int minus11=-11;
__no_init unsigned short maincsm_name_body[140];
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

__arm void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"install elfpack");
}

__arm int starter()
{
   
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  RedrawScreen();
  return 0;
}

