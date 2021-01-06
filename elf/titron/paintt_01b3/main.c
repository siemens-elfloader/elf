#include "../inc/swilib.h"
#include "../inc/xtask_ipc.h"
#include "conf_loader.h"
#include "version.h"
#include "rect_patcher.h"
#include "image.c"
#include "menu.c"

int maincsm_id;

extern void kill_data(void *p, void (*func_p)(void *));
const int minus11=-11;

GBSTMR drcur;

typedef struct
{
  CSM_RAM csm;
  int view_id;
}MAIN_CSM;


//===============================================================================================
void DrawCur();

void reinit()
{
	InitConfig();
	YDP=YDISP;
	#ifdef ELKA
	if(UseFullScr) YDP=0;
	#endif
	p1.mod=DEF_PICT_MOD;
	p1.zoom=0;
	//p1.zoom=DEF_ZOOM_MOD;
	PCPS.y=YDP+2*sf_h;
	PCPS.y2=SCR.sh-2*f_h;
	if(SWOW_SL) PCPS.x2=SCR.sw-13;
	else PCPS.x2=SCR.sw;
}

void initpar()
{
	int i;
	SCR.sw=ScreenW()-1;
	SCR.sh=ScreenH()-1;
	SCR.skh=SoftkeyH();
	SCR.hh=HeaderH();
	memcpy(COL[0].c, red, 4);
	memcpy(COL[1].c, black, 4);
	memcpy(COL[2].c, white, 4);
	memcpy(&dop_col0[0], &COL[0].c32, 4);
	f_h=GetFontYSIZE(FONT_SMALL);
	sf_h=GetFontYSIZE(FONT_NUMERIC_SMALL);
	reinit();
	tmp_p=p1;
	for(i=0; i<5; i++) mcv[i].y=mcv[i].y+f_h;
	if(open) {start=0; crpic();}
	else menu(newpicm);
	cur.x=0;
	cur.y=0;
	DrawCur();
}

void DrawSl()
{
	int i;
	char *CoL;
	DrawRectangle(PCPS.x2, PCPS.y, SCR.sw+1, PCPS.y2-1, 0,white,black);
	DrawRectangle(PCPS.x2+1, PCPS.y2-12*(p1.ac_sl+1)-2, SCR.sw, PCPS.y2-12*(p1.ac_sl+1)+10, 0,white,red);
	for(i=0; i<p1.sl_cnt; i++)
	{
		if(sl[i].v) CoL=blue;
		else CoL=black;
		DrawRectangle(PCPS.x2+3, PCPS.y2-12*(i+1), SCR.sw-2, PCPS.y2-12*(i+1)+8, 0,white,CoL);
	}
}

void DrawCur()
{
	if (gst==2)
	{
		crp++;
		if(crp>2) crp=0;
		DrawRectangle(p1.x+(p1.zoom+1)*cur.x, YDP+p1.y+(p1.zoom+1)*cur.y,
				p1.x+(p1.zoom+1)*cur.x+p1.zoom, YDP+p1.y+(p1.zoom+1)*cur.y+p1.zoom,
				1,dop_col0[crp],dop_col0[crp]);
	}
	GBS_StartTimerProc(&drcur, TMR_SEC/4, DrawCur);
}

