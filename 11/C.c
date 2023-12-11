#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *container;
    int size;
    int head;
    int tail;
} queue;

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

void initialized(int *distance, bool *arrived, int n) {
    for(int i = 0; i < n; i++) {
        arrived[i] = false;
        distance[i] = -1;
    }
}

queue * createQueue() {
    const int max = 10000;
    queue *q = (queue *)malloc(sizeof(queue));
    q->container = (int *)malloc(max * sizeof(int));
    q->size = max;
    q->head = 0;
    q->tail = 0;
    return q;
}

void deleteQueue(queue *q) {
    free(q->container);
    free(q);
}

void push(queue *q, int key) {
    q->container[q->tail++] = key;
    q->tail %= q->size;
}

int pop(queue *q) {
    int a = q->container[q->head++];
    q->head %= q->size;
    return a;
}

bool isEmpty(queue *q) {
    if(q->tail == q->head) return true;
    else return false;
}

int * createDistance(int **graph, int n) {
    bool *arrived = (bool *)malloc(n * sizeof(bool));
    int *distance = (int *)malloc(n * sizeof(int));
    initialized(distance, arrived, n);
    queue *q = createQueue();
    push(q, 0);
    distance[0] = 0;
    arrived[0] = true;
    while(!isEmpty(q)) {
        int cur = pop(q);
        for(int i = 0; i < graph[cur][0]; i++) {
            int v = graph[cur][1 + i];
            if(arrived[v]) continue;
            arrived[v] = true;
            distance[v] = distance[cur] + 1;
            push(q, v);
        }
    }
    free(arrived);
    deleteQueue(q);
    return distance;
}

void deleteDistance(int *distance) {
    free(distance);
}

void print(int *distance, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d %d\n", i + 1, distance[i]);
    }
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int **graph = createGraph(n);
    int *distance = createDistance(graph, n);
    print(distance, n);
    deleteGraph(graph, n);
    deleteDistance(distance);
}

int main() {
    solve();
    return 0;
}