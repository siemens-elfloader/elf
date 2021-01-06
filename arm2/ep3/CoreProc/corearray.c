
#include <swilib.h>
#include <spl/corearray.h>


void corearray_fill_cached(CoreArray *array, void *fill)
{
    for(unsigned int i = array->size; i<array->cached; ++i)
    {
        array->array[i] = fill;
    }
}


void corearray_init(CoreArray *array, void *empty_cell_fill)
{
    void *__malloc(size_t size) {
        return malloc(size);
    }

    void __free(void *ptr) {
        free(ptr);
    }

    void *__realloc(void *ptr, size_t size) {
        return realloc(ptr, size);
    }

    array->array = (void **)malloc( 4 * sizeof(void*) );
    array->cached = 4;
    array->size = 0;
    array->empty_fill = empty_cell_fill;
    array->malloc = __malloc;
    array->free = __free;
    array->realloc = __realloc;

    corearray_fill_cached(array, array->empty_fill);
}


void corearray_release(CoreArray *array)
{
    if(!array->array)
        return;
    array->free(array->array);
    array->array   = 0;
    array->cached = 0;
    array->size   = 0;
}


int corearray_reserve(CoreArray *array, size_t reserve)
{
    if(!array->array)
        return -1;

    if(array->cached >= reserve) return 0;

    if(array->array)
        array->array = array->realloc(array->array, reserve * sizeof(void*));
    else
        array->array = array->malloc(reserve);


    if(!array->array) {
        return -2;
    }

    array->cached = reserve;

    corearray_fill_cached(array, array->empty_fill);
    return 0;
}


int corearray_push_back(CoreArray *array, void *val)
{
    if(!array->array)
        return -1;

    if(array->cached <= array->size)
        if(corearray_reserve(array, array->size+4))
            return -1;

    array->array[array->size] = val;
    return array->size++;
}


int corearray_pop_back(CoreArray *array)
{
    if(!array->array)
        return -1;

    return --array->size;
}


int corearray_store_cell(CoreArray *array, size_t cell, void *val)
{
    if(!array->array)
        return -1;

    if(cell >= array->size)
        return -1;
        //if(corearray_reserve(array, cell+4))
            //return -1;

    array->array[cell] = val;
    return 0;
}


int corearray_adjust_by_size(CoreArray *array)
{
    if(!array->array)
        return -1;

    if(array->size == array->cached)
        return 0;

    array->array = array->realloc(array->array, array->size);

    if(!array->array) {
        return -1;
    }

    array->cached = array->size;
    return 0;
}


int corearray_set_size(CoreArray *array, size_t size)
{
    if(!array->array)
        return -1;

    array->array = array->realloc(array->array, array->size);

    if(!array->array) {
        return -1;
    }

    array->cached = size;

    if(array->cached <= array->size)
        array->size = size;

    return 0;
}


int corearray_clear(CoreArray *array, void *clear)
{
    if(!array->array)
        return -1;

    int val __attribute__((unused));
    int it = 0;
    corearray_foreach(int, val, array, it) {
        corearray_store_cell(array, it, clear);
    }

    array->size = 0;
    return 0;
}


int corearray_lock(CoreArray *array)
{
    UNUSED(array);
    return 0;
}


int corearray_unlock(CoreArray *array)
{
    UNUSED(array);
    return 0;
}