void DrPic()
{
	//int i;
		DrawRectangle(p1.x-1,YDP+p1.y-1, p1.x+p1.w*(p1.zoom+1),YDP+p1.y+p1.h*(p1.zoom+1), 1,white,red);
		DrwImg((IMGHDR *)&prf, p1.x, YDP+p1.y, white, black);
		DrwImg((IMGHDR *)&vpic, p1.x, YDP+p1.y, white, black);
		//for(i=0;i<6;i++)
		//{
			//pic[i].bitmap=(char *)picmap[i];
			//if(sl[i].v) DrwImg((IMGHDR *)&sl[i].p, p1.x+sl[i].x, YDP+p1.y+sl[i].y, white, black);
		//}
		//DrawRectangle(SCR.sw-40,SCR.sh-20,SCR.sw-4,SCR.sh-2,0,COL[2].c,COL[2].c);
		DrawRectangle(0,YDP,SCR.sw,PCPS.y,0,white,black);
		DrawRectangle(0,PCPS.y2-1,SCR.sw,SCR.sh,0,white,black);
		DrawRectangle(SCR.sw-2*sf_h,YDP+sf_h-2,SCR.sw-2,YDP+2*sf_h-2,0,white,COL[1].c);
		DrawRectangle(SCR.sw-3*sf_h,YDP+2,SCR.sw-sf_h,YDP+sf_h+3,0,white,COL[0].c);
		if((p1.inst>1)&&(inst[p1.inst].p))
			wsprintf(ws,"%d/%d\n%d/%d   %d/%d",p1.w,p1.h,cur.x2,cur.y2,cur.x,cur.y);
		else 
			wsprintf(ws,"%d/%d\n%d/%d",p1.w,p1.h,cur.x,cur.y);
		DrawString(ws,3,YDP+1,SCR.sw,SCR.sh,FONT_NUMERIC_SMALL,1,white,NULL);

		wsprintf(ws,"%d,%t\n %t",inst[p1.inst].p,inst[p1.inst].nm,"Меню");
		DrawString(ws,3,SCR.sh-2*f_h+1,SCR.sw,SCR.sh,FONT_SMALL,1,white,NULL);
		if(SWOW_SL) DrawSl();
}


 //Redraw
static void _GUIRedraw(VIEW_GUI *data) //Redraw
{
	if (data->gui.state==2)
	{
		DrawRectangle(0,YDP, SCR.sw,SCR.sh, 0,white,black);
		DrPic();
		if(inst[p1.inst].p) inst[p1.inst].dr();
		DrawCur();
		if(SWOW_SL&&(inst[p1.inst].p!=2)) DrawSl();
	}
}

 //Create
static void _GUICreate(VIEW_GUI *data,void *(*malloc_adr)(int)) //Create
{
	initpar();
	data->gui.state=1;
	gst=1;
}

 //Close
static void _GUIClose(VIEW_GUI *data,void (*mfree_adr)(void *))
{
	int i=0;
	mfree(prf.bitmap);
	mfree(vpic.bitmap);
	for(i=0; i<p1.sl_cnt; i++) mfree(sl[i].p.bitmap);
	GBS_DelTimer(&drcur);
	data->gui.state=0;
	gst=0;
}

 //Focus
static void _GUIFocus(VIEW_GUI *data,void *(*malloc_adr)(int),void (*mfree_adr)(void *))
{
	DisableIDLETMR();
	#ifdef ELKA
	if(UseFullScr) DisableIconBar(1);
	#endif
	data->gui.state=2;
	gst=2;
}

 //Unfocus
static void _GUIUnfocus(VIEW_GUI *data,void (*mfree_adr)(void *))
{
	#ifdef ELKA
	if(UseFullScr) DisableIconBar(0);
	#endif
  if (data->gui.state!=2)
    return;
  data->gui.state=1;
	gst=1;
}

 //OnKey
static int _GUIOnKey(VIEW_GUI *data,GUI_MSG *msg)
{
	if (Quit) return(1);
  return(inst[p1.inst].key(msg));
}

static int _method8(void){return(0);}

static int _method9(void){return(0);}

static const void * const gui_methods[11]={
  (void *)_GUIRedraw,
  (void *)_GUICreate,
  (void *)_GUIClose,
  (void *)_GUIFocus,
  (void *)_GUIUnfocus,
  (void *)_GUIOnKey,
  0,
  (void *)kill_data, //method7, //Destroy
  (void *)_method8,
  (void *)_method9,
  0
};

#pragma inline=forced
int toupper(int c)
{
  if ((c>='a')&&(c<='z')) c+='A'-'a';
  return(c);
}
#pragma inline
int strcmp_nocase(const char *s1,const char *s2)
{
  int i;
  int c;
  while(!(i=(c=toupper(*s1++))-toupper(*s2++))) if (!c) break;
  return(i);
}

