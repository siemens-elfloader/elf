
// cards.cpp --------------------------
//        Пасьянсы версия 0.05
// win32 ----------------VISUAL C++ 6.0

#include <ddraw.h>
#include "mylib.h"

// Глобальные переменные
char *card, *begcard, *endcard; // Буфер карт
const datasys=9, datamem=10;
char *data[]={"cardhi.bmp","cardhib.bmp","cardhie.bmp",
              "cardme.bmp","cardmeb.bmp","cardmee.bmp",
              "cardlo.bmp","cardlob.bmp","cardloe.bmp", "system.bmp", "", NULL};
char *mem=NULL, *back=NULL, *back2, *undo; //free
BMPst *bmp=NULL; //free
int coloda=0, colodax, colodax2, coloday, rybashka=0;
int lastsyskey=0, iscardur=0, menuflag=0; //1=sel game, 2=victory, 3=scrsaver;
int menux, menuy, menuy0, menudy, menucnt, lastbmp;

const miny=22, minx=10, deltay=10, deltax=5;    // Отступы
const cardsincoloda=52;
const card2last=-1, card2nohide=1, card2reverse=1<<1;

#define fortab for(tab=p.table;tab<=p.tablen; tab++)
#define f(flag) if((tab->f)&(flag))

struct tables{  // Таблицы
  int f;        // Флаги
  int cards,    // Карт вначале
      max,      // Максимум карт
      first,    // 1я карта должна быть
      redeal,  // Переворотов сейчас
      sredeal, // Переворотов всего
      x,y,      // Стартовые коорд.(в %)
      yn,       // Насколько вниз (в %)
      x0,y0,    // Реальные коорд. карт (считаются)
      x1,y1,x2,y2, // Ограничения рамки (считаются)
      id,       // Уникальный ID
      num,      // Номер (не исп-ся)
      type,     //==id для показа пустых ячеек (1,2)
      hide,     // Сколько карт скрыть (аналог hidden=all)
      shift,    // Сдвиг открытых карт 
      shifthd;  // Сдвиг скрытых карт

 char *card,    // Карты
      *free,    // Заполнять своб. яч.
      *to,      // Куда перекладывать по щелчку: IDs
      *from;    // Откуда могут лож. карты: IDs
} t,  *table, *tatmp, *tab, *undofrom=0, *undoto=0;

int maxpatien=0;
struct patiens{ // Пасьянсы
tables *table,  // 1е опис-е (колода обычно)
       *tablen; // Последнее
char   *name,   // Название
       *bmp;    // ИФ фона
int    f,       // Флаги (не исп-ся)
       minx,miny,   // Смещения от верха
       deltax,deltay, // Шаг между таблицами
       victory,   // Условия победы (не исп-ся)
       decks,     // Всего колод
       cardsize,  // Размер карт 1-3 (1=large)
       cardback,  // Цвет рубашки (-1=rnd)
       backcolor, // Цвет фона
       backjpeg,  // Фон
       _calculated;  //use in program
} p, *patien=NULL, *curpat;

const stock=1, waste=2, reserve=3, tableau=4, foundation=5; //id's
// Флаги пасьянсов
const calcdy=1,     // Вычислить deltay (как по x)
center=1<<1;        // Поместить рисунок в центр экрана
// Флаги таблиц
const buildup=1,    // Строить вверх
builddown   =1<<1,  // Строить вниз
alternate   =1<<2,  // Альтерн.
suit        =1<<3,  // По масти
rank        =1<<4,  // По рангу
any         =1<<5,  // По любому
color       =1<<6,  // По цвету (черные, красные)
same        =1<<7,  // По любому, кроме той же масти

