
// PsyTests 0.1

#include "..\swilib.h"

#define free mfree
#define STREAM int
#define ffopen fopen
#define ffclose fclose
#define ffread fread

#define boolean char
#define true 1
#define false 0
#define null 0
#define byte signed char

char *Title="PsyTests 0.1 (c)bn";
const char *errors[]={
  0,
  "Не найден tab или fnt файлы!\0",
  "Ошибка открытия data файла!\0",
  "Ошибка распаковки data файла!\0",
  "Неверный data файл!\0"
};

char *alldata=0;
extern short *screen; // Экран 132*176*2
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();
extern int width, height, screensize;

int scrlength;
char filename[128], *file;

  int fquit=0;
	const int MEMSIZE=1500+1024, // размер шрифта + 0x400 + 10
	  FONMAX=0xe0, FONSIZEY=9, FONSIZEYY=8, FONTIDX=0x200, DEFIS=0x100,
	  FONT=0x200+0xe0+0xe0, TEXTCOLOR=0, BACKCOLOR=0xffffff, SELCOLOR=0x1f, MAXQUEST=80, MAXSTAT=32; 
  //const int K_UP=-59, K_DOWN=-60,  K_LEFT=-61, K_RIGHT=-62, K_FIRE=-26, K_SOFT_LEFT=-1, K_SOFT_RIGHT=-4; // Клавиши
	boolean fstart = false, ftype2=false, fexit=false;
	byte *mem = null, *data=null;	// Вся память
	int *scr = null;		// Экран
	int pos2, showpos=0, qst, qrez, qrezptr, allrez; // Тек.ук-ль, начало вопросов scr[qst] и стат
	int nstart, ncur, nend, nmax; // Меню: старт. поз, тек., конец и всего 
	int head, vved, stat;	// Смещ. заг-ка, введ-я, статистики

///////
extern int maxcnt; // Всего файлов в 7z архиве
    extern int un7zinit(char *buf); // Иниц-я 
extern char *un7z(int num); // Получить файл номер num
extern void un7zexit(); // Выход
extern char *un7znext(); // Распаковать следующий un7z файл
        
        
/////////////

  void exit(){
    if(scr) free(scr);
    if(mem) free(mem);
    if(data) free(data);
    if(alldata) free(alldata);
  }

  void repaint(){ }
  void serviceRepaints(){}
  //void testexit(){ } //ВЫХОД ()


void Psy(){
  qst=1;//width*height;
  qrez=qst+MAXQUEST;
  qrezptr=qrez+MAXSTAT;
  scr = (int*)malloc((scrlength=qrezptr+MAXSTAT)*4);
  mem = (byte*)malloc(MEMSIZE);
}

