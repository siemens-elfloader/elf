/*
* amr2wav 
* 2011
*/

#include "..\inc\swilib.h"


/****************************************************
**************Wave file format***********************
	  __________________________
	| RIFF WAVE Chunk	   |
	|   groupID  = 'RIFF'      |
	|   riffType = 'WAVE'      |
	|    __________________    |
	|   | Format Chunk     |   |
	|   |	ckID = 'fmt '  |   |
	|   |__________________|   |
	|    __________________    |
	|   | Sound Data Chunk |   |
	|   |	ckID = 'data'  |   |
	|   |__________________|   |
	|__________________________|

****************************************************/




#include "wavefile.h"


/*
 *	Function		:	OpenWaveFile
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Open a wave file 
 *	Entry			:	WavName -- wave file name 
 *
 *	Return			:	WavStruct -- WAVStruct*
 *						The struct to collect wave file information 
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */


WAVStruct* OpenWaveFile( char* WavName ) 
{
	int			fp = 0  ; 
	char			buf4[5] ;
	WAVStruct*		WavStruct = 0 ; 
	unsigned long	bytes ;
        fp = fopen(WavName,A_ReadOnly+A_BIN,P_READ,0);
	if( fp ==-1)
		goto error;

	WavStruct = malloc( sizeof( WAVStruct ) ) ;
	if(!WavStruct )
		goto error;
	memset( WavStruct , 0 ,  sizeof( WAVStruct )  ) ; 
	bytes = fread(fp, &(WavStruct->riff)  , sizeof( WAVInfo ) , 0 ) ;
	if( bytes != sizeof( WAVInfo ) )
		goto error;
	
	strcpy( buf4 , "RIFF" ) ;
	if( memcmp( WavStruct->riff.riffHead , buf4 ,4  ) != 0  )
		goto error;
	strcpy( buf4 , "WAVE" ) ;
	if( memcmp( WavStruct->riff.riffType, buf4,  4 ) != 0  )
		goto error;	
	strcpy( buf4 , "fmt " ) ;
	if( memcmp( WavStruct->foramt.chunkID, buf4, 4 ) != 0  )
		goto error;
	if( WavStruct->foramt.wFormatTag != WAVE_FORMAT_PCM )
		goto error;

	WavStruct->fp = fp ; 
	WavStruct->IsWrite = 0 ;
	return WavStruct ;
error:if( fp )
		  fclose( fp ,0) ;
	if( WavStruct )
		mfree( WavStruct ) ;
	return 0 ;
}


/*
 *	Function		:	CreateWaveFile
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Create a wave file to writing
 *	Entry			:	WavName -- wave file name 
 *
 *	Return			:	WavStruct -- WAVStruct*
 *						The struct to collect wave file information 
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */


WAVStruct* CreateWaveFile( char* WavName , short nChannel , short sampleBits , long sampleRate  ) 
{
	int		fp = 0  ; 
	WAVStruct*		WavStruct = 0 ; 
	unsigned long	bytes ;
        fp = fopen(WavName,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0);
	if( !fp )
		goto error;

	WavStruct = malloc( sizeof( WAVStruct ) ) ;
	if(!WavStruct )
		goto error;
	memset( WavStruct , 0 , sizeof( WAVStruct ) ) ;
	WavStruct->riff.riffHead[0] = 'R';
	WavStruct->riff.riffHead[1] = 'I';
	WavStruct->riff.riffHead[2] = 'F';
	WavStruct->riff.riffHead[3] = 'F';
	WavStruct->riff.riffType[0] = 'W';
	WavStruct->riff.riffType[1] = 'A';
	WavStruct->riff.riffType[2] = 'V';
	WavStruct->riff.riffType[3] = 'E';
	
	WavStruct->foramt.chunkID[0]= 'f';
	WavStruct->foramt.chunkID[1]= 'm';
	WavStruct->foramt.chunkID[2]= 't';
	WavStruct->foramt.chunkID[3]= ' ';
	WavStruct->foramt.chunkSize = sizeof(FormatChunk) - 8 ;
	WavStruct->riff.length =  20 + WavStruct->foramt.chunkSize ;
	WavStruct->foramt.wFormatTag =  WAVE_FORMAT_PCM ;
	WavStruct->foramt.wChannels =  nChannel  ;
	WavStruct->foramt.dwSamplesPerSec = sampleRate ;
	WavStruct->foramt.dwAvgBytesPerSec = sampleRate*sampleBits*nChannel/8 ;
	WavStruct->foramt.wBlockAlign = sampleBits*nChannel/8;
	WavStruct->foramt.wBitsPerSample = sampleBits ;
	WavStruct->data.chunkID[0] = 'd';
	WavStruct->data.chunkID[1] = 'a';
	WavStruct->data.chunkID[2] = 't';
	WavStruct->data.chunkID[3] = 'a';

	bytes = fwrite(fp, &WavStruct->riff  , sizeof( WAVInfo ) ,  0 ) ;
	if( bytes != sizeof( WAVInfo ) )goto error;
		
	WavStruct->fp = fp ; 
	WavStruct->IsWrite = 1  ;
	return WavStruct ;
error:
  if( fp )fclose( fp,0 ) ;
 if( WavStruct ) mfree( WavStruct ) ;
	return 0 ;
}



