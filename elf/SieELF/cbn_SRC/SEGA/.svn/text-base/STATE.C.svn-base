// state.c

#include "shared.h"
#include "genesis.h"
//#include "cyclone.h"
#include "state.h"
//#include "vdp.h"
//#include "m68kcpu.h"

extern uint8 sat[0x400];               /* Internal copy of sprite attribute table */
extern uint8 vram[0x10000];            /* Video RAM (64Kx8) */
extern uint8 cram[0x80];               /* On-chip color RAM (64x9) */
extern uint8 vsram[0x80];              /* On-chip vertical scroll RAM (40x11) */
extern uint8 reg[0x20];                /* Internal VDP registers (23x8) */
extern uint16 addr;                    /* Address register */
extern uint16 addr_latch;              /* Latched A15, A14 of address */
extern uint8 code;                     /* Code register */
extern uint8 pending;                  /* Pending write flag */
extern uint16 buffer;                  /* Read buffer */
extern uint16 status;                  /* VDP status flags */
extern uint16 ntab;                    /* Name table A base address */
extern uint16 ntbb;                    /* Name table B base address */
extern uint16 ntwb;                    /* Name table W base address */
extern uint16 satb;                    /* Sprite attribute table base address */
extern uint16 hscb;                    /* Horizontal scroll table base address */
extern uint16 sat_base_mask;           /* Base bits of SAT */
extern uint16 sat_addr_mask;           /* Index bits of SAT */
extern uint8 is_color_dirty;           /* 1= One or more colors have changed */
extern uint8 color_dirty[0x40];        /* 1= This color is dirty */
extern uint8 border;                   /* Border color index */
extern uint8 is_border_dirty;          /* 1= The border color has changed */
extern uint8 bg_name_dirty[0x800];     /* 1= This pattern is dirty */
extern uint16 bg_name_list[0x800];     /* List of modified pattern indices */
extern uint16 bg_list_index;           /* # of modified patterns in list */
extern uint8 *bg_pattern_cache;/* Cached and flipped patterns */
extern uint8 playfield_shift;          /* Width of planes A, B (in bits) */
extern uint8 playfield_col_mask;       /* Vertical scroll mask */
extern uint16 playfield_row_mask;      /* Horizontal scroll mask */
extern uint32 y_mask;                  /* Name table Y-index bits mask */
extern int hint_pending;               /* 0= Line interrupt is pending */
extern int vint_pending;               /* 1= Frame interrupt is pending */
extern int counter;                    /* Raster counter */
extern int dma_fill;                   /* 1= DMA fill has been requested */
extern int im2_flag;                   /* 1= Interlace mode 2 is being used */
extern int frame_end;                  /* End-of-frame (IRQ line) */
extern int v_counter;                  /* VDP scan line counter */
extern int v_update;                  /* 1= VC was updated by a ctrl or HV read */
extern uint8 fm_status;            /* Read-only status flags */

extern void AddMessage (char * string, int ttl);

#define SIG	'GPSF'

extern char RomPath[260];
//char genZ_curVolume;
/*
void load_sram(void)
{
	STREAM file;
	char chaine[256];  	
	sprintf(chaine,"%s%s",RomPath,".srm");
	file=OPEN_STREAM(chaine,"rb");
	if (!file) return;
	READ(saveram,save_len);
	CLOSE_STREAM(file);
}

void save_sram(void)
{
	STREAM file;
	char chaine[256];  	
	sprintf(chaine,"%s%s",RomPath,".srm");
	file=OPEN_STREAM(chaine,"w+b");
	if (!file) return;
	WRITE(saveram,save_len);
	CLOSE_STREAM(file);
}

void GetStateFileName(int num,char *str)
{
	sprintf(str,"%s%s%d",RomPath,".gs",num);
}

int state_delete(int num)
{
	char savename[255];
	GetStateFileName(num,savename);
#ifndef _MSC_VER
	unlink(savename);
#endif
}
*/
int state_load(int file)
{
	uint32	tmp32;
	uint32	sig;
	int i;
	int		height, width;

	READ(&sig, 4); 
	if (sig != SIG)
	{
		return -1;
	}
	
	// gen.c stuff
	READ(work_ram, 0x10000);
	READ(zram, 0x2000);
	READ(&zbusreq, 1);
	READ(&zreset, 1);
	READ(&zbusack, 1);
	READ(&zirq, 1);
	READ(&zbank, 4);

	// io.c stuff
	READ(io_reg, 0x10);
	
	// vdp.c stuff
	READ(sat, 0x400);
	READ(vram, 0x10000);
	READ(cram, 0x80);
	READ(vsram, 0x80);
	READ(reg, 0x20);
	READ(&addr, 2);
	READ(&addr_latch, 2);
	READ(&code, 1);
	READ(&pending, 1);
	READ(&buffer, 2);
	READ(&status, 2);
	READ(&ntab, 2);
	READ(&ntbb, 2);
	READ(&ntwb, 2);
	READ(&satb, 2);
	READ(&hscb, 2);
	READ(&sat_base_mask, 2);
	READ(&sat_addr_mask, 2);
	READ(&border, 1);
	READ(&playfield_shift, 1);
	READ(&playfield_col_mask, 1);
	READ(&playfield_row_mask, 2);
	READ(&y_mask, 4);
	READ(&hint_pending, 4);
	READ(&vint_pending, 4);
	//READ(&scanline,4);
	READ(&counter, 4);
	READ(&dma_fill, 4);
	READ(&im2_flag, 4);
	READ(&frame_end, 4);
	READ(&v_counter, 4);
	READ(&v_update, 4);
/*	
	// sound.c stuff
	READ(fm_reg[0], 0x100);
	READ(fm_reg[1], 0x100);
	READ(fm_latch, 2);
	READ(&fm_status, 2);
	READ(&timer[0].running, sizeof(int));
	READ(&timer[0].enable, sizeof(int));
	READ(&timer[0].count, sizeof(int));
	READ(&timer[0].base, sizeof(int));
	READ(&timer[0].index, sizeof(int));
	READ(&timer[1].running, sizeof(int));
	READ(&timer[1].enable, sizeof(int));
	READ(&timer[1].count, sizeof(int));
	READ(&timer[1].base, sizeof(int));
	READ(&timer[1].index, sizeof(int));
*/	
	// Window size
	READ(&height, sizeof(int));
	READ(&width, sizeof(int));
/*
	if (height != bitmap.viewport.h)
	{
		bitmap.viewport.oh = bitmap.viewport.h;
		bitmap.viewport.h = height;
		bitmap.viewport.changed = 1;
	}
	if (width != bitmap.viewport.w)
	{
		bitmap.viewport.ow = bitmap.viewport.w;
		bitmap.viewport.w = width;
		bitmap.viewport.changed = 1;
	}
*/
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_D0, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_D1, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_D2, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_D3, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_D4, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_D5, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_D6, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_D7, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_A0, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_A1, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_A2, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_A3, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_A4, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_A5, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_A6, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_A7, tmp32);
	READ(&tmp32, 4); m68k_set_reg(M68K_REG_PC, tmp32);	
	READ(&tmp32, 2); m68k_set_reg(M68K_REG_SR, tmp32);
	// Remake cache
	/*make_bg_pattern_cache();
	vdp_restore_colours();*/
	for (i=0;i<0x800;i++) 
    {
	    bg_name_list[i]=i;
	    bg_name_dirty[i]=0xFF;
    }
    bg_list_index=0x800;
