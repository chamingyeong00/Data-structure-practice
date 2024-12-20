#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode {
    double coef;
    int expon;
    struct PolyNode *next;
} PolyNode;

typedef PolyNode *Polynomial;

PolyNode *createNode(double coef, int expon) {
    PolyNode *newNode = (PolyNode *)malloc(sizeof(PolyNode));
    if (!newNode) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    newNode->coef = coef;
    newNode->expon = expon;
    newNode->next = NULL;
    return newNode;
}

void addTerm(Polynomial *poly, double coef, int expon) {
    if (coef == 0) return;
    PolyNode *newNode = createNode(coef, expon);
    if (*poly == NULL) {
        *poly = newNode;
        newNode->next = *poly;
        return;
    }
    PolyNode *temp = *poly, *prev = NULL;
    do {
        if (temp->expon < expon) {
            if (prev == NULL) {
                PolyNode *last = *poly;
                while (last->next != *poly) last = last->next;
                last->next = newNode;
                newNode->next = *poly;
                *poly = newNode;
            } else {
                prev->next = newNode;
                newNode->next = temp;
            }
            return;
        } else if (temp->expon == expon) {
            temp->coef += coef;
            if (temp->coef == 0) {
                if (prev == NULL) {
                    PolyNode *last = *poly;
                    while (last->next != *poly) last = last->next;
                    last->next = temp->next;
                    *poly = temp->next;
                } else {
                    prev->next = temp->next;
                }
                free(temp);
            }
            free(newNode);
            return;
        }
        prev = temp;
        temp = temp->next;
    } while (temp != *poly);
    prev->next = newNode;
    newNode->next = *poly;
}

void printPolynomial(Polynomial poly) {
    if (!poly) {
        printf("0\n");
        return;
    }
    PolyNode *temp = poly;
    do {
        printf("\t%.2lf \t%d\n", temp->coef, temp->expon);
        temp = temp->next;
    } while (temp != poly);
}

void cpdiv(Polynomial A, Polynomial B, Polynomial *Q, Polynomial *R) {
    *Q = NULL;
    *R = NULL;

    while (A && A->expon >= B->expon) {
        double coef = A->coef / B->coef;
        int expon = A->expon - B->expon;

        addTerm(Q, coef, expon);

        Polynomial temp = NULL;
        Polynomial bNode = B;
        do {
            addTerm(&temp, -coef * bNode->coef, expon + bNode->expon);
            bNode = bNode->next;
        } while (bNode != B);

        Polynomial newR = NULL;
        Polynomial aNode = A;
        do {
            addTerm(&newR, aNode->coef, aNode->expon);
            aNode = aNode->next;
        } while (aNode != A);

        Polynomial tempNode = temp;
        do {
            addTerm(&newR, tempNode->coef, tempNode->expon);
            tempNode = tempNode->next;
        } while (tempNode != temp);

        A = newR;
    }

    if (A) {
        *R = A;
    }
}


int main() {
    Polynomial A = NULL;
    Polynomial B = NULL;
    Polynomial Q = NULL;
    Polynomial R = NULL;

    while (1) {
        printf("다항식 A (계수 지수) : ");
        double coef;
        int expon;
        scanf("%lf %d", &coef, &expon);
        if (coef == -1 && expon == -1) break;
        addTerm(&A, coef, expon);
    }

    while (1) {
        printf("다항식 B (계수 지수) : ");
        double coef;
        int expon;
        scanf("%lf %d", &coef, &expon);
        if (coef == -1 && expon == -1) break;
        addTerm(&B, coef, expon);
    }

    cpdiv(A, B, &Q, &R);

    printf("다항식 Q : A / B\n");
    printf("\tcoef\texpon\n");
    printPolynomial(Q);

    printf("다항식 R : A %% B\n");
    printf("\tcoef\texpon\n");
    printPolynomial(R);

    return 0;
}
