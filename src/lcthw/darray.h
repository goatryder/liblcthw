#ifndef _DArray_h
#define _DArray_h
#include <stdlib.h>
#include <assert.h>
#include <lcthw/dbg.h>

typedef struct DArray {
	int end;
	int max;
	size_t element_size;
	size_t expand_rate;
	void **contents; // pointer to pointer contents which is point to memory
					// with an unspecified type
} DArray;

// contents is a pointer to whole array
// *contents is a pointer to the first element it's equal to
// contents[0]
// contents[index] <=> *(content + index)

// int* p;  variable p is pointer to integer type
// int i;   integer value
// int i2 = *p;  integer i2 is assigned with integer value that pointer p is pointing to
// int* p2 = &i; pointer p2 will point to the address of integer i

// int* p <=> int p*

DArray *DArray_create(size_t element_size, size_t initial_max);

void DArray_destroy(DArray *array);

void DArray_clear(DArray *array);

int DArray_expand(DArray *array);

int DArray_contract(DArray *array);

int DArray_push(DArray *array, void *el);

void *DArray_pop(DArray *array); // WHY POINTER?

void DArray_clear_destroy(DArray *array);

#define DArray_last(A) ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A) ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A) ((A)->max)

#define DEFAULT_EXPAND_RATE 300


static inline void DArray_set(DArray *array, int i, void *el) //Why pointer
{
	check(i < array->max, "darray attempt to set past max");
	array->contents[i] = el;
error:
	return;
}

static inline void *DArray_get(DArray *array, int i) // here is pointer cause we return pointer of value from pointed darray
{
	check(i < array->max, "darray attemt to get past max");
	return array->contents[i];
error:
	return NULL;
}

static inline void *DArray_remove(DArray *array, int i)
{
	void *el = array->contents[i];
	
	array->contents[i] = NULL;
	
	return el;
}

static inline void *DArray_new(DArray *array) //we return pointer to new adress of darray which is size of argument darray
{
	check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.");
	
	return calloc(1, array->element_size);
	
error:
	return NULL;
}

#define DArray_free(E) free((E))

#endif
