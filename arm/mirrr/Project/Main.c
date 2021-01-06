//#define INPUT_OK
#define HIGHCOLOR  // 16-битный режим
#define GRAPH      // Графика
//#define NEWSGOLD
//#define ELKA


#include "swilib.h"
#include "SWILIB.C"
#define paramlength 16
#ifdef ELKA
  #define width 240
  #define height 320
#else
  #define width 132
 #define height 176
#endif

extern  char devka[];
extern int test_dir();
IMGHDR *FImage;

//---------------------------------- Переменные ---------------------------------------------------

char *Title="Hello World!"; //ТО что видим в XTask
char *enter="\x0D\x0A";     //строка с переходом каретки
 WSHDR *maks;               //Cюда записываем текст перед выводом на екран


const char *errors[]={
  0,
  "Файл не обнаружен либо поврежден!\0",
  "Unknown error!"
};

volatile int running=0; // Процесс проверяет флаг и выходит если =0



//---------------------------------- Внешние переменные -------------------------------------------

extern short *screen;                          // Экран 240*320*2
extern int screensize;
extern void DrawScreen();                      // Функция перерисовки экрана
extern IMGHDR *read_pngimg(const char *buf);
extern char loggerCWILIB[512];
extern int s1,s2,s3,s4,s5;
extern int plott(char liter, int font, int x, int y, int fcolor);
extern void EditColors(char *color);
extern FLIST *AddToFList(const char* full_name, const char *name, int is_folder);
extern volatile FLIST *fltop;
extern int FindFiles(char *str, int type);
extern void open_fm();

 //extern int alabama;
void onredraw();
int mode=0; //1-menu, 0-desk
//---------------------------------- Временные переменные -----------------------------------------
 int curx=4, cury=1; //координаты синего квадратика

 



//==========================================================================================================
void drawcur(int curx, int cury, int color){
  int i;
  short *scr=screen+((7-cury)*15+6)*width+(7-curx)*15+6;
  memsetw(scr,curcolor,15);
  memsetw(scr+=width,curcolor,15);
  scr+=width;
  for(i=0;i<11;i++,scr+=width){
    *scr=scr[1]=scr[13]=scr[14]=color;
  }
  memsetw(scr,curcolor,15);
  memsetw(scr+width,curcolor,15);
}
//==========================================================================================================
inline void cls(){memsetw(screen,bkcolor,screensize>>1);}//menubkcolor
//================================================================= R E D R A W ===================================== = = = ====================
void onredraw(){ // Перерисовка экрана // записываем в Screen, а дальше будет видно
  DisIconbar(1);
 int i,j;
 cls();  
 
 
 // for(i=0;i<16;i++) for(j=0;j<16;j++) drawcur(curx,cury,curcolor);  

}
//==========================================================================================================

void odraw(){ // Перерисовка экрана //Screen на экран уже вывели теперь рисуем исчо чево

    wsprintf(maks,"Test resource image (c)mirrr, 2008");
    DrawRectangle(0,0,240,24,0, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(1));
    DrawString(maks,15,265,240,320,9,0x20,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(1));
    drawim(FImage,10,10,0,0,0,0);
    //DrawImg(0,0,(int)FImage);
  }


//=================================================================================================================== = = = ====================

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0;          // Клавиша отпущена
  case LONG_PRESS:                // Клавиша удерживается долго (повтор)
   switch(mode){case 0: default: // 
    switch(keycode){
    case RIGHT_BUTTON: if(--curx<0) curx=7; break;
    case LEFT_BUTTON:  if(++curx>7) curx=0; break;
    case DOWN_BUTTON:  if(--cury<0) cury=7; break;
    case UP_BUTTON:    if(++cury>7) cury=0; break;
    default: return 0;
    }}     
  case KEY_DOWN:                  // Клавиша нажата

      if(keycode==RED_BUTTON) return 1;     
switch(mode){ 
    case 0: default: 
    switch(keycode){ // Код клавиши
    case RIGHT_SOFT: return 1; //выход 
    case LEFT_SOFT:   break; 
    case RIGHT_BUTTON: if(--curx<0) curx=7; break;
    case LEFT_BUTTON:  if(++curx>7) curx=0; break;
    case DOWN_BUTTON:  if(--cury<0) cury=7; break;
    case UP_BUTTON:    if(++cury>7) cury=0; break;
    case '9': break;    
    case ENTER_BUTTON:  break;
    case GREEN_BUTTON:  break; 
    default:  return 0;
    }}
    REDRAW();
  }
  return 0;
}





void onclose(){ //При закрытии окна
  running=0; // Сигнал на остановку фонового процесса
} 
 //===========================================================================/
void onexit(){ // При выходе // Освобождаем память
 // if(fon) mfree(fon); // Освобождаем память
 // if(curImg) mfree(curImg); // Освобождаем память  
  //	if (wsbuf) FreeWS(wsbuf);
}
 //===========================================================================/
void oncreate(){ // При cоздание окна 

}
 //===========================================================================/          
int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
 //===========================================================================/
  //test_dir();
  if (isfile ("4:\\Z.txt")) ShowMSG(1,(int)"OK!"); else ShowMSG(1,(int)"File not found!");
   maks=AllocWS(256);
 bkcolor=0x0; frcolor=0x0; //последние два цвета - фона и фронта соответственно
    FImage=read_jpgimg(devka); 
   
   
 return 0;
}

































