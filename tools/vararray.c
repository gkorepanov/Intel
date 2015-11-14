#include "s_alerts.h"
#include "vararray.h"
#include <stdlib.h>
#include <string.h>

//find the closest power of two (to provide speed)
static size_t _get_power_of_two(size_t n) {
	return (n == 1)? 1 : --n, (n << 1) & ~n;
}


vararray* var_ctor(size_t elem_size, size_t initial_size) {

	vararray* result = (vararray*)calloc(1, sizeof(vararray));
	result->sz = _get_power_of_two(initial_size);
	result->mem = calloc(result->sz, elem_size);
	result->elem_size = elem_size;
	result->nmax = 0;

	return result;
}

void* var_get(vararray* array, off_t idx) {
	if (idx < array->nmax) 
		return (void*)((char*)array->mem + (idx * array->elem_size));

	FATALERR("Gone out of the array.");
	
}

void _var_grow(vararray* array) {
	array->mem = realloc(array->mem, array->elem_size * array->sz * 2);
	array->sz <<= 1;
}

void var_put(vararray* array, off_t idx, const void* data) {
	if (idx >= array->nmax) {
		if (idx*10 > 7*array->sz) {
			// fill factor exceeded
			_var_grow(array);
		}
		array->nmax = idx+1;
	}
	memcpy((char*)array->mem + (idx * array->elem_size), data, array->elem_size);
}

void var_push(vararray* array, void* data) {
	if (array->nmax*10 > 5*array->sz) {
		/* fill factor exceeded */
		_var_grow(array);
    }

	memcpy((char*)array->mem + (array->nmax * array->elem_size), data, array->elem_size);
    (array->nmax)++;
}

void var_pushn(vararray* array, void* data, size_t elem_size) {
	if (array->nmax*10 > 5*array->sz) {
		/* fill factor exceeded */
		_var_grow(array);
    }

	memcpy((char*)array->mem + (array->nmax * array->elem_size), data, elem_size);
    (array->nmax) += (elem_size/(array->elem_size));
}

void var_dtor(vararray* array) {
	free(array->mem);
	free(array);
}
