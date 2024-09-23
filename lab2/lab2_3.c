#include <stdio.h>
#include <time.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void perm(int *list, int i, int n);

int main(void){
    double duration[10], end;
    int start, len, cnt = 0;
    int A[10] = {0};
    for (int i=0; i<10; i++)
        A[i] = i;
    for (int i = 0; i<10; i++)
    {
        start = clock();
        perm(A, 0, i);
        end = (double)clock();
        duration[i] = (end - start)/CLOCKS_PER_SEC;
    }
    for (int i = 0; i<10; i++)
    {
        perm(A, 0, i);
        printf("\n");
    }
    printf("\t원소갯수\t실행시간\n");
    for (int i = 0; i<10; i++)
    {
        printf("\t%d\t%f\n", i+1, duration[i]);
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
