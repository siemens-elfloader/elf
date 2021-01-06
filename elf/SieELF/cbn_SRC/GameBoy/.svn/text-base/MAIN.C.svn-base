
// GameBoyColor

//#define HIGHCOLOR
//#define UNPACK

#include "..\ZFont.h"
#include "defs.h"
#include "regs.h"
#include "mem.h"
#include "hw.h"
#include "rtc.h"
#include "rc.h"

extern unsigned int randseed;
const void *ZEROSTART=&randseed;
const int ZEROSIZE=0x78df6;

extern short *screen;
extern int width, height, screensize;
extern unsigned char SGOLD2, C65, S75, EL71;
char *Title="GameBoy 0.91 (c)bn";
//extern char *error;

extern void cpu3_emulate(int cycles);

void (*cpuemulate)(int cycles)=cpu_emulate;
int frames=0;
int frameskip=2;

short *scr=0;//[160*144];

char filename[128], romname[128];
const byte timedelays[]={0, 262/5, 262/10, 262/15, 262/20, 262/25};
//typedef unsigned char byte;

volatile int running=0, exit=0, isredraw=0, loadsave=0;//, stopped=0; // Процесс проверяет флаг и выходит если =0
volatile int mode=0, timedelay=0;

extern void DrawScreen();
void onredraw();

const char *errors[]={
  0,
  "Нажимайте на .gbc или .gb\0",
  "Не создать буфер!\0",
  "Ром слишком велик! :)\0"
  "Нулевой размер памяти РОМ\0",
  "Нулевой размер РАМ\0"
};


//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

#define paramlength 256

//0 64 параметры 
//64 32*3  коды  действия  нажаты
//160 32*3 то же альтерн
byte param[paramlength]=
"\x02\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x3D\x3E\x3B\x3C\x2A\x23\x34\x36\x32\x38\x35\x1A\x31\x33\x37\x39"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x02\x01\x04\x08\x10\x20\x02\x01\x04\x08\x10\x80\x80\x40\x10\x20"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x3D\x3E\x3B\x3C\x2A\x23\x34\x36\x32\x38\x35\x1A\x31\x33\x37\x39"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x02\x01\x04\x08\x10\x20\x02\x01\x04\x08\x10\x80\x80\x40\x10\x20"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
enum{ pframeskip, palternate, protate, presize, pfrlimit, poptimize}; //параметры

#define maxkey 32
#define key1 64
#define key2 160

inline void cls(){ memset(screen,0,screensize);}
int saveini();
int loadini();
byte *redefineptr;

void  keyboard_init(){
  memset(param+key2-maxkey,0,maxkey);
  memset(param+paramlength-maxkey,0,maxkey);
//  byte *ptr=param;
//  for(; *ptr; ptr++) *++ptr&=0x7f;
//  ptr=param+param[palternate];
//  for(; *ptr; ptr++) *++ptr&=0x7f;
}

char menu[256]; // Меню
char help[]=
" GameBoy 0.91"
"\n1.Load 0-9"
"\n2.Save 0-9"
"\n3.FrmSkp 0-9:%d"
"\n4.FrmLim 0-5:%d"
"\n5.Redefine"
"\n6.Optimize:%d"
"\n7.Rotate"
"\n8.Resize"
"\n0.Exit"
"\ncbn.narod.ru"
"\ncbn@yandex.ru";

char helpkey[]=" 1 start\n2 up\n3 select\n4 left\n5\n6 right\n7 A\n8 down\n9 B";
char helpsel[]=" Select key";

void drawsym(short *out, char c){ // Отобразить символ на экране
  int i,j;
  unsigned char b, *bptr=(unsigned char*)zfont+((c-=0x20)<=0?0:(c<<3));
  for(j=0;j<8;j++){
    b=*bptr++;
    for(i=0;i<8;i++){
      *out++=(b&0x80)?0xffff:0x1f; //colors 0xffff
      b<<=1;
    }
    out+=width-8;
  }
}

void drawhelp(char *help){ // Показать меню
  int i=0,x=0,y=0;
  sprintf(menu,help,frameskip,param[pfrlimit],param[poptimize]);//,param[pslow]);//,buf[stwidth],buf[stheight],buf[speed],buf[free],buf[fill],buf[lorec]|(buf[hirec]<<8));
  while(menu[i]){
    if(menu[i]=='\n' || x>=width/8){ x=0; ++y;}
    if(y>=height/10) break;
    drawsym(screen+y*width*10+x*8+4,menu[i]);
    ++x;
    ++i;
  }
}


GBSTMR timer;
void timer_proc(void){ // Функция выполняется по таймеру n раз в секунду
//  if(!stopped){
  if(isredraw){
    isredraw=0;
    REDRAW(); // Перерисовать экран
  }
  if(timedelay)
    GBS_StartTimerProc(&timer,timedelay,timer_proc); // Стартуем таймер с частотой 10 раз в секунду
  // Он выполняется однократно поэтому его нужно постоянно запускать
//  }
}

