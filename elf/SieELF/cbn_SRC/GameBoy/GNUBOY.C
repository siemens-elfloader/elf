

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>


//char *strdup(); 

//#include <stdarg.h>
//#include <signal.h>

#include "input.h"
#include "rc.h"
#include "defs.h"
#include "fb.h"

//#include "Version"
//void savescreen(char *fname);/////

/*
static char *defaultconfig[] =
{
	"bind esc quit",
	"bind up +up",
	"bind down +down",
	"bind left +left",
	"bind right +right",
	"bind d +a",
	"bind s +b",
	"bind enter +start",
	"bind space +select",
	"bind tab +select",
	"bind joyup +up",
	"bind joydown +down",
	"bind joyleft +left",
	"bind joyright +right",
	"bind joy0 +b",
	"bind joy1 +a",
	"bind joy2 +select",
	"bind joy3 +start",
	"bind 1 \"set saveslot 1\"",
	"bind 2 \"set saveslot 2\"",
	"bind 3 \"set saveslot 3\"",
	"bind 4 \"set saveslot 4\"",
	"bind 5 \"set saveslot 5\"",
	"bind 6 \"set saveslot 6\"",
	"bind 7 \"set saveslot 7\"",
	"bind 8 \"set saveslot 8\"",
	"bind 9 \"set saveslot 9\"",
	"bind 0 \"set saveslot 0\"",
	"bind ins savestate",
	"bind del loadstate",
	"source gnuboy.rc",
	NULL
};

*/
void doevents()
{
	event_t ev;
	int st;

	ev_poll();
	while (ev_getevent(&ev))
	{
		if (ev.type != EV_PRESS && ev.type != EV_RELEASE)
			continue;
		st = (ev.type != EV_RELEASE);
		rc_dokey(ev.code, st);
	}
}




static void shutdown()
{
	vid_close();
	pcm_close();
}

void die(char *fmt, ...)
{
	//va_list ap;

	//va_start(ap, fmt);
	//vfprintf(stderr, fmt, ap);
	//va_end(ap);
	//exit(1);
}

/*
static int bad_signals[] =
{
	// These are all standard, so no need to #ifdef them... 
	SIGINT, SIGSEGV, SIGTERM, SIGFPE, SIGABRT, SIGILL,
#ifdef SIGQUIT
	SIGQUIT,
#endif
#ifdef SIGPIPE
	SIGPIPE,
#endif
	0
};

static void fatalsignal(int s)
{
	die("Signal %d\n", s);
}
*/

//static void catch_signals()
//{
//	int i;
//	for (i = 0; bad_signals[i]; i++)
		//signal(bad_signals[i], fatalsignal);
//}


/*
static char *base(char *s)
{
	char *p;
	p = strrchr(s, '/');
	if (p) return p+1;
	return s;
}
*/
extern char *romfile;

int gnuboy(char *fname)
{
  int i;
  vid_preinit();
  init_exports();
  vid_init();
  pcm_init();
//sys_sanitize(fname);

  romfile = fname;
  if(i=rom_load()) return i;
  sram_load();
  //if(loader_init(fname)) return 1;
  emu_reset();
  //emu_run();
  return 0;
}




//fakes//////////////
int sys_elapsed(struct timeval *prev){ return 0;}
void sys_sleep(int us){}

int pcm_submit(){ return 0;}
//void sys_timer(){}
void vid_setpal(int a,int b,int c,int d){}
int isdigit(char c){return 0;}
void pcm_close(void){}
void vid_preinit(void){}
//void __cdecl sys_sanitize(char *){}
//void __cdecl sys_initpath(char *){}

//void * __cdecl sys_timer(void){ return NULL;}
/*
struct fb
{
	byte *ptr;
	int w, h;
	int pelsize;
	int pitch;
	int indexed;
	struct
	{
		int l, r;
	} cc[4];
	int yuv;
	int enabled;
	int dirty;
};*/

extern short *scr;//[160*144];

struct fbst fb;//add
//extern struct fb fb;

void vid_init(void){
  fb.ptr=(byte*)scr;
  fb.w=160;
  fb.h=144;
  fb.pelsize=2;
  fb.pitch=160*2;
  fb.enabled=1;
  fb.dirty=0;
  //
  fb.indexed=0;
  fb.cc[0].r=fb.cc[2].r=3;
  fb.cc[1].r=2;
  fb.cc[0].l=11;
  fb.cc[1].l=5;
  fb.cc[2].l=0;
}

void vid_close(void){
  //освоб.вирдеопамять, кл....
}


void ev_poll(void){
  //обновить клавиатуру
}

void vid_begin(){}

//short screen[132*176];
//const int screensize=132*176*2;

extern int frames;
extern int frameskip;

//int counter=0;

//extern void DrawScreen();
extern void on2redraw(void);
extern unsigned char SGOLD2;
extern volatile int timedelay;

void vid_end(){
  if(frames--<=0){
    frames=frameskip;
    on2redraw();
    if(!timedelay) REDRAW();
//    printf("\nshow");
//    savescreen("out.bmp");
  }
}



void  pcm_init(void){}
int isalnum(char c){ return 0;}
void sys_checkdir(char *s,int a){}
void vid_settitle(char *s){}
//int unzip(unsigned char *s,unsigned long *a){return 0;}
int  time(int t){return 0;}

void  init_exports(void){}
void  show_exports(void){}




/*
const char bmphead[]={
"\x42\x4D\xC6\xB5\x00\x00\x00\x00\x00\x00\x36\x00\x00\x00\x28\x00"
"\x00\x00\x84\x00\x00\x00\xB0\x00\x00\x00\x01\x00\x10\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x12\x0B\x00\x00\x12\x0B\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\xF8\x00\x00\xE0\x07\x00\x00\x1F\x00"
"\x00\x00\x00\x00\x00\x00"};

void savescreen(char *fname){
  FILE *f;
  int i;
  short scr[132*176], *s=screen;
  //for(i=0; i<132*176;i++,s++){
  for(i=132*176-1;i>=0;i--,s++){//reverse
    scr[i]=(*s&0x1f)|((*s>>1)&0xffe0);//RGB 555 convert! чтобы BMP корректно выглядело!
     //scr[i]=*s;//<<4;//((*s&0xf)<<1)|((*s&0xf0)<<3)|((*s&0xf00)<<8);
  }// ИЗОБРАЖЕНИЕ здесь повернуто зеркально!!!
  if((f=ffopen(fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))==0) return;
  ffwrite(f,bmphead,sizeof(bmphead),&err); 
  ffwrite(f,scr,screensize,&err); 
  ffclose(f,&err); 
}
*/
//pcm pcm;
//fb fb;

//кооректировал (возм. некорректно)
//NEWSOUND
//rccmds
//LOADER - исправить!!!уже
//emu  emu.ran - timer()
