/* limits.h standard header -- 8-bit version */
#ifndef _LIMITS
#define _LIMITS

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#ifndef _YVALS
  #include <yvals.h>
#endif

        /* CHAR PROPERTIES */
#define CHAR_BIT    __CHAR_BITS__

#define CHAR_MAX    __CHAR_MAX__
#define CHAR_MIN    __CHAR_MIN__

        /* INT PROPERTIES */
#define INT_MAX     __SIGNED_INT_MAX__
#define INT_MIN     __SIGNED_INT_MIN__
#define UINT_MAX    __UNSIGNED_INT_MAX__

        /* MULTIBYTE PROPERTIES */
#define MB_LEN_MAX  _MBMAX

        /* SIGNED CHAR PROPERTIES */
#define SCHAR_MAX   __SIGNED_CHAR_MAX__
#define SCHAR_MIN   __SIGNED_CHAR_MIN__

        /* SHORT PROPERTIES */
#define SHRT_MAX    __SIGNED_SHORT_MAX__
#define SHRT_MIN    __SIGNED_SHORT_MIN__

        /* LONG PROPERTIES */
#define LONG_MAX    __SIGNED_LONG_MAX__
#define LONG_MIN    __SIGNED_LONG_MIN__

        /* UNSIGNED PROPERTIES */
#define UCHAR_MAX   __UNSIGNED_CHAR_MAX__
#define USHRT_MAX   __UNSIGNED_SHORT_MAX__
#define ULONG_MAX   __UNSIGNED_LONG_MAX__

        /* LONG LONG PROPERTIES */
#ifdef _LONGLONG
  #define LLONG_MIN __SIGNED_LONGLONG_MIN__
  #define LLONG_MAX __SIGNED_LONGLONG_MAX__
  #define ULLONG_MAX __UNSIGNED_LONGLONG_MAX__
#endif /* _LONGLONG */

#endif /* _LIMITS */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
