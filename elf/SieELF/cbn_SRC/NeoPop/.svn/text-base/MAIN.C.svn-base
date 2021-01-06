
// NeoPop (c)bn 0.24
// Взято с http://cbn.narod.ru

#include "neopop.h"
#include "..\menu.h"
extern short *screen; // Экран 132*176*2
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();
void on2redraw(void);
extern void savescreen(char *s);
extern int width,height,screensize;

extern unsigned int randseed;
const void *ZEROSTART=&randseed;
const int ZEROSIZE=0x3f000;    

const byte version=0x30;

const char *errors[]={ //Коды ошибок
  0,
  "Запускайте .ngc файлы\0",
  "Не могу открыть файл!\0",
  "Пустой файл\0",
  "Недостаточно памяти\0",
   "Неизвестная ошибка"
};

//int mode=0;
char *Title="NeoGeoPop 0.3";
extern unsigned char SGOLD2, C65, S75, EL71;
_u8 system_frameskip_key=3;//??
char romname[128];
//int key=0;

byte param[paramlength]=
"\x30\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x3D\x3E\x3B\x3C\x2A\x23\x34\x36\x32\x38\x35\x1A\x31\x33\x37\x39"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x04\x08\x01\x02\x10\x20\x04\x08\x01\x02\x10\x20\x40\x80\x10\x20"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x3D\x3E\x3B\x3C\x2A\x23\x34\x36\x32\x38\x35\x1A\x31\x33\x37\x39"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x04\x08\x01\x02\x10\x20\x04\x08\x01\x02\x10\x20\x40\x80\x10\x20"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

char help[]=
" NeoPop 0.3"
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

const char helpkey[]=" 1 start\n2 up\n3 select\n4 left\n5\n6 right\n7 A\n8 down\n9 B";//??



volatile int isredraw=0; // Процесс проверяет флаг и выходит если =0
int color=0;
volatile int timedelay=0;

GBSTMR gtimer;
void timer_proc(void){ // Функция выполняется по таймеру n раз в секунду
  if(isredraw){
    isredraw=0;
    REDRAW(); // Перерисовать экран
  }
  if(timedelay) GBS_StartTimerProc(&gtimer,timedelay,timer_proc); // Стартуем таймер с частотой 10 раз в секунду
}

#include "TLCS900h_interpret.h"
#include "TLCS900h_registers.h"
#include "Z80_interface.h"
#include "interrupt.h"
#include "mem.h"
#include "bios.h"
#include "TLCS900h_interpret_single.h"
#include "TLCS900h_interpret_src.h"
#include "TLCS900h_interpret_dst.h"
#include "TLCS900h_interpret_reg.h"
extern void (*decodeExtra[256])();
extern void (*decode[256])();
extern  _u8		cycles;			//How many state changes?
extern  _u8		cycles_extra;	//How many extra state changes?

const int maxintr=20;//20
/*
void execute(){ // Фоновый процесс
  int intr=0, i=0;
  _u8 *ptr;
  running=1;
  //
  while(running){ // Пока нет команды на останов
  brCode = FALSE;
  ptr = (_u8*)translate_address_read(pc++);	//Get the first byte
  first=ptr?*ptr:0;
	cycles_extra = 0;
	if (decodeExtra[first])
		(*decodeExtra[first])();
	(*decode[first])();	//Decode
	 //updateTimers(cycles + cycles_extra);
   i+=cycles + cycles_extra;
   //printf("\n%d",ram[0x20]);
   
   //if(i>= TIMER_HINT_RATE || (ram[0x20]&0xf)){
     //printf("  OK");
   if (++intr>maxintr){
      if(Z80ACTIVE)
        Z80EMULATE
	    updateTimers(i);
      intr=i=0;
   }
		//updateTimers(TLCS900h_interpret());
  }
}
*/

extern BOOL timer0, timer2;
//int nnn=0;

void execute(){ // Фоновый процесс НОВЫЙ
  int intr=0, i=0;
  _u8 *ptr;
  running=1;
  //
  while(running){ // Пока нет команды на останов
  //	++nnn;
    cycles_extra = brCode = 0;//FALSE;
    //timer0= timer2 =0;

    ptr = (_u8*)translate_address_read(pc++);	//Get the first byte

	if (decodeExtra[first=ptr?*ptr:0])
      (*decodeExtra[first])();
	(*decode[first])();	//Decode

	i+=cycles+cycles_extra;
	if(++intr>20){
	 intr=0;
          if(ram[0xb9] == 0x55){//if(Z80ACTIVE) //ram[0xb9]=0xaa;
	   ExecZ80(&Z80_regs); //  Z80EMULATE
	 }

  	//timer_clock0 += (cycles+=cycles_extra);//НАДО вообще то
	//timer_clock1 += cycles;
//	timer_clock2 += cycles;
	timer_clock3 += i;//cycles;!!!!!!!!!!!!!!!!!!!!

//	 =FALSE;	//Clear the timer2 tick, for timer3 chain mode.
   

	if((timer_hint += i) >= TIMER_HINT_RATE){// || (ram[0x20] & 0xf)){
        updateTimers(i);
	}
	i=0;
	}
   }
}

const int romkey=0x6F82;

void system_VBL(void){ 
//  if(++framenum>frameskip){
//    framenum=0;
    //REDRAW();
    on2redraw();
    if(!timedelay) REDRAW();
//  }
  ram[romkey]=joy;
}

