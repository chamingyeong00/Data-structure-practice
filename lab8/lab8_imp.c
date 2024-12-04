#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
    int data;
    struct node *lchild;
    struct node *rchild;
};

struct node *make_tree_by_code(){
    struct node *root;
    struct node *n1;
    struct node *n2;
    struct node *n3;
    struct node *n4;

    root = (struct node *)malloc(sizeof(struct node));
    n1 = (struct node *)malloc(sizeof(struct node));
    n2 = (struct node *)malloc(sizeof(struct node));
    n3 = (struct node *)malloc(sizeof(struct node));
    n4 = (struct node *)malloc(sizeof(struct node));

    root->data = 5;
    root->lchild = n1;
    root->rchild = n2;

    n1->data = 3;
    n1->lchild = n3;
    n1->rchild = n4;

    n2->data = 8;
    n2->lchild = NULL;
    n2->rchild = NULL;

    n3->data = 1;
    n3->lchild = NULL;
    n3->rchild = NULL;

    n4->data = 4;
    n4->lchild = NULL;
    n4->rchild = NULL;

    return root;

}

struct node *copy(struct node *original){
    struct node *temp;
    if (original){
        temp = (struct node *)malloc(sizeof(struct node));
        temp->lchild = copy(original->lchild);
        temp->rchild = copy(original->rchild);
        temp->data = original->data;
        return temp;
    }
    return NULL;
}

int equal(struct node *first, struct node *second){
    return ((!first && !second) || (first && second && 
    (first->data == second->data) && 
    equal(first->lchild, second->lchild) && 
    equal(first->rchild, second->rchild)));
}

struct node *swap(struct node *original){
    struct node *temp;
    if (original){
        temp = (struct node *)malloc(sizeof(struct node));
        temp->lchild = swap(original->rchild);
        temp->rchild = swap(original->lchild);
        temp->data = original->data;
        return temp;
    }
    return NULL;
}

void inorder(struct node *root){
    if(root){
        inorder(root->lchild);
        printf("%d ", root->data);
        inorder(root->rchild);
    }
}

void preorder(struct node *root){
    if(root){
        printf("%d ", root->data);
        preorder(root->lchild);
        preorder(root->rchild);
    }
}

void postorder(struct node *root){
    if(root){
        postorder(root->lchild);
        postorder(root->rchild);
        printf("%d ", root->data);
    }
}

struct node *create_node(int data){
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->data = data;
    node->rchild = NULL;
    node->lchild = NULL;
    return node;
}

struct node *insert_random(int num){
    struct node *root = create_node(1);
    for (int i = 2; i<=num; i++){
        struct node *current = root;
        struct node *temp = create_node(i);

        while(1){
            int random = rand()%2;
            if (random == 0){
                if (current->lchild){
                    current = current->lchild;
                } else{
                    current->lchild = temp;
                    break;
                }
            }else{
                if (current->rchild){
                    current = current->rchild;
                } else{
                    current->rchild = temp;
                    break;
                }
            }
        }
    }
    return root;
    
}

int main(void){
    struct node *A = make_tree_by_code();

    printf("트리 구성 (A = make_tree_by_code())\n");
    printf("트리 순회 (A)\n");
    printf("inorder(A) : ");
    inorder(A);
    printf("\npreorder(A) : ");
    preorder(A);
    printf("\npostorder(A) : ");
    postorder(A);
    printf("\n\n");

    struct node *B = copy(A);

    printf("트리 복사 (B = copy(A))\n");
    printf("트리 순회 (B)\n");
    printf("inorder(B) : ");
    inorder(B);
    printf("\npreorder(B) : ");
    preorder(B);
    printf("\npostorder(B) : ");
    postorder(B);
    printf("\n\n");

    printf("트리 동질성 검사 (equal(A, B))\n");
    printf("equal(A, B) : ");
    if(equal(A, B)){
        printf("TRUE\n\n");
    }
    else{
        printf("FALSE\n\n");
    }

    
    struct node *C = swap(A);

    printf("트리 swap (C = swap(A))\n");
    printf("트리 순회 (C)\n");
    printf("inorder(C) : ");
    inorder(C);
    printf("\npreorder(C) : ");
    preorder(C);
    printf("\npostorder(C) : ");
    postorder(C);
    printf("\n\n");
    
    int num;
    srand(time(NULL));
    printf("랜덤 트리 자동 생성 (D)\n");
    printf("Input n : ");
    scanf("%d", &num);
    struct node *D = insert_random(num);
    printf("트리 순회 (D)\n");
    printf("inorder(D) : ");
    inorder(D);
    printf("\npreorder(D) : ");
    preorder(D);
    printf("\npostorder(D) : ");
    postorder(D);
    printf("\n\n");
}