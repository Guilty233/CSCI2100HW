#include <stdio.h>
#include <stdlib.h>


#define NumItems 400

typedef int ElementType;
typedef unsigned int Index;
typedef struct ListNode *Position;

struct ListNode
{
	ElementType Element;
	Position    Next;
};

typedef Position List;
/* List *TheLists will be an array of lists, allocated later */
/* The lists use headers (for simplicity), though this wastes space */
struct HashTbl
{
	int TableSize;
	List *TheLists;
};

typedef struct HashTbl *HashTable;

/* Return next prime; assume N >= 10 */
static int NextPrime( int N )
{
	int i;

	if( N % 2 == 0 )
		N++;
	for( ; ; N += 2 )
	{
		for( i = 3; i * i <= N; i += 2 )
			if( N % i == 0 )
				goto ContOuter;  /* Sorry about this! */
		return N;
		ContOuter: ;
	}
}

/* Hash function for ints */
Index Hash( ElementType Key, int TableSize )
{
	return Key % TableSize;
}

/* START: fig5_8.txt */
HashTable InitializeTable( int TableSize )
{
	HashTable H;
	int i;
	if( TableSize < 10 )
	{
		TableSize = 10;
	}
	/* Allocate table */
	H = malloc( sizeof( struct HashTbl ) );
	if( H == NULL )
		printf( "Out of space!!!" );

	H->TableSize = NextPrime( TableSize );

	/* Allocate array of lists */
	H->TheLists = malloc( sizeof( List ) * H->TableSize );
	if( H->TheLists == NULL )
		printf( "Out of space!!!" );

	/* Allocate list headers */
	for( i = 0; i < H->TableSize; i++ )
	{
		H->TheLists[ i ] = malloc( sizeof( struct ListNode ) );
		if( H->TheLists[ i ] == NULL )
			printf( "Out of space!!!" );
		else
			H->TheLists[ i ]->Next = NULL;
	}

	return H;
}
/* END */

/* START: fig5_9.txt */
Position Find( ElementType Key, HashTable H )
{
	Position P;
	List L;

	L = H->TheLists[ Hash( Key, H->TableSize ) ];
	P = L->Next;
	while( P != NULL && P->Element != Key ) /* Probably need strcmp!! */
		P = P->Next;
	return P;
}
/* END */

/* START: fig5_10.txt */
void Insert( ElementType Key, HashTable H )
{
	Position Pos, NewCell;
	List L;

	Pos = Find( Key, H );
	if( Pos == NULL )   /* Key is not found */
	{
		NewCell = malloc( sizeof( struct ListNode ) );
		if( NewCell == NULL )
			printf( "Out of space!!!" );
		else
		{
			L = H->TheLists[ Hash( Key, H->TableSize ) ];
			NewCell->Next = L->Next;
			NewCell->Element = Key;  /* Probably need strcpy! */
			L->Next = NewCell;
		}
	}
}
/* END */

ElementType Retrieve( Position P )
{
	return P->Element;
}

void DestroyTable( HashTable H )
{
	int i;

	for( i = 0; i < H->TableSize; i++ )
	{
		Position P = H->TheLists[ i ];
 		Position Tmp;

		while( P != NULL )
		{
			Tmp = P->Next;
 			free( P );
			P = Tmp;
		}
	}
	free( H->TheLists );
	free( H );
}
int compare(const void *a, const void *b){
	return *(int *)a - *(int *)b;
}
int main(){
    short N;
    int n, m;
    int i,j,k;
    int count;
	int arrsize;	
	//freopen("test521.txt", "r", stdin);
	//freopen("output521.txt", "w", stdout);
    scanf("%hd", &N);
    for(i = 0; i < N; i++){
        scanf("%d %d", &n, &m);
		count = 0;
		int *arr = (int *)malloc(sizeof(int) * n);
		arrsize = 0;
		for(j = 0; j < n; j++){
			scanf("%d", &k);
			if(k == 0){
				if(m == 0){
					count = (n-1)*(n-2)/2;
				}
			}
			else{
				if(m % k == 0 && m != 0){
					arr[arrsize] = k;
					arrsize++;
				}
			}
		}
		//printf("arrsize: %d\n", arrsize);
		if(count != 0 && m == 0){
			printf("%d\n", count);
			free(arr);
			continue;
		}
		else if(m == 0 && count == 0){
			printf("0\n");
			free(arr);
			continue;
		}
		arr = (int *)realloc(arr, sizeof(int) * arrsize);
		qsort(arr, arrsize, sizeof(int), compare);
		HashTable H = InitializeTable(arrsize);
		for(j = 0; j < arrsize; j++){
			Insert(arr[j], H);
		}
		if(arrsize >= 10){
			for(j = 0; j < arrsize - 2; j++){
				for(k = j + 1; k < arrsize - 1; k++){
					//printf("%d %d %d \n", arr[j], arr[k], (m/arr[j])/arr[k]);
					if(m%(arr[j]*arr[k]) == 0 && m/(arr[j]*arr[k]) > arr[j] && m/(arr[j]*arr[k]) > arr[k]){
						//printf("Checking triplet (%d, %d, %d)\n", arr[j], arr[k], (m/arr[j])/arr[k]);
						if(Find((m/arr[j])/arr[k], H) != NULL){
							count++;
							//printf("count : %d\n", count);
						}
					}
					else if (m/(arr[j]*arr[k]) < arr[j] && m/(arr[j]*arr[k]) < arr[k])
						break;
				}
			}
		}	
		else{
			for (j = 0; j < arrsize - 1; j++) {
				for (k = j + 1; k < arrsize; k++) {
					int third = m / (arr[j] * arr[k]);
					if (m % (arr[j] * arr[k]) == 0 && third > arr[j] && third > arr[k]) {
						if (Find(third, H) != NULL) {
							count++;
						}
					}
				}
			}
		}
		DestroyTable(H);
		free(arr);	
		printf("%d\n", count);
	}
    return 0;
}