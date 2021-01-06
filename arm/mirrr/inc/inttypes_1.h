/* inttypes.h standard header */
#ifndef _INTTYPES
#define _INTTYPES
#include <stdint.h>

_C_STD_BEGIN

         /* Support symbols for correct prefixes according to size */

#if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS)

                /* PRINT FORMAT MACROS */
#ifdef __INT8_T_TYPE__
  #define PRId8          __INT8_SIZE_PREFIX__ "d"
#endif
#ifdef __INT16_T_TYPE__
  #define PRId16         __INT16_SIZE_PREFIX__ "d"
#endif
#ifdef __INT32_T_TYPE__
  #define PRId32         __INT32_SIZE_PREFIX__ "d"
#endif
#ifdef __INT64_T_TYPE__
  #define PRId64         __INT64_SIZE_PREFIX__ "d"
#endif
#define PRIdLEAST8       __INT_LEAST8_SIZE_PREFIX__ "d"
#define PRIdLEAST16      __INT_LEAST16_SIZE_PREFIX__ "d"
#define PRIdLEAST32      __INT_LEAST32_SIZE_PREFIX__ "d"
#ifdef __INT_LEAST64_T_TYPE__
  #define PRIdLEAST64    __INT_LEAST64_SIZE_PREFIX__  "d"
#endif
#define PRIdFAST8        __INT_FAST8_SIZE_PREFIX__ "d"
#define PRIdFAST16       __INT_FAST16_SIZE_PREFIX__ "d"
#define PRIdFAST32       __INT_FAST32_SIZE_PREFIX__ "d"
#ifdef __INT_FAST64_T_TYPE__
  #define PRIdFAST64     __INT_FAST64_SIZE_PREFIX__ "d"
#endif
#define PRIdMAX          __INTMAX_SIZE_PREFIX__ "d"
#define PRIdPTR          __INTPTR_SIZE_PREFIX__ "d"

#ifdef __INT8_T_TYPE__
  #define PRIi8          __INT8_SIZE_PREFIX__ "i"
#endif
#ifdef __INT16_T_TYPE__
  #define PRIi16         __INT16_SIZE_PREFIX__ "i"
#endif
#ifdef __INT32_T_TYPE__
  #define PRIi32         __INT32_SIZE_PREFIX__ "i"
#endif
#ifdef __INT64_T_TYPE__
  #define PRIi64         __INT64_SIZE_PREFIX__ "i"
#endif
#define PRIiLEAST8       __INT_LEAST8_SIZE_PREFIX__ "i"
#define PRIiLEAST16      __INT_LEAST16_SIZE_PREFIX__ "i"
#define PRIiLEAST32      __INT_LEAST32_SIZE_PREFIX__ "i"
#ifdef __INT_LEAST64_T_TYPE__
  #define PRIiLEAST64    __INT_LEAST64_SIZE_PREFIX__  "i"
#endif
#define PRIiFAST8        __INT_FAST8_SIZE_PREFIX__ "i"
#define PRIiFAST16       __INT_FAST16_SIZE_PREFIX__ "i"
#define PRIiFAST32       __INT_FAST32_SIZE_PREFIX__ "i"
#ifdef __INT_FAST64_T_TYPE__
  #define PRIiFAST64     __INT_FAST64_SIZE_PREFIX__ "i"
#endif
#define PRIiMAX          __INTMAX_SIZE_PREFIX__ "i"
#define PRIiPTR          __INTPTR_SIZE_PREFIX__ "i"

#ifdef __INT8_T_TYPE__
  #define PRIo8          __INT8_SIZE_PREFIX__ "o"
#endif
#ifdef __INT16_T_TYPE__
  #define PRIo16         __INT16_SIZE_PREFIX__ "o"
#endif
#ifdef __INT32_T_TYPE__
  #define PRIo32         __INT32_SIZE_PREFIX__ "o"
