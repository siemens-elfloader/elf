/* xalloc.h internal header */
/* Copyright (C) 2003 IAR Systems.  All rights reserved. */
#ifndef _XALLOC
#define _XALLOC

#ifndef _SYSTEM_BUILD
#pragma system_include
#endif

#include <stddef.h>
#include <stdlib.h>
#ifndef _YVALS
  #include <yvals.h>
#endif
#include <yfuns.h>

#ifdef DEBUG
  #include <assert.h>
#endif

_C_STD_BEGIN

#pragma language=save
#pragma language=extended

                /* macros */

typedef union
{ /* To get max alignment */
  char ch;
  short sh;
  int i;
  long l;
  _Longlong lg;
  float f;
  double d;
  long double ld;
  void *p;
  void (*fp)();
} __m_mask_union;
#define MAX_ALIGNMENT (__ALIGNOF__(__m_mask_union))

#define M_MASK     (MAX_ALIGNMENT - 1)        /* rounds all sizes */
#define CELL_OFF(M)   (offsetof(M##_Cell, _Next) + M_MASK & ~M_MASK)
#define SIZE_CELL(M)  (sizeof (M##_Cell) + M_MASK & ~M_MASK)

                /* type definitions */

  /* heap item */

#define __HEAP_MEM_HELPER1__(M, I)                                      \
typedef struct M##_Cell                                                 \
{                                                                       \
  M##_size_t _Size;   /* CELL_OFF <= SIZE_CELL <= _Size */              \
  struct M##_Cell M *_Next;    /* reused if CELL_OFF < SIZE_CELL */     \
} M##_Cell;

__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__

  /* heap control information */

#define __HEAP_MEM_HELPER1__(M, I)                                      \
typedef struct                                                          \
{                                                                       \
  M##_Cell M * M *_Plast;   /* null, or where to resume malloc scan */  \
  M##_Cell M *_Head;   /* null, or lowest addressed free cell */        \
} M##_Altab;

__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__

                /* declarations */
_C_LIB_DECL

#define __HEAP_MEM_HELPER1__(M, I)                              \
__INTRINSIC void M * M##_GetMemChunk(void);                     \
extern M M##_Altab M##_Aldata;  /* free list initially empty */

__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__


_END_C_LIB_DECL

#define _PTR_NORM(p) (p)

#ifdef DEBUG
  #define ASSERT(e) assert(e)
  _C_LIB_DECL

#define __HEAP_MEM_HELPER1__(M, I)                                      \
  __INTRINSIC int M##_OK_Cell(M##_Cell M * p);                          \
  __INTRINSIC int M##_OK_Altab(M##_Altab M * p);                        \
  __INTRINSIC void M##_UPD_Altab(M##_size_t d_heap, M##_size_t d_alloc, \
                                 M##_size_t d_free);
__HEAP_MEMORY_LIST1__()
#undef __HEAP_MEM_HELPER1__

  #define _OK_CELL(M, p) M##_Ok_Cell(p)
  #define _OK_ALTAB(M, p) M##_Ok_Altab(p)
  #define _UPD_ALTAB(M, h, d, f) M##_UPD_Altab(h, d, f)
  #define _WHEN_DEBUG(s) s

  _END_C_LIB_DECL
#else /* is NDEBUG */
  #define ASSERT(e) (void)0
  #define _OK_CELL(M, p) (void)0
  #define _OK_ALTAB(M, p) (void)0
  #define _UPD_ALTAB(M, d_heap, d_alloc, d_free) (void)0
  #define _WHEN_DEBUG(s)
#endif /*DEBUG*/
_C_STD_END

#define _HEAP_REDIRECT_TO_I(I) _GLUE3(__DATA_MEM,I,_HEAP__)
#define _HEAP_REDIRECT(I)      (_HEAP_REDIRECT_TO_I(I) != (I))
#define _HEAP_REDIRECT_TO(I)   _GLUE3(__DATA_MEM,_HEAP_REDIRECT_TO_I(I),__)

#pragma language=restore

#endif /* _XALLOC */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V3.12:0576 */
