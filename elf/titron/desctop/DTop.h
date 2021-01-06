#include "../plglib.h"

#pragma swi_number=0x221
__swi __arm void SetCpuClockLow(int const_2);
#pragma swi_number=0x222
__swi __arm void SetCpuClockTempHi(int const_2);
#pragma swi_number=0x5E
__swi __arm int GetMMIMemUsed(void);


#define DT_NRDR	0
#define DT_MAIN	1
#define DT_MENU	2
#define DT_MOVE	3
#define DT_CHSZ	4


//extern void ShowWMSG(int flag, const char* msg, int font, const char* foncolor, const char* fringcolour, int ena);


#define IPC_DT_NAME "_DeskTop"

#define IPC_NPLG	1

#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#else
#define DEFAULT_DISK "0"
#endif

// menu point parameter
#define MNP_NORM 0
#define MNP_L_UP 1
#define MNP_L_DN 2
#define MNP_L	 3

#define MNP_NACT 10

const static char *icon_config=DEFAULT_DISK":\\ZBin\\EXPROJECT\\DeskTop\\icon.dt",
	*fon_img=DEFAULT_DISK":\\ZBin\\EXPROJECT\\DeskTop\\fon.png",
	*cur_img=DEFAULT_DISK":\\ZBin\\EXPROJECT\\DeskTop\\cur.png";

DT_ICON *AI, *TAI;
DT_MENU_P *AMP;

int menup_run()
{
	AI->onEnter();
	return 0;
}

int exit()
{
	return 1;
}

/* typedef struct
{
	void *next;
	RECT p;
	char type, *nm, *inf;
	void (*onEnter)();
} */
DT_MENU_P mm1={
		NULL,
		{0,0,0,0},
		MNP_NORM,
		"Open",
		"",
		menup_run
		},
	mm2={
		NULL,
		{0,0,0,0},
		MNP_NORM+MNP_NACT,
		"Exit",
		"",
		exit
		};

struct
{
	RECT p;
	DT_MENU_P *first;
	char foc;
}mm={{0,0,0,0},NULL,0};
/* DT_MN;

DT_MN  */


typedef struct
{
  GUI gui;
}MAIN_GUI;

struct{
	unsigned short icon_cnt, n;
	DT_ICON *icon;
	char inf, foc;
}Dt;

WSHDR *ws, *ews;
extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;
short scr_w, scr_h;
unsigned int MAINCSM_ID = 0,
		f_h; // высота шрифта
		
struct{
	signed char x,y, st;
}movcr={0,0,10};

RECT cur={0,0,0,0};

GBSTMR curtmr,
	inftmr;

IMGHDR *mfn, *cursor;

void bar(), m_redr();

 // ничего не делающие функции :)
static int int_0(void){return(0);}
static void void_0(){}

/* char _09[]=
{
	0x78, 0x84, 0x84, 0x84, 0x84, 0x7c, 0x04, 0x08, 0x70
}; */

int infoc(RECT *p, short x, short y)
{
	if((x>=p->x)&&(x<=p->x2)&&(y>=p->y)&&(y<=p->y2)) return 1;
	else return 0;
}

void showinf()
{
	Dt.inf=1;
	DirectRedrawGUI();
}

void movecur()
{
	Dt.inf=0;
	cur.x+=movcr.st*movcr.x;
	cur.y+=movcr.st*movcr.y;
	if(cur.x>=scr_w) cur.x=scr_w;
	if(cur.x<=0) cur.x=0;
	if(cur.y>=scr_h) cur.y=scr_h;
	if(cur.y<=0) cur.y=0;
	DirectRedrawGUI();
	if((movcr.x!=0)||(movcr.y!=0))
	{
		if(IsTimerProc(&inftmr)) GBS_DelTimer(&inftmr);
		if(movcr.st<10) GBS_StartTimerProc(&curtmr, 50, movecur);
		else GBS_StartTimerProc(&curtmr, 10, movecur);
	}
	else
	{
		SetCpuClockLow(2);
		if(IsTimerProc(&inftmr)) GBS_DelTimer(&inftmr);
		GBS_StartTimerProc(&inftmr, 108, showinf);
	}
	movcr.st=10;
}

void srart_movecur()
{
	movcr.st=3;
	if(IsTimerProc(&curtmr)) GBS_DelTimer(&curtmr);
	SetCpuClockTempHi(2);
	movecur();
}

/* void stop_movecur()
{
	Dt.inf=0;
	if((movcr.x==0)&&(movcr.y==0))
} */

void curkey(GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
  switch(m)
  {
   case KEY_DOWN:
	switch(msg->gbsmsg->submess)
	{
	 case UP_BUTTON:
	 case '2':
		movcr.y=-1;
		srart_movecur();
	   break;
	 case DOWN_BUTTON:
	 case '8':
		movcr.y=1;
		srart_movecur();
	   break;
	 case RIGHT_BUTTON:
	 case '6':
		movcr.x=1;
		srart_movecur();
	   break;
	 case LEFT_BUTTON:
	 case '4':
		movcr.x=-1;
		srart_movecur();
	   break;
	 case '1':
		movcr.x=-1;
		movcr.y=-1;
		srart_movecur();
	   break;
	 case '3':
		movcr.x=1;
		movcr.y=-1;
		srart_movecur();
	   break;
	 case '7':
		movcr.x=-1;
		movcr.y=1;
		srart_movecur();
	   break;
	 case '9':
		movcr.x=1;
		movcr.y=1;
		srart_movecur();
	   break;
	}
	DirectRedrawGUI();
	break;
   case KEY_UP:
	switch(msg->gbsmsg->submess)
	{
	 case UP_BUTTON:
	 case DOWN_BUTTON:
	 case '2':
	 case '8':
		movcr.y=0;
	   break;
	 case RIGHT_BUTTON:
	 case LEFT_BUTTON:
	 case '4':
	 case '6':
		movcr.x=0;
	   break;
	 case '1':
	 case '3':
	 case '7':
	 case '9':
		movcr.x=0;
		movcr.y=0;
	   break;
	}
	DirectRedrawGUI();
	break;
  }
}
