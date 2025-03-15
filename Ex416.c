#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize (1000000)
#define MinPQSize (10)
#define MinData (-32767)

typedef int ElementType;
struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Elements;
};
        
typedef struct HeapStruct *PriorityQueue;

/* START: fig6_0.txt */
PriorityQueue Initialize( int MaxElements )
{
    PriorityQueue H;

    if( MaxElements < MinPQSize )
        printf( "Priority queue size is too small" );

    H = malloc( sizeof( struct HeapStruct ) );
    if( H ==NULL )
        printf( "Out of space!!!" );

    /* Allocate the array plus one extra for sentinel */
    H->Elements = malloc( ( MaxElements + 1 ) * sizeof( ElementType ) );
    if( H->Elements == NULL )
        printf( "Out of space!!!" );

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[ 0 ] = MinData;

    return H;
}
PriorityQueue copyqueue(PriorityQueue H){
    PriorityQueue tmp = Initialize(H->Capacity);
    tmp->Size = H->Size;
    for(int i = 0; i <= H->Size; i++)
        tmp->Elements[i] = H->Elements[i];
    return tmp;
}

/* END */
int IsEmpty( PriorityQueue H )
{
    return H->Size == 0;
}

int IsFull( PriorityQueue H )
{
    return H->Size == H->Capacity;
}

void Destroy( PriorityQueue H )
{
    free( H->Elements );
    free( H );
}

void MakeEmpty( PriorityQueue H )
{
    H->Size = 0;
}

/* START: fig6_8.txt */
/* H->Element[ 0 ] is a sentinel */
void Insert( ElementType X, PriorityQueue H , bool isMax)
{
    int i;

    if( IsFull( H ) )
    {
        printf( "Priority queue is full" );
        return;
    }

    for( i = ++H->Size; isMax ? H->Elements[ i / 2 ] < X : H->Elements[ i / 2 ] > X; i /= 2 ) // MAX: <
        H->Elements[ i ] = H->Elements[ i / 2 ]; 
    H->Elements[ i ] = X;
}

/* END */

/* START: fig6_12.txt */
ElementType Delete( PriorityQueue H ,bool isMax)
{
    int i, Child;
    ElementType Element, LastElement;

    if( IsEmpty( H ) )
    {
        printf( "Priority queue is empty" );
        return H->Elements[ 0 ];
    }
    Element = H->Elements[ 1 ];
    LastElement = H->Elements[ H->Size-- ];

    if(isMax){
        for( i = 1; i * 2 <= H->Size; i = Child )
        {
            /* Find smaller child */
            Child = i * 2;
            if( Child != H->Size && H->Elements[ Child + 1 ] > H->Elements[ Child ] )
                Child++;
            /* Percolate one level */
            if( LastElement < H->Elements[ Child ] )
                H->Elements[ i ] = H->Elements[ Child ];
            else
                break;
        }
    }else{
        for( i = 1; i * 2 <= H->Size; i = Child )
        {
            /* Find smaller child */
            Child = i * 2;
            if( Child != H->Size && H->Elements[ Child + 1 ] < H->Elements[ Child ] )
                Child++;
            /* Percolate one level */
            if( LastElement > H->Elements[ Child ] )
                H->Elements[ i ] = H->Elements[ Child ];
            else
                break;
        }
    }
    H->Elements[ i ] = LastElement;
    return Element;
}
/* END */

ElementType FindMin( PriorityQueue H )
{
    if( !IsEmpty( H ) )
        return H->Elements[ 1 ];
    printf( "Priority Queue is Empty" );
    return H->Elements[ 0 ];
}
int main(){
    short N, n, k, i;
    unsigned short x;
    bool isMax;
    freopen("test416.txt", "r", stdin);
    freopen("output416.txt", "w", stdout);
    scanf("%hd", &N);
    while(N > 0){
        scanf("%hd %hd", &n, &k);
        PriorityQueue H = Initialize(n*n);
        if(k < n*n - k){
            isMax = true;
        }
        else{
            isMax = false;
            k = n*n - k;
        }	
        for(i = 0; i < n*n; i++){
            scanf("%hu", &x);
            Insert(x, H, isMax);
        }   
        for(i = 0; i < k; i++){
            Delete(H, isMax);
            if(i == k - 1)
                printf("%d\n", Delete(H, isMax));
        }
        Destroy(H);
        N--;
    }
    return 0;
}