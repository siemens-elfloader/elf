
// Function.h Встроенные функции MS-DOS

char *par(char *to, char *s){ //получить полный путь для параметра
  if(s[1]!=':') strcpy(to,curdir); else *to=0;
  strcat(to,s);
  return to;
}

int quit(){ exit=1; return 0;}
int empty(){ return 0;}
int cls(){cr(); return 0;}

int echo(){ 
  if(stricmp(*++argv,"ON")) echooff=0;
  else if(stricmp(*argv,"OFF")) echooff=1;
  else{ --argv; 
    while(*++argv) print(*argv); 
  }
  return 0;
}

int mem(){
  sprintf(temp,"На диске Data всего: %d Кб"\
          "\r\nСвободно: %d Кб"\
          "\r\nПамяти свободно: %d Кб\r\n",
          GetTotalFlexSpace(0,&err)>>10,
          GetFreeFlexSpace(0,&err)>>10,
          GetFreeRamAvail()>>10);
  print(temp);
  return 0;
}

int date(){
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  sprintf(temp,"%d.%02d.%d", date.day, date.month, date.year);
  print(temp);
  return 0;
}

int time(){
  TDate date;
  TTime time;
  GetDateTime(&date,&time);
  sprintf(temp,"%d:%02d", time.hour, time.min);
  print(temp);
  return 0;
}

int md(){
  par(ar1,argv[1]);
  mkdir(ar1,&err);
  return err?errpath:ok;
}

int rd(){
  par(ar1,argv[1]);
  rmdir(ar1,&err);
  return err?errpath:ok;
}

int ver(){ 
  print(Title); 
  return 0;
}

int setpath(){
  if(argc==1){ cr(); print(path);}
  else{
    if(path[strlen(path)-1]!=';') strcat(path,ezap);
    strcat(path,argv[1]);
  }
  return 0;
}

int ren(){
  char *s;
  if(argc!=3) return errarg;
  par(ar1,argv[1]);
  par(ar2,argv[2]);
  if(!strchr(ar1,'*')){
    fmove(ar1,ar2,&err);
    if(err) return error;
    print(argv[1]); print(" => "); print(argv[2]);
  }else{
    reset();
    extnn(curdir,strrchr(ar1,'\\')+1);
    s=list;
    while(s<lend){
      fmove(s,ar2,&err);
      if(err) return error;
      cr(); print(s); print(" => "); print(argv[2]);
      s+=strlen(s)+1;
    }
  }
  return 0;
}

int del(){
  char *s;
  par(ar1,argv[1]);
  if(!strchr(ar1,'*')){
    unlink(ar1,&err);
    return err?errpath:ok;
  }
  reset();
  extnn(curdir,strrchr(ar1,'\\')+1);
  s=list;
  while(s<lend){
    unlink(s,&err);
    if(err) return error;
    s+=strlen(s)+1;
  }
  return 0;  
}

int copyxx(char *file, int todir){
    int f=-1,size;
    char *mem;
    if((f=fopen(file,A_ReadOnly+A_BIN,P_READ,&err))==-1) return erropen;
    size=lseek(f,0,2,&err,&err);
    lseek(f,0,0,&err,&err);
    if(!(mem=(char*)malloc(size+1))){ fclose(f,&err); return errmemory;}
    fread(f,mem,size,&err);
    fclose(f,&err);
    strcpy(temp,ar2);
    if(todir){
      if(temp[strlen(temp)-1]!='\\') strcat(temp,eline);
      strcat(temp,strrchr(file,'\\')+1);
    }
    if((f=fopen(temp,A_WriteOnly+A_BIN+A_Create,P_WRITE,&err))==-1){ mfree(mem); return errcreate;}
    fwrite(f,mem,size,&err);
    fclose(f,&err);
    mfree(mem);
    cr(); print(file); print(" => "); print(ar2);
    return 0;
}

