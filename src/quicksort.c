#include <stdio.h>
#include <string.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*));

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to type (char *) and works with them as char pointers
 * for the remainder of the function. Swaps one byte at a time, until all 'size'
 * bytes have been swapped. For example, if ints are passed in, size will be 4
 * and this function will swap 4 bytes starting at a and b pointers.
 */
static void swap(void *a, void *b, size_t size) {
    // TODO
    char temp;
    unsigned char *p_a = a;
    unsigned char *p_b = b;

    for (size_t i = 0; i < size; i++) {
        temp = p_a[i];
        p_a[i] = p_b[i];
        p_b[i] = temp;
    }
}

/**
 * Partitions array around a pivot, utilizing the swap function. Each time the
 * function runs, the pivot is placed into the correct index of the array in
 * sorted order. All elements less than the pivot should be to its left, and all
 * elements greater than or equal to the pivot should be to its right.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
                  int (*cmp) (const void*, const void*)) {
    // TODO
    unsigned char *arr = array;
    unsigned char *pivot = arr + left * elem_sz;  // pivot at leftmost position
    int s = left;

    for (int i = left + 1; i <= right; i++) {
        if (cmp(arr + i * elem_sz, pivot) < 0) {
            s++;
            swap(arr + s * elem_sz, arr + i * elem_sz, elem_sz);
        }
    }

    swap(arr + left * elem_sz, arr + s * elem_sz, elem_sz); // put pivot in correct position
    return s;
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
                             int (*cmp) (const void*, const void*)) {
    // TODO
    if (left < right) {
        int s = lomuto(array, left, right, elem_sz, cmp);  // Partition array
        quicksort_helper(array, left, s - 1, elem_sz, cmp); // Sort left side
        quicksort_helper(array, s + 1, right, elem_sz, cmp); // Sort right side
    }
}

// PART B //

void quicksort(void *array, size_t len, size_t elem_sz,
    int (*cmp) (const void*, const void*)) {
    if (array != NULL && len > 1) {
        quicksort_helper(array, 0, len - 1, elem_sz, cmp);
    }
}

int int_cmp(const void *a, const void *b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_a > int_b) - (int_a < int_b);  // Returns -1, 0, or 1
}

int dbl_cmp(const void *a, const void *b) {
    double dbl_a = *((double*)a);
    double dbl_b = *((double*)b);
    return (dbl_a > dbl_b) - (dbl_a < dbl_b);  // Returns -1, 0, or 1
}

int str_cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);  // Compare strings
}
