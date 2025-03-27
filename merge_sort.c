#include <stdio.h>
#include <stdlib.h>

// A function that merges two sorted arrays
void merge_two_arrays(int n1, int n2, int *arr1, int *arr2, int *merged) {
    int i = 0, j = 0, k = 0; // Pointers to the first element of arr1, arr2 and merged

    // Both pointers are not out-of-bounds
    while (i < n1 && j < n2) {
        if (arr1[i] <= arr2[j]) { // Put smaller element into output and update pointers
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }

    // Remaining elements
    while (i < n1) {
        merged[k++] = arr1[i++];
    }

    while (j < n2) {
        merged[k++] = arr2[j++];
    }
}

// A function that splits an array into two sub-arrays
void divide_step(int n1, int n2, int *arr, int *arr1, int *arr2) {
    int i; // Loop variable
    for (i = 0; i < n1; i++) {
        arr1[i] = arr[i];
    }
    for (i = 0; i < n2; i++) {
        arr2[i] = arr[n1+i];
    }
}

// A function that performs merge sort on an array
void merge_sort(int n, int *arr) {
    int n1, n2; // Number of elements in the sub-arrays
    int *arr1, *arr2; // Sub-arrays

    if (n > 1) {
        // Divide: Divide the array into two sub-arrays of smaller size
        n1 = n / 2;
        n2 = n - n1;
        arr1 = (int *)malloc(n1 * sizeof(int));
        arr2 = (int *)malloc(n2 * sizeof(int));
        divide_step(n1, n2, arr, arr1, arr2);

        // Conquer: Solve the sub-problem for each sub-array
        merge_sort(n1, arr1);
        merge_sort(n2, arr2);

        // Merge: Merge the sorted sub-arrays to form the required sorted array
        merge_two_arrays(n1, n2, arr1, arr2, arr);
        free(arr1);
        free(arr2);
    }
}

int main() {
    int i; // Loop variable
    int arr[] = {19, 25, 14, 1, 26, 22, 5, 27, 3};
    merge_sort(9, arr);
    for (i = 0; i < 9; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    return 0;
}