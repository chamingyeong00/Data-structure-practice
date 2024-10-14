#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 1000000
#define COMPARE(x, y) (x > y ? 1 : (x < y ? -1 : 0)) //세미콜론 필요없음

typedef struct polynomial {
    int exp;
    float coef;
} polynomial;
polynomial *D, *B, *D;

int main(void){
    int A_idx=0, B_idx=0, i =0;
    int spacing = 10;
    D = (polynomial*)malloc(sizeof(polynomial)*spacing);
    while(1){
        printf("A(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &D[A_idx].coef, &D[A_idx].exp);
        if (D[A_idx].coef == -1 && D[A_idx].exp == -1){
            break;
        }
        if (A_idx >= spacing){
            spacing += 10;
            D = (polynomial*)realloc(D, spacing*sizeof(polynomial));
        }
        A_idx++;
    }
    D[A_idx].coef =0;
    D[A_idx].exp =0;
    printf("다항식 A(x)\n");
    printf("\tcoef \texpon\n");
    while(i < A_idx){
        printf("\t%.2f\t%d\n", D[i].coef, D[i].exp);
        i++;
    }
    i=0;
    B = (polynomial*)malloc(sizeof(polynomial)*spacing);
    while(1){
        printf("B(x)의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &B[B_idx].coef, &B[B_idx].exp);
        if (B[B_idx].coef == -1 && B[B_idx].exp == -1){
            break;
        }
        if (B_idx >= spacing){
            spacing += 10;
            B = (polynomial*)realloc(B, spacing*sizeof(polynomial));
        }
        B_idx++;
    }
    B[B_idx].coef =0;
    B[B_idx].exp =0;
    printf("다항식 B(x)\n");
    printf("\tcoef \texpon\n");
    while(i <B_idx){
        printf("\t%.2f\t%d\n", B[i].coef, B[i].exp);
        i++;
    }
}