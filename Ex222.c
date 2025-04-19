#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int N;
    scanf("%d", &N);
    getchar();
    char* line = (char*)malloc(sizeof(char)*10000);
    char* token;
    while(N--){
        fgets(line, 10000, stdin);
        for(int i = 0; i < strlen(line); i++){
            if(line[i] >= '0' && line[i] <= '9'){
                
            }
        }
    }
}