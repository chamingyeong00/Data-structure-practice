#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x, y) (x > y ? 1 : (x < y ? -1 : 0))
#define FALSE 0
#define TRUE 1

struct poly {
    float coef;
    int expon;
    struct poly *link;
} ;

typedef struct poly *polyPointer;
typedef struct poly polyNode;

polyPointer avail = NULL;

polyPointer getNode(void){
    polyPointer node;
    if (avail){
        node = avail;
        avail = avail->link;
    }
    else{
        node = (polyPointer) malloc(sizeof(struct poly));
        if (node == NULL){
            fprintf(stderr, "The memory is full\n");
            exit(1);
        }
    }
    return node;
}

void retNode(polyPointer node){
    node->link = avail;
    avail = node;
}

void cerease(polyPointer *ptr){
    polyPointer temp;
    while (*ptr){
        temp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = temp;
        *ptr = NULL;
    }
    *ptr = NULL;
}

void attach(float coefficient, int exponent, polyPointer *ptr){
    polyPointer temp = getNode();
    temp->coef = coefficient;
    temp->expon = exponent;
    temp->link = NULL;
    (*ptr)->link = temp;
    *ptr = temp;
}

polyPointer create_polynomial(){
    polyPointer temp = getNode();
    temp->coef = -1;
    temp->expon = -1;
    polyPointer node = temp;

    float coefficient = 0;
    int exponent = 0;
    while(1){
        printf("다항식의 항을 입력하세요. (coef expon) : ");
        scanf("%f %d", &coefficient, &exponent);
        if (exponent == -1)
            break;
        attach(coefficient, exponent, &temp);
    }
    temp->link = node;
    return node;
}

polyPointer cpadd(polyPointer a, polyPointer b){
    polyPointer startA, c, lastC;
    int done = FALSE;
    float sum;
    startA = a;
    a = a->link;
    b = b->link;
    c = getNode();
    c->expon = -1;
    lastC = c;
    do{
        switch(COMPARE(a->expon, b->expon)){
            case -1:
                attach(b->coef, b->expon, &lastC);
                b = b->link;
                break;
            case 0:
                if(startA == a)
                    done = TRUE;
                else{
                    sum = a->coef + b->coef;
                    if(sum)
                        attach(sum, a->expon, &lastC);
                    a = a->link;
                    b = b->link;
                }
                break;
            case 1:
                attach(a->coef, a->expon, &lastC);
                a = a->link;
        }
    }while (!done);
    lastC->link = c;
    return c;
}

void print_polynomial(polyPointer C){
    printf("\tcoef \texpon\n");
    C = C->link;
    while (C->expon != -1){
        printf("\t%.2f\t%d\n", C->coef, C->expon);
        C = C->link;
    }
}

polyPointer single_cpmul(polyNode Ai, polyPointer B){
    polyPointer Ci = getNode();
    polyPointer lastC = Ci;
    Ci->expon = -1;
    
    B = B->link;
    while (B->expon != -1){
        attach(Ai.coef*B->coef, Ai.expon+B->expon, &lastC);
        B = B->link;
    }
    lastC->link = Ci;
    return Ci;
}

polyPointer cpmul(polyPointer A, polyPointer B) {
    polyPointer D = getNode();  
    D->expon = -1;              
    D->link = D;            
    B = B->link;
    int i = 1;

    while (B->expon != -1) {  
        polyPointer Di = single_cpmul(*B, A);
        printf("single_mul - C%d(x)\n", i);
        print_polynomial(Di);

        polyPointer tempD = cpadd(D, Di);
        cerease(&D);
        D = tempD;

        i++;
        B = B->link;
    }

    polyPointer last = D;
    while (last->link != NULL && last->link != D) {
        last = last->link;
    }
    last->link = D;
    return D;
}

int main(void){
    polyPointer A, B, C, D;
    printf("다항식 생성\n");

    printf("다항식 A(x)\n");
    A = create_polynomial();
    printf("다항식 A(x) : \n");
    print_polynomial(A);

    printf("다항식 B(x)\n");
    B = create_polynomial();
    printf("다항식 B(x) : \n");
    print_polynomial(B);

    printf("다항식 덧셈\n");
    C = cpadd(A, B);
    printf("다항식 덧셈 결과 : C(x)\n");
    print_polynomial(C);

    printf("다항식 곱셈\n");
    D = cpmul(A, B);
    printf("다항식 곱셈 결과 : D(x)\n");
    print_polynomial(D);

    cerease(&A);
    cerease(&B);
    cerease(&C);
    cerease(&D);

    return 0;
}