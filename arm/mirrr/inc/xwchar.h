/* xwchar.h internal header */
#ifndef _XWCHAR
#define _XWCHAR

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#include <wchar.h>
#include <wctype.h>
#include <xstate.h>
#include <xencoding.h>
_C_STD_BEGIN

                /* DECLARATIONS */
_C_LIB_DECL
__INTRINSIC int _Mbtowc(wchar_t *, const char *, size_t, _Mbstatet *);
__INTRINSIC size_t _Wcsftime(wchar_t *, size_t, const char *, size_t,
                             const struct tm *);
__INTRINSIC int _Wctomb(char *, wchar_t, _Mbstatet *);
__INTRINSIC long double _WStold(const wchar_t *, wchar_t **, long);
__INTRINSIC _Longlong _WStoll(const wchar_t *, wchar_t **, int);
__INTRINSIC unsigned long _WStoul(const wchar_t *, wchar_t **, int);
__INTRINSIC _ULonglong _WStoull(const wchar_t *, wchar_t **, int);

__INTRINSIC int _Mbtowcx(wchar_t *, const char *, size_t, mbstate_t *,
                         _Statab *);
__INTRINSIC int _Wctombx(char *, wchar_t, mbstate_t *,
                         _Statab *, _Statab *);

__INTRINSIC _Statab const *_Getpcostate(void);
__INTRINSIC _Statab const *_Getpwcostate(void);

_END_C_LIB_DECL
_C_STD_END
#endif /* _XWCHAR */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
