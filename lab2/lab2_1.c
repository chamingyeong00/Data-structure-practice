#include <stdio.h>
#include <string.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

void perm(char *list, int i, int n);

int main(void){
    char A[][10] ={"GO", "BOY", "GIRL", "GIRLS"};
    for (int i = 0; i < 4; i++)
    {
        int len = strlen(A[i]);
        //printf("len : %d\n", len);
        printf("str : ");
        for (int j=0; j<len; j++)
            printf("%c", A[i][j]);
        printf("\n");
        perm(A[i], 0, len-1);
        printf("\n");
    }
}

void perm(char *list, int i, int n){
    int j, temp;
    if (i==n)
    {
        for (int i=0; i<=n; i++)
        {
            printf("%c", list[i]);
        }
        printf("\t");
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