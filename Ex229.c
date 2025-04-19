#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *data;
    int top;
    int size;
}Stack;

int creatStack(Stack *s, int size){
    s->data = (int*)malloc(sizeof(int)*size);
    if(s->data == NULL)
        return 0;
    s->size = size;
    s->top = -1;
    return 1;
}

int isEmpty(Stack *s){
    if(s->top < 0)
        return 1;
    else
        return 0;
}
int isFull(Stack *s){
    if(s->top >= s->size - 1)
        return 1;
    else 
        return 0;
}
int top(Stack* s){
    if(!isEmpty(s))
        return s->data[s->top];
    else
        return 0;
}
int pop(Stack* s){
    if(!isEmpty(s)){
        int adata = top(s);
        s->top--;
        return adata;
    }
    else 
        return 0;
}
int makeEmpty(Stack* s){
    s->top = -1;
    return 1;
}
int push(Stack* s, int data){
    if(!isFull(s)){
        s->top++;
        s->data[s->top] = data;
        return 1;
    }
    else 
        return 0;
}
void DisposeStack( Stack* S )
{
	if( S != NULL )
	{
		free( S->data );
		free( S );
	}
}

int main(){
    short N;
    short i, j;
    char c;
    freopen("test229.txt", "r", stdin);
    scanf("%hd", &N);
    Stack *s = (Stack*)malloc(sizeof(Stack));
    creatStack(s, 200);
    while(N--){
        scanf("%hd", &i);
        getchar();
        for(j = 0; j < i; j++){
            c = getchar();
            if(c == '(')
                push(s, 1);
            else if(c == ')'){
                if(!isEmpty(s) && top(s) == 1){
                    pop(s);
                }
                else{
                    push(s, 0);
                }
            }
        }
        getchar();
        if(isEmpty(s)){
            printf("0\n");
        }
        else{
            printf("%hd\n", s->top + 1);
        }
        makeEmpty(s);
    }
    DisposeStack(s);
    return 0;
}