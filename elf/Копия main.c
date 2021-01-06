#include "G:\Iar\lib\swilib.h"

const int minus11=-11;

unsigned short maincsm_name_body[140];

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

int flag=0;


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

void printkn(int kn)
{
  DrawRoundedFrame(0,0, ScreenW()-1, ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  WSHDR *ws = AllocWS(256);
  WSHDR *wt = AllocWS(256);
  WSHDR *wu = AllocWS(256);  
  
  wsprintf(wu, "KeyTest. (c) feanor.");
  wsprintf(ws, "%t %d","Код клавиши (DEC)",kn);
  wsprintf(wt, "%t %X","Код клавиши (HEX)",kn);  

  DrawString(wu,3,5,119,20,8,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1)); 
  DrawString(ws,3,20,119,35,8,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1)); 
  DrawString(wt,3,35,119,50,8,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1)); 
  
  FreeWS(ws);
  FreeWS(wt);
  FreeWS(wu);
}
void OnRedraw(MAIN_GUI *data)
{  

 DrawRoundedFrame(0,0, ScreenW()-1, ScreenH()-1,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
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
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case 0x00: {printkn(0);}      break;
    case 0x01: {printkn(1);}      break;
    case 0x02: {printkn(2);}      break;
    case 0x03: {printkn(3);}      break; 
    case 0x04: {printkn(4);}      break;
    case 0x05: {printkn(5);}      break;
    case 0x06: {printkn(6);}      break;
    case 0x07: {printkn(7);}      break;
    case 0x08: {printkn(8);}      break;
    case 0x09: {printkn(9);}      break;
    case 0x0A: {printkn(10);}     break;
    case 0x0B: {printkn(11);}     break;
    case 0x0C: { if (flag==0) { flag=1; printkn(12);} else {return (1);};}     break;
    case 0x0D: {printkn(13);}     break;
    case 0x0E: {printkn(14);}     break;
    case 0x0F: {printkn(15);}     break;
    case 0x10: {printkn(16);}     break;
    case 0x11: {printkn(17);}     break;
    case 0x12: {printkn(18);}     break;
    case 0x13: {printkn(19);}     break; 
    case 0x14: {printkn(20);}     break;
    case 0x15: {printkn(21);}     break;
    case 0x16: {printkn(22);}     break;
    case 0x17: {printkn(23);}     break;
    case 0x18: {printkn(24);}     break;
    case 0x19: {printkn(25);}     break;
    case 0x1A: {printkn(26);}     break;
    case 0x1B: {printkn(27);}     break;
    case 0x1C: {printkn(28);}     break;
    case 0x1D: {printkn(29);}     break;
    case 0x1E: {printkn(30);}     break;
    case 0x1F: {printkn(31);}     break;
    case 0x20: {printkn(32);}     break;
    case 0x21: {printkn(33);}     break;
    case 0x22: {printkn(34);}     break;
    case 0x23: {printkn(35);}     break; 
    case 0x24: {printkn(36);}     break;
    case 0x25: {printkn(37);}     break;
    case 0x26: {printkn(38);}     break;
    case 0x27: {printkn(39);}     break;
    case 0x28: {printkn(40);}     break;
    case 0x29: {printkn(41);}     break;
    case 0x2A: {printkn(42);}     break;
    case 0x2B: {printkn(43);}     break;
    case 0x2C: {printkn(44);}     break;
    case 0x2D: {printkn(45);}     break;
    case 0x2E: {printkn(46);}     break;
    case 0x2F: {printkn(47);}     break;
    case 0x30: {printkn(48);}     break;
    case 0x31: {printkn(49);}     break;
    case 0x32: {printkn(50);}     break;
    case 0x33: {printkn(51);}     break; 
    case 0x34: {printkn(52);}     break;
    case 0x35: {printkn(53);}     break;
    case 0x36: {printkn(54);}     break;
    case 0x37: {printkn(55);}     break;
    case 0x38: {printkn(56);}     break;
    case 0x39: {printkn(57);}     break;
    case 0x3A: {printkn(58);}     break;
    case 0x3B: {printkn(59);}     break;
    case 0x3C: {printkn(60);}     break;
    case 0x3D: {printkn(61);}     break;
    case 0x3E: {printkn(62);}     break;
    case 0x3F: {printkn(63);}     break;
    
 
    }
  }
  return(0);
}
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
extern void kill_data(void *p, void (*func_p)(void *));
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

const RECT Canvas={0,0,129,129};
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
  MAINGUI_ID=csm->gui_id;
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
  WSHDR *ws=AllocWS(256);
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"KeyTest");
  FreeWS(ws);
}


int main(char *exename, char *fname)
{
  char dummy[sizeof(MAIN_CSM)];
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  return 0;
}
