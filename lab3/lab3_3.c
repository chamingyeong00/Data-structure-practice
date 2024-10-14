#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_TERMS 1000000
#define COMPARE(x, y) (x > y ? 1 : (x < y ? -1 : 0)) //세미콜론 필요없음

typedef struct polynomial {
    int exp;
    float coef;
} polynomial;

polynomial* single_pmul(polynomial Ai, polynomial* B);
polynomial* padd(polynomial* A, polynomial* B);
polynomial* pmul(polynomial* A, polynomial* B);

void attach(float coefficient, int exponent);

polynomial *B, *D, *S;
int A_idx=0, B_idx=0, D_idx=0, temp=0;

void SWAP(polynomial *a, polynomial *b, polynomial *temp){
    *temp = *a;
    *a = *b;
    *b = *temp;
}

void quickSort(polynomial *a, int left, int right){
    if (left < right){
        int pivot = a[left].exp;
        polynomial temp;
        int i=left;
        int j=right+1;
        do{
            do{
                i++;
            }while(a[i].exp > pivot);
            do{
                j--;
            }while(a[j].exp < pivot);
            if (i<j)
                SWAP(&a[i], &a[j], &temp);
        }while(i<j);
        SWAP(&a[left], &a[j], &temp);
        quickSort(a, left, j-1);
        quickSort(a, j+1, right);
    }
}


