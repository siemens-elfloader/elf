
// GameGear SMS emulator

//#define HIGHCOLOR // 16-битный режим
//#define UNPACK // Распаковк
#include "shared.h"
#include "..\ZFont.h"

#define version 0x35

const char *errors[]={
  0,
  "Нажимать на .gg или .sms\0",
  "Ром не помещается в памяти. Выгрузите мастера и др.эльфы\0",
  "Не хватает 256 кб памяти\0",
  "Не хватает 128 кб памяти\0",
  "Не хватает 100 кб памяти\0",
  "Не хватает 64 кб памяти\0",
};

extern char game_name[PATH_MAX];

extern void savescreen(char *s);

void osd_init(void);
void osd_update_inputs(void);

uint8 (*cpu_readport16)(uint16 port);
int (*cpu_readport)(int port);
void (*cpu_writemem16)(int address, int data);
void (*cpu_writeport16)(uint16 port, uint8 data);
int onquit(); //add

int save_state(char n);
int load_state(char n);

int crc322(int a, int rom, int size){ return 0;} //fake!!!
/*int stricmp(char *s1, char *s2){
  int l1=strlen(s1), l2=strlen(s2);
  if(l1!=l2) return 1;
  while(--l1>=0) if(*s1++!=*s2++) return 1;
  return 0;
}*/

unsigned char *cpu_readmap[64];
unsigned char *cpu_writemap[64];

extern uint32 *bp_lut;
extern uint8 *lut;
//extern uint8 *bg_pattern_cache;

extern unsigned char SGOLD2, C65, S75, EL71;
extern int width, height, screensize;

short *scr=0;//[256*192];
extern short *screen;//[132*176]; // Экран 132*176*2
extern void DrawScreen(); // Функция перерисовки экрана
void onredraw();
void on2redraw(void);
char *Title="GameGear 0.5 (c)bn";
//#define RGB8(R,G,B) (B+(G<<2)+(R<<5))
#define RGB16(R,G,B) ((B>31?31:B)+((G>63?63:G)<<5)+((R>31?31:R)<<11))

volatile int mode=0, timedelay=0, isredraw=0;
const unsigned char timedelays[]={0, 262/5, 262/10, 262/15, 262/20, 262/25};

/* Display timing data */
int frame_skip      = 3;
int frame_count     = 0;
//volatile int frames_rendered = 0;
//volatile int frame_rate      = 0;
//volatile int tick_count      = 0;
//volatile int old_tick_count  = 0;
//volatile int skip            = 0;
//int running                  = 1;
//int state_slot               = 0;
//int snap_count               = 0;
//int use_mouse                = 0;

//volatile int frame_skip=2, frame_count=0;
volatile int running=0, quit=0, loadsave=0;//, process=0; // Процесс проверяет флаг и выходит если =0
char sname;
char filename[120];

typedef unsigned char byte;
#define paramlength 256

//0 64 параметры 
//64 32*3  коды  действия  нажаты
//160 32*3 то же альтерн
byte param[paramlength]=
"\x35\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

"\x3d\x3e\x3b\x3c*#46285\x1a\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x4\x6\x2\x8\x7\x9\x4\x6\x2\x8\x1\x3\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

"\x3d\x3e\x3b\x3c*#46285\x1a\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x4\x6\x2\x8\x7\x9\x4\x6\x2\x8\x1\x3\x00\x00\x00\x00";

enum { pversion, pframeskip, palternate, protate, presize, pslow, pc65, pfrmlimit, poptimize}; //параметры

#define maxkey 32
#define key1 64
#define key2 160

inline void cls(){ memsetd(screen,0,screensize>>2);}
int saveini();
void loadini();
byte *redefineptr;

void  keyboard_init(){
  memset(param+key2-maxkey,0,maxkey);
  memset(param+paramlength-maxkey,0,maxkey);
}

char menu[256]; // Меню
char help[]=
" GameGear 0.5"
"\n1.Load 0-9"
"\n2.Save 0-9"
"\n3.FrmSkp 0-9:%d"
"\n4.FrmLim 0-5:%d"
"\n5.Redefine"
"\n6.Optimize:%d"
"\n7.Rotate"
"\n8.Resize"
"\n9.c65"
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
  sprintf(menu,help,frame_skip,param[pfrmlimit], param[poptimize]);//,buf[stwidth],buf[stheight],buf[speed],buf[free],buf[fill],buf[lorec]|(buf[hirec]<<8));
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
  if(isredraw){
    isredraw=0;
    REDRAW(); // Перерисовать экран
  }
  if(timedelay)
    GBS_StartTimerProc(&timer,timedelay,timer_proc); // Стартуем таймер с частотой 10 раз в секунду
}

