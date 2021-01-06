
// fakes
#include "snes9x.h"
#include "memmap.h"
#include "ppu.h"
#include "dsp1.h"
#include "cpuexec.h"
#include "debug.h"
#include "apu.h"
#include "dma.h"
#include "sa1.h"
#include "cheats.h"
#include "srtc.h"
#include "sdd1.h"
#include "spc7110.h"
#include "obc1.h"

#include "soundux.h"
#include "spc7110.h"
#include "srtc.h"

struct ssGUI GGUI;

struct Colour{ ///מע באכהû
  BYTE red,blue,green;
};
static Colour FixedColours [256];
unsigned char  cpu_mmx=0;

//PALETTEENTRY 
Colour S9xPaletteEntry[256];
uint8	palette [0x10000]; //extern?

struct SSurface {
	unsigned char *Surface;
	unsigned int Pitch;
	unsigned int Width, Height;
};

void S9xSetWinPixelFormat ();
void S9xTextMode( void){}
void S9xGraphicsMode (){}

//void S9xExit( void)
//{
//	if(Settings.SPC7110)
//		(*CleanUp7110)();
//    SendMessage (GUI.hWnd, WM_COMMAND, ID_FILE_EXIT, 0);
//}

const char *S9xGetFilename (const char *e)
{
	return 0;
/*    static char filename [_MAX_PATH + 1];
    char drive [_MAX_DRIVE + 1];
    char dir [_MAX_DIR + 1];
    char fname [_MAX_FNAME + 1];
    char ext [_MAX_EXT + 1];

    if (strlen (GUI.FreezeFileDir))
    {
        _splitpath (Memory.ROMFilename, drive, dir, fname, ext);
        strcpy (filename, GUI.FreezeFileDir);
        strcat (filename, TEXT("\\"));
        strcat (filename, fname);
        strcat (filename, e);
    }
    else
    {
        _splitpath (Memory.ROMFilename, drive, dir, fname, ext);
        _makepath (filename, drive, dir, fname, e);
    }

    return (filename);*/
}

const char *S9xGetFilenameInc (const char *e)
{
	return 0;
	/*
    static char filename [_MAX_PATH + 1];
    char drive [_MAX_DRIVE + 1];
    char dir [_MAX_DIR + 1];
    char fname [_MAX_FNAME + 1];
    char ext [_MAX_EXT + 1];
    char *ptr;

    if (strlen (GUI.FreezeFileDir))
    {
        _splitpath (Memory.ROMFilename, drive, dir, fname, ext);
        strcpy (filename, GUI.FreezeFileDir);
        strcat (filename, TEXT("\\"));
        strcat (filename, fname);
        ptr = filename + strlen (filename);
        strcat (filename, TEXT("00/"));
        strcat (filename, e);
    }
    else
    {
        _splitpath (Memory.ROMFilename, drive, dir, fname, ext);
        strcat (fname, TEXT("00/"));
        _makepath (filename, drive, dir, fname, e);
        ptr = strstr (filename, TEXT("00/"));
    }

    do
    {
        if (++*(ptr + 2) > '9')
        {
            *(ptr + 2) = '0';
            if (++*(ptr + 1) > '9')
            {
                *(ptr + 1) = '0';
                if (++*ptr > '9')
                    break;
            }
        }
    } while (_access (filename, 0) == 0);

    return (filename);*/
}



//bool8 S9xOpenSnapshotFile( const char *fname, bool8 read_only, STREAM *file)
//{
	//return 0;
	/*
    char filename [_MAX_PATH + 1];
    char drive [_MAX_DRIVE + 1];
    char dir [_MAX_DIR + 1];
    char fn [_MAX_FNAME + 1];
    char ext [_MAX_EXT + 1];

    _splitpath( fname, drive, dir, fn, ext);
    _makepath( filename, drive, dir, fn, ext[0] == '\0' ? ".000" : ext);

    if (read_only)
    {
	if ((*file = OPEN_STREAM (filename, "rb")))
	    return (TRUE);
    }
    else
    {
	if ((*file = OPEN_STREAM (filename, "wb")))
	    return (TRUE);
        FILE *fs = fopen (filename, "rb");
        if (fs)
        {
            sprintf (String, "Freeze file \"%s\" exists but is read only",
                     filename);
            fclose (fs);
            S9xMessage (S9X_ERROR, S9X_FREEZE_FILE_NOT_FOUND, String);
        }
        else
        {
            sprintf (String, "Cannot create freeze file \"%s\". Directory is read-only or does not exist.", filename);
            
            S9xMessage (S9X_ERROR, S9X_FREEZE_FILE_NOT_FOUND, String);
        }
    }
    return (FALSE);*/
//}

//void S9xCloseSnapshotFile( STREAM file)
//{
//    CLOSE_STREAM (file);
//}

//void S9xMessage (int, int, const char *str)
//{
/*
#ifdef DEBUGGER
    static FILE *out = NULL;

    if (out == NULL)
        out = fopen ("out.txt", "w");

    fprintf (out, "%s\n", str);
#endif

    S9xSetInfoString (str);
	*/
//}

unsigned long _interval = 10;
long _buffernos = 4;
long _blocksize = 4400;
long _samplecount = 440;
long _maxsamplecount = 0;
long _buffersize = 0;
uint8 *SoundBuffer = NULL;
bool StartPlaying = false;
DWORD _lastblock = 0;
bool8 pending_setup = false;
long pending_rate = 0;
bool8 pending_16bit = false;
bool8 pending_stereo = false;

