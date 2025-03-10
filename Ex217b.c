#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int capacity;
    int numofelements;
    int head;
    int tail;
    int *data;
}queue;
int createqueue(queue *q, int capacity)
{
    q->data = (int*)malloc(sizeof(int) * capacity);
    q->capacity = capacity;
    q->numofelements = 0;
    q->head = 0;
    q->tail = -1;
    q->data = malloc(sizeof(int) * capacity);
    return 1;
}
int enqueue(queue *q, int element)
{
    if(q->numofelements == q->capacity)
    {
        return 0;
    }
    q->tail = (q->tail + 1) % q->capacity;
    q->data[q->tail] = element;
    q->numofelements++;
    return 1;
}
int dequeue(queue *q)
{
    if(q->numofelements == 0)
    {
        return 0;
    }
    q->head = (q->head + 1) % q->capacity;
    q->numofelements--;
    return 1;
}
void freequeue(queue *q)
{
    free(q->data);
    free(q);
}

int main(){
    int x, y;
    size_t i, j, k;
    size_t stringsize = 100;
    size_t newstringsize = 0;
    char *string = malloc(sizeof(char) * stringsize);
    string[0] = '\0';
    int size = 0;
    scanf("%d", &x);
    for(i = 0; i < x; i++){
        scanf("%d", &y);
        queue *q = malloc(sizeof(queue));
        createqueue(q, y);
        int *arr = malloc(sizeof(int) * y);
        char *str = malloc(sizeof(char) * (2*y+1));
        int strindex = 0;
        for(j = 0; j < y; j++){
            scanf("%d", &arr[j]);
        }
        k = 1; //1 to N, only enqueue or striaght will increase k
        for(j = 0; j < y; j++){
            //printf("arr[%d]: %d ", j, arr[j]);
            //printf("K: %d ", k);
            if(arr[j] > k){
                //printf("P1");
                while(k < arr[j]){
                    enqueue(q, k);
                    str[strindex] = 'I';
                    strindex++;
                    k++;
                }
                str[strindex] = 'S';
                strindex++;
                k++;
            }
            else if(arr[j] == k){
                //printf("P2");
                str[strindex] = 'S';
                strindex++;
                k++;
            }
            else if(q->data[q->head] == arr[j]){
                //printf("P3");
                str[strindex] = 'O';
                strindex++;
                dequeue(q);
            }
            else{
                //printf("P4");
                break;
            }
        }
        if(j == y && q->numofelements == 0){
            newstringsize = strlen(string) + strlen(str) + 2;
            if(newstringsize > stringsize){
                stringsize = newstringsize;
                string = realloc(string, stringsize);
            }
            str[strindex] = '\0';
            strcat(string,str);
            strcat(string, "\n");
        }
        else{
            newstringsize = strlen(string) + 11;
            if(newstringsize > stringsize){
                stringsize = newstringsize;
                string = realloc(string, stringsize);
            }
            strcat(string, "Impossible");
            strcat(string, "\n");
        }
        free(arr);
        free(str);
        freequeue(q);
    }
    printf("%s", string);
    free(string);
    return 0;
}