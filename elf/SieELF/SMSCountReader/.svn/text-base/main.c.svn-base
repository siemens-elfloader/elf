#include "..\inc\swilib.h"


typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;

extern void kill_data(void *p, void (*func_p)(void *));

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
int is_editing=0;
int edit_line=1;
int screenw;
int screenh;
char dat_path[]="2:\\SMSCount.dat";
int f;
unsigned int ferr;
WSHDR *ws_sk;
char *utf8_str;
WSHDR *xws;

#define CP_MSG		"SMSCountReader v1.7\n(C) 2008 BingK(binghelingxi)"
#define ELFNAME		"SMSCountReader"
#define szLoadDATFail	"Load SMSCount.dat failed!"
#define szSaveALL	"Save All Change?"
#define szClearALL	"Clear ALL?"
#define szSaveErr	"Save Error!"
#define szEditExit	"Is Editing, Save First?"
#define utf8_clear	"\xE6\xB8\x85\xE9\x9B\xB6" //清零
#define utf8_exit	"\xE9\x80\x80\xE5\x87\xBA" //退出
#define utf8_edit	"\xE7\xBC\x96\xE8\xBE\x91" //编辑
#define utf8_cancel	"\xE6\x92\xA4\xE9\x94\x80" //撤销
#define name_header	"SMSCount v3.7.1\nSMSCountReader v1.7\n" 
#define utf8_all	"\xE5\x85\xA8\xE9\x83\xA8: %d" //全部
#define utf8_chm	"\xE7\xA7\xBB\xE5\x8A\xA8: %d"  //移动
#define utf8_chu	"\xE8\x81\x94\xE9\x80\x9A: %d"  //联通
#define utf8_xlt	"\xE5\xB0\x8F\xE7\x81\xB5\xE9\x80\x9A: %d"  //小灵通
#define utf8_oth	"\xE5\x85\xB6\xE4\xBB\x96: %d"  //其它
#define utf8_date	"\xE5\xBD\x93\xE5\x89\x8D\xE6\x97\xA5\xE6\x9C\x9F: %04d.%i.%i" 
#define utf8_editing	"\xE7\xBC\x96\xE8\xBE\x91\xE4\xB8\xAD\xE3\x80\x82\xE3\x80\x82\xE3\x80\x82\n\xE8\xAF\xB7\xE6\x8C\x89\xE7\xBB\xBF\xE9\x94\xAE\xE4\xBF\x9D\xE5\xAD\x98" 
#define utf8_press_enter_key	"\xE6\x8C\x89\xE4\xB8\xAD\xE9\x94\xAE\xE5\xBC\x80\xE5\xA7\x8B\xE4\xBF\xAE\xE6\x94\xB9\xE6\x95\xB0\xE6\x8D\xAE" 

#define FASTADD	  3

#define	COUNT_ALL 0
#define	COUNT_CHM 1
#define	COUNT_CHU 2
#define	COUNT_XLT 3
#define	COUNT_OTH 4
#define	TYPE_ALL  5
#define	BUF_LEN   (TYPE_ALL*sizeof(int))


int count[TYPE_ALL];
int count_bak[TYPE_ALL];

void intmemcpy_n(int *s1, int *s2, int len)
{
	int i;
	for(i=0;i<len;i++)
		s1[i]=s2[i];
}

int get_string_width(WSHDR *ws, int font)
{
  int width=0;
  unsigned short *body=ws->wsbody;
  int len=body[0];
  while(len)
  {
    width+=GetSymbolWidth(body[len],font);
    len--;
  }
  return (width);
}

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
	rc->x=x;
	rc->y=y;
	rc->x2=x2;
	rc->y2=y2;
}

int load_dat(void)
{
	//unsigned int err;
	if((f=fopen(dat_path, A_ReadWrite+A_BIN, P_READ+P_WRITE, &ferr))!=-1)
	{
		fread(f, count, BUF_LEN, &ferr);
		lseek(f, 0, S_SET, &ferr, &ferr);
		intmemcpy_n(count_bak, count, TYPE_ALL);
	}
	else if((f=fopen(dat_path, A_ReadWrite+A_Create+A_Truncate, P_READ+P_WRITE, &ferr))==-1)
		return -1;
	return 1;
}

void save_dat(int type)
{
	//unsigned int err;
	if(type==1)
	{
		int i;
		for(i=0; i<TYPE_ALL; i++)
			count[i]=0;
	}
	if(fwrite(f, count, BUF_LEN, &ferr)!=BUF_LEN)
		MsgBoxError(1,(int)szSaveErr);
	intmemcpy_n(count_bak, count, TYPE_ALL);
	is_editing=0;
}
void clearProc(int id)
{
  if(id==0)
  	save_dat(1);
}

void saveProc(int id)
{
  if(id==0)
    save_dat(0);
}

void exitsaveProc(int id)
{
	if(id==0)
		save_dat(0);
	CloseCSM(MAINCSM_ID);
}