bool8 SetupSound (long rate, bool8 sixteen_bit, bool8 stereo)
{
  return 0;
/*
#ifdef FMOD_SUPPORT
    if (Settings.SoundDriver >= WIN_FMOD_DIRECT_SOUND_DRIVER)
    {
        so.mute_sound = TRUE;
        if (SoundBuffer)
        {
            SoundBuffer -= 32 * 1024;
            delete SoundBuffer;
            SoundBuffer = NULL;
        }
        
        _interval = 20;
        if (Settings.SoundBufferSize < 1)
            Settings.SoundBufferSize = 1;
        if (Settings.SoundBufferSize > 64)
            Settings.SoundBufferSize = 64;
        
        _buffernos = 4 * Settings.SoundBufferSize;
        int s = (rate * _interval *
                 (Settings.Stereo ? 2 : 1) * 
                 (Settings.SixteenBitSound ? 2 : 1)) / 1000;
        
        _blocksize = 64;
        while (_blocksize < s)
            _blocksize *= 2;
        
        _buffersize = _blocksize * _buffernos;
        _lastblock = 0;
        
        StartPlaying = false;
        
        so.playback_rate = Settings.SoundPlaybackRate;
        so.stereo = Settings.Stereo;
        so.sixteen_bit = Settings.SixteenBitSound;
        so.buffer_size = _blocksize;
        so.encoded = FALSE;
        
        if (DirectX.SetSoundMode ())
        {
            SoundBuffer = new uint8 [_blocksize * _buffernos + 1024 * 64];
            ZeroMemory (SoundBuffer, _blocksize * _buffernos + 1024 * 64);
            SoundBuffer += 32 * 1024;
            S9xSetPlaybackRate (so.playback_rate);
        }
        _samplecount = so.sixteen_bit ? _blocksize / 2 : _blocksize;
        _maxsamplecount = SOUND_BUFFER_SIZE;
        if (so.sixteen_bit)
            _maxsamplecount /= 2;
        if (so.stereo)
            _maxsamplecount /= 2;
        
        if (so.samples_mixed_so_far >= _maxsamplecount)
            so.samples_mixed_so_far = 0;
        so.mute_sound = FALSE;

        return (SoundBuffer != NULL);
    }
    else
    {
#endif
        pending_setup = TRUE;
        pending_rate = rate;
        pending_16bit = sixteen_bit;
        pending_stereo = stereo;
#ifdef FMOD_SUPPORT
    }
#endif
    return (TRUE);*/
}


//void S9xSetPalette( void)
//{
/*
    LPDIRECTDRAWPALETTE lpDDTemp;
    uint16 Brightness = IPPU.MaxBrightness * 140;

    // Only update the palette structures if needed
    if( GUI.ScreenDepth == 8)
    {
        if (Settings.SixteenBit)
        {
            for (int i = 0; i < 256; i++)
            {
                S9xPaletteEntry[i].peRed   = FixedColours [i].red;
                S9xPaletteEntry[i].peGreen = FixedColours [i].green;
                S9xPaletteEntry[i].peBlue  = FixedColours [i].blue;
            }
        }
        else
        {
            for (int i = 0; i < 256; i ++)
            {	
                S9xPaletteEntry[i].peRed   = (((PPU.CGDATA [i] >>  0) & 0x1F) * Brightness) >> 8;
                S9xPaletteEntry[i].peGreen = (((PPU.CGDATA [i] >>  5) & 0x1F) * Brightness) >> 8;
                S9xPaletteEntry[i].peBlue  = (((PPU.CGDATA [i] >> 10) & 0x1F) * Brightness) >> 8;
            }
        }

        DirectX.lpDDSPrimary2->GetPalette (&lpDDTemp);
        if (lpDDTemp != DirectX.lpDDPalette)
            DirectX.lpDDSPrimary2->SetPalette (DirectX.lpDDPalette);
        DirectX.lpDDPalette->SetEntries (0, 0, 256, S9xPaletteEntry);
    }*/
//}


//bool8 S9xInitUpdate (void)
//{
	//return 0;
	/*
    GFX.SubScreen = SubScreenBuffer;
    GFX.ZBuffer = ZBuffer;
    GFX.SubZBuffer = SubZBuffer;

    if (GUI.Scale <= 1 &&
        (GUI.Stretch || !GUI.FullScreen) &&
        !GUI.NeedDepthConvert &&
        ((DirectX.lpDDSOffScreen2 &&
          LockSurface2 (DirectX.lpDDSOffScreen2, &Dst))))
    {
        GFX.RealPitch = GFX.Pitch = GFX.Pitch2 = Dst.Pitch;
        GFX.Screen = Dst.Surface;
        DirectX.lpDDSOffScreen2->Unlock (Dst.Surface);
        locked_surface = TRUE;
    }
    else
    {
        locked_surface = FALSE;
#ifdef USE_OPENGL
        // For OpenGL lock the screen buffer size width to 512 (might be
        // overriden in S9xStartScreenRefresh) so the buffer can be uploaded
        // into texture memory with a single OpenGL call.
        if (Settings.OpenGLEnable)
            GFX.RealPitch = GFX.Pitch = GFX.Pitch2 = 512 * sizeof (uint16);
        else
#endif
        GFX.RealPitch = GFX.Pitch = GFX.Pitch2 = EXT_PITCH;
        GFX.Screen = ScreenBuffer;
    }
    GFX.Delta = (GFX.SubScreen - GFX.Screen) >> 1;
    if (Settings.SixteenBit)
    {
        GFX.PPL = GFX.Pitch >> 1;
        GFX.PPLx2 = GFX.Pitch;
        GFX.ZPitch = GFX.Pitch >> 1;
    }
    else
    {
        GFX.PPL = GFX.Pitch;
        GFX.PPLx2 = GFX.Pitch * 2;
        GFX.ZPitch = GFX.Pitch;
    }
    return (TRUE);*/
//}

