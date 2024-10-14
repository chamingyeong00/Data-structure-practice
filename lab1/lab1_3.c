#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100001
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t))
#define COMPARE(x,y) ((x)>(y) ? 1 : (((x) < (y)) ? -1 : 0))
void sort(int [],int); 
int is_sorted(int [], int n);
int binsearch(int list[], int searchnum, int left, int right);

int main(void)
{
    int n = 100000, i, j, key=0;
    int list[MAX_SIZE];
    printf("랜덤 숫자 : ");
    for (i = 0; i < n; i++) {
        list[i] = rand()%100000 + 1;
    }
    for (j = 0; j < 10; j++)
        printf("%d ",list[j]);
    printf(" . . . ");
    for (j = n-10; j < n; j++)
        printf("%d ",list[j]);
    sort(list, n);
    printf("\nSorted array:\n");
    for (j = 0; j < 10; j++)
        printf("%d ",list[j]);
    printf(" . . . ");
    for (j = n-10; j < n; j++)
        printf("%d ",list[j]);
    printf("\n");
    if(is_sorted(list, n) == 1){
        printf("is sorted\n");
    }
    else{
        printf("is not sorted\n");
    }

    while(1)
    {
        printf("검색 데이터(1 ~ 100000): ");
        scanf("%d", &key);
        if (key  == -1)
        {
            printf("검색 종료");
            break;
        }
        int cnt = binsearch(list, key, 0, n-1);
        //printf("%d\n", key);
        printf("cnt : %d\n", cnt);
    }

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


int binsearch(int list[], int searchnum, int left, int right)
{
    int cnt = 0;
    int middle;
    while (left <= right)
    {
        cnt++;
        //printf("cnt : %d\n", cnt);
        middle = (left + right)/2;
        //printf("list[%d] : %d\n", middle, list[middle]);
        switch (COMPARE(list[middle], searchnum))
        {
            case -1: left = middle + 1;
                break;
            case 0: return cnt;
            case 1: right = middle - 1;
        }
    }
    return -1;
}