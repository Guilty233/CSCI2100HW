#include <stdio.h>
#include <stdbool.h>

int main(){
    short N;
    short i, l;
    bool flag;
    freopen("test125.txt", "r", stdin);
    scanf("%hd", &N);
    while(N--){
        flag = true;
        scanf("%hd", &i);
        while(i>0){
            l = i %2;
            i /= 2;
            if(i%2 == l ){
                flag = false;
                break;
            }
        }   
        printf("%s\n", flag ? "True" : "False");
    }
}