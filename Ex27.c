#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )

typedef int ElementType;

struct StackRecord
{
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};
typedef struct StackRecord *Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
void MakeEmpty(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack( Stack S );
void Push( ElementType X, Stack S );
ElementType Top( Stack S );
void Pop( Stack S );
ElementType TopAndPop( Stack S );
/* START: fig3_48.txt */
int IsEmpty( Stack S )
{
	return S->TopOfStack == EmptyTOS;
}
/* END */

int IsFull( Stack S )
{
	return S->TopOfStack == S->Capacity - 1;
}

/* START: fig3_49.txt */
void MakeEmpty( Stack S )
{
	S->TopOfStack = EmptyTOS;
}
/* END */

/* START: fig3_46.txt */
Stack CreateStack( int MaxElements )
{
	Stack S;

	if( MaxElements < MinStackSize )
		printf( "Stack size is too small" );

	S = malloc( sizeof( struct StackRecord ) );
	if( S == NULL )
		printf( "Out of space!!!" );

	S->Array = malloc( sizeof( ElementType ) * MaxElements );
	if( S->Array == NULL )
		printf( "Out of space!!!" );
	S->Capacity = MaxElements;
	MakeEmpty( S );

	return S;
}
/* END */



/* START: fig3_47.txt */
void DisposeStack( Stack S )
{
	if( S != NULL )
	{
		free( S->Array );
		free( S );
	}
}
/* END */

/* START: fig3_50.txt */
void Push( ElementType X, Stack S )
{
	if( IsFull( S ) )
		printf( "Full stack" );
	else
		S->Array[ ++S->TopOfStack ] = X;
}
/* END */


/* START: fig3_51.txt */
ElementType Top( Stack S )
{
	if( !IsEmpty( S ) )
		return S->Array[ S->TopOfStack ];
	//printf( "Empty stack" );
	return 0;  /* Return value used to avoid warning */
}
/* END */

/* START: fig3_52.txt */
void Pop( Stack S )
{
	if( IsEmpty( S ) )
		printf( "Empty stack" );
	else
		S->TopOfStack--;
}
/* END */

/* START: fig3_53.txt */
ElementType TopAndPop( Stack S )
{
	if( !IsEmpty( S ) )
		return S->Array[ S->TopOfStack-- ];
	printf( "Empty stack" );
	return 0;  /* Return value used to avoid warning */
}
int main(){
    char line[1024];
    bool  error;    
    freopen("test27.txt", "r", stdin);
    while(fgets(line, 1024, stdin) != NULL){
        Stack S = CreateStack(100);
        error = false;
        for(int i = 0; i < strlen(line); i++){
            if(line[i] == '(' || line[i] == '[' || line[i] == '{'){
                Push(line[i], S);
            }
            else if(line[i] == ')'){
                if(Top(S) == '('){
                    Pop(S);
                } 
                else if(IsEmpty(S)){
                    printf("Error: stack empty\n");
                    error = true;
                    break;
                }
                else{
                    printf("Unmatched Error:  (.\n");
                    error = true;
                    MakeEmpty(S);
                    break;
                }
            }
            else if(line[i] == ']'){
                if(Top(S) == '['){
                    Pop(S);
                }
                else if(IsEmpty(S)){
                    printf("Error: stack empty\n");
                    error = true;
                    break;
                }
                else{
                    printf("Unmatched Error:  (.\n");
                    error = true;
                    MakeEmpty(S);
                    break;
                }
            }
            else if(line[i] == '}'){
                if(Top(S) == '{'){
                    Pop(S);
                }
                else if(IsEmpty(S)){
                    printf("Error: stack empty\n");
                    error = true;
                    break;
                }
                else{
                    printf("Unmatched Error:  (.\n");
                    error = true;
                    MakeEmpty(S);
                    break;
                }
            }
        }
        if(IsEmpty(S) && !error){
            printf("No error\n");
        }
        if (!IsEmpty(S) && !error){
            printf("Error: Too many leftover symbol(s).\n");
        }
    }

    return 0;
}