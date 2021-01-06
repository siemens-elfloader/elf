
// Игра Lines

#define HIGHCOLOR // 16-битный режим
#define GRAPH  // Графика
#include "..\swilib.h" // Главная библ. - берем ее из др.примеров
#include "..\random.h" // "Случайные" числа

char *Title="Lines 0.3 (c)bn";
extern int width, height;
typedef unsigned char byte;
extern short *screen;//[132*176]; // Экран 132*176
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
void enter(); // Нажат enter
void newgame(); // Начать новую игру
int tabempty(void); // Нет больше шариков
int dropball();  // Бросить n шариков

#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))
const int curcolor=0x1f, selcolor=RGB16(31,0,31), bkcolor=RGB16(22,44,22);
const int colw=0xffff, colb=RGB16(8,16,8);

#define cx curx
#define cy cury
#define ccx selx
#define ccy sely
const int drop=3, lpick=5, squares=0;
#define tab(xx,yy) data[(yy)*maxx+(xx)]
#define tab2(xx,yy) data2[(yy)*(maxx+2)+(xx)]

char *bmp=0, *smbmp=0;
char filename[128]; // Храним имя файла
char data[10*13];
byte data2[12*15];  // Буфер с параметрами и данными поля

const int maxx=10, maxx2=12;
int curx=5,cury=5, selx=-1, sely=-1, maxy=10, maxy2;
int points=0;

void drawcur(int curx, int cury, int color){
  int i;
  short *scr=screen+(cury*13)*width+curx*13;
  memsetw((scr+=width)+1,color,11);
//  memsetw(scr+=width,color,13);
  for(i=0;i<10;i++,scr+=width){
    scr[1]=scr[11]=color;
  }
  memsetw(scr+1,color,11);
//  memsetw(scr+width,color,13);
}

void drawtable(){ // Рисукм табличку
  int i,j;
  short *scr=screen;
  memset(screen,0,screensize);
  for(i=0;i<width*13*maxy;i++) screen[i]=bkcolor;
//  for(i=0;i<132*13*maxy;i++) screen[i]=bkcolor;
  //сетка
  for(i=0;i<maxy;i++,scr+=width*13){
    memsetw(scr,colw,130);
    memsetw(scr+width*12,colb,130);
  }
  for(scr=screen,i=0;i<maxy*13;i++,scr+=width)
    for(j=0;j<130;j+=13){
      scr[j]=colw;
      scr[j+12]=colb;
    }
}

void drawballs(){ // Рисуем мячики
  int x,y,i,k;
  for(y=0;y<maxy;y++)
    for(x=0;x<maxx;x++)
      if(i=data[y*maxx+x])
        if(i&0x80){ // маленький мячик
          k=(i&0x7f)-1;
          if(k<0 || k>6){ k=0; data[y*maxx+x]=1|0x80;}
          bitblt(screen,smbmp,x*13+4,y*13+4, 5,5, 0,k*5, 0,0);
        }else{
          k=i-1;
          if(k<0 || k>6){ k=0; data[y*maxx+x]=1;}
          bitblt(screen,bmp,x*13+1,y*13+1, 11,11, 0,k*11, 0,0);
        }
}

void onredraw(void){ // Перерисовка экрана screen[132*176]
  drawtable();
  drawballs();
  drawcur(curx,cury,curcolor);
  if(selx>=0) drawcur(selx,sely,selcolor);
}

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
      switch(keycode){ // Код клавиши
      case RED_BUTTON: case GREEN_BUTTON: return 1; // Выход
      //case GREEN_BUTTON: 
      case RIGHT_SOFT:
        newgame(); break;
//      case LEFT_SOFT:
//        maxy=(maxy==10)?13:10;
//        curx=cury=5; selx=sely=-1;
//        if(tabempty()) dropball();
//        break;
      case LEFT_BUTTON: case '4':
        if(--curx<0) curx=maxx-1; break;
      case RIGHT_BUTTON: case '6': 
        if(++curx>=maxx) curx=0; break;
      case UP_BUTTON: case '2': 
        if(--cury<0) cury=maxy-1; break;
      case DOWN_BUTTON: case '8': 
        if(++cury>=maxy) cury=0; break;
      case ENTER_BUTTON: case '5': enter(); break;
      default: return 0;
  }
  onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

