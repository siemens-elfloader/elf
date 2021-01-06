/* assert.h standard header */

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#ifndef _YVALS
 #include <yvals.h>
#endif
_C_STD_BEGIN

#undef assert   /* remove existing definition */

#ifdef NDEBUG
  #define assert(test)  ((void)0)
#else /* NDEBUG */
  _C_LIB_DECL
  __INTRINSIC void _Assert(const char *, const char *,
                           const char *, const char *);
  /* Debugger returns non-zero if user hits "Ignore" or "Debug". */
  __INTRINSIC int _ReportAssert(const char *, const char *,
                                const char *, const char *);
  __INTRINSIC void _EmptyStepPoint(void);
  _END_C_LIB_DECL

                /* Help function */

                /* MACROS */
  #define _FUNNAME      0
  #define _STRIZE(x)    _VAL(x)
  #define _VAL(x)       #x

  #ifdef _VERBOSE_DEBUGGING
    #include <stdio.h>
    #define assert(test) ((test) ? (void)_CSTD fprintf(stderr,          \
        __FILE__ ":" _STRIZE(__LINE__) " " #test " -- OK\n")            \
        : (_CSTD _Assert(__FILE__, _STRIZE(__LINE__), _FUNNAME, #test), \
                 _EmptyStepPoint()))
  #else /* _VERBOSE_DEBUGGING */
    #define assert(test) ((test) ? (void)0                              \
        : (_CSTD _Assert(__FILE__, _STRIZE(__LINE__), _FUNNAME, #test), \
                 _EmptyStepPoint()))
  #endif /* _VERBOSE_DEBUGGING */
#endif /* NDEBUG */
_C_STD_END

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
