
// Игра Mozaic

//#define HIGHCOLOR // 16-битный режим
//#define GRAPH  // Графика
#include "..\swilib.h" // Главная библ. - берем ее из др.примеров
#include "..\random.h" // "Случайные" числа
#include "..\zfont.h"

char *Title="Mozaic 0.1 (c)bn";
extern int width, height;
typedef unsigned char byte;
extern short *screen; // Экран 132*176
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
void enter(); // Нажат enter
int newgame(); // Начать новую игру

const char *errors[]={
  0,
  "Вызов: ... Файл.bmp\0",
  "Ошибка загрузки рисунка\0",
  "Неверные размеры рисунка!\0",
  "Недостаточно памяти\0"
};

//x*y
#define maxy 9
const byte cxy[]={2,3,  3,4,  4,5,  5,6,  5,7,  5,8,  6,8,  7,9, 8,10, 10,12};
byte allsize=4;

#define maxpole 2
int mode=0; //режим: 0=выбор уровня, 1=просмотр картинки, 2,3 - экраны
int sel=0; //взято?
byte *ppic;
char *bmp=0, *back=0; // рисунок и бэкбуфер
byte *pole=0;

int curx, cury; // курсор
int sizex, sizey; // шаг курсора
int sizex2, sizey2;
int isizex, isizey;
int cntx, cnty; // кусочков
int cntx2, cnty2;
int dx, dy; // отступ для дырочек


inline void drawsym(short *out, char c){ // Отобразить символ на экране
  int i,j;
  unsigned char b, *bptr=(unsigned char*)zfont+((c-=0x20)<=0?0:(c<<3));
  for(j=0;j<8;j++){
    b=*bptr++;
    for(i=0;i<8;i++){
      *out++=(b&0x80)?0xffff:0;//0x1f; //colors 0xffff
      b<<=1;
    }
    out+=width-8;
  }
}

inline void drawhelp(){ // Показать меню
  int i=0,x=0,y=0;
  char menu[32];
  sprintf(menu,"  Puzzles: %d",cxy[allsize*2]*cxy[allsize*2+1]);
  while(menu[i]){
    if(menu[i]=='\n' || x>=width/8){ x=0; ++y;}
    if(y>=height/10) break;
    drawsym(screen+y*width*10+x*8+4,menu[i]);
    ++x;
    ++i;
  }
}

#define curcolor 0xffe0
#define selcolor 0x7ff


inline void showcur(){
  int i, color=sel?selcolor:curcolor;
  short *scr=screen+(sizey2*width)*cury+sizex2*curx;
  memsetw(scr,color,sizex2);
  for(i=0;i<sizey2;i++,scr+=width)
    scr[0]=scr[sizex2-1]=color;
  memsetw(scr,color,sizex2);
}

void onredraw(){ // Перерисовка экрана screen[132*176]
//  WSHDR *ws;
  int x,y,z;
  byte *p;
  memsetd(screen,0,screensize>>2);
  switch(mode){
  case 0: //input mozaic size
    drawhelp();
    break;
  case 1: //draw all pic
    movsd(screen,bmp+4,screensize>>2);
    break;
  case 2: case 3: //draw table 2 or 3
    p=pole+(mode-2)*cntx*cnty*4;
    for(y=0;y<cnty2;y++)
      for(x=0;x<cntx2;x++){
        if(z=p[y*cntx2+x]){
          bitblt(screen,back, x*sizex2,y*sizey2, sizex,sizey, dx,dy+isizey*(z-1), 0,0);
        }
      }
    showcur();
    break;
  }
//  bitblt(screen,dev, x-devsize/2,y-devsize/2, devsize,devsize,  (seldev&3)*devsize, (seldev>>2)*devsize, 0x1f,0);
}

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(keycode==RED_BUTTON) return 1;
    switch(mode){
    default: case 0: //input mozaic size
      switch(keycode){
      case UP_BUTTON: case LEFT_BUTTON:    if(allsize>0) --allsize; break;
      case DOWN_BUTTON: case RIGHT_BUTTON: if(allsize<maxy) ++allsize; break;
      case ENTER_BUTTON: case '5': newgame(); mode=1; break;
      default: return 0;
      }break;
    case 1: //draw all pic
      if(keycode=='0') return 1;
      mode=2; break;
    case 2: case 3: 
      switch(keycode){
      case GREEN_BUTTON:
      case LEFT_SOFT:        
        mode=1; break;
      case RIGHT_SOFT:
        if(++mode>maxpole+1) mode=2; break;
      case LEFT_BUTTON: case '4':
        if(curx>0) --curx; else curx=cntx2-1; break;
      case RIGHT_BUTTON: case '6': 
        if(++curx>=cntx2) curx=0; break;
      case UP_BUTTON: case '2': 
        if(cury>0) --cury; else cury=cnty2-1; break;
      case DOWN_BUTTON: case '8': 
        if(++cury>=cnty2) cury=0; break;
      case ENTER_BUTTON: case '5': enter(); break;
      default: return 0;
      }break;
    }
  onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}


