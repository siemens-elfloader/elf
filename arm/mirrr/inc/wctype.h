/* wctype.h standard header */
#ifndef _WCTYPE
#define _WCTYPE

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#ifndef _YVALS
  #include <yvals.h>
#endif

#include <xlocale.h>

_C_STD_BEGIN

                /* MACROS */
#define WEOF    ((wint_t)(-1))

                /* TYPE DEFINITIONS */
typedef _Sizet wctrans_t;
typedef _Sizet wctype_t;

#ifndef _WINTT
  #define _WINTT
  typedef _Wintt wint_t;
#endif

                /* ctype DECLARATIONS */
_C_LIB_DECL
__INTRINSIC int _Iswctype(wint_t, wctype_t);
__INTRINSIC wint_t _Towctrans(wint_t, wctrans_t);
__INTRINSIC wctrans_t wctrans(const char *);
__INTRINSIC wctype_t wctype(const char *);

__INTRINSIC int iswalnum(wint_t);
__INTRINSIC int iswalpha(wint_t);
#if _DLIB_ADD_C99_SYMBOLS
  __INTRINSIC int iswblank(wint_t);
#endif /* _DLIB_ADD_C99_SYMBOLS */
__INTRINSIC int iswcntrl(wint_t);
__INTRINSIC int iswctype(wint_t, wctype_t);
__INTRINSIC int iswdigit(wint_t);
__INTRINSIC int iswgraph(wint_t);
__INTRINSIC int iswlower(wint_t);
__INTRINSIC int iswprint(wint_t);
__INTRINSIC int iswpunct(wint_t);
__INTRINSIC int iswspace(wint_t);
__INTRINSIC int iswupper(wint_t);
__INTRINSIC int iswxdigit(wint_t);
__INTRINSIC wint_t towlower(wint_t);
__INTRINSIC wint_t towupper(wint_t);
__INTRINSIC wint_t towctrans(wint_t, wctrans_t);

_END_C_LIB_DECL

#pragma inline
int iswctype(wint_t _Wc, wctype_t _Off)
{       /* test for ctype category */
  return (_Iswctype(_Wc, _Off));
}

#pragma inline
int iswalnum(wint_t _Wc)
{       /* test for alnum */
  return (   iswalpha(_Wc)
          || iswdigit(_Wc));
}

#if _DLIB_ADD_C99_SYMBOLS
  #pragma inline
  int iswblank(wint_t _Wc)
  {       /* test for blank */
    return (   _Wc == L' '
            || _Wc == L'\t'
            || iswspace(_Wc));
  }
#endif /* _DLIB_ADD_C99_SYMBOLS */

#pragma inline
int iswgraph(wint_t _Wc)
{       /* test for graph */
  return (   iswpunct(_Wc)      /* All printable, except iswspace */
          || iswalnum(_Wc));
}

#pragma inline
int iswprint(wint_t _Wc)
{       /* test for graph */
  return (   iswpunct(_Wc)
          || iswalnum(_Wc)
          || (   iswspace(_Wc)
              && !iswcntrl(_Wc)));
}

#pragma inline
wint_t towctrans(wint_t _Wc, wctrans_t _Off)
{       /* translate by category */
  return (_Towctrans(_Wc, _Off));
}


#if !_DLIB_FULL_LOCALE_SUPPORT

  _EXTERN_C
  extern int _LOCALE_WITH_USED(iswalpha)(wint_t);
  extern int _LOCALE_WITH_USED(iswcntrl)(wint_t);
  extern int _LOCALE_WITH_USED(iswdigit)(wint_t);
  extern int _LOCALE_WITH_USED(iswlower)(wint_t);
  extern int _LOCALE_WITH_USED(iswpunct)(wint_t);
  extern int _LOCALE_WITH_USED(iswspace)(wint_t);
  extern int _LOCALE_WITH_USED(iswupper)(wint_t);
  extern int _LOCALE_WITH_USED(iswxdigit)(wint_t);
  extern wint_t _LOCALE_WITH_USED(towlower)(wint_t);
  extern wint_t _LOCALE_WITH_USED(towupper)(wint_t);
  _END_EXTERN_C


                /* INLINES, FOR C and C++ */
  #pragma inline
  int iswalpha(wint_t _Wc)
  {       /* test for alpha */
    return _LOCALE_WITH_USED(iswalpha)(_Wc);
  }

  #pragma inline
  int iswcntrl(wint_t _Wc)
  {       /* test for cntrl */
    return _LOCALE_WITH_USED(iswcntrl)(_Wc);
  }

  #pragma inline
  int iswdigit(wint_t _Wc)
  {       /* test for digit */
    return _LOCALE_WITH_USED(iswdigit)(_Wc);
  }

  #pragma inline
  int iswlower(wint_t _Wc)
  {       /* test for lower */
    return _LOCALE_WITH_USED(iswlower)(_Wc);
  }

  #pragma inline
  int iswpunct(wint_t _Wc)
  {       /* test for punct */
    return _LOCALE_WITH_USED(iswpunct)(_Wc);
  }

  #pragma inline
  int iswspace(wint_t _Wc)
  {       /* test for space */
    return _LOCALE_WITH_USED(iswspace)(_Wc);
  }

  #pragma inline
  int iswupper(wint_t _Wc)
  {       /* test for upper */
    return _LOCALE_WITH_USED(iswupper)(_Wc);
  }

  #pragma inline
  int iswxdigit(wint_t _Wc)
  {       /* test for xdigit */
    return _LOCALE_WITH_USED(iswxdigit)(_Wc);
  }

  #pragma inline
  wint_t towlower(wint_t _Wc)
  {       /* translate to lower */
    return _LOCALE_WITH_USED(towlower)(_Wc);
  }

  #pragma inline
  wint_t towupper(wint_t _Wc)
  {       /* translate to upper */
    return _LOCALE_WITH_USED(towupper)(_Wc);
  }

#endif /* !_DLIB_FULL_LOCALE_SUPPORT */

_C_STD_END
#endif /* _WCTYPE */

#ifdef _STD_USING
  using _CSTD wctrans_t; using _CSTD wctype_t; using _CSTD wint_t;

  using _CSTD iswalnum; using _CSTD iswalpha; using _CSTD iswcntrl;
  using _CSTD iswctype; using _CSTD iswdigit; using _CSTD iswgraph;
  using _CSTD iswlower; using _CSTD iswprint; using _CSTD iswpunct;
  using _CSTD iswspace; using _CSTD iswupper; using _CSTD iswxdigit;
  using _CSTD towctrans; using _CSTD towlower; using _CSTD towupper;
  using _CSTD wctrans; using _CSTD wctype;
  #if _DLIB_ADD_C99_SYMBOLS
    using _CSTD iswblank;
  #endif /* _DLIB_ADD_C99_SYMBOLS */
#endif /* _STD_USING */


/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