//bool8 S9xDeinitUpdate (int Width, int Height, bool8 sixteen_bit)
//{
//	return 0;
	/*
	#define BLACK BUILD_PIXEL(0,0,0)
    SSurface Src;
    LPDIRECTDRAWSURFACE2 lpDDSurface2 = NULL;
    LPDIRECTDRAWSURFACE2 pDDSurface = NULL;
    bool PrimarySurfaceLockFailed = false;
    RECT srcRect;

#ifdef USE_DIRECTX3D
    HRESULT Render3DEnvironment ();

    Render3DEnvironment ();
    return true;
#endif

    Src.Width = Width;
	if(Height%SNES_HEIGHT)
	    Src.Height = Height;
	else
	{
		if(Height==SNES_HEIGHT)
			Src.Height=SNES_HEIGHT_EXTENDED;
		else Src.Height=SNES_HEIGHT_EXTENDED<<1;
	}
    Src.Pitch = GFX.Pitch;
    Src.Surface = GFX.Screen;

	// avi writing
	DoAVIVideoFrame(&Src, Width, Height, sixteen_bit);

	if(Settings.SixteenBit)
	{
		uint32 q;
		uint16* foo=(uint16*)(Src.Surface+(Height*Src.Pitch));
		for(q=0; q<(((Src.Height-Height)*Src.Pitch)>>1); q++)
		{
			foo[q]=BLACK;
		}
		Height = Src.Height;
	}
	else
	{
		uint32 q;
		uint8* foo=(uint8*)(Src.Surface+(Height*Src.Pitch));
		for(q=0; q<(((Src.Height-Height)*Src.Pitch)); q++)
		{
			foo[q]=BLACK;
		}
		Height = Src.Height;
	}

	GUI.ScreenCleared = true;

    SelectRenderMethod ();

    if (!VOODOO_MODE && !OPENGL_MODE)
    {
        if (locked_surface)
        {
            lpDDSurface2 = DirectX.lpDDSOffScreen2;
            PrimarySurfaceLockFailed = true;
            srcRect.top    = 0;
            srcRect.bottom = Height;
            srcRect.left   = 0;
            srcRect.right  = Width;
        }
        else
        {
            DDSCAPS caps;
            caps.dwCaps = DDSCAPS_BACKBUFFER;
            
            if (DirectX.lpDDSPrimary2->GetAttachedSurface (&caps, &pDDSurface) != DD_OK ||
                pDDSurface == NULL)
            {
                lpDDSurface2 = DirectX.lpDDSPrimary2;
            }
            else 
                lpDDSurface2 = pDDSurface;
            
            if (GUI.Stretch || GUI.Scale == 1 || !GUI.FullScreen ||
                !LockSurface2 (lpDDSurface2, &Dst))
            {
                lpDDSurface2 = DirectX.lpDDSOffScreen2;
                if (!LockSurface2 (lpDDSurface2, &Dst))
                    return (false);
                
                PrimarySurfaceLockFailed = true;
            }
            
            if (Settings.SixteenBit && GUI.Scale >= 3 && GUI.Scale <= 6)
            {
                // Clear the old areas of the SNES rendered image otherwise the
                // image processors might try to access some of the old rendered
                // data.
                static int LastWidth;
                static int LastHeight;
                
                if (Width < LastWidth)
                {
                    for (int i = 0; i < Height; i++)
                        memset (GFX.Screen + Width * 2 + i * GFX.Pitch, 0, 4);
                }
                if (Height < LastHeight)
                {
                    int ww = LastWidth > Width ? LastWidth : Width;
                    for (int i = Height; i < Height + 3; i++)
                        memset (GFX.Screen + i * GFX.Pitch, 0, ww * 2);
                }
                LastWidth = Width;
                LastHeight = Height;
            }
            if (GUI.NeedDepthConvert)
            {
                if (GUI.Scale <= 1)
                {
                    srcRect.left = srcRect.top = 0;
                    srcRect.right = Width;
                    srcRect.bottom = Height;
                    ConvertDepth (&Src, &Dst, &srcRect);
                }
                else
                {
                    SSurface tmp;
                    BYTE buf [MAX_SNES_WIDTH * MAX_SNES_HEIGHT * 4];
                    
                    tmp.Surface = buf;
                    tmp.Pitch = MAX_SNES_WIDTH * 4;
                    tmp.Width = MAX_SNES_WIDTH;
                    tmp.Height = MAX_SNES_HEIGHT;
                    RenderMethod (Src, tmp, &srcRect);
                    ConvertDepth (&tmp, &Dst, &srcRect);
                }
            }
            else RenderMethod (Src, Dst, &srcRect);
        }
        
        RECT lastRect = GUI.SizeHistory [GUI.FlipCounter % GUI.NumFlipFrames];
        if (PrimarySurfaceLockFailed)
        {
            POINT p;
            
            if (GUI.Stretch)
            {	
				p.x = p.y = 0;
				ClientToScreen (GUI.hWnd, &p);
				GetClientRect (GUI.hWnd, &dstRect);
				dstRect.bottom = int(double(dstRect.bottom) * double(239.0 / 240.0));
				OffsetRect(&dstRect, p.x, p.y);
            }
            else
            {
                GetClientRect (GUI.hWnd, &dstRect);
                int width = srcRect.right - srcRect.left;
                int height = srcRect.bottom - srcRect.top;
                
                if (GUI.Scale == 1)
                {
                    width = MAX_SNES_WIDTH;
                    if (height < 240)
                        height *= 2;
                }
                p.x = ((dstRect.right - dstRect.left) - width) >> 1;
 			p.y = ((dstRect.bottom - dstRect.top) - height) >> 1;
                ClientToScreen (GUI.hWnd, &p);
                
                dstRect.top = p.y;
                dstRect.left = p.x;
                dstRect.bottom = dstRect.top + height;
                dstRect.right  = dstRect.left + width;
            }
        }
        else
            dstRect = srcRect;
	
        lpDDSurface2->Unlock (Dst.Surface);	
        if (PrimarySurfaceLockFailed)
        {
            DDSCAPS caps;
            caps.dwCaps = DDSCAPS_BACKBUFFER;
            
            if (DirectX.lpDDSPrimary2->GetAttachedSurface (&caps, &pDDSurface) != DD_OK ||
                pDDSurface == NULL)
            {
                lpDDSurface2 = DirectX.lpDDSPrimary2;
            }
            else 
                lpDDSurface2 = pDDSurface;
            
            while (lpDDSurface2->Blt (&dstRect, DirectX.lpDDSOffScreen2, &srcRect, DDBLT_WAIT, NULL) == DDERR_SURFACELOST)
                lpDDSurface2->Restore ();
        }
        
        RECT rect;
        DDBLTFX fx;
        
        memset (&fx, 0, sizeof (fx));
        fx.dwSize = sizeof (fx);
        
        if (GUI.FlipCounter >= GUI.NumFlipFrames)
        {
            if (lastRect.top < dstRect.top)
            {
                rect.top = lastRect.top;
                rect.bottom = dstRect.top;
                rect.left = min(lastRect.left, dstRect.left);
                rect.right = max(lastRect.right, dstRect.right);
                lpDDSurface2->Blt (&rect, NULL, &rect,
                                   DDBLT_WAIT | DDBLT_COLORFILL, &fx);
            }
            if (lastRect.bottom > dstRect.bottom)
            {
                rect.left = min(lastRect.left, dstRect.left);
                rect.right = max(lastRect.right, dstRect.right);
                rect.top = dstRect.bottom;
                rect.bottom = lastRect.bottom;
                lpDDSurface2->Blt (&rect, NULL, &rect,
                                   DDBLT_WAIT | DDBLT_COLORFILL, &fx);
            }
            if (lastRect.left < dstRect.left)
            {
                rect.left = lastRect.left;
                rect.right = dstRect.left;
                rect.top = dstRect.top;
                rect.bottom = dstRect.bottom;
                lpDDSurface2->Blt (&rect, NULL, &rect,
                                   DDBLT_WAIT | DDBLT_COLORFILL, &fx);
            }
            if (lastRect.right > dstRect.right)
            {
                rect.left = dstRect.right;
                rect.right = lastRect.right;
                rect.top = dstRect.top;
                rect.bottom = dstRect.bottom;
                lpDDSurface2->Blt (&rect, NULL, &rect,
                                   DDBLT_WAIT | DDBLT_COLORFILL, &fx);
            }
        }
        
        DirectX.lpDDSPrimary2->Flip (NULL, DDFLIP_WAIT);
    }
    else
    {
        srcRect.top    = 0;
        srcRect.bottom = Height;
        srcRect.left   = 0;
        srcRect.right  = Width;
        dstRect = srcRect;
	RenderMethod (Src, Dst, &srcRect);
    }
    
    GUI.SizeHistory [GUI.FlipCounter % GUI.NumFlipFrames] = dstRect;
    GUI.FlipCounter++;

    return (true);*/
