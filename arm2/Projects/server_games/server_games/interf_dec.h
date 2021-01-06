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
 * interf_dec.h
 *
 *
 * Project:
 *    AMR Floating-Point Codec
 *
 * Contains:
 *    Defines interface to AMR decoder
 *
 */

#ifndef _interf_dec_h_
#define _interf_dec_h_

/*
 * Function prototypes
 */
/*
 * Conversion from packed bitstream to endoded parameters
 * Decoding parameters to speech
 */
void D_IF_decode(

      unsigned char *bits,


      short *synth);

/*
 * Reserve and init. memory
 */
void D_IF_init( void );

/*
 * Exit and free memory
 */
void D_IF_exit();

#endif

