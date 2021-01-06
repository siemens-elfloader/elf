
#undef TRUE
#undef FALSE

#include "snes9x.h"
#include "memmap.h"
#include "debug.h"
#include "ppu.h"
#include "snapshot.h"
#include "gfx.h"
#include "display.h"
#include "apu.h"
#include "soundux.h"

#define COUNT(a) (sizeof(a) / sizeof(a[0]))

//#define sti() __asm__ __volatile__ ("sti": : :"memory")
//#define cli() __asm__ __volatile__ ("cli": : :"memory")

static int screen_pitch = 132;
uint32 screen_width = 132;
uint32 screen_height = 176;
static int mode = -1;
static bool8 planar = FALSE;
static bool8 in_text_mode = TRUE;
static bool8 stretch = FALSE;

uint8 *off_screen;
uint8 *sub_screen;
uint8 *Delta = NULL;
extern uint8 *screen;

static int num_sidewinders = 0;
static bool8 grip_initialised = FALSE;
extern int NumControllers;
static bool8 mouse_installed = FALSE;
static int prev_mouse_x = 0;
static int prev_mouse_y = 0;
static uint32 superscope_turbo = 0;
static uint32 superscope_pause = 0;
static int mouse_offset_x = 0;
static int mouse_offset_y = 0;
static double mouse_scale_h = 1.0;
static double mouse_scale_v = 1.0;
static bool8 wait_for_vsync = FALSE;
static bool8 interpolate = FALSE;

uint32 last_rendered_width = 0;
uint32 last_rendered_height = 0;

extern uint32 joypads [5];

void SaveScreenshot ();

#define ATTRCON_ADDR	0x3c0
#define MISC_ADDR	0x3c2
#define VGAENABLE_ADDR	0x3c3
#define SEQ_ADDR	0x3c4
#define GRACON_ADDR	0x3ce
#define CRTC_ADDR	0x3d4
#define STATUS_ADDR	0x3da

//struct PALLETE {
//  uint8 r,g,b;
//} pal[256];


short pal[256];

/*
typedef struct
{
    int width;
    int height;
    int mode;
} Mode;

static Mode modes [] = {
    {320, 240, GFX_MODEX},	    // 0
    {320, 200, GFX_VGA},	    // 1
    {256, 256, GFX_VGA},	    // 2
    {640, 480, GFX_AUTODETECT},	    // 3
    {640, 480, GFX_VESA1},	    // 4
    {640, 480, GFX_VESA2B},	    // 5
    {640, 480, GFX_VESA2L},	    // 6
    {640, 400, GFX_XTENDED},	    // 7
    {800, 600, GFX_AUTODETECT},	    // 8

    {320, 240, GFX_AUTODETECT},	    // 9
    {640, 480, GFX_AUTODETECT},	    // 10
    {512, 384, GFX_AUTODETECT},	    // 11
    {800, 600, GFX_AUTODETECT}	    // 12
};
*/
void S9xInitDisplay ()
{
//	set_color_depth (16);
	//Settings.Transparency = TRUE;
	//Settings.SixteenBit = TRUE;
//	set_color_depth (8);
	Settings.Transparency = FALSE;
	Settings.SixteenBit = FALSE;

    off_screen = (uint8*)malloc ((IMAGE_WIDTH + 2)* IMAGE_HEIGHT);

    GFX.Screen = (uint8 *) off_screen;
    if (!GFX.Screen)
    {
	//fprintf (stdout, "Cannot allocate screen buffer.\n");
	//S9xExit ();
    }
    GFX.Pitch = IMAGE_WIDTH + 2;
	GFX.SubScreen = GFX.Screen;
	GFX.ZBuffer = (uint8 *) malloc ((IMAGE_WIDTH + 2)* IMAGE_HEIGHT);
	GFX.SubZBuffer = NULL;
	sub_screen = NULL;
	Delta = NULL;
    //}
    screen_pitch = IMAGE_WIDTH + 2;
}

void S9xDeinitDisplay ()
{
    //S9xTextMode ();
	if(off_screen){ free(off_screen); off_screen=0;}
    if(sub_screen){ free(sub_screen); sub_screen=0;}
	if(Delta){ free(Delta); Delta=0;}
    if(GFX.ZBuffer){ free((char *)GFX.ZBuffer); GFX.ZBuffer=0;}
    if(GFX.SubZBuffer){ free((char *)GFX.SubZBuffer); GFX.SubZBuffer=0;}
}

void S9xInitInputDevices ()
{
}

