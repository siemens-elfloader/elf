
// PPoint 0.1

#define HIGHCOLOR // 16-битный режим
#define GRAPH  // Графика
#define UNPACK // Распаковка архивов
//?
#define NOZIP  // Кроме zip 
#define NORAR  // Кроме rar

#include "..\swilib.h" // Главная библ. - берем ее из др.примеров
#include "..\font.h"
//#include "..\random.h" // "Случайные" числа

char *Title="PPoint 0.3 (c)bn";
extern int width, height;
typedef unsigned char byte;
extern short *screen;//[132*176]; // Экран 132*176
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

int delay=262/2;
const int curcolor=0x1f, selcolor=0xffff;
const int colw=RGB16(11,22,11), colb=RGB16(8,16,8);
const int FONMAX=0xe0, FONSIZEY=7, FONSIZEX=6;
const int color=0xffff, bkcolor=0;// Цвета текста и фона

short *back=0;//[132*176]; //бэкбуфер
char *lnk=0, *wall=0, *ptr; //free
char path[256], *file;
byte *symptr[256]; //* символы
byte sym[256];  // стр. симв.

void initfont();
void nextframe();
void textout(char *s, int y, int x, int maxx, int textcolor);

GBSTMR timer;
void timer_proc(){ // Функция выполняется по таймеру
  nextframe();
}  


void onredraw(void){ // Перерисовка экрана screen[132*176]
//  drawtable();
//  if(selx>=0) drawcur(selx,sely,&sell,RGB16(31,63,0));
//  drawcur(curx,cury,&curl,RGB16(31,0,0));
}

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
      switch(keycode){ // Код клавиши
      case RED_BUTTON: 
      case ENTER_BUTTON:
      case LEFT_SOFT:
      case RIGHT_SOFT:
      case GREEN_BUTTON: return 1; // Выход
//      default: nextframe(); break;
  }}
  return 0;
}


void onexit(){ // Выход
  if(lnk) mfree(lnk);
  if(wall) mfree(wall);
  if(back) mfree(back);
}

void onclose(){ // Закрытие окна
  GBS_DelTimer(&timer); 
}

void oncreate(){ // Создание окна
  GBS_StartTimerProc(&timer,10,timer_proc); // Стартуем таймер с частотой N раз в секунду
}

void loadppt(){ //должно кончаться 0!
  char *s, *ss;
  s=ss=lnk;
  do{
    while(*s==' ') ++s;
    if(!*s) break;
    if(*s==';'){
      while(*++s && *s!=0xd);
    }else{ //команда
      if(*s!=0xd){
        do{
          *ss++=*s++;
        }while(*s && *s!=0xd);
        *ss++=0;
      }
    }
    if(!*s) break;
    if(*++s==0xa) ++s;
  }while(*s);
  *ss++=0;
  //Преобразуем в нижний регистр
  s=lnk;
  do{
    if(*s<'0' || *s>'9'){
      --s;
      while(*++s && *s!='=') *s|=0x20;
    }
    while(*s) ++s;
    ++s;
  }while(*s);
}



int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  strcpy(path,fname);
  file=path+strlen(path);
  while(*--file!='\\');
  ++file;
  if(!fname || !(ptr=lnk=loadfile(fname))) return 1;
  lnk[loadfilesize-2]=0;
  if(!(back=(short*)malloc(screensize))) return 1;
  loadppt();
  if(!*lnk) return 1; //пусто
  initfont();
//  Randomize();
  return 0;
}

