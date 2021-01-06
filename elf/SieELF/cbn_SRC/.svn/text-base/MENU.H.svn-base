
#ifndef SEGA 
#ifndef SNES
#include "Swilib.h"
#endif
typedef unsigned char byte;
#endif
#include "ZFont.h"

//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))


extern unsigned char SGOLD2, C65, S75, EL71;
extern int width, height, screensize;
#ifdef HIGHCOLOR
extern short *screen;
#else
extern char *screen;
#endif
/*
char *Title="NES 0.65 (c)bn";
const char *errors[]={
  0,
  "Щелкните на .nes файл",
  "Не хватает 0x80000 памяти",
  "Не хватает 0x40000 памяти",
  "Ошибка инициализации",
  "Ошибка загрузки рома"
};*/

int mode=0;
volatile int running=0, exit=0;

char filename[128], *file;
#define paramlength 256
extern const byte version;
//0 64 параметры 
//64 32*3  коды  действия  нажаты
//160 32*3 то же альтерн
extern byte param[paramlength];
/*
"\x64\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x3D\x3E\x3B\x3C\x2A\x23\x34\x36\x32\x38\x35\x1A\x31\x33\x37\x39"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x40\x80\x10\x20\x10\x20\x40\x80\x10\x20\x08\x01\x08\x04\x01\x02"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x3D\x3E\x3B\x3C\x2A\x23\x34\x36\x32\x38\x35\x1A\x31\x33\x37\x39"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x40\x80\x10\x20\x10\x20\x40\x80\x10\x20\x08\x01\x08\x04\x01\x02"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
*/
enum{ pversion, pframeskip, palternate, protate, presize, pfrlimit}; //параметры

#define maxkey 32
#define key1 64
#define key2 160

inline void cls(){ memsetd(screen,0,screensize>>2);}
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
extern char help[];
/*
" NES 0.65 (c)bn"
"\n1.Load 0-9"
"\n2.Save 0-9"
"\n3.FrmSkp 0-9:%d"
"\n5.Redefine"
"\n7.Rotate"
"\n8.Resize"
"\n0.Exit"
"\ncbn.narod.ru"
"\ncbn@yandex.ru";
*/
extern void outmenu(const char *help);//{
//  sprintf(menu,help,param[pframeskip]);//,param[pslow]);//,buf[stwidth],buf[stheight],buf[speed],buf[free],buf[fill],buf[lorec]|(buf[hirec]<<8));
//}
//вставить в onredraw():
//if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));

//вставить в onstart():
//strcpy(filename, exename);
//  loadini();

extern const char helpkey[];//=" 1 start\n2 up\n3 select\n4 left\n5\n6 right\n7 A\n8 down\n9 B";
const char helpsel[]=" Select key";

void drawsym(
#ifdef HIGHCOLOR
  short 
#else
  byte
#endif    
  *out, char c){ // Отобразить символ на экране
  int i,j;
  unsigned char b, *bptr=(unsigned char*)zfont+((c-=0x20)<=0?0:(c<<3));
  for(j=0;j<8;j++){
    b=*bptr++;
    for(i=0;i<8;i++){
      *out++=(b&0x80)
#ifdef HIGHCOLOR        
        ?0xffff:0x1f; //colors 0xffff
#else
        ?0xff:0x3; //colors 0xffff
#endif        
      b<<=1;
    }
    out+=width-8;
  }
}

void drawhelp(const char *help){ // Показать меню
  int i=0,x=0,y=0;
  outmenu(help);
  while(menu[i]){
    if(menu[i]=='\n' || x>=width/8){ x=0; ++y;}
    if(y>=height/10) break;
    drawsym(screen+y*width*10+x*8+4,menu[i]);
    ++x;
    ++i;
  }
}

int loadini(){
  int f;
  *param=version;
  strcpy(strrchr(filename,'.'),".ini");
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f, param, 1, &err);
    if(*param!=version) *param=version;
    else fread(f, param+1, paramlength-1, &err);
    fclose(f,&err);
  }