//}

BYTE  *ScreenBuf1=0, *ScreenBuf2=0, *SubScreenBuffer =0,
    *ZBuffer = 0,   *SubZBuffer=0;  //free
BYTE *ScreenBuffer;

void InitSnes9X( void)
{
#ifdef DEBUGGER
//    extern FILE *trace;

//    trace = fopen( "SNES9X.TRC", "wt");
    freopen( "SNES9X.OUT", "wt", stdout);
    freopen( "SNES9X.ERR", "wt", stderr);

//    CPU.Flags |= TRACE_FLAG;
//    APU.Flags |= TRACE_FLAG;
#endif

#ifdef GENERATE_OFFSETS_H
    offsets_h = fopen ("offsets.h", "wt");
    generate_offsets_h (0, NULL);
    fclose (offsets_h);
#endif

    Memory.Init();

    ScreenBuf1 = new BYTE [EXT_PITCH * EXT_HEIGHT];
    ScreenBuf2 = new BYTE [EXT_PITCH * EXT_HEIGHT];
    SubScreenBuffer = new BYTE [EXT_PITCH * EXT_HEIGHT];
    ZBuffer = new BYTE [EXT_WIDTH * EXT_HEIGHT];
    SubZBuffer = new BYTE [EXT_WIDTH * EXT_HEIGHT];

    ScreenBuffer = ScreenBuf1 + EXT_OFFSET;
    memset (ScreenBuf1, 0, EXT_PITCH * EXT_HEIGHT);
    memset (ScreenBuf2, 0, EXT_PITCH * EXT_HEIGHT);
    memset (SubScreenBuffer, 0, EXT_PITCH * EXT_HEIGHT);
    memset (ZBuffer, 0, EXT_WIDTH * EXT_HEIGHT);
    memset (SubZBuffer, 0, EXT_WIDTH * EXT_HEIGHT);

    GFX.Pitch = EXT_PITCH;
    GFX.RealPitch = EXT_PITCH;
    GFX.Screen = ScreenBuf1 + EXT_OFFSET;
    GFX.SubScreen = SubScreenBuffer;
    GFX.Delta = (GFX.SubScreen - GFX.Screen) >> 1;

    S9xSetWinPixelFormat ();
    S9xGraphicsInit();

    S9xInitAPU();
//    S9xInitSound (7, true, _blocksize);

//    so.playback_rate = Settings.SoundPlaybackRate;
    //so.stereo = Settings.Stereo;
    //so.sixteen_bit = Settings.SixteenBitSound;
    //so.buffer_size = _blocksize;

    // Sound options
    Settings.SoundBufferSize = Settings.SoundBufferSize;

#ifdef USE_GLIDE
    Settings.GlideEnable = FALSE;
#endif

//	S9xMovieInit ();

 //   for (int C = 0; C != 16; C ++)
 //       Joystick[C].Attached = joyGetDevCaps (JOYSTICKID1+C, &Joystick[C].Caps,
 //                                             sizeof( JOYCAPS)) == JOYERR_NOERROR;
}

void DeinitS9x()
{
	if(ScreenBuf1)
		delete [] ScreenBuf1;
	if(ScreenBuf2)
		delete [] ScreenBuf2;
	if(SubScreenBuffer)
		delete [] SubScreenBuffer;
	if(ZBuffer)
		delete [] ZBuffer;
	if(SubZBuffer)
		delete [] SubZBuffer;
	if (SoundBuffer)
	{
		SoundBuffer -= 32 * 1024;
		delete [] SoundBuffer;
		SoundBuffer = NULL;
	}
//	if(GUI.GunSight)
//		DestroyCursor(GUI.GunSight);//= LoadCursor (hInstance, MAKEINTRESOURCE (IDC_CURSOR_SCOPE));
    //if(GUI.Arrow)
//		DestroyCursor(GUI.Arrow);// = LoadCursor (NULL, IDC_ARROW);
//	if(GUI.Accelerators)
//		DestroyAcceleratorTable(GUI.Accelerators);// = LoadAccelerators (hInstance, MAKEINTRESOURCE (IDR_SNES9X_ACCELERATORS));

//	S9xMovieStop (TRUE);
}
int ffs (uint32 mask)
{
    int m = 0;
    if (mask)
    {
        while (!(mask & (1 << m)))
            m++;

        return (m);
    }

    return (0);
}

