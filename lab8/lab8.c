#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 트리 노드 정의
typedef struct Node {
	int data;
	struct Node* lchild;
	struct Node* rchild;
} node;

// 함수 선언
node* make_tree_by_code();
void inorder(node*);
void preorder(node*);
void postorder(node*);
node* copy(node*);
int equal(node*, node*);
node* swap(node*);
node* rand_tree(int, node*);

int main() {
	// 8.1.1 트리 구성
	printf("8.1.1. 트리 구성 (A = make_tree_by_code())\n");
	node* A = make_tree_by_code();

	// 8.1.2 트리 순회
	printf("8.1.2. 트리 순회 (A)\n");
	printf("inorder(A) : ");
	inorder(A);
	printf("\npreorder(A) : ");
	preorder(A);
	printf("\npostorder(A) : ");
	postorder(A);

	// 8.2.1 트리 복사
	printf("\n\n8.2.1. 트리 복사 (B = copy(A))\n");
	node* B = copy(A);

	// 8.2.2 복사된 트리 순회
	printf("inorder(B) : ");
	inorder(B);
	printf("\npreorder(B) : ");
	preorder(B);
	printf("\npostorder(B) : ");
	postorder(B);

	// 8.2.3 트리 동일성 검사
	printf("\n\nequal(A, B) : ");
	if (equal(A, B)) 
		printf("TRUE\n");
	else 
		printf("FALSE\n");

	// 8.2.4 트리 스왑
	printf("\nC = swap(A)\n");
	node* C = swap(A);

	// 8.2.5 스왑된 트리 순회
	printf("inorder(C) : ");
	inorder(C);
	printf("\npreorder(C) : ");
	preorder(C);
	printf("\npostorder(C) : ");
	postorder(C);

	// 8.3.1 랜덤 트리 자동 생성
	printf("\n\n8.3.1. 랜덤 트리 자동 생성 (D)\n");
	int n;
	srand((unsigned int)time(NULL));
	printf("Input n : ");
	scanf("%d", &n);

	node* root = (node*)malloc(sizeof(node));
	root->data = 1;
	root->lchild = NULL;
	root->rchild = NULL;

	node* D = rand_tree(n, root);

	// 8.3.2 랜덤 트리 순회
	printf("8.3.2. 트리 순회 (D)\n");
	printf("inorder(D) : ");
	inorder(D);
	printf("\npreorder(D) : ");
	preorder(D);
	printf("\npostorder(D) : ");
	postorder(D);

	return 0;
}

// 코드로 트리 생성
node* make_tree_by_code() {
	node* root = (node*)malloc(sizeof(node));
	node* n1 = (node*)malloc(sizeof(node));
	node* n2 = (node*)malloc(sizeof(node));
	node* n3 = (node*)malloc(sizeof(node));
	node* n4 = (node*)malloc(sizeof(node));

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

// 트리 복사
node* copy(node* original) {
	if (original) {
		node* temp = (node*)malloc(sizeof(node));
		temp->data = original->data;
		temp->lchild = copy(original->lchild);
		temp->rchild = copy(original->rchild);
		return temp;
	}
	return NULL;
}

// 트리 동일성 검사
int equal(node* first, node* second) {
	return ((!first && !second) || 
		(first && second && 
		(first->data == second->data) && 
		equal(first->lchild, second->lchild) && 
		equal(first->rchild, second->rchild)));
}

// 트리 스왑
node* swap(node* ptr) {
	if (ptr) {
		node* temp = ptr->lchild;
		ptr->lchild = ptr->rchild;
		ptr->rchild = temp;
		swap(ptr->lchild);
		swap(ptr->rchild);
	}
	return ptr;
}

// 랜덤 트리 생성
node* rand_tree(int n, node* ptr) {
	node* head = ptr;

	for (int i = 2; i <= n; i++) {
		node* temp = (node*)malloc(sizeof(node));
		temp->data = i;
		temp->lchild = NULL;
		temp->rchild = NULL;

		while (ptr != NULL) {
			int randnum = rand() % 2;
			if (randnum == 0) {
				if (ptr->lchild == NULL) {
					ptr->lchild = temp;
					break;
				}
				ptr = ptr->lchild;
			} else {
				if (ptr->rchild == NULL) {
					ptr->rchild = temp;
					break;
				}
				ptr = ptr->rchild;
			}
		}
		ptr = head;
	}

	return head;
}

// 트리 순회
void inorder(node* ptr) {
	if (ptr) {
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}

void preorder(node* ptr) {
	if (ptr) {
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void postorder(node* ptr) {
	if (ptr) {
		postorder(ptr->lchild);
		postorder(ptr->rchild);
		printf("%d ", ptr->data);
	}
}