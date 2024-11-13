#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_TERMS 1000000
#define COMPARE(x, y) (x > y ? 1 : (x < y ? -1 : 0)) //세미콜론 필요없음

typedef struct polynomial {
    int exp;
    float coef;
} polynomial;

double peval(polynomial *D, double b);
polynomial* psub(polynomial* A, polynomial* B);
void attach(float coefficient, int exponent);
polynomial *D, *B;
int A_idx=0, B_idx=0, D_currentidx;

int main(void){
    int i =0;
    int A_spacing = 10, B_spacing = 10;
    D = (polynomial*)malloc(sizeof(polynomial)*A_spacing);
    while(1){
        printf("다항식 A (계수 지수) : ");
        scanf("%f %d", &D[A_idx].coef, &D[A_idx].exp);
        if (D[A_idx].coef == -1 && D[A_idx].exp == -1){
            break;
        }
        A_idx++;
        if (A_idx >= A_spacing){
            A_spacing += 10;
            D = (polynomial*)realloc(D, A_spacing*sizeof(polynomial));
        }
    }
    i=0;
    B = (polynomial*)malloc(sizeof(polynomial)*B_spacing);
    while(1){
        printf("다항식 B (계수 지수) : ");
        scanf("%f %d", &B[B_idx].coef, &B[B_idx].exp);
        if (B[B_idx].coef == -1 && B[B_idx].exp == -1){
            break;
        }
        B_idx++;
        if (B_idx >= B_spacing){
            B_spacing += 10;
            B = (polynomial*)realloc(B, B_spacing*sizeof(polynomial));
        }
    }
    D = psub(D, B);
    i = 0;
    printf("다항식 D(x) : A - B\n");
    printf("\tcoef \texpon\n");
    while(i < D_currentidx -1){
        printf("\t%.2f\t%d\n", D[i].coef, D[i].exp);
        i++;
    }
    double b, y;
    printf("다항식 D의 미지수(x) 값은 : ");
    scanf("%lf", &b);
    y = peval(D, b);
    printf("다항식 D의 계산 결과 : %.0f", y);
}

double peval(polynomial *D, double b){
    double eval=0;
      for(int i=0; i< D_currentidx - 1; i++)
     {
        eval += D[i].coef * pow(b,D[i].exp);
        //printf("eval : %f D_currentidx : %f\n", eval, i);
    }
    return eval;
}

polynomial* psub(polynomial* A, polynomial* B){
    D = (polynomial*)malloc(sizeof(polynomial)*(A_idx + B_idx));
    int A_currentidx = 0, B_currentidx = 0;
    float coefficient;
    //printf("A_idx : %d B_idx : %d\n", A_idx, B_idx);
    while (A_currentidx < A_idx && B_currentidx < B_idx){ //A[i].expon >= 0 && B[i].expon >= 0
        switch(COMPARE(A[A_currentidx].exp, B[B_currentidx].exp)){
            case -1:
                if (B[B_currentidx].coef != 0)
                    attach(-B[B_currentidx].coef, B[B_currentidx].exp);
                B_currentidx++;
                break;
            case 0:
                coefficient = A[A_currentidx].coef - B[B_currentidx].coef;
                if (coefficient != 0)
                    attach(coefficient, B[B_currentidx].exp);
                A_currentidx++;
                B_currentidx++;
                break;
            case 1:
                if (A[A_currentidx].coef != 0)
                    attach(A[A_currentidx].coef, A[A_currentidx].exp);
                A_currentidx++;
        }
    }
    for(; A_currentidx < A_idx; A_currentidx++)
        attach(A[A_currentidx].coef, A[A_currentidx].exp);
    for(; B_currentidx < B_idx; B_currentidx++)
        attach(B[B_currentidx].coef, B[B_currentidx].exp);
    attach(-1, -1); //안넣으면 오류 날수 있음
    return D;
}


void attach(float coefficient, int exponent){
    if (D_currentidx >= MAX_TERMS){
        fprintf(stderr, "max polynomial\n");
        exit(1);
    }
    D[D_currentidx].coef = coefficient;
    D[D_currentidx].exp = exponent;
    //printf("D[%d] coef: %f exp: %d\n", D_currentidx,D[D_currentidx].coef, D[D_currentidx].exp );
    D_currentidx++;
}