int copy(){
  if(argc!=3) return errarg;
  int i,todir;
  char *s;
  par(ar1,argv[1]);
  par(ar2,argv[2]);
  todir=isdir(ar2,&err);
  if(!strchr(ar1,'*')){
    return copyxx(ar1,todir);
  }
  reset();
  extnn(curdir,strrchr(ar1,'\\')+1);
  s=list;
  while(s<lend){
    if(i=copyxx(s,todir)) return i;
    s+=strlen(s)+1;
  }
  return 0;
}

int type(){
  if(argc!=2) return errarg;
  int f,size;
  par(ar1,argv[1]);
  if((f=fopen(ar1,A_ReadOnly+A_BIN,P_READ,&err))==-1) return erropen;
  size=fread(f,conbuf,conbufsize,&err);
  fclose(f,&err);
  conend=conbuf+size;
  return 0;
}

int sset(){
  if(argc==1){ //вывести список
    char *s=set;
    while(s<setend){
      cr(); print(s);
      s+=strlen(s)+1;
    }
  }else{ //добавить в список
    if(setend+strlen(argv[1])+1<set+maxset){
      strcpy(setend,argv[1]);
      setend+=strlen(argv[1])+1;
    }else return errmemory;
  }
  return 0;
}

int dir(){
  int i,f,app,rec;
  char *s, **ar=argvv, *to=0;
  i=f=app=rec=0;
  strcpy(spath,curdir);
  spath[strlen(spath)-1]=0;
  while(*++ar){
    if(**ar=='>'){ to=*ar; --argc; break;}
    if(**ar=='<'){ rec=1; --argc; break;}
  }
  reset();
  if(argc<2){ 
    if(rec) find(0,spath,"*.*");
    else extnn(curdir,"*.*");
  }else{
    ar=argvv;
    while(*++ar){
      if(**ar!='>' && **ar!='<')
        if(rec) find(0,spath,*ar);
        else extnn(curdir,*ar);
    }
  }
  s=list;
  if(to){ //в файл
    if(*++to=='>'){ app=1; ++to;}
    if(to[1]==':') *temp=0;
    else strcpy(temp,curdir);
    strcat(temp,to);
    if((f=fopen(temp,A_ReadWrite+A_BIN+A_Append+A_Create,P_WRITE+((app)?P_READ:0),&err))!=-1){
      lseek(f,0,2,&err,&err);
      fwrite(f,list,lend-list,&err); 
      fclose(f,&err); 
    }
  }else{
  while(s<lend){
    cr(); print(s);
    s+=strlen(s)+1;
    ++i;
  }
  sprintf(con,"\r\n%d файлов",i);
  print(con);
  }
  return 0;
}

int cd(){
  char *s=argv[1], *ss;
  if(argc!=2) return 0;//errarg;
  if(s[1]==':'){ //"0:\"
    strcpy(curdir,s);
  }else
  switch(*s){
  case '.':
    if(s[1]=='.'){ //.. level up
      curdir[strlen(curdir)-1]=0;
      if(ss=strrchr(curdir,'\\')) ss[1]=0;
    }break;
  case '\\': //"\bin"
    strcpy(curdir+2,s);
    break;
  default: // bb
    strcat(curdir,s);
  }
  if(curdir[strlen(curdir)-1]!='\\') 
    strcat(curdir,eline);
  return 0;
}

//////Функции://///////
struct cmdst commands[]={
  {"CD",cd},
  {"CHDIR",cd},
  {"COPY",copy},
  {"ECHO",echo},
  {"REN",ren},
  {"RENAME",ren},
  {"REM",empty},
  {"PATH",setpath},
  {"DIR",dir},
  {"MEM",mem},
  {"DATE",date},
  {"TIME",time},
  {"MD",md},
  {"MKDIR",md},
  {"RD",rd},
  {"RMDIR",rd},
  {"TYPE",type},
  {"VER",ver},
  {"SET",sset},
  {"CLS",cls},
  {"QUIT",quit},
  {"EXIT",quit},
  {"DEL",del},
  {"ERASE",del},
  {"PAUSE",empty},
  {"GOTO",empty},
{0,0}
};

