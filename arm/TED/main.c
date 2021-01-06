#include "..\inc\swilib.h"
#include "..\inc\cfg_items.h"

#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}
int menusoftkeys[]={0,1,2};

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"Select"},
  {0x0001,0x0000,(int)"Back"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

#define icon 0

char t_bm1[]="BM1 000000000";
char t_bm2[]="BM2 000000000";
char t_bm3[]="BM3 000000000";
char t_bm4[]="BM4 000000000";

WSHDR *info_ws;
WSHDR *upinfo_ws;
WSHDR *e_ws;

extern const unsigned int INK;
extern const unsigned int PAPER;
extern const unsigned int DISPLAY_LIGHT;

volatile int terminated=0;
volatile int loadmenu_id;

volatile int edit_id;

volatile int text_changed=0;

volatile unsigned int editmode=0;
volatile int stk_fhandle=-1;

volatile int rotate = 0;

// Флаг необходимости завершить работу
char Quit_Required = 0;
char *asterix="*";

//Флаг необходимости перерисовать экран
volatile unsigned int draw_mode=255;
volatile unsigned int font_selected=0;
volatile unsigned int fonts_count = 0;

volatile unsigned int clip_pasted;

typedef struct
{
  GUI gui;
  //  WSHDR *ws1;
  //  WSHDR *ws2;
  //  int i1;
}MAIN_GUI;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

const int minus11=-11;

const char bmpDiskAccess[12]={0xFC,0x86,0xB3,0xA9,0xB1,0xA9,0x81,0xFF};
const IMGHDR imgDiskAccess = {8,8,0x1,(char *)bmpDiskAccess};

//Указатель блока в верхнем стеке
int u_disk; //Дисковый указатель верхнего стека (в блоках по STKSZ50)
//Указатель блока в нижнем стеке
int d_disk; //Дисковый указатель нижнего стека (в блоках по STKSZ50)

unsigned int usp; //Указатель на верхний стек
unsigned int dsp; //Указатель на нижний стек

//Флаг работы с диском
#define FIRSTLOAD 1
#define LOAD_UP 2
#define LOAD_DOWN 4
#define SAVE_UP 8
#define SAVE_DOWN 16
#define SAVE_FILE 32

volatile int disk_access=FIRSTLOAD;

int cursor_cnt;
int disable_exit;

int win_dos_koi;
unsigned int cursor_off;

extern const char ted_path[];

char stkfile[128];

//Строка, на которую надо установить позицию в самом начале
unsigned long seek_to_line;
//Общее количество строк
unsigned long total_line;
//Номер текущей строки (курсор)
unsigned long curline;
//Текущий символ для редактирования (курсор)
unsigned int curpos;
//Номер верхней отображаемой строки
unsigned long viewline;
//Номер самого левого отображаемого символа
unsigned int viewpos;

unsigned int max_y;
unsigned int max_y_emode;
unsigned int max_x;
unsigned int max_x_emode;

unsigned int sheight_emode;
unsigned int sheight;

//---------------------------------
// Состояние конвертора
//---------------------------------
//unsigned int CSM;
//Символ конца строки в конверторе
//unsigned int eolsymb;

//Прототипы конверторов
unsigned int ConvertFormat(int fin,int fs,int fmt);
unsigned int ConvertSimple(int fin,int fs);


#define SSIZE 131072
//Размер стеков
unsigned int STKSZ=(SSIZE);
//Размер, при котором происходит запись во временный файл
unsigned int STKMAX=(SSIZE-16000);
//Размер, при котором происходит чтение из временного файла
unsigned int STKMIN=(16000);
//Размер блока во временном файле
unsigned int STKSZ50=(SSIZE/2);

char *ustk; //верхний стек строк
char *dstk; //нижний стек строк, строки хранятся в обратном порядке

#define MAXBLOCK 1024
unsigned int dbat[MAXBLOCK]; //Таблица распределения блоков нижнего стека во временном файле
unsigned int ubat[MAXBLOCK]; //Таблица распределения блоков верхнего стека во временном файлe
char bfree[MAXBLOCK]; //Таблица занятости блоков (0 - свободен)

//char font[4096]; //Буфер для шрифта
unsigned char *font = 0; //Буфер для шрифта
char chars_width[256]; //Ширины символов
char chars_width_src[256]; //Ширины символов исходные
int FW, FH; //Размер матрицы символа

char editline[256]; //Буфер для редактирования строки
char filename[128];
struct
{
  char name[128]; //Имя файла
  char font; //Размер шрифта
  char fmt; //Тип форматера
  char rotate; //Как повёрнут экран
  char codepage; //Кодировка
  char cursor_off; //Если 1 - выключен курсор при просмотре
  unsigned long line; //Номер строки для перехода
  unsigned long total; //Общее количество. Если не совпадает, переход по отношению
  unsigned long bookm1;
  unsigned long bookm2;
  unsigned long bookm3;
  unsigned long bookm4;
} HISTORY;

#define SCR_WIDTH 256
#define SCR_MODULO (SCR_WIDTH/8)

#ifdef ELKA
#define SCR_HEIGHT (320-YDISP)
#else
#define SCR_HEIGHT (256)
#endif

char myscr[SCR_HEIGHT*SCR_WIDTH/8];

//#ifdef ELKA
IMGHDR MyScrHdr = {SCR_WIDTH-1,SCR_HEIGHT-1,0x1,myscr};
//#else
//IMGHDR MyScrHdr = {255,SCR_HEIGHT-1,0x1,myscr};
//#endif


void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  char *rscr = malloc(SCR_WIDTH*SCR_HEIGHT/8);
  unsigned char block[8];
  int xx, yy, i, dy, mx, my, scr_wb, scr_hb;
  RECT rc;
  DRWOBJ drwobj;

  if(!editmode && rotate && img==&MyScrHdr)
  {
    IMGHDR R_hdr = {SCR_WIDTH-1,SCR_HEIGHT-1,0x1,rscr};
//ScreenH()-(editmode?(HeaderH()+SoftkeyH()+YDISP+1):0)
    StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
    //zeromem(rscr, SCR_WIDTH*SCR_HEIGHT/8);
            
    scr_wb = SCR_HEIGHT>>3;
    scr_hb = SCR_WIDTH>>3;
    mx = ScreenH()-1-YDISP;
    my = ScreenW()-1;
  
    if(rotate==2)
    {
      for(xx = 0; xx <= (mx>>3); xx++)
      {
        for(yy = 0; yy <= (my>>3); yy++)
        {
          for(dy = 0; dy < 8; dy++)
          {
            for(i = 0; i < 8; i++)
            {
              block[i] <<= 1;
              block[i] |= ((*(myscr + ((yy<<3)+(7-dy))*scr_wb+xx))>>(i))&1;
            }
          }
          for(i = 0; i < 8; i++)
            *(rscr+((xx<<3)+i)*scr_hb+((my>>3)-yy)) = block[7-i];
        }
      }
#ifndef ELKA
      for(i = 1; i < SCR_WIDTH*SCR_HEIGHT/8; i++)
        rscr[i-1] = ((rscr[i-1] << 4)&0xF0) | ((rscr[i] >> 4)&0x0F);
#endif
    }
    else
    {
      for(xx = 0; xx <= (mx>>3); xx++)
      {
        for(yy = 0; yy <= (my>>3); yy++)
        {
          for(dy = 0; dy < 8; dy++)
          {
            for(i = 0; i < 8; i++)
            {
              block[i] <<= 1;
              block[i] |= ((*(myscr + ((yy<<3)+dy)*scr_wb+xx))>>(7-i))&1;
            }
          }
          for(i = 0; i < 8; i++)
            *(rscr+((((mx>>3)-xx)<<3)+i)*scr_hb+yy) = block[7-i];
        }
      }
    }
   SetPropTo_Obj5(&drwobj,&rc,0,&R_hdr);
  }
  else
  {
    StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
    SetPropTo_Obj5(&drwobj,&rc,0,img);
  }
  
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
  mfree(rscr);
}

/*GBSTMR tmr2sec;

void tmr2sec_proc(void)
{
if ((disk_access)||(draw_mode>1))
{
REDRAW;
GBS_StartTimerProc(&tmr2sec,262/2,tmr2sec_proc);
  }
}

void Start_tmr2sec(void)
{
GBS_StartTimerProc(&tmr2sec,262/2,tmr2sec_proc);
}*/

volatile char Q_DiskError;

void DiskErrorMsg(int mode)
{
  if (Q_DiskError&(1<<mode)) return; //Такое сообщение уже отобразили
  LockSched();
  Q_DiskError|=(1<<mode);
  switch(mode)
  {
  case 4:
    ShowMSG(1,(int)"Can't create or write outfile!");
    break;
  case 3:
    ShowMSG(1,(int)"Can't open tempfile!");
    break;
  case 2:
    ShowMSG(1,(int)"Can't seek in tempfile!");
    break;
  case 1:
    ShowMSG(1,(int)"Can't write tempfile!");
    break;
  case 0:
    ShowMSG(1,(int)"Can't read tempfile!");
    break;
  }
  UnlockSched();
}

const char wintranslation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0x5F,0xFD,0x83,0xB3,0x15,0xF0,0x63,0xF2,0x3C,0xBF,0x2D,0x52,0xF4,
  0xF8,0x2B,'I' ,'i' ,0xA3,0xE7,0x14,0xFA,0xF1,0xFC,0xF3,0x3E,0x5F,0x5F,0x5F,0xF5,
  0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
  0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
  0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
  0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF
};

const char koi8translation[128]=
{
  0x5F,0x5F,0x27,0x5F,0x22,0x3A,0xC5,0xD8,0x5F,0x25,0x5F,0x3C,0x5F,0x5F,0x5F,0x5F,
  0x5F,0x27,0x27,0x22,0x22,0x07,0x2D,0x2D,0x5F,0x54,0x5F,0x3E,0x5F,0x5F,0x5F,0x5F,
  0xFF,0xF6,0xF7,0xF1,0xF3,0x5F,'i' ,0xF5,0xF0,0x63,0xF2,0x3C,0xBF,0xA3,0x52,0xF4,
  0xF8,0x2B,0x5F,0xF0,0xF2,0xE7,'I' ,0xF4,0xF1,0xFC,0xF3,0x3E,0x5F,0x83,0x5F,0xF5,
  
  0xEE,0xA0,0xA1,0xE6,0xA4,0xA5,0xE4,0xA3,0xE5,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,
  0xAF,0xEF,0xE0,0xE1,0xE2,0xE3,0xA6,0xA2,0xEC,0xEB,0xA7,0xE8,0xED,0xE9,0xE7,0xEA,
  0x9E,0x80,0x81,0x96,0x84,0x85,0x94,0x83,0x95,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,
  0x8F,0x9F,0x90,0x91,0x92,0x93,0x86,0x82,0x9C,0x9B,0x87,0x98,0x9D,0x99,0x97,0x9A
};

