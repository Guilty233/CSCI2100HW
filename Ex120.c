#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int main(){
    int d;
    scanf("%d", &d);
    char **arr = malloc(sizeof(char*) * d);
    for (size_t i = 0; i < d; i++) 
    {
        arr[i] = malloc(sizeof(char) * 100);
        scanf("%s", arr[i]); 
    }
    for(size_t i = 0; i < d; i++)
    {
        for(size_t j = 0; j < strlen(arr[i]); j++)
        {
            if(!isdigit(arr[i][j]))
            {
                printf("%c", arr[i][j]);
            }
            
        }
        
        printf("\n");
    }
    for (size_t i = 0; i < d; i++) 
    {
        free(arr[i]); 
    }
    free(arr); 
    return 0;
}