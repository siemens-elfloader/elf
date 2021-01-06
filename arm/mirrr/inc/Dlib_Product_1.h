#ifndef _DLIB_PRODUCTS_H_
#define _DLIB_PRODUCTS_H_

/*********************************************************************
*
*       Configuration
*
*********************************************************************/

#define _DLIB_THREAD_SUPPORT 2   /* enable system locking  */

/*********************************************************************
*
*       Defines for locking functions.
*
*********************************************************************/

#define _DLIB_THREAD_LOCK_ONCE_TYPE      unsigned
#define _DLIB_THREAD_LOCK_ONCE_MACRO(pCv, ifun) {if (*pCv == 0) ifun(); *pCv = 1;}
#define _DLIB_THREAD_LOCK_ONCE_TYPE_INIT 0

#endif


