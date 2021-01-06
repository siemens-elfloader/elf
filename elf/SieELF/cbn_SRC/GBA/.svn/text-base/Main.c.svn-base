
//fakes.c
//в util fakes fgets()!!!!!!!!!!!!!!!!!!!!!!!!1
//исправления в gbainline могут быть ошибочными!

#include "GBA.h"
//#include <string.h>
#define IMAGE_GBA 0

fmapst fmap;
unsigned int mtemp; //tmp
int res=0; //keys
int mode=0;

char *Title="GBA 0.2 (c)bn";
const char *errors[]={ //строки ошибок для кодов возврата
  0,
  "Щелкните на .gba файл!\0",
  "Ошибка открытия файла\0",
  "Файл пуст\0",
  "Нет памяти для Delta\0",
  "Нет памяти для workRAM\0",//5
  "Нет памяти для bios\0",
  "Нет памяти для internalRAM\0",
  "Нет памяти для paletteRAM\0",
  "Нет памяти для vram\0",
  "Нет памяти для oam\0",
  "Нет памяти для pix\0",
  "Нет памяти для ioMem\0"
  "Неизвестная ошибка"
};
int ROMSIZE=0x2000000; //добавил

extern unsigned int randseed;
//const void *ZEROSTART=&randseed; 
//const int ZEROSIZE=0x1d42d;

extern int width,height;

volatile int running=0, runstop=0;
int c65=0;
int flags=0;

#define fload 1
#define fsave 2

extern short *screen;//[132*176];
extern int screensize;
short *scr=0;//[256*224];
extern unsigned char EL71, C65;
void sstop();

  //GB fakes!
int  gbColorOption=0;
int  gbEmulatorType=0;

int  gbBorderAutomatic=0;
int  gbBorderOn=0;
int  gbFrameSkip=0;
int  gbBorderRowSkip=0;
int  gbBorderColumnSkip=0;

int  gbBorderLineSkip=0;

void gbReset(void){}
bool gbUpdateSizes(void){ return 0;}

unsigned char *  gbRom=0;

int  gbRomSize=0;

struct EmulatedSystem  GBSystem;
bool gbLoadRom(char const *a){ return 0;}
void gbSgbRenderBorder(void){}

//cheats
void cheatsWriteMemory(unsigned int *a,unsigned int b,unsigned int c){}
void cheatsSaveGame(int a){}

void cheatsReadGame(int a){}
void cheatsWriteHalfWord(unsigned short *a,unsigned short b,unsigned short c){}

void cheatsWriteByte(unsigned char *a,unsigned char b){}
int  cheatsCheckKeys(unsigned int a,unsigned int b){ return 0;}

//sound

void soundReset(void){}

#define USE_TICKS_AS  380
int SOUND_CLOCK_TICKS = 2 * USE_TICKS_AS;

void soundTick(void){}
void soundTimerOverflow(int a){}
int  soundTicks=0;
int  soundVolume=0;

bool  soundReverse=0;

bool  soundLowPass=0;
bool  soundEcho=0;

void soundDisable(int a){}

void soundEnable(int a){}

bool  soundOffFlag=0;
int  soundQuality=0;
void soundPause(void){}

void soundResume(void){}

void soundShutdown(void){}




int  soundBufferLen=1000;

int  soundBufferTotalLen=1000;

bool soundInit(void){ return 0;}
/////////////

void soundEvent(u32 address, u8 data){}
//void soundEvent(u32 address, u16 data){}

void soundChannel1(){}
void soundChannel2(){}
void soundChannel3(){}
void soundChannel4(){}

void soundDirectSoundA(){}
void soundDirectSoundATimer(){}
void soundDirectSoundB(){}
void soundDirectSoundBTimer(){}

void soundMix(){}
int soundGetEnable(){ return 0;}
void soundReadGame(gzFile gzFile1, int version){}
void soundSaveGame(gzFile gzFile1){}
void soundSetQuality(int quality){}

//remote

void remoteCleanUp(void){}
void remoteInit(void){}
void remoteSetPort(int a){}

void remoteSetProtocol(int a){}
void remoteOutput(char *a ,unsigned int b){}
void remoteStubSignal(int a,int b){}
void remoteStubMain(void){}

//text
void drawTextTransp(unsigned char *a,int b,int bb,int bbb,char const *aa){}
void drawText(unsigned char *a,int aa,int b,int bb,char const *bbb){}


//agbprint
void agbPrintFlush(void){}
bool agbPrintWrite(unsigned int a,unsigned short b){ return 0;}
void agbPrintEnable(bool a){}