void S9xSetWinPixelFormat ()
{
    //extern int Init_2xSaI (uint32 BitFormat);

    S9xSetRenderPixelFormat (RGB565);
    //Init_2xSaI (565);
    GGUI.NeedDepthConvert = FALSE;

/*    if (VOODOO_MODE)
    {
        GUI.ScreenDepth = 16;
        GUI.RedShift = 11;
        GUI.GreenShift = 5;
        GUI.BlueShift = 0;
        Settings.SixteenBit = TRUE;
    }
    else
    if (OPENGL_MODE)
    {
        GUI.ScreenDepth = 16;
        GUI.RedShift = 11;
        GUI.GreenShift = 6;
        GUI.BlueShift = 1;
        Settings.SixteenBit = TRUE;
	S9xSetRenderPixelFormat (RGB5551);
//	Init_2xSaI (555);
    }
    else*/
    {
//        GUI.ScreenDepth = DirectX.DDPixelFormat.dwRGBBitCount;
        if (GGUI.ScreenDepth == 15)
            GGUI.ScreenDepth = 16;

//        GUI.RedShift = ffs (DirectX.DDPixelFormat.dwRBitMask);
//        GUI.GreenShift = ffs (DirectX.DDPixelFormat.dwGBitMask);
//        GUI.BlueShift = ffs (DirectX.DDPixelFormat.dwBBitMask);

/*        if((DirectX.DDPixelFormat.dwFlags&DDPF_RGB) != 0 &&
           GUI.ScreenDepth == 16 &&
           DirectX.DDPixelFormat.dwRBitMask == 0xF800 &&
           DirectX.DDPixelFormat.dwGBitMask == 0x07E0 &&
           DirectX.DDPixelFormat.dwBBitMask == 0x001F)
        {
            S9xSetRenderPixelFormat (RGB565);
            Init_2xSaI (565);
        }
        else
            if( (DirectX.DDPixelFormat.dwFlags&DDPF_RGB) != 0 &&
                GUI.ScreenDepth == 16 &&
                DirectX.DDPixelFormat.dwRBitMask == 0x7C00 &&
                DirectX.DDPixelFormat.dwGBitMask == 0x03E0 &&
                DirectX.DDPixelFormat.dwBBitMask == 0x001F)
            {
                S9xSetRenderPixelFormat (RGB555);
                Init_2xSaI (555);
            }
            else
                if((DirectX.DDPixelFormat.dwFlags&DDPF_RGB) != 0 &&
                   GUI.ScreenDepth == 16 &&
                   DirectX.DDPixelFormat.dwRBitMask == 0x001F &&
                   DirectX.DDPixelFormat.dwGBitMask == 0x07E0 &&
                   DirectX.DDPixelFormat.dwBBitMask == 0xF800)
                {
                    S9xSetRenderPixelFormat (BGR565);
                    Init_2xSaI (565);
                }
                else
                    if( (DirectX.DDPixelFormat.dwFlags&DDPF_RGB) != 0 &&
                        GUI.ScreenDepth == 16 &&
                        DirectX.DDPixelFormat.dwRBitMask == 0x001F &&
                        DirectX.DDPixelFormat.dwGBitMask == 0x03E0 &&
                        DirectX.DDPixelFormat.dwBBitMask == 0x7C00)
                    {
                        S9xSetRenderPixelFormat (BGR555);
                        Init_2xSaI (555);
                    }
                    else
                        if (DirectX.DDPixelFormat.dwRGBBitCount == 8 ||
                            DirectX.DDPixelFormat.dwRGBBitCount == 24 ||
                            DirectX.DDPixelFormat.dwRGBBitCount == 32)
                        {
                            S9xSetRenderPixelFormat (RGB565);
                            Init_2xSaI (565);
                        }
  */      
        if (((GGUI.ScreenDepth == 8 && Settings.SixteenBit) ||
             (GGUI.ScreenDepth == 16 && !Settings.SixteenBit) ||
             GGUI.ScreenDepth == 24 || GGUI.ScreenDepth == 32))
            GGUI.NeedDepthConvert = TRUE;
        
        if (Settings.SixteenBit && 
            (GGUI.ScreenDepth == 24 || GGUI.ScreenDepth == 32))
        {
            GGUI.RedShift += 3;
            GGUI.GreenShift += 3;
            GGUI.BlueShift += 3;
        }
    }

    int l = 0;
    int i;

    for (i = 0; i < 6; i++)
    {
	int r = (i * 31) / (6 - 1);
	for (int j = 0; j < 6; j++)
	{
	    int g = (j * 31) / (6 - 1);
	    for (int k = 0; k < 6; k++)
	    { 
		int b = (k * 31) / (6 - 1);

		FixedColours [l].red = r << 3;
		FixedColours [l].green = g << 3;
		FixedColours [l++].blue = b << 3;
	    }
	}
    }

    int *color_diff = new int [0x10000];
    int diffr, diffg, diffb, maxdiff = 0, won = 0, lost;
    int r, d = 8;
    for (r = 0; r <= (int) MAX_RED; r++)
    {
	int cr, g, q;
      
	int k = 6 - 1;
	cr = (r * k) / MAX_RED;
	q  = (r * k) % MAX_RED;
	if (q > d && cr < k) 
	    cr++;
	diffr = abs (cr * k - r);
	for (g = 0; g <= (int) MAX_GREEN; g++)
	{
	    int cg, b;
	  
	    k  = 6 - 1;
	    cg = (g * k) / MAX_GREEN;
	    q  = (g * k) % MAX_GREEN;
	    if(q > d && cg < k)
		cg++;
	    diffg = abs (cg * k - g);
	    for (b = 0; b <= (int) MAX_BLUE; b++) 
	    {
		int cb;
		int rgb = BUILD_PIXEL2(r, g, b);

		k  = 6 - 1;
		cb = (b * k) / MAX_BLUE;
		q  = (b * k) % MAX_BLUE;
		if (q > d && cb < k)
		    cb++;
		diffb = abs (cb * k - b);
		palette[rgb] = (cr * 6 + cg) * 6 + cb;
		color_diff[rgb] = diffr + diffg + diffb;
		if (color_diff[rgb] > maxdiff)
		    maxdiff = color_diff[rgb];
	    }
	}
    }

    while (maxdiff > 0 && l < 256)
    {
	int newmaxdiff = 0;
	lost = 0; won++;
	for (r = MAX_RED; r >= 0; r--)
	{
	    int g;
      
	    for (g = MAX_GREEN; g >= 0; g--)
	    {
		int b;
	  
		for (b = MAX_BLUE; b >= 0; b--) 
		{
		    int rgb = BUILD_PIXEL2(r, g, b);

		    if (color_diff[rgb] == maxdiff)
		    {
			if (l >= 256)
			    lost++;
			else
			{
			    FixedColours [l].red = r << 3;
			    FixedColours [l].green = g << 3;
			    FixedColours [l].blue = b << 3;
			    palette [rgb] = l++;
			}
			color_diff[rgb] = 0;
		    }
		    else
			if (color_diff[rgb] > newmaxdiff)
			    newmaxdiff = color_diff[rgb];
		    
		}
	    }
	}
	maxdiff = newmaxdiff;
    }
    delete [] color_diff;
}



