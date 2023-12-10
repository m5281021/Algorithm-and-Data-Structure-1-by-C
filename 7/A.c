#include <stdio.h>
#include <stdlib.h>

#define nullptr NULL

typedef struct {
    int id;
    int parent;
    int child;
    int *children;
    int depth;
    char *type;
} node;

void initialize(node *nodes, int n) {
    for(int i = 0; i < n; i++) {
        nodes[i].id = i;
        nodes[i].parent = -1;
        nodes[i].child = 0;
        nodes[i].depth = 0;
    }
}

void getNodes(node *nodes, int n) {
    initialize(nodes, n);
    for(int i = 0; i < n; i++) {
        int id = 0;
        scanf("%d", &id);
        int num = 0;
        scanf("%d", &num);
        nodes[id].id = id;
        nodes[id].child = num;
        nodes[id].children = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < num; j++) {
            int child = 0;
            scanf("%d", &child);
            nodes[id].children[j] = child;
            nodes[child].parent = id;
        }
    }
}

int getRoot(node *nodes) {
    int i = 0;
    while(nodes[i].parent != -1) {
        i = nodes[i].parent;
    }
    return i;
}

void determine(node *nodes, int id) {
    if(nodes[id].parent == -1) {
        nodes[id].type = "root";
        nodes[id].depth = 0;
    }
    else if(nodes[id].child == 0) {
        nodes[id].type = "leaf";
        nodes[id].depth = nodes[nodes[id].parent].depth + 1;
    }
    else {
        nodes[id].type = "internal node";
        nodes[id].depth = nodes[nodes[id].parent].depth + 1;
    }
    for(int i = 0; i < nodes[id].child; i++) {
        determine(nodes, nodes[id].children[i]);
    }
}

void print(node *nodes, int n) {
    for(int i = 0; i < n; i++) {
        printf("node %d: parent = %d, depth = %d, %s, [", nodes[i].id, nodes[i].parent, nodes[i].depth, nodes[i].type);
        for(int j = 0; j < nodes[i].child; j++) {
            printf("%d", nodes[i].children[j]);
            if(j != nodes[i].child - 1) printf(", ");
        }
        printf("]\n");
        free(nodes[i].children);
        nodes[i].type = nullptr;
    }
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    node *nodes = (node *)malloc(n * sizeof(node));
    getNodes(nodes, n);
    determine(nodes, getRoot(nodes));
    print(nodes, n);
    free(nodes);
}

int main() {
    solve();
    return 0;
}