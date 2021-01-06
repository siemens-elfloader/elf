#include "../inc/swilib.h"
#include "main.h"
#include "cl_work.h"

//”ничтожить список
void LoadLocalCL(void){
 FSTATS stat;
 char fn[256];
 int f;
 unsigned int ul;
 int fsize;
 char *p,*s;
 char cn[64];
 unsigned int uin;

 strcpy(fn,TEMPLATES_PATH);
 strcat(fn,"\\local.cl");
 if (GetFileStats(fn,&stat,&ul)==-1) return;
 if ((fsize=stat.size)<=0) return;
 if ((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&ul))==-1) return;
 s=p=malloc(fsize+1);
 s[fread(f,p,fsize,&ul)]=0;
 fclose(f,&ul);
 while(*p!=0){
  char cc;
  while((cc=*p)!=';'){    //нах им€ группы
   if (cc==0) goto L_EOF;
   p++;
  }
  p++;
  uin=0;
  while((cc=*p)!=';'){   //uin
   if (cc==0) goto L_EOF;
   uin*=10;
   uin+=((*p++)-'0');
  }
  p++;
  char *c=cn;
  while((cc=*p)!=';'){   //nick
   if (cc==0) goto L_EOF;
   *c++=*p++;
  }
  *c=0;
  while(*p!=13 && *p!=10 && *p!=0) p++; //нах конец строки
  if (*p!=0) p++;
  if ((*p==13)||(*p==10)) p++;
  if (!FindContactByUin(uin)) AddContact(uin, cn, 0, 1);
 }
L_EOF:
 mfree(s);
}