movegroup   =1<<8,  // Перемещать группами
moveone     =1<<9,  // Перемещать по одной
moveany     =1<<10, // Перемещать по любому
ka          =1<<11, // Переходить от королей к тузам и обратно
kasuit      =1<<12, // При переходе можно сменить масть
happy       =1<<13, // Все карты лежат только там для победы
hidden      =1<<14,  // Скрыть карты (рубашкой вверх)
firsthidden =1<<15, // Скрыть верхнюю карту
redeal3     =1<<16, // Листать по 3 карты
dropgroup   =1<<17, // Бросать несколько можно всегда
nodrawfirst =1<<18, // Не показывать какую карту ложить первой (tableau)
firstrnd    =1<<19, // СЧ начальная карта
top         =1<<20, // Перемещать карту наверх по щелчку
shiftx      =1<<21, // Выкладывать вправо (по х) (not used!)
firstsuit   =1<<22, // 1-я карта д.б. этой масти 
firstcard   =1<<23, // 1-я карта д.б.  
nosuit      =1<<24, // Ложить не по масти
autodel     =1<<25; // Автом. удал. сложен. послед-й из 13 карт
/* Карты:
 0 0 00 0000
 | |  | младшие 4 бита ранг: 1-туз, 13-король (14 дурак?)
 | |  2 бита масть (0=крести, 1=буби, 2=черви, 3=пики)
 | резерв
 старший бит установлен - карта перевернута (рубашкой вверх)
*/
const maxpar=67;
struct params{  // Параметры из файла
  char *name;   // Имя
  int  *in;     // Указатель на переменную
  int  flag;    // 0=число, -1=список, иначе биты
} *partmp, par[maxpar]={
{"alternate",&t.f,alternate},  // Альтерн.
{"any",&t.f,any},              // По любому
{"autodel",&t.f,autodel},
{"backcolor",&p.backcolor,0}, 
{"backjpeg",&p.backjpeg,0}, 
{"builddown",&t.f,builddown},  // Строить вниз
{"buildup",&t.f, buildup},     // Строить вверх
{"calcdy",&p.f,calcdy},
{"card",&(int &)t.card,-1},    // Карты
{"cardback",&p.cardback,0},
{"cards",&t.cards,0},          // Карт в начале
{"cardsize",&p.cardsize,0},
{"center",&p.f,center},
{"colod",&p.decks,0},
{"color",&t.f,color},
{"decks",&p.decks,0},
{"deltax",&p.deltax,0},
{"deltay",&p.deltay,0},
{"dropgroup",&t.f,dropgroup},
{"first",&t.first,0},            // 1я карта д.б.
{"firstcard",&t.f,firstcard},
{"firsthidden",&t.f,firsthidden},// Скрыть верхнюю карту
{"firstrnd",&t.f,firstrnd},
{"firstsuit",&t.f,firstsuit},
{"foundation",&t.id,foundation}, // foundation
{"free",&(int &)t.free,-1},      // Заполнять своб. яч.
{"from",&(int &)t.from,-1},      // Откуда могут лож. карты: IDs
{"happy",&t.f,happy},            // Условия победы
{"hidden",&t.f,hidden},          // Скрыть все карты (рубашкой вверх)
{"hide",&t.hide,0},              // Скрыть N карт (рубашкой вверх)

{"id",&t.id,0},                  // Уникальный ID
{"ka",&t.f,ka},                  // Переходить от королей к тузам и обратно
{"kasuit",&t.f,kasuit},                

{"max",&t.max,0},               // Максимум карт
{"minx",&p.minx,0},
{"miny",&p.miny,0},
{"moveany",&t.f,moveany},      // Перемещать по любому
{"movegroup",&t.f,movegroup},  // Перемещать группами
{"moveone",&t.f,moveone},      // Перемещать по одной
{"nodrawfirst",&t.f,nodrawfirst}, 
{"nosuit",&t.f,nosuit},        // Не по масти
{"num",&t.num,0},              // Номер

{"rank",&t.f,rank},            // По рангу
{"redeal",&t.sredeal,0},       // Для пасьянсов
{"redeal3",&t.f,redeal3},      // Листать по 3 карты
{"reserve",&t.id,reserve},     // reserve
 
{"same",&t.f,same},
{"shift",&t.shift,0},          // Сдвиг карт на сколько
{"shifthd",&t.shifthd,0},      // Сдвиг скрытых карт на сколько
{"shiftx",&t.f,shiftx},        // Выкладывать вправо (по х)
{"stock",&t.id,stock},         // stock
{"suit",&t.f,suit},            // По масти

{"tableau",&t.id,tableau},     // tableau
{"to",&(int &)t.to,-1},        // Куда перекладывать по щелчку: IDs
{"top",&t.f,top},
{"type",&t.type,0},

{"victory",&p.victory,0},
{"waste",&t.id,waste},        // waste
{"x",&t.x,0},                 // коорд.
{"x0",&t.x0,0},
{"x1",&t.x1,0},
{"x2",&t.x2,0},
{"y",&t.y,0},  
{"y0",&t.y0,0},
{"y1",&t.y1,0},
{"y2",&t.y2,0},
{"yn",&t.yn,0}
};

char *findparam(char *s){     // Получить значение параметра
  char cc, *ss=s;
  int r1=0, r2=maxpar-1, r3, rez, val;
  while((cc=*ss) && cc!=' ' && cc!=0xd && cc!='}' && cc!='{' && cc!='=') ++ss;
  *ss=0;
  do{
    r3=(r1+r2)>>1;
    if(!(rez=(*s-*par[r3].name)) && !(rez=strcmp(s,par[r3].name))) break;
    else
     if(rez<0) r2=r3-1;
     else r1=r3+1;
  }while(r1<=r2);
  if(rez){ *ss=cc;  return 0;}
  partmp=par+r3;
  *ss=cc;
  s+=strlen(partmp->name)-1;
  while(*++s==' ' || *s=='=');
  s=getatoi(s,&val);
  if(!partmp->flag){    //0
    if(!val) return 0;
    *partmp->in=val;
  }else 
    if(partmp->flag==-1){ //list
    if(!val) return 0;
    *partmp->in=(int)card;
    do{
      *card++=val;
      s=getatoi(s,&val);
    }while(val);
    *card++=0;
  }else
  *partmp->in|=partmp->flag;
  return s;
}

