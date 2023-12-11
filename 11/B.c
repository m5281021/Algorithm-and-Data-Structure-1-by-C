#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int ** createGraph(int n) {
    int **graph = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        int u = 0;
        int k = 0;
        scanf("%d%d", &u, &k);
        graph[u - 1] = (int *)malloc((k + 1) * sizeof(int));
        graph[u - 1][0] = k;
        for(int j = 0; j < k; j++) {
            int v = 0;
            scanf("%d", &v);
            graph[u - 1][j + 1] = v - 1;
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

void initialized(int **time, bool *arrived, int n) {
    for(int i = 0; i < n; i++) {
        time[i] = (int *)malloc(n * sizeof(int));
        arrived[i] = false;
        time[i][0] = 0;
        time[i][1] = 0;
    }
}

int DFS(int **graph, int **time, bool *arrived, int cur, int n, int now) {
    arrived[cur] = true;
    time[cur][0] = now;
    for(int i = 0; i < graph[cur][0]; i++) {
        if(arrived[graph[cur][i + 1]]) continue;
        now = DFS(graph, time, arrived, graph[cur][i + 1], n, now + 1);
    }
    now++;
    time[cur][1] = now;
    return now;
}

void print(int **time, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d %d %d\n", i + 1, time[i][0], time[i][1]);
    }
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int **graph = createGraph(n);
    int **time = (int **)malloc(n * sizeof(int *));
    bool *arrived = (bool *)malloc(n * sizeof(bool));
    initialized(time, arrived, n);
    int now = 1;
    for(int i = 0; i < n; i++) {
        if(arrived[i]) continue;
        now = DFS(graph, time, arrived, i, n, now);
        now++;
    }
    print(time, n);
    deleteGraph(graph, n);
    free(time);
    free(arrived);
}

int main() {
    solve();
    return 0;
}