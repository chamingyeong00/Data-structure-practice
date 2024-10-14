#include <stdio.h>
#include <time.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void perm(int *list, int i, int n);

int main(void){
    double duration;
    int start, len, cnt = 0;
    int A[32] = {0};
    while(1)
    {
        printf("input : ");
        scanf("%d", &len);
        if (len == -1)
            break;
        if (len < 1 || len > 32)
        {
            printf("입력 범위를 벗어났습니다.\n");  
            continue;
        }
        for (int i=0; i<len; i++)
            A[i] = i;
        printf("순열 : \n");
        start = clock();
        perm(A, 0, len - 1);
        duration = ((double)clock() - start)/CLOCKS_PER_SEC;
        printf("\n실행시간 %6f", duration);
        printf("\n");
    }
}

void perm(int *list, int i, int n){
    int j, temp;
    if (i==n)
    {
        for (int i=0; i<=n; i++)
        {
            printf("%d", list[i]);
        }
        printf(" ");
    }
    else{
        for(int j=i; j<=n; j++)
        {
            SWAP(list[i], list[j], temp);
            perm(list, i+1, n);
            SWAP(list[i], list[j], temp);
        }
    }
}