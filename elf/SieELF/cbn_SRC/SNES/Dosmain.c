
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

//void InitTimer ();

int MAX_ROM_SIZE=0x800000;

char *rom_filename = NULL;
char *snapshot_filename = NULL;

void OutOfMemory ()
{
/*    fprintf (stderr, "\
Snes9X: Memory allocation failure - not enough RAM/virtual memory available.\n\
        S9xExiting...\n");
    Memory.Deinit ();
    S9xDeinitAPU ();
    
    exit (1);*/
}

void S9xParseArg (char **argv, int &i, int argc)
{
	if (argc==2)
	    snapshot_filename = *++argv;
	else
	    S9xUsage ();
}

int dosmain (char *exename, char *fname)
{
    //_crt0_startup_flags = _CRT0_FLAG_FILL_SBRK_MEMORY;

//    if (argc !=2)
//	S9xUsage ();
	
    memset(&Settings, 0,sizeof (Settings));

    Settings.JoystickEnabled = FALSE;
    Settings.SoundPlaybackRate = 4;
    Settings.Stereo = FALSE;//TRUE;
    Settings.SoundBufferSize = 0;
    Settings.CyclesPercentage = 100;
    Settings.DisableSoundEcho = FALSE;
    Settings.APUEnabled = Settings.NextAPUEnabled = TRUE;
    Settings.H_Max = SNES_CYCLES_PER_SCANLINE;
#ifdef VISUALC
    Settings.SkipFrames = 200;//AUTO_FRAMERATE;
#else
	Settings.SkipFrames = 3;//AUTO_FRAMERATE;
#endif
    Settings.ShutdownMaster = TRUE;
    Settings.FrameTimePAL = 20000;
    Settings.FrameTimeNTSC = 16667;
    Settings.FrameTime = Settings.FrameTimeNTSC;
    Settings.DisableSampleCaching = FALSE;
    Settings.DisableMasterVolume = FALSE;
    Settings.Mouse = FALSE;
    Settings.SuperScope = FALSE;
    Settings.MultiPlayer5 = FALSE;
    Settings.ControllerOption = SNES_JOYPAD;
    Settings.Transparency = FALSE;
    Settings.SixteenBit = FALSE;
    Settings.SupportHiRes = FALSE;
    Settings.NetPlay = FALSE;
    Settings.ServerName [0] = 0;
    Settings.ThreadSound = FALSE;
    Settings.AutoSaveDelay = 30;
    Settings.ApplyCheats = TRUE;
    Settings.TurboMode = FALSE;
    Settings.TurboSkipFrames = 1500;//15
    
	rom_filename = fname;
		//S9xParseArgs (argv, argc);

	//add
	Settings.Mute=1;
    Settings.TraceSoundDSP=0;
    Settings.APUEnabled=0;
    //add2 ??????????
    Settings.SoundPlaybackRate = 0;//4;
    Settings.Stereo = FALSE;//TRUE;
    Settings.SoundBufferSize = 0;
    //Settings.CyclesPercentage = 100;
    Settings.DisableSoundEcho = TRUE;//FALSE;
    Settings.APUEnabled = Settings.NextAPUEnabled = FALSE;//TRUE;
//////////

    Settings.Transparency = Settings.ForceTransparency;
    if (Settings.ForceNoTransparency)
	Settings.Transparency = FALSE;

    if (Settings.Transparency)
	Settings.SixteenBit = TRUE;

    Settings.HBlankStart = (256 * Settings.H_Max) / SNES_HCOUNTER_MAX;

    //rom_filename = S9xParseArgs (argv, argc);

    if (!Memory.Init () || !S9xInitAPU()){
	  OutOfMemory ();
	  return 2;
	}

    uint32 saved_flags = CPU.Flags;

#ifdef GFX_MULTI_FORMAT
    S9xSetRenderPixelFormat (RGB565);
#endif

    //if (rom_filename)
    //{
	if (!Memory.LoadROM (rom_filename))
	{
		return 3;
		/*
	    char dir [_MAX_DIR];
	    char drive [_MAX_DRIVE];
	    char name [_MAX_FNAME];
	    char ext [_MAX_EXT];
	    char fname [_MAX_PATH];

	    _splitpath (rom_filename, drive, dir, name, ext);
	    _makepath (fname, drive, dir, name, ext);

	    //strcpy (fname, S9xGetROMDirectory ());
	    //strcat (fname, SLASH_STR);
	    strcpy (fname, name);
	    if (ext [0])
	    {
		strcat (fname, ".");
		strcat (fname, ext);
	    }
	    _splitpath (fname, drive, dir, name, ext);
	    _makepath (fname, drive, dir, name, ext);
	    if (!Memory.LoadROM (fname))
	    {
		printf ("Error opening: %s\n", rom_filename);
		exit (1);
	    }*/
	}
	//Memory.LoadSRAM (S9xGetSRAMFilename ());
    //}
    //else
    //{
	//S9xReset ();
	//Settings.Paused |= 2;
    //}
    CPU.Flags = saved_flags;

    S9xInitInputDevices ();

    S9xInitDisplay ();
    if (!S9xGraphicsInit ()){
	  OutOfMemory ();
	  return 4;
	}
    //S9xTextMode ();

//    (void) S9xInitSound (Settings.SoundPlaybackRate, Settings.Stereo,
//		      Settings.SoundBufferSize);
    if (!Settings.APUEnabled)
   	  S9xSetSoundMute (TRUE);

    if (snapshot_filename)
    {
	int Flags = CPU.Flags & (DEBUG_MODE_FLAG | TRACE_FLAG);
	//if (!S9xLoadSnapshot (snapshot_filename))
//	    exit (1);
	CPU.Flags |= Flags;
    }

    //S9xGraphicsMode ();

    //sprintf (String, "\"%s\" %s: %s", Memory.ROMName, TITLE, VERSION);
    //S9xSetTitle (String);
    
//#ifdef JOYSTICK_SUPPORT
//    uint32 JoypadSkip = 0;
//#endif

    //InitTimer ();
    //if (!Settings.APUEnabled)  //?????????
  	//  S9xSetSoundMute (FALSE);

#if 0
    {
	FILE *fs = fopen ("test.bin", "r");
	if (fs)
	{
	    int bytes = fread (IAPU.RAM, 1, 1024 * 64, fs);
	    fclose (fs);
	    int len = 0;
	    char buffer [200];
	    for (int i = 0; i < bytes; i += len)
	    {
		len = S9xAPUOPrint (buffer, i);
		printf ("%s\n", buffer);
	    }
	}
    }
#endif

#if 0
    if (Settings.APUEnabled)
    {
	// Needed for Goal
	for (int z = 0; z < 0x2000; z++)
	{
	    APU_EXECUTE1();
	}
    }
#endif
/*
    while (1)
    {
	if (!Settings.Paused)
	    S9xMainLoop ();

	if (Settings.Paused
#ifdef DEBUGGER
	    || (CPU.Flags & DEBUG_MODE_FLAG)
#endif
           )
	{
	    S9xSetSoundMute (TRUE);
	}

#ifdef DEBUGGER
	if (CPU.Flags & DEBUG_MODE_FLAG)
	{
	    S9xDoDebug ();
	}
	else
#endif
	if (Settings.Paused)
	    S9xProcessEvents (TRUE);

#ifdef JOYSTICK_SUPPORT
	if (Settings.JoystickEnabled && (JoypadSkip++ & 1) == 0)
	    ReadJoysticks ();
#endif
	S9xProcessEvents (FALSE);
	
	if (!Settings.Paused
#ifdef DEBUGGER
	    && !(CPU.Flags & DEBUG_MODE_FLAG)
#endif	    
           )
	{
	    S9xSetSoundMute (FALSE);
	}
    }
*/
    return (0);
}