static void maincsm_oncreate(CSM_RAM *data)
{
  static const RECT Canvas={0,0,0,0};
  MAIN_CSM *csm=(MAIN_CSM*)data;
  VIEW_GUI *view_gui=malloc(sizeof(VIEW_GUI));
  zeromem(view_gui,sizeof(VIEW_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  view_gui->gui.canvas=(void *)(&Canvas);
//  view_gui->gui.flag30=2;
  view_gui->gui.methods=(void *)gui_methods;
  view_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
	ews=AllocWS(256);
	ws=AllocWS(256);
	fws=AllocWS(256);
  csm->view_id=CreateGUI(view_gui);
  gipc.name_to=ipc_my_name;
  gipc.name_from=ipc_my_name;
  gipc.data=(void *)-1;
  GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_CHECK_DOUBLERUN,&gipc);
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
	FreeWS(fws);
  SUBPROC((void *)Killer);
}

void CheckDoubleRun(void)
{
  int csm_id;
  if ((csm_id=(int)(gipc.data))!=-1)
  {
    gipc.name_to=ipc_xtask_name;
    gipc.name_from=ipc_my_name;
    gipc.data=(void *)csm_id;
    GBS_SendMessage(MMI_CEPID,MSG_IPC,IPC_XTASK_SHOW_CSM,&gipc);  
    LockSched();
    CloseCSM(maincsm_id);
    //ShowMSG(1,(int)LG_ALREADY_STARTED);
    UnlockSched();
  }
}

static int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  
  if(msg->msg == MSG_RECONFIGURE_REQ) // Перечитывание конфига по сообщению
  {
    if (strcmp_nocase(successed_config_filename,(char *)msg->data0)==0)
    {
		reinit();
		ShowMSG(1,(int)"Paintt config updated!");
    }
  }

	if (msg->msg==MSG_IPC)
	{
		IPC_REQ *ipc;
		if ((ipc=(IPC_REQ*)msg->data0))
		{
			if (strcmp_nocase(ipc->name_to,ipc_my_name)==0)
			{
				switch (msg->submess)
				{
					case IPC_CHECK_DOUBLERUN:
						//Если приняли свое собственное сообщение, значит запускаем чекер
						if (ipc->name_from==ipc_my_name) SUBPROC((void *)CheckDoubleRun);
						else ipc->data=(void *)maincsm_id;
					  break;
					case IPC_SAVE_FINISHED:
						SAVEp.cur_part=SAVEp.parts;
						waitsave=0;
						DirectRedrawGUI();
					  break;
					case IPC_SAVE_PART:
						SAVEp.cur_part++;
						DirectRedrawGUI();
					  break;
				}
			}
		}
	}



  if (msg->msg==MSG_GUI_DESTROYED)
  {
    if ((int)msg->data0==csm->view_id)
    {
		csm->csm.state=-3;
    }
  }

	if(UseHiCPU) SetCpuClockTempHi(2);
	if (Quit)
    {
		csm->csm.state=-3;
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
  //WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Paintt v%t",ver);
  //FreeWS(ws);
}

int main(const char *exename, const char *filename)
{
	if(*(filename+1)==':')
	{
		open=1;
		int p=read_file(filename);
		if(p!=RES_OK)
		{
			switch(p)
			{
				case FAIL_OPEN:
				    MsgBoxError(1,(int)"Не открывается!!!");
					break;
				case N_PTI_VER:
				    MsgBoxError(1,(int)"Несовпадение версии формата!!!");
					break;
				case N_FORMAT:
				    MsgBoxError(1,(int)"Неподдерживаемый фотмат!!!");
					break;
				default:
				    MsgBoxError(1,(int)"Неизвестная ошибка!!!");
					break;
			}
			SUBPROC((void *)Killer);
			return 0;
		}
		char dummy[sizeof(MAIN_CSM)];
		InitConfig();
		UpdateCSMname();
		LockSched();
		maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
		UnlockSched();
		return 0;
	}
	else
	{
		open=0;
		char dummy[sizeof(MAIN_CSM)];
		InitConfig();
	    UpdateCSMname();
	    LockSched();
	    maincsm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
	    UnlockSched();
	}
  return 0;
}