const unsigned short dos2unicode[128]=
{
  0x0410,0x0411,0x0412,0x0413,0x0414,0x0415,0x0416,0x0417,
  0x0418,0x0419,0x041A,0x041B,0x041C,0x041D,0x041E,0x041F,
  0x0420,0x0421,0x0422,0x0423,0x0424,0x0425,0x0426,0x0427,
  0x0428,0x0429,0x042A,0x042B,0x042C,0x042D,0x042E,0x042F,
  0x0430,0x0431,0x0432,0x0433,0x0434,0x0435,0x0436,0x0437,
  0x0438,0x0439,0x043A,0x043B,0x043C,0x043D,0x043E,0x043F,
  0x002D,0x002D,0x002D,0x00A6,0x002B,0x00A6,0x00A6,0x00AC,
  0x00AC,0x00A6,0x00A6,0x00AC,0x002D,0x002D,0x002D,0x00AC,
  0x004C,0x002B,0x0054,0x002B,0x002D,0x002B,0x00A6,0x00A6,
  0x004C,0x0433,0x00A6,0x0054,0x00A6,0x003D,0x002B,0x00A6,
  0x00A6,0x0054,0x0054,0x004C,0x004C,0x002D,0x0433,0x002B,
  0x002B,0x002D,0x002D,0x002D,0x002D,0x00A6,0x00A6,0x002D,
  0x0440,0x0441,0x0442,0x0443,0x0444,0x0445,0x0446,0x0447,
  0x0448,0x0449,0x044A,0x044B,0x044C,0x044D,0x044E,0x044F,
  0x0401,0x0451,0x0404,0x0454,0x0407,0x0457,0x040E,0x045E,
  0x00B0,0x2022,0x00B7,0x0076,0x2116,0x00A4,0x00A6,0x00A0
};

unsigned int char8to16(int c)
{
  if (c<32) return('_');
  if (c>=128)
  {
    switch(win_dos_koi)
    {
    case 1:
      //Win->Dos
      c=wintranslation[c-128];
      break;
    case 2:
      //Koi8->Dos
      c=koi8translation[c-128];
      break;
    }
    if (c<128) return(c);
    return(dos2unicode[c-128]);
  }
  return(c);
}

void CharWidthForCodepage()
{
  int c;

  for(c = 0; c < 128; c++)
  chars_width[c] = chars_width_src[c];
  for(c = 128; c < 256; c++)
  {
    switch(win_dos_koi)
    {
    case 1:
      //Win->Dos
      chars_width[c] = chars_width_src[wintranslation[c-128]];
      break;
    case 2:
      //Koi8->Dos
      chars_width[c] = chars_width_src[koi8translation[c-128]];
      break;
    default:
      chars_width[c] = chars_width_src[c];      
      break;
    }
  }
}

// RECODING TABLE
//utf16,cp866,cp1251,koi8
//const far unsigned int unicode2char[]=
typedef struct
{
  unsigned short u;
  char dos;
  char win;
  char koi8;
} TUNICODE2CHAR;

const TUNICODE2CHAR unicode2char[]=
{
  // CAPITAL Cyrillic letters (base)
  0x410,0x80,0xC0,0xE1, // А
  0x411,0x81,0xC1,0xE2, // Б
  0x412,0x82,0xC2,0xF7, // В
  0x413,0x83,0xC3,0xE7, // Г
  0x414,0x84,0xC4,0xE4, // Д
  0x415,0x85,0xC5,0xE5, // Е
  0x416,0x86,0xC6,0xF6, // Ж
  0x417,0x87,0xC7,0xFA, // З
  0x418,0x88,0xC8,0xE9, // И
  0x419,0x89,0xC9,0xEA, // Й
  0x41A,0x8A,0xCA,0xEB, // К
  0x41B,0x8B,0xCB,0xEC, // Л
  0x41C,0x8C,0xCC,0xED, // М
  0x41D,0x8D,0xCD,0xEE, // Н
  0x41E,0x8E,0xCE,0xEF, // О
  0x41F,0x8F,0xCF,0xF0, // П
  0x420,0x90,0xD0,0xF2, // Р
  0x421,0x91,0xD1,0xF3, // С
  0x422,0x92,0xD2,0xF4, // Т
  0x423,0x93,0xD3,0xF5, // У
  0x424,0x94,0xD4,0xE6, // Ф
  0x425,0x95,0xD5,0xE8, // Х
  0x426,0x96,0xD6,0xE3, // Ц
  0x427,0x97,0xD7,0xFE, // Ч
  0x428,0x98,0xD8,0xFB, // Ш
  0x429,0x99,0xD9,0xFD, // Щ
  0x42A,0x9A,0xDA,0xFF, // Ъ
  0x42B,0x9B,0xDB,0xF9, // Ы
  0x42C,0x9C,0xDC,0xF8, // Ь
  0x42D,0x9D,0xDD,0xFC, // Э
  0x42E,0x9E,0xDE,0xE0, // Ю
  0x42F,0x9F,0xDF,0xF1, // Я
  // CAPITAL Cyrillic letters (additional)
  0x402,'_',0x80,'_', // _ .*.*
  0x403,'_',0x81,'_', // _ .*.*
  0x409,'_',0x8A,'_', // _ .*.*
  0x40A,'_',0x8C,'_', // _ .*.*
  0x40C,'_',0x8D,'_', // _ .*.*
  0x40B,'_',0x8E,'_', // _ .*.*
  0x40F,'_',0x8F,'_', // _ .*.*
  0x40E,0xF6,0xA1,'_', // Ў ...*
  0x408,0x4A,0xA3,0x4A, // _ .*.*
  0x409,0x83,0xA5,0xBD, // _ .*..
  0x401,0xF0,0xA8,0xB3, // Ё
  0x404,0xF2,0xAA,0xB4, // Є
  0x407,0xF4,0xAF,0xB7, // Ї
  0x406,0x49,0xB2,0xB6, // _ .*..
  0x405,0x53,0xBD,0x53, // _ .*.*
  // SMALL Cyrillic letters (base)
  0x430,0xA0,0xE0,0xC1, // а
  0x431,0xA1,0xE1,0xC2, // б
  0x432,0xA2,0xE2,0xD7, // в
  0x433,0xA3,0xE3,0xC7, // г
  0x434,0xA4,0xE4,0xC4, // д
  0x435,0xA5,0xE5,0xC5, // е
  0x436,0xA6,0xE6,0xD6, // ж
  0x437,0xA7,0xE7,0xDA, // з
  0x438,0xA8,0xE8,0xC9, // и
  0x439,0xA9,0xE9,0xCA, // й
  0x43A,0xAA,0xEA,0xCB, // к
  0x43B,0xAB,0xEB,0xCC, // л
  0x43C,0xAC,0xEC,0xCD, // м
  0x43D,0xAD,0xED,0xCE, // н
  0x43E,0xAE,0xEE,0xCF, // о
  0x43F,0xAF,0xEF,0xD0, // п
  0x440,0xE0,0xF0,0xD2, // р
  0x441,0xE1,0xF1,0xD3, // с
  0x442,0xE2,0xF2,0xD4, // т
  0x443,0xE3,0xF3,0xD5, // у
  0x444,0xE4,0xF4,0xC6, // ф
  0x445,0xE5,0xF5,0xC8, // х
  0x446,0xE6,0xF6,0xC3, // ц
  0x447,0xE7,0xF7,0xDE, // ч
  0x448,0xE8,0xF8,0xDB, // ш
  0x449,0xE9,0xF9,0xDD, // щ
  0x44A,0xEA,0xFA,0xDF, // ъ
  0x44B,0xEB,0xFB,0xD9, // ы
  0x44C,0xEC,0xFC,0xD8, // ь
  0x44D,0xED,0xFD,0xDC, // э
  0x44E,0xEE,0xFE,0xC0, // ю
  0x44F,0xEF,0xFF,0xD1, // я
  // SMALL Cyrillic letters (additional)
  0x452,'_',0x90,'_', // _ .*.*
  0x453,'_',0x83,'_', // _ .*.*
  0x459,'_',0x9A,'_', // _ .*.*
  0x45A,'_',0x9C,'_', // _ .*.*
  0x45C,'_',0x9D,'_', // _ .*.*
  0x45B,'_',0x9E,'_', // _ .*.*
  0x45F,'_',0x9F,'_', // _ .*.*
  0x45E,0xF7,0xA2,'_', // ў ...*
  0x458,0x6A,0xBC,0x6A, // _ .*.*
  0x491,0xA3,0xB4,0xAD, // _ .*..
  0x451,0xF1,0xB8,0xA3, // ё
  0x454,0xF3,0xBA,0xA4, // є
  0x457,0xF5,0xBF,0xA7, // ї
  0x456,0x69,0xB3,0xA6, // _ .*..
  0x455,0x73,0xBE,0x73, // _ .*.*
  0x0A0,'_',0xA0,0x20, // space .*..
  0x0A4,'_',0xA4,0xFD, // ¤   .*..
  0x0A6,'_',0xA6,'_', // ¦   .*.*
  0x0B0,0xF8,0xB0,0x9C, // °
  0x0B7,0xFA,0xB7,0x9E, // ·
  // 0x2022,,0x95,0x95, //    .*..
  // 0x2116,0xFC,0xB9,0x23, // №   ...*
  // 0x2219,,0xF9,0x9E, //    .*..
  // 0x221A,0xFB,,0x96, // v   ..*.
  // 0x25A0,0xFE,,0x94, // ¦
  0x0000,0,0,0
};

unsigned int char16to8(unsigned int c)
{
  const TUNICODE2CHAR *p=unicode2char;
  unsigned int i;
  if (c<32) return(' ');
  if (c<128) return(c);
  while((i=p->u))
  {
    if (c==i)
    {
      switch(win_dos_koi)
      {
      case 1:
	//Win
	return(p->win);
      case 2:
	//Koi8
	return(p->koi8);
      }
      return(p->dos);
    }
    p++;
  }
  c&=0xFF;
  if (c<32) return(' ');
  return(c);
}

//--------------------------------------------------------------------------
//Печать символа
void DrawChar(int c,int x,int y)
{
  char *d, *dd; //Куда рисуем
//  char *s; //Откуда рисуем
  int i, j;
  int xb, xsb;
  int mask_h, mask_l;
//  if(rotate) {if(editmode) x+=SoftkeyH()+HeaderH()+YDISP+1; else x+=1;}
  int scr_wb = rotate?(SCR_HEIGHT>>3):(SCR_WIDTH>>3);
//  int scr_wb = (SCR_WIDTH>>3);
  

  if (c>=128)
    switch(win_dos_koi)
    {
    case 1:
      //Win->Dos
      c=wintranslation[c-128];
      break;
    case 2:
      //Koi8->Dos
      c=koi8translation[c-128];
      break;
    }

  xb = x >> 3;
  xsb = x&7;
  mask_h = (0xFF<<(8-xsb))&0xFF;
  mask_l = (0xFF>>xsb)&0xFF;
  unsigned char *l = malloc(FW+1);
  

  dd=myscr+(y*(FH*(scr_wb))+xb); //Основной экран

  for(i = 0; i < FH; i++)
  {
    l[FW] = 0;
    memcpy(l, &font[FW*FH*c+i*FW], FW);
    for(j = FW; j; j--)
    {
      l[j] &= mask_l;
      l[j] |= l[j-1]<<(8-xsb);
      l[j-1] >>= xsb;
    }
    l[0] |= (*dd)&mask_h;
    for(j = 0, d = dd; j < (FW+1) && xb+j < (scr_wb); j++, d++)
      *d = l[j];
    dd += (scr_wb);
  }
  mfree(l);
  
}