#define color_update color_update_16
    {
    	for(i = 0; i < 0x40; i += 1)
        {
        	color_update(i, *(uint16 *)&cram[i << 1]);                    
        }
        color_update(0x00, *(uint16 *)&cram[border << 1]);
        color_update(0x40, *(uint16 *)&cram[border << 1]);
        color_update(0x80, *(uint16 *)&cram[border << 1]);
    }    					
		
	// Flush fm
	//fm_flush();
	return 0;
}

int state_save(int file)
{
	uint32	tmp32;
	uint32	sig;	

	sig = SIG;
	WRITE(&sig, 4);

	// gen.c stuff
	WRITE(work_ram, 0x10000);
	WRITE(zram, 0x2000);
	WRITE(&zbusreq, 1);
	WRITE(&zreset, 1);
	WRITE(&zbusack, 1);
	WRITE(&zirq, 1);
	WRITE(&zbank, 4);

	// io.c stuff
	WRITE(io_reg, 0x10);
	
	// vdp.c stuff
	WRITE(sat, 0x400);
	WRITE(vram, 0x10000);
	WRITE(cram, 0x80);
	WRITE(vsram, 0x80);
	WRITE(reg, 0x20);
	WRITE(&addr, 2);
	WRITE(&addr_latch, 2);
	WRITE(&code, 1);
	WRITE(&pending, 1);
	WRITE(&buffer, 2);
	WRITE(&status, 2);
	WRITE(&ntab, 2);
	WRITE(&ntbb, 2);
	WRITE(&ntwb, 2);
	WRITE(&satb, 2);
	WRITE(&hscb, 2);
	WRITE(&sat_base_mask, 2);
	WRITE(&sat_addr_mask, 2);
	WRITE(&border, 1);
	WRITE(&playfield_shift, 1);
	WRITE(&playfield_col_mask, 1);
	WRITE(&playfield_row_mask, 2);
	WRITE(&y_mask, 4);
	WRITE(&hint_pending, 4);
	WRITE(&vint_pending, 4);
	//WRITE(&scanline,4);
	WRITE(&counter, 4);
	WRITE(&dma_fill, 4);
	WRITE(&im2_flag, 4);
	WRITE(&frame_end, 4);
	WRITE(&v_counter, 4);
	WRITE(&v_update, 4);
/*	
	// sound.c stuff
	WRITE(fm_reg[0], 0x100);
	WRITE(fm_reg[1], 0x100);
	WRITE(fm_latch, 2);
	WRITE(&fm_status, 2);
	WRITE(&timer[0].running, sizeof(int));
	WRITE(&timer[0].enable, sizeof(int));
	WRITE(&timer[0].count, sizeof(int));
	WRITE(&timer[0].base, sizeof(int));
	WRITE(&timer[0].index, sizeof(int));
	WRITE(&timer[1].running, sizeof(int));
	WRITE(&timer[1].enable, sizeof(int));
	WRITE(&timer[1].count, sizeof(int));
	WRITE(&timer[1].base, sizeof(int));
	WRITE(&timer[1].index, sizeof(int));
*/	
	// Window size
	WRITE(&bitmap.viewport.h, sizeof(int));
	WRITE(&bitmap.viewport.w, sizeof(int));
	
	// 68000 CPU

	tmp32 =m68k_get_reg(NULL, M68K_REG_D0);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_D1); 	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_D2);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_D3);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_D4);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_D5);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_D6);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_D7);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_A0);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_A1);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_A2);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_A3);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_A4);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_A5);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_A6);	WRITE(&tmp32, 4);
	tmp32 =	m68k_get_reg(NULL, M68K_REG_A7);	WRITE(&tmp32, 4);		
	tmp32 = m68k_get_reg(NULL, M68K_REG_PC);	WRITE(&tmp32, 4);
	tmp32 = m68k_get_reg(NULL, M68K_REG_SR);	WRITE(&tmp32, 2); 
  	
	return 0;
}