void S9xAutoSaveSRAM ()
{
    //Memory.SaveSRAM (S9xGetSRAMFilename ());
}

void S9xExit ()
{
    S9xDeinitDisplay ();
    //Memory.SaveSRAM (S9xGetSRAMFilename ());
    Memory.Deinit ();
    S9xDeinitAPU ();

#ifdef NETPLAY_SUPPORT
    if (Settings.NetPlay)
	S9xNetPlayDisconnect ();
#endif
    
    //exit (0);
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

const char *GetHomeDirectory ()
{
    return (".");
}

bool8 S9xOpenSnapshotFile (const char *fname, bool8 read_only, STREAM *file)
{
    if (read_only)
    {
	if ((*file = fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))!=-1)
	    return (TRUE);
    }
    else
    {
    if ((*file = fopen (fname,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,&err))!=-1)
	    return (TRUE);
    }
    return (FALSE);
}

void S9xCloseSnapshotFile (STREAM file)
{
    fclose (file,&err);
}

bool8 S9xInitUpdate ()
{
    return (TRUE);
}

bool8 S9xDeinitUpdate (int Width, int Height, bool8 sixteen_bit)
{
    S9xPutImage (Width, Height);

    return (TRUE);
}



uint32 S9xReadJoypad (int which1)
{
    if (which1 < NumControllers)
	return (0x80000000 | joypads [which1]);
    return (0);
}
/*

uint32 S9xReadJoypad (int which1)
{
//	return 0;
	/*
    if (which1 > 4)
        return 0;

    if (which1 == 0 && !Settings.NetPlay)
        S9xWinScanJoypads ();

#ifdef NETPLAY_SUPPORT
    if (Settings.NetPlay)
	return (S9xNPGetJoypad (which1));
#endif

    return (joypads [which1]);
}
*/



//int main(int argc, char **argv){
	//return 0;
//}
