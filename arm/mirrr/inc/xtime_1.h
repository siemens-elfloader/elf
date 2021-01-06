/* xtime.h internal header */
#ifndef _XTIME
#define _XTIME

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#include <xtinfo.h>
_C_STD_BEGIN

                /* macros */
#define WDAY    1       /* to get day of week right */

                /* type definitions */
typedef struct
{       /* rule for daylight savings time */
  unsigned char wday, hour, day, mon, year;
} Dstrule;

                /* internal declarations */
_C_LIB_DECL
__INTRINSIC int _Daysto(int, int);
__INTRINSIC const char * _Gentime(const struct tm *, const _Tinfo *, char, 
                                  char,
                                  int *, char *);
__INTRINSIC Dstrule * _Getdst(const char *);
__INTRINSIC const char * _Gettime(const char *, int, int *);
__INTRINSIC int _Isdst(const struct tm *);
__INTRINSIC struct tm * _Ttotm(struct tm *, time_t, int);
__INTRINSIC time_t _Tzoff(void);

_END_C_LIB_DECL
_C_STD_END
#endif /* _XTIME */

/*
* Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
