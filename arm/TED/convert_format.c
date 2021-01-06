#include "..\inc\swilib.h"

/*void my_memset(void *dst, int v, unsigned int len)
{
  char *d=(char *)dst;
  if (len)
  {
    do
    {
      *d++=v;
    }
    while(--len);
  }
}*/
#define my_memset memset

extern unsigned long curline; //Наружная переменная, счетчик строк
extern unsigned int max_x; //Наружная переменная - макс. размер строки

extern char *dstk;
extern char *ustk;

extern unsigned int FL_loader(int fin, unsigned int p);
extern unsigned int FL_saver(int fs, unsigned int p);

extern int win_dos_koi;
extern const char wintranslation[];
extern const char koi8translation[];

extern void CharWidthForCodepage();

extern char chars_width[];

static const char ctype[128]=
{
  2,1,1,1,1,2,1,1, 2,3,1,1,1,1,2,1,
  1,1,1,2,1,1,1,1, 1,1,3,2,3,2,2,2,
  2,1,1,1,1,2,1,1, 2,3,1,1,1,1,2,1,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
  1,1,1,2,1,1,1,1, 1,1,3,2,3,2,2,2,
  2,2,2,2,2,2,2,2, 0,0,0,0,0,0,0,0,
};

int GetCharType_x(int c)
{
  if (c==' ') return(4); //Пробел
  if (c<32) return(5); //Конец строки
  if ((c=='i')||(c=='I')) return 2; //Гласная для украинского ;)
  if (c<128) return(0); //Не русская буква
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
  if (c<128) return(0); //Не русская буква
  return(ctype[c-128]);
}

unsigned int def_code (void);

