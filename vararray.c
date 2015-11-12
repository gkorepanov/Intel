#include"vararray.h"
#include<stdlib.h>
#include<string.h>


static size_t _get_power_of_two(size_t n) {
	if ( n == 1) {
		return 1;
	} else {
		n--;
		return (n<<1) & ~n;
	}
	/*	return (n == 1)? 1 : --n, (n << 1) & ~n; */
}

/* creates array of initial_size elements of size elem_size */
vararray* var_alloc(size_t elem_size, size_t initial_size) {
	vararray* result = (vararray*)calloc(1, sizeof(vararray));

	result->sz = _get_power_of_two(initial_size);
	result->mem = malloc(elem_size * result->sz);
	result->elem_size = elem_size;
	result->nmax = 0;
	memset(result->mem, 0, result->elem_size * result->sz);
   /* if (!var_ok(result))
        FATALERR("vararray con-tor made bad array");*/

	return result;
}





/* gets element from array */
void* var_get(vararray* array, off_t idx) {
	if (idx < array->nmax) 
		return array->mem + (idx * array->elem_size);

	return NULL;
	
}

void _var_grow(vararray* array) {
	printf("reallocating to %ld\n", array->sz*2);
	array->mem = realloc(array->mem, array->elem_size * array->sz * 2);
	array->sz <<= 1;
}

/* puts element into array */
void var_put(vararray* array, off_t idx, const void* data) {
	if ( idx >= array->nmax) {
		if ( idx*10 > 5*array->sz) {
			/* fill factor exceeded */
			_var_grow(array);
		}
		array->nmax = idx+1;
	}
	memcpy(array->mem + (idx * array->elem_size), data, array->elem_size);
}

void var_push(vararray* array, void* data) {
	if (array->nmax*10 > 5*array->sz) {
		/* fill factor exceeded */
		_var_grow(array);
    }

	memcpy(array->mem + (array->nmax * array->elem_size), data, array->elem_size);
    (array->nmax)++;
}


void var_pushn(vararray* array, void* data, size_t elem_size) {
	if (array->nmax*10 > 5*array->sz) {
		/* fill factor exceeded */
		_var_grow(array);
    }

	memcpy(array->mem + (array->nmax * array->elem_size), data, elem_size);
    (array->nmax) += (elem_size/(array->elem_size));
}



size_t var_size(vararray* array) {
	return array->nmax;

}

void var_free(vararray* array) {
	free(array->mem);
	free(array);
}


