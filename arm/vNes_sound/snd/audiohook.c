/*    ��������� ��� ����� ����. 
ILYA_ZX.
mailto: ilya.zx@gmail.com 
*/

#include "swilib.h"

typedef struct
{
  void * FillProc;
  unsigned short * buffer;
  unsigned short * curpos;
  unsigned short * buffend;
}
_wavplayer;

_wavplayer * WAV_PLAYER;



signed char Volume=4;

//extern void( * SetAmplifierGate ) ( int Amp, int Gate, int SessionID );
/* ������� ������������� */
int samplerate=16000;

float smpratemul = 1;
/* ������� ������� ��������� ����� ������� */
//void( * GetSound ) ( unsigned short *, int );
/* ����� � ���(�� ���������� �������) */
long /* * AdpcmWaveParams */ * PcmWaveParams;
/* ������, ����������� �������� PlayMelodyInMem */
//signed short * buffer;
/* ����� ���������� ������� ��� ����������. ���� ������ ������� ������� �� ��� */
unsigned char nextbuff;
/* ������, ������������ ��� ������� ������������ */
//signed short * AudioBuf = 0;
signed short * TempBuf;
/* ������ ��� PCM ������ */
//signed short * pcmbuff=0;
/* ���������� ���������� ����������������. ��� ���������: Playing=0; */
signed char Playing;
/* ����� ������������ � 1/16000 ������� */
signed long PlayingTime;
/* ��������� ���������� ������������� */
void PlayingProc();
/* ������ :) */
GBSTMR ahtimer;
/* ������ �������.*/
//static const int BUFFERSIZE = 64000;

char Paused = 0;
signed short GetSound();
/* ��������� wave PCM */
unsigned char WavHdr[44] = {
	0x52, 0x49, 0x46, 0x46, 0x0A, 0x46, 0x03, 0x00, 0x57, 0x41, 0x56, 0x45, 0x66, 0x6D, 0x74, 0x20, 
	0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x40, 0x1F, 0x00, 0x00, 0x40, 0x1F, 0x00, 0x00, 
	0x01, 0x00, 0x08, 0x00, 0x64, 0x61, 0x74, 0x61, 0x5F, 0x45, 0x03, 0x00
};

void GetAacSound(unsigned short *ptr, int nsamples);



char PcmPlayerFill()
{
  
    
  unsigned long i = 0xA0/16;
  //unsigned short * curpos = WAV_PLAYER->curpos;
  long * rambuf = PcmWaveParams+0x23;

  while ( i>0 )
  {
    * rambuf = GetSound();
    * (rambuf+1) = GetSound();
    * (rambuf+2) = GetSound();
    * (rambuf+3) = GetSound();    
    * (rambuf+4) = GetSound();
    * (rambuf+5) = GetSound();
    * (rambuf+6) = GetSound();
    * (rambuf+7) = GetSound();    
    * (rambuf+8) = GetSound();
    * (rambuf+9) = GetSound();
    * (rambuf+10) = GetSound();    
    * (rambuf+11) = GetSound();
    * (rambuf+12) = GetSound();
    * (rambuf+13) = GetSound();
    * (rambuf+14) = GetSound();
    * (rambuf+15) = GetSound();
    
    rambuf+=16;
    //curpos+=16;
    i--;
  }
  
  /*
  if ( curpos >= WAV_PLAYER->buffend )
  {
    WAV_PLAYER->curpos = WAV_PLAYER->buffer;
    return;
  }
  WAV_PLAYER->curpos = curpos;
  */
return 1;
}

/* ������� ��������� � ���������� ������������ �������, �� 0 - ������������ �������� */
void SetHookState( unsigned char hookstate )
{
  if ( hookstate ) PcmWaveParams[32]=(long)WAV_PLAYER; 
  else
    PcmWaveParams[32]=0; 

}

/* ���������� ������� � ������� */
unsigned long BuffPos()
{
  return (long)(WAV_PLAYER->curpos-WAV_PLAYER->buffer);
  ;
}





int PlayStatus()
{
  return ( PcmWaveParams[0x18] );
};



