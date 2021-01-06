#include "../inc/swilib.h"
#include "../inc/xtask_ipc.h"
#include "paintt_IPC.h"
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

void do_small_prf()
{
	unsigned int i,j, k=2*SQ_SZ,f;
	char cl;
	small_prf.w=3*sf_h+2;
	small_prf.h=2*sf_h-1;
	//if(prf.bitmap) mfree(prf.bitmap);
	small_prf.bitmap=malloc(small_prf.w*small_prf.h);
	for (i=0;i<small_prf.h;i++)
	{
		k++;
		if(k>=2*SQ_SZ) k=0;
		if(k<SQ_SZ) f=2*SQ_SZ;
		else f=SQ_SZ-1;
		for (j=0;j<small_prf.w;j++)
		{
			f++;
			if(f>=2*SQ_SZ) f=0;
			if(f<SQ_SZ)
			{
				cl=RGB_24_8((char*)B_COL_1);
			}
			else
			{
				cl=RGB_24_8((char*)B_COL_2);
			}
			memcpy(small_prf.bitmap+i*small_prf.w+j, &cl, 1);
		}
	}
}

void reinit()
{
	InitConfig();
	YDP=YDISP;
	#ifdef ELKA
	if(UseFullScr) YDP=0;
	#endif
	Pt.m=DEF_PICT_MOD;
	//p->z=DEF_ZOOM_MOD;
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
	do_small_prf();
	reinit();
	//zeromem(&tmp_p, sizeof(PIC_PARAM));
	tmp_p.w=DEF_W;
	tmp_p.h=DEF_H;
	for(i=0; i<5; i++) mcv[i].y=mcv[i].y+f_h;
	if(open) {crpic();}
	else {sprintf(tmp_p.nm, perc_s, "Image_1");
		menu(newpicm);}
	DrawCur();
}

void DrawSl()
{
	int i;
	char *CoL;
	DrawRectangle(PCPS.x2, PCPS.y, SCR.sw+1, PCPS.y2-1, 0,white,black);
	DrawRectangle(PCPS.x2+1, PCPS.y2-12*(p->ns+1)-2, SCR.sw, PCPS.y2-12*(p->ns+1)+10, 0,white,red);
	for(i=0; i<p->cs; i++)
	{
		if(p->sl[i].v) CoL=blue;
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
		drawArc(p->x+(p->z+1)*(p->cur.x-3),			YDP+p->y+(p->z+1)*(p->cur.y-3),
				p->x+(p->z+1)*(p->cur.x+3)+p->z,	YDP+p->y+(p->z+1)*(p->cur.y+3)+p->z,
				0,360,0,dop_col0[crp],NULL);
		
		DrawRectangle(	p->x+(p->z+1)*p->cur.x, 		YDP+p->y+(p->z+1)*p->cur.y,
						p->x+(p->z+1)*p->cur.x+p->z,	YDP+p->y+(p->z+1)*p->cur.y+p->z,
						0,dop_col0[crp],dop_col0[crp]);
	}
	GBS_StartTimerProc(&drcur, TMR_SEC/4, DrawCur);
}

void DrPic()
{
	//int i;
		DrawRectangle(p->x-1,YDP+p->y-1, p->x+p->w*(p->z+1),YDP+p->y+p->h*(p->z+1), 1,white,red);
		//DrwImg((IMGHDR *)&prf, p->x, YDP+p->y, white, black);
		DrwImg((IMGHDR *)&vpic, p->x, YDP+p->y, white, black);
		//for(i=0;i<6;i++)
		//{
			//pic[i].bitmap=(char *)picmap[i];
			//if(p->sl[i].v) DrwImg((IMGHDR *)&p->sl[i].p, p->x+p->sl[i].x, YDP+p->y+p->sl[i].y, white, black);
		//}
		//DrawRectangle(SCR.sw-40,SCR.sh-20,SCR.sw-4,SCR.sh-2,0,COL[2].c,COL[2].c);
		DrawRectangle(0,YDP,SCR.sw,PCPS.y,0,white,black);
		DrawRectangle(0,PCPS.y2-1,SCR.sw,SCR.sh,0,white,black);
		DrwImg((IMGHDR *)&small_prf, SCR.sw-3*sf_h-2, YDP+1, white, black);
		DrawRectangle(SCR.sw-3*sf_h-1,YDP+1,SCR.sw-1,YDP+2*sf_h-1,0,COL[2].c,COL[2].c);
		DrawRectangle(SCR.sw-2*sf_h,YDP+sf_h-2,SCR.sw-2,YDP+2*sf_h-2,0,white,COL[1].c);
		DrawRectangle(SCR.sw-3*sf_h,YDP+2,SCR.sw-sf_h,YDP+sf_h+3,0,white,COL[0].c);
		
		
		wsprintf(ws,"Zoom:\n%dX ",p->z+1);
		DrawString(ws,3,SCR.sh-2*f_h+1,SCR.sw-3,SCR.sh,FONT_SMALL,4,white,NULL);
		
		if((Pt.i>1)&&(inst[Pt.i].p))
			wsprintf(ws,"%d/%d\n%d/%d   %d/%d",p->w,p->h,p->cur.x2,p->cur.y2,p->cur.x,p->cur.y);
		else 
			wsprintf(ws,"%d/%d\n%d/%d",p->w,p->h,p->cur.x,p->cur.y);
		DrawString(ws,3,YDP+1,SCR.sw,SCR.sh,FONT_NUMERIC_SMALL,1,white,NULL);

		wsprintf(ws,"%d,%t\n %t",inst[Pt.i].p,inst[Pt.i].nm,"Меню");
		DrawString(ws,3,SCR.sh-2*f_h+1,SCR.sw,SCR.sh,FONT_SMALL,1,white,NULL);
}


 //Redraw
static void _GUIRedraw(VIEW_GUI *data) //Redraw
{
	if (data->gui.state==2)
	{
		DrawRectangle(0,YDP, SCR.sw,SCR.sh, 0,white,black);
		DrPic();
		if(inst[Pt.i].p) inst[Pt.i].dr();
		//if(SWOW_SL) DrawSl();
		DrawCur();
		if(SWOW_SL&&(inst[Pt.i].p!=2)) DrawSl();
	}
}

 //Create
static void _GUICreate(VIEW_GUI *data,void *(*malloc_adr)(int)) //Create
{
	//p->sl[0]=malloc(sizeof(SLOY));
	//p->sl[1]=malloc(sizeof(SLOY));
	initpar();
	data->gui.state=1;
	gst=1;
}

 //Close
static void _GUIClose(VIEW_GUI *data,void (*mfree_adr)(void *))
{
	int i, j;
	mfree(small_prf.bitmap);
	if(!open)
	{
		mfree(prf);
		mfree(vpic.bitmap);
		for(j=0; j<Pt.cp; j++)
			for(i=0; i<picp[j].cs; i++) mfree(picp[j].sl[i].map);
	}
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
  return(inst[Pt.i].key(msg));
}

//static int _method8(void){return(0);}

//static int _method9(void){return(0);}

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
		Pt.cp=1;
		Pt.np=0;
		if(!open_file(filename))
		{
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