//Печать строки из буфера текста
void drawStkStr(char *p, unsigned int y, unsigned int vp, int ep)
{
  unsigned int iw=0;
  unsigned int c;
  do
  {
    c=*p;
    if (c)
    {
      if (ep>=0) editline[ep++]=c;
      p++;
      if (vp!=0)
        vp--;
      else
      {
        DrawChar(c,iw,y); 
        iw += chars_width[c];
      }
    }
    else
    {
      DrawChar(' ',iw,y);
      iw += chars_width[' '];
    }
  }
  while(iw<(editmode?max_x_emode:max_x));
  if (ep>=0) while((c=*p++)) editline[ep++]=c; //Добиваем остаток строки
}

void drawFrmStkStr(char *p, unsigned int y, unsigned int vp, int ep)
{
  unsigned int i=0, iw=0;
  unsigned int c;
  unsigned long spcsum;
  unsigned long spcadd;
  unsigned int spcs=0;

  
  //Надо посчитать пробелы
  if (*p)
  {
//    i=1; //Считаем со второго символа
    if(*p == ' ') *p = 1; //костыль для попиксельного расширения
    iw += chars_width[p[0]];
    while((c=p[i++])) //Пока не конец строки
    {
      if(c == ' ') c = 1; //костыль для попиксельного расширения
      if (c==1) spcs++; //Считаем пробелы
      iw += chars_width[c];
    }
  }
  if (iw>(editmode?max_x_emode:max_x))
    i=0; //Не добавляем пробелы, строка длиннее, чем экран
  else
  {
//    i=max_x-i; //Теперь в i - общее количество добавляемых пробелов
//    i=((editmode?max_x_emode:max_x)-iw)/chars_width[' ']; //Теперь в i - общее количество добавляемых пробелов
    i=((editmode?max_x_emode:max_x)-iw)/chars_width[1]; //Теперь в i - общее количество добавляемых пробелов
  }
  spcadd=0;
  spcsum=0;
  if (spcs)
  {
    spcadd=((unsigned long)i<<16)/spcs;
    spcsum=((unsigned long)i<<16)%spcs;
  }
  spcsum+=spcadd; //Начальное значение
  
  iw=0;
  c=*p;
  if (c)
  {
    if (ep>=0) editline[ep++]=c;
    if (vp!=0) vp--; else {DrawChar(c,iw,y); iw += chars_width[c];}
    p++;
  }
  else goto L2;
  do
  {
    c=*p;
    if(c == ' ') c = 1; //костыль для попиксельного расширения
    if (c)
    {
      if (ep>=0) editline[ep++]=c;
      if (vp!=0) vp--; else {DrawChar(c,iw,y); iw += chars_width[c];}
      if (c==1)
      {
	//Добавляем пробелы
	if (spcsum>=65536)
	{
	  spcsum-=65536;
	  continue;
	}
	spcsum+=spcadd;
      }
      p++;
    }
    else
    {
    L2:
//      DrawChar(' ',iw,y);
//      iw += chars_width[' '];
      DrawChar(1,iw,y);
      iw += chars_width[1];
    }
  }
  while(iw<(editmode?max_x_emode:max_x));
  if (ep>=0) while((c=*p++)) editline[ep++]=c; //Добиваем остаток строки
}

//Поиск начала строки в верхнем стеке
extern unsigned int bl_us(unsigned int pos);
extern unsigned int bl_ds(unsigned int pos);

//Перенос из верхнего стека в нижний (на строку вверх)
extern void move_up(void);
//Перенос из нижнего стека в верхний (на строку вниз)
extern void move_dw(void);
//---------------------------------------
// Работа с таблицей блоков
//---------------------------------------
//Поиск первого свободного блока
int FindFreeBlock(void)
{
  unsigned int i=0;
  do
  {
    if (!bfree[i])
    {
      bfree[i]=1;
      break;
    }
  }
  while((++i)!=MAXBLOCK);
  return(i);
}

