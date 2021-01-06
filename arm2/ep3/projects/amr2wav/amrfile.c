/*
* amr2wav
* 2011
*/

#include <swilib.h>
#include "amrfile.h"
#include "frmbtord.h"

const char* amrStr[4] = { "#!AMR\n" , "#!AMR-WB\n" , "#!AMR_MC1.0\n" , "#!AMR-WB_MC1.0\n" } ;

AMRStruct* OpenAmrFile(char* AmrName , unsigned int* pid , int isIdFile , int offsetForIdFile )
{
	char buf[15] ;
	FILE		*fp ;
	AMRStruct* AmrStruct = 0  ;
	enum AmrFileType AmrType ;
	short n ;

       fp = fopen(AmrName,"rb");




      fread( buf , 1 , 15 , fp ) ;
	AmrType =  AMR_NB_SC ;
	while ( AmrType < AMR_TYPE_NUM )
	{
		if( memcmp( buf , amrStr[AmrType] ,  strlen( amrStr[AmrType] ) ) == 0 )
			break ;
		AmrType ++  ;
	}

	if( AmrType >= AMR_TYPE_NUM )
		goto error ;

	fseek( fp , strlen( amrStr[AmrType] )  , SEEK_SET );
/*	if( !isIdFile  )
		fseek( fd , strlen( amrStr[AmrType] )  , SEEK_SET);
	else
		fseek( fd , strlen( amrStr[AmrType] ) + offsetForIdFile  , SEEK_SET);
*/
	AmrStruct = (AMRStruct*)malloc( sizeof( AMRStruct ) ) ;

	if( !AmrStruct )
		goto error ;

	memset( AmrStruct , 0 , sizeof( AMRStruct ) ) ;
	AmrStruct->AmrType = AmrType ;
	AmrStruct->fp  = fp ;
	//AmrStruct->fd  = fd ;
	if( AmrType >=  AMR_NB_MC )
	{
		fread( &(AmrStruct->nChannels ) , 2 , 1 , fp )  ;
		fread( &(AmrStruct->nChannels ) , 2 , 1 , fp )  ;

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
	   if( fp )
		   fclose( fp) ;
	   if( !AmrStruct )
		   mfree( AmrStruct ) ;
	   return 0 ;
}






short ReadOneFrameBlock( AMRStruct* AmrStruct  )
{
	unsigned long bytes ;
	int frametype  ;
	int  nF  ;

	for(  nF  = 0 ; nF < AmrStruct->nChannels ;  nF ++ )
	{
		bytes  = fread( AmrStruct->ChannelBuffer[nF] , 1 , 1 , AmrStruct->fp );
		if( bytes <= 0 )return 0 ;
		frametype  =  (AmrStruct->ChannelBuffer[nF][0] >> 3 )&15 ;
		bytes  = fread( &AmrStruct->ChannelBuffer[nF][1] , 1 , bit_Byte_Number[frametype][1] , AmrStruct->fp );
		if( bytes != bit_Byte_Number[frametype][1] )return 0 ;

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
	if(AmrStruct->fp) fclose( AmrStruct->fp) ;
	mfree( AmrStruct ) ;
	return 0  ;
}