void Convert8To24 (SSurface *src, SSurface *dst, RRECT *srect)
{
    uint32 brightness = IPPU.MaxBrightness >> 1;
    uint32 conv [256];
    int height = srect->bottom - srect->top;
    int width = srect->right - srect->left;
    int offset1 = srect->top * src->Pitch + srect->left;
    int offset2 = ((dst->Height - height) >> 1) * dst->Pitch +
        ((dst->Width - width) >> 1) * sizeof (uint32);

    for (int p = 0; p < 256; p++)
    {
        uint32 pixel = PPU.CGDATA [p];
        conv [p] = (((pixel & 0x1f) * brightness) << GGUI.RedShift) |
                   ((((pixel >> 5) & 0x1f) * brightness) << GGUI.GreenShift) |
                   ((((pixel >> 10) & 0x1f) * brightness) << GGUI.BlueShift);
    }
    for (register int y = 0; y < height; y++)
    {
        register uint8 *s = ((uint8 *) src->Surface + y * src->Pitch + offset1);
        register uint32 *d = (uint32 *) ((uint8 *) dst->Surface + 
                                         y * dst->Pitch + offset2);
        for (register int x = 0; x < width; x++)
            *d++ = conv [PPU.CGDATA [*s++]];
    }
}

void Convert16To24 (SSurface *src, SSurface *dst, RRECT *srect)
{
    int height = srect->bottom - srect->top;
    int width = srect->right - srect->left;
    int offset1 = srect->top * src->Pitch + srect->left * 2;
    int offset2 = ((dst->Height - height) >> 1) * dst->Pitch +
        ((dst->Width - width) >> 1) * sizeof (uint32);

    for (register int y = 0; y < height; y++)
    {
        register uint16 *s = (uint16 *) ((uint8 *) src->Surface + y * src->Pitch + offset1);
        register uint32 *d = (uint32 *) ((uint8 *) dst->Surface + 
                                         y * dst->Pitch + offset2);
        for (register int x = 0; x < width; x++)
        {
            uint32 pixel = *s++;
            *d++ = (((pixel >> 11) & 0x1f) << GGUI.RedShift) |
                   (((pixel >> 6) & 0x1f) << GGUI.GreenShift) |
                   ((pixel & 0x1f) << GGUI.BlueShift);
        }
    }
}

void Convert8To24Packed (SSurface *src, SSurface *dst, RRECT *srect)
{
    uint32 brightness = IPPU.MaxBrightness >> 1;
    uint8 levels [32];
    int height = srect->bottom - srect->top;
    int width = srect->right - srect->left;
    int offset1 = srect->top * src->Pitch + srect->left;
    int offset2 = ((dst->Height - height) >> 1) * dst->Pitch +
        ((dst->Width - width) >> 1) * 3;

    for (int l = 0; l < 32; l++)
	levels [l] = l * brightness;
	
    for (register int y = 0; y < height; y++)
    {
        register uint8 *s = ((uint8 *) src->Surface + y * src->Pitch + offset1);
        register uint8 *d = ((uint8 *) dst->Surface + y * dst->Pitch + offset2);
        
#ifdef LSB_FIRST
        if (GGUI.RedShift < GGUI.BlueShift)
#else	    
	if (GGUI.RedShift > GGUI.BlueShift)
#endif
        {
            // Order is RGB
            for (register int x = 0; x < width; x++)
            {
                uint16 pixel = PPU.CGDATA [*s++];
                *(d + 0) = levels [(pixel & 0x1f)];
                *(d + 1) = levels [((pixel >> 5) & 0x1f)];
                *(d + 2) = levels [((pixel >> 10) & 0x1f)];
                d += 3;
            }
        }
        else
        {
            // Order is BGR
            for (register int x = 0; x < width; x++)
            {
                uint16 pixel = PPU.CGDATA [*s++];
                *(d + 0) = levels [((pixel >> 10) & 0x1f)];
                *(d + 1) = levels [((pixel >> 5) & 0x1f)];
                *(d + 2) = levels [(pixel & 0x1f)];
                d += 3;
            }
        }
    }
}

void Convert16To24Packed (SSurface *src, SSurface *dst, RRECT *srect)
{
    int height = srect->bottom - srect->top;
    int width = srect->right - srect->left;
    int offset1 = srect->top * src->Pitch + srect->left * 2;
    int offset2 = ((dst->Height - height) >> 1) * dst->Pitch +
        ((dst->Width - width) >> 1) * 3;

    for (register int y = 0; y < height; y++)
    {
        register uint16 *s = (uint16 *) ((uint8 *) src->Surface + y * src->Pitch + offset1);
        register uint8 *d = ((uint8 *) dst->Surface + y * dst->Pitch + offset2);
        
#ifdef LSB_FIRST
        if (GGUI.RedShift < GGUI.BlueShift)
#else	    
	if (GUI.RedShift > GUI.BlueShift)
#endif
        {
            // Order is RGB
            for (register int x = 0; x < width; x++)
            {
                uint32 pixel = *s++;
                *(d + 0) = (pixel >> (11 - 3)) & 0xf8;
                *(d + 1) = (pixel >> (6 - 3)) & 0xf8;
                *(d + 2) = (pixel & 0x1f) << 3;
                d += 3;
            }
        }
        else
        {
            // Order is BGR
            for (register int x = 0; x < width; x++)
            {
                uint32 pixel = *s++;
                *(d + 0) = (pixel & 0x1f) << 3;
                *(d + 1) = (pixel >> (6 - 3)) & 0xf8;
                *(d + 2) = (pixel >> (11 - 3)) & 0xf8;
                d += 3;
            }
        }
    }
}

void Convert16To8 (SSurface *src, SSurface *dst, RRECT *srect)
{
    int height = srect->bottom - srect->top;
    int width = srect->right - srect->left;
    int offset1 = srect->top * src->Pitch + srect->left * 2;
    int offset2 = ((dst->Height - height) >> 1) * dst->Pitch +
        ((dst->Width - width) >> 1);

    for (register int y = 0; y < height; y++)
    {
        register uint16 *s = (uint16 *) ((uint8 *) src->Surface + y * src->Pitch + offset1);
        register uint8 *d = ((uint8 *) dst->Surface + y * dst->Pitch + offset2);

        for (register int x = 0; x < width; x++)
            *d++ = palette [*s++];
    }
}

