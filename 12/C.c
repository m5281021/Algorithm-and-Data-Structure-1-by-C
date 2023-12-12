#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define nullptr NULL

typedef struct {
    int to;
    int cost;
} place;

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

void copy(place *p, int to, int cost) {
    p->to = to;
    p->cost = cost;
}

void swap(place *p, int x, int y) {
    place q;
    copy(&q, p[x].to, p[x].cost);
    copy(&p[x], p[y].to, p[y].cost);
    copy(&p[y], q.to, q.cost);
}

void downMinHeap(place *p, int cur, int n) {
    int left = cur * 2 + 1;
    int right = cur * 2 + 2;
    int smallest = cur;
    if(left < n && p[left].cost < p[smallest].cost) smallest = left;
    if(right < n && p[right].cost < p[smallest].cost) smallest = right;
    if(smallest != cur) {
        swap(p, smallest, cur);
        downMinHeap(p, smallest, n);
    }
}

void upMinHeap(place *p, int cur) {
    if(cur == 0) return;
    int parent = (cur - 1) / 2;
    if(p[parent].cost > p[cur].cost) {
        swap(p, parent, cur);
        upMinHeap(p, parent);
    }
}

void buildUpMinHeap(place *p, int n) {
    for(int i = (n - 1) / 2; i >= 0; i--) {
        downMinHeap(p, i, n);
    }
}

place * extract(place *p, int *n) {
    place *min = (place *)malloc(sizeof(place));
    copy(min, p[0].to, p[0].cost);
    (*n)--;
    copy(&p[0], p[*n].to, p[*n].cost);
    downMinHeap(p, 0, *n);
    return min;
}

place * createHeap(int n) {
    place *heap = (place *)malloc(n * n * sizeof(place));
    return heap;
}

void deleteHeap(place *p) {
    free(p);
}

void initialized(int *distance, bool *flag, int n) {
    for(int i = 0; i < n; i++) {
        distance[i] = INT_MAX;
        flag[i] = false;
    }
}

int * calculate(int **graph, int n) {
    int *distance = (int *)malloc(n * sizeof(int));
    bool *flag = (bool *)malloc(n * sizeof(bool));
    initialized(distance, flag, n);
    place *heap = createHeap(n);
    int v = 1;
    copy(&heap[0], 0, 0);
    buildUpMinHeap(heap, v);
    distance[0] = 0;
    while(v != 0) {
        place *min = extract(heap, &v);
        flag[min->to] = true;
        if(min->cost > distance[min->to]) continue;
        for(int j = 0; j < graph[min->to][0]; j++) {
            if(flag[graph[min->to][1 + 2 * j]]) continue;
            if(distance[min->to] + graph[min->to][2 + 2 * j] < distance[graph[min->to][1 + 2 * j]]) {
                distance[graph[min->to][1 + 2 * j]] = distance[min->to] + graph[min->to][2 + 2 * j];
                copy(&heap[v++], graph[min->to][1 + 2 * j], distance[graph[min->to][1 + 2 * j]]);
                upMinHeap(heap, v - 1);
            }
        }
        free(min);
    }
    deleteHeap(heap);
    free(flag);
    return distance;
}

void print(int **graph, int n) {
    int *distance = calculate(graph, n);
    for(int i = 0; i < n; i++) {
        printf("%d %d\n", i, distance[i]);
    }
    free(distance);
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