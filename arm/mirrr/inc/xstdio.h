/* xstdio.h internal header */
#ifndef _XSTDIO
#define _XSTDIO

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#ifndef _YVALS
  #include <yvals.h>
#endif
_C_STD_BEGIN

#if _DLIB_FILE_DESCRIPTOR
                /* bits for _Mode in FILE */
  #define _MOPENR 0x1
  #define _MOPENW 0x2
  #define _MOPENA 0x4
  #define _MTRUNC 0x8
  #define _MCREAT 0x10
  #define _MBIN   0x20
  #define _MALBUF 0x40
  #define _MALFIL 0x80
  #define _MEOF   0x100
  #define _MERR   0x200
  #define _MLBF   0x400
  #define _MNBF   0x800
  #define _MREAD  0x1000
  #define _MWRITE 0x2000
  #define _MBYTE  0x4000
  #define _MWIDE  0x8000

#endif /* _DLIB_FILE_DESCRIPTOR */

                /* codes for _Printf and _Scanf */
#define _FSP    0x01
#define _FPL    0x02
#define _FMI    0x04
#define _FNO    0x08
#define _FZE    0x10
#define _WMAX   (INT_MAX-9/10)


                /* macros for atomic file locking */
#if _FILE_OP_LOCKS
  #define _Lockfileatomic(str)          _Lockfile(str)
  #define _Unlockfileatomic(str)        _Unlockfile(str)

#else /* _FILE_OP_LOCKS */
  #define _Lockfileatomic(str)          (void)0
  #define _Unlockfileatomic(str)        (void)0
#endif /* _FILE_OP_LOCKS */

                /* type definitions */
#if !_DLIB_PRINTF_LONG_LONG
  #if __INTMAX_T_MAX__ > __SIGNED_LONG_MAX__
    #define _PRINTF_INTERNAL_QUALIFIER_J 0
  #endif
#endif

#ifndef _PRINTF_INTERNAL_QUALIFIER_J
  #define _PRINTF_INTERNAL_QUALIFIER_J 1
#endif


#if _DLIB_PRINTF_INT_TYPE_IS_LONG && !_DLIB_PRINTF_QUALIFIERS
  typedef   signed long int _PrintfSignedIntType;
  typedef unsigned long int _PrintfUnsignedIntType;
#elif _DLIB_PRINTF_INT_TYPE_IS_INT && !_DLIB_PRINTF_QUALIFIERS
  typedef   signed int _PrintfSignedIntType;
  typedef unsigned int _PrintfUnsignedIntType;
#elif !_DLIB_PRINTF_LONG_LONG
  typedef   signed long int _PrintfSignedIntType;
  typedef unsigned long int _PrintfUnsignedIntType;
#else
  typedef  _Longlong _PrintfSignedIntType;
  typedef _ULonglong _PrintfUnsignedIntType;
#endif

#define _PRINTF_INTERNAL_HAS_N2  _DLIB_PRINTF_SPECIFIER_FLOAT
#define _PRINTF_INTERNAL_HAS_NZ1 _DLIB_PRINTF_SPECIFIER_FLOAT
#define _PRINTF_INTERNAL_HAS_NZ2 _DLIB_PRINTF_SPECIFIER_FLOAT

#define _PRINTF_INTERNAL_HAS_NZ0 \
  (_DLIB_PRINTF_SPECIFIER_FLOAT || _DLIB_PRINTF_WIDTH_AND_PRECISION)

#if _DLIB_PRINTF_CHAR_BY_CHAR
  typedef void *(_PrintfPfnType)(void *, char);
#else
  typedef void *(_PrintfPfnType)(void *, const char *, size_t);
#endif


typedef struct
{       /* print formatting information */
  union
  {     /* long or long double value */
    _PrintfSignedIntType li;
    #if _DLIB_PRINTF_SPECIFIER_FLOAT
      long double ld;
    #endif
  } v;
  _PrintfPfnType * pfn;
  void *arg;
  char *s;
  char *ac;
  int n0;
  int n1;
  #if _PRINTF_INTERNAL_HAS_N2
    int n2;
  #endif
  #if _PRINTF_INTERNAL_HAS_NZ0
    int nz0;
  #endif
  #if _PRINTF_INTERNAL_HAS_NZ1
    int nz1;
  #endif
  #if _PRINTF_INTERNAL_HAS_NZ2
    int nz2;
  #endif
  int nchar;
  #if _DLIB_PRINTF_WIDTH_AND_PRECISION
    int prec,width;
  #endif
  #if _DLIB_PRINTF_FLAGS
    unsigned short flags;
  #endif
  #if _DLIB_PRINTF_QUALIFIERS
    char qual;
  #endif
} _Pft;
#define _PRINTF_BUFFERT_SIZE (_MAX_SIG_DIG + _MAX_EXP_DIG + 16)

typedef struct
{       /* scan formatting information */
  int (*pfn)(void *, int, int);
  void *arg;
  va_list ap;
  const char *s;
  int nchar, nget;
  #if _DLIB_SCANF_WIDTH
    int width;
  #endif
  #if _DLIB_SCANF_ASSIGNMENT_SUPPRESSING
    char noconv;
  #endif
  #if _DLIB_SCANF_QUALIFIERS
    char qual;
  #endif
  char stored;
} _Sft;

