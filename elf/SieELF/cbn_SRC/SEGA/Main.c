
/*
    dos.c --
    DOS interface code for the emulator
*/
//#define HIGHCOLOR // 16-битный режим
//#define UNPACK // Распаковка архивов //пока без нее

//SEGA emulator (main)
//menu.h modified!

typedef unsigned char byte;

extern unsigned int randseed;
const void *ZEROSTART=&randseed; 
const int ZEROSIZE=0x1d42d;

#include "osd.h"
#include "m68kops.h"
#include "..\menu.h"

const byte version=0x32;
char *Title="SEGA 0.55 (c)bn";

extern unsigned char *lut_base;
extern int width,height;
extern unsigned char *bg_pattern_cache;//[0x80000];

//volatile int running=0;
int c65=0;
int flags=0;

#define fload 1
#define fsave 2

extern short *screen;//[132*176];
extern int screensize;
short *scr=0;//[256*224];
extern unsigned char EL71, C65;

byte param[paramlength]=
"\x32\x03\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x3D\x3E\x3B\x3C\x2A\x23\x34\x36\x32\x38\x35\x1A\x31\x33\x37\x39"
"\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x02\x03\x00\x01\x08\x10\x02\x03\x00\x05\x01\x04\x80\x04\x04\x06"
"\x09\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x3D\x3E\x3B\x3C\x2A\x23\x34\x36\x32\x38\x35\x1A\x31\x33\x37\x39"
"\x30\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x02\x03\x00\x01\x08\x10\x02\x03\x00\x05\x01\x04\x80\x04\x04\x06"
"\x09\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

//enum{ pversion, pframeskip, palternate, protate, presize, pfrlimit}; //параметры

const char *errors[]={
  0,
  "Выберите .BIN файл\0",
  "Нехватка 0x80000 памяти\0",
  "Нехватка 0x60000 памяти\0",
  "Нехватка 0x40000 памяти\0",
  "Нехватка 0x30000 памяти\0",    
  "Нехватка 0x20000 памяти\0",
  "Нехватка 0x10000 памяти\0",
  "Не .bin файл! Используйте конвертер Smd2bin\0", //8
  "Нажмите еще раз!\0",
  "Файл пустой\0",
  "Нет памяти для карты рома\0"
};

char romname[256];

char help[]=
"  SEGA 0.55"
"\n1.Load 0-9"
"\n2.Save 0-9"
"\n3.FrmSkp:%d"
"\n5.Redefine"
"\n7.Rotate"
"\n8.Resize"
"\n0.Exit"
"\ncbn.narod.ru"
"\ncbn@yandex.ru";

/*
GBSTMR timer;
void timer_proc(void){ // Функция выполняется по таймеру 10 раз в секунду
  if(running){
    GBS_StartTimerProc(&timer,262/10,timer_proc); // Стартуем таймер с частотой 10 раз в секунду
  } // Он выполняется однократно поэтому его нужно постоянно запускать
}
*/

void outmenu(const char *help){
  sprintf(menu,help,param[pframeskip]);//,param[pslow]);//,buf[stwidth],buf[stheight],buf[speed],buf[free],buf[fill],buf[lorec]|(buf[hirec]<<8));
}
//вставить в onredraw():
//if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));

//вставить в onstart():
//strcpy(filename, exename);
//  loadini();

//const char helpkey[]=" 1 start\n2 up\n3 \n4 left\n5 C\n6 right\n7 A\n8 down\n9 B";
const char helpkey[]=" 1 Start\n2 Up\n3 Mode\n4 Left\n5 Down\n6 Right\n7 A\n8 B\n9 C\n* X\n0 Y\n# Z";

#define FRAMES_PER_SECOND   60

struct RGB{
  unsigned char r,g,b;
} vdp_palette[3][0x200];
//PALETTE gen_pal;
struct PALST gen_pal[0x100];//add

//BITMAP *gen_bmp;

volatile int frame_skip      = 11;//16
volatile int frame_count     = 0;
volatile int frames_rendered = 0;
volatile int frame_rate      = 0;
volatile int tick_count      = 0;
volatile int old_tick_count  = 0;

