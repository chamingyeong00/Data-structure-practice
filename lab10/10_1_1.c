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

struct queue{
    int vertex;
    struct queue *link;
};

struct edge{
    int src, dest;
};

struct queue *front = NULL;
struct queue *rear = NULL;

void addq(struct queue **front, struct queue **rear, int data){
    struct queue* newnode = (struct queue*)malloc(sizeof(struct queue));
    newnode->vertex = data;
    newnode->link = NULL;
    if (*rear != NULL)
        (*rear)->link = newnode;
    else
        *front = newnode;
    (*rear) = newnode;
}

int deleteq(){
    if (front == NULL){
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

struct node* createNode(int v){
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = v;
    newnode->next = NULL;
    return newnode;
}

void insert_front(struct node* graph[], int src, int dest){
    struct node* newnode = createNode(dest);
    newnode->next = graph[src];
    graph[src] = newnode;

    newnode = createNode(src);
    newnode->next = graph[dest];
    graph[dest] = newnode;
}

void print_graph(struct node* graph[], int node_count){
    for(int i = 0; i < node_count; i++){
        struct node* temp = graph[i];
        printf("[%d]: ", i);
        while(temp){
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("end\n");
    }
}

void find_max_node_degree(struct node* graph[], int node_count, int *max_node, int *max_degree){
    for(int i = 0; i < node_count; i++){
        struct node* temp = graph[i];
        int cnt = 0;

        while(temp){
            cnt++;
            temp = temp->next;
        }
        if (*max_degree < cnt){
            *max_degree = cnt;
            *max_node = i;
        }
    }
}
/*
void DFS(int v){
    struct node *w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = graph[v]; w; w = w->next){
        if (!visited[w->data])
            DFS(w->data);
    }
}*/

void DFS(int v, struct edge tree[], int* edge_count){
    struct node *w;
    visited[v] = TRUE;
    printf("%5d", v);
    for (w = graph[v]; w; w = w->next){
        if (!visited[w->data]){
            tree[(*edge_count)].src = v;
            tree[(*edge_count)].dest = w->data;
            (*edge_count)++;
            DFS(w->data, tree, edge_count);
        }
    }
}

/*
void BFS(int v){
    struct node *w;
    
    front = NULL;
    rear = NULL;
    printf("%5d", v);
    visited[v] = TRUE;
    addq(&front, &rear, v);
    while (front){
        v = deleteq();
        for (w = graph[v]; w; w = w->next){
            if (!visited[w->data]){
                printf("%5d", w->data);
                addq(&front, &rear, w->data);
                visited[w->data] = TRUE;
            }
        }
    }
    printf("\n");
}*/

void BFS(int v, struct edge tree[], int* edge_count){
    struct node *w;
    
    front = NULL;
    rear = NULL;
    printf("%5d", v);
    visited[v] = TRUE;
    addq(&front, &rear, v);
    while (front){
        v = deleteq();
        for (w = graph[v]; w; w = w->next){
            if (!visited[w->data]){
                printf("%5d", w->data);
                tree[(*edge_count)].src = v;
                tree[(*edge_count)].dest = w->data;
                (*edge_count)++;
                addq(&front, &rear, w->data);
                visited[w->data] = TRUE;
            }
        }
    }
    printf("\n");
}

void printf_tree(struct edge tree[], int count){
    for (int i = 0; i < count; i++){
        printf("    (%d, %d)", tree[i].src, tree[i].dest);
    }
    printf("\n");
}


int main(void){
    int node_count, vi, vj;
    printf("인접 리스트 형태의 무방향성 그래프 생성\n");
    printf("노드 개수 (n) : ");
    scanf("%d", &node_count);
    for (int i =0; i < node_count; i++){
        graph[i] = NULL;
    }

    while(1){
        printf("에지 정보 (vi, vj) : ");
        scanf("%d %d", &vi, &vj);
        if (vi == -1 && vj == -1)
            break;
        insert_front(graph, vi, vj);
    }

    printf("\n인접 리스트를 이용하여 구성한 그래프\n");
    print_graph(graph, node_count);

    int max_node = -1, max_degree = -1;
    find_max_node_degree(graph, node_count, &max_node, &max_degree);
    printf("\n\ndegree가 가장 큰 노드와 degree 값 : 노드 %d, degree %d\n\n", max_node, max_degree);

    printf("탐색 알고리즘(DFS, BFS)\n");
    printf("깊이 우선 탐색 (DFS)\n");
    printf("시작노드 %d : ", 0);
    struct edge dfs_tree0[node_count];
    int dfs_edge_count0 = 0;
    for (int i =0; i<node_count; i++)
        visited[i] = FALSE;
    DFS(0, dfs_tree0, &dfs_edge_count0);
    printf("\n시작노드 %d : ", 2);
    struct edge dfs_tree2[node_count];
    int dfs_edge_count2 = 0;
    for (int i =0; i<node_count; i++)
        visited[i] = FALSE;
    DFS(2, dfs_tree2, &dfs_edge_count2);
    printf("\n시작노드 %d : ", 4);
    struct edge dfs_tree4[node_count];
    int dfs_edge_count4 = 0;
    for (int i =0; i<node_count; i++)
        visited[i] = FALSE;
    DFS(4, dfs_tree4, &dfs_edge_count4);

    printf("\n\n너비 우선 탐색(BFS)\n");
    for (int i =0; i<node_count; i++)
        visited[i] = FALSE;
    printf("시작노드 %d : ", 1);
    struct edge bfs_tree1[node_count];
    int bfs_edge_count1 = 0;
    BFS(1, bfs_tree1, &bfs_edge_count1);
    for (int i =0; i<node_count; i++)
        visited[i] = FALSE;
    printf("시작노드 %d : ", 3);
    struct edge bfs_tree3[node_count];
    int bfs_edge_count3 = 0;
    BFS(3, bfs_tree3, &bfs_edge_count3);
    for (int i =0; i<node_count; i++)
        visited[i] = FALSE;
    printf("시작노드 %d : ", 5);
    struct edge bfs_tree5[node_count];
    int bfs_edge_count5 = 0;
    BFS(5, bfs_tree5, &bfs_edge_count5);


    printf("신장트리 알고리즘(DFS, BFS 기반)\n");
    printf("DFS 신장트리\n");
    printf("시작노드 %d : ", 0);
    printf_tree(dfs_tree0, dfs_edge_count0);
    printf("시작노드 %d : ", 2);
    printf_tree(dfs_tree2, dfs_edge_count2);
    printf("시작노드 %d : ", 4);
    printf_tree(dfs_tree4, dfs_edge_count4);
    
    printf("\nBFS 신장트리\n");
    printf("시작노드 %d : ", 1);
    printf_tree(bfs_tree1, bfs_edge_count1);
    printf("시작노드 %d : ", 3);
    printf_tree(bfs_tree3, bfs_edge_count3);
    printf("시작노드 %d : ", 5);
    printf_tree(bfs_tree5, bfs_edge_count5);
}