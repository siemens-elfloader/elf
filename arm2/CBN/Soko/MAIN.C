
// Sokoban.cpp --------------------------
//        Sokoban 1.00  16bit color
// win32 ----------------VISUAL C++ 6.0

#include "..\swilib.h"
#include "..\random.h"
typedef unsigned char byte;

extern short *screen;
extern int screensize;
char filename[128], *file;
byte level=0;
extern unsigned char EL71, C65;

char *Title="Sokoban 0.1 (c)bn";
const char *errors[]={
  0,
  "Unknown error\0",
  "Ошибка чтения BMP файла!\0",
  "Ошибка чтения INI файла!\0",
  "Недостаточно памяти\0",
  "Нет уровней\0"
};

char *ini=NULL, *balls=NULL, *ball, *bballs, *s; //free
byte *table, *table2, *show, *showend, b;
const int fmenu=1, fstart=1<<1, fend=1<<2, frgb555=1<<3;

int twidth=0, theight=0;//, pitch, rgbmask; // Разрешение экрана //0xb35203
const int bitpix=16, shiftpix=1;	
const int csizexy=64, bmpoff=54, maxrezerv=4096, delay=30;

int flags=0, balloff;   // Флаги
int menux, menuy, menuy0, menudy, menucnt, lastbmp; //menu
int sizexy=1, sizexy2=4, sizelxy, ballkf, x0, y0;
int cx,cy, ccx,ccy;

int maxgames=0; // Всего игр
struct gamest{  // Игры
  byte *level;  // Игровое поле
  char *name;   // Название уровня
  byte x,y,     // Размеры x на y
       px,py;   // Коорд. игрока
}g, *gg=NULL, *ggg, *gend;


/* Структура soko.dat - рисунки 64x64 (16x16)  поле 8x11
 0 пол, 1 цель, 2 ящик, 3 ящик на цели, 4 стена, 5 фон(не исп), 6 робот, далее сис.кн.

soko.ini
xozp 1024 768 
Обозначения ящ,ц,я&ц,игрок,пол
[level1]
MMMMMMM
Mo x oM
M x p M
MMMMMMM
[...]*/

#define tab(xx,yy) table[(yy)*g.x+(xx)]
#define tab2(xx,yy) table2[(yy)*g.x+(xx)]

inline void showadd(char x, char y){ *showend--=x; *showend--=y;}

char *loadfileex(char *filename, int rezerv);//=0

int atoi(char *s){
  int res=0;
  --s;
  while(*++s>='0' && *s<='9') res=res*10+*s;
  return res;
}

char *getatoi(char *s, int *val){ // Получить число из строки
  char *ss,c;
  while(*s==' ') ++s;
  if(*s=='-' || (*s>='0' && *s<='9')){
    ss=s;
    while(*++s>='0' && *s<='9');
    c=*s; *s=0; *val=atoi(ss); *s=c;
  }else  *val=0;
  return s;
}


// bitbltfst Вывод bmp на screen без проверки и перекодировки
//bmp: 10 off, 18 x, 22 y, 28 bitpix
// +30 stepscreen, +34 stepbmp, +38 sizex, +42 sizey
//void bitbltfst(char *screen, char *bmp, DWORD flags=0, int colormask=0, int x0=0, int y0=0,
//  UINT sizex=0, UINT sizey=0, UINT bx0=0, UINT by0=0){

/*
void smallballs(void){ // Уменьшенный шарики
  short *t=(short*)(ball+balloff), *tt=(short*)(balls+balloff);
  int i,j;
  *(long*)(ball+18)=32;
  *(long*)(ball+22)=*(long*)(balls+22)/2;
  for(j=0;j<csizexy*3;j++){
    for(i=0;i<csizexy;i++,tt++) *t++=*tt++;
    tt+=csizexy<<shiftpix;
  }
}
  

#define bbf(c) bitbltfst(screen,bballs,0,0, xx, yy, sizexy,sizexy, 0,sizexy*(c))

void drawball(char *screen, int x ,int y){
  int xx=x0+x*sizexy, yy=y0+y*sizexy, zz=tab(x,y);
  if(zz==1) bbf(0);
  bbf(zz);
  if(ccx==x && ccy==y) bbf(6);
}

void DrawChange(void) { // Нарисовать изменения
  char *screen;
    while(++showend<show){
      drawball(screen,*(showend+1),*showend);
      ++showend;
    }
  showend=show;
}

void Dr2awScreen(void) { // Все нарисовать
  int x,y;
  char *screen;

    for(x=0;x<g.x;x++)
      for(y=0;y<g.y;y++)
        drawball(screen,x,y);
    //drawplayer(screen);
  showend=show;
}
*/