//addmame
void AdMame2x32(unsigned char *a,unsigned int a2,unsigned char *a3,unsigned char *a4,unsigned int a5,int a6,int a7){}
void AdMame2x(unsigned char *a9,unsigned int a6,unsigned char *a5,unsigned char *a4,unsigned int a3,int a2,int a1){}

//bool cpu_mmx=0;
unsigned int *  qRGB_COLOR_MASK=0;

//sdl
void winlog(const char *a, ...){}








unsigned short *  soundFinalWave=0;

//////////////////MAIN/////////////////
///////////////////////////////////////

//int sdlFlashSize=0, failed;
//int cartridgeType=0, type=0;
extern bool soundEcho;
extern bool soundLowPass;
extern bool soundReverse;


extern int Init_2xSaI(u32);
extern void _2xSaI(u8*,u32,u8*,u8*,u32,int,int);
extern void _2xSaI32(u8*,u32,u8*,u8*,u32,int,int);  
extern void Super2xSaI(u8*,u32,u8*,u8*,u32,int,int);
extern void Super2xSaI32(u8*,u32,u8*,u8*,u32,int,int);
extern void SuperEagle(u8*,u32,u8*,u8*,u32,int,int);
extern void SuperEagle32(u8*,u32,u8*,u8*,u32,int,int);  
extern void Pixelate(u8*,u32,u8*,u8*,u32,int,int);
extern void Pixelate32(u8*,u32,u8*,u8*,u32,int,int);
extern void MotionBlur(u8*,u32,u8*,u8*,u32,int,int);
extern void MotionBlur32(u8*,u32,u8*,u8*,u32,int,int);
extern void AdMame2x(u8*,u32,u8*,u8*,u32,int,int);
extern void AdMame2x32(u8*,u32,u8*,u8*,u32,int,int);
extern void Simple2x(u8*,u32,u8*,u8*,u32,int,int);
extern void Simple2x32(u8*,u32,u8*,u8*,u32,int,int);
extern void Bilinear(u8*,u32,u8*,u8*,u32,int,int);
extern void Bilinear32(u8*,u32,u8*,u8*,u32,int,int);
extern void BilinearPlus(u8*,u32,u8*,u8*,u32,int,int);
extern void BilinearPlus32(u8*,u32,u8*,u8*,u32,int,int);
extern void Scanlines(u8*,u32,u8*,u8*,u32,int,int);
extern void Scanlines32(u8*,u32,u8*,u8*,u32,int,int);
extern void ScanlinesTV(u8*,u32,u8*,u8*,u32,int,int);
extern void ScanlinesTV32(u8*,u32,u8*,u8*,u32,int,int);
extern void hq2x(u8*,u32,u8*,u8*,u32,int,int);
extern void hq2x32(u8*,u32,u8*,u8*,u32,int,int);
extern void lq2x(u8*,u32,u8*,u8*,u32,int,int);
extern void lq2x32(u8*,u32,u8*,u8*,u32,int,int);

extern void SmartIB(u8*,u32,int,int);
extern void SmartIB32(u8*,u32,int,int);
extern void MotionBlurIB(u8*,u32,int,int);
extern void MotionBlurIB32(u8*,u32,int,int);


void Quit_Overlay(void);


extern void remoteInit();
extern void remoteCleanUp();
extern void remoteStubMain();
extern void remoteStubSignal(int,int);
extern void remoteOutput(char *, u32);
extern void remoteSetProtocol(int);
extern void remoteSetPort(int);
extern void debuggerOutput(char *, u32);

extern void CPUUpdateRenderBuffers(bool);

struct EmulatedSystem emulator = {
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  false,
  0
};

//SDL_Surface *surface = NULL;
//SDL_Overlay *overlay = NULL;
//SDL_Rect overlay_rect;

int systemSpeed = 0;
int systemRedShift = 0;
int systemBlueShift = 0;
int systemGreenShift = 0;
int systemColorDepth = 0;
int systemDebug = 0;
int systemVerbose = 0;
int systemFrameSkip = 0;
int systemSaveUpdateCounter = SYSTEM_SAVE_NOT_UPDATED;

int srcPitch = 0;
int srcWidth = 0;
int srcHeight = 0;
int destWidth = 0;
int destHeight = 0;

int sensorX = 2047;
int sensorY = 2047;

int filter = 0;
u8 *delta = NULL;

int sdlPrintUsage = 0;
int disableMMX = 0;

int cartridgeType = 3;
int sizeOption = 0;
int captureFormat = 0;

