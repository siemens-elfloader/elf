
// Пример 4. Игра Tetris 0.1 cbn(c) http://cbn.narod.ru  e-mail: cbn@yandex.ru
// Подключаем к проекту все приложенные файлы и еще div.r79 (библ. деления)


#include "..\swilib.h" // Главная библ. - берем ее из др.примеров
#include "font.h" // Шрифт
#include "..\random.h_" // "Случайные" числа
#include "tetris.h" // Заголовки
char *Title="Tetris 0.6 (c)bn";

const char *errors[]={
  0,0
};

typedef unsigned char byte;
extern char *screen;//[width*height]; // Экран 132*176
extern int width, height, screensize;
extern void DrawScreen(); // Функция перерисовки экрана
extern byte C65, S75, EL71;

//unsigned int err;
volatile int running=0; // Флаг активности
int x0, y0, size, mode=0;
#define RGB8(R,G,B) (B+(G<<2)+(R<<5))


//void savelog(int num){ // Записать лог
//  int f;
//  char tmp[100];
//  if((f=fopen("0:\\ZBin\\tet",A_WriteOnly+A_BIN+A_Create+A_Append,P_WRITE,&err))!=-1){
//    sprintf(tmp,"\n%d",num);
//    fwrite(f,tmp,strlen(tmp),&err); 
//    fclose(f,&err); 
//  }
//}

char filename[128]; // Храним имя файла
byte buf[1024];  // Буфер с параметрами и данными стакана
byte defbuf[]="T\10\15\4"; // Значения buf по умолчанию
/* Параметры в буфере: 
0 буква 'T'
1 ширина стакана x
2 высота стакана y
3 скорость игры
4 клеток не заполнено а линия убирается
5 уже заполнено линий снизу
6 номер текущей фигуры (0 нет)
7 ее поворот
8 ее x
9 ее y
10 ее цвет
11 Флаги: C65
12-13 очки
14-15 резерв
16 и далее данные цветов фигур стакана размером x*y */
enum {title,stwidth,stheight,speed,free,fill,num,rotate,x,y,color,c65,lorec,hirec,rez1,rez2,rez3,data};

const char stcolor=RGB8(3,3,1);
const unsigned char colors[]={ // Цвета фигур
  RGB8(7,0,0),RGB8(0,7,0),RGB8(0,0,3),RGB8(7,7,0),
  RGB8(7,0,0),RGB8(0,7,3),RGB8(7,0,3),RGB8(5,5,2),
  RGB8(3,7,3),RGB8(7,3,3),RGB8(7,7,1),RGB8(7,2,1),
  RGB8(3,3,3),RGB8(7,3,1),RGB8(3,7,1),RGB8(0,0,3)
};
const int colormask=0xf, figmask=7;
const int CMP=0, PUT=1, CLR=2;
int f, tmp, curx, cury, ecolor=0, oldcolor=0;
byte *eptr;

char menu[256]; // Меню
char help[]=
" Tetris 0.6"
"\n1.Load"
"\n2.Save"
"\n3.Width00-25:%d"
"\n4.Heigh00-34:%d"
"\n5.Speed 0-9:%d"
"\n6.FreeLn 0-9:%d"
"\n7.FillLn 0-9:%d"
"\n8.C65"
"\n9.Editor"
"\n0.Exit"
"\nScore:%d"
"\ncbn.narod.ru"
"\ncbn@yandex.ru";

GBSTMR timer;
void timer_proc(void){ // Функция выполняется по таймеру N раз в секунду
  if(running){
   if(!mode){
    down(0);
    REDRAW(); // Перерисовать экран
   }
   GBS_StartTimerProc(&timer,(10-buf[speed])*50,timer_proc); // Стартуем таймер с частотой N раз в секунду
//   }
 }
}

void onredraw(){ // Перерисовка экрана screen[132*176]
  if(!mode || mode==9){
    drawtetris();
  }
  if(mode==1) drawhelp();
}

inline void mode1(int n){
  mode=n;
//  GBS_DelTimer(&timer); 
}