void onclose(){ // Закрытие окна
}

void onexit(){ // Выход
  if(back) mfree(back);
  if(bmp) mfree(bmp);
  if(pole) mfree(pole);
}

void oncreate(){ // Создание окна
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  if(!fname || fname[1]!=':') //return 1;
    strcpy(strrchr(fname=exename,'.'),".moz");
  if(!(bmp=loadgraph(fname))) return 2;
  if(*(short*)bmp!=width || *(short*)(bmp+2)!=height) return 3;
  Randomize();
  return 0;
}

int newgame(){ // Начать новую игру
  int x,y,z;
  short *s, *ss;
  //sizex,y  посчитать из allsize
  dx=(sizex=width/(cntx=cxy[allsize*2]))>>2;
  dy=(sizey=height/(cnty=cxy[allsize*2+1]))>>2;
  sizex2=sizex>>1; sizey2=sizey>>1;
  if(back) mfree(back);
  if(!(back=malloc(z=4+(isizex=sizex+dx+dx)*(y=(isizey=sizey+dy+dy)*cntx*cnty)*2))) return 1;
  memset(back,0,z);
  *(short*)back=isizex; *(short*)(back+2)=y;
  //перенести кусочки (пока без шаблона вырезок)
  s=(short*)back+2+dx+dy*isizex;
  for(y=0;y<cnty;y++)
    for(x=0;x<cntx;x++){
      ss=(short*)bmp+2+y*sizey* *(short*)bmp + x*sizex;
      for(z=0;z<sizey;z++,s+=isizex, ss+=*(short*)bmp){
        memcpy(s,ss,sizex*2);
      }
      s+=(dy+dy)*isizex;
    }
  // заполнить pole
  if(pole) mfree(pole);
  if(!(pole=(byte*)malloc(z=cntx*cnty*4*maxpole))) return 2;
  memset(pole,0,z);
  x=cntx*cnty;
  while(x>0){  //кусок начинается с 1 !!!!!!!
    while(pole[y=randint(z)]);
    pole[y]=x--;
  }
  cntx2=cntx*2; cnty2=cnty*2;
  return mode=sel=0;
}

inline int isvict(){ //победа?
  int x,y,z;
  byte *p=pole+(mode-2)*cntx*cnty*4;
  for(y=z=0;y<cnty2;y+=2){
    for(x=0;x<cntx2;x+=2){
      if(p[x]!=++z) return 0;
    }
    p+=cntx2+cntx2;
  }
  return 1;
}

void enter(){ // Нажат enter
  byte *p=pole+(mode-2)*cntx*cnty*4 + cury*cntx2+curx;
  if(sel){ //ложим
    if(!*p){ //свободно
      *p=*ppic; *ppic=0;
    }
    sel=0;
  }else{ //берем
    if(*p){
      ppic=p;
      sel=1;
    }
  }
  if(isvict()) mode=0;
}
