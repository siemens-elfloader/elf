#ifndef _MAIN_H_
  #define _MAIN_H_

#define VIBRA_POWER 10 // Сила вибры для событий разного рода

#define USE_PNG_EXT   // Использовать ли расширение PNG для картинок (ELFLoader >2.0)

#define USE_LOG  // Вести лог, если нет - строку закомментировать

#define MAX_INIBUF 256  // Размер буфера ини-файла

#define LONG_PRESS_DIFF 0x40 // Для реализации длинного нажатия через конфиг клавиш

typedef void (*INIPROC) (char *name, char *value); // Процедура обработки ини-файла

// Общие функции модуля MAIN.C

//#define color(x) (char *)(&(x))

// Для модуля main.c
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
// Для модуля main.c
/*
typedef struct
{
  char r;
  char g;
  char b;
  char a;
}RGBA;
*/
// Структура плейлиста
typedef struct
{
  char *filename;
  char *name;
  void *next;
}PLIST;

typedef struct
{
 // char full_name[256]; // Путь к файлу   AAA
  char istagg[3]; // Слово "TAG"
  char title[30]; // Название
  char artist[30]; // Исполнитель
  char album[30]; // Альбом
  char year[4]; // Год
  char comment[30]; // Комментарий
  int number; // Номер   AAA
  int genre; // Жанр
  int version1_1; // 1 - версия 1.1, 0 - версия 1.0   AAA
  int present; // Присутствует
}ID3TAGDATA;

int ReadID3v1(WSHDR* fnamews, ID3TAGDATA *tag); // Чтение ID3 v1

#ifndef NO_PNG  /////////////////////////////////////////

#define TOTAL_ITEMS_1 18
#define ALLPNG 39

// Лепота... Но за один запуск жрет много   AAA
static const char * const items1[TOTAL_ITEMS_1] = {
/*  0*/ "background",
/*  1*/ "volume",   // x2
/*  2*/ "stop",     // x3
/*  3*/ "pause",    // x3
/*  4*/ "play",     // x3
/*  5*/ "playall",  // x2
/*  6*/ "repeat",   // x2
/*  7*/ "random",   // x2
/*  8*/ "repeatone",// x2
/*  9*/ "next",     // x2
/* 10*/ "prev",     // x2
/* 11*/ "keylock",
/* 12*/ "cursor",
/* 13*/ "_down",
/* 14*/ "_idle",
/* 15*/ "splash",
/* 16*/ "rewtb",
/* 17*/ "rewte",
};
#define PNGEXT ".png"

#endif///////////////////////////////////////////////////

#define ncoord 31
#define ncolor 12
/*                                       Расшифровка координат/цветов
        // Полоса прокрутки
0         BR_x=data[3];
1         BR1_y=data[4]+data[5];
2         BR2_y=data[6]+data[7];
3         BR_w=data[8];
4         BRC_x=data[9];
5         BRC_w=data[10];
         // Полоса прокрутки
6         s=data[11];
7         CTmy_x=data[12];
8         CTmy_y=data[13]+data[14];
9         VOLmy_x=data[15];
10        VOLmy_y=data[16]+data[17];
11        STATmy_x=data[18];
12        STATmy_y=data[19]+data[20];
13        NUMmy_x=data[21];
14        NUMmy_y=data[22]+data[23];
15        RANDmy_x=data[24];
16        RANDmy_y=data[25]+data[26];
17        KeyLock_x=data[27];
18        KeyLock_y=data[28]+data[29];
19        Next_x=data[30];
20        Next_y=data[31]+data[32];
21        Prev_x=data[33];
22        Prev_y=data[34]+data[35];
        // Время
23        time_x=data[36];
24        time_y=data[37]+data[38];
        // Длительность песни
25        length_x=data[39];
26        length_y=data[40]+data[41];
        // Прогрессбар
27        progress_x=data[42];
28        progress_y=data[43]+data[44];
29        progress_x2=data[45];
30        progress_y2=data[46]+data[47];


0        COLOR_TEXT[4];
1        LINE_COLOR[4];
2        COLOR_BG[4];
3        COLOR_BG_CURSOR[4];
4        COLOR_TEXT_CURSOR[4];
5        COLOR_TEXT_PLAY[4];
6        COLOR_BANDROLL[4];
7        COLOR_BANDROLL_C[4];
8        COLOR_PROG_BG[4];               // Фон прогрессбара
9        COLOR_PROG_BG_FRAME[4];               // Ободок
10       COLOR_PROG_MAIN[4];             // Сам прогресс
11       COLOR_PROG_MAIN_FRAME[4];             // Ободок
*/

//>>>>>>>>>>>>>>>>>>>>>>>> SPerrs/Ошибки <<<<<<<<<<<<<<<<<<<<<<<<<<<<//
// Чтоб проще ламеров гонять   AAA
//#define SPerr0 "0x00"
#define SPerr1 "0x01"  // Ошибка определения кфг файла
#define SPerr2 "0x02"  // Нет кфг файла
#define SPerr3 "0x03"  // Ошибка конфига клавиш
#define SPerr4 "0x04"  // Нажата клавиша с ошибочным определением
//>>>>>>>>>>>>>>>>>>>>>>>> SPerrs/Ошибки <<<<<<<<<<<<<<<<<<<<<<<<<<<<//

#ifdef NEWSGOLD
#define CBOX_CHECKED 0xE116
#define CBOX_UNCHECKED 0xE117
#else
#define CBOX_CHECKED 0xE10B
#define CBOX_UNCHECKED 0xE10C
#endif

void Log(int dummy, char *txt);

void load_skin(char const* fname);

void PlayMP3File(WSHDR * fname);

void SendNULL();    // Послать по окончании воспр.   AAA

void ToDevelop();   // Развернуть   AAA

void Refresh();     // Загрузить конфиги скина   AAA

void WriteSPerr(char* err);

void QuitCallbackProc(int decision);

void DoErrKey();

void DoExit();

void LoadDefPlaylist();

void PrevTrackDown();

void NextTrackDown();

void SwitchPlayModeDown();

void SavePL();

void StartRewindToEnd();

void StartRewindToBegin();

void NextPL();

void PrevPL();

void CTDownSpeed(void);

void CTUpSpeed(void);

void DoKey(int key);

char *strtolower(char *src, char *dst, int sz);

int EnumIni(int local, char *ininame, INIPROC proc);

void LoadKeys();

//IMGHDR* CreateImgHdrByAnyFile (WSHDR * path,short width, short height, int rot);

//void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush);

void EXT_REDRAW();

void StopTMR(unsigned short s);

void CrPopup();

void PlayPopup(unsigned short xp, unsigned short yp, unsigned short xp2, unsigned short yp2, const char *Color);

#endif
