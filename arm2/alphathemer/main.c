#include "../inc/swilib.h"
#include "rect_patcher.h"
#include "dat.h"
#include "rw.c"

#define TMR_SEC	216
#define mcnt 	2

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;

static const void * const wgui_methods[11];

typedef struct
{
  CSM_RAM csm;
  int view_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}VIEW_GUI;

int maincsm_id, scr_w, scr_h, xd[2]={1,1}, f_h;
WSHDR *ews, *ws;

GBSTMR scrtmr;
void (*subdr)();

const char white[]={0xff,0xff,0xff,100},
		black[]={0,0,0,100},
		red[]={0xFF,0,0,100},
		white0[]={0xff,0xff,0xff,50},
		perc_t[]="%t",
		*bitnm[]={"8bit", "16bit", "24bit+alfa"},
		*YN[]={"no","yes"};

//===============================================================================================

int initprpd()
{
	int f;
	unsigned int ul;
	unlink(PROF_PD,&ul);
	if ((f=fopen(PROF_PD,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fclose(f,&ul);
		return _OK;
	}
	else return F_PROF_PD;
}

void initdir()
{
	int tmp[2];
	unsigned int er, i=0xA0800000, ch=0;
	while((i<0xA0A00000)&&(!ch))
	{
		memcpy(&tmp[0], (char*)i, 4);
		if(tmp[0]==tcd_[0])
		{
		  memcpy(&tmp[1], (char*)i+4, 4);
		  if(tmp[1]==tcd_[1])
		  {
			zeromem(c_dir, 64);
			memcpy(c_dir, (char*)i-1, 16);
			ch=1;
		  }
		}
		i++;
	}
	if((ch)&&(isdir(c_dir, &er))) state=initprpd();
	else state=F_CACHE_DIR;
	/* if(isdir(CACHE_DIR_1, &er))
	{
		strcpy(c_dir, CACHE_DIR_1);
		state=initprpd();
	}
	else if(isdir(CACHE_DIR_2, &er))
		{
			strcpy(c_dir, CACHE_DIR_2);
			state=initprpd();
		}
		else state=F_CACHE_DIR; */
	REDRAW();
//	DirectRedrawGUI();
}

void sdr2()
{
	// wsprintf(ws, perc_t, YN[1]);
	// char w=Get_WS_width(ws, FONT_SMALL);
	wsprintf(ws, "%t\n%t", YN[0], YN[1]);
	char w=Get_WS_width(ws, FONT_SMALL);
	DrawRectangle(12+c_w,YDISP+1+4*f_h, 14+c_w+w,YDISP+3+6*f_h, 0,white,black);
	DrawRectangle(13+c_w,YDISP+2+(4+sbpos)*f_h, 13+c_w+w,YDISP+2+(5+sbpos)*f_h, 0,white,white0);
	DrawString(ws,12+c_w,YDISP+2+4*f_h,14+c_w+w,YDISP+2+6*f_h,FONT_SMALL,2,white,NULL);
}

void scr0()
{
	switch(pos)
	{
	 case 0:
		str_2ws(ws, c_dir, 256);
	   break;
	 case 1:
		str_2ws(ws, PROF_PD, 256);
	   break;
	}
	unsigned int w=Get_WS_width(ws, FONT_SMALL);
	if(w>scr_w)
	{
		if(w-xd[pos]<=scr_w-10)
		{
			xd[pos]=1;
			GBS_StartTimerProc(&scrtmr, TMR_SEC/2, scr0);
		}
		else
			if(xd[pos]==1)
			{
				xd[pos]++;
				GBS_StartTimerProc(&scrtmr, TMR_SEC/2, scr0);
				DirectRedrawGUI();
			}
			else
			{
				xd[pos]+=5;
				GBS_StartTimerProc(&scrtmr, 10, scr0);
				DirectRedrawGUI();
			}
	}
}

const char *errstr[]={"Wait!", "", "Cache directory is not found!!!",
			"Profile config file is not found!!!", "Unknown error!!!"};

 //Redraw
static void _GUIRedraw(VIEW_GUI *data) //Redraw
{
	DrawRectangle(0,YDISP, scr_w,scr_h, 0,white,black);
	DrawRectangle(0,scr_h-f_h-2, scr_w,scr_h, 0,white,black);
	switch(state)
	{
	 case _OK:
		if(pos>1) DrawRectangle(1,YDISP+1+(pos*2)*f_h,scr_w-1,YDISP+3+(1+pos*2)*f_h,0,white,white0);
		else DrawRectangle(1,YDISP+1+(pos*2+1)*f_h,scr_w-1,YDISP+3+(2+pos*2)*f_h,0,white,white0);

		wsprintf(ws, perc_t, "Cache dir:\n\nProfile conf:\n\nCompress:");
		DrawString(ws,2,YDISP+2,scr_w-2,scr_h,FONT_SMALL,1,white0,NULL);

		str_2ws(ws, c_dir, 64);
		DrawScrollString(ws,2,YDISP+2+f_h,scr_w-2,scr_h,xd[0],FONT_SMALL,1,white,NULL);

		str_2ws(ws, PROF_PD, 64);
		DrawScrollString(ws,2,YDISP+2+3*f_h,scr_w-2,scr_h,xd[1],FONT_SMALL,1,white,NULL);

		wsprintf(ws, perc_t, YN[compr]);
		DrawString(ws,12+c_w,YDISP+2+4*f_h,scr_w-2,scr_h,FONT_SMALL,1,white,NULL);

		wsprintf(ws, perc_t, "Init");
		DrawString(ws,0,scr_h-f_h, scr_w/3,scr_h,FONT_SMALL,2,white0,NULL);
	   break;
	 default:
		wsprintf(ws, perc_t, errstr[state]);
		DrawString(ws,2,YDISP+20,scr_w-2,scr_h,FONT_MEDIUM,2,red,NULL);
	   break;
	}
	wsprintf(ws, perc_t, "Exit");
	DrawString(ws,scr_w*2/3,scr_h-f_h, scr_w,scr_h,FONT_SMALL,2,white0,NULL);

	if(sb) subdr();
}

 //Create
static void _GUICreate(VIEW_GUI *data,void *(*malloc_adr)(int)) //Create
{
	state=0;
	SUBPROC((void*)initdir);
	scr_h=ScreenH()-1;
	scr_w=ScreenW()-1;
	f_h=GetFontYSIZE(FONT_SMALL);
	wsprintf(ws, perc_t, "Compress: ");
	c_w=Get_WS_width(ws, FONT_SMALL);
	scr0();
	data->gui.state=1;
}

 //Close
static void _GUIClose(VIEW_GUI *data,void (*mfree_adr)(void *))
{
	if(IsTimerProc(&scrtmr)) GBS_DelTimer(&scrtmr);

	for(int i=0; i<ccnt; i++ )
		if(strlen(c[i].fl)) mfree(c[i].fl);
	data->gui.state=0;
}

 //Focus
static void _GUIFocus(VIEW_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
	DisableIDLETMR();
	data->gui.state=2;
}

 //Unfocus
static void _GUIUnfocus(VIEW_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

 //OnKey
static int _GUIOnKey(VIEW_GUI *data,GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
  if ((m==KEY_DOWN)||(m==LONG_PRESS))
  {
	switch(msg->gbsmsg->submess)
	{
	 case RIGHT_SOFT:
	 case RED_BUTTON:
	   if(sb) sb=0;
	   else return 1;
	   break;
	 case ENTER_BUTTON:
	   if(!sb)
		switch(pos)
		{
		 case 2:
			sb=1;
			sbpos=compr;
			subdr=sdr2;
		   break;
		}
	   else
	   {
		switch(pos)
		{
		 case 2:
			compr=sbpos;
		   break;
		}
		sb=0;
	   }
	   break;
	 case UP_BUTTON:
	 case VOL_UP_BUTTON:
	 case '2':
		if(!sb)
		{
			pos--;
			if(pos>mcnt) pos=mcnt;
			xd[0]=xd[1]=1;
			if(IsTimerProc(&scrtmr)) GBS_DelTimer(&scrtmr);
			if(pos<2) scr0();
		}
		else
		{
			sbpos--;
			if((pos==2)&&(sbpos>=2)) sbpos=1;
		}
	   break;
	 case DOWN_BUTTON:
	 case VOL_DOWN_BUTTON:
	 case '8':
		if(!sb)
		{
			pos++;
			if(pos>mcnt) pos=0;
			xd[0]=xd[1]=1;
			if(IsTimerProc(&scrtmr)) GBS_DelTimer(&scrtmr);
			if(pos<2) scr0();
		}
		else
		{
			sbpos++;
			if((pos==2)&&(sbpos>=2)) sbpos=0;
		}
	   break;
	 case LEFT_SOFT:
		if(state==_OK) rPD();
	   break;
	}
	DirectRedrawGUI();
  }
  return 0;
}

static int met0(void){return(0);}

static const void * const gui_methods[11]={
  (void *)_GUIRedraw,
  (void *)_GUICreate,
  (void *)_GUIClose,
  (void *)_GUIFocus,
  (void *)_GUIUnfocus,
  (void *)_GUIOnKey,
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)met0,
  (void *)met0,
  0
};



// #pragma inline=forced
// int toupper(int c)
// {
  // if ((c>='a')&&(c<='z')) c+='A'-'a';
  // return(c);
// }
// #pragma inline
// int strcmp_nocase(const char *s1,const char *s2)
// {
  // int i;
  // int c;
  // while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  // return(i);
// }

static void maincsm_oncreate(CSM_RAM *data)
{
	ews=AllocWS(256);
	ws=AllocWS(256);
  MAIN_CSM *csm=(MAIN_CSM*)data;
		//rPD();
  static const RECT Canvas={0,0,0,0};
  VIEW_GUI *view_gui=malloc(sizeof(VIEW_GUI));
  zeromem(view_gui,sizeof(VIEW_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  view_gui->gui.canvas=(void *)(&Canvas);
  view_gui->gui.methods=(void *)gui_methods;
  view_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->view_id=CreateGUI(view_gui);
}

static void Killer(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

static void maincsm_onclose(CSM_RAM *csm)
{
	FreeWS(ws);
	FreeWS(ews);
  SUBPROC((void *)Killer);
}

// void CheckDoubleRun(void)
// {
  // int csm_id;
  // if ((csm_id=(int)(gipc.data))!=-1)
  // {
    // gipc.name_to=ipc_xtask_name;
    // gipc.name_from=ipc_my_name;
    // gipc.data=(void *)csm_id;
    // GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);
    // LockSched();
    // CloseCSM(maincsm_id);
    // UnlockSched();
  // }
// }

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;

	/* if (msg->msg==MSG_IPC)
	{
		IPC_REQ *ipc;
		if ((ipc=(IPC_REQ*)msg->data0))
		{
			if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
			{
				switch (msg->submess)
				{
				}
			}
		}
	} */



  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->view_id)
    {
		csm->csm.state=-3;
    }
  }
  return(1);
}

static unsigned short maincsm_name_body[140];

static const struct
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

static void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),perc_t,ipc_my_name);
}

