#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000001
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
void sort(int [],int); 
int is_sorted(int [], int n);

int main(void)
{
    int i, n, j;
    int A[MAX_SIZE];
    printf("Enter the number of numbers to generate: ");
    scanf("%d", &n);

    if( n < 1 || n > MAX_SIZE) {
        fprintf(stderr, "Improper value of n\n"); 
        return 0;
    }
    printf("랜덤 숫자 : ");
    for (i = 0; i < n; i++) {
        A[i] = rand()%100000 + 1;
    }
    printf("\nSorted array:\n");
    for (j = 0; j < 10; j++)
        printf("%d ",A[j]);
    printf(" . . . ");
    for (j = n-10; j < n; j++)
        printf("%d ",A[j]);
    printf("\n");
    sort(A, n);
    printf("\nSorted array:\n");
    for (j = 0; j < 10; j++)
        printf("%d ",A[j]);
    printf(" . . . ");
    for (j = n-10; j < n; j++)
        printf("%d ",A[j]);
    printf("\n");
    if(is_sorted(A, n) == 1){
        printf("is sorted\n");
    }
    else{
        printf("is not sorted\n");
    }
}

int is_sorted(int *list, int n)
{
    for(int i=0; i<n-1; i++)
    {
        if(list[i] > list[i+1])
        {
            return 0;
        }
    }
    return 1;
}

void sort(int *list,int n)
{
    int i, j, min, temp;
    for(i=0; i<n-1; i++){
        min = i;
        for (j=i; j<n; j++){
            if (list[j] < list[min])
                min = j;
        }
        SWAP(list[i],list[min],temp);
    }
    
}

