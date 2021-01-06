
//Command.c Командный интерпретатор BAT файлов

#include "..\swilib.h"
const char Title[]="\r\n\r\nMS-DOS 0.4 (c)bn";
#define conbufsize 2048
char conbuf[conbufsize], *conend; // врем. буфер

#define MAXPATH 256
char con[MAXPATH]; // Строка для вывода в sprintf()
char path[MAXPATH], spath[MAXPATH], curdir[MAXPATH], temp[MAXPATH], ar1[MAXPATH], ar2[MAXPATH];
#define maxset 256
char set[maxset], *setend=set; //окружение

// аргументы ком. строки
#define maxargv 16
char *argvv[maxargv], **argv;
int argc, fcon; //console
//char *file;

void *SG=0;
char echooff=0, exit=0;

const char link[]="4:\\ZBin\\Link.elf";
const char eline[]="\\", ezap[]=";";
// ОТКРЫТЬ при старте в onstart()
// ЗАВЕРШАТЬ выгрузкой буфера по команде
// Переход на след. строку
//#define crlf {*conend++=0xd;*conend++=0xa;}
// Принудительно сбросить буфер
#define flush {fwrite(fcon,conbuf,conend-conbuf,&err);*(conend=conbuf)=0;}

const char *cext[]={".bat",".lnk",".elf",".dll",0};

struct cmdst{ //команды
  const char *name; //название
  int (*func)(void); //ф-я
} *cmd;


enum {ok, error, errcommand, errpath, errarg, errmemory, erropen, errcreate, erroption
};

const char *msg[]={
  "OK",
  "Ошибка",  
  "Неправильная команда или имя файла",
  "Неправильный путь",
  "Недостаточно аргументов",
  "Недостаточно памяти",
  "Ошибка открытия файла",
  "Ошибка создания файла",
  "Неверная опция",
};

int striicmp(const char *s, char *ss){ //т.к. stricmp глючит!!!
  do{
    if((*s|0x20)-(*ss|0x20)) return 1;
    ++s; ++ss;
  }while(*s);
  return 0;
}



int execbat(char *fname); // Выполнить bat файд
  
void print(const char *con){ // Напечатать строку con
  if(fcon>0 && *con){
    //crlf
    if(conend+strlen(con)>=conbuf+conbufsize-4) flush
    strcpy(conend, con);
    conend+=strlen(con);
    //*con=0;
  }
}

inline void cr(){
  *conend++=0xd; *conend++=0xa;
}

void arg(char *s){ // Получить аргументы argc, argv[]
  argc=0;
  do{
    argvv[argc++]=s;
    while(*++s && *s!=' ');
    if(!*s) break;
    *s=0;
    while(*++s && *s==' ');
  }while(*s && argc<maxargv-1);
  argvv[argc]=0;
  argv=argvv;
}

