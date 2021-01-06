#ifndef ALL_H
#define ALL_H

#ifdef __WIN32__
#include <wtypes.h>
#endif

// real number
typedef float real;		// float should be enough

// Signed & unsigned integers, define SIXTEEN_BIT_COMPILER if the
// default integer size is 16 bits

#ifdef SIXTEEN_BIT_COMPILER
typedef long int32;							// 32 Bit signed integer
typedef unsigned long  uint32;         // 32 Bit unsigned integer
typedef int int16;		               // 16 Bit signed integer
typedef unsigned int	uint16;		      // 16 Bit unsigned integer
#else
typedef int int32;							// 32 Bit signed integer
typedef unsigned uint32;               // 32 Bit unsigned integer
typedef   signed short  int16;	      // 16 Bit signed integer
typedef unsigned short uint16;	      // 16 Bit unsigned integer
#endif // SIXTEEN_BIT_COMPILER

#ifdef ULAW
typedef unsigned char	ulawsample;	// u-law byte
#endif // ULAW

// mutex type (only for user seekable or stoppable streams)
#ifdef SEEK_STOP

#ifdef __WIN32__
typedef HANDLE _Mutex;
#else
#ifdef BEOS
typedef BLocker * _Mutex;
#endif // BEOS
#endif // __WIN32__

#endif // SEEK_STOP

#ifdef NObool
typedef int32 bool;
#define TRUE  1
#define FALSE 0
#endif // NObool

enum e_channels { both, left, right, downmix };

// What character marks the end of a directory entry? For DOS and
// Windows, it is "\"; in UNIX it is "/".
#if defined(__WIN32__) || defined(OS2) || defined(__DOS__)
#define DIR_MARKER '\\'
#define DIR_MARKER_STR "\\"
#else
#define DIR_MARKER '/'
#define DIR_MARKER_STR "/"
#endif // __WIN32__

#endif // ALL_H