int quit = 0;

int keyexit(){
  running=0; exit=1; saveini(); return 0;
}

#define _INPUT_MODE       (0x0000011)
#define _INPUT_Z         (0x0000010)
#define _INPUT_Y         (0x000009)
#define _INPUT_X         (0x000008)
#define _INPUT_START     (0x0000007)
#define _INPUT_C         (0x0000006)
#define _INPUT_B         (0x0000005)
#define _INPUT_A         (0x0000004)
#define _INPUT_LEFT      (0x00000003)
#define _INPUT_RIGHT     (0x00000002)
#define _INPUT_DOWN      (0x00000001)
#define _INPUT_UP        (0x0000000)

extern int state_save(int file);
extern int state_load(int file);

void loadgame(){
  int f;
        if((f=fopen(romname,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
          state_load(f);
          fclose(f,&err);
        }
}

void savegame(){
  int f;
        if((f=fopen(romname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
          state_save(f);
          fclose(f,&err);
        }
}
//extern void savescreen(char *fname);
//int tmpint=0;

void savename(char c){
  char *s=strrchr(romname,'.');
  *++s='s'; *++s=c; *++s=0;
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
      case '3': mode=31; break; //frmskip
//      case '4': mode=4; break; //frmlim
      case '5': mode=99; break; //redefine
      case '7': mode=0; cls(); if(++param[protate]>2) param[protate]=0; 
        memsetd(screen,0,screensize>>2);  break; //rotate
      case '8': mode=0; cls(); param[presize]=~param[presize]; 
        memsetd(screen,0,screensize>>2);  break; //resize
//      case '9': param[pslow]=(param[pslow]+1)&1; break; //slow
      default: mode=0; break;
      }break;
    case 1: //load
      if(keycode>='0' && keycode<='9'){ 
        savename(keycode); flags|=fload; running=0;
      } mode=0; break;
    case 2: //save
      if(keycode>='0' && keycode<='9'){
        savename(keycode); flags|=fsave; running=0;
      } mode=0; break;
//    case 31: //frame_skip1
//       if(keycode>='0' && keycode<='9'){ mode=32; tmpint=keycode-'0';}
//       else mode=0;  break;
    case 31: //frame_skip2
      if(keycode>='0' && keycode<='9') frame_skip=param[pframeskip]=keycode-'0';
       mode=0;  break;
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
        //const char helpkey[]=" 1 Start\n2 Up\n4 Left\n5 Down\n6 Right\n7 A\n8 B\n9 C\n* X\n0 Y\n# Z";
      case '1': *redefineptr=_INPUT_START; break;
      case '3': *redefineptr=_INPUT_MODE; break;
      case '2': *redefineptr=_INPUT_UP; break;
      case '5': *redefineptr=_INPUT_DOWN; break;

      case '4': *redefineptr=_INPUT_RIGHT; break;
      case '6': *redefineptr=_INPUT_LEFT; break;//LEFT & RIGHT перепутаны!!!!!
      
      case '7':  *redefineptr=_INPUT_A; break;
      case '8':  *redefineptr=_INPUT_B; break;
      case '9':  *redefineptr=_INPUT_C; break;
      case '*':  *redefineptr=_INPUT_X; break;
      case '0':  *redefineptr=_INPUT_Y; break;
      case '#':  *redefineptr=_INPUT_Z; break;
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

extern void segasc(void *to, void *from, int size);
extern void segarot(void *to, void *from, int size);
extern void rotate(void *buf, int dbufsize);

void onredraw(){ // Перерисовке экрана
  int j,k=0;
  short *s=screen, *ss=scr+((reg[12]&1)?64:32);
  if(EL71){ //EL71
  for(j=0;j<223;j++){
    movsd(s,ss,120);
    s+=240; ss+=320;
  }  
 }else
   if(param[protate]){ // Поворот
    s=screen+8*132+128; ss-=32;
    for(j=0;j<120;j++){
      segarot(--s,ss,160);
      ss+=640;
    }
    if(param[protate]>1) rotate(screen,screensize);
   }else{ //без поворота
   if(param[presize]){ //c65
  for(j=0;j<120;j++){
    segasc(s,ss,132);
    s+=132;
    ss+=640;
  }
  }else{   //132*176
  for(j=0;j<176;j++){
    segasc(s,ss,132);
    s+=132;
    ss+=320;
    if(++k>=4){ ss+=320; k=0;}
  }
  }
   }
if(mode) drawhelp(mode==99?helpsel:(mode==98?helpkey:help));
}


void on2redraw(void){ // Перерисовке экрана
//  if(++cnt>200){
//     cnt=0;
    //if(bitmap.remap == 0) 
    //   dos_update_palette();
//     makescreen();
  //   printf("show ");
  //   savescreen("out.bmp");
//  }
}

void onclose(){ // Закрытии окна
  running=0;
//  GBS_DelTimer(&timer); // Останавливаем таймер  pickoff!!  
}

void onexit(){ // Выходе
  if(lut_base) mfree(lut_base);
  if(bg_pattern_cache) mfree(bg_pattern_cache);
  if(cart_rom) mfree(cart_rom);
  if(work_ram) mfree(work_ram);
  if(scr) mfree(scr);
  //
  if(m68ki_cycles) mfree(m68ki_cycles);
  if(m68ki_instruction_jump_table) mfree(m68ki_instruction_jump_table);
  //
  fmapclose(&fmap);
}


////////////
#include "m68kops.h"
#include "m68kcpu.h"
extern int  m68ki_initial_cycles;

//ОПТИМИЗИРОВАНО (глючно???)
inline int m68k_inline_execute(int num_cycles)//inline copy of m68k_execute 
{
	/* Make sure we're not stopped */
	if(!CPU_STOPPED)
	{
		/* Set our pool of clock cycles available */
		SET_CYCLES(num_cycles);
		m68ki_initial_cycles = num_cycles;

		/* ASG: update cycles */
		USE_CYCLES(CPU_INT_CYCLES);
		CPU_INT_CYCLES = 0;

		/* Return point if we had an address error */
		m68ki_set_address_error_trap(); /* auto-disable (see m68kcpu.h) */

		/* Main loop.  Keep going until we run out of clock cycles */
		m68ki_cpu.ppc=m68ki_cpu.pc;

		do{
			m68ki_instruction_jump_table[m68ki_cpu.ir= m68ki_read_imm_16()]();
		} while((m68ki_remaining_cycles-=16)>=0);
                        //(m68ki_remaining_cycles-= m68ki_cpu.cyc_instruction[m68ki_cpu.ir]) > 0);

		/* set previous PC to current PC for the next entry into the loop */
		REG_PPC = REG_PC;

		/* ASG: update cycles */
		USE_CYCLES(CPU_INT_CYCLES);
		CPU_INT_CYCLES = 0;

		/* return how many clocks we used */
		return m68ki_initial_cycles - GET_CYCLES();
	}

	/* We get here if the CPU is stopped or halted */
	SET_CYCLES(0);
	CPU_INT_CYCLES = 0;

	return num_cycles;
}

int line; 

void execute(){ 
    system_init();
    system_reset();
do{    
exe1:
  flags=0;
  running=1;
    while(running)
    {
    //input.pad[0]=inputpad;  
    status &= ~0x0008;
    if(im2_flag)
        status ^= 0x0010;
    parse_satb(0x80);

    for(line = 0; line < 262; line ++){
        v_counter = line;
        m68k_inline_execute(487);//487
        if(zirq == 1)  zirq = 0;
        if(!frame_count){
          if(line <  frame_end   ) render_line(line);
          if(line <  frame_end-1 ) parse_satb(0x81 + line);
        }
        if(line > frame_end) counter = reg[10];
        else{
            if((--counter) == -1){
                counter = reg[10];
                hint_pending = 1;
                if(reg[0] & 0x10)  m68k_set_irq(4);
            }
        if(line == frame_end){
            status |= 0x0088;
            vint_pending = 1;
            m68k_inline_execute(16);
            if(reg[1] & 0x20) m68k_set_irq(6); 
            if(zreset == 1 && zbusreq == 0)  zirq = 1;
        }
        }
    }
        if(!frame_count) REDRAW(); //или dos_update_video();
        if(++frame_count>=frame_skip) frame_count=0;
    }
    if(flags & fload){
      loadgame();
      goto exe1;
    }
    if(flags & fsave){
      savegame();
      goto exe1;
    }
}while(0);

    trash_machine();
    system_shutdown();
    error_shutdown();
}



/*до оптимизации!!!
void execute(){ 
    system_init();
    system_reset();
    running=1;
    while(running)
    {
//        frame_count += 1;
//        //if(quit) break;
      input.pad[0]=inputpad;
//        dos_update_input();
//        if((frame_count % frame_skip) == 0)
        if(++frame_count>frame_skip)
        {
            frame_count=0;
            system_frame(0);
            dos_update_video();
        }
        else
        {
            system_frame(1);
        }
        if(option.sound) dos_update_audio();
    }

    trash_machine();
    system_shutdown();
    error_shutdown();
}
*/

void oncreate(){ // Создании окна
  SUBPROC((void*)execute);
//  GBS_StartTimerProc(&timer,262/2,timer_proc); // Стартуем таймер с частотой 2 раз в секунду
}

int onstart(char *exename, char *fname)
{
    int i;
    if(C65) c65=1;
    if(!fname || fname[1]!=':') return 1;
    strcpy(romname,fname);
    if(!(bg_pattern_cache = (unsigned char*)malloc(0x80000))) return 2;
    if(!(lut_base = (unsigned char*)malloc((LUT_MAX * LUT_SIZE) + LUT_SIZE))) return 3; //0x60000
    if(!(m68ki_instruction_jump_table=malloc(0x40000))) return 4;
    if(!(m68ki_cycles=(unsigned char(*)[0x10000])malloc(0x30000))) return 5;
    if(!(scr = (short*)malloc(320*240*2))) return 6;//256*224*2
    if(!(work_ram = (unsigned char*)malloc(0x10000))) return 7;
 
    memset(bg_pattern_cache, 0, 0x80000);
    memset(lut_base, 0,(LUT_MAX * LUT_SIZE) + LUT_SIZE);
    memset(m68ki_instruction_jump_table,0,0x40000);
    memset(m68ki_cycles,0,0x30000);
    memset(scr, 0, 320*240*2);//256*224*2);
    memset(work_ram, 0, 0x10000);

    strcpy(filename,exename);
    loadini();
    frame_skip=param[pframeskip];
    if(i=load_rom(fname)) return i+7;

    init_machine();

    error_init();

//    FreeRamDebug(exename, "use");////add    
    
//    if(option.sound)
//    {
//        audio_init(option.sndrate);
//    }
/////////////to create
    return (0);
}

/* Timer handler */
void tick_handler(void)
{
    tick_count += 1;
    if(tick_count % FRAMES_PER_SECOND == 0)
    {
        frame_rate = frames_rendered;
        frames_rendered = 0;
    }
}
//END_OF_FUNCTION(tick_handler);


int load_file(char *filename, char *buf, int size)
{
    int fd;
    if((fd=fopen(filename,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 0;
    fread(fd, buf, size, &err);
    fclose(fd,&err);
    return (1);
}

int save_file(char *filename, char *buf, int size)
{
    int fd;
    if((fd=fopen(filename,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==-1) return 0;
    fwrite(fd, buf, size, &err);
    fclose(fd, &err);
    return (1);
}


void dos_update_input(void)
{/*
    if(key[KEY_ESC] || key[KEY_END])
    {
        quit = 1;
    }

    input.pad[0] = 0;

    // Is the joystick being used ? 
    if(option.joy_driver != JOY_TYPE_NONE)
    {
        poll_joystick();

        // Check player 1 joystick 
        if(joy[0].stick[0].axis[1].d1) input.pad[0] |= INPUT_UP;
        else
        if(joy[0].stick[0].axis[1].d2) input.pad[0] |= INPUT_DOWN;

        if(joy[0].stick[0].axis[0].d1) input.pad[0] |= INPUT_LEFT;
        else
        if(joy[0].stick[0].axis[0].d2) input.pad[0] |= INPUT_RIGHT;

        if(joy[0].button[0].b)  input.pad[0] |= INPUT_A;
        if(joy[0].button[1].b)  input.pad[0] |= INPUT_B;
        if(joy[0].button[2].b)  input.pad[0] |= INPUT_C;
        if(joy[0].button[3].b)  input.pad[0] |= INPUT_START;
        if(joy[0].button[4].b)  input.pad[0] |= INPUT_X;
        if(joy[0].button[5].b)  input.pad[0] |= INPUT_Y;
        if(joy[0].button[6].b)  input.pad[0] |= INPUT_Z;
        if(joy[0].button[7].b)  input.pad[0] |= INPUT_MODE;

        // More than one joystick supported ? 
        if(num_joysticks > 2)
        {
            // Check player 2 joystick 
            if(joy[1].stick[0].axis[1].d1) input.pad[1] |= INPUT_UP;
            else
            if(joy[1].stick[0].axis[1].d2) input.pad[1] |= INPUT_DOWN;

            if(joy[1].stick[0].axis[0].d1) input.pad[1] |= INPUT_LEFT;
            else
            if(joy[1].stick[0].axis[0].d1) input.pad[1] |= INPUT_RIGHT;

            if(joy[1].button[0].b)  input.pad[1] |= INPUT_A;
            if(joy[1].button[1].b)  input.pad[1] |= INPUT_B;
            if(joy[1].button[2].b)  input.pad[1] |= INPUT_C;
            if(joy[1].button[3].b)  input.pad[1] |= INPUT_START;
            if(joy[1].button[4].b)  input.pad[1] |= INPUT_X;
            if(joy[1].button[5].b)  input.pad[1] |= INPUT_Y;
            if(joy[1].button[6].b)  input.pad[1] |= INPUT_Z;
            if(joy[1].button[7].b)  input.pad[1] |= INPUT_MODE;
        }
    }

    if(key[KEY_UP])     input.pad[0] |= INPUT_UP;
    else
    if(key[KEY_DOWN])   input.pad[0] |= INPUT_DOWN;
    if(key[KEY_LEFT])   input.pad[0] |= INPUT_LEFT;
    else
    if(key[KEY_RIGHT])  input.pad[0] |= INPUT_RIGHT;

    if(key[KEY_A])      input.pad[0] |= INPUT_A;
    if(key[KEY_S])      input.pad[0] |= INPUT_B;
    if(key[KEY_D])      input.pad[0] |= INPUT_C;
    if(key[KEY_F])      input.pad[0] |= INPUT_START;
    if(key[KEY_Z])      input.pad[0] |= INPUT_X;
    if(key[KEY_X])      input.pad[0] |= INPUT_Y;
    if(key[KEY_C])      input.pad[0] |= INPUT_Z;
    if(key[KEY_V])      input.pad[0] |= INPUT_MODE;

    if(check_key(KEY_TAB))
        system_reset();

    if(check_key(KEY_F1)) frame_skip = 1;
    if(check_key(KEY_F2)) frame_skip = 2;
    if(check_key(KEY_F3)) frame_skip = 3;
    if(check_key(KEY_F4)) frame_skip = 4;
    */
}

void dos_update_audio(void)
{
    //osd_play_streamed_sample_16(option.swap ^ 0, snd.buffer[0], snd.buffer_size * 2, option.sndrate, FRAMES_PER_SECOND, -100);
    //osd_play_streamed_sample_16(option.swap ^ 1, snd.buffer[1], snd.buffer_size * 2, option.sndrate, FRAMES_PER_SECOND,  100);
}

void dos2_update_palette(void)
{/*
    if(is_border_dirty)
    {
        uint16 data = *(uint16 *)&cram[(border << 1)];
        RGB *color;

        is_border_dirty = 0;

        if(reg[12] & 8)
        {
            int j;
            for(j = 0; j < 3; j += 1)
            {
                color = &vdp_palette[j][data];
//                set_color((j << 6), color);
            }
        }
        else
        {
            color = &vdp_palette[1][data];
    //        set_color(0x00, color);
    //        set_color(0x40, color);
    //        set_color(0x80, color);
        }
    }

    if(is_color_dirty)
    {
        int i;
        uint16 *p = (uint16 *)&cram[0];
        is_color_dirty = 0;

        for(i = 0; i < 64; i += 1)
        {
            if((color_dirty[i]) && ((i & 0x0F) != 0x00))
            {
                RGB *color;
                color_dirty[i] = 0;
                if(reg[12] & 8)
                {
                    int j;
                    for(j = 0; j < 3; j += 1)
                    {
                        color = &vdp_palette[j][p[i]];
//                        set_color((j << 6) | i, color);
                    }
                }
                else
                {
                    color = &vdp_palette[1][p[i]];
//                    set_color(0x00 | i, color);
 //                   set_color(0x40 | i, color);
  //                  set_color(0x80 | i, color);
                }
            }
        }
    }*/
}

void dos_update_video(void)
{
    REDRAW();
/*
    int width = (reg[12] & 1) ? 320 : 256;
    int height = (reg[1] & 8) ? 240 : 224;
    int center_x = (SCREEN_W - width) / 2;
    int center_y = (SCREEN_H / (option.scanlines ? 4 : 2)) - (height / 2);

    // Wait for VSync 
    if(option.vsync) vsync();

    if(bitmap.viewport.changed)
    {
        bitmap.viewport.changed = 0;
        if(bitmap.remap)
        {
            clear(screen);
        }
        else
        {
            clear_to_color(screen, 0xFF);
        }
    }

    if(bitmap.remap == 0)
    {
        dos_update_palette();
    }


    if(option.scanlines)
    {
        int y;
        for(y = 0; y < height; y += 1)
        {
            blit(gen_bmp, screen, 0x20, y, center_x, (center_y + y) << 1, width, 1);
        }
    }
    else
    {

        blit(gen_bmp, screen, 0x20, 0, center_x, center_y, width, height);
    }*/
}

void init2_machine(void)
{
  /*
    do_config("gen.cfg");

    if(option.sound)
    {
        msdos_init_sound(&option.sndrate, option.sndcard);
    }

    allegro_init();
    install_keyboard();
    install_joystick(option.joy_driver);

    install_timer();
    LOCK_FUNCTION(tick_handler);
    LOCK_VARIABLE(tick_count);
    LOCK_VARIABLE(frame_rate);
    install_int_ex(tick_handler, BPS_TO_TIMER(FRAMES_PER_SECOND));

    set_color_depth(option.video_depth);
    gen_bmp = create_bitmap(512, 512);
    clear(gen_bmp);

    memset(&bitmap, 0, sizeof(bitmap));
    bitmap.data = (uint8 *)&gen_bmp->line[0][0];
    bitmap.width = gen_bmp->w;
    bitmap.height = gen_bmp->h;
    bitmap.depth = option.video_depth;
    switch(option.video_depth)
    {
        case 8:
            bitmap.granularity = 1;
            break;
        case 15:
            bitmap.granularity = 2;
            break;
        case 16:
            bitmap.granularity = 2;
            break;
        case 32:
            bitmap.granularity = 4;
            break;
    }
    bitmap.pitch = (bitmap.width * bitmap.granularity);
    bitmap.viewport.w = 256;
    bitmap.viewport.h = 224;
    bitmap.viewport.x = 0x20;
    bitmap.viewport.y = 0x00;
    bitmap.remap = 0;
    if(option.remap) bitmap.remap = 1;
    else
    if(bitmap.depth > 8) bitmap.remap = 1;

    make_vdp_palette();

    memcpy(gen_pal, black_palette, sizeof(PALETTE));
    gen_pal[0xFE].r = \
    gen_pal[0xFE].g = \
    gen_pal[0xFE].b = 0x3F;

    dos_change_mode();
    */
}

void trash_machine(void)
{
    if(option.sound)
    {
        //msdos_shutdown_sound();
    }
//    clear(screen);
//    destroy_bitmap(gen_bmp);
 //   set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
}

void make_vdp_palette(void)
{
    uint8 lut[3][8] =
    {
        {0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C},
        {0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38},
        {0x20, 0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C},
    };

    int j;
    for(j = 0; j < 0x600; j += 1)
    {

        int r = (j >> 6) & 7;
        int g = (j >> 3) & 7;
        int b = (j >> 0) & 7;
        int i = (j >> 9) & 3;

        vdp_palette[i][j & 0x1FF].r = lut[i][r];
        vdp_palette[i][j & 0x1FF].g = lut[i][g];
        vdp_palette[i][j & 0x1FF].b = lut[i][b];
    }
}

void dos_change_mode(void)
{/*
    int ret;
    int width = option.video_width;
    int height = option.video_height;

    if(option.scanlines) height *= 2;
    ret = set_gfx_mode(option.video_driver, width, height, 0, 0);
    if(ret != 0)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        printf("Error setting graphics mode (%dx%d %dbpp).\nAllegro says: `%s'\n", width, height, option.video_depth, allegro_error);
        exit(1);
    }

    if(bitmap.depth == 8)
    {
        if(bitmap.remap)
        {
            int i;
            for(i = 0; i < 0x100; i += 1)
            {                     
                gen_pal[i].r = ((i >> 5) & 7) << 3;
                gen_pal[i].g = ((i >> 2) & 7) << 3;
                gen_pal[i].b = ((i >> 0) & 3) << 4;
            }
        set_palette(gen_pal);
        }
        else
        {
            clear_to_color(screen, 0xFF);
            gen_pal[0xfe].r = 0xff;
            gen_pal[0xfe].g = 0xff;
            gen_pal[0xfe].b = 0xff;
            set_palette(gen_pal);
            inp(0x3DA);
            outp(0x3C0, 0x31);
            outp(0x3C0, 0xFF);
        }
    }
    else
    {
        clear(screen);
    }*/
}



/* Check if a key is pressed */
int check_key(int code)
{/*
    static char lastbuf[0x100] = {0};

    if((!key[code]) && (lastbuf[code] == 1))
        lastbuf[code] = 0;

    if((key[code]) && (lastbuf[code] == 0))
    {
        lastbuf[code] = 1;
        return (1);
    }                                                                    
*/
    return (0);
}


void init_machine(void)
{  
//    memset(&scr, 0,sizeof(scr));
    memset(&bitmap, 0, sizeof(bitmap));
    
    bitmap.data = (unsigned char *)scr;
    bitmap.width = 320;//256;
    bitmap.height = 240;//224;
    bitmap.depth = 16;
    bitmap.granularity = 2;

    bitmap.pitch = (bitmap.width * bitmap.granularity);
    bitmap.viewport.w = 256;
    bitmap.viewport.h = 224;
    bitmap.viewport.x = 0x20;
    bitmap.viewport.y = 0x00;
    bitmap.remap = 1; //0???

//    if(option.remap) bitmap.remap = 1;
//    else
//    if(bitmap.depth > 8) bitmap.remap = 1;

    make_vdp_palette();

    memset(gen_pal,0,sizeof(gen_pal));//add
 //   memcpy(gen_pal, black_palette, sizeof(PALETTE));
    gen_pal[0xFE].r = \
    gen_pal[0xFE].g = \
    gen_pal[0xFE].b = 0x3F;

    dos_change_mode();

}


//FAKES!!!
void psg_write(int data){}
int fm_read(int address){ return 0;}
void fm_write(int address, int data){}
unsigned int m68k_read_disassembler_32(unsigned int a){ return 0;}
unsigned int m68k_read_disassembler_16(unsigned int a){ return 0;}
int __crt0_argc;
char * *  __crt0_argv;

//int isFreeRam(char *exename, char *fname){ //1=использ.FreeRam, 0=нет
//  return !EL71;
//}