void AudioInit()
{

  Volume = 2;
  /* ����� ���������� wave �� ���������� �������, ������� ������� ��� �������� � �� ����� */
  //AdpcmWaveParams = ( void * ) 0xA0FD426C;
  // AdpcmWaveParams = ( void * ) AdpcmWaveParams[0];
  //AdpcmWaveParams = AudioParamsAdr();
  PcmWaveParams = ( void * ) 0xA879F7C0;
  // c75v22  0xA874CC04
  //s65v58 0xA879F7C0
  //c72 A86B9954
  WAV_PLAYER = malloc( sizeof( _wavplayer ) );
  //PcmWaveParams[-1]=(long)WAV_PLAYER; 
  /* +44 - �� ��������� wave */
  //AudioBuf = malloc(BUFFERSIZE);
  TempBuf=malloc(8192);
  //zeromem( AudioBuf, BUFFERSIZE);
  zeromem( TempBuf, 8192);
 // WAV_PLAYER->buffer=AudioBuf;
 // WAV_PLAYER->curpos=AudioBuf;
  //WAV_PLAYER->buffend=AudioBuf+BUFFERSIZE/2;
  WAV_PLAYER->FillProc = ( void * ) PcmPlayerFill;
  //pcmbuff = malloc( 1014 );
  /* �������� ��������� wave */
  memcpy( ( char * ) TempBuf, ( void * ) ( WavHdr ), 44 );

}

void AudioStart()
{



#ifdef _profile
  ResetProfile();
#endif 
  
  //WAV_PLAYER->curpos=AudioBuf;
  /* ��������������� ������� */
  Playing = 1;
  /* 0xFF - ��� ��������� ��������� � ��������� ������ ������� */
  nextbuff = 0xFF;
  /* �������������� ������ */
  //if(playsamplerate==samplerate)
  //GetSound(AudioBuf,BUFFERSIZE / 2);
  //else FillBufferres();
  /* ������������� ������������ */
  SetHookState( 1 );
  //   /*�������� ��������� wave */
  // memcpy( AudioBuf, ( void * ) ( WavHdr ), 44 );
  /* ������������� ������� ������������� */
  /* �������� ��������� wave */
  memcpy( ( char * ) TempBuf, ( void * ) ( WavHdr ), 44 );
  memcpy( ( char * ) TempBuf + 24, & samplerate, 4 );
  //* ( ( char * ) 0xA879DB90 ) = ( 48 - ( Volume * 2 ) ) + 1;
  //  *(( (char *) PcmWaveParams)+0x86)=9;
  /* ��������� ������ �� ������������ */
  PlayMelodyInMem( 0x11, TempBuf, 0x140 * 16, 0xFFFF, 0, 0 );
  /* ��������� ���� ������������ ������������ */
  GBS_StartTimerProc( & ahtimer, 64, PlayingProc );
 // AdpcmWaveParams[16] = 0;

}

/* ��������� ���������������. ������� ���������� ���� Playing=0 */
void AudioStop()
{
  /* ��������� ��� */
  SetHookState( 0 );

  /* ����������� �������� ���� ��� ��������� ������������ ��������� ������� */
  //PlayMelodyInMem( 0x11, AudioBuf, 256 + 44, 0xFFFF, 0, 0 );
}

void FreeMemory()
{
  if(TempBuf)
  {
    mfree(TempBuf);
    TempBuf=0;
  }
  
  if(WAV_PLAYER)
  { 
    mfree(WAV_PLAYER);  
    WAV_PLAYER=0;
}
}

void AudioTerminate()
{
  Playing = 0;
  AudioStop();
  FreeMemory();
  //GBS_StartTimerProc( & ahtimer, 16, FreeMemory );
  
  //if(pcmbuff!=0){
  //mfree( pcmbuff );
  // pcmbuff=0;
  //}
}


void SetVolume(char Vol)
{
if(Vol>4)return;
Volume=Vol;
//ChangeVolume(Volume);
}
               
void PlayingProc()
{
  
  
  //ChangeVolume(Volume);
  
  
}
