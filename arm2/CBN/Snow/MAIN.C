
// Snow - снег (новогодний эльф)

//#define HIGHCOLOR // 16-битный режим
//#define GRAPH  // Графика
//#define UNPACK // Распаковка архивов
//#define NOZIP  // Кроме zip
//#define NORAR  // Кроме rar
#include "..\swilib.h"
#include "..\random.h"
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

char *Title="Snow New Year(c)bn";
const char *errors[]={
 0,
 "Нету памяти!",
 "Неверный .png(bmp) файл!"
};

typedef unsigned char byte;
//const int width=132, height=176, widhei=132*176;
extern short *screen;//[width*height]; // Экран 132*176*2
extern int width, height, screensize;
int widhei;//=(screensize>>1);

volatile int running=0;

int sgf=0;
char *gf=0;
short *back=0;//[width*height]; //бэкбуфер
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw(void);

#define maxcolors 16
unsigned short colors[maxcolors]={ 
  RGB16(15,31,0), RGB16(0,31,15), RGB16(15,0,15), RGB16(31,63,31),
  RGB16(31,63,0), RGB16(0,63,31), RGB16(31,0,31), RGB16(31,63,31), 
  RGB16(31,0,0), RGB16(0,63,0), RGB16(0,0,31), RGB16(31,63,31),
  RGB16(15,0,0), RGB16(0,31,0), RGB16(0,0,15), RGB16(31,63,31)
};
#define stepsnow 64
#define maxisnow 2048
int maxsnow=1024;//256+64;
unsigned short snow[maxisnow];
byte type[maxisnow], color[maxisnow];
#define maxtime 5
#define maxtype 7
const byte time[maxtime]={256/7,256/10,256/15,256/20,256/25};
int timenum=2;

int vtime=0; //направление ветра 0 -n +n, уже упало строк и время до оконч.

void initsnow(){
  int i;
  unsigned int j;
  for(i=0;i<maxsnow;i++){
    j=Random()|(Random()<<8);
    while(j>=widhei) j-=widhei;
    snow[i]=j?j:1;
    j=Random();
    type[i]=j&maxtype;
    color[i]=(j>>4)&0xf;
   }
}

void onredraw(){} //нарисовать все

void onredraw2(){ //нарисовать все
  //memcpy(screen,back,screensize);
  movsd(screen,back,screensize/4);
  int i,j,x;
  short *p;
  ++vtime;
  for(i=0;i<maxsnow;i++){
    switch(type[i]){ //типы снежинок
    case 0: x=width; break;//падает вниз
    case 1: x=width*2; break; //средне падает вниз
    case 2: x=width*3; break; //быстро падает вниз
    case 3: x=width*2+((vtime&0x10)?1:-1); break;
    case 4: x=width+((vtime&0x8)?1:-1); break;
    case 5: x=width-((vtime&0x10)?1:-1); break;
    case 6: x=width*3-((vtime&0x8)?1:-1); break;
    default: x=width+((vtime&0x10)?1:-1); break;
    }
    if((snow[i]+=x)>=widhei){
      snow[i]=Random()+1;
      j=Random();
      type[i]=j&maxtype;
      color[i]=(j>>4)&0xf;
    }
    if(i&7) screen[snow[i]]=colors[color[i]];
    else{
      p=(short*)(gf+4);
      for(j=0;j<sgf; j++,p++)
        if(*p) *p=colors[color[i]];
      bitblt(screen, gf, snow[i]%width, snow[i]/width, 0,0,0,0,0,0x40);
    }
  }
}

//GBSTMR timer;
//void timer_proc(void){ // Функция выполняется по таймеру
//  REDRAW(); // Перерисовать экран 
//  GBS_StartTimerProc(&timer,time[timenum],timer_proc); // Стартуем таймер с частотой 10 раз в секунду
//}

void execute(){ // Выполняем basic код
  running=1;
  while(running){ // Пока нет команды на останов
    onredraw2();
    REDRAW();
  }
}

//void onredraw(void){ // Перерисовка экрана screen[132*176]
//  int i,j;
//  for(i=0,j=color++;i<132*176;i++){
//    screen[i]=j++;
//  }
//}

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: break; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    switch(keycode){ // Код клавиши
    case RED_BUTTON: 
    case LEFT_SOFT:
    case RIGHT_SOFT:
      return 1; // Выход
    case RIGHT_BUTTON:
      if((maxsnow+=stepsnow)>maxisnow) maxsnow=maxisnow;
      initsnow(); break;
    case LEFT_BUTTON:
      if((maxsnow-=stepsnow)<stepsnow) maxsnow=stepsnow;
      initsnow(); break;
    case UP_BUTTON:
      if(--timenum<0) timenum=0; break;
    case DOWN_BUTTON:
      if(++timenum>=maxtime) timenum=maxtime-1; break;
    }
 //   onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

void onclose(){ // Закрытие окна
  running=0;
  //GBS_DelTimer(&timer); // Останавливаем таймер  pickoff!!
}

void onexit(){ // Выход
  if(gf) mfree(gf); // Освобождаем память
  if(back) mfree(back);
}

void oncreate(){ // Создание окна
  SUBPROC((void *)execute); // Запускаем фоновый процесс 
  //GBS_StartTimerProc(&timer,26,timer_proc); // Стартуем таймер 
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  char *bmp;
  int x,y;
  widhei=screensize>>1;
  if(!(back=(short*)malloc(screensize))) return 1;
  memset(back,0,screensize);
  memcpy(exename+strlen(exename)-3,"png",4);
  if(!(gf=loadgraph(exename))) return 2;
  sgf=*(short*)gf* *(short*)(gf+2);
//  if(!fname){
    memcpy(exename+strlen(exename)-3,"bmp",4);
//    bmp=exename;
//  }else bmp=fname;
  if(bmp=loadgraph(exename)){ //фон в back буфер
    if(*(short*)bmp==width && *(short*)(bmp+2)==height){
      memcpy(back,bmp+4,screensize);
    }else{
      x=(width-*(short*)bmp)>>1;
      y=(height-*(short*)(bmp+2))>>1;
      bitblt(back, bmp, x<0?0:x, y<0?0:y, 0,0,0,0,0,0);
    }
    mfree(bmp);
  }//else return 1;
  Randomize();
  initsnow();
  return 0;
}