int loadparam(char *file){     // Получить параметры из файла (в card)
  int cj,cc,flag;
  char *s,*ss,*sss;
  //patiens *curpat;
  loadfilenomsg=1;
  if(!(s=loadfile(file,20))){
    loadfilenomsg=0;
    if(!(s=loadfile(file,20,&PK)))
      return 1;
  }loadfilenomsg=0;
  ss=s;
  cj=cc=flag=0;
  do
    switch(*s){
      case 0: break;
      case '[': ++flag; ++cc; break;
      case ']': flag=0; break;
      case '}': ++cj; break;
      case '{': 
      case 9: *s=' '; break;
      case ';': case ':': case '/': case '?':
        do *s=' '; while(*++s && *s!=0xd); break;
      default: if(!flag && *s>='A' && *s<='Z') *s|=0x20;
    }
  while(*s++);
  if(!cc || !cj){
    MessageBox(NULL,"Нет пасьянсов в файле!",file,MB_OK);
    return 2;
  }
  if(!(card=(char *)GlobalAlloc(GPTR,(sizeof(struct patiens)*cc)+10000+(sizeof(struct tables)*cj)))){
    MessageBox(NULL,"Недостаточно памяти!",NULL,MB_OK);
    return 3;
  }
  ZeroMemory(&t,sizeof(tables));
  ZeroMemory(&p,sizeof(patiens));
  patien=curpat=(patiens *)card;
  table=tatmp=(tables *)(patien+(maxpatien=cc));
  card=(char *)(table+cj);
  --curpat; 
  s=ss;
  do{
    switch(*s){
      case '[': 
        if(curpat>=patien){ 
          p.tablen=tatmp-1;
          memcpy(curpat,&p,sizeof(patiens)); 
          ZeroMemory(&p,sizeof(patiens));
        }
        ++curpat;
        p.table=tatmp;
        p.name=card;
        while(*++s && *s!=']' && *s!=0xd) *card++=*s;
        *card++=0;
        if(!*s) break;
        while(*++s && *s!=0xd && *s!=0xa && *s==' ');
        if(!*s) break;
        if(*s!=0xd && *s!=0xa){
          p.bmp=card; --s;
          while(*++s && *s!=0xd) *card++=*s;
          *card++=0;
        }break;
      case '}': 
        memcpy(tatmp++,&t,sizeof(tables)); 
        ZeroMemory(&t,sizeof(tables)); break;
      case 0: case 0xd: case 0xa: case ' ': break;
      default: 
        if(!(sss=findparam(s))){
          sss=s;
          while(*++s && *s!=0xd);
          *s=0;
          MessageBox(NULL,sss,"Неверная строка в конфигурации",NULL);
          return 4;
        }
        s=sss-1;
     }
  }while(*s++);
  p.tablen=tatmp-1;
  memcpy(curpat,&p,sizeof(patiens)); 
  ZeroMemory(&t,sizeof(tables));
  begcard=endcard=card;
  curpat=patien;
  GlobalFree(ss);
  return 0;
}
/*Структура ini файла:
[Имя пасьянса] Фон.jpg
{ 
параметры 1-ого поля
}
{ 
параметры n-ого поля
}
*/

void cardnabor(int n){    // Наборы колод 0-2
  coloda=(n%3)*3; BMPst *bmp=(BMPst *)data[coloda];
  colodax=bmp->biWidth/14; 
  colodax2=colodax>>1;
  coloday=bmp->biHeight/4;
}

inline int iscard(int card){ // Является ли картой
  return((!(card & 0xF) || ((card & 0xF)>(13+iscardur))))?0:1;
}

char *fillcoloda(char *buf){    // Выложить колоду
  for(int i=1; i<0x3F; i++) 
    if(iscard(i)) *buf++=(char)i;
  return buf;
}

tables *gettab(int x, int y){   // Какая таблица с X,Y, возвращ. в tab
  fortab if(tab->x1<=x && x<=tab->x2 && tab->y1<=y && y<=tab->y2) return tab;
  return tab=NULL;
}

int getsizey(int first){
  char *s=tab->card+first;
  int i=coloday;
  if(!*(s+1)) return i;
  do{ 
    if(*s & 0x80){
      if(tab->shifthd)
        i+=tab->shifthd;
    }else{
      if(tab->shift)
        i+=tab->shift;
    }
  }while(*++s);
  return i;
}

inline void getmousey(void){
  t.yn+=getsizey(t.first);
}

int isalternate(char c1, char c2){   //Альтерн?
  if((c1=(c1>>4)&3)==(c2=(c2>>4)&3)) return 0;
  return (c1+c2==3)?0:1;
}

int iscolor(char c1, char c2){
  if((c1=(c1>>4)&3)==(c2=(c2>>4)&3)) return 1;
  return (c1+c2==3)?1:0;
}

int dropcard(void){ // Можно ли бросить карту t в tab?
  long f=tab->f;
  char l, c;
  int i;
  if(!(c=*t.card)) return 0;
  //if(f&alternate || f&suit || f&rank || f&any) ; else return 0;
  if(*(t.card+1)) if (tab->shift || tab->shifthd || (f&dropgroup)); else return 0; 
  if(tab->max && (UINT)tab->max < strlen(t.card)+ strlen(tab->card)) return 0;
  if(!*tab->card){  // пусто
    if(!(l=tab->first)) return (f&(any|alternate|suit|buildup|builddown|same|color|nosuit))?1:0;
    if(f&firstsuit) return (((l>>4)&3)==((c>>4)&3))?1:0;
    if(f&firstcard || l>15) return (c==(l&0x3f))?1: 0;
    return ((c&0xf)==l)?1: 0;
  }
  l=tab->card[strlen(tab->card)-1];
  if(f&any) return 1;   //any
  if(f&rank) return ((l&0xf)==(c&0xf))?1:0; 
  if(f&alternate) if(!isalternate(c,l)) return 0;
  if(f&same) if(((l>>4)&3)==((c>>4)&3)) return 0;
  if(f&color) if(!iscolor(c,l)) return 0;
  if((f&suit) && !(f&nosuit)){   //suit
    if(f&kasuit){ 
      if((f&buildup) && (l&0xf)==13 && (c&0xf)==1) return 1;
      if((f&builddown) && (c&0xf)==13 && (l&0xf)==1) return 1;
    }
    if(((l>>4)&3)!=((c>>4)&3)) return 0;
  }  
  if((f&buildup) && (f&builddown)){
    if((f&ka) && (i=(l&0xf)-(c&0xf))==12 || i==-12) return 1;
    return ((i=(l&0xf)-(c&0xf))==1 || i==-1)?1:0;
  }
  if(f&buildup){
    if((f&ka) && (l&0xf)==13 && (c&0xf)==1) return 1;
    return ((c&0xf)-(l&0xf)==1)?1:0;
  }
  if(f&builddown){
    if((f&ka) && (l&0xf)==1 && (c&0xf)==13) return 1;
    return ((l&0xf)-(c&0xf)==1)?1:0;
  }
  return (f&(alternate|suit|buildup|builddown|same|color|nosuit))?1:0;
}