//Процедура форматирования текста
unsigned int ConvertFormat(int fin,int fs,int fmt)
{
  unsigned int c0;
  unsigned int c1=1; //Начать с пропуска символов
  unsigned int c2=1;
  unsigned int c3=32; //Начать с абзаца, раз у нас форматирование ;)

  //unsigned int last_space;

  unsigned int sl;

  register unsigned int s;
  register unsigned int d;
  char ct[256]; //Массив для описания типа символов

  char *ds=dstk;
  register char *us=ustk;

  extern unsigned int STKSZ50;

  int maxstk=STKSZ50;
  
  d=0;
  us[d]=0;
  sl=0;
  //last_space=0xFFFF;
  s=FL_loader(fin,0xFFFFFFFF);

  if (win_dos_koi==0xFF) win_dos_koi=def_code ();
  CharWidthForCodepage();

  //Подготавливаем массив ct
  c0=0;
  do
  {
    ct[c0]=GetCharType_x(c0);
  }
  while((++c0)!=sizeof(ct));

#define GetCharType(VAR) (ct[VAR])

  for(;;)
  {
    c0=c1;
    c1=c2;
    c2=c3;
  LSKIP1:
    c3=ds[s++];
    if (s>=maxstk) s=FL_loader(fin,s);
    if (c3==9) c3=' '; //Замена табуляции на пробел
    if (c3==1) c3=' '; //Замена служ. символов
    if ((c3==' ')&&(c2==' ')) goto LSKIP1; //Пропуск пробелов
    if ((c3==13)&&(ds[s]==10)) s++; //0D0A->0D
    if ((c3==10)&&(ds[s]==13)) s++; //0A0D->0A
    if (c3==10) c3=13; //0A->0D
    if (c0==0) goto LEOF; //Конец текста
    if (fmt==1)
    {
      if ((c0>' ')&&(c1=='-')&&(c2==13)&&(c3>' '))
      {
	//Удаление переноса
	c1=1;
	c2=1;
	goto LSYM;
      }
      if ((c0>' ')&&(c1==13)&&(c2>' '))
      {
	//Замена перевода строки на пробел между словами
	c1=' ';
	goto LSYM;
      }
    }
    if (c0==13)
    {
      //Во всех других случаях перенос строки - это абзац
      //last_space=0xFFFF;
      sl=0;
      d=FL_saver(fs,d); //Сливаем не слитое
      us[d++]=0; //Конец строки
      curline++;
      if ((c1>' ')&&(fmt==2))
      {
	us[d++]=' '; //Если сл. символ - буква, добавляем отступ
	sl+=chars_width[' ']; //добавим ширину символа
      }
      continue;
    }
  LSYM:
    if (c0!=1)
    {
      us[d]=c0;
      //if ((c0==' ')&&sl) last_space=d; //Запоминаем последний пробел
      d++;
      sl+=chars_width[c0]; //добавим ширину символа
//      sl++;
      if (sl>max_x)
      {
	//Слишком длинная строка, ищем, куда вставить перенос
	unsigned int pp=d+2; //Начинаем с конца c учетом доп. символов
	unsigned int pg1=0xFFFFFFFF;
	unsigned int pg2=0xFFFFFFFF;
	int c;
	us[d]=c1;
	us[d+1]=c2;
	us[d+2]=c3;
	for(;;)
	{
	  c=GetCharType(us[pp]);
	  if ((c==5)&&(pp<d))
	  {
	    //Нет подходящих пробелов, режем по живому ;)
	  L_CUT:
	    d--;
	    d=FL_saver(fs,d);
	    us[d++]=0;
	    us[d++]=c0;
	    sl=chars_width[c0]; //ширина символа в накопитель
	    break;
	  }
	  if ((c==4)&&(pp<d))
	  {
            unsigned int wc;
	    //Режем по пробелу
	    if (us[pp-1]<2) goto L_CUT; //Первый пробел не обрезаем
	    us[pp]=0; //Обрезаем по пробелу и признак форматирования
            sl = 0;
            for(wc = pp+1; wc < d; wc++)
              sl+=chars_width[us[wc]];
                
	    //sl=(d-pp)-1;
	    d=FL_saver(fs,d); //Сливаем не слитое
	    //last_space=0xFFFF;
	    break;
	  }
	  if ((c<1)||(c>3))
	  {
	    pg1=0xFFFFFFFF; //Новое слово
	    pg2=0xFFFFFFFF;
	  }
	  if (c==2)
	  {
	    pg2=pg1;
	    pg1=pp;
	    if (pg2!=0xFFFFFFFF)
	    {
	      //Нашли 2 гласных
	      unsigned int pm=(pg2+pg1+1)>>1;
	      if (GetCharType(us[pm])==3) pm++; //Если нельзя отрывать букву
	      c=GetCharType(us[pm-2]);
	      if ((pm<(d-1))&&(c>0)&&(c<4))
	      {
                unsigned int wc;
		if (pm==pg2)
		{
		  //Если гласная непостредственно справа, проверяем не одна ли она
		  c=GetCharType(us[pg2+1]);
		  if ((c<1)||(c>3)) goto L_NOPERE;
		}
		{
		  //memmove(us+(pm+2),us+pm,d-pm);
		  unsigned int len=d-pm;
		  if (len)
		  {
		    char *d=us+(pm+2)+len-1;
		    char *s=us+pm+len-1;
		    do
		    {
		      *d=*s;
		      d--;
		      s--;
		    }
		    while(--len);
		  }
		}
		us[pm++]='-';
		us[pm++]=0;
		d+=2; //Т.к. вставили 2 символа

                sl = 0;
                for(wc = pm; wc < d; wc++)
                  sl+=chars_width[us[wc]];
            
  //              sl=(d-pm);
		d=FL_saver(fs,d); //Сливаем не слитое
		break;
	      L_NOPERE:
		;
	      }
	    }
	  }
	  pp--;
	}
	curline++;
      }
    }
  }
LEOF:
  if (sl) //Не записана последняя строка
  {
    us[d++]=0;
    curline++;
  }
  d=FL_saver(fs,d); //Сливаем не слитое
  return(d);
}

//-------------------------------------------------------------
// Автоматическое определение кодировки (по первой загрузке)
//-------------------------------------------------------------
/* Таблица сочетаний */

