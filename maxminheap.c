#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

// Define the element type here - can be changed to float, double, etc.
typedef int ElementType;

typedef struct {
    ElementType* array;
    int size;
    int capacity;
} Heap;

// Max Heap Implementation
Heap* create_max_heap() {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->array = (ElementType*)malloc(sizeof(ElementType) * MAX_SIZE);
    heap->size = 0;
    heap->capacity = MAX_SIZE;
    return heap;
}

void max_heapify_up(Heap* heap, int index) {
    int parent = (index - 1) / 2;
    
    while (index > 0 && heap->array[parent] < heap->array[index]) {
        ElementType temp = heap->array[parent];
        heap->array[parent] = heap->array[index];
        heap->array[index] = temp;
        
        index = parent;
        parent = (index - 1) / 2;
    }
}

void max_insert(Heap* heap, ElementType value) {
    if (heap->size >= heap->capacity) {
        printf("Heap is full!\n");
        return;
    }
    
    heap->array[heap->size] = value;
    heap->size++;
    max_heapify_up(heap, heap->size - 1);
}

void max_heapify_down(Heap* heap, int index) {
    int max_index = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->array[left] > heap->array[max_index]) {
        max_index = left;
    }
    
    if (right < heap->size && heap->array[right] > heap->array[max_index]) {
        max_index = right;
    }
    
    if (max_index != index) {
        ElementType temp = heap->array[index];
        heap->array[index] = heap->array[max_index];
        heap->array[max_index] = temp;
        max_heapify_down(heap, max_index);
    }
}

ElementType max_delete(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty!\n");
        return (ElementType)-1; // Assuming -1 is not a valid value
    }
    
    ElementType max = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    
    if (heap->size > 0) {
        max_heapify_down(heap, 0);
    }
    
    return max;
}

// Min Heap Implementation
Heap* create_min_heap() {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->array = (ElementType*)malloc(sizeof(ElementType) * MAX_SIZE);
    heap->size = 0;
    heap->capacity = MAX_SIZE;
    return heap;
}

void min_heapify_up(Heap* heap, int index) {
    int parent = (index - 1) / 2;
    
    while (index > 0 && heap->array[parent] > heap->array[index]) {
        ElementType temp = heap->array[parent];
        heap->array[parent] = heap->array[index];
        heap->array[index] = temp;
        
        index = parent;
        parent = (index - 1) / 2;
    }
}

void min_insert(Heap* heap, ElementType value) {
    if (heap->size >= heap->capacity) {
        printf("Heap is full!\n");
        return;
    }
    
    heap->array[heap->size] = value;
    heap->size++;
    min_heapify_up(heap, heap->size - 1);
}

void min_heapify_down(Heap* heap, int index) {
    int min_index = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size && heap->array[left] < heap->array[min_index]) {
        min_index = left;
    }
    
    if (right < heap->size && heap->array[right] < heap->array[min_index]) {
        min_index = right;
    }
    
    if (min_index != index) {
        ElementType temp = heap->array[index];
        heap->array[index] = heap->array[min_index];
        heap->array[min_index] = temp;
        min_heapify_down(heap, min_index);
    }
}

ElementType min_delete(Heap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty!\n");
        return (ElementType)-1; // Assuming -1 is not a valid value
    }
    
    ElementType min = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    
    if (heap->size > 0) {
        min_heapify_down(heap, 0);
    }
    
    return min;
}

void free_heap(Heap* heap) {
    free(heap->array);
    free(heap);
}

// Example usage
int main() {
    // Max Heap example
    Heap* max_heap = create_max_heap();
    max_insert(max_heap, 5);
    max_insert(max_heap, 2);
    max_insert(max_heap, 7);
    max_insert(max_heap, 1);
    max_insert(max_heap, 9);
    
    printf("Max Heap deletions:\n");
    printf("Max: %d\n", max_delete(max_heap)); // 9
    printf("Max: %d\n", max_delete(max_heap)); // 7
    
    // Min Heap example
    Heap* min_heap = create_min_heap();
    min_insert(min_heap, 5);
    min_insert(min_heap, 2);
    min_insert(min_heap, 7);
    min_insert(min_heap, 1);
    min_insert(min_heap, 9);
    
    printf("\nMin Heap deletions:\n");
    printf("Min: %d\n", min_delete(min_heap)); // 1
    printf("Min: %d\n", min_delete(min_heap)); // 2
    
    free_heap(max_heap);
    free_heap(min_heap);
    return 0;
}