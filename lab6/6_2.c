#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
struct node {
    int data;
    struct node *next;
};

int top = -1;
struct node *A;

void print_list(struct node **A){
    struct node *ptr= (struct node*)malloc(sizeof(struct node));
    printf("Head->");
    for (ptr=*A; ptr!= NULL; ptr=ptr->next){
        printf("%d->", ptr->data);
    }
    printf("NULL\n\n");
}

void insert_front(struct node **A, int data){
    struct node *ptr = (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next=NULL;
    if (*A==NULL){
        *A = ptr;
    }
    else{
        ptr->next = *A;
        *A = ptr;
    }
}

void push(struct node **A, int data){
    insert_front(A,data);
}

int delete_front(struct node **A){
    int data=0;
    if (*A == NULL){
        printf("리스트가 비어있습니다\n");
        return data;
    }
    else{
        struct node *ptr;
        ptr = *A;
        data = ptr->data;
        *A = ptr->next;
        free(ptr);
        return data;
    }
}

int pop(struct node **A, int data){
    int n = delete_front(A);
    return n;
}


void insert_last(struct node **A, int data){
    struct node *ptr= (struct node*)malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = NULL;
    if (*A==NULL){
        *A = ptr;
    }
    else{
        struct node *temp= (struct node*)malloc(sizeof(struct node));
        for (temp=*A; temp->next!= NULL; temp=temp->next){
        }
        temp->next = ptr;
    }  
}

void add(struct node **A, int data){
    insert_last(A, data);
}

int delete(struct node **A, int data){
    int n = delete_front(A);
    return n;
}

int main(void){
    int n=0, data;
    A = (struct node *)malloc(sizeof(struct node)*MAX_SIZE);
    A = NULL;
    printf("리스트로 구현한 스택\n");
    while(n!=-1){
        printf("1. push\n");
        printf("2. pop\n");
        printf("-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &n);
        switch(n){
            case -1:
                printf("프로그램 종료\n");
                break;
            case 1:
                printf("push item : ");
                scanf("%d", &data);
                push(&A, data);
                print_list(&A);
                break;
            case 2:
                printf("pop item : ");
                scanf("%d", &data);
                pop(&A, data);
                print_list(&A);
                break;
        }
    }
    printf("리스트로 구현한 큐\n");
    n=0;
    A = NULL;
    while(n!=-1){
        printf("1. add\n");
        printf("2. delete\n");
        printf("-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &n);
        switch(n){
            case -1:
                printf("프로그램 종료\n");
                break;
            case 1:
                printf("push item : ");
                scanf("%d", &data);
                add(&A, data);
                print_list(&A);
                break;
            case 2:
                printf("pop item : ");
                scanf("%d", &data);
                delete(&A, data);
                print_list(&A);
                break;
        }
    }
}