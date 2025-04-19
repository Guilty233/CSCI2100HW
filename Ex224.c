#include <stdio.h>

int main(){
    int N;
    int num5coin = 0;
    int coin;
    int numbot = 0;
    freopen("test224.txt", "r", stdin);
    scanf("%d", &N);
    while(N--){
        scanf("%d", &coin);
        if(coin == 5){
            num5coin++;
            numbot++;
        }
        else if(coin == 10){
            if(num5coin > 0){
                num5coin--;
                numbot++;
            }
            else
                continue;
        }
    }
    printf("%d\n", numbot);
    return 0;
}