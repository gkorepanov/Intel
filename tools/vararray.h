#ifndef _VARARRAY_H_
#define _VARARRAY_H_
#include <stdio.h>


typedef struct {
	void* mem; /* pointer to allocated memory */
	size_t elem_size; /* size of elements */
	size_t sz; /* allocated size */
	size_t nmax; /* max index */
} vararray;



vararray* var_ctor(size_t elem_size, size_t initial_size);
void var_dtor(vararray* array);

void* var_get(vararray* array, off_t idx);

//put simple element
void var_put(vararray* array, off_t idx, void* data);


//push new element to the top
void var_push(vararray* array, void* data);

//push new element of size elem_size
void var_pushn(vararray* array, void* data, size_t elem_size);




#endif
