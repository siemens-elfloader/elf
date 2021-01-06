

#ifndef __DEFS_H__
#define __DEFS_H__

#include "..\swilib.h"

#define IS_LITTLE_ENDIAN
#undef ALLOW_UNALIGNED_IO

#ifdef IS_LITTLE_ENDIAN
#define LO 0
#define HI 1
#else
#define LO 1
#define HI 0
#endif


typedef unsigned char byte;

typedef unsigned char un8;
typedef unsigned short un16;
typedef unsigned int un32;

typedef signed char n8;
typedef signed short n16;
typedef signed int n32;

typedef un16 word;
typedef word addr;







#endif

/*
extern void hw_interrupt(byte i, byte mask);
extern void lcdc_trans();
extern void debug_disassemble(addr a, int c);
extern void die(char *fmt, ...);
	extern void hw_reset();
extern void 	lcd_reset();
	extern void cpu_reset();
	extern void mbc_reset();
	extern void sound_reset();
  extern int cpu_emulate(int cycles);
extern void doevents();
extern void pal_set332();
extern void pal_expire();
extern void refresh_1(byte *dest, byte *src, byte *pal, int cnt);
extern void refresh_2(un16 *dest, byte *src, un16 *pal, int cnt);//un16 !!!
extern void refresh_3(byte *dest, byte *src, un32 *pal, int cnt);
extern void refresh_4(un32 *dest, byte *src, un32 *pal, int cnt); //un32 !!!
extern void refresh_1_2x(byte *dest, byte *src, byte *pal, int cnt);
extern void refresh_2_2x(un16 *dest, byte *src, un16 *pal, int cnt);
extern void refresh_3_2x(byte *dest, byte *src, un32 *pal, int cnt);
extern void refresh_4_2x(un32 *dest, byte *src, un32 *pal, int cnt);
extern void refresh_2_3x(un16 *dest, byte *src, un16 *pal, int cnt);
extern void refresh_3_3x(byte *dest, byte *src, un32 *pal, int cnt);
extern void refresh_4_3x(un32 *dest, byte *src, un32 *pal, int cnt);
extern void refresh_3_4x(byte *dest, byte *src, un32 *pal, int cnt);
extern void refresh_4_4x(un32 *dest, byte *src, un32 *pal, int cnt);
extern void pal_release(byte n);
extern byte pal_getcolor(int c, int r, int g, int b);
extern void hw_hdma();
extern void lcd_refreshline();
extern void savestate(FILE *f);//?
extern void 		vram_dirty();
extern void 		pal_dirty();
extern void 		sound_dirty();
		void loadstate(FILE *f);
    	void rtc_save_internal(FILE *f);
void      	rtc_load_internal(FILE *f);



void	emu_reset();
void	emu_run();
void	ev_poll();
void	vid_close();
void	pcm_close();
void	show_exports();
void	vid_preinit();
void	init_exports();
void	ev_poll();
void rc_dokey(int key, int st);
int rc_command(char *line);
void loader_init(char *s);
void		pad_refresh();
void		lcdc_change(byte b);
void		stat_write(byte b);
void		stat_trigger();
void		hw_dma(byte b);
void		hw_hdma_cmd(byte b);
void 	rtc_latch(byte b);


*/

//cpu.cpp
void cpu_reset();
void div_advance(int cnt);
void timer_advance(int cnt);
void lcdc_advance(int cnt);
void sound_advance(int cnt);
void cpu_timers(int cnt);
int cpu_idle(int max);
void cpu_emulate(int cycles);
int cpu_step(int max);

//debug
void debug_disassemble(addr a, int c);

//emu
void emu_init();
void emu_reset();
void emu_step();
void emu_run();

//events
//int ev_postevent(event_t *ev);
//int ev_getevent(event_t *ev);

//exports
void init_exports();
void show_exports();

//fastmem
static void no_write();

//hw
void hw_interrupt(byte i, byte mask);
void hw_dma(byte b);
void hw_hdma_cmd(byte c);
void hw_hdma();
void pad_refresh();
void pad_press(byte k);
void pad_release(byte k);
void pad_set(byte k, int st);
void hw_reset();

//inflate
//[...]

//keytable
int k_keycode(char *name);
char *k_keyname(int code);

//LCD
void updatepatpix();
void tilebuf();
void bg_scan();
void wnd_scan();
static void blendcpy(byte *dest, byte *src, byte b, int cnt);
static int priused(void *attr);
void bg_scan_pri();
void wnd_scan_pri();
void bg_scan_color();
void wnd_scan_color();
static void recolor(byte *buf, byte fill, int cnt);
void spr_count();
void spr_enum();
void spr_scan();
void lcd_begin();
void lcd_refreshline();
static void updatepalette(int i);
void pal_write(int i, byte b);
void pal_write_dmg(int i, int mapnum, byte d);
void vram_write(int a, byte b);
void vram_dirty();
void pal_dirty();
void lcd_reset();

