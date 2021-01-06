//(C)opy(R)ights - Авторство или чувство собственной важности (ЧСВ) ;)
#define ELF_NAME     "SuDoKu"
#define ELF_VERSION  "2.0"
#define ELF_AUTHOR   "Dimadze"
#define ELF_RESPECT  "SIEMENS"

#ifdef SGOLD
#define ELF_PLATFORM "SGold"
#endif

#ifdef NEWSGOLD
#ifndef ELKA
#define ELF_PLATFORM "NewSGold"
#endif
#endif
    
#ifdef ELKA
#define ELF_PLATFORM "NewSGold (E/EL71)"
#endif

//General game #defines  - Основные игровые дефайны (как-бы замещения)

#define SCRH 160 //ScreenH() //Высота игрового окна
#define SCRW 128 //ScreenW() //Ширина игрового окна

#define SCRHM 130 //Наименьшая Высота экрана
#define SCRWM 128 //Наименьшая Ширина экрана

#define TIMER_SECOND 262
#define MAXXC        9
#define MAXYC        9
#define MAXPREVIEW   200   //200 Подглядываний
#define MAXSECOND    18000 //5 часов на игру
 

//General game/system #includes - Основные игровые/системные включения

#include "..\inc\swilib.h"
#include "..\inc\rect_patcher.h"
#include "conf_loader.h"

#include "engine\fileop\resources.h" //Ресурсы: фаилы, вшитые в эльф

//Global consts and vars - Глобальные константы и переменные
GBSTMR timer;
int GBSTIMER_KOEFFICENT = 1;
int RENDERWINDOW = 0;
int MESSAGEWINDOW =0;
char TYPEREDRAW = 0;
char TEMPREDRAW = 0;

int pravda = 0;

char sudoku[256], bgg[256], bgm[256]; //Пути png - картинок: sudoku.png, bgg.png, bgm.png
char dig[28][256];                    //Пути png - картинок: 0.png, 1-9.png, 1s-9s.png, 1a-9a.png

char ssffile[5][256];          //Пути 5 ssf - фаилов                      (/cfg/sudoku_%02d.ssf)
char hlpfile[256];             //Путь hlp - фаила                         (/cfg/sudoku.hlp)
char seditor[256];             //Путь эльф - редактора фаилов карт SuDoKu (/smfeditor.elf)
char cfgfile[256];             //Путь BCFG - фаила

char elffolder[256];           //Путь папки запущенного эльфа
char imgfolder[256];           //Путь папки /SCRWxSCRH/ - графика
char cfgfolder[256];           //Путь папки /cfg/ - различные настройки, сейвы
char smffolder[256];           //Путь папки /smf/ - фаилы карт SuDoKu

IMGHDR  logo_img = {90, 90, 0x88, logo_bitmap};                                     //Логотип (вшит в эльф)
IMGHDR *sudoku_img     = 0;                                                         //Заголовок в меню (на C72, SL65 он не нужен)
IMGHDR *bgg_img        = 0;                                                         //Фон игрового окна
IMGHDR *bgm_img        = 0;                                                         //Фон меню
IMGHDR *dig_img[28]    = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Картинки ячеек


//BCFG - переменные
int bcfg_mmenu_font         = 7;              // Шрифт основного меню
char bcfg_mmenu_col[4]      = {0,0,255,100};  // Цвет основного меню
char bcfg_mmenu_bgcol_u[4]  = {0,0,0,100};    // Цвет градиента элемента меню
char bcfg_mmenu_bgcol_m[4]  = {255,0,0,100};  // Цвет градиента выделенного элемента меню

int bcfg_sh_headfont         = 7;
char bcfg_sh_headcolt[4]     = {0,0,0,100};
char bcfg_sh_headcolg[4]     = {0,0,0,100};

int bcfg_sh_softfont         = 7;
char bcfg_sh_softcolt[4]     = {255,0,0,100};
char bcfg_sh_softcolg[4]     = {0,0,0,100};


//Additional game/system #includes - Дополнителные игровые/системные включения

#include "engine\system\lang.h"      //Язык интерфейса - библиотека специальных #define'ов (По принципу Ivoplay)
#include "engine\system\sieelf.h"    //Интерфейс мобилы для IAR
#include "engine\system\addfunc.h"   //Библиотека дополнительных ф-ий
#include "engine\system\sudoku.h"    //Библиотека игровых ф-ий, структур, констант, переменных для игры SuDoKu, то бишь для этой ;)

#include "engine\fileop\ext_work.h"  //Библиотека ф-ий для работы с фаилами карт SuDoKu 
#include "engine\fileop\ssf_work.h"  //Библиотека ф-ий для работы с ssf - фаилами  [!]
#include "engine\fileop\elffolder.h" //Библиотека ф-ий для работы с фаилами из рабочей папки elf - приложения


