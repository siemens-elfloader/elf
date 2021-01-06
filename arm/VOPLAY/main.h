#ifndef _MAIN_H_
  #define _MAIN_H_
void clear_cache();
void readskinparamsfromfile();
void WriteLastPlaylist();
int  CreateMenuFindPlaylist();
int  CreateMenuSkins();
void rereadskin();
void StopTMR(unsigned short s);
void EXT_REDRAW();
void Spysok();
void Play(char *fname);
static const char pt[]="%t";
static const char pp[]="";
static const char p_i[]="%i";
static const char pp_s[]=" %s";
static const char one_s[]="%s";
static const char perc2_d[]="%d";
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
extern const unsigned int STEP_REW;  
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
extern void kill_data(void *p, void (*func_p)(void *));
int method(void);
char *GetFon();
int GetKatalogfontcolour();
int GetKatalogbackgroundcolour();
int GetKatalogFont();
int GetKatalogXotstup();
void crtIMGHDR();
void delImghdr();
void findlisttime(void);
int my_keyhook(int submsg, int msg);
void findtegs();
#endif