//lcdc
void stat_trigger();
void stat_write(byte b);
static void stat_change(int stat);
void lcdc_change(byte b);
void lcdc_trans();

//loader
static void initmem(void *mem, int size);
//static byte *loadfile(FILE *f, int *len);
//static void inflate_callback(byte b);
//static byte *decompress(byte *data, int *len);
int rom_load();
int sram_load();
int sram_save();
void state_save(int n);
void state_load(int n);
void rtc_save();
void rtc_load();
void loader_unload();
//static char *base(char *s);
static char *ldup(char *s);
static void cleanup();
int loader_init(char *s);

//main
//static void banner();
//static void copyright();
static void usage(char *name);
static void copying();
//static void help(char *name);
static void version(char *name);
void doevents();
//static void shutdown();
void die(char *fmt, ...);
static void fatalsignal(int s);
//static char *base(char *s);

//mem
void mem_updatemap();
void ioreg_write(byte r, byte b);
byte ioreg_read(byte r);
void mbc_write(int a, byte b);
void mem_write(int a, byte b);
byte mem_read(int a);
void mbc_reset();

//newsound
//void sound_mix(int cycles);
void sound_update(int force);

//palette
static byte bestmatch(int c);
static void makecourse(int c, byte n);
static byte findcourse(int c);
void pal_lock(byte n);
byte pal_getcolor(int c, int r, int g, int b);
void pal_release(byte n);
void pal_expire();
void pal_set332();

//path
char *path_search(char *name, char *mode, char *path);

//rccmds
int rc_command(char *line);

//rcfile
int rc_sourcefile(char *filename);

//rckeys
int rc_bindkey(char *keyname, char *cmd);
int rc_unbindkey(char *keyname);
void rc_unbindall();
void rc_dokey(int key, int st);

//rcvars
//void rc_export(rcvar_t *v);
//void rc_exportvars(rcvar_t *vars);
int rc_findvar(char *name);
int my_atoi(const char *s);
int rc_setvar_n(int i, int c, char **v);
int rc_setvar(char *name, int c, char **v);
void *rc_getmem_n(int i);
void *rc_getmem(char *name);
int rc_getint_n(int i);
int *rc_getvec_n(int i);
char *rc_getstr_n(int i);
int rc_getint(char *name);
int *rc_getvec(char *name);
char *rc_getstr(char *name);


//refresh
void refresh_1(byte *dest, byte *src, byte *pal, int cnt);
void refresh_2(un16 *dest, byte *src, un16 *pal, int cnt);
void refresh_3(byte *dest, byte *src, un32 *pal, int cnt);
void refresh_4(un32 *dest, byte *src, un32 *pal, int cnt);
void refresh_1_2x(byte *dest, byte *src, byte *pal, int cnt);
void refresh_2_2x(un16 *dest, byte *src, un16 *pal, int cnt);
void refresh_3_2x(byte *dest, byte *src, un32 *pal, int cnt);
void refresh_4_2x(un32 *dest, byte *src, un32 *pal, int cnt);
void refresh_2_3x(un16 *dest, byte *src, un16 *pal, int cnt);
void refresh_3_3x(byte *dest, byte *src, un32 *pal, int cnt);
void refresh_4_3x(un32 *dest, byte *src, un32 *pal, int cnt);
void refresh_3_4x(byte *dest, byte *src, un32 *pal, int cnt);
void refresh_4_4x(un32 *dest, byte *src, un32 *pal, int cnt);

//rtc
void rtc_latch(byte b);
void rtc_write(byte b);
void rtc_tick();
void rtc_save_internal(int f);
void rtc_load_internal(int f);

//save
void loadstate(int f);
void savestate(int f);

//sound
static void s1_freq_d(int d);
static void s1_freq();
static void s2_freq();
static void s3_freq();
static void s4_freq();
void sound_dirty();
void sound_off();
void sound_reset();
void sound_mix();
byte sound_read(byte r);
void s1_init();
void s2_init();
void s3_init();
void s4_init();
void sound_write(byte r, byte b);

//split
char *splitnext(char **pos);
int splitline(char **argv, int max, char *line);



//////////////////////////////////////
//fakes
int time(int n); //fake
int isdigit(const char s);//fake
//int unzip(byte *data, unsigned long *pos); //fake modified!
int isalnum(char s); //fake

void vid_init();
void	pcm_init();


void		rtc_tick();
void		sound_mix();

void sys_checkdir(char *path, int wr);
void vid_settitle(char *title);

void ev_poll();
void	vid_close();
void	pcm_close();
void show_exports();
void	vid_preinit();
void	init_exports();
void	sys_sanitize(char *s);
void	sys_initpath(char *s);
void vid_setpal(int i, int r, int g, int b);

void lcd_begin();

//fakes
//struct timeval{int time;} //fake

//int sys_elapsed(struct timeval *prev);
void sys_sleep(int us);
int pcm_submit();
void vid_begin();
void vid_end();