inline void cls(void){  // Подготовка экрана
  memsetd(screen,0,screensize>>2);}

#define bbf(c) bitblt(screen,balls, xx<<4, yy<<4, 16,16, 0, sizexy*16*(c), 0,0x40)

void drawball(int x ,int y){
  int xx=x0+x*sizexy, yy=y0+y*sizexy, zz=tab(x,y);
  if(zz==1) bbf(0);
  bbf(zz);
  if(ccx==x && ccy==y) bbf(6);
}

void onredraw() { // Все нарисовать
  cls();
  int x,y;//, maxx=(g.x<8)?g.x:8, maxy=(g.y<11)?g.y:11;
    for(x=0;x<g.x;x++)
      for(y=0;y<g.y;y++)
        drawball(x,y);
    //drawplayer(screen);
}


void newgame(void){   // Новая игра
  if(level>=maxgames) level=0;
  ggg=gg+level;
//  flags=ccx=ccy=0;
//  showend=show;
  memcpy(&g,ggg,sizeof(struct gamest));
  sizelxy=g.x*g.y;
//  sizexy=csizexy;
//  if(height/g.y<sizexy || width/g.x<sizexy) sizexy>>=1;
//  ballkf=csizexy/sizexy;
//  sizexy2=sizexy<<shiftpix;
//  x0=(width-sizexy*g.x)>>1;
//  y0=(height-sizexy*g.y)>>1;
//  if(ballkf==1) bballs=balls;
//  else{bballs=ball; smallballs();}
  memcpy(table,g.level,sizelxy);
  ccx=g.px; ccy=g.py;
//  flags|=fstart;
  REDRAW();
}

char *loadfileex(char *filename, int rezerv){
  int f;
  char *buf;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1){
    loadfilesize=0;
    return 0;
  }
  loadfilesize=lseek(f,0,2,&err,&err);
  lseek(f,0,0,&err,&err);
  if(!(buf=(char *)malloc(loadfilesize+rezerv))){
    loadfilesize=0;
    return 0;
  }
  fread(f,buf,loadfilesize,&err);
  fclose(f,&err);
  return buf;
}
/*
void selgame(int x, int y){   // Игра выбрана?
  switch(issyskeys(x,y)){
//  case 3: SendMessage(hWnd, WM_CLOSE, 0, 0); return;
  case 2: if(flags&fstart){ flags&=(~fmenu); clrscr(); DrawScreen();} return;
  case 1: return;
  }
  if((y-=menuy0)<0 || (y=y/menudy)>=menuy) return;
  x=x/(width/menux);
  int i;
  if((i=x*menuy+y)>=maxgames) return;
  ggg=gg+i;
  newgame();
}
*/
int sempty(void){
  char *ss=s-1;
  while(*++ss && *ss==' ');
  if(!*ss) s=ss+2;
  return !(ss[0]==0 && ss[1]==0) && s!=ss;
}

inline void snext(void){
  --s; while(*++s); s+=2;
}

void sprep(char *s){
  do switch(*++s){
    case 0: return;
    case ']': case 9: case 0xa: *s=' '; break;
    case ';': case '/': *s=' '; while(*++s && *s!=0xd) *s=' '; if(!*s) return;
    case 0xd: *s=0; break;
    }
  while(1);
}


///////////Init////////