int main(const char *exename, const char *filename)
{
	char dummy[sizeof(MAIN_CSM)];
    UpdateCSMname();
    LockSched();
    maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
    UnlockSched();
  return 1;
}






//////////////////////////////////////////////////

static void WGRedraw(VIEW_GUI *data) //Redraw
{
	DrawRectangle(0,YDISP, scr_w,scr_h, 0,white,black);
		DrawRectangle(0,scr_h-f_h-2, scr_w,scr_h, 0,white,black);

	switch(state)
	{
	 case _OK:
		wsprintf(ws,"Ready to install");
		if((w_err)||(w_warn)) DrawString(ws,1,YDISP+2,scr_w-1,scr_h,FONT_SMALL,2,red,NULL);
		else DrawString(ws,1,YDISP+2,scr_w-1,scr_h,FONT_SMALL,2,white0,NULL);
		wsprintf(ws, "Cancel");
		DrawString(ws,2,scr_h-f_h-1,scr_w-2,scr_h,FONT_SMALL,4,white0,NULL);
		wsprintf(ws, "Isntall");
		DrawString(ws,2,scr_h-f_h-1,scr_w-2,scr_h,FONT_SMALL,1,white0,NULL);
	  break;
	 case W_INIT:
		wsprintf(ws, perc_t, "initialization...");
		DrawString(ws,1,YDISP+2,scr_w-1,scr_h,FONT_SMALL,2,white,NULL);
	  break;
	 case W_WRT:
		wsprintf(ws, perc_t, "writing...");
		DrawString(ws,1,YDISP+2,scr_w-1,scr_h,FONT_SMALL,2,white,NULL);
	  break;
	 case W_FIN:
		wsprintf(ws, perc_t, "DONE!\n\nnow you need to reboot");
		DrawString(ws,1,YDISP+20,scr_w-1,scr_h,FONT_MEDIUM,2,white,NULL);
		wsprintf(ws, "Exit");
		DrawString(ws,2,scr_h-f_h-1,scr_w-2,scr_h,FONT_SMALL,4,white0,NULL);
		wsprintf(ws, "Reboot");
		DrawString(ws,2,scr_h-f_h-1,scr_w-2,scr_h,FONT_SMALL,1,white0,NULL);
	  break;
	 case NOT_24:
		wsprintf(ws, perc_t, "Not \"24 bits+alpha\" in ElfPack's config!!!");
		DrawString(ws,1,YDISP+20,scr_w-1,scr_h,FONT_MEDIUM,2,white,NULL);
		wsprintf(ws, "Exit");
		DrawString(ws,2,scr_h-f_h-1,scr_w-2,scr_h,FONT_SMALL,4,white0,NULL);
	  break;
	 case W_FAIL:
		wsprintf(ws, perc_t, "Error!!!");
		DrawString(ws,1,YDISP+20,scr_w-1,scr_h,FONT_MEDIUM,2,white,NULL);
		wsprintf(ws, "Exit");
		DrawString(ws,2,scr_h-f_h-1,scr_w-2,scr_h,FONT_SMALL,4,white0,NULL);
	  break;
	}
	if(state>_OK)
	{
		wsprintf(ws, "%t:\n\n%t", c[k].nm, c[k].fl);
		DrawString(ws,1,YDISP+5+f_h,scr_w-1,scr_h,FONT_SMALL,1,white,NULL);
		DrawRectangle(5, scr_h-2*f_h-2, scr_w-5, scr_h-f_h-5, 0,white,black);
		DrawRectangle(5, scr_h-2*f_h-2, 5+(scr_w-10)*k/ccnt, scr_h-f_h-5, 0,white,white0);
	}
}

 //Create
