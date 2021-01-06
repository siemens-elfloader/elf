
// Siemens.c 0.1
// Интерфейс мобилы для IAR
// Здесь ничего не трогаем! (если не уверены)
// Внешние функции вызываются при:
extern int onstart(char *exename, char *fname); // Старте приложения. Возвращает 0 или 1 для выхода.
extern void oncreate(); // Создании окна
extern void onclose(); // Закрытии окна
extern void onexit(); // Выходе
extern void onredraw(void); // Перерисовке экрана
extern int onkey(unsigned char keycode, int pressed); // Нажатии клавиши. Возвращает 0 или 1 для выхода.

// В swilib.h комментируем // строку #define NEWSGOLD если не S75
#include "E:\ARM\swilib.h"
// Следующая строка задает 16 битный режим (RGB 565 по 2 байта на точку экрана screen)
// закомментировав получим 8 битный режим (RGB 232 по 1 байту на точку)
#define HIGHCOLOR
#ifdef HIGHCOLOR
  short screen[132*176];
  const int screensize=132*176*sizeof(short);
  const IMGHDR img = {(unsigned)132,(unsigned)176,8,0,(char*)screen};
#else
  char screen[132*176];
  const int screensize=132*176*sizeof(char);
  const IMGHDR img = {(unsigned)132,(unsigned)176,5,0,(char*)screen};
#endif

// Ниже читать уже не надо! :)
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void DrawScreen(){
  RECT rc;  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,0,0,img.w,img.h);
  SetPropTo_Obj5(&drwobj,&rc,0,(IMGHDR*)&img);
  SetColor(&drwobj,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  DrawObject(&drwobj);
}
void method0(MAIN_GUI *data){  onredraw(); DrawScreen();}
void method1(MAIN_GUI *data, void *(*malloc_adr)(int)){  oncreate(); data->gui.state=1;}
void method2(MAIN_GUI *data, void (*mfree_adr)(void *)){  data->gui.state=0;}
void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){  data->gui.state=2;}
void method4(MAIN_GUI *data, void (*mfree_adr)(void *)){ if (data->gui.state!=2) return; data->gui.state=1;}
int method5(MAIN_GUI *data, GUI_MSG *msg){
  return onkey(msg->gbsmsg->submess, msg->gbsmsg->msg);}
void method7(MAIN_GUI *data, void (*mfree_adr)(void *)){}//  mfree_adr(data);
int method8(void){return(0);} // Пустая ф-я
int method9(void){return(0);} // Пустая ф-я

const void * const gui_methods[11]={
  (void *)method0,	//Redraw
  (void *)method1,	//Create
  (void *)method2,	//Close
  (void *)method3,	//Focus
  (void *)method4,	//Unfocus
  (void *)method5,	//OnKey
  0,
  (void *)method7,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,131,175};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
 // ustk=malloc(STKSZ); // Выделяем память
 // info_ws=AllocWS(512);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void Killer(void){
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  onexit();
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
//  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void maincsm_onclose(CSM_RAM *csm)
{
  onclose();
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg){  
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
     csm->csm.state=-3; 
  return(1);
}

const int minus11=-11;
unsigned short maincsm_name_body[140];

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

int main(char *exename, char *fname){
  char dummy[sizeof(MAIN_CSM)];
  if(onstart(exename,fname)) SUBPROC((void *)Killer);
  else CreateCSM(&MAINCSM.maincsm,dummy,0);
  return 0;
}

