
// Adinf - антивирус - следит за размерами всех эльфов
// Функция поиска - составляет список всех файлов в папке и подпапках 3-его уровня

#include "..\swilib.h" // Главная библ. - берем ее из др.примеров

const char zbin[]="4:"; //BIN!!!!!!!!
const char extelf[]="elf", extlst[]="lst", extsum[]="chk", extlog[]="txt";

unsigned int err=0;
int loadfilesize=0;
void *SG=0;
char *ext;

#define virwarning 5
#define maxlevel 7
DIR_ENTRY de[maxlevel], dee;
char tmp[maxlevel][256], temp[256], name[256], *etemp, *ename;
#define listsize 32*1024
char list[listsize], *lend=list; //список эльфов

int filesize[1024]; //размер эльфов

char log[4096], *logend=log; //лог файл

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

int savefile(char *fname, char *buf, int size){
  int f,i;
  if((f=fopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 0;
  i=fwrite(f,buf,size,&err); 
  fclose(f,&err); 
  return i;
}

char *loadfile(char *filename){ // Загрузить файл, распак-ть
  int f; unsigned int err;  char *buf=0;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    if(loadfilesize=lseek(f,0,2,&err,&err)){
      buf=(char*)malloc(loadfilesize);
      lseek(f,0,0,&err,&err);
      if(fread32(f,buf,loadfilesize,&err)!=loadfilesize){ mfree(buf); buf=0;}
    } fclose(f,&err);
#ifdef UNPACK
    extern char *un7z(char *buf);
    extern char *unrar(char *buf);
    extern char *unzip(char *buf);
    if(buf && loadfilesize>4){
#ifndef NORAR
      if(*(int *)buf=='!raR') buf=unrar(buf); //unrar
      else
#endif      
#ifndef NOZIP
      if(*(int*)buf==0x4034b50) buf=unzip(buf); //unzip
      else
#endif
#ifndef NO7Z      
      if(*(short*)buf=='z7') buf=un7z(buf); //un7z
#endif
     ;      
    }
#endif      
  } return buf;
}


void Killer(void){
extern void *ELF_BEGIN;
((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}

inline void ex(char *exename, char *fname){ //fname-параметр (имя файла), передаваемый в эльф 
  WSHDR *ws=AllocWS(128); 
  str_2ws(ws,exename,strlen(exename)+1); 
  ExecuteFile(ws,0,fname); 
  FreeWS(ws);
} 

int fnd(char *s, char *what){
  int i=0;
  while(*s){
    if(!strcmp(s,what)) return i;
    s+=strlen(s)+1;
    ++i;
  }
  return -1;
}


int main(char *exename, char *fname){
int i,n=0,f, cnt=0,j=0;
char *names, *s;
int *sizes;

TDate date;
TTime time;
GetDateTime(&date,&time);

ext=strrchr(exename,'.')+1;
if(SG=malloc(2500000)) mfree(SG); //S75 
  find(0, (char*)zbin, (char*)extelf);
  *(char*)zbin='0';
  find(0, (char*)zbin, (char*)extelf);
  //получаем длину
  s=list;
  while(s<lend){
    if((f=fopen(s,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
      filesize[n++]=lseek(f,0,2,&err,&err);
      fclose(f,&err);
    }else filesize[n++]=-1;
    s+=strlen(s)+1;
  }
  sprintf(log,"\r\nAdinf 0.2 (c)bn\nДата проверки: %d.%02d.%d  %d:%02d\r\n",
          date.day,date.month,date.year, time.hour,time.min);
  logend=log+strlen(log);
  //старые данные
  strcpy(ext,extlst);
  names=loadfile(exename);
  strcpy(ext,extsum);
  sizes=(int*)loadfile(exename);
  if(names && sizes){  //проверяем    
    s=list;
    while(s<lend){
      if((i=fnd(names,s))!=-1){ //найден = уже был
        if(filesize[j]!=sizes[i]){
          sprintf(logend,"Изменился размер: %s на %d байт\r\n",s,filesize[i]-sizes[i]);
          logend+=strlen(logend);
          ++cnt;
        }
      }else{
        sprintf(logend,"Новый эльф: %s\r\n",s);
        logend+=strlen(logend);
      }
      s+=strlen(s)+1;
      ++j;
    }
  }else{ strcat(log,"Базы Adinf созданы\r\n"); goto lll;}
  if(cnt>=virwarning){
    sprintf(logend,"ИЗМЕНЕНО %d эльфов! Возможен ВИРУС!!! %d\r\n",cnt);
    logend+=strlen(logend);
  }else if(!cnt){
    logend+=strlen(logend);
    sprintf(logend,"Изменений нет.\r\n");
    logend+=strlen(logend);
  }
lll:  
  if(names) mfree(names);
  if(sizes) mfree(sizes);
  //сохраняем новые данные
  strcpy(ext,extlst);
  savefile(exename,list,lend-list+2);
  strcpy(ext,extsum);
  savefile(exename,(char*)filesize,n*4);
  strcpy(ext,extlog);
  logend=logend+strlen(logend);
  if((f=fopen(exename,A_ReadWrite+A_BIN+A_Append+A_Create,P_READ+P_WRITE,&err))!=-1){
    lseek(f,0,2,&err,&err);
    fwrite(f,log,logend-log,&err); 
    fclose(f,&err); 
  }
  ShowMSG(1,(cnt>=virwarning)?((int)"ВНИМАНИЕ!ВИРУС!!!Смотри файл Adinf.txt"):((int)"Смотри файл Adinf.txt"));  
  SUBPROC((void *)Killer);
  return 0;
}
