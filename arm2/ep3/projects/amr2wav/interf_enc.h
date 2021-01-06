/*
 * ===================================================================
 *  TS 26.104
 *  R99   V3.4.0 2002-02
 *  REL-4 V4.3.0 2002-02
 *  3GPP AMR Floating-point Speech Codec
 * ===================================================================
 *
 */

/*
 * interf_enc.h
 *
 *
 * Project:
 *    AMR Floating-Point Codec
 *
 * Contains:
 *    Defines interface to AMR encoder
 *
 */

#ifndef _interf_enc_h_
#define _interf_enc_h_

/*
 * include files
 */
#include"sp_enc.h"
#define MAX_SERIAL_SIZE 244    /* max. num. of serial bits                 */
/*
 * Function prototypes
 */
/*
 * Encodes one frame of speech
 * Returns packed octets
 */
int Encoder_Interface_Encode( void *st, enum Mode mode, short *speech,

#ifndef ETSI
      unsigned char *serial,  /* max size 31 bytes */

#else
      short *serial, /* size 500 bytes */
#endif

      int forceSpeech );   /* use speech mode */

/*
 * Reserve and init. memory
 */
void *Encoder_Interface_init( int dtx );

/*
 * Exit and free memory
 */
void Encoder_Interface_exit( void *state );

typedef void Speech_Encode_FrameState; 



#endif
