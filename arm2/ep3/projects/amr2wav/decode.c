#include "typedef.h"
#include "bitparse.h"
#include "frmbtord.h"
#include "amrfile.h"
#include "wavefile.h"
#include "interf_dec.h"
#include "interf_enc.h"
#include "rom_dec.h"
#include "decode.h"

#define SERIAL_FRAMESIZE (1+MAX_SERIAL_SIZE+5)

extern short ParseOneFrameBits( Word16* serial, AMRStruct* AmrStruct, short nChannel ) ;
Word32 frame;

int decodeOneAmrFile( char* AmrName , char* WavNAme )
{

	typedef void Speech_Decode_FrameState ;


	AMRStruct*	AmrStruct = 0 ;
	WAVStruct*	WavStruct = 0 ;
	Speech_Decode_FrameState *speech_decoder_state = NULL;

	Word16 serial[SERIAL_FRAMESIZE];   /* coded bits                    */
	Word16* synth0[6];        // L_FRAME    /* Synthesis                     */
	Word16* synthBuffer = 0  ;
	Word16* synth ;

#if 0
    Word16  reset_flag = 0;
    Word16  reset_flag_old = 1;
#endif

    Word16
#if 0
      i ,
#endif
      n ;

#if 0
//  int rxframetypeMode = 1 ;           /* use RX frame type codes       */
    enum Mode mode = (enum Mode)0;
    enum RXFrameType rx_type = (enum RXFrameType)0;
    enum TXFrameType tx_type = (enum TXFrameType)0;
    #endif
	AmrStruct = OpenAmrFile( AmrName , 0 , 0 , 0 )  ;
	if( !AmrStruct )goto error ;

	synthBuffer = (Word16* ) malloc( AmrStruct->nChannels * L_FRAME * sizeof( Word16 ) ) ;

	if( !synthBuffer )goto error ;

	for( n = 0 ;  n < AmrStruct->nChannels ; n ++ )	synth0[ n ] = synthBuffer + n*L_FRAME ;


	WavStruct = CreateWaveFile( WavNAme, AmrStruct->nChannels , 16 , AmrStruct->SampleRate) ;

	if( !WavStruct )goto error ;

	speech_decoder_state = Decoder_Interface_init() ;

	if (!speech_decoder_state)goto error ;


	/*-----------------------------------------------------------------------*
	* process serial bitstream frame by frame                               *
	*-----------------------------------------------------------------------*/


	frame = 0;
	while ( ReadOneFrameBlock( AmrStruct )  )
	{
		++frame;
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

			Decoder_Interface_Decode( speech_decoder_state , (unsigned char*)serial , synth , 0 );
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


	/*-----------------------------------------------------------------------*
	* Close down speech decoder                                             *
	*-----------------------------------------------------------------------*/

	Decoder_Interface_exit(speech_decoder_state);
	CloseWaveFile( WavStruct );
	CloseAmrFile( AmrStruct );
	mfree(synthBuffer );

	return 1;

error:
	if( WavStruct )
		CloseWaveFile( WavStruct );
	if( AmrStruct )
		CloseAmrFile( AmrStruct );
	if( synthBuffer )
		mfree(synthBuffer );
	if(speech_decoder_state )
		Decoder_Interface_exit(speech_decoder_state);
	return 0 ;
}

