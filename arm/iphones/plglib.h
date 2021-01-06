

#define IPC_DT_NAME "_DeskTop"

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

#define DTI_PLAGIN	'P'
#define DTI_SHORT	'S'
#define DTI_ENTRY	'E'
#define DTI_FILE	'F'
#define DTI_MC		'm'

#define DTI_CLOCK	'C'
#define DTI_BAT		'B'
#define DTI_NET		'N'
#define DTI_MENU	'M'

typedef void (*func)();

// typedef struct
// {
//   int mode; //0-normal mode, 1-select mode 
//   int dir_enum; //0x26 by default
//   WSHDR* path_to_file; //path to file
//   WSHDR* file_name; //put cursor to this file
//   int unk5;
//   int is_exact_dir;
//   int unk7_11[5];
//   WSHDR* full_filename;
//   int unk13;
//   int (*user_handler)(void*); //called in select mode
//   void* this_struct_addr;
//   int unk16_26[11]; 
// }NativeExplorerData;

typedef struct{
	char shortcut[0x10];
	int entry;
}SHORTCUTREC;

#pragma swi_number=0x221
__swi __arm void SetCpuClockLow(int const_2);
#pragma swi_number=0x222
__swi __arm void SetCpuClockTempHi(int const_2);
// #pragma swi_number=0x5E
// __swi __arm int GetMMIMemUsed(void);
/*#pragma swi_number=0x254
__swi __arm int StartNativeExplorer(NativeExplorerData* data);*/
#pragma swi_number=116
__swi __arm SHORTCUTREC *GetShortcutRecordByName(char *szShortcutName);

typedef struct{
	void (*D)();
	int (*K)(GUI_MSG *msg);
}DtSt;

typedef struct
{
	void *prev,*next;
	RECT p;
	char type, *nm;
	int (*onEnter)();
}DT_MN_POINT;

typedef struct
{
	RECT p;
	DT_MN_POINT *first, *last, *act;
	void *sub;
}DT_MN;




// PGUI states:
#define PG_st_unfoc 0
#define PG_st_norm 1
#define PG_st_min 2
#define PG_st_max 3
#define PG_st_maxunfoc 4

// typedef struct{
// 	PGUI_methods *first;
// }PGUIS




typedef struct{
	void *prev,*next, // previous, next icons
 *up,*down,*left,*right; // nothing
	RECT p, // position
  pp; // хз, не помню
	IMGHDR *img; // image
	char alfa, // transparency
  n, // number
  type, //type
  d, // 1-mfree when clear
  *nm, // name
  *inf, // popup info text
  *img_fl, // image file
  *fl, // file, shortcut or entrypoint
  dyn, // 0-static icon, 1-dinamic icon
  sel; // nothing
	void (*onDraw)(); // draw function
	int (*onEnter)(); // action on enter button
	void (*onInf)(); // create info text
	void (*onClose)(); // action on close (for plagins)
	void (*Refresh)(); // refresh (for plagins)
	void (*onMessage)(GBS_MSG* msg); // action on close (for plagins)
	//PGUI_methods *pg; // methods for subgui
}DT_ICON; // Структура иконки





typedef struct{
  void *prev,*next;
  int n;
  RECT r;
  char *inf;
  int (*Enter)();
}PG_BUTTON; // Кнопка в окне

typedef struct{
  PG_BUTTON *first, *last, *act;
  int cnt;
}PG_BTN; // Кнопки окна


typedef struct{
	char *name; // name
	char st, // PGUI state 
 type, // PGUI type (0-without cursor, 1-with cursor, +2-with window, +4-disactive desctop)
 n; // focused subicon number// хз, чо я этим сказать хотел :) лучше не трогать
 RECT p; // position
 void (*OnRedraw)(),
	(*OnCreate)(),
	(*OnClose)(),
	(*OnFocus)(),
	(*OnUnfocus)();
 int (*OnKey)(GUI_MSG *msg);
 DT_ICON *ic; // надо :) (dont touch this)
 IMGHDR *w;
 PG_BTN btn;
// 	void *next;
}PGUI_methods;


typedef struct{
	void (*dr_m)( char fnd, char inf );
	void (*curkey)(GUI_MSG *msg);
	void (*stdmove)(GUI_MSG *msg);
}M_FUNCS;

typedef struct{
	void (*add_icon)(DT_ICON *TI);
	void (*del_icon)(DT_ICON *TI);
	IMGHDR* (*resz_img)(IMGHDR *img, int px, int py, int fast, int del);
	int (*ICON_REDRAW)(void *dt, DT_ICON *ic);
	int (*GetBitmapMapPos)(IMGHDR *img, int x, int y);
	int (*DrwImg2Img)(IMGHDR *img, RECT p, IMGHDR *buf, char alfa/* , IMGHDR *fn */);
	int (*FillRectByNum)(IMGHDR *buf, RECT p, char n);
	void (*fill_icons)(int t);
	IMGHDR* (*create_imghdr)(const char *fname, int type);
	IMGHDR* (*img_24_16)(IMGHDR *img, int del);
}EXT_FUNCS;

typedef struct{
	void (*Cr_PGUI)(PGUI_methods *p);
	void (*Close_PGUI)();
	void (*reset_WIND)(PGUI_methods *p, char t);
	void (*add_btn)(PGUI_methods *p, PG_BUTTON *btn, RECT *r);
// 	void (*crpgwind)(PGUI_methods *p);
	void (*OnClose)();
}PGUI_FUNCS;

typedef struct{
  DtSt *st_MAIN,
  *st_MENU,
  *st_MOVE,
  *st_RESZ,
  *st_CHTR,
  *st_WAIT,
  
  
  *st_LPLG,
  *st_ERR;
}DtStates; // 

typedef struct{
	int MAINCSM_ID, // ID цсм (если есть)
		MAINGUI_ID; // ID гуя
	int w, h; // ширина, высота
	DT_ICON *first, *last, *act; // firsr, last & active icons
	char inf, // 1-draw popup info
		foc, // 1-any icon is on focus
		cnt, // icons count
		n, // focused icon number
		nn, // temp
		*rootadr; // adres of root folder
	IMGHDR i, // draw buffer
		ni, // icon numbers map
		*fon, // background image
		*cursor; // cursor image
	DtStates *states; //  Draw & Keys struct
	DtSt *st; //  active state
	PGUI_methods *actpg; // Активное окно
	RECT cur, // cursor position
 		mi, mic; // temp
	M_FUNCS *mf; // Основные функции (в самом ельфе)
	EXT_FUNCS *ef; // Доп. функции (будут отдельным эльфом)
	PGUI_FUNCS *pf; // Функции "окон"
}DT; // Основная структура

typedef struct{
	DT *dt;
	DT_ICON *ic;
}PLG_P; // Надо :)



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
