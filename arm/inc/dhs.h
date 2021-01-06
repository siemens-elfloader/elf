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
  int    w;       // ������ ������
  int    h;       // ������ ������
  RECT   unk_rc;  // 
  RECT   rc;      // ���������� ������� ���������
  short *buf;     // ����� ������ ������
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

//������� ������� �������
typedef struct {
  void (*dh_proc)(LCDLAYER *); //�-�� ���������
  void  *prev; // ����� ����������� �������� (���� ������� ������, �� ����� DHS_FIRST_ITEM) 
  void  *next; // ����� ���������� �������� (���� ������� ���������, �� ����� DHS_LAST_ITEM) 
}DHS_ITEM;

//������� ������� �������
typedef struct {
  DHS_ITEM *first;  // ����� ������� �������� (���� ���, �� DHS_FIRST_ITEM)
  int       count;  // ���������� ��������� (�-��), ��������������� � �������
  int       unlock; // ���� ������ �������� ����� DHS_UNLOCKDVALUE, �� ��������� �� ��o���������
  DHS_ITEM *last;   // ����� ���������� �������� (���� ���, �� DHS_LAST_ITEM)
}DHS_TOP;
