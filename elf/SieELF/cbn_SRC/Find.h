
//find.h
//Поиск файлов 0.1

#include "..\swilib.h"


//extern void find( int level, char *s, char *ext); // Найти все пути в s (рекурсивно)
//extern char *lgetn(int num); //получить имя элемента N
//extern int lmax(); //кол-во эл-в
//extern void lreset(); //очистить список

//ВЫЗОВ:  
//const char zbin[]="4:\\ZBin"; //BIN!!!!!!!!
//const char sbin[]="bin"
//  find(0, (char*)zbin, (char*)self); "4:","elf"
//  *(char*)zbin='0';
//  find(0, (char*)zbin, (char*)self);

//#define DOS //желательно
//#define debug //ОТЛАДКА
#define listsize 16*1024
char list[listsize], *lend=list;
#define maxlevel 4
DIR_ENTRY de[maxlevel], dee;
char tmp[maxlevel][256], temp[256], name[256], *etemp, *ename;
extern unsigned int err=0;
int linit=0;
void *SG=0;

inline void un(){ // Занесение имени файла temp в список
  int i;
  if(lend+(i=strlen(temp)+1)<list+listsize-3){
    memcpy(lend,temp,i);
    lend+=i;
  }
}

inline void extn(char *dir, char *ext){ // Найти все эльфы в dir (использ.temp)
  strcpy(temp,dir);
  strcat(temp,"\\*.");  //*.
  strcat(temp,ext);
  if (FindFirstFile(&dee,temp,&err)){
    do{
      strcpy(strrchr(temp,'\\')+1,SG?dee.file_name:((char*)&dee+169));
      un(); //занести в список
    }while(FindNextFile(&dee,&err));
  }
  FindClose(&dee,&err); 
}

void find( int level, char *s, char *ext){ // Найти все пути в s (рекурсивно)
  char *path;
  if(!linit){
    if(SG=malloc(2500000)) mfree(SG); //S75 
    linit=1;
  }
  if(level<maxlevel){
    strcpy(path=tmp[level],s);
    extn(path,ext);
    strcat(path,"\\*.*");
    if(FindFirstFile(&de[level],path,&err)){
      do{
      strcpy(strrchr(path,'\\')+1,SG?de[level].file_name:((char*)&de[level]+169));
      if(*((char*)&de[level]+(SG?44:14))&0x10) //44 for newsgold
      //if(isdir(path,&err))
        find(level+1, path, ext);
    }while(FindNextFile(&de[level],&err));
    }
    FindClose(&de[level],&err);
  }
}

#ifdef debug
int savefile(char *fname, char *buf, int size){
  int f,i;
  if((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 0;
  i=fwrite(f,buf,size,&err); 
  fclose(f,&err); 
  return i;
}
//  strcpy(strrchr(exename,'.'),".lst");
//  savefile(exename,list,lend-list);
#endif

void lreset(){ //очистить список
  lend=list;
}

int lmax(){ //кол-во эл-в
  int i=0;
  char *s=list;
  while(s<lend){
    s+=strlen(s)+1;
    ++i;
  }
  return i;
}

char *lgetn(int num){ //получить имя элемента N
  char *s=list;
  while(s<lend && --num>=0){
//    strcpy(temp,s);
//    strcpy(name,s);
    s+=strlen(s)+1;
  }
  return s;
}
