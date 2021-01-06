#ifndef _MAIN_H_
  #define _MAIN_H_


int CreateMenuFindPlaylist();
void Spysok();
void Play(char *fname);
static const char pt[]="%t";
static const char pp[]="";
static const char p_i[]="%i";
static const char pp_s[]=" %s";
void CLOSECURENTCSM();
int main(char *exename, char *fname);
void UpdateCSMname(void);
int IsFile(char *name);
void Play_PauseResume();
void PlayNext();
void VolumeMute();
void VolumeDown();
void VolumeUp();
void Message(char *text);
void SavePlaylist(void);
void WhatToDo(int param);
int strcmp_nocase(const char *s1,const char *s2);
typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;
void onCreate2(MAIN_GUI *data, void *(*malloc_adr)(int));
void onClose2(MAIN_GUI *data, void (*mfree_adr)(void *));
void onFocus2(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *));
void onUnfocus2(MAIN_GUI *data, void (*mfree_adr)(void *));
#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *));
#else
extern void kill_data(void *p, void (*func_p)(void *));
#endif
int method(void);
char *GetFon();
int GetKatalogfontcolour();
int GetKatalogbackgroundcolour();
void findlisttime(void);
#endif
