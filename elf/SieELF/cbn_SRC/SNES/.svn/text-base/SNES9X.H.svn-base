

#ifndef _SNES9X_H_
#define _SNES9X_H_


//#define _MAX_PATH 256

//#define ZeroMemory(a,b) memset((a),0,(b))

//#include <limits.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <memory.h>
#include "port.h"
//#include <string.h>
#include "65c816.h"
#include "messages.h"


#ifndef ACCEPT_SIZE_T
#ifdef __WIN32__
#define ACCEPT_SIZE_T int
#else
#define ACCEPT_SIZE_T unsigned int
#endif
#endif

//#include <sys/types.h>

struct RRECT{
	int top,bottom,left,right;
};

#define VERSION "1.43"

//#include <stdio.h>
//#include <stdlib.h>

//#ifdef __WIN32__
//#include "..\wsnes9x.h"
//#include "..\zlib\zlib.h"
//#endif

//#include "../language.h"


#if defined(USE_GLIDE) && !defined(GFX_MULTI_FORMAT)
#define GFX_MULTI_FORMAT
#endif

#define ROM_NAME_LEN 23

#define BYTE unsigned char
#define DWORD unsigned int

#undef EXT_WIDTH
#undef EXT_HEIGHT
#undef EXT_PITCH
#undef EXT_OFFSET

#define EXT_WIDTH 320
#define EXT_HEIGHT 240
#define EXT_PITCH  320
#define EXT_OFFSET 0 //???????

//struct RECT{
//	int top,bottom,right,left;
//};


#ifdef ZLIB
#ifndef __WIN32__
#include "zlib.h"
#endif
#define STREAM gzFile
#define READ_STREAM(p,l,s) gzread (s,p,l)
#define WRITE_STREAM(p,l,s) gzwrite (s,p,l)
#define OPEN_STREAM(f,m) gzopen (f,m)
#define REOPEN_STREAM(f,m) gzdopen (f,m)
#define FIND_STREAM(f)	gztell(f)
#define REVERT_STREAM(f,o,s)  gzseek(f,o,s)
#define CLOSE_STREAM(s) gzclose (s)
#else
#define STREAM int
#define READ_STREAM(p,l,s) fread (s,p,l,&err)
#define WRITE_STREAM(p,l,s) fwrite (s,p,l,&err)
#define OPEN_STREAM(f,m) fopen (f,m,&err)
#define REOPEN_STREAM(f,m) fdopen (f,m,&err)
#define FIND_STREAM(f)	ftell(f)
#define REVERT_STREAM(f,o,s)	 fseek(f,o,s)
#define CLOSE_STREAM(s) fclose (s,&err)
#endif


/* SNES screen width and height */
#define SNES_WIDTH		256
#define SNES_HEIGHT		224
#define SNES_HEIGHT_EXTENDED	239
#define IMAGE_WIDTH		(Settings.SupportHiRes ? SNES_WIDTH * 2 : SNES_WIDTH)
#define IMAGE_HEIGHT		(Settings.SupportHiRes ? SNES_HEIGHT_EXTENDED * 2 : SNES_HEIGHT_EXTENDED)

#define SNES_MAX_NTSC_VCOUNTER  262
#define SNES_MAX_PAL_VCOUNTER   312
#define SNES_HCOUNTER_MAX	342
#define SPC700_TO_65C816_RATIO	2
#define AUTO_FRAMERATE		200

/* NTSC master clock signal 21.47727MHz
 * PPU: master clock / 4
 * 1 / PPU clock * 342 -> 63.695us
 * 63.695us / (1 / 3.579545MHz) -> 228 cycles per scanline
 * From Earth Worm Jim: APU executes an average of 65.14285714 cycles per
 * scanline giving an APU clock speed of 1.022731096MHz                    */

/* PAL master clock signal 21.28137MHz
 * PPU: master clock / 4
 * 1 / PPU clock * 342 -> 64.281us
 * 64.281us / (1 / 3.546895MHz) -> 228 cycles per scanline.  */

#define SNES_SCANLINE_TIME (63.695e-6)
#define SNES_CLOCK_SPEED (3579545)

#define SNES_CLOCK_LEN (1.0 / SNES_CLOCK_SPEED)

#define SNES_CYCLES_PER_SCANLINE ((uint32) ((SNES_SCANLINE_TIME / SNES_CLOCK_LEN) * 6 + 0.5))

#define SNES_APUTIMER2_CYCLEx10000 ((uint32) ((SNES_CYCLES_PER_SCANLINE * 10000L) * (1.0 / 64000.0) / SNES_SCANLINE_TIME + 0.5))

#define ONE_CYCLE 6
#define SLOW_ONE_CYCLE 8
#define TWO_CYCLES 12


#define SNES_TR_MASK	    (1 << 4)
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
#define SNES_B_MASK	    (1 << 15)

