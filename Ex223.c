#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

void createStack(Stack *stack, int capacity) {
    stack->data = (int*)malloc(sizeof(int) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
}

void push(Stack *stack, int value) {
    stack->data[++stack->top] = value;
}

int pop(Stack *stack) {
    return stack->data[stack->top--];
}

void freeStack(Stack *stack) {
    free(stack->data);
}

int main() {
    int n;
    scanf("%d", &n);
    size_t i, j;
    int a, b;
    char line[255];
    for (i = 0; i < n; i++) {
        scanf(" %[^\n]", line); 
        char *token = strtok(line, " ");
        Stack stack;
        createStack(&stack, 255);
        while (token != NULL) {
            if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0) {
                b = pop(&stack);
                a = pop(&stack);
                if (strcmp(token, "+") == 0) {
                    push(&stack, a + b);
                } else if (strcmp(token, "-") == 0) {
                    push(&stack, a - b);
                } else if (strcmp(token, "*") == 0) {
                    push(&stack, a * b);
                } else if (strcmp(token, "/") == 0) {
                    if (b == 0) {
                        printf("division by zero\n");
                        break;
                    } else {
                        push(&stack, a / b);
                    }
                }
            } else if (strcmp(token, "!") == 0) {
                a = pop(&stack);
                if (a < 0) {
                    printf("factorial of an negative number\n");
                    break;
                } else {
                    int fact = 1;
                    for (int k = 1; k <= a; k++) {
                        fact *= k;
                    }
                    push(&stack, fact);
                }
            } else {
                push(&stack, atoi(token));
            }
            token = strtok(NULL, " ");
        }
        if(token == NULL) {
            printf("%d\n", stack.data[stack.top]);
        }
        freeStack(&stack);
    }

    return 0;
}