#endif
#ifdef __INT64_T_TYPE__
  #define PRIo64         __INT64_SIZE_PREFIX__ "o"
#endif
#define PRIoLEAST8       __INT_LEAST8_SIZE_PREFIX__ "o"
#define PRIoLEAST16      __INT_LEAST16_SIZE_PREFIX__ "o"
#define PRIoLEAST32      __INT_LEAST32_SIZE_PREFIX__ "o"
#ifdef __INT_LEAST64_T_TYPE__
  #define PRIoLEAST64    __INT_LEAST64_SIZE_PREFIX__  "o"
#endif
#define PRIoFAST8        __INT_FAST8_SIZE_PREFIX__ "o"
#define PRIoFAST16       __INT_FAST16_SIZE_PREFIX__ "o"
#define PRIoFAST32       __INT_FAST32_SIZE_PREFIX__ "o"
#ifdef __INT_FAST64_T_TYPE__
  #define PRIoFAST64     __INT_FAST64_SIZE_PREFIX__ "o"
#endif
#define PRIoMAX          __INTMAX_SIZE_PREFIX__ "o"
#define PRIoPTR          __INTPTR_SIZE_PREFIX__ "o"

#ifdef __INT8_T_TYPE__
  #define PRIu8          __INT8_SIZE_PREFIX__ "u"
#endif
#ifdef __INT16_T_TYPE__
  #define PRIu16         __INT16_SIZE_PREFIX__ "u"
#endif
#ifdef __INT32_T_TYPE__
  #define PRIu32         __INT32_SIZE_PREFIX__ "u"
#endif
#ifdef __INT64_T_TYPE__
  #define PRIu64         __INT64_SIZE_PREFIX__ "u"
#endif
#define PRIuLEAST8       __INT_LEAST8_SIZE_PREFIX__ "u"
#define PRIuLEAST16      __INT_LEAST16_SIZE_PREFIX__ "u"
#define PRIuLEAST32      __INT_LEAST32_SIZE_PREFIX__ "u"
#ifdef __INT_LEAST64_T_TYPE__
  #define PRIuLEAST64    __INT_LEAST64_SIZE_PREFIX__  "u"
#endif
#define PRIuFAST8        __INT_FAST8_SIZE_PREFIX__ "u"
#define PRIuFAST16       __INT_FAST16_SIZE_PREFIX__ "u"
#define PRIuFAST32       __INT_FAST32_SIZE_PREFIX__ "u"
#ifdef __INT_FAST64_T_TYPE__
  #define PRIuFAST64     __INT_FAST64_SIZE_PREFIX__ "u"
#endif
#define PRIuMAX          __INTMAX_SIZE_PREFIX__ "u"
#define PRIuPTR          __INTPTR_SIZE_PREFIX__ "u"

#ifdef __INT8_T_TYPE__
  #define PRIx8          __INT8_SIZE_PREFIX__ "x"
#endif
#ifdef __INT16_T_TYPE__
  #define PRIx16         __INT16_SIZE_PREFIX__ "x"
#endif
#ifdef __INT32_T_TYPE__
  #define PRIx32         __INT32_SIZE_PREFIX__ "x"
#endif
#ifdef __INT64_T_TYPE__
  #define PRIx64         __INT64_SIZE_PREFIX__ "x"
#endif
#define PRIxLEAST8       __INT_LEAST8_SIZE_PREFIX__ "x"
#define PRIxLEAST16      __INT_LEAST16_SIZE_PREFIX__ "x"
#define PRIxLEAST32      __INT_LEAST32_SIZE_PREFIX__ "x"
#ifdef __INT_LEAST64_T_TYPE__
  #define PRIxLEAST64    __INT_LEAST64_SIZE_PREFIX__  "x"
