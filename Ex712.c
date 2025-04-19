#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_EDGES 1000


int main() {
    short n, i, k, u, v;
    freopen("test712.txt", "r", stdin);
    scanf("%hd", &n);
    for (i = 0; i < n; i++) {
        bool boolean = true;
        scanf("%hd", &k);
        short* color = (short*)calloc(k , sizeof(short));// color[i] = 0/1/2;
        while (1) {
            scanf("%hd", &u);
            if (u == -1) break;
            scanf("%hd", &v);
            switch(color[u-1]){
                case 0:
                    switch(color[v-1]){
                        case 0:
                            color[u-1] = 1;
                            color[v-1] = 2;
                            break;
                        case 1:
                            color[u-1] = 2;
                            break;
                        case 2:
                            color[u-1] = 1;
                            break;
                    }
                    break;
                case 1:
                    switch(color[v-1]){
                        case 0:
                            color[v-1] = 2;
                            break;
                        case 1:
                            boolean = false;
                            break;
                    }
                    break;
                case 2:
                    switch(color[v-1]){
                        case 0:
                            color[v-1] = 1;
                            break;
                        case 2:
                            boolean = false;
                            break;
                    }
                    break;
            }
            
        }
        free(color);
        if (boolean) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}