/////////////
void setcodepage(int page){ // Подг. табл. перекод. симв.
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

void initfont(){  // Подготовить шрифт
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

int slen(char *s){ // Длина строки в тчк.
  int i=0;
  while(*s) i+=font[sym[*(byte*)s++]];
  return i;
}

///////////тута специф. PPoint//////////
const int maxcmd=10; //ВСЕГО команд

const char *command[]={
"textcolor=",
"backcolor=",
"wallcolor=",
"maskcolor=",
"textsize=",
"next=",
"wait=",
"speed=",
"loop=",
"wallpaper="
};

int textcolor, backcolor, wallcolor, maskcolor, textsize=1, next=0, wait=0, speed=1, loop=1;
byte fastfon=0;

int *cmdat[]={
&textcolor, 
&backcolor, 
&wallcolor, 
&maskcolor, 
&textsize, 
&next, 
&wait, 
&speed, 
&loop,
0
};

inline void cls(){
  memsetw(back,wallcolor,screensize>>1);
//  for(int i=0;i<132*176;i++) back[i]=wallcolor;
}

inline void centerbmp(char *bmp){
  if(bmp){
  int x=(width-*(short*)bmp)>>1, y=(height-*(short*)(bmp+2))>>1;
    bitblt(back, bmp, x<0?0:x, y<0?0:y, 0,0,0,0,0,0);
  }
}

inline void showfon(){ 
  if(fastfon) memcpy(back,wall+4,screensize);
  else{
    cls();
    centerbmp(wall);
  }
}

inline int getval(){
  int val=0;
  char *s=ptr;
  while(*++s && *s!=' ');
  if(*--s=='h'){ //hex
    s=ptr-1;
    while(*++s && *s!=' '){
      if(*s>='0' && *s<='9') val=(val<<4)+*s-'0';
      else if((*s|=0x20)>='a' && *s<='f') val=(val<<4)+*s-'a'+10;
      else break;
    }
  }else{ //dec
    s=ptr-1;
    while(*++s && *s>='0' && *s<='9') val=val*10+*s-'0';
  }
  return val;
}


inline int docmd(int num){ //команда=
  ptr+=strlen(command[num]);
  if(num!=9){ //числа
    *cmdat[num]=getval();
    ptr+=strlen(ptr)+1;///??
  }
  switch(num){
  case 5: //next
    showfon();
    memcpy(screen,back,screensize);
    //wait=next; //эффект here! и ПЕРЕХОД
    return !wait;
  case 6: //wait
    return 0;
  case 7: //speed
    if(!speed) delay=262*3;
    else delay=262/speed;
    break;
  case 8: //loop
    break;
  case 9: //wallpaper
    if(wall) mfree(wall); wall=0;
    if(*ptr){
      if(ptr[1]==':')
        wall=loadgraph(ptr);
      else{
        strcpy(file,ptr);
        wall=loadgraph(path);
      }
    }
    fastfon=(wall && *(short*)wall==width && *(short*)(wall+2)==height);
    ptr+=strlen(ptr)+1;///??
    break;
  }
  return 1;
}

inline int docmdxy(){ // х у номер ...
  int x=0,y=0,z=0;
  char *bmp;
  --ptr;
  while(*++ptr>='0' && *ptr<='9') x=x*10+*ptr-'0';
  while(*++ptr>='0' && *ptr<='9') y=y*10+*ptr-'0';
  while(*++ptr>='0' && *ptr<='9') z=z*10+*ptr-'0';
  if(*++ptr=='"'){ //строка
    //удалить посл. ""
    bmp=ptr++;
    while(*++bmp && *bmp!='"');
    if(*bmp) *bmp=' ';
    //z???????? эффект!
    textout(ptr,y,x,0,textcolor);
  }else{ //рис.
    if(ptr[1]==':')
      bmp=loadgraph(ptr);
    else{
      strcpy(file,ptr);
//      ShowMSG(1,(int)path);////////
      bmp=loadgraph(path);
    }
    //z???????? эффект!
    if(bmp){
      bitblt(screen, bmp, x, y, 0,0,0,0,maskcolor,0);
      mfree(bmp);
    }
  }
  ptr+=strlen(ptr)+1;//??
  return !z;
}

//сравнение подстрок
inline int cmdcmp(char *s, const char *cmd){ //s=324234, "abc="
  while(*cmd && *s++==*cmd++);
  if(*--s=='=' && *--cmd=='=') return 1;
  return 0;
}

//ret 1 если нужно повторить
int nextline(){ // Выполн. след. строку ptr  
//  char *s;
  int i;
  if(!*ptr) ptr=lnk;
  if(*ptr<'0' || *ptr>'9'){ //не число
    for(i=0;i<maxcmd;i++){
      if(*ptr==*command[i] && cmdcmp(ptr,command[i])){ //эта команда
        return docmd(i);
        //break;
      }
    }
    return 1;//nothing to do
  }else{ //число x y ...
    return docmdxy();
  }
}

//int col=1;

void nextframe(){ // Выполн. след. команду (запуск по таймеру)
  if(wait>0) --wait;
  else{
    while(nextline());
    REDRAW();
  }
  GBS_StartTimerProc(&timer,delay,timer_proc);
}