#endif
#define PRIxFAST8        __INT_FAST8_SIZE_PREFIX__ "x"
#define PRIxFAST16       __INT_FAST16_SIZE_PREFIX__ "x"
#define PRIxFAST32       __INT_FAST32_SIZE_PREFIX__ "x"
#ifdef __INT_FAST64_T_TYPE__
  #define PRIxFAST64     __INT_FAST64_SIZE_PREFIX__ "x"
#endif
#define PRIxMAX          __INTMAX_SIZE_PREFIX__ "x"
#define PRIxPTR          __INTPTR_SIZE_PREFIX__ "x"

#ifdef __INT8_T_TYPE__
  #define PRIX8          __INT8_SIZE_PREFIX__ "X"
#endif
#ifdef __INT16_T_TYPE__
  #define PRIX16         __INT16_SIZE_PREFIX__ "X"
#endif
#ifdef __INT32_T_TYPE__
  #define PRIX32         __INT32_SIZE_PREFIX__ "X"
#endif
#ifdef __INT64_T_TYPE__
  #define PRIX64         __INT64_SIZE_PREFIX__ "X"
#endif
#define PRIXLEAST8       __INT_LEAST8_SIZE_PREFIX__ "X"
#define PRIXLEAST16      __INT_LEAST16_SIZE_PREFIX__ "X"
#define PRIXLEAST32      __INT_LEAST32_SIZE_PREFIX__ "X"
#ifdef __INT_LEAST64_T_TYPE__
  #define PRIXLEAST64    __INT_LEAST64_SIZE_PREFIX__  "X"
#endif
#define PRIXFAST8        __INT_FAST8_SIZE_PREFIX__ "X"
#define PRIXFAST16       __INT_FAST16_SIZE_PREFIX__ "X"
#define PRIXFAST32       __INT_FAST32_SIZE_PREFIX__ "X"
#ifdef __INT_FAST64_T_TYPE__
  #define PRIXFAST64     __INT_FAST64_SIZE_PREFIX__ "X"
#endif
#define PRIXMAX          __INTMAX_SIZE_PREFIX__ "X"
#define PRIXPTR          __INTPTR_SIZE_PREFIX__ "X"

                /* SCAN FORMAT MACROS */
#ifdef __INT8_T_TYPE__
  #define SCNd8          __INT8_SIZE_PREFIX__ "d"
#endif
#ifdef __INT16_T_TYPE__
  #define SCNd16         __INT16_SIZE_PREFIX__ "d"
#endif
#ifdef __INT32_T_TYPE__
  #define SCNd32         __INT32_SIZE_PREFIX__ "d"
#endif
#ifdef __INT64_T_TYPE__
  #define SCNd64         __INT64_SIZE_PREFIX__ "d"
#endif
#define SCNdLEAST8       __INT_LEAST8_SIZE_PREFIX__ "d"
#define SCNdLEAST16      __INT_LEAST16_SIZE_PREFIX__ "d"
#define SCNdLEAST32      __INT_LEAST32_SIZE_PREFIX__ "d"
#ifdef __INT_LEAST64_T_TYPE__
  #define SCNdLEAST64    __INT_LEAST64_SIZE_PREFIX__  "d"
#endif
#define SCNdFAST8        __INT_FAST8_SIZE_PREFIX__ "d"
#define SCNdFAST16       __INT_FAST16_SIZE_PREFIX__ "d"
#define SCNdFAST32       __INT_FAST32_SIZE_PREFIX__ "d"
#ifdef __INT_FAST64_T_TYPE__
  #define SCNdFAST64     __INT_FAST64_SIZE_PREFIX__ "d"
#endif
#define SCNdMAX          __INTMAX_SIZE_PREFIX__ "d"
#define SCNdPTR          __INTPTR_SIZE_PREFIX__ "d"

#ifdef __INT8_T_TYPE__
  #define SCNi8          __INT8_SIZE_PREFIX__ "i"
#endif
#ifdef __INT16_T_TYPE__
  #define SCNi16         __INT16_SIZE_PREFIX__ "i"
