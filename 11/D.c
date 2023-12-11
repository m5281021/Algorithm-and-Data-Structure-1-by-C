#include <stdio.h>
#include <stdlib.h>

void add(int **graph, int a, int b) {
    int k = graph[a][0];
    int *list1 = (int *)malloc(k * sizeof(int));
    for(int i = 0; i < k; i++) {
        list1[i] = graph[a][1 + i];
    }
    free(graph[a]);
    graph[a] = (int *)malloc((k + 2) * sizeof(int));
    graph[a][0] = k + 1;
    for(int i = 0; i < k; i++) {
        graph[a][1 + i] = list1[i];
    }
    graph[a][k + 1] = b;
    free(list1);
}

int ** createGraph(int n, int m) {
    int **graph = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(1 * sizeof(int));
        graph[i][0] = 0;
    }
    for(int i = 0; i < m; i++) {
        int a = 0;
        int b = 0;
        scanf("%d%d", &a, &b);
        add(graph, a, b);
        add(graph, b, a);
    }
    return graph;
}

void deleteGraph(int **graph, int n) {
    for(int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);
}

void initialized(int *colour, int n) {
    for(int i = 0; i < n; i++) {
        colour[i] = -1;
    }
}

void grouping(int **graph, int *colour, int cur, int c) {
    colour[cur] = c;
    for(int i = 0; i < graph[cur][0]; i++) {
        if(colour[graph[cur][1 + i]] == -1) grouping(graph, colour, graph[cur][1 + i], c);
    }
}

void answer(int *colour) {
    int n = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int a = 0;
        int b = 0;
        scanf("%d%d", &a, &b);
        if(colour[a] == colour[b]) printf("yes\n");
        else printf("no\n");
    }
}

void solve() {
    int n = 0;
    int m = 0;
    scanf("%d%d", &n, &m);
    int **graph = createGraph(n, m);
    int *colour = (int *)malloc(n * sizeof(int));
    initialized(colour, n);
    int c = 0;
    for(int i = 0; i < n; i++) {
        if(colour[i] != -1) continue;
        grouping(graph, colour, i, c);
        c++;
    }
    answer(colour);
    deleteGraph(graph, n);
    free(colour);
}

int main() {
    solve();
    return 0;
}