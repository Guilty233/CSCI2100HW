#include <stdio.h>
#include <stdlib.h>
int* mergedarr(int *a, int n, int *b, int m){
    int *c = (int*)malloc(sizeof(int) * (n + m));
    int i = 0, j = 0, k = 0;
    while(i < n && j < m){
        if(a[i] < b[j]){
            c[k++] = a[i++];
        }
        else{
            c[k++] = b[j++];
        }
    }
    while(i < n){
        c[k++] = a[i++];
    }
    while(j < m){
        c[k++] = b[j++];
    }
    return c;
}
int main(){
    short N;
    short n , m;
    freopen("test613.txt", "r", stdin);
    scanf("%hd", &N);
    getchar();
    while(N--){
        scanf("%hd %hd", &n, &m);
        int *a = (int*)malloc(sizeof(int) * n);
        int *b = (int*)malloc(sizeof(int) * m);
        for(int i = 0; i < n; i++){
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < m; i++){
            scanf("%d", &b[i]);
        }
        int*c = mergedarr(a, n, b, m);
        for(int i = 0; i < n + m; i++){
            printf("%d ", c[i]);
        }
        int size = n+m;
        printf("size = %d\n", size);
        if(size%2 == 0){
            printf("%0.1f", ((float)c[size/2] + (float)c[size/2 - 1])/2);
        }
        else{
            printf("%0.1f", (float)c[size/2]);
        }
        printf("\n");
        free(a);
        free(b);
        free(c);
    }
}