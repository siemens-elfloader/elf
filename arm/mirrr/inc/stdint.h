/* stdint.h standard header */
/* Copyright (C) 2003 IAR Systems.  All rights reserved. */
#ifndef _STDINT
#define _STDINT

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#ifndef _YVALS
#include <yvals.h>
#endif
_C_STD_BEGIN

/* Fixed size types. These are all optional. */
#ifdef __INT8_T_TYPE__
  typedef __INT8_T_TYPE__   int8_t;
  typedef __UINT8_T_TYPE__ uint8_t;
#endif /* __INT8_T_TYPE__ */

#ifdef __INT16_T_TYPE__
  typedef __INT16_T_TYPE__   int16_t;
  typedef __UINT16_T_TYPE__ uint16_t;
#endif /* __INT16_T_TYPE__ */

#ifdef __INT32_T_TYPE__
  typedef __INT32_T_TYPE__   int32_t;
  typedef __UINT32_T_TYPE__ uint32_t;
#endif /* __INT32_T_TYPE__ */

#ifdef __INT64_T_TYPE__
  typedef __INT64_T_TYPE__   int64_t;
  typedef __UINT64_T_TYPE__ uint64_t;
#endif /* __INT64_T_TYPE__ */

/* Types capable of holding at least a certain number of bits.
   These are not optional for the sizes 8, 16, 32, 64. */
typedef __INT_LEAST8_T_TYPE__   int_least8_t;
typedef __UINT_LEAST8_T_TYPE__ uint_least8_t;

typedef __INT_LEAST16_T_TYPE__   int_least16_t;
typedef __UINT_LEAST16_T_TYPE__ uint_least16_t;

typedef __INT_LEAST32_T_TYPE__   int_least32_t;
typedef __UINT_LEAST32_T_TYPE__ uint_least32_t;

/* This isn't really optional, but make it so for now. */
#ifdef __INT_LEAST64_T_TYPE__
  typedef __INT_LEAST64_T_TYPE__ int_least64_t;
#endif /* __INT_LEAST64_T_TYPE__ */
#ifdef __UINT_LEAST64_T_TYPE__
  typedef __UINT_LEAST64_T_TYPE__ uint_least64_t;
#endif /* __UINT_LEAST64_T_TYPE__ */

/* The fastest type holding at least a certain number of bits.
   These are not optional for the size 8, 16, 32, 64.
   For now, the 64 bit size is optional in IAR compilers. */
typedef __INT_FAST8_T_TYPE__   int_fast8_t;
typedef __UINT_FAST8_T_TYPE__ uint_fast8_t;

typedef __INT_FAST16_T_TYPE__   int_fast16_t;
typedef __UINT_FAST16_T_TYPE__ uint_fast16_t;

typedef __INT_FAST32_T_TYPE__   int_fast32_t;
typedef __UINT_FAST32_T_TYPE__ uint_fast32_t;

#ifdef __INT_FAST64_T_TYPE__
  typedef __INT_FAST64_T_TYPE__ int_fast64_t;
#endif /* __INT_FAST64_T_TYPE__ */

#ifdef __UINT_FAST64_T_TYPE__
  typedef __UINT_FAST64_T_TYPE__ uint_fast64_t;
#endif /* __UINT_FAST64_T_TYPE__ */

/* The integer type capable of holding the largest number of bits. */
typedef __INTMAX_T_TYPE__   intmax_t;
typedef __UINTMAX_T_TYPE__ uintmax_t;

/* An integer type large enough to be able to hold a pointer.
   This is optional, but always supported in IAR compilers. */
typedef __INTPTR_T_TYPE__   intptr_t;
typedef __UINTPTR_T_TYPE__ uintptr_t;

/* An integer capable of holding a pointer to a specific memory type. */
#define __DATA_PTR_MEM_HELPER1__(M, I)                     \
typedef __DATA_MEM##I##_INTPTR_TYPE__ M##_intptr_t;        \
typedef __DATA_MEM##I##_UINTPTR_TYPE__ M##_uintptr_t;
__DATA_PTR_MEMORY_LIST1__()
#undef __DATA_PTR_MEM_HELPER1__

/* Minimum and maximum limits. */
#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)

#ifdef __INT8_T_TYPE__
  #define INT8_MAX   __INT8_T_MAX__
  #define INT8_MIN   __INT8_T_MIN__
  #define UINT8_MAX __UINT8_T_MAX__
#endif

#ifdef __INT16_T_TYPE__
  #define INT16_MAX   __INT16_T_MAX__
  #define INT16_MIN   __INT16_T_MIN__
  #define UINT16_MAX __UINT16_T_MAX__
#endif

#ifdef __INT32_T_TYPE__
  #define INT32_MAX   __INT32_T_MAX__
  #define INT32_MIN   __INT32_T_MIN__
  #define UINT32_MAX __UINT32_T_MAX__