typedef struct _SNProutInfo
{	/* package buffer and count */
  char *s;
  size_t size;
  size_t count;
} _SNProutInfo;

typedef struct _SProutInfo
{	/* package buffer and count */
  char *s;
} _SProutInfo;

#if 0
  #ifndef _SYS_INT_TYPES_H
    typedef _Longlong intmax_t;
    typedef _ULonglong uintmax_t;
  #endif
#endif

                /* macros for _Scanf and friends */
#if !_DLIB_SCANF_LONG_LONG
  typedef   signed long int _ScanfSignedIntType;
  typedef unsigned long int _ScanfUnsignedIntType;
  #define _SCANF_INTERNAL_TO_SIGNED   strtol
  #define _SCANF_INTERNAL_TO_UNSIGNED strtoul
#else
  typedef  _Longlong _ScanfSignedIntType;
  typedef _ULonglong _ScanfUnsignedIntType;
  #define _SCANF_INTERNAL_TO_SIGNED   _Stoll
  #define _SCANF_INTERNAL_TO_UNSIGNED _Stoull
#endif

#if !_DLIB_SCANF_LONG_LONG
  #if __INTMAX_T_MAX__ > __SIGNED_LONG_MAX__
    #define _SCANF_INTERNAL_QUALIFIER_J 0
  #endif
#endif

#ifndef _SCANF_INTERNAL_QUALIFIER_J
  #define _SCANF_INTERNAL_QUALIFIER_J 1
#endif


#pragma inline
static int _Get(_Sft *px)
{ ++(px)->nchar; return (*(px)->pfn)((px)->arg, 0, 1); }
#pragma inline
static int _GetN(_Sft *px)
{ return (0 <= --(px)->nget ? _Get(px) : (++(px)->nchar, EOF)); }
#pragma inline
static void _Unget(_Sft *px, int ch)
{ --(px)->nchar; (*(px)->pfn)((px)->arg, ch, 0); }
#pragma inline
static void _UngetN(_Sft *px, int ch)
{
  if ((int)(ch) != EOF) _Unget(px, ch);
  else --(px)->nchar;
}
#define GET(px)       _Get(px)
#define GETN(px)      _GetN(px)
#define UNGET(px,ch)  _Unget(px,ch)
#define UNGETN(px,ch) _UngetN(px,ch)

#pragma inline
static char chvalid(unsigned char ch, unsigned char base)
{
  if (ch >= 'a')
  {
    ch -= 'a' - 10;
  }
  else if (ch >='A')
  {
    ch -= 'A' - 10;
  }
  else if (ch >= '0' && ch <= '9')
  {
    ch -= '0';
  }
  else
  {
    ch = 0xFF;
  }

  return ch < base;
}

                /* declarations */
_C_LIB_DECL
#if _DLIB_FILE_DESCRIPTOR
  __INTRINSIC FILE * _Fofind(void);
  __INTRINSIC FILE * _Foprep(const char *, const char *, FILE *, _FD_TYPE);
  __INTRINSIC _FD_TYPE _Fopen(const char *, unsigned int, const char *);
  __INTRINSIC int _Frprep(FILE *);
  __INTRINSIC int _Fwprep(FILE *);
#endif
__INTRINSIC int _Ftmpnam(char *, int);
__INTRINSIC void _Genld(_Pft *, char, char *, short, short);
__INTRINSIC int _Getfld(_Sft *);
__INTRINSIC int _Getfloat(_Sft *);
__INTRINSIC int _Getint(_Sft *);
__INTRINSIC int _Getstr(_Sft *, int);
__INTRINSIC void _Ldtob(_Pft *, char);
__INTRINSIC void _Litob(_Pft *, char);
__INTRINSIC int _Printf(_PrintfPfnType *,
                        void *, const char *, va_list *);
__INTRINSIC int _Putfld(_Pft *, va_list *, char);
__INTRINSIC int _Putstr(_Pft *, const wchar_t *);
__INTRINSIC int _Puttxt(_Pft *, const char *);
__INTRINSIC int _Putchar(_Pft *, char);
__INTRINSIC int _Putchars(_Pft *, const char *, int);
__INTRINSIC int _Scanf(int (*)(void *, int, int),
                       void *, const char *, va_list *);
__INTRINSIC int _Scin (void *str, int ch, int getfl);
__INTRINSIC int _FScin(void *str, int ch, int getfl);
__INTRINSIC int _SScin(void *str, int ch, int getfl);
__INTRINSIC _PrintfPfnType _Prout;
__INTRINSIC _PrintfPfnType _FProut;
__INTRINSIC _PrintfPfnType _SProut;
__INTRINSIC _PrintfPfnType _SNProut;
__INTRINSIC int _PrintfTiny(_PrintfPfnType *, void *, const char *, va_list *);


/* __INTRINSIC void _Vacopy(va_list *, va_list); */
_END_C_LIB_DECL
_C_STD_END
#endif /* _XSTDIO */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
