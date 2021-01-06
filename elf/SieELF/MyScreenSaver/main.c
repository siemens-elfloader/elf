#include "..\inc\swilib.h"

#define COPYRIGHT	"MyScreenSaver\n(c)BingK(binghelingxi)"
#define ELFNAME		"MyScreenSaver"
#define SCREENW		239
#define SCREENH		319

#ifdef VKP
#define PROCESSOR_MODE __thumb
#else
#define PROCESSOR_MODE __arm
#endif

extern void kill_data(void *p, void (*func_p)(void *));
extern void Update_MissedEventsPtr(void);

const char color_black[4]={0, 0, 0, 100};
const char color_white[4]={255, 255, 255, 100};

#define TMR_SECOND	216
#define TIME		3
#define EXT_BUTTON	0x63

#define RamIsLocked	0xA8DF3458

#define DATE_POS_X	0
#define DATE_POS_Y	64
#define TIME_POS_X	0
#define TIME_POS_Y	120
#define ME_POS_X	0
#define ME_POS_Y	230

#define	ICON		0x4DA
#define	ICON_X		0x10
#define	ICON_Y		289

#pragma swi_number=0x221
__swi __arm void SetCpuClockLow(int _2);

#pragma swi_number=0x9E
__swi __arm int GetMissedEventCount(unsigned int Event);

#pragma swi_number=0x44
__swi __arm void TempLightOn(int x, int y);

typedef struct
{
	CSM_RAM csm;
	int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;

#ifdef  VKP
__no_init GBSTMR mytmr @ "RAM_TMR";
__no_init WSHDR *xws @ "RAMP_XWS";
__no_init int IsKbdLocked @ "RAM_IsKbdLocked";
__no_init unsigned int csm_id @ "RAM_CSM_ID";
__no_init unsigned int gui_id @ "RAM_GUI_ID";
__no_init int missed_events @ "MISSED_EVENS";
#else
GBSTMR mytmr;
WSHDR *xws;
int IsKbdLocked;
unsigned int csm_id;
unsigned int gui_id;
int missed_events;
#endif


void drawScreen(void)
{
#ifdef ELKA
	DisableIconBar(1);
#endif
	DrawRectangle(0, 0, SCREENW, SCREENH, 0, color_black, color_black);

	TTime time;
	TDate date;
	GetDateTime(&date, &time);
	wsprintf(xws, "%d-%02d-%02d", date.year, date.month, date.day);
	DrawString(xws, DATE_POS_X, DATE_POS_Y, SCREENW, SCREENH, FONT_MEDIUM_ITALIC_BOLD, TEXT_ALIGNMIDDLE, color_white, color_black);
	
	wsprintf(xws, "%02d:%02d", time.hour, time.min);
	DrawString(xws, TIME_POS_X, TIME_POS_Y, SCREENW, SCREENH, FONT_LARGE_ITALIC_BOLD, TEXT_ALIGNMIDDLE, color_white, color_black);
	
	wsprintf(xws, "%d Missed Event(s)!", missed_events);
	DrawString(xws, ME_POS_X, ME_POS_Y, SCREENW, SCREENH, FONT_SMALL, TEXT_ALIGNMIDDLE, color_white, color_black);
	
	if(missed_events)
		DrawImg(ICON_X, ICON_Y, ICON);
}

void TimerProc(void)
{
	GBS_SendMessage(MMI_CEPID, KEY_UP, EXT_BUTTON);
	Update_MissedEventsPtr();
	missed_events=GetMissedEventCount(0);
	if(IsGuiOnTop(gui_id))
		drawScreen();
	//else
	//	CloseCSM(csm_id);
	SetCpuClockLow(2);
	GBS_StartTimerProc(&mytmr, TMR_SECOND*TIME, TimerProc);
}


void onRedraw(MAIN_GUI *data)
{
	drawScreen();
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
	if(msg->gbsmsg->msg==LONG_PRESS)
	{
		TempLightOn(3, 0x7FFF);
		if(msg->gbsmsg->submess=='#')
			return 1;
	}
	if(msg->gbsmsg->msg==KEY_DOWN)
	{
		if(msg->gbsmsg->submess==LEFT_SOFT)
		{
			extern	void OPEN_INBOX(void);
			if(missed_events)
			{
				TempLightOn(3, 0x7FFF);
				OPEN_INBOX();
				//return 1;
			}
		}
	}
	//DirectRedrawGUI();
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
	*(int *)RamIsLocked=0; //将系统的锁键盘标志置零
	IsKbdLocked=1;
	xws=AllocWS(32);
	MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	MAIN_CSM *csm=(MAIN_CSM *)data;
	zeromem(main_gui,sizeof(MAIN_GUI));
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();	
	csm->csm.state=0;
	csm->csm.unk1=0;
	gui_id=csm->gui_id=CreateGUI(main_gui);
	GBS_StartTimerProc(&mytmr, TMR_SECOND*TIME, TimerProc);
}


int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
	MAIN_CSM *csm=(MAIN_CSM*)data;
	if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
	{
		csm->csm.state=-3;
	}
	if(!IsGuiOnTop(gui_id))
		CloseCSM(csm_id);
	return(1);
}

void Killer(void)
{
	TempLightOn(3, 0x7FFF);
	*(int *)RamIsLocked=0; //将系统的锁键盘标志置零
	IsKbdLocked=0;
	GBS_DelTimer(&mytmr);
	FreeWS(xws);
	xws=0;
	csm_id=0;
	gui_id=0;
	missed_events=0;
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
const unsigned short maincsm_name_body[16]={13,'M', 'y', 'S', 'c', 'r', 'e', 'e', 'n', 'S', 'a', 'v', 'e', 'r'};

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
	if(xws)
		return 0;
	char dummy[sizeof(MAIN_CSM)];
#ifndef VKP
	UpdateCSMname();
#endif
	LockSched();
	csm_id=CreateCSM(&MAINCSM.maincsm,dummy,0);
	UnlockSched();
	return 0;
}

__thumb int new_IsUnlocked(void)
{
	if(IsKbdLocked)
		return 0;
	return 1;
}

//#pragma diag_suppress=Pe177
//__root static const int SWILIB_IsUnlocked @ "SWILIB_IsUnlocked" = (int)new_IsUnlocked;
//#pragma diag_default=Pe177
//
//#pragma diag_suppress=Pe177
//__root static const int SWILIB_KBDLOCK @ "SWILIB_KBDLOCK" = (int)main;
//#pragma diag_default=Pe177
