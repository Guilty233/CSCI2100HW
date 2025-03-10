#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char *data;
    int head;
    int size;
}Stack;

int createStack(Stack *stack, int size){
    stack->data = (char*)malloc(sizeof(char)*size);
    if(stack->data == NULL){
        return 0;
    }
    stack->head = -1;
    stack->size = size;
    return 1;
}

int push(Stack *stack, char c){
    if(stack->head == stack->size-1){
        return 0;
    }
    stack->head++;
    stack->data[stack->head] = c;
    return 1;
}

char pop(Stack *stack){
    if(stack->head == -1){
        return 0;
    }
    char c = stack->data[stack->head];
    stack->head--;
    return c;
}

void freeStack(Stack *stack){
    free(stack->data);
}

int main(){
    int n;
    scanf("%d\n", &n);
    size_t j, i;
    int count;
    int *result = (int*)malloc(sizeof(int)*n);
    for(j = 0; j < n; j++){
        char *s = (char*)malloc(sizeof(char)*1000000); 
        fgets(s, 1000000, stdin);
        Stack stack;
        count = 0;
        createStack(&stack, 1000000);
        size_t len = strlen(s); 
        for(i = 0; i < len; i++){
            switch(s[i]){
                case '(':
                case '[':
                case '{':
                case '<':
                    push(&stack, s[i]);
                    break;
                case ')':
                case ']':
                case '}':
                case '>':
                    if(stack.head == -1){
                        i = len; 
                    } else {
                        char c = pop(&stack);
                        if((c == '(' && s[i] != ')') || (c == '[' && s[i] != ']') || (c == '{' && s[i] != '}') || (c == '<' && s[i] != '>')){
                            count++;
                        }
                    }
                    break;
            }
        }
        if(stack.head == -1 && i == len){
            printf("%d\n", count);
        } else {
            printf("-1\n");
        }
        freeStack(&stack);
        free(s);
    }
    free(result); 
    return 0;
}