inline void savegame(){ // Записать игру
  int f;
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    fwrite(f,data,sizeof(data),&err); 
    fclose(f,&err);
}}


void onclose(){ // Закрытие окна
  savegame();  // Сохраняем результаты
}

void onexit(){ // Выход
  if(bmp) mfree(bmp);
  if(smbmp) mfree(smbmp);
}

void oncreate(){ // Создание окна
  //REDRAW();//??
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  int f,i;
  strcpy(filename,exename);
  memcpy(filename+(i=strlen(filename)-3),"bmp",4);
  if(!(bmp=loadgraph(filename))) return 1;
  memcpy(filename+i,"gif",4);
  if(!(smbmp=loadgraph(filename))) return 1;
  memcpy(filename+i,"sav",4);
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f,data,sizeof(data),&err);
    fclose(f,&err);
  }else newgame();
  Randomize();
  return 0;
}

//////////////// Ниже специфичные lines функции /////////////////////

inline void showadd(int x, int y){} //fake

int square(int x, int y, char color){ // Квадрат?
  if(x<0 || y<0 || x>=maxx-1 || y>=maxy-1) return 0;
  return (tab(x,y)==color && tab(x+1,y)==color && tab(x,y+1)==color && tab(x+1,y+1)==color);
}

void delsquare(int x, int y){ // Удалить квадрат
  tab(x,y)=tab(x+1,y)=tab(x,y+1)=tab(x+1,y+1)=0;
//  showadd(x,y); showadd(x+1,y); showadd(x,y+1); showadd(x+1,y+1);
}

int cmpdel(int x, int y){  // Проверить позицию x,y на удаление + showadd
  int x1,x2,x3,x4,x5,x6;
  int y1,y2,y3,y4,y5,y6;
  int n=0;
  char c;
if((c=tab(x,y))>0){
  if(squares){  // Квадратами
//    x1=square(x,y,c);
//    x2=square(x-1,y,c);
//    x3=square(x,y-1,c);
//    x4=square(x-1,y-1,c);
//    if(x1){ n=4; delsquare(x,y);}
//    if(x2){ n+=4-((n)?2:0); delsquare(x-1,y);}
//    if(x3){ n+=4-((n)?2:0); delsquare(x,y-1);}
//    if(x4){ n+=4-((n)?2:0); delsquare(x-1,y-1);}
//    lpick=4;
  }else{
  x1=x3=x5=x;
  y1=y3=y5=y;
  //вертикально
  while(--y1>=0 && tab(x,y1)==c); y2=++y1;
  while(++y2<maxy && tab(x,y2)==c);
  //горизонтально
  while(--x1>=0 && tab(x1,y)==c); x2=++x1;
  while(++x2<maxx && tab(x2,y)==c);
  //слева сверху вниз вправо
  --x3,--y3;
  while(x3>=0 && y3>=0 && tab(x3,y3)==c) --x3,--y3; 
  x4=++x3+1; y4=++y3+1;
  while(x4<maxx && y4<maxy && tab(x4,y4)==c) ++x4,++y4;
  //справа сверху вниз влево
  ++x5,--y5;
  while(x5<maxx && y5>=0 && tab(x5,y5)==c) ++x5,--y5; 
  x6=--x5-1; y6=++y5+1; 
  while(x6>=0 && y6<maxy && tab(x6,y6)==c) --x6,++y6;
  //рез-т (кол-во шаров)
  if(y2-y1>=lpick){ n=y2-y1; while(y1<y2){ tab(x,y1)=0; showadd(x,y1++);}}
  if(x2-x1>=lpick){ n+=x2-x1-((n)?1:0); while(x1<x2){ tab(x1,y)=0; showadd(x1++,y);}}
  if(y4-y3>=lpick){ n+=y4-y3-((n)?1:0); while(y3<y4){ tab(x3,y3)=0; showadd(x3++,y3++);}}
  if(y6-y5>=lpick){ n+=y6-y5-((n)?1:0); while(y5<y6){ tab(x5,y5)=0; showadd(x5--,y5++);}}
  }
  if(n){ showadd((char)255,(char)255);  points+=(n-lpick+1)*lpick; //PlaySound(3);
} }
  return n;
}