#endif
#ifdef __INT32_T_TYPE__
  #define SCNi32         __INT32_SIZE_PREFIX__ "i"
#endif
#ifdef __INT64_T_TYPE__
  #define SCNi64         __INT64_SIZE_PREFIX__ "i"
#endif
#define SCNiLEAST8       __INT_LEAST8_SIZE_PREFIX__ "i"
#define SCNiLEAST16      __INT_LEAST16_SIZE_PREFIX__ "i"
#define SCNiLEAST32      __INT_LEAST32_SIZE_PREFIX__ "i"
#ifdef __INT_LEAST64_T_TYPE__
  #define SCNiLEAST64    __INT_LEAST64_SIZE_PREFIX__  "i"
#endif
#define SCNiFAST8        __INT_FAST8_SIZE_PREFIX__ "i"
#define SCNiFAST16       __INT_FAST16_SIZE_PREFIX__ "i"
#define SCNiFAST32       __INT_FAST32_SIZE_PREFIX__ "i"
#ifdef __INT_FAST64_T_TYPE__
  #define SCNiFAST64     __INT_FAST64_SIZE_PREFIX__ "i"
#endif
#define SCNiMAX          __INTMAX_SIZE_PREFIX__ "i"
#define SCNiPTR          __INTPTR_SIZE_PREFIX__ "i"

#ifdef __INT8_T_TYPE__
  #define SCNo8          __INT8_SIZE_PREFIX__ "o"
#endif
#ifdef __INT16_T_TYPE__
  #define SCNo16         __INT16_SIZE_PREFIX__ "o"
#endif
#ifdef __INT32_T_TYPE__
  #define SCNo32         __INT32_SIZE_PREFIX__ "o"
#endif
#ifdef __INT64_T_TYPE__
  #define SCNo64         __INT64_SIZE_PREFIX__ "o"
#endif
#define SCNoLEAST8       __INT_LEAST8_SIZE_PREFIX__ "o"
#define SCNoLEAST16      __INT_LEAST16_SIZE_PREFIX__ "o"
#define SCNoLEAST32      __INT_LEAST32_SIZE_PREFIX__ "o"
#ifdef __INT_LEAST64_T_TYPE__
  #define SCNoLEAST64    __INT_LEAST64_SIZE_PREFIX__  "o"
#endif
#define SCNoFAST8        __INT_FAST8_SIZE_PREFIX__ "o"
#define SCNoFAST16       __INT_FAST16_SIZE_PREFIX__ "o"
#define SCNoFAST32       __INT_FAST32_SIZE_PREFIX__ "o"
#ifdef __INT_FAST64_T_TYPE__
  #define SCNoFAST64     __INT_FAST64_SIZE_PREFIX__ "o"
#endif
#define SCNoMAX          __INTMAX_SIZE_PREFIX__ "o"
#define SCNoPTR          __INTPTR_SIZE_PREFIX__ "o"

#ifdef __INT8_T_TYPE__
  #define SCNu8          __INT8_SIZE_PREFIX__ "u"
#endif
#ifdef __INT16_T_TYPE__
  #define SCNu16         __INT16_SIZE_PREFIX__ "u"
#endif
#ifdef __INT32_T_TYPE__
  #define SCNu32         __INT32_SIZE_PREFIX__ "u"
#endif
#ifdef __INT64_T_TYPE__
  #define SCNu64         __INT64_SIZE_PREFIX__ "u"
#endif
#define SCNuLEAST8       __INT_LEAST8_SIZE_PREFIX__ "u"
#define SCNuLEAST16      __INT_LEAST16_SIZE_PREFIX__ "u"
#define SCNuLEAST32      __INT_LEAST32_SIZE_PREFIX__ "u"
#ifdef __INT_LEAST64_T_TYPE__
  #define SCNuLEAST64    __INT_LEAST64_SIZE_PREFIX__  "u"
