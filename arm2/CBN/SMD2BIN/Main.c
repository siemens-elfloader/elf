
//smd2bin converter elf 0.1
#include "..\swilib.h"

#define bsize 0x4000
#define hsize 0x2000

char block[bsize], buf[bsize];

const char *errors[]={
  "OK\0",
  "Щелкните на .SMD файл!\0",
  "Не могу открыть файл!\0",
  "Не .SMD файл!\0",
  "Не могу создать файл!\0"
};

void ElfKiller(void){
  extern void *ELF_BEGIN;
  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

int smd2bin(char *fname){
  unsigned int err;
  int f,ff,i;
  char *ptr;
  if(fname[1]!=':') return 1;
  if((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 2;
  if(!(((lseek(f,0,2,&err,&err)) / 512) & 1)){ fclose(f,&err); return 3;}
  strcpy(strrchr(fname,'.'),".bin");
  if((ff=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1){ fclose(f,&err); return 4;}
  lseek(f,512,0,&err,&err);
  while(fread(f,block,bsize,&err)>0){
    for(i = 0, ptr=buf; i < hsize; i ++){
      *ptr++=block[hsize+i];
      *ptr++=block[i];
    }
    fwrite(ff,buf,bsize,&err);
  }
  fclose(f,&err);
  fclose(ff,&err);
/*   for(ptr=cart_rom; ptr<cart_rom+cartromsize; ){
        memcpy(block,ptr,0x4000);
        for(i = 0; i < 0x2000; i ++){
          *ptr++=block[0x2000+i];
          *ptr++=block[0x0000+i];
        }
      }*/
  return 0;
}

int main(char *exename, char *fname){
  ShowMSG(1,(int)errors[smd2bin(fname)]);
  SUBPROC((void *)ElfKiller);
  return 0;
}