static const unsigned char table_2s[128]={0xFF,0xFF,0xFF,0xC7,0xFE,0xBE,0xF7,0xFB,
0xFD,0xBF,0xF7,0xF9,0xFC,0xBE,0xF1,0x80,0xFF,0xFF,0xF7,0xBB,0xFF,0xFF,0xFF,
0xCF,0xDE,0xBF,0xD1,0x08,0xFF,0xBF,0xF1,0xBF,0xFF,0xFF,0xFF,0xC7,0x1D,0x3F,
0x7F,0x81,0xA7,0xB6,0xF2,0x82,0xFF,0xFF,0x75,0xDB,0xFC,0xBF,0xD7,0x9D,0xFF,
0xAE,0xFB,0xDF,0xFF,0xFF,0xFF,0xC7,0x84,0xB7,0xF3,0x9F,0xFF,0xFF,0xFF,0xDB,
0xFF,0xBF,0xFF,0xFF,0xFD,0xBF,0xFF,0xFF,0xFF,0xFF,0xE7,0xC7,0x84,0x9E,0xF0,
0x12,0xBC,0xBF,0xF0,0x84,0xA4,0xBA,0x10,0x10,0xA4,0xBE,0xB8,0x88,0xAC,0xBF,
0xF7,0x0A,0x84,0x86,0x90,0x08,0x04,0x00,0x00,0x03,0x7F,0xFD,0xF7,0xC1,0x7D,
0xAE,0x6F,0xCB,0x15,0x3D,0xFC,0x00,0x7F,0x7D,0xE7,0xC2,0x7F,0xFD,0xF7,0xC3};

/* =========================================================================
Вспомогательная функция alt2num.
Вход: a - код русской буквы в кодировке ALT.
Выход: порядковый номер этой буквы (0-31).
========================================================================= */
unsigned int alt2num (int a)
{
  if (a>=0xE0) a-=0x30;
  return (a&31);
}
/* =========================================================================
Вспомогательная функция koi2num.
Вход: a - код русской буквы в кодировке KOI.
Выход: порядковый номер этой буквы (0-31).
========================================================================= */
unsigned int koi2num (int a)
{
  static const unsigned char t[32]={30,0,1,22,4,5,20,3,21,8,9,10,11,12,13,14,15,31,
  16,17,18,19,6,2,28,27,7,24,29,25,23,26};
  return (t[a&31]);
}

/* =========================================================================
Вспомогательная функция work_2s - обработка двухбуквенного сочетания.
Вход:  с1 - порядковый номер первой буквы (0-31),
c2 - порядковый номер второй буквы (0-31),
check - надо ли проверять, встречалось ли сочетание раньше
(1 - да, 0 - нет),
buf - адрес массива с информацией о встреченных сочетаниях.
Выход: 0 - указанное сочетание уже встречалось раньше,
1 - сочетание не встречалось раньше и является допустимым,
2 - сочетание не встречалось раньше и является недопустимым.
========================================================================= */

unsigned int work_2s (unsigned int c1, unsigned int c2, unsigned int check, unsigned char buf[128])
{
  unsigned int i=(c1<<2)+(c2>>3); /* Номер байта в массиве. */
  unsigned int mask=0x80>>(c2&7); /* Маска, соответствующая номеру бита в байте. */

  /* Если check=1, проверяем: если соответствующий бит массива buf равен 0,
  значит, указанное сочетание уже встречалось раньше. Тогда выходим из
  функции, возвращая 0. Если же сочетание не встречалось, то помечаем, что
  оно встретилось (обнуляем соответствующий бит массива buf). */

  if (check==1)
  {
    if ((buf[i]&mask)==0) return (0);
    buf[i]&=~mask;
  }

  /* Проверяем, допустимо сочетание или нет. */

  if ((table_2s[i]&mask)!=0) return (1); /* Допустимо. */
  return (2);                            /* Недопустимо. */
}

