#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize (1000000)
#define MinData (-32767)

typedef int ElementType;
struct HeapStruct { int Capacity; int Size; ElementType *Elements; };
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements) {
    PriorityQueue H = malloc(sizeof(struct HeapStruct));
    if (!H) exit(1);
    H->Elements = malloc((MaxElements + 1) * sizeof(ElementType));
    if (!H->Elements) { free(H); exit(1); }
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData;
    return H;
}

int IsEmpty(PriorityQueue H) { return H->Size == 0; }
int IsFull(PriorityQueue H) { return H->Size == H->Capacity; }
void Destroy(PriorityQueue H) { free(H->Elements); free(H); }

void Insert(ElementType X, PriorityQueue H) {
    int i;
    if (IsFull(H)) return;
    for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
        H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = X;
}

ElementType Delete(PriorityQueue H) {
    int i, Child;
    ElementType Element, LastElement;
    if (IsEmpty(H)) return H->Elements[0];
    Element = H->Elements[1];
    LastElement = H->Elements[H->Size--];
    for (i = 1; i * 2 <= H->Size; i = Child) {
        Child = i * 2;
        if (Child != H->Size && H->Elements[Child + 1] < H->Elements[Child])
            Child++;
        if (LastElement > H->Elements[Child])
            H->Elements[i] = H->Elements[Child];
        else
            break;
    }
    H->Elements[i] = LastElement;
    return Element;
}

int main() {
    short N, n, k, i;
    unsigned short x;
    bool isMax;
    if (!freopen("test416.txt", "r", stdin)) { perror("Input file error"); return 1; }
    if (!freopen("output416.txt", "w", stdout)) { perror("Output file error"); return 1; }
    if (scanf("%hd", &N) != 1) { fprintf(stderr, "Failed to read N\n"); return 1; }
    //fprintf(stderr, "N = %d\n", N);
    while (N > 0) {
        if (scanf("%hd %hd", &n, &k) != 2) { fprintf(stderr, "Failed to read n k\n"); return 1; }
        //fprintf(stderr, "n = %d, k = %d\n", n, k);
        PriorityQueue H = Initialize(n * n);
        for (i = 0; i < n * n; i++) {
            if (scanf("%hu", &x) != 1) { fprintf(stderr, "Failed to read element %d\n", i); Destroy(H); return 1; }
            Insert(x, H);
        }
        k = n * n - k + 1;
        for (i = 0; i < k; i++) {
            ElementType val = Delete(H);
            if (i == k - 1) {
                printf("%d\n", val);
                fflush(stdout);
            }
        }
        Destroy(H);
        N--;
    }
    return 0;
}