SUDOKUMAP *sdm = 0;
ERRORSTRUCT *errs = 0;

#include "engine\render\logow.c"     //Рендеринг Лого Окна
#include "engine\render\mmenu.c"     //Рендеринг Главного Меню

//General programs functions - Основные функции игры/программы


void START_CONTROL(char *exename, char *fname) // Выполнение ф-ий при старте приложения, exename - путь запущенного эльфа, fname - параметр при запуске, например, путь какого-либо фаила
{
  //if (SECRETFUNCTION(exename)==1) {ShowMSG(1,(int)"AAAAA!");SUBPROC((void *)ElfKiller); }
 
  
 sdm = CreateSUDOKUMAPbyEXTFILE(fname);
 
 ElfFolderOperations(exename);
 errs = ElfFolderCheckFiles(sdm, fname);
 InitConfig(); 
}


void END_CONTROL() // Выполнение ф-ий при завершении приложения
{
  MemFreeOfIMGHDR(bgm_canvas_mmenu);
  MemFreeOfIMGHDR(bgm_canvas_mrsoft);
  MEMORYFREE(counter); 
  GBS_DelTimer(&timer);
  
}

void MINIMIZE_CONTROL() // Выполнение ф-ий при "сворачивании" приложения
{
  
 GBS_StopTimer(&timer);
  
}

void MAXIMIZE_CONTROL() // Выполнение ф-ий при "разворачивании" приложения
{ 
 FULLREDRAW();
}

void CREATE_CONTROL() // Выполнение ф-ий при создания окна приложения
{
 GBS_StartTimerProc(&timer,TIMER_SECOND/GBSTIMER_KOEFFICENT,REDRAW_CONTROL);
 FULLREDRAW();
}

void MESSAGES_CONTROL() // Выполнение ф-ий при приходе сообщений
{

}

void REDRAW_CONTROL() // Выполнение ф-ий прорисовки экрана, REDRAW() - для вызова этой ф-ии
{
if (MESSAGEWINDOW == 0)
{
  if (RENDERWINDOW  == 0) LOGOW_RENDER();
  if (RENDERWINDOW  == 1) MMENU_RENDER();
} 

}


int KEY_CONTROL(GUI_MSG *msg) // Выполнение ф-ий при нажатии клавиш, KEYMSG - тип нажатия, KEYSMSG - код клавиши, END - завершение программы, NEXT - ожидание следующего нажатия клавиши
{ 
int MT=0;
 if (KEYMSG == KEY_DOWN || KEYMSG == LONG_PRESS)
  {
    if (MESSAGEWINDOW == 1)
     {
       if (KEYSMSG > 0 && RENDERWINDOW == -1) END;
       if (KEYSMSG > 0 && RENDERWINDOW != -1) {MESSAGEWINDOW = 0;MT=1; GKEYEND;}
     }
    else
    {
      if (RENDERWINDOW == 1)
       {
         if (KEYSMSG == '0') if (pravda == 0) pravda = 1; else pravda = 0;
         if (KEYSMSG == UP_BUTTON    || KEYSMSG == '2') {if (mmenu_cur==0) mmenu_cur=(MMENU_CT - 1); else mmenu_cur--; GKEYEND;}
         if (KEYSMSG == DOWN_BUTTON  || KEYSMSG == '8') {if (mmenu_cur==(MMENU_CT - 1)) mmenu_cur=0; else mmenu_cur++; GKEYEND;}
         if (KEYSMSG == ENTER_BUTTON || KEYSMSG == '5')
         {
           if (mmenu_cur == 0) {RENDERWINDOW = 2;    GKEYEND;}
           if (mmenu_cur == 1) {RENDERWINDOW = 3;    GKEYEND;}
           if (mmenu_cur == 2) {OpenFile(cfgfile,0); GKEYEND;}
           if (mmenu_cur == 3) {ShowMessage(LG_MMENU_ERROR, 7, MSGINFO); GKEYEND;}
           if (mmenu_cur == 4) {ShowMessage(LG_MMENU_ERROR, 7, MSGINFO); GKEYEND;}
           if (mmenu_cur == 5) {RENDERWINDOW = 5;    GKEYEND;}
           if (mmenu_cur == 6) END;  
         }
       }
         
    }
    
    
      
  }
 
 
KEYEND:

if (TEMPREDRAW != RENDERWINDOW || MT == 1) FULLREDRAW(); else SMARTREDRAW();
TEMPREDRAW = RENDERWINDOW; 
 
 NEXT; 
}
