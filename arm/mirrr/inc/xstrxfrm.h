/* xstrxfrm.h internal header */
#ifndef _XSTRXFRM
#define _XSTRXFRM

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#include <string.h>
#include <xstate.h>
_C_STD_BEGIN

                /* TYPES */
typedef struct Xfrm
{       /* storage for transformations */
  const unsigned char *sbegin, *sin, *send;
  long weight;
  unsigned short phase, state, wc;
} Xfrm;

                /* DECLARATIONS */
_C_LIB_DECL
__INTRINSIC int _Strcollx(const char *, const char *, _Statab const *);
__INTRINSIC size_t _Strxfrmx(char *, const char *, size_t, _Statab const *);

__INTRINSIC size_t _CStrxfrm(char *, size_t, Xfrm *, _Statab const *);
_END_C_LIB_DECL
_C_STD_END
#endif /* _XSTRXFRM */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
