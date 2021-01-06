#include "..\inc\swilib.h"

#define COPYRIGHT	"ViewTheLastSMS\n(c)BingK(binghelingxi)"
#define ELFNAME		"ViewTheLastSMS"
#ifdef	ELKA
#define SCREENW		239
#define SCREENH		319
#else
#define SCREENW		131
#define SCREENH		175
#endif


extern void kill_data(void *p, void (*func_p)(void *));
void GetSMSData(WSHDR *the_ws);

const char color_black[4]={0, 0, 0, 100};
const char color_white[4]={255, 255, 255, 100};

#define POS_X	0
#define POS_Y	1
#define _t	"%t"

typedef struct
{
	CSM_RAM csm;
	int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;

void soft_key(void)
{
  WSHDR *wsl=AllocWS(32);
  wsprintf(wsl, _t, "ÍË³ö");
  DrawString(wsl, 0, SCREENH-GetFontYSIZE(FONT_SMALL)-2, SCREENW, SCREENH, FONT_SMALL, TEXT_OUTLINE+TEXT_ALIGNRIGHT, color_white, color_black); 
  FreeWS(wsl);
}

void onRedraw(MAIN_GUI *data)
{
#ifdef ELKA
	DisableIconBar(1);
#endif
	DrawRectangle(0, 0, SCREENW, SCREENH, 0, color_black, color_black);
	soft_key();
	WSHDR *ws=AllocWS(512);
	GetSMSData(ws);
	DrawString(ws, POS_X, POS_Y, SCREENW, SCREENH, FONT_SMALL, TEXT_ALIGNLEFT, color_white, color_black);
	FreeWS(ws);
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
		if(msg->gbsmsg->submess==RIGHT_SOFT)
			return 1;
	}
	DirectRedrawGUI();
	return 0;
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
	if(data->gui.state!=2)
		return;
	data->gui.state=1;
}

int method8(void)
{
	return(0);
}

int method9(void)
{
	return(0);
}

const RECT Canvas={0, 0, SCREENW, SCREENH};

const void * const gui_methods[11]=
{
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
void maincsm_oncreate(CSM_RAM *data)
{
	MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	MAIN_CSM *csm=(MAIN_CSM *)data;
	zeromem(main_gui,sizeof(MAIN_GUI));
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
	csm->csm.state=0;
	csm->csm.unk1=0;
	csm->gui_id=CreateGUI(main_gui);
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
#ifndef VKP
	extern void *ELF_BEGIN;
	extern void kill_data(void *p, void (*func_p)(void *));
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
#endif
}

void maincsm_onclose(CSM_RAM *csm)
{
	SUBPROC((void *)Killer);
}

const int minus11=-11;
const unsigned short maincsm_name_body[16]={14,'V', 'i', 'e', 'w', 'T', 'h', 'e', 'L', 'a', 's', 't', 'S', 'M', 'S'};

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
		(unsigned short *)maincsm_name_body,
		NAMECSM_MAGIC1,
		NAMECSM_MAGIC2,
		0x0,
		139
	}
};

#ifndef VKP
void UpdateCSMname(void)
{
	wsprintf((WSHDR *)(&MAINCSM.maincsm_name), ELFNAME);
}
#endif

int main(void)
{
	char dummy[sizeof(MAIN_CSM)];
#ifndef VKP
	UpdateCSMname();
#endif
	LockSched();
	CreateCSM(&MAINCSM.maincsm,dummy,0);
	UnlockSched();
	return 0;
}

