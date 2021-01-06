
// Siemens.c 0.1 cbn(c) http://cbn.narod.ru  e-mail: cbn@yandex.ru
// Интерфейс мобилы для IAR
// Здесь ничего не трогаем! (если не уверены)
// Внешние функции вызываются при:
extern int onstart(char *exename, char *fname); // Старте приложения. Возвращает 0 или 1 для выхода.
extern void oncreate(); // Создании окна
extern void onclose(); // Закрытии окна
extern void onexit(); // Выходе
extern void onredraw(void); // Перерисовке экрана
extern int onkey(unsigned char keycode, int pressed); // Нажатии клавиши. Возвращает 0 или 1 для выхода.
extern char Title[];


// В swilib.h комментируем // строку #define NEWSGOLD если не S75
//#include "E:\ARM\swilib.h"
#include "mylib.h"
// HIGHCOLOR задает 16 битный режим (RGB 565 по 2 байта на точку экрана screen)
// или 8 битный режим (RGB 232 по 1 байту на точку)



//extern "C"{

FILE *ffopen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber);
int ffread(FILE *FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber);
unsigned int ffwrite(FILE *FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber);
void ffclose(FILE *FileHandler, unsigned int *ErrorNumber);
unsigned int llseek(FILE *FileHandler, unsigned int offset, unsigned int origin, unsigned int *ErrorNumber, unsigned int *ErrorNumber2);
void mfree(void *mem);

//}



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
  GUI2 gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

void UpdateCSMname();
void DrawScreen(){
//  RECT rc;  DRWOBJ drwobj;
//  StoreXYWHtoRECT(&rc,0,0,img.w,img.h);
//  SetPropTo_Obj5(&drwobj,&rc,0,(IMGHDR*)&img);
//  SetColor(&drwobj,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
//  DrawObject(&drwobj);
}
void method0(MAIN_GUI *data){ onredraw(); DrawScreen();}
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

const RECT2 Canvas={0,0,131,175};

void maincsm_oncreate(CSM_RAM *data)
{
//  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
//  MAIN_CSM*csm=(MAIN_CSM*)data;
//  zeromem(main_gui,sizeof(MAIN_GUI));
 // ustk=malloc(STKSZ); // Выделяем память
 // info_ws=AllocWS(512);
//  main_gui->gui.canvas=(void *)(&Canvas);
//  main_gui->gui.flag30=2;
//  main_gui->gui.methods=(void *)gui_methods;
//  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
//  csm->csm.state=0;
//  csm->csm.unk1=0;
//  csm->gui_id=CreateGUI(main_gui);
//  UpdateCSMname();
}

void Exit(void){
//  extern void *ELF_BEGIN;
//  extern void kill_data(void *p, void (*func_p)(void *));
  //onclose(); //add
  onexit();
//  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
//  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void maincsm_onclose(CSM_RAM *csm)
{
  onclose();
  Exit();
  //SUBPROC((void *)Exit);
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

inline void UpdateCSMname(){
//WSHDR *ws=AllocWS(256);
//wsprintf((WSHDR *)(&MAINCSM.maincsm_name),Title);
//FreeWS(ws);
}

int main(int argc, char **argv){
//  char dummy[sizeof(MAIN_CSM)];
  if(onstart(argv[0],argv[1])) 
    Exit(); ///SUBPROC((void *)Killer);
  else{ //CreateCSM(&MAINCSM.maincsm,dummy,0);
    oncreate();//
  }
  onclose(); 
  onexit();
  return 0;
}

//////////38
const char bmphead[]={
"\x42\x4D\xC6\xB5\x00\x00\x00\x00\x00\x00\x36\x00\x00\x00\x28\x00"
"\x00\x00\x84\x00\x00\x00\xB0\x00\x00\x00\x01\x00\x10\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x12\x0B\x00\x00\x12\x0B\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\xF8\x00\x00\xE0\x07\x00\x00\x1F\x00"
"\x00\x00\x00\x00\x00\x00"};

void savescreen(char *fname){
  FILE *f;
  int i;
  short scr[132*176], *s=screen;
  //for(i=0; i<132*176;i++,s++){
  for(i=132*176-1;i>=0;i--,s++){//reverse
    scr[i]=(*s&0x1f)|((*s>>1)&0xffe0);//RGB 555 convert! чтобы BMP корректно выглядело!
     //scr[i]=(*s);//<<4;//((*s&0xf)<<1)|((*s&0xf0)<<3)|((*s&0xf00)<<8);
  }// ИЗОБРАЖЕНИЕ здесь повернуто зеркально!!!
  if((f=ffopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==0) return;
  ffwrite(f,bmphead,sizeof(bmphead),&err); 
  ffwrite(f,scr,screensize,&err); 
  ffclose(f,&err); 
}