int memload(int poss, char* ext){ // Загрузить в mem pos файл name
  STREAM f;
  strcpy(file,ext);
  if((f=ffopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==0) return fquit=-1; // ret: pos=р-р ф-а
  pos2=ffread(f,mem+poss,MEMSIZE, &err);
  ffclose(f,&err);
  if(!pos2) return fquit=-1;
  return pos2+poss;
}

//int getshort(int pos){ // Целое из 2б строки
//  return (mem[pos]&0xff|(mem[pos+1]&0xff)<<8);}

void skip(){ //pos=nextstr Переход к след. строке
  while(data[pos2]!=0 && data[pos2]!=0xd) ++pos2;
  if(data[pos2]!=0) pos2+=2;
}

int ror(int val){ return ((val&1)!=0)?((val>>1)+0x80):(val>>1);}
//public void cls(int color){  for(int i=0;i<qst;i++) scr[i]=color;}

boolean empty(){ // Пустая ли строка?
  int p=pos2;
  while(data[p]!=0 && data[p]==0x20) ++p;
  if(data[p]==0) return false; //??
  return (data[p]==0xd);
}

boolean isval2(int endswith){
  if(endswith==0) return (data[pos2]>=0x30 && data[pos2]<=0x39);
  while(data[pos2]!=0 && data[pos2]>=0x30 && data[pos2]<=0x39) ++pos2;
  return(data[pos2]==(byte)endswith);
}

void abzac(){
  do{
    skip();
  }while(data[pos2]!=0 && !empty());
  do{
    skip();
  }while(data[pos2]!=0 && empty());
}

void nextq(){
  do{
    skip();
  }while(data[pos2]!=0 && !isval2(0) && !empty());
}

void getquest(){ // Получ. ук-и на вопросы для отобр.
  nstart=nend=ncur=nmax=0;
  ++ncur;
  if(isval2(0) && !isval2(0x2e)) scr[qst]=0;
  else{
    scr[qst]=pos2;
    nextq();
  }
  scr[qst+(++nmax)]=pos2;
  while(data[pos2]!=0 && !empty()){
    nextq();
    scr[qst+(++nmax)]=pos2;
  }
  while(data[pos2]!=0 && empty()) skip();
}

boolean testload(int num){ // Загрузить тест *name  // ret: size=р-р ф-а
  int i;
//  STREAM f;
  fexit=false;
/*  file[0]='0'+num/10;
  file[1]='0'+num%10;
  file[2]=0;
  if((f=ffopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==0) return fquit=-1;*/
  if(data) mfree(data);
  if(!(data=un7z(num))) return fquit=-1;
  pos2=loadfilesize;
  char *data2=(char*)malloc(loadfilesize+1);
  memcpy(data2,data,loadfilesize); mfree(data); data=data2;
//  pos2=ftell(f);
//  pos2=lseek(f,0,2,&err,&err);
//  lseek(f,0,0,&err,&err);
  if(pos2<100) return fquit=-1;
//  if(data) mfree(data);
//  if(!(data=(byte*)malloc(pos2+1))) return fquit=-1;
  data[pos2]=0;//-1!!!!!
//  if(ffread(f,data,pos2,&err)!=pos2) return fquit=-1;
//  ffclose(f,&err);
  while(--pos2>=0){ data[pos2]=(byte)ror((data[pos2]-1)&0xff); } //decoding
  // Подготовка данных
  for(pos2=vved=stat=allrez=0;data[pos2]!=0 && data[pos2]==0x20; pos2++); //устан. заг-к
  head=pos2;
  skip(); skip();
  for(i=0;i<MAXSTAT+MAXSTAT;i++) scr[qrez+i]=0;
  if(!isval2(0)){ // Есть введенение
    vved=pos2;
    abzac();
  }
  stat=pos2;
  if(ftype2=isval2(0x2e)){ //Сложн. тип вопросов
    for(i=0;i<MAXSTAT;i++){
      scr[qrezptr+i]=pos2;
      if(empty()){
        scr[qrezptr+i+1]=pos2;
        break;
      }
      skip();
    }
  }else abzac();
  if(head>0){
    nstart=nend=0;
    nmax=ncur=1;
    scr[qst]=head;
    scr[qst+1]=stat;
  }else getquest();
  return 0;//add
}


boolean start(){
  int i,j,k;
  memset(scr,0,scrlength*4);
  memset(mem,0,MEMSIZE);
  for(i=0x20;i<0x80;i++)
    mem[i]=(byte)(i-0x20);
  for(i=0;i<0x10;i++){
    mem[0x80+i]=(byte)(0xa0+i);
    mem[0x90+i]=(byte)(0xb0+i);
    mem[0xa0+i]=(byte)(0xc0+i);
    mem[0xe0+i]=(byte)(0xd0+i);
  } mem[0xf0]=0x25; mem[0xf1]=0x45;  //Ёё в Ее
  // load all
  if(memload(DEFIS,"tab")==-1) return -1;
  if(memload(FONT,"fnt")==-1) return -1;
  for(i=0,j=FONTIDX,k=FONT+FONMAX;i<FONMAX;i++){
    mem[j++]=(byte)k; mem[j++]=(byte)(k>>8);
    k+=mem[FONT+i]&0xff;
  }
  testload(0);
  fstart=true;
  REDRAW();
//  repaint();
//  serviceRepaints();
  return 0; //add
}

int getlastpos(int ppos, int lpos){
  int sym,x=0; 
  //--ppos;
  while(data[++ppos]!=0 && ppos<lpos){
    sym=mem[data[ppos]&0xff]&0xff;
    if((x+=mem[FONT+sym])>=width){
      while(data[ppos]!=0x20 && data[ppos]!=0xa) --ppos;
      return ppos;
    }
  }
  return ppos;
}

void show(int ppos){ // Отобразить меню
  int i,j,k,b,sym, x,y=0, xy, npos, lpos;
  memsetw(screen,0xffff,width*height);
//  for(i=0;i<qst;i++) scr[i]=0xffffff;
  for(i=nstart;i<nmax;i++){
    if(ppos==0)
      ppos=scr[qst+i]-1;
    if(i>0){ //not head
      ++ppos;
      while(data[++ppos]!=0x20);
    }
    lpos=scr[qst+i+1];
    do{
     npos=getlastpos(--ppos,lpos);
     if(ppos>npos-3) break;
     x=0; 
     if((y+=(FONSIZEY+1)*width)>=(screensize>>1)){
       nend=i; 
       if(i==0) showpos=++ppos;//??
       else{ showpos=0; --nend;}
       return;
     }
     while(data[++ppos]!=0 && ppos<npos){
      sym=mem[data[ppos]&0xff]&0xff;
     // if(x+mem[FONT+sym]>=width){
     //   x=0; if((y+=(FONSIZEY+2)*width)>=qst) return;
     // }
      for(j=0;j<mem[FONT+sym];j++){
        b=(mem[getshort(mem+FONTIDX+(sym<<1))+j]);
        ++x;
        xy=x+y;
        for(k=0;k<FONSIZEYY;k++,xy-=width){
          screen[xy]=((b&1)==0)?BACKCOLOR:((i==ncur)?SELCOLOR:TEXTCOLOR); 
          b>>=1;
        }
      }
     }//--ppos;
    }while(true);
    y+=width<<2;
  }
  nend=i;
  showpos=0;
}

int getval(int ptr){
  return data[ptr]-0x30;
}

int getval2(){
  int res=0;
  --pos2;
  while(data[++pos2]>=0x30 && data[pos2]<=0x39){
    res=res*10+data[pos2]-0x30;
  }
  return res;
}

void putval2(int val){
  do{
    data[--pos2]=(byte)((val%10)+0x30);
    val/=10;
  }while(val>0);
}

void putval3(int pos2, int val){
  do{
    data[--pos2]=(byte)((val%10)+0x30);
    val/=10;
  }while(val>0);
}


boolean meminmem(byte *s1, int p1, int l1, byte *s2, int p2, int l2){ //Входит стр. в строку?
  int i,j;
  for(j=0;j<l1-l2;j++){
    for(i=0;i<l2;i++)
      if(s1[p1+j+i]!=s2[p2+i])
        break;
    if(i==l2) return true;
  }      
  return false;
}

void addval(int ptr){ //для type2 найти и +1 значение
  int i,p=MEMSIZE-10,pp;
  mem[p++]=0x20;
  do{
    mem[p++]=data[ptr++];
  }while(p<MEMSIZE-2 && data[ptr]!=0x20);
  mem[p++]=0x20;
  //
  for(i=0;scr[qrezptr+i+1]!=0;i++){
    pp=scr[qrezptr+i];
    while(data[++pp]!=0x3a && data[pp]!=0);//":"
    if(meminmem(data,++pp,scr[qrezptr+i+1]-pp,mem,MEMSIZE-10,p-MEMSIZE+10)){
      scr[qrez+i]++;
      return;
    }
  }
}

void outtype2(){ //Отобр.рез-ты для type2
  int i, cnt, outpos=pos2;
  nmax=0;
  do{
    scr[qst+nmax++]=outpos;
    do{
      data[outpos++]=data[pos2++];
    }while(data[pos2]!=0x3a && data[pos2]!=0);
    cnt=0; ++pos2;
    while(data[++pos2]!=0xd) if(data[pos2]==0x20) ++cnt;
    for(i=0;i<4;i++)
      data[outpos++]=0x20;
    if(cnt==0) ++cnt;
    putval3(outpos,scr[qrez+nmax-1]*100/cnt);
    data[outpos++]=0x25; //"%"
    skip();
  }while(!empty());
  scr[qst+nmax]=outpos;
  //frez=true;
  //return outpos;
}

int select(){
  if(fexit){
    if(testload(0)<0) return fquit=-1;
  }
  //обраб.рез-та ??
  //while(data[pos]!=0)
  if(nmax>1){
   if(nmax>30){ //30 = main menu
     if(ncur==nmax-1) return fquit=-1;
       if(testload(ncur)<0) return fquit=-1;
   }
   if(ftype2) addval(scr[qst+ncur]);
   else allrez+=getval(scr[qst+ncur]);
  }
  if(data[pos2]!=0) getquest();
  else{ //end test Отобр. рез-ты
    fexit=true;
    pos2=stat;
  if(ftype2){
    nstart=nend=0;
    nmax=ncur=1;
    outtype2();
    //scr[qst]=pos2;
    //scr[qst+1]=outtype2();
  }else{
    while(allrez<getval2()){
     do{
      skip();
     }while(!isval2(0) && data[pos2]!=0);
    }
    nstart=nend=0;
    nmax=ncur=1;
    putval2(allrez);
    scr[qst]=pos2;
    do{
      skip();
    }while(!isval2(0) && data[pos2]!=0 && !empty());
    scr[qst+1]=pos2;
  }
  }
  return 0;
}

int keyPressed(int keyCode){
  if(fstart){
  if(showpos==0)
  if(fquit) return 1;//exit
  switch(keyCode){
    case '2': case '*': //Up
    case LEFT_SOFT: case LEFT_BUTTON: case UP_BUTTON:
      if(--ncur<1){
        if(nstart>0){ ++ncur; nstart=0;}
        else{ ncur=nmax-1; nstart=ncur;}
      }else if(ncur<nstart) nstart=ncur;
      break;
    case '8': case '#': //Down
    case RIGHT_SOFT: case RIGHT_BUTTON: case DOWN_BUTTON:
      if(++ncur>=nmax){ ncur=1; nstart=0;}
      else if(ncur>nend) nstart=ncur;//-((showpos>0)?1:0))
      break;
    case '5': case '0': case ENTER_BUTTON: //Select
      select();
      break;
   default: return 0;
  }
  REDRAW();
//  repaint();
//  serviceRepaints();
  }
  return 0;
}


//void paint(){
//  if(fstart){
//    show(showpos);
////    image=Image.createRGBImage( scr, width, height, false); 
////    g.drawImage(image, 0, 0, Graphics.TOP|Graphics.LEFT);	
//  }
//}

//int main2(char *exename, char *fname){
//  strcpy(filename, exename);
//  file=strrchr(filename,'\\')+1;
//  Psy();
//  start();
//  return 0;
//}

//void main(int argc, char **argv){
//  main2(*argv,0);
//}
void onredraw(){ // Перерисовка экрана screen[132*176]
  if(fstart)
    show(showpos);
//    image=Image.createRGBImage( scr, width, height, false); 
//    g.drawImage(image, 0, 0, Graphics.TOP|Graphics.LEFT);	

  //  int i,j;
//  for(i=0,j=color++;i<132*176;i++){
//    screen[i]=j++;
//  }
}

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: break; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
//    if(keycode==RED_BUTTON) return 1;
    return keyPressed(keycode);
    //onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}




void onclose(){ // Закрытие окна
  //  running=0; // Сигнал на остановку фонового процесса
//  GBS_StopTimer(&timer); // Останавливаем таймер  pickoff!!
//  savelog();  // Сохраняем лог
}

void onexit(){ // Выход
  un7zexit();
  exit();
  //  if(buf) mfree(buf); // Освобождаем память
}

void oncreate(){ // Создание окна
//  SUBPROC((void *)execute); // Запускаем фоновый процесс 
//  GBS_StartTimerProc(&timer,262/2,timer_proc); // Стартуем таймер с частотой 2 раз в секунду
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  strcpy(filename, exename);
  file=strrchr(filename,'\\')+1;
  strcpy(file,"data");
  if(!(alldata=loadfile(filename))) return 2;
  if(!un7zinit(alldata)) return 3;
  if(maxcnt<54) return 4;
  Psy();
  if(start()) return 1;
  return 0;
}