//int cnt=100;
/*
void onredraw2(void){ // Перерисовка экрана
  int i,j;
  short *s=screen, *ss=(short*)cfb+256-62;
  for(j=0;j<176;j++){
    for(i=0;i<128;i++){
      *s++=((*ss&0xf)<<12)|((*ss&0xf0)<<3)|((*ss&0xf00)>>7);
        //((*ss&0xf)<<1)|((*ss&0xf0)<<3)|((*ss&0xf00)<<8);
      //((*ss&0xf)<<12)|((*ss&0xf0)<<3)|((*ss&0xf00)>>15);//
      ss+=2;
    }
    s+=4; 
  }
//  if(++cnt>500){ savescreen("out.bmp"); cnt=0;
//    printf("\nshow");
//  }
}

void onredraw3(void){ // Перерисовка экрана
  int i,j;
  short *s=screen, *ss=(short*)cfb+12;
  for(j=0;j<176;j++){
    for(i=0;i<132;i++){
      *s++=((*ss&0xf)<<12)|((*ss&0xf0)<<3)|((*ss&0xf00)>>7);
        //((*ss&0xf)<<1)|((*ss&0xf0)<<3)|((*ss&0xf00)<<8);
      //((*ss&0xf)<<12)|((*ss&0xf0)<<3)|((*ss&0xf00)>>15);//
      ++ss;
    }
    // *s++=*s++=*s++=*s++=0;
    //s+=4; 
    ss+=124;
  }
}
*/
void onredraw(){// Перерисовка экрана
}

void on2redraw(void){ // Перерисовка экрана
  int j;
  short *s=screen, *ss=(short*)cfb+12;
  for(j=0;j<176;j++){
    movsd(s,ss,64);
    s+=width; ss+=256;
  }
  extern void rgb444to565(short *screen, int screensize);
  rgb444to565(screen,screensize);
  if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));
  isredraw=1;
}

int keyexit(){
  running=0; exit=1; saveini(); 
  return 0;
}

void savename(char c){
  char *s=strrchr(romname,'.');
  *++s='s'; *++s=c; *++s=0;
}

const int JOY_UP=1, JOY_DOWN=1<<1, JOY_LEFT=1<<2, JOY_RIGHT=1<<3, JOY_A=1<<4, JOY_B=1<<5, JOY_START=1<<6, 
  JOY_SELECT=1<<7;

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
//      case '4': mode=4; break; //frmlim
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
      if(keycode>='0' && keycode<='9') param[pframeskip]=system_frameskip_key=keycode-'0';
//            if(keycode>'0' && keycode<='9') system_frameskip_key=keycode-'0';
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


void onclose(){ // Закрытие окна
  running=0; // Сигнал на остановку фонового процесса
  if(timedelay) GBS_DelTimer(&gtimer); // Останавливаем таймер  
  rom_unload();
}

void onexit(){ // Выход
  fmapclose(&fmap);
}

void oncreate(){ // Создание окна
  SUBPROC((void *)execute); // Запускаем фоновый процесс 
  if(timedelay)
    GBS_StartTimerProc(&gtimer,262/3,timer_proc); // Стартуем таймер с частотой 10 раз в секунду
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  int i;
  if(!fname || fname[1]!=':') return 1; // Если не задано имя файла выходим
  strcpy(filename, exename);
  strcpy(romname,fname);
  loadini();
  system_frameskip_key=param[pframeskip];
//
  mute=1;
  system_colour=COLOURMODE_AUTO;
  language_english=1;
  //reset();?? VVV
    if(i=fmapopen(fname,&fmap,5)) return i;
    rom.data=(_u8*)*fmap.mem; //???
  //if(!(rom.data=(_u8*)loadfile(fname))) return 2;
  rom.length=loadfilesize;
  bios_install();
  rom_loaded();
  reset();
  /////rom_unload(); ////addddd!!!!
  if(SGOLD2) timedelay=262/20;
  return 0;
}
 
//////////////Специфика NeoPop/////

//fakes
char* system_get_string(STRINGS string_id){ 
  //printf("\n%d",string_id);
  return 0;}
void __cdecl system_message(char* vaMessage,...){
  //printf("%s",vaMessage);
}
BOOL system_comms_read(_u8* buffer){ return FALSE;}
BOOL system_comms_poll(_u8* buffer){ return FALSE;}
void system_comms_write(_u8 data){}
BOOL system_io_flash_read(_u8* buffer, _u32 bufferLength){ return FALSE;}
BOOL system_io_flash_write(_u8* buffer, _u32 bufferLength){ return FALSE;} //TRUE

BOOL system_io_state_read(char* filename, _u8* buffer, _u32 bufferLength){
  return 0;
}

BOOL system_io_state_write(char* filename, _u8* buffer, _u32 bufferLength){
  return 0;
}

//в интеррупт вставить OADD OSUB!

//int OADD64(_u32 a, _u32 b){  //DELETE!!!!!!!!!!!!!
//  return (a+b) > 0xFFFFFFFF; 
//}

//int OSUB64(_u32 a, _u32 b){
//  return (a-b) > 0xFFFFFFFF;
//}

void __cdecl system_sound_silence(void){}
void __cdecl system_sound_chipreset(void){}

//int isFreeRam(char *exename, char *fname){ //1=использ.FreeRam, 0=нет
//  return !SGOLD2;
//}

