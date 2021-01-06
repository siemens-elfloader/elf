
// Test для работы с MMC
#include "E:\ARM\swilib.h"

void ElfKiller(void)
{
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

int main(char *exename, char *fname){
  int n=0;
  if(fname){
    fname+=strlen(fname);
    while(*--fname!='\\');
    while(*++fname>='0' && *fname<='9'){
      n=n*10+*fname -'0'; 
    }
    PlaySound(1,0,0,n,0) ;
  }
  SUBPROC((void *)ElfKiller);
 return (0);
}  



int main2(char *exename, char *fname)
{
  char out[3]="0";
  unsigned int err;
  int f=-1, size=0;
  char *buf=0, *file;
  do{
    if(!fname){*out='1'; break;}
    if((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1){*out='2'; break;}//error 0 here
    file=fname+strlen(fname); 
    while(*--file!='.');
    *file=0;
    size=lseek(f,0,2,&err,&err);
    if(!size){*out='3'; break;}
    if(!(buf=malloc(size))){*out='4'; break;}
    lseek(f,0,0,&err,&err);
    if(fread(f,buf,size,&err)!=size){ *out='5'; break;}
    fclose(f,&err);
    f=-1;
    if((f=fopen(fname,A_WriteOnly+A_BIN+A_Create,P_WRITE,&err))==-1){*out='6'; break;}
//    lseek(f,0,0,&err,&err);
    fwrite(f,buf,size,&err);
    *out='8'; //all ok
 }while(0);
 if(buf) mfree(buf);
 if(f!=-1) fclose(f,&err);
////log
 if((f=fopen("0:\\ZBin\\log",A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))!=-1){
   fwrite(f,out,1,&err);
   fclose(f,&err);
 }
 SUBPROC((void *)ElfKiller);
 return (0);
}

/*работает
int main(char *exename, char *fname)
{
  char out[3]="0";
  unsigned int err;
  int f=-1, size=0;
  char *buf=0, *file;
  do{
    if(!fname){*out='1'; break;}
    if((f=fopen(fname,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))==-1)
      {*out='9'; break;}
//    if((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1){*out='2'; break;}//error 0 here
    file=fname+strlen(fname);
    while(*--file!='.');
    *file=0;
    size=lseek(f,0,2,&err,&err);
    if(!size){*out='3'; break;}
    if(!(buf=malloc(size))){*out='4'; break;}
    lseek(f,0,0,&err,&err);
    if(fread(f,buf,size,&err)!=size){ *out='5'; break;}
    fclose(f,&err);
    f=-1;
    if((f=fopen(fname,A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))==-1){*out='6'; break;}
    lseek(f,0,0,&err,&err);
    fwrite(f,buf,size,&err);
    *out='8'; //all ok
 }while(0);
 if(buf) mfree(buf);
 if(f!=-1) fclose(f,&err);
////log
 if((f=fopen("0:\\ZBin\\log",A_ReadWrite+A_BIN+A_Create,P_READ+P_WRITE,&err))!=-1){
   fwrite(f,out,1,&err);
   fclose(f,&err);
 }
 SUBPROC((void *)ElfKiller);
 return (0);
}
*/
