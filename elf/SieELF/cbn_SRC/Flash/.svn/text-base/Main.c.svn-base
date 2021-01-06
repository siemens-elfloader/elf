#include "E:\ARM\swilib.h"

void Exit(void){
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

int fwrite32(int fh, void *buf, int len, unsigned int *err){
  int clen, rlen, total=0;
  while(len){
  if (len>16384) clen=16384; else clen=len;
  total+=(rlen=fwrite(fh, buf, clen, err));
  if (rlen!=clen) break;
  buf=(char*)buf+rlen;
  len-=clen;
  }return(total);
}

int getval(char *s){
  int val=0;
  --s;
  while(*++s && *s!='-'){
    if(*s>='0' && *s<='9') val=(val<<4)+*s-'0';
    else if((*s|=0x20)>='a' && *s<='f') val=(val<<4)+*s-'a'+10;
    else break;
  }
  return val;
}

int main(char *exename, char *fname){
  unsigned int err;
  int f, from, size;
  char *s, tmp[128];
  if(fname && (f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    s=fname+strlen(fname);
    while(*--s!='\\');
    from=getval(++s);
    while(*++s && *s!='-');
    if(*s && (size=getval(s+1))){
      fwrite32(f,(char*)0xA0000000+from,size,&err);
      sprintf(tmp,"%X-%X\nсохранен в файл",from,size);
      ShowMSG(1,(int)tmp);
    }fclose(f,&err);
  }
  SUBPROC((void *)Exit);
  return (0);
}
