//D.H.S. 

#define DHS_FIRST_ITEM  (DHS_ITEM *)0xBAD0
#define DHS_LAST_ITEM   (DHS_ITEM *)0xBAD1
#define DHS_NULLITEM    (DHS_ITEM *)-1
#define DHS_ZERO         0
#define DHS_NULL        -1

#define DHS_LOCKDRAW     1
#define DHS_UNLOCKDRAW   0

#define DHS_ITEM_TOP       1
#define DHS_ITEM_BOTTOM   -1
#define DHS_ITEM_MIDDLE    0

#define DHS_PRIOPROC_ADD      1
#define DHS_PRIOPROC_REMOVE   0
#define DHS_PRIOPROC_GETSTAT -1

#define DHS_UNLOCKDVALUE 0xDB6DB6DB


typedef struct{
  int    w;       // Ширина экрана
  int    h;       // Высота экрана
  RECT   unk_rc;  // 
  RECT   rc;      // Глобальные границы отрисовки
  short *buf;     // Адрес буфера экрана
  int    unk_0x20;
  int    unk_0x24;
  char   unk_0x28;
  char   unk_0x29;
  char   unk_0x2A;
  char   unk_0x2B;
  int    unk_0x2C;
  int    unk_0x30;
  int    unk_0x34; // 0, 1 --
  int    unk_0x38; // 0, 1 --
  int    unk_0x3C; // 0, 1 --
  
  
}LCDLAYER;

// 0xA0

//Рядовой элемент системы
typedef struct {
  void (*dh_proc)(LCDLAYER *); //Ф-ия отрисовки
  void  *prev; // Адрес предыдущего элемента (Если элемент первый, то равен DHS_FIRST_ITEM) 
  void  *next; // Адрес следующего элемента (Если элемент последний, то равен DHS_LAST_ITEM) 
}DHS_ITEM;

//Базовый элемент системы
typedef struct {
  DHS_ITEM *first;  // Адрес первого элемента (Если нет, то DHS_FIRST_ITEM)
  int       count;  // Количество элементов (ф-ий), задействованных в системе
  int       unlock; // Если данное значение равно DHS_UNLOCKDVALUE, то отрисовка не прoизводится
  DHS_ITEM *last;   // Адрес последнего элемента (Если нет, то DHS_LAST_ITEM)
}DHS_TOP;
