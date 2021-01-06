/* 
 * File Name:       amrfile.c
 * Author:			Han Josen
 * Start Date:		Dec 09 , 2003
 * Language:        Microsoft Visual C++ 6.0
 * Target:			Codec for AMR file
 * Summary:			This file contains the functions to decompress amr to wav
 *					Ref document:
 *					1. << draft-ietf-avt-rtp-amr-12.txt >> 	
 *					2. << 3GPP TS 26.101 V4.20(2002-3) , AMR Speech Codec Frame Structure>> 
 *	 
 * Change Note:     
 */

#ifndef WIN32
#include <itk.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 
#ifdef WIN32
#include <memory.h>
#include <io.h>
#else
#include <unistd.h>
#endif
#include <stdio.h>
#include "amrfile.h"
#include "frmbtord.h"

#ifdef WIN32
#define O_BINARY _O_BINARY
#define O_RDONLY _O_RDONLY
#endif


/*
 *	Function		:	OpenAmrFile
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Open a amr file 
 *	Entry			:	AmrName -- Amr file name 
 *
 *	Return			:	AmrStruct -- AMRStruct*
 *						The struct to collect amr file information 
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */

/*
#ifndef WIN32
#include <time.h>
#include <itk.h>
#define O_BINARY
 0
#endif
*/

/* The start string of AMR file : Norrow-band single-channel, Norrow-band single-channel,
   Wide-band single-channel,  Wide-band multi-channel */
const char* amrStr[4] = { "#!AMR\n" , "#!AMR-WB\n" , "#!AMR_MC1.0\n" , "#!AMR-WB_MC1.0\n" } ;
AMRStruct* OpenAmrFile(char* AmrName , unsigned int* pid , int isIdFile , int offsetForIdFile ) 
{
	char buf[15] ;	
	unsigned long bytes ;
	
	int		fd = -1 ;
	AMRStruct* AmrStruct = 0  ;
	enum AmrFileType AmrType ;
	short n ;
	
	//FILE* fp  = 0  ;
	//fp = fopen( AmrName , "rb" ) ;
	//if( !fp ) 
	//	goto error ;

	if( !isIdFile  )
#ifdef WIN32	
	    fd = open( AmrName , O_RDONLY|O_BINARY ) ; 
	
#else
	    fd = open( AmrName , O_RDONLY ) ; 
	else
	{
	    fd = itkOpenIdFile( AmrName ,pid ,  O_RDONLY ) ; 
		lseek( fd , offsetForIdFile , SEEK_SET ) ;
	}
#endif

	if( fd == -1 )
		goto error ;

	//bytes = fread( buf , 1 , 15 , fp ) ;
	bytes = read( fd , buf , 15) ;
	AmrType =  AMR_NB_SC ;
	while ( AmrType < AMR_TYPE_NUM )
	{
		if( memcmp( buf , amrStr[AmrType] ,  strlen( amrStr[AmrType] ) ) == 0 )
			break ;
		AmrType ++  ;
	}
	
	if( AmrType >= AMR_TYPE_NUM )
		goto error ;
	
	//fseek( fp , strlen( amrStr[AmrType] )  , SEEK_SET );
	if( !isIdFile  )
		lseek( fd , strlen( amrStr[AmrType] )  , SEEK_SET );
	else 
		lseek( fd , strlen( amrStr[AmrType] ) + offsetForIdFile  , SEEK_SET );

	AmrStruct = (AMRStruct*)malloc( sizeof( AMRStruct ) ) ;
	if( !AmrStruct )
		goto error ;
	memset( AmrStruct , 0 , sizeof( AMRStruct ) ) ;
	AmrStruct->AmrType = AmrType ;
	//AmrStruct->fp  = fp ; 
	AmrStruct->fd  = fd ; 
	if( AmrType >=  AMR_NB_MC )
	{
		//fread( &(AmrStruct->nChannels ) , 2 , 1 , fp )  ;
		//fread( &(AmrStruct->nChannels ) , 2 , 1 , fp )  ;
		read( fd , &(AmrStruct->nChannels ) , 2  )  ;
		read( fd , &(AmrStruct->nChannels ) , 2  )  ;

		AmrStruct->Channel_Struct = AmrStruct->Channel_Struct ;
		if( AmrStruct->nChannels < 4 )
			AmrStruct->Channel_Struct ++ ;
	}
	else
	{
		AmrStruct->nChannels = 1  ;
		AmrStruct->Channel_Struct = SINGLE_CHANNEL ;
	}
	AmrStruct->ChannelBuffer[0]  = AmrStruct->BufferPointer ;
	for( n = 1  ; n <  AmrStruct->nChannels ; n ++ )
		AmrStruct->ChannelBuffer[n] = AmrStruct->ChannelBuffer[n-1] + MAXBYTESOFONFRAME ;	

	if( (AmrType == AMR_WB_SC ) || (AmrType == AMR_WB_MC) )
		AmrStruct->SampleRate = 16000 ;
	else
		AmrStruct->SampleRate = 8000 ;

	InitFrameBitOrder() ;
	return AmrStruct ;

error: 
	   if( fd )
		   close( fd ) ;
		//if( fp )
		 //  fclose( fp ) ;
	   if( !AmrStruct )
		   free( AmrStruct ) ;
	   return 0 ;	
}




