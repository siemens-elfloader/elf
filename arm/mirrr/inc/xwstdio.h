/* xwstdio.h internal header */
#ifndef _XWSTDIO
#define _XWSTDIO

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#include <xstdio.h>
#include <xwchar.h>
_C_STD_BEGIN

                /* backup definition of va_copy */
#ifndef va_copy
  #define va_copy(dest, src)    (dest[0] = src[0])
#endif

                /* macros for _WScanf and friends */
#define WGET(px)        \
        (++(px)->nchar, (*(px)->pfn)((px)->arg, 0, 1))
#define WGETN(px)       (0 <= --(px)->nget ? WGET(px) \
        : (++(px)->nchar, WEOF))
#define WUNGET(px, ch)  \
        (--(px)->nchar, (*(px)->pfn)((px)->arg, ch, 0))
#define WUNGETN(px, ch) do if ((int)(ch) != WEOF) WUNGET(px, ch); \
        else --(px)->nchar; while (0)

                /* type definitions */
typedef struct
{       /* print formatting information */
  union
  {       /* long or long double value */
    _Longlong li;
    long double ld;
  } v;
  void *(*pfn)(void *, const wchar_t *, size_t);
  void *arg;
  wchar_t *s;
  int n0, nz0, n1, nz1, n2, nz2, nchar, prec, width;
  unsigned short flags;
  wchar_t qual;
} _WPft;

typedef struct
{       /* scan formatting information */
  wint_t (*pfn)(void *, wint_t, int);
  void *arg;
  va_list ap;
  const wchar_t *s;
  int nchar, nget, width;
  wchar_t qual;
  char noconv, stored;
} _WSft;

typedef struct
{       /* swprintf vswprintf information */
  wchar_t *s;
  size_t max;
} _WSPftArgs;


                /* declarations */
_C_LIB_DECL
#if _DLIB_FILE_DESCRIPTOR
  __INTRINSIC int _WFrprep(FILE *);
  __INTRINSIC int _WFwprep(FILE *);
#endif
__INTRINSIC void _WGenld(_WPft *, wchar_t, wchar_t *, short, short);
__INTRINSIC int _WGetfld(_WSft *);
__INTRINSIC int _WGetfloat(_WSft *);
__INTRINSIC int _WGetint(_WSft *);
__INTRINSIC int _WGetstr(_WSft *, int);
__INTRINSIC void _WLdtob(_WPft *, wchar_t);
__INTRINSIC void _WLitob(_WPft *, wchar_t);
__INTRINSIC int _WPrintf(void *(*)(void *, const wchar_t *, size_t),
                         void *, const wchar_t *, va_list *);
__INTRINSIC int _WPutstr(_WPft *, const char *);
__INTRINSIC int _WPutfld(_WPft *, va_list *, wchar_t, wchar_t *);
__INTRINSIC int _WPuttxt(_WPft *, const wchar_t *);
__INTRINSIC int _WScanf(wint_t (*)(void *, wint_t, int),
                        void *, const wchar_t *, va_list *);

__INTRINSIC wint_t _WScin (void *str, wint_t ch, int getfl);
__INTRINSIC wint_t _WSScin(void *str, wint_t ch, int getfl);
#if _DLIB_FILE_DESCRIPTOR
  __INTRINSIC wint_t _WFScin(void *str, wint_t ch, int getfl);
#endif

__INTRINSIC void *_WProut (void *, const wchar_t *, size_t);
__INTRINSIC void *_WSProut(void *, const wchar_t *, size_t);
#if _DLIB_FILE_DESCRIPTOR
  __INTRINSIC void *_WFProut(void *, const wchar_t *, size_t);
#endif

_END_C_LIB_DECL
_C_STD_END
#endif /* _XWSTDIO */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