void Convert8To16 (SSurface *src, SSurface *dst, RRECT *srect)
{
    uint32 levels [32];
    uint32 conv [256];
    int height = srect->bottom - srect->top;
    int width = srect->right - srect->left;
    int offset1 = srect->top * src->Pitch + srect->left;
    int offset2 = ((dst->Height - height) >> 1) * dst->Pitch +
        ((dst->Width - width) >> 1) * sizeof (uint16);

    for (int l = 0; l < 32; l++)
	levels [l] = (l * IPPU.MaxBrightness) >> 4;
	
    for (int p = 0; p < 256; p++)
    {
        uint32 pixel = PPU.CGDATA [p];
        
        conv [p] = (levels [pixel & 0x1f] << GGUI.RedShift) |
                   (levels [(pixel >> 5) & 0x1f] << GGUI.GreenShift) |
                   (levels [(pixel >> 10) & 0x1f] << GGUI.BlueShift);
    }
    for (register int y = 0; y < height; y++)
    {
        register uint8 *s = ((uint8 *) src->Surface + y * src->Pitch + offset1);
        register uint16 *d = (uint16 *) ((uint8 *) dst->Surface + 
                                         y * dst->Pitch + offset2);
        for (register int x = 0; x < width; x += 2)
        {
            *(uint32 *) d = conv [*s] | (conv [*(s + 1)] << 16);
            s += 2;
            d += 2;
        }
    }
}

void ConvertDepth (SSurface *src, SSurface *dst, RRECT *srect)
{
    if (Settings.SixteenBit)
    {
        // SNES image has been rendered in 16-bit, RGB565 format
        switch (GGUI.ScreenDepth)
        {
            case 8:
                Convert16To8 (src, dst, srect);
                break;
            case 15:
            case 16:
                break;
            case 24:
                Convert16To24Packed (src, dst, srect);
                break;
            case 32:
                Convert16To24 (src, dst, srect);
                break;
        }
    }
    else
    {
        // SNES image has been rendered only in 8-bits
        switch (GGUI.ScreenDepth)
        {
            case 8:
                break;
            case 15:
            case 16:
                Convert8To16 (src, dst, srect);
                break;
            case 24:
                Convert8To24Packed (src, dst, srect);
                break;
            case 32:
                Convert8To24 (src, dst, srect);
                break;
        }
    }
    srect->left = (dst->Width - src->Width) >> 1;
    srect->right = srect->left + src->Width;
    srect->top = (dst->Height - src->Height) >> 1;
    srect->bottom = srect->top + src->Height;
}

//void S9xAutoSaveSRAM ()
//{
    //Memory.SaveSRAM (S9xGetFilename (".srm"));
//}

void S9xSetPause (uint32 mask)
{
    Settings.ForcedPause |= mask;
}

void S9xClearPause (uint32 mask)
{
    Settings.ForcedPause &= ~mask;
    if (!Settings.ForcedPause)
    {
        // Wake up the main loop thread just if its blocked in a GetMessage
        // call.
//        PostMessage (GUI.hWnd, WM_NULL, 0, 0);
    }
}

static int S9xCompareSDD1IndexEntries (const void *p1, const void *p2)
{
    return (*(uint32 *) p1 - *(uint32 *) p2);
}


const char *S9xBasename (const char *f)
{
    const char *p;
    if ((p = strrchr (f, '/')) != NULL || (p = strrchr (f, '\\')) != NULL)
	return (p + 1);

#ifdef __DJGPP
    if (p = strrchr (f, SLASH_CHAR))
	return (p + 1);
#endif

    return (f);
}

//}


//fakes

void SetInfoDlgColor(unsigned char a,unsigned char b,unsigned char c){}
void  FxCacheWriteAccess(unsigned short a){}
void fx_updateRamBank(unsigned char a){}
void  fx_dirtySCBR(void){}
void  FxFlushCache(void){}

int FxEmulate(unsigned int a){ return 0;}
unsigned char S9xOpenSoundDevice(int a,unsigned char b,int c){ return 0;}

//extern "C" void S9xParseArg (char **argv, int &i, int argc){}
//extern "C" void S9xExtraUsage (){}

bool8 S9xReadSuperScopePosition (int &x, int &y, uint32 &buttons){ return 0;}


//void main(){}

void JustifierButtons(unsigned int &a){}
bool JustifierOffscreen(void){ return 0;}

//srtc
void  S9xResetSRTC(void){}
void  S9xHardResetSRTC(void){}
//struct SRTC_DATA  rtc;
void  S9xSRTCPostLoadState(void){}
void  S9xSRTCPreSaveState(void){}
void  S9xSetSRTC(unsigned char a,unsigned short aa){}
unsigned char  S9xGetSRTC(unsigned short a){ return 0;}

SRTC_DATA           rtc;

/////////soundux

void S9xSetSoundVolume (int channel, short volume_left, short volume_right){}
void S9xSetSoundFrequency (int channel, int hertz){}
void S9xSetSoundHertz (int channel, int hertz){}
void S9xSetSoundType (int channel, int type_of_sound){}
void S9xSetMasterVolume (short master_volume_left, short master_volume_right){}
void S9xSetEchoVolume (short echo_volume_left, short echo_volume_right){}
void S9xSetSoundControl (int sound_switch){}
bool8 S9xSetSoundMute (bool8 mute){ return 0;}
void S9xSetEnvelopeHeight (int channel, int height){}
void S9xSetSoundADSR (int channel, int attack, int decay, int sustain,
                      int sustain_level, int release){}
void S9xSetSoundKeyOff (int channel){}
void S9xSetSoundDecayMode (int channel){}
void S9xSetSoundAttachMode (int channel){}
void S9xSoundStartEnvelope (Channel *a){}
void S9xSetSoundSample (int channel, uint16 sample_number){}
void S9xSetEchoFeedback (int echo_feedback){}
void S9xSetEchoEnable (uint8 byte){}
void S9xSetEchoDelay (int byte){}
void S9xSetEchoWriteEnable (uint8 byte){}
void S9xSetFilterCoefficient (int tap, int value){}
void S9xSetFrequencyModulationEnable (uint8 byte){}
void S9xSetEnvelopeRate (int channel, unsigned long rate, int direction,
                         int target){}
bool8 S9xSetSoundMode (int channel, int mode){ return 0;}
int S9xGetEnvelopeHeight (int channel){ return 0;}
void S9xResetSound (bool8 full){}
void S9xFixSoundAfterSnapshotLoad (){}
void S9xPlaybackSoundSetting (int channel){}
void S9xPlaySample (int channel){}
//void S9xFixEnvelope (int channel, uint8 gain, uint8 adsr1, uint8 adsr2){}
void S9xStartSample (int channel){}

