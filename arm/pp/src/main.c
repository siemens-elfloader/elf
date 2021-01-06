/*
* (c) Danil e71
* 2009 - 2010
* Спасибо огромное за помощь в разработке Half, Gangster
* Tails [sc], Snoop-Cat и многим другим за тестирование
* Dj_Shell за графику
* http://team-sc.ru/
* http://code.google.com/p/sieelf-dev/
*/

#include "..\inc\swilib.h"
#include "conf_loader.h"
#include "rect_patcher.h"
#include "main.h"
#include "save.c"
#include "Redraw.c"
#include "pp.c"
#include "lang.c"
#include "keys.c"
#include "other.c"




static void OnRedraw(MAIN_GUI *data){}//Не использую)
static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))//Тут делаем что либо при создании гуи
{
  #ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
  #endif
  Time.str=malloc(24);
  data->ws1=AllocWS(256);//Выделяем память под строку
  data->gui.state=1;
}
static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))//Сдесь делаем что нить при закрытии гуи:)
{
  data->gui.state=0;
  mfree(Time.str);
  FreeWS(data->ws1);//например, освобождаем память
  FreeWS(data->ws5);
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
  #ifdef ELKA//Если елка,то отключаем иконбар
  DisableIconBar(1);
  #endif
  if(idle==0){RedrawScreen();idle=1;}
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
  UpdateCSMname();//обновляем имя для хтаска
  deltimers();
  if(idle==1)idle=0;
  if(status==load)exit();//антилаг
  if (data->gui.state!=2) return;
  data->gui.state=1;
}



static int OnKey(MAIN_GUI *data, GUI_MSG *msg)//Ну это кей хук
{
  switch(msg->gbsmsg->msg)
  {
   case KEY_UP: user.dx=STOP_SIDE; break;
   case LONG_PRESS: // Клавиша удерживается долго (повтор)
   case KEY_DOWN: // Клавиша нажата
         switch(msg->gbsmsg->submess)
         { 
         case RIGHT_SOFT:right_soft();break;
         case LEFT_SOFT:left_soft();break;
         case UP_BUTTON: case '2':up_but();break;
         case DOWN_BUTTON: case '8':down_but();break; 
         case ENTER_BUTTON:enter_but();break;
         case LEFT_BUTTON: case '4':left_but();break;
         case RIGHT_BUTTON: case '6':right_but();break;
         case GREEN_BUTTON:green_but();break; 
         case '0':if(status==game)setpause();break;  
         case '#':if(msg->gbsmsg->msg==LONG_PRESS)resh_but();break;
         }
         if(exiting) return 1;
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
  static const RECT Canvas={0,0,max_width-1,max_height-1};
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
  mfreeImages();
  mfreelang();
  deltimers();
  SetVibration(0);
  delimghdr();
  PlayMelody_StopPlayback(PLAY_ID);
  if(mode==0)savedata(1);
  SUBPROC((void *)ElfKiller);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{

  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
 if (msg->msg==MSG_RECONFIGURE_REQ)
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      InitConfig();
      RedrawScreen();
    }
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
  if (status==game)wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"%t: %d vs Cpu: %d ",name,user.lifetime,cpu.lifetime);
  else wsprintf((WSHDR *)(&MAINCSM.maincsm_name),perc_t,"Ping-Pong Last Edition");
}


int main()
{
  MAIN_CSM main_csm;
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  InitConfig();
  Init();
  return 0;
}
