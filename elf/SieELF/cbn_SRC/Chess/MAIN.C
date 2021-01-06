
// Chess
//#define HIGHCOLOR // 16-битный режим
//#define GRAPH  // Графика
//#define NEWSGOLD
#include "..\swilib.h"
#include "symtab.h"
#include "gai.h"

char filename[128];

#define paramlength 16
unsigned char param[paramlength]={2,5,1};

enum{ pversion, plevel, pcolor};
int save_B[120], undo_B[120] ;//saved

unsigned char bw=1, movfrom=0, movto=0;
int figur=0, figcol=0;
int from=0, to=0;
volatile int thinking=0;

char *Title="Chess 0.4 (c)bn";
const char *errors[]={
  0,
  "No Dat file!\0",
  "Unknown error!"
};

void newgame(int saved);
extern short *screen; // Экран 132*176*2
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();
//typedef unsigned char byte;

//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

char *fon=0;
char *fig=0;
int curx=4, cury=1;
char fastfon=0;
extern int width, height;

//byte log[4096], *plog=log;
//const int maxlog=4096;
//int logged=0; // Флаг: Нужно сохранять лог?
//byte *buf=0; 
//int bufsize; 
volatile int running=0; // Процесс проверяет флаг и выходит если =0
int mode=0;
const int curcolor=0x1f, maskcolor=0x1f, bkcolor=RGB16(22,44,22),menucolor=0xffff,menubkcolor=0x1f, movecolor=0;

char menu[]=
" Chess 0.4 (c)bn"
"\n3.New"
"\n4.Undo"
"\n5.Editor"
"\n6.Easy/Hard"
"\n9.Hint"
"\n0.Exit"
"\ncbn.narod.ru"
"\ncbn@yandex.ru";

//"\n7.Black/White"
//"\n8.Rotate"

void drawsym(short *out, char c){ // Отобразить символ на экране
  int i,j;
  byte b, *bptr=(byte*)symtab+((c-=0x20)<=0?0:(c<<3));
  for(j=0;j<8;j++){
    b=*bptr++;
    for(i=0;i<8;i++){
      *out++=(b&0x80)?menucolor:menubkcolor; //colors
      b<<=1;
    }
    out+=width-8;
  }
}

void drawhelp(){
  int i=0,x=0,y=0;
//  sprintf(menu,help,frameskip,splitcolor);
  while(menu[i]){
    if(menu[i]=='\n' || x>=width/8){ x=0; ++y;}
    if(y>=height/10) break;
    drawsym(screen+y*width*10+x*8+4,menu[i]);
    ++x;
    ++i;
  }
}
//void outlog(char *s){
//  int i;
//  if(plog+(i=strlen(s))<log+maxlog-3){
//    memcpy(plog,s,i); *(plog+=i)=0xd; *++plog=0xa; ++plog;
//  }logged=1;
//}
//
//GBSTMR timer;
//void timer_proc(void){ // Функция выполняется по таймеру 10 раз в секунду
//  if(running){
////    REDRAW(); // Перерисовать экран
//  }
//  GBS_StartTimerProc(&timer,262/10,timer_proc); // Стартуем таймер с частотой 10 раз в секунду
//  // Он выполняется однократно поэтому его нужно постоянно запускать
//}

void drawcur1(int pos){
  int i, cx=7-(pos-21)%10, cy=7-(pos-21)/10;
  short *scr=screen+(cy*15+6)*width+cx*15+6;
  memsetw(scr,movecolor,15);
  scr+=width;
  for(i=0;i<13;i++,scr+=width){
    *scr=scr[14]=movecolor;
  }
  memsetw(scr,movecolor,15);
}


void drawcur(int curx, int cury, int color){
  int i;
  short *scr=screen+((7-cury)*15+6)*width+(7-curx)*15+6;
  memsetw(scr,curcolor,15);
  memsetw(scr+=width,curcolor,15);
  scr+=width;
  for(i=0;i<11;i++,scr+=width){
    *scr=scr[1]=scr[13]=scr[14]=color;
  }
  memsetw(scr,curcolor,15);
  memsetw(scr+width,curcolor,15);
}

inline void cls(){
  memsetw(screen,bkcolor,screensize>>1);
//  for(int i=0;i<132*176;i++) screen[i]=bkcolor;
}

inline void centerbmp(char *bmp){
  if(bmp){
  int x=(width-*(short*)bmp)>>1, y=(height-*(short*)(bmp+2))>>1;
    bitblt(screen, bmp, x<0?0:x, y<0?0:y, 0,0,0,0,0,0);
  }
}

inline void showfon(){ 
  if(fastfon) memcpy(screen,fon+4,screensize);
  else{
    cls();
    centerbmp(fon);
  }
//  showstart();
}


inline void drawfig(int xx, int yy, int num){
  bitblt(screen,fig,xx,yy,15,15, ((num>>4)-1)*15,(num&1)?15:0, maskcolor,0);
}

void drawexcel(int x, int y){
  int xx, yy;
  int i=(x+y)&1, j=y*10+21+x;
  bitblt(screen,fig,xx=(7-x)*15+6,yy=(7-y)*15+6,15,15, i?15:0,30, 0,0);
  if(B[j]) drawfig(xx,yy,B[j]);
//  if((tmp+=0x10)>0x62) tmp=0x10+((tmp&1)?2:1);
}

void drawdeck(){
  int i,j;
//  tmp=0x11;
  showfon();
  for(i=0;i<8;i++)
    for(j=0;j<8;j++)
      drawexcel(i,j);

  if(!thinking)
    drawcur(curx,cury,curcolor);

    if(from){
      drawcur1(from);
    }else
  if(movfrom){
    drawcur1(movfrom);
    drawcur1(movto);
    movfrom=0;
  }
}

