#include <stdio.h>

// A helper function that swaps two elements in an array
void swap(int *arr, int a, int b) {
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

// A function that performs partition on an array
int partition(int *arr, int left, int right) {
    int pivot = arr[left]; // Key value of pivot (First element as pivot)
    int l = left; // Left pointer
    int r = right; // Right pointer

    while (l < r) {
        while (arr[l] <= pivot && l < r) {
            l++; // Move to the right
        }
        while (arr[r] > pivot) {
            r--; // Move to the left
        }
        if (l < r) {
            swap(arr, l, r); // Swap
        }
    }

    arr[left] = arr[r];
    arr[r] = pivot;
    return r; // New position of pivot
}

// A function that performs quicksort on an array
void q_sort(int *arr, int left, int right) {
    int pivot; // Position of the pivot after partition

    if (left < right) { // Not the base case
        // Divide: Partition
        pivot = partition(arr, left, right);

        // Conquer: Solve sub-problems
        q_sort(arr, left, pivot-1);
        q_sort(arr, pivot+1, right);
    }
}

// A wrapper function that performs quicksort on an array
void quicksort(int n, int *arr) {
    q_sort(arr, 0, n-1);
}

int main() {
    int i; // Loop variable

    int arr[] = {19, 25, 14, 1, 26, 22, 5, 27, 3};    
    quicksort(9, arr);
    for (i = 0; i < 9; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
    return 0;
}