//---------------------------------------
// Загрузка с диска нового фрагмента
//---------------------------------------
void DoDiskAccess(unsigned int flag)
{
  int f;
  char b;
  unsigned int ul;
  unsigned int seekpos;
  
  if ((f=stk_fhandle)==-1)
  {
    stk_fhandle=f=fopen(stkfile,A_ReadWrite+A_BIN,P_READ+P_WRITE,&ul); //Файл верхнего стека
    if (stk_fhandle==-1) DiskErrorMsg(3);
  }
  if (disk_access&LOAD_UP)
  {
    memcpy(ustk+STKSZ50,ustk,usp);
    b=ubat[u_disk--];
    bfree[b]=0;
    seekpos=STKSZ50*b;
    if (lseek(f,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (fread(f,ustk,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(0);
    usp+=STKSZ50;
  }
  if (disk_access&LOAD_DOWN)
  {
    memcpy(dstk+(dsp-STKSZ50),dstk+dsp,STKSZ-dsp);
    b=dbat[d_disk--];
    bfree[b]=0;
    seekpos=STKSZ50*b;
    if (lseek(f,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (fread(f,dstk+STKSZ50,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(0);
    dsp-=STKSZ50;
  }
  if (disk_access&SAVE_UP)
  {
    b=FindFreeBlock();
    ubat[++u_disk]=b;
    seekpos=STKSZ50*b;
    if (lseek(f,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (fwrite(f,ustk,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(1);
    memcpy(ustk,ustk+STKSZ50,usp-=STKSZ50);
  }
  if (disk_access&SAVE_DOWN)
  {
    b=FindFreeBlock();
    dbat[++d_disk]=b;
    seekpos=STKSZ50*b;
    if (lseek(f,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (fwrite(f,dstk+STKSZ50,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(1);
    memcpy(dstk+(dsp+STKSZ50),dstk+dsp,STKSZ50-dsp);
    dsp+=STKSZ50;
  }
  disk_access=0;
  if (flag)
  {
    fclose(f,&ul);
    stk_fhandle=-1;
  }
  if ((!terminated)/*&&flag*/)
  {
    REDRAW();
  }
  return;
}

//------------------------------------------
// Проверка необходимости чтения/записи с диска/на диск
//------------------------------------------
void CheckDiskAccess(void)
{
  if ((usp<STKMIN)&&(u_disk>=0)) disk_access|=LOAD_UP;
  if ((dsp>STKMAX)&&(d_disk>=0)) disk_access|=LOAD_DOWN;
  if (usp>STKMAX) disk_access|=SAVE_UP;
  if (dsp<STKMIN) disk_access|=SAVE_DOWN;
}

//-------------------------------------------------------
// Работа с историей
//-------------------------------------------------------
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


unsigned int SearchHistory(void)
{
  unsigned int history_pos=0;
  int fin;
  int i;
  unsigned int ul;
  char historyfile[128];
  snprintf(historyfile,sizeof(historyfile),"%sTED.history",ted_path);
  
  if ((fin=fopen(historyfile,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    for(;;)
    {
      i=fread(fin,&HISTORY,sizeof(HISTORY),&ul);
      if (i<sizeof(HISTORY)) goto L_NO_HISTORY;
      if (!strcmp_nocase(HISTORY.name,filename))
      {
   	history_pos|=0x8000;
	break; //Нашли
      }
      history_pos++;
    }
  L_NO_HISTORY:
    fclose(fin,&ul);
  }
  return(history_pos);
}

//Записать историю, вызывается в контексте MMC_Filesystem
void SaveHistory(void)
{
  int f;
  unsigned int ul;
  char ss[sizeof(HISTORY)];
  unsigned int history_pos;
  
  char historyfile[128];
  snprintf(historyfile,sizeof(historyfile),"%sTED.history",ted_path);
  
  memcpy(ss,&HISTORY,sizeof(HISTORY));
  history_pos=SearchHistory()&0x7FFF;
  memcpy(&HISTORY,ss,sizeof(HISTORY));
  memcpy(HISTORY.name,filename,128);
  HISTORY.rotate=rotate;
  HISTORY.font=font_selected;
  HISTORY.line=curline;
  HISTORY.total=total_line;
  HISTORY.codepage=win_dos_koi;
  HISTORY.cursor_off=cursor_off;
  if ((f=fopen(historyfile,A_ReadWrite+A_BIN,P_READ+P_WRITE,&ul))==-1)
    f=fopen(historyfile,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    lseek(f,sizeof(HISTORY)*history_pos,0,&ul,&ul);
    fwrite(f,&HISTORY,sizeof(HISTORY),&ul);
    fclose(f,&ul);
  }
  /*  if (terminated)
  {
  //Записываем snap-shoot
  if ((f=FileOpen((STR)snapshootfile,_O_BINARY+_O_CREAT+_O_RDWR,_S_IEXEC))!=-1)
  {
  FileWrite(f,(void far *)0x80000,16384);
  FileWrite(f,(void far *)0x84000,16384);
  FileWrite(f,(void far *)0x88000,16384);
  FileWrite(f,(void far *)0x8C000,16384);
  FileWrite(f,(void far *)0x90000,16384);
  FileClose(f);
}
}*/
}
//------------------------------------------
// Собственно редактор
//------------------------------------------
void GotoLine(void) //Переход на строку seek_to_line, вызывается в контексте MMC_Filesystem
{
  // unsigned int l;
  // unsigned int p;
  unsigned int ul;
  
  for(;;)
  {
    disk_access=0; //Закончили дисковые операции
    CheckDiskAccess();
    if (disk_access) DoDiskAccess(0);
    if (seek_to_line==curline) break; //Пришли
    if (seek_to_line<curline)
    {
      //Пытаемся идти вверх
      if (!curline) break; //начало!
      if (curline==viewline) viewline--; //Если первая строка экрана
      curline--;
      move_up();
    }
    else
    {
      //Пытаемся идти вниз
      if (dsp==STKSZ) break; //Конец текста
      curline++;
      if ((curline-viewline)==(editmode?max_y_emode:max_y))
      {
	viewline++;
      }
      move_dw();
    }
  }
  if (stk_fhandle!=-1)
  {
    fclose(stk_fhandle,&ul);
    stk_fhandle=-1;
  }
  draw_mode=1; //Перерисовываем
  if (!terminated) REDRAW();
}

void LineUp(void)
{
  // unsigned int l;
  // unsigned int p;
  if (curline) //Не начало!
  {
    if (curline==viewline) viewline--; //Если первая строка экрана
    curline--;
    move_up();
  }
}

void LineDw(void)
{
  // unsigned int l;
  // unsigned int p;
  if (dsp==STKSZ) return; //Конец текста
  curline++;
  if ((curline-viewline)==(editmode?max_y_emode:max_y))
  {
    viewline++;
  }
  move_dw();
}

void PageUp(unsigned int lines)
{
  unsigned int i;
  // unsigned int l;
  // unsigned int p;
  if (curline<lines)
  {
    i=curline;
    viewline=0;
    curline=0;
  }
  else
  {
    i=lines;
    curline-=i;
    if (viewline>i) viewline-=i; else viewline=0;
  }
  while(i)
  {
    move_up();
    i--;
  }
}

void PageDw(unsigned int lines)
{
  unsigned int i;
  // unsigned int l;
  // unsigned int p;
  i=lines;
  do
  {
    if (dsp==STKSZ) break; //Конец текста
    viewline++;
    curline++;
    move_dw();
  }
  while(--i);
}

void ToEOL(void)
{
  unsigned int i=strlen(editline);
  if (i>255) curpos=0; else curpos=i;
  if (curpos>=(editmode?max_x_emode:max_x)) viewpos=curpos-(editmode?max_x_emode:max_x)+1; else viewpos=0;
}

void ToBOL(void)
{
  curpos=0;
  viewpos=0;
}

void WordLeft(void)
{
  if (curpos==0) return;
  for(;;)
  {
    if ((--curpos)==0) break;
    if ((editline[curpos-1]==' ')&&(editline[curpos]!=' ')) break;
  }
  while(curpos<viewpos)
  {
    if (viewpos>8) viewpos-=8; else viewpos=0;
  }
}

void WordRight(void)
{
  int p, x, xw;
  if (!editline[curpos]) return;
  for(;;)
  {
    curpos++;
    if (!editline[curpos]) break;
    if ((editline[curpos-1]==' ')&&(editline[curpos]!=' ')) break;
  }
  
  for(x=curpos-viewpos, xw=0, p=dsp+viewpos; x; x--)
    xw += chars_width[*(dstk+p++)];

  while(xw>=(editmode?max_x_emode:max_x))
  {
    viewpos+=8;
    for(x=curpos-viewpos, xw=0, p=dsp+viewpos; x; x--)
      xw += chars_width[*(dstk+p++)];
  }
}

void DrawInfo(void)
{
  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  char codepage[32];
  switch(win_dos_koi)
  {
    case 1:
      strcpy(codepage, "win1251");
      break;
    case 2:
      strcpy(codepage, "koi8");
      break;
    default:
      strcpy(codepage, "dos866");
      break;
  }
  
  DrawRoundedFrame(0,YDISP,scr_w-1,scr_h-1,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  str_2ws(e_ws,filename,126);
  wsprintf(info_ws,"Time:\n%02d:%02d\n"
	   "Current line %lu\nTotal lines %lu\nCodepage: %s\n\nCurrent file:\n%w",
	   t.hour,t.min,curline,total_line,codepage,e_ws);
  DrawString(info_ws,3,3+YDISP,scr_w-4,scr_h-4,FONT_SMALL,2,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

//=============================================================================
//Вывод на экран
//=============================================================================
#pragma optimize=z 9
void DrawScreen(void)
{
  unsigned int y;
  unsigned int p;
  unsigned int c;
  int f;
  unsigned int my;
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  int scr_wb = rotate?(SCR_HEIGHT>>3):(SCR_WIDTH>>3);
  
  int r_sw, r_sh;
  if(rotate && !editmode)
  {
    r_sw = scr_h-YDISP;
    r_sh = scr_w;
  }
  else
  {
    r_sw = scr_w;
    r_sh = scr_h-YDISP;
  }
  zeromem(myscr,sizeof(myscr));
  
  char *ink=GetPaletteAdrByColorIndex(INK);
  char *paper=GetPaletteAdrByColorIndex(PAPER);
  
  if (disk_access)
  {
    DrawRoundedFrame(0,YDISP+8,8,GetFontYSIZE(FONT_SMALL)+YDISP-1,0,0,0,paper,paper);
    DrwImg((IMGHDR *)&imgDiskAccess,0,YDISP,ink,paper);
    if (draw_mode==2)
    {
      wsprintf(upinfo_ws,"Goto line %u...",curline);
      goto L_W1;
    }
    if (disk_access==SAVE_FILE)
    {
      wsprintf(upinfo_ws,"Saving...");
      goto L_W1;
    }
    if (disk_access==FIRSTLOAD)
    {
      wsprintf(upinfo_ws,"Line %u...",curline);
    L_W1:
      DrawRoundedFrame(8,YDISP,scr_w-1,GetFontYSIZE(FONT_SMALL)+YDISP-1,0,0,0,paper,paper);
      DrawString(upinfo_ws,8,YDISP,scr_w-1,GetFontYSIZE(FONT_SMALL)+YDISP-1,FONT_SMALL,2,ink,paper);
      goto L_WELLCOME2;
    }
    if (draw_mode==255) goto L_WELLCOME;
  }
  else
  {
    switch(draw_mode)
    {
    case 1:
      my=(editmode?max_y_emode:max_y);
      zeromem(editline,256);
      //Перерисовываем весь экран
      y=curline-viewline;
      p=usp;
      if (dsp!=STKSZ) c=dstk[dsp]; else c=0; //Первый символ текущей строки - если буква - форматируем
      while(y)
      {
	//Есть строки выше текущей
	p=bl_us(p);
	if ((c>' ')&&((HISTORY.fmt&0x80))&&(cursor_off))
	  drawFrmStkStr(ustk+p,--y,viewpos,-1);
	else
	  drawStkStr(ustk+p,--y,viewpos,-1);
	c=ustk[p];
      }
      y=curline-viewline;
      //Теперь печатаем от текущей вниз
      p=dsp;
      f=0;
      while(y!=(my))
      {
	if (p==STKSZ)
	{
	  drawStkStr("<<EOF>>",y++,0,-1);
	  while(y!=my) drawStkStr("",y++,viewpos,-1);
	  break;
	}
	else
	{
	  unsigned int p1;
	  p1=bl_ds(p);
	  if (p1!=STKSZ) c=dstk[p1]; else c=0; //Посл. строка не расширяется
	  if ((c>' ')&&((HISTORY.fmt&0x80))&&(cursor_off))
	    drawFrmStkStr(dstk+p,y++,viewpos,f);
	  else
	    drawStkStr(dstk+p,y++,viewpos,f);
	  p=p1;
	  f=-1;
	}
      }
      //DrawCursor(curpos-viewpos,curline-viewline);
      {
	//Рисуем скролл-бар
	char *d=myscr+((r_sw-1)>>3); //Последний байт
	if (total_line)
	  y=((editmode?sheight_emode-8:r_sh-8)*curline)/total_line;
	else
	  y=0;
	p=0;
	do
	{
	  if ((p<y)||(p>(y+7)))
	    *d=p&1?0x50:0x28;
	  else
	    *d=0x78;
	  d+=scr_wb;
	  p++;
	}
	while(p<r_sh);
      }
      if (editmode)
      {
        int h=HeaderH()+YDISP;
        int rh=((h+7)&(~7));
        int s=SoftkeyH();
        int rs=((s+7)&(~7));
	MyScrHdr.h=scr_h-rh-rs;
	DrawRoundedFrame(0,h,scr_w-1,rh-1,0,0,0,paper,paper);
	DrawRoundedFrame(0,scr_h-rs,scr_w-1,scr_h-s-1,0,0,0,paper,paper);
	DrwImg(&MyScrHdr,0,rh,ink,paper);
      }
      else
      {
	MyScrHdr.h=scr_h-YDISP;
	DrwImg(&MyScrHdr,0,YDISP,ink,paper);
      }
      cursor_cnt=3;
      goto L_CURSOR;
    case 2:
      //Процесс перехода на строку
      {
	wsprintf(upinfo_ws,"Goto line %u...",curline);
	DrawRoundedFrame(0,YDISP,scr_w-1,GetFontYSIZE(FONT_SMALL)+YDISP,0,0,0,paper,paper);
	DrawString(upinfo_ws,0,YDISP,scr_w-1,GetFontYSIZE(FONT_SMALL)+YDISP,FONT_SMALL,2,ink,paper);
	goto L_WELLCOME2;
      }
      //return;
    case 4:
      //Экран информации
      DrawInfo();
      return;
    case 255:
      //Экран приветствия
    L_WELLCOME:
      DrawRoundedFrame(0,YDISP,scr_w-1,GetFontYSIZE(FONT_SMALL)+YDISP-1,0,0,0,paper,paper);
      draw_mode=1;
    L_WELLCOME2:
      DrawRoundedFrame(0,GetFontYSIZE(FONT_SMALL)+YDISP,scr_w-1,scr_h-1,0,0,0,paper,paper);
      str_2ws(e_ws,filename,126);
      wsprintf(info_ws,"Text viewer/editor\nversion 1.7\n" __DATE__ "\n" __TIME__ "\nCopyright(C)2006-2008\nby Rst7/CBSIE\n\n%w",e_ws);
      DrawString(info_ws,0,GetFontYSIZE(FONT_SMALL)+9+YDISP,scr_w-1,ScreenH()-1,FONT_SMALL,2,ink,paper);
      return;
    case 0:
      //Курсор
      if (cursor_cnt)
      {
	cursor_cnt--;
	break;
      }
    L_CURSOR:
      {
	unsigned int x, xw;
	unsigned int y=curline-viewline;
	unsigned int dy=editmode?((HeaderH()+7)&(~7)):0;

	my=(editmode?max_y_emode:max_y);

        for(x=curpos-viewpos, xw=0, p=dsp+viewpos; x && *(dstk+p); x--)
          xw += chars_width[*(dstk+p++)];
        for(; x; x--)
          xw += chars_width[' '];
    
	if ((xw<(editmode?max_x_emode:max_x))&&(y<my)&&(!cursor_off))
	{
	  int yy=y*FH;
          if(rotate && !editmode)
          {
            if(rotate==2)
  	      DrawRoundedFrame(scr_w-(yy+FH),xw+YDISP,scr_w-yy,xw+YDISP+chars_width[*(dstk+p)],0,0,0,ink,GetPaletteAdrByColorIndex(23));
            else
  	      DrawRoundedFrame(yy,r_sw-xw+YDISP-dy,yy+FH,r_sw-xw-chars_width[*(dstk+p)]+YDISP-dy,0,0,0,ink,GetPaletteAdrByColorIndex(23));
          }
          else
	    DrawRoundedFrame(xw,yy+YDISP+dy,xw+chars_width[*(dstk+p)],yy+dy+YDISP+FH,0,0,0,ink,GetPaletteAdrByColorIndex(23));
	}
      }
      break;
    }
    draw_mode=1;
  }
  return;
}

int DrawLoadMenu(void);
void DrawSoftMenu(void);

void doCurRight(void)
{
  int p, xw = 0, x;
  if (cursor_off)
  {
    if (curpos>=(256-8)) return;
    curpos+=8;
    viewpos+=8;
    draw_mode=1;
    return;
  }
  if (curpos>=256) return;
  curpos++;
  
  p=dsp+viewpos;
  
  for(x=curpos-viewpos; x; x--)
  {
    char c = *(dstk+p);
    if(c!=13)
    {
      xw += chars_width[c];
      p++;
    }
    else
      xw += chars_width[' '];
  };
        
  if (xw>=(editmode?max_x_emode:max_x))
  {
    viewpos+=8;
  }
  draw_mode=1;
}

void doCurLeft(void)
{
  if (cursor_off)
  {
    if (curpos<8)
      curpos=0;
    else
      curpos-=8;
    if (viewpos<8)
      viewpos=0;
    else
      viewpos-=8;
    draw_mode=1;
    return;
  }
  if (curpos==0) return;
  draw_mode=1;
  curpos--;
  if (curpos>=viewpos) return;
  if (viewpos>8) viewpos-=8; else viewpos=0;
}

void insline(void)
{
  text_changed=1;    
  dstk[--dsp]=0;
  total_line++;
  GeneralFuncF1(1);
}

void delline(void)
{
  text_changed=1;    
  if (dsp!=STKSZ)
  {
    dsp=bl_ds(dsp);
    total_line--;
  }
  GeneralFuncF1(1);
}

void splitline(void)
{
  if ((curpos<=strlen(dstk+dsp))&&(dsp!=STKSZ))
  {
    while(curpos)
    {
      ustk[usp++]=dstk[dsp++];
      curpos--;
    }
    viewpos=0;
    ustk[usp++]=0;
    total_line++;
    curline++;
    text_changed=1;    
  }
  GeneralFuncF1(1);
}

void joinlines(void)
{
  unsigned int p=bl_ds(dsp);
  if (p!=STKSZ)
  {
    p--;
    while(p!=dsp)
    {
      dstk[p]=dstk[p-1];
      p--;
    }
    dsp++;
    total_line--;
    text_changed=1;    
  }
  GeneralFuncF1(1);
}

void instime(void)
{
  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  usp+=sprintf(ustk+usp,"%02d:%02d",t.hour,t.min)+1;
  curline++;
  total_line++;
  text_changed=1;    
  GeneralFuncF1(1);
}

void insdate(void)
{
  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  usp+=sprintf(ustk+usp,"%02d-%02d-%04d",d.day,d.month,d.year)+1;
  curline++;
  total_line++;
  text_changed=1;    
  GeneralFuncF1(1);
}

void paste(void)
{
  clip_pasted=1;
  GeneralFuncF1(1);
}

//void cliperase(void)
//{
// FileErase((STR)clipfile);
//}

void clearclipb(void)
{
  // FilesysICall(cliperase);
  clip_pasted=1;
  GeneralFuncF1(1);
}

void* edmenu_HNDLS[8]=
{
  (void *)delline,
  (void *)insline,
  (void *)splitline,
  (void *)joinlines,
  (void *)instime,
  (void *)insdate,
  (void *)paste,
  (void *)clearclipb
};

MENUITEM_DESC edmenu_ITEMS[8]=
{
  {NULL,(int)"Delete line"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Insert line"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Split line"     ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Join lines"     ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Insert time"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Insert date"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Paste"          ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Clear clipboard",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

HEADER_DESC edmenu_HDR={0,0,0,0,icon,(int)"Special...",LGP_NULL};

MENU_DESC edmenu_STRUCT=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  edmenu_ITEMS,
  (MENUPROCS_DESC*)&edmenu_HNDLS,
  8
};

int ed_inp_onkey(GUI *data, GUI_MSG *msg)
{
  int k=msg->gbsmsg->submess;
  
  if (msg->keys==0xFFF)
  {
    editmode=0xFFF; //Признак меню
    patch_header(&edmenu_HDR);
    edit_id=CreateMenu(0,0,&edmenu_STRUCT,&edmenu_HDR,0,8,0,0);
    return(1); //Закрываем лавочку
  }
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    switch(k)
    {
    case GREEN_BUTTON:
    case VOL_UP_BUTTON:
    case VOL_DOWN_BUTTON:
      editmode=k;
      return(1);
    case LEFT_BUTTON:
    case RIGHT_BUTTON:
      if(rotate && !editmode)
      {
        editmode=k;
        return(1);
      }
      break;

    case UP_BUTTON:
    case DOWN_BUTTON:
      if(!rotate || editmode)
      {
        editmode=k;
        return(1);
      }
      break;      
    }
  }
  return(0); //Do standart keys
  //1: close
}

void ed_inp_redraw(void *data)
{
  unsigned int sz;
  unsigned int p;
  
  sz=e_ws->wsbody[0];
  p=0;
  while((p<255)&&(p<sz))
  {
    unsigned int wc=e_ws->wsbody[p+1];
    editline[p]=char16to8(wc);
    p++;
  }
  editline[p]=0;
  if ((sz=dsp)==STKSZ)
  {
    text_changed=1;    
    total_line++;
  }
  else
  {
    if (strcmp(editline,dstk+dsp)!=0) text_changed=1;
  }
  sz=bl_ds(sz); //Ищем начало сл. строки
  sz-=p+1; //Вновь добавляемая строка
  strcpy(dstk+(dsp=sz),editline); //Добавляем
  draw_mode=1;
  DrawScreen();
}

void ed_inp_locret(void){}

void ed_inp_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Menu"};
  static void *methods[16];
  EDITCONTROL ec;
  int ecp;
  if (cmd==2)
  {
    //Called after onCreate
    void **m=GetDataOfItemByID(data,4);
    memcpy(methods,m[1],sizeof(methods));
    //    old_inp_redraw=methods[0];
    methods[0]=(void *)ed_inp_redraw;
    m[1]=methods;
  }
  if (cmd==7)
  {
    if (!editmode)
    {
      EDIT_SetCursorPos(data,curpos+1);
      editmode=0xFFFFFFFF;
    }
    ecp=EDIT_GetCursorPos(data);
    ecp--;
    while(ecp>curpos) doCurRight();
    while(ecp<curpos) doCurLeft();
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    ExtractEditControl(data,1,&ec);
    wstrcpy(e_ws,ec.pWS);
  }
}

HEADER_DESC ed_inp_hdr={0,0,0,0,icon,(int)"Edit text",LGP_NULL};

INPUTDIA_DESC ed_inp_desc=
{
  1,
  ed_inp_onkey,
  ed_inp_ghook,
  (void *)ed_inp_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

void CreateEditDialog(void)
{
  unsigned int p;
  unsigned int c;
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  
  editmode=0;
  cursor_off=0;
  while ((curline-viewline)>=max_y_emode) viewline++; //Если ниже чем 16 строк - перемещаемся
  
  CutWSTR(e_ws,0);
  if ((p=dsp)!=STKSZ)
  {
    while((c=dstk[p]))
    {
      wsAppendChar(e_ws,char8to16(c));
      p++;
    }
  }
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,e_ws,255);
  AddEditControlToEditQend(eq,&ec,ma);
  
  patch_header(&ed_inp_hdr);
  patch_input(&ed_inp_desc);
  edit_id=CreateInputTextDialog(&ed_inp_desc,&ed_inp_hdr,eq,1,0);
}


void SetViewIllumination(void)
{
  extern const int ADJ_LIGHT;
  if (ADJ_LIGHT)
  {
#ifdef ELKA
#else
    SetIllumination(0,1,DISPLAY_LIGHT,0);
    SetIllumination(1,1,0,0);
#endif
  }
  //  light_count=30;
  //  GBS_StartTimerProc(&light_tmr,1,LightTimerProc);
}

//Перерисовка основного диалога
void maincsm_onRedraw(MAIN_GUI *data)
{
  if (data->gui.state==2)
  {
    DrawScreen();
  }
}

void maincsm_onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  void FirstLoadFile(unsigned int);
  SUBPROC((void *)FirstLoadFile,0xFFFFFFFF);
  data->gui.state=1;
}

void maincsm_onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  terminated=1;
  data->gui.state=0;
}

void maincsm_onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  if (!draw_mode) draw_mode=1;
  DisableIDLETMR();
  data->gui.state=2;
}

void maincsm_onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

extern void kill_data(void *p, void (*func_p)(void *));

void maincsm_onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
  //  mfree_adr(data);
}

int method8(void){return(0);}

int method9(void){return(0);}

void actLeft(int d)
{
  if (d)
    doCurLeft();
  else
  {
    WordLeft();
    cursor_off&=0xFE;
    draw_mode=1;
  }
}

void actRight(int d)
{
  if (d)
    doCurRight();
  else
  {
    WordRight();
    cursor_off&=0xFE;
    draw_mode=1;
  }  
}

void actUp()
{
  if (cursor_off)
    PageUp(1);
  else
    LineUp();
  draw_mode=1;
}

void actDown()
{
  if (cursor_off)
    PageDw(1);
  else
    LineDw();
  draw_mode=1;
}

void QuitCallbackProc(int decision)
{
  if(!decision)
    Quit_Required = 1;
}

void DisplayQuitQuery()
{
  MsgBoxYesNo(1,(int)"Exit without save?",QuitCallbackProc);
}

//------------------------------------------------------------------------------
// Осн. диалог - обработка кнопок
//------------------------------------------------------------------------------
int maincsm_onKey(MAIN_GUI *data, GUI_MSG *msg)
{
  void FirstLoadFile(unsigned int);
  if (disk_access) return(0); //Если дисковые операции
  if ((draw_mode>1)&&(draw_mode!=4)) return(0); //Если еще рисуем
  if (msg->gbsmsg->msg==KEY_UP)
  {
    if (draw_mode==4)
    {
      draw_mode=1;
      SetViewIllumination();
      DrawScreen();
    }
    return(0);
  }
  if ((msg->gbsmsg->msg==KEY_DOWN)||(msg->gbsmsg->msg==LONG_PRESS))
  {
    switch(msg->gbsmsg->submess)
    {
    case RED_BUTTON:
    case RIGHT_SOFT:
      //  L_EXIT:
      if (text_changed)
        DisplayQuitQuery();
      else
        return(1); //Происходит вызов GeneralFunc для тек. GUI -> закрытие GUI
      break;
    case GREEN_BUTTON:
      //    L_EDIT:
      CreateEditDialog();
      return(0);
    case ENTER_BUTTON:
      loadmenu_id=DrawLoadMenu();
//      loadmenu_id=0;
      return(0);
    case LEFT_SOFT:
      DrawSoftMenu();
      return(0);
    case UP_BUTTON:
      if(rotate && !editmode)
      {
        if(rotate==2)
          actLeft(msg->gbsmsg->msg!=LONG_PRESS);
        else
          actRight(msg->gbsmsg->msg!=LONG_PRESS);
      }
      else
        actUp();
      break;
      /*    case RECORD_BUTTON:
      if (cursor_off||(dsp==STKSZ)) break;
      else
      {
      unsigned int i=strlen(dstk+dsp); //Длина тек. строки
      char far *s;
      s=EX_heap_malloc_with_lock(i+2); //Т.к. добавляем 0 и 0d
      if (s)
      {
      strcpy(s,dstk+dsp);
      s[i]=0x0D;
      s[i+1]=0x00;
      FilesysICall_FP(add_to_clip,s);
    }
    }*/
    case DOWN_BUTTON:
      if(rotate && !editmode)
      {
        if(rotate==2)
          actRight(msg->gbsmsg->msg!=LONG_PRESS);
        else
          actLeft(msg->gbsmsg->msg!=LONG_PRESS);
      }
      else
        actDown();
      break;
    case VOL_UP_BUTTON:
      PageUp((editmode?max_y_emode:max_y));
      draw_mode=1;
      break;
    case '2':
      if(rotate && !editmode)
      {
        if(rotate==2)
        {
          WordLeft();
          cursor_off&=0xFE;
          draw_mode=1;
        }
        else
        {
          WordRight();
          cursor_off&=0xFE;
          draw_mode=1;
        }
      }
      else
      {
        PageUp((editmode?max_y_emode:max_y));
        draw_mode=1;
      }
      break;
    case VOL_DOWN_BUTTON:
      PageDw((editmode?max_y_emode:max_y));
      draw_mode=1;
      break;
    case '8':
      if(rotate && !editmode)
      {
        if(rotate==2)
        {
          WordRight();
          cursor_off&=0xFE;
          draw_mode=1;
        }
        else
        {
          WordLeft();
          cursor_off&=0xFE;
          draw_mode=1;
        }
      }
      else
      {
        PageDw((editmode?max_y_emode:max_y));
        draw_mode=1;
      }
      break;
    case '5':
      cursor_off^=1;
      draw_mode=1;
      break;
    case LEFT_BUTTON:
      if(rotate && !editmode)
        if(rotate==2)
          actDown();
        else
          actUp();
      else
          actLeft(msg->gbsmsg->msg!=LONG_PRESS);
      break;
    case '4':
      if(rotate && !editmode)
      {
        if(rotate==2)
        {
          PageDw((editmode?max_y_emode:max_y));
          draw_mode=1;        
        }
        else
        {
          PageUp((editmode?max_y_emode:max_y));
          draw_mode=1;        
        }
      }
      else
      {
        //На слово влево
        WordLeft();
        cursor_off&=0xFE;
        draw_mode=1;
      }
      break;
    case RIGHT_BUTTON:
      if(rotate && !editmode)
        if(rotate==2)
          actUp();
        else
          actDown();
      else
          actRight(msg->gbsmsg->msg!=LONG_PRESS);
      break;
    case '6':
      if(rotate && !editmode)
      {
        if(rotate==2)
        {
          PageUp((editmode?max_y_emode:max_y));
          draw_mode=1;        
        }
        else
        {
          PageDw((editmode?max_y_emode:max_y));
          draw_mode=1;        
        }
      }
      else
      {
        //На слово вправо
        WordRight();
        cursor_off&=0xFE;
        draw_mode=1;
      }
      break;
    case '9':
      ToEOL();
      cursor_off&=0xFE;
      draw_mode=1;
      break;
    case '7':
      ToBOL();
      cursor_off&=0xFE;
      draw_mode=1;
      break;
    case '0':
      draw_mode=4;
      break;
    case '#':
      if (win_dos_koi>1) win_dos_koi=0; else win_dos_koi++;
      CharWidthForCodepage();
      draw_mode=1;
      break;
    case '*':
      if(!editmode)
        rotate++;
      if(rotate>2)
        rotate = 0;
      HISTORY.rotate = rotate;
      disk_access=FIRSTLOAD;
      draw_mode=255; //Экран приветствия
    
      SUBPROC((void *)FirstLoadFile,HISTORY.fmt);
  
      break;

    default:
      break;
    }
    CheckDiskAccess();
    if (disk_access) SUBPROC((void *)DoDiskAccess,1);
    SetViewIllumination();
    DrawScreen();
    return(0);
  }
  return(0);
}

//===================================================================
// Меню загрузки файла
//===================================================================
int sf_inp_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF)
  {
    extern void savetext(void);
    void UpdateCSMname(void);
    ws_2str(e_ws,filename,126);
    UpdateCSMname();
    HISTORY.fmt=0; //Грузим его теперь как DirectLoad
    disk_access=SAVE_FILE;
    text_changed=0;    
    SUBPROC((void *)savetext);
    return(1); //Close
  }
  return(0);
}

void sf_inp_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Save..."};
  EDITCONTROL ec;
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    ExtractEditControl(data,1,&ec);
    wstrcpy(e_ws,ec.pWS);
  }
}

void sf_inp_locret(void){}

HEADER_DESC sf_inp_hdr={0,0,0,0,icon,(int)"Save as:",LGP_NULL};

INPUTDIA_DESC sf_inp_desc=
{
  1,
  sf_inp_onkey,
  sf_inp_ghook,
  (void *)sf_inp_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

void CreateSaveAsDialog(void)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  str_2ws(e_ws,filename,126);
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,e_ws,128);
  AddEditControlToEditQend(eq,&ec,ma);
  
  patch_header(&sf_inp_hdr);
  patch_input(&sf_inp_desc);
  CreateInputTextDialog(&sf_inp_desc,&sf_inp_hdr,eq,1,0);
}

typedef struct FontListItem FontListItem;

struct FontListItem
{
  char *name;
  int size;
  char *file;
  FontListItem *next;
};

FontListItem *FontList = NULL;

FontListItem *CreateFontListItem(char *n, char *f, int size)
{
  FontListItem *ret = malloc(sizeof(FontListItem));
  ret->next = NULL;
  ret->name = malloc(strlen(n)+1);
  ret->file = malloc(strlen(f)+1);
  strcpy(ret->name, n);
  strcpy(ret->file, f);
  ret->size = size;
  return ret;
}
                                  
void AddFont(char *n, char *f, int size)
{
  FontListItem *cur = FontList;
  if(!FontList)
  {
    FontList = CreateFontListItem(n, f, size);
    return;
  }
  while(cur->next)
    cur = cur->next;
  cur->next = CreateFontListItem(n, f, size);
}

void DeleteFonts(FontListItem *head)
{
  if(!head) return;
  if(head->next)
    DeleteFonts(head->next);
  mfree(head->name);
  mfree(head->file);
  mfree(head);
  fonts_count = 0;
}

int GetFontList()
{
  DIR_ENTRY de;
  unsigned int err, ul;
  char *path, *fname, tmp;
  char fn_font[17];
  int fin, n = 0;
  char size = 0;
  
  fn_font[16] = 0;
  
  DeleteFonts(FontList);
  FontList = NULL;
    
  path = malloc(strlen(ted_path)+7);
  strcpy(path, ted_path);
  strcat(path, "*.tfn");
  
  if (FindFirstFile(&de,path,&err))
  {
    do
    {
      if (!(de.file_attr&FA_DIRECTORY))
      {
        fname = malloc(strlen(de.folder_name) + strlen(de.file_name)+2);
        strcpy(fname, de.folder_name);
        strcat(fname, "\\");
        strcat(fname, de.file_name);
        
        if ((fin=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
        {
          fread(fin,&tmp,1,&ul);
          fread(fin,&size,1,&ul);
          fread(fin,fn_font,16,&ul);
          fclose(fin,&ul);
          AddFont(fn_font, fname, size);
        }
        n++;
        mfree(fname);
      }
    }
    while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  
  mfree(path);  
  fonts_count = n;
  return n;
}

void LoadFont(int flag)
{
  char fn_font[128], tmp;
  int fin;
  unsigned ul;
  int i, eh;
  
  FontListItem *cur = FontList;
  
  //snprintf(fn_font,sizeof(fn_font),"%sm%d.tfn",ted_path,font_size);
  for(i = 0; i < font_selected && cur; i++)
    cur=cur->next;

  if ((fin=fopen(cur->file,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {

    fread(fin,&tmp,1,&ul);
    FW = tmp;
    fread(fin,&tmp,1,&ul);
    FH = tmp;
    fread(fin,fn_font,16,&ul);

    if(font)
      mfree(font);
    font = malloc(256*FH*FW);
    for(i = 0; i < 256; i++)
    {
      fread(fin,&chars_width_src[i],1,&ul);
      fread(fin,font+i*FW*FH,FW*FH,&ul);
    }
    fclose(fin,&ul);
  }
  chars_width_src[1] = 1;
  zeromem(font+FW*FH, FW*FH);

  CharWidthForCodepage();
  
  if(rotate)
  {
    sheight_emode=eh=(sheight=ScreenH()-YDISP)-((HeaderH()+7)&(~7))-((SoftkeyH()+7)&(~7));
    
    max_y_emode=eh/FH;
    max_x_emode=ScreenW()-4;
    
    max_y=(ScreenW())/FH;
    max_x=ScreenH()-YDISP-4;
  }
  else
  {
    sheight_emode=eh=(sheight=ScreenH()-YDISP)-((HeaderH()+7)&(~7))-((SoftkeyH()+7)&(~7));
    
    max_y_emode=eh/FH;
    max_y=(ScreenH()-YDISP)/FH;
    max_x_emode=max_x=ScreenW()-4;
  }

    
  zeromem(myscr,sizeof(myscr));
  if(flag)
  {
    disk_access=0;
    draw_mode=1;
    if (!terminated) REDRAW(); //Перерисовываем
  }

}

void setfont(int sz)
{
//  strcpy(font_file, fname);

  font_selected=sz;
  if (disk_access==FIRSTLOAD) //Пришли из первой загрузки
  {
    ShowMSG(1,(int)"Font selected!");
    return;
  }
  
  disk_access=FIRSTLOAD;
  draw_mode=255; //Экран приветствия
//  SUBPROC((void *)loadfont,1);
  SUBPROC((void *)LoadFont,1);
  GeneralFuncF1(1); //Закрываем меню
}

void FirstLoadFile(unsigned int fmt);


void do_rotate(void)
{
  rotate++;
  if(rotate>2)
    rotate = 0;
  HISTORY.rotate = rotate;
  if (disk_access==FIRSTLOAD) //Пришли из первой загрузки
  {
    ShowMSG(1,(int)"Screen rotated!");
    return;
  }
  disk_access=FIRSTLOAD;
  draw_mode=255; //Экран приветствия

  GeneralFuncF1(1);
  SUBPROC((void *)FirstLoadFile,HISTORY.fmt);
}

void load_direct(void)
{
//  loadmenu_id=0;
  if(HISTORY.fmt!=255) GeneralFuncF1(1);
  draw_mode=255;
  disk_access=FIRSTLOAD;
  HISTORY.fmt = 0|(HISTORY.fmt&0x80);
  
  SUBPROC((void *)FirstLoadFile,0);
}

void load_format(void)
{
//  loadmenu_id=0;
  draw_mode=255;
  disk_access=FIRSTLOAD;
  HISTORY.fmt=1|(HISTORY.fmt&0x80);
  
  GeneralFuncF1(1);
  SUBPROC((void *)FirstLoadFile,1);
}

void load_eolspc(void)
{
//  loadmenu_id=0;
  draw_mode=255;
  disk_access=FIRSTLOAD;
  HISTORY.fmt=2|(HISTORY.fmt&0x80);
    
  GeneralFuncF1(1);
  SUBPROC((void *)FirstLoadFile,2);
}

void load_pad(void)
{
  HISTORY.fmt^=0x80;
  
  GeneralFuncF1(1);
}

void load_save(void)
{
  GeneralFuncF1(1);
  
  CreateSaveAsDialog();
}

//-------------------------------------------------------------------
int mode_menu_onkey(void *data, GUI_MSG *msg)
{
  int n = GetCurMenuItem(data);
  
  if(msg->keys==0x3D)
  {
    switch(n)
    {
    case 0:
//      GeneralFunc_flag1(loadmenu_id, 1);
      load_direct();
      break;
    case 1:
//      GeneralFunc_flag1(loadmenu_id, 1);
      load_format();
      break;
    case 2:
//      GeneralFunc_flag1(loadmenu_id, 1);
      load_eolspc();
      break;
    }
    return (0);
  }
  
  return (0);
}

void mode_menu_ghook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
    DisableIDLETMR();
}

void mode_menu_iconhndl(void * data, int curitem, void * user_pointer)
{
  WSHDR * ws;
  char tmp[128];
  int len;
  void * item = AllocMenuItem(data);
  tmp[0] = 0;
  switch(curitem)
  {
    case 0:
      if((HISTORY.fmt&0x7F)==0) strcat(tmp, asterix);
      strcat(tmp, "Direct load");
      //GeneralFunc_flag1(loadmenu_id, 1);
      break;
    case 1:
      if((HISTORY.fmt&0x7F)==1) strcat(tmp, asterix);
      strcat(tmp, "DOS format");
      //GeneralFunc_flag1(loadmenu_id, 1);
      break;
    case 2:
      if((HISTORY.fmt&0x7F)==2) strcat(tmp, asterix);
      strcat(tmp, "WIN format");
      //GeneralFunc_flag1(loadmenu_id, 1);
      break;
    default:
      strcpy(tmp, "Error");
      break;       
  }
  len = strlen(tmp);
  ws = AllocMenuWS(data, len + 4);
  str_2ws(ws, tmp, len);
  
  SetMenuItemText(data, item, ws, curitem);
}


MENUITEM_DESC modemenu_ITEMS[3]=
{
  {NULL,(int)"Direct load"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"DOS format"     ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"WIN format"     ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2}
};

HEADER_DESC modemenu_HDR={0,0,0,0,icon,(int)"Select mode",LGP_NULL};

MENU_DESC modemenu_STRUCT=
{
  8,mode_menu_onkey,mode_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  mode_menu_iconhndl,
  0,
  0, 
  3
};

int DrawModeMenu(void)
{
  patch_header(&modemenu_HDR);
  return CreateMenu(0,0,&modemenu_STRUCT,&modemenu_HDR,0,3,0,0);
}

//------------------------------------------------------------------------------

int font_menu_onkey(void *data, GUI_MSG *msg)
{
  int i, n = GetCurMenuItem(data);
  FontListItem *cur = FontList;
  
  for(i = 0; i < n && cur; i++)
    cur=cur->next;
  
  if (msg->keys==0x3D && cur)
  {
    setfont(i);
    return(0);
  }
  return (0);
}

void font_menu_ghook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
    DisableIDLETMR();
}

void font_menu_iconhndl(void * data, int curitem, void * user_pointer)
{
  WSHDR * ws;
  int i, len;
  void * item = AllocMenuItem(data);
  FontListItem *cur = FontList;
  
  for(i = 0; i < curitem && cur; i++)
    cur=cur->next;
  
  if (cur)
  {
    len = strlen(cur->name);
    ws = AllocMenuWS(data, len + 4);
    str_2ws(ws, cur->name, len);
  }

  SetMenuItemText(data, item, ws, curitem);
}


MENUITEM_DESC *fontmenu_ITEMS;

HEADER_DESC fontmenu_HDR={0,0,0,0,icon,(int)"Select font",LGP_NULL};

MENU_DESC fontmenu_STRUCT=
{
  8,font_menu_onkey,font_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  font_menu_iconhndl,
  0,
  0, //(MENUPROCS_DESC*)&loadmenu_HNDLS,
  0
};

int DrawFontMenu(void)
{
  int n=fonts_count;
 
  patch_header(&fontmenu_HDR);
  return CreateMenu(0,0,&fontmenu_STRUCT,&fontmenu_HDR,0,n,0,0);
}

//------------------------------------------------------------------------------

int load_menu_onkey(void *data, GUI_MSG *msg)
{
  int n = GetCurMenuItem(data);
  
  if(msg->keys==0x3D)
  {
    switch(n)
    {
    case 0:
      load_save();
      break;
    case 1:
      do_rotate();
      break;
    case 2:
      DrawModeMenu();
      break;
    case 3:
      load_pad();
      break;
    case 4:
      DrawFontMenu();
      break;

    }
    return (0);
  }
 
  return (0);
}

void load_menu_ghook(void *data, int cmd)
{
  if (cmd == TI_CMD_FOCUS)
    DisableIDLETMR();
}

void load_menu_iconhndl(void * data, int curitem, void * user_pointer)
{
  WSHDR * ws;
  int i, len;
  void * item = AllocMenuItem(data);
  FontListItem *cur = FontList;
  
  for(i = 0; i < font_selected && cur; i++)
    cur=cur->next;
  
   char tmp[128];
   switch(curitem)
   {
    case 0:
      strcpy(tmp, "Save as...");
      break;
    case 1:
      strcpy(tmp, "Rotate");
      break;
    case 2:
      switch((HISTORY.fmt&0x7F)+100)
      {
        case 100:
          strcpy(tmp, ">Direct load");
          break;
        case 101:
          strcpy(tmp, ">DOS format");
          break;
        case 102:
          strcpy(tmp, ">WIN format");
          break;
        default:
          strcpy(tmp, ">Direct load");
          //HISTORY.fmt=0;
          break;
      }
      break;
    case 3:
      if(HISTORY.fmt & 0x80)
        strcpy(tmp, "Padding on");
      else
        strcpy(tmp, "Padding off");
      break;
    case 4:
      if (cur)
      {
        strcpy(tmp, ">");
        strcat(tmp, cur->name);
      }
      else
        strcpy(tmp, ">Select font");
      break;
    default:
      strcpy(tmp, "Error");
      break;       
   }
  len = strlen(tmp);
  ws = AllocMenuWS(data, len + 4);
  str_2ws(ws, tmp, len);
    
  SetMenuItemText(data, item, ws, curitem);
}


MENUITEM_DESC *loadmenu_ITEMS;

HEADER_DESC loadmenu_HDR={0,0,0,0,icon,(int)"General...",LGP_NULL};

MENU_DESC loadmenu_STRUCT=
{
  8,load_menu_onkey,load_menu_ghook,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  load_menu_iconhndl,
  0,
  0, //(MENUPROCS_DESC*)&loadmenu_HNDLS,
  0
};

int DrawLoadMenu(void)
{
  int n=1;
 
 
  if (disk_access==FIRSTLOAD) n+=2; else n+=4;
//  *((int *)(&loadmenu_STRUCT.n_items))=n;
  patch_header(&loadmenu_HDR);
  return CreateMenu(0,0,&loadmenu_STRUCT,&loadmenu_HDR,0,5,0,0);
}



//-------------------------------------------------------------------


//===================================================================
// Меню Goto...
//===================================================================
void goto_l(unsigned long l)
{
  seek_to_line=l;
  draw_mode=2; //Переходим на нужную строку
  SUBPROC((void *)GotoLine);
  GeneralFuncF1(1);
}

void goto_top(void)
{
  goto_l(0);
}

void goto_bot(void)
{
  goto_l(0xFFFFFFFF);
}

int gl_num;

unsigned int my_atoui(WSHDR *ws)
{
  unsigned int i=0;
  int p=1;
  unsigned int c;
  while(p<=ws->wsbody[0])
  {
    c=ws->wsbody[p]-'0';
    if (c>9) break;
    i=(i*10)+c;
    p++;
  }
  return(i);
}

int gl_inp_onkey(GUI *data, GUI_MSG *msg)
{
  if (msg->keys==0xFFF)
  {
    if (gl_num)
    {
      seek_to_line=total_line*my_atoui(e_ws)/100;
    }
    else
    {
      seek_to_line=my_atoui(e_ws);
    }
    draw_mode=2; //Переходим на нужную строку
    SUBPROC((void *)GotoLine);
    return(1); //Close
  }
  return(0);
}

void gl_inp_ghook(GUI *data, int cmd)
{
  static SOFTKEY_DESC sk={0x0FFF,0x0000,(int)"Goto..."};
  EDITCONTROL ec;
  if (cmd==7)
  {
    SetSoftKey(data,&sk,SET_SOFT_KEY_N);
    ExtractEditControl(data,1,&ec);
    wstrcpy(e_ws,ec.pWS);
  }
}

void gl_inp_locret(void){}

HEADER_DESC gl_inp_hdr_percent={0,0,0,0,icon,(int)"Goto percent:",LGP_NULL};
HEADER_DESC gl_inp_hdr_line={0,0,0,0,icon,(int)"Goto line:",LGP_NULL};

INPUTDIA_DESC gl_inp_desc=
{
  1,
  gl_inp_onkey,
  gl_inp_ghook,
  (void *)gl_inp_locret,
  0,
  &menu_skt,
  {0,0,0,0},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};


void goto_line_inp(int f)
{
  void *ma=malloc_adr();
  void *eq;
  EDITCONTROL ec;
  CutWSTR(e_ws,0);
  wsAppendChar(e_ws,'0');
  gl_num=f;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,2,0x40,e_ws,7);
  AddEditControlToEditQend(eq,&ec,ma);
  patch_input(&gl_inp_desc);
  patch_header(f?&gl_inp_hdr_percent:&gl_inp_hdr_line);
  CreateInputTextDialog(&gl_inp_desc,f?&gl_inp_hdr_percent:&gl_inp_hdr_line,eq,1,0);
}

void goto_line(void)
{
  GeneralFuncF1(1);
  goto_line_inp(0); //Признак перехода по строке
}

void goto_percent(void)
{
  GeneralFuncF1(1);
  goto_line_inp(1); //Признак перехода по процентам
}

void goto_last_saved(void)
{
  goto_l(HISTORY.line);
}

void goto_book1(void)
{
  goto_l(HISTORY.bookm1);
}
void goto_book2(void)
{
  goto_l(HISTORY.bookm2);
}
void goto_book3(void)
{
  goto_l(HISTORY.bookm3);
}
void goto_book4(void)
{
  goto_l(HISTORY.bookm4);
}

void *gotomenu_HNDLS[9]=
{
  (void *)goto_top,
  (void *)goto_line,
  (void *)goto_percent,
  (void *)goto_bot,
  (void *)goto_last_saved,
  (void *)goto_book1,
  (void *)goto_book2,
  (void *)goto_book3,
  (void *)goto_book4
};

MENUITEM_DESC gotomenu_ITEMS[9]=
{
  {NULL,(int)"Top"       ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Line"      ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Percent"   ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Bottom"    ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Last saved",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)t_bm1       ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)t_bm2       ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)t_bm3       ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)t_bm4       ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

HEADER_DESC gotomenu_HDR={0,0,0,0,icon,(int)"Goto...",LGP_NULL};

MENU_DESC gotomenu_STRUCT=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  gotomenu_ITEMS,
  (MENUPROCS_DESC*)&gotomenu_HNDLS,
  9
};

void goto_menu(void)
{
  GeneralFuncF1(1);
  patch_header(&gotomenu_HDR);
  CreateMenu(0,0,&gotomenu_STRUCT,&gotomenu_HDR,0,9,0,0);
}

//===================================================================
// Меню Bookmark...
//===================================================================
void set_book1(void)
{
  HISTORY.bookm1=curline;
  GeneralFuncF1(1);
}

void set_book2(void)
{
  HISTORY.bookm2=curline;
  GeneralFuncF1(1);
}

void set_book3(void)
{
  HISTORY.bookm3=curline;
  GeneralFuncF1(1);
}

void set_book4(void)
{
  HISTORY.bookm4=curline;
  GeneralFuncF1(1);
}

MENUITEM_DESC bookmenu_ITEMS[4]=
{
  {NULL,(int)t_bm1,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)t_bm2,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)t_bm3,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)t_bm4,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

void *bookmenu_HNDLS[4]=
{
  (void *)set_book1,
  (void *)set_book2,
  (void *)set_book3,
  (void *)set_book4
};

HEADER_DESC bookmenu_HDR={0,0,0,0,icon,(int)"Set Bookmark...",LGP_NULL};

MENU_DESC bookmenu_STRUCT=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  bookmenu_ITEMS,
  (MENUPROCS_DESC*)&bookmenu_HNDLS,
  4
};

void bookm_menu(void)
{
  GeneralFuncF1(1);
  patch_header(&bookmenu_HDR);
  CreateMenu(0,0,&bookmenu_STRUCT,&bookmenu_HDR,0,4,0,0);
}
//===================================================================
// Меню по левому софту
//===================================================================

void search_menu(void)
{
}

MENUITEM_DESC softmenu_ITEMS[3]=
{
  {NULL,(int)"Goto..."        ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Set Bookmark...",LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
  {NULL,(int)"Search..."      ,LGP_NULL,0,NULL,MENU_FLAG3,MENU_FLAG2},
};

void *softmenu_HNDLS[3]=
{
  (void *)goto_menu,
  (void *)bookm_menu,
  (void *)search_menu
};

HEADER_DESC softmenu_HDR={0,0,0,0,icon,(int)"TED menu",LGP_NULL};

MENU_DESC softmenu_STRUCT=
{
  8,NULL,NULL,NULL,
  menusoftkeys,
  &menu_skt,
  0,
  NULL,
  softmenu_ITEMS,
  (MENUPROCS_DESC*)&softmenu_HNDLS,
  3
};

void DrawSoftMenu(void)
{
  static const char lfrm[]="%u";
  sprintf(t_bm1+4,lfrm,HISTORY.bookm1);
  sprintf(t_bm2+4,lfrm,HISTORY.bookm2);
  sprintf(t_bm3+4,lfrm,HISTORY.bookm3);
  sprintf(t_bm4+4,lfrm,HISTORY.bookm4);
  patch_header(&softmenu_HDR);
  CreateMenu(0,0,&softmenu_STRUCT,&softmenu_HDR,0,3,0,0);
}

//======================================================================

//Загрузка куска входного файла
unsigned int FL_loader(int fin, unsigned int p)
{
  unsigned int i;
  unsigned int ul;
  if (p==0xFFFFFFFF)
  {
    //Первая загрузка
    i=fread(fin,dstk,STKSZ,&ul);
    if (i<STKSZ)
    {
      //Загрузили меньше размера стека
      dstk[i]=0; //Маркер конца файла
    }
    p=0;
  }
  if (p>=STKSZ50) //Если указатель перешел за границу половины буфера
  {
    memcpy(dstk,dstk+STKSZ50,STKSZ50); //Копируем конец буфера в начало
    p-=STKSZ50; //Новый указатель
    i=fread(fin,dstk+STKSZ50,STKSZ50,&ul); //Следующие пол-буфера
    if (i<STKSZ50) dstk[i+STKSZ50]=0; //Меньше половины - маркер конца файла
  }
  return(p);
}

//Запись верхнего стека при начальной загрузке
unsigned int FL_saver(int fs, unsigned int p)
{
  unsigned int b;
  unsigned int ul;
  unsigned int seekpos;
  if (p>=STKSZ50)
  {
    b=FindFreeBlock();
    ubat[++u_disk]=b;
    seekpos=STKSZ50*b;
    if (lseek(fs,seekpos,0,&ul,&ul)!=seekpos) DiskErrorMsg(2);
    if (fwrite(fs,ustk,STKSZ50,&ul)!=STKSZ50) DiskErrorMsg(1);
    p-=STKSZ50;
    memcpy(ustk,ustk+STKSZ50,p);
    if (!terminated) REDRAW();
  }
  return(p);
}

//==================================================================
// Первая загрузка файла
// TODO:
//==================================================================
void FirstLoadFile(unsigned int fmt)
{
  int fin;
  int fs;
  int fnts;
  unsigned int ul;
  
  extern const int ENA_AUTOF;
  extern const int AUTOF_MODE;
  extern const int AUTOF_FONT;
  
  u_disk=-1; //Дисковый указатель верхнего стека
  d_disk=-1; //Дисковый указатель нижнего стека
  zeromem(ubat,sizeof(ubat)); //Прочищаем таблицу блоков верхнего стека
  zeromem(dbat,sizeof(dbat)); //Прочищаем таблицу блоков нижнего стека
  zeromem(bfree,sizeof(bfree)); //Прочищаем таблицу занятых блоков
  usp=0; //Указатель на верхний стек
  dsp=STKSZ; //Указатель на нижний стек
  viewpos=0;
  curpos=0;
  curline=0;
  text_changed=0;
  //CSM=0;
  
  draw_mode=255;
  
  if (fmt==0xFFFFFFFF)
  {
    //Ищем историю
    if (SearchHistory()&0x8000)
    {
      font_selected=HISTORY.font;
      rotate=HISTORY.rotate;
      fmt=HISTORY.fmt;
      win_dos_koi=HISTORY.codepage;
      cursor_off=HISTORY.cursor_off;
    }
    else
    {
      win_dos_koi=0xFF; //Неизвестный
      FontListItem *cur = FontList;
      for(font_selected = 0; cur && cur->size != AUTOF_FONT; font_selected++)
        cur=cur->next;

      if(!cur) font_selected = 0;
      //font_selected = cur->size;
    
      zeromem(&HISTORY.line,4*6); //Все на самом верху
      HISTORY.cursor_off=cursor_off=1; //Выключить курсор
      HISTORY.total=1;
      //      HISTORY.fmt=0;
      HISTORY.fmt=255; //Первый запуск!!!!
      HISTORY.rotate=0;
      if (ENA_AUTOF)
      {
        HISTORY.fmt=fmt=AUTOF_MODE;

      }
      else
      {  
        LockSched();
        loadmenu_id=DrawLoadMenu(); //Определяем, как грузить через меню
        UnlockSched();
        return;
      }
    }
  }
  if ((fmt&0x7F)>2) fmt=0;

  fnts = fonts_count;
  if(font_selected>fnts) font_selected = fnts-1;
  
  //Загружаем шрифт
//  GetFontList();
  LoadFont(0);
 
  //Конвертируем все строки в верхний стек
  fs=fopen(stkfile,A_Create+A_ReadWrite+A_BIN,P_READ+P_WRITE,&ul); //Файл верхнего стека
  if (fs==-1) DiskErrorMsg(3);
  if ((fin=fopen(filename,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    switch(fmt&0x7F)
    {
    case 1:
    case 2:
      usp=ConvertFormat(fin,fs,fmt&0x7F);
      break;
    case 0:
    default:
      if (win_dos_koi==0xFF) win_dos_koi=0;
      CharWidthForCodepage();
      usp=ConvertSimple(fin,fs);
      break;
    }
    fclose(fin,&ul);
  }
  fclose(fs,&ul);
  total_line=viewline=curline; //Находимся в последней строке
  HISTORY.font=font_selected;
  HISTORY.fmt=fmt;
  HISTORY.rotate=rotate;
  memcpy(HISTORY.name,filename,sizeof(HISTORY.name));
  //Расчитываем, куда перейти
  if (HISTORY.total==total_line)
  {
    seek_to_line=HISTORY.line; //Прямой переход
  }
  else
  {
    if (HISTORY.total)
      seek_to_line=(total_line*HISTORY.line)/HISTORY.total; //По отношению
    else
      seek_to_line=0;
    HISTORY.line=seek_to_line;
  }
  draw_mode=2; //Переходим на нужную строку
  GotoLine();
}

//=========================================================================
const void * const gui_methods[11]={
  (void *)maincsm_onRedraw,	//Redraw
  (void *)maincsm_onCreate,	//Create
  (void *)maincsm_onClose,	//Close
  (void *)maincsm_onFocus,	//Focus
  (void *)maincsm_onUnfocus,	//Unfocus
  (void *)maincsm_onKey,	//OnKey
  0,
  (void *)maincsm_onDestroy,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  
 // *font_file = 0;
  info_ws=AllocWS(512);
  upinfo_ws=AllocWS(256);
  e_ws=AllocWS(256);
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
}

void Killer2(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void Killer(void)
{
  static unsigned int ul;
/*  if (text_changed)
  {
    extern void savetext(void);
    LockSched();
    ShowMSG(1,(int)"File as .new saved!");
    UnlockSched();
    strcat(filename,".new");
    HISTORY.fmt=0; //Грузим его теперь как DirectLoad
    disk_access=SAVE_FILE;
    text_changed=0;    
    savetext();	
  }*/ //Это уже лишнее
  if (HISTORY.fmt!=255)
  {
    SaveHistory();
  }
  DeleteFonts(FontList);
  mfree(font);
  mfree(ustk);
  mfree(dstk);
  FreeWS(info_ws);
  FreeWS(upinfo_ws);
  FreeWS(e_ws);
  unlink(stkfile,&ul);
  //  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
  SUBPROC((void *)Killer2);
}

void maincsm_onclose(CSM_RAM *csm)
{
  //  GBS_StopTimer(&light_tmr);
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==loadmenu_id)
    {
      if(HISTORY.fmt == 255)
        load_direct();
    }
    if ((int)msg->data0==csm->gui_id)
    {
      csm->csm.state=-3;
    }
    if ((int)msg->data0==edit_id)
    {
      //Закрыт диалог редактирования, проверяем
      //Вышли из редактора стрелками вверх/вниз, выполняем	переход
      switch(editmode)
      {
      case VOL_UP_BUTTON:
	PageUp(max_y_emode);
	break;
      case UP_BUTTON:
	if(!rotate || editmode)
          LineUp();
        else
	  return(0);
	break;
      case LEFT_BUTTON:
        if(rotate && !editmode)
          LineUp();
        else
	  return(0);
        break;
      case VOL_DOWN_BUTTON:
	PageDw(max_y_emode);
	break;
      case DOWN_BUTTON:
	if(!rotate || editmode)
          LineDw();
        else
	  return(0);
	break;
      case RIGHT_BUTTON:
        if(rotate && !editmode)
          LineDw();
        else
	  return(0);
        break;
      case 0xFFF: //Просто меню
	break;
      default:
	editmode=0; //Выключаем редактор
	REDRAW();
	return(1);
      }
      CheckDiskAccess();
      if (disk_access)
      {
	DoDiskAccess(1); //Тут кривость, принято через SUBPROC
      }
      CreateEditDialog();
    }
  }
  if(Quit_Required)
  {
    csm->csm.state=-3;
  }
  return(1);
}

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

void UpdateCSMname(void)
{
  WSHDR *ws=AllocWS(256);
  str_2ws(ws,filename,126);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"TED: %w",ws);
  FreeWS(ws);
}

#pragma segment="CONFIG_C"

int LoadConfigData(const char *fname)
{
  int f;
  unsigned int ul;
  char *buf;
  int result=0;
  void *cfg;
  
  extern const CFG_HDR cfghdr0; //first var in CONFIG
  cfg=(void*)&cfghdr0;
  
  unsigned int len=(int)__segment_end("CONFIG_C")-(int)__segment_begin("CONFIG_C");
  
  if (!(buf=malloc(len))) return -1;
  if ((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
  {
    if (fread(f,buf,len,&ul)==len)
    {
      memcpy(cfg,buf,len);
      fclose(f,&ul);
    }
    else
    {
      fclose(f,&ul);
      goto L_SAVENEWCFG;
    }
  }
  else
  {
  L_SAVENEWCFG:
    if ((f=fopen(fname,A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&ul))!=-1)
    {
      if (fwrite(f,cfg,len,&ul)!=len) result=-1;
      fclose(f,&ul);
    }
    else
      result=-1;
  }
  mfree(buf);
  return(result);
}


int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  TDate d;
  TTime t;
  if (LoadConfigData("4:\\ZBin\\etc\\TED.bcfg")<0)
  {
    LoadConfigData("0:\\ZBin\\etc\\TED.bcfg");
  }
  GetDateTime(&d,&t);
  snprintf(stkfile,sizeof(stkfile),"%s%d_%d_%d_%d_%d_%d.tmp",ted_path,d.year,d.month,d.day,t.hour,t.min,t.sec);
  if (fname)
  {
    if (strlen(fname)<128)
    {
      strcpy(filename,fname);
    }
  }
  UpdateCSMname();
  fonts_count = GetFontList();
  if ((ustk=malloc(STKSZ)))
  {
    if ((dstk=malloc(STKSZ)))
    {
      LockSched();
      CreateCSM(&MAINCSM.maincsm,dummy,0);
      UnlockSched();
      return 0;      
    }
    mfree(ustk);
    LockSched();
    ShowMSG(1,(int)"Can't alloc DSTK!");
    UnlockSched();
    SUBPROC((void *)Killer2);
    return 0;
  }
  LockSched();
  ShowMSG(1,(int)"Can't alloc USTK!");
  UnlockSched();
  SUBPROC((void *)Killer2);
  return 0;
}
