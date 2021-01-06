
// Игра Balloons 0.3  (c)cbn  http://cbn.narod.ru
// Собираем кучи блоков

#define NEWSGOLD
//NEWSGOLD должно быть задано ВСЕГДА!
//т.к. Siemens.c автоопределяет тип мобилы.

#include "..\swilib.h" // Главная библ. - берем ее из др.примеров
#include "..\random.h" // "Случайные" числа

char *Title="Balloons 0.3 (c)bn";

typedef unsigned char byte;
extern int width, height;
const int block=10;
extern char *screen;//[132*176]; // Экран 132*176
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
//unsigned int err;
int f;
#define RGB8(R,G,B) (B+(G<<2)+(R<<5))

const char *errors[]={0};

char filename[128]; // Храним имя sav файла
int maxy=17, maxxy=17*13;
#define maxx 13
#define maxyy 247
#define rec 248
#define maxrec 252
#define datasize 256
byte data[datasize];  // Буфер с параметрами и данными стакана
#define dat(x,y) data[(y)*maxx+(x)]

const byte curcolor=0xff;//RGB8(0,0,3);
const byte colors[]={ // Цвета фигур
  0, RGB8(7,0,0),RGB8(0,7,0),RGB8(0,0,3),RGB8(7,0,3),
};

int curx=maxx/2, cury=17/2;
byte col; //tmp color
int del; //tmp число удал.ячеек

//void *memset(void *mem, int val, int size){
//  char *s=(char*)mem;
//  while(--size>=0) *s++=(char)val;
//  return mem;
//}

void newgame(){ //новая игра
  int i;
  byte *ptr=data;
  memset(screen,0,screensize);
  memset(data,0,maxrec);
  //генерируем случ. ячейки
  for(i=0;i<maxxy;i++)
    *ptr++=(rand()&3)+1;
}

int endgame(){ //проверка закончилась ли игра?
  int curx,cury;
  for(cury=0;cury<maxy;cury++)
    for(curx=0;curx<maxx;curx++)
    if(col=dat(curx,cury)){
      if(curx>0 && dat(curx-1,cury)==col) return 0;
      if(curx<maxx-1 && dat(curx+1,cury)==col) return 0;
      if(cury>0 && dat(curx,cury-1)==col) return 0;
      if(cury<maxy-1 && dat(curx,cury+1)==col) return 0;
    }
  //игра законч.
  char msg[32];
  sprintf(msg,"Очков: %d\nРекорд: %d",*(int*)(data+rec), *(int*)(data+maxrec));
  if(*(int*)(data+rec)>*(int*)(data+maxrec)) *(int*)(data+maxrec)=*(int*)(data+rec);
  ShowMSG(1,(int)msg);
  newgame();
  return 1;
}


void down(){ //падаем вниз (удал.пустых ячеек)
  int i=maxxy,j,k;
  while(--i>=maxx){
    if(!data[i]){ //пустая ячейка - падаем сверху
      j=i;
      k=0;
      while(j>=maxx){
        if(data[j]=data[j-maxx]) k=1;
        j-=maxx;
      }
      data[j]=0;
      if(k) ++i;
    }
  }
}

void is(int curx,int cury){ //рекурсивное удаление ближлежайших ячеек с цветом col
  ++del;
  dat(curx,cury)=0;
  if(curx>0 && dat(curx-1,cury)==col) is(curx-1,cury);
  if(curx<maxx-1 && dat(curx+1,cury)==col) is(curx+1,cury);
  if(cury>0 && dat(curx,cury-1)==col) is(curx,cury-1);
  if(cury<maxy-1 && dat(curx,cury+1)==col) is(curx,cury+1);
}

void enter(){ //нажата кл. enter
//  int pos=cury*maxx+curx;
  if(col=dat(curx,cury)){
    del=0;
    is(curx,cury); //рекурсивно проверяем яч.
    if(del>1){
      *(int*)(data+rec)+=del*(del-1);
      down();
    }else dat(curx,cury)=col;
  }
}

void onredraw(){ // Перерисовка экрана screen[132*176]
  //нарисовать "ячейки"
  int i,j,k;
  char *sc, *scr=screen+width+1;
  byte *dat=data, color;
  for(j=0;j<maxy;j++){
    sc=scr;
    for(i=0;i<maxx;i++){
      color=colors[*dat++];
      for(k=0;k<block;k++,scr+=width)
        memset(scr,color,block);
      scr-=width*block-block;
    }
    scr=sc+width*block;
  }
  //нарисовать курсор
  scr=screen+width+1+cury*block*width+curx*block;
  memset(scr,curcolor,block);
  for(i=0;i<block;i++,scr+=width)
    scr[0]=scr[block-1]=curcolor;
  memset(scr-width,curcolor,block);
}


int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    switch(keycode){ // Код клавиши
    case RED_BUTTON: return 1; // Выход
    case GREEN_BUTTON: 
      maxy=(maxy==17)?13:17;
      maxxy=maxx*maxy;
      if(cury>=maxy) cury=maxy-1;
    case LEFT_SOFT: case RIGHT_SOFT:
      newgame(); break;
    //перемещ. курсора
    case LEFT_BUTTON: case '4': 
      if(--curx<0) curx=maxx-1; break;
    case RIGHT_BUTTON: case '6': 
      if(++curx>=maxx) curx=0; break;
    case UP_BUTTON: case '2':
      if(--cury<0) cury=maxy-1; break;
    case DOWN_BUTTON: case '8': 
      if(++cury>=maxy) cury=0; break;
    case ENTER_BUTTON: case '5': 
      enter(); if(endgame()) return 0;
      break;
    default: return 0;
    }
  }
  onredraw(); DrawScreen(); // Перерисовать экран
  return 0;
}

void savegame(){ // Записать игру
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    data[maxyy]=(byte)maxy;
    fwrite(f,data,datasize,&err); 
    fclose(f,&err);
}}

void loadgame(){ // Загрузить игру
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    if(fread(f,data,datasize,&err)==datasize){
      maxy=data[maxyy];
      maxxy=maxx*maxy;
      endgame();
    }else newgame();
    fclose(f,&err);
  }else newgame();
}

void onclose(){ // Закрытие окна
  savegame();  // Сохраняем результаты
}

void onexit(){ // Выход
}

void oncreate(){ // Создание окна
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  strcpy(filename,exename);
  memcpy(filename+strlen(filename)-3,"sav",4);
  Randomize();
  loadgame();
  return 0;
}

