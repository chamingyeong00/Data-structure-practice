#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INT_MAX 99999

void print_mtrx(int** arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("\t[ %d ]", i);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("[ %d ]", i);
        for (int j = 0; j < n; j++) {
            printf("%6d\t", arr[i][j]);
        }
        printf("\n");
    }
}

int choose(int distance[], int n, bool found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && found[i] == false) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void shortestpath(int v, int** cost, int n) {
    int i, u, w;
    int* distance = (int*)malloc(n * sizeof(int));
    bool* found = (bool*)malloc(n * sizeof(bool));

    for (i = 0; i < n; i++) {
        found[i] = false;
        distance[i] = cost[v][i];
    }

    found[v] = true;
    distance[v] = 0;
    for (i = 0; i < n - 1; i++) {
        u = choose(distance, n, found);
        if (u == -1) break;
        found[u] = true;
        for (w = 0; w < n; w++) {
            if (!found[w] && cost[u][w] < INT_MAX) {
                if (distance[u] + cost[u][w] < distance[w]) {
                    distance[w] = distance[u] + cost[u][w];
                }
            }
        }
    }

    printf("Distance : ");
    for (i = 0; i < n; i++) {
        printf("%d ", distance[i]);
    }
    printf("\n");

    free(distance);
    free(found);
}

void allcosts(int** cost, int n) {
    int** distance = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; ++i) {
        distance[i] = (int*)malloc(n * sizeof(int));
    }
    int i, j, k;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            distance[i][j] = cost[i][j];

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (distance[i][k] < INT_MAX && distance[k][j] < INT_MAX) {
                    if (distance[i][k] + distance[k][j] < distance[i][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                    }
                }
            }
        }
    }

    print_mtrx(distance, n);

    for (i = 0; i < n; i++) {
        free(distance[i]);
    }
    free(distance);
}

int main() {
	while(1){
		int n;
		printf("11.1. 인접 행렬 형태의 방향성 그래프 생성\n");
		printf("  노드 수 (n) : ");
		scanf("%d", &n);

        if (n == -1)
            break;


		int** G = (int**)malloc(n * sizeof(int*));
		for (int i = 0; i < n; ++i) {
			G[i] = (int*)malloc(n * sizeof(int));
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) {
					G[i][j] = 0;
				} else {
					G[i][j] = INT_MAX;
				}
			}
		}

		int from, to, weight;
		while (1) {
			printf("  에지 정보 (from to weight) : ");
			scanf("%d %d %d", &from, &to, &weight);
			if (from == -1) {
				break;
			}
			G[from][to] = weight;
		}

		printf("  인접 행렬을 이용한 그래프의 구성 :\n");
		print_mtrx(G, n);

		printf("\n11.2. 최단 경로 (단일 출발점)\n");
		int startnode;
		while (1) {
			printf("시작 노드 (v) : ");
			scanf("%d", &startnode);
			if (startnode == -1) {
				break;
			}
			shortestpath(startnode, G, n);
		}

		printf("\n11.3. 최단 경로 (모든 경로)\n");
		printf("  All Path Distance : \n");
		allcosts(G, n);

		for (int i = 0; i < n; i++) {
			free(G[i]);
		}
		free(G);
	}
    return 0;
}