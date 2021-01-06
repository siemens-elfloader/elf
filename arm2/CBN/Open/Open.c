
// Open
// Аналог EXtd
// Запускает эльфы по расширению

#include "..\swilib.h"

void Killer(void){
  extern void *ELF_BEGIN;
//  if(task) mfree(task);
//  if(lnk) mfree(lnk);
  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}


void exec(char *exe, char *fname){
  char *s=exe;
  while(*++s && *s!=0xd);
  *s=0;
  WSHDR *ws=AllocWS(256);
  str_2ws(ws,exe,strlen(exe)+1);
  ExecuteFile(ws,0,fname);
  FreeWS(ws);
}

int main(char *exename, char *fname){
  char *lnk=0, *ext, *s, *ss, *def=0;
  int f=0,size;
  unsigned int err;
  do{
    if(!fname) break;
    memcpy(exename+strlen(exename)-3,"cfg",4);
    if((f=fopen(exename,A_ReadOnly+A_BIN,P_READ,&err))<0) break;
    if(!(size=lseek(f,0,2,&err,&err))) break;
    lseek(f,0,0,&err,&err);
    if(!(s=lnk=(char*)malloc(size+1))) break;
    if(fread(f,lnk,size,&err)!=size) break;
    lnk[size]=0;
    fclose(f,&err);
    f=0;
    ext=fname+strlen(fname);
    while(--ext>fname && *ext!='.') *ext|=0x20;
    if(*ext!='.') break;
    ++ext;
//    ss=ext++;
//    while(*++ss) *ss|=0x20;
    --s;
    do{
      while(*++s && *s==' ');
      if(*s!=0xd){
      if(*s=='*') def=s+2;
      else
      if((*s|0x20)==*ext){ // Проверяем далее
        ss=ext;
        while(*++s!=':' && *++ss && (*s|0x20)==*ss);
        if(*s==':' && !*++ss){
          def=s+1;
          break;
        }
      }
      while(*++s && *s!=0xd);
      if(!*s) break;
      }
      if(*++s!=0xa) --s;
    }while(*s);
  }while(0);
  //not found, default
  if(def) exec(def,fname);  
  if(f>0) fclose(f,&err);
  if(lnk) mfree(lnk);
//  ShowMSG(1,(int)"Ошибка в Open.ini файле!");
  SUBPROC((void *)Killer);
  return 0;
}
