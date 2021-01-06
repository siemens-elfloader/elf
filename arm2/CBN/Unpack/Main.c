
#include "..\swilib.h"

void Killer(void){
  extern void *ELF_BEGIN;
  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

inline void execelf(char *exename, char *fname){ //fname-ןאנאלוענ (טלÿ פאיכא), ןונוהאגאולûי ג ‎כüפ 
  WSHDR *ws=AllocWS(256); 
  str_2ws(ws,exename,strlen(exename)+1); 
  ExecuteFile(ws,0,fname); 
  FreeWS(ws);
}

int main(char *exename, char *fname){
  int f,mag;
  unsigned int err;
  char *exec;
  do{
    if(!fname || fname[1]!=':' || (f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1  || fread(f,&mag,4,&err)!=4) break;
    fclose(f,&err);
    if(mag=='!raR')  exec="Unrar.elf";//unrar
      else
      if(mag==0x4034b50) exec="Unzip.elf"; //unzip
      else
        if((mag&0xffff)=='z7') exec="Un7z.elf"; //un7z
        else break;
      strcpy(strrchr(exename,'\\')+1,exec);
      //ShowMSG(1,(int)exename);
      execelf(exename,fname);
      //ShowMSG(1,(int)"OK");
   }while(0);
 SUBPROC((void *)Killer);
 return 0;
}
