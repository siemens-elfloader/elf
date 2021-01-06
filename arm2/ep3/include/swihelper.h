
#ifndef __SWI_HELPER_H__
#define __SWI_HELPER_H__

#ifdef __cplusplus
extern "C" const int __sys_switab_addres[];
#else
extern const int __sys_switab_addres[];
#endif



#ifdef __cplusplus

#define __pdef(point, ret, ...)  { \
    ((ret (*)(...))point)(__VA_ARGS__); }
#else

#define __pdef(point, ret, ...)  { \
    ((ret (*)())point)(__VA_ARGS__); }

#endif


#ifndef __NO_DIRECT_SWI
#define __inl static inline

#ifdef __cplusplus

//#define __def(id, ret, ...) { return ((ret (*)(...))((__sys_switab_addres[id])))(__VA_ARGS__); }
#define __def(id, ret, ...) \
  {\
      if(id >= 0x8000)\
        return (ret)(__sys_switab_addres[id-0x8000]); \
      else\
        return ((ret (*)(...))((__sys_switab_addres[id])))(__VA_ARGS__); \
  }\

#define __defn(id, ...) { ((void (*)(...))((__sys_switab_addres[id])))(__VA_ARGS__); }

#define __cdef(id, ret, ...) (ret)((ret (*)(...))((__sys_switab_addres[id])))(__VA_ARGS__)
#define __cdefn(id, ...) ((void (*)(...))((__sys_switab_addres[id])))(__VA_ARGS__)

#define __nul_def(id, ret) { return ((ret (*)())((__sys_switab_addres[id])))(); }
#define __nul_defn(id) { ((void (*)())((__sys_switab_addres[id])))(); }

#define __def_noinline(id, ret, ...) \
      if(id >= 0x8000)\
        return (ret)(__sys_switab_addres[id-0x8000]); \
      else\
        return ((ret (*)(...))((__sys_switab_addres[id])))(__VA_ARGS__); \

//#define __ldr(id, ret) { return (ret)(__sys_switab_addres[id-0x8000]); }

#else

//#define __def(id, ret, ...) { return ((ret (*)())((__sys_switab_addres[id])))(__VA_ARGS__); }
#define __def(id, ret, ...) \
  {\
      if(id >= 0x8000)\
        return (ret)(__sys_switab_addres[id-0x8000]); \
      else\
        return ((ret (*)())((__sys_switab_addres[id])))(__VA_ARGS__); \
  }\

#define __defn(id, ...) { ((void (*)())((__sys_switab_addres[id])))(__VA_ARGS__); }

/* использовать для функций типа sprintf, но не юзать для рамных функций! */
#define __cdef(id, ret, ...) (ret)((ret (*)())((__sys_switab_addres[id])))(__VA_ARGS__)
#define __cdefn(id, ...) ((void (*)())((__sys_switab_addres[id])))(__VA_ARGS__)


#define __nul_def(id, ret) { return ((ret (*)())((__sys_switab_addres[id])))(); }

#define __def_noinline(id, ret, ...) \
      if(id >= 0x8000)\
        return (ret)(__sys_switab_addres[id-0x8000]); \
      else\
        return ((ret (*)())((__sys_switab_addres[id])))(__VA_ARGS__); \

#define __nul_defn(id) { ((void (*)())((__sys_switab_addres[id])))(); }

//#define __ldr(id, ret) { return (ret)(__sys_switab_addres[id-0x8000]); }

#endif

#else /*__USE_SWI */
#define __inl

#define __def(id, ret, ...) \
        __attribute__((swi(id)));

#define __defn(id, ...) \
        __attribute__((swi(id)));

#define __nul_def(id, ret) \
        __attribute__((swi(id)));

#define __nul_defn(id) \
        __attribute__((swi(id)));

#endif /*__USE_SWI */


#endif
