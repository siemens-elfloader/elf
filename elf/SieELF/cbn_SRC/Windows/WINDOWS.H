
// Windows.h
//#define GRAPH
//#define UNPACK на время отладки убираем!

#include "..\swilib.h"
#include "..\font.h"
#include "..\random.h"

char *Title="Windows 0.3 (c)bn";
typedef unsigned char byte;
extern unsigned char SGOLD2, C65, S75, EL71;
extern int width, height;
extern short *screen; // Экран 132*176*2
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))
const int bkcolor=RGB16(31,63,31); // Цвета текста и фона
const int curcolor=RGB16(0,0,3);
const int startcolor=RGB16(24,48,24);
const int maskcolor=0xe4;// Прозрачный цвет
const int redcolor=RGB16(31,0,0);
const int WHITE=0xffff, BLACK=0, BLUE=31;

void openwindow();
void showtable();
void showerror();
void showstart();
void showmenu();
void showfiles(); // Показать все файлы
void initfont();
void textout(char *s, int y, int x, int maxx, int textcolor);
int slen(char *s); // Длина строки в тчк.
void rewindow();//tmp
void infolder();
void enter();
void levelup();
void menuinit(); //подгот.меню
void menuenter();
void loadwinini();
void loadsystemini();
void loadext();
void loadgr();

const char *errors[]={
  0,
  "Неизвестная ошибка\0"
};

//bmps
const char fwallpaper[]="wallpaper.bmp", ftitle[]="title.bmp", fstart[]="start.bmp";
const char flogo[]="logo.bmp", ferror[]="error.bmp";
//system
const char fswap[]="win386.swp", ficonself[]="icons.elf";
const char fwin[]="win.ini", fsystem[]="system.ini", fexten[]="extension.ini";
const char allext[]="*.*";
//tmp
const char *Diskname[]={"DATA(0:)", "(1:)", "(2:)", "(3:)", "MMC(4:)"};
const char *nametmp[]={"Demo01", "Мои документы", "Диск C:", "Ярлык","Readme",
"Настройки","Соединение", "Мои рисунки", "Корзина","Мой компьютер","Связь","Connect"
};
const char merror[]="ОШИБКА! Строка не найдена в win.ini";

#define FONMAX 0xe0
#define FONSIZEY 7
#define FONSIZEX 6 //р-р шрифта и строк на экране;

byte *symptr[256]; //* символы
byte sym[256];  // стр. симв.

/*
int maxextn=0, defextn=0;
struct extst{
  char *ex;
  char *exe;
}extn[64];
*/

WSHDR *ws=0;

//p=временные
char *extini=0; //free
int *ext, *pext; // расш-я массив по 8 байт на каждое  free!  0-е это [*] по умолчанию
int *extnum;   // [] с какого номера описатель (см ниже)

char **extact, **pextact; //название действия "Открыть н-р
char **extelf, **pextelf;  //эльф на действие
//0=конец списка

int *bmpext; // расш-я массив по 8 байт для картинок

char *winini=0; //free!!!
#define maxmsg 256 //1000  строк сообщений из win.ini
char *msg[maxmsg];

enum {PLOGO, PSAFE, PDEBUG, PENGLISH, PMAX}; // параметры из system.ini
int param[PMAX];
const char *mparam[PMAX]={
  "logo", "safe", "debug", "english"
};

char temp[256], tempext[8];
char *wallpaper=0, *title=0, *start=0, *icons=0, *error=0; // Графика  free!!!
char path[128], *file; // Путь Windows и начало файла
byte fastfon=0, cryticalerror=0; // Флаги
byte pysk=0; // 1=кнопка пуск нажата
volatile int running=0; // Процесс проверяет флаг и выходит если =0
int mode=0; // 0=table, 1=window
enum {modeontable, modeinwindow, modeonpysk}; //режимы

#define maxbufsize 4096
#define maxwinfiles 320

struct windows{ // ОКНА
  int flags; // Флаги
  int curx, cury; // Позиция курсора
  int maxfiles; // Файлов в папке
  char dir[256]; // Путь папки
  char buf[maxbufsize]; // Тут хранятся имена файлов
  char *filename[maxwinfiles]; // Указатели на ^^^^
  short filetype[maxwinfiles]; // Тип файла (номер значка)
  byte fileflag[maxwinfiles]; // 1=выделен
} w, menu; // Текущее окно и меню

