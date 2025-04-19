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
    short N;
    freopen("test215.txt", "r", stdin);
    scanf("%hd", &N);
    getchar();
    Stack *stack = (Stack *)malloc(sizeof(Stack));;
    createStack(stack, 20);
    int a, b;
    while(N--){
        char *line = (char*)malloc(sizeof(char)*80);
        fgets(line, 80, stdin);
        char* token = strtok(line, " \n");
        while(token != NULL){
            if(!strcmp(token, "P")){
                if(isEmpty(stack))
                    printf("NULL ");
                else{
                    printf("%d ", top(stack));
                    
                }
            }
            else if(!strcmp(token, "+")){
                a = top(stack);
                //printf("a:%d ", a);
                pop(stack);
                b = top(stack);
                pop(stack);
                //printf("b:%d ", b);
                //printf("+:%d ", a+b);
                push(stack, a+b);
            }
            else if(!strcmp(token, "-")){
                a = top(stack);
                pop(stack);
                //printf("a:%d ", a);
                b = top(stack);
                pop(stack);
                //printf("b:%d ", b);
                //printf("-:%d ", b-a);
                push(stack, b-a);
            }
            else if(!strcmp(token, "*")){
                a = top(stack);
                //printf("a:%d ", a);
                pop(stack);
                b = top(stack);
                //printf("b:%d ", b);
                pop(stack);
                //printf("*:%d ", a*b);
                push(stack, a*b);
            }
            else{
                int num = atoi(token);
                push(stack, num);
            }
            token = strtok(NULL, " \n");
        }
        printf("\n");
        free(line);
    }
    return 0;
}