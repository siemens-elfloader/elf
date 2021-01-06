#define TMR_SEC 216

#pragma swi_number=0x222
__swi __arm void SetCpuClockTempHi(int const_2);

static IPC_REQ gipc;

typedef signed char		CHAR;
typedef unsigned char	BYTE;
typedef short			SHORT;
typedef unsigned short	WORD;
typedef int				INT;
typedef unsigned int	UINT;
typedef long			LONG;
typedef unsigned long	DWORD;


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
int Preview();

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
	signed char lev;
	char sh_all;
}MENU_GUI;

typedef struct
{
	char cnt, pos, bt1[16], bt2[16];
	RECT cv;
	int (*key)(GUI_MSG *msg, MENU_GUI *data);
	void (*dr)(RECT cv, int lev);
}MENU_PARAM;

int	mm_key(GUI_MSG *msg, MENU_GUI *data),
	zmenu_key(GUI_MSG *msg, MENU_GUI *data);
void DrPic(), DrawSl(),
	mm_dr(RECT cv, int lev),
	zmenu_dr(RECT cv, int lev);

static const MENU_PARAM mm={7,0,"выбор","назад",{0,0,0,0},mm_key,mm_dr},
					zmenu={2,0,"выбор","назад",{0,0,0,0},zmenu_key,zmenu_dr};

struct{
	char fl[256], nm[128], type, btype, param, compr;
	unsigned short parts, cur_part, n;
	int (*doit)(int prm);
}SAVEp;

struct{
	unsigned short sh,sw,hh,skh;
}SCR;

struct{
	char m,
		i;
	unsigned short cp, np;
}Pt;

typedef struct{
	char v,
		nm[19];
	short x, y,
		w, h;
	char *map;
}SLOY;

SLOY tmp_sl;

typedef struct{
	char nm[32];
	signed char z;
	int x,
		y;
	RECT cur;
	char cs, // количество слоёв
		ns; // номер активного слоя
	unsigned short w,
		h;
	unsigned int sz;
	SLOY sl[16];
}PIC_PARAM;

PIC_PARAM picp[6]/* ={2,0,0,0,0,40,40,0,0,0} */,
		tmp_p,
		*p;

typedef struct{
	char c[4],
		c8;
	unsigned short c16;
	unsigned int c32;
}COLR;

COLR COL[3], prz={{0,0,0,0},0xC0,0xE000,0}, tmp_col;

WSHDR *ews, *ws, *fws;
IMGHDR small_prf={40,40,5,NULL}, vpic, t_img;
RECT Canvas_2={0,0,0,0},
	dr, PCPS={0,0,0,0};
static const char perc_t[]="%t", perc_s[]="%s", perc_sn[]="%s\n", _SLASH='\\', map_mod[6]={5,8,10,1,2,4};
extern const int DEF_PICT_MOD, /* DEF_ZOOM_MOD, */ UseHiCPU, UseFullScr, SWOW_SL;
extern const unsigned int SQ_SZ, DEF_W, DEF_H;
extern const char SAVE_PATH[], B_COL_1[], B_COL_2[];
char rewr=0, Quit=0, start=1, open, crp, gst, f_h, sf_h, BigPx=0, BigPy=0, waitsave=0, fmtype,
		*prf,
		fname[256],
		dop_col0[3][4]={{0xff,0xff,0xff,0xff},{0,0,0,0xff},{0xff,0xff,0xff,0xff}},
		dop_col[2][4]={{0,0,0,70},{0,0,0,40}},
			white[4]={0xff,0xff,0xff,0xff},
			white0[4]={0xff,0xff,0xff,0},
			black[4]={0,0,0,0xff},
			blpr[4]={0,0,0,70},
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


char *ver="0.1";