enum {
    SNES_MULTIPLAYER5,
    SNES_JOYPAD,
    SNES_MOUSE_SWAPPED,
    SNES_MOUSE,
    SNES_SUPERSCOPE,
	SNES_JUSTIFIER,
	SNES_JUSTIFIER_2,
    SNES_MAX_CONTROLLER_OPTIONS
};

#define DEBUG_MODE_FLAG	    (1 << 0)
#define TRACE_FLAG			(1 << 1)
#define SINGLE_STEP_FLAG    (1 << 2)
#define BREAK_FLAG			(1 << 3)
#define SCAN_KEYS_FLAG	    (1 << 4)
#define SAVE_SNAPSHOT_FLAG  (1 << 5)
#define DELAYED_NMI_FLAG    (1 << 6)
#define NMI_FLAG			(1 << 7)
#define PROCESS_SOUND_FLAG  (1 << 8)
#define FRAME_ADVANCE_FLAG  (1 << 9)
#define DELAYED_NMI_FLAG2   (1 << 10)
#define IRQ_PENDING_FLAG    (1 << 11)

struct SCPUState{
    uint32  Flags;
    bool8   BranchSkip;
    bool8   NMIActive;
    bool8   IRQActive;
    bool8   WaitingForInterrupt;
    bool8   InDMA;
    uint8   WhichEvent;
    uint8   *PC;
    uint8   *PCBase;
    uint8   *PCAtOpcodeStart;
    uint8   *WaitAddress;
    uint32  WaitCounter;
    long   Cycles;
    long   NextEvent;
    long   V_Counter;
    long   MemSpeed;
    long   MemSpeedx2;
    long   FastROMSpeed;
    uint32 AutoSaveTimer;
    bool8  SRAMModified;
    uint32 NMITriggerPoint;
    bool8  BRKTriggered;
    bool8  TriedInterleavedMode2;
    uint32 NMICycleCount;
    uint32 IRQCycleCount;
#ifdef DEBUG_MAXCOUNT
    unsigned long GlobalLoopCount;
#endif
};

#define HBLANK_START_EVENT 0
#define HBLANK_END_EVENT 1
#define HTIMER_BEFORE_EVENT 2
#define HTIMER_AFTER_EVENT 3
#define NO_EVENT 4

struct SSettings{
    /* CPU options */
    bool8  APUEnabled;
    bool8  Shutdown;
    uint8  SoundSkipMethod;
    long   H_Max;
    long   HBlankStart;
    long   CyclesPercentage;
    bool8  DisableIRQ;
    bool8  Paused;
    bool8  ForcedPause;
    bool8  StopEmulation;
    bool8  FrameAdvance;

    /* Tracing options */
    bool8  TraceDMA;
    bool8  TraceHDMA;
    bool8  TraceVRAM;
    bool8  TraceUnknownRegisters;
    bool8  TraceDSP;

    /* Joystick options */
    bool8  SwapJoypads;
    bool8  JoystickEnabled;

    /* ROM timing options (see also H_Max above) */
    bool8  ForcePAL;
    bool8  ForceNTSC;
    bool8  PAL;
    uint32 FrameTimePAL;
    uint32 FrameTimeNTSC;
    uint32 FrameTime;
    uint32 SkipFrames;

    /* ROM image options */
    bool8  ForceLoROM;
    bool8  ForceHiROM;
    bool8  ForceHeader;
    bool8  ForceNoHeader;
    bool8  ForceInterleaved;
    bool8  ForceInterleaved2;
    bool8  ForceNotInterleaved;

    /* Peripherial options */
    bool8  ForceSuperFX;
    bool8  ForceNoSuperFX;
    bool8  ForceDSP1;
    bool8  ForceNoDSP1;
    bool8  ForceSA1;
    bool8  ForceNoSA1;
    bool8  ForceC4;
    bool8  ForceNoC4;
    bool8  ForceSDD1;
    bool8  ForceNoSDD1;
    bool8  MultiPlayer5;
    bool8  Mouse;
    bool8  SuperScope;
    bool8  SRTC;
    uint32 ControllerOption;
    
    bool8  ShutdownMaster;
    bool8  MultiPlayer5Master;
    bool8  SuperScopeMaster;
    bool8  MouseMaster;
    bool8  SuperFX;
    bool8  DSP1Master;
    bool8  SA1;
    bool8  C4;
    bool8  SDD1;
	bool8  SPC7110;
	bool8  SPC7110RTC;
	bool8  OBC1;
    /* Sound options */
    uint32 SoundPlaybackRate;
    bool8  TraceSoundDSP;
    bool8  Stereo;
    bool8  ReverseStereo;
    bool8  SixteenBitSound;
    int    SoundBufferSize;
    int    SoundMixInterval;
    bool8  SoundEnvelopeHeightReading;
    bool8  DisableSoundEcho;
    bool8  DisableSampleCaching;
    bool8  DisableMasterVolume;
    bool8  SoundSync;
    bool8  InterpolatedSound;
    bool8  ThreadSound;
    bool8  Mute;
    bool8  NextAPUEnabled;
    uint8  AltSampleDecode;
    bool8  FixFrequency;
    
