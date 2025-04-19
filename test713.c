#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure for adjacency list graph
typedef struct Graph {
    Node** adj; // Array of pointers to adjacency lists
    int V;      // Number of vertices
} Graph;

// Structure for min-heap
typedef struct MinHeap {
    int* arr;
    int size;
    int capacity;
} MinHeap;

// Create a new node for adjacency list
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++) {
        graph->adj[i] = NULL;
    }
    return graph;
}

// Add edge to the graph
void addEdge(Graph* graph, int x, int y) {
    Node* newNode = createNode(y);
    newNode->next = graph->adj[x];
    graph->adj[x] = newNode;
}

// Create a min-heap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Swap two elements in the heap
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify down to maintain min-heap property
void heapifyDown(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }
    if (smallest != idx) {
        swap(&heap->arr[idx], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

// Push element to min-heap
void pushHeap(MinHeap* heap, int val) {
    if (heap->size == heap->capacity) return;
    heap->arr[heap->size] = val;
    int idx = heap->size;
    heap->size++;

    // Heapify up
    while (idx > 0 && heap->arr[(idx - 1) / 2] > heap->arr[idx]) {
        swap(&heap->arr[idx], &heap->arr[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
}

// Pop minimum element from min-heap
int popHeap(MinHeap* heap) {
    if (heap->size == 0) return -1;
    int result = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
    return result;
}

// Check if heap is empty
bool isHeapEmpty(MinHeap* heap) {
    return heap->size == 0;
}

// Free graph memory
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        Node* current = graph->adj[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adj);
    free(graph);
}

// Free heap memory
void freeHeap(MinHeap* heap) {
    free(heap->arr);
    free(heap);
}

// Function to perform topological sort
void topologicalSort(Graph* graph, int n, int* result, int* resultSize) {
    int V = graph->V;
    int* in_degree = (int*)calloc(V, sizeof(int));

    // Calculate in-degrees
    for (int u = 0; u < V; u++) {
        Node* current = graph->adj[u];
        while (current) {
            in_degree[current->vertex]++;
            current = current->next;
        }
    }

    // Initialize min-heap
    MinHeap* pq = createMinHeap(V);
    for (int i = 0; i < V; i++) {
        if (in_degree[i] == 0) {
            pushHeap(pq, i);
        }
    }

    int cnt = 0;
    *resultSize = 0;

    // Process vertices
    while (!isHeapEmpty(pq)) {
        int u = popHeap(pq);
        result[(*resultSize)++] = u + 1; // Adjust for 1-based indexing

        // Decrease in-degree of neighbors
        Node* current = graph->adj[u];
        while (current) {
            if (--in_degree[current->vertex] == 0) {
                pushHeap(pq, current->vertex);
            }
            current = current->next;
        }
        cnt++;
    }

    // Check for cycle
    if (cnt != V) {
        *resultSize = 0; // Indicate failure
    }

    free(in_degree);
    freeHeap(pq);
}

int main() {
    int N;
    freopen("test713.txt", "r", stdin);
    scanf("%d", &N);

    for (int test = 0; test < N; test++) {
        int n, m;
        scanf("%d %d", &n, &m);

        // Create graph
        Graph* graph = createGraph(n);

        // Read inversions and add edges
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            addEdge(graph, a - 1, b - 1); // Adjust for 0-based indexing
        }

        // Perform topological sort
        int result[500];
        int resultSize;
        topologicalSort(graph, n, result, &resultSize);

        // Print result
        if (resultSize == 0) {
            printf("-1\n");
        } else {
            for (int i = 0; i < resultSize; i++) {
                printf("%d", result[i]);
                if (i < resultSize - 1) {
                    printf(" ");
                }
            }
            printf("\n");
        }

        // Clean up
        freeGraph(graph);
    }

    return 0;
}