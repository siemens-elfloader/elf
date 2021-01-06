/*
This material and information (“Information”) is a trade secret owned
by VoiceAge Corporation and is strictly confidential and you agree to
keep this information confidential and to take all necessary measures
to maintain its secrecy. Without limiting the foregoing, VoiceAge
Corporation considers its confidential information, including, but not
limited to, source code and technical information, as an unpublished
proprietary trade secret.

If publication occurs, the following notice shall appear: Copyright ©
1996-2003 VoiceAge Corporation. All Rights Reserved.

No part of this material may be reproduced, stored in a retrieval
system, or transmitted, in any form or by any means, including, but
not limited to, photocopying, electronic or mechanical, recording, or
otherwise, without the prior written permission of VoiceAge
Corporation. VoiceAge Corporation assumes no responsibility for
errors or omissions. This material is subject to continuous
developments and improvements. All warranties implied or
expressed, including but not limited to, implied warranties of
merchantability, fitness for purpose, condition of title, noninfringement,
are excluded. In no event shall VoiceAge Corporation
and its suppliers be liable for any special, indirect or consequential
damages or any damages whatsoever arising out of or in connection
with the use of this information. The foregoing disclaimer shall apply
to the maximum extent permitted by applicable law, even if any
remedy fails its essential purpose.

ACELP®, and VoiceAge® are either registered
trademarks or trademarks of VoiceAge Corporation in Canada and/or
other countries. Any unauthorized use is strictly prohibited. *
*/

/*
 * encoder.c
 *
 *
 * Project:
 *    AMR Floating-Point Codec
 *
 * Contains:
 *     encoder main sample program
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include "typedef.h"
#include "interf_enc.h"



static void Usage(char* argv[])
{
   fprintf (stderr,
      "Usage of %s:\n\n"
      "[-dtx] mode speech_file bitstream_file \n\n"
      "mode = 0,     1,     2,    3,    4,    5,     6,     7\n"
      "       MR475, MR515, MR59, MR67, MR74, MR795, MR102, MR122 \n\n\n",
      argv[0]);
}
/*
 * main
 *
 *
 * Function:
 *    Speech encoder main program
 *
 *    Usage: encoder [dtx] mode speech_file bitstream_file 
 *
 *    Format for speech_file:
 *       Speech is read from a binary file of 16 bits data.
 *
 *
 *    Format for 3GPP IF2 bitstream file:
 *       Holds mode information and bits packed to octets.
 *       Size is from 1 byte to 31 bytes.
 *
 *
 *    mode        : MR475, MR515, MR59, MR67, MR74, MR795, MR102, MR122
 * Returns:
 *    0
 */
int main (int argc, char * argv[]){

   /* file strucrures */
	FILE * file_speech = NULL;
	FILE * file_encoded = NULL;

   /* input speech vector */
	short speech[160];

	enum Mode mode;

   /* counters */
	int byte_counter, frames = 0, bytes = 0;

   /* requested mode */
	int dtx = 0;

   /* bitstream filetype */
	unsigned char serial_data[32];

   /* Process command line options */

	printf("\n**************         VoiceAge Corporation        **************");
	printf("\n");
	printf("\n-------------      AMR-NB floating-point Encoder      ------------");
	printf("\n                   Compressed format : IF2 ");
	printf("\n");


	dtx = 0;

	if ((argc == 4)||(argc == 5)){
		if (strcmp(argv[1], "-dtx") == 0) {
			dtx = 1;
			argv++;
		}

		file_encoded = fopen(argv[3], "wb");
		if (file_encoded == NULL){
			Usage(argv);
			exit(-1);
		}
		file_speech = fopen(argv[2], "rb");
		if (file_speech == NULL){
			fclose(file_encoded);
			Usage(argv);
			exit(-1);
		}
		mode = (enum Mode) atoi(argv[1]);
		if ((mode < 0) || (mode > 7)) {	
			fclose(file_encoded);
			fclose(file_speech);
			Usage(argv);
			exit(-1);
		}
	}
	else {
		Usage(argv);
		exit(-1);
	}


   E_IF_init(dtx);


   /* read file */
   while (fread( speech, sizeof (Word16), 160, file_speech ) > 0)
   {
      /* read mode */

      frames ++;

      /* call encoder */
      byte_counter = E_IF_encode(mode, speech, serial_data);

      bytes += byte_counter;
      fwrite(serial_data, sizeof (UWord8), byte_counter, file_encoded );
      fflush(file_encoded);
   }
   E_IF_exit();


   fclose(file_speech);
   fclose(file_encoded);

   return 0;
}
