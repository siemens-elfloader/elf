/* signal.h standard header */
#ifndef _SIGNAL
#define _SIGNAL

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#ifndef _YVALS
 #include <yvals.h>
#endif
_C_STD_BEGIN

                /* signal codes */
#define SIGABRT _SIGABRT
#define SIGINT  2
#define SIGILL  4
#define SIGFPE  8
#define SIGSEGV 11
#define SIGTERM 15
#define _NSIG   _SIGMAX /* one more than last code */

                /* signal return values */
#define SIG_DFL ((_CSTD _Sigfun *)0)
#define SIG_ERR ((_CSTD _Sigfun *)-1)
#define SIG_IGN ((_CSTD _Sigfun *)1)

_EXTERN_C
                /* type definitions */
typedef int sig_atomic_t;
typedef void _Sigfun(int);

                /* low-level functions */
__INTRINSIC _Sigfun * signal(int, _Sigfun *);
_END_EXTERN_C

_C_LIB_DECL             /* declarations */
__INTRINSIC int raise(int);
_END_C_LIB_DECL
_C_STD_END
#endif /* _SIGNAL */

#ifdef _STD_USING
using _CSTD sig_atomic_t; using _CSTD raise; using _CSTD signal;
#endif /* _STD_USING */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
