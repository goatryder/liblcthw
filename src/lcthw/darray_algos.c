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
/*
void *merge(void *left, size_t nmemb_left, void *right, size_t nmemb_right,
		size_t size, int (*compar)(const void *, const void *))
{
    DArray *result = malloc(size * (nmemb_left + nmemb_right));
    void *val = NULL;

    while (nmemb_left > 0 || nmemb_right > 0) {
        if (nmemb_left > 0 && nmemb_right > 0) {
            if (compar(left[0], right[0]) <= 0) {
            	val = left[0]
            	free(left[0])
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

void *merge_sort(void *base, size_t nmemb, size_t size,
		int (*compar)(const void *, const void *))
{
    void *result = NULL;

    if (nmemb <= 1) {
        return NULL;
    }
	
	size_t left_nmemb = nmemb >> 1;
	size_t right_nmemb = (nmemb + 1) >> 1;
	void *left = malloc(size * left_nmemb);
	void *right = malloc(size * right_nmemb);

    int middle = (int)nmemb >> 1;
    
    int i = 0;
    for(i = 0; i < nmemb; i++) {
    	if (middle > 0) {
    		left[i] = base[i];
    	} else {
    		right[i-middle] = base[i];
    	}
    	
    	middle--;
    }

    void *sort_left = merge_sort(left, left_nmemb, size, compar);
    void *sort_right = merge_sort(right, right_nmemb, size, compar);

    if (sort_left != left) free(left);
    if (sort_right != right) free(right);

    result = merge(sort_left, sort_right, cmp);

    free(sort_left);
    free(sort_right);

    return result;
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
    merge_sort(array->contents, DArray_count(array), sizeof(void *), cmp)
    return 0;
}
*/