void mode0(){
  drawstak();
  mode=0;
//  GBS_StartTimerProc(&timer,(10-buf[speed])*50,timer_proc); // Стартуем таймер с частотой N раз в секунду
}

//#define dat(x,y) buf[data+(y)*buf[width]+(x)]

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(keycode==RED_BUTTON) return 1; // Выход
    switch(mode){
    case 0: // in game
      switch(keycode){ // Код клавиши
      case LEFT_SOFT: case RIGHT_SOFT: mode1(1); break;
      case LEFT_BUTTON: case '4': 
        putfig(CLR); --buf[x]; if(putfig(CMP)) ++buf[x]; putfig(PUT); break;
      case RIGHT_BUTTON: case '6': 
        putfig(CLR); ++buf[x]; if(putfig(CMP)) --buf[x]; putfig(PUT); break;
      case UP_BUTTON: case '2': case ENTER_BUTTON: case '5':
        putfig(CLR); ++buf[rotate]; if(putfig(CMP)) --buf[rotate]; putfig(PUT); break;
      case DOWN_BUTTON: case '8': down(1); break; //drop
      default: return 0;
      }break;
    case 1: // main menu
      switch(keycode){
      case '0': return 1; // Exit
      case '1': loadgame(); mode0(); break;
      case '2': savegame(); mode0(); break;
      case '3': mode1(3); break;
      case '4': mode1(4); break;
      case '5': mode1(5); break;
      case '6': mode1(6); break;
      case '7': mode1(7); break;
      case '8': buf[c65]=(buf[c65]?0:1); init(); 
        newgame(); newfig(); mode0(); break;
      case '9': mode1(9); curx=cury=0; oldcolor=buf[data]; *(eptr=buf+data)=colors[ecolor]; 
        drawstak(); break;
      case LEFT_SOFT: case RIGHT_SOFT: 
      case LEFT_BUTTON: case RIGHT_BUTTON:
      case UP_BUTTON:   case DOWN_BUTTON: case ENTER_BUTTON:
        mode0(); break;
      default: return 0;
      } break;
    case 3: // width
      if(keycode>='0' && keycode<='9'){ tmp=keycode-'0'; mode1(31);}
      else mode0();; break;
    case 4: // height
      if(keycode>='0' && keycode<='9'){ tmp=keycode-'0'; mode1(41);}
      else mode0(); break;
    case 31: 
      if(keycode>='0' && keycode<='9'){ 
        buf[stwidth]=tmp*10+keycode-'0'; init(); newgame(); newfig(); }
      mode0(); break;
    case 41: 
      if(keycode>='0' && keycode<='9'){ 
        buf[stheight]=tmp*10+keycode-'0'; init(); newgame(); newfig(); }
      mode0(); break;
    case 5: // speed
      if(keycode>='0' && keycode<='9'){ buf[speed]=keycode-'0';}
      mode0(); break;
    case 6: // freelines
      if(keycode>='0' && keycode<='9'){ buf[free]=keycode-'0';}
      mode0(); break;
    case 7: // fillines
      if(keycode>='0' && keycode<='9'){ buf[fill]=keycode-'0';}
      mode0(); break;
    case 9: // editor
      switch(keycode){
      case LEFT_SOFT: *eptr=colors[ecolor=(ecolor+1)&colormask]; break;
      case RIGHT_SOFT: *eptr=oldcolor; mode0(); break;
      case ENTER_BUTTON: case '5': oldcolor=colors[ecolor]; break;
      case GREEN_BUTTON: oldcolor=0; break;
      case LEFT_BUTTON: case '4': 
        if(curx>0){ *eptr=oldcolor; oldcolor=*--eptr; *eptr=colors[ecolor]; --curx;} break;
      case RIGHT_BUTTON: case '6': 
        if(curx<buf[stwidth]){ *eptr=oldcolor; oldcolor=*++eptr; *eptr=colors[ecolor]; ++curx;} break;
      case UP_BUTTON: case '2':
        if(cury>0){ *eptr=oldcolor; oldcolor=*(eptr-=buf[stwidth]); *eptr=colors[ecolor]; --cury;} break;
      case DOWN_BUTTON: case '8': 
        if(cury<buf[stheight]){ *eptr=oldcolor; oldcolor=*(eptr+=buf[stwidth]); *eptr=colors[ecolor]; ++cury;} break;
      default: return 0;
      }break;
    default: mode0(); break;
    } break;
  }
  onredraw(); DrawScreen(); // Перерисовать экран
  return 0;
}

