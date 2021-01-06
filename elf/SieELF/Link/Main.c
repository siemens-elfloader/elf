/*
(c) cbn
*/
// Link - загрузчик ярлыков
#include "..\inc\swilib.h"

#define lnksize 512
char lnk[512], *s, *exe, *img=0, *par=0;
int f;
unsigned int err;

extern void kill_data(void *p, void (*func_p)(void *));

void Exit(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int main(char *exename, char *fname)
{
  do
  {
   if(!fname) break;
   if((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) break;
   if(!fread(f,lnk,lnksize,&err)) break;
   fclose(f, &err);
   //exe
   s=exe=lnk;
   while(*++s && *s!=0xd && *s!=':');
   if(*s!=':') break;
   while(*++s && *s!=0xd);
   do
   {
     if(!*s) break;
     *s++=0;
     //img
     img=s+1;
     while(*++s && *s!=0xd && *s!=':');
     if(*s==':')
     { // Есть картинка
       while(*++s && *s!=0xd);
     }else img=0;
     if(!*s) break;
     *s++=0;
     //par
     par=s+1;
     while(*++s && *s!=0xd && *s!=':');
     if(*s==':')
     {
       while(*++s && *s!=0xd);
     }else par=0;
     *s=0;
   }while(0);
   //execute
   WSHDR *ws=AllocWS(256);
   str_2ws(ws,exe,strlen(exe)+1);
   ExecuteFile(ws,0,par);
   FreeWS(ws);
 }while(0);
 SUBPROC((void *)Exit);
 return (0);
}
