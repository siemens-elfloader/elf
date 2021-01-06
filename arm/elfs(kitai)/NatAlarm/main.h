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

extern unsigned long  strtoul (const char *nptr,char **endptr,int base);
#pragma inline
void patch_header(const HEADER_DESC* head)
{
  ((HEADER_DESC*)head)->rc.x=0;
  ((HEADER_DESC*)head)->rc.y=YDISP;
  ((HEADER_DESC*)head)->rc.x2=ScreenW()-1;
  ((HEADER_DESC*)head)->rc.y2=HeaderH()+YDISP-1;
}



int IsIdle(void)
{ 
  void *icsm=FindCSMbyID(CSM_root()->idle_id); 
  if (IsGuiOnTop(((int*)icsm)[DISPLACE_OF_IDLEGUI_ID/4 ])) return(1); 
  else return(0); 
}


#endif
