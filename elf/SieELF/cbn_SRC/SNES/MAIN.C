
// SNES elf
//char sign\unsign переключить!!!???
//call_ctors in asm левый
//sprintf везде снести!!!

#include "snes9x.h"
#include "memmap.h"
#include "debug.h"
#include "cpuexec.h"
#include "ppu.h"
#include "snapshot.h"
#include "apu.h"
#include "display.h"
#include "gfx.h"
#include "soundux.h"

#include "..\menu.h"


extern unsigned int randseed;
const void *ZEROSTART=&randseed; // Начало ZERO сегмента
//const int ZEROSIZE=0x23241;

extern short *screen; // Экран 132*176*2
extern int screensize;
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();

extern unsigned char SGOLD2, C65, EL71;

const byte version=0x2;
char *Title="SNES 0.22 (c)bn";


const char *errors[]={
  0,
  "Запустите .smc файл!\0",
  "Мало памяти! Перезагрузитесь!\0"
  "Мало памяти для графики!\0",
  "Ром не влазит в память!\0",
  "Нет памяти для off_screen\0",//5
  "Нет памяти для sub_screen\0",
  "Нет памяти для Delta\0",
  "Нет памяти для ZBuffer\0" //8
  "Нет памяти для SubZBuffer\0" //9
};

byte param[paramlength]=
"\x02\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
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
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

char help[]=
" SNES 0.22"
"\n1.Load 0-9"
"\n2.Save 0-9"
"\n3.FrmSkp 0-9:%d"
"\n5.Redefine"
"\n7.Rotate"
"\n8.Resize"
"\n0.Exit"
"\ncbn.narod.ru"
"\ncbn@yandex.ru";

void outmenu(const char *help){
  sprintf(menu,help,param[pframeskip]);//,param[pslow]);//,buf[stwidth],buf[stheight],buf[speed],buf[free],buf[fill],buf[lorec]|(buf[hirec]<<8));
}
const char helpkey[]=" 1 start\n2 up\n3 select\n4 left\n5\n6 right\n7 A\n8 down\n9 B\n* X\n# Y";

//char filename[256]; //Здесь путь к рому (НУЖНО!!!)
char romname[128];


void execute(){ // Выполняем basic код
  running=1;
  while(running){ // Пока нет команды на останов
    S9xMainLoop ();
  }
}

extern short pal[256];
extern uint8 *off_screen;

void onredraw(){ // Перерисовка экрана screen[132*176]  //256*224
//  memcpy(screen,sub_screen+132*112,screensize);//неверно т.к. за границей вывода!!!!
  int i,j,k=0;
  short *ss=screen;
  uint8 *s=off_screen;
  if(EL71){
  s+=8;
  for(j=0;j<224;j++){
    for(i=0;i<240;i++){
      *ss++=pal[*s];
      s++;
    }
    s+=(16+2);
  }
  }else{//sgold
  for(j=0;j<176;j++){
    for(i=0;i<128;i++){
      *ss++=pal[*s];
      s+=2;
    }
    ss+=4;
    s+=2;
    if(++k>4){ s+=258; k=0;}
  }
  }
//  char *s=GFX.ZBuffer;
//  return;/////////
/*  int i,j;
  uint8 c;
  short *ss=screen;
  uint8 *s=sub_screen;
  for(j=0;j<176;j++){
    for(i=0;i<128;i++){
      c=(*s)&0xff;
      *ss++=pal[c];        //(p[c].b>>3<<11)|(p[c].g>>2<<5)|(p[c].r>>3);
      s+=2;
    }
    ss+=4;
    s+=260;
  }
*/  //  int i,j;
//  for(i=0,j=color++;i<132*176;i++){
//    screen[i]=j++;
//  }
  if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));
}
/*
// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){      
  case KEY_UP: break; // Клавиша отпущена
  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(key RED_BUTTON: return 1; // Выход
    switch(keycode){ // Код клавиши
    
    case LEFT_SOFT: case RIGHT_BUTTON: case UP_BUTTON: case ENTER_BUTTON: // Делаем что-либо
    case '0': case '9': case '#': case '*':  break; 
    default: return 0;
    }
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

//    onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}
*/
       
int keyexit(){
  running=0; exit=1; saveini(); 
  return 0;
}

void savename(char c){
  char *s=strrchr(romname,'.');
  *++s='s'; *++s=c; *++s=0;
}

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
          //FCEUSS_SaveFP(f);
          fclose(f,&err);
        }
      }
      mode=0; break;
    case 3: //frame_skip
      if(keycode>='0' && keycode<='9') Settings.SkipFrames=param[pframeskip]=keycode-'0';
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
      //  const char helpkey[]=" 1 start\n2 up\n3 select\n4 left\n5\n6 right\n7 A\n8 down\n9 B";