int pauseWhenInactive = 0;
int active = 1;
int emulating = 0;
int RGB_LOW_BITS_MASK=0x821;
u32 systemColorMap32[0x10000];
u16 systemColorMap16[0x10000];
u16 systemGbPalette[24];
void (*filterFunction)(u8*,u32,u8*,u8*,u32,int,int) = NULL;
void (*ifbFunction)(u8*,u32,int,int) = NULL;
int ifbType = 0;
char filename[2048];
char ipsname[2048];
char biosFileName[2048];
char captureDir[2048];
char saveDir[2048];
char batteryDir[2048];

static char *rewindMemory = NULL;
static int rewindPos = 0;
static int rewindTopPos = 0;
//static int rewindCounter = 0;
static int rewindCount = 0;
static bool rewindSaveNeeded = false;
//static int rewindTimer = 0;

#define REWIND_SIZE 400000

#define _stricmp strcasecmp

bool sdlButtons[4][12] = {
  { false, false, false, false, false, false, 
    false, false, false, false, false, false },
  { false, false, false, false, false, false,
    false, false, false, false, false, false },
  { false, false, false, false, false, false,
    false, false, false, false, false, false },
  { false, false, false, false, false, false,
    false, false, false, false, false, false }
};

bool sdlMotionButtons[4] = { false, false, false, false };

int sdlNumDevices = 0;
//SDL_Joystick **sdlDevices = NULL;

bool wasPaused = false;
int autoFrameSkip = 0;
int frameskipadjust = 0;
int showRenderedFrames = 0;
int renderedFrames = 0;

int throttle = 0;
u32 throttleLastTime = 0;
u32 autoFrameSkipLastTime = 0;

int showSpeed = 1;
int showSpeedTransparent = 1;
bool disableStatusMessages = false;
bool paused = false;
bool pauseNextFrame = false;
bool debugger = false;
bool debuggerStub = false;
int fullscreen = 0;
bool systemSoundOn = false;
bool yuv = false;
int yuvType = 0;
bool removeIntros = false;
int sdlFlashSize = 0;
int sdlAutoIPS = 1;
int sdlRtcEnable = 0;
int sdlAgbPrint = 0;

int sdlDefaultJoypad = 0;

extern void debuggerSignal(int,int);

void (*dbgMain)() = 0;//debuggerMain;
void (*dbgSignal)(int,int) = 0;//debuggerSignal;
void (*dbgOutput)(char *, u32) = 0;// debuggerOutput;

int  mouseCounter = 0;
int autoFire = 0;
bool autoFireToggle = false;

bool screenMessage = false;
char screenMessageBuffer[21];
u32  screenMessageTime = 0;

//SDL_cond *cond = NULL;
//SDL_mutex *mutex = NULL;
u8 sdlBuffer[4096];
int sdlSoundLen = 0;

char *arg0;

#ifndef C_CORE
u8 sdlStretcher[16384];
int sdlStretcherPos;
#else
void (*sdlStretcher)(u8 *, u8*) = NULL;
#endif
/*
enum {
  KEY_LEFT, KEY_RIGHT,
  KEY_UP, KEY_DOWN,
  KEY_BUTTON_A, KEY_BUTTON_B,
  KEY_BUTTON_START, KEY_BUTTON_SELECT,
  KEY_BUTTON_L, KEY_BUTTON_R,
  KEY_BUTTON_SPEED, KEY_BUTTON_CAPTURE
};
*/

#define optind 1


extern bool CPUIsGBAImage(const char *qa);
extern bool gbIsGameboyRom(char *a);

/*
static int sdlCalculateShift(u32 mask)
{
  int m = 0;
  
  while(mask) {
    m++;
    mask >>= 1;
  }

  return m-5;
}

static int sdlCalculateMaskWidth(u32 mask)
{
  int m = 0;
  int mask2 = mask;

  while(mask2) {
    m++;
    mask2 >>= 1;
  }

  int m2 = 0;
  mask2 = mask;
  while(!(mask2 & 1)) {
    m2++;
    mask2 >>= 1;
  }

  return m - m2;
}
*/

void sdlWriteBattery()
{
  char buffer[1048];

//  if(batteryDir[0])
//    sprintf(buffer, "%s/%s.sav", batteryDir, sdlGetFilename(filename));
//  else  
//    sprintf(buffer, "%s.sav", filename);

  emulator.emuWriteBattery(buffer);

  systemScreenMessage("Wrote battery");
}

void sdlReadBattery()
{
 char buffer[1048];
//НЕВЕРНО! Подставить в буфер !!! имя файла
//  if(batteryDir[0])
//    sprintf(buffer, "%s/%s.sav", batteryDir, sdlGetFilename(filename));
//  else 
//    sprintf(buffer, "%s.sav", filename);
  
  bool res = false;

  res = emulator.emuReadBattery(buffer);

  if(res)
    systemScreenMessage("Loaded battery");
}