inline void drawsys(char *screen, int x_only=0){ 
  bitblt(screen,data[datasys],0,1, width-66+x_only,0, 0,0, x_only);
}

int drawcard(char *screen, int x, int y, int card, int flag=0){ // Отобразить карту
  int xx, yy, nc;                                           // flag если место под карту
  if(flag){  nc=2; card&=0xf;  xx=(colodax+((coloda)?1:0))*((card<14)?(card+2):(card-14)); yy=0;}
  else{ if(!iscard(card)) return 0;
    if(card&0x80){ nc=1; xx=colodax*(rybashka&0x7); yy=coloday*((rybashka>>3)&0x1); }
    else{ nc=0; xx=colodax*((card&0xf)-1); yy=coloday*((card>>4)&0x3); }
  }
  bitblt(screen,data[coloda+nc],0,(nc==1)?RGB(246,8,246):RGB(248,8,248), x,y, colodax, coloday, xx,yy);
  return 1;
}

int drawcards(char *screen, tables *tab){ // Отобразить таблицу
  int y=tab->y0, x=tab->x0-colodax2;
  char *card=tab->card;
  if(!*card){   //empty
    if(tab->first && tab->id!=tableau && tab->id!=tableau && !(tab->f&nodrawfirst)) 
      return drawcard(screen,x, y,tab->first,1);
    switch((tab->type)?tab->type:tab->id){
    case stock:
      return drawcard(screen,x, y,(tab->redeal==1)?14:15,1);
    case tableau:
      return 0;
    case waste:
    case reserve:
      return drawcard(screen,x, y,0,1);
    }
    if(tab->first) drawcard(screen,x, y,tab->first,1);
    return 0;
  }
  if(!tab->shifthd && !tab->shift) card+=strlen(tab->card)-1;
  do{
    drawcard(screen, x,y, (int)*card);
    y+=((*card)&0x80)?tab->shifthd : tab->shift;
  }while(*++card);
  return 1;
}

void clearpage(){
  char *screen=getscreen();
  ZeroMemory(screen,pitch*height<<2);
  flip();
}

void background(void){
  if(!back) return;
  if((p.f&center) || p.backcolor){
    _asm{
      mov edi,back
      mov eax,height
      mul pitch
      xchg  eax,ecx
      mov eax,p.backcolor
      cld
      rep stosd
    }
    if(!(p.f&center)) return;
  }
  if(!bmp) return;
  unsigned x,y, dx=bmp->biWidth, dy=bmp->biHeight; 
  if(p.f&center || (dx==(UINT)width && dy==(UINT)height)) 
    bitblt(back,(char *)bmp,0,1,(width-dx)>>1,(height-dy)>>1);
  else
  for(y=0;y<=height/dy;y++)
    for(x=0;x<=width/dx;x++)
      bitblt(back,(char *)bmp,0,1, x*dx, y*dy);
}

inline int issyskeys(int x, int y){ return((x-=(width-66))>0 && (y<22))?(x/22+1):0;}
inline int issyskeys2(int x, int y){ return((x-=(width-22))>0 && (y<22))?1:0;}

inline void drawtab(tables *tab, tables *tab2=0) { // нарисовать tab
  char *screen;
  if(screen=lockprimary()){
    drawcards(screen,tab); 
    if(tab2) drawcards(screen,tab2); 
    unlockprimary();
  }
}
void drawback(void) { // Все нарисовать
  background();
  drawsys(back);
  fortab  drawcards(back,tab); 
}

void back2screen(void){
  char *screen;
  if(screen=lockprimary()){
    CopyMemory(screen,back,pitch*height<<2);
    unlockprimary();
  }
}

int pickcard(int x, int y){   // Можно ли брать эту карту?
  char *s, *ss, c;
  int i, f=tab->f;
  s=ss=tab->card+t.first;
  if(f&top && *(s+1) && !(*s&0x80)){
    c=*s; memmove(s,s+1,strlen(s));
    s[strlen(s)]=c; drawtab(tab);
  }
  if(f&moveone) return 0;
  do if(*s&0x80) return 0; while(*++s);
  t.x=x; t.y=y; ///
  //return 1; //////////
  if(f&moveany) return 1; 
  //f(any) return 1;
  s=ss;
  if(f&alternate){ while(*(s+1)){ if(!isalternate(*s,*(s+1))) return 0; ++s;}
  s=ss;}
  if(f&suit){ while(*(s+1)) if(((*s>>4)&3)!=(((*++s)>>4)&3)) return 0;
  s=ss;}
  if(f&same){ while(*(s+1)) if(((*s>>4)&3)==(((*++s)>>4)&3)) return 0;
  s=ss;}
  if(f&color){ while(*(s+1)){ if(!iscolor(*s,*(s+1))) return 0; ++s;}
  s=ss;}
  if((f&buildup) && (f&builddown)){
    while(*(ss+1)) if((i=(*ss&0xf)-((*++ss)&0xf))!=-1 && i!=1) return 0; return 1;
  }
  ss=s;
  if(f&buildup) while(*(ss+1)) if((*ss&0xf)-((*++ss)&0xf)!=-1) return 0;
  ss=s;
  if(f&builddown) while(*(ss+1)) if((*ss&0xf)-((*++ss)&0xf)!=1) return 0;
  return (f&(alternate|suit|buildup|builddown))?1:0;
}

