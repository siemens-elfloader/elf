#include "inc\mc.h"
#include "inc\zslib.h"

const int minus11=-11; // стремная константа
unsigned short maincsm_name_body[140];
volatile int GUIStarted = 0; //Elf вызван
volatile int Terminate = 0; // флаг необходимости завершения работы
volatile int Busy = 0;

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

int MsgBoxResult = -1;

unsigned int err;


char* zippathbuf;
FN_LIST tmp_files;

typedef struct
{
	CSM_RAM csm;
	int gui_id;
} MAIN_CSM;

typedef struct
{
	GUI gui;
	//  WSHDR *ws1;
	//  WSHDR *ws2;
	//  int i1;
} MAIN_GUI;


void OnRedraw(MAIN_GUI *data) // OnRedraw
{

			}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{

	  
	data->gui.state = 1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{

	data->gui.state = 0;
	
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
	
	data->gui.state = 2;
	
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
	

	if (data->gui.state != 2) return;
	data->gui.state = 1;
}


int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
	

	return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

void Killer(void)
{
	
	extern void *ELF_BEGIN;
	kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
	(void *)OnRedraw,	//Redraw
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

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
	rc->x=x;
	rc->y=y;
	rc->x2=x2;
	rc->y2=y2;
}
const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{

	MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
	MAIN_CSM *csm=(MAIN_CSM*)data;
	zeromem(main_gui,sizeof(MAIN_GUI));
	//patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
	main_gui->gui.canvas=(void *)(&Canvas);
	main_gui->gui.flag30=2;
	main_gui->gui.methods=(void *)gui_methods;
	main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
	csm->csm.state=0;
	csm->csm.unk1=0;
	csm->gui_id=CreateGUI(main_gui);
	MAINGUI_ID=csm->gui_id;
}


void maincsm_onclose(CSM_RAM *csm)
{

	SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{

	return(1);
}

const struct
{
	CSM_DESC maincsm;
	WSHDR maincsm_name;
} MAINCSM =
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
	
		
		wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"install");
	
}
ZIPINF zi2;
int main(char *exename, char *fname)
{
  ZIPINF* pzi = &zi2;
  OpenZip(pzi,"0:\\1.zip");
	
	char dummy[sizeof(MAIN_CSM)];
	MAINCSM_ID = CreateCSM(&MAINCSM.maincsm, dummy, 0);
	UpdateCSMname();
	return 0;
}