static void WGCreate(VIEW_GUI *data,void *(*malloc_adr)(int)) //Create
{
	data->gui.state=1;
}

 //Close
static void WGClose(VIEW_GUI *data,void (*mfree_adr)(void *))
{
	data->gui.state=0;
}

 //Focus
static void WGFocus(VIEW_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
	DisableIDLETMR();
	data->gui.state=2;
}

 //Unfocus
static void WGUnfocus(VIEW_GUI *data,void (*mfree_adr)(void *))
{
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
}

 //OnKey
static int WGOnKey(VIEW_GUI *data,GUI_MSG *msg)
{
  int m=msg->gbsmsg->msg;
  if ((m==KEY_DOWN)||(m==LONG_PRESS))
  {
	switch(msg->gbsmsg->submess)
	{
	 case RED_BUTTON:
	 case RIGHT_SOFT:
		if(state<=W_FIN) CloseCSM(maincsm_id);
		if(state==_OK) return 1;
	   break;
	 case LEFT_SOFT:
		if(state==W_FIN)
		{
			RebootPhone();
			CloseCSM(maincsm_id);
		}
		if(state==_OK) SUBPROC((void*)dodat);
	   break;
	}
	DirectRedrawGUI();
  }
  return 0;
}

static const void * const wgui_methods[11]={
  (void *)WGRedraw,
  (void *)WGCreate,
  (void *)WGClose,
  (void *)WGFocus,
  (void *)WGUnfocus,
  (void *)WGOnKey,
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)met0,
  (void *)met0,
  0
};

int rPD()
{
	int f;
	unsigned int ul;
	if ((f=fopen(PROF_PD,A_ReadOnly+A_BIN,P_READ,&ul))!=-1)
	{
		fclose(f,&ul);

		static const RECT Canvas={0,0,0,0};
		VIEW_GUI *w_gui=malloc(sizeof(VIEW_GUI));
		zeromem(w_gui,sizeof(VIEW_GUI));
		patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
		w_gui->gui.canvas=(void *)(&Canvas);
//  view_gui->gui.flag30=2;
		w_gui->gui.methods=(void *)wgui_methods;
		w_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
		CreateGUI(w_gui);

		SUBPROC((void*)initdatc);
		return _OK;
	}
	return OTH_ERR;
}

