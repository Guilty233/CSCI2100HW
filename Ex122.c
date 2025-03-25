#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
int main(){
    short N;
    size_t len = 256;
    short sum = 0;
    freopen("test122.txt", "r", stdin);
    scanf("%hd", &N);
    getchar();
    char *str = (char *)malloc(256 * sizeof(char));
    while(N--){
        fgets(str, len, stdin);
        sum = 0;
        for(int i = 0; i < strlen(str); i++){
            if(isdigit(str[i])){
                sum++;
            }
        }
        printf("%hd\n", sum);
    }
    free(str);
    return 0;
}