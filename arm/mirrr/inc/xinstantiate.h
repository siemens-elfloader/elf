/* _INSTANTIATE macro */
/* Copyright (C) 2003 IAR Systems.  All rights reserved. */

#ifndef _INSTANTIATE_H
#define _INSTANTIATE_H

typedef void __instantiate_t(void);

#define _INSTANTIATE0(f) \
  __instantiate_t * const _Instansiator_##f = (__instantiate_t *)&f
#define _INSTANTIATE(f) _INSTANTIATE0(f)

#endif /* _INSTANTIATE_H */