/* #define SNES_TR_MASK	    (1 << 4)
#define SNES_TL_MASK	    (1 << 5)
#define SNES_X_MASK	    (1 << 6)
#define SNES_A_MASK	    (1 << 7)
#define SNES_RIGHT_MASK	    (1 << 8)
#define SNES_LEFT_MASK	    (1 << 9)
#define SNES_DOWN_MASK	    (1 << 10)
#define SNES_UP_MASK	    (1 << 11)
#define SNES_START_MASK	    (1 << 12)
#define SNES_SELECT_MASK    (1 << 13)
#define SNES_Y_MASK	    (1 << 14)
#define SNES_B_MASK	    (1 << 15)*/
      case '1': *redefineptr=12; break;
      case '3': *redefineptr=13; break;
      case '2': *redefineptr=11; break;
      case '8': *redefineptr=10; break;
      case '4': *redefineptr=9; break;
      case '6': *redefineptr=8; break;
      case '7':  *redefineptr=7; break;
      case '9':  *redefineptr=15; break;
      case '*':  *redefineptr=6; break;
      case '#': *redefineptr=14; break;
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

void onclose(){ // Закрытие окна
  running=0; // Сигнал на остановку фонового процесса
//  GBS_StopTimer(&timer); // Останавливаем таймер  pickoff!!
//  savelog();  // Сохраняем лог
}

void onexit(){ // Выход
  FreeRamDebug(filename,"use");
//  if(buf) mfree(buf); // Освобождаем память
}

void oncreate(){ // Создание окна
  SUBPROC((void *)execute); // Запускаем фоновый процесс 
//  GBS_StartTimerProc(&timer,262/2,timer_proc); // Стартуем таймер с частотой 2 раз в секунду
}


//////////
/*
uint32 joypads [5] = {0};
int NumControllers = 2;

#ifdef JOYSTICK_SUPPORT
bool8 joystick_has_four_buttons = FALSE;
bool8 joystick_has_six_buttons = FALSE;
bool8 joystick_has_eight_buttons = FALSE;

#ifdef SIDEWINDER_SUPPORT
void InitSidewinders ();
int ReadSidewinders ();
bool8 alternate_sidewinder_mapping = FALSE;
#endif
void InitJoysticks ();
void ReadJoysticks ();
#endif
*/

extern char *rom_filename;
extern char *snapshot_filename;

int dosmain (char *exename, char *fname);

int onstart(char *exename, char *fname)// (int argc, char **argv)
{
    int i,f;
    if(!fname || fname[1]!=':') return 1;

    strcpy(filename,exename);
    loadini();
    filename[strlen(filename)-1]=0;
    //*filename='9';//diff name

    rom_filename = fname;//S9xParseArgs (argv, argc);

    if((f = fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 1;
    MAX_ROM_SIZE=lseek(f,0,2,&err,&err);
    fclose(f,&err);

    if(i=dosmain(exename, fname)) return i;
  
/*
   if (!Init()){  Deinit (); return 2;}
  //   S9xSetRenderPixelFormat (RGB565);
    
   //if (!S9xInitAPU()){ Deinit(); S9xDeinitAPU (); return 3;}	//OutOfMemory ();
    //uint32 saved_flags = CPU.Flags;

  	if (!LoadROM (rom_filename)) return 4;
   
// НАДО!!!!
 // LoadSRAM (S9xGetSRAMFilename ());//подзагрузка .srm (позже)

    S9xInitInputDevices ();

    if(i=S9xInitDisplay ()) return i;
    if (!S9xGraphicsInit ()) return 3;//	OutOfMemory ();
	
#ifdef JOYSTICK_SUPPORT
    uint32 JoypadSkip = 0;
#endif

    InitTimer ();
*/    
    return 0;
}

#ifdef SIDEWINDER_SUPPORT
int SidewinderToSNES [] =
{
    SNES_UP_MASK, SNES_DOWN_MASK, SNES_RIGHT_MASK, SNES_LEFT_MASK,
    SNES_B_MASK, SNES_A_MASK, SNES_A_MASK, 
    SNES_Y_MASK, SNES_X_MASK, SNES_B_MASK, 
    SNES_TL_MASK, SNES_TR_MASK,
    SNES_START_MASK, SNES_SELECT_MASK
};

int SidewinderToSNES2 [] =
{
    SNES_UP_MASK, SNES_DOWN_MASK, SNES_RIGHT_MASK, SNES_LEFT_MASK,
    SNES_A_MASK, SNES_B_MASK, SNES_A_MASK, 
    SNES_X_MASK, SNES_Y_MASK, SNES_B_MASK, 
    SNES_TL_MASK, SNES_TR_MASK,
    SNES_START_MASK, SNES_SELECT_MASK
};
#endif

////////////////
/*
uint32 S9xReadJoypad (int which1)
{
#ifdef NETPLAY_SUPPORT
//    if (Settings.NetPlay)
//	return (S9xNetPlayGetJoypad (which1));
#endif
    if (which1 < NumControllers)
	return (0x80000000 | joypads [which1]);
    return (0);
}

void S9xExit ()
{
    S9xDeinitDisplay ();
    SaveSRAM (S9xGetSRAMFilename ());
    Deinit ();
    S9xDeinitAPU ();

#ifdef NETPLAY_SUPPORT
    if (Settings.NetPlay)
	S9xNetPlayDisconnect ();
#endif
    
//    exit (0);
}
*/
