/* locale.h standard header */
#ifndef _LOCALE
#define _LOCALE

#ifndef _SYSTEM_BUILD
  #pragma system_include
#endif

#ifndef _YVALS
  #include <yvals.h>
#endif

_C_STD_BEGIN

                /* Module consistency. */
#pragma rtmodel="__dlib_full_locale_support",\
  _STRINGIFY(_DLIB_FULL_LOCALE_SUPPORT)
                /* MACROS */
#ifndef NULL
  #define NULL   _NULL
#endif /* NULL */

                /* LOCALE CATEGORY INDEXES */
#define _LC_COLLATE             0
#define _LC_CTYPE               1
#define _LC_MONETARY            2
#define _LC_NUMERIC             3
#define _LC_TIME                4
#define _LC_MESSAGE             5
        /* ADD YOURS HERE, THEN UPDATE _NCAT */
#define _NCAT                   6       /* one more than last index */

                /* LOCALE CATEGORY MASKS */
#define _CATMASK(n)     (1 << (n))

#define _M_COLLATE      _CATMASK(_LC_COLLATE)
#define _M_CTYPE        _CATMASK(_LC_CTYPE)
#define _M_MONETARY     _CATMASK(_LC_MONETARY)
#define _M_NUMERIC      _CATMASK(_LC_NUMERIC)
#define _M_TIME         _CATMASK(_LC_TIME)
#define _M_MESSAGE      _CATMASK(_LC_MESSAGE)
#define _M_ALL          (_CATMASK(_NCAT) - 1)

                /* LOCALE CATEGORY HANDLES */
#define LC_COLLATE      _CATMASK(_LC_COLLATE)
#define LC_CTYPE        _CATMASK(_LC_CTYPE)
#define LC_MONETARY     _CATMASK(_LC_MONETARY)
#define LC_NUMERIC      _CATMASK(_LC_NUMERIC)
#define LC_TIME         _CATMASK(_LC_TIME)
#define LC_MESSAGE      _CATMASK(_LC_MESSAGE)
#define LC_MESSAGES     _CATMASK(_LC_MESSAGE)
#define LC_ALL          (_CATMASK(_NCAT) - 1)

                /* MACROS FOR LOCKING GLOBAL LOCALES */
#if _GLOBAL_LOCALE
  #define _Locklocale()         _Locksyslock(_LOCK_LOCALE)
  #define _Unlocklocale()       _Unlocksyslock(_LOCK_LOCALE)

#else /* _GLOBAL_LOCALE */
  #define _Locklocale()         (void)0
  #define _Unlocklocale()       (void)0
#endif /* _GLOBAL_LOCALE */

                /* TYPE DEFINITIONS */
struct lconv
{       /* locale-specific information */
  /* controlled by LC_MONETARY */
  char *currency_symbol;
  char *int_curr_symbol;
  char *mon_decimal_point;
  char *mon_grouping;
  char *mon_thousands_sep;
  char *negative_sign;
  char *positive_sign;

  char frac_digits;
  char n_cs_precedes;
  char n_sep_by_space;
  char n_sign_posn;
  char p_cs_precedes;
  char p_sep_by_space;
  char p_sign_posn;

  char int_frac_digits;

  /* controlled by LC_NUMERIC */
  char *decimal_point;
  char *grouping;
  char *thousands_sep;
  char *_Frac_grouping;
  char *_Frac_sep;
  char *_False;
  char *_True;

  /* controlled by LC_MESSAGE */
  char *_No;
  char *_Yes;
};

struct _Linfo;

                /* DECLARATIONS */
_C_LIB_DECL
__INTRINSIC struct lconv *localeconv(void);
#if _DLIB_FULL_LOCALE_SUPPORT
  __INTRINSIC char *setlocale(int, const char *);
#endif
_END_C_LIB_DECL

_C_STD_END
#endif /* _LOCALE */

#ifdef _STD_USING
  using _CSTD lconv; using _CSTD localeconv;
  #if _DLIB_FULL_LOCALE_SUPPORT
    using _CSTD setlocale;
  #endif
#endif /* _STD_USING */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