void execute(){
exe1:  
  loadsave=0;
  running=1;
  while(running){ // Пока нет команды на останов
    osd_update_inputs();
    if(++frame_count>frame_skip){
       frame_count=0;
       system_frame(0);
       on2redraw();
       if(!timedelay) 
         REDRAW();
    }else 
      system_frame(1);
  }
  switch(loadsave){
  case 1: //load
    load_state(sname);
    goto exe1;
  case 2: //save
    save_state(sname);
    goto exe1;
  }
  system_poweroff();//НАДО = сохраняет память ПЕРЕНЕСЕНО В execute()
  system_shutdown();//НАДО = выкл. все
}

  extern void redraw(short *to, short *from); //обычное
  extern void redraw2(short *to, short *from);//со сжатием
  extern void redraw3(short *to, short *from);//поворот
  extern void redraw4(short *to, short *from);//for EL71
  extern void redraw5(short *to, short *from);//for EL71 крупно
  extern void rotate(void *buf, int dwordsize); //поворот

 void reEL71(){
   short *s, *ss;
   int j;
    if(0){//!param[pslow]){
      if(param[presize]) redraw5(screen,scr);
      else redraw4(screen,scr);
    }else{     
      s=screen+50*240; ss=scr;//+64;
      for(j=0;j<192;j++){
        movsd(s,ss,120);
        //memcpy(s,ss,480);
        s+=240;
        ss+=256;
      }
    }
  }

 void reC65(short *s, short *ss){
   int j,k;
//   s=screen; ss=scr+64;
   for(j=k=0;j<128;j++){
      movsd(s,ss,66);
      s+=width;
      ss+=256;
      if(++k>=3){ k=0; ss+=256;}
   }
 }
 
 void redra3(short *s, short *ss){
   int i,j;
   short *sss=s;
   for(j=0;j<132;j++){
     //sss=s;
     for(i=0;i<176;i++){
       *s=*ss++;
       s+=132;
     }
     ss+=80;
     s=--sss;
   }
 }
 
void onredraw(){ // Перерисовка экрана
  if(param[protate]==2 && !param[pc65]) rotate(screen, screensize);
  if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));
}


//#pragma optimize=???
void on2redraw(void){ // Перерисовка экрана
  if(EL71) reEL71();
  else  if(param[pc65]) reC65(screen, scr+64);
  else{
  if(param[protate]){
    if(param[poptimize])  redraw3(screen+8*132,scr+48+256*20);//redraw3
    else redra3(screen+8*132,scr+48+256*20);//redraw3
//    if(param[protate]==2) rotate(screen, screensize);
  }else{
    if(!param[presize]) redraw2(screen,scr+48+8*256);
    else  redraw(screen,scr+64+8*256);
  }
  }
//  if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));
  isredraw=1;
}

const int UP=1, DOWN=1<<1, LEFT=1<<2, RIGHT=1<<3, BUT_A=1<<4, BUT_B=1<<5, OPT=1<<6;
int key=0;

void keypress(unsigned char keycode, int press){
  byte *ptr=param+((param[palternate])?key2:key1);
  if(ptr=(byte*)strchr((char*)ptr,keycode)) //есть клавиша
    if(press){ 
      key|=ptr[maxkey];
      ptr[maxkey+maxkey]=1;
    }else{
      key&=~ptr[maxkey];
      ptr[maxkey+maxkey]=0;
    }
}

