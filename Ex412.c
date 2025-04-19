#include<stdio.h>
#include<stdlib.h>
typedef int ElementType;

typedef struct {
    ElementType* array;
    int size;
    int capacity;
} Heap;
Heap* create_min_heap(int size) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->array = (ElementType*)malloc(sizeof(ElementType) * size);
    heap->size = 0;
    heap->capacity = size;
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
int main(){
    short N;
    freopen("test412.txt", "r", stdin);
    scanf("%hd", &N);
    getchar();
    Heap* heap = create_min_heap(100000);
    for(int i = 0; i < N; i++){
        int num;
        scanf("%d", &num);
        for(int j = 0; j < num; j++){
            int a;
            scanf("%d", &a);
            min_insert(heap, a);
        }
    }
    //printf("size : %d", heap->size);
    int size = heap->size;
    for(int i = 0; i < size; i++){
        printf("%d\n", min_delete(heap));
    }
    
    free_heap(heap);
    return 0;
}
