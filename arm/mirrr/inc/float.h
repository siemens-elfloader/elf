/* float.h standard header -- IEEE 754 version */
#ifndef _FLOAT
#define _FLOAT

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#ifndef _YVALS
  #include <yvals.h>
#endif
_C_STD_BEGIN

                /* TYPE DEFINITIONS */

#if __SHORT_SIZE__ != 2
  #error "Float implementation assumes short is 2 bytes"
#endif

typedef struct
{       /* parameters for a floating-point type */
  int _Ddig, _Dmdig, _Dmax10e, _Dmaxe, _Dmin10e, _Dmine;
  union
  {       /* union of short array and all floats */
    unsigned short _Us[__LONG_DOUBLE_SIZE__ / 2];
    float _Float;
    double _Double;
    long double _Long_double;
  } _Deps, _Dmax, _Dmin;
} _Dvals;

                /* DECLARATIONS */
_C_LIB_DECL
extern const _Dvals _Dbl, _Flt, _Ldbl;
_END_C_LIB_DECL

                /* COMMON PROPERTIES */
#define FLT_RADIX       2
#if _DLIB_ADD_C99_SYMBOLS
  #define FLT_ROUNDS      1 /* Towards nearest */
  #define FLT_EVAL_METHOD 0 /* All operations are performed in own type */

                            /*
                             * If converting a floating-point number to
                             * and rhen back from a decimal number with
                             * DECIMAL_DIG digits then no information
                             * should be lost.
                             */

  #if __LONG_DOUBLE_SIZE__ == 10
    #define DECIMAL_DIG 21
  #elif __LONG_DOUBLE_SIZE__ == 8
    #define DECIMAL_DIG 17
  #else
    #define DECIMAL_DIG 10
  #endif
#endif /* _DLIB__ADD_C99_SYMBOLS */

                /* float properties */
#define FLT_EPSILON     _CSTD _Flt._Deps._Float
#define FLT_MAX         _CSTD _Flt._Dmax._Float
#define FLT_MIN         _CSTD _Flt._Dmin._Float

#define FLT_DIG         _CSTD _Flt._Ddig
#define FLT_MANT_DIG    _CSTD _Flt._Dmdig
#define FLT_MAX_10_EXP  _CSTD _Flt._Dmax10e
#define FLT_MAX_EXP     _CSTD _Flt._Dmaxe
#define FLT_MIN_10_EXP  _CSTD _Flt._Dmin10e
#define FLT_MIN_EXP     _CSTD _Flt._Dmine

                /* double properties */
#define DBL_EPSILON     _CSTD _Dbl._Deps._Double
#define DBL_MAX         _CSTD _Dbl._Dmax._Double
#define DBL_MIN         _CSTD _Dbl._Dmin._Double

#define DBL_DIG         _CSTD _Dbl._Ddig
#define DBL_MANT_DIG    _CSTD _Dbl._Dmdig
#define DBL_MAX_10_EXP  _CSTD _Dbl._Dmax10e
#define DBL_MAX_EXP     _CSTD _Dbl._Dmaxe
#define DBL_MIN_10_EXP  _CSTD _Dbl._Dmin10e
#define DBL_MIN_EXP     _CSTD _Dbl._Dmine

                /* long double properties */
#define LDBL_EPSILON    _CSTD _Ldbl._Deps._Long_double
#define LDBL_MAX        _CSTD _Ldbl._Dmax._Long_double
#define LDBL_MIN        _CSTD _Ldbl._Dmin._Long_double

#define LDBL_DIG        _CSTD _Ldbl._Ddig
#define LDBL_MANT_DIG   _CSTD _Ldbl._Dmdig
#define LDBL_MAX_10_EXP _CSTD _Ldbl._Dmax10e
#define LDBL_MAX_EXP    _CSTD _Ldbl._Dmaxe
#define LDBL_MIN_10_EXP _CSTD _Ldbl._Dmin10e
#define LDBL_MIN_EXP    _CSTD _Ldbl._Dmine

#ifdef _FLOAT_IS_DOUBLE
  #define _Flt _Dbl
#endif
#ifdef _LONG_DOUBLE_IS_DOUBLE
  #define _Ldbl _Dbl
#endif

_C_STD_END
#endif /* _FLOAT */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