// keycode - код клавиши, pressed - нажата/отпущена/удерживается
int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  byte *ptr;
  switch(pressed){      
  case KEY_UP: if(!mode) keypress(keycode,0); break; // Клавиша отпущена
//  case LONG_PRESS: // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(quit) return 1; //Exit
    if(keycode==RED_BUTTON) return onquit(); //exit
    switch(mode){
    case 100: // main menu
      switch(keycode){
      case '0': return onquit(); // Exit
      case '1': mode=1; break; //load
      case '2': mode=2; break; //save
      case '3': mode=3; break; //frmskip
      case '4': mode=4; break; //frmlim
      case '5': mode=99; break; //redefine
      case '6': param[poptimize]=(param[poptimize]+1)&1; mode=0; break;
      case '7': mode=0; cls(); if(++param[protate]>2) param[protate]=0; break; //rotate
      case '8': mode=0; cls(); param[presize]=~param[presize]; break; //resize
      case '9': mode=0; cls(); param[pc65]=(param[pc65]+1)&1; break; //c65
      default: mode=0; break;
      }break;
    case 1: //load
      if(keycode>='0' && keycode<='9'){
        sname=keycode; loadsave=1; running=0; 
      } mode=0; break;
    case 2: //save
      if(keycode>='0' && keycode<='9'){
        sname=keycode; loadsave=2; running=0; 
      } mode=0; break;
    case 3: //frame_skip
      if(keycode>='0' && keycode<='9') frame_skip=keycode-'0';
      mode=0; break;
    case 4: //frame_limit
      if(keycode>='0' && keycode<='5'){
        if(timedelay=timedelays[param[pfrmlimit]=keycode-'0'])
          GBS_StartTimerProc(&timer,timedelay,timer_proc);
      }
      mode=0; break;
    case 99: //redefine - sel key
     switch(keycode){
      case RIGHT_SOFT:
      case LEFT_SOFT:
      //case GREEN_BUTTON: 
      case RED_BUTTON: mode=0; break;
      default:
      ptr=param+((param[palternate])?key2:key1);
      if(!(redefineptr=(byte*)strchr((char*)ptr,keycode))){ //нет клавиши
        if((redefineptr=ptr+strlen((char*)ptr))<ptr+maxkey) //modify
        *redefineptr=keycode;
      }
       redefineptr+=maxkey;
       mode=98; break;
     } break; 

    case 98: //select key action
      switch(keycode){
      case '1': 
      case '3': *redefineptr=OPT; break;
      case '2': *redefineptr=UP; break;
      case '8': *redefineptr=DOWN; break;
      case '4': *redefineptr=LEFT; break;
      case '6': *redefineptr=RIGHT; break;
      case '7':  *redefineptr=BUT_A; break;
      case '9':  *redefineptr=BUT_B; break;
      } mode=0; break;

    case 0: default:
      switch(keycode){
      case RIGHT_SOFT: mode=100; break; //main menu
      case LEFT_SOFT: param[palternate]=~param[palternate]; break;
      default: keypress(keycode,1);
      }break;
    }
 //   onredraw(); DrawScreen(); // Перерисовать экран
  }
  return 0;
}

int onquit(){
  running=0; // Сигнал на остановку фонового процесса
//  saveini();
  quit=1;
  return 0;
}

void onclose(){ // Закрытие окна
  //перенести ожидание в onexit()
  //if(running){
  running=0; // Сигнал на остановку фонового процесса
  if(timedelay) 
    GBS_DelTimer(&timer); // Останавливаем таймер  pickoff!!
  timedelay=0;//add
  //system_poweroff();//НАДО = сохраняет память ПЕРЕНЕСЕНО В execute()
  //system_shutdown();//НАДО = выкл. все
  saveini();
}

void onexit(){ // Выход
  if(cart.rom) mfree(cart.rom);
  if(bp_lut) mfree(bp_lut);
  if(lut) mfree(lut);
  if(bg_pattern_cache) mfree(bg_pattern_cache);
  if(scr) mfree(scr);
  scr=0;
}

void oncreate(){ // Создание окна
  //execute();  
  SUBPROC((void *)execute); // Запускаем фоновый процесс 
  if(timedelay) 
    GBS_StartTimerProc(&timer,262/3,timer_proc); // Стартуем таймер с частотой 2 раз в секунду
}

int onstart(char *exename, char *fname){ // Старт приложения. Возвращает 0 или 1 для выхода.
  if(!fname || fname[1]!=':') return 1; // Если не задано имя файла выходим
  strcpy(filename,exename);
  if(C65) param[pc65]=1;
  loadini();
  sms.use_fm=0;
  if(!load_rom(fname)) return 2;
  //
  if(!(bp_lut=(uint32*)malloc(0x40000))) return 3;
  if(!(bg_pattern_cache=(uint8*)malloc(0x20000))) return 4;
  if(!(scr=(short*)malloc(256*192*2))) return 5;
  if(!(lut=(uint8*)malloc(0x10000))) return 6;
  memset(bp_lut,0,0x40000);
  memset(bg_pattern_cache,0,0x20000);
  memset(scr,0,256*192*2);
  memset(lut,0,0x10000);
  memset(screen,0,screensize);
  //
  osd_init();
 // snd.sample_rate = 0;
  system_init();
  system_poweron();
//pick_blitter_proc();
  return 0;
}