void S9xMixSamples (uint8 *buffer, int sample_count){}
void S9xMixSamplesO (uint8 *buffer, int sample_count, int byte_offset){}
//bool8 S9xOpenSoundDevice (int, bool8, int){ return 0;}
void S9xSetPlaybackRate (uint32 rate){}

void S9xInitSound(){}

//
bool8 S9xLoadSnapshot (const char *filename){return 0;}
bool8 S9xSPCDump (const char *filename){ return 0;}

void ComputeClipWindows(void){}

void S9xMovieUpdate (){}


/////////////cheats
void S9xInitCheatData (){}
//const char *S9xGameGenieToRaw (const char *code, uint32 *address, uint8 *byte){ return 0;}
//const char *S9xProActionReplayToRaw (const char *code, uint32 *address, uint8 *byte){return 0;}
//char const *S9xGoldFingerToRaw (const char *code, uint32 *address, bool8 *sram,
//                                uint8 *num_bytes, uint8 bytes[3]){return 0;}

char const * S9xGoldFingerToRaw(char const *a,unsigned int &b,unsigned char &c,unsigned char &d,unsigned char * const e){ return 0;}
char const * S9xProActionReplayToRaw(char const *a,unsigned int &b,unsigned char &v){ return 0;}
char const * S9xGameGenieToRaw(char const *a,unsigned int &b,unsigned char &c){ return 0;}

void S9xApplyCheats (){}
void S9xApplyCheat (uint32 which1){}
void S9xRemoveCheats (){}
void S9xRemoveCheat (uint32 which1){}
void S9xEnableCheat (uint32 which1){}
void S9xDisableCheat (uint32 which1){}
void S9xAddCheat (bool8 enable, bool8 save_current_value, uint32 address,
                  uint8 byte){}
void S9xDeleteCheats (){}
void S9xDeleteCheat (uint32 which1){}
bool8 S9xLoadCheatFile (const char *filename){return 0;}
bool8 S9xSaveCheatFile (const char *filename){return 0;}

void S9xStartCheatSearch (struct SCheatData *a){}
void S9xSearchForChange (struct SCheatData *a, S9xCheatComparisonType cmp,
                         S9xCheatDataSize size, bool8 is_signed, bool8 update){}
void S9xSearchForValue (struct SCheatData *a, S9xCheatComparisonType cmp,
                        S9xCheatDataSize size, uint32 value,
                        bool8 is_signed, bool8 update){}
void S9xOutputCheatSearchResults (struct SCheatData *a){}


unsigned char S9xDoScreenshot(int a,int b){return 0;}


//C4
void  S9xInitC4(void){}
unsigned char S9xGetC4(unsigned short a){ return 0;}
void S9xSetC4(unsigned char a,unsigned short b){}

///////dsp1-n
/*
void  DSP1SetByte(uint8 byte, uint16 address){}
uint8 DSP1GetByte(uint16 address){ return 0;}

void  DSP2SetByte(uint8 byte, uint16 address){}
uint8 DSP2GetByte(uint16 address){ return 0;}

void  DSP3SetByte(uint8 byte, uint16 address){}
uint8 DSP3GetByte(uint16 address){ return 0;}
void  DSP3_Reset(){}

void  DSP4SetByte(uint8 byte, uint16 address){}
uint8 DSP4GetByte(uint16 address){ return 0;}


void S9xResetDSP1 (){}
uint8 S9xGetDSP (uint16 Address){ return 0;}
void S9xSetDSP (uint8 Byte, uint16 Address){}

unsigned char (__cdecl* GetDSP)(unsigned short a)=S9xGetDSP;
void (__cdecl* SetDSP)(unsigned char a,unsigned short b)=S9xSetDSP;
*/

//obc
uint8 GetOBC1 (uint16 Address){ return 0;}
void SetOBC1 (uint8 Byte, uint16 Address){}
void ResetOBC1(){}

uint8 *GetBasePointerOBC1(uint32 Address){ return 0;}
uint8 *GetMemPointerOBC1(uint32 Address){ return 0;}


//spc7110

void (* CleanUp7110)(void);
void  Do7110Logging(void){}
unsigned short  cacheMegs=0;
void  SPC7110Grab(char *a){}
void  SPC7110Open(char *a){}
void  SPC7110Load(char *a){}

void (* LoadUp7110)(char *a);

struct SPC7110EmuVars  s7r;
struct SPC7110RTC  rtc_f9;

void  S9xSpc7110Reset(void){}

unsigned char  S9xSaveSPC7110RTC(struct SPC7110RTC *a){ return 0;}
unsigned char  S9xLoadSPC7110RTC(struct SPC7110RTC *a){ return 0;}

void  S9xSpc7110Init(void){}
void  S9xSetSPC7110(unsigned char a,unsigned short v){}
void  S9xUpdateRTC(void){}

uint8 S9xGetSPC7110(uint16 Address){ return 0;}
uint8 S9xGetSPC7110Byte(uint32 Address){ return 0;}

uint8* Get7110BasePtr(uint32 Address){ return 0;}

//seta
uint8 S9xGetSetaDSP(uint32 Address){ return 0;}
void S9xSetSetaDSP(uint8 Byte, uint32 Address){}

uint8 S9xGetST010(uint32 Address){return 0;}
void S9xSetST010(uint32 Address, uint8 Byte){}

uint8 S9xGetST018(uint32 Address){ return 0;}
uint8 S9xGetST011(uint32 Address){ return 0;}

void S9xSetST018(uint32 Address, uint8 Byte){}
void S9xSetST011(uint32 Address, uint8 Byte){}

void S9xSetST018(unsigned char a, unsigned int b){}
unsigned char (* GetSETA)(unsigned int a);
void (* SetSETA)(unsigned int a, unsigned char b);

//////////sdd1.c
void S9xResetSDD1(void){}
void S9xSDD1LoadLoggedData(void){}

void S9xSDD1SaveLoggedData(void){}
void S9xSetSDD1MemoryMap(unsigned int a,unsigned int b){}

void S9xSDD1PostLoadState(void){}


//sa1
void S9xSA1Init(void){}
void S9xSA1MainLoop(void){}

void S9xSetSA1(unsigned char a,unsigned int b){}
unsigned char S9xGetSA1(unsigned int a){ return 0;}


int isdigit(int a){
	return (a>='0' && a<='9');
}

int isalpha(int a){
     if(a>='a' && a<='z') return 1;
     if(a>='A' && a<='Z') return 1;
	return 0;
}
