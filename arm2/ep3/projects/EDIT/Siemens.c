// Siemens.c 0.5 cbn(c) SGOLD 1,2,3 вместе! :) +FreeRam
// http://cbn.narod.ru  e-mail: cbn@yandex.ru
// Интерфейс мобилы для IAR
// Здесь ничего не трогаем! (если не уверены)
// #define NEWSGOLD //ДОЛЖНО БЫТЬ ЗАДАНО ВСЕГДА!
// т.к. тип мобилы определяется автоматически
// Если экран в приложении объявлен как short *screen, то нужно указать и #define HIGHCOLOR
// Внешние функции вызываются при:

//#define DLL //для обработки elf2dll

extern int onstart(char *exename, char *fname); // Старте приложения. Возвращает 0 или 1 для выхода.
extern void oncreate(); // Создании окна
extern void onclose(); // Закрытии окна
extern void onexit(); // Выходе
extern void onredraw(); // Перерисовке экрана
extern int onkey(unsigned char keycode, int pressed); // Нажатии клавиши. Возвращает 0 или 1 для выхода.
extern char *Title;
extern const char *errors[]; //строки ошибок для кодов возврата
char *msgerror=0; //текст ошибки при выходе

//#define RAMSCREEN
//экран в памяти
//#define FREERAM
// FREERAM задает нестандартное использ. памяти
#ifdef FREERAM
  extern int isFreeRam(char *exename, char *fname); //1=использ.FreeRam, 0=нет
  extern void FreeRamInit(char *exename);
  extern void FreeRamExit();
  unsigned char USERAM=0; //использ. ли FreeRam
#endif
//#define HIGHCOLOR
#include <swilib.h>
//#include "addons.h"
//#define NEWSGOLD
// HIGHCOLOR задает 16 битный режим (RGB 565 по 2 байта на точку экрана screen)
// или 8 битный режим (RGB 232 по 1 байту на точку)
#ifdef HIGHCOLOR
  #define scrtype short
  #define scrtypedat 8
#else
  #define scrtype char
  #define scrtypedat 5
#endif

unsigned char SGOLD2=0, C65=0, S75=0, EL71=0;
#ifdef DEBUG
  unsigned char debug=0;
#endif
extern unsigned int err;
int width=132, height=176, screensize;

scrtype *screen=0;//[width*height];
unsigned char img[12]={132,176,scrtypedat,0,0,0};
//IMGHDR img = {132, 176, scrtypedat,0,0};

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

typedef struct{
//#ifdef NEWSGOLD
//  int pid_from;
//  int msg;
//#else
  short pid_from;
  short msg;
//#endif
  int submess;
  void *data0;
  void *data1;
} GBSS_MSG;

void UpdateCSMname();
void DrawScreen(){
#ifndef RAMSCREEN
  RECT rc;  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,0,EL71?24:0,width,height);
  SetPropTo_Obj5(&drwobj,&rc,0,(IMGHDR*)&img);
  SetColor(&drwobj,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  DrawObject(&drwobj);
#endif
}

//FAKES delete!!!
//void *memset(void *mem, int val, int size){ return 0;}
//void *memcpy(void *to, const void *from, int size){return 0;}


void method0(MAIN_GUI *data){ onredraw(); DrawScreen();}
void method1(MAIN_GUI *data, void *(*malloc_adr)(int)){  oncreate(); data->gui.state=1;}
void method2(MAIN_GUI *data, void (*mfree_adr)(void *)){  data->gui.state=0;}
void method3(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *)){
#ifndef NOIDLETMR
  DisableIDLETMR();// это чтобы эльф не выкл. через 2 минуты
#endif
  data->gui.state=2;
}
void method4(MAIN_GUI *data, void (*mfree_adr)(void *)){ if (data->gui.state!=2) return; data->gui.state=1;}
int method5(MAIN_GUI *data, GUI_MSG *msg){
  if(SGOLD2) return onkey(msg->gbsmsg->submess, msg->gbsmsg->msg);
  return onkey(((GBSS_MSG*)msg->gbsmsg)->submess, ((GBSS_MSG*)msg->gbsmsg)->msg);}
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