#endif
#define SCNuFAST8        __INT_FAST8_SIZE_PREFIX__ "u"
#define SCNuFAST16       __INT_FAST16_SIZE_PREFIX__ "u"
#define SCNuFAST32       __INT_FAST32_SIZE_PREFIX__ "u"
#ifdef __INT_FAST64_T_TYPE__
  #define SCNuFAST64     __INT_FAST64_SIZE_PREFIX__ "u"
#endif
#define SCNuMAX          __INTMAX_SIZE_PREFIX__ "u"
#define SCNuPTR          __INTPTR_SIZE_PREFIX__ "u"

#ifdef __INT8_T_TYPE__
  #define SCNx8          __INT8_SIZE_PREFIX__ "x"
#endif
#ifdef __INT16_T_TYPE__
  #define SCNx16         __INT16_SIZE_PREFIX__ "x"
#endif
#ifdef __INT32_T_TYPE__
  #define SCNx32         __INT32_SIZE_PREFIX__ "x"
#endif
#ifdef __INT64_T_TYPE__
  #define SCNx64         __INT64_SIZE_PREFIX__ "x"
#endif
#define SCNxLEAST8       __INT_LEAST8_SIZE_PREFIX__ "x"
#define SCNxLEAST16      __INT_LEAST16_SIZE_PREFIX__ "x"
#define SCNxLEAST32      __INT_LEAST32_SIZE_PREFIX__ "x"
#ifdef __INT_LEAST64_T_TYPE__
  #define SCNxLEAST64    __INT_LEAST64_SIZE_PREFIX__  "x"
#endif
#define SCNxFAST8        __INT_FAST8_SIZE_PREFIX__ "x"
#define SCNxFAST16       __INT_FAST16_SIZE_PREFIX__ "x"
#define SCNxFAST32       __INT_FAST32_SIZE_PREFIX__ "x"
#ifdef __INT_FAST64_T_TYPE__
  #define SCNxFAST64     __INT_FAST64_SIZE_PREFIX__ "x"
#endif
#define SCNxMAX          __INTMAX_SIZE_PREFIX__ "x"
#define SCNxPTR          __INTPTR_SIZE_PREFIX__ "x"

#ifdef __INT8_T_TYPE__
  #define SCNX8          __INT8_SIZE_PREFIX__ "X"
#endif
#ifdef __INT16_T_TYPE__
  #define SCNX16         __INT16_SIZE_PREFIX__ "X"
#endif
#ifdef __INT32_T_TYPE__
  #define SCNX32         __INT32_SIZE_PREFIX__ "X"
#endif
#ifdef __INT64_T_TYPE__
  #define SCNX64         __INT64_SIZE_PREFIX__ "X"
#endif
#define SCNXLEAST8       __INT_LEAST8_SIZE_PREFIX__ "X"
#define SCNXLEAST16      __INT_LEAST16_SIZE_PREFIX__ "X"
#define SCNXLEAST32      __INT_LEAST32_SIZE_PREFIX__ "X"
#ifdef __INT_LEAST64_T_TYPE__
  #define SCNXLEAST64    __INT_LEAST64_SIZE_PREFIX__  "X"
#endif
#define SCNXFAST8        __INT_FAST8_SIZE_PREFIX__ "X"
#define SCNXFAST16       __INT_FAST16_SIZE_PREFIX__ "X"
#define SCNXFAST32       __INT_FAST32_SIZE_PREFIX__ "X"
#ifdef __INT_FAST64_T_TYPE__
  #define SCNXFAST64     __INT_FAST64_SIZE_PREFIX__ "X"
#endif
#define SCNXMAX          __INTMAX_SIZE_PREFIX__ "X"
#define SCNXPTR          __INTPTR_SIZE_PREFIX__ "X"

#endif /* !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS) */

_C_STD_END
#endif /* _INTTYPES */

/*
 * Copyright (c) 1992-2003 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:0576 */
