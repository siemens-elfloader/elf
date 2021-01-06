/* xmath.h internal header */
#ifndef _XMATH
#define _XMATH

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#include <errno.h>
#include <math.h>
#include <stddef.h>
#include <ymath.h>

_C_STD_BEGIN

                /* float properties */
#if __FLOAT_SIZE__ == 4
 /* IEEE 754 float properties */
  #if _F0 == 0
    #define _F1    1        /* big-endian */
  #else
    #define _F1    0        /* little-endian */
  #endif
  #define _FFRAC    ((unsigned short)((1 << _FOFF) - 1))
  #define _FMASK    ((unsigned short)(0x7fff & ~_FFRAC))
  #define _FMAX_    ((1U << (15 - _FOFF)) - 1)
  #define _FMAX     ((unsigned short)_FMAX_)
  #define _FSIGN    ((unsigned short)0x8000)
  #define FSIGN(x)  (((unsigned short *)&(x))[_F0] & _FSIGN)
  #define FHUGE_EXP (int)(_FMAX * 900L / 1000)
  #define FHUGE_RAD 40.7  /* ~ 2^7 / pi */
  #define FSAFE_EXP ((unsigned short)(_FMAX >> 1))
#else
  #error "<xmath.h> __FLOAT_SIZE__ not 4"
#endif /* __FLOAT_SIZE__ */

                /* double properties */
#if __DOUBLE_SIZE__ == 8
 /* IEEE 754 double properties */
  #if _D0 == 0
    #define _D1    1      /* big-endian */
    #define _D2    2
    #define _D3    3
  #else
    #define _D1    2      /* little-endian */
    #define _D2    1
    #define _D3    0
  #endif
#elif __DOUBLE_SIZE__ == 4
  #if _D0 == 0
    #define _D1    1      /* big-endian */
    #define _D2    xxx    /* should never be used */
    #define _D3    xxx    /* should never be used */
  #else
    #define _D1    0      /* little-endian */
    #define _D2    xxx    /* should never be used */
    #define _D3    xxx    /* should never be used */
  #endif
#else
  #error "<xmath.h> __DOUBLE_SIZE__ not 4 or 8"
#endif /* __DOUBLE_SIZE__ */
#define _DFRAC  ((unsigned short)((1 << _DOFF) - 1))
#define _DMASK  ((unsigned short)(0x7fff & ~_DFRAC))
#define _DMAX_  ((1U << (15 - _DOFF)) - 1)
#define _DMAX   ((unsigned short)_DMAX_)
#define _DSIGN  ((unsigned short)0x8000)
#define DSIGN(x)        (((unsigned short *)&(x))[_D0] & _DSIGN)
#define HUGE_EXP        (int)(_DMAX * 900L / 1000)
#define HUGE_RAD        2.73e9  /* ~ 2^33 / pi */
#define SAFE_EXP        ((unsigned short)(_DMAX >> 1))

                /* long double properties */
#if __LONG_DOUBLE_SIZE__ == 10
 /* IEEE 754 long double properties */
  #if _L0 == 0
    #define _L1    1      /* big-endian */
    #define _L2    2
    #define _L3    3
    #define _L4    4
    #define _L5    xxx    /* should never be used, 128-bit only */
    #define _L6    xxx    /* should never be used, 128-bit only */
    #define _L7    xxx    /* should never be used, 128-bit only */
  #else
    #define _L1    3      /* little-endian */
    #define _L2    2
    #define _L3    1
    #define _L4    0
    #define _L5    xxx    /* should never be used, 128-bit only */
    #define _L6    xxx    /* should never be used, 128-bit only */
    #define _L7    xxx    /* should never be used, 128-bit only */
  #endif
  #define _LFRAC ((unsigned short)(-1))
  #define _LMASK ((unsigned short)0x7fff)
  #define _LMAX  ((unsigned short)0x7fff)