RECT Canvas={0,0,131,175};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=(MAIN_GUI *)malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
 // ustk=malloc(STKSZ); // Выделяем память
 // info_ws=AllocWS(512);
  if(EL71){ Canvas.x2=239; Canvas.y2=319;}//added

  main_gui->gui.canvas=(RECT*)((void *)(&Canvas));
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  UpdateCSMname();
}

//#ifdef CPP
//#define externC extern "C"
//#else
//#define externC extern
//#endif


void Killer(void){
  onexit();
#ifdef RAMSCREEN
  if(C65)
#endif
  if(screen) mfree(screen); //screen=0; //moved
#ifdef FREERAM
  ////if(USERAM)
    FreeRamExit();
#endif
#ifndef DLL
  kill_elf();
#endif
//  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void maincsm_onclose(CSM_RAM *csm)
{
  onclose();
#ifdef DLL
  Killer();
#else
  SUBPROC((void *)Killer);
#endif
}

//int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg){
//  MAIN_CSM *csm=(MAIN_CSM*)data;
//  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
//     csm->csm.state=-3;
//  return(1);
//}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *ms){
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if(SGOLD2){
    if ((ms->msg==MSG_GUI_DESTROYED)&&((int)ms->data0==csm->gui_id))
     csm->csm.state=-3;
  }else{
    GBSS_MSG *msg=(GBSS_MSG *)ms;
    if ((msg->msg==0x98)&&((int)msg->data0==csm->gui_id))
     csm->csm.state=-3;
  }
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

inline void UpdateCSMname(){
  wsprintf((WSHDR *)&MAINCSM.maincsm_name,Title);
}

int main(char *exename, char *fname){
  char dummy[sizeof(MAIN_CSM)];
  char *s;
  int f;
#ifdef DEBUG
  if((f=_open("0:\\ZBin\\DEBUG",A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    debug=1; _close(f,&err);
  }
#endif
  if((f=_open("0:\\ZBin\\SGOLD",A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    _close(f,&err);
  }else{
  if((f=ScreenH())<176) C65=1; //C65
  else if(f>176){ EL71=SGOLD2=1; //EL71
    *(short*)img=width=240; *(short*)(img+2)=height=296;
    img[4]=scrtypedat;
  }else{
    if(s=(char*)malloc(2500000)){
      mfree(s); S75=SGOLD2=1; //S75
    }
  }
  }
#ifdef FREERAM
  if((f=_open("0:\\ZBin\\NEWSGOLD",A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    _close(f,&err);
  }else
    if(USERAM=isFreeRam(exename,fname)) FreeRamInit(exename);//!SGOLD вместо EL
#endif
#ifdef RAMSCREEN
  if(C65){
#endif
  if(!(*(long*)(img+(EL71?8:4))=(long)(screen=(scrtype*)malloc(screensize=width*height*sizeof(scrtype))))){
    ShowMSG(1,(int)"NoMemory");
   #ifdef DLL
     Killer();
   #else
     SUBPROC((void *)Killer);
   #endif
    return 0;
  }
#ifdef RAMSCREEN
  }else screen=RamScreenBuffer()+(EL71?(24*240):0);
#endif
  memset(screen,0,screensize);
  if(f=onstart(exename,fname)){
    char buf[128];
    sprintf(buf,"%s Ошибка %d", (msgerror)?msgerror:errors[f], f);
    ShowMSG(1,(int)buf);
//#ifdef FREERAM
//    if(USERAM) FreeRamExit();
//#endif
  #ifdef DLL
  Killer();
  #else
  SUBPROC((void *)Killer);
  #endif
  }else{
    if(!SGOLD2) memcpy(((char*)&MAINCSM.maincsm)+8,((char*)&MAINCSM.maincsm)+24,sizeof(CSM_DESC)-24);
    CreateCSM(&MAINCSM.maincsm,dummy,0);
  }
  return 0;
}