#endif

#ifdef __INT64_T_TYPE__
  #define INT64_MAX   __INT64_T_MAX__
  #define INT64_MIN   __INT64_T_MIN__
  #define UINT64_MAX __UINT64_T_MAX__
#endif

#define INT_LEAST8_MAX   __INT_LEAST8_T_MAX__
#define INT_LEAST8_MIN   __INT_LEAST8_T_MIN__
#define UINT_LEAST8_MAX __UINT_LEAST8_T_MAX__

#define INT_LEAST16_MAX   __INT_LEAST16_T_MAX__
#define INT_LEAST16_MIN   __INT_LEAST16_T_MIN__
#define UINT_LEAST16_MAX __UINT_LEAST16_T_MAX__

#define INT_LEAST32_MAX   __INT_LEAST32_T_MAX__
#define INT_LEAST32_MIN   __INT_LEAST32_T_MIN__
#define UINT_LEAST32_MAX __UINT_LEAST32_T_MAX__

#ifdef __INT_LEAST64_T_TYPE__
  #define INT_LEAST64_MAX __INT_LEAST64_T_MAX__
  #define INT_LEAST64_MIN __INT_LEAST64_T_MIN__
#endif

#ifdef __UINT_LEAST64_T_TYPE__
  #define UINT_LEAST64_MAX __UINT_LEAST64_T_MAX__
#endif

#define INT_FAST8_MAX   __INT_FAST8_T_MAX__
#define INT_FAST8_MIN   __INT_FAST8_T_MIN__
#define UINT_FAST8_MAX __UINT_FAST8_T_MAX__

#define INT_FAST16_MAX   __INT_FAST16_T_MAX__
#define INT_FAST16_MIN   __INT_FAST16_T_MIN__
#define UINT_FAST16_MAX __UINT_FAST16_T_MAX__

#define INT_FAST32_MAX   __INT_FAST32_T_MAX__
#define INT_FAST32_MIN   __INT_FAST32_T_MIN__
#define UINT_FAST32_MAX __UINT_FAST32_T_MAX__

#ifdef __INT_FAST64_T_TYPE__
  #define INT_FAST64_MAX __INT_FAST64_T_MAX__
  #define INT_FAST64_MIN __INT_FAST64_T_MIN__
#endif

#ifdef __UINT_FAST64_T_TYPE__
  #define UINT_FAST64_MAX __UINT_FAST64_T_MAX__
#endif

#define INTMAX_MAX   __INTMAX_T_MAX__
#define INTMAX_MIN   __INTMAX_T_MIN__
#define UINTMAX_MAX __UINTMAX_T_MAX__

#define SIZE_MAX __SIZE_T_MAX__

#define PTRDIFF_MAX __PTRDIFF_T_MAX__
#define PTRDIFF_MIN __PTRDIFF_T_MIN__

#define INTPTR_MAX   __INTPTR_T_MAX__
#define INTPTR_MIN   __INTPTR_T_MIN__
#define UINTPTR_MAX __UINTPTR_T_MAX__

#define WCHAR_MIN _WCMIN
#define WCHAR_MAX _WCMAX

#define WINT_MIN _WIMIN
#define WINT_MAX _WIMAX


#endif /* !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) */


/* Macros expanding to integer constants. */
#if !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS)

#ifdef __INT8_T_TYPE__
  #define INT8_C(x)  _GLUE(x,__INT8_C_SUFFIX__)
  #define UINT8_C(x) _GLUE(x,__UINT8_C_SUFFIX__)
#endif

#ifdef __INT16_T_TYPE__
  #define INT16_C(x)  _GLUE(x,__INT16_C_SUFFIX__)
  #define UINT16_C(x) _GLUE(x,__UINT16_C_SUFFIX__)
#endif

#ifdef __INT32_T_TYPE__
  #define INT32_C(x)  _GLUE(x,__INT32_C_SUFFIX__)
  #define UINT32_C(x) _GLUE(x,__UINT32_C_SUFFIX__)
#endif

#ifdef __INT_LEAST64_T_TYPE__
  #define INT64_C(x) _GLUE(x,__INT64_C_SUFFIX__)
#endif

#ifdef __UINT_LEAST64_T_TYPE__
  #define UINT64_C(x) _GLUE(x,__UINT64_C_SUFFIX__)
#endif

#define INTMAX_C(x)  _GLUE(x,__INTMAX_C_SUFFIX__)
#define UINTMAX_C(x) _GLUE(x,__UINTMAX_C_SUFFIX__)

#endif /* !defined(__cplusplus) || defined(__STDC_CONSTANT_MACROS) */

_C_STD_END
#endif /* _STDINT */
