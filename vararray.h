#ifndef _VARARRAY_H_
#define _VARARRAY_H_
#include <stdio.h>


typedef struct {
	void* mem; /* pointer to allocated memory */
	size_t elem_size; /* size of elements */
	size_t sz; /* allocated size */
	size_t nmax; /* max index */
} vararray;



/* creates array of initial_size elements of size eleme_size */
vararray* var_alloc(size_t elem_size, size_t initial_size);

/* gets element from array */
void* var_get(vararray* array, off_t idx);

/* puts element into array */
void var_put(vararray* array, off_t idx, void* data);

void var_putn(vararray* array, off_t idx, void* data, size_t elem_size);
void var_push(vararray* array, void* data);
void var_pushn(vararray* array, void* data, size_t elem_size);

size_t var_size(vararray* array);

void var_free(vararray* array);


#endif
