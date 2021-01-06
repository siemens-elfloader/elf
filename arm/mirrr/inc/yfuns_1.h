/* yfuns.h - Declaration of overridable low-level functions. */
/* Copyright (C) 2003 IAR Systems.  All rights reserved. */
#ifndef _YFUNS
#define _YFUNS

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#include <ysizet.h>

_C_STD_BEGIN

/* Constants used by the low-level I/O system. */

                /* Return values */
#define _LLIO_ERROR ((size_t)-1) /* For __read and __write. */

                /* Standard file handles */
#define _LLIO_STDIN  0
#define _LLIO_STDOUT 1
#define _LLIO_STDERR 2

                /* Open modes */
#define _LLIO_RDONLY       0x0000
#define _LLIO_WRONLY       0x0001
#define _LLIO_RDWR         0x0002

#define _LLIO_RDWRMASK     0x0003 /* Mask used to get _LLIO_RDONLY etc. */

#define _LLIO_APPEND       0x0008
#define _LLIO_TRUNC        0x0200
#define _LLIO_CREAT        0x0100

#define _LLIO_BINARY       0x8000
#define _LLIO_TEXT         0x4000


                /* interface declarations */
_EXTERN_C
extern const char *__environ;
__INTRINSIC int    __close(int);
__INTRINSIC int    __open(const char *, int /* mode */);
#pragma object_attribute = __noreturn
__INTRINSIC void   _exit(int) _NO_RETURN;
#pragma object_attribute = __noreturn
__INTRINSIC void   __exit(int) _NO_RETURN;
__INTRINSIC size_t __read(int, unsigned char *, size_t);
__INTRINSIC size_t __write(int, const unsigned char *, size_t);
__INTRINSIC size_t __dwrite(int, const unsigned char *, size_t);
__INTRINSIC long   __lseek(int, long, int);
__INTRINSIC int    __putchar(int);
__INTRINSIC int    __getchar(void);
__INTRINSIC const char * __getzone(void);
__INTRINSIC size_t __write_buffered(int, const unsigned char *, size_t);

                /* Label in cstartup */
/* If this is required then _Close_all is called.*/
extern void * __cstart_closeall;
void _Close_all(void);


_END_EXTERN_C
_C_STD_END

#endif /* _YFUNS */