#define ttt if(*tt==(byte)253) return 0; if(*tt==(byte)254) *tt=Ni+1

int ismove(void){  // Можно ли переместить ccx,ccy в cx,cy
  // Волновой алгоритм поиска (взято от Медноногова)
  //if(l.f&moveany) return 0;
  byte *t, *tt;
  int maxy2=maxy+2;
  int i,j,k,Ni=0,size2=maxx2*maxy;
//  undoflag=0;
  memset(data2-maxx2-1,255,maxx2*maxy2);
  for(j=k=0;j<maxy;j++)
    for(i=0;i<maxx;i++)
      if(data[k++]<=0) --tab2(i,j);
  tab2(cx,cy)=0;
  tab2(ccx,ccy)=(byte)253;
  do
    for(i=0,t=data2;i<size2;i++,t++)
      if(*t==Ni){
        tt=t+1; ttt;
        tt=t-1; ttt;
        tt=t+maxx2; ttt;
        tt=t-maxx2; ttt;
      }
  while(++Ni<252);
  return 1;
}

int nextb(int drop, int flag){ // Следующие шарики 0x80, бросить 0
  int i,j,k,l;
  for(l=0;l<drop;l++){  
    for(i=0,j=0;i<maxx*maxy;i++)
      if(!data[i]) ++j;
    if(!j) return 1;
    k=Random()%j;
    for(i=0,j=0;i<maxx*maxy;i++)
      if(!data[i] && ++j>=k) break;
    data[i]=(char)(((Random()&7)+1)|flag);
    if(!flag) cmpdel(i%maxx,i/maxx);
  }  
  return 0;
}

inline int nextball(){
  return nextb(drop,0x80);
}

//nextball(drop,0x80);

int dropball(){  // Бросить n шариков
  int i,m;
  for(i=0,m=0;i<maxx*maxy;i++)
    if(data[i]<0){ data[i]&=0x7f; ++m; cmpdel(i%maxx,i/maxx);}
  return nextb(drop-m,0);
}

//void movestep(void){  // Пошаговое перемещение из ccx,ccy в cx,cy
//  byte m,o=0,c=tab(ccx,ccy);
//  int mx,my;
//  do{
//    m=tab2(mx=ccx,my=ccy+1);
//    if(tab2(ccx,ccy-1)<m) m=tab2(mx=ccx,my=ccy-1);
//    if(tab2(ccx+1,ccy)<m) m=tab2(mx=ccx+1,my=ccy);
//    if(tab2(ccx-1,ccy)<m) m=tab2(mx=ccx-1,my=ccy);
//    tab(ccx,ccy)=o;
//    o=tab(mx,my);
//    tab(mx,my)=c;
//    showadd(ccx,ccy);
//    showadd(mx,my);
//    DrawChange();
//    ccx=mx; ccy=my;
//    Sleep(delay);
//  }while(m);
//}

int tabempty(void){ // Нет больше шариков
  for(int i=0;i<maxx*maxy;i++)
    if(data[i]>0) return 0;
  return 1;
}

int tabfull(void){ // Нет своб. места
  for(int i=0;i<maxx*maxy;i++)
    if(data[i]<=0) return 0;
  return 1;
}

void enter(){ // Нажат enter
  if(tab(curx,cury)>0){ // Поле занято
    selx=curx; sely=cury;
  }else{
    if(selx>=0){ // Выбрано откуда
      if(!ismove()){ // Можно
        tab(curx,cury)=tab(selx,sely);
        tab(selx,sely)=0;
        selx=sely=-1;
        if(cmpdel(curx,cury)){
          if(tabempty()) dropball();
        }else{
          if(dropball() || tabfull()) newgame();
          else nextball();
        }
     }
    }
  }
}

void newgame(){ // Начать новую игру
  points=0;
  curx=cury=5;
  selx=sely=-1;
  memset(data,0,sizeof(data));
  dropball(); 
  nextball();
}