/*
 *	Function		:	WriteCombineSamplesWaveFile
 *--------------------------------------------------------------------------------
 *	Purpose 		:	write sample into file 
 *	Entry			:	WavStruct -- WAVStruct*
 *						The struct to collect wave file information 
 *						samples -- unsigned char* , to store sample data with format:
 *						data of all channels in one sample is stored in the same location
 *						for example : two channels ,16bit/channel is placed as :
 *						l-ch-by0 , l-ch-by1;r-ch-by0, r-ch-by1;l-ch-by0,l-ch-by1;r-ch-by0,r-ch-by1
 *	Return			:	
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */


short WriteCombineSamplesWaveFile( WAVStruct* WavStruct , unsigned char* samples , long sampleNum ) 
{
	long bytes ;
	long sampleBytes = sampleNum * WavStruct->foramt.wBlockAlign  ;		
	bytes = fwrite(WavStruct->fp, samples , sampleBytes ,0 ) ;
	WavStruct->data.chunkSize += bytes ;
	if( bytes != sampleBytes )
		return 0 ;
	else
		return 1 ;

}


/*
 *	Function		:	WriteSeparateWaveFile
 *--------------------------------------------------------------------------------
 *	Purpose 		:	write sample into file 
 *	Entry			:	WavStruct -- WAVStruct*
 *							The struct to collect wave file information 
 *						samples -- unsigned char** , to a pointer group that has nChannel unsigned char
 *									buffer to store each channel samples	
 *						data of each channels is stored separate
 *						for example : two channels ,16bit/channel is placed as :
 *						samples[0] is left channel data , samples[1] is right channel data
 *	Return			:
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */


short WriteSeparateWaveFile( WAVStruct* WavStruct , unsigned char** samples , long  sampleNum , short nChannel ) 
{
	long bytes ;
	unsigned char buf0[48] ;
	unsigned char* buf ;
	unsigned char* samplesTmp[12] ;
	long bytesEachChannel;
	int n , k ; 
	
	if( nChannel != WavStruct->foramt.wChannels ) 
		return 0 ; 
	memcpy( samplesTmp , samples , nChannel*sizeof( unsigned char* ) ) ;	
	bytesEachChannel = WavStruct->foramt.wBitsPerSample/8 ;
	
	buf = buf0 ;
	for( n = 0 ; n < sampleNum ; n ++  )
	{		
		for( k = 0 ; k < nChannel ; k ++ )
		{
			memcpy( buf , samplesTmp[k]  , bytesEachChannel ) ;
			samplesTmp[k] += bytesEachChannel ;
			buf += bytesEachChannel ;
		}
		buf = buf0 ;
		bytes = fwrite(WavStruct->fp , buf  , WavStruct->foramt.wBlockAlign , 0) ;
		WavStruct->data.chunkSize += bytes ;
	}
		
	return 1 ;
}





short ReadCombineSamplesWaveFile( WAVStruct* WavStruct , unsigned char* samples , long* sampleNum ) 
{
	long bytes ;
	long sampleBytes = *sampleNum * WavStruct->foramt.wBlockAlign  ;		
	bytes = fread( WavStruct->fp,samples  , sampleBytes ,0 ) ;
	if( bytes < sampleBytes )
		* sampleNum = bytes/WavStruct->foramt.wBlockAlign ; 	
	return 1 ;

}



/*
 *	Function		:	ReadSeparateWaveFile
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Read sample into file 
 *	Entry			:	WavStruct -- WAVStruct*
 *							The struct to collect wave file information 
 *						samples -- unsigned char** , to a pointer group that has nChannel unsigned char
 *									buffer to store each channel samples	
 *						data of each channels is stored separate
 *						for example : two channels ,16bit/channel is placed as :
 *						samples[0] is left channel data , samples[1] is right channel data
 *	Return			:
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */

short ReadSeparateWaveFile( WAVStruct* WavStruct , unsigned char** samples , long  *sampleNum , short nChannel ) 
{
	long bytes ;
	unsigned char buf0[48] ;
	unsigned char* buf ;
	unsigned char* samplesTmp[12] ;
	long bytesEachChannel;
	int n , k ; 
	long  sampleNum1 = *sampleNum ;
	
	if( nChannel != WavStruct->foramt.wChannels ) 
		return 0 ; 
	memcpy( samplesTmp , samples , nChannel*sizeof( unsigned char* ) ) ;	
	bytesEachChannel = WavStruct->foramt.wBitsPerSample/8 ;


	*sampleNum = 0 ;
	for( n = 0 ; n < sampleNum1 ; n ++  )
	{
		buf = buf0 ;
		bytes = fread(WavStruct->fp, buf  , WavStruct->foramt.wBlockAlign , 0 ) ;
		if( bytes != WavStruct->foramt.wBlockAlign )
			return 0 ;
		for( k = 0 ; k < nChannel ; k ++ )
		{
			memcpy( samplesTmp[k]  , buf   , bytesEachChannel ) ;
			samplesTmp[k] += bytesEachChannel ;
			buf += bytesEachChannel ;
		}
		(*sampleNum )++ ;
		
	}
	if( *sampleNum  == sampleNum1 )
		return 1 ;
	else
		return 0 ;
}



short CloseWaveFile( WAVStruct* WavStruct )
{
	if( !WavStruct->IsWrite )
	{
		fclose( WavStruct->fp,0) ;
		mfree( WavStruct ) ;
	}
	else
	{
		WavStruct->riff.length += WavStruct->data.chunkSize ;
		lseek( WavStruct->fp , 0 , SEEK_SET,0,0 ) ;
		fwrite( WavStruct->fp,&(WavStruct->riff)  , sizeof(WAVInfo) , 0  ) ;
		fclose( WavStruct->fp,0) ;
		mfree( WavStruct ) ;
	}
	return 1 ;
}