/* =========================================================================
Вспомогательная функция def_code - определение кодировки текста. Функции
m_def_code и f_def_code - лишь надстройки над этой функцией.
Вход:  get_char - указатель на функцию, которую надо вызывать для получения
очередного символа текста. Функция должна возвращать либо
код символа, либо, при достижении конца текста, -1.
n - количество различных сочетаний русских букв (1-255), которого
достаточно для определения кодировки.
Выход: 0 - текст в кодировке ALT, 1 - WIN, 2 - KOI.
========================================================================= */

unsigned int def_code (void)
{
  /* В массиве buf_1 хранится информация о том, какие сочетания руских букв
  уже встречались в варианте ALT, а в массиве buf_2 - в варианте WIN. */

  unsigned char buf_1 [128];
  unsigned char buf_2 [128];


  unsigned int s=0;

  unsigned int bad_1=0;
  unsigned int bad_2=0;
  unsigned int bad_3=0;
  unsigned int all_1=0;
  unsigned int all_3=0;  /* all_2=all_3 */

  unsigned int c1;
  unsigned int c2=0; /* Символы текущего обрабатываемого сочетания. */

  /* Инициализация buf_1 и buf_2. */

  my_memset(buf_1,0xFF,sizeof(buf_1));
  my_memset(buf_2,0xFF,sizeof(buf_2));

  /* Главный цикл - обработка сочетаний для каждого из трёх вариантов. Цикл
  выполняется, пока не кончится текст или в каком-либо из вариантов не
  встретится n сочетаний. */

  while ((s<16384)&&(all_1<255)&&(all_3<255))
  {
    c1=c2;
    if ((c2=dstk[s])==0) break;
    s++;
    /* Вариант ALT. Вначале проверяем, являются ли символы текущего сочетания
    кодами русских букв в кодировке ALT. */

    if ((((c1>=0x80)&&(c1<0xB0))||((c1>=0xE0)&&(c1<0xF0)))&&
	(((c2>=0x80)&&(c2<0xB0))||((c2>=0xE0)&&(c2<0xF0))))
    {
      switch (work_2s(alt2num(c1),alt2num(c2),1,buf_1)) /* Обработали. */
      {
      case 2: bad_1++;
      case 1: all_1++;
      }
    }
    /* Варианты WIN и KOI. Вначале проверяем, являются ли символы текущего
    сочетания кодами русских букв в этих кодировках (в обеих кодировках
    диапазоны кодов русских букв совпадают). */

    if ((c1&c2)>=0xC0) /* Эквивалентно условию (c1>=0xC0)&&(c2>=0xC0). */
    {
      switch (work_2s(c1&31,c2&31,1,buf_2)) /* Обработали. */
      {
      case 0: continue; /* Если сочетание букв уже встречалось в варианте WIN,
      то оно уже встречалось и в варианте KOI, так что
      пропускаем обработку варианта KOI и переходим
      к следующей итерации главного цикла. */
      case 2: bad_2++;
      }

      /* Если сочетание букв ещё не встречалось в варианте WIN, то оно заведомо
      не встречалось и в варианте KOI, поэтому специально проверять это не
      надо - значит, функцию work_2s вызываем с параметром check, равным 0. */

      switch (work_2s(koi2num(c1),koi2num(c2),0,NULL)) /* Обработали. */
      {
      case 2: bad_3++;
      case 1: all_3++;
      }
    }
  }

  /* Данные собраны. Теперь, если в каком-либо из вариантов недопустимых
  сочетаний не больше 1/32 от общего их числа, то считаем, что их и не
  было. */

  if (bad_1<=(all_1>>5)) bad_1=0;
  if (bad_2<=(all_3>>5)) bad_2=0;
  if (bad_3<=(all_3>>5)) bad_3=0;

  /* Получаем результат. */

  {
    unsigned int a=((255-bad_1)<<8)+all_1;
    unsigned int b=((255-bad_2)<<8)+all_3;
    unsigned int c=((255-bad_3)<<8)+all_3;

    if ((a>=b)&&(a>=c)) return (0);
    if (b>=c) return (1); else return (2);
  }
}
