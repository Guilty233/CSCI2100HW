#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int lareven(int *input, size_t length)
{
    int i = 0;
    size_t j;
    for(j = 0; j < length; j++)
    {
        if(input[j] > i && input[j]%2 == 0)
        {
            i = input[j];
        }
    }
    return i;
}
int main(){
    int d;
    scanf("%d", &d);
    size_t i,j;
    int *output = malloc(sizeof(int)*d);
    for(i = 0; i < d; i++)
    {
        int k;
        scanf("%d", &k);
        int *arr = malloc(sizeof(int)*k);
        for(j = 0; j < k; j++)
            scanf("%d", &arr[j]);
        output[i] = lareven(arr, k);
        free(arr);
    }
    for(i = 0; i < d; i++)
    {
        printf("%d\n", output[i]);
    }
    return 0;
}