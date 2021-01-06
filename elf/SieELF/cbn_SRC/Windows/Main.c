
// Windows
#include "windows.h"

void onredraw(){ // Перерисовка экрана
}

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){       
  case KEY_UP: return 0; // Клавиша отпущена 
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(cryticalerror) return 1; // Выход
    if(keycode==GREEN_BUTTON) return 1; //отладка только!!!
/*  if(pysk){ //Нажата кнопка пуск
      switch(keycode){ // Код клавиши
        case '0': return 1; //exit
        case UP_BUTTON: if(ww.cury>0) --ww.cury; else ww.cury=ww.maxfiles-1; showmenu(); break;
        case DOWN_BUTTON: if(ww.cury<ww.maxfiles-1) ++ww.cury; else ww.cury=0; showmenu(); break;
        case ENTER_BUTTON: if(ww.cury==9) return 1; 
          menuenter(); break;
        default: pysk=0; if(mode) rewindow(); else showtable(); break;
      }
    }else */
  switch(mode){ 
    default:
    case modeinwindow:  //in WINDOW
    switch(keycode){ // Код клавиши
      case LEFT_BUTTON: if(w.curx>0) --w.curx; rewindow(); break;
      case RIGHT_BUTTON: if(w.curx<2) ++w.curx; rewindow(); break;
      case UP_BUTTON: if(w.cury>0) --w.cury; rewindow(); break;
      case DOWN_BUTTON: if(w.cury<3) ++w.cury; rewindow(); break;
      case ENTER_BUTTON: enter(); break;
//      case RIGHT_SOFT: //конт.меню
      case GREEN_BUTTON: showstart(); menuinit(); showmenu(); break; //пуск
      case LEFT_SOFT: case RED_BUTTON: levelup(); break;
      default: return 0;
    } break;
    case modeontable: //on TABLE
    switch(keycode){ // Код клавиши
      case LEFT_BUTTON: if(w.curx>0) --w.curx; showtable(); break;
      case RIGHT_BUTTON: if(w.curx<2) ++w.curx; showtable(); break;
      case UP_BUTTON: if(w.cury>0) --w.cury; showtable(); break;
      case DOWN_BUTTON: if(w.cury<3) ++w.cury; showtable(); break;
      case ENTER_BUTTON: openwindow(); break;
//    case LEFT_SOFT: showtable(); break;
//    case RIGHT_SOFT: //конт.меню
      case GREEN_BUTTON: menuinit(); showmenu(); break; //пуск
      default: return 0;
    } break;
    case modeonpysk: //on ПУСК
    switch(keycode){ // Код клавиши
      case LEFT_BUTTON: if(w.curx>0) --w.curx; showtable(); break;
      case RIGHT_BUTTON: if(w.curx<2) ++w.curx; showtable(); break;
    } break;
    }
    onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

void onclose(){ // Закрытие окна
  running=0; // Сигнал на остановку фонового процесса
  //  GBS_DelTimer(&timer); // Останавливаем таймер  pickoff!!
//  savelog();  // Сохраняем лог
}

void onexit(){ // Выход
//что-то можно перенести в onclose() ???
  if(wallpaper) mfree(wallpaper);
  if(title) mfree(title);
  if(start) mfree(start);
  if(icons) mfree(icons);
  if(error) mfree(error);
  if(ext) mfree(ext);
  if(extini) mfree(extini);
  if(winini) mfree(winini);
  if(ws) FreeWS(ws);
}

inline void cls(){
//  memset(screen,bkcolor,screensize);
  memsetd(screen,-1,screensize>>2);
}

void centerbmp(char *bmp){
  if(bmp){
  int x=(width-*(short*)bmp)>>1, y=(height-*(short*)(bmp+2))>>1;
    bitblt(screen, bmp, x<0?0:x, y<0?0:y, 0,0,0,0,0,0);
  }
}

inline void showtitle(){ //+заголовок!!!
  bitblt(screen, title, 0, 0, 0,0,0,0,0,0);
}
 
void showwindow(){ // Показать окно //........
  cls();
  showtitle();
  textout(w.dir,2,2,0,WHITE);
}

void showstart(){ // Показать кнопку пуск
  char tmp[8];
  TDate date; TTime time;
  GetDateTime(&date,&time);
  if(start) bitblt(screen, start, 0, height-15, 0,0,0,0,0,0);
  sprintf(tmp,"%d:%02d",time.hour, time.min);
  textout(tmp,height-12,width-slen(tmp)-3,0,BLACK);
}

void showerror(){ // Показать сообщ "Недопуст.операция"
  if(!error){
    strcpy(file,ferror);
    error=loadgraph(path);
  }
  if(error){
    bitblt(screen, error, 0, (height-41)>>1, 0,0,0,0,0,0);
    mfree(error);
    error=0;
  }
}

void showcur(int y, int x){ // Рамочный курсор
  int j;
  short *scr=screen+y*width+x;
  memsetw(scr,curcolor,32);
  memsetw(scr+=width,curcolor,32);
  for(j=0;j<29;j++){
    scr+=width;
    *scr=scr[1]=scr[30]=scr[31]=curcolor;
  }
  memsetw(scr,curcolor,32);
  memsetw(scr+width,curcolor,32);
}

void showpic(int y, int x, char *bmp, int num, char *name, int color){ // Показать 1 пиктограмму
  int i,j;
  short *scr=screen+y*width+x, *ic=(short*)icons+2+num*32*32;
  for(j=0;j<32;j++){
    for(i=0;i<32;i++,ic++,scr++)
      if(*ic!=redcolor) *scr=*ic;
    scr+=width-32;
  }
//  if((unsigned int)num<xx*yy){
//    bitblt(screen,bmp,x,y,32,32, 0,num<<5, maskcolor,0);
//  }
  textout(name,y+32,x,32,color);
}

void showicons(){ // Показать все значки
  int i,j,k=0,l;
  for(j=0;j<4;j++){
    for(i=0;i<3;i++){
      l=k++;
      if(l==0) l=9;
      else if(l==9) l=0;
      showpic(j*40,i*40+8,icons,l,(char*)nametmp[l],WHITE);
    }
  }
//  w.curx=w.cury=0; //// no move cursor
  showcur(w.cury*40,w.curx*40+8);
}

void showtable(){ // Показать рабочий стол
  if(fastfon) movsd(screen,wallpaper+4,screensize>>2);
  else{  cls(); centerbmp(wallpaper); }
  showstart();
  showicons();
  mode=0;
}

inline void setcodepage(int page){ // Подг. табл. перекод. симв.
  int i, A,P,a,p;
  memset(sym,0,0x100);
  switch(page){
    case 0:  A=0x80; P=0x90; a=0xa0; p=0xe0; break; //dos
    case 1:  A=0xc0; P=0xd0; a=0xe0; p=0xf0; break; //win
    default: A=0xb0; P=0xc0; a=0xd0; p=0xe0; //iso
  }
  for(i=0x20;i<0x80;i++)
    sym[i]=(byte)(i-0x20);
  for(i=0;i<0x10;i++){
    sym[A+i]=(byte)(0xa0+i);
    sym[P+i]=(byte)(0xb0+i);
    sym[a+i]=(byte)(0xc0+i);
    sym[p+i]=(byte)(0xd0+i);
  }
  if(page!=1){sym[0xf0]=0x25; sym[0xf1]=0x45;}  //Ёё в Ее
}

inline void initfont(){  // Подготовить шрифт
  int i;
  byte *k;
  for(i=0,k=font+FONMAX;i<FONMAX;i++){
    symptr[i]=k;
    k+=font[i];
  } setcodepage(1);
}

void textout(char *s, int y, int x, int maxx, int textcolor){ // Отобразить текст цветом textcolor в х,у
  if(!s || !*s || (unsigned int)y>=height-FONSIZEY || (unsigned int)x>=width ) return;
  if(!maxx) maxx=width;
  if(maxx>width-x) maxx=width-x;
  short *scr=screen+(y+FONSIZEY)*width+x;
  int i,j,b, ssym;
  --s;
  while(*++s){
    if(ssym=sym[*(byte*)s]){
      for(j=0;j<font[ssym];j++){
        b=*(symptr[ssym]+j);
        if(--maxx<0) return;
        for(i=0;i<FONSIZEY;i++,scr-=width){
          if(b&1) *scr=textcolor; 
          b>>=1;
        }
        scr+=width*FONSIZEY+1;
      }
    }else scr+=font[ssym];
  }
}


void getlist(struct windows *w, char *tpath){ // Получить список файлов
  static DIR_ENTRY de;
  char *s=w->buf, *stemp, *ss;
  int i;
//  char *mask=w.dir;
/*  if(!*w->dir || *w->dir==' '){ //strcpy(w.dir,"0:\\"); //default here!!!!!!!!!!!!1
    for(i=0;i<5;i++){
      w->filename[i]=(char*)Diskname[i];
      w->filetype[i]=2;
    }
    w->maxfiles=5;
    strcpy(w->dir," Мой компьютер");
  }else{*/
  //w->maxfiles=0;
  strcpy(temp,tpath);
  stemp=temp+strlen(temp);
  memset(w,0,sizeof(struct windows));
  strcpy(w->dir,temp);
  strcat(w->dir,allext);
  if (FindFirstFile(&de,w->dir,&err)){
    do{
      w->filename[w->maxfiles]=s;
      w->filetype[w->maxfiles]=idunknown;
      ss=(SGOLD2)?(de.file_name):((char*)&de+169);
      memcpy(s,ss,i=strlen(ss)+1);
      memcpy(stemp,s,i);
      if(isdir(temp,&err)) 
        w->filetype[w->maxfiles]=idfolder;
      else{
        getext(ss);
        if(*(int*)tempext)
          if(i=findext(bmpext,tempext)>=0)
            w->filetype[w->maxfiles]=i;
      }
      s+=i;
      w->maxfiles++;
    }while(s<w->buf+maxbufsize-40 && w->maxfiles<maxwinfiles && FindNextFile(&de,&err));
  }
  FindClose(&de,&err);
  w->dir[strlen(w->dir)-3]=0;
//  }
}

void rewindow(){
  showwindow();
  showfiles();
  showcur(w.cury*40+14,w.curx*40+8);
}

void openwindow(){ // Открытие окна
  getlist(&w,w.dir);
  rewindow();
  mode=1;
}

void showfiles(){ // Показать все файлы
  int i,j,k=0;
  for(j=0;j<4;j++){
    for(i=0;i<3;i++,k++){
      if(k>=w.maxfiles) return;
      showpic(j*40+14,i*40+8,icons,w.filetype[k],w.filename[k],BLACK);
    }
  }
}

void enter(){ // Зайти в папку или выполн.действие
//  int i;
  char *s, *ss;
  int n=w.curx+w.cury*3;
  if(n>=w.maxfiles) return;
  switch(w.filetype[n]){
  case 2: //disk
    strcpy(w.dir,"0:\\");
    *w.dir=0x30+n;
    goto opens;//!!
  case 1: //dir
  s=w.filename[n];
  ss=w.dir+strlen(w.dir);
  while(*--ss!='\\');
  do{
    *++ss=*s++;
  }while(*ss);
  //memcpy(ss,"\\*.*",5);
  *ss='\\'; ss[1]=0;

opens:
//  w.curx=w.cury=0;
  openwindow();
  break;
  default: //file execute!!!
    s=w.filename[n];
    WSHDR *ws=AllocWS(256);
    s+=strlen(s);
    while(s>w.filename[n] && *--s!='.');
    if(*s=='.'){
      ss=++s;
      do{ *ss=*ss|0x20; }while(*++ss);
/*
      for(i=0;i<maxextn;i++)
        if(*s==*extn[i].ex && !strcmp(s,extn[i].ex)) break; //расш. нашлось!
      if(i<maxextn){ //i=defextn;
        strcpy(temp,w.dir);
        strcat(temp,w.filename[n]);
        str_2ws(ws,extn[i].exe,strlen(extn[i].exe)+1);
        ExecuteFile(ws,0,temp);
        FreeWS(ws);
        return;
      }
*/
    }
    strcpy(temp,w.dir);
    strcat(temp,w.filename[n]);
    str_2ws(ws,temp,strlen(temp)+1);
    ExecuteFile(ws,0,0);
    FreeWS(ws);
  //showerror(); 
    break;
  }
}

void levelup(struct windows *w){ // На уровень выше
  char *s=w->dir;
  if(!*s || *s==' '){  showtable(); return;}//7
  if(strlen(s)<4) *s=0;
  else *(strrchr(s,'\\')+1)=0;
  openwindow();
}

void entermenu(){
  //...
  int i;
  if(!*menu.dir){
    for(i=0;i<10;i++){
      menu.filename[i]=(char*)Menuname[i];
//      ww.filetype[i]=2;//?????????
    }
    menu.maxfiles=10;
//    strcpy(w.dir," Мой компьютер");
  }
}

void showmenu(){ //Показать меню пуск
  /*
  int i,j,x=0,y;
  for(i=0;i<menu.maxfiles;i++)
    if((j=slen(menu.filename[i]))>x) x=j;
  x+=6;
  if(x>=width) x=width-1;
  y=height-15-(j=ww.maxfiles*10+6);
  if(y<0){ y=0; j=height-15;}
  short *s=screen+y*width;
  memsetw(s,BLACK,x);
  --j;
  for(;j>0;j--){
    s+=width;
    memsetw(s,startcolor,x);
    *s=s[x]=BLACK;
  }
  memsetw(s,BLACK,x);
  for(i=0;i<ww.maxfiles;i++){
    if(ww.cury==i){ //cursor
      s=screen+(y+2+i*10)*width;
      for(j=0;j<10;j++,s+=width) 
        memsetw(s+1,BLUE,x-2);
      textout(ww.filename[i],y+3+i*10,4,0,WHITE);
    }else textout(ww.filename[i],y+3+i*10,4,0,BLACK);
  }*/
}

void menuinit(){ //подгот.меню
  pysk=1;
  menu.cury=0;
  *menu.dir=0;
  entermenu();//??
  //...
}

void menuenter(){
}

void loadwinini(){ //вида 000 строка   win.ini
  char *s;
  int i;
  for(i=0;i<maxmsg;i++) msg[i]=(char*)merror;
  strcpy(file,fwin);
  if(!(s=winini=loadfile(path))) return;
  s[loadfilesize-2]=0;
  --s;
  do{
    switch(*++s){
    case ' ': case 9: case 0xd: case 0xa: case 0: break;
    case ':': case '/': while(*++s && *s!=0xd); break;
    default: 
    i=s[0]*100+s[1]*10+s[2];
    if(i>=0 && i<maxmsg){
      msg[i]=s+4;
      while(*++s && *s!=0xd && *s!=';' && *s!='/'); 
      if(*s) break;
      if(*s==0xd) *s++=0;
      else{ *s=0;  while(*++s && *s!=0xd); }
    }else{ //error num
      while(*++s && *s!=0xd); 
    }
    }
  }while(*s);
}

inline void findpar(char *str){ //find in param
  int i, num;
  char *s=str-1;
  while(*++s && *s!=0xd && *s!='=') *s|=0x20;
  if(*s!='=') return;
  for(i=num=0;i<PMAX;i++){
    if(*str==*mparam[i] && strlen(mparam[i])==s-str && memcmp((void*)mparam[i],str,s-str)){ //found
      while(*++s>='0' && *s<='9') num=num*10+*s-'0';
      param[i]=num;
      return;
    }
  }
}

void loadsystemini(){ //вида парам=значение  system.ini
  char *s, *ini;
  strcpy(file,fsystem);
  if(!(s=ini=loadfile(path))) return;
  s[loadfilesize-2]=0;
  --s;
  do{
    switch(*++s){
    case ' ': case 9: case 0xd: case 0xa: case 0: break;
    case ':': case '/': while(*++s && *s!=0xd); break;
    default:  findpar(s); while(*++s && *s!=0xd);
    }
  }while(*s); 
  mfree(ini);
}

void loadext(){ // загр. расширений и соотв. эльфов      extension.ini
  int i, ii, razd, act, size;
  char *s, *ss;
  strcpy(file,fexten);
  if(!(extini=loadfile(path))) return;
  extini[loadfilesize-2]=0;
  razd=getcnt(extini,'[')+1;
  act=getcnt(extini,0xd);
  //выдел. памяти
  if(!(pext=ext=(int*)malloc(size=8*razd+4*razd+4*act+4*act))) return;
  memset(ext,0,size);
  extnum=ext+razd*2;
  pextact=extact=(char**)(extnum+razd);
  pextelf=extelf=extact+act;
  //"разбить" строки
  s=extini-1;
  do{
    switch(*++s){
    case 0: case 0xd: case 0xa: case 9: case ' ': break;
    case ':': case '/': //коммент.
      while(*s && *s!=0xd) ++s;
      break;
    case '[': //тип
      if(pextact>extact){ ++pextact; ++pextelf; }
      ss=(char*)pext; ++s;
      for(i=0; i<8 && *s!=']' && *s; i++) *ss++=(*s++)|0x20;
      pext+=2;
      extnum[(pext-ext)>>1]=pextact-extact; //номер действия
      while(*s && *s!=0xd) ++s;
      break;
    default:
      *pextact++=s;
      while(*++s && *s!=':' && *s!=0xd);
      if(*s!=':'){ ++pextelf; break;}
      *s=0; while(*++s==' ');
      if(s[1]!=':') ///сюда номер станд.ф-ции вставить!!!
        *pextelf=(char*)getval(s);
      else
        *pextelf++=s;
      while(*++s && *s!=0xd);
      ss=s; ++s;
      while(*--ss==' ');
      ss[1]=0;
    }
  }while(*s);
  //ищем по умолч. [*]
  //pext=ext;
  //clrfext();
  *(int*)tempext=*(int*)(tempext+4)=0;
  *tempext='*';
  if(i=findext(ext,tempext)>0){ //поменять местами с 0м
    ii=extnum[i]; extnum[i]=extnum[0]; extnum[0]=ii;
    ii=ext[i<<=1]; ext[i]=ext[0]; ext[0]=ii;
    ii=ext[i+=1]; ext[i]=ext[1]; ext[1]=ii;
  }
}

void loadswap(){ //загрузка кеша иконок  win386.swp
  int i,flag=0;
  do{
    strcpy(file,fswap);
    if((icons=loadfile(path)) || flag) break;
    strcpy(file,ficonself);
    execelf(path,0);
    flag=1;
  }while(1);
  bmpext=(int*)(icons+*(int*)icons);
  // ищем станд. значки
  for(i=0;i<idmax;i++)
    sysbmpnum[i]=findext(bmpext,(char*)sysbmp[i]);
  // грузим фон
  strcpy(file,fwallpaper);
  if(wallpaper=loadgraph(path))
    if(*(short*)wallpaper==width && *(short*)(wallpaper+2)==height) fastfon=1;
}

void oncreate(){ // Создание окна
  strcpy(file,ftitle);
  title=loadgraph(path);
  strcpy(file,fstart);
  start=loadgraph(path);
  strcpy(file,ferror);
  error=loadgraph(path);
  loadswap();
  if(!(title && start && icons)){ cryticalerror=1; showerror();}
  showtable();//??
//  SUBPROC((void *)execute); // Запускаем фоновый процесс 
//  GBS_StartTimerProc(&timer,262/2,timer_proc); // Стартуем таймер с частотой 2 раз в секунду
  REDRAW(); //?
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  //some init here
  ws=AllocWS(256);
  param[PLOGO]=1; 
  //path copy
  strcpy(path,exename);
  file=strrchr(path,'\\')+1;
  //XP screen
  char *logo;
  strcpy(file,flogo);
  if(logo=loadgraph(path)){
    centerbmp(logo);
    onredraw(); DrawScreen(); // Перерисовать экран  //REDRAW();
    mfree(logo); 
  }//load all
  loadwinini();
  loadsystemini();
  loadext();
  initfont();
  Randomize(); //if(Random());
  return 0;
}