void savegame(){ // Записать игру
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    fwrite(f,buf,buf[stwidth]*buf[stheight]+data,&err); 
    fclose(f,&err);
}}

void loadgame(){ // Загрузить игру
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f,buf,sizeof(buf),&err);
    fclose(f,&err);
  }
  init();
}

void onclose(){ // Закрытие окна
  running=0; // Сигнал на остановку фонового процесса
  GBS_DelTimer(&timer); //(у меня pickoff)???
  //  GBS_StopTimer(&timer); // Останавливаем таймер (у меня pickoff)
  savegame();  // Сохраняем результаты
}

void onexit(){ // Выход
}

//void execute(){ // Выполняем фоновый процесс (не нужен счас)
//  running=1;
//  while(running){ // Пока нет команды на останов
//   ;
//  }
//}

void oncreate(){ // Создание окна
//  SUBPROC((void *)execute); // Запускаем фоновый процесс (не нужен счас)
  running=1; mode=0;
  //REDRAW();//??
  GBS_StartTimerProc(&timer,(10-buf[speed])*50,timer_proc); // Стартуем таймер с частотой N раз в секунду
}

double atan2(double,double);

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  char *file=exename+strlen(exename);
  while(--file>exename && *file!='.');
  file[1]='t';file[2]='e'; file[3]='t'; file[4]=0;
  memcpy(filename,exename,strlen(exename)+1);
  file=fname?fname:exename;
  if((f=fopen(file,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f,buf,sizeof(buf),&err);
    fclose(f,&err);
  }
  Randomize();
  init();
//  int a=atan2(1,2);
//  *(int*)filename=a;
  return 0;
}

//////////////// Ниже специфичные тетрис функции /////////////////////
// функции выше универсальны и пригодятся вам в создании своей игры //

void drawstak(){ // Нарисовать пустой стакан 
  int i,j;
  char *s;
  memset(screen,0,screensize);
  if(x0>=3){
    s=screen+y0*width+x0;
    for(i=size*buf[stheight], j=size*buf[stwidth];i>0;i--,s+=width)
      s[-3]=s[-2]=s[-1]=s[j]=s[j+1]=s[j+2]=stcolor;
  }
  if(y0>=3){  
    s=screen+(y0+size*buf[stheight])*width+x0-3;
    memset(s,stcolor,j+6);
    memset(s+width,stcolor,j+6);      
  }
}

void init(){ // Иниц. парам.
  int i;
  if(buf[title]!='T' || buf[speed]>9 || buf[stwidth]<5 || buf[stheight]<5 || buf[stwidth]>25 || buf[stheight]>34
     || buf[fill]>buf[stheight]-3 || buf[free]>buf[stwidth]-3){
    memset(buf,0,sizeof(buf));
    memcpy(buf,defbuf,sizeof(defbuf));
  }
  size=(buf[c65]?130:(height-6))/buf[stheight]; 
  i=126/buf[stwidth];
  if(i<size) size=i;
  x0=(width-size*buf[stwidth])>>1;
  y0=((buf[c65]?130:(height-6))-size*buf[stheight])>>1;
  drawstak();
  if(!buf[num]) newfig();
  else delines();
}

void drawtetris(){ // Нарисовать все фигуры внутри стакана
  int i,j,k,dscr=width*size;
  byte *ptr=buf+data;
  char *s, *scr=screen+y0*width+x0, col;
  for(j=0;j<buf[stheight];j++){
    s=scr;
    for(i=0;i<buf[stwidth];i++){
      col=*ptr++;//colors[*ptr++];
      for(k=0;k<size;k++,scr+=width)
        memset(scr,col,size);
      scr-=dscr-size;
    }
    scr=s+dscr;
  }
}

