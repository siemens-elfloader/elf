#ifndef _MAIN_H_
#define _MAIN_H_
typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
}MAIN_GUI;

typedef struct
{
  void *next;
  char *filename;
  char *name;
  char *text;
  int item;
  int FNAME;
  int is_first;
}MNU;

typedef struct
{
  void *next;
  char *name;
  int item;
}MNU_dir;

int DrawText(int i,MNU *fl);
int create();
void SaveMark(char *name,char *text);

#pragma inline
void patch_header(HEADER_DESC* head)
{ 
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}

#define Xpluss 4

#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=Xpluss;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1-Xpluss;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}

#endif
