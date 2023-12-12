#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int ** createGraph(int n) {
    int **graph = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        int u = 0;
        int k = 0;
        scanf("%d%d", &u, &k);
        graph[u] = (int *)malloc((2 * k + 1) * sizeof(int));
        graph[u][0] = k;
        for(int j = 0; j < k; j++) {
            int v = 0;
            int c = 0;
            scanf("%d%d", &v, &c);
            graph[u][1 + 2 * j] = v;
            graph[u][2 + 2 * j] = c;
        }
    }
    return graph;
}

void deleteGraph(int **graph, int n) {
    for(int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
}

int * createDistance(int n) {
    int *distance = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        distance[i] = -1;
    }
    return distance;
}

void deleteDistance(int *distance) {
    free(distance);
}

int * calculate(int **graph, int n) {
    int *distance = createDistance(n);
    distance[0] = 0;
    for(int i = 0; i < n - 1; i++) {
        int min = INT_MAX;
        int to = -1;
        for(int j = 0; j < n; j++) {
            if(distance[j] != -1) {
                for(int k = 0; k < graph[j][0]; k++) {
                    int v = graph[j][1 + 2 * k];
                    int c = graph[j][2 + 2 * k];
                    if(distance[v] != -1) continue;
                    if(distance[j] + c < min) {
                        min = distance[j] + c;
                        to = v;
                    }
                }
            }
        }
        distance[to] = min;
    }
    return distance;
}

void print(int **graph, int n) {
    int *distance = calculate(graph, n);
    for(int i = 0; i < n; i++) {
        printf("%d %d\n", i, distance[i]);
    }
    deleteDistance(distance);
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int **graph = createGraph(n);
    print(graph, n);
    deleteGraph(graph, n);
}

int main() {
    solve();
    return 0;
}