/*
* amr2wav 
* 2011
*/


#include "..\inc\swilib.h"
#include "decode.c"

extern Word32 frame;
char *wav,*name;
GBSTMR tmr;
int seconds=0,font;
FSTATS fs;
unsigned int oldsize,rr;

void func()
{
    extern void kill_data(void *p, void (*func_p)(void *)), *ELF_BEGIN;
    extern int decodeOneAmrFile( char* AmrName , char* WavNAme );
    if( decodeOneAmrFile(  name , wav) ) ShowMSG(1,(int)"converted!");
    else  ShowMSG(1,(int)"error");
     GBS_DelTimer(&tmr);
     mfree(wav);
     mfree(name);
     if(isNewSGold()==2) DisableIconBar(0);

    SUBPROC((void *)kill_data,&ELF_BEGIN,(void (*)(void *))mfree_adr());
}


void DrawWindow()
{
  rr=fs.size/1024-oldsize;
  oldsize=fs.size/1024;
  if(isNewSGold()==2) DisableIconBar(2);
  GetFileStats(wav,&fs,0);
  seconds++;
  WSHDR *ws=AllocWS(128);
  int scr_w=ScreenW();
  int scr_h=ScreenH();
  DrawRoundedFrame(0,YDISP,scr_w-1,scr_h-1,0,0,0,GetPaletteAdrByColorIndex(4),GetPaletteAdrByColorIndex(1));
  wsprintf(ws, "Converting...\n%s -> %s\nframes:%ld %d kb\ntime:%d sec speed:%d kb/sec",name,wav,frame,fs.size/1024,seconds,rr);
  DrawString(ws,3,3+YDISP,scr_w-4,scr_h-4-GetFontYSIZE(FONT_MEDIUM_BOLD),
             font,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  FreeWS(ws);
  
  GBS_StartTimerProc(&tmr,216,DrawWindow);
}


int main(char *exename, char *fname)
 {
    if(isNewSGold()==2)font=9;else font=5;
    wav=malloc(strlen(fname)+5);
    strcpy(wav,fname);
    strcat(wav,".wav");
    name=malloc(strlen(fname)+1);
    strcpy(name,fname);
    DrawWindow();
    SUBPROC((void *)func);

    
    return 0;
 }