#elif __LONG_DOUBLE_SIZE__ == 8
  #if _L0 == 0
    #define _L1    1      /* big-endian */
    #define _L2    2
    #define _L3    3
    #define _L4    xxx    /* should never be used */
    #define _L5    xxx    /* should never be used, 128-bit only */
    #define _L6    xxx    /* should never be used, 128-bit only */
    #define _L7    xxx    /* should never be used, 128-bit only */
  #else
    #define _L1    2      /* little-endian */
    #define _L2    1
    #define _L3    0
    #define _L4    xxx    /* should never be used */
    #define _L5    xxx    /* should never be used, 128-bit only */
    #define _L6    xxx    /* should never be used, 128-bit only */
    #define _L7    xxx    /* should never be used, 128-bit only */
  #endif
  #define _LFRAC ((unsigned short)((1 << _LOFF) - 1))
  #define _LMASK ((unsigned short)(0x7fff & ~_LFRAC))
  #define _LMAX  ((unsigned short)((1 << (15 - _LOFF)) - 1))
#elif __LONG_DOUBLE_SIZE__ == 4
  #if _L0 == 0
    #define _L1    1      /* big-endian */
    #define _L2    xxx    /* should never be used */
    #define _L3    xxx    /* should never be used */
    #define _L4    xxx    /* should never be used */
    #define _L5    xxx    /* should never be used, 128-bit only */
    #define _L6    xxx    /* should never be used, 128-bit only */
    #define _L7    xxx    /* should never be used, 128-bit only */
  #else
    #define _L1    0      /* little-endian */
    #define _L2    xxx    /* should never be used */
    #define _L3    xxx    /* should never be used */
    #define _L4    xxx    /* should never be used */
    #define _L5    xxx    /* should never be used, 128-bit only */
    #define _L6    xxx    /* should never be used, 128-bit only */
    #define _L7    xxx    /* should never be used, 128-bit only */
  #endif
  #define _LFRAC ((unsigned short)((1 << _LOFF) - 1))
  #define _LMASK ((unsigned short)(0x7fff & ~_LFRAC))
  #define _LMAX_ ((1 << (15 - _LOFF)) - 1)
  #define _LMAX  ((unsigned short)_LMAX_)
#else
  #error "<xmath.h> __LONG_DOUBLE_SIZE__ not 4, 8 or 10"
#endif /* __LONG_DOUBLE_SIZE__ */
#define _LSIGN  ((unsigned short)0x8000)
#define LSIGN(x)        (((unsigned short *)&(x))[_L0] & _LSIGN)
#define LHUGE_EXP       (int)(_LMAX * 900L / 1000)
#define LHUGE_RAD       2.73e9  /* ~ 2^33 / pi */
#define LSAFE_EXP       ((unsigned short)(_LMAX >> 1))

                /* return values for _Stopfx/_Stoflt */
#define FL_ERR  0
#define FL_DEC  1
#define FL_HEX  2
#define FL_INF  3
#define FL_NAN  4
#define FL_NEG  8

_C_LIB_DECL
__INTRINSIC int _Stopfx(const char **, char **);
__INTRINSIC int _Stoflt(const char *, const char *, char **,
                        long[], int);
__INTRINSIC int _Stoxflt(const char *, const char *, char **,
                         long[], int);
__INTRINSIC int _WStopfx(const wchar_t **, wchar_t **);
__INTRINSIC int _WStoflt(const wchar_t *, const wchar_t *, wchar_t **,
                         long[], int);
__INTRINSIC int _WStoxflt(const wchar_t *, const wchar_t *, wchar_t **,
                          long[], int);

                /* double declarations */
__INTRINSIC double _Atan(double, int);
__INTRINSIC short _Dint(double *, short);
__INTRINSIC short _Dnorm(unsigned short *);
__INTRINSIC short _Dscale(double *, long);
__INTRINSIC double _Dtento(double, long);
__INTRINSIC short _Dunscale(short *, double *);
__INTRINSIC double _Hypot(double, double, int *);
__INTRINSIC double _Poly(double, const double *, int);
extern const _Dconst _Eps, _Rteps;
extern const double _Xbig, _Zero;

                /* float declarations */
#ifndef _FLOAT_IS_DOUBLE
  __INTRINSIC float _FAtan(float, int);
  __INTRINSIC short _FDint(float *, short);
  __INTRINSIC short _FDnorm(unsigned short *);
  __INTRINSIC short _FDscale(float *, long);
  __INTRINSIC float _FDtento(float, long);
  __INTRINSIC short _FDunscale(short *, float *);
  __INTRINSIC float _FHypot(float, float, int *);
  __INTRINSIC float _FPoly(float, const float *, int);
  extern const _Dconst _FEps, _FRteps;
  extern const float _FXbig, _FZero;
#endif /* _FLOAT_IS_DOUBLE */

                /* long double functions */
