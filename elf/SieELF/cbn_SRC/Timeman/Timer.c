
// Timer резидент
// Запускает др. процессы в нужное время

#include "..\swilib.h"

GBSTMR mytmr;
char first=0;

inline void *memset(void *mem, int val, int size){
  char *s=(char*)mem;
  while(--size>=0) *s++=(char)val;
  return mem;
}

char *lnk=0; //free
int maxtask;

struct taskst{    //задачи:
  char *exe;      //имя файла для запуска
  unsigned short used,     //сколько раз запускалось
        maxused,  //ск. всего нужно запускать
        interval, //интервал между запусками
        week;     //день недели 1-7 когда запускать
  short time;     //время последнего запуска
}*task=0; //free

char *mask;
// в данную минуту стартовать? (бит)     //все обнуляется если зап.нужн.к-во раз??
//180*maxtask    буфер путей

inline void everymin(int hm, int week){ // запустить все задачи во время hm
  int i;
  char *mm=mask;
  struct taskst *tt=task;
  for(i=0;i<maxtask;i++,mm+=180,tt++){
    if(mm[hm>>3] & (1<<(hm&7))){ //активирован
      if(hm-tt->time > tt->interval && tt->used < tt->maxused  && (!tt->week || (tt->week & (1<<week)))){
        tt->time=hm;
        ++tt->used;
        //execute tt->exe
        WSHDR *ws=AllocWS(256);
        //ShowMSG(1,(int)tt->exe);/////////
        str_2ws(ws,tt->exe,strlen(tt->exe)+1);
        ExecuteFile(ws,0,0);
        FreeWS(ws);
//        SetIllumination(0,1,10,0);
        //;R0 id устройства 0-дисплей,1-кл,2-дин.свет
        ///;R1 1
        //;R2 яркость подсветки
        //;R3 задержка гашения
        REDRAW();
      }
    }
  }
}

void Check(void){
  int i,t;
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  if(!(t=time.hour*60+time.min)){ //00:00 reset
    for(i=0;i<maxtask;i++){
      task[i].time-=24*60;
      if(task[i].maxused!=1)
        task[i].used=0;//task[i].maxused;
    }
  }
  if(first) everymin(t,GetWeek(&date)+1);
  else first=1;
  GBS_StartTimerProc(&mytmr,262*60,Check);//-time.param)
}

// ДОЛЖЕН кончаться 0!
inline char *delrem(char *lnk){ //удаляет комментарий и считает сколько строк
  char *s,*ss;
  s=ss=lnk-1;
  maxtask=0;
  do{
    while(*++s && *s==' ');
    if(!*s) break;
    if(*s==0xd) ++s;
    else if(*s==';'){
      while(*++s && *s!=0xd);
      if(!*s++) break;
    }else{
      ++maxtask;
      do{
        *++ss=*s++;
      }while(*ss && *ss!=0xd);
      if(!*ss) break;
      *ss=0;
    }
  }while(*s);
  *++ss=0;
  return ss;
}

inline int loadini(){ 
  char *maxlnk,*s;
  int i,tsk,h,m,hm,h2,m2,hm2;
  maxlnk=delrem(lnk);
  if(!maxtask) return 1;
  if(task){ mfree(task); task=0;}
  if(!(task=(struct taskst *)malloc(i=(sizeof(struct taskst)+180)*maxtask+maxlnk-lnk))) return 1;
  memset(task,0,i);
  mask=(char*)task+sizeof(struct taskst)*maxtask;
  s=mask+180*maxtask;
  memcpy(s,lnk,maxlnk-lnk);
  mfree(lnk); lnk=0; //???
  --s;
  tsk=0;
  do{
   do{
lll:     
    h=*++s-'0';
    if(*++s=='.'){
      task[tsk].week |= (1<<h);
      goto lll;
    }
    if(*s!=':') h=h*10+*s++-'0';
    if(*s!=':') return 1; //00:
    m=(*++s-'0')*10;
    m+=*++s-'0';
    if(*++s=='-'){ //-00:00
      h2=*++s-'0';
      if(*++s!=':') h2=h2*10+*s++-'0';
      if(*s!=':') return 1; //00:
      m2=(*++s-'0')*10;
      m2+=*++s-'0';
      //
      hm=h*60+m;
      hm2=h2*60+m2;
      while(hm<hm2){
        mask[tsk*180+(hm>>3)] |= 1<<(hm&7);
        ++hm;
      }
    }else{ //1 раз в 6:00
       hm=h*60+m;
       mask[tsk*180+(hm>>3)] |= 1<<(hm&7);
    }
   }while(*++s==',');
   while(*s==' ') ++s;
   if(s[1]!=':'){ //интервал
     i=*s-'0';
     while(*++s!=' ') i=i*10+*s-'0';
     task[tsk].interval=i;
     while(*++s==' ');
     if(s[1]!=':'){ //всего запусков
       i=*s-'0';
       while(*++s!=' ') i=i*10+*s-'0';
       task[tsk].maxused=i;
       while(*++s==' ');
     }
   }
   //путь
   task[tsk].exe=s;
   while(*++s);
  }while(++tsk<maxtask && s[1]);
  for(tsk=0;tsk<maxtask;tsk++)
    if(!task[tsk].maxused) --task[tsk].maxused;
  return 0;
}

void Killer(void){
  extern void *ELF_BEGIN;
  if(task) mfree(task);
  if(lnk) mfree(lnk);
  ((void (*)(void *))(mfree_adr()))(&ELF_BEGIN);
}


int main(char *exename, char *fname){
  int f=0,size;
  unsigned int err;
  do{
    memcpy(exename+strlen(exename)-3,"ini",4);
    if((f=fopen(exename,A_ReadOnly+A_BIN,P_READ,&err))<0) break;
    if(!(size=lseek(f,0,2,&err,&err))) break;
    lseek(f,0,0,&err,&err);
    if(!(lnk=(char*)malloc(size+1))) break;
    if(fread(f,lnk,size,&err)!=size) break;
    lnk[size]=0;
    fclose(f,&err);
    f=0;
    if(loadini()) break;
//    ShowMSG(1,(int)"TimeMan активирован!");//////////
    Check();
    return 0;
  }while(0);
  if(f>0) fclose(f,&err);
  ShowMSG(1,(int)"Ошибка в TimeMan.ini файле!");
  SUBPROC((void *)Killer);
  return 0;
}
