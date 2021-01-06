/* stddef.h standard header */
#ifndef _STDDEF
#define _STDDEF

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#ifndef _YVALS
 #include <yvals.h>
#endif

#include <ysizet.h>
_C_STD_BEGIN

                /* macros */
#ifndef NULL
  #define NULL   _NULL
#endif /* NULL */

#ifndef offsetof
  #define offsetof(T, member)     (__INTADDR__((&((T *)0)->member)))
#endif /* offsetof */

                /* type definitions */
#if !defined(_PTRDIFF_T) && !defined(_PTRDIFFT)
  #define _PTRDIFF_T
  #define _PTRDIFFT
  #define _STD_USING_PTRDIFF_T
  typedef _Ptrdifft ptrdiff_t;
#endif /* !defined(_PTRDIFF_T) && !defined(_PTRDIFFT) */

#ifndef _WCHART
  #define _WCHART
  typedef _Wchart wchar_t;
#endif /* _WCHART */
_C_STD_END

#if defined(_STD_USING) && defined(__cplusplus)
  #ifdef _STD_USING_PTRDIFF_T
using _CSTD ptrdiff_t;
  #endif /* _STD_USING_PTRDIFF_T */
#endif /* defined(_STD_USING) && defined(__cplusplus) */

#endif /* _STDDEF */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
