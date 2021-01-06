/*
* Ping-Pong 2009 - 2010
* main
* (c) Danil_e71
*/

//Заголовки + инты
#include "C:\arm\inc\swilib.h"
#ifdef ELKA//Елка
#define max_width 240
#define max_height 320
#define FONT 9//9 шрифт
#define timer_speed 5//Скорость перерисовки
#define nimg 1//Для правильной отрисовки под все платформы
#else
#ifdef SG//Сголд
#define max_width 132
#define max_height 176
#define FONT 2//2 шрифт
#define timer_speed 7
#define nimg 0.5
#else//Нсг
#define max_width 132
#define max_height 176
#define FONT 5//5 шрифт
#define timer_speed 12
#define nimg 0.5
#endif
#endif
#define NUM_RECORD 5//От этого числа пляшут рекорды
#define TMR_SECOND 216//Секунда наша
#define LGP_MENU_LANG1                 "Выберите язык"//Самое первое меню языка
#define LGP_MENU_LANG2                 "Select language"
#define LGP_LANG_RU                    "Русский"
#define LGP_LANG_EN                    "English"
#define LEFT_SIDE  1//USER.DX
#define RIGHT_SIDE 2//USER.DX
#define STOP_SIDE  0//USER.DX



IMGHDR *pics[6];//Шесть картинок

int clear=0;//Для устранения пикофа

const int rndtable[64]={//Таблица рандома
 0,  1,  6, -3,  7, -2,  5, -1,  3,  4,  2, -7, -5,  0,  4,  1,
 3, -4,  4,  6, -1,  2,  7, -3, -7, -5, -3,  0,  3,  0,  2,  4,
-7,  1,  5,  3,  0,  2, -5, -2,  5,  7, -1,  2, -5,  3,  1,  4,
-3, -7,  2,  6,  0, -2,  1,  3,  5, -4, -1,  2,  0, -3,  4, -6
};
int rndindex=0;//Индекс рандома
volatile int running=0; // Флаг активности
typedef struct//Структурка юзверя , бола и цпу
{
  int x,
      y,
      height,
      width,
      speed,
      lifetime,
      round,
      dx,
      dy;
}Mytype;
Mytype user;
Mytype cpu;
Mytype ball;

struct{int mymsec,hour,min,sec;char *str;}Time;//время

enum {load,menu,settings,settings_igra,music,game,rec}status; //параметры для меню

int 
cur_x=nimg*30,//x курсоров
cur_y=nimg*52,//y курсоров
main_y=nimg*60,//^
difficult=0,//Уровни сложности
lives=7,//Жизни(а вдруг нет data.sys????)
mode=0,//Очки или жизни
speed_game=0,//Скорость игры
gdy,//От слова где наверно))))))Опр. позицию шарика после гола
def_vol=0,//Громкость
on_off_sound=0,//Звук музыка или выкл
PLAY_ID=0xFFF,//Удобно)))Спс Half65
saveload=1,//Сохранение или загрузка
img_count,//Для загрузки
game_new_cont=1,//Новая или продолжить
langenru=0,//Какой язык??
vibra,//Все параметры вибры
exiting=0,//Для выхода
error_count=0,//Количество ошибок(нехватающих картинок)
AI_line=0,//Линия, после которой начинает думать cpu
isload=0,//Если 1 - идет загрузка
color_frame[8]={23,23,23,23,23,23,23,23};//8 фреймов(для загрузки)
extern const char folder[128];//Путь к эльфу
extern const char name[15];//Имя игрока
const char bgcol_lang_cur[4]={1,1,1,100};//Бэкграункд курсора в выборе языка
const char linecol2[4] = {100,0,0,100};//Цвет средней линии
const char bgcol[4]={50,50,50,255};//Бэкграунд при загрузке
const char perc_t[]="%t";
const char per_s[]="%s%s";

char *folders;//Для всего
char *lang[60];//Наш лэнгпак
char *images[6];//5 картинок(для путей)
GBSTMR tmr,vibr;//Таймер перерисовки+времени, вибры
extern void UpdateCSMname();
extern void RedrawScreen();
extern void lgpInitLangPack();//Инициируем язык
extern void T_Load_IMG();//Загрузка графики
extern void load_lang();//Загрузка графики №2

int idle=1;

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
  WSHDR *ws5;
  int i1;
}MAIN_GUI;
