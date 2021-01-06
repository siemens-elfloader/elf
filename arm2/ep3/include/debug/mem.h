

#ifndef __DEBUG_MEM_H__
#define __DEBUG_MEM_H__



void *val_malloc(size_t sz, const char *file, int line);
void *val_calloc(size_t sz, size_t cnt, const char *file, int line);
void *val_realloc(void *ptr, size_t sz, const char *file, int line);
void val_free(void *ptr, const char *file, int line);




#endif
