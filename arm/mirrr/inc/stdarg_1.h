/* stdarg.h standard header wrapper */
#ifndef _STDARG
#define _STDARG

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#ifndef _YVALS
 #include <yvals.h>
#endif

_C_STD_BEGIN

_EXTERN_C
__intrinsic char *__va_start1(void);
_END_EXTERN_C

typedef __Va_list va_list;

#ifndef _VA_DEFINED
                /* type definitions */
  #ifndef __VA_STACK_ALIGN__
    #error "__VA_STACK_ALIGN__ not set up (check compiler)"
  #endif /* !__VA_STACK_ALIGN__ */
  #ifndef __VA_STACK_ALIGN_EXTRA_BEFORE__
    #error "_VA__STACK_ALIGN_EXTRA_BEFORE__ not set up (check compiler)"
  #endif /* !__VA_STACK_ALIGN_EXTRA_BEFORE__ */

                /* macros */
  #define va_start(ap, A) (ap._Ap = __va_start1())
  #define va_end(ap)      ((void) 0)

  #ifndef __VA_STACK_DECREASING__
  #define __VA_STACK_DECREASING__ 1
  #endif

  #define _SIZE_ON_STACK(T) \
          (((sizeof(T) + __VA_STACK_ALIGN__ - 1) / __VA_STACK_ALIGN__) * \
          __VA_STACK_ALIGN__)

  #if __VA_STACK_ALIGN_EXTRA_BEFORE__
    #define _STACK_ADJUST_AFTER(T) 0
  #else /* !__VA_STACK_ALIGN_EXTRA_BEFORE__ */
    #define _STACK_ADJUST_AFTER(T) (_SIZE_ON_STACK(T) - sizeof(T))
  #endif /* __VA_STACK_ALIGN_EXTRA_BEFORE__ */

  #if __VA_STACK_DECREASING__
    #define va_arg(ap, T) \
            (_SIZE_ON_STACK(T) == sizeof(T) \
                 ? (*(*(T **) &(ap)._Ap)++) \
                 : ((ap)._Ap += _SIZE_ON_STACK(T), \
                    *(T *) ((ap)._Ap - (sizeof(T) + _STACK_ADJUST_AFTER(T)))))
  #else /* !__VA_STACK_DECREASING__ */
    #define va_arg(ap, T) \
            (_SIZE_ON_STACK(T) == sizeof(T) \
                 ? (*--(*(T **) &(ap)._Ap)) \
                 : ((ap)._Ap -= _SIZE_ON_STACK(T), \
                    *(T *) ((ap)._Ap + _STACK_ADJUST_AFTER(T))))
  #endif /* __VA_STACK_DECREASING__ */

#else /* _VA_DEFINED */

  #define va_start(ap, A) _VA_START(ap, A)
  #define va_end(ap)      _VA_END(ap)
  #define va_arg(ap, T)   _VA_ARG(ap, T)

#ifdef _VA_COPY
  #define va_copy(d,s) _VA_COPY(d,s)
#endif

#endif /* !_VA_DEFINED */

#if _DLIB_ADD_C99_SYMBOLS
  #ifndef va_copy
    #define va_copy(d,s) ((d) = (s))
  #endif
#endif /* _DLIB_ADD_C99_SYMBOLS */

_C_STD_END

#ifdef _STD_USING
  using std::va_list;
#endif /* _STD_USING */
#endif /* _STDARG */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
