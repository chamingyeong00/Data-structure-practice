#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node{
    int key;
    double value; 
    struct node *lchild;
    struct node *rchild;
};

typedef struct node *treePointer;

treePointer avail = NULL;

treePointer modified_search(treePointer tree, int key){
    for (struct node *ptr = tree; ptr != NULL ;){
        if (ptr->key == key)
            return NULL;
        if (key < ptr->key){
            if (ptr->lchild == NULL)
                return ptr;
            else
                ptr = ptr->lchild;
        }
        else{
            if (ptr->rchild == NULL)
                return ptr;
            else
                ptr = ptr->rchild;
        }
    }
    return NULL;
}

treePointer getNode() {
	treePointer newnode;
	if (avail != NULL) {
		newnode = avail;
		avail = avail->lchild;
	}
	else {
		newnode = (treePointer)malloc(sizeof(struct node));
		if (newnode == NULL) {
			fprintf(stderr, "The memory is full\n");
			exit(1);
		}
	}
	return newnode;
}

void insert_node(treePointer *root, int num, double value){

    treePointer parent = modified_search(*root, num);

    if (parent || !(*root)){
        treePointer ptr = getNode();
        ptr->key = num;
        ptr->value = value;
        ptr->lchild = ptr->rchild = NULL;

        if (*root){
            if (num < parent->key)
                parent->lchild = ptr;
            else   
                parent->rchild = ptr;
        } else{
            *root = ptr;
        }
    }
}

/*recursion
treePointer search(treePointer tree, int k){
    if (!tree)
        return NULL;
    if (k == tree->key)
        return tree;
    if (k < tree->key)
        return search(tree->lchild, k);
    return search(tree->rchild, k);
}*/

//iteration
treePointer iterSearch(treePointer tree, int k, int *cnt){
    while (tree){
        (*cnt)++;
        if (k == tree->key)
            return tree;
        if (k < tree->key)
            tree = tree->lchild;
        else
            tree = tree->rchild;
    }
    return NULL;
}

void inorder(treePointer ptr){
    if (ptr){
        inorder(ptr->lchild);
        printf("(key : %d value : %f)\n", ptr->key, ptr->value);
        inorder(ptr->rchild);
    }
}

treePointer make_bst(int n){
    treePointer root = NULL;
    for (int i = 0; i < n; i++){
        int key = rand() % 100000 + 1;
        double val = 1.0/key;
        insert_node(&root, key, val);
    }
    return root;
}

int count_node(treePointer ptr){
    int count = 0;
    if (ptr != NULL)
        count = 1 + count_node(ptr->lchild) + count_node(ptr->rchild);
    return count;
}

int count_depth(treePointer ptr){
    int count = 0;
    if (ptr != NULL){
        int left_depth = 1 + count_depth(ptr->lchild);
        int right_depth = 1 + count_depth(ptr->rchild);
        if (left_depth > right_depth)
            return left_depth;
        else
            return right_depth;
    }
    return count;
}

int count_leaf(treePointer ptr){
    if (ptr == NULL)
        return 0;
    if (ptr->lchild == NULL && ptr->rchild == NULL)
            return 1;
    return count_leaf(ptr->lchild) + count_leaf(ptr->rchild);
}

void print_limited_node(treePointer ptr, int *cnt, int total_node){
    if (ptr){
        print_limited_node(ptr->lchild, cnt, total_node);
        if (*cnt < 2 || *cnt >= total_node - 3)
            printf("(key : %d value : %f)\n", ptr->key, ptr->value);
        else if (*cnt == 2)
            printf(". . . . .\n");
        (*cnt)++;

        print_limited_node(ptr->rchild, cnt, total_node);
    }
}

int main(void){
    srand(time(NULL));
    treePointer  tree = NULL;
    int key, i = 0;
    double val;
    printf("12개의 (key, value)쌍을 생성하여 이진 탐색 트리 생성\n");
    while (1){
        printf("%d의 key 값 입력 : ", ++i);
        scanf("%d", &key);
        if (key == -1)
            break;
        val = 1.0 / key;
        insert_node(&tree, key, val);
    }
    printf("생성 완료\n");
    inorder(tree);
    
    int search_key;
    treePointer search_node = NULL;

    printf("\n생성된 이진 검색 트리에서 key값을 활용한 검색\n");
    while(1){
        int cnt = 0;
        printf("찾고자 하는 key 값을 입력하세요 : ");
        scanf("%d", &search_key);
        if (search_key==-1)
            break;
        search_node = iterSearch(tree, search_key, &cnt);
        if (search_node == NULL)
            printf("key : %d 노드가 없습니다.\n", search_key);
        else
            printf("count : %d, key : %d의 value : %f\n", cnt, search_node->key, search_node->value);
    }

    printf("\n\nn개의 노드를 가진 이진트리 생성시간 및 노드 수, 높이(깊이), 단말 노드 수 관찰\n");
    int n;

    while(1){
        printf("n개의 노드를 가진 이진검색 트리 생성 (n) : ");
        scanf("%d", &n);
        if (n == -1)
            break;
        double start = (double)clock() / CLOCKS_PER_SEC;
        treePointer B = make_bst(n);
        double end = (double)clock() / CLOCKS_PER_SEC;
        printf("이진검색트리 B : \n");
        printf("\tkey, \tvalue)\n");
        int total_node = count_node(B);
        //inorder(B);
        int cnt = 0;
        print_limited_node(B, &cnt, total_node);
        printf("이진검색트리 B의 생성시간 : %f\n", end-start);
        printf("이진검색트리 B의 노드 수 : %d\n", total_node);
        printf("이진검색트리 B의 높이(깊이) 수 : %d\n", count_depth(B));
        printf("이진검색트리 B의 단말노드 수 : %d\n\n", count_leaf(B));
    }
}