//#define ttt if(*tt==(byte)253) return 0; if(*tt==(byte)254) *tt=Ni+1
/*
int ismove(void){  // Можно ли переместить ccx,ccy в cx,cy
  // Волновой алгоритм поиска (взято от Медноногова)
  //if(l.f&moveany) return 0;
  int i,Ni=0;
  byte *t, *tt;
  memset(table2,255,sizelxy);
  for(i=0;i<sizelxy;i++)
    if(table[i]<=1) --table2[i];
  //undoflag=0;
  tab2(cx,cy)=0;
  tab2(ccx,ccy)=(byte)253;
  do
    for(i=0,t=table2;i<sizelxy;i++,t++)
      if(*t==Ni){
        tt=t+1; ttt;
        tt=t-1; ttt;
        tt=t+g.x; ttt;
        tt=t-g.x; ttt;
      }
  while(++Ni<252);
  return 1;
}

void movestep(void){  // Пошаговое перемещение из ccx,ccy в cx,cy
  byte m,o=0,c=tab(ccx,ccy);
  int mx,my;
  do{
    m=tab2(mx=ccx,my=ccy+1);
    if(tab2(ccx,ccy-1)<m) m=tab2(mx=ccx,my=ccy-1);
    if(tab2(ccx+1,ccy)<m) m=tab2(mx=ccx+1,my=ccy);
    if(tab2(ccx-1,ccy)<m) m=tab2(mx=ccx-1,my=ccy);
    showadd(ccx,ccy);
    showadd(ccx=mx,ccy=my);
    DrawChange();
    Sleep(delay);
  }while(m);
}

int yajik(void){ // Перемещение ящика cx,cy
  int dx=cx-ccx, dy=cy-ccy;
  if(abs(dx)>1 || abs(dy)>1 || (dx && dy) || tab(cx+dx,cy+dy)>1) return 0;
  showadd(ccx,ccy);
  showadd(ccx=cx,ccy=cy);
  showadd(cx+dx,cy+dy);
  tab(cx,cy)-=2;
  tab(cx+dx,cy+dy)+=2;
  DrawChange();
  return victory();
}

int getpos(int x, int y){   // Позиция мышки на поле
  if((x-=x0)<0 || (y-=y0)<0) return 1;
  if((x/=sizexy)>=g.x || (y/=sizexy)>=g.y) return 1;
  cx=x; cy=y;
  return 0;
}
*/

int victory(void){
  int i;
  for(i=0;i<sizelxy;i++)
    if(table[i]==1) return 0;
  ++level;
  newgame();
  return 1;
}

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  int dx=0,dy=0;
  switch(pressed){      
  case KEY_UP: break; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    switch(keycode){ // Код клавиши
    case RED_BUTTON: return 1; // Выход
    case GREEN_BUTTON:
      ++level;
    case LEFT_SOFT:
      newgame();
    default:  
      return 0;
    case RIGHT_BUTTON: dx=1; break;
    case LEFT_BUTTON: dx=-1; break;    
    case UP_BUTTON:  dy=-1; break;
    case DOWN_BUTTON: dy=1; break;
    //case ENTER_BUTTON: // Делаем что-либо
    }

    switch(tab(cx=ccx+dx,cy=ccy+dy)){
    case 2: case 3:
      if(tab(cx+dx,cy+dy)>1) return 0;
      tab(cx,cy)-=2;
      tab(cx+dx,cy+dy)+=2;
      if(victory()) return 0;
//      showadd(cx+dx,cy+dy);
    case 0: case 1:
//      showadd(ccx,ccy);
//      showadd(ccx=cx,ccy=cy);
      ccx=cx; ccy=cy;
      break;
    default: return 0;
    }

    REDRAW();
//    onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

/*
void lbuttondown(int x, int y){ // Лев. кн. нажата
  if(flags&fmenu){ selgame(x,y); return;}
  switch(issyskeys(x,y)){
//  case 3: SendMessage(hWnd, WM_CLOSE, 0, 0); return;
  case 2: showmenu(); return;
  case 1: newgame(); return;
  }
  if(getpos(x,y) || (cx==ccx && cy==ccy) || (b=tab(cx,cy))>3) return;
  if(b>1){ if(yajik()) newgame(); return;}
  if(!ismove()) movestep();
}

void rbuttondown(int x, int y){ // Прав. кн. нажата
  if(flags&fmenu){ selgame(x,y); return;}
  switch(issyskeys(x,y)){
//  case 3: SendMessage(hWnd, WM_CLOSE, 0, 0); return;
  case 2: showmenu(); return;
  case 1: newgame(); return;
  }
  if(getpos(x,y) || (cx==ccx && cy==ccy) || (b=tab(cx,cy))>3) return;
  int dx=cx-ccx, dy=cy-ccy, i;
  if(dx && dy) return;
  i=(dx)?abs(dx):abs(dy);
  dx/=i; dy/=i;
  do{
    switch(tab(cx=ccx+dx,cy=ccy+dy)){
    case 2: case 3:
      if(tab(cx+dx,cy+dy)>1) return;
      tab(cx,cy)-=2;
      tab(cx+dx,cy+dy)+=2;
      if(victory()) return;
      showadd(cx+dx,cy+dy);
    case 0: case 1:
      showadd(ccx,ccy);
      showadd(ccx=cx,ccy=cy);
      break;
    default: return;
    }
    DrawChange();
//    Sleep(delay);
  }while(--i);
}
*/
void saves(){
  int f;
  unsigned int err;
  strcpy(strrchr(filename,'.'),".sav");
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    fwrite(f,&level,1,&err);
    fclose(f,&err);
  }
}