//int onstart(int argc, char **argv)
int onstart(char *exename, char *fname) // Старте приложения. Возвращает 0 или 1 для выхода.
{
  int f, type, size, ii, i ;
  if(!fname || fname[1]!=':') return 1;
  if(delta == NULL) {
    if(!(delta = (u8*)malloc(322*242*4))) return 4;
    memset(delta, 255, 322*242*4);
  }
/*
  int argc; 
  char **argv;
  arg0 = argv[0];
*/  
  captureDir[0] = 0; 
  saveDir[0] = 0;
  batteryDir[0] = 0;
  ipsname[0] = 0;
  
//  int op = -1;

  frameSkip = 2; //2-3
//  gbBorderOn = 0;

  parseDebug = true;

  //sdlReadPreferences();

  sdlPrintUsage = 0;
  if(sdlFlashSize == 0)
    flashSetSize(0x10000);
  else
    flashSetSize(0x20000);

//  rtcEnable(sdlRtcEnable ? true : false);//?????????????НАДО
/*
  agbPrintEnable(sdlAgbPrint ? true : false);
  
  if(!debuggerStub) {
	  if(optind >= argc) {
      systemMessage(0,"Missing image name");
      usage(argv[0]);
      exit(-1);
    }
  }

  if(filter) {
    sizeOption = 1;
  }
*/
  for(i = 0; i < 24;) {
    systemGbPalette[i++] = (0x1f) | (0x1f << 5) | (0x1f << 10);
    systemGbPalette[i++] = (0x15) | (0x15 << 5) | (0x15 << 10);
    systemGbPalette[i++] = (0x0c) | (0x0c << 5) | (0x0c << 10);
    systemGbPalette[i++] = 0;
  }

  systemSaveUpdateCounter = SYSTEM_SAVE_NOT_UPDATED;

//  if(optind < argc) {
    char *szFile = fname;//argv[optind];

    //utilGetBaseName(szFile, filename);
    //char *p = strrchr(filename, '.');

    //if(p)
    //  *p = 0;

    if(ipsname[0] == 0)
      sprintf(ipsname, "%s.ips", filename);
    
    bool failed = false;

    type = IMAGE_GBA; //utilFindType(szFile);

    cartridgeType = type;
//   if(type == IMAGE_GBA) {
        if((f=fopen(szFile,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 2;
        size = ROMSIZE = lseek(f,0,2,&err,&err);
        fclose(f,&err);

        if(ii= CPULoadRom(szFile)) return ii+4;
//return 2;        
      if(ii=fmapopen(szFile,&fmap,5)) return ii;
      failed = (size == 0);
      if(!failed) {
        //        if(cpuEnhancedDetection && cpuSaveType == 0) {
        //          utilGBAFindSave(rom, size);
        //        }

//        sdlApplyPerImagePreferences();
        
        cartridgeType = 0;
        emulator = GBASystem;

        /* disabled due to problems
        if(removeIntros && rom != NULL) {
          WRITE32LE(&rom[0], 0xea00002e);
        }
        */
        
        CPUInit(biosFileName, useBios);
        CPUReset();
        if(sdlAutoIPS) {
          int size = 0x2000000;
//          utilApplyIPS(ipsname, &rom, &size);
          if(size != 0x2000000) {
            CPUReset();
          }
        }
      }
  //  }
    
    if(failed) {
      systemMessage(0, "Failed to load file %s", szFile);
      return -1;//exit(-1);
    }
/*  } else {
    cartridgeType = 0;
    strcpy(filename, "gnu_stub");
    rom = (u8 *)malloc(ROMSIZE);
    workRAM = (u8 *)calloc(1, 0x40000);
    bios = (u8 *)calloc(1,0x4000);
    internalRAM = (u8 *)calloc(1,0x8000);
    paletteRAM = (u8 *)calloc(1,0x400);
    vram = (u8 *)calloc(1, 0x20000);
    oam = (u8 *)calloc(1, 0x400);
    pix = (u8 *)calloc(1, 4 * 240 * 160);
    ioMem = (u8 *)calloc(1, 0x400);

    emulator = GBASystem;
    
    CPUInit(biosFileName, useBios);
    CPUReset();    
  }
*/  
  sdlReadBattery();
  
//  sdlCheckKeys();
  
  if(cartridgeType == 0) {
    srcWidth = 240;
    srcHeight = 160;
    systemFrameSkip = frameSkip;
  } else if (cartridgeType == 1) {
    if(0) {
      srcWidth = 256;
      srcHeight = 224;
//      gbBorderLineSkip = 256;
//      gbBorderColumnSkip = 48;
//      gbBorderRowSkip = 40;
    } else {      
      srcWidth = 160;
      srcHeight = 144;
//      gbBorderLineSkip = 160;
 //     gbBorderColumnSkip = 0;
 //     gbBorderRowSkip = 0;
    }
//    systemFrameSkip = gbFrameSkip;
  } else {
    srcWidth = 320;
    srcHeight = 240;
  }
  
  destWidth = (sizeOption+1)*srcWidth;
  destHeight = (sizeOption+1)*srcHeight;
  
  systemRedShift = 11;//sdlCalculateShift(surface->format->Rmask);
  systemGreenShift = 5;//sdlCalculateShift(surface->format->Gmask);
  systemBlueShift = 0;//sdlCalculateShift(surface->format->Bmask);
  
  systemColorDepth = 16;//surface->format->BitsPerPixel;
  if(systemColorDepth == 15)
    systemColorDepth = 16;

  
  if(systemColorDepth != 16 && systemColorDepth != 24 &&
     systemColorDepth != 32) {
    printf("Unsupported color depth '%d'.\nOnly 16, 24 and 32 bit color depths are supported\n", systemColorDepth);
    return -1; //exit(-1);
  }
/*
#ifndef C_CORE
//  sdlMakeStretcher(srcWidth);
#else
  switch(systemColorDepth) {
  case 16:
    sdlStretcher = sdlStretcher16[sizeOption];
    break;
  case 24:
    sdlStretcher = sdlStretcher24[sizeOption];
    break;
  case 32:
    sdlStretcher = sdlStretcher32[sizeOption];
    break;
  default:
    fprintf(stderr, "Unsupported resolution: %d\n", systemColorDepth);
    exit(-1);
  }
#endif
*/
//  printf("Color depth: %d\n", systemColorDepth);
  
  if(systemColorDepth == 16) {
   // if(sdlCalculateMaskWidth(surface->format->Gmask) == 6) {
      //Init_2xSaI(565);
      RGB_LOW_BITS_MASK = 0x821;
   // } else {
      //Init_2xSaI(555);
   //   RGB_LOW_BITS_MASK = 0x421;      
   // }
    if(cartridgeType == 2) {
      for(i = 0; i < 0x10000; i++) {
        systemColorMap16[i] = (((i >> 1) & 0x1f) << systemBlueShift) |
          (((i & 0x7c0) >> 6) << systemGreenShift) |
          (((i & 0xf800) >> 11) << systemRedShift);  
      }      
    } else {
      for(i = 0; i < 0x10000; i++) {
        systemColorMap16[i] = ((i & 0x1f) << systemRedShift) |
          (((i & 0x3e0) >> 5) << systemGreenShift) |
          (((i & 0x7c00) >> 10) << systemBlueShift);  
      }
    }
    srcPitch = srcWidth * 2+4;
  } else {
    if(systemColorDepth != 32)
      filterFunction = NULL;
    RGB_LOW_BITS_MASK = 0x010101;
    if(systemColorDepth == 32) {
      //Init_2xSaI(32);
    }
    for(i = 0; i < 0x10000; i++) {
      systemColorMap32[i] = ((i & 0x1f) << systemRedShift) |
        (((i & 0x3e0) >> 5) << systemGreenShift) |
        (((i & 0x7c00) >> 10) << systemBlueShift);  
    }
    if(systemColorDepth == 32)
      srcPitch = srcWidth*4 + 4;
    else
      srcPitch = srcWidth*3;
  }

  if(systemColorDepth != 32) {
    switch(filter) {
    case 0:
	default:
      filterFunction = NULL;
      break;
    }
  } else {
    switch(filter) {
	default:
    case 0:
      filterFunction = NULL;
      break;
    }
  }
  
  if(systemColorDepth == 16) {
    switch(ifbType) {
    case 0:
    default:
      ifbFunction = NULL;
      break;
    }
  } else if(systemColorDepth == 32) {
    switch(ifbType) {
    case 0:
    default:
      ifbFunction = NULL;
      break;
    }
  } else
    ifbFunction = NULL;

//  if(delta == NULL) {
//    delta = (u8*)malloc(322*242*4);
//    memset(delta, 255, 322*242*4);
//  }
  
  emulating = 1;
  renderedFrames = 0;

  autoFrameSkipLastTime = throttleLastTime = systemGetClock();
  
//  SDL_WM_SetCaption("VisualBoyAdvance", NULL);

//  FreeRamDebug(exename,"use"); //debug only
  return 0;//1;  //FAKE!!!!modifieed!!!!
}  
   
  
void emulate(){  //Главный цикл эмуляции
  running=emulating=1;
  while(running) {
//    if(!paused && active) {
//      if(debugger && emulator.emuHasDebugger)
//        dbgMain();
//      else {
        CPULoop(250000);
        //НАДО! Типа запись
/*        if(rewindSaveNeeded && rewindMemory && emulator.emuWriteMemState) {
          rewindCount++;
          if(rewindCount > 8)
            rewindCount = 8;
          if(emulator.emuWriteMemState &&
             emulator.emuWriteMemState(&rewindMemory[rewindPos*REWIND_SIZE], 
                                       REWIND_SIZE)) {
            rewindPos = (rewindPos+1) & 7;
            if(rewindCount == 8)
              rewindTopPos = (rewindTopPos+1) & 7;
          }
        }*/

        rewindSaveNeeded = false;
//      }
//    } else {
//      SDL_Delay(500);
//    }
//    sdlPollEvents();
//    if(mouseCounter) {
//      mouseCounter--;
//      if(mouseCounter == 0)
//        SDL_ShowCursor(SDL_DISABLE);
//    }
  }
}


void sstop(){
  running = emulating=0;
  runstop=1;

//  printf("Shutting down\n");
  //remoteCleanUp();
  //soundShutdown();

//  if(rom != NULL) {
    //sdlWriteBattery();
    //emulator.emuCleanUp();
//  }

//  SDL_Quit();
}

/*
unsigned int err;

FILE *ffopen(const char * cFileName, unsigned int iFileFlags, unsigned int iFileMode, unsigned int *ErrorNumber){
  return fopen(cFileName,(iFileFlags&1)?"wb":"rb");
}

int ffread(FILE *FileHandler, void *cBuffer, int iByteCount, unsigned int *ErrorNumber){
  return fread(cBuffer, 1, iByteCount, FileHandler);
}

unsigned int ffwrite(FILE *FileHandler, void const * cBuffer, int iByteCount, unsigned int *ErrorNumber){
  return fwrite(cBuffer, 1, iByteCount, FileHandler);
}

void ffclose(FILE *FileHandler, unsigned int *ErrorNumber){
  fclose(FileHandler);
}






/////////////
const char bmphead[]={
"\x42\x4D\xC6\xB5\x00\x00\x00\x00\x00\x00\x36\x00\x00\x00\x28\x00"
"\x00\x00\x84\x00\x00\x00\xB0\x00\x00\x00\x01\x00\x10\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x12\x0B\x00\x00\x12\x0B\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\xF8\x00\x00\xE0\x07\x00\x00\x1F\x00"
"\x00\x00\x00\x00\x00\x00"};

//unsigned int err;
const int screensize=132*176*2;

void savescreen(char *fname){
  FILE *f;//240 160
  int i,j;
  short scr[132*176], *s=scr;
  short *ss=(short*)pix;
  //for(i=0; i<132*176;i++,s++){
  //for(i=132*176-1;i>=0;i--,s++){//reverse
//    scr[i]=(*s&0x1f)|((*s>>1)&0xffe0);//RGB 555 convert! чтобы BMP корректно выглядело!
     //scr[i]=(*s);//<<4;//((*s&0xf)<<1)|((*s&0xf0)<<3)|((*s&0xf00)<<8);
//  }// ИЗОБРАЖЕНИЕ здесь повернуто зеркально!!!
  for(j=0;j<160;j++){
    for(i=0;i<120;i++){
      *s++=*ss;
	  ss+=2;
    }
    s+=12;
	ss+=2;
  }

  if((f=ffopen(fname,1,0,&err))==0) return;
  ffwrite(f,bmphead,sizeof(bmphead),&err); 
  ffwrite(f,scr,screensize,&err); 
  ffclose(f,&err); 
}

*/

//int cnt=1000;

void systemDrawScreen() //НАРИсовать экран???
{
  renderedFrames++;
//  if(++cnt>3){
//	cnt=0;
	//printf("show ");
    //savescreen("out.bmp");
        REDRAW();
//  }
 /*  
  SDL_LockSurface(surface);

//  if(ifbFunction) {
//    if(systemColorDepth == 16)
//      ifbFunction(pix+destWidth+4, destWidth+4, srcWidth, srcHeight);
//    else
//      ifbFunction(pix+destWidth*2+4, destWidth*2+4, srcWidth, srcHeight);
//  }
  
    int destPitch = surface->pitch;
    u8 *src = pix;
    u8 *dest = (u8*)surface->pixels;
    int i;
    u32 *stretcher = (u32 *)sdlStretcher;
    if(systemColorDepth == 16)
      src += srcPitch;
    int option = sizeOption;
    if(yuv)
      option = 0;
    switch(sizeOption) {
    case 0:
      for(i = 0; i < srcHeight; i++) {
        SDL_CALL_STRETCHER;
        src += srcPitch;
        dest += destPitch;
      }
      break;
    case 1:
      for(i = 0; i < srcHeight; i++) {
        SDL_CALL_STRETCHER;     
        dest += destPitch;
        SDL_CALL_STRETCHER;
        src += srcPitch;
        dest += destPitch;
      }
      break;
    case 2:
      for(i = 0; i < srcHeight; i++) {
        SDL_CALL_STRETCHER;
        dest += destPitch;
        SDL_CALL_STRETCHER;
        dest += destPitch;
        SDL_CALL_STRETCHER;
        src += srcPitch;
        dest += destPitch;
      }
      break;
    case 3:
      for(i = 0; i < srcHeight; i++) {
        SDL_CALL_STRETCHER;
        dest += destPitch;
        SDL_CALL_STRETCHER;
        dest += destPitch;
        SDL_CALL_STRETCHER;
        dest += destPitch;
        SDL_CALL_STRETCHER;
        src += srcPitch;
        dest += destPitch;
      }
      break;
    }

  SDL_UnlockSurface(surface);
  SDL_Flip(surface);*/
}

// SDL fakes

int systemGetSensorY(void){ return 0;}
int systemGetSensorX(void){ return 0;}

void systemScreenMessage(char const *a){}
unsigned int systemGetClock(void){ return 0;}

void  systemMessage(int a,char const *b,...){}

void systemSoundResume(void){}
void systemSoundPause(void){}
bool systemPauseOnFrame(void){ return 0;}
void  systemScreenCapture(int a){}
void systemUpdateMotionSensor(void){}
bool  systemReadJoypads(void){ return 1;}

unsigned int systemReadJoypad(int a){ 
/*
u32 systemReadJoypad(int which)
{
  if(which < 0 || which > 3)
    which = sdlDefaultJoypad;
  
  u32 res = 0;
  
  if(sdlButtons[which][KEY_BUTTON_A])
    res |= 1;
  if(sdlButtons[which][KEY_BUTTON_B])
    res |= 2;
  if(sdlButtons[which][KEY_BUTTON_SELECT])
    res |= 4;
  if(sdlButtons[which][KEY_BUTTON_START])
    res |= 8;
  if(sdlButtons[which][KEY_RIGHT])
    res |= 16;
  if(sdlButtons[which][KEY_LEFT])
    res |= 32;
  if(sdlButtons[which][KEY_UP])
    res |= 64;
  if(sdlButtons[which][KEY_DOWN])
    res |= 128;
  if(sdlButtons[which][KEY_BUTTON_R])
    res |= 256;
  if(sdlButtons[which][KEY_BUTTON_L])
    res |= 512;

  // disallow L+R or U+D of being pressed at the same time
  if((res & 48) == 48)
    res &= ~16;
  if((res & 192) == 192)
    res &= ~128;

  if(sdlButtons[which][KEY_BUTTON_SPEED])
    res |= 1024;
  if(sdlButtons[which][KEY_BUTTON_CAPTURE])
    res |= 2048;

  if(autoFire) {
    res &= (~autoFire);
    if(autoFireToggle)
      res |= autoFire;
    autoFireToggle = !autoFireToggle;
  }
*/  
  return res;
}

void  systemShowSpeed(int a){}
void  system10Frames(int a){}
void  systemFrame(void){}


////////////
//int onstart(char *exename, char *fname){ // Старте приложения. Возвращает 0 или 1 для выхода.
//  return 0;
//}
void oncreate(){
  SUBPROC((void*)emulate);
}

void onclose(){
//  sstop();
}

void onexit(){
  //mfree all!!!
  CPUCleanUp();
  fmapclose(&fmap);
  if(delta) {
    mfree(delta);
//    delta = NULL;
  }
} 

int color=1;

void onredraw(){
  int i,j;
  short *s=screen;
  short *ss=(short*)pix;
  //for(i=0; i<132*176;i++,s++){
  //for(i=132*176-1;i>=0;i--,s++){//reverse
//    scr[i]=(*s&0x1f)|((*s>>1)&0xffe0);//RGB 555 convert! чтобы BMP корректно выглядело!
     //scr[i]=(*s);//<<4;//((*s&0xf)<<1)|((*s&0xf0)<<3)|((*s&0xf00)<<8);
//  }// ИЗОБРАЖЕНИЕ здесь повернуто зеркально!!!

//  color=(color<<1)+((color&0x8000)?1:0);
//  memsetw(screen,color,screensize>>1);
  if(EL71){
  for(j=0;j<148;j++){
    movsd(s,ss,120);
    movsd(s+240,ss,120);
    s+=480;
    ss+=242;
  }
  }else{ //sgold
    s+=6+8*132;
  for(j=0;j<160;j++){
    for(i=0;i<120;i++){
      *s++=*ss;
      ss+=2;
    }
    s+=12;
    ss+=2;
  }
  }
} 

int onkey(unsigned char keycode, int pressed){ //  Обработчик клавиш. Вернуть 0 или 1 для выхода
  switch(pressed){
  case KEY_UP: 
 switch(keycode){
case LEFT_BUTTON: res&=~32; break;
case RIGHT_BUTTON: res&=~16; break;
case UP_BUTTON: res&=~64; break;
case DOWN_BUTTON: res&=~128; break;
case '*': res&=~1; break; //A
case '#': res&=~2; break; //B
case '7': res&=~4; break; //select
case '9': res&=~8; break; //start
case '1': res&=~256; break; //R
case '3': res&=~512; break; //L
}
    break; // Клавиша отпущена
  case LONG_PRESS:  // Клавиша удерживается долго (повтор)
  case KEY_DOWN: // Клавиша нажата
    if(runstop) return 1;
    if(keycode==RED_BUTTON){ sstop(); return 0;}
    if(keycode==GREEN_BUTTON){ mode=1; return 0;}
    if(mode==1){
      if(keycode>='0' && keycode<='9')
        systemFrameSkip = frameSkip = keycode-'0';
      mode=0; return 0;
    }
switch(keycode){
case LEFT_BUTTON: res|=32; break;
case RIGHT_BUTTON: res|=16; break;
case UP_BUTTON: res|=64; break;
case DOWN_BUTTON: res|=128; break;
case '*': res|=1; break; //A
case '#': res|=2; break; //B
case '7': res|=4; break; //select
case '9': res|=8; break; //start
case '1': res|=256; break; //R
case '3': res|=512; break; //L
}
//    REDRAW(); //debug only
  }
  return 0;
}

int isFreeRam(char *exename, char *fname){ //1=использ.FreeRam, 0=нет
  return !EL71;//!SGOLD2;
} 

/////////////fmap!!!


//16k
#define pagesize 0x4000
#define pagemask 0x3FFF
#define pageshift 14

int fmapopen(char *fname, struct fmapst *fmap, int freepages){ //открыть файл и спроецировать на память, оставить своб. free страниц
  int i, pages;
  int f;
  char **mem;
  if((fmap->f=f=fopen(fname,A_ReadOnly+A_BIN,P_READ,&err))==-1) return 2; //no open
  loadfilesize=lseek(f,0,2,&err,&err);
  lseek(f,0,0,&err,&err);
  if(!(pages=fmap->pages=loadfilesize>>pageshift)) return 3; //file empty
  if(!(mem=fmap->mem=(char**)malloc(pages<<2))) return 4; //no mem
  memset(mem,0,pages<<2);
  for(i=0;i<pages;i++)
//	  if(i>7){ *mem++=0; break;} else  ////////test - vary slow!!!
		  if(!(*mem++=(char*)malloc(pagesize))) break;
  if(i<pages)
    while(--freepages>=0){ mfree(*--mem); *mem=0; --i;}
  *mem=0;
  fmap->allocpages=i;
  //cache
  mem=fmap->mem;
  while(--i>=0){
    fread(f,*mem,pagesize,&err);
#ifdef SEGA
	xswap(*mem,pagesize);//add
#endif
	mem++;
  }
  return 0;
}

void fmapclose(struct fmapst *fmap){ //закрыть файл
  char **mem=fmap->mem;
  int i=fmap->pages;
  while(--i>=0){
    if(*mem) mfree(*mem);
    ++mem;
  }
  mfree(fmap->mem);
  if(fmap->f>0) fclose(fmap->f,&err);
//  memset(&fmap,0,sizeof(struct fmapst));
}

void readfile(int f, char *buf, int n){//читать сектор
  //llseek(f,n<<pageshift,0,&err,&err);
  lseek(f,n<<pageshift,0,&err,&err);
  fread(f,buf,pagesize,&err);
#ifdef SEGA
  xswap(buf,pagesize); //add
#endif
}


//int random(){ return 1;}//FAKE!!! //должен возвр. 2 байта!!!
extern unsigned int randint( int max );

void fmapread(struct fmapst *fmap, int page){ // "подгрузить" страницу
  int n;
  if(fmap->mem[page]) return;
  char **mem=fmap->mem+1;//+1 резерв!!!
  //получ. СЧ сектор или по частоте n=random/pageees
   n=randint(fmap->allocpages-1);
  while(n>=0) if(*mem++) --n; //>=0????
  //читать сектор
  readfile(fmap->f, fmap->mem[page]=*--mem, page);
  *mem=0; //освободить место
}
//rom[address & 0x1FFFFFF];        

// Readdata
