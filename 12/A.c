#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int ** createGraph(int n) {
    int **graph = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++) {
            int w = 0;
            scanf("%d", &w);
            if(w == -1) graph[i][j] = INT_MAX;
            else graph[i][j] = w;
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

bool * createFlag(int n) {
    bool *flag = (bool *)malloc(n * sizeof(bool));
    for(int i = 0; i < n; i++) {
        flag[i] = false;
    }
    return flag;
}

void deleteFlag(bool *flag) {
    free(flag);
}

int minimize(int **graph, int n) {
    bool *flag = createFlag(n);
    flag[0] = true;
    int cost = 0;
    for(int i = 0; i < n - 1; i++) {
        int min = INT_MAX;
        int to = -1;
        for(int j = 0; j < n; j++) {
            if(flag[j]) {
                for(int k = 0; k < n; k++) {
                    if(flag[k]) continue;
                    if(min > graph[j][k]) {
                        min = graph[j][k];
                        to = k;
                    }
                }
            }
        }
        flag[to] = true;
        cost += min;
    }
    deleteFlag(flag);
    return cost;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int **graph = createGraph(n);
    printf("%d\n", minimize(graph, n));
    deleteGraph(graph, n);
}

int main() {
    solve();
    return 0;
}