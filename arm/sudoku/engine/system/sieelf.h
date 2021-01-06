const int minus11=-11;
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

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

extern void START_CONTROL();
extern void CREATE_CONTROL();
extern void MAXIMIZE_CONTROL();
extern void MINIMIZE_CONTROL();
extern void END_CONTROL();
extern void REDRAW_CONTROL();
extern void MESSAGES_CONTROL();
extern int KEY_CONTROL();


//Keys
#define KEYMSG  msg->gbsmsg->msg
#define KEYSMSG msg->gbsmsg->submess
#define GKEYEND goto KEYEND
#define NEXT return(0)
#define END return(1)


//#define LG_RECONFIG  "Реконфиг!"
//#define LG_FOR_SG    "Данный эльф\nдля SGold!"
//#define LG_FOR_NSG   "Данный эльф\nдля NewSGold!"
//#define LG_FOR_ELKA  "Данный эльф\nдля E/EL71!"


static void OnRedraw(MAIN_GUI *data)//эта функция нужна для перерисовки экрана,тут рисуем все что нам нужно
{
 REDRAW_CONTROL();
}

static void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  
  CREATE_CONTROL();
  data->gui.state=1;
}

static void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  END_CONTROL();
  data->gui.state=0;
}

static void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Если гуи на верху то опять же делаем что нужно
{
#ifdef ELKA
  DisableIconBar(1);
#endif
  
  data->gui.state=2;
  DisableIDLETMR();//отключаем таймер,иначе через 2 минуты эльф закроется
  MAXIMIZE_CONTROL();
  
}

static void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))//а если гуи не вверху,то можно закрыть эльф например:)
{
  MINIMIZE_CONTROL();
  if (data->gui.state!=2) return;
  data->gui.state=1;
}


static int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  return(KEY_CONTROL(msg)); 
}



extern void kill_data(void *p, void (*func_p)(void *));//Эта функция убивает эльф и освобождает память

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

static void maincsm_oncreate(CSM_RAM *data)//Вызывается при открытии эльфа,делаем что нужно
{
  static const RECT Canvas={0,0,0,0};
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,YDISP,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void ElfKiller(void)//освобождаем все занятое место эльфом в оперативе
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


static void maincsm_onclose(CSM_RAM *csm)//функция закрытия эльфа,тут освобождаем памчть если нужно и т.п.
{
  SUBPROC((void *)ElfKiller);
}


#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}

int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)//тут вообщем протекают все сообщения поступаемые из эльфа так сказать:)
{
  //сообщение о реконфигурации например,ипц и т.д. и т.п.
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  if (msg->msg==MSG_RECONFIGURE_REQ)//Елси была реконфигурация,то обновляем настройки эльфа
  {
    extern const char *successed_config_filename;
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
      //ShowMSG(1,(int)LG_RECONFIG);
      InitConfig();
    }
  }
  MESSAGES_CONTROL();

  return(1);
}


static const struct //это структура цсм,разбираться не надо:)
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




void UpdateCSMname(void)//ну собственно имя эльфа передаваемое хтаску
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),ELF_NAME);
}

int main(char *exename, char *fname)//exename-путь запускаемого эльфа, fname параметр передаваемый эльфу
{
#ifndef MULTISGOLD
  
  #ifdef SGOLD
  if (isnewSGold()!=0) ShowMSG(1,(int)LG_FOR_SG);
  if (isnewSGold()==0){
  #endif
  
  #ifdef NEWSGOLD
  #ifndef ELKA
  if (isnewSGold()!=1) ShowMSG(1,(int)LG_FOR_NSG);
  if (isnewSGold()==1){
  #endif
  #endif
    
  #ifdef ELKA
  if (isnewSGold()!=2) ShowMSG(1,(int)LG_FOR_ELKA);
  if (isnewSGold()==2){
  #endif
    
#endif
    
  START_CONTROL(exename, fname);

#ifndef MULTISGOLD 
  
  MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);//создаем цсм
  UnlockSched();
  }
  
#endif
  
  return 0;
}