void Killer(void){
  extern void *ELF_BEGIN;
  extern void kill_data(void *p, void (*func_p)(void *));
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

typedef long Elf(char*, void*, void*, void*);

int rundll(char *exename, void *fc, void *curdir, void *arrgc, void *arrgv){
    int f, l, size, msize, exoff;
    unsigned int err;
    char *mem;
    long *tab;
    if((f=fopen(exename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return erropen;
    if((l=lseek(f,0,2,&err,&err))<16) return error;
    lseek(f,l-4,0,&err,&err);
    fread(f,&size,4,&err);
    lseek(f,0,0,&err,&err);
    //if(size<l-4) return 3;
    msize=(size>l)?size:l;
    if(!(mem=(char*)malloc(msize))) return errmemory;
    zeromem(mem,msize);
    fread(f,mem,msize,&err);
    fclose(f,&err);
    tab=(long*)(mem+l);
    *--tab=0;
    exoff=*--tab;
    *tab=0;
    while(*--tab);
    while(*++tab){
      *(long*)(mem+*tab)+=(long)mem;
      *tab=0;
    }
    l=((Elf*)(mem+exoff))(fc,curdir,arrgc,arrgv);
    mfree(mem);
  return ok;
}


int isfile(char *fname){ //есть ли файл?  
  unsigned char at; 
  GetFileAttrib(fname,&at,&err); //можно и по др. определять наличие ф-а
  return !err;
}

void execelf(char *exename, char *fname){ //запустить эльф
 WSHDR *ws=AllocWS(256);
 str_2ws(ws,exename,strlen(exename)+1);
 ExecuteFile(ws,0,fname); 
 FreeWS(ws);
}

/////////
#include "find.h"
#include "function.h"
///////

int findall(){//char ext){ //ищет файл argv[0] по temp
  char *ptr, **ext=(char**)cext;
  strcat(temp,*argvv);
  if(strrchr(temp,'.'))
    return isfile(temp);
  ptr=temp+strlen(temp);
  while(*ext){
    strcpy(ptr,*ext++);
    if(isfile(temp)) return 1;
  }
  return 0;
}

int gettype(char *s){
  char **ss=(char**)cext;
  if(!(s=strrchr(s,'.'))) return 0;
  while(*ss){
    if(!striicmp(*ss++,s)) return ss-(char**)cext;
  }
  return 0;
}

int command(){ //выполнить команду argv[]
  char *s=*argvv, *ss, *sss;
  //ищем внутренние команды
  for(cmd=commands;cmd->name;cmd++){
    if(!striicmp(cmd->name,s)){
      cr(); return cmd->func();
    }
  }
  if(s[1]==':'){ //задан полный путь
    if(isfile(s)){ 
      strcpy(temp,s); goto lexec; //temp!!!
    }
    if(strrchr(s,'.')) return errcommand;
    *(ss=strrchr(s,'\\'))=0;
    strcpy(spath,s);
    strcpy(s,ss+1);
  }else{ //подготовить путь
    strcpy(spath,curdir);
    strcat(spath,";");
    strcat(spath,path);
  }
  //ищем внешнюю команду в SPATH (bat,lnk,elf,dll)
  ss=spath;
  while(*ss){
    while(*ss==' ') ++ss;
    sss=ss;
    while(*++sss && *sss!=';');
    memcpy(temp,ss,sss-ss);
    temp[sss-ss]=0;
    if(temp[sss-ss-1]!='\\') strcat(temp,eline);
    if(findall()){
lexec:
    switch(gettype(temp)){
    case 1: //bat
      execbat(temp); break; //error recurse????!!!!
    case 2: //lnk
      if(!isfile((char*)link)) *((char*)link)='0';
      execelf((char*)link,temp); break;//??
    case 3: //elf
      execelf(temp,argv[1]); break;
    case 4: //dll
      flush
      rundll(temp,(void*)fcon,curdir,(void*)argc,argvv); break;
    default: 
      return errcommand;
    }
    return 0;
    }
    if(!*sss) break;
    ss=sss+1;
  }
  return errcommand;
}


int exec(char *s){  // Выполнить команду
  while(*s==' ') ++s;
  if(!*s) return 0; //empty
  if(!echooff){ cr(); print(s);}
  arg(s); //получ. argc, argv[]
  return command(); //выполнить команду argv[]
}

int execbat(char *fname){ // Выполнить bat файд
  int i,f;
  char *buf, *s, *ss, c;
  if((f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) return erropen;
  if(!(i=lseek(f,0,2,&err,&err))
     || !(s=buf=(char*)malloc(i+1))){ fclose(f,&err); return errmemory;}
  lseek(f,0,0,&err,&err);
  fread(f,buf,i,&err);
  buf[i]=0; //eof
  fclose(f,&err);
  //for() exec()
  do{
    ss=s;
    while(*s && *s!=0xd) ++s;
    c=*s; *s=0;
    if(i=exec(ss)){ cr(); print((char*)msg[i]);}
    if(!c) break;
    if(*++s==0xa) ++s;
  }while(*s);
  mfree(buf);
  return ok; 
}

int main(char *exename, char *fname){
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  if(SG=malloc(2500000)) mfree(SG); //S75 
  *(strrchr(exename,'\\')+1)=0;
  strcpy(path,exename);
  strcat(path,";4:\\ZBin\\;0:\\ZBin\\");
  if(fname[1]!=':'){ //no fname
    strcpy(curdir,exename);
  }else{    
    strcpy(curdir,fname);
    *(strrchr(curdir,'\\')+1)=0;
  }
  strcpy(temp,curdir);
  strcat(temp,"Console.txt");
  if((fcon=fopen(temp,A_ReadWrite+A_Append+A_Create,P_READ+P_WRITE,&err))>0)
    lseek(fcon,0,2,&err,&err); 
  conend=conbuf; 
  print(Title);
  sprintf(con,"\r\nДата: %d.%02d.%d  %d:%02d\n",
          date.day,date.month,date.year, time.hour,time.min);
  print(con);
  strcpy(temp,exename);
  strcat(temp,"autoexec.bat");
  execbat(temp);
  if(fname[1]==':'){
    execbat(fname);
  }
  if(fcon>0){ cr(); flush fclose(fcon,&err);}
  SUBPROC((void *)Killer); 
  return 0;
}