void S9xSetPalette ()
{
//    uint16 Brightness = IPPU.MaxBrightness * 138;
//	uint8 r,g,b;
    for (int i = 0; i < 256; i++)
    {
/*      
	r = (((PPU.CGDATA [i] >> 0) & 0x1F) * Brightness) >> 10;
	g = (((PPU.CGDATA [i] >> 5) & 0x1F) * Brightness) >> 10;
	b = (((PPU.CGDATA [i] >> 10) & 0x1F) * Brightness) >> 10;
    pal[i]=(b>>3<<11)|(g>>2<<5)|(r>>3);*/
      pal[i]=(PPU.CGDATA [i]&0x1f)|((PPU.CGDATA [i]&0xffe0)<<1);
//      pal[i]=PPU.CGDATA [i];
    }
    //set_palette_range (p, 0, 255, FALSE);
}

void S9xProcessEvents (bool8 block)
{
}

void S9xSetTitle (const char *title)
{
}

/*
//////////38
const char bmphead[]={
"\x42\x4D\xC6\xB5\x00\x00\x00\x00\x00\x00\x36\x00\x00\x00\x28\x00"
"\x00\x00\x84\x00\x00\x00\xB0\x00\x00\x00\x01\x00\x10\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x12\x0B\x00\x00\x12\x0B\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\xF8\x00\x00\xE0\x07\x00\x00\x1F\x00"
"\x00\x00\x00\x00\x00\x00"};
const int screensize=132*176*2;

void savescreen(char *fname){//256 224
  FILE *f;
  int i,j;
//  uint8 c;

  short scr[132*176], *ss=scr;
  uint8 *s=off_screen;
  for(j=0;j<176;j++){
    for(i=0;i<128;i++){
      //c=*s;//&0xff;
      *ss++=pal[*s];//(pal[c].b>>3<<11)|(pal[c].g>>2<<5)|(pal[c].r>>3);
      s+=2;
    }
	s+=2;
    ss+=4;
    //s+=260;
  }


//  for(i=0; i<132*176;i++,s++){
  //for(i=132*176-1;i>=0;i--,s++){//reverse
//    scr[i]=(*s&0x1f)|((*s>>1)&0xffe0);//RGB 555 convert! чтобы BMP корректно выглядело!
     //scr[i]=(*s);//<<4;//((*s&0xf)<<1)|((*s&0xf0)<<3)|((*s&0xf00)<<8);
//  }// ИЗОБРАЖЕНИЕ здесь повернуто зеркально!!!
  if((f=fopen(fname,"wb"))==NULL) return;
  fwrite(bmphead,sizeof(bmphead),1,f); 
  fwrite(scr,screensize,1,f); 
  fclose(f); 
}
//#endif
int ncnt=100;
*/
void S9xPutImage (int width, int height) //256 224
{
#ifdef VISUALC
    savescreen("out.bmp");
    printf("show ");
#else
    REDRAW();
#endif
	/*
    //extern volatile char key[128];

    if (IPPU.Controller == SNES_SUPERSCOPE)
	scare_mouse ();

    if (wait_for_vsync)
    {
	vsync ();
	//while ((inportb (0x3da) & 8) && !key [SCANCODE_ESCAPE]);
	//while (!(inportb (0x3da) & 8) && !key [SCANCODE_ESCAPE]);
    }

    if (interpolate && Settings.SixteenBit && screen_width >= 512 &&
	height < 240)
    {
	void TVMode (uint8 *srcPtr, uint32 srcPitch,
		     uint8 *deltaPtr,
		     BITMAP *dstBitmap, int width, int height);

	if (width != last_rendered_width || height != last_rendered_height)
	    memset (Delta, 0xff, (IMAGE_WIDTH + 2) * IMAGE_HEIGHT * 2);
	TVMode (GFX.Screen, GFX.Pitch, Delta, screen, width, height);
    }
    else
    if (stretch)
    {
	stretch_blit (off_screen, screen, 0, 0, width, height,
		      0, 0, screen_width, screen_height);
	mouse_offset_x = 0;
	mouse_offset_y = 0;
	mouse_scale_h = screen_width / (double) width;
	mouse_scale_v = screen_height / (double) height;
    }
    else
    if (Settings.SupportHiRes)
    {
	if (screen_width < width || screen_height < height)
	{
	    stretch_blit (off_screen, screen, 0, 0, width, height,
			  0, 0, screen_width, screen_height);
	    mouse_offset_x = 0;
	    mouse_offset_y = 0;
	    mouse_scale_h = screen_width / (double) width;
	    mouse_scale_v = screen_height / (double) height;
	}
	else
	{
	    int h = height;
	    int w = width;

	    if (h < 240)
		h <<= 1;
	    if (w == 256)
		w = 512;
	    if (w > screen_width)
		w = screen_width;
	    if (h > screen_height)
		h = screen_height;
	    mouse_offset_x = (screen_width - w) >> 1;
	    mouse_offset_y = (screen_height - h) >> 1;
	    stretch_blit (off_screen, screen, 0, 0, width, height,
			  mouse_offset_x, mouse_offset_y, w, h);
	    mouse_scale_h = w / (double) width;
	    mouse_scale_v = h / (double) height;
	}
    }
    else
    {
	if (modes [mode].mode == GFX_VGA && screen_width == 256)
	{
	    int y_buff;
	    int y_start;
	    int y_end;
	    int x_start = (screen_width - width) >> 1;

	    mouse_offset_x = 0;
	    mouse_scale_h = 1.0;
	    mouse_scale_v = 1.0;
	    if (screen_height >= height)
	    {
		mouse_offset_y = y_start = (screen_height - height) >> 1;
		y_end = y_start + height;
		y_buff = 0;
	    }
	    else
	    {
		y_start = 0;
		y_end = screen_height;
		y_buff = (height - screen_height) >> 1;
	    }
	    uint8 *s = GFX.Screen + screen_pitch * y_buff;
	    uint8 *p = screen->line[0] + screen->w * y_start + x_start;
	    for (int y = y_start; y < y_end; y++, s += screen_pitch, p += screen->w)
		movedata (_my_ds(), (unsigned int) s, 
			  (unsigned int) screen->seg, (unsigned int) p, 
			  width);
	}
	else
	{
	    mouse_offset_x = (screen_width - width) >> 1;
	    mouse_offset_y = (screen_height - height) >> 1;
	    mouse_scale_h = 1.0;
	    mouse_scale_v = 1.0;
	    blit (off_screen, screen, 0, 0, mouse_offset_x, mouse_offset_y,
		  width, height);
	}
    }
    if (IPPU.Controller == SNES_SUPERSCOPE)
	unscare_mouse ();

    last_rendered_width = width;
    last_rendered_height = height;*/
}

