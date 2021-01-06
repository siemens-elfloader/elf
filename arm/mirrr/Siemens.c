
#define NEWSGOLD 
#define ELKA




#include "swilib.h"

extern int onstart(char *exename, char *fname);       // Старте приложения. Возвращает 0 или 1 для выхода.
extern void oncreate();                               // Создании окна
extern void onclose();                                // Закрытии окна
extern void onexit();                                 // Выходе
extern void onredraw();                               // Перерисовке экрана
extern int onkey(unsigned char keycode, int pressed); // Нажатии клавиши. Возвращает 0 или 1 для выхода.
extern char *Title;
extern char Text_in_Editor[4000];
void odraw();
extern FONTINT *FontInt;
extern char fastfon;
///////////////////////////////////////////////////
extern IMGHDR *read_pngimg(const char *buf);
extern IMGHDR *read_jpgimg(const char *buf);
///////////////////////////////////////////////////
//extern char *Title2;
extern const char *errors[]; //строки ошибок для кодов возврата
char *msgerror=0; //текст ошибки при выходе
char closer=1; //количество открытых окон
//WSHDR *wsbuf;


#ifdef FREERAM
  extern int isFreeRam(char *exename, char *fname); //1=использ.FreeRam, 0=нет
  extern void FreeRamInit(char *exename);
  extern void FreeRamExit();
  unsigned char USERAM=0; //использ. ли FreeRam
#endif


  #define scrtype short


unsigned char SGOLD2=0, C65=0, S75=0, EL71=1;
#ifdef DEBUG
  unsigned char debug=0;
#endif
int scr_w=240, scr_h=320;  
int width=240, height=320, screensize;

scrtype *screens=0;//[width*height];
unsigned char img[12]={240,255,8,0,0,0};


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

  RECT rc;  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,0,EL71?24:0,width,height);
  SetPropTo_Obj5(&drwobj,&rc,0,(IMGHDR*)&img);
  SetColor(&drwobj,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
  DrawObject(&drwobj);
  odraw();
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

void maincsm_oncreate2(CSM_RAM *data)
{
  MAIN_GUI *main_gui2=(MAIN_GUI *)malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui2,sizeof(MAIN_GUI));
 // ustk=malloc(STKSZ); // Выделяем память
 // info_ws=AllocWS(512);
  if(EL71){ Canvas.x2=239; Canvas.y2=319;}//added
  
 // main_gui2->gui.canvas=(RECT*)((void *)(&Canvas));
  main_gui2->gui.flag30=2;
  main_gui2->gui.methods=(void *)gui_methods;
  main_gui2->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui2);
  UpdateCSMname();
}
//#ifdef CPP
//#define externC extern "C"
//#else
//#define externC extern
//#endif
externC void *ELF_BEGIN;
externC void kill_data(void *p, void (*func_p)(void *));

void Killer(void){
  onexit();
#ifdef RAMSCREEN
  if(C65)
#endif
  if(screens) mfree(screens); //screen=0; //moved
#ifdef FREERAM
  ////if(USERAM) 
    FreeRamExit();
#endif    
#ifndef DLL    
    
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
#endif  
//  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void maincsm_onclose(CSM_RAM *csm)
{
  if (closer<2){ 
  onclose();
#ifdef DLL  
  Killer();
#else  
  SUBPROC((void *)Killer);
#endif
  }
 closer--; 
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
unsigned short maincsm_name_body2[140];
const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
//#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
//#endif  
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
const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM2 =
{
  {
  maincsm_onmessage,
  maincsm_oncreate2,
  0,
  0,
  0,
  0,
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body2,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};
inline void UpdateCSMname(){
  wsprintf((WSHDR *)&MAINCSM.maincsm_name,Title);
//  wsprintf((WSHDR *)&MAINCSM2.maincsm_name,Title2);  
}

int main(char *exename, char *fname){
  char dummy[sizeof(MAIN_CSM)];
 // char dummy2[sizeof(MAIN_CSM)];  

 EL71=SGOLD2=1; //EL71
   int f;
 
 
 
 
    *(short*)img=width=240; 
    *(short*)(img+2)=height=296;
    img[4]=8;
 

  if(!(*(long*)(img+(8))=(long)(screens=(scrtype*)malloc(screensize=width*height*sizeof(scrtype))))){
    ShowMSG(1,(int)"NoMemory");
    SUBPROC((void *)Killer);
    return 0;
  }
  
  memset(screens,0,screensize);
  if(f=onstart(exename,fname)){
    char buf[128];
    sprintf(buf,"%s Ошибка %d", (msgerror)?msgerror:errors[f], f);
    ShowMSG(1,(int)buf);
    SUBPROC((void *)Killer);
  }else{
    if(!SGOLD2) memcpy(((char*)&MAINCSM.maincsm)+8,((char*)&MAINCSM.maincsm)+24,sizeof(CSM_DESC)-24);
  //  if(!SGOLD2) memcpy(((char*)&MAINCSM2.maincsm)+8,((char*)&MAINCSM2.maincsm)+24,sizeof(CSM_DESC)-24);    
    CreateCSM(&MAINCSM.maincsm,dummy,0);
//    CreateCSM(&MAINCSM2.maincsm,dummy2,2);    
  }
 
  
  
  
  
  
  
  
  
  
  

  
  
 //------------------------------------------------------------------------------------------------------------ 

  return 0;
}
                                 