    /* Graphics options */
    bool8  SixteenBit;
    bool8  Transparency;
    bool8  SupportHiRes;
    bool8  Mode7Interpolate;

    /* SNES graphics options */
    bool8  BGLayering;
    bool8  DisableGraphicWindows;
    bool8  ForceTransparency;
    bool8  ForceNoTransparency;
    bool8  DisableHDMA;
    bool8  DisplayFrameRate;
    bool8  DisableRangeTimeOver; /* XXX: unused */

    /* Others */
    bool8  NetPlay;
    bool8  NetPlayServer;
    char   ServerName [128];
    int    Port;
    bool8  GlideEnable;
    bool8  OpenGLEnable;
    int32  AutoSaveDelay; /* Time in seconds before S-RAM auto-saved if modified. */
    bool8  ApplyCheats;
    bool8  TurboMode;
    uint32 TurboSkipFrames;
    uint32 AutoMaxSkipFrames;
    
/* Fixes for individual games */
    bool8  StarfoxHack;
    bool8  WinterGold;
    bool8  BS;	/* Japanese Satellite System games. */
    bool8  DaffyDuck;
    uint8  APURAMInitialValue;
    bool8  SampleCatchup;
	bool8  JustifierMaster;
	bool8  Justifier;
	bool8  SecondJustifier;
	int8   SETA;
    bool8  TakeScreenshot;
    int8   StretchScreenshots;
	uint16 DisplayColor;
    int    SoundDriver;
    int    AIDOShmId;
    bool8  SDD1Pack;
	bool8  NoPatch;
	bool8  ForceInterleaveGD24;
#ifdef DEBUG_MAXCOUNT
    unsigned int MaxCount;
#endif
};

struct SSNESGameFixes
{
    uint8 alienVSpredetorFix;
    uint8 APU_OutPorts_ReturnValueFix;
    uint8 SoundEnvelopeHeightReading2;
    uint8 SRAMInitialValue;
	uint8 Uniracers;
	bool8 EchoOnlyOutput;
};

START_EXTERN_C
extern struct SSettings Settings;
extern struct SCPUState CPU;
extern struct SSNESGameFixes SNESGameFixes;
extern char String [513];

void S9xExit ();
void S9xMessage (int type, int number, const char *message);
void S9xLoadSDD1Data ();
END_EXTERN_C

enum {
    PAUSE_NETPLAY_CONNECT = (1 << 0),
    PAUSE_TOGGLE_FULL_SCREEN = (1 << 1),
    PAUSE_EXIT = (1 << 2),
    PAUSE_MENU = (1 << 3),
    PAUSE_INACTIVE_WINDOW = (1 << 4),
    PAUSE_WINDOW_ICONISED = (1 << 5),
    PAUSE_RESTORE_GUI = (1 << 6),
    PAUSE_FREEZE_FILE = (1 << 7)
};
void S9xSetPause (uint32 mask);
void S9xClearPause (uint32 mask);

#undef MAX_PATH
#define MAX_PATH 256 //my


/*
typedef struct 
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} RECT;
*/
struct ssGUI {
    DWORD hFrameTimer;
    DWORD hSoundTimer;
    BYTE Language;

    unsigned long PausedFramesBeforeMutingSound;
    int  Width;
    int  Height;
    int  Depth;
    int  Scale;
    int  NextScale;
    bool DoubleBuffered;
    bool FullScreen;
    bool Stretch;
    bool ScreenCleared;
    bool IgnoreNextMouseMove;
    int  MouseX;
    int  MouseY;
    unsigned int MouseButtons;
    int CursorTimer;
    bool NeedDepthConvert;
    bool BGR;
    bool TurboModeToggle;
    int  ScreenDepth;
    int  RedShift;
    int  GreenShift;
    int  BlueShift;
    unsigned int FlipCounter;
    unsigned int NumFlipFrames;
    char FreezeFileDir [MAX_PATH];
    char **RecentGames;

	//turbo switches -- SNES-wide
	unsigned char TurboMask;
	char StarOceanPack[MAX_PATH];
	char SFA2PALPack[MAX_PATH];
	char SFA2NTSCPack[MAX_PATH];
	char SFZ2Pack[MAX_PATH];
	char SJNSPack[MAX_PATH];
	char FEOEZPack[MAX_PATH];
	char SPL4Pack[MAX_PATH];
	char MDHPack[MAX_PATH];
//	COLORREF InfoColor;
	bool HideMenu;
	bool VideoMemory;

	// avi writing
//	struct AVIFile* AVIOut;
};

bool8 S9xOpenSnapshotFile (const char *base, bool8 read_only, STREAM *file);
void S9xCloseSnapshotFile (STREAM file);


#endif



