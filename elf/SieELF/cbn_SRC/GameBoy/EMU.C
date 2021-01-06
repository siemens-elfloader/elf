


#include "defs.h"
#include "regs.h"
#include "hw.h"
#include "cpu.h"
#include "mem.h"
#include "lcd.h"
#include "rc.h"

extern volatile int running, loadsave;
extern void (*cpuemulate)(int cycles);

static int framelen = 16743;
static int framecount;

rcvar_t emu_exports[] =
{
	RCV_INT("framelen", &framelen),
	RCV_INT("framecount", &framecount),
	RCV_END
};







void emu_init()
{
	
}


/*
 * emu_reset is called to initialize the state of the emulated
 * system. It should set cpu registers, hardware registers, etc. to
 * their appropriate values at powerup time.
 */

void emu_reset()
{
	hw_reset();
	lcd_reset();
	cpu_reset();
	mbc_reset();
	sound_reset();
}





inline void emu_step()
{
	cpuemulate(cpu.lcdc);
}



/* This mess needs to be moved to another module; it's just here to
 * make things work in the mean time. */

void *sys_timer();

extern char romname[128];

void emu_run()
{
	//void *timer = 0;//sys_timer();//ÍÀÄÎ
	int delay, f;

	vid_begin();
	lcd_begin();
lloop:
        loadsave=0;
        running=1;
	while(running)
        {
		cpuemulate(2280);
		while (R_LY > 0 && R_LY < 144)
		  cpuemulate(cpu.lcdc);//emu_step();
		
		vid_end();
		rtc_tick();
		//sound_mix();
	//	if (!pcm_submit())
//		{
//			delay = 0;//framelen - sys_elapsed((struct timeval *)timer); //add
//			sys_sleep(delay);
			//sys_elapsed((struct timeval *)timer);
//		}
	//	doevents();
		vid_begin();
//		if (framecount) { if (!--framecount) die("finished\n"); }
		
		if (!(R_LCDC & 0x80))
			cpuemulate(32832);
		
		while (R_LY > 0) // wait for next frame 
                  cpuemulate(cpu.lcdc);//emu_step();
	}
        switch(loadsave){
        case 1: //load
          if((f=fopen(romname,A_ReadOnly+A_BIN,P_READ,&err))!=-1){
            //emu_reset();
            loadstate(f);
            fclose(f,&err);
            vram_dirty();
            pal_dirty();
            mem_updatemap();
          } goto lloop;
        case 2: //save
          if((f=fopen(romname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1){
            savestate(f);
            fclose(f,&err);
          } goto lloop;
        }
}

/*error
void emu2_run()
{
//	void *timer = 0;//sys_timer();//ÍÀÄÎ
//	int delay;
	vid_begin();
	lcd_begin();
	while(running)
	{
		cpu_emulate(2280);
		while (R_LY > 0 && R_LY < 144)
			cpu_emulate(cpu.lcdc);//emu_step();
		
		vid_end();
		rtc_tick();
//		sound_mix();
//		if (!pcm_submit())
//		{
//			delay = framelen - sys_elapsed((struct timeval *)timer); //add
//			sys_sleep(delay);
//			sys_elapsed((struct timeval *)timer);
//		}
//		doevents();
//
//		vid_begin();
//		if (framecount) { if (!--framecount) die("finished\n"); }
//		
		if (!(R_LCDC & 0x80))
			cpu_emulate(32832);
		
		while (R_LY > 0) // wait for next frame 
     	cpu_emulate(cpu.lcdc);//	emu_step();
	}
}
*/