int main(void){
    int i =0;
    int A_spacing = 10, B_spacing = 10;
    D = (polynomial*)malloc(sizeof(polynomial)*A_spacing);
    while(1){
        printf("A(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &D[A_idx].coef, &D[A_idx].exp);
        if (D[A_idx].exp == -1){ //D[A_idx].coef == -1 && 
            break;
        }
        A_idx++;
        if (A_idx >= A_spacing){
            A_spacing += 10;
            D = (polynomial*)realloc(D, A_spacing*sizeof(polynomial));
        }
    }
    //D[A_idx].coef = 0;
    //D[A_idx].exp =0;
    quickSort(D, 0, A_idx-1);
    printf("다항식 A(x)\n");
    printf("\tcoef \texpon\n");
    while(i < A_idx){
        printf("\t%.2f\t%d\n", D[i].coef, D[i].exp);
        i++;
    }
    i=0;
    B = (polynomial*)malloc(sizeof(polynomial)*B_spacing);
    while(1){
        printf("B(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &B[B_idx].coef, &B[B_idx].exp);
        if (B[B_idx].exp == -1){ //B[B_idx].coef == -1 && 
            break;
        }
        B_idx++;
        if (B_idx >= B_spacing){
            B_spacing += 10;
            B = (polynomial*)realloc(B, B_spacing*sizeof(polynomial));
        }
    }
    quickSort(B, 0, B_idx-1);
    printf("다항식 B(x)\n");
    printf("\tcoef \texpon\n");
    while(i <B_idx){
        printf("\t%.2f\t%d\n", B[i].coef, B[i].exp);
        i++;
    }
    S = pmul(D, B);
    i = 0;
    printf("다항식 곱셈 결과 : D(x)\n");
    printf("\tcoef \texpon\n");
    while(i < D_idx){
        printf("\t%.2f\t%d\n", S[i].coef, S[i].exp);
        i++;
    }
}

//polynomial expon기준으로 정렬 함수
polynomial* single_pmul(polynomial Ai, polynomial* B){
    int i;
    polynomial* Ci = (polynomial *)malloc(B_idx*sizeof(polynomial));
    for (i=0; i<B_idx; i++){
        if (i == MAX_TERMS)
            return 0;
        Ci[i].coef = Ai.coef * B[i].coef;
        Ci[i].exp = Ai.exp + B[i].exp;
        printf("\t%.2f\t%d\n",Ci[i].coef, Ci[i].exp);
    }
    //Ci[i].coef = -1;
    //Ci[i].exp = -1;
    return Ci;
}


polynomial* pmul(polynomial* A, polynomial* B){
    //printf("pow(A_idx ^ B_idx) : %f\n", pow(A_idx, B_idx));
    D = (polynomial*)malloc(sizeof(polynomial)*pow(A_idx, B_idx));
    S = (polynomial*)malloc(sizeof(polynomial)*pow(A_idx, B_idx));
    for (int i=0; i<A_idx; i++){
        /*printf("D list test D_idx : %d \n", D_idx);
        printf("\tcoef \texpon\n");
        for (int i=0; i<D_idx; i++){
            printf("\tD[%d] %.2f\t%d\n", i, D[i].coef, D[i].exp);
        }*/
        printf("single_mul - C%d(x)\n", i+1);
        printf("\tcoef \texpon\n");
        polynomial *Ci = single_pmul(A[i], B);
        S = padd(D, Ci);
        D_idx = temp;
        memcpy(D, S, D_idx * sizeof(polynomial));
    }
    return S;
}


polynomial* padd(polynomial* D, polynomial* B){
    int D_currentidx = 0, B_currentidx = 0;
    float coefficient;
    temp = 0;
    //printf("D_idx : %d B_idx : %d\n", D_idx, B_idx);
    //printf("\n\npadd : D_currentidx : %d D_idx : %d \t B_currentidx : %d B_idx : %d\n\n\n", D_currentidx, D_idx, B_currentidx, B_idx);
    while (D_currentidx < D_idx && B_currentidx < B_idx){
        switch(COMPARE(D[D_currentidx].exp, B[B_currentidx].exp)){
            case -1:
                //printf("-1 : \t");
                //printf("D_currentidx : %d B_currentidx : %d D.exp : %d B_.exp : %d \n", D_currentidx, B_currentidx, D[D_currentidx].exp, B[B_currentidx].exp);
                attach(B[B_currentidx].coef, B[B_currentidx].exp);
                B_currentidx++;
                break;
            case 0:
                coefficient = D[D_currentidx].coef + B[B_currentidx].coef;
                //printf("0 : \t");
                //printf("D_currentidx : %d B_currentidx : %d D.exp : %d B_.exp : %d \n", D_currentidx, B_currentidx, D[D_currentidx].exp, B[B_currentidx].exp);
                if (coefficient != 0)
                    attach(coefficient, B[B_currentidx].exp);
                D_currentidx++;
                B_currentidx++;
                //printf("D_currentidx %d B_currentidx %d\n",D_currentidx, B_currentidx);
                break;
            case 1:
                //printf("1 : \t");
                //printf("D_currentidx : %d B_currentidx : %d D.exp : %d B_.exp : %d \n", D_currentidx, B_currentidx, D[D_currentidx].exp, B[B_currentidx].exp);
                attach(D[D_currentidx].coef, D[D_currentidx].exp);
                D_currentidx++;
                break;
        }
    }
    for(; D_currentidx < D_idx; D_currentidx++){
        //printf("for padd D_idx : %d D[%d].coef : %f D[%d].exp : %d\n", D_idx, D_currentidx, D[D_currentidx].coef, D_currentidx, D[D_currentidx].exp);
        attach(D[D_currentidx].coef, D[D_currentidx].exp);
    }
    for(; B_currentidx < B_idx; B_currentidx++){
        //printf("for padd B_idx : %d B[%d].coef : %f B[%d].exp : %d\n", B_idx, B_currentidx, B[B_currentidx].coef, B_currentidx, B[B_currentidx].exp);
        attach(B[B_currentidx].coef, B[B_currentidx].exp);
    }
    return S;
}

void attach(float coefficient, int exponent){
    //printf("attach :D_idx : %d \n", D_idx);
    if (D_idx >= MAX_TERMS){
        fprintf(stderr, "max polynomial\n");
        exit(1);
    }
    S[temp].coef = coefficient;
    S[temp].exp = exponent;
    //printf("attach S[%d] coef: %f exp: %d\n", temp, S[temp].coef, S[temp].exp );
    temp++;
}