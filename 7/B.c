#include <stdio.h>
#include <stdlib.h>

#define nullptr NULL

typedef struct {
    int id;
    int parent;
    int sibling;
    int child;
    int left;
    int right;
    int depth;
    int height;
    char *type;
} node;

void initialized(node *nodes, int n) {
    for(int i = 0; i < n; i++) {
        nodes[i].id = i;
        nodes[i].parent = -1;
        nodes[i].sibling = -1;
        nodes[i].child = 0;
        nodes[i].left = -1;
        nodes[i].right = -1;
        nodes[i].depth = 0;
        nodes[i].height = 0;
        nodes[i].type = nullptr;
    }
}

void getNodes(node *nodes, int n) {
    initialized(nodes, n);
    for(int i = 0; i < n; i++) {
        int id = 0;
        int left = 0;
        int right = 0;
        scanf("%d%d%d", &id, &left, &right);
        nodes[id].id = id;
        nodes[id].left = left;
        if(left != -1) {
            nodes[left].parent = id;
            nodes[id].child++;
        }
        nodes[id].right = right;
        if(right != -1) {
            nodes[right].parent = id;
            nodes[id].child++;
        }
    }
}

int getRoot(node *nodes) {
    int id = 0;
    while(nodes[id].parent != -1) {
        id = nodes[id].parent;
    }
    return id;
}

void determine(node *nodes, int id) {
    if(nodes[id].parent == -1) {
        nodes[id].type = "root";
        nodes[id].depth = 0;
    }
    else if(nodes[id].child == 0) {
        nodes[id].type = "leaf";
        nodes[id].depth = nodes[nodes[id].parent].depth + 1;
        nodes[id].height = 0;
        return;
    }
    else {
        nodes[id].type = "internal node";
        nodes[id].depth = nodes[nodes[id].parent].depth + 1;
    }
    int left = nodes[id].left;
    int right = nodes[id].right;
    if(nodes[id].child == 2) {
        nodes[left].sibling = right;
        nodes[right].sibling = left;
    }
    int height = -1;
    if(left != -1) {
        determine(nodes, left);
        if(height < nodes[left].height) height = nodes[left].height;
    }
    if(right != -1) {
        determine(nodes, right);
        if(height < nodes[right].height) height = nodes[right].height;
    }
    nodes[id].height = height + 1;
}

void print(node *nodes, int n) {
    for(int i = 0; i < n; i++) {
        printf("node %d: parent = %d, sibling = %d, degree = %d, depth = %d, height = %d, %s\n", nodes[i].id, nodes[i].parent, nodes[i].sibling, nodes[i].child, nodes[i].depth, nodes[i].height, nodes[i].type);
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