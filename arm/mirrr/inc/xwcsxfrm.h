/* xwcsxfrm.h internal header */
#ifndef _XWCSXFRM
#define _XWCSXFRM

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#include <xstate.h>
#include <xwchar.h>
_C_STD_BEGIN

                /* declarations */
_C_LIB_DECL
__INTRINSIC int _Wcscollx(const wchar_t *, const wchar_t *, _Statab const *);
__INTRINSIC size_t _Wcsxfrmx(wchar_t *, const wchar_t *, size_t,
                             _Statab const *);

__INTRINSIC size_t _CWcsxfrm(wchar_t *, const wchar_t **, size_t,
                             mbstate_t *, _Statab const *);
_END_C_LIB_DECL
_C_STD_END
#endif /* _XWCSXFRM */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