//void execute(){ // Выполняем basic код
//  running=1;
//  while(running){ // Пока нет команды на останов
//    ;
//  }
//}

extern void redraw(void *TO, void *FROM); //1 в 1 (обрезано по краям)
extern void redraw2(void *TO, void *FROM); //уменьшение до экрана
extern void redraw3(void *TO, void *FROM); //повернуто

extern void redraw5(void *TO, void *FROM); //for EL
extern void redraw6(void *TO, void *FROM); //EL double size

extern void rotate(void *buf, int dwordsize); //поворот

//EL
//  int j;
//  short *s, *ss;
//  s=screen+76*240+40; ss=scr;
//  for(j=0;j<144;j++){
//    movsd(s,ss,80);
//    s+=240;
//    ss+=160;
//  }
//176
//      if(0){//param[pslow]){ //медленно но верно
//      s=screen+(C65?0:(132*16)); ss=scr+14;
//      for(j=0;j<144;j++){
//        memcpy(s,ss,132*2);
//        s+=132;
//        ss+=160;
//       }
//      }else{ //быстро


void onredraw(){ // Перерисовка экрана screen[132*176]
  if(running){
    if(param[protate]==2 && !C65) rotate(screen, screensize);  
    if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));
  }
}

void on2redraw(void){
if(EL71){
  if(param[presize]) redraw5(screen+76*240+40,scr);
  else redraw6(screen+4*240,scr);
}else{//176*132
  if(param[protate] && !C65){
    redraw3(screen+8*132,scr+6*160);//???
//    if(param[protate]==2) rotate(screen, screensize);
  }else{
    if(param[presize]) redraw(screen,scr+14+((C65)?7*160:0));
    else redraw2(screen,scr+((C65)?7*160:0)); //уменьшение
  }
}
//  if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));
  isredraw=1;
}

//  int i,j;
//  for(i=0,j=color++;i<132*176;i++){
//    screen[i]=j++;
//  }
/*
void kbhit(unsigned char keycode){
  switch(keycode){
  case '4': hw.pad|=PAD_LEFT; break;
  case '2': hw.pad|=PAD_UP; break;
  case '6': hw.pad|=PAD_RIGHT; break;
  case '8': hw.pad|=PAD_DOWN; break;
  case '5': hw.pad|=PAD_START; break;
  case '0': hw.pad|=PAD_SELECT; break;
  case '#': hw.pad|=PAD_A; break;
  case '*': hw.pad|=PAD_B; break;
  }
}

void kbunhit(unsigned char keycode){
  switch(keycode){
  case '4': hw.pad&=~PAD_LEFT; break;
  case '2': hw.pad&=~PAD_UP; break;
  case '6': hw.pad&=~PAD_RIGHT; break;
  case '8': hw.pad&=~PAD_DOWN; break;
  case '5': hw.pad&=~PAD_START; break;
  case '0': hw.pad&=~PAD_SELECT; break;
  case '#': hw.pad&=~PAD_A; break;
  case '*': hw.pad&=~PAD_B; break;
  }
}
*/
void keypress(unsigned char keycode, int press){
  byte *ptr=param+(param[palternate]?key2:key1);
  if(ptr=(byte*)strchr((char*)ptr,keycode)) //есть клавиша
    if(press){ 
      hw.pad|=ptr[maxkey];
      ptr[maxkey+maxkey]=1;
    }else{
      hw.pad&=~ptr[maxkey];
      ptr[maxkey+maxkey]=0;
    }
}


int keyexit(){
  running=0; exit=1; saveini(); 
//    fmapclose(&fmap);
  return 0;
}

void savename(char c){
  char *s=strrchr(romname,'.');
  *++s='s'; *++s=c; *++s=0;
}

void setemulate(){
  cpuemulate=(param[poptimize])?cpu_emulate: cpu3_emulate;
}


// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  byte *ptr;
//  int f;
  switch(pressed){
  case KEY_UP: if(!mode) keypress(keycode,0); break; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(exit) return 1; //Выход
    if(keycode==RED_BUTTON)  return keyexit();
    switch(mode){
    case 100: // main menu
      switch(keycode){
      case '0': return keyexit(); // Exit
      case '1': mode=1; break; //load
      case '2': mode=2; break; //save
      case '3': mode=3; break; //frmskip
      case '4': mode=4; break; //frmlim
      case '5': mode=99; break; //redefine
      case '6': param[poptimize]=(param[poptimize]+1)&1;
        setemulate(); mode=0; break; //optimize
      case '7': mode=0; cls(); if(++param[protate]>2) param[protate]=0; break; //rotate
      case '8': mode=0; cls(); param[presize]=~param[presize]; break; //resize
//      case '9': param[pslow]=(param[pslow]+1)&1; break; //slow
      default: mode=0; break;
      }break;
    case 1: //load
      if(keycode>='0' && keycode<='9'){ 
        savename(keycode);
        loadsave=1; running=0;
//        if((f=fopen(romname,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
//          loadstate(f);
//          fclose(f,&err);
//        }
      }
      mode=0; break;
    case 2: //save
      if(keycode>='0' && keycode<='9'){
        savename(keycode);
        loadsave=2; running=0;
//        if((f=fopen(romname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
//          savestate(f);
//          fclose(f,&err);
//        }
      }
      mode=0; break;
    case 3: //frame_skip
      if(keycode>='0' && keycode<='9') frames=frameskip=keycode-'0';
      mode=0; break;
    case 4: //frame_limit
      if(keycode>='0' && keycode<='5'){
        if(timedelay=timedelays[param[pfrlimit]=keycode-'0'])
          GBS_StartTimerProc(&timer,timedelay,timer_proc);
      }
      mode=0; break;
    case 5: //redefine
      mode=99; break;

    case 99: //redefine - sel key
     switch(keycode){
      case RIGHT_SOFT:
      case LEFT_SOFT:
      //case GREEN_BUTTON: 
      case RED_BUTTON: mode=0; break;
      default:
      ptr=param+(param[palternate]?key2:key1);
      if(!(redefineptr=(byte*)strchr((char*)ptr,keycode))){ //нет клавиши
        redefineptr=ptr+strlen((char*)ptr);
        *redefineptr=keycode;
      }
       redefineptr+=maxkey;
       mode=98; break;
     } break; 

    case 98: //select key action
      switch(keycode){
      //  char helpkey[]=" 1 start\n2 up\n3 select\n4 left\n5\n6 right\n7 A\n8 down\n9 B";
      case '1': *redefineptr=PAD_START; break;
      case '3': *redefineptr=PAD_SELECT; break;
      case '2': *redefineptr=PAD_UP; break;
      case '8': *redefineptr=PAD_DOWN; break;
      case '4': *redefineptr=PAD_LEFT; break;
      case '6': *redefineptr=PAD_RIGHT; break;
      case '7':  *redefineptr=PAD_A; break;
      case '9':  *redefineptr=PAD_B; break;
      } mode=0; break;

    case 0: default:
      switch(keycode){
      case RIGHT_SOFT: mode=100; break; //main menu
      case LEFT_SOFT: param[palternate]=~param[palternate]; break;
      default: keypress(keycode,1);
      }break;
    }

//    onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

/*
void kbunhit(unsigned char keycode){
  switch(keycode){
  case '4': hw.pad&=~PAD_LEFT; break;
  case '2': hw.pad&=~PAD_UP; break;
  case '6': hw.pad&=~PAD_RIGHT; break;
  case '8': hw.pad&=~PAD_DOWN; break;
  case '5': hw.pad&=~PAD_START; break;
  case '0': hw.pad&=~PAD_SELECT; break;
  case '#': hw.pad&=~PAD_A; break;
  case '*': hw.pad&=~PAD_B; break;
  }
}
*/

void onclose(){ // Закрытие окна
  running=0; // Сигнал на остановку фонового процесса
//  loader_unload();
  //if(SGOLD2) 
//  stopped=1;
    if(timedelay) 
      GBS_DelTimer(&timer); // Останавливаем таймер  pickoff!!
//  savelog();  // Сохраняем лог
}

void onexit(){ // Выход
  if (rom.bank) mfree(rom.bank);
  if (ram.sbank) mfree(ram.sbank);
  if(scr) mfree(scr);
  fmapclose(&fmap);
  //  if(buf) mfree(buf); // Освобождаем память
}

void oncreate(){ // Создание окна
  SUBPROC((void *)emu_run); // Запускаем фоновый процесс 
  if(timedelay) 
    GBS_StartTimerProc(&timer,262/3,timer_proc); // Стартуем таймер с частотой 2 раз в секунду
}

extern int gnuboy(char *fname);

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  int i;
  if(!fname || fname[1]!=':') return 1;
  strcpy(filename,exename);
  loadini();
  setemulate();
  if(!(scr=(short*)malloc(160*144*2))) return 2;
  memset(scr,0,160*144*2);
  if(i=gnuboy(strcpy(romname,fname))) return i;
  return 0; //!!!
}

int loadini(){
  int f;
  strcpy(strrchr(filename,'.'),".ini");
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f, param, paramlength, &err);
    fclose(f,&err);
  }
  frameskip=frames=param[pframeskip];
//  if(SGOLD2 && !param[pfrlimit]) param[pfrlimit]=4;
  timedelay=timedelays[param[pfrlimit]];
  keyboard_init();
  return 0;
}

int saveini(){
  int f;
  strcpy(strrchr(filename,'.'),".ini");
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 1;
  param[pframeskip]=(byte)frameskip;
  keyboard_init();
  fwrite(f, param, paramlength, &err);
  fclose(f,&err);
  return 0;
} 

int isFreeRam(char *exename, char *fname){ //1=использ.FreeRam, 0=нет
  return !EL71;//!SGOLD2;
}
