/*****************************************************************************
 *       This file contains modules floating point exception flags.
 *
 *       Copyright 1998-2005 IAR Systems. All rights reserved.
 * 
 *       $Revision: 1.6 $
 *
 *****************************************************************************/


#pragma language=extended

/*
 * Note: The only exceptions that can coincide are Overflow with Inexact
 * and Underflow with Inexact. The composed flags are for efficient
 * usage of the flags. 
 */

#ifndef MATHFLOATFLAGS_H
#define MATHFLOATFLAGS_H

#ifdef __IAR_SYSTEMS_ICC__

__intrinsic unsigned int __getFpStatus( void );
__intrinsic unsigned int __clearFpStatus( void );
__intrinsic unsigned int __setFpStatus( unsigned int new_status );

#endif

#define FE_INVALID_BIT      0     // Invalid Operation
#define FE_DIVBYZERO_BIT    1     // Division By Zero
#define FE_OVERFLOW_BIT     2     // Overflow
#define FE_UNDERFLOW_BIT    3     // Underflow
#define FE_INEXACT_BIT      4     // Inexact

#define FE_INVALID      (1<<FE_INVALID_BIT)    // Invalid Operation
#define FE_DIVBYZERO    (1<<FE_DIVBYZERO_BIT)  // Division By Zero
#define FE_OVERFLOW     (1<<FE_OVERFLOW_BIT)   // Overflow
#define FE_UNDERFLOW    (1<<FE_UNDERFLOW_BIT)  // Underflow
#define FE_INEXACT      (1<<FE_INEXACT_BIT)    // Inexact

#define FE_OVERF_INEX   (FE_OVERFLOW | FE_INEXACT)    // FE_OVERFLOW + FE_INEXACT
#define FE_UNDERF_INEX  (FE_UNDERFLOW | FE_INEXACT)   // FE_UNDERFLOW + FE_INEXACT

#endif

#pragma language=default

