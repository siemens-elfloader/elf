/*
* amr2wav 
* 2011
*/

#include "typedef.h"
#include "sp_dec.h"
#include "interf_rom.h"
#include "rom_dec.h"

/*
 * definition of constants
 */
#define EHF_MASK 0x0008 /* encoder homing frame pattern */
typedef

struct
{
   int reset_flag_old;   /* previous was homing frame */


   enum RXFrameType prev_ft;   /* previous frame type */
   enum Mode prev_mode;   /* previous mode */
   void *decoder_State;   /* Points decoder state */


}dec_interface_State;

#ifdef ETSI


static Word16 Bin2Int( Word16 no_of_bits, Word16 *bitstream )
{
   Word32 value, i, bit;


   value = 0;

   for ( i = 0; i < no_of_bits; i++ ) {
      value = value << 1;
      bit = *bitstream++;

      if ( bit == 0x1 )
         value = value + 1;
   }
   return( Word16 )( value );
}



static void Bits2Prm( enum Mode mode, Word16 bits[], Word16 prm[] )
{
   Word32 i;


   switch ( mode ) {
      case MR122:
         for ( i = 0; i < PRMNO_MR122; i++ ) {
            prm[i] = Bin2Int( bitno_MR122[i], bits );
            bits += bitno_MR122[i];
         }
         break;

      case MR102:
         for ( i = 0; i < PRMNO_MR102; i++ ) {
            prm[i] = Bin2Int( bitno_MR102[i], bits );
            bits += bitno_MR102[i];
         }
         break;

      case MR795:
         for ( i = 0; i < PRMNO_MR795; i++ ) {
            prm[i] = Bin2Int( bitno_MR795[i], bits );
            bits += bitno_MR795[i];
         }
         break;

      case MR74:
         for ( i = 0; i < PRMNO_MR74; i++ ) {
            prm[i] = Bin2Int( bitno_MR74[i], bits );
            bits += bitno_MR74[i];
         }
         break;

      case MR67:
         for ( i = 0; i < PRMNO_MR67; i++ ) {
            prm[i] = Bin2Int( bitno_MR67[i], bits );
            bits += bitno_MR67[i];
         }
         break;

      case MR59:
         for ( i = 0; i < PRMNO_MR59; i++ ) {
            prm[i] = Bin2Int( bitno_MR59[i], bits );
            bits += bitno_MR59[i];
         }
         break;

      case MR515:
         for ( i = 0; i < PRMNO_MR515; i++ ) {
            prm[i] = Bin2Int( bitno_MR515[i], bits );
            bits += bitno_MR515[i];
         }
         break;

      case MR475:
         for ( i = 0; i < PRMNO_MR475; i++ ) {
            prm[i] = Bin2Int( bitno_MR475[i], bits );
            bits += bitno_MR475[i];
         }
         break;

      case MRDTX:
         for ( i = 0; i < PRMNO_MRDTX; i++ ) {
            prm[i] = Bin2Int( bitno_MRDTX[i], bits );
            bits += bitno_MRDTX[i];
         }
         break;
   }
   return;
}

#else


