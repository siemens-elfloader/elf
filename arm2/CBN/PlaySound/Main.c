
// Test для работы с MMC
#include "E:\ARM\swilib.h"

void Killer(void){
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

int main(char *exename, char *fname){
  SFO sfo={1,0,0,3};
  char *file;
  if(fname){
  file=fname+strlen(fname);
  while(*--file!='\\');
  WSHDR *ws1=AllocWS(256), *ws2=AllocWS(256);
  str_2ws(ws2,file+1,strlen(file));
  *file=0;
  str_2ws(ws1,fname,strlen(fname)+1);
  PlayFile(0xC,ws1,ws2,MMI_CEPID,0x167,&sfo);  //GBS_GetCurCepid()
  FreeWS(ws1);
  FreeWS(ws2);
  }
  SUBPROC((void *)Killer);
  return (0);
}  

