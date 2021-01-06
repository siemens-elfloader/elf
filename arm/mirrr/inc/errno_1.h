/* errno.h standard header */
#ifndef _ERRNO
#define _ERRNO

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#ifndef _YVALS
  #include <yvals.h>
#endif
_C_STD_BEGIN

                /* ERROR CODES */
#define EDOM    _EDOM
#define ERANGE  _ERANGE
#define EFPOS   _EFPOS
#define EILSEQ  _EILSEQ
        /* ADD YOURS HERE */
#define _NERR   _ERRMAX /* one more than last code */

                /* DECLARATIONS */
_C_LIB_DECL
#if !_MULTI_THREAD || _COMPILER_TLS && !_GLOBAL_LOCALE
  extern int _TLS_QUAL errno;

#else /* !_MULTI_THREAD || _COMPILER_TLS && !_GLOBAL_LOCALE */
  __INTRINSIC int *_Geterrno(void);

  #define errno (*_Geterrno())
#endif /* !_MULTI_THREAD || _COMPILER_TLS && !_GLOBAL_LOCALE */
_END_C_LIB_DECL
_C_STD_END
#endif /* _ERRNO */

#ifdef _STD_USING
  #ifndef errno
    using _CSTD errno;
  #endif
#endif /* _STD_USING */
/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
