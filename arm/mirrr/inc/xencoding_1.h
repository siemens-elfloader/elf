/* xencoding.h internal header file */
/* Copyright (C) 2003 IAR Systems.  All rights reserved. */

#ifndef _XENCODING_H
#define _XENCODING_H

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#ifndef _YVALS
  #include <yvals.h>
#endif
#include <ysizet.h>
#include <xencoding_limits.h>
_C_STD_BEGIN

#ifndef _WCHART
  #define _WCHART
  typedef _Wchart wchar_t;
#endif /* _WCHART */

#ifndef _WINTT
  #define _WINTT
  typedef _Wintt wint_t;
#endif /* _WINT */

/* Encoding identifier. */

enum _EncodingId
{
  _EncodingSb_Id,                  /* Single byte encoding. */
  #ifdef _ENCODING_USE_UTF8
    _EncodingUtf8_Id,
  #endif

  _EncodingCount                /* Number of encondings. */
};

_C_LIB_DECL
__INTRINSIC int _EncodingSb_Mbtowc(wchar_t *pwc, const char *s,
                                   size_t nin, _Mbstatet *pst);
__INTRINSIC int _EncodingSb_Wctomb(char *s, wchar_t wc,
                                   _Mbstatet *pst);
#ifdef _ENCODING_USE_UTF8
  __INTRINSIC int _EncodingUtf8_Mbtowc(wchar_t *pwc, const char *s,
                                       size_t nin, _Mbstatet *pst);
  __INTRINSIC int _EncodingUtf8_Wctomb(char *s, wchar_t wc,
                                       _Mbstatet *pst);
#endif


#if !_DLIB_FULL_LOCALE_SUPPORT

  int _Mbtowc(wchar_t *, const char *, size_t, _Mbstatet *);
  int _Wctomb(char *, wchar_t, _Mbstatet *);

  #pragma inline
  int _Mbtowc(wchar_t * _WC, const char * _C, size_t _S, _Mbstatet * _ST)
  {
    return _ENCODING_WITH_USED(Mbtowc)(_WC, _C, _S, _ST);
  }

  #pragma inline
  int _Wctomb(char * _C, wchar_t _WC, _Mbstatet * _ST)
  {
    return _ENCODING_WITH_USED(Wctomb)(_C, _WC, _ST);
  }

#endif /* _DLIB_FULL_LOCALE_SUPPORT */

_END_C_LIB_DECL
_C_STD_END
#endif /* _XENCODING_H */