void exit(void)
{
	if(is_editing)
	{
		MsgBoxYesNo(1, (int)szEditExit, exitsaveProc);
	}
	else
		CloseCSM(MAINCSM_ID);
}

void cancel_edit(void)
{
	intmemcpy_n(count, count_bak, TYPE_ALL);
	is_editing=0;
}

void soft_key(void)
{
  //WSHDR *wsl=AllocWS(32);
  utf8_2ws(ws_sk,utf8_exit,strlen(utf8_exit));
  DrawString(ws_sk,screenw-get_string_width(ws_sk,FONT_SMALL)-4,screenh-GetFontYSIZE(FONT_SMALL)-2,screenw,screenh,FONT_SMALL,TEXT_OUTLINE+TEXT_ALIGNRIGHT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  utf8_2ws(ws_sk,utf8_clear,strlen(utf8_clear));
  DrawString(ws_sk,2,screenh-GetFontYSIZE(FONT_SMALL)-2,screenw,screenh,FONT_SMALL,TEXT_OUTLINE+TEXT_ALIGNLEFT,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  if(is_editing)
  	utf8_2ws(ws_sk,utf8_cancel,strlen(utf8_cancel));
  else
  	utf8_2ws(ws_sk,utf8_edit,strlen(utf8_edit));
  DrawString(ws_sk,screenw/2-get_string_width(ws_sk,FONT_SMALL)/2-0x10,screenh-GetFontYSIZE(FONT_SMALL)-2,screenw/2+get_string_width(ws_sk,FONT_SMALL)/2+0x10,screenh,FONT_SMALL,TEXT_OUTLINE+TEXT_ALIGNMIDDLE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
  //FreeWS(wsl);
}

void onRedraw(MAIN_GUI *data)
{
#ifdef ELKA
	DisableIconBar(1);
#endif
	int color_index=0;
	int font_h=GetFontYSIZE(FONT_SMALL);
	DrawRectangle(0,0,screenw,screenh,0,GetPaletteAdrByColorIndex(1),GetPaletteAdrByColorIndex(1));
	soft_key();
//	char *utf8_str=malloc(128);
//	WSHDR *ws = AllocWS(128);
	wsprintf(xws, name_header);
	DrawString(xws,0,0,screenw,screenh,FONT_SMALL,TEXT_ALIGNMIDDLE+TEXT_OUTLINE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
	//全部
	sprintf(utf8_str, utf8_all, count[0]);
	utf8_2ws(xws,utf8_str,strlen(utf8_str));
	DrawString(xws,2,3*font_h,screenw,screenh,FONT_SMALL,TEXT_OUTLINE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23)); 
	//移动
	sprintf(utf8_str, utf8_chm, count[1]);
	utf8_2ws(xws,utf8_str,strlen(utf8_str));
	if(is_editing)
	{
	  if(edit_line==1)
	    color_index=2;
	  else color_index=0;
	}
	else color_index=0;
	DrawString(xws,2,4*font_h,screenw,screenh,FONT_SMALL,TEXT_OUTLINE,GetPaletteAdrByColorIndex(color_index),GetPaletteAdrByColorIndex(23)); 
	//联通
	sprintf(utf8_str, utf8_chu, count[2]);
	utf8_2ws(xws,utf8_str,strlen(utf8_str));
	if(is_editing)
	{
	  if(edit_line==2)
	    color_index=2;
	  else color_index=0;
	}
	else color_index=0;
	DrawString(xws,2,5*font_h,screenw,screenh,FONT_SMALL,TEXT_OUTLINE,GetPaletteAdrByColorIndex(color_index),GetPaletteAdrByColorIndex(23)); 
	//小灵通
	sprintf(utf8_str, utf8_xlt, count[3]);
	utf8_2ws(xws,utf8_str,strlen(utf8_str));
	if(is_editing)
	{
	  if(edit_line==3)
	    color_index=2;
	  else color_index=0;
	}
	else color_index=0;
	DrawString(xws,2,6*font_h,screenw,screenh,FONT_SMALL,TEXT_OUTLINE,GetPaletteAdrByColorIndex(color_index),GetPaletteAdrByColorIndex(23)); 
	//其它
	sprintf(utf8_str, utf8_oth, count[4]);
	utf8_2ws(xws,utf8_str,strlen(utf8_str));
	if(is_editing)
	{
	  if(edit_line==4)
	    color_index=2;
	  else color_index=0;
	}
	else color_index=0;
	DrawString(xws,2,7*font_h,screenw,screenh,FONT_SMALL,TEXT_OUTLINE,GetPaletteAdrByColorIndex(color_index),GetPaletteAdrByColorIndex(23)); 
	//显示当前日期
	TTime tt;
	TDate td;
	GetDateTime(&td,&tt);
	sprintf(utf8_str, utf8_date, td.year, td.month, td.day);
	utf8_2ws(xws,utf8_str,strlen(utf8_str));
	DrawString(xws,2,9*font_h,screenw,screenh,FONT_SMALL,TEXT_OUTLINE,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
	//正在编辑 
	if(is_editing)
		utf8_2ws(xws,utf8_editing,strlen(utf8_editing));
	else //提示按中键编辑
		utf8_2ws(xws, utf8_press_enter_key, strlen(utf8_press_enter_key));
	DrawString(xws,2,10*font_h,screenw,screenh,FONT_SMALL,TEXT_OUTLINE,GetPaletteAdrByColorIndex(7),GetPaletteAdrByColorIndex(23)); 
  
//	mfree(utf8_str);
//	FreeWS(ws);
}

void show_about(void)
{
	ShowMSG(1, (int)CP_MSG);
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
	  int i=msg->gbsmsg->submess;
	  switch(i)
	  {
	    case RIGHT_SOFT: 
	      exit();
	      break;
	    case LEFT_SOFT:
	      MsgBoxYesNo(1, (int)szClearALL, clearProc);
	      break;
	    case ENTER_BUTTON:
	    	if(is_editing==0)
	      		is_editing=1;
	      	else
	      		cancel_edit();
	      break;
	    case DOWN_BUTTON:
	    	if(is_editing)
	    	{
	      if(edit_line!=4) 
	        edit_line++;
	      else edit_line=1;
	      	}
	      break;
	    case UP_BUTTON:
	    	if(is_editing)
	    	{
	      if(edit_line!=1)
	        edit_line--;
	      else edit_line=4;
		}
	      break;
	    case LEFT_BUTTON:
	    	if(is_editing)
	    	{
	      if(count[edit_line])
	      {
	        count[0]--;
	        count[edit_line]--;
	      }
		}
	      break;
	    case RIGHT_BUTTON:
	    	if(is_editing)
	    	{
	        count[0]++;
	        count[edit_line]++;
		}
	      break;
	    case GREEN_BUTTON:
	      if(is_editing) MsgBoxYesNo(1, (int)szSaveALL, saveProc);
	      break;
	     case '*':
	     	show_about();
	     	break; 
	  }
	}
	if(msg->gbsmsg->msg==LONG_PRESS)
	{
		int i=msg->gbsmsg->submess;
		switch(i)
		{
		case DOWN_BUTTON:
	    		if(is_editing)
	    		{
				if(edit_line!=4) 
					edit_line++;
				else
					edit_line=1;
			}
			break;
		case UP_BUTTON:
			if(is_editing)
			{
				if(edit_line!=1)
					edit_line--;
				else 
					edit_line=4;
			}
			break;
		case LEFT_BUTTON:
			if(is_editing)
			{
				if(count[edit_line]>FASTADD)
				{
					count[0]-=FASTADD;
					count[edit_line]-=FASTADD;
				}
			}
			break;
		case RIGHT_BUTTON:
			if(is_editing)
			{
				count[0]+=FASTADD;
				count[edit_line]+=FASTADD;
			}
			break;
		}
	}
	DirectRedrawGUI();
	return(0);
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int method8(void){return(0);}
int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)onRedraw,	//Redraw
	(void *)onCreate,	//Create
	(void *)onClose,	//Close
	(void *)onFocus,	//Focus
	(void *)onUnfocus,	//Unfocus
	(void *)OnKey,		//OnKey
	0,
	(void *)kill_data,	//Destroy
	(void *)method8,
	(void *)method9,
	0
};

const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
	screenw=ScreenW()-1;
	screenh=ScreenH()-1;
	ws_sk=AllocWS(32);
	utf8_str=malloc(256);
	xws=AllocWS(256);
	int i;
	for(i=0; i<TYPE_ALL; i++)
		count[i]=0;
	if(load_dat()<0)
		ShowMSG(1, (int)szLoadDATFail);
	MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	MAIN_CSM *csm=(MAIN_CSM *)data;
	zeromem(main_gui,sizeof(MAIN_GUI));
	patch_rect((RECT*)&Canvas,0,0,screenw-1,screenh-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
	
	csm->csm.state=0;
	csm->csm.unk1=0;
	csm->gui_id=CreateGUI(main_gui);
	
	MAINGUI_ID=csm->gui_id;
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
	return(1);
}

void Killer(void)
{
  extern void *ELF_BEGIN;
  //unsigned int err;
  fclose(f, &ferr);
  FreeWS(ws_sk);
  mfree(utf8_str);
  FreeWS(xws);
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)Killer);
}

const int minus11=-11;
unsigned short maincsm_name_body[140];

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
    maincsm_onmessage,
    maincsm_oncreate,
#ifdef NEWSGOLD
0,
0,
0,
0,
#endif
maincsm_onclose,
sizeof(MAIN_CSM),
1,
&minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void) 
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name), ELFNAME);
}

int main(char *initday)
{
  char dummy[sizeof(MAIN_CSM)];
  UpdateCSMname();
  LockSched();
  MAINCSM_ID=CreateCSM(&MAINCSM.maincsm,dummy,0);
  UnlockSched();
  return 0;
}
