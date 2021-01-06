/* setjmp.h standard header wrapper */
#ifndef _SETJMP
#define _SETJMP

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#ifndef _YVALS
 #include <yvals.h>
#endif

_C_STD_BEGIN

#ifndef __JMP_BUF_ELEMENT_TYPE__
  #ifndef __JMP_BUF_NUM_ELEMENTS__
    #define __JMP_BUF_ELEMENT_TYPE__  char
    #ifndef __JMP_BUF__
      #define __JMP_BUF_NUM_ELEMENTS__  8
    #else
      #define __JMP_BUF_NUM_ELEMENTS__  __JMP_BUF__
    #endif
  #endif
#endif

typedef __JMP_BUF_ELEMENT_TYPE__  jmp_buf[__JMP_BUF_NUM_ELEMENTS__];

_C_LIB_DECL
__INTRINSIC int setjmp (jmp_buf);
__INTRINSIC void longjmp(jmp_buf, int);
_END_C_LIB_DECL
_C_STD_END

#ifdef _STD_USING
  using std::jmp_buf; using std::longjmp;
#endif /* _STD_USING */

#endif /* _SETJMP */

/*
* Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