/*
 *	Function		:	CreateAmrFile
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Create a new  a amr file for writing 
 *	Entry			:	AmrName -- Amr file name 
 *
 *	Return			:	AmrStruct -- AMRStruct*
 *						The struct to collect amr file information 
 *						
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */

/* The start string of AMR file : Norrow-band single-channel, Norrow-band single-channel,
   Wide-band single-channel,  Wide-band multi-channel */
//const char* amrStr[4] = { "#!AMR\n" , "#!AMR-WB\n" , "#!AMR_MC1.0\n" , "#!AMR-WB_MC1.0\n" } ;
AMRStruct* CreateAmrFile(char* AmrName , enum AmrFileType amrfiletype , enum ChannelStruct channelstruct , int bCreateFile ) 
{
	FILE* fp = 0  ; 	
	unsigned long bytes ;
	AMRStruct* AmrStruct = 0  ;
	if( bCreateFile )
	{
		fp = fopen( AmrName , "wb" ) ;
		if( !fp ) 
			goto error  ; 
	}

	AmrStruct =(AMRStruct*) malloc( sizeof( AMRStruct ) ) ;
	if( ! AmrStruct )
		goto error  ; 
	memset( AmrStruct , 0 , sizeof( AMRStruct ) ) ;

	strcpy( (char*)AmrStruct->AmrFileHead ,  amrStr[ amrfiletype] ) ;
	AmrStruct->AmrFileHeadLength = strlen( amrStr[ amrfiletype] ) ;
	if ( (amrfiletype == AMR_NB_MC)  || (amrfiletype == AMR_WB_MC) )
	{
		bytes = channelstruct ;
		memcpy( AmrStruct->AmrFileHead + strlen( amrStr[ amrfiletype] ),   &bytes , 4  );
		AmrStruct->AmrFileHeadLength += 4 ;
	}

	if( bCreateFile )
	{
		bytes = fwrite( AmrStruct->AmrFileHead , 1 , AmrStruct->AmrFileHeadLength , fp ) ;
		if( bytes != AmrStruct->AmrFileHeadLength ) 
			goto error;
	}

	AmrStruct->AmrType =  amrfiletype ; 
	AmrStruct->fp = fp ; 
	AmrStruct->Channel_Struct = channelstruct ;
	AmrStruct->nChannels = channelstruct + 1 ;
	AmrStruct->ChannelBuffer[0] = AmrStruct->BufferPointer ; 
	for( bytes = 1 ; bytes <   AmrStruct->nChannels  ; bytes ++ )
		AmrStruct->ChannelBuffer[bytes] = AmrStruct->ChannelBuffer[bytes-1] + MAXBYTESOFONFRAME ;
	 
	InitFrameBitOrder();
	return  AmrStruct ;
error:
	if( fp )
		fclose( fp ) ;
	if( AmrStruct )
		free( AmrStruct ) ;
	return 0 ;

}

