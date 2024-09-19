#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_SIZE 1000001
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
void sort(int [],int); 
int is_sorted(int [], int n);

int main(void)
{
    int n, i, j, step=10;
    int list[MAX_SIZE];
    double duration;
    clock_t start;
    for (n = 100; n <= 1000000; n+= step)
    {
        for (i = 0; i < n; i++)
            list[i] = n-i;
        start = clock();
        sort(list, n);
        duration = ((double) (clock() - start))/CLOCKS_PER_SEC;
        printf("\nSorted array:\n");
        for (j = 0; j < n; j++)
            printf("%d ",list[j]);
        printf("\n");
        if(is_sorted(list, n) == 1){
            printf("is sorted\n");
        }
        else{
            printf("is not sorted\n");
        }
        printf("%6d     %f\n", n, duration);
        if (n == 100)
            step = 100;
        else if (n == 1000)
            step = 1000;
        else if (n == 10000)
            step = 10000;
        else if (n == 100000)
            step = 100000;
        else if (n == 1000000)
            step = 1000000;
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