//  frameskip=frames=param[pframeskip];
//  timedelay=timedelays[param[pfrlimit]];
  keyboard_init();
  return 0;
}

int saveini(){
  int f;
  strcpy(strrchr(filename,'.'),".ini");
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 1;
//  param[pframeskip]=(byte)frameskip;
  keyboard_init();
  fwrite(f, param, paramlength, &err);
  fclose(f,&err);
  return 0;
}

int isFreeRam(char *exename, char *fname){ //1=использ.FreeRam, 0=нет
  return !EL71;//!SGOLD2;
} 

#ifdef SEGA
int inputpad=0;
#include "sega\system.h"
#define joy input.pad[0]

#elif vNES
#define joy k_int_static_fld
extern int k_int_static_fld; //joy from vNES
extern char l_boolean_static_fld;
extern char j_boolean_static_fld;
#define JOY_AA 0xff    
#define JOY_BB 0xfe
//    if(i1 == key[8])  l_boolean_static_fld = true;
//    if(i1 == key[9])  j_boolean_static_fld = true;
#elif SNES
extern unsigned joypads[5];
#define joy joypads[0]
#else
int joy=0;
#endif

void keypress(unsigned char keycode, int press){
  byte *ptr=param+(param[palternate]?key2:key1);
  if(ptr=(byte*)strchr((char*)ptr,keycode)) //есть клавиша
#ifdef vNES
  if(ptr[maxkey]==JOY_AA) l_boolean_static_fld=press;
  else if(ptr[maxkey]==JOY_BB) j_boolean_static_fld=press;
  else
#endif    
#ifdef SNES
    if(press){ 
      joy|=(1<<ptr[maxkey]);
      ptr[maxkey+maxkey]=1;
    }else{
      joy&=~(1<<ptr[maxkey]);
      ptr[maxkey+maxkey]=0;
    }
#elif SEGA
    if(press){ 
      joy|=(1<<ptr[maxkey]);
      ptr[maxkey+maxkey]=1;
    }else{
      joy&=~(1<<ptr[maxkey]);
      ptr[maxkey+maxkey]=0;
    }
#else
    if(press){ 
      joy|=ptr[maxkey];
      ptr[maxkey+maxkey]=1;
    }else{
      joy&=~ptr[maxkey];
      ptr[maxkey+maxkey]=0;
    }
#endif  
}

//int keyexit(){
//  running=0; exit=1; saveini(); return 0;
//}

//void savename(char c){
//  char *s=strrchr(romname,'.');
//  *++s='s'; *++s=c; *++s=0;
//}
/*
// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  byte *ptr;
  int f;
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
      case '7': mode=0; cls(); if(++param[protate]>2) param[protate]=0; break; //rotate
      case '8': mode=0; cls(); param[presize]=~param[presize]; break; //resize
//      case '9': param[pslow]=(param[pslow]+1)&1; break; //slow
      default: mode=0; break;
      }break;
    case 1: //load
      if(keycode>='0' && keycode<='9'){ 
        savename(keycode);
        if((f=fopen(romname,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
          //FCEUSS_LoadFP(f);
          fclose(f,&err);
        }
      }
      mode=0; break;
    case 2: //save
      if(keycode>='0' && keycode<='9'){
        savename(keycode);
        if((f=fopen(romname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
          FCEUSS_SaveFP(f);
          fclose(f,&err);
        }
      }
      mode=0; break;
    case 3: //frame_skip
      if(keycode>='0' && keycode<='9') param[pframeskip]=keycode-'0';
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
      case '1': *redefineptr=JOY_START; break;
      case '3': *redefineptr=JOY_SELECT; break;
      case '2': *redefineptr=JOY_UP; break;
      case '8': *redefineptr=JOY_DOWN; break;
      case '4': *redefineptr=JOY_LEFT; break;
      case '6': *redefineptr=JOY_RIGHT; break;
      case '7':  *redefineptr=JOY_A; break;
      case '9':  *redefineptr=JOY_B; break;
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
*/