int getcard(int x, int y){   // Можно ли взять карту с tab;
  long f=tab->f;
  char *s;
  x-=tab->x0;
  y-=tab->y0;
  if(x<-colodax2 || x>=colodax2 || y<0) return 0;
  if(tab->to && y<getsizey(0)) return 1;
  if(!*tab->card || (tab->card[strlen(tab->card)-1]&0x80)) return 0;
  if((f&moveone) || (f&movegroup) || (f&moveany));
  else return 0;
  if(!tab->shift && !tab->shifthd){
    if(y>=coloday) return 0; 
    t.first=strlen(tab->card)-1; 
    t.x=x; t.y=y; return 1;
  }
  for(t.first=0, s=tab->card;*(s+1);t.first++,s++){
    if(*s & 0x80){
      if(tab->shifthd)
        if((y-=tab->shifthd)<0) return pickcard(x,y+tab->shifthd);
    }else{
      if(tab->shift)
        if((y-=tab->shift)<0) return pickcard(x,y+tab->shift);
    }
  }
  if(y>=coloday) return 0;
  t.x=x; t.y=y; return 1;
}

void prikol(void){
  char c, cc, *s;
  tables *tab2, *tab=p.table+random(p.tablen-p.table+1);
  if(!*tab->card) return;
  if((c=*(s=tab->card+strlen(tab->card)-1))&0x80) return; 
  switch(random(5)){
  case 0: cc=14; ++iscardur;  break;
  case 1: case 2: tab2=p.table+random(p.tablen-p.table+1);
    if(!*tab2->card) return; cc=tab2->card[strlen(tab2->card)-1];  break;
  case 3: case 4: do cc=(char)random(64); while(!iscard(cc));  break;
  }
  *s=(cc&0x7f); drawtab(tab); *s=c; iscardur=0; 
  menuflag=3;
}

inline void DrawScreen(void) { // Все нарисовать
  drawback();
  back2screen();
}

void newgame(void){   // Новая игра
  menuflag=t.f=0;
  undofrom=undoto=0;
  memcpy(&p,curpat,sizeof(patiens)); 
  char *s, *ss, *buf;
  int i, maxcard, rnd, rndval, _decks=(p.decks)?p.decks:1;  
  unsigned hide;
if(!p._calculated){
  int maxx=0, maxy=0, max_y=0, stepx,
    _minx=(p.minx)?p.minx:minx, 
    _miny=(p.miny)?p.miny:miny, 
    _deltax=(p.deltax)?p.deltax:deltax,
    _deltay=(p.deltay)?p.deltay:deltay;  
  // Иниц.
  fortab{
    if(tab->x>maxx) maxx=tab->x;
    if(tab->y>maxy) maxy=tab->y;
    if(tab->y<0) max_y=1;
  }
  stepx=(width-_minx-_minx)/(maxx+1);
  if(p.cardsize) --p.cardsize;
   else{
     p.cardsize=-1;
     do cardnabor(++p.cardsize);
     while(p.cardsize<2 && colodax+_deltax>stepx);
   }
   if(p.f & calcdy) _deltay=(height-_miny-_miny-(maxy+1)*coloday)/((maxy)?maxy:1);
  // Задать координаты
  fortab{
    if(!tab->x1) tab->x1=tab->x*stepx+_minx; 
    if(!tab->x2) tab->x2=tab->x1+stepx; 
    if(!tab->x0) tab->x0=tab->x1+(stepx>>1);
    if(!tab->x) tab->x1=-500; 
    if(tab->x==maxx) tab->x2=width+500;
  if(!tab->y0 || !tab->y1)   
    if(tab->y<0) tab->y1=tab->y0=height-_miny-coloday;
    else tab->y1=tab->y0=tab->y*(coloday+_deltay)+_miny;
  if(!tab->y2)   
    if(tab->y==maxy) tab->y2=(max_y)?height-coloday-_deltay:height;
    else tab->y2=tab->y1+(((tab->yn)?(tab->yn):(tab->shift || tab->shifthd)?2:1)*coloday)+_deltay;
  }
} // Общая часть
  cardnabor(p.cardsize);
  rybashka=(p.cardback==-1)?random(16):p.cardback;
  card=endcard=begcard;
  maxcard=cardsincoloda*_decks+1;
  t.card=card;
  card+=maxcard;
  undo=card;
  card+=maxcard;
  fortab{
     tab->card=card;
     card+=maxcard;
     tab->redeal=tab->sredeal;  
  }
  ZeroMemory(begcard,card-begcard);
  s=t.card;
  for(i=0;i<_decks;i++) s=fillcoloda(s);
  rndval=random(13)+1;
  // Заполняем картами
  fortab{
    f(firstrnd) tab->first=rndval;
    s=tab->card; ss=t.card;
    for(i=0;i<tab->cards;i++){
      if(!strlen(ss)) break;
      rnd=random(strlen(ss));
      *s++=ss[rnd];
      ss[rnd]=ss[strlen(ss)-1];
      ss[strlen(ss)-1]=0;
    }
  }
  fortab if(tab->id==stock) break;  // Остаток карт
  if(tab>p.tablen) tab=p.table;
  s=tab->card-1; ss=t.card; while(*++s);
  while(*ss){ 
    rnd=random(strlen(ss));
    *s++=ss[rnd];
    ss[rnd]=ss[strlen(ss)-1];
    ss[strlen(ss)-1]=0;
  }
  ZeroMemory(t.card,maxcard);
  // Переворачиваем если нужно
  fortab{
    if(tab->f&hidden || tab->hide){
      s=tab->card; hide=tab->hide;
      while(*s && *(s+1)){ *s|=0x80; ++s; if(!--hide) break;}
      f(firsthidden) if(*s) *s|=0x80;
    }
  }
if(!p._calculated){
  if(p.bmp && PKfind(toup(p.bmp),&PK))
    p.backjpeg=PK.curdir+1;
  ++p._calculated;
  memcpy(curpat,&p,sizeof(patiens)); 
}
  // Новый фон
  i=(p.backjpeg)?((p.backjpeg-1)%PK.maxdir):random(PK.maxdir);
  if(!bmp || lastbmp!=i){
    if(bmp){ GlobalFree(bmp); bmp=NULL;}
    if(!(PKgetnum(i,&PK))) return;
    if(!(buf=PKread(&PK))) return;
    if((s=PKextention(&PK)) && *(long *)s=='PMB.') bmp=(BMPst *)buf;
    else 
    if(!(bmp=(BMPst *)jpeg(buf,PK.cur->unpack_size))) return;
  }
  lastbmp=i;
  DrawScreen();
}