void osd_init(void){
    //sms_bmp = create_bitmap_ex(option.video_depth, 256, 256);
    //clear(sms_bmp);
    /* Set up bitmap structure */
  sms.use_fm=0;
    memset(&bitmap, 0, sizeof(bitmap_t));
    bitmap.width  = 256;
    bitmap.height = 192;
    bitmap.depth  = 16;
    bitmap.granularity = (bitmap.depth >> 3);
    bitmap.pitch  = bitmap.width * bitmap.granularity;
    bitmap.data   = (uint8 *)scr;
    bitmap.viewport.x = 0;
    bitmap.viewport.y = 0;
    bitmap.viewport.w = 256;
    bitmap.viewport.h = 192;
}

void osd_update_inputs(void){
    /* Reset input states */
    input.system    = 0;
    input.pad[0]    = 0;
    input.pad[1]    = 0;
    input.analog[0] = 0x7F;
    input.analog[1] = 0x7F;

    /* ENTER | SPACE : SMS PAUSE or GG START button */
    if(key&OPT)
        input.system |= (IS_GG) ? INPUT_START : INPUT_PAUSE;

    /* Player #1 inputs */
    if(key&UP)         input.pad[0] |= INPUT_UP;
    else
    if(key&DOWN)       input.pad[0] |= INPUT_DOWN;
    if(key&LEFT)       input.pad[0] |= INPUT_LEFT;
    else
    if(key&RIGHT)      input.pad[0] |= INPUT_RIGHT;
    if(key&BUT_A)          input.pad[0] |= INPUT_BUTTON2;
    if(key&BUT_B)          input.pad[0] |= INPUT_BUTTON1;

//    /* Player #2 inputs */
//    if(key[KEY_8_PAD])      input.pad[1] |= INPUT_UP;
//    else
//    if(key[KEY_2_PAD])      input.pad[1] |= INPUT_DOWN;
//    if(key[KEY_4_PAD])      input.pad[1] |= INPUT_LEFT;
//    else
//    if(key[KEY_6_PAD])      input.pad[1] |= INPUT_RIGHT;
//    if(key[KEY_1_PAD])      input.pad[1] |= INPUT_BUTTON2;
//    if(key[KEY_3_PAD])      input.pad[1] |= INPUT_BUTTON1;
//
//    /* TAB : SMS RESET button */
//    if(key[KEY_TAB])
//        input.system |= INPUT_RESET;
}

//void system_manage_sram(uint8 *sram, int slot, int mode){}
/*--------------------------------------------------------------------------*/

/* Load system state */
int load_state(char n)
{
    int fd;
    char *s=strrchr(game_name,'.');
    *++s='s'; *++s=n; *++s=0;
    if((fd=fopen(game_name,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
    system_load_state(fd);
    fclose(fd, &err);
    return 1;
}

/* Save system state */
int save_state(char n)
{
    int fd;
    char *s=strrchr(game_name,'.');
    *++s='s'; *++s=n; *++s=0;
    if((fd=fopen(game_name,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 0;
    system_save_state(fd);
    fclose(fd, &err);
    return 1;
}

/* Save or load SRAM */
void system_manage_sram(uint8 *sram, int slot, int mode)
{
    int fd;
    strcpy(strrchr(game_name,'.'),".sav");
    switch(mode)
    {
        case SRAM_SAVE:
            if(sms.save)
            {
                if((fd=fopen(game_name,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1)
                {
                    fwrite(fd, sram, 0x8000, &err);
                    fclose(fd, &err);
                }
            }
            break;

        case SRAM_LOAD:
            if((fd=fopen(game_name,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
            {
                sms.save = 1;
                fread(fd, sram, 0x8000, &err);
                fclose(fd, &err);
            }
            else
            {
                /* No SRAM file, so initialize memory */
                memset(sram, 0x00, 0x8000);
            }
            break;
    }
}

void loadini(){
  int f;
  *param=version;
  strcpy(strrchr(filename,'.'),".ini");
  if((f=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
    fread(f, param, 1, &err);
    if(*param!=version) *param=version;
    else fread(f, param+1, paramlength-1, &err);
    fclose(f,&err);
  }
  frame_skip=param[pframeskip];
//  if(SGOLD2 && !param[pfrmlimit]) param[pfrmlimit]=4;
  timedelay=timedelays[param[pfrmlimit]];
  keyboard_init();
}

int saveini(){
  int f;
  strcpy(strrchr(filename,'.'),".ini");
  if((f=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 1;
  param[pframeskip]=(byte)frame_skip;
  keyboard_init();
  fwrite(f, param, paramlength, &err);
  fclose(f,&err);
  return 0;
}