#ifndef _LONG_DOUBLE_IS_DOUBLE
  __INTRINSIC long double _LAtan(long double, int);
  __INTRINSIC short _LDint(long double *, short);
  __INTRINSIC short _LDnorm(unsigned short *);
  __INTRINSIC short _LDscale(long double *, long);
  __INTRINSIC long double _LDtento(long double, long);
  __INTRINSIC short _LDunscale(short *, long double *);
  __INTRINSIC long double _LHypot(long double, long double, int *);
  __INTRINSIC long double _LPoly(long double, const long double *, int);
  extern const _Dconst _LEps, _LRteps;
  extern const long double _LXbig, _LZero;
#endif /* _LONG_DOUBLE_IS_DOUBLE */
void _Feraise(int);
_END_C_LIB_DECL

_C_STD_END

#if !defined(_FLOATING_LESS_INLINES) && !defined(_FLOATING_NO_INLINES)
  _STD_BEGIN
  __INTRINSIC short _Dtest(double);
  __INTRINSIC short _Dunscale(short *, double *);
  #if __DOUBLE_SIZE__ == 4
    #include "xxtd.h"
    #pragma inline
    #include "xxdtest4.h"
    #pragma inline
    #include "xxdunscal4.h"
  #elif __DOUBLE_SIZE__ == 8
    #include "xxtd.h"
    #pragma inline
    #include "xxdtest8.h"
    #pragma inline
    #include "xxdunscal8.h"
  #else /* ! __DOUBLE_SIZE__ == 4 or 8 */
    #error "__DOUBLE_SIZE__ must be 4 or 8"
  #endif /* __DOUBLE_SIZE__ == 4 */
  #include "xxtundef.h"

  #ifndef _FLOAT_IS_DOUBLE
    __INTRINSIC short _FDtest(float);
    __INTRINSIC short _FDunscale(short *, float *);
    #include "xxtf.h"
    #pragma inline
    #include "xxdtest4.h"
    #pragma inline
    #include "xxdunscal4.h"
    #include "xxtundef.h"
  #endif /* _FLOAT_IS_DOUBLE */

  #ifndef _LONG_DOUBLE_IS_DOUBLE
    __INTRINSIC short _LDtest(long double);
    __INTRINSIC short _LDunscale(short *, long double *);
    #if __LONG_DOUBLE_SIZE__ == 4
      #include "xxtl.h"
      #pragma inline
      #include "xxdtest4.h"
      #pragma inline
      #include "xxdunscal4.h"
      #include "xxtundef.h"
    #elif __LONG_DOUBLE_SIZE__ == 8
      #include "xxtl.h"
      #pragma inline
      #include "xxdtest8.h"
      #pragma inline
      #include "xxdunscal8.h"
      #include "xxtundef.h"
    #endif /* __LONG_DOUBLE_SIZE__ */
  #endif /* _LONG_DOUBLE_IS_DOUBLE */
  _STD_END
#endif /* _FLOATING_LESS_INLINES && _FLOATING_NO_INLINES */


  /* Exception handling. */
#if _DLIB_FLOAT_ENVIRONMENT
  #include <fenv.h>

  #define _FE_INVALID   FE_INVALID
  #define _FE_DIVBYZERO FE_DIVBYZERO
  #define _FE_OVERFLOW  FE_OVERFLOW
  #define _FE_UNDERFLOW FE_UNDERFLOW
  #define _FE_INEXACT   FE_INEXACT

#else

  #define _FE_INVALID   (1 << 0)
  #define _FE_DIVBYZERO (1 << 1)
  #define _FE_OVERFLOW  (1 << 2)
  #define _FE_UNDERFLOW (1 << 3)
  #define _FE_INEXACT   (1 << 4)

#endif /* _DLIB_FLOAT_ENVIRONMENT */

_STD_BEGIN
#pragma inline=forced
void (_Feraise)(int except)
{	/* report floating-point exception */
  if ((except & (_FE_DIVBYZERO | _FE_INVALID)) != 0)
    errno = EDOM;
  else if ((except & (_FE_UNDERFLOW | _FE_OVERFLOW)) != 0)
    errno = ERANGE;
  #if _DLIB_FLOAT_ENVIRONMENT
    feraiseexcept(except);
  #endif
}
_STD_END


#endif /* _XMATH */

/*
 * Copyright (c) 1992-2001 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.10:0576 */
