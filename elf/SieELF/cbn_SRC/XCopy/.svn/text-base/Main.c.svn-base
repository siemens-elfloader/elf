
// XCopy создать папку и переместить в нее все файлы
// из папки откуда вызвался fname
// в fname 1 строка - куда копировать (оканч. на '\\')

#include "E:\ARM\swilib.h"

#define bufsize 128
char buf[bufsize];
char path[128];

#define listsize 8192
char listb[listsize], *list=listb;


void ElfKiller(void){
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void move(char *source, char *dest){
  int f=-1,size;
  unsigned int err;
  char *mem=0;
  do{
    if((f=fopen(source,A_ReadOnly+A_BIN,P_READ,&err))==-1) break;
    size=lseek(f,0,2,&err,&err);
    lseek(f,0,0,&err,&err);
    if(!(mem=(char*)malloc(size+1))) break;
    if(fread(f,mem,size,&err)!=size) break;
    fclose(f,&err);
    if((f=fopen(dest,A_WriteOnly+A_BIN+A_Create,P_WRITE,&err))==-1) break;    
    fwrite(f,mem,size,&err);
  }while(0);
  if(mem) mfree(mem);
  if(f>0) fclose(f,&err);
}

void addname(char *name){
  strcpy(list,name);
  list+=strlen(name)+1;
}

void doit(){
  char *ptr;
  list=listb;
  while(*list){
    move(list, ptr=list+strlen(list)+1);
    list=ptr+strlen(ptr)+1;
  }
}


int main(char *exename, char *fname){
  static DIR_ENTRY de;
  char *ptr;
  int f, i;
  unsigned int err;
  if(fname){
  if((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) goto exit;
  i=fread(f,buf,bufsize,&err);
  fclose(f,&err);
  if(buf[1]!=':' || buf[i-1]!='\\') goto exit;
  buf[i-1]=0;
  mkdir(buf,&err);
//  if(err) goto exit;
  buf[i-1]='\\';
  //найти все файлы и скопировать
  strcpy(path,fname);
  ptr=path+strlen(path);
  while(*--ptr!='\\');
  memcpy(++ptr,"*.*",4);
  if(FindFirstFile(&de,path,&err)){
    do{
      strcpy(ptr,de.file_name);
      strcpy(buf+i,de.file_name);
      addname(path);
      addname(buf); //fmove(path,buf);//fmove
    }while(FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  doit();
  buf[i]=0;
  strcpy(path,"Установлен в ");
  strcat(path,buf);  
  ShowMSG(1,(int)path);
  }
exit:
 SUBPROC((void *)ElfKiller);
 return (0);
}  


/*
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

//работает
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