enum { idunknown,idfolder,iddrive,iddrivemmc,idmycomp,idrecycled,idmax};
const char sysbmp[idmax][8]={ //системные значки
  "unknown","folder","drive","drivemmc","mycomp","recycled"
};
int sysbmpnum[idmax]; //номер картинки, соотв. системн. значку


const char *Menuname[]={
"1. Программы",
"2. След.окно",
"3. Свернуть",
"4. Закрыть",
"5. Мои документы",
"6. Избранное",
"7. Найти",
"8. Справка",
"9. Выполнить",
"0. Завершение работы"};

/*extension.ini:
[txt]
Открыть:0:\ZBin\elf1.elf
Копировать:0:\ZBin\elf2.elf
[*]


inline char shift(byte c){
  return (char)(((c&0xc0)>>1)|((c&0x18)>>1)|((c&3)));}

void showcur2(int y, int x){ // "Затененный" курсор
  int i,j;
  char *scr=screen+y*width+x;
  for(j=0;j<32;j++){
    for(i=0;i<32;i++,scr++){
      *scr=shift(*(byte*)scr);
    }scr+=width-32;
  }
}


//#define maxlog 4096
//byte log[maxlog], *plog=log;
//byte logged=0; // Флаг: Нужно сохранять лог?

//void outlog(char *s){
//  int i;
//  if(plog+(i=strlen(s))<log+maxlog-3){
//    memcpy(plog,s,i); *(plog+=i)=0xd; *++plog=0xa; ++plog;
//  }logged=1;
//}

//void savelog(){ // Записать лог
//  int f;
//  byte *file;
//  if(logged){
//  file=log+strlen((char*)log);
//  while(--file>log && *file!='.');
//  *++file='e';file[1]='r'; file[2]='r'; file[3]=0;
//  if((f=fopen((char*)log,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
//    *file='b';file[1]='a'; file[2]='s'; 
//    fwrite(f,log,plog-log,&err); 
//    fclose(f,&err); 
//}}}

//GBSTMR timer;
//void timer_proc(void){ // Функция выполняется по таймеру 10 раз в секунду
//  if(running){
////    REDRAW(); // Перерисовать экран
//  }
//  GBS_StartTimerProc(&timer,262/10,timer_proc); // Стартуем таймер с частотой 10 раз в секунду
//  // Он выполняется однократно поэтому его нужно постоянно запускать
//}

//void execute(){ // Выполняем basic код
//  running=1;
//  while(running){ // Пока нет команды на останов
//    ;
//  }
//}

контекст. меню: (прав.кн.)
-------------
Открыть
(действия...)
Вырезать
Копировать
Вставить
Создать ярлык
Создать папку (+)
Выбрать значок (+)
Удалить
Переименовать
Свойства


мой комп.
-------
Открыть
Создать ярлык
Переименовать
Свойства

Корзина
--------
Открыть
Вставить
Создать ярлык
Свойства

/// ф-ции:
rewindow
showmenu
showtable
openwindow
//
конт. меню:
Отправить {ярлык на раб.стол, на ММС, через блютуз, ir}
вырезать 
копировать
вставить
создать ярлык

удалить
переименовать
свойства
выделить(все)

*/

//inline void clrfext(){
//  *(int*)fext=*(int*)(fext+4)=0;}

int findext(int *pext, char *fext){ // вернуть номер найденного расширения fext или -1 в 8б массиве pext
  while(*pext){
    if(*pext==*(int*)fext && pext[1]==*(int*)(fext+4)) return ((pext-ext)>>1);
    pext+=2;
  }
  return -1;
}

int getcnt(char *s, char c){
  int i=0;
  while(*s)
    if(*s++==c) ++i;
  return i;
}

int getval(char *s){
  int i=0;
  --s;
  while(*++s>='0' && *s<='9') i=i*10+*s-'0';
  return i;
}

int slen(char *s){ // Длина строки в тчк.
  int i=0;
  while(*s) i+=font[sym[*(byte*)s++]];
  return i;
}

void getext(char *s){
  int i;
  char *ss;
  *(int*)(ss=tempext)=*(int*)(tempext+4)=0;
  if(!(s=strrchr(s,'.'))) return;
  for(i=0; i<8 && *s; i++) *ss++=(*++s)|0x20;
}

void execelf(char *exename, char *fname){ //запустить эльф
 str_2ws(ws,exename,strlen(exename)+1);
 ExecuteFile(ws,0,fname); 
}