enum Mode Decoder3GPP( Word16 *param, UWord8 *stream, enum RXFrameType
                      *frame_type, enum Mode *speech_mode )
{
   enum Mode mode;
   Word32 j;
   Word16 *mask;

  
   memset( param, 0, PRMNO_MR122 <<1 );
   mode = ( enum Mode )(0xF & *stream);
   *stream >>= 4;

   if ( mode == MRDTX ) {
      mask = order_MRDTX;

      for ( j = 5; j < 40; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }

      /* get SID type bit */

      *frame_type = RX_SID_FIRST;
      if (*stream)
         *frame_type = RX_SID_UPDATE;

      /* since there is update, use it */
      /* *frame_type = RX_SID_UPDATE; */
      stream++;

      /* speech mode indicator */
      *speech_mode = ( enum Mode )*stream;
   }
   else if ( mode == 15 ) {
      *frame_type = RX_NO_DATA;
   }
   else if ( mode == MR475 ) {
      mask = order_MR475;

      for ( j = 5; j < 100; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR515 ) {
      mask = order_MR515;

      for ( j = 5; j < 108; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR59 ) {
      mask = order_MR59;

      for ( j = 5; j < 123; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR67 ) {
      mask = order_MR67;

      for ( j = 5; j < 139; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR74 ) {
      mask = order_MR74;

      for ( j = 5; j < 153; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR795 ) {
      mask = order_MR795;

      for ( j = 5; j < 164; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR102 ) {
      mask = order_MR102;

      for ( j = 5; j < 209; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else if ( mode == MR122 ) {
      mask = order_MR122;

      for ( j = 5; j < 249; j++ ) {
         if ( *stream & 0x1 )
            param[ * mask] = ( short )( param[ * mask] + *( mask + 1 ) );
         mask += 2;

         if ( j % 8 )
            *stream >>= 1;
         else
            stream++;
      }
      *frame_type = RX_SPEECH_GOOD;
   }
   else
      *frame_type = RX_SPEECH_BAD;
   return mode;
}
#endif


void Decoder_Interface_reset( dec_interface_State *st )
{
   st->reset_flag_old = 1;
   st->prev_ft = RX_SPEECH_GOOD;
   st->prev_mode = MR475;   /* minimum bitrate */
}


void * Decoder_Interface_init( void )
{
   dec_interface_State * s;

   /* allocate memory */
   if ( ( s = ( dec_interface_State * ) malloc( sizeof( dec_interface_State ) ) ) ==
         NULL ) {
      //fprintf( stderr, "Decoder_Interface_init: "
           // "can not malloc state structure\n" );
      return NULL;
   }
   s->decoder_State = Speech_Decode_Frame_init( );

   if ( s->decoder_State == NULL ) {
      mfree( s );
      return NULL;
   }
   Decoder_Interface_reset( s );
   return s;
}



void Decoder_Interface_exit( void *state )
{
   dec_interface_State * s;
   s = ( dec_interface_State * )state;

   /* mfree memory */
   Speech_Decode_Frame_exit(s->decoder_State );
   mfree( s );
   s = NULL;
   state = NULL;
}



void Decoder_Interface_Decode( void *st,

#ifndef ETSI
      UWord8 *bits,

#else
      Word16 *bits,
#endif

      Word16 *synth, int bfi)
{
   enum Mode mode;   /* AMR mode */

#ifndef ETSI
   enum Mode speech_mode = MR475;   /* speech mode */
#endif

   Word16 prm[PRMNO_MR122];   /* AMR parameters */

   enum RXFrameType frame_type;   /* frame type */
   dec_interface_State * s;   /* pointer to structure */

   const Word16 *homing;   /* pointer to homing frame */
   Word16 homingSize;   /* frame size for homing frame */
   Word32 i;   /* counter */
   Word32 resetFlag = 1;   /* homing frame */


   s = ( dec_interface_State * )st;

#ifndef ETSI

   /*
    * extract mode information and frametype,
    * octets to parameters
    */
   mode = Decoder3GPP( prm, bits, &frame_type, &speech_mode );

   /*
    * if no mode information
    * guess one from the previous frame
    */
   if ( frame_type == RX_SPEECH_BAD ) {
      if ( s->prev_ft > 3 ) {
         frame_type = RX_SID_BAD;
         mode = MRDTX;
      }
      else {
         mode = s->prev_mode;
      }
   }
   else if ( frame_type == RX_NO_DATA ) {
      mode = s->prev_mode;
   }

   if ( bfi == 1 ) {
      if ( mode < 8 ) {
         frame_type = RX_SPEECH_BAD;
      }
      else if ( mode != 15 ) {
         frame_type = RX_SID_BAD;
      }
   }

#else
   bfi = 0;
   frame_type = bits[0];

   switch ( frame_type ) {
      case 0:
         frame_type = RX_SPEECH_GOOD;
         mode = bits[245];
         Bits2Prm( mode, &bits[1], prm );
         break;

      case 1:
         frame_type = RX_SID_FIRST;
         mode = s->prev_mode;
         break;

      case 2:
         frame_type = RX_SID_UPDATE;
         mode = s->prev_mode;
         Bits2Prm( MRDTX, &bits[1], prm );
         break;

      case 3:
         frame_type = RX_NO_DATA;
         mode = s->prev_mode;
         break;
   }

#endif

   /* test for homing frame */
   if ( s->reset_flag_old == 1 ) {
      switch ( mode ) {
         case MR122:
            homing = dhf_MR122;
            homingSize = 18;
            break;

         case MR102:
            homing = dhf_MR102;
            homingSize = 12;
            break;

         case MR795:
            homing = dhf_MR795;
            homingSize = 8;
            break;

         case MR74:
            homing = dhf_MR74;
            homingSize = 7;
            break;

         case MR67:
            homing = dhf_MR67;
            homingSize = 7;
            break;

         case MR59:
            homing = dhf_MR59;
            homingSize = 7;
            break;

         case MR515:
            homing = dhf_MR515;
            homingSize = 7;
            break;

         case MR475:
            homing = dhf_MR475;
            homingSize = 7;
            break;

         default:
            homing = NULL;
            homingSize = 0;
            break;
      }

      for ( i = 0; i < homingSize; i++ ) {
         resetFlag = prm[i] ^ homing[i];

         if ( resetFlag )
            break;
      }
   }

   if ( ( resetFlag == 0 ) && ( s->reset_flag_old != 0 ) ) {
      for ( i = 0; i < 160; i++ ) {
         synth[i] = EHF_MASK;
      }
   }
   else
      Speech_Decode_Frame( s->decoder_State, mode, prm, frame_type, synth );

   if ( s->reset_flag_old == 0 ) {
      /* check whole frame */
      switch ( mode ) {
         case MR122:
            homing = dhf_MR122;
            homingSize = PRMNO_MR122;
            break;

         case MR102:
            homing = dhf_MR102;
            homingSize = PRMNO_MR102;
            break;

         case MR795:
            homing = dhf_MR795;
            homingSize = PRMNO_MR795;
            break;

         case MR74:
            homing = dhf_MR74;
            homingSize = PRMNO_MR74;
            break;

         case MR67:
            homing = dhf_MR67;
            homingSize = PRMNO_MR67;
            break;

         case MR59:
            homing = dhf_MR59;
            homingSize = PRMNO_MR59;
            break;

         case MR515:
            homing = dhf_MR515;
            homingSize = PRMNO_MR515;
            break;

         case MR475:
            homing = dhf_MR475;
            homingSize = PRMNO_MR475;
            break;

         default:
            homing = NULL;
            homingSize = 0;
      }

      for ( i = 0; i < homingSize; i++ ) {
         resetFlag = prm[i] ^ homing[i];

         if ( resetFlag )
            break;
      }
   }

   /* reset decoder if current frame is a homing frame */
   if ( resetFlag == 0 ) {
      Speech_Decode_Frame_reset( s->decoder_State );
   }
   s->reset_flag_old = !resetFlag;
   s->prev_ft = frame_type;
   s->prev_mode = mode;
}
