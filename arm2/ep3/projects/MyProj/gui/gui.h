#include <swilib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" void kill_data(void *p, void (*func_p)(void *));


class MYGUI
{

   //---------------------------------//
    typedef struct
{
    CSM_RAM csm;
    int gui_id;
} MAIN_CSM;

typedef struct
{
    GUI gui;
    WSHDR *ws;
} MAIN_GUI;
//------------------------------//
private:
unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID;// = 0;
unsigned int MAINGUI_ID;// = 0;
int minus11;//=-11;
int my_csm_id;//=0;
char clrWhite[];//= {0xFF,0xFF,0xFF,0x64};
char clrBlack[];//= {0x00,0x00,0x00,0x64};
int scr_w,scr_h;
RECT Canvas;//= {0,0,0,0};
public:
//-----------------------//
void OnRedraw(MAIN_GUI *data);
void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int));
void onClose(MAIN_GUI *data, void (*mfree_adr)(void *));
void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *));
void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *));
int method8(void);
int method9(void);
int OnKey(MAIN_GUI *data, GUI_MSG *msg);
void maincsm_oncreate(CSM_RAM *data);
void ElfKiller(void);
void maincsm_onclose(CSM_RAM *csm);
int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg);
void UpdateCSMname(void);
MYGUI();
~MYGUI();
};
