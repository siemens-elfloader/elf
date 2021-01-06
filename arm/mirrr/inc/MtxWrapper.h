/***************************************************
 *
 * Callback interface to the library threads manager.
 *
 * Copyright (C) 2006 IAR Systems.  All rights reserved.
 *
 * $Revision: 1.1.2.1 $
 *
 * This is an experimental interface to allow a RTOS kernel
 * to register thread safe support with the prebuilt libraries.
 *
 * System locking is enable (malloc/free).
 * File locking is not enabled.
 * TLS (locking of library static data) is not enabled.
 *
 ***************************************************/

#ifndef _YVALS
  #include <yvals.h>
#endif
#include <DLib_Threads.h>

typedef void (*_MtxFuncPtr)(_Rmtx *m);

/* Functions to register the callbacks */

/* Register the init function (called by _Mtxinit()) */
void _MtxinitRegister(_MtxFuncPtr func);

/* Register the destroy function (called by _Mtxdst()) */
void _MtxdstRegister(_MtxFuncPtr func);

/* Register the lock function (called by _Mtxlock()) */
void _MtxlockRegister(_MtxFuncPtr func);

/* Register the unlock function (called by _Mtxunlock()) */
void _MtxunlockRegister(_MtxFuncPtr func);
