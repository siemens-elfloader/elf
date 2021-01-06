#include "../plglib.h"

#define DT_NRDR	0
#define DT_MAIN	1
#define DT_MENU	2
#define DT_MOVE	3
#define DT_CHSZ	4


//extern void ShowWMSG(int flag, const char* msg, int font, const char* foncolor, const char* fringcolour, int ena);


#define IPC_NPLG	1

// menu point parameter
#define MNP_NORM 0
#define MNP_L_UP 1
#define MNP_L_DN 2
#define MNP_L	 3

#define MNP_NACT 10

char State, v=0, firstmsg=1, idle_ch=0;

extern const char BG_IMG[], CUR_IMG[], ICON_DT[], MC_PATH[];
extern const int KEY_CPU_HI, MN_SEL_MOD, CH_IDLE, CUR_JUMP;
extern const unsigned int CUR_BIG_STEP, CUR_TIMER, L_STEP_COUNT;
// const static char *icon_config=DEFAULT_DISK":\\ZBin\\EXPROJECT\\DeskTop\\icon.dt",
	// *fon_img=DEFAULT_DISK":\\ZBin\\EXPROJECT\\DeskTop\\fon.png",
	// *cur_img=DEFAULT_DISK":\\ZBin\\EXPROJECT\\DeskTop\\cur.png";

DT_ICON /* *AI, */ *TAI;
//DT_MENU_P *AMP;


int menup_run()
{
	Dt.act->onEnter();
	State=DT_MAIN;
	return 0;
}

int exit()
{
	return 1;
}

int openicondt()
{
	WSHDR *fws=AllocWS(256);
	extern const char *successed_config_filename;
	wsprintf(fws,perc_t,ICON_DT);
	ExecuteFile(fws,NULL,NULL);
	FreeWS(fws);
	State=DT_MAIN;
	return 0;
}

int openconf()
{
	WSHDR *fws=AllocWS(256);
	extern const char *successed_config_filename;
	wsprintf(fws,perc_t,successed_config_filename);
	ExecuteFile(fws,NULL,NULL);
	FreeWS(fws);
	State=DT_MAIN;
	return 0;
}

extern void ClearIcons(),initic(),dofn();

int refresh_dt()
{
	ClearIcons();
	extern DT_ICON dt_first;
	dofn();
	State=DT_MAIN;
	Dt.inf=0;
	Dt.first=Dt.last=Dt.act=&dt_first;
	SUBPROC((void*)initic);
	return 0;
}

/* typedef struct
{
	void *prev,*next;
	RECT p;
	char type, *nm, *inf;
	int (*onEnter)();
}DT_MENU_P; */
DT_MN_POINT mm_open={
		NULL,NULL,
		{0,0,0,0},
		MNP_NORM,
		"Open",
		menup_run
		},
	mm_exit={
		NULL,NULL,
		{0,0,0,0},
		MNP_NORM,
		"Exit",
		exit
		},
	mm_icon_dt={
		NULL,NULL,
		{0,0,0,0},
		MNP_NORM,
		"Icon Config",
		openicondt,
		},
	mm_bcfg={
		NULL,NULL,
		{0,0,0,0},
		MNP_NORM,
		"Config",
		openconf,
		},
	mm_refresh_dt={
		NULL,NULL,
		{0,0,0,0},
		MNP_NORM,
		"Refresh",
		refresh_dt,
		};

struct
{
	RECT p;
	DT_MN m;
	DT_MN_POINT *act;
	char foc;
}mm={{0,0,0,0},NULL,NULL,NULL,0};


typedef struct
{
  GUI gui;
}MAIN_GUI;

WSHDR *ws, *ews;
extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;
short scr_w, scr_h;
unsigned int MAINCSM_ID = 0,
		f_h; // высота шрифта
		
struct{
	signed char x,y, st, t;
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

#pragma inline
int infoc(RECT *p, short x, short y)
{
	if((x>=p->x)&&(x<=p->x2)&&(y>=p->y)&&(y<=p->y2)) return 1;
	else return 0;
}

void showinf()
{
	Dt.inf=1;
	if(Dt.foc) DirectRedrawGUI();
}

void movecur()
{
	Dt.inf=0;
	cur.x+=movcr.st*movcr.x;
	cur.y+=movcr.st*movcr.y;

	if(!CUR_JUMP)
	{
		if(cur.x>scr_w) cur.x=scr_w;
		if(cur.x<0) cur.x=0;
		if(cur.y>scr_h) cur.y=scr_h;
		if(cur.y<0) cur.y=0;
	}
	else
	{
		if(cur.x>scr_w) cur.x=0;
		if(cur.x<0) cur.x=scr_w;
		if(cur.y>scr_h) cur.y=0;
		if(cur.y<0) cur.y=scr_h;
	}

	DirectRedrawGUI();
	if((movcr.x!=0)||(movcr.y!=0))
	{
		if(IsTimerProc(&inftmr)) GBS_DelTimer(&inftmr);
		if(movcr.t<L_STEP_COUNT)
		{
		 movcr.t++;
		 GBS_StartTimerProc(&curtmr, CUR_TIMER, movecur);
		}
// 		else if(movcr.t<15)
// 		{
// 		 movcr.st=5;
// 		 movcr.t++;
// 		 GBS_StartTimerProc(&curtmr, 10, movecur);
// 		}
		else
		{
		 movcr.st=CUR_BIG_STEP;
		 GBS_StartTimerProc(&curtmr, CUR_TIMER, movecur);
		}
	}
	else
	{
		movcr.t=0;
		if(KEY_CPU_HI) SetCpuClockLow(2);
		if(IsTimerProc(&inftmr)) GBS_DelTimer(&inftmr);
		GBS_StartTimerProc(&inftmr, 108, showinf);
	}
	//movcr.st=10;
}

void srart_movecur()
{
	movcr.st=2;
	if(IsTimerProc(&curtmr)) GBS_DelTimer(&curtmr);
	if(KEY_CPU_HI) SetCpuClockTempHi(2);
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
	//DirectRedrawGUI();
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
	 case '#':SetCpuClockLow(2);
	   break;
	}
	//DirectRedrawGUI();
	break;
  }
}



/* RamAccPoint:


#pragma swi_number=0x80D0
__swi __arm char* RamAccPoint(void);

	int* pointer = (int*)RamAccPoint()+2;
	if (*pointer != 0)
{
		int* device = (int*)*pointer+3;
		int* id = (int*)*pointer+2;
		if (*id != 0)
{
			wsprintf(ws, "%t:%t", *device, *id);
			DrawString(ws,10,10,230,320,FONT_SMALL,1,white,black);
}
		else
{
			wsprintf(ws, "%t", *device);
			DrawString(ws,10,10,230,320,FONT_SMALL,1,white,black);
}
} */


