#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
typedef struct{
    int *data;
    int top;
    int size;
}Stack;
int createStack(Stack * astack, int size){
    astack->data = (int*)malloc(sizeof(int)*size);
    astack->size = size;
    astack->top = -1;
    return 1;
}
int isEmpty(Stack* astack){
    if(astack->top < 0){
        return 1;
    }
    else 
        return 0;
}
int isFull(Stack* astack){
    if(astack->top >= astack->size-1){
        return 1;
    }
    else 
        return 0;
}
int top(Stack* astack){
    if(!isEmpty(astack)){
        return astack->data[astack->top];
    }
    else
        return 0;
}
int push(Stack* astack, int data){
    if(!isFull(astack)){
        astack->top++;
        astack->data[astack->top] = data;
        return 1;
    }
    else{
        return 0;
    }
}
int pop(Stack* astack){
    if(!isEmpty(astack)){
        astack->top--;
        return 1;
    }
    else{
        return 0;
    }
}
int main(){
    int N;
    int j, k;
    freopen("test220.txt", "r", stdin);
    while(scanf("%d", &N) != EOF){
        if(N == 0)
            break;
        getchar();
        int *arr = (int*)malloc(sizeof(int)*N*2);
        Stack *stack = (Stack*)malloc(sizeof(Stack));
        createStack(stack, 2);
        for(int i = 0; i < N; i++){
            scanf("%d %d", &j, &k);
            arr[j-1] = i;
            arr[k-1] = i;
            getchar(); 
        }
        for(int i = 0; i < 2*N; i++){
            if(arr[i] == top(stack))
                pop(stack);
            else if(!isFull(stack)){
                push(stack, arr[i]);
            }
            else{
                printf("NO\n");
                break;
            }
        }
        if(isEmpty(stack)){
            printf("YES\n");
        }
        free(arr);
        free(stack->data);
        free(stack);
    }      
    return 0;
}
