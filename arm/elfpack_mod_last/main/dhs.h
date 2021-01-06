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

__arm   void DHS_init();
__arm   void DHS_kill();
__thumb void DHS_drawItems(LCDLAYER *layer);
__arm   int  DHS_addProc_ep(void (*dh_proc)(LCDLAYER *));
__arm   int  DHS_removeProc_ep(void (*dh_proc)(LCDLAYER *));
__thumb void DHS_lockDraw_ep(int lock);
__thumb DHS_TOP *DHS_getBaseAddr_ep();
__thumb int  DHS_getStatusItem_ep(void (*dh_proc)(LCDLAYER *));
__arm   int  DHS_workProcPrio_ep(void (*dh_proc)(LCDLAYER *), int work);
