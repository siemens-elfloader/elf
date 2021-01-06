
#ifndef __EXT_ARRAY_H__
#define __EXT_ARRAY_H__

#include <swilib.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    void **array;
    size_t size,
           cached;

    void *empty_fill;

    void *(*malloc)(size_t);
    void (*free)(void *);
    void *(*realloc)(void *, size_t);
}CoreArray;

#define corearray_foreach(type, value, _array, iterator)           \
    if((size_t)iterator < (_array)->size)                           \
        for( value = (type)((_array)->array[iterator]);               \
             (size_t)iterator < (_array)->size;                     \
             ++iterator, value = (type)((_array)->array[iterator]))

void corearray_init(CoreArray *array, void *empty_cell_fill);
void corearray_release(CoreArray *array);
int corearray_reserve(CoreArray *array, size_t reserve);
int corearray_push_back(CoreArray *array, void *val);
int corearray_pop_back(CoreArray *array);
int corearray_store_cell(CoreArray *array, size_t cell, void *val);
int corearray_adjust_by_size(CoreArray *array);
int corearray_clear(CoreArray *array, void *clear);

int corearray_lock(CoreArray *array);
int corearray_unlock(CoreArray *array);


static inline void *
corearray_cell(CoreArray *array, unsigned int cell)
{
    if(cell >= array->size) return 0;

    return array->array[cell];
}


#endif /* __EXT_ARRAY_H__ */
