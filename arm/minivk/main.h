#include "..\inc\swilib.h"

typedef struct
{
  CSM_RAM csm;
}MAIN_CSM;

static const int minus11=-11;
static unsigned short maincsm_name_body[140];

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM_GUI;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;
extern void kill_data(void *p, void (*func_p)(void *));
static CSM_RAM *under_idle;
extern int gui_mode;
static int KEY_START='0';
extern  char logmsg[256];
