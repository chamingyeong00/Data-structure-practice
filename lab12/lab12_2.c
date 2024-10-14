
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX_SIZE 1000000
void copy(int list[], int temp[], int n);
void copy2(int list[], int temp[], int n);
void sort(int list[], int n);
void insert(int e, int a[], int i);
void insertionSort(int a[], int n);
int is_sorted(int *list, int n);
int is_sorted2(int *list, int n);
void quickSort(int a[], int left, int right);

int main(void){
    int cnt = 0, num;
    double start, duration;
    int list[MAX_SIZE+1], A[MAX_SIZE+1];
    printf("오름차순 정렬된 데이터의 정렬\n");
    while(cnt < 4)
    {
        printf("element number : ");
        scanf("%d", &num);
        for (int i = 0; i<num; i++){
            list[i] = i; //(rand()/(0x7fff * 1.0)) * 100000000; //i
        }
		copy(A, list, num);
        printf("selection sort time : ");
        start = clock();
        sort(A, num);
        duration = ((double)clock() - start)/CLOCKS_PER_SEC;
        printf("%f\n", duration);

        if(is_sorted(A, num) == 1){
            printf("is sorted\n");
        }
        else{
            printf("is not sorted\n");
        }

        for (int i = 0; i<num; i++){
            A[i+1] = list[i];
        }

		copy2(A, list, num);
        printf("insertion sort time : ");
        start = clock();
        insertionSort(A, num);
        duration = ((double)clock() - start)/CLOCKS_PER_SEC;
        printf("%f\n", duration);
        if(is_sorted2(A, num) == 1){
            printf("is sorted\n");
        }
        else{
            printf("is not sorted\n");
        }

		copy(A, list, num);
        printf("quick sort time : ");
        start = clock();
        quickSort(A, 0, num-1);
        duration = ((double)clock() - start)/CLOCKS_PER_SEC;
        printf("%f\n", duration);
        if(is_sorted(A, num) == 1){
            printf("is sorted\n");
        }
        else{
            printf("is not sorted\n");
        }
        printf("\n");
        cnt++;
    }
    cnt = 0;
    printf("내림차순 정렬된 데이터의 정렬\n");
    while(cnt < 4)
    {
        printf("element number : ");
        scanf("%d", &num);
        for (int i = 0; i<num; i++){
            list[i] = num-i;//(rand()/(0x7fff * 1.0)) * 100000000;//num-i;
        }
		copy(A, list, num);
        printf("selection sort time : ");
        start = clock();
        sort(A, num);
        duration = ((double)clock() - start)/CLOCKS_PER_SEC;
        printf("%f\n", duration);

        if(is_sorted(A, num) == 1){
            printf("is sorted\n");
        }
        else{
            printf("is not sorted\n");
        }

		copy2(A, list, num);
        printf("insertion sort time : ");
        start = clock();
        insertionSort(A, num);
        duration = ((double)clock() - start)/CLOCKS_PER_SEC;
        printf("%f\n", duration);

        if(is_sorted2(A, num) == 1){
            printf("is sorted\n");
        }
        else{
            printf("is not sorted\n");
        }

		copy(A, list, num);
        printf("quick sort time : ");
        start = clock();
        quickSort(A, 0, num-1);
        duration = ((double)clock() - start)/CLOCKS_PER_SEC;
        printf("%f\n", duration);

        if(is_sorted(A, num) == 1){
            printf("is sorted\n");
        }
        else{
            printf("is not sorted\n");
        }
        printf("\n");
        cnt++;
    }
}

void copy(int list[], int temp[], int n) {
	for (int i = 0; i < n; i++)
		temp[i] = list[i];
}

void copy2(int list[], int temp[], int n) {
    temp[0] = 0;
    for (int i = 0; i < n; i++)
		temp[i+1] = list[i];
}

void sort(int list[], int n){ //index, value
    int temp, min_index;
    for (int i=0; i<n-1; i++){ //n-1까지
        min_index = i; //min에 i index값을 넣어야 함.
        for (int j=i+1; j<n; j++){
            if (list[min_index] > list[j])
                min_index = j; //min에 j index값을 넣어야 함.
        }    
        if (list[i] != list[min_index])
        {
            SWAP(list[i], list[min_index], temp); //swap list[min_index]
        }
    }
}

void insert(int e, int a[], int i){
    a[0]=e;
    while(e < a[i]){
        a[i+1]=a[i];
        i--;
    }
    a[i+1]=e;
}

void insertionSort(int a[], int n){
    for (int i=2; i<=n; i++){
        int key = a[i];
        insert(key, a, i-1); //i-1 i전과 비교
    }
}


void quickSort(int a[], int left, int right){
    if (left < right){
        int pivot = a[left];
        int temp;
        int i=left;
        int j=right+1;
        do{
            do{
                i++;
            }while(a[i]< pivot);
            do{
                j--;
            }while(a[j]> pivot);
            if (i<j)
                SWAP(a[i], a[j], temp);
        }while(i<j);
        SWAP(a[left], a[j], temp);
        quickSort(a, left, j-1);
        quickSort(a, j+1, right);
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

int is_sorted2(int *list, int n)
{
    for(int i=1; i<n; i++)
    {
        if(list[i] > list[i+1])
        {
            return 0;
        }
    }
    return 1;
}
