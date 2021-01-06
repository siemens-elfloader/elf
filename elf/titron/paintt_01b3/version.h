#define TMR_SEC 216

#pragma swi_number=0x222
__swi __arm void SetCpuClockTempHi(int const_2);

static IPC_REQ gipc;

#define IPC_PAINTT_NAME "Paintt_"
#define IPC_CHECK_DOUBLERUN	1
#define IPC_SAVE_FINISHED	2
#define IPC_SAVE_PART		3

const char ipc_my_name[32]=IPC_PAINTT_NAME;
const char ipc_xtask_name[]=IPC_XTASK_NAME;
IPC_REQ gipc;

void DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

int met0(void){return(0);}
int	mm_key(GUI_MSG *msg, int lev);
void DrPic(), mm_dr(RECT cv, int lev);

typedef struct
{
  GUI gui;
}VIEW_GUI;

typedef struct
{
  GUI gui;
  int x,y;
}PREVIEW_GUI;

typedef struct
{
	GUI gui;
	char lev;
}MENU_GUI;

typedef struct
{
	char cnt, pos, bt1[16], bt2[16];
	int (*key)(GUI_MSG *msg, int lev);
	void (*dr)(RECT cv, int lev);
}MENU_PARAM;

static const MENU_PARAM mm={7,0,"выбор","назад",mm_key,mm_dr};

struct{
	char nm[32], type, bit;
	unsigned short parts, cur_part;
	int (*doit)(int prm);
}SAVEp;

struct{
	unsigned short sh,sw,hh,skh;
}SCR;

struct{
	unsigned short x,y, x2,y2;
	RECT st;
}cur;

typedef struct{
	char v,
		nm[16];
	short x,
		y;
	IMGHDR p;
}SLOY;

SLOY sl[16], tmp_sl;

typedef struct{
	char mod,
		sl_cnt,
		ac_sl,
		inst;
	signed char zoom;
	unsigned short w,
		h;
	unsigned int sz;
	int x,
		y;
}PIC_PARAM;

PIC_PARAM p1={2,0,0,0,0,40,40,0,0,0},
		tmp_p;

typedef struct{
	char c[4],
		c8;
	unsigned short c16;
	unsigned int c32;
}COLR;

COLR COL[3], prz={{0,0,0,0},0xC0,0xE000,0}, tmp_col;

WSHDR *ews, *ws, *fws;
IMGHDR prf={40,40,5,NULL}, vpic, t_img;
RECT Canvas_2={0,0,0,0},
	dr, PCPS={0,0,0,0};
static const char perc_t[]="%t", perc_sn[]="%s\n", map_mod[6]={5,8,10,1,2,4};
extern const int DEF_PICT_MOD, /* DEF_ZOOM_MOD, */ UseHiCPU, UseFullScr, SWOW_SL;
extern const unsigned int SQ_SZ;
extern const char SAVE_PATH[], B_COL_1[], B_COL_2[];
char rewr=0, Quit=0, start=1, open, crp, gst, f_h, sf_h, BigPx=0, BigPy=0, waitsave=0,
		savename[32]="", fname[256],
		dop_col0[3][4]={{0xff,0xff,0xff,0xff},{0,0,0,0xff},{0xff,0xff,0xff,0xff}},
		dop_col[2][4]={{0,0,0,70},{0,0,0,40}},
			white[4]={0xff,0xff,0xff,0xff},
			white0[4]={0xff,0xff,0xff,0},
			black[4]={0,0,0,0xff},
			blpr[4]={0,0,0,50},
			pr[4]={0,0,0,0},
			green[4]={0,0xff,0,0xff},
			blue[4]={0,0,0xff,0xff},
			red[4]={0xff,0,0,0xff};
unsigned int YDP;

void ExitProc(int decision)
{
  if(!decision)Quit = 1;
}

void do_file(char *filepath, char *mimetype, void *param)
{
	wsprintf(fws,filepath);
	wsprintf(ws,mimetype);
	ExecuteFile(fws,ws,param);
}


char *ver="0.1.b3";