void drawsym(char *out, char c){ // Отобразить символ на экране
  int i,j;
  byte b, *bptr=(byte*)font+((c-=0x20)<=0?0:(c<<3));
  for(j=0;j<8;j++){
    b=*bptr++;
    for(i=0;i<8;i++){
      *out++=(b&0x80)?0xff:0; //colors
      b<<=1;
    }
    out+=width-8;
  }
}

void drawhelp(){ // Показать меню
  //return; /////////
  int i=0,x=0,y=0;
  sprintf(menu,help,buf[stwidth],buf[stheight],buf[speed],buf[free],buf[fill],buf[lorec]|(buf[hirec]<<8));
  while(menu[i]){
    if(menu[i]=='\n' || x>=width/8){ x=0; ++y;}
    if(y>=height/10) break;
    drawsym(screen+y*width*10+x*8+4,menu[i]);
    ++x;
    ++i;
  }
//  onredraw(); DrawScreen();
}

//void *memset(void *mem, int val, int size){ // Станд. ф-я очистки памяти
//  char *s=(char*)mem;
//  while(--size>=0) *s++=(char)val;
//  return mem;
//}

void newgame(){ // Новая игра
  int i,j,k;
  buf[lorec]=buf[hirec]=0;
  memset(buf+data,0,j=buf[stwidth]*buf[stheight]);
  if(buf[fill]){
    k=buf[stwidth]*buf[fill];
    for(i=0;i<k;i++) buf[data+j-Random()%k]=colors[Random()&colormask];
  }
}

int newfig(){ // Новая фигура (тут же проверка новой игры)
  int cnt=0;
lll:
    delines();
    buf[rotate]=buf[y]=0;
    buf[x]=buf[stwidth]>>1;
    buf[color]=colors[Random()&colormask];
    if((buf[num]=(Random()&figmask)+1)==8) buf[num]=3;
      //while((buf[num]=(Random()&figmask)+1)==8);
    if(putfig(CMP)){ //new game
//      savelog(buf[num]);
      newgame();//!!!!!!!!!
      if(!cnt++) goto lll;
    }putfig(PUT);
  return 0;
} 

// action: 0=CMP помещается ли фигура, 1=PUT положить фигуру, 2=CLR убрать фигуру
inline int collis(int x, int y, int action){ // фигура врезается?
  if(x<0 || (action && y<0) || x>=buf[stwidth] || (y>=buf[stheight])) return 1;
  if(action)
    buf[data+y*buf[stwidth]+x]=(action==1)?buf[color]:0;
  else 
    if(y>=0 && y<buf[stheight] && buf[data+y*buf[stwidth]+x]) return 1;
  return 0;
}

int putfig(int action){ //0=CMP, 1=PUT, 2=CLR (см.выше)
  signed char *f=fig+((buf[num]-1)<<5)+((buf[rotate]&3)<<3);
  int i;
  for(i=0;i<4;i++,f+=2)
    if(collis(buf[x]+f[0],buf[y]+f[1],action))
      if(!action) return 1;
  return 0;
}

void down(int loop){ // Бросить фигуру вниз
  do{
    putfig(CLR); ++buf[y];
    if(putfig(CMP)){
      --buf[y]; putfig(PUT);
      newfig();
      break;
    }else putfig(PUT);
  }while(loop);
}

void delines(){ // Удалить заполненные линии
  int i=0,j, len=buf[stwidth];
//  char tmp[8];
  byte *p,*pp;
  p=buf+data+buf[stwidth]*buf[stheight];
  do{
    j=0;
    for(i=0;i<len;i++)
      if(*--p) ++j;
    if(j>=len-buf[free]){
      if(!++buf[lorec]) ++buf[hirec];
      pp=p;
      p+=len;
      while(--pp>buf+data) pp[len]=*pp;
      memset(buf+data,0,len);
    }
  }while(p>buf+data);
  //print record
//  sprintf(tmp,"%d",(int)(buf[lorec]|(buf[hirec]<<8)));
//  while(tmp[i]){
//    drawsym(screen+i*8+4,tmp[i]);
//    i++;
//  }
}

