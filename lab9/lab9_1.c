#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    double value;
    struct Node* lchild;
    struct Node* rchild;
} node;

typedef node* treePointer;

// 함수 선언 (프로토타입)
treePointer search(treePointer root, int key);
treePointer delete_node(treePointer root, int key);
treePointer getNode();
void inorder(treePointer ptr);
treePointer modified_search(treePointer root, int key);
void insert_node(treePointer* pnode, int key);
void postorder_free(treePointer ptr);

// 노드 생성 함수
treePointer getNode() {
    treePointer newnode = (treePointer)malloc(sizeof(node));
    if (newnode == NULL) {
        fprintf(stderr, "The memory is full\n");
        exit(1);
    }
    return newnode;
}

// 중위 순회
void inorder(treePointer ptr) {
    if (ptr) {
        inorder(ptr->lchild);
        printf("(%10d, %10.6f)\n", ptr->key, ptr->value);
        inorder(ptr->rchild);
    }
}

// 삽입 위치 찾는 함수
treePointer modified_search(treePointer root, int key) {
    treePointer ptr = root;
    while (ptr != NULL) {
        if (ptr->key == key) return NULL; // 이미 key가 존재하면 NULL 반환
        if (key > ptr->key) {
            if (ptr->rchild == NULL) return ptr;
            ptr = ptr->rchild;
        } else {
            if (ptr->lchild == NULL) return ptr;
            ptr = ptr->lchild;
        }
    }
    return NULL;
}

// 노드 삽입 함수
void insert_node(treePointer* pnode, int key) {
    treePointer ptr = getNode();
    ptr->key = key;
    ptr->value = 1.0 / key; // value를 key를 기반으로 자동 계산
    ptr->lchild = NULL;
    ptr->rchild = NULL;

    if (key >= (*pnode)->key)
        (*pnode)->rchild = ptr;
    else
        (*pnode)->lchild = ptr;
}

// 키 값으로 노드 검색
treePointer search(treePointer root, int key) {
    if (!root) return NULL;
    if (key == root->key) return root;
    if (key > root->key) return search(root->rchild, key);
    return search(root->lchild, key);
}

// 삭제 함수
treePointer delete_node(treePointer root, int key) {
    if (root == NULL) {
        printf("Key %d is not found in the tree.\n", key);
        return root;
    }

    // 탐색
    if (key < root->key) {
        root->lchild = delete_node(root->lchild, key);
    } else if (key > root->key) {
        root->rchild = delete_node(root->rchild, key);
    } else {
        // 삭제할 노드를 찾음
        if (root->lchild == NULL) {
            // 자식이 없는 경우 또는 오른쪽 자식만 있는 경우
            treePointer temp = root->rchild;
            free(root);
            return temp;
        } else if (root->rchild == NULL) {
            // 왼쪽 자식만 있는 경우
            treePointer temp = root->lchild;
            free(root);
            return temp;
        }

        // 두 자식을 가진 경우: 오른쪽 서브트리의 최소값 찾기
        treePointer temp = root->rchild;
        while (temp->lchild != NULL) {
            temp = temp->lchild;
        }
        // 최소값을 현재 노드로 복사
        root->key = temp->key;
        root->value = temp->value;

        // 최소값 노드 삭제
        root->rchild = delete_node(root->rchild, temp->key);
    }
    return root;
}

// 트리 순회 및 메모리 해제
void postorder_free(treePointer ptr) {
    if (ptr) {
        postorder_free(ptr->lchild);
        postorder_free(ptr->rchild);
        free(ptr);
    }
}

int main() {
    treePointer root = NULL;
    int key;

    printf("9.1. (key, value) 쌍을 입력하여 이진 탐색 트리를 작성\n");
    printf("key 값을 입력하세요 (-1 to exit) : ");
    scanf("%d", &key);

    if (key != -1) {
        root = getNode();
        root->key = key;
        root->value = 1.0 / key; // value를 자동 계산
        root->lchild = NULL;
        root->rchild = NULL;

        while (1) {
            printf("key 값을 입력하세요 (-1 to exit) : ");
            scanf("%d", &key);
            if (key == -1) break;

            treePointer modinode = modified_search(root, key);
            if (modinode != NULL) insert_node(&modinode, key);
        }
        printf("입력 완료\n");
        printf("inorder print\n");
        inorder(root);
    }

    printf("\n9.2. 입력된 값을 검색하여 키 값을 기반으로 탐색\n");
    while (1) {
        printf("찾고자 하는 key 값을 입력하세요 (-1 to exit) : ");
        scanf("%d", &key);
        if (key == -1) break;

        treePointer found = search(root, key);
        if (found)
            printf("key : %d의 value : %.6f\n", found->key, found->value);
        else
            printf("key : %d 값이 존재하지 않습니다.\n", key);
    }

    printf("\n9.4. 이진 탐색 트리에서 노드 삭제\n");
    while (1) {
        printf("삭제할 key 값을 입력하세요 (-1 to exit) : ");
        scanf("%d", &key);
        if (key == -1) break;

        root = delete_node(root, key);

        printf("삭제 후 트리 (inorder traversal):\n");
        inorder(root);
    }

    if (root) postorder_free(root);
    return 0;
}