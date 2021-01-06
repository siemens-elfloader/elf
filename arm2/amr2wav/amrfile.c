/*
* amr2wav 
* 2011
*/

#include "..\inc\swilib.h"
#include "amrfile.h"
#include "frmbtord.h"

const char* amrStr[4] = { "#!AMR\n" , "#!AMR-WB\n" , "#!AMR_MC1.0\n" , "#!AMR-WB_MC1.0\n" } ;

AMRStruct* OpenAmrFile(char* AmrName , unsigned int* pid , int isIdFile , int offsetForIdFile ) 
{
	char buf[15] ;	
	int		fd = -1 ;
	AMRStruct* AmrStruct = 0  ;
	enum AmrFileType AmrType ;
	short n ;
	
       fd = fopen(AmrName,A_ReadOnly+A_BIN,P_READ,0);


	if( fd == -1 )goto error ;
        
        fread( fd , buf , 15,0) ;
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
		lseek( fd , strlen( amrStr[AmrType] )  , SEEK_SET ,0,0);
	else 
		lseek( fd , strlen( amrStr[AmrType] ) + offsetForIdFile  , SEEK_SET,0,0 );

	AmrStruct = (AMRStruct*)malloc( sizeof( AMRStruct ) ) ;
        
	if( !AmrStruct )
		goto error ;
        
	memset( AmrStruct , 0 , sizeof( AMRStruct ) ) ;
	AmrStruct->AmrType = AmrType ;
	//AmrStruct->fp  = fp ; 
	AmrStruct->fd  = fd ; 
	if( AmrType >=  AMR_NB_MC )
	{
		fread( fd , &(AmrStruct->nChannels ) , 2  ,0)  ;
		fread( fd , &(AmrStruct->nChannels ) , 2 ,0 )  ;

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
		   fclose( fd ,0) ;
	   if( !AmrStruct )
		   mfree( AmrStruct ) ;
	   return 0 ;	
}



AMRStruct* CreateAmrFile(char* AmrName , enum AmrFileType amrfiletype , enum ChannelStruct channelstruct , int bCreateFile ) 
{
	int fp = 0  ; 	
unsigned long bytes ;
	AMRStruct* AmrStruct = 0  ;
	if( bCreateFile )
	{
                fp = fopen(AmrName,A_WriteOnly+A_BIN+A_Create+A_Truncate,P_WRITE,0);
		if( fp ==-1) 
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
		bytes = fwrite( fp,AmrStruct->AmrFileHead  , AmrStruct->AmrFileHeadLength , 0 ) ;
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
		fclose( fp ,0) ;
	if( AmrStruct )
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
		bytes  = fread( AmrStruct->fd , AmrStruct->ChannelBuffer[nF] , 1  ,0 );
		if( bytes <= 0 )return 0 ;		
		frametype  =  (AmrStruct->ChannelBuffer[nF][0] >> 3 )&15 ;
		bytes  = fread(  AmrStruct->fd ,  &AmrStruct->ChannelBuffer[nF][1] ,  bit_Byte_Number[frametype][1] ,0);
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

short WriteOneFrameBlock( AMRStruct* AmrStruct  ) 
{
	unsigned long bytes ;
	int frametype  ;
	int  nF  ;

	for(  nF  = 0 ; nF < AmrStruct->nChannels ;  nF ++ )
	{
		bytes  = fwrite(AmrStruct->fp, AmrStruct->ChannelBuffer[nF] , 1 , 0 );
		if( bytes <= 0 )
			return 0 ;

		frametype  =  (AmrStruct->ChannelBuffer[nF][0] >> 3 )&15 ;
		bytes  = fwrite(AmrStruct->fp, &AmrStruct->ChannelBuffer[nF][1]  , bit_Byte_Number[frametype][1] ,0  );
		if( bytes != bit_Byte_Number[frametype][1] )//error
		{
//			
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
	if(AmrStruct->fp) fclose( AmrStruct->fp ,0) ; 
	if( AmrStruct->fd ) fclose( AmrStruct->fd ,0) ; 
	mfree( AmrStruct ) ; 
	return 0  ;
}

