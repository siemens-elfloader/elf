#ifndef _MAIN_H_
  #define _MAIN_H_

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

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

int my_csm_id=0;


#endif
