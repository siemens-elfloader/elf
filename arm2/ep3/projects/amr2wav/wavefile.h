/*
 * File Name:       wavefile.h
 * Author:			Han Josen
 * Start Date:		Dec 10 , 2002
 * Language:        Microsoft Visual C++ 6.0
 * Target:			Codec for AMR file
 * Summary:			This file contains the functions read/write wave file
 *
 * Change Note:
 */


#ifdef __cplusplus
extern "C" {
#endif



#define WAVE_FORMAT_PCM     1
//WAVEFORMAT

#pragma pack(1)

typedef struct {
	char	riffHead[4];
	long	length;
	char	riffType[4] ;
}RiffStrut;

typedef struct {
  char           chunkID[4];
  long           chunkSize;

  short          wFormatTag;
  unsigned short wChannels;
  unsigned long  dwSamplesPerSec;
  unsigned long  dwAvgBytesPerSec;
  unsigned short wBlockAlign;
  unsigned short wBitsPerSample;
/* Note: there may be additional fields here, depending upon wFormatTag. */
} FormatChunk ;

typedef struct {
	char	chunkID[4] ;
	long    chunkSize;
} DataChunk ;


typedef struct tagWAVStruct
{
	FILE			*fp ;
	short			IsWrite ;
	RiffStrut		riff ;
	FormatChunk		foramt ;
	DataChunk		data ;
}WAVStruct ;


typedef struct tagWAVInfo
{
	RiffStrut		riff ;
	FormatChunk		foramt ;
	DataChunk		data ;
}WAVInfo ;
#pragma pack()
WAVStruct* OpenWaveFile( char* WavName )  ;
WAVStruct* CreateWaveFile( char* WavName , short nChannel , short sampleBits , long sampleRate  ) ;
short WriteCombineSamplesWaveFile( WAVStruct* WavStruct , unsigned char* samples , long sampleNum ) ;
short WriteSeparateWaveFile( WAVStruct* WavStruct , unsigned char** samples , long  sampleNum , short nChannel )  ;
short ReadCombineSamplesWaveFile( WAVStruct* WavStruct , unsigned char* samples , long* sampleNum ) ;
short ReadSeparateWaveFile( WAVStruct* WavStruct , unsigned char** samples , long  *sampleNum , short nChannel )  ;
short CloseWaveFile( WAVStruct* WavStruct );


typedef struct _WaveDevConfig
{
	unsigned long bufferSize ;
	int			  bufferCount ;
	int			  writeMode ;
}WaveDevConfig, *PWaveDevConfig ;

typedef struct _WaveConfig
{
	unsigned long sampleRate ;
	unsigned long dataBits ;
	unsigned long channels ;
}WaveConfig, *PWaveConfig ;



#ifdef __cplusplus
}
#endif

