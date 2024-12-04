#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICES 100

short int visited[MAX_VERTICES];
struct node *graph[MAX_VERTICES];

struct node {
    int data;
    struct node *next;
};

struct queue {
    int vertex;
    struct queue *link;
};

struct edge {
    int src, dest;
};

struct queue *front = NULL;
struct queue *rear = NULL;

void addq(struct queue **front, struct queue **rear, int data) {
    struct queue* newnode = (struct queue*)malloc(sizeof(struct queue));
    newnode->vertex = data;
    newnode->link = NULL;
    if (*rear != NULL)
        (*rear)->link = newnode;
    else
        *front = newnode;
    (*rear) = newnode;
}

int deleteq() {
    if (front == NULL) {
        printf("queue_empty\n");
        exit(1);
    }
    struct queue* temp = front;
    int data = temp->vertex;
    front = front->link;
    free(temp);
    if (front == NULL)
        rear = NULL;
    return data;
}

struct node* createNode(int v) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = v;
    newnode->next = NULL;
    return newnode;
}

void insert_front(struct node* graph[], int src, int dest) {
    struct node* newnode = createNode(dest);
    newnode->next = graph[src];
    graph[src] = newnode;

    newnode = createNode(src);
    newnode->next = graph[dest];
    graph[dest] = newnode;
}

void DFS(int v) {
    struct node *w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = graph[v]; w; w = w->next) {
        if (!visited[w->data]) {
            DFS(w->data);
        }
    }
}

void DFS_tree(int v, struct edge tree[], int* edge_count) {
    struct node *w;
    visited[v] = TRUE;
    for (w = graph[v]; w; w = w->next) {
        if (!visited[w->data]) {
            tree[(*edge_count)].src = v;
            tree[(*edge_count)].dest = w->data;
            (*edge_count)++;
            DFS_tree(w->data, tree, edge_count);
        }
    }
}

void BFS(int v) {
    struct node *w;
    front = NULL;
    rear = NULL;
    printf("%5d", v);
    visited[v] = TRUE;
    addq(&front, &rear, v);

    while (front) {
        v = deleteq();
        for (w = graph[v]; w; w = w->next) {
            if (!visited[w->data]) {
                printf("%5d", w->data);
                addq(&front, &rear, w->data);
                visited[w->data] = TRUE;
            }
        }
    }
    printf("\n");
}

void BFS_tree(int v, struct edge tree[], int* edge_count) {
    struct node *w;
    front = NULL;
    rear = NULL;
    visited[v] = TRUE;
    addq(&front, &rear, v);

    while (front) {
        v = deleteq();
        for (w = graph[v]; w; w = w->next) {
            if (!visited[w->data]) {
                tree[(*edge_count)].src = v;
                tree[(*edge_count)].dest = w->data;
                (*edge_count)++;
                addq(&front, &rear, w->data);
                visited[w->data] = TRUE;
            }
        }
    }
}

void printf_tree(struct edge tree[], int count) {
    for (int i = 0; i < count; i++) {
        printf("  (%d, %d)", tree[i].src, tree[i].dest);
    }
    printf("\n");
}

void find_degree(struct node* graph[], int node_count) {
    int max_degree = 0, max_node = -1;

    for (int i = 0; i < node_count; i++) {
        int degree = 0;
        struct node* temp = graph[i];
        while (temp) {
            degree++;
            temp = temp->next;
        }
        if (degree > max_degree) {
            max_degree = degree;
            max_node = i;
        }
    }

    printf("\n  degree가 가장 큰 노드와 degree 값 : 노드 %d, degree %d\n", max_node, max_degree);
    printf("  노드 %d와 연결된 노드들 : ", max_node);

    struct node* temp = graph[max_node];
    while (temp) {
        printf(" %d ->", temp->data);
        temp = temp->next;
    }
    printf(" end\n");
}

int main(void) {
    int node_count, vi, vj;

    printf("10.1. 인접 리스트 형태의 무방향성 그래프 생성\n");
    printf("  노드 개수(n): ");
    scanf("%d", &node_count);
    if (node_count == -1) {
        printf("종료합니다.\n");
        return 0;
    }

    for (int i = 0; i < node_count; i++) {
        graph[i] = NULL;
    }

    while (1) {
        printf("  에지 정보(vi vj): ");
        scanf("%d %d", &vi, &vj);
        if (vi == -1 && vj == -1)
            break;
        insert_front(graph, vi, vj);
    }

    printf("\n  인접 리스트를 이용하여 구성한 그래프\n");
    for (int i = 0; i < node_count; i++) {
        printf("   [%d]: ", i);
        struct node* temp = graph[i];
        while (temp) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("end\n");
    }

    find_degree(graph, node_count);

    printf("\n10.2. 탐색 알고리즘(DFS, BFS)\n");
    printf("  깊이 우선 탐색 (DFS)\n");
    for (int i = 0; i < node_count; i++) {
        if (i % 2 == 0) {
            printf("  시작노드 %d: ", i);
            struct edge dfs_tree[node_count - 1];
            int dfs_edge_count = 0;
            for (int j = 0; j < node_count; j++) visited[j] = FALSE;
            DFS(i);
            printf("\n");
        }
    }

    printf("\n  너비 우선 탐색 (BFS)\n");
    for (int i = 0; i < node_count; i++) {
        if (i % 2 != 0) {
            printf("  시작노드 %d: ", i);
            struct edge bfs_tree[node_count - 1];
            int bfs_edge_count = 0;
            for (int j = 0; j < node_count; j++) visited[j] = FALSE;
            BFS(i);
        }
    }

    printf("\n10.3. 신장트리 알고리즘(DFS, BFS 기반)\n");
    printf("  DFS 신장트리\n");
    for (int i = 0; i < node_count; i++) {
        if (i % 2 == 0) {
            printf("  시작노드 %d: ", i);
            struct edge dfs_tree[node_count - 1];
            int dfs_edge_count = 0;
            for (int j = 0; j < node_count; j++) visited[j] = FALSE;
            DFS_tree(i, dfs_tree, &dfs_edge_count);
            printf_tree(dfs_tree, dfs_edge_count);
        }
    }

    printf("\n  BFS 신장트리\n");
    for (int i = 0; i < node_count; i++) {
        if (i % 2 != 0) {
            printf("  시작노드 %d: ", i);
            struct edge bfs_tree[node_count - 1];
            int bfs_edge_count = 0;
            for (int j = 0; j < node_count; j++) visited[j] = FALSE;
            BFS_tree(i, bfs_tree, &bfs_edge_count);
            printf_tree(bfs_tree, bfs_edge_count);
        }
    }

    return 0;
}