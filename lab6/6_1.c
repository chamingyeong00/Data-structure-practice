#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
struct node {
    int data;
    struct node *next;
};

struct node *A=NULL;

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
void print_list(struct node **A){
    struct node *ptr= (struct node*)malloc(sizeof(struct node));
    printf("Head->");
    for (ptr=*A; ptr!= NULL; ptr=ptr->next){
        printf("%d->", ptr->data);
    }
    printf("NULL\n\n");
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

int search(struct node **A, int data){
    struct node *ptr= (struct node*)malloc(sizeof(struct node));
    int idx=0;
    for (ptr=*A; ptr != NULL; ptr=ptr->next, idx++){
        if(ptr->data == data)
            return idx;
    }
    printf("%d값이 리스트에 없습니다.\n",data);
    return -1;
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

int delete(struct node **A, int data){
    struct node *ptr= (struct node*)malloc(sizeof(struct node));
    for (ptr=*A; ptr!= NULL; ptr=ptr->next){
        if (ptr->data == data){
            if (ptr == *A){
                *A = ptr->next;
                free(ptr);
            }
            else{
                struct node *temp= (struct node*)malloc(sizeof(struct node));
                for (temp=*A; temp->next != ptr; temp = temp->next){
                }
                temp->next = ptr->next;
                free(ptr);
            }
            return data;
        }
    }
    printf("삭제할 데이터가 없습니다.\n");
    return -1;
}

int main(void){
    printf("리스트 기본연산\n");
    int n=0, data;
    struct node *A = (struct node *)malloc(sizeof(struct node)*MAX_SIZE);
    A = NULL;
    while(n!=-1){
        printf("0. print_list\n");
        printf("1. insert_front\n");
        printf("2. insert_last\n");
        printf("3. delete_front\n");
        printf("4. delete\n");
        printf("5. search\n");
        printf("-1. exit\n");
        printf("어떤 기능을 수행할까요? : ");
        scanf("%d", &n);
        switch (n){
            case -1:
                printf("프로그램 종료\n");
                break;
            case 0:
                print_list(&A);
                break;
            case 1:
                printf("데이터 : ");
                scanf("%d", &data);
                insert_front(&A, data);
                print_list(&A);
                break;    
            case 2:
                printf("데이터 : ");
                scanf("%d", &data);
                insert_last(&A, data);
                print_list(&A);
                break;
            case 3:
                delete_front(&A);
                print_list(&A);
                break;
            case 4:
                printf("데이터 : ");
                scanf("%d", &data);
                printf("삭제 데이터 : %d\n", delete(&A, data));
                print_list(&A);
                break;
            case 5:
                printf("데이터 : ");
                scanf("%d", &data);
                printf("노드 번호 : %d\n", search(&A, data));
                print_list(&A);
                break;
        }
    }
}