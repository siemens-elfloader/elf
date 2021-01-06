// iostream.h standard header
#ifndef _IOSTREAM_H_
#define _IOSTREAM_H_

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#include <istream>
_STD_BEGIN

                // OBJECTS
extern istream cin;
extern ostream cout;
_STD_END
 #if _HAS_NAMESPACE

using namespace std;
 #else
 #endif /* _HAS_NAMESPACE */
#endif /* _IOSTREAM_H_ */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