void showmenu(void){  // Меню выбора игры
  clearpage(); clearpage();
  char *screen;
  if(screen=lockprimary()){
    drawsys(screen,44);
    unlockprimary();
  }
  HDC hdc;
  TEXTMETRIC tm;
  int i,x,y,x0,xxmin;
  menuflag=1;
  if(hdc=GetDC(hWnd)){
    GetTextMetrics(hdc,&tm);
    SetBkColor(hdc,0);
    SetTextColor(hdc,0x00ffffff);
    xxmin=tm.tmAveCharWidth<<3;
    menudy=max(tm.tmHeight,6);
    menux=maxpatien/(height/menudy)+1;
    menuy=maxpatien/menux+1;
    menux=maxpatien/menuy+1;
    menuy0=(height-menuy*menudy)>>1;
    x0=width/(menux+1);
    for(i=-1,x=1;x<=menux;x++)
      for(y=0;y<menuy;y++)
        if(++i<maxpatien)
          TextOut(hdc, x0*x-xxmin, menuy0+y*menudy, patien[i].name,strlen(patien[i].name)); 
    ReleaseDC(hWnd,hdc);
  }
}

void selgame(int x, int y){   // Игра выбрана?
  if(issyskeys2(x,y)){ SendMessage(hWnd, WM_CLOSE, 0, 0); return;}
  if((y-=menuy0)<0 || (y=y/menudy)>=menuy) return;
  x=x/(width/menux);
  int i;
  if((i=x*menuy+y)>=maxpatien) return;
  curpat=patien+i;
  newgame();
}

void showvictory(){
  char *screen;
  int i;
  if(screen=lockprimary()){
    for(i=0;i<1000;i++)
      drawcard(screen,random(width),random(height),random(64)); 
    unlockprimary();
  }
}

void autodelete(tables *tab){
  char *s=tab->card, *ss, c;
  int f=tab->f, i;
  do{
    while(*s && (*s&0xf)!=13) ++s;
    if(!*s || !s[1]) return;
    ss=s; i=0;
    while((c=*(s+1)) && ++i<12 && (*s&0xf)-(c&0xf)==1){
      if((f&alternate) && !isalternate(*s,c)){i=0; break;}
      if((f&suit) && (((*s)>>4)&3)!=((c>>4)&3)){i=0; break;}
      if((f&same) && (((*s)>>4)&3)==((c>>4)&3)){i=0; break;}
      if((f&color) && !iscolor(*s,c)){i=0; break;}
      ++s;
    }
    if(i>=12){ //delete
      memmove(ss,ss+13,strlen(ss)-12);
      undofrom=undoto=0;
      DrawScreen();
      return;
    }
  }while(*s++);
}

void isvictory(void){ // Победа?
  tables *tabc=tab;
  fortab if(!(tab->f&happy) && *tab->card){ tab=tabc; return;}
  tab=tabc;
  menuflag=2;
  menucnt=1;
  SetTimer(hWnd, 2, 200, 0);
  showvictory();  
}

///////////Init////////
int Init(void){
  char **arg=argv;
  if(argc && (**argv=='/' || **argv=='?')){
	  MessageBox(NULL,"Cards ver 1.00 CB(c) 2005"\
      "\nВызов: Cards [Разрешение_X] [Y] [ini-файл]","   HELP",MB_OK);
    return 1;
  }
  if(argc && **argv>='0' && **argv<='9'){
    width=atoi(*argv);
    height=atoi(*++arg);
    *++arg; --argc; --argc;
  }
  randomize();
  // Загруз. парам.
  if(!loadfile("cardat.zip",PKopen,&PK)) return 2;  
  if(loadparam(((argc)?*arg:"cards.ini")))   
    return 3;
  // Загрузить карты
  if(!(mem=loadfile((char *)data,PKlist,&PK))) return 3;
  loadfile(0,PKclose,&PK);
  // Загрузить фоны
  if(!loadfile("fons.zip",PKopen,&PK)) return 4;  
  cardnabor(0);
  //selgame();
  //newgame();
   return 0;
}