void S9xExtraUsage ()
{
    printf ("\
-m  num     Screen mode:\n\
            0 - 320x240 (modex, slower), 1 - 320x200 (faster but clipped)\n\
            2 - 256x256 (fastest but non-standard), 3-6 - 640x480, 7 - 640x400\n\
            8 - 800x600, 9 - 320x240 16 bit, 10 - 640x480 16 bit\n");
    printf ("\
-scale      Scale SNES screen to fit S-VGA screen\n");
}

void S9xParseDisplayArg (char **argv, int &ind, int)
{/*
    if ((strcmp (argv [ind], "-m") == 0 ||
	 strcasecmp (argv [ind], "-mode") == 0 ) && argv [ind + 1])
    {
	mode = atoi (argv [++ind]);
	if (mode >= sizeof (modes) / sizeof (modes [0]))
	    mode = 0;
    }
    else
    if (strcasecmp (argv [ind], "-scale") == 0 ||
	strcasecmp (argv [ind], "-sc") == 0)
	stretch = TRUE;
    else 
    if (strcasecmp (argv [ind], "-w") == 0)
	wait_for_vsync = TRUE;
    else
    if (strcasecmp (argv [ind], "-y") == 0)
    {
	Settings.SixteenBit = TRUE;
	Settings.SupportHiRes = TRUE;
	Settings.Transparency = TRUE;
	interpolate = TRUE;
    }
    else*/
	S9xUsage ();
}

//volatile uint32 FrameTimer = 0;

//static void TimerInterrupt (...)
//{
//    FrameTimer++;
//}
//static END_OF_FUNCTION (TimerInterrupt);

//void InitTimer ()
//{
    //install_timer ();
    //LOCK_VARIABLE (FrameTimer);
    //LOCK_FUNCTION (TimerInterrupt);
    //if (install_int (TimerInterrupt, Settings.FrameTime / 1000) < 0)
    //{
	//printf ("Snes9X: Dynamic speed limiting not available\n");
	//Settings.SkipFrames = 3;
    //}
//}

int S9xMinCommandLineArgs ()
{
    return (2);
}

//static uint32 GamePadProToSNES [10] = {
    //SNES_TR_MASK, SNES_TL_MASK, SNES_X_MASK, SNES_A_MASK,
    //SNES_Y_MASK, SNES_TL_MASK, SNES_B_MASK, SNES_TR_MASK,
    //SNES_START_MASK, SNES_SELECT_MASK
//};

//static uint32 GamePadProToSNESDir [4] = {
    //SNES_RIGHT_MASK, SNES_LEFT_MASK, SNES_UP_MASK, SNES_DOWN_MASK
//};


//extern volatile uint32 FrameTimer;

void S9xSyncSpeed ()
{
	if (++IPPU.FrameSkip >= Settings.SkipFrames)
	{
	    IPPU.FrameSkip = 0;
	    IPPU.RenderThisFrame = TRUE;
	    IPPU.SkippedFrames = 0;
	}
	else
	{
	    IPPU.SkippedFrames++;
	    IPPU.RenderThisFrame = FALSE;
	}
}

void S9xMessage (int type, int message_no, const char *str)
{
}

