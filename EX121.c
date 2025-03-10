#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
bool isPowerOfFive(int x){
    if(x == 0){
        return false;
    }
    else{
        while(x > 1){
            if(x%5 != 0 ){
                return false;
            }else{
                x/=5;
            }
        }
    }
    return true;
}
int main(){
    int d;
    scanf("%d", &d);
    int  *arr = malloc(sizeof(int) * d);
    size_t i;
    for(i = 0; i < d; i++)
    {
        scanf("%d", &arr[i]);
    }
    for(i = 0; i < d; i++)
    {
        if(isPowerOfFive(arr[i])){
            printf("True\n");
        }else{
            printf("False\n");
        }
    }
    free(arr);
    return 0;
}