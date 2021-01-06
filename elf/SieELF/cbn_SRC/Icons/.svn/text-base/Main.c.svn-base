
// ICONS
// Создает кеш иконок для эльфа Windows

//#define NEWSGOLD //это Должно быть для любых телефонов
#include "..\swilib.h" // Главная библ. - берем ее из др.примеров

int f; //outfile
char filename[128], *file, *ptr, *SGOLD2;

char ext[2048], *extp;  //по 8 байт на заг-к = имена расширений


void ElfKiller(void){
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

void make(){ // картинку из filename
  char *bmp;
  int i;
  if(!(bmp=loadgraph(filename))) return;
  if(*(long*)bmp!=0x200020){ mfree(bmp); return;} //32x32 only!
  memcpy(extp,ptr,strlen(ptr)-4); // копируем имя расш-я
  for(i=0;i<7;i++,extp++) if(*extp>=0x40 && *extp<0x5b) *extp|=0x20;
  *extp++=0;
  fwrite(f,bmp+4,32*32*2,&err);//2 for highcolor
  mfree(bmp);
}

int main(char *exename, char *fname){
  static DIR_ENTRY dee;
  int off=0;
  extp=ext;
  if(SGOLD2=(char*)malloc(2500000)) mfree(SGOLD2); //проверка SGOLD2
  strcpy(filename,exename);
  strcpy(file=strrchr(filename,'\\')+1,"win386.swp");
do{
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) break;
  fwrite(f,&off,4,&err); //заголовок 0
  strcpy(file,"icons\\*.bmp");
  ptr=file+6;
  if(FindFirstFile(&dee,filename,&err)){
    do{
      strcpy(ptr,SGOLD2?dee.file_name:((char*)&dee+169));
      make();
    }while(FindNextFile(&dee,&err));
  }
  FindClose(&dee,&err); 
  off=lseek(f,0,1,&err,&err); //тек. позиция
  fwrite(f,ext,extp-ext+8,&err); //пишем список имен в конец
  lseek(f,0,0,&err,&err); //в начало
  fwrite(f,&off,4,&err); //заголовок = смещение списка
  fclose(f,&err);
}while(0);
 SUBPROC((void *)ElfKiller);
 return 0;
}