void cardto(tables *to, tables *from, int num, int flag=0){ // Начиная с num карты (-1 последняя)
  char *s, *ss;
  if(!*from->card) return;
  if(num==-1) num=strlen(from->card)-1;
  if(flag & card2reverse){  //reverse
    s=to->card+strlen(to->card); ss=from->card+strlen(from->card);
    while(ss>from->card+num) *s++=(*--ss);
    *s=0;
  }else{
    //strcat(to->card,from->card+num);
    s=to->card+strlen(to->card); ss=from->card+num;
    do *s++=*ss++; while(*ss); *s=0;
  }
  from->card[num]=0;
  if(flag & card2nohide)
    to->card[strlen(to->card)-1]&=0x7f;
  //if(num>0 && !(from->f&firsthidden)) from->card[num-1]&=0x7f;
}

inline void hiddenall(tables *tab){
  char *s=tab->card;
  while(*s){ *s|=0x80; ++s;}
}

void stock2waste(){
  int i=0;
  tables *tabc;
  table=tab; 
  if(*table->card){
    fortab
      if(*table->card && strchr(table->to, (char)tab->id)) {++i; tabc=tab;
        undo[0]=table->card[strlen(table->card)-1];
        undo[1]=0;
        cardto(undoto=tab,undofrom=table,-1,card2nohide);
        f(autodel) autodelete(tab);
        if(table->f&redeal3){ undofrom=undoto=0;
          cardto(tab,table,-1,card2nohide); cardto(tab,table,-1,card2nohide);}
      }
      f(happy) isvictory();
  }else{
    if(!table->from) return;
    if(table->redeal==1) return;
    if(table->redeal>0) --table->redeal; 
    fortab
      if(strchr(table->from, (char)tab->id)) {++i; tabc=tab;
      cardto(table,tab,0,card2reverse);}
    hiddenall(table);
  }
  if(i!=1 || table->shift || table->shifthd || tabc->shift || tabc->shifthd){ undoto=undofrom=0; DrawScreen();}
  else{ drawtab(table,tabc);}
  //DrawScreen();
}

void fastredraw(int x, int y, int recalc){
  char *screen;
  bitbltfast(back2,back, t.x1-colodax2,t.y1, colodax,t.yn);
  bitbltfast(back2,back, x-t.x-colodax2,y-t.y, colodax,t.yn);
if(recalc){
  t.x0=x-t.x; t.y0=y-t.y;
  drawcards(back2,&t);
}
  if(screen=lockprimary()){
    bitbltfast(screen,back2, x-t.x-colodax2,y-t.y, colodax,t.yn);
    bitbltfast(screen,back2, t.x1-colodax2,t.y1, colodax,t.yn);
    unlockprimary();
  }
}

void strcat2(char *to, char *from){
  while(*to) ++to;
  do *to++=*from++; while(*from);
}

void makeundo(void){
  if(undofrom && undoto){ 
    strcat2(undofrom->card,undo); 
    undoto->card[strlen(undoto->card)-strlen(undo)]=0;
    undofrom=undoto=0; DrawScreen();
} }

void rbuttondown(int x, int y){
  int fnd;
  tables *from;
  if (menuflag) return;
 switch(issyskeys(x,y)){
  case 3: showmenu(); return;
  case 2: newgame(); return;
  case 1: makeundo(); return;
  }
  if(gettab(x,y) && getcard(x,y)){
    if(tab->to){ stock2waste(); return;}
    t.from=(char *)(from=tab);
    t.shift=tab->shift;
    t.shifthd=tab->shifthd;
    *t.card=0;
    cardto(&t,tab,t.first); 
    fnd=0;
    fortab if((tab->id==foundation) && (fnd=dropcard())) break;
    if(!fnd) fortab if(tab->id==tableau && tab!=from && (fnd=dropcard())) break;
    if(!fnd) fortab if(tab->id!=foundation && tab->id!=tableau && tab!=from && (fnd=dropcard())) break;
    if(fnd){ strcpy(undo,t.card);  undofrom=from; cardto(undoto=tab,&t,0);
       if(*from->card && !(from->f&firsthidden)) 
        from->card[strlen(from->card)-1]&=0x7f;
        f(autodel) autodelete(tab);
        f(happy) isvictory();
      if(from->shift || from->shifthd || !*from->card) DrawScreen();
      else{ drawtab(tab,from);}
    }else cardto(from,&t,0);
  }
}

void lbuttondown(int x, int y){
  switch(menuflag){
  case 1: selgame(x,y); return;
  case 2: if(menucnt--<=0){ KillTimer(hWnd,2); newgame();} return;
  case 3: DrawScreen(); menuflag=0; break;
  }
  switch(issyskeys(x,y)){
  case 3: showmenu(); return;
  case 2: newgame(); return;
  case 1: makeundo(); return;
  }
  if(gettab(x,y) && getcard(x,y)){
   if(tab->to){ stock2waste(); return;}
   t.from=(char *)tab;
   t.shift=tab->shift;
   t.shifthd=tab->shifthd;
   getmousey();
   *t.card=0;
   cardto(&t,tab,t.first);
   t.x0=t.x1=x-t.x; t.y0=t.y1=y-t.y;
   drawback();
   //back2screen();
   //drawtab(&t);
   t.f=1;
  }else{ t.f=0; *t.card=0;}
  t.num=0;
}