//void execute(){
//  running=1;
//  while(running){ // Пока нет команды на останов
//    ;
//  }
//}

void onredraw(){ // Перерисовка экрана
  if(mode>1) drawhelp();
  else drawdeck();
}

void hod(){ // Ход компьютера
  thinking=1;
  struct MOVE *m;  // СДелать MOV через int для СОРТИРОВКИ
  BeReady(); 
  m=ComputerThink();
  DoMove(movfrom=m->from,movto=m->dest);
  thinking=0;
  REDRAW();
}

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: return 0; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(thinking) return 0;
    if(keycode==RED_BUTTON) return 1; //exit    
    switch(mode){ // in MENU
      case 100:
      switch(keycode){
      case '0': return 1; // Выход
      case '3': newgame(0); mode=0; break;
      case '4': if(*undo_B){ //is it undo
           movsd(B,undo_B,120);        
           build(); BeReady();
        }  mode=0; break;
      case '5': mode=1; break; //editor
      case '6': param[plevel]=(param[plevel]==5)?4:5;
        SetLevel(param[plevel],bw);  mode=0; break;
      //case '7': bw=(bw+1)&1; mode=0; break;        
      case '9':  mode=0; thinking=1; SUBPROC((void*)hod); break;
       default: mode=0; break;
      }break;
      //
    case 1: //FIG EDIT
    switch(keycode){ // Код клавиши
    case RIGHT_BUTTON: if((figur+=0x10)>0x60) figur=0; break;
    case LEFT_BUTTON: if((figur-=0x10)<0) figur=0x60; break;
    case UP_BUTTON: 
    case DOWN_BUTTON: figcol=(figcol+1)&1; break;

    case RIGHT_SOFT: case GREEN_BUTTON:
    case ENTER_BUTTON: mode=0; 
      B[cury*10+curx+21]=(figur)?((figcol+1)|figur):0;
      build(); BeReady(); break;
    } B[cury*10+curx+21]=(figur)?((figcol+1)|figur):0;
    break;
    //      
    case 0: default: // in GAME
    switch(keycode){ // Код клавиши
      case RIGHT_SOFT: mode=100; showfon();  break;  
    //case LEFT_SOFT: 
    case RIGHT_BUTTON: if(--curx<0) curx=7; break;
    case LEFT_BUTTON: if(++curx>7) curx=0; break;
    case DOWN_BUTTON: if(--cury<0) cury=7; break;
    case UP_BUTTON: if(++cury>7) cury=0; break;
    case ENTER_BUTTON: //MOVE!!!//if(GlobalAI_CanMove) DoMove();
      if(from){
        if((to=cury*10+curx+21)==from){ from=0; break;}
        if(GlobalAI_CanMove(from,to)){ 
          movsd(undo_B,B,120);        
          DoMove(from,to); from=0; thinking=1; SUBPROC((void*)hod); 
        } from=0;
      }else{
        if(!B[from=cury*10+curx+21]) from=0;
      }break;
      
    case GREEN_BUTTON:  mode=1; break; //edit
    case LEFT_SOFT: thinking=1; SUBPROC((void*)hod); break; //hint
    default: return 0;
    }}
//    onredraw(); DrawScreen(); // Перерисовать экран
    REDRAW();
  }
  return 0;
}

//void savelog(){ // Записать лог
//  int f;
//  byte *file;
//  if(logged){
//  file=log+strlen((char*)log);
//  while(--file>log && *file!='.');
//  *++file='e';file[1]='r'; file[2]='r'; file[3]=0;
//  if((f=fopen((char*)log,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
//    *file='b';file[1]='a'; file[2]='s'; 
//    fwrite(f,log,plog-log,&err); 
//    fclose(f,&err); 
//}}}

void loadgame(){
  int f;
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f,param,paramlength,&err);
    fread(f,save_B,120*4,&err);
    Color=param[pcolor];
    fclose(f,&err);
  }
}

void savegame(){
  int f;
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
    param[pcolor]=Color;
    fwrite(f,param,paramlength,&err);
    fwrite(f,B,120*4,&err);
    fclose(f,&err);
  }
}

void onclose(){ // Закрытие окна
  running=0; // Сигнал на остановку фонового процесса
  savegame();
//  GBS_StopTimer(&timer); // Останавливаем таймер  pickoff!!
//  savelog();  // Сохраняем лог
} 

void onexit(){ // Выход
  if(fig) mfree(fig); // Освобождаем память
  if(fon) mfree(fon); // Освобождаем память
}

void newgame(int saved){
//  Randomize();
//  Color=bw;
  curx=4; cury=1;
  SetLevel(param[plevel], Color); 
  init();
  Color=saved?1:2;//WHITE;
  memcpy(B,(saved)?save_B:ref_B,10*12*sizeof(int));
  build();
  BeReady(); 
  if(!saved) hod();
}

void oncreate(){ // Создание окна 
  Randomize();
  GlobalAIinit();
  newgame(*save_B);
//  SUBPROC((void *)execute); // Запускаем фоновый процесс 
//  GBS_StartTimerProc(&timer,262/2,timer_proc); // Стартуем таймер с частотой 2 раз в секунду
}
          
int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  strcpy(strrchr(exename,'.'),".png");
  if(!(fig=loadgraph(exename))) return 1;
  strcpy(strrchr(exename,'.'),".bmp");
  if((fon=loadgraph(exename)) && *(short*)fon==width && *(short*)(fon+2)==height) fastfon=1;
  strcpy(strrchr(exename,'.'),".chs");
  strcpy(filename,exename);
  loadgame();
  return 0;
}

