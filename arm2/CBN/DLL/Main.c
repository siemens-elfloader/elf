
// DLL подзагрузка
// Формируются на компе elf2dll
// Содержат код + \0 + настр. таблица + exec смещение + выделить памяти всего

#include "..\swilib.h"

typedef long Elf(char*, void*, void*, void*);

void Killer(void){
  extern void *ELF_BEGIN;
  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

int rundll(char *exename, void *p1, void *p2, void *p3){
    int f, l, size, msize, exoff;
    unsigned int err;
    char *mem;
    long *tab;
    if((f=fopen(exename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 1;
    if((l=lseek(f,0,2,&err,&err))<16) return 2;
    lseek(f,l-4,0,&err,&err);
    fread(f,&size,4,&err);
    lseek(f,0,0,&err,&err);
    //if(size<l-4) return 3;
    msize=(size>l)?size:l;
    if(!(mem=(char*)malloc(msize))) return 4;
    zeromem(mem,msize);
    fread(f,mem,msize,&err);
    fclose(f,&err);
    tab=(long*)(mem+l);
    *--tab=0;
    exoff=*--tab;
    *tab=0;
    while(*--tab);
    while(*++tab){
      *(long*)(mem+*tab)+=(long)mem;
      *tab=0;
    }
    //zeromem(tab,mem+size-(char*)tab);
    ((Elf*)(mem+exoff))(exename,p1,p2,p3);
    mfree(mem);
  return 0;
}


int main(char *exename, char *fname){
  strcpy(exename+strlen(exename)-3,"dll");
  if(rundll(exename,fname,0,0)) ShowMSG(1,(int)"Ошибка запуска DLL");
  SUBPROC((void *)Killer);
 return 0;
}