void onexit(){   // Освободить ресурсы
  if(!ini)   mfree(ini);
  if(!balls) mfree(balls);
  if(!gg) mfree(gg);
  saves();
}


void loads(){
  int f;
  unsigned int err;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f,&level,1,&err);
    fclose(f,&err);
  }
}

void onclose(){ // Закрытие окна
}

void oncreate(){ // Создание окна
  newgame();
}

#define s0 if(!*s) return 0

int onstart(char *exename, char *fname){
  strcpy(filename,exename);
  file=strrchr(filename,'.')+1;
  strcpy(file,"bmp");
  if(!(balls=loadgraph(filename))) return 2;
  strcpy(file,"ini");
  //
  int ballsize=0, x, y, maxx=0, maxy=0, tmpsize;
  char xx,o,z,p,e;
  char c, *ss;
  char *card;
  Randomize();
  if(!(ini=loadfileex(filename,16))) return 3;
  strcpy(file,"sav");
  loads();
  *(long*)ini|=0x20202020;
  xx=ini[0];o=ini[1];z=ini[2];p=ini[3];e=ini[4];
  s=ini+5;
  while((c=*++s) && (c==' ' || c==9));
  if(c>='0' && c<='9'){ s=getatoi(s,&twidth); s=getatoi(s,&theight);}
  s0; while(*++s && *s!='[');
  s0; sprep(ss=s); 
  do{
    ballsize+=strlen(++s);
    snext();
    ++maxgames;
    y=0; x=0;
    do{
      if(!x) x=strlen(s);
      snext(); while(sempty()); 
      if(*s==0 && s[1]==0) break;
      ++y;
    }while(*s!='[' && !(*s==0 && s[1]==0));
    maxx=max(maxx,x); maxy=max(maxy,y);
    ballsize+=x*y;
   }while(!(*s==0 && s[1]==0));
//  if(!(balls=loadfileex(sokodat,2))) return 0;
  //balloff=getint(balls+10);
  tmpsize=10000;//((loadfilesize-balloff)>>1)+balloff;
  if(maxgames<1) return 5;
  if(!(gg=ggg=(struct gamest *)malloc(x=maxgames*sizeof(struct gamest)+\
    ballsize+(maxx*maxy<<1)+maxrezerv+tmpsize))){
      sprintf((char*)errors[4],"%d",x);
      //ShowMSG(1,(int)debug);
//    MessageBox(NULL,"Недостаточно памяти!",NULL,MB_OK);
    return 4;
  }
  gend=gg+maxgames;
  card=(char*)gend;
  table=(byte*)card+ballsize;
  table2=table+maxx*maxy;
  ball=(char*)table2+maxx*maxy;
  show=showend=(byte*)gg+x-1;
  //memcpy(ball,balls,balloff);
  s=ss;
  do{
    ++s;
    memcpy(ggg->name=card,s,x=strlen(s)-1);
    card+=x;
    *card++=0;
    snext();
    y=0; x=0;
    ggg->level=(byte*)card;
    do{
      if(!ggg->x) ggg->x=strlen(s);////////??????????????
      x=0;
      do{
        if((c=(*s|0x20))==e) c=0;
        else if(c==o) c=1;
        else if(c==xx) c=2;
        else if(c==z) c=3;
        else if(c==p){ c=0; ggg->py=y; ggg->px=x;}
        else c=4;
        *card++=c;
        ++x; 
      }while(*++s);
      while(x<ggg->x-1){ *card++=5; ++x;}
      s+=2; while(sempty()); 
      if(s[0]==0 && s[1]==0) break;
      ++y;
    }while(*s!='[' && !(s[0]==0 && s[1]==0));
    ggg->y=y;
    ggg->x=x;
    ++ggg;
  }while(!(s[0]==0 && s[1]==0));
  memcpy(&g,ggg=gg,sizeof(struct gamest));
  mfree(ini); ini=0;
  return 0;
}

