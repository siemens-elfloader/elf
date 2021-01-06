#include "..\inc\swilib.h"

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

const int minus11=-11;
unsigned short maincsm_name_body[140];
void OnRedraw(MAIN_GUI *data)
{
}
extern void On();
extern void Off();
extern int stat;

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
 
#ifdef ELKA
  DisableIconBar(1);// если елка то отключим иконбар
#endif
   data->gui.state=1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// делаем все что надо при закрытии
void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  data->gui.state=0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// делаем все при развертывании таском
void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  data->gui.state=2;
  DisableIDLETMR();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char msgg[256];
// при нажатии клавиш
int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case  RIGHT_SOFT : return(1);   
    case '0':DisableIconBar(1);break;
    case '1':DisableIconBar(0);break;
    case '2':sprintf(msgg,"ss:%d",(char)0xA8D9EF33);ShowMSG(1,(int)msgg);break;
    }
  }
  return(0);
}





extern void kill_data(void *p, void (*func_p)(void *));
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
kill_data(data,mfree_adr);
}

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,	
  (void *)onCreate,	
  (void *)onClose,	
  (void *)onFocus,
  
  (void *)onUnfocus,
  (void *)OnKey,	
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,	
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,239,319};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
 // MAINGUI_ID=csm->gui_id;
}

void ElfKiller(void)
{
  extern void kill_data(void *p, void (*func_p)(void *));
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}
void maincsm_onclose(CSM_RAM *csm)
{
  SUBPROC((void *)ElfKiller);
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
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Test");// имя в менеджере задач
}
int main(char *exename, char *fname)
{
 MAIN_CSM main_csm;
  LockSched();
  UpdateCSMname();
  CreateCSM(&MAINCSM.maincsm,&main_csm,0);
  UnlockSched();
  return 0;
}
