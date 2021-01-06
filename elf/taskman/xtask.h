//attrib listbox   1-func. 2-scrollbar 4-with pict 
//attrib item   0x100 - sub  0x200 - underline  0x400 - color  0x800 - disabled
//attib item 0x00XX0000 - color

typedef struct
{
  void *next;
  WSHDR *name;
  void *p;
} NAMELIST;

typedef struct {
  int (*KeyPressProc)(int action, int key);
  void *next;
}tkeymessages;

typedef struct {
  void (*RedrawProc)();
  void *next;
}tredrawmessages;

typedef struct {
  int x;
  int y;
  int width;
  int heigh;
  int hline;
  int cline;
  int hfont, font;
  int tpos;
  int bc, fc, sbc, sfc, stbc, stfc, ssize, pos, cursor, fatr;
  //void (*CreateProc)();
  //void (*DestroyProc)();
  //int (*KeyPressProc)(int action, int key);
  //void (*RedrawProc)();
  NAMELIST *start;
  NAMELIST *finish;
  NAMELIST *selected;
} tlistbox;

typedef struct {
  int x;
  int y;
  int width;
  int heigh;
  int hline;
  int bc, fc, tfc, cbc;
  int font, fatr, cfont, cfatr;
  char *text;
  char *caption;
  //void (*CreateProc)();
  //void (*DestroyProc)();
  //int (*KeyPressProc)(int action, int key);
  //void (*RedrawProc)();
} tmsgbox;

typedef struct {
  void *next;
  int selected;
  NAMELIST *start;
}tmenuitem;


typedef struct {
  void *next;
  IMGHDR image;
}timage;

typedef struct {
  tmenuitem *start;
  int selected;
  timage *pic;
  timage *selpic;  
}tmainmenu;

typedef struct {
  void *next;
  int selected;
  tlistbox *llist;
  int (*KeyPressProc)(int action, int key);
  void (*RedrawProc)();
}tsubms;