/*
 *	Function		:	ReadOneFrameBlock
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Get the bytes  of one frame block  from amr file
 *	Entry			:	AmrStruct -- AMRStruct , The struct to collect amr file information 
 *
 *	Return			:	short
 *						1, if success
 *						0, if Fail
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */

short ReadOneFrameBlock( AMRStruct* AmrStruct  ) 
{
	unsigned long bytes ;
	int frametype  ;
	int  nF  ;

	for(  nF  = 0 ; nF < AmrStruct->nChannels ;  nF ++ )
	{
		//bytes  = fread( AmrStruct->ChannelBuffer[nF] , 1 , 1 , AmrStruct->fp );

		bytes  = read( AmrStruct->fd , AmrStruct->ChannelBuffer[nF] , 1   );
		if( bytes <= 0 )
			return 0 ;		
		frametype  =  (AmrStruct->ChannelBuffer[nF][0] >> 3 )&15 ;
//		printf( " Read frametype = %d and  bit_Byte_Number = %d\n" , frametype , bit_Byte_Number[frametype][1] ) ;
		//bytes  = fread( &AmrStruct->ChannelBuffer[nF][1] , 1 , bit_Byte_Number[frametype][1] , AmrStruct->fp );
		bytes  = read(  AmrStruct->fd ,  &AmrStruct->ChannelBuffer[nF][1] ,  bit_Byte_Number[frametype][1] );
		if( bytes != bit_Byte_Number[frametype][1] )
		{
//			printf( " Error to Read");
			return 0 ;
		}
	}
	return 1 ;
}




/*
 *	Function		:	WriteOneFrameBlock
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Write the bytes  of one frame block  from amr file
 *	Entry			:	AmrStruct -- AMRStruct , The struct to collect amr file information 
 *
 *	Return			:	short
 *						1, if success
 *						0, if Fail
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */

short WriteOneFrameBlock( AMRStruct* AmrStruct  ) 
{
	unsigned long bytes ;
	int frametype  ;
	int  nF  ;

	for(  nF  = 0 ; nF < AmrStruct->nChannels ;  nF ++ )
	{
		bytes  = fwrite( AmrStruct->ChannelBuffer[nF] , 1 , 1 , AmrStruct->fp );
		if( bytes <= 0 )
			return 0 ;

		frametype  =  (AmrStruct->ChannelBuffer[nF][0] >> 3 )&15 ;
//		printf( " frametype = %d and  bit_Byte_Number = %d\n" , frametype , bit_Byte_Number[frametype][1] ) ;
		bytes  = fwrite( &AmrStruct->ChannelBuffer[nF][1] , 1 , bit_Byte_Number[frametype][1] , AmrStruct->fp );
		if( bytes != bit_Byte_Number[frametype][1] )
		{
//			printf( "Error to write\n"  ) ;
			return 0 ;
		}
	}
	return 1 ;
}




/*
 *	Function		:	CloseAmrFile
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Close amrfile
 *	Entry			:	AmrStruct -- AMRStruct , The struct to collect amr file information 
 *
 *	Return			:	short
 *						1, if success
 *						0, if Fail
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */


short CloseAmrFile( AMRStruct* AmrStruct ) 
{
	int ret ;
	if(AmrStruct->fp)
		ret = fclose( AmrStruct->fp ) ; 
	if( AmrStruct->fd )
		ret = close( AmrStruct->fd ) ; 
	free( AmrStruct ) ; 
	return !ret   ;
}

