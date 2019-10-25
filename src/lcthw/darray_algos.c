#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}
/*
int DArray_heapsort(DArray *array, DArray_compare cmp)
{
    heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}
*/

DArray *DArray_merge(DArray *left, DArray *right, DArray_compare cmp)
{
    DArray *result = DArray_create(right->element_size, right->max << 1);
    void *val = NULL;

    while (DArray_count(left) > 0 || DArray_count(right) > 0) {
        if (DArray_count(left) > 0 && DArray_count(right) > 0) {
            if (cmp(DArray_first(left), DArray_first(right)) <= 0) {
                val = DArray_remove(left, 0);
            } else {
                val = DArray_remove(right, 0);
            }

            DArray_push(result, val);
        } else if (DArray_count(left) > 0) {
            val = DArray_remove(left, 0);
            DArray_push(result, val);
        } else if (DArray_count(right) > 0) {
            val = DArray_remove(right, 0);
            DArray_push(result, val);
        }
    }

    return result;
}

DArray *DArray_msort(DArray *array, DArray_compare cmp)
{
    DArray *result = NULL;

    if (DArray_count(array) <= 1) {
        return array;
    }

    DArray *left = DArray_create(array->element_size, array->max >> 1);
    DArray *right = DArray_create(array->element_size, (array->max + 1) >> 1);
    int middle = DArray_count(array) >> 1;
    
    int i = 0;
    
    for(i = 0; i < DArray_count(array); i++) {
    	if (middle > 0) {
    		DArray_push(left, DArray_get(array, i));
    	} else {
    		DArray_push(right, DArray_get(array, i));
    	}
    	
    	middle--;
    }

    DArray *sort_left = DArray_msort(left, cmp);
    DArray *sort_right = DArray_msort(right, cmp);

    if (sort_left != left)
        DArray_destroy(left);
    if (sort_right != right)
        DArray_destroy(right);

    result = DArray_merge(sort_left, sort_right, cmp);

    DArray_destroy(sort_left);
    DArray_destroy(sort_right);

    return result;
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
    DArray_msort(array, cmp);
    return 0;
}
