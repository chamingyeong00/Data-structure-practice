#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_LENGTH 100

typedef struct Node {
    int key;
    char data[MAX_DATA_LENGTH];
    struct Node *left, *right;
} Node;

Node* createNode(int key, const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    strcpy(newNode->data, data);
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int key, const char* data) {
    if (root == NULL) 
        return createNode(key, data);

    if (key < root->key)
        root->left = insert(root->left, key, data);
    else if (key > root->key)
        root->right = insert(root->right, key, data);
    else {
        printf("오류: 키 %d가 이미 존재\n", key);
    }
    return root;
}

Node* search(Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == NULL) {
        printf("오류: 키 %d를 찾을 수 없음\n", key);
        return root;
    }

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        Node* temp = findMin(root->right);
        root->key = temp->key;
        strcpy(root->data, temp->data);
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("키: %d, 데이터: %s\n", root->key, root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    Node* root = NULL;
    int choice, key;
    char data[MAX_DATA_LENGTH];

    while (1) {
        printf("\n1. 삽입\n2. 검색\n3. 삭제\n4. 중위 순회 출력\n5. 종료\n");
        printf("원하는 작업을 선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("키와 데이터를 입력: ");
                scanf("%d", &key);
                getchar();
                fgets(data, MAX_DATA_LENGTH, stdin);
                data[strcspn(data, "\n")] = '\0';
                root = insert(root, key, data);
                break;

            case 2:
                printf("검색할 키를 입력: ");
                scanf("%d", &key);
                Node* result = search(root, key);
                if (result != NULL)
                    printf("데이터: %s\n", result->data);
                else
                    printf("오류: 키 %d를 찾을 수 없음.\n", key);
                break;

            case 3:
                printf("삭제할 키를 입력: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                break;

            case 4:
                printf("중위 순회 출력:\n");
                inorderTraversal(root);
                break;

            case 5:
                printf("프로그램을 종료.\n");
                exit(0);

            default:
                printf("잘못된 선택.\n");
        }
    }
    return 0;
}
