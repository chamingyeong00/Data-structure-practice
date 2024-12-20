#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef Node* nodePointer;

void DFS(nodePointer* G, int v, int* visited);
void BFS(nodePointer* G, int v, int* visited);
void spanning_DFS(nodePointer* G, int v, int* visited);
void spanning_BFS(nodePointer* G, int v, int* visited);

void addEdge(nodePointer* G, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = G[u];
    G[u] = newNode;
}


void DFS(nodePointer* G, int v, int* visited) {
    visited[v] = 1;
    printf("%d ", v);

    Node* temp = G[v];
    while (temp) {
        if (!visited[temp->vertex]) {
            DFS(G, temp->vertex, visited);
        }
        temp = temp->next;
    }
}

void BFS(nodePointer* G, int v, int* visited) {
    int queue[MAX_VERTICES], front = 0, rear = 0;
    visited[v] = 1;
    queue[rear++] = v;

    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        Node* temp = G[current];
        while (temp) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                queue[rear++] = temp->vertex;
            }
            temp = temp->next;
        }
    }
}

void spanning_DFS(nodePointer* G, int v, int* visited) {
    visited[v] = 1;
    Node* temp = G[v];
    while (temp) {
        if (!visited[temp->vertex]) {
            printf("(%d, %d) ", v, temp->vertex);
            spanning_DFS(G, temp->vertex, visited);
        }
        temp = temp->next;
    }
}

void spanning_BFS(nodePointer* G, int v, int* visited) {
    int queue[MAX_VERTICES], front = 0, rear = 0;
    visited[v] = 1;
    queue[rear++] = v;

    while (front < rear) {
        int current = queue[front++];
        Node* temp = G[current];
        while (temp) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                queue[rear++] = temp->vertex;
                printf("(%d, %d) ", current, temp->vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int vertices, start, u, v;

    printf("Input Vertex # : ");
    scanf("%d", &vertices);

    nodePointer* G = (nodePointer*)malloc(vertices * sizeof(nodePointer));
    for (int i = 0; i < vertices; i++) {
        G[i] = NULL;
    }

    while (1) {
        printf("Input Edge (u v): ");
        scanf("%d %d", &u, &v);
        if (u < 0 && v < 0) break;
        addEdge(G, u, v);
        addEdge(G, v, u);
    }

    printf("Start Vertex # : ");
    scanf("%d", &start);

    int* visited = (int*)calloc(vertices, sizeof(int));
    printf("DFS : ");
    DFS(G, start, visited);
    printf("\n");

    for (int i = 0; i < vertices; i++) visited[i] = 0;
    printf("BFS : ");
    BFS(G, start, visited);
    printf("\n");

    for (int i = 0; i < vertices; i++) visited[i] = 0;
    printf("Spanning Tree by DFS: ");
    spanning_DFS(G, start, visited);
    printf("\n");

    for (int i = 0; i < vertices; i++) visited[i] = 0;
    printf("Spanning Tree by BFS: ");
    spanning_BFS(G, start, visited);
    printf("\n");

    free(visited);
    for (int i = 0; i < vertices; i++) {
        Node* temp = G[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(G);

    return 0;
}
