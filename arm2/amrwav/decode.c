/* 
 * File Name:       decodec.c
 * Author:			Han Josen
 * Start Date:		Dec 03 , 2003
 * Language:        Microsoft Visual C++ 6.0
 * Target:			Codec for AMR file
 * Summary:			This file contains the functions to decompress amr to wav
 *	 
 * Change Note:     
 */



#include <stdio.h>
#include "typedef.h"
//#include "n_proc.h"
//#include "cnst.h"
//#include "mode.h"
//#include "frame.h"
//#include "strfunc.h"
//#include "sp_dec.h"
//#include "d_homing.h"

#include "frmbtord.h"
#include "amrfile.h"
#include "wavefile.h"
#include "interf_dec.h"
#include "interf_enc.h"
#include "rom_dec.h"

#define SERIAL_FRAMESIZE (1+MAX_SERIAL_SIZE+5)


/*
 *	Function		:	DecodeAmrToWav
 *--------------------------------------------------------------------------------
 *	Purpose 		:	Decode AMR to wave 
 *	Entry			:	AmrName -- char* , The input Amr file file name 
 *						WavName -- char* , The output wave sample file name ( no head )
 *
 *	Return			:	static void
 *	External Ref.	:	
 *	Summary			:	
 *	Flowchart		:	
 *--------------------------------------------------------------------------------
 *	Note			:	
 *--------------------------------------------------------------------------------
 */

int decodeOneAmrFile( char* AmrName , char* WavNAme )
{

	typedef void Speech_Decode_FrameState ; 
#ifdef _IMPROVE_SPEED
  extern unsigned long GetWindowsTickCount() ;
  unsigned long t1 , t2 ;
#endif

	AMRStruct*	AmrStruct = 0 ;  	
	WAVStruct*	WavStruct = 0 ;
	Speech_Decode_FrameState *speech_decoder_state = NULL;

	Word16 serial[SERIAL_FRAMESIZE];   /* coded bits                    */
	Word16* synth0[6];        // L_FRAME    /* Synthesis                     */
	Word16* synthBuffer = 0  ;
	Word16* synth ;
	Word32 frame;

	Word16	reset_flag = 0;
	Word16	reset_flag_old = 1;
	Word16	i , n ;
	



	AmrStruct = OpenAmrFile( AmrName , 0 , 0 , 0 )  ;  	
	if( !AmrStruct )
		goto error ;
	synthBuffer = (Word16* ) malloc( AmrStruct->nChannels * L_FRAME * sizeof( Word16 ) ) ;
	if( !synthBuffer )
		goto error ;
	for( n = 0 ;  n < AmrStruct->nChannels ; n ++ )	
		synth0[ n ] = synthBuffer + n*L_FRAME ;	
	WavStruct = CreateWaveFile( WavNAme, AmrStruct->nChannels , 16 , AmrStruct->SampleRate ) ;
	if( !WavStruct )
		goto error ;
	speech_decoder_state = Decoder_Interface_init() ;
	if (!speech_decoder_state)
	  //exit(-1);
		goto error ;
	  

	/*-----------------------------------------------------------------------*
	* process serial bitstream frame by frame                               *
	*-----------------------------------------------------------------------*/

#ifdef _IMPROVE_SPEED
  t1 =  GetWindowsTickCount() ;  
#endif

	frame = 0;
	while ( ReadOneFrameBlock( AmrStruct )  ) 
	{
		++frame;
#ifdef DEBUG
		if ( (frame%50) == 0) {
		fprintf (stderr, "frame=%d\n  ", frame);
		}
#endif
		for( n = 0 ; n < AmrStruct->nChannels ; n ++ )
		{
			synth = synth0[n] ;
			if( ParseOneFrameBits(  serial, AmrStruct, n ) == 0 )
				break ;
#if 0
			rx_type = (enum RXFrameType)serial[0];
			mode = (enum Mode) serial[1+MAX_SERIAL_SIZE];
			if (rx_type == RX_NO_DATA) 
				mode = speech_decoder_state->prev_mode;			 
			else 
				speech_decoder_state->prev_mode = mode;			

			/* if homed: check if this frame is another homing frame */
			if (reset_flag_old == 1)			
			 /* only check until end of first subframe */
				reset_flag = decoder_homing_frame_test_first(&serial[1], mode);
			
			/* produce encoder homing frame if homed & input=decoder homing frame */
			if ((reset_flag != 0) && (reset_flag_old != 0))
			{
				for (i = 0; i < L_FRAME; i++)				
					synth[i] = EHF_MASK;				
			}
			else	
				 /* decode frame */				 
				 Speech_Decode_Frame(speech_decoder_state, mode, &serial[1],
									 rx_type, synth);			
#endif

			Decoder_Interface_Decode( speech_decoder_state , serial , synth , 0 );
#if 0
			/* if not homed: check whether current frame is a homing frame */
			if (reset_flag_old == 0)
				/* check whole frame */
				reset_flag = decoder_homing_frame_test(&serial[1], mode);
			
			/* reset decoder if current frame is a homing frame */
			if (reset_flag != 0)
				 Speech_Decode_Frame_reset(speech_decoder_state);			
			reset_flag_old = reset_flag;
#endif
		}
		
		WriteSeparateWaveFile( WavStruct , (unsigned char**)synth0 , AmrStruct->SampleRate/50 , AmrStruct->nChannels ) ;
	}

#ifdef _IMPROVE_SPEED
  t2 = GetWindowsTickCount() ;
  printf(" Frame num is %d \n  decode time is %ld  \n", frame ,  t2-t1 ) ;  
#endif

	/*-----------------------------------------------------------------------*
	* Close down speech decoder                                             *
	*-----------------------------------------------------------------------*/
	//Speech_Decode_Frame_exit(&speech_decoder_state);
	Decoder_Interface_exit(speech_decoder_state);
	CloseWaveFile( WavStruct );
	CloseAmrFile( AmrStruct ); 
	free(synthBuffer );

	return 1;

error:
	if( WavStruct )
		CloseWaveFile( WavStruct );
	if( AmrStruct )
		CloseAmrFile( AmrStruct ); 
	if( synthBuffer )
		free(synthBuffer );
	if(speech_decoder_state )
		Decoder_Interface_exit(speech_decoder_state);
	return 0 ;
}