void lbuttonup(int x, int y){
  //int res;
  tables *from, *tabc;
  if(t.f){ 
    t.f=0;
    from=(tables *)t.from;
    if(gettab(x,y) && tab!=from && dropcard()){  // если можно положить
      strcpy(undo,t.card);
      undofrom=(tables *)t.from;
      cardto(tabc=undoto=tab,&t,0); 
      if(!*from->card && from->from && *from->from && !from->to) // Если последняя и from и !to
        fortab if(tab->id==*from->from && *tab->card){ 
        cardto(from,tab,-1); drawtab(tab); break;}
      if(*from->card && !(from->f&firsthidden)) 
        from->card[strlen(from->card)-1]&=0x7f;
      f(autodel) autodelete(tabc);
      f(happy) isvictory();
    }else{    // иначе вернуть на место
      cardto(tabc=from,&t,0);
    }
    fastredraw(x,y,0);
    drawtab(tabc,(from!=tabc)?from:0);
    //DrawScreen();
  } 
}

/////////////
int DDrawInit(HWND hWnd) {
  DDSCAPS ddscaps;
  if (DirectDrawCreate(NULL, &lpDDraw, NULL) != DD_OK) return 0;
  if (lpDDraw->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN) != DD_OK) return 0;
  if (lpDDraw->SetDisplayMode(width, height, bitpix) != DD_OK) return 0;
  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
  ddsd.dwBackBufferCount=1;
  ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
  if (lpDDraw->CreateSurface(&ddsd, &lpPrimarySurface, NULL) != DD_OK) return 0;
  ZeroMemory(&ddscaps, sizeof(ddscaps));
  ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
  if (lpPrimarySurface->GetAttachedSurface(&ddscaps,&lpSecondarySurface) != DD_OK) return 0;
  return 1;
}

void CleanUp(){   // Освободить ресурсы
  if(lpSecondarySurface) lpSecondarySurface->Release();
  if(lpPrimarySurface) lpPrimarySurface->Release();
  if(lpDDraw) lpDDraw->Release();
  loadfile(0,PKclose,&PK);
  if(!mem) GlobalFree(mem);
  if(!patien) GlobalFree(patien);
  if(!back) GlobalFree(back);
  if(!bmp)  GlobalFree(bmp);
  if(Mutex) ReleaseMutex(Mutex);
}

LRESULT CALLBACK DDrawWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  switch(message) {
    //case WM_CREATE: return 0;
    case WM_TIMER:  if(wParam==1){ if(++t.num>1) prikol();}else showvictory(); return 0;
    case WM_KEYDOWN:  if(wParam==VK_ESCAPE) SendMessage(hWnd, WM_CLOSE, 0, 0);  return 0;
    case WM_MOUSEMOVE: if(t.f){ fastredraw(LOWORD(lParam),HIWORD(lParam),1); t.x1=t.x0; t.y1=t.y0;}; return 0;
    case WM_LBUTTONDOWN: lbuttondown(LOWORD(lParam),HIWORD(lParam)); return 0;
    case WM_LBUTTONUP:  lbuttonup(LOWORD(lParam),HIWORD(lParam));  return 0;
    case WM_RBUTTONDOWN: rbuttondown(LOWORD(lParam),HIWORD(lParam)); return 0;
    case WM_DESTROY: KillTimer(hWnd, 1); CleanUp(); PostQuitMessage(0); return 0;
    default: return DefWindowProc(hWnd, message, wParam, lParam);
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  WNDCLASS wndClass;
  MSG msg;
  if(!(Mutex=CreateMutex(0,0,"ScreenSL"))) return 10;
  if(GetLastError()==ERROR_ALREADY_EXISTS) return 11;
  getargv(lpCmdLine);	
  if(int i=Init()){ CleanUp(); return i;}
#ifdef debugg
   tmptmp();
#endif
  ZeroMemory(&wndClass, sizeof(wndClass));
  wndClass.style = CS_HREDRAW | CS_VREDRAW;
  wndClass.lpfnWndProc = DDrawWndProc;
  wndClass.hInstance = hInstance;
  wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndClass.lpszClassName = "DDrawApp";
  RegisterClass(&wndClass);
  hWnd = CreateWindowEx(WS_EX_TOPMOST, wndClass.lpszClassName, "DirectDraw Application", WS_POPUP | WS_MAXIMIZE, 0, 0, GetSystemMetrics(SM_CXSCREEN), 
GetSystemMetrics(SM_CYSCREEN), NULL, NULL, hInstance, NULL);
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  if(!DDrawInit(hWnd)){ 
     MessageBox(hWnd,"Не могу запустить DirectX",0,MB_OK | MB_ICONEXCLAMATION);
     CleanUp(); return 12;
  }
  pitch=getpitch();
  if(!(back=(char *)GlobalAlloc(GPTR,(height*pitch<<3)+30000))){ CleanUp(); return 13;}
  back2=back+(height*pitch<<2);
  SetTimer(hWnd, 1, 420000, 0);
  showmenu();
  //selgame(0,0);
 // newgame();
  //DrawScreen();
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  //hWnd=GetForegroundWindow();
  //InvalidateRect(hWnd,0, 1);	
  /*HWND hw;
  hw=GetNextWindow(hWnd,GW_HWNDNEXT);
  ShowWindow(hw,SW_SHOWMAXIMIZED);
    InvalidateRect(hw,0, 1);
  UpdateWindow(hw); 
  //InvalidateRect(hWnd,0, 1);	*/
  return msg.wParam;
}


